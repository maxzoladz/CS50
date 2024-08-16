import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, get_time

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)
    cashLeft = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    if cashLeft and "cash" in cashLeft[0]:
        cashLeft = float(cashLeft[0]["cash"])
    else:
        cashLeft = 0.0

    totalAmount = cashLeft

    try:
        for stock in portfolio:
            symbol = stock["symbol"]
            stockInfo = lookup(symbol)

            currentPrice = float(stockInfo["price"])
            stockValue = currentPrice * stock["shares"]

            stock.update({"currentPrice": currentPrice, "stockValue": stockValue})
            totalAmount += float(stock["stockValue"])

    except (ValueError, LookupError):
        return apology("Could not update stock prices!", 404)

    return render_template("index.html", portfolio=portfolio, cashLeft=cashLeft, totalAmount=totalAmount)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        user_id = session["user_id"]

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        stock = lookup(symbol)

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        elif not request.form.get("shares"):
            return apology("must provide quantity of shares", 403)

        stockCheck = lookup(str(request.form.get("symbol")))

        if not stockCheck:
            return apology("Enter a valid Symbol!", 406)

        stock = lookup(symbol)

        transactionValue = int(shares) * stock["price"]

        userCash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        userCash = userCash[0]["cash"]

        if transactionValue > userCash:
            return apology("Not enough money!", 408)

        updateUserCash = userCash - transactionValue
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updateUserCash, user_id)

        balance = f"${updateUserCash:,.2f} (-${transactionValue:,.2f})"

        db.execute(
            "INSERT INTO history (user_id, symbol, shares, action, balance, date) VALUES (?, ?, ?, ?, ?, ?)",
            user_id,
            stock["symbol"],
            shares,
            "Buy",
            balance,
            get_time(),
        )

        balance = f"${updateUserCash:,.2f}"

        db.execute(
            "INSERT INTO portfolio (user_id, symbol, shares, paidPrice, currentPrice, stockValue) VALUES (?, ?, ?, ?, ?, ?)",
            user_id,
            symbol,
            shares,
            stock["price"],
            stock["price"],
            stock["price"],
        )

        flash(f"Successfully bought {shares} shares of {symbol.upper()}!")

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)

    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        stock = lookup(str(request.form.get("symbol")))

        if not stock:
            return apology("Enter a valid Symbol!", 406)

        stock["price"] = usd(stock["price"])

        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("confirmPassword"):
            return apology("must confirm password", 403)

        username = request.form.get("username")
        password = request.form.get("password")
        confirmPassword = request.form.get("confirmPassword")

        hashedPassword = generate_password_hash(password)

        if password == confirmPassword:
            try:
                db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashedPassword)
            except ValueError:
                return apology("username already taken", 420)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        shares = int(request.form.get("shares"))

        ownedStock = db.execute(
            "SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?",
            user_id,
            symbol,
        )

        if not ownedStock:
            return apology(f"You don't own any shares of {symbol}!")

        currentShares = sum([stock["shares"] for stock in ownedStock])
        if currentShares < shares:
            return apology("You don't have enough shares to sell!")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = cash[0]["cash"]

        currentPrice = stock["price"]
        cash += shares * currentPrice

        for info in ownedStock:

            if info["shares"] > shares:
                db.execute(
                    "UPDATE portfolio SET shares = ? WHERE user_id = ? AND symbol = ?",
                    info["shares"] - shares,
                    user_id,
                    symbol,
                )

            else:
                db.execute(
                    "DELETE FROM portfolio WHERE user_id = ? AND symbol = ?",
                    user_id,
                    symbol,
                )

        balance = f"${cash:,.2f} (+${(shares * currentPrice):,.2f})"

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        db.execute(
            "INSERT INTO history (user_id, symbol, shares, action, balance, date) VALUES (?, ?, ?, ?, ?, ?)",
            user_id,
            symbol,
            shares,
            "Sell",
            balance,
            get_time(),
        )

        flash(f"Successfully sold {shares} shares of {symbol.upper()}!")
        return redirect("/")

    return render_template("sell.html", portfolio=portfolio)

@app.route("/profile", methods=["GET", "POST"])
def profile():
    """Profile Management"""

    user_id = session["user_id"]

    if request.method == "POST":

        if not request.form.get("currentPassword"):
            return apology("must provide current password", 403)

        elif not request.form.get("newPassword"):
            return apology("must provide new password", 403)

        elif not request.form.get("confirmNewPassword"):
            return apology("must confirm new password", 403)

        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("currentPassword")
        ):
            return apology("invalid password", 403)

        password = request.form.get("newPassword")
        confirmPassword = request.form.get("confirmNewPassword")

        if password == confirmPassword:
            hashedPassword = generate_password_hash(password)
            db.execute("UPDATE users SET hash = ? WHERE id = ?", hashedPassword, user_id)
            session.clear()
            return redirect("/login")
        else:
            return apology("Passwords do not match!", 403)


    name = db.execute("SELECT username FROM users WHERE id = ?", user_id)
    name = name[0]["username"]

    return render_template("profile.html", name=name)

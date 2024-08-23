while True:
    try:
        cardNumberInt = int(input("Enter Card Number: "))
        break
    except ValueError:
        print("INVALID")
        continue

cardNumberLength = len(str(cardNumberInt))

if cardNumberLength < 13 or cardNumberLength > 16 or cardNumberLength == 14:
    print("INVALID")
else:
    cardNumber = str(cardNumberInt)
    checksum = 0

    for secondToLast in range(cardNumberLength - 2, -1, -2):
        digit = int(cardNumber[secondToLast]) * 2
        if digit >= 10:
            checksum += (digit // 10) + (digit % 10)
        else:
            checksum += digit

    for last in range(cardNumberLength - 1, -1, -2):
        checksum += int(cardNumber[last])

    if checksum % 10 == 0:
        print("Carrier: ", end="")
        if cardNumberLength == 15 and (cardNumberInt // 10 ** 13 == 34 or cardNumberInt // 10 ** 13 == 37):
            print("AMEX")
        elif (cardNumberLength == 16 or cardNumberLength == 13) and cardNumberInt // 10 ** (cardNumberLength - 1) == 4:
            print("VISA")
        elif cardNumberLength == 16 and 51 <= cardNumberInt // 10 ** 14 <= 55:
            print("MASTERCARD")
    else:
        print("INVALID")

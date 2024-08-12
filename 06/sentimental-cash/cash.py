while True :
    try:
        change = int(input("Change Owed: "))
        break
    except ValueError:
        pass

coinCounter = 0

while change >= 25:
    change -= 25
    coinCounter += 1

while change >= 10:
    change -= 10
    coinCounter += 1

while change >= 5:
    change -= 5
    coinCounter += 1

while change >= 1:
    change -= 1
    coinCounter += 1

print(coinCounter)
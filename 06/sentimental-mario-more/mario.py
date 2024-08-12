while True :
    try:
        height = int(input("Enter Height: "))
        if height > 0 and height < 8:
            break
    except ValueError:
        pass

spaces = height - 1

print()

for i in range(height):

    for j in range(spaces):
        print(" ", end="")

    spaces -= 1

    for k in range(i + 1):
        print("#", end="")

    print("  ", end="")

    for m in range(i + 1):
        print("#", end="")

    print()



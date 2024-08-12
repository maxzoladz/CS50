while True :
    try:
        height = int(input("Enter Height: "))
        if height > 0 and height < 8:
            break
    except ValueError:
        pass

spaces = height - 1

print()

for counter in range(height):

    for spacesCounter in range(spaces):
        print(" ", end="")

    spaces -= 1

    for leftPyramidCounter in range(counter + 1):
        print("#", end="")

    print("  ", end="")

    for rightPyramidCounter in range(counter + 1):
        print("#", end="")

    print()



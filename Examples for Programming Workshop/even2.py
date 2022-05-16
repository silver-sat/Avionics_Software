# Odd or even exercise

# Ask user for a number

while True:
    try:
        number = int(input("Please enter a number: "))
        break
    except ValueError:
        print("That was not a valid number. Try again...")


# Decide if it is odd or even

if (number % 2 == 0):

# Print the result

    print ("That number is even")
else:
    print ("That number isn't even")


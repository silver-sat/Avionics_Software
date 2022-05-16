# Print the divisors of a number

# get the number

while True:
    try:
        number = int(input("Please enter a number: "))
        break
    except ValueError:
        print("That was not a valid number. Try again...")

# for everything less than the number, see if it divides evenly

for test_number in range(1, number // 2 + 1):
    if (number % test_number == 0):

# if so, print the number

        print(test_number, " is a divisor")
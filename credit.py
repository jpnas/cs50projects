from cs50 import get_int

cardnumber = get_int("Number: ")

count = 0
digits = cardnumber
while digits >= 1:
    digits = digits/10
    count += 1
    
if count != 13 and count != 15 and count != 16:
    print("INVALID")
    exit()

figures = []
for i in range(count):
    figures.append(cardnumber % 10)
    cardnumber = int((cardnumber - cardnumber % 10) / 10)

sum1 = 0
for i in range(count):
    if i % 2 == 1:
        x = figures[i] * 2
        while x >= 1:
            sum1 = sum1 + (x % 10)
            x = (x - x % 10) / 10

sum2 = 0
for i in range(count):
    if i % 2 == 0:
        sum2 = sum2 + figures[i]

if (sum1 + sum2) % 10 != 0:
    print("INVALID")
    exit()
    
if count == 15:
    if figures[14] == 3 and figures[13] == 4 or figures[13] == 7:
        print("AMEX")
        exit()

if count == 13:
    if figures[12] == 4:
        print("VISA")
        exit()

if count == 16:
    if figures[15] == 4:
        print("VISA")
        exit()
    if figures [15] == 5 and figures[14] <= 5:
        print("MASTERCARD")
        exit()
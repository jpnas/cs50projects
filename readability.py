from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if text[i] >='a' and text[i] <= 'z' or text[i] >='A' and text[i] <= 'Z':
        letters += 1
    elif text[i] == ' ':
        words += 1
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1

index = 0.0588 *  (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8

if round(index) < 1:
    print("Before Grade 1")

elif round(index) >= 16:
    print("Grade 16+")

else:
    print(f"Grade {round(index)}")

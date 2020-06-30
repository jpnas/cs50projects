from cs50 import SQL
import sys

if len(sys.argv) != 2:
    print("Usage: python roster.py House")
    exit()
    
db = SQL("sqlite:///students.db")

house = sys.argv[1]

for i in db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", house):
    if i['middle'] == None:
        print(i['first'] + " " + i['last'] + ", born " + str(i['birth']))
    else:
        print(i['first'] + " " + i['middle'] + " " + i['last'] + ", born " + str(i['birth']))

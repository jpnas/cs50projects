import csv
from cs50 import SQL
import sys

if len(sys.argv) != 2:
    print("Usage: python import.py file.csv")
    exit()
    
db = SQL("sqlite:///students.db")

with open(sys.argv[1], 'r') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    
    for line in csv_reader:
        name = line["name"].split()
        house = line["house"]
        birth = line["birth"]
        
        if len(name) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name[0], name[1], name[2], house, birth)
        elif len(name) == 2: 
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name[0], None, name[1], house, birth)
        
        
        
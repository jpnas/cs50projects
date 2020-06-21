import csv
import sys

if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
database = sys.argv[1]
sequence = sys.argv[2]

with open(sequence, 'r') as csv_sequence:
    csv_reader = csv.reader(csv_sequence)

    for line in csv_reader:
        dna = line[0]

with open(database, 'r') as csv_database:
    database_reader = csv.reader(csv_database)
    data = []

    for line in database_reader:
        data.append(line)

dnavalues = []

for str in data[0][1:]:
    values = []
    for i in range(len(dna)):
        a = 0
        n = i
        value = 0
        while a == 0:
            if dna[n:n+len(str)] == str:
                value += 1
                n += len(str)
            else:
                values.append(value)
                a += 1
    dnavalues.append((max(values)))

for i in range(len(data) - 1):
    for j in range(len(dnavalues)):
        data[i + 1][j + 1] = int(data[i + 1][j + 1])



for i in range(len(data[1:])):
    if data[i][1:1+len(dnavalues)] == dnavalues:
        print(data[i][0])
        exit()

print("No match")
import numpy as np
def parse(fileName):
	fichier = open(fileName,"r")
	counter = 0
	sudoku = []
	newLine = []
	newCase = []
	for line in fichier:
		line = line[0:len(line)-1]
		newLine = line.split("|")
		sudoku.append([])
		for i in range(len(newLine)):
			newCase  = newLine[i].split(" ")
			sudoku[-1].append(newCase)
	sudoku = np.array(sudoku)
	print(sudoku)

for i 
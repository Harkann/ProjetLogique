import sys                


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
	print(sudoku)

def convert (sudoku):
	










if (sys.argv):
	try :
		if (".input" in sys.argv[1]):
			parse(sys.argv[1])
		else :
			print("[Error] : file name must end by .input")
	except :
		print("[Error] : Missing input file")
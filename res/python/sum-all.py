#!/home/agostini/anaconda3/bin/python
import fileinput
import numpy as np


def main():
	myList = [line.strip() for line in fileinput.input()]
	#myList = map(int,myList)

	myList=np.array(myList,dtype=np.uint8)
	print(sum(myList[3:-1]))


if __name__ == "__main__":
    main()

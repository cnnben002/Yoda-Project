#Yoda Project
#Group 1
#Benjamin Connolly
#18/05/2022

#Importing necessary libraries
from numpy import asarray
import numpy as np

#Opening the txt files
fname = input("Please type .txt reference file:\n")
f1 = open(fname, "r")
fname = input("Please type .txt comparison file:\n")
f2 = open(fname, "r")

#Getting files dimensions
line1 = f1.readline().strip()
rows1 = int(line1)
line1 = f1.readline().strip()
cols1 = int(line1)

line2 = f2.readline().strip()
rows2 = int(line2)
line2 = f2.readline().strip()
cols2 = int(line2)

#Comparing images
if (rows1 != rows2 or rows1 != rows2):
    print("Error: File dimensions do not match")

else:
    sum = 0
    rgb = False
    for i in range(rows1*cols1):
        line1 = f1.readline().strip()
        line2 = f2.readline().strip()
        if len(line1)<=4:
            sum += (float(line1)+1)/(float(line2)+1)
	else:
            s1 = line1.split(" ")
            s2 = line2.split(" ")
            sum += (float(s1[0])+1)/(float(s2[0])+1)
            sum += (float(s1[1])+1)/(float(s2[1])+1)
            sum += (float(s1[2])+1)/(float(s2[2])+1)
            rgb = True

    #Printing the  output
    if rgb != True:
        print("The % accuracy of the image is: ")
        print(sum/(rows1*cols1)*100)
    else:
        print("The % accuracy of the image is: ")
        print(sum/(rows1*cols1*3)*100)

f1.close()
f2.close()


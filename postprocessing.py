#Yoda Project
#Group 1
#Benjamin Connolly
#12/05/2022

#Importing necessary libraries
from PIL import Image
from numpy import asarray
import numpy as np

#Opening the txt file
fname = input("Please type in file to be converted:\n")
f = open(fname, "r")

#Getting file dimensions
line = f.readline().strip()
rows = int(line)
line = f.readline().strip()
cols = int(line)

#Creating array for image
data = np.zeros((rows, cols, 3), dtype=np.uint8)

#Converting the txt file to an array
for i in range(rows):
    for j in range(cols):
        line = f.readline().strip()
        if len(line)<=4:
            data[i][j][0] = int(line)
            data[i][j][1] = int(line)
            data[i][j][2] = int(line)
        else:
            s = line.split(" ")
            data[i][j][0] = int(s[0])
            data[i][j][1] = int(s[1])
            data[i][j][2] = int(s[2])
f.close()
print("File conversion done...")

#Data shape
#print(data.shape)

#Converting array to image
image = Image.fromarray(data, 'RGB')
print("Image conversion done...")

#Saving the image
image.save('processedYoda.png')
print("Image saved.")

#Yoda Project
#Group 1
#Benjamin Connolly
#12/05/2022

#Importing necessary libraries
from PIL import Image
from numpy import asarray

#Opening the image
image = Image.open("yoda.jpg")

#Getting image properties
format = image.format
col, row = image.size

print("Format: " + str(format))
print("Width: " + str(col))
print("Height: " + str(row))

#Getting array of data
data = asarray(image)

print(data.shape)
print("Image conversion done...")

#Saving the array to a txt file
f = open("imageData.txt", "w")

s = str(row)+"\n"
f.write(s)
s = str(col)+"\n"
f.write(s)

print("Writing file...")

for x in range(row):
    for y in range(col):
        s = ""
        for i in range(3):
            s += str(data[x][y][i])
            s += " "
        s += "\n"
        f.write(s)
f.close()

print("File saved.")

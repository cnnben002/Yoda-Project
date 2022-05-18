# Yoda Project
## Intro 
The following project allows for appling a median filter and edge detector to images.
This can be done by following these steps:
1) Run preprocessing.py to preprocess the image 
2) Compile and run medianFilter.cpp file in the MedianFilter folder to apply a median filter to the image
3) Compile and run edgeDetector.cpp file in the EdgeDetection folder to apply a edge detector filter to the image
4) Run postprocessing.py and select the "medianImageData.txt" file to get the median filtered image
5) Run postprocessing.py and select the "edgeImageData.txt" file to get the median filtered image

## Preprocessing 
Preprocessing is done using the preprocessing.py file and is run in python. This takes an image and converts it into a .txt file for use in the filtering stages of the code. The program allows you to select your image by typing it into the terminal and saves the output to a file called imageData.txt.

## Median Filtering
Median filtering is done using the medianFilter.cpp file in the MedianFilter folder and is run in C++. This takes an .txt image file and applies a median filter algorithm to it. The program selects the prepoccesed image imageData.txt file and saves the filtered image to a file called medianImageData.txt. This program makes use of OpenCL to utilise parallel processing capabilities. There is also a golden measure implementation of this program, that does not make use of parallel processing, to provide a benchmark for the system. The golden measure saves the output to a file called gsMedianImageData.txt.

## Edge Detector Filtering
Edge detector filtering is done using the edgeDetector.cpp file in the edgeDetector folder and is run in C++. This takes an .txt image file and applies a edge detection filter algorithm to it. The program selects the median filtering image medianImageData.txt file and saves the edge detection filtered image to a file called edgeImageData.txt. This program makes use of OpenCL to utilise parallel processing capabilities. There is also a golden measure implementation of this program, that does not make use of parallel processing, to provide a benchmark for the system. The golden measure saves the output to a file called gsEdgeImageData.txt.

## Postprocessing 
Postprocessing is done using the postprocessing.py file and is run in python. This takes an image in .txt format and converts it into a .png image. The program allows you to select your input file and name your output file by typing it into the terminal.

## Postprocessing Batch
There is also a postprocessingbatch.py file which can be run in python. It does the exact same thing as the postprocessing.py file, but does all image conversions from both the edge and median filtering files, including the golden measures, and also doesnt allow you to pick names.  

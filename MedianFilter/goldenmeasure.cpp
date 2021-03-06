#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <tuple>
#include <bits/stdc++.h>
using namespace std;

void getImageDimensions(string fname, int* dimensions) // reading in dimensions of preprocessed data
{
        fstream file;
        file.open(fname,ios::in);

        if (file.is_open())
        {
                string line;
                bool test1 = true;
                bool test2 = true;
                while(getline(file, line))
                {
                        if(test1)
                        {
                                dimensions[0] = stoi(line);
                                test1 = false;
                        }
                        else if(test2)
                        {
                                dimensions[1] = stoi(line);
                                test2 = false;
                        }
                        else
                        {
                                break;
                        }
                }

                file.close();
        }
}

int main(void)
{
	clock_t begin = clock(); //timer begin 
	


	cout << "Golden standard median filter...\n";

        //Initilising variables
        bool displayMatrix = false;
        int dimensions[2];
	string fname = "../imageData.txt"; //data file

        getImageDimensions(fname, dimensions); //image dimensions

        int cols = dimensions[0]; 
        int rows = dimensions[1];
	int items = rows*cols;
	int imageMatrixR[items]; //colour layer individual arrays
	int imageMatrixG[items];
	int imageMatrixB[items];

	cout << "Variables initliased...\n";

	//Getting data from preprocessed image
	fstream file;
        file.open(fname,ios::in);

        if (file.is_open())//taking data from image data text file
        {
                int pos = -2;
                string line;
                bool test1 = true;
                bool test2 = true;

                while(getline(file, line))
                {
                        if(test1)
                        {
                                test1 = false;
                        }
                        else if(test2)
                        {
                                test2 = false;
                        }
                        else
                        {
                                bool testR = true;
                                bool testG = true;
                                int n = line.length();
                                string s = "";

                                for(int i = 0; i < n; i++)
                                {
                                        if(line[i] != ' ')
                                        {
                                                s += line[i];
                                        }
                                        else if(testR)
                                        {
                                                imageMatrixR[pos] = stoi(s);
                                                s = "";
                                                testR = false;
                                        }
                                        else if(testG)
                                        {
                                                imageMatrixG[pos] = stoi(s);
                                                s = "";
                                                testG = false;
                                        }
                                }

                                imageMatrixB[pos] = stoi(s);
                        }
                        pos += 1;
                }

                file.close();
        }

	cout << "Image data read in...\n\n";
	clock_t beginf = clock();// begining processing and  hence processing timer
	
	int pos;

	
	
	int out[items][3]; //output array of length items and depth of the three colour layers 
        
	int w = cols;
	//row iteration
	for (int r = 0; r < rows; r++){ 
		//col iteration
		for (int c = 0; c < cols; c++){
        		pos = r*cols+c;
			int i = pos;
			if ((r != 0)&&(r != (rows-1))&&(c != 0)&&(c != (cols-1))){//accounting for edgecases
			//create sub array of the elements surronding each red pixel
				int pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22; 
				pixel00 = imageMatrixR[pos - 1 - cols] ;
                                pixel01 = imageMatrixR[pos - cols] ;
                                pixel02 = imageMatrixR[pos + 1 - cols] ;
                                pixel10 = imageMatrixR[pos - 1] ;
                                pixel11 = imageMatrixR[pos] ;
                                pixel12 = imageMatrixR[pos + 1] ; 
                                pixel20 = imageMatrixR[pos - 1 + cols] ;
                                pixel21 = imageMatrixR[pos + cols] ;
                                pixel22 = imageMatrixR[pos + 1 + cols] ;
                                int filterVector[9] = {pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22};
                                for (int x = 0; x < 9; x++) { //simple sorting function
                                    for(int j = x+ 1; j < 9; j++){
                                        if (filterVector[x] > filterVector[j]) {
                                            int tmp = filterVector[x];
                                            filterVector[x] = filterVector[j];
                                            filterVector[j] = tmp;
                                        }
                                    }
                                }
				//create sub array of the elements surronding each green pixel
				 int pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22;
                                 pixelG00 =  imageMatrixG[i - 1 - w] ;
                                 pixelG01 =  imageMatrixG[i - w] ;
                                 pixelG02 =  imageMatrixG[i + 1 - w] ;
                                 pixelG10 =  imageMatrixG[i - 1] ;
                                 pixelG11 =  imageMatrixG[i] ;
                                 pixelG12 =  imageMatrixG[i + 1] ;
                                 pixelG20 =  imageMatrixG[i - 1 + w] ;
                                 pixelG21 =  imageMatrixG[i + w] ;
                                 pixelG22 =  imageMatrixG[i + 1 + w] ;
                                 int filterVectorG[9] = {pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22};
                                 for (int xG = 0; xG < 9; xG++) { //simple sorting function
                                     for(int jG = xG+ 1; jG < 9; jG++){
                                         if (filterVectorG[xG] > filterVectorG[jG]) {
                                             int tmpG = filterVectorG[xG];
                                             filterVectorG[xG] = filterVectorG[jG];
                                             filterVectorG[jG] = tmpG;
                                         }
                                     }
                                 }
//create sub array of the elements surronding each bluepixel
                                 int pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22;
                                 pixelB00 =  imageMatrixB[i - 1 - w] ;
                                 pixelB01 =  imageMatrixB[i - w] ;
                                 pixelB02 =  imageMatrixB[i + 1 - w] ;
                                 pixelB10 =  imageMatrixB[i - 1] ;
                                 pixelB11 =  imageMatrixB[i] ;
                                 pixelB12 =  imageMatrixB[i + 1] ;
                                 pixelB20 =  imageMatrixB[i - 1 + w] ;
                                 pixelB21 =  imageMatrixB[i + w] ;
                                 pixelB22 =  imageMatrixB[i + 1 + w] ;
                                 int filterVectorB[9] = {pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22};
                                 for (int xB = 0; xB < 9; xB++) { //simple sorting function
                                     for(int jB = xB+ 1; jB < 9; jB++){
                                         if (filterVectorB[xB] > filterVectorB[jB]) {
                                             int tmpB = filterVectorB[xB];
                                             filterVectorB[xB] = filterVectorB[jB];
                                             filterVectorB[jB] = tmpB;
                                         }
                                     }
                                 }

				out[pos][0] = (filterVector[4]);//median pixel at position 4
				out[pos][1] = (filterVectorG[4]);
				out[pos][2] = (filterVectorB[4]);
			}else{
				out[pos][0] = imageMatrixR[pos];//add edge cases to output
				out[pos][1] = imageMatrixG[pos];
				out[pos][2] = imageMatrixB[pos];
			}
		}
	}
	clock_t endf = clock();//end timer 
	cout << "edge detection complete...\n\n";

	ofstream outFile("../gsMedianImageData.txt"); //output file

	outFile << rows << "\n";
	outFile << cols << "\n";

	for(int i = 0; i < items; i ++) //loop through array and output
	{
  		outFile << out[i][0] << " " << out[i][1] << " " << out[i][2] <<"\n";
	}

  	outFile.close();
	
	clock_t end = clock();
        double runtime = (double)(end-begin)*1000/CLOCKS_PER_SEC;
        double filterRuntime = (double)(endf-beginf)*1000/CLOCKS_PER_SEC;

	//runtime
        cout << "Program runtime: " << runtime << " ms\n";
        cout << "Filter runtime: " << filterRuntime << " ms\n";
        cout << "Overhead runtime: " << runtime-filterRuntime << " ms\n";

	return 0;
}

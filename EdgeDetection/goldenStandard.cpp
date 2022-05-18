#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <tuple>
using namespace std;

//Reads in the image dimensions from the image preprocessing
void getImageDimensions(string fname, int* dimensions)
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
	int sobx[3][3] = { {-1, 0, 1},
                           {-2, 0, 2},
                           {-1, 0, 1} };

	int soby[3][3] = { {-1,-2,-1},
                           { 0, 0, 0},
                           { 1, 2, 1} };

	cout << "Golden standard edge detection...\n";

        //Initilising variables
        bool displayMatrix = false;
        int dimensions[2];
	string fname = "../imageData.txt";
	//retrieving image dimensions
        getImageDimensions(fname, dimensions);
	//indeces
        int cols = dimensions[0];
        int rows = dimensions[1];
	int items = rows*cols;
	//local matrices for individual colour values
	int imageMatrixR[items];
	int imageMatrixG[items];
	int imageMatrixB[items];

	cout << "Variables initliased...\n";

	//Getting data from preprocessed image
	fstream file;
        file.open(fname,ios::in);
        if (file.is_open())
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

	//greyscale matrix and relative position
	int Grey[items];
	int pos;
	clock_t begin = clock();

	//converting to greyscale
	for (int i = 0; i < items; i++){
                Grey[i] = round(0.299*imageMatrixR[i]+0.587*imageMatrixG[i]+0.114*imageMatrixB[i]);
        }

	cout << "Image data converted to greyscale...\n\n";

	//Edge detection
	int sumx = 0, sumy = 0, angle = 0;
	int p;
       	int k;
	int out[items];

	//row iteration
	for (int r = 0; r < rows; r++){
		//col iteration
		for (int c = 0; c < cols; c++){
			//calculating possition in linear array
			pos = r*cols+c;
			//ignoring outer rows and columbs
			if ((r != 0)&&(r != (rows-1))&&(c != 0)&&(c != (cols-1))){
				//finding surounding values
				sumx = 0;
				sumy = 0;
				p = -1;
				for (int i = 0; i < 3; i++){
					k = -1;
					for (int j = 0; j < 3; j++){
						sumx += sobx[i][j]*Grey[pos+p*cols+k];
						sumx += soby[i][j]*Grey[pos+p*cols+k];
						k = k+1;
					}
					p = p+1;
				}
				out[pos] = min(255,max(0, (int)pow((sumx*sumx+sumy*sumy),0.5)));
			}
			//if on outer edge set output value to original greyscale
			else{

				out[pos] = Grey[pos];
			}
		}
	}
	cout << "edge detection complete...\n\n";

	//writing to output textfile
	ofstream outFile("../gsEdgeImageData.txt");
	outFile << rows << "\n";
	outFile << cols << "\n";

	for(int i = 0; i < items; i ++)
	{
  		outFile << out[i] << "\n";
	}
  	outFile.close();
	clock_t end = clock();
        double runtime = (double)(end-begin)*1000/CLOCKS_PER_SEC;

	//runtime
        cout << "Runtime: " << runtime << " ms\n";

	return 0;
}

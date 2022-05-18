__kernel void medianFilter(__global int* imageMatrixR, __global int* imageMatrixG, __global int* imageMatrixB, __global int* outputMatrixR, __global int* outputMatrixG, __global int* outputMatrixB)
{
    int* MatrixR = imageMatrixR; //Pointers to input arrays
    int* MatrixB = imageMatrixB;
    int* MatrixG = imageMatrixG;

    int resultR; //result r,g,b values for each work item
    int resultB;
    int resultG;

    int workItemNum = get_global_id(0);     //Work item ID
    int workGroupNum = get_group_id(0);     //Work group ID

    int items = get_global_size(0);
    int rows = get_local_size(0);               //Number of rows
    int cols = items/rows;
     
    int lenMat = get_global_size(0); 
    int w = cols; //image width
    int h = w; // image height
    int posx = get_global_id(1); //position x and y values 
    int posy = get_global_id(0);
    int i = posy; // position in array


    int pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22; // pixels surrounding the pixel requiring filter
    pixel00 = MatrixR[i - 1 - w] ; //using the width of the image to index the array properly
    pixel01 = MatrixR[i - w] ;
    pixel02 = MatrixR[i + 1 - w] ;
    pixel10 = MatrixR[i - 1] ;
    pixel11 = MatrixR[i] ;
    pixel12 = MatrixR[i + 1] ; 
    pixel20 = MatrixR[i - 1 + w] ;
    pixel21 = MatrixR[i + w] ;
    pixel22 = MatrixR[i + 1 + w] ;
    int filterVector[9] = {pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22};
    for (int x = 0; x < 9; x++) {//simple sorting algorithm
        for(int j = x+ 1; j < 9; j++){
            if (filterVector[x] > filterVector[j]) {
                int tmp = filterVector[x];
                filterVector[x] = filterVector[j];
                filterVector[j] = tmp;
            }
        }
    }

    int pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22; // pixels surrounding the pixel requiring filter
    pixelG00 =  MatrixG[i - 1 - w] ; //using the width of the image to index the array properly
    pixelG01 =  MatrixG[i - w] ;
    pixelG02 =  MatrixG[i + 1 - w] ;
    pixelG10 =  MatrixG[i - 1] ;
    pixelG11 =  MatrixG[i] ;
    pixelG12 =  MatrixG[i + 1] ;
    pixelG20 =  MatrixG[i - 1 + w] ;
    pixelG21 =  MatrixG[i + w] ;
    pixelG22 =  MatrixG[i + 1 + w] ;
    int filterVectorG[9] = {pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22};
    for (int xG = 0; xG < 9; xG++) { //simple sorting algorithm
        for(int jG = xG+ 1; jG < 9; jG++){
            if (filterVectorG[xG] > filterVectorG[jG]) {
                int tmpG = filterVectorG[xG];
                filterVectorG[xG] = filterVectorG[jG];
                filterVectorG[jG] = tmpG;
            }
        }
    }

    int pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22; // pixels surrounding the pixel requiring filter
    pixelB00 =  MatrixB[i - 1 - w] ; //using the width of the image to index the array properly
    pixelB01 =  MatrixB[i - w] ;
    pixelB02 =  MatrixB[i + 1 - w] ;
    pixelB10 =  MatrixB[i - 1] ;
    pixelB11 =  MatrixB[i] ;
    pixelB12 =  MatrixB[i + 1] ;
    pixelB20 =  MatrixB[i - 1 + w] ;
    pixelB21 =  MatrixB[i + w] ;
    pixelB22 =  MatrixB[i + 1 + w] ;
    int filterVectorB[9] = {pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22};
    for (int xB = 0; xB < 9; xB++) { //simple sorting algorithm
        for(int jB = xB+ 1; jB < 9; jB++){
            if (filterVectorB[xB] > filterVectorB[jB]) {
                int tmpB = filterVectorB[xB];
                filterVectorB[xB] = filterVectorB[jB];
                filterVectorB[jB] = tmpB;
            }
        }
    }

    outputMatrixR[i] = (filterVector[4]); //position 4 of arrays is median of each pixel for each color layer 
    outputMatrixG[i] = (filterVectorG[4]);
    outputMatrixB[i] = (filterVectorB[4]);

}
                            

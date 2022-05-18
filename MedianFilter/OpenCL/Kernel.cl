__kernel void medianFilter(__global int* imageMatrixR, __global int* imageMatrixG, __global int* imageMatrixB, __global int* outputMatrixR, __global int* outputMatrixG, __global int* outputMatrixB)
{
    int* MatrixR = imageMatrixR;
    int* MatrixB = imageMatrixB;
    int* MatrixG = imageMatrixG;

    int resultR;
    int resultB;
    int resultG;

    int workItemNum = get_global_id(0);     //Work item ID
    int workGroupNum = get_group_id(0);     //Work group ID

    int lenMat = get_global_size(0);
    int w = 355;
    int h = w;
    int posx = get_global_id(1);
    int posy = get_global_id(0);
    int i = posy;


    int pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22;
    pixel00 = MatrixR[i - 1 - w] ;
    pixel01 = MatrixR[i - w] ;
    pixel02 = MatrixR[i + 1 - w] ;
    pixel10 = MatrixR[i - 1] ;
    pixel11 = MatrixR[i] ;
    pixel12 = MatrixR[i + 1] ; 
    pixel20 = MatrixR[i - 1 + w] ;
    pixel21 = MatrixR[i + w] ;
    pixel22 = MatrixR[i + 1 + w] ;
    int filterVector[9] = {pixel00, pixel01, pixel02, pixel10, pixel11, pixel12, pixel20, pixel21, pixel22};
    for (int x = 0; x < 9; x++) {
        for(int j = x+ 1; j < 9; j++){
            if (filterVector[x] > filterVector[j]) {
                int tmp = filterVector[x];
                filterVector[x] = filterVector[j];
                filterVector[j] = tmp;
            }
        }
    }

    int pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22;
    pixelG00 =  MatrixG[i - 1 - w] ;
    pixelG01 =  MatrixG[i - w] ;
    pixelG02 =  MatrixG[i + 1 - w] ;
    pixelG10 =  MatrixG[i - 1] ;
    pixelG11 =  MatrixG[i] ;
    pixelG12 =  MatrixG[i + 1] ;
    pixelG20 =  MatrixG[i - 1 + w] ;
    pixelG21 =  MatrixG[i + w] ;
    pixelG22 =  MatrixG[i + 1 + w] ;
    int filterVectorG[9] = {pixelG00, pixelG01, pixelG02, pixelG10, pixelG11, pixelG12, pixelG20, pixelG21, pixelG22};
    for (int xG = 0; xG < 9; xG++) {
        for(int jG = xG+ 1; jG < 9; jG++){
            if (filterVectorG[xG] > filterVectorG[jG]) {
                int tmpG = filterVectorG[xG];
                filterVectorG[xG] = filterVectorG[jG];
                filterVectorG[jG] = tmpG;
            }
        }
    }

    int pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22;
    pixelB00 =  MatrixB[i - 1 - w] ;
    pixelB01 =  MatrixB[i - w] ;
    pixelB02 =  MatrixB[i + 1 - w] ;
    pixelB10 =  MatrixB[i - 1] ;
    pixelB11 =  MatrixB[i] ;
    pixelB12 =  MatrixB[i + 1] ;
    pixelB20 =  MatrixB[i - 1 + w] ;
    pixelB21 =  MatrixB[i + w] ;
    pixelB22 =  MatrixB[i + 1 + w] ;
    int filterVectorB[9] = {pixelB00, pixelB01, pixelB02, pixelB10, pixelB11, pixelB12, pixelB20, pixelB21, pixelB22};
    for (int xB = 0; xB < 9; xB++) {
        for(int jB = xB+ 1; jB < 9; jB++){
            if (filterVectorB[xB] > filterVectorB[jB]) {
                int tmpB = filterVectorB[xB];
                filterVectorB[xB] = filterVectorB[jB];
                filterVectorB[jB] = tmpB;
            }
        }
    }

    outputMatrixR[i] = (filterVector[4]);
    outputMatrixG[i] = (filterVectorG[4]);
    outputMatrixB[i] = (filterVectorB[4]);

}
                            

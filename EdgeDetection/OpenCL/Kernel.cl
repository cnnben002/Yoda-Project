//Yoda Project
//Group 1
//12/05/2022

__constant int sobx[3][3] = { {-1, 0, 1},
                              {-2, 0, 2},
                              {-1, 0, 1} };

__constant int soby[3][3] = { {-1,-2,-1},
                              { 0, 0, 0},
                              { 1, 2, 1} };

__kernel void edgeDetector(__global int* imageMatrixR, __global int* imageMatrixG, __global int* imageMatrixB, __global int* outputMatrix)
{
	//Work item and work groups numbers
	int workItemNum = get_global_id(0);     //Work item ID
	int workGroupNum = get_group_id(0);     //Work group ID
	int items = get_global_size(0);         //Number of items in image
	
	//global possition and row/column index
	int rows = get_local_size(0);		//Number of rows
	int cols = items/rows;			//Number of columns
	int row = workGroupNum;
	int col = get_local_id(0);
	int pos = workItemNum;
	
	//result
	int final;

	//dereferencing
	//int* matR = imageMatrixR;
	//int* matG = imageMatrixG;
	//int* matB = imageMatrixB;

	//private matrices
	int l_dataG[3][3];
        int l_dataB[3][3];
        int l_dataR[3][3];	
	int l_dataGrey[3][3];
	
	//ignoring first and last row and column
	if ((row != 0)&&(row != 354)&&(col != 0)&&(col != 354)){
		
		//converting to 3*3 matrices and calculating greyscale value
		int p = -1;
		int k = -1;
		for (int i = 0; i < 3; i++){
			k = -1;
			for (int j = 0; j < 3; j++){
				l_dataG[i][j] =imageMatrixG[pos+p*cols+k];
				l_dataB[i][j] =imageMatrixB[pos+p*cols+k];
				l_dataR[i][j] =imageMatrixR[pos+p*cols+k];
				l_dataGrey[i][j] = round(0.299*l_dataR[i][j]+0.587*l_dataG[i][j]+0.114*l_dataB[i][j]);
				k = k+1;
			}
			p = p+1;
		}
		
		//calculating derivatives
		int sumx = 0, sumy = 0, angle = 0;
		for (int i = 0; i < 3; i++){
                        for (int j = 0; j < 3; j++){
				sumx += sobx[i][j] * l_dataGrey[i][j];
				sumy += soby[i][j] * l_dataGrey[i][j];
			}
		}
		//calculating final gradient
		final = min(255,max(0, (int)pow((sumx*sumx+sumy*sumy),0.5)));
		
		//testing results
		//printf("pos:  %d\t row:  %d\t col:  %d\n  %d\t   %d\t   %d\n   %d\t   %d\t   %d\n  %d\t   %d\t   %d\n final:  %d\n \n",
                //        pos,row,col,
                //        l_dataGrey[0][0],l_dataGrey[0][1],l_dataGrey[0][2],
                //        l_dataGrey[1][0],l_dataGrey[1][1],l_dataGrey[1][2],
                //        l_dataGrey[2][0],l_dataGrey[2][1],l_dataGrey[2][2],final);
		
		//output data
		//barrier(CLK_LOCAL_MEM_FENCE);

	}
	else{
		final = (int)(0.299*imageMatrixR[pos]+0.587*imageMatrixG[pos]+0.114*imageMatrixB[pos]);
		//barrier(CLK_LOCAL_MEM_FENCE);
	}
	outputMatrix[pos] = final;
}

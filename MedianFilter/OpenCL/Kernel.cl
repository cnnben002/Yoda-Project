//Yoda Project
//Group 1
//12/05/2022

__kernel void medianFilter(__global int* imageMatrixR, __global int* imageMatrixG, __global int* imageMatrixB, __global int* outputMatrix)
{
	//Work item and work groups numbers
	int workItemNum = get_global_id(0);     //Work item ID
	int workGroupNum = get_group_id(0);     //Work group ID
	int rows = get_local_size(0);           //Number of rows in image

	//memory buffers
	int arg1 = *imageMatrixR;
	int arg2 = *imageMatrixG;
	int arg3 = *imageMatrixB;
	
	outputMatrix[workItemNum] = imageMatrixG[workItemNum];

	//Code here
	printf("Work item: %i\t Output: %i\n", workItemNum, imageMatrixR[workItemNum]);
}

//Yoda Project
//Group 1
//12/05/2022

__kernel void medianFilter(__global int* imageMatrixR, __global int* imageMatrixG, __global int* imageMatrixB, __global char* outputMatrix)
{
	//Work item and work groups numbers
	int workItemNum = get_global_id(0);     //Work item ID
	int workGroupNum = get_group_id(0);     //Work group ID
	int rows = get_local_size(0);           //Number of rows in image
	
	//Code here
}

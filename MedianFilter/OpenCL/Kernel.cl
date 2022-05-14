//Yoda Project
//Group 1
//12/05/2022

__kernel void medianFilter(__global string* imageMatrixR, __global string* imageMatrixG, __global string* imageMatrixB, __global int* outputMatrix)
{
	//Work item and work groups numbers
	int workItemNum = get_global_id(0);     //Work item ID
	int workGroupNum = get_group_id(0);     //Work group ID
	int items = get_global_size(0);         //Number of items in image
	int rows = get_local_size(0);		//Number of rows
	int cols = items/rows;			//Number of columns

	//Code here
}

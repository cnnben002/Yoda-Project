//Yoda Project
//Group 1
//Benjamin Connolly
//12/05/2022

#define CL_TARGET_OPENCL_VERSION 220
#include<stdio.h>
#include<CL/cl.h>
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
	cout << "Median filter processing started...\n";

        //Initilising variables
        bool displayMatrix = false;
        int dimensions[2];
	string fname = "../imageData.txt";

        getImageDimensions(fname, dimensions);

        int cols = dimensions[0];
        int rows = dimensions[1];
	int items = rows*cols;
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

	//Displaying matrice info
	cout << "Number of elements in matrix: " << items << "\n";
	cout << "Dimensions of matrix: " << cols << "x" << rows << "\n\n";

	//Initializing buffers
	cl_mem imageMatrixR_buffer, imageMatrixG_buffer, imageMatrixB_buffer, outputMatrix_buffer;
	cout << "Buffers initialised...\n\n";

    	//------------------------------------------------------------------------
	//Getting platform info
	cl_uint platformCount;
	cl_platform_id *platforms;
	clGetPlatformIDs(5, NULL, &platformCount);

	//Getting all avaliable platforms
	platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
	clGetPlatformIDs(platformCount, platforms, NULL);
	cl_platform_id platform = platforms[0];

	//Outputting platform info
	char* Info = (char*)malloc(0x1000*sizeof(char));
	clGetPlatformInfo(platform, CL_PLATFORM_NAME      , 0x1000, Info, 0);
	printf("Name      : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_VENDOR    , 0x1000, Info, 0);
	printf("Vendor    : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_VERSION   , 0x1000, Info, 0);
	printf("Version   : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_PROFILE   , 0x1000, Info, 0);
	printf("Profile   : %s\n", Info);

	cout << "\nStage 1 complete...\n\n";

	//------------------------------------------------------------------------
	//Getting device id
	cl_device_id device;
	cl_int err;

	//Acessing the device
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

	if(err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	}

	printf("Device ID = %i\n\n",err);

	cout << "Stage 2 complete...\n";

	//------------------------------------------------------------------------
	//Creating context that allows device to send/recieve/transfer data
	cl_context context;
	context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);

	cout << "Stage 3 complete...\n";

	//------------------------------------------------------------------------
	//Reading in file
	FILE *program_handle;
	program_handle = fopen("OpenCL/Kernel.cl", "r");

	//Getting the program size
	size_t program_size;
	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);

	//Sorting the buffer out
	char *program_buffer;
	program_buffer = (char*)malloc(program_size + 1);
	program_buffer[program_size] = '\0';
	fread(program_buffer, sizeof(char), program_size, program_handle);
	fclose(program_handle);

	cout << "Stage 4 complete...\n";

	//------------------------------------------------------------------------
	//Compling kernel code
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&program_buffer, &program_size, NULL);

        cout << "Stage 5 complete...\n\n";

	//------------------------------------------------------------------------
	//Building the program from the above code

	cl_int err3 = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	printf("program ID = %i\n\n", err3);

        cout << "Stage 6 complete...\n";

	//------------------------------------------------------------------------
	//Creating the kernel
	cl_kernel kernel = clCreateKernel(program, "medianFilter", &err);

        cout << "Stage 7 complete...\n";

	//-----------------------------------------------------------------------
	//Creating command queue to target device
	cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, NULL);

	cout << "Stage 8 complete...\n";

	//------------------------------------------------------------------------
	//Creating data buffers for memory management
	size_t global_size = items; 			//Total number of work items/pixels in image
	size_t local_size = rows; 			//Size of each work group/rows in image
	cl_int num_groups = global_size/local_size; 	//Number of work groups needed

	//Initialising output matrix
        int outputMatrix[global_size];

	//Creating buffers
	imageMatrixR_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, global_size*sizeof(int), &imageMatrixR, &err);
        imageMatrixG_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, global_size*sizeof(int), &imageMatrixG, &err);
        imageMatrixB_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, global_size*sizeof(int), &imageMatrixB, &err);
	outputMatrix_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, global_size*sizeof(int), outputMatrix, &err);

        cout << "Stage 9 complete...\n";

	//------------------------------------------------------------------------
	//Creating kernel arguments
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &imageMatrixR_buffer);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &imageMatrixG_buffer);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &imageMatrixB_buffer);
	clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputMatrix_buffer);

        cout << "Stage 10 complete...\n";

	//------------------------------------------------------------------------
	//Enqueueing the kernel and deploying it

	cl_int err4 = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
	printf("\nKernel check: %i \n\n",err4);

        cout << "Stage 11 complete...\n";

	//------------------------------------------------------------------------
	//Allowing the host to read from the buffer object
	err = clEnqueueReadBuffer(queue, outputMatrix_buffer, CL_TRUE, 0, sizeof(outputMatrix), outputMatrix, 0, NULL, NULL);

	//Stopping the program here until everything in the queue has been run
	clFinish(queue);

	cout << "Stage 12 complete...\n";

        //------------------------------------------------------------------------
	//Checking that the host was able to retrieve the output data from the output buffer
	if(displayMatrix)
	{
		for(int i =0; i < items; i++)
		{
			cout << imageMatrixR[i] << " ";
		}
	}
	cout << "Stage 13 complete...\n";

	//------------------------------------------------------------------------
	//Deallocating resources
	clReleaseKernel(kernel);
	clReleaseMemObject(outputMatrix_buffer);
	clReleaseMemObject(imageMatrixR_buffer);
	clReleaseMemObject(imageMatrixG_buffer);
	clReleaseMemObject(imageMatrixB_buffer);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);

	cout << "Stage 14 complete...\n";

	//------------------------------------------------------------------------
        //Writing the output array to a text file for post median filter processing
	ofstream outFile("../medianImageData.txt");

	for(int i = 0; i < items; i ++)
	{
  		outFile << outputMatrix[i] << "\n";
	}

  	outFile.close();

	cout << "Stage 15 complete...\n";

	return 0;
}

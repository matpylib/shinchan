#include "cuda_runtime.h"
#include "cooperative_groups.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#include <iostream>
using namespace std;

__global__ void sum(int* input)  		// kernel function definition
{
	const int tid = threadIdx.x;    //current thread id
	int step_size = 1;
	int number_of_threads = blockDim.x;    // no of threads


	while (number_of_threads > 0)
	{
		if (tid < number_of_threads) // still alive?
		{
			const int fst = tid * step_size * 2;    //get the index in array
			const int snd = fst + step_size;		//get the index in array
			if (input[fst] < input[snd])
				input[fst] = input[snd];			

		}

		step_size <<= 1; 				// increment step_size by 2
		number_of_threads >>= 1;		//decrement number of threads by 2
	}

}

int main()
{
	int count = SIZE;
	cout << "Enter the number of elements:\n" << endl;
	

	const int size = count * sizeof(int);

	int h[SIZE];
	cout << "Enter the elements:\n" << endl;
	for (int i = 0; i<count; i++)
	{
		h[i] = rand()%500;
	}
	h[3]=1001;
	for (int i = 0; i<count; i++)
	{
		printf("%d  ",h[i]);
	}

	int* d;							//GPU parameter


	cudaMalloc(&d, size);			//assign memory to parameters on GPU

	float elapsed=0;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	cudaMemcpy(d, h, size, cudaMemcpyHostToDevice);		//copy the array from CPU to GPU
	sum <<< 1, 256 >>>(d);							// call kernel function <<<number of blocks, number of threads= number of elements/2

	cudaEventRecord(stop, 0);
	cudaEventSynchronize (stop);
	cudaEventElapsedTime(&elapsed, start, stop);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cout<<"\nThe elapsed time in gpu was : "<<elapsed<<"\n";

	int result;

	cudaMemcpy(&result, d, sizeof(int), cudaMemcpyDeviceToHost);		// copy the result back from GPU to CPU

	cout << "Max is " << result << endl;

	getchar();

	cudaFree(d);					// Free the allocated memory


	return 0;
}

/*

nvcc 3_1.cu -o a
a.exe

Thread: This is just an execution of a kernel with a given index. Each thread uses its index to access elements in array (see the kernel in my first CUDA program) such that the collection of all threads cooperatively processes the entire data set.

Block: This is a group of threads. There’s not much you can say about the execution of threads within a block – they could execute concurrently or serially and in no particular order. You can coordinate the threads, somewhat, using the _syncthreads() function that makes a thread stop at a certain point in the kernel until all the other threads in its block reach the same point.

Grid: This is a group of blocks. There’s no synchronization at all between the blocks

may allow up to 8 thread blocks to be assigned to an SM.

After a block of threads is assigned to a SM, it is divided into sets of 32 threads, each called a warp. However, the size of a warp depends upon the implementation. 

https://www.tutorialspoint.com/cuda/index.htm

*/


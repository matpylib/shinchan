// 1. Implement parallel reduction using Min and Max operations

#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	int n;
	cout<<"Enter No of Elements\n";
	cin>>n;
	int arr[n];
	
	omp_set_num_threads(256);
	
	int min_val = 9999 , max_val = 0;	
		
	for(int i=0;i<n;i++)
	{
		arr[i] = rand();		
	}
	
	//PARALLEL MAX
	
	max_val = 0 ;
	double start , end , res , time;
	start = omp_get_wtime(); // get time for parallel
	
	#pragma omp parallel for reduction(max : max_val)
	for(int i = 0 ; i <n ; i++)
	{
		//cout<<"\nThread id = "<<omp_get_thread_num();
		if(arr[i] > max_val)
		{
			max_val = arr[i];
		}
	}
	
	end = omp_get_wtime();
	res = end - start;
	cout<<"\nTime for Parallel Maximum :"<<res <<"\n";
	
	cout<<"\n Maximum Value is : "<<max_val <<"\n";
	
	//SERAIL MAX
	
	max_val = 0;
	clock_t c1 = clock();
	
	for(int i = 0 ; i < n ; i++)
	{
		if(arr[i] > max_val)
		{
			max_val = arr[i];
		}
	}
	
	time = (float)(clock() - c1) / CLOCKS_PER_SEC;
	cout<<"\n Execution time of Serial Maximum : "<<time<<"\n";
	
	cout<<"\n Maximum Value is : "<<max_val <<"\n";
		
	//PARALLEL MIN
	
	min_val = 9999 ;
	start = omp_get_wtime();
	
	#pragma omp parallel for reduction(min : min_val)
	for(int i = 0 ; i <n ; i++)
	{
		//cout<<"\nThread id = "<<omp_get_thread_num();
		if(arr[i] < min_val)
		{
			min_val = arr[i];
		}
	}
	
	end = omp_get_wtime();
	res = end - start;
	cout<<"\nTime for Parallel Minimum :"<<res <<"\n";
	
	cout<<"\n Minimum Value is : "<<min_val <<"\n";
	
	//SERAIL Min
	
	min_val = 9999;
	clock_t c2 = clock();
	
	for(int i = 0 ; i < n ; i++)
	{
		if(arr[i] < min_val)
		{
			min_val = arr[i];
		}
	}
	
	time = (float)(clock() - c2) / CLOCKS_PER_SEC;
	cout<<"\n Execution time of Serial Minimum : "<<time<<"\n";
	
	cout<<"\n Minimum Value is : "<<min_val <<"\n";

	return 0;
}

//  g++ 1.cpp -fopenmp -o a
//  ./a


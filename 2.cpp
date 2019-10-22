// 1. Implement parallel reduction using sum and Average operations

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
	
	int avg_val = 0 , sum_val = 0;	
		
	for(int i=0;i<n;i++)
	{
		arr[i] = rand();		
	}
	
	//PARALLEL SUM
	
	sum_val = 0 ;
	double start , end , res , time;
	start = omp_get_wtime();
	
	#pragma omp parallel for reduction(+ : sum_val)
	for(int i = 0 ; i <n ; i++)
	{
		//cout<<"\nThread id = "<<omp_get_thread_num();
		sum_val = sum_val + arr[i];
	}
	
	end = omp_get_wtime();
	res = end - start;
	cout<<"\nTime for Parallel Sum :"<<res <<"\n";
	
	cout<<"\n Sum  is : "<<sum_val <<"\n";
	
	//SERAIL SUM
	
	sum_val = 0;
	clock_t c1 = clock();
	
	for(int i = 0 ; i < n ; i++)
	{
		sum_val = sum_val + arr[i];
	}
	
	time = (float)(clock() - c1) / CLOCKS_PER_SEC;
	cout<<"\n Execution time of Serial Sum : "<<time<<"\n";
	
	cout<<"\n SUm is : "<<sum_val <<"\n";
		
	//PARALLEL AVG
	
	avg_val = 0 ;
	start = omp_get_wtime();
	
	#pragma omp parallel for reduction(+ : avg_val)
	for(int i = 0 ; i <n ; i++)
	{
		//cout<<"\nThread id = "<<omp_get_thread_num();
		avg_val = avg_val + arr[i];
	}
	avg_val = avg_val/n;
	
	end = omp_get_wtime();
	res = end - start;
	cout<<"\nTime for Parallel Average :"<<res <<"\n";
	
	cout<<"\n Average is : "<<avg_val <<"\n";
	
	//SERAIL AVG
	
	avg_val = 0;
	clock_t c2 = clock();
	
	for(int i = 0 ; i < n ; i++)
	{
		avg_val = avg_val + arr[i];
	}
	avg_val = avg_val / n;
	
	time = (float)(clock() - c2) / CLOCKS_PER_SEC;
	cout<<"\n Execution time of Serial Average : "<<time<<"\n";
	
	cout<<"\n Average is : "<<avg_val <<"\n";

	return 0;
}


//  g++ 1.cpp -fopenmp -o a
//  ./a


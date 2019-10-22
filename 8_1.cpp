#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<iostream>
using namespace std;

int main()
{
	int n;
	cout<<"\nEnter the elements of array\n";
	cin>>n;
	int arr[n];
	int temp = 0;
	
	//omp_set_num_threads(256);
	
	for(int i = 0 ; i < n ; i++)
	{
		arr[i] = rand()%100;
	}
	
	cout<<"\nPARALLEL\n";
	
	double start , end , time;
	start = omp_get_wtime();
	
	#pragma omp parallel for
	for(int i = 0 ;i <n ; i ++)
	{
		int first = i%2;
		#pragma omp parallel for shared(arr,first)
		for(int j = first ; j <n-1;j+=2)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	end = omp_get_wtime();
	time = (double)(end - start);
	cout<<"\nTime for parallel execution : "<<time<<endl;
	
	cout<<"\nSorted Array \n";
	for(int i = 0 ; i < n ; i++)
	{
		cout<<"\t"<<arr[i];
	}
	
	cout<<"\nSERIAL\n";
	clock_t c1 = clock();
	
	for (int i = 0; i < n-1; i++)      
    {
		for (int j = 0; j < n-1; j++)  
		{
		    if (arr[j] > arr[j+1])
		    {
		    	temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
		    }           
		}
	}
	float t = (float)(clock() - c1 )/CLOCKS_PER_SEC;
	cout<<"\nTime for Serial execution : "<<t<<endl;
	
	cout<<"\nSorted Array \n";
	for(int i = 0 ; i < n ; i++)
	{
		cout<<"\t"<<arr[i];
	}
	
	return 0;
}


/*g++ binarysearch.cpp -fopenmp -o bs
	./bs
*/

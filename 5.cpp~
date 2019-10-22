#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
using namespace std;

int main()
{
	int size;
	double start , end , res;
	cout<<"Enter the size of vector"<<endl;
	cin >> size;
	
	omp_set_num_threads(32);
	
	int a[size] , b[size] , c[size] = {0};
	
	for(int i = 0 ; i <size ; i++)
	{
		a[i] = rand()%100;
		b[i] = rand()%100;
		c[i] = 0;
	}
	
	// PARALLEL
	cout<<"\n PARALLEL \n";
	start = omp_get_wtime();
	
	#pragma omp parallel for
	for(int i = 0 ; i<size ; i++)
	{
		c[i] = a[i] + b[i];
	}
	end = omp_get_wtime();
	res = (double)(end - start);
	cout<<"\nTime for parallel : "<<res<<endl;
	for(int i = 0; i<size ; i++)
	{
		cout<<"\n"<<a[i]<<" "<<b[i]<<" "<<c[i];
	}
	
	// SERIAL
	cout<<"\n SERIAL \n";
	
	clock_t c1 = clock();
	
	for(int i = 0 ; i<size ; i++)
	{
		c[i] = a[i] + b[i];
	}
	
	float time  = (float)(clock()-c1)/CLOCKS_PER_SEC;
	
	cout<<"\nTime for Serial : "<<time<<endl;
	//for(int i = 0; i<size ; i++)
	//{
	//	cout<<"\n"<<a[i]<<" "<<b[i]<<" "<<c[i];
	//}
	return 0;
}

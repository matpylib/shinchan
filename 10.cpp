#include<iostream>
#include<map>
#include<vector>
#include<set>
using namespace std;

int cal_heu(vector<vector<int>>curr,vector<vector<int>>goal)
{
	int dis=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(curr[i][j]==goal[k][l])
							dis+=abs(i-k)+abs(j-l);
					}
				}
		}
	}
	return dis;
}

int cal_g(int dashrow,int dashcol,int currow,int curcol)
{
	return (abs(currow-dashrow)+abs(curcol-dashcol));
}

int main()
{
	int temp,row,col,total,r,c;
	vector<vector<int>>start(3),goal(3),tempv(3),copy;
	
	cout<<"Enter start state: "<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>temp;
			start[i].push_back(temp);
			if(temp==-1) 			//-1 == dash(-)
			{
				r = i;			//row,col starting position of dash or -1
				c = j;
			} 
		}
	}
	
	cout<<"Enter goal state: "<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>temp;
			goal[i].push_back(temp);
		}
	}
	
	map<int, vector<vector<int>> >m;
	set< vector<vector<int>> >s;
	
	s.insert(start);
	tempv = start;
	row=r;
	col=c;
	cout<<endl;
	
	while(tempv != goal)
	{
		int left = col - 1;	//left
		if(left>=0)
		{
			copy = tempv;
			temp = copy[row][left];
			copy[row][left] = copy[row][col];	
			copy[row][col] = temp;
			if(s.find(copy)==s.end())   // already not visited or explored
			{
				total = cal_heu(copy,goal) + cal_g(r,c,row,left);   //h(n) + g(n)
				m.insert({total,copy});
				s.insert(copy);
			}
		}
		
		int right = col + 1;	//right
		if(right<=2)
		{
			copy = tempv;
			temp = copy[row][right];
			copy[row][right] = copy[row][col];	
			copy[row][col] = temp;
			if(s.find(copy)==s.end())
			{
				total = cal_heu(copy,goal) + cal_g(r,c,row,right);
				m.insert({total,copy});
				s.insert(copy);
			}
		}
		
		int down= row+1;	//down shift
		if(down<=2)
		{
			copy = tempv;
			temp = copy[down][col];
			copy[down][col] = copy[row][col];	
			copy[row][col] = temp;
			if(s.find(copy)==s.end())
			{
				total = cal_heu(copy,goal) + cal_g(r,c,down,col);
				m.insert({total,copy});
				s.insert(copy);
			}
		}
		
		int up = row-1; //up shift
		if(up>=0)
		{
			temp = tempv[up][col];
			tempv[up][col] = tempv[row][col];	
			tempv[row][col] = temp;
			if(s.find(tempv)==s.end())
			{
				total = cal_heu(tempv,goal) + cal_g(r,c,up,col);
				m.insert({total,tempv});
				s.insert(tempv);
			}
		}
		
		auto itr = m.begin();
		tempv = itr->second;
		m.erase(itr);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(tempv[i][j]==-1)
				{
					row = i;
					col = j;
				}
				cout<<tempv[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
		
	}

}

/*g++ binarysearch.cpp -fopenmp -o bs
	./bs
*/
/*Output // -1 represents - (dash)
Enter start state: 
3 7 6
5 1 2
4 -1 8
Enter goal state: 
5 3 6
7 -1 2
4 1 8

3 7 6 
5 -1 2 
4 1 8 

3 -1 6 
5 7 2 
4 1 8 

-1 3 6 
5 7 2 
4 1 8 

5 3 6 
-1 7 2 
4 1 8 

5 3 6 
7 -1 2 
4 1 8 
*/

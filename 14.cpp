#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
using namespace std;

int main()
{
	int n,temp,node,goal,flag=0;
	cout<<"Enter number of nodes"<<endl;
	cin>>n;
	
	int adj_mat[n][n]={0};
	vector<int>heu;
	vector<int>vis(n); //closed list
	
	cout<<"Enter Edge weight: "<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			cout<<"Edge:"<<(i+1)<<" "<<(j+1)<<endl;
			cin>>temp;
			adj_mat[i][j]=temp;
			adj_mat[j][i]=temp;
		}
	}

	cout<<"Enter heuristic values of all nodes"<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<"For node: "<<(i+1)<<"  ";
		cin>>temp;
		heu.push_back(temp);
	}
	
	cout<<"Enter goal node: ";
	cin>>goal;
	multimap<int,int>m; //heu,node   open list
	unordered_map<int,int>cp;	//child -> parent For path
	unordered_map<int,int>minv; //node,heu
	
	for(int i =1;i<n;i++)
	{
		temp = adj_mat[0][i];
		if(temp!=0)
		{
			m.insert({heu[i]+temp,i});
			minv.insert({i,heu[i]+temp});
			cp.insert({i,0});
			vis[i]++;
		}
	}
	vis[0]=2; //2 = visited and explored, 1 = visited only
	
	cout<<"The node traversed in A* are as follows:"<<endl;
	int dis,cur;
	while(m.size()!=0)
	{
		auto itr = m.begin();
		temp = itr->first;
		node = itr->second;
		cout<<(node+1)<<"	";
		vis[node]++;
		
		if(node+1==goal)
		{
			cout<<endl<<"Goal State found";
			flag=1;
			break;
		}

		m.erase(itr);
		dis = temp - heu[node];
		for(int i=0;i<n;i++)
		{
			cur = adj_mat[node][i];
			if(cur!=0 && vis[i]==0)
			{
				cur += heu[i]+dis;
				m.insert({cur,i});
				minv.insert({i,cur});
				vis[i]++;
				cp.insert({i,node});
			}
			else if(cur!=0 && vis[i]==1)
			{
				cur += heu[i]+dis;
				if(minv[i] > cur)
				{
					cp[i] = node;
					itr = m.find(minv[i]);
					while(itr->second!=i)
						itr++;
					m.erase(itr);
					m.insert({cur,i});
					minv[i] = cur;		
				}
			}
		}
	}
	cout<<endl;
	
	if(flag==0)
		cout<<"\nGoal State not found";
	else
	{
		cout<<"\nThe path from starting node to end node is as follows: ";
		vector<int>ans;
		while(node != 0) //0 is starting node
		{
			ans.push_back(node);
			node = cp[node];
		}
		ans.push_back(0);
		for(int i=ans.size()-1;i>=0;i--)
			cout<<(ans[i]+1)<<" ";
	}	
	cout<<endl;			
	
return 0;
}

/*g++ binarysearch.cpp -fopenmp -o bs
	./bs
*/

/*Output
Enter number of nodes
8
Enter Edge weight: 
Edge:1 2
3
Edge:1 3
4
Edge:1 4
0
Edge:1 5
0
Edge:1 6
0
Edge:1 7
0
Edge:1 8
0
Edge:2 3
5
Edge:2 4
4
Edge:2 5
0
Edge:2 6
0
Edge:2 7
0
Edge:2 8
0
Edge:3 4
0
Edge:3 5
2
Edge:3 6
0
Edge:3 7
0
Edge:3 8
0
Edge:4 5
5
Edge:4 6
4
Edge:4 7
0
Edge:4 8
0
Edge:5 6
0
Edge:5 7
4
Edge:5 8
0
Edge:6 7
0
Edge:6 8
0
Edge:7 8
3
Enter heuristic values of all nodes
For node: 1  15
For node: 2  4
For node: 3  12
For node: 4  10
For node: 5  10
For node: 6  8
For node: 7  10
For node: 8  0
Enter goal node: 8
The node traversed in A* are as follows:
2	3	5	4	6	7	8	
Goal State found

The path from starting node to end node is as follows: 1 3 5 7 8
*/

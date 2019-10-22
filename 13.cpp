#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

int main()
{
	int n,temp,node,goal,flag=0;
	cout<<"Enter number of nodes"<<endl;
	cin>>n;
	
	int adj_mat[n][n]={0};
	vector<int>heu;
	vector<int>vis(n); //closed list
	
	cout<<"Edge: Present=1 Not-Present=0"<<endl;
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
	unordered_map<int,int>cp;
	
	vis[0]=1;
	for(int i =1;i<n;i++)
	{
		if(adj_mat[0][i]==1)
		{
			m.insert({heu[i],i});
			cp.insert({i,0});
			vis[i]=1;
		}
	}
	
	cout<<"The node traversed in best first search are as follows:"<<endl;
	
	while(m.size()!=0)
	{
		auto itr = m.begin();
		node = itr->second;
		cout<<(node+1)<<"	";
		if(node+1==goal)
		{
			cout<<"\nGoal State found";
			flag=1;
			break;
		}
		m.erase(itr);
		for(int i=0;i<n;i++)
		{
			if(adj_mat[node][i]!=0 && vis[i]==0)
			{
				m.insert({heu[i],i});
				cp.insert({i,node});
				vis[i]=1;
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

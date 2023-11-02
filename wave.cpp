#include<climits>
#include<iostream>
#include<queue>
#include<vector>

// Adjacency matrix, wave algorithm
// what is the smallest amount of steps is needed to reach i-node from 0-node?

using namespace std;

int main()
{
	queue<int> q;
    q.push(0);
	int N = 7;
	int ans[N];
	bool was[N];
	ans[0] = 0; was[0] = false;

	for(int i = 1; i < N; i++)
    {
        ans[i] = INT_MAX;
        was[i] = false;                       // simple graph
    }
                                              //    - - - - -
	vector<vector <int> > ways;               //  |           |
	ways.push_back({1, 3, 6});                //  0 - 1 - 2 - 3
	ways.push_back({0, 2});                   //  |       |   |
	ways.push_back({1, 3, 5});                //  6 - -- -5 - 4
	ways.push_back({0, 2, 4});
	ways.push_back({3, 5});
	ways.push_back({2, 4, 6});
	ways.push_back({0, 5});
	cout << "Adjacency matrix:\n" << endl;

	for(unsigned int cycle_1 = 0; cycle_1 < ways.size(); cycle_1++)
    {
        cout << "[";
        for(unsigned int cycle_2 = 0; cycle_2 < ways[cycle_1].size(); cycle_2++)
            if(cycle_2 + 1 < ways[cycle_1].size())
                cout << ways[cycle_1][cycle_2] << ", ";
            else
                cout << ways[cycle_1][cycle_2] << "]" << endl;
    }

	while(!q.empty())
    {
        int a = q.front();
        q.pop();
        if (was[a])
            continue;
        was[a] = true;
        for(int i = 0; i < ways[a].size(); i++)
        {
            int b = ways[a][i];
            if (ans[b] > ans[a] + 1)
            {
                ans[b] = ans[a] + 1;
                q.push(b);
            }
        }
    }
    cout << "\nMatrix of answers:\n" << endl;
    for(int i = 0; i < N; i++)
    {
        if(ans[i] != INT_MAX)
            cout << "0 -> " << i << " for " << ans[i] << " steps" << endl;
        else
            cout << "impossible way: 0 -> " << i << endl;
    }
return 0;
}

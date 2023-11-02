#include<climits>
#include<iostream>
#include<queue>
#include<vector>

// Adjacency matrix, wave algorithm
// what is the smallest amount of steps is needed to reach i-node from 0-node?

using namespace std;

int main()
{

	int N = 7;
	int ans[N];
	bool was[N];

	ans[0] = 0; was[0] = false;
	for(int i = 1; i < N; i++)
    {
        ans[i] = INT_MAX;
        was[i] = false;
    }                                           //        (3)
	typedef pair<int, int> pr;                  //    - - -> - -
	vector<vector <pr> > ways;                  //   |(2) (2) (3)|
	ways.push_back({{1, 2}, {3, 3}, {6, 4}});   //   0 - 1 < 2 - 3
	ways.push_back({{0, 2}});                   //(4)|    (5)|   v (2)
	ways.push_back({{1, 2}, {3, 3}, {5, 5}});   //   6 --> - 5 - 4
	ways.push_back({{2, 3}, {4, 2}});           //      (1)   (3)
	ways.push_back({{5, 3}});
	ways.push_back({{2, 5}, {4, 3}});
	ways.push_back({{0, 4}, {5, 1}});

	priority_queue<pr> q;
    q.push(pr(0, 0));

	cout << "Adjacency matrix:\n" << endl;

	for(unsigned int cycle_1 = 0; cycle_1 < ways.size(); cycle_1++)
    {
        cout << "[";
        for(unsigned int cycle_2 = 0; cycle_2 < ways[cycle_1].size(); cycle_2++)
            if(cycle_2 + 1 < ways[cycle_1].size())
                cout << "(" << ways[cycle_1][cycle_2].first << ", " << ways[cycle_1][cycle_2].second << "), ";
            else
                cout << "(" << ways[cycle_1][cycle_2].first << ", " << ways[cycle_1][cycle_2].second << ")]" << endl;
    }

	while(!q.empty())
    {
        int vertex = q.top().first;
        int dist = - q.top().second;    // >0
        q.pop();
        if (was[vertex])
            continue;
        was[vertex] = true;
        for(int i = 0; i < ways[vertex].size(); i++)
        {
            int nghbr = ways[vertex][i].first;               // neighbor vertex
            int ndist = ways[vertex][i].second + abs(dist);  // distance to n.v. (>0)
            if (ndist < ans[nghbr])
            {
                ans[nghbr] = ndist;
                q.push(pr(nghbr, -ndist)); // the less == the more priority (<0)
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

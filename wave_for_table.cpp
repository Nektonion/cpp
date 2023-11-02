#include<climits>
#include<iostream>
#include<queue>
#include<vector>
#include<cmath>
// Adjacency matrix, wave algorythm
// what is the smallest amount of steps is needed to reach i-node from 0-node?

using namespace std;

int main()                                  // chess board 5x5
{
	queue<int> q;                           // 0  1  2  -  4
    q.push(0);                              // -  6  7  8  9
	int N = 25;                             // 10 -  12 13 14
	int ans[N];                             // 15 16 17 -  19
	bool was[N];                            // -  21 -  -  24
	ans[0] = 0; was[0] = false;

	for(int i = 1; i < N; i++)
    {
        ans[i] = INT_MAX;
        was[i] = false;
    }

	vector<vector <int> > ways;

	ways.push_back({1});
	ways.push_back({0, 2, 6});
	ways.push_back({1, 7});
	ways.push_back({});
	ways.push_back({9});
	ways.push_back({});
	ways.push_back({1, 7});
	ways.push_back({2, 6, 8, 12});
	ways.push_back({7, 9, 13});
	ways.push_back({4, 8, 14});
	ways.push_back({15});
	ways.push_back({});
	ways.push_back({7, 13, 17});
	ways.push_back({8, 12, 14});
	ways.push_back({9, 13, 19});
	ways.push_back({10, 16});
	ways.push_back({15, 17, 21});
	ways.push_back({12, 16});
	ways.push_back({});
	ways.push_back({14, 24});
	ways.push_back({});
	ways.push_back({16});
	ways.push_back({});
	ways.push_back({});
	ways.push_back({19});

	cout << "Adjacency matrix:/n" << endl;

	for(unsigned int cycle_1 = 0; cycle_1 < ways.size(); cycle_1++)
    {
        cout << "[";
        for(unsigned int cycle_2 = 0; cycle_2 < ways[cycle_1].size(); cycle_2++)
            if(cycle_2 + 1 < ways[cycle_1].size())
                cout << ways[cycle_1][cycle_2] << ", ";
            else
                cout << ways[cycle_1][cycle_2];
            cout << "]" << endl;
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

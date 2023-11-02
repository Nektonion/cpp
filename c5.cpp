#include <iostream>

/* http://cppstudio.com/cat/285/ */

using namespace std;

int main()
{
    int jumpers, jumps;
    cout << "Input number of jumpers and number of their jumps: ";
    cin >> jumpers >> jumps;

    float **res = new float*[jumpers];
    for(int i = 0; i < jumpers; i++)
        res[i] = new float[jumps];

    for(int i = 0; i < jumpers; i++)
    {
        cout << "input results of " << (i+1) << " jumper: ";
        for(int j = 0; j < jumps; j++)
            cin >> res[i][j];
    }

    for(int i = 0; i < jumpers; i++)
    {
        int best = 1;
        float longest = res[i][0];
        for(int j = 1; j < jumps; j++)
        {
            if (res[i][j] > longest)
            {
                best = (j+1);
                longest = res[i][j];
            }
        }
        cout << "the best jump of " << (i+1) << " jumper is: " << best << endl;
    }

    for(int i = 0; i < jumpers; i++)
        delete[] res[i];
    delete[] res;

    return 0;
}

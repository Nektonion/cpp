#include <iostream>

/* http://cppstudio.com/cat/285/ */

using namespace std;

int main()
{
    int x1, y1, x2, y2;
    cout << "enter the coordinates of initial and final horse's position (x,y):" << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 > 0 && x1 < 9 && y1 > 0 && y1 < 9 ||
        x2 > 0 && x2 < 9 && y2 > 0 && y2 < 9)
    {
        if ( (abs(x1 - x2) == 1 && abs(y1 - y2) == 2) ||
            (abs(x1 - x2) == 2 && abs(y1 - y2) == 1) )
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    else
        cout << "horse is out of table" << endl;
    return 0;
}

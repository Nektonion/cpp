#include <iostream>
#include <math.h>
//#include <vector>
using namespace std;

void arrOut(int a[], int cols, int rows = 1)    // важен порядок, т.к. у вектора только столбцы
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << a[i*cols + j] << " ";
        cout << endl;
    }
}

int main()
{
    setlocale (LC_ALL, "RUS");
    int rows = 2;
    int cols = 4;
    int n = 5;

    int a[rows][cols]{{0,1,2,3},{4,5,6,7}};

    int b[n]{1,2,3,4,5};

    arrOut(&a[0][0], cols, rows);
    arrOut(&b[0], n);

    return 0;
}

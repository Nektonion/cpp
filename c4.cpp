#include <iostream>
#include <math.h>
//#include <vector>
using namespace std;

/* http://cppstudio.com/cat/285/ */

// input: 2 4 1 2 3 4 5 6 7 8 1 0 1 0

int main()
{
    setlocale (LC_ALL, "RUS");

    int rows, cols;
    cout << "¬ведите количество строк матрицы: ";
    cin >> rows;
    cout << "¬ведите количество столбцов матрицы: ";
    cin >> cols;

    int **mat = new int* [rows];
    for(int i = 0; i < rows; i++)
        mat[i] =  new int[cols];

    int *vec = new int[cols];
    int *res = new int[cols];

    cout << "¬ведите элементы матрицы: ";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            cin >> mat[i][j];
        }

    cout << "¬ведите элементы вектора: ";
    for (int i = 0; i < cols; i++)
        cin >> vec[i];

    cout << endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i] += mat[i][j] * vec[j];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    for (int j = 0; j < cols; j++)
        cout << vec[j] << " ";
    cout << endl;

    for (int j = 0; j < rows; j++)
        cout << res[j] << " ";
    cout << endl;

    for (int i = 0; i < rows; i++)
        delete[] mat[i];
    delete[] mat;
    delete[] res;
    delete[] vec;

    return 0;
}

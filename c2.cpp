#include <iostream>
#include <math.h>
//#include <vector>
using namespace std;

/* http://cppstudio.com/cat/285/ */

int main()
{
    setlocale (LC_ALL, "RUS");

    int rows, cols;
    cout << "������� ���������� ����� �������: ";
    cin >> rows;
    cout << "������� ���������� �������� �������: ";
    cin >> cols;
    int mat[rows][cols];
    int vec[cols];
    int res[rows]{};
    cout << "������� �������� �������: ";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> mat[i][j];

    cout << "������� �������� �������: ";
    for (int i = 0; i < cols; i++)
        cin >> vec[i];

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

    return 0;
}

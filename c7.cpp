#include <iostream>

//   array  functions with it resizing

/* http://cppstudio.com/cat/285/ */

using namespace std;

void FillArray(int *arr, const int xsize)
{
    for(int i = 0; i < xsize; i++)
        arr[i] = rand() % 10;
}

void ShowArray(const int *arr, const int xsize)
{
    for(int i = 0; i < xsize; i++)
        cout << arr[i] << "\t";
    cout << endl;
}

void DeleteElement(int *&arr, int &xsize, const int pos)
{
    int* arr2 = new int[xsize - 1];

    for(int i = 0; i < pos; i++)
        arr2[i] = arr[i];

    for(int i = pos + 1; i < xsize; i++)
        arr2[i - 1] = arr[i];

    delete[] arr;
    arr = arr2;
    xsize--;
}

void AddElement(int *&arr, int &xsize, const int pos, const int value)
{
    int* arr2 = new int[xsize + 1];

    for(int i = 0; i < pos; i++)
        arr2[i] = arr[i];

    arr2[pos] = value;

    for(int i = pos; i < xsize; i++)
        arr2[i + 1] = arr[i];

    delete[] arr;
    arr = arr2;
    xsize++;
}

int main()
{
    int xsize;
    cout << "enter the array's size: ";
    cin >> xsize;

    int* arr = new int[xsize];

    FillArray(arr, xsize);

    ShowArray(arr, xsize);

    int pos = 3; //position
    cout << "enter position(0, 1, ...) of element you want to delete : ";
    cin >> pos;

    DeleteElement(arr, xsize, pos);

    ShowArray(arr, xsize);

    int value = 228;
    cout << "enter value and position(0, 1, ...) of new element: ";
    cin >> value >> pos;
    AddElement(arr, xsize, pos, value);

    ShowArray(arr, xsize);

    delete[] arr;
    return 0;
}

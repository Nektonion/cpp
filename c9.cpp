#include <iostream>
#include <string>
using namespace std;

/* http://cppstudio.com/cat/285/ */

int strlen(const string str)
{
    int i;
    for(i = 0; str[i] != '\0'; i++);

    return i;
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

void arrayUnique(int *&arr, int &arrSize)
{
    for(int i = 1; i < arrSize; i++)
        for(int j = 0; j < i; j++)
                if (arr[j] == arr[i])
                {
                    DeleteElement(arr, arrSize, i);
                    i--;
                    break;
                }
}

int main()
{
    setlocale (LC_ALL, "RUS");

    int arrSize;
    cout << "enter the array's length: ";
    cin >> arrSize;

    int* arr = new int[arrSize];

    for(int i = 0; i < arrSize; i++)
        arr[i] = rand() % 10;

    cout << "initial and final results:\n";

    for(int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";

    cout << endl;
    arrayUnique(arr, arrSize);

    for(int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";

    delete[] arr;

    return 0;
}

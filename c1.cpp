#include <iostream>
#include <math.h>
using namespace std;

/*
 * ==== http://cppstudio.com/cat/285/ ====
 * ��� �������� � = �_1 + �_2 + ... + �_n
 * ��� ������ x ����� 3 ���������
 * ����� �������� y �� �������
 */

int main()
{
    setlocale (LC_ALL, "RUS");
    int n;
    float y = 0;
    cout << "������� ���������� �����: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        float z, b, a, betta;
        cout << "������� �������� Z, B, A, Betta ��� X" << i << ":" << endl;
        cin >> z >> b >> a >> betta;
        y += z*z*z - b + a*a / tan(betta) / tan(betta);
    }
    cout << "y = " << y << endl;
    return 0;
}

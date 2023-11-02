#include <iostream>
#include <math.h>
using namespace std;

/*
 * ==== http://cppstudio.com/cat/285/ ====
 * Для величины Х = х_1 + х_2 + ... + х_n
 * где каждый x имеет 3 параметра
 * нужно почитать y по формуле
 */

int main()
{
    setlocale (LC_ALL, "RUS");
    int n;
    float y = 0;
    cout << "Введите количество иксов: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        float z, b, a, betta;
        cout << "Введите значения Z, B, A, Betta для X" << i << ":" << endl;
        cin >> z >> b >> a >> betta;
        y += z*z*z - b + a*a / tan(betta) / tan(betta);
    }
    cout << "y = " << y << endl;
    return 0;
}

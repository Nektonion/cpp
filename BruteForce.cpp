#include <iostream>
//#include <algorithm> // for sort
#include <string>
using namespace std;

int main()
{
    setlocale (LC_ALL, "RUS");

    string tokens;

    cout << "�������� ���������� ������� ��� ������: " << endl;

    cout << "1. �������� ����� � �����" << endl;
    cout << "2. �������� � ��������� ����� � �����" << endl;
    cout << "3. �������� � ��������� �����, �����, ����� ����������" << endl;
    int flag, len;
    cin >> flag;

    cout << "������� ����� ������ (�� ����� 4 ��������)" << endl;

    cin >> len;
    char result[len];

    cout << "������� ������: ";
    string password;
    cin >> password;

    switch(flag)
    {
    case 1:
        tokens = "qwertyuiopasdfghjklzxcvbnm1234567890";
    case 2:
        tokens = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
    case 3:
        tokens = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()_+-=*/";
    default:
        break;
    }

    if(flag > 3 || flag < 1)
    {
        for(int i = 0; i < len; i++)
            for(char token = 33; token <= 122; token++)
            {
                if( password[i] == token )
                {
                    result[i] = token;
                    break;
                }
            }
    }
    else
        for(int i = 0; i < len; i++)
        {
            int position = 0;
            while(tokens[position] != '\0')
            {
                if( password[i] == tokens[position] )
                {
                    result[i] = tokens[position];
                    break;
                }
                position++;
            }
        }


    for(int i = 0; i < len; i++)
        cout << result[i];
    return 0;
}

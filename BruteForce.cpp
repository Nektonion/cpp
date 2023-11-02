#include <iostream>
//#include <algorithm> // for sort
#include <string>
using namespace std;

int main()
{
    setlocale (LC_ALL, "RUS");

    string tokens;

    cout << "Выберите допустимые символы для пароля: " << endl;

    cout << "1. Строчные буквы и цифры" << endl;
    cout << "2. Строчные и заглавные буквы и цифры" << endl;
    cout << "3. Строчные и заглавные буквы, цифры, знаки препинания" << endl;
    int flag, len;
    cin >> flag;

    cout << "Введите длину пароля (не более 4 символов)" << endl;

    cin >> len;
    char result[len];

    cout << "Введите пароль: ";
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

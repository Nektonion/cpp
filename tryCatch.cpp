#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MyException : public exception
{
private:

public:
    MyException(string ex)
    {
        cout << ex << endl;
    }
};

template<typename Type>
float f(Type x)
{
    if(x < 0)
        throw false;
    if(x == 0)
        throw "bruh you divide by a zero\n";
    if(x == 1)
        throw x;
    if(x == 228)
        throw MyException("you win");

    return 1.0 / x;
}

int main()
{
    int x;
    cout << "input number" << endl;
    cin >> x;

    try
    {
        cout << "reciprocal number is:" << endl << f(x) << endl;
    }
    catch(const char* ex)
    {
        cout << ex << endl;
    }
    catch(const int ex)
    {
        cout << "exception with your number: " << ex << endl;
    }
    catch(const exception& ex)
    {
        cout << "exception caught" << endl;
        cout << ex.what() << endl;
    }
    catch(...)
    {
        cout << "no negative bro" << endl;
    }

    /*fstream fs;

    try
    {
        string path = "tryCatchLogs.txt";
        fs.open(path, ios::in | ios::out | ios::app);
        cout << "file is opened" << endl;
        if(fs.is_open())
            fs << f(x) << endl;
        fs.close();
    }
    catch(const std::exception& ex)
    {
        cout << ex.what() << endl;
    }
    catch(int number)
    {
        cout << "inf, divide by zero may be" << endl;
    }
    */

    return 0;
}

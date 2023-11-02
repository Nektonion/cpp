#include <fstream>
#include <iostream>
#include <string>
//#include <vector>
//#include <algorithm> // for sort

//#define DEBUG

using namespace std;

class Point
{
private:

    int x, y, z;

public:

    Point()
    {
        x = y = z = 0;
    }

    Point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    int GetX()
    {
        return this->x;
    }

    int GetY()
    {
        return this->y;
    }

    int GetZ()
    {
        return this->z;
    }

    void SetX(int x)
    {
        this->x = x;
    }

    void SetY(int y)
    {
        this->y = y;
    }

    void SetZ(int z)
    {
        this->z = z;
    }

    ~Point()
    {
    }

    void Print()
    {
        cout << "x = " << x <<  ", y = " << y <<  ", z = " << z << endl;
    }
};

ostream& operator << (ostream& out, Point &p)   // no const!
{
    //out << "x = " << p.GetX() <<  ", y = " << p.GetY() <<  ", z = " << p.GetZ() << endl;
    out << p.GetX() << " " << p.GetY() << " " << p.GetZ() << endl;
    return out;
}

void operator >> (istream& in, Point &p) // istream& operator
{
    int x, y, z;
    in >> x >> y >> z;
    p.SetX(x);
    p.SetY(y);
    p.SetZ(z);
    //return in;
}

int main()
{
    string path = "uwu.txt";

    Point point(1, 2, 3);
    Point empti;

    /*
    ofstream fout;
    fout.open(path, ios::app); // app, in, out, ate, trunc, binary

    if(fout.is_open())
    {
        fout << point;
        fout << empti;
    }
    else
        cout << "smth is wrong bru" << endl;

    fout.close();
    */


    ifstream fin;
    fin.open(path);

    if(fin.is_open())
    {
        cout << "file is open" << endl;

        while(!fin.eof())
        {
            Point p;
            fin >> p;   // \n is equal to Point with trash
            cout << p << endl;
        }

    }
    else
        cout << "smth is wrong bru" << endl;

    fin.close();

    //empti.Print();


    /*
    ofstream fout;
    string path = "uwu.txt";
    fout.open(path, ios::app); // app, in, out, ate, trunc, binary

    if(fout.is_open())
    {
        fout << "koniciwaa" << endl;
        int a;
        cin >> a;
        fout << a << endl;
    }
    else
        cout << "smth is wrong bru" << endl;

    fout.close();
    */

    /*
    ifstream fin;
    fin.open(path);

    if(fin.is_open())
    {
        cout << "file is open" << endl;
        char ch;
        while(fin.get(ch))
        {
            cout << ch;
        }

    }
    else
        cout << "smth is wrong bru" << endl;

    fin.close();
    */

    /*
    fstream fs;
    fs.open(path, ios::in | ios::out | ios::app);


    int flag = 0;
    while (flag<1 || flag>2)
    {
        cout << "1 for writing, 2 for reading" << endl;
        cin >> flag;
    }

    if(fs.is_open() && flag == 1)
    {
        string s = "";
        cout << "input data:" << endl;
        cin >> s;
        fs << s << endl;
    }
    else if (fs.is_open() && flag == 2)
    {
        while(!fs.eof())
        {
            string s = "";
            fs >> s;
            cout << s << endl;
        }
    }
    else
    {
        cout << "smth is wrong bru" << endl;
    }
    */

    return 0;
}

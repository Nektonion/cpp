#include <iostream>
//#include <typeinfo>

using namespace std;

template <typename Type>
class TypeInfo
{
protected:
    Type unit;

public:

    TypeInfo(Type a)
    {
        this->unit = a;
    }

    void PrintInfo()
    {
        cout << unit << " has type: " << typeid(unit).name() << endl;
    }
};

template <typename Type>
class TypeSize : public TypeInfo<Type>
{
public:

    TypeSize(Type a): TypeInfo<Type>(a)
    {

    }

    void PrintSize()
    {
        cout << this->unit << " has size: " << sizeof(this->unit) << endl;
    }
};

int main()
{
    double a = 10;

    //TypeInfo<int> ti(a);
    //ti.PrintInfo();

    TypeSize<double> ts(a);
    ts.PrintSize();
    ts.PrintInfo();
    return 0;
}

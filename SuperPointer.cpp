#include <iostream>

using namespace std;

/*
 * template class for smart pointer, which delete itself by itself
 */

template<typename Type>
class SuperPointer;

template<typename Type>
ostream& operator << (ostream& os, SuperPointer<Type>& ptr)
{
    os << ptr.ptr;
    return os;
}

template<typename Type>
class SuperPointer
{
private:
    Type *ptr;

public:
    /*SuperPointer()
    {
        ptr = nullptr;
    }*/

    SuperPointer(Type *ptr)
    {
        this->ptr = ptr;
    }

    ~SuperPointer()
    {
        delete ptr;
    }

    Type& operator * ()
    {
        return *ptr;
    }

    friend ostream& operator << <Type>(ostream&, SuperPointer<Type>&);
};

int main()
{
    //int* a = new int(5);

    SuperPointer<double> b(new double(50.22));

    cout << b << endl;
    cout << *b << endl;


    //delete a;
    return 0;
}

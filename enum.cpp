#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Me
{
public:

    enum MyState
    {
        SLEEP,
        EAT,
        WORK,
        TRAIN
    };

private:

    MyState State;

public:

    void SetState(MyState State)
    {
        this->State = State;
    }

    MyState GetState()
    {
        return this->State;
    }
};

int main()
{
    Me i;

    i.SetState(Me::MyState::SLEEP);

    switch(i.GetState())
    {
    case Me::MyState::EAT:
        cout << "bonapeti" << endl;
        break;
    case Me::MyState::SLEEP:
        cout << "gunai" << endl;
        break;
    case Me::MyState::TRAIN:
        cout << "they don know me son" << endl;
        break;
    case Me::MyState::WORK:
        cout << "wokhad bro" << endl;
        break;
    }

    return 0;
}

#include <iostream>

using namespace std;

class Weapon
{
public:
    virtual void Shoot() = 0;
    virtual void Reload() = 0;
};

class Gun : public Weapon
{
private:
    int gunBullets;
public:

    Gun()
    {
        cout << "Makarov gun, 8/8" << endl;
        gunBullets = 8;
    }

    ~Gun()
    {
        cout << "you lose the gun" << endl;
    }

    void Shoot() override
    {
        if(gunBullets > 0)
        {
            cout << "Pew" << endl;
            gunBullets--;
        }
        else
        {
            cout << "no bullets, press R to reload" << endl;
        }
    }

    void Reload()
    {
        cout << "reloaded, 8/8" << endl;
        gunBullets = 8;
    }

};

class AssaultRifle : public Weapon
{
private:
    int rifleBullets;

public:
    AssaultRifle()
    {
        cout << "AK-47 assault rifle, 30/30" << endl;
        rifleBullets = 30;
    }

    ~AssaultRifle()
    {
        cout << "you lose the assault rifle" << endl;
    }

    void Shoot() override
    {
        if(rifleBullets >= 6)
        {
            cout << "RATATATATATA" << endl;
            rifleBullets -= 6;
        }
        else if(rifleBullets > 0)
            while(rifleBullets > 0)
            {
                cout << "Bang";
                rifleBullets--;
            }
        else
            cout << "no bullets, press R to reload" << endl;
        cout << endl;
    }

    void Reload()
    {
        cout << "reloaded, 30/30" << endl;
        rifleBullets = 30;
    }
};

class Player
{
public:
    void Shoot(Weapon* weapon)
    {
        weapon->Shoot();
    }

    void Reload(Weapon* weapon)
    {
        weapon->Reload();
    }
};

int main()
{
    Gun gun;
    AssaultRifle rifle;
    //Weapon w;

    Weapon *weapon = &rifle;

    Player misa;
    misa.Shoot(weapon);

    //weapon->Shoot();weapon->Shoot();weapon->Shoot();
    //weapon->Shoot();weapon->Shoot();weapon->Shoot();
    //weapon->Reload();

    return 0;
}

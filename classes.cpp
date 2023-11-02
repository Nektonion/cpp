#include <iostream>
#include <string>
//#include <vector>
//#include <algorithm> // for sort

//#define DEBUG


using namespace std;

//class Badminton;
class Student;
class Graduate;
class Rocket;
class Badminton;

class Graduate : public Student
{
private:
    string almaMatter;
    Graduate()
    {
        almaMatter = "-";
    }

    ~Graduate()
    {

    }
};


class Badminton
{
private:
    static int BadmintonCount;
    int BadmintonId;
    string rocket;
    string category;
    string education;

public:
    string name;

    Badminton()
    {
        name = "-";
        category = "beginner";
        rocket = "-";
        BadmintonCount++;
        BadmintonId = BadmintonCount;
    }

    Badminton(string name):Badminton()
    {
        this->name = name;
    }

    Badminton(string name, string category, string rocket):Badminton(name)
    {
        this->rocket = rocket;
        this->category = category;
    }

    ~Badminton()
    {
        BadmintonCount--;
    }

    Badminton& BuyRocket(Rocket& NewRocket);

    Badminton& SellRocket(Rocket& ByeRocket);

    static int GetCount()
    {
        return BadmintonCount;
    }

    int GetId()
    {
        return BadmintonId;
    }

    string GetRocket()
    {
        return this->rocket;
    }

    void Info()
    {
        cout << "name: " << name << endl;
        cout << "category: " << category << endl;
        cout << "rocket: " << rocket << endl << endl;
    }
};

// there is aggregation with Badminton, but it will be better a composition
class Rocket
{
private:
    int weight;
    string name;
    int RocketId;
    static int RocketCount;

public:
    Rocket()
    {
        weight = 0;
        name = "-";
        RocketCount++;
        RocketId = RocketCount;
    }

    Rocket(string name, int weight):Rocket()
    {
        this->weight = weight;
        this->name = name;
    }

    ~Rocket()
    {

        RocketCount--;
        //cout << "destructor" << endl;
    }

    int GetId()
    {
        return RocketId;
    }

    static int GetCount()
    {
        return RocketCount;
    }

    friend Badminton& Badminton::SellRocket(Rocket& ByeRocket);

    friend Badminton& Badminton::BuyRocket(Rocket& NewRocket);
};

class Student
{
    friend Badminton;

private:
    int age;
    int StudentId;
    string education;
    string hobby;
    string group;
    static int StudentCount;

public:
    string name;

    Student()
    {
        StudentCount++;
        StudentId = StudentCount;
        name = "-";
        age = 0;
        education = "enrollee";
        hobby = "-";
        group = "-";
    }

    Student(string name):Student()
    {
        this->name = name;
        age = 18;
    }

    ~Student()
    {
        StudentCount--;
    }

    static int GetCount()
    {
        return StudentCount;
    }

    int GetId()
    {
        return StudentId;
    }

    void SetAge(int Age)
    {
        this->age = Age;
    }

    static void HappyBirthday(Student &student)
    {
        cout << "Happy Birthday, " << student.name << "!\n\n";
        student.age++;
    }

    void SetEducation(string Education)
    {
        this->education = Education;
    }

    void SetHobby(string Hobby)
    {
        this->hobby = Hobby;
    }

    void SetGroup(string Group)
    {
        this->group = Group;
    }

    void Info()
    {
        cout << "name: " << name << endl;
        cout << "age: " << age << endl;
        cout << "education: " << education << endl;
        cout << "hobby: " << hobby << endl;
        cout << "group: " << group << endl << endl;
    }

    Student& JoinBadminton(Badminton& WhoInvited)
    {
        hobby = "badminton";
        group = "sport group";
        cout << WhoInvited.name << " invited his friend " << name << endl << endl;
        return *this;
    }
};

int Student::StudentCount = 0;
int Rocket::RocketCount = 0;
int Badminton::BadmintonCount = 0;

int main()
{
    Badminton Adolf("Adolf");
    Adolf.Info();

    Rocket rocket("Yonex 1488", 128);

    Adolf.BuyRocket(rocket);

    Adolf.Info();

    Student Benito("Benito");

    Benito.Info();

    if(Adolf.GetRocket() != "-")
        Benito.JoinBadminton(Adolf);

    Student::HappyBirthday(Benito);
    Benito.Info();

    Adolf.SellRocket(rocket);

    Adolf.Info();

    return 0;
}

Badminton& Badminton::BuyRocket(Rocket& NewRocket)
{
    cout << "Player bought a new rocket: " << endl;
    cout << "weight = " << NewRocket.weight << ", name: " << NewRocket.name << endl << endl;
    this->rocket = NewRocket.name;
    return *this;
}

Badminton& Badminton:: SellRocket(Rocket& ByeRocket)
{
    if(this->rocket == "-")
    {
        cout << "there's no rocket to sell" << endl;
        return *this;
    }
    else
    {
        cout << this->name <<" sell his rocket: " << endl;
        cout << "weight = " << ByeRocket.weight << ", name: " << ByeRocket.name << endl << endl;
        this->rocket = "-";
    }
    return *this;
}


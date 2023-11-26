#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person
{
private:
    string afm;
    string name;
    int age;
    int isStudent;

public:
    Person()
    {
        afm = "";
        name = "";
        age = 0;
        isStudent = -1;
        cout << "Default constructor called" << endl;

    }; // Defult Constructor

    Person(string af, string n, int ag, int i)
    {
        afm = af;
        name = n;
        age = ag;
        isStudent = i;
    }

    ~Person(){}; // Destructor

    // Overloading >> operator
    friend istream &operator>>(istream &is, Person &person)
    {
        cout << "Is student (1 for yes, 0 for no): ";
        is >> person.isStudent;

        cout << "AFM: ";
        is >> person.afm;

        cout << "Name: ";
        is >> person.name;

        cout << "Age: ";
        is >> person.age;

        return is;
    }

    // Overloading << operator
    friend ostream &operator<<(ostream &os, Person &person)
    {
        string profession;

        if (person.isStudent = 1)
        {
            profession = "Student";
        }
        else if (person.isStudent = 0)
        {
            profession = "Professor";
        }
        else
        {
            profession = "Undefined";
        }

        os << "Profession: " << profession << ", AFM: " << person.afm << ", Name: " << person.name << ", Age: " << person.age;
        return os;
    }
    string getName()
    {
        return name;
    }
};

int main()
{

    return 0;
}
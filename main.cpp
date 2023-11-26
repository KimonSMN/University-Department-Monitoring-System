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
    string getAFM()
    {
        return afm;
    }
};

class Secretary
{
private:
    vector<Person *> department;

public:
    Secretary();
    ~Secretary()
    {
        for (auto &person : department)
        {
            delete person; // Deallocate memory for each Person object
        }
    };

    // Copy constructor
    Secretary(const Secretary &other)
    {
        for (auto &person : other.department)
        {
            department.push_back(new Person(*person)); // Create a new copy of each Person and add to the department
        }
    }

    // Overloading assignment operator
    Secretary &operator=(const Secretary &other)
    {
        if (this == &other)
        {
            return *this; // Self-assignment, return current object
        }

        // Clear current department contents
        for (auto &person : department)
        {
            delete person;
        }
        department.clear();

        // Copy elements from the other Secretary
        for (auto &person : other.department)
        {
            department.push_back(new Person(*person)); // Create a new copy of each Person and add to the department
        }
        return *this; // Return the updated object
    }

    // Overloading + operator
    Secretary &operator+(Person *newPerson)
    {
        department.push_back(newPerson);
        return *this;
    }

    // Overloading << operator for Secretary
    friend ostream &operator<<(ostream &os, Secretary &secretary)
    {
        os << "Department Information:" << endl;
        for (auto &person : secretary.department)
        {
            os << *person << endl;
        }
        return os;
    }

    // Overloading >> operator for Secretary
    friend istream &operator>>(istream &is, Secretary &secretary)
    {
        Person *newPerson = new Person();
        is >> *newPerson;
        secretary.department.push_back(newPerson);
        return is;
    }

    // Find a person by AFM
    string findPerson(const string &afm)
    {
        for (auto &person : department)
        {
            if (person->getAFM() == afm)
            {
                return "Person Found"; // Person Found
            }
        }
        return "Person NOT Found"; // Person NOT Found
    }
};

int main()
{

    return 0;
}
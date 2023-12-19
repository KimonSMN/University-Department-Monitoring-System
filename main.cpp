#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person
{
private:
    static int counter; // Variable to count Person objects
    string afm;         // AFM of Person object
    string name;        // Name of Person object
    int age;            // Age of Person object
    int isStudent;      // Variable to check Profession

public:
    // Default Constructor for Person
    Person()
    {
        afm = "";
        name = "";
        age = 0;
        isStudent = -1;
        counter++;
        cout << "Default constructor called" << endl;
    };

    // Constructor with Parameters for Person
    Person(string af, string n, int ag, int i)
    {
        afm = af;
        name = n;
        age = ag;
        isStudent = i;
        counter++;
    }

    // Destructor for Person
    ~Person(){};

    // Function to get the counter value
    static int getCounter()
    {
        return counter;
    }

    // Overload of >> operator
    friend istream &operator>>(istream &is, Person &person)
    {
        cout << "Is student (1 for yes, 0 for no): ";
        is >> person.isStudent;

        cout << "AFM (numbers only): ";
        while (true) // Checks if AFM is correct
        {
            is >> person.afm;
            bool validAfm = true;
            for (char c : person.afm) // For every char in person.afm
            {
                if (!isdigit(c)) // Check if character is NOT decimal digit (0-9)
                {
                    validAfm = false;
                    break;
                }
            }
            if (validAfm)
            {
                break;
            }
            else
            {
                cout << "Invalid AFM! Please enter numbers only: ";
            }
        }

        cout << "Name: ";
        is >> person.name;

        cout << "Age (positive number): ";
        while (true) // Checks if Age is positive number
        {
            is >> person.age;
            if (person.age > 0)
            {
                break;
            }
            else
            {
                cout << "Invalid Age! Please enter a positive number: ";
            }
        }

        return is;
    }

    // Overload of << operator
    friend ostream &operator<<(ostream &os, Person &person)
    {
        string profession;

        if (person.isStudent == 1)
        {
            profession = "Student";
        }
        else if (person.isStudent == 0)
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

    // Function to return the afm
    string getAFM()
    {
        return afm;
    }
};

int Person::counter = 0; // Initializing the static member variable

class Secretary
{
private:
    vector<Person *> department; // Vector to store the Person objects

public:
    // Constructor
    Secretary(){};
    // Destructor
    ~Secretary()
    {
        for (auto &person : department) // For every Person in department
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
            return *this; // Return current object
        }

        for (auto &person : department)
        {
            delete person; // Deallocate memory for each Person object
        }
        department.clear();

        // Copy elements from the other department
        for (auto &person : other.department)
        {
            department.push_back(new Person(*person)); // Create a new copy of each Person, add them to the department
        }
        return *this; // Return the new object
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

class Student : public Person
{
public:
    // Student-specific attributes and methods can be added here
    Student() : Person() {}                                        // Default constructor
    Student(string af, string n, int ag) : Person(af, n, ag, 1) {} // Constructor with parameters
};

class Professor : public Person
{
public:
    // Professor-specific attributes and methods can be added here
    Professor() : Person() {}                                        // Default constructor
    Professor(string af, string n, int ag) : Person(af, n, ag, 0) {} // Constructor with parameters
};

class Course
{
private:
    int semester;     // Semester of the course (1-8)
    int points;       // Points awarded by the course
    bool isMandatory; // Whether the course is mandatory

public:
    // Constructors
    Course() : semester(1), points(0), isMandatory(false) {}
    Course(int sem, int pts, bool mandatory) : semester(sem), points(pts), isMandatory(mandatory) {}

    // Getters and setters for private attributes
    int getSemester() const { return semester; }
    void setSemester(int sem) { semester = sem; }

    int getPoints() const { return points; }
    void setPoints(int pts) { points = pts; }

    bool getIsMandatory() const { return isMandatory; }
    void setIsMandatory(bool mandatory) { isMandatory = mandatory; }
};

int main()
{

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
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

    static int getCounter() { return counter; } // Function to get the counter value
    string getAFM() { return afm; }             // Function to return the afm
    string getName() { return name; }           // Function to return the name
    int getAge() { return age; }                // Function to return the age

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
};

// int Person::counter = 0; // Initializing the static member variable

class Secretary
{
private:
    vector<Student *> allStudents;
    vector<Professor *> allProfessors;
    vector<Course *> allCourses;
    vector<Semester *> allSemesters;

public:
    // Constructor
    Secretary(){};
    // Destructor
    ~Secretary(){};
};

class Student : private Person
{
private:
    int currentSemester;
    int accumulatedPoints;
    int finalGrade;
    vector<Course *> enrolledCourses;

public:
    string getStudentName()
    {
        return getName();
    }
};

class Professor : private Person
{
private:
    vector<Course *> taughtCourses;

public:
    Professor()
    {

    } // Constructor
};

class Course
{
private:
    string courseName;
    int semester;
    int points;
    bool isMandatory;
    vector<Student *> enrolledStudents;
    vector<Professor *> assignedProfessors;

public:
};

class Semester
{
private:
    vector<Course *> coursesOffered;

public:
};

main()
{
    return 0;
}

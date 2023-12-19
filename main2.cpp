#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Forward declarations
class Student;
class Professor;

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

class Course
{
public:
    string courseName;                      // Course name
    int semester;                           // Semester of Course
    int points;                             // Points that Course gives
    bool isMandatory;                       // Course Required
    vector<Student *> enrolledStudents;     // Vector of Students attending Course
    vector<Professor *> assignedProfessors; // Vectir of Professors assigned in Course

    Course(string name, int sem, int pts, bool mandatory)
        : courseName(name), semester(sem), points(pts), isMandatory(mandatory) {}
};

class Semester
{
public:
    int semesterNumber;
    vector<Course *> coursesOffered;

    Semester(int number) : semesterNumber(number) {}

    void addCourse(Course *course)
    {
        if (course->semester == semesterNumber)
        {
            coursesOffered.push_back(course);
        }
    }

    void displayCourses()
    {
        cout << "Semester " << semesterNumber << " Courses:\n";
        for (auto course : coursesOffered)
        {
            cout << "  " << course->courseName << " - Points: " << course->points
                 << ", Mandatory: " << (course->isMandatory ? "Yes" : "No") << "\n";
        }
    }
};

class Student : public Person
{
private:
    int currentSemester;
    int accumulatedPoints;
    int finalGrade;
    vector<Course *> enrolledCourses;

public:
    // Constructor for Student
    Student() : currentSemester(0), accumulatedPoints(0), finalGrade(0)
    {
        cout << "Student constructor called" << endl;
    }
    // Destructor
    ~Student()
    {
        cout << "Student destructor called" << endl;
    }
};

class Professor : public Person
{
private:
    vector<Course *> taughtCourses;

public:
    // Constructor for Professor
    Professor()
    {
        cout << "Professor constructor called" << endl;
    }
    // Destructor
    ~Professor()
    {
        cout << "Professor destructor called" << endl;
    }
};

class Secretary
{
private:
    vector<Student *> allStudents;
    vector<Professor *> allProfessors;
    vector<Course *> allCourses;
    vector<Semester *> allSemesters;

public:
    // Constructor for Secretary
    Secretary()
    {
        cout << "Secretary constructor called" << endl;
    }
    // Destructor
    ~Secretary()
    {
        for (Student *student : allStudents)
        {
            delete student;
        }
        for (Professor *professor : allProfessors)
        {
            delete professor;
        }
        for (Course *course : allCourses)
        {
            delete course;
        }
        for (Semester *semester : allSemesters)
        {
            delete semester;
        }
        cout << "Secretary destructor called" << endl;
    }
};

int Person::counter = 0;

int main()
{
    // Create two semesters
    Semester semester1(1), semester2(2);

    // Create courses
    Course course1("Mathematics", 1, 5, true);
    Course course2("Physics", 1, 4, false);
    Course course3("Literature", 2, 3, true);
    Course course4("Chemistry", 2, 4, false);

    // Add courses to semesters
    semester1.addCourse(&course1);
    semester1.addCourse(&course2);
    semester2.addCourse(&course3);
    semester2.addCourse(&course4);

    // Writing to courses.csv file
    ofstream coursesFile("courses.csv");
    coursesFile << "Course Name,Semester,Points,Mandatory\n";
    coursesFile << course1.courseName << "," << course1.semester << "," << course1.points << "," << course1.isMandatory << "\n";
    coursesFile << course2.courseName << "," << course2.semester << "," << course2.points << "," << course2.isMandatory << "\n";
    coursesFile << course3.courseName << "," << course3.semester << "," << course3.points << "," << course3.isMandatory << "\n";
    coursesFile << course4.courseName << "," << course4.semester << "," << course4.points << "," << course4.isMandatory << "\n";
    coursesFile.close();

    // Display courses in each semester
    semester1.displayCourses();
    semester2.displayCourses();

    return 0;
}

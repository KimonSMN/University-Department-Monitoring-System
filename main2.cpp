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

    static int getCounter() { return counter; }      // Function to get the counter value
    string getAFM() { return afm; }                  // Function to return the afm
    string getName() const { return name; }          // Function to return the name
    int getAge() { return age; }                     // Function to return the age
    int getIfStudent() { return isStudent; }         // Function to return If Student
    void setName(string newName) { name = newName; } // Function to set Name
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

// class Semester
// {
// public:
//     int semesterNumber;
//     vector<Course *> coursesOffered;

//     Semester(int number) : semesterNumber(number) {}

//     void addCourse(Course *course)
//     {
//         if (course->semester == semesterNumber)
//         {
//             coursesOffered.push_back(course);
//         }
//     }

//     void displayCourses()
//     {
//         cout << "Semester " << semesterNumber << " Courses:\n";
//         for (auto course : coursesOffered)
//         {
//             cout << "  " << course->courseName << " - Points: " << course->points
//                  << ", Mandatory: " << (course->isMandatory ? "Yes" : "No") << "\n";
//         }
//     }
// };

class Student : public Person
{
private:
    int currentSemester;
    int accumulatedPoints;
    int finalGrade;
    vector<Course *> enrolledCourses;

public:
    // Constructor for Student
    Student() : currentSemester(0), accumulatedPoints(0), finalGrade(0) {}
    // Destructor
    ~Student() {}

    void enrollInCourse(Course *course) // Function to Enroll in course
    {
        if (course->semester <= currentSemester) // If the semester is equal or less than the currentSemester
        {
            enrolledCourses.push_back(course);
        }
    }

    // Calculate Points
    int getAccumulatedPoints()
    {
        return accumulatedPoints;
    }
};

class Professor : public Person
{
private:
    vector<Course *> taughtCourses;

public:
    // Constructor for Professor
    Professor() {}
    // Destructor
    ~Professor() {}

    void assignToCourse(Course *course) // Assigns Self to Course
    {
        taughtCourses.push_back(course);
    }
};

class Secretary
{
private:
    vector<Student *> allStudents;
    vector<Professor *> allProfessors;
    vector<Course *> allCourses;

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
        cout << "Secretary destructor called" << endl;
    }

    void loadStudents()
    {
        ifstream file("students.csv");
        string line;

        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }
        while (getline(file, line))
        {
            stringstream ss(line);
            string name;
            if (getline(ss, name, ',')) // Assuming name is the first item before the comma
            {
                Student *newStudent = new Student(); // Assuming such a constructor exists
                newStudent->setName(name);
                allStudents.push_back(newStudent);
            }
        }

        file.close();
    }

    void loadProfessors()
    {
        ifstream file("professors.csv");
        string line;

        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }
        while (getline(file, line))
        {
            stringstream ss(line);
            string name;
            if (getline(ss, name, ',')) // Assuming name is the first item before the comma
            {
                Professor *newProfessor = new Professor(); // Assuming such a constructor exists
                newProfessor->setName(name);
                allProfessors.push_back(newProfessor);
            }
        }

        file.close();
    }

    void enrollStudent(Student *student, Course *course) // Assigns student to Course
    {
        if (student && course)
        { // Check if the pointers are not null
            student->enrollInCourse(course);
        }
    }

    void assignProfessor(Professor *professor, Course *course) // Assigns Professor to Course
    {
        if (professor && course)
        { // Check if the pointers are not null
            professor->assignToCourse(course);
        }
    }

    // Getter for allStudents
    const vector<Student *> &getStudents() const { return allStudents; }

    // Getter for allProfessors
    const vector<Professor *> &getProfessors() const { return allProfessors; }

    // Getter for allCourses
    const vector<Course *> &getCourses() const { return allCourses; }
};

int Person::counter = 0;

int main()
{
    Secretary secretary;

    // Load students and professors from the respective CSV files
    secretary.loadStudents();
    secretary.loadProfessors();

    // Assuming the CSV files have at least one student and one professor,
    // and for demonstration purposes, we create a course manually.
    Course *exampleCourse = new Course("Intro to Programming", 1, 3, true);

    // Enrolling the first student in the example course
    if (!secretary.getStudents().empty())
    {
        secretary.enrollStudent(secretary.getStudents().front(), exampleCourse);
    }

    // Assigning the first professor to the example course
    if (!secretary.getProfessors().empty())
    {
        secretary.assignProfessor(secretary.getProfessors().front(), exampleCourse);
    }

    // Displaying loaded students
    cout << "Loaded Students: " << endl;
    for (const auto *student : secretary.getStudents())
    {
        cout << student->getName() << endl;
    }

    // Displaying loaded professors
    cout << "Loaded Professors: " << endl;
    for (const auto *professor : secretary.getProfessors())
    {
        cout << professor->getName() << endl;
    }

    // Clean up the dynamically allocated Course object
    delete exampleCourse;

    return 0;
}

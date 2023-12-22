#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

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
    string getAFM() const { return afm; }            // Function to return the afm
    string getName() const { return name; }          // Function to return the name
    int getAge() const { return age; }               // Function to return the age
    int getIfStudent() const { return isStudent; }   // Function to return If Student
    void setName(string newName) { name = newName; } // Function to set Name
    void setAfm(string newAfm) { afm = newAfm; }     // Function to set Afm
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
    int courseId;                           // Course Id
    string courseName;                      // Course name
    int semester;                           // Semester of Course
    int points;                             // Points that Course gives
    bool isMandatory;                       // Course Required
    vector<Student *> enrolledStudents;     // Vector of Students attending Course
    vector<Professor *> assignedProfessors; // Vectir of Professors assigned in Course

    Course(int newCourseId) : courseId(newCourseId) {}
    void setId(int newCourseId) { courseId = newCourseId; } // Function to set Name
    void setName(string newName) { courseName = newName; }  // Function to set Name
    string getName() const { return courseName; }           // Function to return Name
    int getCourseId() const { return courseId; }            // Function to return Course Id
};

class Student : public Person
{
private:
    int currentSemester;
    int accumulatedPoints;
    int finalGrade;
    bool graduated;
    vector<Course *> enrolledCourses;

public:
    // Constructor for Student
    Student() : currentSemester(0), accumulatedPoints(0), finalGrade(0), graduated(0) {}
    // Destructor
    ~Student() {}

    void enrollInCourse(Course *course) // Function to Enroll in course
    {
        if (course->semester <= currentSemester) // If the semester is equal or less than the currentSemester
        {
            enrolledCourses.push_back(course);
        }
    }

    void checkGraduation() // Function to check if able to graduate
    {
        if (currentSemester > 8 && accumulatedPoints >= 240) //
        {
            graduated = 1;
            cout << "You can Graduate!" << endl;
        }
        else
        {
            cout << "You can't Graduate yet" << endl;
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

bool isAFMInStudents(
    const vector<Student *> &vec,
    const string &afm)
{
    for (const auto &student : vec)
    {
        if (student->getAFM() == afm)
        {
            return true; // AFM found in one of the students
        }
    }
    return false; // AFM not found
}

class Secretary
{
private:
    vector<Student *> allStudents;
    vector<Professor *> allProfessors;
    vector<Course *> allCourses;

public:
    // Constructor for Secretary
    Secretary() {}
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

        // Skip the first line (header)
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string name, afm;
            int age;

            getline(ss, name, ',');
            getline(ss, afm, ',');
            ss >> age; // Assuming further parsing for age, etc.

            // Trim the AFM string
            afm = trim(afm);

            // Debug output
            cout << "Debug: AFM = '" << afm << "'" << endl;

            if (afm.empty())
            {
                cerr << "Warning: Empty AFM found, skipping line." << endl;
                continue; // Skip this line if AFM is empty
            }

            Student *newStudent = new Student();
            newStudent->setAfm(afm);
            newStudent->setName(name);
            // Set other properties as needed

            allStudents.push_back(newStudent);
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

        // Skip the first line (header)
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string name, afm;
            int age;

            getline(ss, name, ',');
            getline(ss, afm, ',');
            ss >> age; // Assuming further parsing for age, etc.

            // Trim the AFM string
            afm = trim(afm);

            // Debug output
            cout << "Debug: AFM = '" << afm << "'" << endl;

            if (afm.empty())
            {
                cerr << "Warning: Empty AFM found, skipping line." << endl;
                continue; // Skip this line if AFM is empty
            }

            Professor *newProfessor = new Professor();
            newProfessor->setAfm(afm);
            newProfessor->setName(name);
            // Set other properties as needed

            allProfessors.push_back(newProfessor);
        }

        file.close();
    }

    void loadCourses()
    {
        ifstream file("courses.csv");
        string line;

        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }

        // Skip the first line (header)
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            int courseId;
            string temp, courseName; // Use 'temp' to read courseId as string and convert it to int
            int semester, points;
            bool mandatory;

            getline(ss, temp, ',');
            courseId = stoi(trim(temp)); // Convert to int after trimming
            getline(ss, courseName, ',');
            ss >> semester >> points;
            ss.ignore(); // Ignore the comma after points
            ss >> mandatory;

            // Debug output
            cout << "Debug: CourseId = '" << courseId << "', CourseName = '" << courseName << "'" << endl;

            // Create a new Course object with courseId
            Course *newCourse = new Course(courseId);

            allCourses.push_back(newCourse);
        }

        file.close();
    }

    void enrollStudent(Student *student, Course *course) // Assigns student to Course
    {
        if (student && course) // Check if the pointers are not null
            student->enrollInCourse(course);
    }

    void assignProfessor(Professor *professor, Course *course) // Assigns Professor to Course
    {
        if (professor && course) // Check if the pointers are not null
            professor->assignToCourse(course);
    }

    void addStudent(const string &name, const string &afm, int age)
    {
        // Open the students.csv file in append mode
        ofstream file("students.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        // Write the new student's information to the file
        file << name << "," << afm << "," << age << "," << 1 << "," << 0 << endl;

        // Create a new Student object
        Student *newStudent = new Student();
        newStudent->setAfm(afm);
        // Assuming other properties (afm, age, etc.) are set through appropriate methods or constructors

        // Add the new Student to the allStudents vector
        allStudents.push_back(newStudent);

        // Close the file
        file.close();
    }

    void removeStudent(const string &afm)
    {
        bool removed = false;
        for (auto it = allStudents.begin(); it != allStudents.end();)
        {
            if ((*it)->getAFM() == afm)
            {
                delete *it;                 // Free the memory of the student object
                it = allStudents.erase(it); // Remove the student from the vector and update the iterator
                removed = true;
            }
            else
            {
                ++it; // Only increment if not erased
            }
        }

        if (removed)
        {
            cout << "Student with AFM " << afm << " has been removed." << endl;
            // Rewrite the students.csv file without the removed student
            ofstream file("students.csv");
            if (!file.is_open())
            {
                cerr << "Error opening file for writing" << endl;
                return;
            }

            // Write the header
            file << "Name,Afm,Age,Current Semester,Accumulated Points" << endl;

            // Write the remaining students to the file
            for (const auto *student : allStudents)
            {
                file << student->getName() << ","
                     << student->getAFM() << ","
                     << student->getAge() << ","
                     << "1,0" << endl; // Assuming default values for Current Semester and Accumulated Points
            }

            file.close();
        }
        else
        {
            cout << "The AFM is not in the vector." << endl;
        }
    }

    void addProfessor(const string &name, const string &afm, int age)
    {
        // Open the students.csv file in append mode
        ofstream file("professors.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        // Write the new student's information to the file
        file << name << "," << afm << "," << age << endl;

        // Create a new Student object
        Professor *newProfessor = new Professor();
        newProfessor->setAfm(afm);
        // Assuming other properties (afm, age, etc.) are set through appropriate methods or constructors

        // Add the new Student to the allStudents vector
        allProfessors.push_back(newProfessor);

        // Close the file
        file.close();
    }

    const vector<Student *> &getStudents() const { return allStudents; }       // Getter for allStudents
    const vector<Professor *> &getProfessors() const { return allProfessors; } // Getter for allProfessors
    const vector<Course *> &getCourses() const { return allCourses; }          // Getter for allCourses
};

int Person::counter = 0;

int main()
{
    // Create an instance of Secretary
    Secretary secretary;

    // Load students and professors from CSV files
    secretary.loadStudents();
    secretary.loadProfessors();
    secretary.loadCourses();

    // Displaying loaded students before removal
    cout << "Loaded Students Before Removal: " << endl;
    for (const auto *student : secretary.getStudents())
    {
        cout << "AFM: " << student->getAFM() << endl;
    }

    // Remove a student by AFM
    string afmToRemove = "005"; // Replace with an actual AFM from your loaded data
    cout << "Removing student with AFM: " << afmToRemove << endl;
    secretary.removeStudent(afmToRemove);

    // Displaying loaded students after removal
    cout << "Loaded Students After Removal: " << endl;
    for (const auto *student : secretary.getStudents())
    {
        cout << "AFM: " << student->getAFM() << endl;
    }

    // Displaying loaded professors
    cout << "Loaded Professors: " << endl;
    for (const auto *professor : secretary.getProfessors())
    {
        cout << "Name: " << professor->getName() << endl;
    }

    // Displaying loaded courses
    cout << "Loaded Courses: " << endl;
    for (const auto *course : secretary.getCourses())
    {
        cout << "Course Id: " << course->getCourseId() << endl;
    }

    return 0;
}

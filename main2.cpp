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
    void setName(string newName) { name = newName; } // Function to set Name
    void setAfm(string newAfm) { afm = newAfm; }     // Function to set Afm
    void setAge(int newAge) { age = newAge; }        // Function to set Age

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
    int graduated;
    vector<Course *> enrolledCourses;

public:
    // Constructor for Student
    Student(string name, string afm, int age, int newCurrentSemester, int newAccumulatedPoints,
            int newFinalGrade, int newGraduated)
    {
        setName(name);
        setAfm(afm);
        setAge(age);
        currentSemester = newCurrentSemester;
        accumulatedPoints = newAccumulatedPoints;
        finalGrade = newFinalGrade;
        graduated = newGraduated;
    }
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

    void setCurrentSemester(int newCurrentSemester)
    {
        currentSemester = newCurrentSemester;
    }

    void setAccumulatedPoints(int newAccumulatedPoints)
    {
        accumulatedPoints = newAccumulatedPoints;
    }

    void setFinalGrade(int newFinalGrade)
    {
        finalGrade = newFinalGrade;
    }

    void setGraduated(bool isGraduated)
    {
        graduated = isGraduated;
    }

    int getCurrentSemester() const
    {
        return currentSemester;
    }

    int getAccumulatedPoints() const
    {
        return accumulatedPoints;
    }

    int getFinalGrade() const
    {
        return finalGrade;
    }

    int getGraduated() const
    {
        return graduated;
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

        getline(file, line); // Skip the first line (header)

        while (getline(file, line))
        {
            stringstream ss(line);
            string name, afm, age, currentSemester, finalGrade, accumulatedPoints, graduated;

            getline(ss, name, ',');
            getline(ss, afm, ',');
            getline(ss, age, ',');
            getline(ss, currentSemester, ',');
            getline(ss, accumulatedPoints, ',');
            getline(ss, finalGrade, ',');
            getline(ss, graduated, ',');

            name = trim(name);
            afm = trim(afm);
            age = trim(age);
            currentSemester = trim(currentSemester);
            accumulatedPoints = trim(accumulatedPoints);
            finalGrade = trim(finalGrade);
            graduated = trim(graduated);

            Student *newStudent = new Student(name, afm, stoi(age), stoi(currentSemester), stoi(accumulatedPoints), stoi(finalGrade), stoi(graduated));
            allStudents.push_back(newStudent);
            cout << name << "," << afm << "," << age << "," << currentSemester << "," << accumulatedPoints << "," << finalGrade << "," << graduated << endl;
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
        file << name << "," << afm << "," << age << "," << 1 << "," << 0 << "," << 0 << "," << 0 << endl;

        // Create a new Student object
        Student *newStudent = new Student(name, afm, age, 1, 0, 0, 0);

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
            file << "name,afm,age,currentSemester,accumulatedPoints,finalGrade,graduated" << endl;

            // Write the remaining students to the file
            for (const auto *student : allStudents)
            {
                file << student->getName() << ","
                     << student->getAFM() << ","
                     << student->getAge() << ","
                     << student->getCurrentSemester() << ","
                     << student->getAccumulatedPoints() << ","
                     << student->getFinalGrade() << ","
                     << student->getGraduated() << endl;
            }

            file.close();
        }
        else
        {
            cout << "The AFM is not in the vector." << endl;
        }
    }

    void editStudent(const string &afm)
    {
        Student *studentToEdit = nullptr;

        // Find the student in the allStudents vector
        for (auto &student : allStudents)
        {
            if (student->getAFM() == afm)
            {
                studentToEdit = student;
                break;
            }
        }

        if (!studentToEdit)
        {
            cout << "Student with AFM " << afm << " not found." << endl;
            return;
        }

        string newName;
        int newAge, newCurrentSemester, newAccumulatedPoints, newFinalGrade;
        bool newGraduated;
        int change;

        cout << "What would you like to change on student with afm: " << afm << endl;
        cout << "1. Name" << endl
             << "2. Age" << endl
             << "3. Current Semester" << endl
             << "4. Accumulated Points" << endl
             << "5. Final Grade" << endl
             << "6. Gratuated" << endl
             << "Enter 1-6: " << endl;

        cin >> change;

        switch (change)
        {
        case 1:
            cout << "Enter new Name: ";
            cin >> newName;
            studentToEdit->setName(newName);
            break;
        case 2:
            cout << "Enter new Age: ";
            cin >> newAge;
            studentToEdit->setAge(newAge);
            break;
        case 3:
            cout << "Enter new Current Semester: ";
            cin >> newCurrentSemester;
            studentToEdit->setCurrentSemester(newCurrentSemester);
            break;
        case 4:
            cout << "Enter new Accumulated Points: ";
            cin >> newAccumulatedPoints;
            studentToEdit->setAccumulatedPoints(newAccumulatedPoints);
            break;
        case 5:
            cout << "Enter new Final Grade: ";
            cin >> newFinalGrade;
            studentToEdit->setFinalGrade(newFinalGrade);
            break;
        case 6:
            cout << "Enter new Gratuated: ";
            cin >> newGraduated;
            studentToEdit->setGraduated(newGraduated);
            break;
        }

        // Rewrite the students.csv file with updated details
        ofstream file("students.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        file << "Name,Afm,Age,Current Semester,Accumulated Points,Final Grade,Graduated" << endl;

        for (const auto &student : allStudents)
        {
            file << student->getName() << ","
                 << student->getAFM() << ","
                 << student->getAge() << ","
                 << student->getCurrentSemester() << ","
                 << student->getAccumulatedPoints() << ","
                 << student->getFinalGrade() << ","
                 << student->getGraduated() << endl;
        }

        file.close();
        cout << "Student details updated successfully." << endl;
    }

    void removeProfessor(const string &afm)
    {
        bool removed = false;
        for (auto it = allProfessors.begin(); it != allProfessors.end();)
        {
            if ((*it)->getAFM() == afm)
            {
                delete *it;
                it = allProfessors.erase(it); // Remove the student from the vector and update the iterator
                removed = true;
            }
            else
            {
                ++it; // Only increment if not erased
            }
        }

        if (removed)
        {
            cout << "Professor with AFM " << afm << " has been removed." << endl;
            ofstream file("professors.csv");
            if (!file.is_open())
            {
                cerr << "Error opening file for writing" << endl;
                return;
            }

            // Write the header
            file << "Name,Afm,Age" << endl;

            // Write the remaining students to the file
            for (const auto *professor : allProfessors)
            {
                file << professor->getName() << ","
                     << professor->getAFM() << ","
                     << professor->getAge() << endl;
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

// int main()
// {
//     // Create an instance of Secretary
//     Secretary secretary;

//     int loginOption, methodOption, age;
//     string name, afm;
//     cout << "\n\t Welcome to my University Department Monitor System" << endl;

//     cout << "1. Login As Student" << endl;
//     cout << "2. Login As Professor" << endl;
//     cout << "3. Login As Secretary" << endl;
//     cout << "Give option 1 - 3 : ";
//     cin >> loginOption;

//     switch (loginOption)
//     {
//     case 1: // Student
//         cout << "\tYou are logged in as a Student" << endl;
//         cout << "Give your AFM: ";
//         cin >> afm;

//         cout << "1. Enroll self to course" << endl;
//         cout << "2. Calculate Accumulated Points" << endl;
//         cout << "3. Check graduation eligibility" << endl;
//         cout << "Give option 1 - 3 : " << endl;
//         cin >> methodOption;

//         switch (methodOption)
//         {
//         case 1:
//             // Enroll student to course
//             break;
//         case 2:
//             // Calculate Accumulated Points
//             break;
//         case 3:
//             // Check graduation eligibility
//             break;
//         }
//         break;

//     case 2: // Professor
//         cout << "\tYou are logged in as a Professor" << endl;
//         cout << "Give your AFM: ";
//         cin >> afm;

//         cout << "1. Set Finals grade for student" << endl;
//         cout << "2. Conduct Finals Exam" << endl; // Make it look cool! ex. Loading Final scores... Students are given random score.
//         cout << "Give option 1 - 2 : " << endl;
//         cin >> methodOption;

//         switch (methodOption)
//         {
//         case 1:
//             // Set Finals grade for student
//             break;
//         case 2:
//             // Conduct Finals Exam
//             break;
//         }
//         break;

//     case 3: // Secretary
//         cout << "\tYou are logged in as the Secretary" << endl;

//         ////////// Student Management //////////
//         cout << "1. Add new student" << endl;
//         cout << "2. Remove Student" << endl;
//         cout << "3. Update Student Information" << endl;
//         cout << "4. List Students" << endl;
//         cout << "5. Enroll Student in Course" << endl;
//         ////////// Professor Management //////////
//         cout << "6. Add Professor" << endl;
//         cout << "7. Remove Professor" << endl;
//         cout << "8. Update Professor Information" << endl;
//         cout << "9. List Professors" << endl;
//         cout << "10. Assign Professor to Course" << endl;
//         ////////// Course Management //////////
//         cout << "11. Add Course" << endl;
//         cout << "12. Remove Course" << endl;
//         cout << "13. Update Course Details" << endl;
//         cout << "14. List Courses" << endl;
//         cout << "15. Display Every Functionality" << endl;
//         cout << "Give option 1 - 15 : " << endl;
//         cin >> methodOption;

//         switch (methodOption)
//         {
//         case 1: // Add Student
//             cout << "Enter Name: " << endl;
//             cin >> name;
//             cout << "Enter AFM: " << endl;
//             cin >> afm;
//             cout << "Enter Age: " << endl;
//             cin >> age;
//             secretary.addStudent(name, afm, age);
//             break;
//         case 2: // Remove Student
//             cout << "Enter AFM to remove: " << endl;
//             cin >> afm;
//             secretary.removeStudent(afm);
//             break;
//         case 3:
//             // Edit Student details
//             break;
//         case 4: // Display Students
//             secretary.loadStudents();
//             break;
//         case 5:
//             //
//             break;
//         case 6:
//             //
//             break;
//         case 7:
//             //
//             break;
//         case 8:
//             //
//             break;
//         case 9:
//             //
//             break;
//         case 10:
//             //
//             break;
//         case 11:
//             //
//             break;
//         case 12:
//             //
//             break;
//         case 13:
//             //
//             break;
//         case 14:
//             //
//             break;
//         case 15:
//             //
//             break;
//         }
//         break;
//     }

//     // Load students and professors from CSV files

//     // secretary.loadProfessors();
//     // secretary.loadCourses();

//     // Displaying loaded students
//     cout << "Loaded Students: " << endl;
//     for (const auto *student : secretary.getStudents())
//     {
//         cout << "AFM: " << student->getAFM() << endl;
//     }

//     return 0;
// }

int main()
{
    Secretary secretary;
    secretary.loadStudents(); // Make sure students are loaded

    string afmToEdit = "001"; // Specify the AFM of the student you want to edit
    secretary.editStudent(afmToEdit);

    return 0;
}
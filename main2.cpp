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

void removeEmptyLines(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read the file line by line
    while (getline(file, line))
    {
        // Use the trim function to remove any whitespace characters from the beginning and end of the line
        string trimmedLine = trim(line);

        // Check if the line is empty after trimming
        if (!trimmedLine.empty())
        {
            lines.push_back(trimmedLine); // Add non-empty lines to the vector
        }
    }

    file.close(); // Close the file after reading

    // Open the same file for writing to overwrite it
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write each non-empty line back to the file
    for (const auto &validLine : lines)
    {
        outFile << validLine << endl;
    }

    outFile.close(); // Close the file after writing
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
    bool mandatory;                         // Course Required
    vector<Student *> enrolledStudents;     // Vector of Students attending Course
    vector<Professor *> assignedProfessors; // Vectir of Professors assigned in Course

    // Constructor for Course
    Course(int newCourseId, const string &newCourseName, int newSemester, int newPoints, int newMandatory)
    {
        courseId = newCourseId;
        courseName = newCourseName;
        semester = newSemester;
        points = newPoints;
        mandatory = newMandatory;
    }
    // Destructor
    ~Course() {}

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
            // enrolledCourses.push_back(course);

            // Open the studentsToCourses.csv file in append mode
            ofstream file("studentsToCourses.csv", ios::app);
            if (!file.is_open())
            {
                cerr << "Error opening file for writing" << endl;
                return;
            }

            // Write the new student's information to the file
            file << getAFM() << "," << course->getCourseId();

            file.close();
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
    Professor(string name, string afm, int age)
    {
        setName(name);
        setAfm(afm);
        setAge(age);
    }
    // Destructor
    ~Professor() {}

    void pushToVector(Course *course)
    {
        taughtCourses.push_back(course);
    }
    void assignToCourse(Course *course) // Assigns Self to Course
    {
        taughtCourses.push_back(course);

        // Open the professorsToCourses.csv file in append mode
        ofstream file("professorsToCourses.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        // Write the new student's information to the file
        file << getAFM() << "," << course->getCourseId();

        file.close();
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

    void loadTaughtCourses(Professor *professor)
    {
        ifstream file("professorsToCourses.csv");
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
            string professorAfm, courseId;

            getline(ss, professorAfm, ',');
            getline(ss, courseId, ',');

            professorAfm = trim(professorAfm);
            courseId = trim(courseId);

            Course *courseToFind = nullptr;

            for (auto &course : allCourses)
            {
                if (to_string(course->getCourseId()) == courseId)
                {
                    courseToFind = course;
                    break;
                }
            }

            if (!courseToFind)
            {
                cout << "Course with Id " << courseId << " not found." << endl;
                return;
            }

            if (professorAfm == professor->getAFM())
            {
                professor->pushToVector(courseToFind);
            }
        }
    }

    void loadStudents()
    {
        ifstream file("students.csv");
        string line;
        removeEmptyLines("students.csv");

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
            // cout << name << "," << afm << "," << age << "," << currentSemester << "," << accumulatedPoints << "," << finalGrade << "," << graduated << endl;
        }

        file.close();
    }

    void loadProfessors()
    {
        removeEmptyLines("professors.csv");
        ifstream file("professors.csv");
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
            string name, afm, age;

            getline(ss, name, ',');
            getline(ss, afm, ',');
            getline(ss, age, ',');

            name = trim(name);
            afm = trim(afm);
            age = trim(age);

            Professor *newProfessor = new Professor(name, afm, stoi(age));
            allProfessors.push_back(newProfessor);
            // cout << name << "," << afm << "," << age << endl;
        }

        file.close();
    }

    void loadCourses()
    {
        removeEmptyLines("courses.csv");
        ifstream file("courses.csv");
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
            string courseId, courseName, semester, points, mandatory;

            getline(ss, courseId, ',');
            getline(ss, courseName, ',');
            getline(ss, semester, ',');
            getline(ss, points, ',');
            getline(ss, mandatory, ',');

            courseId = trim(courseId);
            courseName = trim(courseName);
            semester = trim(semester);
            points = trim(points);
            mandatory = trim(mandatory);

            Course *newCourse = new Course(stoi(courseId), courseName, stoi(semester), stoi(points), stoi(mandatory));
            allCourses.push_back(newCourse);
            // cout << courseId << "," << courseName << "," << semester << "," << points << "," << mandatory << endl;
        }

        file.close();
    }

    void enrollStudent(const string &afm, int courseId) // Assigns student to Course
    {
        Student *studentToFind = nullptr;
        for (auto &student : allStudents)
        {
            if (student->getAFM() == afm)
            {
                studentToFind = student;
                break;
            }
        }

        Course *courseToFind = nullptr;
        for (auto &course : allCourses)
        {
            if (course->getCourseId() == courseId)
            {
                courseToFind = course;
                break;
            }
        }

        if (studentToFind && courseToFind) // Check if the pointers are not null
            studentToFind->enrollInCourse(courseToFind);
    }

    void assignProfessor(const string &afm, int courseId) // Assigns Professor to Course
    {

        Professor *professorToFind = nullptr;
        for (auto &professor : allProfessors)
        {
            if (professor->getAFM() == afm)
            {
                professorToFind = professor;
                break;
            }
        }

        Course *courseToFind = nullptr;
        for (auto &course : allCourses)
        {
            if (course->getCourseId() == courseId)
            {
                courseToFind = course;
                break;
            }
        }

        if (professorToFind && courseToFind) // Check if the pointers are not null
            professorToFind->assignToCourse(courseToFind);
    }

    void absolveProfessor(const string &afm, const string &courseId)
    {
        ifstream file("professorsToCourses.csv");
        string line;

        if (!file.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }

        // Create a temporary file
        ofstream tempFile("temp.csv");

        int index = 1;
        while (getline(file, line))
        {
            stringstream ss(line);
            string professorAfm, fileCourseId;

            getline(ss, professorAfm, ',');
            getline(ss, fileCourseId, ',');

            professorAfm = trim(professorAfm);
            fileCourseId = trim(fileCourseId);
            if (!(professorAfm == afm && courseId == fileCourseId))
            {
                tempFile << line << endl;
            }
            index++;
        }

        // Close both the files
        file.close();
        tempFile.close();

        // Remove the original file
        remove("professorsToCourses.csv");
        removeEmptyLines("temp.csv");
        // Rename the temporary file to the original file name
        rename("temp.csv", "professorsToCourses.csv");
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
        file << name << "," << afm << "," << age << "," << 1 << "," << 0 << "," << 0 << "," << 0;

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

        cout << "What would you like to change on Student with afm: " << afm << endl;
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

        file << "name,afm,age,currentSemester,accumulatedPoints,finalGrade,graduated" << endl;

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

    void addProfessor(const string &name, const string &afm, int age)
    {
        // Open the professors.csv file in append mode
        ofstream file("professors.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        // Write the new professor's information to the file
        file << name << "," << afm << "," << age;

        // Create a new Student object
        Professor *newProfessor = new Professor(name, afm, age);

        // Add the new Student to the allStudents vector
        allProfessors.push_back(newProfessor);

        // Close the file
        file.close();
    }

    void removeProfessor(const string &afm)
    {
        bool removed = false;
        for (auto it = allProfessors.begin(); it != allProfessors.end();)
        {
            if ((*it)->getAFM() == afm)
            {
                delete *it;                   // Free the memory of the student object
                it = allProfessors.erase(it); // Remove the Professor from the vector and update the iterator
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
            // Rewrite the professors.csv file without the removed student
            ofstream file("professors.csv");
            if (!file.is_open())
            {
                cerr << "Error opening file for writing" << endl;
                return;
            }

            // Write the header
            file << "name,afm,age" << endl;

            // Write the remaining students to the file
            for (const auto *professor : allProfessors)
            {
                file << professor->getName() << ","
                     << professor->getAFM() << ","
                     << professor->getAge() << endl;
            }

            file.close();

            // HAS TO REMOVE FROM ProfessorsToCourses file too !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        else
        {
            cout << "The AFM is not in the vector." << endl;
        }
    }

    void editProfessor(const string &afm)
    {
        Professor *professorToEdit = nullptr;

        // Find the Professor in the allProfessors vector
        for (auto &professor : allProfessors)
        {
            if (professor->getAFM() == afm)
            {
                professorToEdit = professor;
                break;
            }
        }

        if (!professorToEdit)
        {
            cout << "Professor with AFM " << afm << " not found." << endl;
            return;
        }

        string newName;
        int newAge, change;

        cout << "What would you like to change on Professor with afm: " << afm << endl;
        cout << "1. Name" << endl
             << "2. Age" << endl
             << "Enter 1-2: " << endl;
        cin >> change;

        switch (change)
        {
        case 1:
            cout << "Enter new Name: ";
            cin >> newName;
            professorToEdit->setName(newName);
            break;
        case 2:
            cout << "Enter new Age: ";
            cin >> newAge;
            professorToEdit->setAge(newAge);
            break;
        }

        // Rewrite the professors.csv file with updated details
        ofstream file("professors.csv");
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        file << "name,afm,age" << endl;

        for (const auto &professor : allProfessors)
        {
            file << professor->getName() << ","
                 << professor->getAFM() << ","
                 << professor->getAge() << endl;
        }

        file.close();
        cout << "Professor details updated successfully." << endl;
    }

    void addCourse(int courseId, const string &courseName, int semester, int points, bool mandatory)
    {
        // Open the students.csv file in append mode
        ofstream file("courses.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return;
        }

        // Write the new student's information to the file
        file << courseId << "," << courseName << "," << semester << "," << points << "," << mandatory;

        // Create a new Student object
        Course *newCourse = new Course(courseId, courseName, semester, points, mandatory);

        // Add the new Student to the allStudents vector
        allCourses.push_back(newCourse);

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
    removeEmptyLines("professorsToCourses.csv");
    removeEmptyLines("studentsToCourses.csv");

    // Create an instance of Secretary
    Secretary secretary;

    secretary.loadStudents();
    secretary.loadProfessors();
    secretary.loadCourses();

    int loginOption, methodOption, age, courseId, semester, points;
    string name, afm, courseName;
    bool mandatory;

    cout << "\n\t Welcome to my University Department Monitor System" << endl;

    cout << "1. Login As Student" << endl;
    cout << "2. Login As Professor" << endl;
    cout << "3. Login As Secretary" << endl;
    cout << "Give option 1 - 3 : ";
    cin >> loginOption;

    switch (loginOption)
    {
    case 1: // Student
        cout << "\tYou are logged in as a Student" << endl;
        cout << "Give your AFM: ";
        cin >> afm;

        cout << "1. Enroll self to course" << endl;
        cout << "2. Calculate Accumulated Points" << endl;
        cout << "3. Check graduation eligibility" << endl;
        cout << "Give option 1 - 3 : " << endl;
        cin >> methodOption;

        switch (methodOption)
        {
        case 1:
            // Enroll student to course
            cout << "Give the Course Id: " << endl;
            cin >> courseId;
            secretary.enrollStudent(afm, courseId);
            break;
        case 2:
            // Calculate Accumulated Points
            break;
        case 3:
            // Check graduation eligibility
            break;
        }
        break;

    case 2: // Professor
        cout << "\tYou are logged in as a Professor" << endl;
        cout << "Give your AFM: ";
        cin >> afm;

        cout << "1. Set Finals grade for student" << endl;
        cout << "2. Conduct Finals Exam" << endl; // Make it look cool! ex. Loading Final scores... Students are given random score.
        cout << "Give option 1 - 2 : " << endl;
        cin >> methodOption;

        switch (methodOption)
        {
        case 1:
            // Set Finals grade for student
            break;
        case 2:
            cout << "Conducting Finals Exam" << endl;
            break;
        }
        break;

    case 3: // Secretary
        cout << "\tYou are logged in as the Secretary" << endl;

        ////////// Student Management //////////
        cout << "1. Add new student" << endl;
        cout << "2. Remove Student" << endl;
        cout << "3. Update Student Information" << endl;
        cout << "4. List Students" << endl;
        ////////// Professor Management //////////
        cout << "5. Add Professor" << endl;
        cout << "6. Remove Professor" << endl;
        cout << "7. Update Professor Information" << endl;
        cout << "8. List Professors" << endl;
        cout << "9. Assign Professor to Course" << endl;
        cout << "10. Unassign Professor from Course" << endl;
        ////////// Course Management //////////
        cout << "11. Add Course" << endl;
        cout << "12. Remove Course" << endl;
        cout << "13. Update Course Details" << endl; // Also able to move course's semseter
        cout << "14. List Courses" << endl;
        cout << "15. Display Every Functionality" << endl;
        cout << "Give option 1 - 15 : " << endl;
        cin >> methodOption;

        switch (methodOption)
        {
        case 1: // Add new Student
            cout << "Enter Name: " << endl;
            cin >> name;
            cout << "Enter AFM: " << endl;
            cin >> afm;
            cout << "Enter Age: " << endl;
            cin >> age;
            secretary.addStudent(name, afm, age);
            break;
        case 2: // Remove Student
            cout << "Enter AFM to remove: " << endl;
            cin >> afm;
            secretary.removeStudent(afm);
            break;
        case 3: // Edit Student details
            cout << "Enter AFM to Edit: " << endl;
            cin >> afm;
            secretary.editStudent(afm);
            break;
        case 4: // Display Students
            secretary.loadStudents();
            break;
        case 5: // Add new Professor
            cout << "Enter Name: " << endl;
            cin >> name;
            cout << "Enter AFM: " << endl;
            cin >> afm;
            cout << "Enter Age: " << endl;
            cin >> age;
            secretary.addProfessor(name, afm, age);
            break;
        case 6: // Remove Professor
            cout << "Enter AFM to remove: " << endl;
            cin >> afm;
            secretary.removeProfessor(afm);
            break;
        case 7: // Edit Professor Details
            cout << "Enter AFM to Edit: " << endl;
            cin >> afm;
            secretary.editProfessor(afm);
            break;
        case 8: // Display Professors
            secretary.loadProfessors();
            break;
        case 9:
            // Assign Professor to Course
            cout << "Enter Professor AFM: " << endl;
            cin >> afm;
            cout << "Enter Course Id: " << endl;
            cin >> courseId;
            secretary.assignProfessor(afm, courseId);
            break;
        case 10:
            cout << "Enter Professor AFM: " << endl;
            cin >> afm;
            cout << "Enter Course Id: " << endl;
            cin >> courseId;
            secretary.absolveProfessor(afm, to_string(courseId));
            break;
        case 11: // Add new Course
            cout << "Enter Course Id: " << endl;
            cin >> courseId;
            cout << "Enter Course Name: " << endl;
            cin >> courseName;
            cout << "Enter Semester: " << endl;
            cin >> semester;
            cout << "Enter Points: " << endl;
            cin >> points;
            cout << "Enter If Mandatory (0-1): " << endl;
            cin >> mandatory;
            secretary.addCourse(courseId, courseName, semester, points, mandatory);
            break;
        case 12:
            //
            break;
        case 13:
            //
            break;
        case 14: // Display Courses
            secretary.loadCourses();

            break;
        case 15:
            //
            break;
        }
        break;
    }

    // Load students and professors from CSV files

    // secretary.loadProfessors();
    // secretary.loadCourses();

    // Displaying loaded students
    // cout << "Loaded Students: " << endl;
    // for (const auto *student : secretary.getStudents())
    // {
    //     cout << "AFM: " << student->getAFM() << endl;
    // }

    return 0;
}

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Course
{
public:
    string courseName;
    int semester;
    int points;
    bool isMandatory;

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

int main()
{
    // Create two semesters
    Semester semester1(1), semester2(2);

    // Create courses
    Course course1("Mathematics", 1, 5, true);
    Course course2("Physics", 1, 4, false);
    Course course3("Literature", 2, 3, true);
    Course course4("Chemistry", 2, 4, false);
    Course course5("Object Orianted Programming", 1, 4, true);
    Course course6("Object Orianted Programming Two", 2, 4, true); // Add courses to semesters

    semester1.addCourse(&course1);
    semester1.addCourse(&course2);
    semester1.addCourse(&course5);
    semester2.addCourse(&course3);
    semester2.addCourse(&course4);
    semester2.addCourse(&course6);
    // Writing to courses.csv file
    ofstream coursesFile("courses.csv");
    coursesFile << "Course Name,Semester,Points,Mandatory\n";
    coursesFile << course1.courseName << "," << course1.semester << "," << course1.points << "," << course1.isMandatory << "\n";
    coursesFile << course2.courseName << "," << course2.semester << "," << course2.points << "," << course2.isMandatory << "\n";
    coursesFile << course3.courseName << "," << course3.semester << "," << course3.points << "," << course3.isMandatory << "\n";
    coursesFile << course4.courseName << "," << course4.semester << "," << course4.points << "," << course4.isMandatory << "\n";
    coursesFile << course5.courseName << "," << course5.semester << "," << course5.points << "," << course5.isMandatory << "\n";
    coursesFile << course6.courseName << "," << course6.semester << "," << course6.points << "," << course6.isMandatory << "\n";
    coursesFile.close();

    // Display courses in each semester
    semester1.displayCourses();
    semester2.displayCourses();

    return 0;
}

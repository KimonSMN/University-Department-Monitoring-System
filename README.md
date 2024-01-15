# University Department Management System

## Overview

This system is designed to manage a university department's operations, including handling students, professors, and courses. It allows for various operations such as enrolling students in courses, grading, managing professors and courses, and checking graduation eligibility.

## Features

### Student Management

- Enroll in courses.
- Calculate accumulated points.
- Check graduation eligibility.
- View grades for taken courses.

### Professor Management

- Assign grades to students.
- View statistics for courses taught.

### Secretary Management

- Add, remove, and update student and professor records.
- Assign professors to courses.
- Add, remove, and update course details.
- Display eligible students for graduation.

## Installation

To run this program, ensure you have a C++ compiler installed. Clone or download this repository to your local machine.

## Usage

1. Compile the code using a C++ compiler.
2. Run the compiled program: ./university_management
3. Follow the on-screen prompts to interact with the system.

## File Structure

- `university_management.cpp`: Contains the main function and orchestrates the program flow.
- `output/`
  - `courses.csv`
  - `professors.csv`
  - `students.csv`
  - `professorsToCourses.csv`
  - `studentsToCourses.csv`
  - `studentsPassedCourses.csv`

## Contributing

Contributions to this project are welcome. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature.
3. Commit your changes.
4. Push to the branch.
5. Create a new Pull Request.

## License

MIT License

Copyright (c) 2024 Kimon Smirlianos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

#include <iostream>
#include <vector>
using namespace std;


double getGradePoints(char grade) {
    switch (toupper(grade)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return -1; 
    }
}

int main() {
    int numCourses;
    vector<char> grades;
    vector<int> creditHours;
    double totalGradePoints = 0.0;
    int totalCredits = 0;

   
    cout << "Enter the number of courses taken: ";
    cin >> numCourses;

    
    for (int i = 0; i < numCourses; i++) {
        char grade;
        int credits;
        cout << "Enter grade for course " << i + 1 << " (A/B/C/D/F): ";
        cin >> grade;
        double gradePoint = getGradePoints(grade);
        if (gradePoint < 0) {
            cout << "Invalid grade. Please use A, B, C, D, or F." << endl;
            i--;
            continue;
        }
        cout << "Enter credit hours for course " << i + 1 << ": ";
        cin >> credits;
        if (credits <= 0) {
            cout << "Invalid credit hours. Please enter a positive value." << endl;
            i--;
            continue;
        }
        grades.push_back(grade);
        creditHours.push_back(credits);
        totalGradePoints += gradePoint * credits;
        totalCredits += credits;
    }

   
    double gpa = totalGradePoints / totalCredits;
    double cgpa = gpa;

   
    cout << "\nIndividual Course Grades:" << endl;
    for (int i = 0; i < numCourses; i++) {
        cout << "Course " << i + 1 << ": Grade = " << grades[i] << ", Credit Hours = " << creditHours[i] << endl;
    }

    
    cout << "\nFinal CGPA: " << cgpa << endl;

    return 0;
}

/*2.	OUTPUT  OF  CGPA  CALCULATOR

Enter the number of courses taken: 4
Enter grade for course 1 (A/B/C/D/F): A
Enter credit hours for course 1: 4
Enter grade for course 2 (A/B/C/D/F): B
Enter credit hours for course 2: 3
Enter grade for course 3 (A/B/C/D/F): F
Enter credit hours for course 3: 1
Enter grade for course 4 (A/B/C/D/F): C
Enter credit hours for course 4: 3
Enter grade for course 5 (A/B/C/D/F): A
Individual Course Grades:
Course 1: Grade = A, Credit Hours = 4
Course 2: Grade = B, Credit Hours = 3
Course 3: Grade = F, Credit Hours = 1
Course 4: Grade = C, Credit Hours = 3
Course 5: Grade = A, Credit Hours = 3

Final CGPA: 6.07143*/

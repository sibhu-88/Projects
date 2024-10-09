#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILE_NAME_STUDENTS "students.csv"
#define FILE_NAME_TEACHERS "teachers.csv"
#define FILE_NAME_COURSES "courses.csv"
#define FILE_NAME_ATTENDANCE "attendance.csv"

// Define structures
typedef struct {
    int student_id;
    char name[MAX_NAME_LENGTH];
    char course[MAX_NAME_LENGTH];
    float marks;
    float attendance_percentage;
} Student;

typedef struct {
    int teacher_id;
    char name[MAX_NAME_LENGTH];
    char subject[MAX_NAME_LENGTH];
} Teacher;

typedef struct {
    int course_id;
    char course_name[MAX_NAME_LENGTH];
    int credits;
} Course;

typedef struct {
    int student_id;
    int course_id;
    int semester;
    int attendance; // 1 for present, 0 for absent
} Attendance;

// Function prototypes
void add_student(Student student);
void add_teacher(Teacher teacher);
void add_course(Course course);
void record_attendance(Attendance attendance);
void view_students();
void view_teachers();
void view_courses();
void view_attendance();

int main() {
    int choice;
    while (1) {
        printf("\nCollege Management System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Add Teacher\n");
        printf("3. Add Course\n");
        printf("4. Record Attendance\n");
        printf("5. View Students\n");
        printf("6. View Teachers\n");
        printf("7. View Courses\n");
        printf("8. View Attendance\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            Student student;
            printf("Enter student ID: ");
            scanf("%d", &student.student_id);
            printf("Enter student name: ");
            scanf(" %[^\n]", student.name); // Read string with spaces
            printf("Enter course: ");
            scanf(" %[^\n]", student.course); // Read string with spaces
            printf("Enter marks: ");
            scanf("%f", &student.marks);
            printf("Enter attendance percentage: ");
            scanf("%f", &student.attendance_percentage);
            add_student(student);
        } else if (choice == 2) {
            Teacher teacher;
            printf("Enter teacher ID: ");
            scanf("%d", &teacher.teacher_id);
            printf("Enter teacher name: ");
            scanf(" %[^\n]", teacher.name); // Read string with spaces
            printf("Enter subject taught: ");
            scanf(" %[^\n]", teacher.subject); // Read string with spaces
            add_teacher(teacher);
        } else if (choice == 3) {
            Course course;
            printf("Enter course ID: ");
            scanf("%d", &course.course_id);
            printf("Enter course name: ");
            scanf(" %[^\n]", course.course_name); // Read string with spaces
            printf("Enter course credits: ");
            scanf("%d", &course.credits);
            add_course(course);
        } else if (choice == 4) {
            Attendance attendance;
            printf("Enter student ID: ");
            scanf("%d", &attendance.student_id);
            printf("Enter course ID: ");
            scanf("%d", &attendance.course_id);
            printf("Enter semester: ");
            scanf("%d", &attendance.semester);
            printf("Enter attendance (1 for present, 0 for absent): ");
            scanf("%d", &attendance.attendance);
            record_attendance(attendance);
        } else if (choice == 5) {
            view_students();
        } else if (choice == 6) {
            view_teachers();
        } else if (choice == 7) {
            view_courses();
        } else if (choice == 8) {
            view_attendance();
        } else if (choice == 9) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function implementations
void add_student(Student student) {
    FILE *file = fopen(FILE_NAME_STUDENTS, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%.2f,%.2f\n", student.student_id, student.name, student.course, student.marks, student.attendance_percentage);
    fclose(file);
    printf("Student added successfully!\n");
}

void add_teacher(Teacher teacher) {
    FILE *file = fopen(FILE_NAME_TEACHERS, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }
    fprintf(file, "%d,%s,%s\n", teacher.teacher_id, teacher.name, teacher.subject);
    fclose(file);
    printf("Teacher added successfully!\n");
}

void add_course(Course course) {
    FILE *file = fopen(FILE_NAME_COURSES, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }
    fprintf(file, "%d,%s,%d\n", course.course_id, course.course_name, course.credits);
    fclose(file);
    printf("Course added successfully!\n");
}

void record_attendance(Attendance attendance) {
    FILE *file = fopen(FILE_NAME_ATTENDANCE, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }
    fprintf(file, "%d,%d,%d,%d\n", attendance.student_id, attendance.course_id, attendance.semester, attendance.attendance);
    fclose(file);
    printf("Attendance recorded successfully!\n");
}

void view_students() {
    FILE *file = fopen(FILE_NAME_STUDENTS, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    Student student;
    printf("All Students:\n");
    printf("ID, Name, Course, Marks, Attendance Percentage\n");
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%f\n", &student.student_id, student.name, student.course, &student.marks, &student.attendance_percentage) != EOF) {
        printf("%d, %s, %s, %.2f, %.2f%%\n", student.student_id, student.name, student.course, student.marks, student.attendance_percentage);
    }
    fclose(file);
}

void view_teachers() {
    FILE *file = fopen(FILE_NAME_TEACHERS, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    Teacher teacher;
    printf("All Teachers:\n");
    printf("ID, Name, Subject\n");
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &teacher.teacher_id, teacher.name, teacher.subject) != EOF) {
        printf("%d, %s, %s\n", teacher.teacher_id, teacher.name, teacher.subject);
    }
    fclose(file);
}

void view_courses() {
    FILE *file = fopen(FILE_NAME_COURSES, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    Course course;
    printf("All Courses:\n");
    printf("ID, Name, Credits\n");
    while (fscanf(file, "%d,%49[^,],%d\n", &course.course_id, course.course_name, &course.credits) != EOF) {
        printf("%d, %s, %d\n", course.course_id, course.course_name, course.credits);
    }
    fclose(file);
}

void view_attendance() {
    FILE *file = fopen(FILE_NAME_ATTENDANCE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    Attendance attendance;
    printf("Attendance Records:\n");
    printf("Student ID, Course ID, Semester, Attendance\n");
    while (fscanf(file, "%d,%d,%d,%d\n", &attendance.student_id, &attendance.course_id, &attendance.semester, &attendance.attendance) != EOF) {
        printf("%d, %d, %d, %d\n", attendance.student_id, attendance.course_id, attendance.semester, attendance.attendance);
    }
    fclose(file);
}


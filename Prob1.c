#include <stdio.h>

typedef struct Student {
    char Name[20];
    char Surename[20];
    int Number_id;
    float Mark;
} Student;

void create_student(Student *s, int index) {
    s[index].Number_id = index + 1;
    printf("Enter name:");
    scanf("%s", s[index].Name);
    printf("Enter surename:");
    scanf("%s", s[index].Surename);
    printf("Enter Media:");
    scanf("%f", &s[index].Mark);
    printf("____________\n");
}

void create_table(Student *students, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        create_student(students, i);
    }
}

void print_element(Student s) {
    printf("\nNumber:%d", s.Number_id);
    printf("\nName:%s", s.Name);
    printf("\nSurename:%s", s.Surename);
    printf("\nMark:%.2f", s.Mark);
    printf("\n____________");
}

void print_table(Student *students, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        print_element(students[i]);
    }
}

int main() {
    int number_of_students;
    printf("Please enter the number of students:");
    scanf("%d", &number_of_students);

    Student s[number_of_students];
    create_table(s, number_of_students);
    print_table(s, number_of_students);

    for (int j = 0; j < number_of_students; j++) {
        if (s[j].Mark >= 10) {
            printf("\n%s %s is a straight A student: %.2f", s[j].Name, s[j].Surename, s[j].Mark);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char Name[20];
    char Surename[20];
    int Number_id;
    float Mark;
} Student;

Student *table[100];
Student *sorted_table[100];

void create_student(int i);
void create_table(int *number_of_students);
void print_element(Student *student);
void print_table(int *number_of_students);
void print_sorted_table(int *number_of_students);
void free_memory(int *number_of_students);
int find_student(char *temp_string, int *number_of_students);
int menu(char *temp_string, int *number_of_students);
void sort_students_by_mark(int *number_of_students);
int push_front(int *number_of_students);

int main() {
    int number_of_students = 0;
    char temp_string[20];
    create_table(&number_of_students);
    sort_students_by_mark(&number_of_students);
    menu(temp_string, &number_of_students);
    free_memory(&number_of_students);
    return 0;
}

void create_student(int i) {
    table[i] = (Student *)malloc(sizeof(Student));
    table[i]->Number_id = i + 1;
    printf("\nEnter name:");
    scanf("%s", table[i]->Name);
    printf("\nEnter surename:");
    scanf("%s", table[i]->Surename);
    printf("\nEnter mark:");
    scanf("%f", &table[i]->Mark);
    printf("\n____________");
}

void create_table(int *number_of_students) {
    printf("Enter number of students (1-100):");
    if (scanf("%d", number_of_students) != 1 || *number_of_students <= 0 || *number_of_students > 100) {
        printf("Error: Please enter a valid positive number of students (1-100).\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *number_of_students; i++) {
        create_student(i);
    }
}

void print_element(Student *student) {
    printf("\nNumber:%d", student->Number_id);
    printf("\nName:%s", student->Name);
    printf("\nSurename:%s", student->Surename);
    printf("\nMark:%.2f", student->Mark);
    printf("\n____________");
}

void print_table(int *number_of_students) {
    for (int i = 0; i < *number_of_students; i++) {
        print_element(table[i]);
    }
}

void print_sorted_table(int *number_of_students) {
    for (int i = 0; i < *number_of_students; i++) {
        print_element(sorted_table[i]);
    }
}

void free_memory(int *number_of_students) {
    for (int i = 0; i < *number_of_students; i++) {
        free(table[i]);
    }
}

int find_student(char *temp_string, int *number_of_students) {
    for (int i = 0; i < *number_of_students; i++) {
        if (strcmp(temp_string, table[i]->Name) == 0) {
            return i;
        }
    }
    return -1;
}

void sort_students_by_mark(int *number_of_students) {
    for (int i = 0; i < *number_of_students; i++) {
        sorted_table[i] = table[i];
    }
    for (int i = 0; i < *number_of_students - 1; i++) {
        for (int j = 0; j < *number_of_students - i - 1; j++) {
            if (sorted_table[j]->Mark < sorted_table[j + 1]->Mark) {
                Student *temp = sorted_table[j];
                sorted_table[j] = sorted_table[j + 1];
                sorted_table[j + 1] = temp;
            }
        }
    }
}
int push(int *number_of_students,int position) {
    if (position >= number_of_students) {
        printf("Error: Index out of bounds.\n");
        return *number_of_students;
    }

    (*number_of_students)++;
    create_student(*number_of_students );
    int max_table = *number_of_students ;

    for (int i = *number_of_students - 1; i > position; i--) {
        table[i] = table[i - 1];
        table[i]->Number_id += 1;
    }

    table[position] = table[max_table];
    table[position]->Number_id =position+1;
    return *number_of_students;
}
int pop(int *number_of_students, int position) {
    if (position >= *number_of_students) {
        printf("Error: Index out of bounds.\n");
        return *number_of_students;
    }

    free(table[position]);

    for (int i = position; i < *number_of_students - 1; i++) {
        table[i] = table[i + 1];
        table[i]->Number_id -= 1;
    }

    return --(*number_of_students);
}

int menu(char *temp_string, int *number_of_students) {
    int choice;
    printf("\nEnter the number corresponding with your choice:\n1. Print original table;\n2. Search student;\n3. Print sorted table;\n4. Add a new student at the front;\n5. Add a new student a specified position;\n6. Add a new student at the end of list;\n7. Delete a student on a specified position;\n0. Exit program;\n");
    scanf("%d", &choice);
    switch (choice) {
        case 0:
            free_memory(number_of_students);
            printf("Stopped program");
            break;
        case 1:
            print_table(number_of_students);
            break;
        case 2:
            printf("Please introduce the name of the student:");
            scanf("%s", temp_string);
            int index = find_student(temp_string, number_of_students);
            if (index != -1) {
                printf("Student found at index: %d\n", index + 1);
                print_element(table[index]);
            } else {
                printf("Student not found.\n");
            }
            break;
        case 3:
            printf("Print sorted table:\n");
            sort_students_by_mark(number_of_students);
            print_sorted_table(number_of_students);
            break;
        case 4:
            *number_of_students = push(number_of_students,0);
            break;
        case 5:
            printf("\nPlease introduce the position:");
            int add_position = 0;
            scanf("%d",&add_position);
            *number_of_students = push(number_of_students,add_position-1);
            break;
        case 6:
            *number_of_students = push(number_of_students,*number_of_students-1);
            break;
        case 7:
            printf("\nPlease introduce the position:");
            int delete_position = 0;
            scanf("%d",&delete_position);
            *number_of_students = pop(number_of_students,delete_position - 1);
            break;
        default:
            printf("\nInvalid input, try again!");
            break;
    }

    if (choice != 0) {
        menu(temp_string, number_of_students);
    }
}

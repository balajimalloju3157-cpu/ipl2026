#include<stdio.h>
#include<stdlib.h>

#define MAX 5

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void writeRecords(const char *filename, struct Student s[], int n);
void createSeekPositions(const char *filename, long pos[], int *count);
void displayRecord(const char *filename, long position);

int main()
{
    struct Student s[MAX] = {
        {1, "Amit", 85.5},
        {2, "Rahul", 90.0},
        {3, "Sneha", 78.5},
        {4, "Priya", 88.0},
        {5, "Karan", 92.5}
    };

    long positions[MAX];
    int count;

    // Store records in file
    writeRecords("student.txt", s, MAX);

    // Create array of seek positions
    createSeekPositions("student.txt", positions, &count);

    printf("Seek Positions:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Record %d starts at position %ld\n",
               i + 1,
               positions[i]);
    }

    // Display record using position
    int choice;

    printf("\nEnter record number to display (1-%d): ", count);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count)
    {
        displayRecord("student.txt", positions[choice - 1]);
    }
    else
    {
        printf("Invalid record number.\n");
    }

    return 0;
}

void writeRecords(const char *filename, struct Student s[], int n)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %.2f\n",
                s[i].roll,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);
}

void createSeekPositions(const char *filename, long pos[], int *count)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    int i = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF && i < MAX)
    {
        // Move back one character
        fseek(fp, -1, SEEK_CUR);

        // Store beginning position of record
        pos[i] = ftell(fp);

        // Move till end of line
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);

        i++;
    }

    *count = i;

    fclose(fp);
}

void displayRecord(const char *filename, long position)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    struct Student s;

    // Move pointer to desired record
    fseek(fp, position, SEEK_SET);

    fscanf(fp,
           "%d %s %f",
           &s.roll,
           s.name,
           &s.marks);

    printf("\nRecord Found:\n");
    printf("Roll No : %d\n", s.roll);
    printf("Name    : %s\n", s.name);
    printf("Marks   : %.2f\n", s.marks);

    fclose(fp);
}
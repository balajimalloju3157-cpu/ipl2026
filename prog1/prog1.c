#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int id;
    char name[30];
    float marks;
};

/* Function Prototypes */
void storeRecords();
void displayMthRecord(int m);
void deleteRecord(int delId);
int main()
{
    int m, delId;

    storeRecords();

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    displayMthRecord(m);

    printf("\nEnter ID to delete: ");
    scanf("%d", &delId);

    deleteRecord(delId);

    return 0;
}

void storeRecords()
{
    FILE *fp;
    int n, i;
    struct Student s;

    fp = fopen("records.dat", "wb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    printf("Enter number of records: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nRecord %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
}

void displayMthRecord(int m)
{
    FILE *fp;
    struct Student s;

    fp = fopen("records.dat", "rb");

    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    fread(&s, sizeof(struct Student), 1, fp);

    printf("\nMth Record Details\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Marks: %.2f\n", s.marks);

    fclose(fp);
}

void deleteRecord(int delId)
{
    FILE *fp, *temp;
    struct Student s;

    fp = fopen("records.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id != delId)
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("records.dat");
    rename("temp.dat", "records.dat");

    printf("Record deleted successfully\n");
}


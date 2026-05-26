#include <stdio.h>

/* Function to print bits of an integer */
void printBits(int n)
{
    int i;

    for(i = 31; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);

        if(i % 8 == 0)
        {
            printf(" ");
        }
    }

    printf("\n");
}

/* Function to count number of 1 bits */
int countOneBits(int n)
{
    int count = 0;

    while(n != 0)
    {
        if(n & 1)
        {
            count++;
        }

        n = n >> 1;
    }

    return count;
}

/* Function to check endian type */
void checkEndian()
{
    int x = 1;

    char *p = (char *)&x;

    if(*p == 1)
    {
        printf("System is Little Endian\n");
    }
    else
    {
        printf("System is Big Endian\n");
    }
}

/* Function to print bits of float */
void printFloatBits(float f)
{
    int *p = (int *)&f;

    printBits(*p);
}

int main()
{
    int num;
    int negNum;
    float fnum;
    float negFloat;

    /* Integer bits */
    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("\nBits of %d are:\n", num);
    printBits(num);

    /* Count 1 bits */
    printf("\nNumber of 1 bits = %d\n", countOneBits(num));

    /* Endian check */
    printf("\nChecking Endianness:\n");
    checkEndian();

    /* Negative integer */
    printf("\nEnter a negative integer: ");
    scanf("%d", &negNum);

    printf("\nBits of negative integer %d are:\n", negNum);
    printBits(negNum);

    /* Float bits */
    printf("\nEnter a floating point number: ");
    scanf("%f", &fnum);

    printf("\nBits of float %f are:\n", fnum);
    printFloatBits(fnum);

    /* Negative float bits */
    printf("\nEnter a negative floating point number: ");
    scanf("%f", &negFloat);

    printf("\nBits of negative float %f are:\n", negFloat);
    printFloatBits(negFloat);

    return 0;
}
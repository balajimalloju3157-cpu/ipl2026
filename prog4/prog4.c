#include<stdio.h>
struct bitfield{
    unsigned int firstbit:1;
    unsigned int secondbit:2;
}a;
int main(){
    a.firstbit=1;
    a.secondbit=3;
    printf("firstbit=%u\n",a.firstbit);
    printf("secondbit=%u\n",a.secondbit);
    return 0;
}
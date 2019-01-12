#include <stdio.h>


int main()

{

int a = 1;

int b = 2;

int c = 3;

int* p;

int* q;

p= a;

q = &b;

c = *p;

*p = 13;

printf(“%d”,*q);

}



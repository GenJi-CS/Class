#include <stdio.h>
#include <stdlib.h>
#define size 7

int stack[size],top=-1;
void push()
{
    int value;
    if(top>=6) printf("Fail");
    else {
        top+=1;
        printf("Enter a number: ");
        scanf("%d",&value);
        stack[top]=value;
        printf("Success");
    }
}
void pop()
{
    if(top<0) printf("Fail");
    else {
        top-=1;
        printf("Success");
    }
}
void peek()
{
    if(top<0) printf("Fail");
    else printf("Peeked: %d",stack[top]);
}
void disp()
{
    for(int i=0;i<=top;i++)
    {
        printf("%d\t",stack[i]);
    }
}
void isemp()
{
    if(top<0) printf("Empty!");
    else printf("Not empty");
}
void isfull()
{
    if(top>=6) printf("FULL!");
    else printf("Not full");
}
void main()
{
    int choice;
    printf("1.Push\n2.Pop\n3.Peek\n4.Display\n5.Is Empty?\n6.Is full?");
    do{
        printf("\nEnter choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                disp();
                break;
            case 5:
                isemp();
                break;
            case 6:
                isfull();
                break;
            default:
                printf("Quitting!");
        }
    }while(choice>=1 && choice<=6);
}
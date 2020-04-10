#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include<math.h>


#define MAX 100                                     //defining the max length of input

char ex[MAX];                                       //input char array
char stack0[50];                                
int ex0[100];

int check=-1;

struct Stack                                        //Stack type
{
  int top;
  unsigned capacity;
  int* a;
};



struct Stack* createStack(unsigned capacity)        //operations to be done in the stack
{
  struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));

  if(!stack)
  {
    return NULL;
  } 

  stack->top =-1;
  stack->capacity=capacity;
  stack->a = (int*) malloc(stack->capacity * sizeof(int));

  if(!stack->a)
  {
    return NULL;
  }
  return stack;

}

int isEmpty(struct Stack* stack) 
{ 
  return stack->top == -1 ; 
} 

int peek(struct Stack* stack) 
{ 
  return stack->a[stack->top]; 
} 

int pop(struct Stack* stack) 
{ 
  if (!isEmpty(stack)) 
    return stack->a[stack->top--] ; 
  return '$'; 
} 

void push(struct Stack* stack,int op) 
{ 
  stack->a[++stack->top] = op; 
} 

int Prec(char ch)                           //this funcition return preceder of a given operator
{                                           //if the returned value is higher that means higher precedence
  switch (ch) 
  { 
  case '+': 
  case '-': 
    return 1; 

  case '*': 
  case '/': 
    return 2; 

  case '^': 
    return 3; 
  } 
  return -1; 
} 

int validInfix(char stack0[],int n)          //checks if the given input is a valid infix or not
{
  for(int i=0;ex[i]!='\0';i++)
  {
    switch(ex[i])                            //if the case is true then it push it in the stack along with its symbol number
    {
            case '{': check++;
                      stack0[check]='{';
                      check++;
                      stack0[check]=i;
                      break;
            case '[': check++;
                      stack0[check]='[';
                      check++;
                      stack0[check]=i;
                      break;
            case '(': check++;
                      stack0[check]='(';
                      check++;
                      stack0[check]=i;
                      break;
            case '}': if(stack0[check-1]=='{')
                      check = check-2;
                      else
                      {
                        printf("Invalid exression %c at symbol %d \n",stack0[check-1],stack0[check]);
                        return -1;
                      }
                      break;
            case ']': if(stack0[check-1]=='[')
                      check = check-2;
                       else
                      {
                        printf("Invalid exression %c at symbol %d \n",stack0[check-1],stack0[check]);
                        return -1;
                      }
                      break;
            case ')': if(stack0[check-1]=='(')
                      check = check-2;
                       else
                      {
                        printf("Invalid exression %c at symbol %d \n",stack0[check-1],stack0[check]);
                        return -1;
                      }
                      break;
            case '+': 
            case '-':
            case '*': 
            case '/': 
            case '^': 
                      if(ex[i-1]=='+' || ex[i-1]=='-' || ex[i-1]=='*' || ex[i-1]=='/' || ex[i-1]=='^')
                      {
                        printf("Invalid exression %c at symbol %d\n",ex[i],i);
                        return -1;
                      }
                      break;
                       
    }
  }
    if(check!=-1)
       {
         printf("Invalid exression %c at symbol %d \n",stack0[check-1],stack0[check]);
         return -1;
       }

       return 1;
}

int infixToPostfix(char* ex)                             //function to convert infix expression to postfix expression
{
  int i,k,p=-1;
  struct Stack* stack = createStack(strlen(ex));        //creating a stack of size equal to the input

  if(!stack)                                            //checking if the stack is succesfully created or not
    return -1;

  for(i=0,k=-1; ex[i];++i)
  {
    if(isdigit(ex[i]))                                  //if the scanned char is a digit
    {
        
        if(isdigit(ex[i-1])) continue;                  //it will read the full digit and stores it to another array
        else{
        int num=0;                                      //And if the number is of multiple digit the it will only store the first digit
        int j=i;                                        //and the hole number is stored in a different array named ex0[]
        while(isdigit(ex[j])) 
        { 
        num=num*10 + (int)(ex[j]-'0'); 
          j++; 
        } 
        j--; 
        ex0[++p]=num;
           ex[++k] = ex[i];
         }
    //if the scanned character is '(','{' or '[' the it pushes it to the stack
    //if the scanned character is ')','}' or ']' the it will pop the char from the stack until an '(','{' or '[' is encountered respectivly

    }
    else if(ex[i] =='(')
    {
      push(stack,ex[i]);
    }
    else if(ex[i] == ')')
    {
      while(!isEmpty(stack) && peek(stack)!='(')
      {
        ex[++k] = pop(stack);
      }
      if(!isEmpty(stack) && peek(stack)!='(')
        return -1;                      //if there is an error and it becomes an invalid expression
      else
        pop(stack);
    }
    else if(ex[i] =='{')
    {
      push(stack,ex[i]);
    }
    else if(ex[i] == '}')
    {
      while(!isEmpty(stack) && peek(stack)!='{')
      {
        ex[++k] = pop(stack);
      }
      if(!isEmpty(stack) && peek(stack)!='{')
        return -1;
      else
        pop(stack);
    }
    else if(ex[i] =='[')
    {
      push(stack,ex[i]);
    }
    else if(ex[i] == ']')
    {
      while(!isEmpty(stack) && peek(stack)!='[')
      {
        ex[++k] = pop(stack);
      }
      if(!isEmpty(stack) && peek(stack)!='[')
        return -1;
      else
        pop(stack);
    }
    else                                        //if an operator is encountered
    {
      while(!isEmpty(stack) && Prec(ex[i]) <= Prec(peek(stack)))
      {
        ex[++k] = pop(stack);
      }
      push(stack,ex[i]);
    }
  }

  while(!isEmpty(stack))                          //pops out all the remmaining char from the stack
  {
    ex[++k] = pop(stack);
  }

  ex[++k] = '\0';
  int c=0;
  p=-1;
  while(ex[c]!='\0'){
    if(isdigit(ex[c]))
    {
      printf("%d ",ex0[++p]);
    }
    else{
      printf("%c ",ex[c]);
    }
    c++;
  }
  printf("\n");

}

int evaluatePostfix(char* ex)                           //function to evalute the value of the given postfix expression
{ 
  struct Stack* stack = createStack(strlen(ex));        //creating a stack having the capacity equal to the size of the input
  int i; 
  int p=-1;

  if (!stack) return -1;                                //checking if the stack is created succesfully or not

  for (i = 0; ex[i]; ++i) 
  { 
    if(ex[i]==' ')continue;                             //if there is blan char the continue
    
    else if (isdigit(ex[i]))                            //if the scanned char is a digit the get the full digit from the array ex0[]
    {       
      push(stack,ex0[++p]); 
    } 
    
    else                                                //if the scanned char is an operator the pop 2 elements from the stack and apply the operator
    { 
      int val1 = pop(stack); 
      int val2 = pop(stack); 
      
      switch (ex[i]) 
      { 
      case '+': push(stack, val2 + val1); break; 
      case '-': push(stack, val2 - val1); break; 
      case '*': push(stack, val2 * val1); break; 
      case '/': push(stack, val2/val1); break; 
      case '^': push(stack, pow(val2, val1));break;
      
      } 
    } 
  } 
  return pop(stack); 
} 


int main()
{


   scanf("%s",ex);                                    //taking input and storing it in ex


  int x = validInfix(stack0,50);                      //if the inout is a valid expression then x=1

  if(x == 1)
  {
    printf("Valid\n");
    infixToPostfix(ex);
    printf("%d\n",evaluatePostfix(ex));
  }
                                                      //else it will print the wrong symbol and its position
  return 0;

}
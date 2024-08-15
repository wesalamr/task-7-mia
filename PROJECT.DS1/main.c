#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char postfix[100];
typedef struct
{
    float data;
    struct node*next;
} node;
typedef struct
{
    node*top;
} stack;
stack*initialize()
{
    stack*s=malloc(sizeof(stack));
    s->top=NULL;
    return s;
}
node*newnode(float value)
{
    node*n=malloc(sizeof(node));
    n->data=value;
    n->next=NULL;
    return n;
}
void push(stack*s,float value)
{
    node*p=newnode(value);
    p->next=s->top;
    s->top=p;

}
double pop(stack*s)
{
    node*p=s->top;
    float data=p->data;
    s->top=p->next;
    free(p);
    return data;
}
double top(stack*s)
{
    node*p=s->top;
    float data=p->data;
    return data;
}
int isempty(stack*s)
{
    if(s->top==NULL)
        return 1;
    else
        return 0;
}
int space(char c)
{
    if(c==' '|| c=='\t')
        return 1;
    else
        return 0;
}
int priority(char c)
{
    switch(c)
    {
    case '^':
        return 3;
    case '(':
        return 2;
    case '*':
    case '/':
    case '%':
        return 1;
    case '+':
    case '-':
        return 0;
    }
}
float calculate(const char *token, double x, double y)
{
    if(*token=='+')
        return x+y;
    else if(*token== '-')
        return x-y;
    else if(*token== '*')
        return x*y;
    else if(*token== '/')
        return x/y;
    else if(*token=='^')
        return pow(x,y);

}
float evaluatepostfix(char*postfix)
{
    stack*s=initialize();
    double x,y,z;
    char *token;
    const char delimiters[] = " \t";
    token = strtok(postfix, delimiters);
    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
            {
            double f= atof(token);
            push(s,f);
            }
        else if (*token!= delimiters)
        {
            y=pop(s);
            x=pop(s);
            z=calculate(token,x,y);
            push(s,z);
        }
         token = strtok(NULL, delimiters);
    }
    return pop(s);
}
char* infixToPostfix(char *infix) {
    stack *s = initialize();
    char *token;
    const char delimiters[] = " \t";
    postfix[0] = '\0';
    token = strtok(infix, delimiters);
    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            strcat(postfix, token);
            strcat(postfix, " ");
        } else if (strchr("+-*/%^()", token[0]) != NULL) {
            if (token[0] == '(') {
                push(s, token[0]);
            } else if (token[0] == ')') {
                while (!isempty(s) && top(s) != '(') {
                    postfix[strlen(postfix)] = pop(s);
                    strcat(postfix, " ");
                }
                pop(s);
            } else {
                while (!isempty(s) && priority(top(s)) >= priority(token[0]) && top(s) != '(') {
                    postfix[strlen(postfix)] = pop(s);
                    strcat(postfix, " ");
                }
                push(s, token[0]);
                strcat(postfix, " ");
            }
        }
        token = strtok(NULL, delimiters);
    }


    while (!isempty(s)) {
        postfix[strlen(postfix)] = pop(s);
        strcat(postfix, " ");
    }

    postfix[strlen(postfix) - 1] = '\0';
    printf("Postfix expression: %s\n", postfix);

    return postfix;
}




int main()
{

    char infix[100];
    printf("enter the infix expression:");
    gets(infix);
    infixToPostfix(infix);
    float value=evaluatepostfix(postfix);
    printf("value:%f",value);
    return 0;
}

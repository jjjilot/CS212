#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    double values[10];
    int top_i;
    int num_vals;
}Stack;

void InitializeStack(Stack *s)
{
    s->top_i = -1;
    s->num_vals = 0;
}

void Push(Stack *s, double val)
{
    if (s->num_vals>=10)
        return;
    s->top_i++;
    s->values[s->top_i]=val;
}

double Pop(Stack *s)
{
    double val = s->values[s->top_i];
    s->top_i--;
    return val;
}

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   /* DIV, */
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
    int i;
    for (i=0; op[i]!='\0'; i++)
        if (i==1)
            IssueBadOperationError();
    if (*op == '+')
        return ADD;
    else if (*op == 'x')
        return MULT;
    else if (*op == '-')
        return SUBTRACT;
/*     else if (*op == '/')
        return DIV; */
    else
        return UNSUPPORTED;
}

double Pow10(int exp)
{
    double tot = 1;
    while(exp)
    {
        tot *= 10;
        exp -= 1;
    }
    return tot;
}

void CheckValidNum(char val)
{
    int i;
    int happy_list[10] = {0,1,2,3,4,5,6,7,8,9};
    for (i=0; i<11; i++)
        if (val == happy_list[i])
            return;
    IssueBadNumberError();
}

double TransformTime(char *str, int size, int index, int sign)
{
    int i = index;
    int k = 1;
    double outp = 0;
    while(1)
    {
        if (str[i] == '.')
        {
            if (size == 1)
                return sign*(outp + TransformTime(str, -1, i+1, sign));
            else
                IssueBadNumberError();
        }
        if (str[i] == '\0')
            return outp;
        double val = str[i]-'0';
        CheckValidNum(val);
        if (size == 1)
        {
            outp *= 10;
            outp += val;
        }
        else
        {
            outp += (val/Pow10(k));
            k++;
        }
        i++;
    }
}

double StringToDouble(char *str)
{
    if (str[0] == '-')
        return TransformTime(str, 1, 1, -1);
    else
        return TransformTime(str, 1, 0, 1);
}

double Calculate(double val1, double val2, MathOperation op)
{
    double result;
    switch (op)
    {
        case UNSUPPORTED:
          IssueBadOperationError();
        case ADD:
          result = val2+val1;
          break;
        case SUBTRACT:
          result = val2-val1;
          break;
        case MULT:
          result = val2*val1;
          break;
/*         case DIV:
          result = v/v2;
          break; */
    }
    return result;
}

int main(int argc, char *argv[])
{
    /* argc = 8;
    argv[1]="2";
    argv[2]="3";
    argv[3]="11";
    argv[4]="+";
    argv[5]="5";
    argv[6]="-";
    argv[7]="x"; */

    Stack s;
    InitializeStack(&s);

    for (int i=1; i<argc; i++)
    {
        if (*argv[i]=='-' || *argv[i]=='+' || *argv[i]=='x')
        {
            MathOperation op = GetOperation(argv[i]);
            double val1=Pop(&s);
            double val2=Pop(&s);
            double result = Calculate(val1,val2,op);
            Push(&s, result);
        }
        else
        {
            double val = StringToDouble(argv[i]);
            Push(&s, val); 
        } 
    }
    int total = (int) Pop(&s);
    printf("The total is %d\n",total);
    return 0;
}

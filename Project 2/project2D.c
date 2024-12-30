#include <stdio.h>
#include <stdlib.h>

typedef enum
{
   ADD,
   MULT,
   SUBTRACT,
   DIV,
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
    else if (*op == '/')
        return DIV;
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

int main(int argc, char *argv[])
{
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
        case UNSUPPORTED:
          IssueBadOperationError();
        case ADD:
          result = v+v2;
          break;
        case SUBTRACT:
          result = v-v2;
          break;
        case MULT:
          result = v*v2;
          break;
        case DIV:
          result = v/v2;
          break;
    }
    printf("%d\n", (int) result);
 
    return 0;
}

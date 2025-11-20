#include<stdio.h>
#define strok 5 
int main()
{
    int a,b;//номер стр. счет пробела
    char bukva;//буква
    for (a=0;a<strok; a++)
    {
        for (b=0;b<strok-a-1;b++)//пробелы
        {
            printf(" "); 
        }
        for (bukva='A';bukva<='A'+a;bukva++)//буквы по возр
        {
        printf("%c",bukva);
        }
        for (bukva='A'+a-1;bukva>='A';bukva--)//буквы по убыв.
        {
            printf("%c",bukva);
        }
        printf("\n");
    }
    return 0;
}

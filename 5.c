#include <stdio.h>
int main()
{
    char vvod; // Введенный символ
    int a, b; // Счетчики для циклов
    char bukva; // Переменная для букв
    printf("Введите прописную букву: ");
    scanf("%c", &vvod);
    if (vvod < 'A' || vvod > 'Z') {
        printf("Ошибка: введите прописную букву от A до Z!\n");
        return 1;
    }
    int strok = vvod - 'A' + 1; // Количество строк вычисляем на основе введенного символа
    // Внешний цикл для строк пирамиды
    for (a = 0; a < strok; a++)
    {
        // Первый внутренний цикл для пробелов
        for (b = 0; b < strok - a - 1; b++)
        {
            printf(" "); 
        }
        // Второй внутренний цикл для букв по возрастанию
        for (bukva = 'A'; bukva <= 'A' + a; bukva++)
        {
            printf("%c", bukva);
        }
        // Третий внутренний цикл для букв по убыванию
        for (bukva = 'A' + a - 1; bukva >= 'A'; bukva--)
        {
            printf("%c", bukva);
        }
        printf("\n");
    }
    return 0;
}

#include <stdio.h>
// Константы для тарифных ставок
#define bA 8.75
#define bB 9.33
#define bC 10.00
#define bD 11.20
// Константы для налогов
#define nalog1 0.15
#define nalog2 0.20
#define nalog3 0.25
#define naloglim1 300.0
#define naloglim2 150.0
int main()
{
    char bukva;
    float chasy, stavka;
    float zarplata, nalogi, chistaya;
    float sverhyroch_chasy, sverhyroch_oplata;
    while (1) {
        // Выводим меню с буквами
        printf("Выберите тарифную ставку:\n");
        printf("a) $8.75/час\n");
        printf("b) $9.33/час\n");
        printf("c) $10.00/час\n");
        printf("d) $11.20/час\n");
        printf("q) Выход из программы\n");
        printf("Ваша буква: ");
        scanf(" %c", &bukva);  // пробел перед %c чтобы пропустить перевод строки
        // Выход если выбрали q
        if (bukva == 'q' || bukva == 'Q') {
            printf("Выход из программы:\n");
            break;
        }
        // Проверяем правильность выбора
        if (bukva != 'a' && bukva != 'A' && 
            bukva != 'b' && bukva != 'B' &&
            bukva != 'c' && bukva != 'C' &&
            bukva != 'd' && bukva != 'D') {
            printf("Ошибка! Выберите a, b, c, d или q!\n\n");
            continue;
        }
        if (bukva == EOF) {
            return 0;
        }
        while(getchar()!='\n'){
          return 0;
        }
        // Устанавливаем тарифную ставку
        switch (bukva) {
            case 'a':
            case 'A': stavka = bA; break;
            case 'b':
            case 'B': stavka = bB; break;
            case 'c':
            case 'C': stavka = bC; break;
            case 'd':
            case 'D': stavka = bD; break;
        }
        printf("Введите количество отработанных часов: ");
        scanf("%f", &chasy);
        // Расчет зарплаты
        if (chasy <= 40) {
            zarplata = chasy * stavka;
            sverhyroch_chasy = 0;
            sverhyroch_oplata = 0;
        } else {
            zarplata = 40 * stavka;  // первые 40 часов
            sverhyroch_chasy = chasy - 40;
            sverhyroch_oplata = sverhyroch_chasy * stavka * 1.5;  // сверхурочные ×1.5
            zarplata += sverhyroch_oplata;
        }
        // Расчет налогов
        nalogi = 0.0;
        if (zarplata <= naloglim1) {
            nalogi = zarplata * nalog1;
        } else if (zarplata <= naloglim1 + naloglim2) {
            nalogi = naloglim1 * nalog1 + 
                  (zarplata - naloglim1) * nalog2;
        } else {
            nalogi = naloglim1 * nalog1 + 
                  naloglim2 * nalog2 + 
                  (zarplata - naloglim1 - naloglim2) * nalog3;
        }
        // Чистая зарплата
        chistaya = zarplata - nalogi;
        // Вывод результатов
        printf("результаты расчета\n");
        printf("Тарифная ставка: $%.2f/час\n", stavka);
        printf("Отработано часов: %.1f\n", chasy);
        if (sverhyroch_chasy > 0) {
            printf("Сверхурочные часы: %.1f (доплата: $%.2f)\n", 
                   sverhyroch_chasy, sverhyroch_oplata);
        }
        printf("Общая зарплата: $%.2f\n", zarplata);
        printf("Налоги: $%.2f\n", nalogi);
        printf("Чистая зарплата: $%.2f\n", chistaya);
    }
    printf("Программа завершена\n");
    return 0;
}

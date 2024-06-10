#include <stdio.h>
#include "calculations.h"
#include "file_io.h"

#define N 1000

void display_menu() {
    int choice, n = 11;
    float t[N], Uvx[N], Uvix[N];
    float tn = 0, T = 0.00001, tk = T, dt, U = 5, U1 = 2, U2 = 50;
    float eps = 0.01;

    while (1) {
        printf("\nМеню:\n");
        printf("1 - Выполнить контрольный расчет для n точек\n");
        printf("2 - Рассчитать параметры с заданной точностью\n");
        printf("3 - Записать данные в файл\n");
        printf("4 - Рассчитать параметры с погрешностью\n");
        printf("0 - Выход\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите количество точек для контрольного расчета: ");
                scanf("%d", &n);
                dt = (tk - tn) / (n - 1);
                initialize_time_array(t, tn, dt, n);
                calculate_Uvx(t, Uvx, U, T, n);
                calculate_Uvix_array(Uvx, Uvix, U1, U2, n);
                print_results(t, Uvx, Uvix, n);
                break;

            case 2:
                printf("Введите точность (количество точек): ");
                scanf("%d", &n);
                dt = (tk - tn) / (n - 1);
                initialize_time_array(t, tn, dt, n);
                calculate_Uvx(t, Uvx, U, T, n);
                calculate_Uvix_array(Uvx, Uvix, U1, U2, n);

                printf("Выберите расчет для входа (1) или выхода (2): ");
                int sub_choice;
                scanf("%d", &sub_choice);

                float Umax, Umin, Uimp, pulse_duration;
                if (sub_choice == 1) {
                    find_Umax_Umin(Uvx, n, &Umax, &Umin);
                    Uimp = Umin + 0.5 * (Umax - Umin);
                    pulse_duration = calculate_pulse_duration(Uvx, Uimp, dt, n);
                    printf("Для входа: Umax: %f, Umin: %f, Uimp: %f, Длительность импульса: %f\n", Umax, Umin, Uimp, pulse_duration);
                } else if (sub_choice == 2) {
                    find_Umax_Umin(Uvix, n, &Umax, &Umin);
                    Uimp = Umin + 0.5 * (Umax - Umin);
                    pulse_duration = calculate_pulse_duration(Uvix, Uimp, dt, n);
                    printf("Для выхода: Umax: %f, Umin: %f, Uimp: %f, Длительность импульса: %f\n", Umax, Umin, Uimp, pulse_duration);
                } else {
                    printf("Неправильный выбор.\n");
                }
                break;

            case 3:
                write_results_to_files(t, Uvx, Uvix, n);
                break;

            case 4:
                printf("Выберите расчет для входа (1) или выхода (2): ");
                int calc_choice;
                scanf("%d", &calc_choice);
                if (calc_choice == 1 || calc_choice == 2) {
                    calculate_with_precision(t, Uvx, Uvix, tn, tk, U, T, U1, U2, eps, calc_choice == 2);
                } else {
                    printf("Неправильный выбор.\n");
                }
                break;

            case 0:
                return;

            default:
                printf("Неправильный выбор. Попробуйте снова.\n");
                break;
        }
    }
}

#include <stdio.h>
#include "file_io.h"

void write_results_to_files(float t[], float Uvx[], float Uvix[], int n) {
    FILE *file_t = fopen("massiv_t.txt", "w");
    FILE *file_uvx = fopen("massiv_uvx.txt", "w");
    FILE *file_uvix = fopen("massiv_uvix.txt", "w");

    if (!file_t || !file_uvx || !file_uvix) {
        printf("Ошибка при открытии файлов!\n");
        if (file_t) fclose(file_t);
        if (file_uvx) fclose(file_uvx);
        if (file_uvix) fclose(file_uvix);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file_t, "%.6f\n", t[i]);
        fprintf(file_uvx, "%.2f\n", Uvx[i]);
        fprintf(file_uvix, "%.2f\n", Uvix[i]);
    }

    fclose(file_t);
    fclose(file_uvx);
    fclose(file_uvix);

    printf("Данные записаны в файлы: massiv_t.txt, massiv_uvx.txt, massiv_uvix.txt\n");
}

void read_and_print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s для чтения.\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

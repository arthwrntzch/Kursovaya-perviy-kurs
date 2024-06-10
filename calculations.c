#include <stdio.h>
#include <math.h>
#include "calculations.h"

#define N 1000

float calculate_Uvh(float t, float U, float T) {
    return (t <= T / 2) ? (2 * U * t / T) : (2 * U * (T - t) / T);
}

float calculate_Uvix(float Uvh, float U1, float U2) {
    return (Uvh < U1) ? ((U2 / (U1 * U1)) * Uvh * (2 * U1 - Uvh)) : U2;
}

void initialize_time_array(float t[], float tn, float dt, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = tn + i * dt;
    }
}

void calculate_Uvx(float t[], float Uvx[], float U, float T, int n) {
    for (int i = 0; i < n; i++) {
        Uvx[i] = calculate_Uvh(t[i], U, T);
    }
}

void calculate_Uvix_array(float Uvx[], float Uvix[], float U1, float U2, int n) {
    for (int i = 0; i < n; i++) {
        Uvix[i] = calculate_Uvix(Uvx[i], U1, U2);
    }
}

void find_Umax_Umin(float values[], int n, float *Umax, float *Umin) {
    *Umax = *Umin = values[0];
    for (int i = 1; i < n; i++) {
        if (values[i] > *Umax) *Umax = values[i];
        if (values[i] < *Umin) *Umin = values[i];
    }
}

float calculate_pulse_duration(float values[], float threshold, float dt, int n) {
    float pulse_duration = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] >= threshold) {
            pulse_duration += dt;
        }
    }
    return pulse_duration;
}

void calculate_with_precision(float t[], float Uvx[], float Uvix[], float tn, float tk, float U, float T, float U1, float U2, float eps, int use_output) {
    float dt, Umax, Umin, Uimp, pulse_duration;
    float par = 1e10, par1, p = 1;
    int n = 2;

    while (p > 0.01) {
        dt = (tk - tn) / (n - 1);
        initialize_time_array(t, tn, dt, n);
        calculate_Uvx(t, Uvx, U, T, n);
        calculate_Uvix_array(Uvx, Uvix, U1, U2, n);

        float *values = use_output ? Uvix : Uvx;
        find_Umax_Umin(values, n, &Umax, &Umin);
        Uimp = Umin + 0.5 * (Umax - Umin);
        pulse_duration = calculate_pulse_duration(values, Uimp, dt, n);

        par1 = pulse_duration;
        p = fabs(par - par1) / par1;
        printf("n=%3d     параметр=%9.7f  погрешность=%.4f\n", n, par1, p);

        par = par1;
        n = n * 2;
    }
}

void print_results(float t[], float Uvx[], float Uvix[], int n) {
    printf(" №     t        Uvx      Uvix\n");
    for (int i = 0; i < n; i++) {
        printf("%3d %.8f %.3f %.3f\n", i, t[i], Uvx[i], Uvix[i]);
    }
}

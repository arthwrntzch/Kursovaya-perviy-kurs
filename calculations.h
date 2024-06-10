#ifndef CALCULATIONS_H
#define CALCULATIONS_H

float calculate_Uvh(float t, float U, float T);
float calculate_Uvix(float Uvh, float U1, float U2);
void initialize_time_array(float t[], float tn, float dt, int n);
void calculate_Uvx(float t[], float Uvx[], float U, float T, int n);
void calculate_Uvix_array(float Uvx[], float Uvix[], float U1, float U2, int n);
void find_Umax_Umin(float values[], int n, float *Umax, float *Umin);
float calculate_pulse_duration(float values[], float threshold, float dt, int n);
void calculate_with_precision(float t[], float Uvx[], float Uvix[], float tn, float tk, float U, float T, float U1, float U2, float eps, int use_output);
void print_results(float t[], float Uvx[], float Uvix[], int n);

#endif // CALCULATIONS_H

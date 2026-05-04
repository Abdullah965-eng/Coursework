#ifndef WAVEFORM_H
#define WAVEFORM_H
#include <stdint.h>

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

typedef struct {
    double rms;
    double peak_to_peak;
    double dc_offset;
    int clipped_count;
    int compliant; 
    double std_dev;
    uint8_t status_flags;
} PhaseResult;

double compute_rms(const double *voltages, int n);
double compute_peak_to_peak(const double *voltages, int n);
double compute_dc_offset(const double *voltages, int n);
int count_clipped(const double *voltages, int n, double limit);
int check_compliance(double rms, double nominal);
double compute_std_dev(const double *voltages, int n, double mean);
uint8_t build_status_flags(int clipped, int compliant);
PhaseResult analyse_phase(const double *voltages, int n);

#endif
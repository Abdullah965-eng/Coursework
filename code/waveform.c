#include "waveform.h"
#include <math.h>
#include <stdint.h>

double compute_rms(const double *voltages, int n) {
    double sum_sq= 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq +=voltages[i]* voltages[i];
    }
    return sqrt(sum_sq /n);
}

double compute_peak_to_peak(const double *voltages, int n) {
    double vmax = voltages[0];
    double vmin=voltages[0];
    for (int i= 1; i<n; i++) {
        if (voltages[i]>vmax) vmax =voltages[i];
        if (voltages[i] < vmin) vmin= voltages[i];
    }
    return vmax -vmin;
}

double compute_dc_offset(const double *voltages, int n) {
    double sum = 0.0;
    for (int i=0; i < n; i++) {
        sum+= voltages[i];
    }
    return sum/ n;
}

int count_clipped(const double *voltages, int n, double limit) {
    int count =0;
    for (int i = 0; i < n; i++) {
        double v = voltages[i];
        if (v < 0) v =-v;
        if (v >=limit) count++;
    }
    return count;
}

int check_compliance(double rms, double nominal) {
    double low = nominal * 0.9;
    double high= nominal *1.1;
    if (rms >= low && rms <= high) return 1;
    return 0;
}

double compute_std_dev(const double *voltages, int n, double mean) {
    double sum = 0.0;
    for (int i=0; i<n; i++) {
        double d = voltages[i]-mean;
        sum += d*d;
    }
    return sqrt(sum/n);
}

uint8_t build_status_flags(int clipped, int compliant) {
    uint8_t f = 0;
    if (clipped > 0) f|= 0x01;
    if (!compliant) f |=0x02;
    return f;
}

PhaseResult analyse_phase(const double *voltages, int n) {
    PhaseResult r;
    r.rms = compute_rms(voltages, n);
    r.peak_to_peak = compute_peak_to_peak(voltages, n);
    r.dc_offset = compute_dc_offset(voltages, n);
    r.clipped_count = count_clipped(voltages, n, 324.9);
    r.compliant = check_compliance(r.rms, 230.0);
    r.std_dev = compute_std_dev(voltages, n, r.dc_offset);
    r.status_flags = build_status_flags(r.clipped_count, r.compliant);
    return r;
}
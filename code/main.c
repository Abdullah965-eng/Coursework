#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("need a filename\n");
        return 1;
    }

    int n =0;
    WaveformSample *data = load_csv(argv[1], &n);
    if (!data) return 1;

    double *vA = malloc(n* sizeof(double));
    double *vB = malloc(n *sizeof(double));
    double *vC = malloc(n * sizeof(double));

    for (int i= 0; i < n; i++) {
        vA[i] = data[i].phase_A_voltage;
        vB[i]= data[i].phase_B_voltage;
        vC[i] =data[i].phase_C_voltage;
    }

    PhaseResult rA = analyse_phase(vA, n);
    PhaseResult rB = analyse_phase(vB, n);
    PhaseResult rC = analyse_phase(vC, n);

    double fmin = data[0].frequency, fmax =data[0].frequency;
    double pmin = data[0].power_factor, pmax = data[0].power_factor;
    double tmin = data[0].thd_percent, tmax = data[0].thd_percent;

    for (int i = 1; i< n; i++) {
        if(data[i].frequency < fmin) fmin=data[i].frequency;
        if(data[i].frequency > fmax) fmax = data[i].frequency;
        if(data[i].power_factor < pmin) pmin = data[i].power_factor;
        if(data[i].power_factor > pmax) pmax =data[i].power_factor;
        if(data[i].thd_percent < tmin) tmin= data[i].thd_percent;
        if(data[i].thd_percent > tmax) tmax = data[i].thd_percent;
    }

    printf("Analysis complete for %d rows\n", n);
    write_report("results.txt", data, n, rA, rB, rC, fmin, fmax, pmin, pmax, tmin, tmax);

    free(vA); free(vB); free(vC);
    free(data);
    return 0;
}
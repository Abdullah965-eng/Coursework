#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

WaveformSample *load_csv(const char *filename, int *out_count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("couldnt open file\n");
        return NULL;
    }

    char buf[512];
    int count = 0;
    fgets(buf, 512, f);
    while (fgets(buf, 512, f)) count++;

    WaveformSample *data = malloc(count * sizeof(WaveformSample));
    rewind(f);
    fgets(buf, 512, f);

    for (int i= 0; i<count; i++) {
        fgets(buf, 512, f);
        sscanf(buf, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &data[i].timestamp, &data[i].phase_A_voltage, &data[i].phase_B_voltage,
            &data[i].phase_C_voltage, &data[i].line_current, &data[i].frequency,
            &data[i].power_factor, &data[i].thd_percent);
    }

    fclose(f);
    *out_count = count;
    return data;
}

void write_report(const char *filename, const WaveformSample *samples, int n, 
                  PhaseResult res_A, PhaseResult res_B, PhaseResult res_C,
                  double fmin, double fmax, double pmin, double pmax, double tmin, double tmax) {
    FILE *fp = fopen(filename, "w");
    if(!fp) return;

    fprintf(fp, "--- Analysis Report ---\n");
    fprintf(fp, "Samples: %d\n\n", n);
    
    fprintf(fp, "Phase A: RMS=%.2f, DC=%.2f, Flags=%d\n", res_A.rms, res_A.dc_offset, res_A.status_flags);
    fprintf(fp, "Phase B: RMS=%.2f, DC=%.2f, Flags=%d\n", res_B.rms, res_B.dc_offset, res_B.status_flags);
    fprintf(fp, "Phase C: RMS=%.2f, DC=%.2f, Flags=%d\n", res_C.rms, res_C.dc_offset, res_C.status_flags);
    
    fprintf(fp, "\nFreq range: %.2f to %.2f\n", fmin, fmax);
    fprintf(fp, "PF range: %.2f to %.2f\n", pmin, pmax);
    fprintf(fp, "THD range: %.2f to %.2f\n", tmin, tmax);

    fclose(fp);
    printf("report saved to %s\n", filename);
}
#ifndef IO_H
#define IO_H
#include "waveform.h"

WaveformSample *load_csv(const char *filename, int *out_count);
void write_report(const char *filename, const WaveformSample *samples, int n, 
                  PhaseResult res_A, PhaseResult res_B, PhaseResult res_C,
                  double fmin, double fmax, double pmin, double pmax, double tmin, double tmax);

#endif
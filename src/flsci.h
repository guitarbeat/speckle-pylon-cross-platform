/* Copyright (C) 2008-2019 W. James Tom  & Andrew Dunn */

#ifndef FLSCI_H
#define FLSCI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void *flsci_sc;
typedef void *flsci_sc_exact;
typedef void *flsci_rct;
typedef void *flsci_rct_iterate;

flsci_sc flsci_sc128_init(unsigned int width, unsigned int height, unsigned int window, unsigned int thread_count);
void flsci_sc128_process(flsci_sc x, unsigned char **raw_images, unsigned int frame_count, float *sc_image);
void flsci_sc128_end(flsci_sc *x);

flsci_sc flsci_sc_init(unsigned int width, unsigned int height, unsigned int window, unsigned int thread_count);
void flsci_sc_process(flsci_sc x, unsigned char **raw_images, unsigned int frame_count, float *sc_image);
void flsci_sc_end(flsci_sc *x);

flsci_sc_exact flsci_sc_exact_init(unsigned int width, unsigned int height, unsigned int window, unsigned int thread_count);
void flsci_sc_exact_process(flsci_sc_exact x, unsigned char **raw_images, unsigned int frame_count, float *sc_image);
void flsci_sc_exact_end(flsci_sc_exact *x);

flsci_rct flsci_rct_init(float *table, unsigned int table_size, unsigned int width, unsigned int height, unsigned int thread_count);
void flsci_rct_process(flsci_rct z, float *sc_image, float *baseline_image, float *rct_image);
void flsci_rct_end(flsci_rct *z);

flsci_rct_iterate flsci_rct_iterate_init(float *table, unsigned int table_size, unsigned int width, unsigned int height, unsigned int thread_count);
void flsci_rct_iterate_process(flsci_rct_iterate z, float *sc_image, float *baseline_image, float error_limit, unsigned int max_iterations, float *rct_image);
void flsci_rct_iterate_end(flsci_rct_iterate *z);

float *flsci_rct_table_create(unsigned int table_size);
float *flsci_rct_table_load(char *filename, unsigned int *table_size);
int flsci_rct_table_save(char *filename, float *table, unsigned int table_size);

#ifdef __cplusplus
}
#endif

#endif

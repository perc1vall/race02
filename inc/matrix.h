#ifndef RACE02_MATRIX_H
#define RACE02_MATRIX_H

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

bool add_check(int a, int b, int res);

bool sub_check(int a, int b, int res);

bool mul_check(int a, int b, int res);

bool div_check(int a, int b, int res);

int dig_giver(const char *str, const int *arr, int i);

char operation_giver(const char *str, const int *arr, int i);

int **arr_giver(const char **op);

int mx_strlen(const char *s);

int iter_max_giver(const char **op);

void matrix_body(const char **op);

char *mx_atoi(const char *str);

void mx_printerr(const char *s);

#endif

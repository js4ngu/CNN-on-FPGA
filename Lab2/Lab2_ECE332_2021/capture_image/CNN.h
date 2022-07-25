#ifndef CNN_H
#define CNN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "parameter.h"
#include "ifmap_fmap_integer.h"
#include "cnn_func_integer.h"
#include "ifmap_fmap_float.h"
#include "cnn_func_float.h"

unsigned int initializor_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3);
unsigned int validator_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3 );
void cnn_ref(float *ofmap, float *ifmap, int data_set);
void cnn_opt(short *ofmap, short *ifmap, int data_set);

void measurePerformace();
void Classification();
void floatMNIST();
void unfloatMNIST();
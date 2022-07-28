#ifndef _CNN_H
#define _CNN_H

unsigned int initializor_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3);
unsigned int validator_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3 );

void cnn_opt(short *ofmap, short *ifmap, int data_set);
void cnn_img_opt(short *ofmap, short *ifmap);
void MNIST_OPT();
void MNIST_IMG_OPT();
void Classifiacation_opt();

#endif
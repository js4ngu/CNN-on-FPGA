#include <stdint.h>
#include "CNN.h"
#include "parameter.h"
#include "ifmap_fmap_integer.h"
#include "cnn_func_integer.h"
#include "CNN_img.h"

//CNN VAR
float ofmap_ref[_data][_class] = { { 0, }, };
float ofmap_img[_class] 	   = { 0, };
short ofmap_opt[_data][_class] = { { 0, }, };
short ofmap_img_opt[_class] 	   = { 0, };

int data_set = 0, mode_sel = 0;
short max_val_s = 0;
int   n = 0, m = 0, e = 0, f = 0, data_index = 0, estimated_label = 0;
int   ii = 0, kk = 0, i = 0;
float tmp = 0;
/*
short *ifmap = 0;
short *ofmap = 0;
*/
short ifmap[28*28]	= {0,};
short ofmap[10]		= {0,};

void cnn_img_opt(short *ofmap, short *ifmap){
	int i = 0;
	short ofmap1[E_C1*F_C1*M_C1*N_C1] = {0,};
	short ofmap2[E_P1*F_P1*C_P1*N_P1] = {0,};
	short ofmap3[E_C2*F_C2*M_C2*N_C2] = {0,};
	short ofmap4[E_P2*F_P2*C_P2*N_P2] = {0,};
	short ofmap5[E_C3*F_C3*M_C3*N_C3] = {0,};
	short ofmap6[E_R1*F_R1*M_R1*N_R1] = {0,};

	//Input mapping
	for (i = 0; i<28*28; i++) {
		ifmap[i] = (short)(img_data_7[i] * pow(2, SCALE - 1));
	}

	/////////////////////////////
	//         Layer #1       //
	////////////////////////////
	convolution(ofmap1, ifmap, fmap1, N_C1, C_C1, M_C1, F_C1, E_C1, R_C1, S_C1, H_C1, W_C1, U_C1);
	bias(ofmap1, ofmap1, bias1, N_C1, M_C1, E_C1, F_C1);
	pool(ofmap2, ofmap1, E_C1, F_C1, M_C1);

	/////////////////////////////
	//         Layer #2       //
	////////////////////////////
	convolution(ofmap3, ofmap2, fmap2, N_C2, C_C2, M_C2, F_C2, E_C2, R_C2, S_C2, H_C2, W_C2, U_C2);
	bias(ofmap3, ofmap3, bias2, N_C2, M_C2, E_C2, F_C2);
	pool(ofmap4, ofmap3, E_C2, F_C2, M_C2);

	/////////////////////////////
	//         Layer #3       //
	////////////////////////////
	convolution(ofmap5, ofmap4, fmap3, N_C3, C_C3, M_C3, F_C3, E_C3, R_C3, S_C3, H_C3, W_C3, U_C3);
	bias(ofmap5, ofmap5, bias3, N_C3, M_C3, E_C3, F_C3);
	relu(ofmap6, ofmap5, E_C3, F_C3, M_C3);

	/////////////////////////////
	//         Layer #4       //
	////////////////////////////
	convolution(ofmap, ofmap6, fmap4, 1, C_C4, 10, 1, 1, R_C4, S_C4, H_C4, W_C4, U_C4);
	bias(ofmap, ofmap, bias4, 1, 10, 1, 1);
}

void MNIST_IMG_OPT(){
	printf("Case 3: Test IMG Optimization \r\n");
	ifmap[28*28];
	ofmap[10];

	cnn_img_opt(ofmap, ifmap);
	Classifiacation_opt();	//Classifiacation
}

void Classifiacation_opt(){
	max_val_s = ofmap[0];
	data_index = 0;
	for (m = 0; m<10; m++) {
		ofmap_img_opt[data_index] = ofmap[m];

		if (ofmap[m] >= max_val_s) {
			max_val_s = ofmap[m];
			estimated_label = m;
		}
		data_index++;
	}
	printf("estimated label: %d (%d) \r\n", estimated_label, max_val_s);
	int ofmap[10] = {0,};
}

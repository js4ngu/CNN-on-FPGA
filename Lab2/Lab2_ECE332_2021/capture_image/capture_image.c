#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "video.h"
#include "./CNN/parameter.h"
#include "./CNN/ifmap_fmap_integer.h"
#include "./CNN/cnn_func_integer.h"
#include "./CNN/ifmap_fmap_float.h"
#include "./CNN/cnn_func_float.h"
#include "CNN_img.h"

#define KEY_BASE            0xFF200050

#define KEY0				0x1
#define KEY1				0x2
#define KEY2				0x4
#define KEY3				0x8

#define BLACK 				0x0000
#define WHITE				0xFFFF
#define BLUE 				0x00FF
#define GREEN				0x0F00
#define RED 				0xF000

#define TEST_CASE 2
#define TEST_ROUNDS 10

//HW VAR
volatile int * KEY_ptr = (int *) KEY_BASE;
int key_value;

//CNN VAR
float ofmap_ref[_data][_class] = { { 0, }, };
float ofmap_img[_class] 	   = { 0, };
short ofmap_opt[_data][_class] = { { 0, }, };

int data_set = 0, mode_sel = 0;
float max_val_f = 0;
short max_val_s = 0;
int   n = 0, m = 0, e = 0, f = 0, data_index = 0, estimated_label = 0;
int   ii = 0, kk = 0, i = 0;
float tmp = 0;

short *ifmap = 0;
float *ifmap_f = 0;
short *ofmap = 0;
float *ofmap_f = 0;

float error  = 0;
float signal = 0;
float NSRdB = 0;

//Display VAR
int offset_x = 160 - 14;
int offset_y = 120 - 14;
int Size_x = 28;
int Size_y = 28;
int thickness = 1;

//func
unsigned int initializor_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3);
unsigned int validator_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3 );
void cnn_ref(float *ofmap, float *ifmap, int data_set);
void cnn_opt(short *ofmap, short *ifmap, int data_set);
void cnn_img(float *ofmap, float *ifmap);

//void Measure_performance();

int main(void) {
	while (1){
		enableVideo();
		DrawRectangle_filled(offset_x				, offset_y			, Size_x, thickness	, BLUE); //밑변
		DrawRectangle_filled(offset_x				, offset_y + Size_y	, Size_x, thickness, BLUE); //윗변
		DrawRectangle_filled(offset_x				, offset_y			, thickness, Size_y, BLUE); //좌변
		DrawRectangle_filled(offset_x + Size_x		, offset_y			, thickness, Size_y, BLUE); //우변

		if(*(KEY_ptr) != 0){
			key_value = *(KEY_ptr);
			switch (key_value) {
				case KEY0:		//KEY00
					printf("Case 0: Reference \r\n");
					for (data_set = 0; data_set<_data; data_set++){
						ifmap_f = (float *)calloc(H_C1*W_C1*C_C1*N_C1,sizeof(float));
						ofmap_f = (float *)calloc(E_C4*F_C4*M_C4*N_C4,sizeof(float));

						cnn_ref(ofmap_f, ifmap_f, data_set);

						/////////////////////////////
						//     Classifiacation     //
						////////////////////////////
						max_val_f = ofmap_f[0];
						data_index = 0;
						for (n = 0; n<N_C4; n++) {
							for (m = 0; m<M_C4; m++) {
								for (e = 0; e<E_C4; e++) {
									for (f = 0; f<F_C4; f++) {

										ofmap_ref[data_set][data_index] = ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];

										if (ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e] >= max_val_f) {
											max_val_f = ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];
											estimated_label = m;
										}
										data_index++;
									}
								}
							}
						}
						printf("estimated label: %d (%f) \r\n", estimated_label, max_val_f);

						free(ifmap_f);
						free(ofmap_f);
					}
					printf("DONE\r\n");
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY1:		//KEY01
					printf("Case 1: Optimization \r\n");
					
					for (data_set = 0; data_set<_data; data_set++){
						ifmap   = (short *)calloc(H_C1*W_C1*C_C1*N_C1,sizeof(short));
						ofmap   = (short *)calloc(E_C4*F_C4*M_C4*N_C4,sizeof(short));

						cnn_opt(ofmap, ifmap, data_set);

						/////////////////////////////
						//     Classifiacation     //
						////////////////////////////
						max_val_s = ofmap[0];
						data_index = 0;
						for (n = 0; n<N_C4; n++) {
							for (m = 0; m<M_C4; m++) {
								for (e = 0; e<E_C4; e++) {
									for (f = 0; f<F_C4; f++) {

										ofmap_opt[data_set][data_index] = ofmap[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];

										if (ofmap[((n*M_C4 + m)*E_C4 + f)*F_C4 + e] >= max_val_s) {
											max_val_s = ofmap[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];
											estimated_label = m;
										}
										data_index++;
									}
								}
							}
						}
						printf("estimated label: %d (%d) \r\n", estimated_label, max_val_s);

						free(ifmap);
						free(ofmap);
					} 
					
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY2:		//KEY02
					printf("Case 2: Test IMG FLOAT NUMBER \r\n");
					ifmap_f = (float *)calloc(H_C1*W_C1*C_C1*N_C1,sizeof(float));
					ofmap_f = (float *)calloc(E_C4*F_C4*M_C4*N_C4,sizeof(float));

					cnn_img(ofmap_f, ifmap_f);

					/////////////////////////////
					//     Classifiacation     //
					////////////////////////////
					max_val_f = ofmap_f[0];
					data_index = 0;
					for (n = 0; n<N_C4; n++) {
						for (m = 0; m<M_C4; m++) {
							for (e = 0; e<E_C4; e++) {
								for (f = 0; f<F_C4; f++) {

									ofmap_img[data_index] = ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];

									if (ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e] >= max_val_f) {
										max_val_f = ofmap_f[((n*M_C4 + m)*E_C4 + f)*F_C4 + e];
										estimated_label = m;
									}
									data_index++;
								}
							}
						}
					}
					printf("estimated label: %d (%f) \r\n", estimated_label, max_val_f);
					free(ifmap_f);
					free(ofmap_f);
				
					printf("DONE\r\n");

					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY3:		//KEY03
					printf("KEY3 \r\n");
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
			}
		}
	}
}

/*
void Measure_performance(){
	for (ii = 0; ii<_data; ii++) {
		for (kk = 0; kk<_class; kk++) {
			tmp = (float)(ofmap_opt[ii][kk] * pow(2, -SCALE + 1));
			error += pow(fabsf(ofmap_ref[ii][kk] - tmp), 2);
			signal += pow(fabsf(ofmap_ref[ii][kk]), 2);
		}
	}
	NSRdB = 10 * log10((double)error / (double)signal);
	printf("\r\n");
	printf("Measure performance: NSR(dB) = %0.3f \r\n", NSRdB);
}
*/
unsigned int initializor_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3)
{
	return 1;
}

unsigned int validator_dummy(unsigned int uiParam0, unsigned int uiParam1, unsigned int uiParam2, unsigned int uiParam3 )
{
	return 1;
}

void cnn_ref(float *ofmap, float *ifmap, int data_set)
{
	int i = 0;

	float *ofmap1 = (float *) calloc(E_C1*F_C1*M_C1*N_C1, sizeof(float));
	float *ofmap2 = (float *) calloc(E_P1*F_P1*C_P1*N_P1, sizeof(float));
	float *ofmap3 = (float *) calloc(E_C2*F_C2*M_C2*N_C2, sizeof(float));
	float *ofmap4 = (float *) calloc(E_P2*F_P2*C_P2*N_P2, sizeof(float));
	float *ofmap5 = (float *) calloc(E_C3*F_C3*M_C3*N_C3, sizeof(float));
	float *ofmap6 = (float *) calloc(E_R1*F_R1*M_R1*N_R1, sizeof(float));

	//Input mapping
	for (i = 0; i<H_C1*W_C1; i++) {
		ifmap[i] = data[data_set][i];
	}

	/////////////////////////////
	//         Layer #1       //
	////////////////////////////
	convolution_f(ofmap1, ifmap, fmap1_f, N_C1, C_C1, M_C1, F_C1, E_C1, R_C1, S_C1, H_C1, W_C1, U_C1);
	bias_f(ofmap1, ofmap1, bias1_f, N_C1, M_C1, E_C1, F_C1);
	pool_f(ofmap2, ofmap1, E_C1, F_C1, M_C1);

	/////////////////////////////
	//         Layer #2       //
	////////////////////////////
	convolution_f(ofmap3, ofmap2, fmap2_f, N_C2, C_C2, M_C2, F_C2, E_C2, R_C2, S_C2, H_C2, W_C2, U_C2);
	bias_f(ofmap3, ofmap3, bias2_f, N_C2, M_C2, E_C2, F_C2);
	pool_f(ofmap4, ofmap3, E_C2, F_C2, M_C2);

	/////////////////////////////
	//         Layer #3       //
	////////////////////////////
	convolution_f(ofmap5, ofmap4, fmap3_f, N_C3, C_C3, M_C3, F_C3, E_C3, R_C3, S_C3, H_C3, W_C3, U_C3);
	bias_f(ofmap5, ofmap5, bias3_f, N_C3, M_C3, E_C3, F_C3);
	relu_f(ofmap6, ofmap5, E_C3, F_C3, M_C3);

	/////////////////////////////
	//         Layer #4       //
	////////////////////////////
	convolution_f(ofmap, ofmap6, fmap4_f, N_C4, C_C4, M_C4, F_C4, E_C4, R_C4, S_C4, H_C4, W_C4, U_C4);
	bias_f(ofmap, ofmap, bias4_f, N_C4, M_C4, E_C4, F_C4);

	free(ofmap1);
	free(ofmap2);
	free(ofmap3);
	free(ofmap4);
	free(ofmap5);
	free(ofmap6);
}

void cnn_img(float *ofmap, float *ifmap)
{
	int i = 0;

	float *ofmap1 = (float *) calloc(E_C1*F_C1*M_C1*N_C1, sizeof(float));
	float *ofmap2 = (float *) calloc(E_P1*F_P1*C_P1*N_P1, sizeof(float));
	float *ofmap3 = (float *) calloc(E_C2*F_C2*M_C2*N_C2, sizeof(float));
	float *ofmap4 = (float *) calloc(E_P2*F_P2*C_P2*N_P2, sizeof(float));
	float *ofmap5 = (float *) calloc(E_C3*F_C3*M_C3*N_C3, sizeof(float));
	float *ofmap6 = (float *) calloc(E_R1*F_R1*M_R1*N_R1, sizeof(float));

	//Input mapping
	for (i = 0; i<H_C1*W_C1; i++) {
		ifmap[i] = img_data[i];
	}

	/////////////////////////////
	//         Layer #1       //
	////////////////////////////
	convolution_f(ofmap1, ifmap, fmap1_f, N_C1, C_C1, M_C1, F_C1, E_C1, R_C1, S_C1, H_C1, W_C1, U_C1);
	bias_f(ofmap1, ofmap1, bias1_f, N_C1, M_C1, E_C1, F_C1);
	pool_f(ofmap2, ofmap1, E_C1, F_C1, M_C1);

	/////////////////////////////
	//         Layer #2       //
	////////////////////////////
	convolution_f(ofmap3, ofmap2, fmap2_f, N_C2, C_C2, M_C2, F_C2, E_C2, R_C2, S_C2, H_C2, W_C2, U_C2);
	bias_f(ofmap3, ofmap3, bias2_f, N_C2, M_C2, E_C2, F_C2);
	pool_f(ofmap4, ofmap3, E_C2, F_C2, M_C2);

	/////////////////////////////
	//         Layer #3       //
	////////////////////////////
	convolution_f(ofmap5, ofmap4, fmap3_f, N_C3, C_C3, M_C3, F_C3, E_C3, R_C3, S_C3, H_C3, W_C3, U_C3);
	bias_f(ofmap5, ofmap5, bias3_f, N_C3, M_C3, E_C3, F_C3);
	relu_f(ofmap6, ofmap5, E_C3, F_C3, M_C3);

	/////////////////////////////
	//         Layer #4       //
	////////////////////////////
	convolution_f(ofmap, ofmap6, fmap4_f, N_C4, C_C4, M_C4, F_C4, E_C4, R_C4, S_C4, H_C4, W_C4, U_C4);
	bias_f(ofmap, ofmap, bias4_f, N_C4, M_C4, E_C4, F_C4);

	free(ofmap1);
	free(ofmap2);
	free(ofmap3);
	free(ofmap4);
	free(ofmap5);
	free(ofmap6);
}

void cnn_opt(short *ofmap, short *ifmap, int data_set)
{
	///////////////////////////////////////////////////////////////
	// You are allowed to modify only the inside of this function
	// From this line

	int i = 0;

	short *ofmap1 = (short *) calloc(E_C1*F_C1*M_C1*N_C1, sizeof(short));
	short *ofmap2 = (short *) calloc(E_P1*F_P1*C_P1*N_P1, sizeof(short));
	short *ofmap3 = (short *) calloc(E_C2*F_C2*M_C2*N_C2, sizeof(short));
	short *ofmap4 = (short *) calloc(E_P2*F_P2*C_P2*N_P2, sizeof(short));
	short *ofmap5 = (short *) calloc(E_C3*F_C3*M_C3*N_C3, sizeof(short));
	short *ofmap6 = (short *) calloc(E_R1*F_R1*M_R1*N_R1, sizeof(short));

	//Input mapping
	for (i = 0; i<H_C1*W_C1; i++) {
		ifmap[i] = (short)(data[data_set][i] * pow(2, SCALE - 1));
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
	convolution(ofmap, ofmap6, fmap4, N_C4, C_C4, M_C4, F_C4, E_C4, R_C4, S_C4, H_C4, W_C4, U_C4);
	bias(ofmap, ofmap, bias4, N_C4, M_C4, E_C4, F_C4);

	free(ofmap1);
	free(ofmap2);
	free(ofmap3);
	free(ofmap4);
	free(ofmap5);
	free(ofmap6);

	// To this line
	// You are allowed to modify only the inside of this function
	///////////////////////////////////////////////////////////////
}

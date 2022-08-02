#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "video.h"
#include "./CNN/CNN.h"
#include "./CNN/parameter.h"
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

//Display VAR
int offset_x = 160 - 14;
int offset_y = 120 - 14;
int Size_x = 28;
int Size_y = 28;
int thickness = 1;

//DATA
float fixeldata[28][28];
short grayFixeldata[28][28];
short ifmap_1[28*28]	= {0,};
short ofmap_1[10]		= {0,};		

int main(void) {
	while (1){
		DrawRectangle_filled(offset_x				, offset_y			, Size_x, thickness, BLUE); //밑변
		DrawRectangle_filled(offset_x				, offset_y + Size_y	, Size_x, thickness, BLUE); //윗변
		DrawRectangle_filled(offset_x				, offset_y			, thickness, Size_y, BLUE); //좌변
		DrawRectangle_filled(offset_x + Size_x		, offset_y			, thickness, Size_y, BLUE); //우변

		if(*(KEY_ptr) != 0){
			key_value = *(KEY_ptr);
			switch (key_value) {
				case KEY0:		//KEY00
					enableVideo(); //capture the image and store it to the On-Chip Memory inside the FPGA
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY1:		//KEY01

					fixelData(offset_x, offset_y, Size_x, Size_y, fixeldata);
					Grayscale(fixeldata);
					printf("Case 3: Test IMG Optimization \r\n");

					cnn_cam_opt(ofmap_1, ifmap_1, fixeldata);
					Classifiacation_opt();	//Classifiacation
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY2:		//KEY02
					//fixelData(offset_x, offset_y, Size_x, Size_y, fixeldata);
					//print_fixelData(fixeldata);
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;

				case KEY3:		//KEY03
					MNIST_IMG_OPT();
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
			}
		}
	}
}


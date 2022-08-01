#include <stdint.h>
#include "video.h"

#define VIDEO_IN_BASE       0xFF203060
#define FPGA_ONCHIP_BASE    0xC8000000

#define BLACK 				0x0000
#define WHITE				0xFFFF
#define BLUE 				0x00FF
#define GREEN				0x0F00
#define RED 				0xF000

volatile int 	* Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
volatile short	* Video_Mem_ptr		= (short *) FPGA_ONCHIP_BASE;

/*Global var*/
int x, y;
int off_x = 50;
int off_y = 50;
//short fixeldata[28][28];

int x=0; //keep track of coordinates...x goes from 0 to 320
int y=0; //keep track of coordinates...y goes from 0 to 219
int sdram_index=0;
int sum=0;  //keep sum of color of pixels
int average=0;  //sum of color of pixels/# of pixels
int comp = 0; // keep track of bytes compressed
int decomp = 0;
	

void enableVideo(){
    *(Video_In_DMA_ptr + 3) = 0x4;
}

void captureVideo(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			*(Video_Mem_ptr + (y << 9) + x) = temp2; //capture the current image in the buffer and store it in the buffer
		}
	}	
}

void fixelData(int offset_x, int offset_y, int Size_x, int Size_y, float fixeldata[][28]){
	uint16_t data;
	uint8_t R, G, B;
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			if ((offset_x < x) && (x < offset_x + Size_x) && (offset_y < y) && (y < offset_y + Size_y)){
				//capture the current image in the buffer and store it in the buffer
				fixeldata[x - offset_x][y - offset_y] = temp2;
				*(Video_Mem_ptr + (y << 9) + x) = fixeldata[x - offset_x][y - offset_y];
			}
			else{
				*(Video_Mem_ptr + (y << 9) + x) = BLUE;
			}
		}
	}	
}

void print_fixelData(short fixeldata[][28]){
	int i, j;
	uint16_t data;
	uint8_t R, G, B;

	for (i = 0; i < 28; i++) {
		for (j = 0; j < 28; j++) {
			data = (uint16_t)fixeldata[i][j] & 0xF000;
			R = data >> 12;
			data = (uint16_t)fixeldata[i][j] & 0xF000;
			G = data >> 8;
			data = (uint16_t)fixeldata[i][j] & 0x00FF;
			B = data;
			printf("[%u %u %u],", R, G, B);
		}
		printf("\n");
	}
}

void Grayscale(float fixeldata[][28]){
	int i, j;
	float grayScale;
	uint16_t data;
	uint8_t R, G, B;
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 28; j++) {
			data = (uint16_t)fixeldata[i][j] & 0xF000;
			R = data >> 12;
			data = (uint16_t)fixeldata[i][j] & 0x0F00;
			G = data >> 8;
			data = (uint16_t)fixeldata[i][j] & 0x00FF;
			B = data;
			//grayScale = (R + G + B)/3;
			fixeldata[i][j] = (R+G+B);
			printf("%f," ,fixeldata[i][j]);
			//printf("[%u %u %u %f]," ,R,G,B,fixeldata[i][j]);
			//*(Video_Mem_ptr + (y << 9) + x) = grayScale;
		}
		printf("\n");
	}
}

void blackScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = BLACK;
		}
	}	
}

void whiteScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = WHITE;
		}
	}	
}

void RedScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = RED;
		}
	}	
}

void BlueScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = BLUE;
		}
	}	
}

void GreenScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = GREEN;
		}
	}	
}


void DrawRectangle_filled(int off_x, int off_y, int size_x, int size_y, int color){
	if(320 <= (off_x + size_x)) off_x = 320 - size_x;
	if(off_x <= 0 ) off_x = 0;
	if(240 <= (off_y + size_y)) off_y = 240 - size_y;
	if(off_y <= 0 ) off_y = 0;

	for (y = off_y; y < off_y + size_y; y++) {
		for (x = off_x; x < off_x + size_x; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = color;
		}
	}	
}


void DrawRectangle_empty(int off_x, int off_y, int size_x, int size_y, int thick, int color){
	if(320 <= (off_x + size_x)) off_x = 320 - size_x;
	if(off_x <= 0 ) off_x = 0;
	if(240 <= (off_y + size_y)) off_y = 240 - size_y;
	if(off_y <= 0 ) off_y = 0;

	for (y = off_y; y < off_y + size_y; y++) {
		for (x = off_x; x < off_x + size_x; x++) {
			if (( (y < off_y + thick) && (off_y + size_y - thick < y) ) && ( (x < off_x + thick) && (off_x + size_x - thick < x)) )
				*(Video_Mem_ptr + (y << 9) + x) = color;
		}
	}	
}

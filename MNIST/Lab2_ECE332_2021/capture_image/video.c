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
int bW=0; //0 if not b&w or has been already inverted backward 	1 if inverted forward
int off_x = 50;
int off_y = 50;
short fixeldata[320][240];
short (*fixel_ptr)[240] = fixeldata;

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

void fixelData(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			fixeldata[x][y] = *(Video_Mem_ptr + (y << 9) + x);
			*(Video_Mem_ptr + (y << 9) + x) = fixeldata[x][y]; //capture the current image in the buffer and store it in the buffer
		}
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
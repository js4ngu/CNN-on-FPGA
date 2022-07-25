// #include "address_map_arm.h"
#define KEY_BASE            0xFF200050
#define VIDEO_IN_BASE       0xFF203060
#define FPGA_ONCHIP_BASE    0xC8000000

#define BLACK 				0x0000
#define WHITE				0xFFFF
#define BLUE 				0x00FF
#define GREEN				0x0F00
#define RED 				0xF000

#define KEY0				0x1
#define KEY1				0x2
#define KEY2				0x4
#define KEY3				0x8

volatile int 	* KEY_ptr			= (int *) KEY_BASE;
volatile int 	* Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
volatile short	* Video_Mem_ptr		= (short *) FPGA_ONCHIP_BASE;

/*func*/
void captureVideo();
void fixelData();
void blackScreen();
void whiteScreen();
void RedScreen();
void BlueScreen();
void GreenScreen();

void DrawRectangle_filled(int off_x, int off_y, int size_x, int size_y, int color);
void DrawRectangle_empty(int off_x, int off_y, int size_x, int size_y, int thick, int color);

/*Global var*/
int x, y;
int bW=0; //0 if not b&w or has been already inverted backward 	1 if inverted forward
int key_value;
int off_x = 50;
int off_y = 50;
short fixeldata[320][240];
short (*fixel_ptr)[240] = fixeldata;

int main(void) {
	while(1){
		*(Video_In_DMA_ptr + 3) = 0x4;
		
		if(*(KEY_ptr) != 0){
			key_value = *(KEY_ptr);
			switch (key_value) {
				case KEY0:		//KEY00
					DrawRectangle_empty(100,100,80,80,10,RED);
					//while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
				case KEY1:		//KEY01
					*(Video_In_DMA_ptr + 3)	= 0x4;
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything;	
					break;
				case KEY2:		//KEY02
					*(Video_In_DMA_ptr + 3)	= 0x4;
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything;	
					break;
				case KEY3:		//KEY03
					fixelData();
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
			}
		}

	}
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
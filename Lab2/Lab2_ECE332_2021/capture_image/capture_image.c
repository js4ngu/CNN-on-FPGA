// #include "address_map_arm.h"
#define KEY_BASE              0xFF200050
#define VIDEO_IN_BASE         0xFF203060
#define FPGA_ONCHIP_BASE      0xC8000000	  
#define BLACK 				  0x0
#define WHITE				  0x6F
#define BLUE 				  0b0000000011110000 //0b00000011
#define GREEN				  0b0000111100000000 //GREEN
#define RED 				  0b1111000000000000 //0b00011100

/*Pointer*/
volatile int 	* KEY_ptr			= (int *) KEY_BASE;
volatile int 	* Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
volatile short	* Video_Mem_ptr		= (short *) FPGA_ONCHIP_BASE;

/*func*/
void captureVideo();
void blackScreen();
void whiteScreen();
void RedScreen();
void BlueScreen();
void GreenScreen();

/*Global var*/
int x, y;
int bW=0; //0 if not b&w or has been already inverted backward 	1 if inverted forward

int main(void) {
	while(1){
		*(Video_In_DMA_ptr + 3) = 0x4;
		if(*(KEY_ptr) != 0){
			//whiteScreen();
			//RedScreen();
			//BlueScreen();
			GreenScreen();
		}
	}
}

void captureVideo(){
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			*(Video_Mem_ptr + (y << 9) + x) = temp2; //capture the current image in the buffer and store it in the buffer
		}
	}	
}

void blackScreen(){
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = BLACK; //make every pixel black
		}
	}	
}

void whiteScreen(){
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = GREEN; //make every pixel black
		}
	}	
}

void RedScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = RED; //make every pixel black
		}
	}	
}

void BlueScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = BLUE; //make every pixel black
		}
	}	
}

void GreenScreen(){
	*(Video_In_DMA_ptr + 3) = 0x0;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			*(Video_Mem_ptr + (y << 9) + x) = GREEN; //make every pixel black
		}
	}	
}
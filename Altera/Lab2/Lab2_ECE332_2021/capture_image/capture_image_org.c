#include <stdio.h>
#include <stdbool.h>
#include "video.h"

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

volatile int * KEY_ptr = (int *) KEY_BASE;
int key_value;

int main(void) {
	while(1){
		enableVideo();
		if(*(KEY_ptr) != 0){
			key_value = *(KEY_ptr);
			switch (key_value) {
				case KEY0:		//KEY00
					printf("Key 0\n");
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
	
				case KEY1:		//KEY01
					DrawRectangle_empty(100,100,80,80,10,RED);
					break;

				case KEY2:		//KEY02
					DrawRectangle_filled(50,50,200,200,BLUE);
					break;

				case KEY3:		//KEY03
					fixelData();
					while (*KEY_ptr != 0);	//while the key is pressed down dont do anything
					break;
			}
		}
	}
}
#ifndef VIDEO_H
#define VIDEO_H

void captureVideo();
void fixelData();
void blackScreen();
void whiteScreen();
void RedScreen();
void BlueScreen();
void GreenScreen();
void DrawRectangle_filled(int off_x, int off_y, int size_x, int size_y, int color);
void DrawRectangle_empty(int off_x, int off_y, int size_x, int size_y, int thick, int color);

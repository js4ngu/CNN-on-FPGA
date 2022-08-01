#ifndef _CNN_H
#define _CNN_H

void cnn_img_opt(short *ofmap, short *ifmap);
void cnn_cam_opt(short *ofmap, short *ifmap, float fixeldata[][28]);

void MNIST_IMG_OPT();
//void MNIST_camera(short fixeldata[][28]);

void Classifiacation_opt();
#endif
#include "CNN.h"
#include <stdbool.h>

int main(){
	int flag = 0;   
	if (flag == 0) {
		floatMNIST();
	}
	else {
		unfloatMNIST();
	}
	measurePerformace(1);
	return 0;
}

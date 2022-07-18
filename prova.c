#include <stdio.h>

int main(){
	int i = 0;
	while(1){
		printf("iterazione %d\n", i++);
		for(int c=0; c < 100000000; c++);
	}
}

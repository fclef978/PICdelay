//Created by 978//
//2016.9/12(Mon)//
#include<stdio.h>

#define L_OFFSET 5
#define PERIOD 5
#define BIT_WIDTH 255


int make_wait(int cycle);


int main(void){
	int cycle = 0, loop = 0, result = 0, surplus = 0, tmp = BIT_WIDTH, tmp2 = 0, i;
	
	puts("please input time[us]");
	scanf("%d", &cycle);
	cycle *= PERIOD;
	
	for(loop = BIT_WIDTH; loop > 0; loop--){
		result = (cycle - L_OFFSET) / loop - 3;
		surplus = (cycle - L_OFFSET) % loop;
		if(tmp > surplus && result < 30 && result > 0){
			tmp = surplus;
			tmp2 = loop;
		}
	}
	
	result = (cycle - L_OFFSET) / tmp2 - 3;
	surplus = tmp;
	
	printf("all cycle = %d\nloop = %d\ncycle = %d\nsurplus = %d\n", cycle, tmp2, result, surplus);
	
	printf("DELAY\tMOVLW\t%d\n", tmp2);
	printf("\tMOVWF\tDR\n");
	printf("LOOP\n");
	make_wait(result);
	printf("\tDECFSZ\tDR,1\n");
	printf("\tGOTO\tLOOP\n");
	make_wait(surplus);
	printf("\tRETURN\n");
	return 0;
}

int make_wait(int cycle){
	for(cycle++ ; cycle > 1; cycle--){
		if(cycle > 2){
			printf("\tGOTO\t$+1\n");
			cycle--;
		}else
			printf("\tNOP\n");
	}
	return 0;
}

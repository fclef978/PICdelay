//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"struct.c"


#define L_OFFSET 5
#define BIT_WIDTH 255


int make_wait(int cycle);
int get_cycle(void);
DelayElement evaluate_line(int cycle);


int main(void){
	int tmpCycle = get_cycle();

	DelayElement delay = evaluate_line(tmpCycle);

	printf("all cycle = %d\nloop = %d\ncycle = %d\nsurplus = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);

	printf("DELAY\n\tMOVLW\t%d\n", delay.loop);
	printf("\tMOVWF\tDR\n");
	printf("LOOP\n");
	make_wait(delay.intCycle);
	printf("\tDECFSZ\tDR,1\n");
	printf("\tGOTO\tLOOP\n");
	make_wait(delay.surplus);
	printf("\tRETURN\n");
	return 0;
}

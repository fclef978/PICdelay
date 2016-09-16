//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"prot.h"
#include"def.h"


int get_cycle(void){
	int cycle = 0;
	do{
		printf("please input time(%d~%d[us])\n==>", T_MIN, T_MAX);
		scanf("%d", &cycle);
	}while(cycle < T_MIN || T_MAX < cycle);
	return cycle * PERIOD;
}


DelayElement evaluate_line(int cycle){
	int tmpComp = BIT_WIDTH, tmpLoop = 0;

	DelayElement delay = {cycle, 0, 0, 0};

	for(delay.loop = BIT_WIDTH; delay.loop > 0; delay.loop--){
		delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;
		delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;
		int tmpLine = 5 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2);
		if(tmpComp > tmpLine && delay.intCycle > 0){
			tmpComp = tmpLine;
			tmpLoop = delay.loop;
		}
	}

	delay.loop = tmpLoop;
	delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;
	delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;

	return delay;
}


int make_wait(int cycle){
	if(cycle % 2 == 1)
		printf("\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)
		printf("\tGOTO\t$+1\n");
	return 0;
}


void disp_result(DelayElement delay){
	printf("all cycle = %d\nloop = %d\ncycle = %d\nsurplus = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);

	printf("DELAY\n\tMOVLW\t%d\n", delay.loop);
	printf("\tMOVWF\tDR\n");
	printf("LOOP\n");
	make_wait(delay.intCycle);
	printf("\tDECFSZ\tDR,1\n");
	printf("\tGOTO\tLOOP\n");
	make_wait(delay.surplus);
	printf("\tRETURN\n");
}

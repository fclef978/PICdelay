//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include<string.h>
#include"PICdelay.h"


static char *make_wait(int cycle, char tmp[256]);


int get_cycle(double period){
	int cycle = 0;
	do{
		printf("please input time(%d~%d[us])\n==>", T_MIN, T_MAX);
		scanf("%d", &cycle);
	}while(cycle < T_MIN || T_MAX < cycle);
	return cycle / (period * 1000000);
}


DelayElement evaluate_line(int cycle){
	int tmpComp = BIT_WIDTH, tmpLoop = 0;

	DelayElement delay = {cycle, 0, 0, 0};

	for(delay.loop = 1; delay.loop < BIT_WIDTH && (delay.cycle - L_OFFSET) > delay.loop; delay.loop++){
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


void disp_result(DelayElement delay){
	char tmp[256];
	printf("all cycle = %d\nloop = %d\ncycle = %d\nsurplus = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("%dLines\n", 5 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2));

	printf("%s\n\tMOVLW\t%d\n", setting.sl, delay.loop);
	printf("\tMOVWF\t%s\n", setting.rn);
	printf("%s\n", setting.ll);
	printf("%s", make_wait(delay.intCycle, tmp));
	printf("\tDECFSZ\t%s,1\n", setting.rn);
	printf("\tGOTO\t%s\n", setting.ll);
	printf("%s", make_wait(delay.surplus, tmp));
	printf("\tRETURN\n");
}


static char *make_wait(int cycle, char tmp[256]){
	memset(tmp, '\0', strlen(tmp));
	if(cycle % 2 == 1)
		strcat(tmp, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)
		strcat(tmp, "\tGOTO\t$+1\n");
	return tmp;
}

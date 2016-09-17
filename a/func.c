//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include<string.h>
#include"PICdelay.h"


#define T_MIN 2
#define T_MAX 2000
#define L_OFFSET 5
#define BIT_WIDTH 256


static char *make_wait(int cycle, char tmp[256]);


int get_cycle(double period){
	int cycle = 0;
	do{
		printf("ウェイトしたい時間を%d~%d[us]の間で入力してください\n==>", T_MIN, T_MAX);
		scanf("%d", &cycle);
	}while(cycle < T_MIN || T_MAX < cycle);
	printf("%d[sec]で計算します\n", cycle);
	return cycle / (period * 1000000);
}


DelayElement evaluate_line(int cycle){
	int tmpComp = BIT_WIDTH, tmpLoop = 0;

	puts("計算中");

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


char *make_result(DelayElement delay, char result[]){
	char tmp[256], tmp2[256];
	memset(tmp, '\0', strlen(tmp));
	printf("全体必要サイクル数 = %d\nループ回数 = %d\n内部サイクル数 = %d\n余り = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("コードの行数 = %d\n", 7 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2));

	sprintf(tmp, "%s\n\tMOVLW\t%d\n", setting.sl, delay.loop);
	strcat(result, tmp);
	sprintf(tmp, "\tMOVWF\t%s\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "%s\n", setting.ll);
	strcat(result, tmp);
	sprintf(tmp, "%s", make_wait(delay.intCycle, tmp2));
	strcat(result, tmp);
	sprintf(tmp, "\tDECFSZ\t%s,1\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "\tGOTO\t%s\n", setting.ll);
	strcat(result, tmp);
	sprintf(tmp, "%s", make_wait(delay.surplus, tmp2));
	strcat(result, tmp);
	sprintf(tmp, "\tRETURN\n");
	strcat(result, tmp);
	return result;
}


static char *make_wait(int cycle, char str[256]){
	memset(str, '\0', strlen(str));
	if(cycle % 2 == 1)
		strcat(str, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)
		strcat(str, "\tGOTO\t$+1\n");
	return str;
}

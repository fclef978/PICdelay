//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"PICdelay.h"

#define SC 5000000
#define SL "DELAY"
#define RN "COUNTER"
#define LL "D_LOOP"


static FILE *init_setting(void);


void import_setting(void){
	char s_tmp[256], tmp[64];

	FILE *fp;
	if((fp = fopen("setting.ini", "r")) == NULL){
		fp = init_setting();
	}

	fscanf(fp, "%s\r\n", s_tmp);
	fscanf(fp, "SystemClock(Hz)=%s\r\n", tmp);
	fscanf(fp, "SubroutineLabel=%s\r\n", &setting.sl);
	fscanf(fp, "RegisterName=%s\r\n", &setting.rn);
	fscanf(fp, "LoopLabel=%s\r\n", &setting.ll);

	setting.period = 1 / (double)atoi(tmp);

	printf("%s\n", s_tmp);
	printf("%lf\n%s\n%s\n%s\n", (double)atoi(tmp), setting.sl, setting.rn, setting.ll);
}


static FILE *init_setting(void){
	FILE *fp = fopen("setting.ini", "w+");
	fprintf(fp, "[settings]\r\n");
	fprintf(fp, "SystemClock(Hz)=%d\r\n", SC);
	fprintf(fp, "SubroutineLabel=%s\r\n", SL);
	fprintf(fp, "RegisterName=%s\r\n", RN);
	fprintf(fp, "LoopLabel=%s\r\n", LL);
	rewind(fp);
	return fp;
}

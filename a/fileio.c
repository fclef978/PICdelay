//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include<stdlib.h>
#include"PICdelay.h"


#define SC 5000000
#define SL "DELAY"
#define RN "COUNTER"
#define LL "D_LOOP"


static FILE *init_setting(void);


void import_setting(void){
	char s_tmp[256], tmp[64];

	puts("設定ファイルを読み込みます");
	FILE *fp;
	if((fp = fopen("setting.ini", "r")) == NULL){
		puts("設定ファイル\"setting.ini\"が見つからないので生成します");
		fp = init_setting();
		puts("設定ファイル生成完了");
	}

	fscanf(fp, "%s\r\n", s_tmp);
	fscanf(fp, "SystemClock(Hz)=%s\r\n", tmp);
	fscanf(fp, "SubroutineLabel=%s\r\n", &setting.sl);
	fscanf(fp, "RegisterName=%s\r\n", &setting.rn);
	fscanf(fp, "LoopLabel=%s\r\n", &setting.ll);

	puts("設定ファイル\"setting.ini\"の読み込み完了");

	setting.period = 1 / (double)atoi(tmp);

	printf("クロック周期%10.8lf[sec]\n", setting.period);
}


static FILE *init_setting(void){
	FILE *fp = fopen("setting.ini", "w+");
	fprintf(fp, "[settings]\n");
	fprintf(fp, "SystemClock(Hz)=%d\n", SC);
	fprintf(fp, "SubroutineLabel=%s\n", SL);
	fprintf(fp, "RegisterName=%s\n", RN);
	fprintf(fp, "LoopLabel=%s\n", LL);
	rewind(fp);
	return fp;
}


void output(char *str){
	FILE *fp = fopen("result.asm", "w");
	fprintf(fp, str);
	fclose(fp);
}

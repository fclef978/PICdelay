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

	puts("�ݒ�t�@�C����ǂݍ��݂܂�");
	FILE *fp;
	if((fp = fopen("setting.ini", "r")) == NULL){
		puts("�ݒ�t�@�C��\"setting.ini\"��������Ȃ��̂Ő������܂�");
		fp = init_setting();
		puts("�ݒ�t�@�C����������");
	}

	fscanf(fp, "%s\r\n", s_tmp);
	fscanf(fp, "SystemClock(Hz)=%s\r\n", tmp);
	fscanf(fp, "SubroutineLabel=%s\r\n", &setting.sl);
	fscanf(fp, "RegisterName=%s\r\n", &setting.rn);
	fscanf(fp, "LoopLabel=%s\r\n", &setting.ll);

	puts("�ݒ�t�@�C��\"setting.ini\"�̓ǂݍ��݊���");

	setting.period = 1 / (double)atoi(tmp);

	printf("�N���b�N����%10.8lf[sec]\n", setting.period);
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

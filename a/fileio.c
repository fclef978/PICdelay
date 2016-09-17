//=============================================================================
// Contents   : PICのDELAYサブルーチンを生成する
//              ファイル入出力系関数置き場 fileio.c
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : バグの山
//=============================================================================


/*
 *	プリプロセッサ命令
 */
#include<stdio.h>
#include<stdlib.h>
#include"PICdelay.h"


/*
 *	マクロ
 */
#define SC 5000000//システムクロック周波数
#define SL "DELAY"//サブルーチンのラベル
#define RN "COUNTER"//レジスタの名前
#define LL "D_LOOP"//ディレイ内ループポイントのラベル


/*
 *	関数プロトタイプ宣言
 */
static FILE *init_setting(void);//設定ファイルを初期化


/*
 *	設定ファイルから読み込み
 */
void import_setting(void){
	char s_tmp[256], tmp[64];

	puts("設定ファイルを読み込みます");
	FILE *fp;
	if((fp = fopen("setting.ini", "r")) == NULL){//いつもの
		puts("設定ファイル\"setting.ini\"が見つからないので生成します");
		fp = init_setting();//設定ファイル初期化
		puts("設定ファイル生成完了");
	}

	//スキャン
	fscanf(fp, "%s\r\n", s_tmp);
	fscanf(fp, "SystemClock(Hz)=%s\r\n", tmp);
	fscanf(fp, "SubroutineLabel=%s\r\n", &setting.sl);
	fscanf(fp, "RegisterName=%s\r\n", &setting.rn);
	fscanf(fp, "LoopLabel=%s\r\n", &setting.ll);

	puts("設定ファイル\"setting.ini\"の読み込み完了");

	//システムクロック周波数から周期を計算
	setting.period = 1 / (double)atoi(tmp);

	printf("クロック周期%10.8lf[sec]\n", setting.period);
}


/*
 *	設定ファイル初期化
 */
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


/*
 *	外部ファイルにソースコードを出力
 */
void output(char *str){
	FILE *fp = fopen("result.asm", "w");
	fprintf(fp, str);
	fclose(fp);
}

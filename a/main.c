//=============================================================================
// Contents   : PICのDELAYサブルーチンを生成する
//              メインプログラム main.c
// Author     : fclef978
// LastUpdate : 2016/09/18
// Since      : 2016/09/09
// Comment    : さっぱりしていて、それでいてべたつかない。すっきりしたファイルだ。
//=============================================================================


/*
 *	プリプロセッサ命令
 */
#include<stdio.h>
#include"PICdelay.h"


/*
 *	グローバル変数
 */
Setting setting;//設定用の構造体


/*
 *	メイン関数
 */
int main(void){
	int selector = 0;
	puts("PICdelay PICのDELAYサブルーチン生成機へようこそ");
	import_setting();//設定ファイルから読み込み
	//メインループ**************************************************************
	do{
		printf("\n0で終了、1で単ループモード、2で二重ループモード、3で三重ループモード\n==>");
		scanf("%d", &selector);

		//単ループモード********************************************************
		if(selector == 1){
			DelayElement delay;
			delay.cycle = get_cycle(1000, 2);
			evaluate_line(&delay);//サイクル数の取得、行数の一番少ない組み合わせを探す

			char result[4096] = {""};
			make_result(delay, result);//ソースコード生成
			printf("////////////////\n以下よりコード\n////////////////\n\n");
			printf("%s", result);//ソースコード表示

			output(result);//外部ファイルにソースコードを出力

			puts("\n終了しました");
		}
		//二重ループモード******************************************************
		else if(selector == 2){
			DelayElement delay[2];
			delay[0].cycle = get_cycle(500000, 100);	//サイクル数の取得

			evaluate_line_double(delay);//サイクル数の取得、行数の一番少ない組み合わせを探す

			char result[4096] = {""};
			make_result_double(delay, result);//ソースコード生成
			printf("////////////////\n以下よりコード\n////////////////\n\n");
			printf("%s", result);//ソースコード表示

			output(result);//外部ファイルにソースコードを出力

			puts("\n終了しました");
		}
		//三重ループモード******************************************************
		else if(selector == 3){
			DelayElement delay[3];
			delay[0].cycle = get_cycle(100000000, 1000);	//サイクル数の取得

			evaluate_line_triple(delay);//サイクル数の取得、行数の一番少ない組み合わせを探す

			char result[4096] = {""};
			make_result_triple(delay, result);//ソースコード生成
			printf("////////////////\n以下よりコード\n////////////////\n\n");
			printf("%s", result);//ソースコード表示

			output(result);//外部ファイルにソースコードを出力

			puts("\n終了しました");
		}
	}while(selector != 0);

	return 0;//正常終了
}

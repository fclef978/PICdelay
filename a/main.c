//=============================================================================
// Contents   : PICのDELAYサブルーチンを生成する
//              メインプログラム main.c
// Author     : fclef978
// LastUpdate : 2016/09/17
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
	puts("PICdelay PICのDELAYサブルーチン生成機へようこそ");
	import_setting();//設定ファイルから読み込み

	int cycle = get_cycle();//サイクル数の取得

	DelayElement delay = evaluate_line(cycle);//行数の一番少ない組み合わせを探す

	char result[1024] = {""};
	make_result(delay, result);//ソースコード生成
	printf("////////////////\n以下よりコード\n////////////////\n\n");
	printf("%s", result);//ソースコード表示

	output(result);//外部ファイルにソースコードを出力

	puts("\n終了します");
	int tmp = 0;//適当に作った入力待ち
	scanf("%d", &tmp);

	return 0;//正常終了
}

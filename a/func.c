//=============================================================================
// Contents   : PICのDELAYサブルーチンを生成する
//              関数置き場 func.c
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : まるでスパゲッティソースみたいだあ(直喩)
//=============================================================================


/*
 *	プリプロセッサ命令
 */
#include<stdio.h>
#include<string.h>
#include"PICdelay.h"


/*
 *	マクロ
 */
#define T_MIN 2//ウェイト時間の下限
#define T_MAX 2000//ウェイト時間の上限
#define L_OFFSET 5//ループ計算時のオフセット
#define BIT_WIDTH 256//プロセッサのビット幅


/*
 *	関数プロトタイプ宣言
 */
static char *make_wait(int cycle, char tmp[256]);//ループ内サイクルとか余りのサイクルを生成する


/*
 *	サイクル数の取得
 */
int get_cycle(void){
	int cycle = 0;
	do{//時間取得
		printf("ウェイトしたい時間を%d~%d[us]の間で入力してください\n==>", T_MIN, T_MAX);
		scanf("%d", &cycle);
	}while(cycle < T_MIN || T_MAX < cycle);
	printf("%d[sec]で計算します\n", cycle);//確認
	return cycle / (setting.period * 1000000);//クロック周期を計算してリターン
}


/*
 *	行数の一番少ない組み合わせを探す
 */
DelayElement evaluate_line(int cycle){
	int tmpComp = BIT_WIDTH, tmpLoop = 0;

	puts("計算中");

	DelayElement delay = {cycle, 0, 0, 0};

	for(delay.loop = 1; delay.loop < BIT_WIDTH && (delay.cycle - L_OFFSET) > delay.loop; delay.loop++){//無意味な計算は省く
		delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;//内部サイクル計算
		delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;//余り計算
		int tmpLine = 5 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2);//行数計算
		if(tmpComp > tmpLine && delay.intCycle > 0){//判定
			tmpComp = tmpLine;
			tmpLoop = delay.loop;
		}
	}

	delay.loop = tmpLoop;//値を戻す
	delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;
	delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;

	return delay;
}


/*
 *	ソースコード生成
 */
char *make_result(DelayElement delay, char result[]){
	char tmp[256], tmp2[256];
	memset(tmp, '\0', strlen(tmp));
	//要素表示
	printf("全体必要サイクル数 = %d\nループ回数 = %d\n内部サイクル数 = %d\n余り = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("コードの行数 = %d\n", 7 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2));

	//生成と結合を繰り返す
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


/*
 *	ループ内サイクルとか余りのサイクルを生成する
 */
static char *make_wait(int cycle, char str[256]){
	memset(str, '\0', strlen(str));
	if(cycle % 2 == 1)//奇数か判定
		strcat(str, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)//残りをGOTO$+1に
		strcat(str, "\tGOTO\t$+1\n");
	return str;
}

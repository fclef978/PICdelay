//=============================================================================
// Contents		: PICアセンブラのDELAYサブルーチンを生成する
//				: 関数置き場 func.c
// Author		: fclef978
// LastUpdate	: 2016/09/25
// Since		: 2016/09/09
// Comment		: まるでスパゲッティソースみたいだあ(直喩)
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
#define L_OFFSET 5//ループ計算時のオフセット
#define BIT_WIDTH 256//プロセッサのビット幅
#define OFFSET_D 4//内側ループと外側ループの差


/*
 *	関数プロトタイプ宣言
 */
static char *make_wait(int cycle, char tmp[]);//ループ内サイクルとか余りのサイクルを生成する
static int calc_line(DelayElement delay);//行数計算1
static int calc_line_double(DelayElement delay[]);//行数計算2
static int calc_line_triple(DelayElement delay[]);//行数計算3


/*
 *	サイクル数の取得
 */
int get_cycle(int max, int min){
	int cycle = 0;
	do{//時間取得
		printf("ウェイトしたい時間を%d~%d[us]の間で入力してください\n==>", min, max);
		scanf("%d", &cycle);
	}while(cycle < min || max < cycle);
	printf("%d[us]で計算します\n", cycle);//確認
	return (double)cycle / (setting.period * 1000000);//サイクル数を計算してリターン
}


/*
 *	行数の一番少ない組み合わせを探す
 */
 void evaluate_line(DelayElement *delay){
 	int compLine = delay->cycle, tmpLine, tmpLoop;
 	DelayElement tmp = {delay->cycle, 0, 0, 0};

 	for(tmp.loop = 1; tmp.loop < BIT_WIDTH; tmp.loop++){
 		tmp.intCycle = (tmp.cycle - L_OFFSET) / tmp.loop - 3;
 		if(tmp.intCycle < 0) break;
 		tmp.surplus = (tmp.cycle - L_OFFSET) % tmp.loop;
 		tmpLine = calc_line(tmp);
 		if(compLine > tmpLine){//行数比較
 			compLine = tmpLine;
 			tmpLoop = tmp.loop;
 		}
 	}
 	delay->loop = tmpLoop;
 	delay->intCycle = (delay->cycle - L_OFFSET) / delay->loop - 3;
 	delay->surplus = (delay->cycle - L_OFFSET) % delay->loop;
 }


/*
 *	二重ループ版の行数の一番少ない組み合わせを探す
 */
 void evaluate_line_double(DelayElement delay[]){
 	int compLine = delay[0].cycle, tmpLine, tmpLoop[2];
 	DelayElement tmp[2];
 	tmp[0].cycle = delay[0].cycle;

 	for(tmp[0].loop = 1; tmp[0].loop < BIT_WIDTH; tmp[0].loop++){
 		tmp[0].intCycle = (tmp[0].cycle - L_OFFSET) / tmp[0].loop - 3;
 		if(tmp[0].intCycle < 10) break;
 		tmp[0].surplus = (tmp[0].cycle - L_OFFSET) % tmp[0].loop;
 		tmp[1].cycle = tmp[0].intCycle + OFFSET_D;//内側と外側のオフセットの差
 		evaluate_line(&tmp[1]);
 		tmpLine = calc_line_double(tmp);
 		if(compLine > tmpLine){
 			compLine = tmpLine;
 			tmpLoop[0] = tmp[0].loop;
			tmpLoop[1] = tmp[1].loop;
 		}
 	}
 	delay[0].loop = tmpLoop[0];
 	delay[0].intCycle = (delay[0].cycle - L_OFFSET) / delay[0].loop - 3;
 	delay[0].surplus = (delay[0].cycle - L_OFFSET) % delay[0].loop;
 	delay[1].cycle = delay[0].intCycle;
	int tmpCycle = delay[0].intCycle + OFFSET_D;
 	delay[1].loop = tmpLoop[1];
 	delay[1].intCycle = (tmpCycle - L_OFFSET) / delay[1].loop - 3;
 	delay[1].surplus = (tmpCycle - L_OFFSET) % delay[1].loop;
 }


/*
 *	三重ループ版の行数の一番少ない組み合わせを探す
 */
void evaluate_line_triple(DelayElement delay[]){
	int compLine = delay[0].cycle, tmpLine, tmpLoop[3], i;
 	DelayElement tmp[3], tmp2[2];
 	tmp[0].cycle = delay[0].cycle;

 	for(tmp[0].loop = 1; tmp[0].loop < BIT_WIDTH; tmp[0].loop++){
 		tmp[0].intCycle = (tmp[0].cycle - L_OFFSET) / tmp[0].loop - 3;
 		if(tmp[0].intCycle < 10) break;
 		tmp[0].surplus = (tmp[0].cycle - L_OFFSET) % tmp[0].loop;
 		tmp2[0].cycle = tmp[0].intCycle + OFFSET_D;
 		evaluate_line_double(tmp2);
		tmp[1] = tmp2[0];
		tmp[2] = tmp2[1];
 		tmpLine = calc_line_triple(tmp);
 		if(compLine > tmpLine){
 			compLine = tmpLine;
 			tmpLoop[0] = tmp[0].loop;
			tmpLoop[1] = tmp[1].loop;
			tmpLoop[2] = tmp[2].loop;
 		}
 	}
 	delay[0].loop = tmpLoop[0];
 	delay[0].intCycle = (delay[0].cycle - L_OFFSET) / delay[0].loop - 3;
 	delay[0].surplus = (delay[0].cycle - L_OFFSET) % delay[0].loop;
	for(i = 1; i < 3; i++){
 		delay[i].cycle = delay[i - 1].intCycle;
		int tmpCycle = delay[i - 1].intCycle + OFFSET_D;
 		delay[i].loop = tmpLoop[i];
 		delay[i].intCycle = (tmpCycle - L_OFFSET) / delay[i].loop - 3;
 		delay[i].surplus = (tmpCycle - L_OFFSET) % delay[i].loop;
	}
}



/*
 *	行数計算
 */
static int calc_line(DelayElement delay){//行数計算
	return 7 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2);
}


/*
 *	二重ループ行数計算
 */
static int calc_line_double(DelayElement delay[]){//行数計算
	return calc_line(delay[1]) + (delay[0].surplus / 2 + delay[0].surplus % 2) + 5;
}


/*
 *	三重ループ行数計算
 */
static int calc_line_triple(DelayElement delay[]){//行数計算
	DelayElement tmp[2];
	tmp[0] = delay[1];
	tmp[1] = delay[2];
	return calc_line_double(tmp) + (delay[0].surplus / 2 + delay[0].surplus % 2) + 5;
}


/*
 *	ソースコード生成
 */
char *make_result(DelayElement delay, char result[]){
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//要素表示
	printf("全体必要サイクル数 = %d\nループ回数 = %d\n内部サイクル数 = %d\n余り = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("コードの行数 = %d\n",calc_line(delay));

	//生成と結合を繰り返す
	sprintf(tmp, "%s\n\tMOVLW\t%d\n", setting.sl, delay.loop);
	strcat(result, tmp);
	sprintf(tmp, "\tMOVWF\t%s\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "%s\n", setting.ll);
	strcat(result, tmp);
	strcat(result, make_wait(delay.intCycle, tmp2));
	sprintf(tmp, "\tDECFSZ\t%s,1\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "\tGOTO\t%s\n", setting.ll);
	strcat(result, tmp);
	strcat(result, make_wait(delay.surplus, tmp2));
	sprintf(tmp, "\tRETURN\n");
	strcat(result, tmp);
	return result;
}


/*
 *	ソースコード生成
 */
char *make_result_double(DelayElement delay[], char result[]){
	int i;
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//要素表示
	for(i = 0; i < 2; i++)
		printf("ループ%d\n全体必要サイクル数 = %d\nループ回数 = %d\n内部サイクル数 = %d\n余り = %d\n",
		i + 1, delay[i].cycle, delay[i].loop, delay[i].intCycle, delay[i].surplus);
	printf("コードの行数 = %d\n", calc_line_double(delay));

	//生成と結合を繰り返す
	sprintf(tmp, "%s\n", setting.sl);
	strcat(result, tmp);
	for(i = 1; i <= 2; i++){
		sprintf(tmp, "\tMOVLW\t%d\n", delay[i - 1].loop);
		strcat(result, tmp);
		sprintf(tmp, "\tMOVWF\t%s%d\n", setting.rn, i);
		strcat(result, tmp);
		sprintf(tmp, "%s%d\n", setting.ll, i);
		strcat(result, tmp);
	}
	strcat(result, make_wait(delay[1].intCycle, tmp2));
	for(i = 2; i >= 1; i--){
		sprintf(tmp, "\tDECFSZ\t%s%d,1\n", setting.rn, i);
		strcat(result, tmp);
		sprintf(tmp, "\tGOTO\t%s%d\n", setting.ll, i);
		strcat(result, tmp);
		strcat(result, make_wait(delay[i - 1].surplus, tmp2));
	}
	sprintf(tmp, "\tRETURN\n");
	strcat(result, tmp);
	return result;
}


/*
 *	ソースコード生成
 */
char *make_result_triple(DelayElement delay[], char result[]){
	int i;
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//要素表示
	for(i = 0; i < 3; i++)
		printf("ループ%d\n全体必要サイクル数 = %d\nループ回数 = %d\n内部サイクル数 = %d\n余り = %d\n",
		i + 1, delay[i].cycle, delay[i].loop, delay[i].intCycle, delay[i].surplus);
	printf("コードの行数 = %d\n", calc_line_triple(delay));

	//生成と結合を繰り返す
	sprintf(tmp, "%s\n", setting.sl);
	strcat(result, tmp);
	for(i = 1; i <= 3; i++){
		sprintf(tmp, "\tMOVLW\t%d\n", delay[i - 1].loop);
		strcat(result, tmp);
		sprintf(tmp, "\tMOVWF\t%s%d\n", setting.rn, i);
		strcat(result, tmp);
		sprintf(tmp, "%s%d\n", setting.ll, i);
		strcat(result, tmp);
	}
	strcat(result, make_wait(delay[2].intCycle, tmp2));
	for(i = 3; i >= 1; i--){
		sprintf(tmp, "\tDECFSZ\t%s%d,1\n", setting.rn, i);
		strcat(result, tmp);
		sprintf(tmp, "\tGOTO\t%s%d\n", setting.ll, i);
		strcat(result, tmp);
		strcat(result, make_wait(delay[i - 1].surplus, tmp2));
	}
	sprintf(tmp, "\tRETURN\n");
	strcat(result, tmp);
	return result;
}


/*
 *	ループ内サイクルとか余りのサイクルを生成する
 */
static char *make_wait(int cycle, char str[]){
	memset(str, '\0', strlen(str));
	if(cycle % 2 == 1)//奇数か判定
		strcat(str, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)//残りをGOTO$+1に
		strcat(str, "\tGOTO\t$+1\n");
	return str;
}

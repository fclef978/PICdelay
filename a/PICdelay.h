//=============================================================================
// Contents   : PICのDELAYサブルーチンを生成する
//              ヘッダ PICdelay.h
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : 無理やりまとめスギィ！
//=============================================================================


/*
 *	構造体
 */
typedef struct{
	int cycle;//総サイクル数
	int loop;//ループ数
	int intCycle;//ループ内サイクル数
	int surplus;//余り
}DelayElement;//ディレイの要素

typedef struct{
	double period;//クロック周期
	char sl[64];//サブルーチンのラベル
	char rn[64];//レジスタの名前
	char ll[64];//ディレイ内ループポイントのラベル
}Setting;//設定


/*
 *	グローバル変数
 */
extern Setting setting;//設定用の構造体


/*
 *	関数プロトタイプ宣言
 */
//func.c
int get_cycle(void);//サイクル数の取得
DelayElement evaluate_line(int cycle);//行数の一番少ない組み合わせを探す
char *make_result(DelayElement delay, char result[]);//ソースコード生成

//fileio.c
void import_setting(void);//設定ファイルから読み込み
void output(char *str);//外部ファイルにソースコードを出力

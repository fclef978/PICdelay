//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"PICdelay.h"


Setting setting;


int main(void){
	puts("PICdelay PICのDELAYサブルーチン生成機へようこそ");
	import_setting();

	int tmpCycle = get_cycle(setting.period);

	DelayElement delay = evaluate_line(tmpCycle);

	char result[1024] = {""};
	make_result(delay, result);
	printf("////////////////\n以下よりコード\n////////////////\n\n");
	printf("%s", result);

	output(result);

	puts("\n終了します");
	int tmp = 0;
	scanf("%d", &tmp);

	return 0;
}

//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"PICdelay.h"


Setting setting;


int main(void){
	puts("PICdelay PIC��DELAY�T�u���[�`�������@�ւ悤����");
	import_setting();

	int tmpCycle = get_cycle(setting.period);

	DelayElement delay = evaluate_line(tmpCycle);

	char result[1024] = {""};
	make_result(delay, result);
	printf("////////////////\n�ȉ����R�[�h\n////////////////\n\n");
	printf("%s", result);

	output(result);

	puts("\n�I�����܂�");
	int tmp = 0;
	scanf("%d", &tmp);

	return 0;
}

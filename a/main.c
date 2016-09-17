//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"PICdelay.h"


Setting setting;


int main(void){
	import_setting();

	int tmpCycle = get_cycle(setting.period);

	DelayElement delay = evaluate_line(tmpCycle);

	disp_result(delay);

	return 0;
}

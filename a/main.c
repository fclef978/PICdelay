//Created by 978//
//2016.9/17(Sat)//
#include<stdio.h>
#include"Prot.h"


int main(void){
	int tmpCycle = get_cycle();

	DelayElement delay = evaluate_line(tmpCycle);

	disp_result(delay);

	return 0;
}

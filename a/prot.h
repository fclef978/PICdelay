//Created by 978//
//2016.9/17(Sat)//
typedef struct{
	int cycle;
	int loop;
	int intCycle;
	int surplus;
}DelayElement;


int get_cycle(void);
DelayElement evaluate_line(int cycle);
int make_wait(int cycle);
void disp_result(DelayElement delay);

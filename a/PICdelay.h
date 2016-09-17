//Created by 978//
//2016.9/17(Sat)//
#define T_MIN 2
#define T_MAX 10000
#define L_OFFSET 5
#define BIT_WIDTH 256


typedef struct{
	int cycle;
	int loop;
	int intCycle;
	int surplus;
}DelayElement;

typedef struct{
	double period;
	char sl[64];
	char rn[64];
	char ll[64];
}Setting;


extern Setting setting;


int get_cycle(double period);
DelayElement evaluate_line(int cycle);
void disp_result(DelayElement delay);

void import_setting(void);

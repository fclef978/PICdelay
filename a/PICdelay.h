//Created by 978//
//2016.9/17(Sat)//
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
char *make_result(DelayElement delay, char result[]);

void import_setting(void);
void output(char *str);

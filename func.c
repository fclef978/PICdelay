//=============================================================================
// Contents		: PIC�A�Z���u����DELAY�T�u���[�`���𐶐�����
//				: �֐��u���� func.c
// Author		: fclef978
// LastUpdate	: 2016/09/25
// Since		: 2016/09/09
// Comment		: �܂�ŃX�p�Q�b�e�B�\�[�X�݂�������(���g)
//=============================================================================


/*
 *	�v���v���Z�b�T����
 */
#include<stdio.h>
#include<string.h>
#include"PICdelay.h"


/*
 *	�}�N��
 */
#define L_OFFSET 5//���[�v�v�Z���̃I�t�Z�b�g
#define BIT_WIDTH 256//�v���Z�b�T�̃r�b�g��
#define OFFSET_D 4//�������[�v�ƊO�����[�v�̍�


/*
 *	�֐��v���g�^�C�v�錾
 */
static char *make_wait(int cycle, char tmp[]);//���[�v���T�C�N���Ƃ��]��̃T�C�N���𐶐�����
static int calc_line(DelayElement delay);//�s���v�Z1
static int calc_line_double(DelayElement delay[]);//�s���v�Z2
static int calc_line_triple(DelayElement delay[]);//�s���v�Z3


/*
 *	�T�C�N�����̎擾
 */
int get_cycle(int max, int min){
	int cycle = 0;
	do{//���Ԏ擾
		printf("�E�F�C�g���������Ԃ�%d~%d[us]�̊Ԃœ��͂��Ă�������\n==>", min, max);
		scanf("%d", &cycle);
	}while(cycle < min || max < cycle);
	printf("%d[us]�Ōv�Z���܂�\n", cycle);//�m�F
	return (double)cycle / (setting.period * 1000000);//�T�C�N�������v�Z���ă��^�[��
}


/*
 *	�s���̈�ԏ��Ȃ��g�ݍ��킹��T��
 */
 void evaluate_line(DelayElement *delay){
 	int compLine = delay->cycle, tmpLine, tmpLoop;
 	DelayElement tmp = {delay->cycle, 0, 0, 0};

 	for(tmp.loop = 1; tmp.loop < BIT_WIDTH; tmp.loop++){
 		tmp.intCycle = (tmp.cycle - L_OFFSET) / tmp.loop - 3;
 		if(tmp.intCycle < 0) break;
 		tmp.surplus = (tmp.cycle - L_OFFSET) % tmp.loop;
 		tmpLine = calc_line(tmp);
 		if(compLine > tmpLine){//�s����r
 			compLine = tmpLine;
 			tmpLoop = tmp.loop;
 		}
 	}
 	delay->loop = tmpLoop;
 	delay->intCycle = (delay->cycle - L_OFFSET) / delay->loop - 3;
 	delay->surplus = (delay->cycle - L_OFFSET) % delay->loop;
 }


/*
 *	��d���[�v�ł̍s���̈�ԏ��Ȃ��g�ݍ��킹��T��
 */
 void evaluate_line_double(DelayElement delay[]){
 	int compLine = delay[0].cycle, tmpLine, tmpLoop[2];
 	DelayElement tmp[2];
 	tmp[0].cycle = delay[0].cycle;

 	for(tmp[0].loop = 1; tmp[0].loop < BIT_WIDTH; tmp[0].loop++){
 		tmp[0].intCycle = (tmp[0].cycle - L_OFFSET) / tmp[0].loop - 3;
 		if(tmp[0].intCycle < 10) break;
 		tmp[0].surplus = (tmp[0].cycle - L_OFFSET) % tmp[0].loop;
 		tmp[1].cycle = tmp[0].intCycle + OFFSET_D;//�����ƊO���̃I�t�Z�b�g�̍�
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
 *	�O�d���[�v�ł̍s���̈�ԏ��Ȃ��g�ݍ��킹��T��
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
 *	�s���v�Z
 */
static int calc_line(DelayElement delay){//�s���v�Z
	return 7 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2);
}


/*
 *	��d���[�v�s���v�Z
 */
static int calc_line_double(DelayElement delay[]){//�s���v�Z
	return calc_line(delay[1]) + (delay[0].surplus / 2 + delay[0].surplus % 2) + 5;
}


/*
 *	�O�d���[�v�s���v�Z
 */
static int calc_line_triple(DelayElement delay[]){//�s���v�Z
	DelayElement tmp[2];
	tmp[0] = delay[1];
	tmp[1] = delay[2];
	return calc_line_double(tmp) + (delay[0].surplus / 2 + delay[0].surplus % 2) + 5;
}


/*
 *	�\�[�X�R�[�h����
 */
char *make_result(DelayElement delay, char result[]){
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//�v�f�\��
	printf("�S�̕K�v�T�C�N���� = %d\n���[�v�� = %d\n�����T�C�N���� = %d\n�]�� = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("�R�[�h�̍s�� = %d\n",calc_line(delay));

	//�����ƌ������J��Ԃ�
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
 *	�\�[�X�R�[�h����
 */
char *make_result_double(DelayElement delay[], char result[]){
	int i;
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//�v�f�\��
	for(i = 0; i < 2; i++)
		printf("���[�v%d\n�S�̕K�v�T�C�N���� = %d\n���[�v�� = %d\n�����T�C�N���� = %d\n�]�� = %d\n",
		i + 1, delay[i].cycle, delay[i].loop, delay[i].intCycle, delay[i].surplus);
	printf("�R�[�h�̍s�� = %d\n", calc_line_double(delay));

	//�����ƌ������J��Ԃ�
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
 *	�\�[�X�R�[�h����
 */
char *make_result_triple(DelayElement delay[], char result[]){
	int i;
	char tmp[512], tmp2[1024];
	memset(tmp, '\0', strlen(tmp));
	//�v�f�\��
	for(i = 0; i < 3; i++)
		printf("���[�v%d\n�S�̕K�v�T�C�N���� = %d\n���[�v�� = %d\n�����T�C�N���� = %d\n�]�� = %d\n",
		i + 1, delay[i].cycle, delay[i].loop, delay[i].intCycle, delay[i].surplus);
	printf("�R�[�h�̍s�� = %d\n", calc_line_triple(delay));

	//�����ƌ������J��Ԃ�
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
 *	���[�v���T�C�N���Ƃ��]��̃T�C�N���𐶐�����
 */
static char *make_wait(int cycle, char str[]){
	memset(str, '\0', strlen(str));
	if(cycle % 2 == 1)//�������
		strcat(str, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)//�c���GOTO$+1��
		strcat(str, "\tGOTO\t$+1\n");
	return str;
}

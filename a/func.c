//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              �֐��u���� func.c
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : �܂�ŃX�p�Q�b�e�B�\�[�X�݂�������(���g)
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
#define T_MIN 2//�E�F�C�g���Ԃ̉���
#define T_MAX 2000//�E�F�C�g���Ԃ̏��
#define L_OFFSET 5//���[�v�v�Z���̃I�t�Z�b�g
#define BIT_WIDTH 256//�v���Z�b�T�̃r�b�g��


/*
 *	�֐��v���g�^�C�v�錾
 */
static char *make_wait(int cycle, char tmp[256]);//���[�v���T�C�N���Ƃ��]��̃T�C�N���𐶐�����


/*
 *	�T�C�N�����̎擾
 */
int get_cycle(void){
	int cycle = 0;
	do{//���Ԏ擾
		printf("�E�F�C�g���������Ԃ�%d~%d[us]�̊Ԃœ��͂��Ă�������\n==>", T_MIN, T_MAX);
		scanf("%d", &cycle);
	}while(cycle < T_MIN || T_MAX < cycle);
	printf("%d[sec]�Ōv�Z���܂�\n", cycle);//�m�F
	return cycle / (setting.period * 1000000);//�N���b�N�������v�Z���ă��^�[��
}


/*
 *	�s���̈�ԏ��Ȃ��g�ݍ��킹��T��
 */
DelayElement evaluate_line(int cycle){
	int tmpComp = BIT_WIDTH, tmpLoop = 0;

	puts("�v�Z��");

	DelayElement delay = {cycle, 0, 0, 0};

	for(delay.loop = 1; delay.loop < BIT_WIDTH && (delay.cycle - L_OFFSET) > delay.loop; delay.loop++){//���Ӗ��Ȍv�Z�͏Ȃ�
		delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;//�����T�C�N���v�Z
		delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;//�]��v�Z
		int tmpLine = 5 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2);//�s���v�Z
		if(tmpComp > tmpLine && delay.intCycle > 0){//����
			tmpComp = tmpLine;
			tmpLoop = delay.loop;
		}
	}

	delay.loop = tmpLoop;//�l��߂�
	delay.intCycle = (delay.cycle - L_OFFSET) / delay.loop - 3;
	delay.surplus = (delay.cycle - L_OFFSET) % delay.loop;

	return delay;
}


/*
 *	�\�[�X�R�[�h����
 */
char *make_result(DelayElement delay, char result[]){
	char tmp[256], tmp2[256];
	memset(tmp, '\0', strlen(tmp));
	//�v�f�\��
	printf("�S�̕K�v�T�C�N���� = %d\n���[�v�� = %d\n�����T�C�N���� = %d\n�]�� = %d\n", delay.cycle, delay.loop, delay.intCycle, delay.surplus);
	printf("�R�[�h�̍s�� = %d\n", 7 + (delay.intCycle / 2 + delay.intCycle % 2) + (delay.surplus / 2 + delay.surplus % 2));

	//�����ƌ������J��Ԃ�
	sprintf(tmp, "%s\n\tMOVLW\t%d\n", setting.sl, delay.loop);
	strcat(result, tmp);
	sprintf(tmp, "\tMOVWF\t%s\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "%s\n", setting.ll);
	strcat(result, tmp);
	sprintf(tmp, "%s", make_wait(delay.intCycle, tmp2));
	strcat(result, tmp);
	sprintf(tmp, "\tDECFSZ\t%s,1\n", setting.rn);
	strcat(result, tmp);
	sprintf(tmp, "\tGOTO\t%s\n", setting.ll);
	strcat(result, tmp);
	sprintf(tmp, "%s", make_wait(delay.surplus, tmp2));
	strcat(result, tmp);
	sprintf(tmp, "\tRETURN\n");
	strcat(result, tmp);
	return result;
}


/*
 *	���[�v���T�C�N���Ƃ��]��̃T�C�N���𐶐�����
 */
static char *make_wait(int cycle, char str[256]){
	memset(str, '\0', strlen(str));
	if(cycle % 2 == 1)//�������
		strcat(str, "\tNOP\n");
	for(cycle /= 2; cycle > 0; cycle--)//�c���GOTO$+1��
		strcat(str, "\tGOTO\t$+1\n");
	return str;
}

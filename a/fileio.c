//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              �t�@�C�����o�͌n�֐��u���� fileio.c
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : �o�O�̎R
//=============================================================================


/*
 *	�v���v���Z�b�T����
 */
#include<stdio.h>
#include<stdlib.h>
#include"PICdelay.h"


/*
 *	�}�N��
 */
#define SC 5000000//�V�X�e���N���b�N���g��
#define SL "DELAY"//�T�u���[�`���̃��x��
#define RN "COUNTER"//���W�X�^�̖��O
#define LL "D_LOOP"//�f�B���C�����[�v�|�C���g�̃��x��


/*
 *	�֐��v���g�^�C�v�錾
 */
static FILE *init_setting(void);//�ݒ�t�@�C����������


/*
 *	�ݒ�t�@�C������ǂݍ���
 */
void import_setting(void){
	char s_tmp[256], tmp[64];

	puts("�ݒ�t�@�C����ǂݍ��݂܂�");
	FILE *fp;
	if((fp = fopen("setting.ini", "r")) == NULL){//������
		puts("�ݒ�t�@�C��\"setting.ini\"��������Ȃ��̂Ő������܂�");
		fp = init_setting();//�ݒ�t�@�C��������
		puts("�ݒ�t�@�C����������");
	}

	//�X�L����
	fscanf(fp, "%s\r\n", s_tmp);
	fscanf(fp, "SystemClock(Hz)=%s\r\n", tmp);
	fscanf(fp, "SubroutineLabel=%s\r\n", &setting.sl);
	fscanf(fp, "RegisterName=%s\r\n", &setting.rn);
	fscanf(fp, "LoopLabel=%s\r\n", &setting.ll);

	puts("�ݒ�t�@�C��\"setting.ini\"�̓ǂݍ��݊���");

	//�V�X�e���N���b�N���g������������v�Z
	setting.period = 1 / (double)atoi(tmp);

	printf("�N���b�N����%10.8lf[sec]\n", setting.period);
}


/*
 *	�ݒ�t�@�C��������
 */
static FILE *init_setting(void){
	FILE *fp = fopen("setting.ini", "w+");
	fprintf(fp, "[settings]\n");
	fprintf(fp, "SystemClock(Hz)=%d\n", SC);
	fprintf(fp, "SubroutineLabel=%s\n", SL);
	fprintf(fp, "RegisterName=%s\n", RN);
	fprintf(fp, "LoopLabel=%s\n", LL);
	rewind(fp);
	return fp;
}


/*
 *	�O���t�@�C���Ƀ\�[�X�R�[�h���o��
 */
void output(char *str){
	FILE *fp = fopen("result.asm", "w");
	fprintf(fp, str);
	fclose(fp);
}

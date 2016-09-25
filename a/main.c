//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              ���C���v���O���� main.c
// Author     : fclef978
// LastUpdate : 2016/09/18
// Since      : 2016/09/09
// Comment    : �����ς肵�Ă��āA����ł��Ăׂ����Ȃ��B�������肵���t�@�C�����B
//=============================================================================


/*
 *	�v���v���Z�b�T����
 */
#include<stdio.h>
#include"PICdelay.h"


/*
 *	�O���[�o���ϐ�
 */
Setting setting;//�ݒ�p�̍\����


/*
 *	���C���֐�
 */
int main(void){
	int selector = 0;
	puts("PICdelay PIC��DELAY�T�u���[�`�������@�ւ悤����");
	import_setting();//�ݒ�t�@�C������ǂݍ���
	//���C�����[�v**************************************************************
	do{
		printf("\n0�ŏI���A1�ŒP���[�v���[�h�A2�œ�d���[�v���[�h�A3�ŎO�d���[�v���[�h\n==>");
		scanf("%d", &selector);

		//�P���[�v���[�h********************************************************
		if(selector == 1){
			DelayElement delay;
			delay.cycle = get_cycle(1000, 2);
			evaluate_line(&delay);//�T�C�N�����̎擾�A�s���̈�ԏ��Ȃ��g�ݍ��킹��T��

			char result[4096] = {""};
			make_result(delay, result);//�\�[�X�R�[�h����
			printf("////////////////\n�ȉ����R�[�h\n////////////////\n\n");
			printf("%s", result);//�\�[�X�R�[�h�\��

			output(result);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

			puts("\n�I�����܂���");
		}
		//��d���[�v���[�h******************************************************
		else if(selector == 2){
			DelayElement delay[2];
			delay[0].cycle = get_cycle(500000, 100);	//�T�C�N�����̎擾

			evaluate_line_double(delay);//�T�C�N�����̎擾�A�s���̈�ԏ��Ȃ��g�ݍ��킹��T��

			char result[4096] = {""};
			make_result_double(delay, result);//�\�[�X�R�[�h����
			printf("////////////////\n�ȉ����R�[�h\n////////////////\n\n");
			printf("%s", result);//�\�[�X�R�[�h�\��

			output(result);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

			puts("\n�I�����܂���");
		}
		//�O�d���[�v���[�h******************************************************
		else if(selector == 3){
			DelayElement delay[3];
			delay[0].cycle = get_cycle(100000000, 1000);	//�T�C�N�����̎擾

			evaluate_line_triple(delay);//�T�C�N�����̎擾�A�s���̈�ԏ��Ȃ��g�ݍ��킹��T��

			char result[4096] = {""};
			make_result_triple(delay, result);//�\�[�X�R�[�h����
			printf("////////////////\n�ȉ����R�[�h\n////////////////\n\n");
			printf("%s", result);//�\�[�X�R�[�h�\��

			output(result);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

			puts("\n�I�����܂���");
		}
	}while(selector != 0);

	return 0;//����I��
}

//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              ���C���v���O���� main.c
// Author     : fclef978
// LastUpdate : 2016/09/17
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
	puts("PICdelay PIC��DELAY�T�u���[�`�������@�ւ悤����");
	import_setting();//�ݒ�t�@�C������ǂݍ���

	int cycle = get_cycle();//�T�C�N�����̎擾

	DelayElement delay = evaluate_line(cycle);//�s���̈�ԏ��Ȃ��g�ݍ��킹��T��

	char result[1024] = {""};
	make_result(delay, result);//�\�[�X�R�[�h����
	printf("////////////////\n�ȉ����R�[�h\n////////////////\n\n");
	printf("%s", result);//�\�[�X�R�[�h�\��

	output(result);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

	puts("\n�I�����܂�");
	int tmp = 0;//�K���ɍ�������͑҂�
	scanf("%d", &tmp);

	return 0;//����I��
}

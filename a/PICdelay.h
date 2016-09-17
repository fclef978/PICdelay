//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              �w�b�_ PICdelay.h
// Author     : fclef978
// LastUpdate : 2016/09/17
// Since      : 2016/09/09
// Comment    : �������܂Ƃ߃X�M�B�I
//=============================================================================


/*
 *	�\����
 */
typedef struct{
	int cycle;//���T�C�N����
	int loop;//���[�v��
	int intCycle;//���[�v���T�C�N����
	int surplus;//�]��
}DelayElement;//�f�B���C�̗v�f

typedef struct{
	double period;//�N���b�N����
	char sl[64];//�T�u���[�`���̃��x��
	char rn[64];//���W�X�^�̖��O
	char ll[64];//�f�B���C�����[�v�|�C���g�̃��x��
}Setting;//�ݒ�


/*
 *	�O���[�o���ϐ�
 */
extern Setting setting;//�ݒ�p�̍\����


/*
 *	�֐��v���g�^�C�v�錾
 */
//func.c
int get_cycle(void);//�T�C�N�����̎擾
DelayElement evaluate_line(int cycle);//�s���̈�ԏ��Ȃ��g�ݍ��킹��T��
char *make_result(DelayElement delay, char result[]);//�\�[�X�R�[�h����

//fileio.c
void import_setting(void);//�ݒ�t�@�C������ǂݍ���
void output(char *str);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

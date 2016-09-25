//=============================================================================
// Contents   : PIC��DELAY�T�u���[�`���𐶐�����
//              �w�b�_ PICdelay.h
// Author     : fclef978
// LastUpdate : 2016/09/18
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
int get_cycle(int max, int min);//�T�C�N�����̎擾
void evaluate_line(DelayElement *delay);//�s���̈�ԏ��Ȃ��g�ݍ��킹��T��
void evaluate_line_double(DelayElement delay[]);//��d���[�v�łōs���̈�ԏ��Ȃ��g�ݍ��킹��T��
void evaluate_line_triple(DelayElement delay[]);//�O�d���[�v�łōs���̈�ԏ��Ȃ��g�ݍ��킹��T��
char *make_result(DelayElement delay, char result[]);//�\�[�X�R�[�h����
char *make_result_double(DelayElement delay[], char result[]);//��d���[�v�łŃ\�[�X�R�[�h����
char *make_result_triple(DelayElement delay[], char result[]);//�O�d���[�v�łŃ\�[�X�R�[�h����

//fileio.c
void import_setting(void);//�ݒ�t�@�C������ǂݍ���
void output(char *str);//�O���t�@�C���Ƀ\�[�X�R�[�h���o��

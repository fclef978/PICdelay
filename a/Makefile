#=============================================================================
# Contents   : PIC��DELAY�T�u���[�`���𐶐�����
#              �v���W�F�N�g��Makefile Makefile
# Author     : fclef978
# LastUpdate : 2016/09/17
# Since      : 2016/09/09
# Comment    : �����������Ə����ĂȂ�(���X)
#=============================================================================

#�o�C�i���̖��O
PROGRAM = PICdelay.exe
OBJS = main.o func.o fileio.o

#�v���C�}���^�[�Q�b�g
$(PROGRAM): $(OBJS)
	gcc $(OBJS) -o $@ -lm

#�T�t�B�b�N�X���[��
.c.o:
    gcc -c $< -W

#�w�b�_�̈ˑ��֌W
main.o: PICdelay.h
func.o: PICdelay.h
fileio.o: PICdelay.h

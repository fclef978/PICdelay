#=============================================================================
# Contents   : PICのDELAYサブルーチンを生成する
#              プロジェクトのMakefile Makefile
# Author     : fclef978
# LastUpdate : 2016/09/17
# Since      : 2016/09/09
# Comment    : たいしたこと書いてない(今更)
#=============================================================================

#バイナリの名前
PROGRAM = PICdelay.exe
OBJS = main.o func.o fileio.o

#プライマリターゲット
$(PROGRAM): $(OBJS)
	gcc $(OBJS) -o $@ -lm

#サフィックスルール
.c.o:
    gcc -c $< -W

#ヘッダの依存関係
main.o: PICdelay.h
func.o: PICdelay.h
fileio.o: PICdelay.h

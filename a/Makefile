# PICdelay alpha0.1 Makefile

#バイナリの名前
PROGRAM = PICdelay.exe
OBJS = main.o func.o fileio.o

#プライマリターゲット
$(PROGRAM): $(OBJS)
	gcc $(OBJS) -o $@ -lm

.c.o:
    gcc -c $< -W

#ヘッダの依存関係
main.o: PICdelay.h
func.o: PICdelay.h
fileio.o: PICdelay.h

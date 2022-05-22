FLT.out: main.o ftl.o devicedriver.o
	gcc -o FLT.out main.o ftl.o devicedriver.o

main.o: main.c blkmap.h
	gcc -c -o main.o main.c

ftl.o: ftl.c blkmap.h
	gcc -c -o ftl.o ftl.c

devicedriver.o: devicedriver.c blkmap.h
	gcc -c -o devicedriver.o devicedriver.c
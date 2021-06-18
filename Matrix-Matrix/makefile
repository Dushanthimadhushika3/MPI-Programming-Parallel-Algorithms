EXECS=Matrix-Matrix
MPICC?=mpicc

all: ${EXECS}
Matrix-Matrix: bcast.c
	${MPICC} -o Matrix-Matrix matrix-matrix.cpp

clean:
	rm -f ${EXECS}

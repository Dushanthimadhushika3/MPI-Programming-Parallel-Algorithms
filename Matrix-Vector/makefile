EXECS=Matrix-Vector
MPICC?=mpicc

all: ${EXECS}
Matrix-Vector: bcast.c
	${MPICC} -o Matrix-Vector matrix-vector.cpp

clean:
	rm -f ${EXECS}

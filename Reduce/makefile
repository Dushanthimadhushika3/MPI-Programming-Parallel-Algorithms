EXECS=Reduce
MPICC?=mpicc

all: ${EXECS}
Reduce: bcast.c
	${MPICC} -o Reduce reduce.cpp

clean:
	rm -f ${EXECS}

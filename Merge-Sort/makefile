EXECS=Merge-Sort
MPICC?=mpicc

all: ${EXECS}
Merge-Sort: bcast.c
	${MPICC} -o Merge-Sort merge-sort-para.cpp

clean:
	rm -f ${EXECS}

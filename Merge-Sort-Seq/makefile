EXECS=Merge-Sort-Seq
MPICC?=mpicc

all: ${EXECS}
Merge-Sort-Seq: bcast.c
	${MPICC} -o Merge-Sort-Seq merge-sort-seq.cpp

clean:
	rm -f ${EXECS}

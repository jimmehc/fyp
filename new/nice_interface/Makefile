.PHONY: biasedlock progress bias_transfer multiple overhead_to_sequential overhead_to_sequential_no_locks

COMPILER=g++

biasedlock:
	${COMPILER} -o ${OUTPUT} biasedlock.cpp -D${ALG} -D${DOM} -DLOOP -O3 -lpthread

progress:
	${COMPILER} -o ${OUTPUT} progress.cpp -D${ALG} -DNDD=${NDD}  -O3 -lpthread

bias_transfer:

multiple:
	${COMPILER} -o ${OUTPUT} multiple.cpp -D${ALG} -DNDF=${NDF} -DLOOP -O3 -lpthread -DMULTIPLE

overhead_to_sequential:
	${COMPILER} -o ${OUTPUT} overhead_to_sequential.cpp -D${ALG} -DCS_SIZE=${CS_SIZE} -DLOOP -O3 -lpthread

overhead_to_sequential_no_locks:
	${COMPILER} -o ${OUTPUT} overhead_to_sequential.cpp -DFP -DSEQ -DLOOP -DCS_SIZE=${CS_SIZE} -O3 -lpthread

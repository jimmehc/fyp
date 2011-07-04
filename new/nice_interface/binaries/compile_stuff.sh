#!/bin/bash

domarr=(NNPNNN NNPNN NNPN NN NE NS NSI NF NFO NT NTW NO N EF E SF S SI F)
ndfarr=( "100000" "10000" "1000" "100" "50" "25" "10" "9" "8" "7" "6" "5" "4" "3" "2" "1" )
nddarr=( "100000" "10000" "1000" "100" "50" "25" "10" "9" "8" "7" "6" "5" "4" "3" "2" "1" )
cssize=( "1" "2" "3" "4" "5" "6" "7" "8" "9" "10" )
benchmarks=( biasedlock multiple overhead_to_sequential progress )
algs=(SPL VAS FP AFP MP AMP ISPL ISPLMP FPQ MPQ BQ)

cd ..

for i in ${!domarr[*]};do
	for j in ${!algs[*]}; do
		echo `make biasedlock OUTPUT=binaries/biasedlock/$i\_$j DOM=${domarr[i]} ALG=${algs[j]}`;
	done
done

for i in ${!ndfarr[*]};do
	for j in ${!algs[*]}; do
		echo `make multiple OUTPUT=binaries/multiple/$i\_$j NDF=${ndfarr[i]} ALG=${algs[j]}`;
	done
done

for i in ${!nddarr[*]};do
	for j in ${!algs[*]}; do
		echo `make progress OUTPUT=binaries/progress/$i\_$j NDD=${nddarr[i]} ALG=${algs[j]}`;
	done
done

for i in ${!cssize[*]};do
	echo `make overhead_to_sequential_no_locks OUTPUT=binaries/overhead\_to\_sequential/nolocks\_$i CS_SIZE=${cssize[i]}`;
done

for i in ${!cssize[*]};do
	for j in ${!algs[*]};do
		echo `make overhead_to_sequential OUTPUT=binaries/overhead\_to\_sequential/$i\_$j CS_SIZE=${cssize[i]} ALG=${algs[j]}`;
	done
done

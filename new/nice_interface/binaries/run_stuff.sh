#!/bin/bash

domarr=(NNPNNN NNPNN NNPN NN NE NS NSI NF NFO NT NTW NO N EF E SF S SI F)
ndfarr=( "100000" "10000" "1000" "100" "50" "25" "10" "9" "8" "7" "6" "5" "4" "3" "2")
nddarr=( "100000" "10000" "1000" "100" "50" "25" "10" "9" "8" "7" "6" "5" "4" "3" "2" )
cssize=( "1" "2" "3" "4" "5" )
benchmarks=( biasedlock multiple overhead_to_sequential progress )
algs=(SPL VAS FP AFP MP AMP ISPL ISPLMP FPQ MPQ BQ)

cd ..

echo 'progress'
echo '--------------------'
echo ''
for i in ${!nddarr[*]};do
	echo ${nddarr[i]}
	for j in ${!algs[*]}; do
		echo ${algs[j]}
		echo `./binaries/progress/$i\_$j`;
	done
	echo ""
done

echo '---------------------------------------------------------------'

echo 'multiple'
echo '--------------------'
echo ''
for i in ${!ndfarr[*]};do
	echo ${ndfarr[i]}
	for j in ${!algs[*]}; do
		echo ${algs[j]}
		echo `./binaries/multiple/$i\_$j`;
	done
	echo ""
done

echo '---------------------------------------------------------------'

echo 'biasedlock'
echo '--------------------'
echo ''
for i in ${!domarr[*]};do
	echo ${domarr[i]}
	for j in ${!algs[*]}; do
		echo ${algs[j]}
		echo `./binaries/biasedlock/$i\_$j`;
	done
	echo ""
done

echo '---------------------------------------------------------------'

#echo 'overhead_to_sequential'
#echo '--------------------'
#echo ''
#echo 'NOLOCKS'
#for i in ${!cssize[*]};do
#	echo `./binaries/overhead\_to\_sequential/nolocks\_$i`;
#done

#for i in ${!cssize[*]};do
#	echo ${cssize[i]}
#	for j in ${!algs[*]};do
#		echo ${algs[j]}
#		echo `./binaries/overhead\_to\_sequential/$i\_$j`;
#	done
#done

#echo '---------------------------------------------------------------'


all:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -D${TP} -O3 -static

assembly:
	g++ -S biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O3 -static


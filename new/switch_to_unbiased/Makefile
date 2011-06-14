all:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O3 -static

debug:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O3 -static -ggdb

assembly:
	g++ -S biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O3 -static


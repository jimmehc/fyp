all:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -D${ALG} -D${TP} -O3 -static 
assembly:
	g++ -S biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O3 -static

progress:
	g++ -o asymmetric progress.cpp -lpthread -Wall -Wextra -DNON_DOM_DELAY=${NDD} -D${ALG}  -O3 -static

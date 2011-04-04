#!/bin/bash

echo "Control 99.999-90% Dominance"
echo ""
cd control 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "Asymmetric 99.999-90% Dominance"
echo ""
cd asymmetric
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "Asymmetric 99.999-90% Dominance"
echo ""
cd asymmetric_var
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "FPP 99.999-90% Dominance"
echo ""
cd experiment 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "AFPP 99.999-90% Dominance"
echo ""
cd experiment2 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "MP 99.999-90% Dominance"
echo ""
cd experiment3 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "IS 99.999-90% Dominance"
echo ""
cd experiment4 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "Spinlock 99.999-90% Dominance"
echo ""
cd spinlock 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "Pthread Mutex 99.999-90% Dominance"
echo ""
cd pthread_lock 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "Queues 99.999-90% Dominance"
echo ""
cd queues 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..
echo "MPQ 99.999-90% Dominance"
echo ""
cd message_passing 
./asymmetricnnpnnn
./asymmetricnnpnn
./asymmetricnnpn
./asymmetricnn
./asymmetricnf
./asymmetricn
cd ..


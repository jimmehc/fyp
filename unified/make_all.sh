#!/bin/bash

cd control 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd asymmetric
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd asymmetric_var
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd experiment 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd experiment2 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd experiment3 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd experiment4 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd spinlock 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd pthread_lock 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd queues 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..
cd message_passing 
make nnpnnn DELAY=0
make nnpnn DELAY=0
make nnpn DELAY=0
make nnp DELAY=0
make nn DELAY=0
make nf DELAY=0
make n DELAY=0
cd ..


all:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O2 

profile:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O2 -pg -ggdb -fprofile-arcs -ftest-coverage
assembly:
	g++ -S biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG} -O2

WAT:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG}  -O

WATTT:
	g++ -o asymmetric biasedlock.cpp -lpthread -Wall -Wextra -D${DOM} -DDELAY=${DELAY} -D${ALG}  -falign-functions  -falign-jumps  -falign-labels  -fargument-alias  -fasynchronous-unwind-tables  -fbranch-count-reg  -fcaller-saves  -fcommon  -fcprop-registers  -fcrossjumping  -fcse-follow-jumps  -fdce  -fdefer-pop  -fdelete-null-pointer-checks  -fdse  -fearly-inlining  -fexpensive-optimizations  -fextension-elimination  -fforward-propagate  -fgcse  -fgcse-lm  -fguess-branch-probability  -fhandle-exceptions  -fif-conversion  -fif-conversion2  -finline-functions-called-once  -finline-small-functions  -fipa-cp  -fipa-pure-const  -fipa-reference  -fipa-sra  -fivopts  -fjump-tables  -fmath-errno  -fmerge-constants  -fmove-loop-invariants  -fomit-frame-pointer  -foptimize-register-move  -foptimize-sibling-calls  -fpeephole  -fpeephole2  -fregmove  -frename-registers  -freorder-blocks  -freorder-functions  -frerun-cse-after-loop  -frtti  -fsched-critical-path-heuristic  -fsched-dep-count-heuristic  -fsched-group-heuristic  -fsched-interblock  -fsched-last-insn-heuristic  -fsched-rank-heuristic  -fsched-spec  -fsched-spec-insn-heuristic  -fsched-stalled-insns-dep  -fschedule-insns2  -fshort-double  -fshort-enums  -fshort-wchar  -fsigned-zeros  -fsplit-ivs-in-unroller  -fsplit-wide-types  -fstrict-aliasing  -fthread-jumps  -fno-threadsafe-statics  -ftoplevel-reorder  -ftrapping-math  -ftree-builtin-call-dce  -ftree-ccp  -ftree-ch  -ftree-copy-prop  -ftree-copyrename  -ftree-cselim  -ftree-dce  -ftree-dominator-opts  -ftree-dse  -ftree-forwprop  -ftree-fre  -ftree-if-to-switch-conversion  -ftree-loop-im  -ftree-loop-ivcanon  -ftree-loop-optimize  -ftree-phiprop  -ftree-pre  -ftree-pta  -ftree-reassoc  -ftree-scev-cprop  -ftree-sink  -ftree-slp-vectorize  -ftree-sra  -ftree-switch-conversion  -ftree-ter  -ftree-vect-loop-version  -ftree-vrp  -funit-at-a-time  -fvar-tracking  -fvar-tracking-assignments  -fvect-cost-model  -fweb -O

progress:
	g++ -o asymmetric progress.cpp -lpthread -Wall -Wextra -DNDD=${NDD} -D${ALG} -O3 -static

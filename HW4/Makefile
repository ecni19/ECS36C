all : test_multimap cfs_sched

test_multimap : test_multimap.cc multimap.h
	g++ -Wall -Werror -std=c++11 -o test_multimap multimap.h test_multimap.cc -pthread -lgtest

cfs_sched : cfs_sched.cc multimap.h
	g++ -Wall -Werror -std=c++11 -o cfs_sched multimap.h cfs_sched.cc

clean :
	rm -f test_multimap cfs_sched

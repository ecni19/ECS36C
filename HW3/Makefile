all : prime_factors test_multiset

test_multiset : test_multiset.cc multiset.h
	g++ -Wall -Werror -std=c++11 -o test_multiset multiset.h test_multiset.cc -pthread -lgtest

prime_factors : prime_factors.cc multiset.h
	g++ -Wall -Werror -std=c++11 -o prime_factors multiset.h prime_factors.cc

clean :
	rm -f prime_factors test_multiset
all: postfix_eval test_deque

postfix_eval: postfix_eval.cc stack.h
	g++ -Wall -Werror -std=c++11 -o postfix_eval postfix_eval.cc stack.h
test_deque: test_deque.cc deque.h
	g++ -Wall -Werror -std=c++11 -o test_deque test_deque.cc deque.h -pthread -lgtest
clean:
	rm -f postfix_eval test_deque

# COMPILED ON: x86_64 GNU/Linux

SANITIZER_FLAGS = -fsanitize=undefined -fsanitize=bounds -fsanitize=address -fsanitize=leak


ll:
	gcc -std=c11 -Wall -Werror -Wshadow ${SANITIZER_FLAGS} -g -O3 data_struct/linked_list.c -o data_struct/linked_list


stack:
	gcc -std=c11 -Wall -Werror -Wshadow ${SANITIZER_FLAGS} -g -O3 data_struct/stack.c -o data_struct/stack
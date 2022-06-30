#!/bin/bash

############################################################
##### Simple bash script to compile and run .C scripts ######
############################################################

##################
##### SETUP ######
##################
# export SYS_HOME=*<current working directory>*/Intro_to_C

##################
##### EXAMPLE ####
##################
# $SYS_HOME/compile_and_run.sh <name_of_c_file> <name_of_binary_output_file>
# $SYS_HOME/compile_and_run.sh mario mario
clang -lcs50 -lm -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow $1.c -o $2 && ./$2

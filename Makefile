#
# File: Makefile
# Creator: George Ferguson
# Created: Thu Jun 30 11:00:49 2016
#
# Sample Makefile distributed with CSC173 Project 1 code bundle
#
# This Makefile builds the test programs for the data structures
# distributed with the bundle, and show how you might use it to
# build YOUR program for the project.
#

PROG = proj1

CFLAGS = -g -std=c99 -Wall -Werror


SRCS = nfa.c dfa.c IntHashSet.c REPL.c NFA_to_DFA.c
OBJS = ${SRCS:%.c=%.o}

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)


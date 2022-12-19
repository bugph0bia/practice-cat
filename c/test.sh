#!/bin/bash

assert() {
    args="$@"

    cat $args > tmp.1
    ./cat $args > tmp.2

    diffout=$(diff tmp.1 tmp.2)
    retval="$?"

    if [ "$retval" = "0" ]; then
        echo "OK: $args"
        rm tmp.1 tmp.2
    else
        echo "NG: $args"
        echo "$diffout"
        echo ""
        exit 1
    fi
}

assert cat.c 
assert cat.c -A
assert cat.c -b
assert cat.c -e
assert cat.c -E
assert cat.c -n
assert cat.c -s
assert cat.c -t
assert cat.c -T
assert cat.c -u
assert cat.c -v
assert cat.c --show-all
assert cat.c --number-nonblank
assert cat.c --show-ends
assert cat.c --number
assert cat.c --squeeze-blank
assert cat.c --show-tabs
assert cat.c --show-nonprinting

assert cat.c cat.c
assert cat.c cat.c -A
assert cat.c cat.c -b
assert cat.c cat.c -e
assert cat.c cat.c -E
assert cat.c cat.c -n
assert cat.c cat.c -s
assert cat.c cat.c -t
assert cat.c cat.c -T
assert cat.c cat.c -u
assert cat.c cat.c -v
assert cat.c cat.c --show-all
assert cat.c cat.c --number-nonblank
assert cat.c cat.c --show-ends
assert cat.c cat.c --number
assert cat.c cat.c --squeeze-blank
assert cat.c cat.c --show-tabs
assert cat.c cat.c --show-nonprinting

assert cat.o
assert cat.o -A
assert cat.o -b
assert cat.o -e
assert cat.o -E
assert cat.o -n
assert cat.o -s
assert cat.o -t
assert cat.o -T
assert cat.o -u
assert cat.o -v
assert cat.o --show-all
assert cat.o --number-nonblank
assert cat.o --show-ends
assert cat.o --number
assert cat.o --squeeze-blank
assert cat.o --show-tabs
assert cat.o --show-nonprinting

assert cat.o cat
assert cat.o cat -A
assert cat.o cat -b
assert cat.o cat -e
assert cat.o cat -E
assert cat.o cat -n
assert cat.o cat -s
assert cat.o cat -t
assert cat.o cat -T
assert cat.o cat -u
assert cat.o cat -v
assert cat.o cat --show-all
assert cat.o cat --number-nonblank
assert cat.o cat --show-ends
assert cat.o cat --number
assert cat.o cat --squeeze-blank
assert cat.o cat --show-tabs
assert cat.o cat --show-nonprinting

echo "Complete"


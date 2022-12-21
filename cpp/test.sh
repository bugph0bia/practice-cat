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

assert cat.cpp 
assert cat.cpp -A
assert cat.cpp -b
assert cat.cpp -e
assert cat.cpp -E
assert cat.cpp -n
assert cat.cpp -s
assert cat.cpp -t
assert cat.cpp -T
assert cat.cpp -u
assert cat.cpp -v
assert cat.cpp --show-all
assert cat.cpp --number-nonblank
assert cat.cpp --show-ends
assert cat.cpp --number
assert cat.cpp --squeeze-blank
assert cat.cpp --show-tabs
assert cat.cpp --show-nonprinting

assert cat.cpp cat.cpp
assert cat.cpp cat.cpp -A
assert cat.cpp cat.cpp -b
assert cat.cpp cat.cpp -e
assert cat.cpp cat.cpp -E
assert cat.cpp cat.cpp -n
assert cat.cpp cat.cpp -s
assert cat.cpp cat.cpp -t
assert cat.cpp cat.cpp -T
assert cat.cpp cat.cpp -u
assert cat.cpp cat.cpp -v
assert cat.cpp cat.cpp --show-all
assert cat.cpp cat.cpp --number-nonblank
assert cat.cpp cat.cpp --show-ends
assert cat.cpp cat.cpp --number
assert cat.cpp cat.cpp --squeeze-blank
assert cat.cpp cat.cpp --show-tabs
assert cat.cpp cat.cpp --show-nonprinting

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


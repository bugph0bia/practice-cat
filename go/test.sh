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

assert                    cat.go 
assert -A                 cat.go 
assert -b                 cat.go 
assert -e                 cat.go 
assert -E                 cat.go 
assert -n                 cat.go 
assert -s                 cat.go 
assert -t                 cat.go 
assert -T                 cat.go 
assert -u                 cat.go 
assert -v                 cat.go 
#assert -vET               cat.go 
#assert --show-all         cat.go 
#assert --number-nonblank  cat.go 
#assert --show-ends        cat.go 
#assert --number           cat.go 
#assert --squeeze-blank    cat.go 
#assert --show-tabs        cat.go 
#assert --show-nonprinting cat.go 

assert                    cat.go cat.go 
assert -A                 cat.go cat.go 
assert -b                 cat.go cat.go 
assert -e                 cat.go cat.go 
assert -E                 cat.go cat.go 
assert -n                 cat.go cat.go 
assert -s                 cat.go cat.go 
assert -t                 cat.go cat.go 
assert -T                 cat.go cat.go 
assert -u                 cat.go cat.go 
assert -v                 cat.go cat.go 
#assert -vET               cat.go cat.go 
#assert --show-all         cat.go cat.go 
#assert --number-nonblank  cat.go cat.go 
#assert --show-ends        cat.go cat.go 
#assert --number           cat.go cat.go 
#assert --squeeze-blank    cat.go cat.go 
#assert --show-tabs        cat.go cat.go 
#assert --show-nonprinting cat.go cat.go 

assert                    cat 
assert -A                 cat 
assert -b                 cat 
assert -e                 cat 
assert -E                 cat 
assert -n                 cat 
assert -s                 cat 
assert -t                 cat 
assert -T                 cat 
assert -u                 cat 
assert -v                 cat 
#assert -vET               cat 
#assert --show-all         cat 
#assert --number-nonblank  cat 
#assert --show-ends        cat 
#assert --number           cat 
#assert --squeeze-blank    cat 
#assert --show-tabs        cat 
#assert --show-nonprinting cat 

assert                    cat.go cat 
assert -A                 cat.go cat 
assert -b                 cat.go cat 
assert -e                 cat.go cat 
assert -E                 cat.go cat 
assert -n                 cat.go cat 
assert -s                 cat.go cat 
assert -t                 cat.go cat 
assert -T                 cat.go cat 
assert -u                 cat.go cat 
assert -v                 cat.go cat 
#assert -vET               cat.go cat 
#assert --show-all         cat.go cat 
#assert --number-nonblank  cat.go cat 
#assert --show-ends        cat.go cat 
#assert --number           cat.go cat 
#assert --squeeze-blank    cat.go cat 
#assert --show-tabs        cat.go cat 
#assert --show-nonprinting cat.go cat 

echo "Complete"


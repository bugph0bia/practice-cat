#!/bin/bash

assert() {
    args="$@"

    cat $args > tmp.1
    python cat.py $args > tmp.2

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

python -c "import py_compile; py_compile.compile('cat.py')"

assert cat.py 
assert cat.py -A
assert cat.py -b
assert cat.py -e
assert cat.py -E
assert cat.py -n
assert cat.py -s
assert cat.py -t
assert cat.py -T
assert cat.py -u
assert cat.py -v
assert cat.py -vET
assert cat.py --show-all
assert cat.py --number-nonblank
assert cat.py --show-ends
assert cat.py --number
assert cat.py --squeeze-blank
assert cat.py --show-tabs
assert cat.py --show-nonprinting

assert cat.py cat.py
assert cat.py cat.py -A
assert cat.py cat.py -b
assert cat.py cat.py -e
assert cat.py cat.py -E
assert cat.py cat.py -n
assert cat.py cat.py -s
assert cat.py cat.py -t
assert cat.py cat.py -T
assert cat.py cat.py -u
assert cat.py cat.py -v
assert cat.py cat.py -vET
assert cat.py cat.py --show-all
assert cat.py cat.py --number-nonblank
assert cat.py cat.py --show-ends
assert cat.py cat.py --number
assert cat.py cat.py --squeeze-blank
assert cat.py cat.py --show-tabs
assert cat.py cat.py --show-nonprinting

assert __pycache__/cat.cpython-*.pyc
assert __pycache__/cat.cpython-*.pyc -A
assert __pycache__/cat.cpython-*.pyc -b
assert __pycache__/cat.cpython-*.pyc -e
assert __pycache__/cat.cpython-*.pyc -E
assert __pycache__/cat.cpython-*.pyc -n
assert __pycache__/cat.cpython-*.pyc -s
assert __pycache__/cat.cpython-*.pyc -t
assert __pycache__/cat.cpython-*.pyc -T
assert __pycache__/cat.cpython-*.pyc -u
assert __pycache__/cat.cpython-*.pyc -v
assert __pycache__/cat.cpython-*.pyc -vET
assert __pycache__/cat.cpython-*.pyc --show-all
assert __pycache__/cat.cpython-*.pyc --number-nonblank
assert __pycache__/cat.cpython-*.pyc --show-ends
assert __pycache__/cat.cpython-*.pyc --number
assert __pycache__/cat.cpython-*.pyc --squeeze-blank
assert __pycache__/cat.cpython-*.pyc --show-tabs
assert __pycache__/cat.cpython-*.pyc --show-nonprinting

assert cat.py __pycache__/cat.cpython-*.pyc
assert cat.py __pycache__/cat.cpython-*.pyc -A
assert cat.py __pycache__/cat.cpython-*.pyc -b
assert cat.py __pycache__/cat.cpython-*.pyc -e
assert cat.py __pycache__/cat.cpython-*.pyc -E
assert cat.py __pycache__/cat.cpython-*.pyc -n
assert cat.py __pycache__/cat.cpython-*.pyc -s
assert cat.py __pycache__/cat.cpython-*.pyc -t
assert cat.py __pycache__/cat.cpython-*.pyc -T
assert cat.py __pycache__/cat.cpython-*.pyc -u
assert cat.py __pycache__/cat.cpython-*.pyc -v
assert cat.py __pycache__/cat.cpython-*.pyc -vET
assert cat.py __pycache__/cat.cpython-*.pyc --show-all
assert cat.py __pycache__/cat.cpython-*.pyc --number-nonblank
assert cat.py __pycache__/cat.cpython-*.pyc --show-ends
assert cat.py __pycache__/cat.cpython-*.pyc --number
assert cat.py __pycache__/cat.cpython-*.pyc --squeeze-blank
assert cat.py __pycache__/cat.cpython-*.pyc --show-tabs
assert cat.py __pycache__/cat.cpython-*.pyc --show-nonprinting

echo "Complete"


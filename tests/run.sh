#!/bin/bash

./cat </dev/null >tst.tmp
diff tests/empty.txt tst.tmp || exit 1

./cat tests/binom.txt >tst.tmp
diff tests/binom.txt tst.tmp || exit 2

./cat - <tests/binom.txt >tst.tmp
diff tests/binom.txt tst.tmp || exit 3

./cat <tests/binom.txt >tst.tmp
diff tests/binom.txt tst.tmp || exit 4

./cat tests/cup.txt tests/binom.txt >tst.tmp
diff tests/cup-binom.txt tst.tmp || exit 5

./cat - tests/binom.txt <tests/cup.txt >tst.tmp
diff tests/cup-binom.txt tst.tmp || exit 6

./cat tests/cup.txt - <tests/binom.txt >tst.tmp
diff tests/cup-binom.txt tst.tmp || exit 7

./cut </dev/null >tst.tmp
diff tests/empty.txt tst.tmp || exit 8

./cut tests/binom.txt >tst.tmp
diff tests/binom.txt tst.tmp || exit 9

./cut -f1 tests/binom.txt >tst.tmp
diff tests/binom-1.txt tst.tmp || exit 10

./cut -f-1 tests/binom.txt >tst.tmp
diff tests/binom-1.txt tst.tmp || exit 10

./cut -f1-1 tests/binom.txt >tst.tmp
diff tests/binom-1.txt tst.tmp || exit 10

./cut -f2 tests/binom.txt >tst.tmp
diff tests/binom-2.txt tst.tmp || exit 11

./cut -f2-2 tests/binom.txt >tst.tmp
diff tests/binom-2.txt tst.tmp || exit 12

./cut -f-2 tests/binom.txt >tst.tmp
diff tests/binom-1-2.txt tst.tmp || exit 13

./cut -f1-2 tests/binom.txt >tst.tmp
diff tests/binom-1-2.txt tst.tmp || exit 14

rm tst.tmp

#!/bin/bash
gcc proj1.c -o proj1.out
echo Running test1
./proj1.out < test1 > test1outputmine
echo Running test2
./proj1.out < test2 > test2outputmine
echo Running test3
./proj1.out < test3 > test3outputmine
echo Running test4
./proj1.out < test4 > test4outputmine
echo Running test5
./proj1.out < test5 > test5outputmine
echo Diff test1
diff test1output test1outputmine -s
echo Diff test2
diff test2output test2outputmine -s
echo Diff test3
diff test3output test3outputmine -s
echo Diff test4
diff test4output test4outputmine -s
echo Diff test5
diff test5output test5outputmine -s

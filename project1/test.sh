#!/bin/bash
./proj1.out < test1 > test1outputmine
diff test1output test1outputmine
./proj1.out < test2 > test2outputmine
diff test2output test2outputmine
./proj1.out < test3 > test3outputmine
diff test3output test3outputmine
./proj1.out < test4 > test4outputmine
diff test4output test4outputmine
./proj1.out < test5 > test5outputmine
diff test5output test5outputmine
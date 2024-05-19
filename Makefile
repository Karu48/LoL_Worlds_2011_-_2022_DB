run:
	gcc test.cpp -lstdc++
	./a.out
	rm a.out

isam:
	gcc testisam.cpp -lstdc++
	./a.out
	rm a.out

seq:
	gcc SequentialFile.cpp -lstdc++
	./a.out
	rm a.out

isambench:
	gcc ISAMstructs/benchmark-ISAM.cpp -lstdc++
	./a.out
	rm a.out
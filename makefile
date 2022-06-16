CFLAGS=-Wall -g

clean:
	rm -f ./main

exe:
	$(CXX) ./main.c $(CFLAGS) -o ./timeMeasurer

run:
	./timeMeasurer

debug:
	gdb --args ./timeMeasurer

all:
	gcc src/gNB.c -o bin/gNB -lpthread
	gcc src/mme.c -o bin/mme -lpthread
	gcc src/UE_simulator.c -o bin/UE -lpthread

clean:
	rm bin/gNB
	rm bin/mme
	rm bin/UE
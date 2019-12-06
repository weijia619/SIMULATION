all: proj5.exe

proj5.o: proj5.cpp FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl EventClass.h RtSimulationClass.h constants.h
	g++ -Wall -c proj5.cpp -o proj5.o
EventClass.o: EventClass.cpp EventClass.h
	g++ -Wall -c EventClass.cpp -o EventClass.o
RtSimulationClass.o: RtSimulationClass.cpp RtSimulationClass.h SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h LinkedNodeClass.inl constants.h random.h EventClass.h
	g++ -Wall -c RtSimulationClass.cpp -o RtSimulationClass.o
random.o: random.cpp random.h
	g++ -Wall -c random.cpp -o random.o
proj5.exe: proj5.o EventClass.o RtSimulationClass.o random.o
	g++ EventClass.o RtSimulationClass.o random.o proj5.o -o proj5.exe

clean:
	rm -f *.o *.exe
CPP = g++
CPPSTD = -std=c++11
LIBS = play.o CMax3SatProblem.o CGAIndividual.o CGAOptimizer.o Helper.o Pack.o

default: $(LIBS)
	$(CPP) $(LIBS) -o play

clean:
	rm play $(LIBS)

%.o: %.cpp
	$(CPP) $(CPPSTD) -c $< -o $@

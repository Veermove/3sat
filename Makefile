CPP = g++
CPPSTD = -std=c++98
LIBS = play.o

default: $(LIBS)
	$(CPP) $(LIBS) -o play

clean:
	rm play $(LIBS)

%.o: %.cpp
	$(CPP) $(CPPSTD) -c $< -o $@

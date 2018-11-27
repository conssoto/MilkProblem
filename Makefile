OBJS = main.o Reader.o Node.o ProblemInstance.o Trip.o Truck.o Route.o Solution.o Construction.o ReorderNodes.o
CFLAGS =	-std=c++1y #-fmax-errors=1 -ggdb #-ggdb for debug

all: MCPB

MCPB: $(OBJS)
	g++ -o MCPB $(OBJS) $(CFLAGS)

%.o: %.cpp
	g++ -c $(CFLAGS) $< -o $@



clean:
	rm -f MCPB *.o

exe:
	@./MCPB
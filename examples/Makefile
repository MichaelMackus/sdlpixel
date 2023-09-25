EXAMPLES=test.out
CCFLAGS=-Wall
LDFLAGS=-lSDL2

all: $(EXAMPLES)

%.out: %.c
	gcc $< -o $@ $(CCFLAGS) $(LDFLAGS)

clean:
	rm rl *.o

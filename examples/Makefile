EXAMPLES=fast.out pixel.out scale.out
CCFLAGS=-Wall
LDFLAGS=-lSDL2

all: $(EXAMPLES)

%.out: %.c
	gcc $< -o $@ $(CCFLAGS) $(LDFLAGS)

clean:
	rm *.out *.o

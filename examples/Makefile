EXAMPLES=fast.out fast_raw.out fast_texture.out pixel.out scale.out simple.out simple_struct.out nopixel.out
CCFLAGS=-Wall
LDFLAGS=-lSDL2

all: $(EXAMPLES)

%.out: %.c ../sdlpixel.h
	gcc -g $< -o $@ $(CCFLAGS) $(LDFLAGS)

clean:
	rm *.out *.o

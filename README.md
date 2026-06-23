# sdlpixel

Simple SDL single-file library for plotting raw RGB pixels onto the screen.
This is released to the public domain - use it as you wish.

UPDATE: Should probably just use olive.c or something else since this
implementation is lacking in performance & thread safety.

# Usage

See the [examples](examples) folder. For simple stuff, usually this just
means calling `sdlpixel_create` and then plotting some pixels with
`sdlpixel_plot`. Make sure to call `sdlpixel_refresh` to render to the
screen. When you're done, call `sdlpixel_quit`.

A minimal example can be found at [examples/simple.c](here).

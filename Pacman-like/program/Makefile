Pacman: GenericTimer.h draw.o func.o GenericTimer.o load_tex.o main.o struct.h glpng.h libglpng.a
	cc -g -O0 -o Pacman GenericTimer.h struct.h draw.o func.o GenericTimer.o load_tex.o main.o glpng.h -lglpng -lm -L. -I. -lglut -lGL -lGLU \
-lXi -lXrandr

.c.o:
	cc -c $<

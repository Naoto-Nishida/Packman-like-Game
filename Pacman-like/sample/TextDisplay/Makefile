TARGET=TextDisplay

$(TARGET): main.o
	cc -o $(TARGET) main.o -L. -lglut -lGLU -lGL -lXi -lXrandr -lm
.c.o:
	cc -c $< -I. -Wall

run: $(TARGET)
	./$(TARGET)
clean:
	rm -f *.o *.c~ *.h~ $(TARGET)

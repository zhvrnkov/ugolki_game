GL_PKGS=glfw3 glew
CFLAGS=-Wall -Wextra
FILES=main.cpp renderer/setup.c renderer/camera/camera.c

run: main.o
	./main.o

main.o: $(wildcard **/*.h **/*.cpp **/*.c *.h *.cpp *.c)
	g++ $(CFLAGS) `pkg-config --cflags $(GL_PKGS)` $(FILES) -o main.o `pkg-config --libs $(GL_PKGS)`

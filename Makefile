all: main.o tga.o obj_file.o
	g++ main.o tgaimage.o obj_file.o -o main

main.o: main.cpp
	g++ -c main.cpp

tga.o: tgaimage.cpp
	g++ -c tgaimage.cpp

obj_file.o: obj_file.cpp
	g++ -c obj_file.cpp

clean:
	rm -rf *.o main


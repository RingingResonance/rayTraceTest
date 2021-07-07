rayray: rt.o fg.o lodepng.o
	g++ -std=c++11 -pthread -o ../rayray ./lib/renderer.o ./lib/fgetter.o ./lodepng/lodepng.o

rt.o: renderer.cpp renderer.h
	g++ -std=c++11 -pthread -c renderer.cpp -o ./lib/renderer.o

fg.o: fgetter.cpp fgetter.h
	g++ -std=c++11 -pthread -c fgetter.cpp -o ./lib/fgetter.o

lodepng.o: ./lodepng/lodepng.cpp ./lodepng/lodepng.h
	g++ -std=c++11 -pthread -c ./lodepng/lodepng.cpp -o ./lodepng/lodepng.o

clean:
	rm *.o

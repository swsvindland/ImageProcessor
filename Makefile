SRC=main.cpp image.cpp sink.cpp source.cpp PNMreader.cpp PNMwriter.cpp filter.cpp logging.cpp
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o imgPro

.cpp.o: $<
	g++ -I. -c $<

clean:
	rm *.o imgPro

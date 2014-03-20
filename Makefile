objects = main.o vector.o particle.o space.o mesh.o

a : $(objects)
	g++ -o a $(objects)
main.o :	vector.hh space.hh
vector.o : 	vector.hh
particle.o :	vector.hh particle.hh
space.o :	vector.hh particle.hh
mesh.o :	vector.hh mesh.hh

clean:
	rm $(objects) a



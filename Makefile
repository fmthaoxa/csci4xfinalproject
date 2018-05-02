a.out: main.cc save.cc
	g++ -std=c++11 main.cc save.cc

clean:
	rm -f a.out core *.o

sys:
	g++ -O3 system_solver.cpp -fopenmp -o sys.o

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

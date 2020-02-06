sys:
	g++ -O3 system_solver.cpp -fopenmp -o sys.o
	g++ -O3 multiple_system_solver.cpp -fopenmp -o multisys.o
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

CC=mpicc

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@
hwk2make: main.c
	#module load gnu openmpi # module is a function echo $(type module)
	$(CC) -o hwk2 main.c
clean:
	rm hwk2


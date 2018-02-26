CC=mpicc

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@
hwk2make: main.c
	#module load gnu openmpi # Module not found in PATH
	$(CC) -o hwk2 main.c
clean:
	rm hwk2

	

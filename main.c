#include<mpi.h>
#include<stdio.h>
#include<stdlib.h> // rand(), srand()
#include<time.h>

#define RANKS 8
#define DEBUG

int main(int argc, char** argv) {
    int ranks=RANKS;

    int size;    // needed for sending # of processes to MPI
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    //#ifdef DEBUG
	////sleep a certain amount of s (offset based on ranks to demonstrate sync)
    //int offset = rank+1;
	//int s = 0;
	//for(int i = 0; i < 500000000*offset; i++){
	//	s = i;
	//}
    //#endif

    int data = 1;
    MPI_Status status;
    //implement broadcasting
    int step;

    // BROAD RECEIVE

    for(step = ranks>>1; step >= 1; step = step >> 1) {
        if(rank < step) { 
	        MPI_Recv(&data, 1, MPI_INT, rank+step, rank+step, MPI_COMM_WORLD, &status);
#ifdef DEBUG
            printf("%d:\t here0 %d\t Recv? = %d\t Tag = %d\n", 
                    rank, step, rank+step, rank+step);
#endif
        } else if (rank < 2*step) {
	        MPI_Send(&data, 1, MPI_INT, rank-step, rank-step, MPI_COMM_WORLD);
#ifdef DEBUG
            printf("%d:\t here0 %d\t Send? = %d\t Tag = %d\n", 
                    rank, step, rank-step, rank-step);
#endif
        } 
    }   

    // BROADCAST
#ifdef DEBUG
    printf("%d: Broadcast\n", rank);
#endif
    
    for(step = 1; step < ranks; step*=2){
        if(rank < step) {
            MPI_Send(&data, 1, MPI_INT, rank+step, rank+step, MPI_COMM_WORLD);
#ifdef DEBUG
            //printf("%d:\t here0 %d\t Recv? = %d\t Tag = %d\n", 
            //        rank, step, rank+step, rank+step);
#endif
        } else if(rank < 2*step) {
            MPI_Recv(&data, 1, MPI_INT, rank-step, rank, MPI_COMM_WORLD, &status);
#ifdef DEBUG
            //printf("%d:\t here0 %d\t Send? = %d\t Tag = %d\n", 
            //        rank, step, rank-step, rank-step);
#endif
        }
    }

    return MPI_Finalize(); 
}


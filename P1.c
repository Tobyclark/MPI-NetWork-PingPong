#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

#define COMM_MAX_SIZE 2097152
int main(int argc,char *argv[])
{
int rank,p;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&p);
printf("my rank=%d\n",rank);
printf("Rank=%d: number of processes =%d\n",rank,p);

if (rank == 0)
{
    struct timeval before;
    struct timeval after;
    struct timeval diff;
    int comm_size = 1;//size of communication in bytes
    char* in_buffer = (char*)malloc(sizeof(char) * 1048576 * 2);
    int source = 1;
    if (in_buffer == NULL)
    {
        printf("error: couldnt allocate input buffer");
        return 1;
            }
    while ((comm_size *= 2) <= COMM_MAX_SIZE)
    {
        gettimeofday(&before, NULL);
        MPI_Recv(in_buffer, COMM_MAX_SIZE, MPI_CHARACTER, source, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        gettimeofday(&after, NULL);
        //diff.tv_sec = after.tv_sec - before.tv_sec;
        //diff.tv_usec = after.tv_usec - before.tv_usec;
        timersub(&after, &before, &diff);
        printf("%d bytes were sent. The MPI_Recv call took %ld seconds and %ld microseconds \n",comm_size ,diff.tv_sec >    }

    free(in_buffer);
}

if (rank == 1)
{
    struct timeval before;
    struct timeval after;
    struct timeval diff;
    int comm_size = 1;//size of communication in bytes
    char* out_buffer = (char*)malloc(sizeof(char) * 1048576 * 2);
    int dest = 0;
    if (out_buffer == NULL)
    {
        printf("error: couldnt allocate output buffer");
             return 1;
    }
    while ((comm_size *= 2) <= COMM_MAX_SIZE)
    {
        gettimeofday(&before, NULL);
        MPI_Send(out_buffer, comm_size, MPI_CHARACTER, dest, 0, MPI_COMM_WORLD);
        gettimeofday(&after, NULL);
        //diff = after - before;
        timersub(&after, &before, &diff);
        printf("%d bytes were sent. The MPI_Send call took %ld seconds and %ld microseconds \n",comm_size ,diff.tv_sec >    }

    free(out_buffer);
}

MPI_Finalize();
}
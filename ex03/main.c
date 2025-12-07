#include <stdio.h>
#include <stdlib.h>
#include "3d_points_utils.h"


int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: mpirun -n <num_processes> %s <num_points> <min> <max>\n", argv[0]);
        return 1;
    }

    MPI_Datatype MPI_POINT3D;

    int num_points = atoi(argv[1]);
    float min = atof(argv[2]);
    float max = atof(argv[3]);

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Type_contiguous(3, MPI_FLOAT, &MPI_POINT3D);
	MPI_Type_commit(&MPI_POINT3D);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size<3){
        printf("This program requires at least 3 MPI processes.\n");
        MPI_Finalize();
        return 1;
    }

    if(rank==2){
        printf("Process %d is generating %d random 3D points with coordinates x, y, and z in range [%.2f , %.2f].\n", rank, num_points, min, max);
        point3d_t* points = get_random_3d_points(num_points, min, max);
        MPI_Send(points, num_points, MPI_POINT3D, 0, 0, MPI_COMM_WORLD);
        free(points);
    }

    if(rank==0){
        point3d_t* points = malloc(num_points * sizeof(point3d_t));
        MPI_Recv(points, num_points, MPI_POINT3D, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d 3D points:\n", rank, num_points);
        for(int i=0; i<num_points; i++){
            printf("Point %d: (%.2f, %.2f, %.2f)\n", i, points[i].x, points[i].y, points[i].z);
        }
        free(points);
    }

    MPI_Type_free(&MPI_POINT3D);
    MPI_Finalize();

    return 0;
}


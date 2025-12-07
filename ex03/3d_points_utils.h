#include <mpi.h>

typedef struct { float x, y, z; } point3d_t;
point3d_t* get_random_3d_points(int num_points, float lower_bound, float upper_bound);
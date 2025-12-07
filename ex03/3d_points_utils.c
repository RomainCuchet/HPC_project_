#include <stdlib.h>
#include "3d_points_utils.h"


/**
 * @brief Generates an array of random 3D points within the specified bounds.
 *
 * This function allocates memory for an array of `point3d_t` structures and fills each
 * element with random x, y, and z coordinates. Each coordinate is a floating-point value
 * uniformly distributed between `lower_bound` and `upper_bound`.
 *
 * @param num_points   The number of 3D points to generate.
 * @param lower_bound  The lower bound for each coordinate value.
 * @param upper_bound  The upper bound for each coordinate value.
 * @return A pointer to the dynamically allocated array of `point3d_t` structures.
 *         The caller is responsible for freeing the allocated memory.
 */
point3d_t* get_random_3d_points(int num_points, float lower_bound, float upper_bound) {
    point3d_t* points = malloc(num_points * sizeof(point3d_t));
    for (int i = 0; i < num_points; i++) {
        points[i].x = lower_bound + (float)rand() / RAND_MAX * (upper_bound - lower_bound);
        points[i].y = lower_bound + (float)rand() / RAND_MAX * (upper_bound - lower_bound);
        points[i].z = lower_bound + (float)rand() / RAND_MAX * (upper_bound - lower_bound);
    }
    return points;
}

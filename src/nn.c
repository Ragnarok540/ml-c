#define NN_IMPLEMENTATION
#include "nn.h"

int main(void) {
    Mat m = mat_alloc(4, 2);
    // mat_fill(m, 3);
    mat_rand(m, 1, 3);
    mat_print(m);

    Mat a = mat_alloc(2, 3);
    // mat_fill(a, 2);
    mat_rand(a, 4, 6);
    mat_print(a);

    Mat dst = mat_alloc(4, 3);

    mat_dot(dst, m, a);
    mat_print(dst);

    float id_data[4] = {
        1, 0,
        0, 1,
    };

    Mat b = { .rows = 2, .cols = 2, .es = id_data };
    mat_print(b);

    return 0;
}

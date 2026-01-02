#define NN_IMPLEMENTATION
#include "nn.h"

float td_sum[] = {
    0, 0,   0, 0,   0, 0,
    0, 0,   0, 1,   0, 1,
    0, 1,   0, 0,   0, 1,
    0, 1,   0, 1,   1, 0,
    0, 1,   1, 0,   1, 1,
    1, 0,   0, 1,   1, 1,
}

// XOR gate
float td_xor[] = {
    0, 0, 0,
    0, 1, 1,
    1, 0, 1,
    1, 1, 0,
};

// OR gate
float td_or[] = {
    0, 0, 0,
    0, 1, 1,
    1, 0, 1,
    1, 1, 1,
};

int main(void) {
    float *td = td_xor;

    size_t stride = 3;
    size_t n = 4;

    Mat ti = {
        .rows = n,
        .cols = 2,
        .stride = stride,
        .es = td,
    };

    Mat to = {
        .rows = n,
        .cols = 1,
        .stride = stride,
        .es = td + 2,
    };

    size_t arch[] = {2, 2, 1};
    // size_t arch[] = {2, 1}; // not for xor
    NN nn = nn_alloc(arch, ARRAY_LEN(arch));
    NN g = nn_alloc(arch, ARRAY_LEN(arch));
    nn_rand(nn, 0, 1);
    Mat row = mat_row(ti, 1);
    mat_copy(NN_INPUT(nn), row);
    printf("cost = %f\n", nn_cost(nn, ti, to));

    float eps = 1e-1f;
    float rate = 1e-1f;

    nn_finite_diff(nn, g, eps, ti, to);
    nn_learn(nn, g, rate);
    printf("cost = %f\n", nn_cost(nn, ti, to));

    for (size_t i = 0; i < 15000; i++) {
        nn_finite_diff(nn, g, eps, ti, to);
        nn_learn(nn, g, rate);
        printf("%zu: cost = %f\n", i, nn_cost(nn, ti, to));
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            MAT_AT(NN_INPUT(nn), 0, 0) = i;
            MAT_AT(NN_INPUT(nn), 0, 1) = j;
            nn_forward(nn);
            float y = MAT_AT(NN_OUTPUT(nn), 0, 0);

            printf("%zu ^ %zu = %f\n", i, j, y);
        }
    }

    NN_PRINT(nn);

    return 0;
}

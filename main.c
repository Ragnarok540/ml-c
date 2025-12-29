#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};
#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) {
    return (float) arc4random() / (float) UINT32_MAX;
}

float cost(float w, float b) {
    float result = 0.0f;

    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * w + b;
        float d = y - train[i][1];
        result += d * d;
    }

    result /= train_count;
    return result;
}

int main(void) {
    float w = rand_float() * 10.0f;
    float b = rand_float() * 5.0f;
    float eps = 1e-3f;
    float rate = 1e-3f;

    printf("before: %f\n", cost(w, b));

    for (size_t i = 0; i < 500; i++) {
        float dw = (cost(w + eps, b) - cost(w, b)) / eps;
        float db = (cost(w, b + eps) - cost(w, b)) / eps;
        w -= rate * dw;
        b -= rate * db;
        printf("cost = %f, w = %f, bias = %f\n", cost(w, b), w, b);
    }

    printf("----------------------------------------------\n");
    printf("%f\n", w);
    // printf("Hello C!\n");
    return 0;
}

// 1 54:00

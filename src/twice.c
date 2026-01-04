#include <stdio.h>
#include <stdlib.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10},
    {6, 12},
    {7, 14},
};

#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) {
    return (float) arc4random() / (float) UINT32_MAX;
}

float cost(float w) {
    float result = 0.0f;

    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * w;
        float d = y - train[i][1];
        result += d * d;
    }

    result /= train_count;
    return result;
}

float dcost(float w) {
    float result = 0.0f;
    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = train[i][1];
        result += 2 * x * (x * w - y);
    }
    result /= train_count;
    return result;
}

int main(void) {
    float w = rand_float() * 10.0f;
    float rate = 1e-2f;
    printf("before: %f\n", cost(w));

    for (size_t i = 0; i < 50; i++) {
        
#if 0
        float c = cost(w);
        float eps = 1e-3f;
        float dw = (cost(w + eps) - c) / eps;
        w -= rate * dw;
        printf("cost = %f, w = %f\n", c, w);
#else
        float dw = dcost(w);
        w -= rate * dw;
        printf("w = %f\n", w);
#endif

    }

    printf("----------------------------------------------\n");
    printf("w = %f\n", w);

    return 0;
}

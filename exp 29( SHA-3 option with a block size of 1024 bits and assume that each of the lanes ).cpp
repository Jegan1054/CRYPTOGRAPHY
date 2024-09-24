#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_SIZE_BITS 1024
#define LANE_SIZE_BITS 64
#define NUM_LANES (BLOCK_SIZE_BITS / LANE_SIZE_BITS)
#define CAPACITY_LANES 8

int check_nonzero_capacity(unsigned long long state[], int capacity_lanes) {
    for (int i = 0; i < capacity_lanes; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    unsigned long long state[NUM_LANES] = {0};
    int rounds = 0;

    srand(time(NULL));

    for (int i = CAPACITY_LANES; i < NUM_LANES; i++) {
        state[i] = rand();
    }

    while (!check_nonzero_capacity(state, CAPACITY_LANES)) {
        rounds++;
        for (int i = 0; i < CAPACITY_LANES; i++) {
            if (state[i] == 0) {
                state[i] = rand();
            }
        }
    }

    printf("All capacity lanes have nonzero bits after %d rounds.\n", rounds);
    return 0;
}


#include <stdint.h>
#include <stdio.h>
#include "mul11585.h"

static const num128 g = {.s = 4398046511104ULL};

num128 gexp(uint64_t x) {
    num128 result;
    num128 base = g;

    result.s = 1;

    
    while (x > 0) {
        if (x & 1) {            
            result = mul11585(result, base);
        }
        base = mul11585(base, base); 
        x >>= 1;                   
    }
    return result;
}

void test_gexp(uint64_t x, const char *expected_hex) {
    num128 result = gexp(x);

    // Print input
    printf("Testing g^%llu\n", (unsigned long long)x);

    // Print computed value
    printf("Computed:  ");
    print_num128(result);
    printf("\n");

    // Print expected value
    printf("Expected:  %s\n", expected_hex);

    // Compare by converting result to hex string
    char output[35];  // 2*16 bytes + "0x" + NULL
    snprintf(output, sizeof(output), "0x%016llx%016llx",
             (unsigned long long)result.t[1],
             (unsigned long long)result.t[0]);

    if (strcmp(output, expected_hex) == 0) {
        printf("✔ Test PASSED\n\n");
    } else {
        printf("✘ Test FAILED\n\n");
    }
}

int main() {
    // Test cases from the question
    test_gexp(257, "0x42F953471EDC00840EE23EECF13E4");
    test_gexp(112123123412345ULL, "0x21F33CAEB45F4D8BC716B91D838CC");
    test_gexp(18014398509482143ULL, "0x7A2A1DEC09D0325357DAACBF4868F");

    return 0;
}

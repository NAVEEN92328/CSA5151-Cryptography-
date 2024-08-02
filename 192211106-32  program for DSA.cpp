#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint32_t hash(const char *message) {
    uint32_t h = 0;
    while (*message) {
        h = (h << 5) + *message++;
    }
    return h;
}

void dsa_sign(const char *message, uint32_t private_key, uint32_t *r, uint32_t *s) {
    uint32_t k = rand();
    uint32_t h = hash(message);
    *r = (k * k) % private_key;
    *s = (h + private_key * (*r)) / k; 
}

uint32_t rsa_sign(const char *message, uint32_t private_key) {
    uint32_t h = hash(message);
    return h * private_key; 
}

int main() {
    srand(time(NULL));
    
    const char *message = "Hello, world!";
    uint32_t private_key = 12345; 

    uint32_t r1, s1, r2, s2;
    dsa_sign(message, private_key, &r1, &s1);
    dsa_sign(message, private_key, &r2, &s2);

    uint32_t rsa_sig1 = rsa_sign(message, private_key);
    uint32_t rsa_sig2 = rsa_sign(message, private_key);

    printf("Message: %s\n", message);
    printf("DSA Signature 1: (r: %u, s: %u)\n", r1, s1);
    printf("DSA Signature 2: (r: %u, s: %u)\n", r2, s2);
    printf("RSA Signature 1: %u\n", rsa_sig1);
    printf("RSA Signature 2: %u\n", rsa_sig2);

    return 0;
}


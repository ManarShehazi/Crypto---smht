#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ht48.c"


void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]){
    
    uint8_t msg[blen + 6];

    for( uint64_t i=0 ;i< 6 ;i++){
        msg[i] = m[i];
    }

    for( uint8_t i=0 ;i< 6 ;i++){
        msg[blen+i] = k[i];
    }

    ht48(blen+6,msg,h);
}

uint8_t keyrec(uint64_t blen, const uint8_t m[blen],uint8_t h[static 6]){


}

void tcz48_dm(const uint8_t m[static 16], uint8_t h[static 6]){
    
}


int main(){
    uint8_t k1[6] = {0, 1, 2, 3, 4, 5};
    uint8_t m1[6] = {9, 8, 7, 6, 5, 4};
    uint8_t *h1 = malloc(6 * sizeof(uint8_t));

    smht48(k1,6,m1,h1);
    printhash(h1);
    printf("\n");
    free(h1);


    uint8_t k2[6] = {0xE4, 0x16, 0x9F, 0x12, 0xD3, 0xBA};
    uint8_t m2[6] = {9, 8, 7, 6, 5, 4};
    uint8_t *h2 = malloc(6 * sizeof(uint8_t));

    smht48(k2,6,m2,h2);
    printhash(h2);
    printf("\n");
    free(h2);

}
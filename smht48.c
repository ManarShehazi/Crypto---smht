#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "ht48.h"
#include "ht48.c"

#define HASHTABLE_SIZE 16777216
#define HASH_VAL_SIZE 6
#define MSG_SIZE 16


/************************************** TO RUN THE CODE  ***********************************************/

/*
        **1** make
        **2** ./smht48
        **3** tests are written in the main, divided into 4 parts, better to comment unwanted parts - sorry for the inconvenience

*/

/****************************************** PART 1 ***************************************************/
void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]){
    
    uint8_t msg[blen + 6];

    for( uint64_t i=0 ;i< blen ;i++){
        msg[i] = m[i];
    }

    for( uint8_t i=0 ;i< 6 ;i++){
        msg[blen+i] = k[i];
    }

    ht48(blen+6,msg,h);
    //free(msg);
}

/******************************************* PART 2 **************************************************/
// using Brian Kernighan's algo to count nb of bits set to 1 in a byte
int nb_bits_equal_1(uint8_t byte){
    int count = 0;
    while(byte){
        byte &= byte - 1;
        count++;
    }
    return count;
}

//total nb od bits set to 1 in  akey
int total_bits_set_to_1(uint8_t key[6]) {
    int total_count = 0;
    for (int i = 0; i < 6; i++) {
        total_count += nb_bits_equal_1(key[i]);
    }
    return total_count;
}

//set a bit in the key at a certain position
void set_bit(uint8_t key[6], int position) {
    //set the desired bit in the 8 bits of the byte to 1
    // used OR to set only the corresponding bit whithout affectding the pthers
    key[position / 8] |= (1 << (position % 8));
}

//clear all bits in the key
void clear_key(uint8_t key[6]) {
    for (int i = 0; i < 6; i++) {
        key[i] = 0;
    }
}
/*****those functions were useful for debugging*****/

//to commpare hashes
int compare(const uint8_t *h1, const uint8_t *h2) {
    for (int i = 0; i < 6; i++) {
        if (h1[i] != h2[i]) 
            return 0;
    }
    return 1;
}

void keyrec(const uint8_t hash[6],uint64_t blen, const uint8_t message[blen]) {
    uint8_t key[6];
    uint8_t hash_result[6];

    //check all possible key values with 7 bits set to 1
        for (int i0 = 0; i0 < 48 - 6; i0++) {
        for (int i1 = i0 + 1; i1 < 48 - 5; i1++) {
            for (int i2 = i1 + 1; i2 < 48 - 4; i2++) {
                for (int i3 = i2 + 1; i3 < 48 - 3; i3++) {
                    for (int i4 = i3 + 1; i4 < 48 - 2; i4++) {
                        for (int i5 = i4 + 1; i5 < 48 - 1; i5++) {
                            for (int i6 = i5 + 1; i6 < 48; i6++) {
                                clear_key(key);
                                set_bit(key, i0);
                                set_bit(key, i1);
                                set_bit(key, i2);
                                set_bit(key, i3);
                                set_bit(key, i4);
                                set_bit(key, i5);
                                set_bit(key, i6);

                                smht48(key, blen, message, hash_result);

                                if (compare(hash_result, hash)) {
                                    printf("the key is: ");
                                    for (int i = 0; i < 6; i++) {
                                        printf("%02X", key[i]);
                                    }
                                    printf("\n");
                                    return; 
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("there is no such key\n");
}

/*int count_set_bits(uint8_t key[6]) {
    int count = 0;
    for (int i = 0; i < 6; i++) { 
        uint8_t byte = key[i];
        while (byte) {
            count += byte & 1;
            byte >>= 1;
        }
    }
    return count;
}*/
/**************************************** PART 3 - 1 *******************************************/
/*************************************hereeee*************************************/

unsigned int hash(const uint8_t* key) {
    unsigned int hashh = 0;
    for (int i = 0; i < HASH_VAL_SIZE; i++) {
        //multiply by a cst and then XOR
        hashh = (hashh * 33) ^ key[i];
    }
    return hashh % HASHTABLE_SIZE;
}

typedef struct hash_val{
    uint8_t key[HASH_VAL_SIZE];
    uint8_t msg[16];
    struct  hash_val* next;
}hash_val;

typedef struct hashtable{
    hash_val* table[HASHTABLE_SIZE];
} hashtable;

hashtable* construct_hashtable(){
    hashtable* h = malloc(sizeof(hashtable));
    if(h == NULL){
        printf("not able to create a hash table \n");
        exit(EXIT_FAILURE);
    }
    memset(h->table, 0, sizeof(h->table));
    return h; 
}

void insert(hashtable* h , const uint8_t* key, const uint8_t* msg) {
    unsigned int index = hash(key);

    hash_val* newNode = malloc(sizeof(hash_val));   
    if(newNode == NULL) {
        printf("hash inset failed");
        exit(EXIT_FAILURE);
    }  
    memcpy(newNode->key, key, HASH_VAL_SIZE);
    memcpy(newNode->msg, msg, 16);
    newNode->next = NULL;
    newNode->next = h->table[index];
    h->table[index] = newNode;
}
/****worksss***/
//to genearte random msgs
void generate_random(uint8_t *msg, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        msg[i] = rand() % 256;  //rand btraj3 int then % 256 gives byte
    }
}

uint8_t* get(hashtable* h, const uint8_t* key) {
    unsigned int index = hash(key);
    hash_val* val = h->table[index];
    while (val != NULL) {
        if (memcmp(val->key, key, HASH_VAL_SIZE) == 0) {
            return val->msg;  
        }
        val = val->next;
    }
    return NULL; 
}
hash_val* contains(hashtable* h, const uint8_t* key) {
    unsigned int index = hash(key);
    hash_val* val = h->table[index];
    while (val != NULL) {
        if (memcmp(val->key, key, HASH_VAL_SIZE) == 0) {
            return val; 
        }
        val = val->next;
    }
    return NULL; 
}

void destroy(hashtable* h) {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        hash_val* val = h->table[i];
        while (val != NULL) {
            hash_val* temp = val;
            val = val->next;
            free(temp);
        }
    }
    free(h);
}

void colsearch(uint8_t m1[16], uint8_t m2[16]) {
    struct hashtable* ht = construct_hashtable();

    uint8_t h[6];
    uint8_t m[16];
    uint8_t iv[6] = {IVB0, IVB1, IVB2, IVB3, IVB4, IVB5};

    while(true){
        generate_random(m,16);
        memcpy(h,iv,6);//not sure
        tcz48_dm(m, h);
        if(contains(ht,h)){
            //if h already exosts
            uint8_t* origM = get(ht, h);
            //printf("collision found:\n");
            //printf("the common hash is  ");
            //printhash(h); 
            //printf("m1: ");
            //printhash(origM);
            //printf("\nm2: ");
            //printhash(m);
            //printf("\n");
            memcpy(m1, origM, 16);
            memcpy(m2, m, 16);
            break;
        } else {
            insert(ht, h, m);
        }
    }

    destroy(ht);

}


/******************************************* PART 3 - 2 **************************************************/
//same fctn generate random
void draw_random_key(uint8_t k[6]) {
    for (int i = 0; i < 6; i++) {
        k[i] = rand() % 256;
    }
}
void smht48ef(const uint8_t m1[16], const uint8_t m2[16]) {
    uint8_t k[6];    
    uint8_t mac1[6];  
    uint8_t mac2[6];  

    draw_random_key(k);

    smht48(k, 16, m1, mac1);
    smht48(k, 16, m2, mac2);

    if (memcmp(mac1, mac2, 6) == 0) {
        printf("collision in smht48 is found\n");
        printf("the key is: ");
        printhash(k);
        printf("\nmac for both m1 and m2: ");
        printhash(mac1);
        printf("\n");
    } else {
        printf("no collision\n");
    }
}

/************************** MAIN *******************************/

int main(){
    srand(time(NULL));

    /**************** part - 1 - ****************/
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

    
    /**************** part - 2 - ****************/

    //testing bit counting fctn
    //printf("nb of bits equal to 1 in %d is %d \n",50,nb_bits_equal_1(50));

    // The message value provided in the example
    uint8_t message[6] = {9, 8, 7, 6, 5, 4};
    
    // The desired tag value provided in the example
    uint8_t desired_hash[6] = {0x7D, 0x1D, 0xEF, 0xA0, 0xB8, 0xAD};

    // Call the keyrec function to search for the key
    //herrererererere
    keyrec(desired_hash,6, message);


    //to verify
    uint8_t k3[6] = {0x00, 0x16, 0x18, 0x00, 0x90, 0x00};
    uint8_t m3[6] = {9, 8, 7, 6, 5, 4};
    uint8_t *h3 = malloc(6 * sizeof(uint8_t));

    smht48(k3,6,m3,h3);
    printhash(h3);
    printf("\n");
    free(h3);

    /**************** part - 3 - ****************/

    //colsearch();
    uint8_t m6[16], m7[16];

    // Call colsearch to find the colliding messages
    colsearch(m6, m7);

    printf("collision found:\n");
    printf("message 1: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X", m6[i]);
    }
    printf("\n");

    printf("message 2: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X", m7[i]);
    }
    printf("\n");


    /*************** part - 4 - ****************/
    printf("\n");
    printf("here1");
    printf("\n");

    smht48ef(m6,m7);

    printf("\n");
    printf("here2");
    printf("\n");


}

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define MAX_TRANSACTIONS 10
#define DIFFICULTY 4  // Number of leading zeros required in hash
#define HASH_SIZE 65  // SHA256 hash string length (64 chars + null terminator)

// Structure for a transaction
typedef struct {
    char item_id[32];
    char description[256];
    char signature[65];  // Simple hash as signature
} Transaction;

// Structure for a block
typedef struct Block {
    int index;
    time_t timestamp;
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_count;
    char previous_hash[HASH_SIZE];
    char hash[HASH_SIZE];
    int nonce;
    struct Block* next;
} Block;

// Structure for the blockchain
typedef struct {
    Block* head;
    int difficulty;
} Blockchain;

// Function declarations
void calculate_hash(Block* block, char* hash);
void create_blockchain(Blockchain* chain);
void add_transaction(Blockchain* chain, const char* item_id, const char* description);
void mine_block(Blockchain* chain);
void print_blockchain(const Blockchain* chain);
int verify_blockchain(const Blockchain* chain);

#endif
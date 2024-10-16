#include "blockchain.h"

// Helper function to calculate SHA256 hash using EVP interface
void calculate_sha256(const char* input, unsigned char* hash) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    unsigned int length = EVP_MD_size(md);

    EVP_DigestInit_ex(context, md, NULL);
    EVP_DigestUpdate(context, input, strlen(input));
    EVP_DigestFinal_ex(context, hash, &length);
    
    EVP_MD_CTX_free(context);
}

// Calculate hash of a block
void calculate_hash(Block* block, char* hash) {
    char input[1024];
    unsigned char hash_bytes[EVP_MAX_MD_SIZE];
    
    // Concatenate block data
    snprintf(input, sizeof(input), "%d%ld%d%s", 
             block->index, 
             block->timestamp, 
             block->nonce,
             block->previous_hash);
    
    // Add transaction data to input
    for (int i = 0; i < block->transaction_count; i++) {
        strcat(input, block->transactions[i].item_id);
        strcat(input, block->transactions[i].description);
    }
    
    // Calculate hash using EVP interface
    calculate_sha256(input, hash_bytes);
    
    // Convert to hex string
    for(int i = 0; i < 32; i++) {
        sprintf(hash + (i * 2), "%02x", hash_bytes[i]);
    }
    hash[64] = '\0';
}

// Initialize a new blockchain
void create_blockchain(Blockchain* chain) {
    chain->head = NULL;
    chain->difficulty = DIFFICULTY;
    
    // Create genesis block
    Block* genesis = (Block*)malloc(sizeof(Block));
    genesis->index = 0;
    genesis->timestamp = time(NULL);
    genesis->transaction_count = 0;
    genesis->nonce = 0;
    strcpy(genesis->previous_hash, "0");
    genesis->next = NULL;
    
    calculate_hash(genesis, genesis->hash);
    chain->head = genesis;
}

// Add a new transaction to the pending transactions
void add_transaction(Blockchain* chain, const char* item_id, const char* description) {
    Block* current = chain->head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    if (current->transaction_count >= MAX_TRANSACTIONS) {
        printf("Block full. Mine a new block first.\n");
        return;
    }
    
    Transaction* trans = &current->transactions[current->transaction_count];
    strncpy(trans->item_id, item_id, sizeof(trans->item_id) - 1);
    strncpy(trans->description, description, sizeof(trans->description) - 1);
    
    // Create simple signature (hash of item_id + description)
    char combined[289];
    unsigned char sig_bytes[EVP_MAX_MD_SIZE];
    
    snprintf(combined, sizeof(combined), "%s%s", item_id, description);
    calculate_sha256(combined, sig_bytes);
    
    for(int i = 0; i < 32; i++) {
        sprintf(trans->signature + (i * 2), "%02x", sig_bytes[i]);
    }
    
    current->transaction_count++;
    printf("Transaction added successfully.\n");
}

// Mine a new block
void mine_block(Blockchain* chain) {
    Block* current = chain->head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    if (current->transaction_count == 0) {
        printf("No transactions to mine.\n");
        return;
    }
    
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->index = current->index + 1;
    new_block->timestamp = time(NULL);
    new_block->transaction_count = 0;
    new_block->nonce = 0;
    strcpy(new_block->previous_hash, current->hash);
    new_block->next = NULL;
    
    // Mining process (Proof of Work)
    char hash[HASH_SIZE];
    do {
        new_block->nonce++;
        calculate_hash(new_block, hash);
    } while (strncmp(hash, "0000", chain->difficulty) != 0);
    
    strcpy(new_block->hash, hash);
    current->next = new_block;
    printf("Block mined successfully.\n");
}

// Print the entire blockchain
void print_blockchain(const Blockchain* chain) {
    Block* current = chain->head;
    while (current != NULL) {
        printf("\nBlock #%d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Nonce: %d\n", current->nonce);
        printf("Previous Hash: %s\n", current->previous_hash);
        printf("Hash: %s\n", current->hash);
        printf("Transactions:\n");
        
        for (int i = 0; i < current->transaction_count; i++) {
            printf("  Item ID: %s\n", current->transactions[i].item_id);
            printf("  Description: %s\n", current->transactions[i].description);
            printf("  Signature: %s\n", current->transactions[i].signature);
        }
        
        current = current->next;
    }
}

// Verify blockchain integrity
int verify_blockchain(const Blockchain* chain) {
    Block* current = chain->head;
    char calculated_hash[HASH_SIZE];
    
    while (current->next != NULL) {
        calculate_hash(current, calculated_hash);
        if (strcmp(calculated_hash, current->hash) != 0) {
            return 0;  // Hash mismatch
        }
        if (strcmp(current->hash, current->next->previous_hash) != 0) {
            return 0;  // Chain broken
        }
        current = current->next;
    }
    
    return 1;  // Blockchain is valid
}
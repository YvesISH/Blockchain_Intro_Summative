#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_JOBS 100
#define MAX_STR_LEN 256

// Define the structure for each job listing block
typedef struct JobListing {
    char title[MAX_STR_LEN];
    char company[MAX_STR_LEN];
    char location[MAX_STR_LEN];
    char description[MAX_STR_LEN];
    long timestamp;
    char hash[SHA256_DIGEST_LENGTH * 2 + 1];  // 64 characters for SHA-256 hash
    char prev_hash[SHA256_DIGEST_LENGTH * 2 + 1];  // Previous block's hash
} JobListing;

// Global blockchain array and size
JobListing blockchain[MAX_JOBS];
int blockchain_size = 0;

/**
 * Function to calculate the SHA-256 hash of the job listing
 */
void calculate_hash(JobListing* job) {
    char input[2048];  // Increased buffer size to avoid truncation warning
    snprintf(input, sizeof(input), "%s%s%s%s%ld%s",
             job->title, job->company, job->location, job->description, job->timestamp, job->prev_hash);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(job->hash + (i * 2), "%02x", hash[i]);
    }
    job->hash[64] = '\0';  // Null-terminate the hash string
}

/**
 * Function to add a new job listing to the blockchain
 */
void add_job_listing() {
    if (blockchain_size >= MAX_JOBS) {
        printf("Job listing limit reached!\n");
        return;
    }

    JobListing job;
    printf("Enter job title: ");
    scanf(" %[^\n]s", job.title);
    printf("Enter company: ");
    scanf(" %[^\n]s", job.company);
    printf("Enter location: ");
    scanf(" %[^\n]s", job.location);
    printf("Enter job description: ");
    scanf(" %[^\n]s", job.description);

    // Get the current timestamp
    job.timestamp = time(NULL);

    // Set the previous hash: if this is the first block, prev_hash is "0"
    if (blockchain_size == 0) {
        strcpy(job.prev_hash, "0");
    } else {
        strcpy(job.prev_hash, blockchain[blockchain_size - 1].hash);
    }

    // Calculate the hash of the current job block
    calculate_hash(&job);

    // Add the job to the blockchain
    blockchain[blockchain_size] = job;
    blockchain_size++;

    printf("Job listing added successfully!\n");
}

/**
 * Function to search job listings by a keyword
 */
void search_job_by_keyword() {
    char keyword[MAX_STR_LEN];
    printf("Enter keyword to search: ");
    scanf(" %[^\n]s", keyword);

    int found = 0;
    for (int i = 0; i < blockchain_size; i++) {
        if (strstr(blockchain[i].title, keyword) ||
            strstr(blockchain[i].company, keyword) ||
            strstr(blockchain[i].location, keyword) ||
            strstr(blockchain[i].description, keyword)) {
            printf("Job found:\n");
            printf("Title: %s\n", blockchain[i].title);
            printf("Company: %s\n", blockchain[i].company);
            printf("Location: %s\n", blockchain[i].location);
            printf("Description: %s\n", blockchain[i].description);
            printf("-----------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No job listings found with the keyword '%s'.\n", keyword);
    }
}

/**
 * Function to verify the integrity of the blockchain
 */
void verify_blockchain_integrity() {
    for (int i = 1; i < blockchain_size; i++) {
        if (strcmp(blockchain[i].prev_hash, blockchain[i - 1].hash) != 0) {
            printf("Blockchain integrity compromised at block %d!\n", i);
            return;
        }
    }
    printf("Blockchain integrity verified. All blocks are intact.\n");
}

/**
 * Function to print the details of all blocks in the blockchain.
 */
void print_blockchain() {
    for (int i = 0; i < blockchain_size; i++) {
        printf("Block %d\n", i);
        printf("Title: %s\n", blockchain[i].title);
        printf("Company: %s\n", blockchain[i].company);
        printf("Location: %s\n", blockchain[i].location);
        printf("Description: %s\n", blockchain[i].description);
        printf("Timestamp: %ld\n", blockchain[i].timestamp);
        printf("Previous Hash: %s\n", blockchain[i].prev_hash);
        printf("Current Hash: %s\n", blockchain[i].hash);
        printf("-----------------------------\n");
    }
}

/**
 * Print the menu options for the user.
 */
void print_menu() {
    printf("\nBlockchain-based Job Directory\n");
    printf("1. Add a job listing\n");
    printf("2. Search for a job by keyword\n");
    printf("3. Verify blockchain integrity\n");
    printf("4. Print blockchain details\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_job_listing();
                break;
            case 2:
                search_job_by_keyword();
                break;
            case 3:
                verify_blockchain_integrity();
                break;
            case 4:
                print_blockchain();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
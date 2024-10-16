#ifndef JOB_DIRECTORY_H
#define JOB_DIRECTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_TITLE 256
#define MAX_COMPANY 256
#define MAX_LOCATION 256
#define MAX_DESCRIPTION 512
#define MAX_HASH 65

// Structure for a job listing (a block in the blockchain)
typedef struct Job {
    char title[MAX_TITLE];
    char company[MAX_COMPANY];
    char location[MAX_LOCATION];
    char description[MAX_DESCRIPTION];
    time_t timestamp;
    char prev_hash[MAX_HASH];
    char hash[MAX_HASH];
    struct Job* next;
} Job;

// Function declarations
Job* create_job(const char* title, const char* company, const char* location, const char* description, const char* prev_hash);
void add_job(Job** head, Job* new_job);
void calculate_hash(Job* job);
void search_job(Job* head, const char* keyword);
int verify_integrity(Job* head);

#endif
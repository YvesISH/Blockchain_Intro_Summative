## Blockchain-based Job Directory

##### Description

This is a simple blockchain-based job directory application implemented in C. The application simulates a blockchain system where each job listing is treated as a block. Each block contains information such as job title, company, location, job description, and a timestamp. The blocks are cryptographically hashed using SHA-256 to ensure data integrity and linked to the previous block in the chain, mimicking the structure of a blockchain.

The application provides the following functionalities:

##### Add new job listings.

Search for jobs by keyword (title, company, location, or description).
Verify the integrity of the blockchain to detect tampering.
Display all the blocks (job listings) in the blockchain.

##### Features

Add Job Listing: Users can add a new job listing by inputting the job details. Each listing is treated as a block in the blockchain and includes the cryptographic hash of the previous block.
Search Jobs: Users can search for job listings based on a keyword, which searches through the job title, company, location, or description.
Verify Integrity: The application checks if the blockchain has been tampered with by comparing the hashes of the blocks.
View Blockchain: Users can view all job listings (blocks) and their associated details, including the cryptographic hash of each block.


##### Blockchain Principles
The application mimics a blockchain structure by:

Immutability: Once a job listing (block) is added to the chain, its hash is based on the contents of the job listing and the previous block's hash, making it extremely difficult to modify without being detected.
Data Integrity: The SHA-256 hashing mechanism ensures that each block in the blockchain is securely linked to the previous one. Any unauthorized modification will break the chain and trigger a failed verification check.


##### Hashing Mechanism

Each job listing block includes a hash generated using the SHA-256 algorithm. The hash is calculated based on:

Job title
Company
Location
Job description
Timestamp
Previous block's hash
The calculated hash is used to ensure the integrity of each block in the blockchain. If the contents of a block are modified, the hash will no longer match, and the integrity check will fail.

##### Requirements

OpenSSL library for cryptographic hashing (SHA-256).


##### Compilation and Execution

##### Prerequisites
Make sure you have the OpenSSL library installed. You can install it using:


###### sudo apt-get install libssl-dev

##### Compile
To compile the application, run the following command:

###### gcc -o job_directory job_directory.c -lssl -lcrypto

##### Run
To execute the program, use the following command:


###### ./job_directory
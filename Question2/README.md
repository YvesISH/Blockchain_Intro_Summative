# Blockchain-based Supply Chain Tracking System

### Overview

###### This is a simple implementation of a blockchain-based supply chain tracking system written in C. The system allows users to create and maintain a blockchain that records supply chain transactions, ensuring transparency and immutability of supply chain records.


### Features

##### - Blockchain data structures with cryptographic hashing
##### - Transaction management with digital signatures
##### - Proof-of-work block mining
##### - Blockchain verification
##### - Command-line interface (CLI) for interaction
##### - Supply chain record tracking

### Prerequisites

###### GCC compiler
###### OpenSSL development libraries
###### Linux/Unix environment (For Windows users, WSL is recommended)

### Installation

##### Install the required OpenSSL development libraries:

#### For Ubuntu/Debian
###### sudo apt-get update
###### sudo apt-get install libssl-dev

#### For Fedora
###### sudo dnf install openssl-devel

#### For CentOS/RHEL
###### sudo yum install openssl-devel

#### Clone or download the source files:


###### blockchain.h
###### blockchain.c
###### main.c


#### Compile the program:

###### gcc -o blockchain main.c blockchain.c -lssl -lcrypto

### Usage
#### Run the compiled program:
###### ./blockchain


##### The program provides a menu-driven interface with the following options:

###### 1.Create new blockchain
###### 2.Add transaction
###### 3.Mine block
###### 4.Print blockchain
###### 5.Verify blockchain
###### 6.Exit
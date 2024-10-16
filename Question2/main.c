#include "blockchain.h"

void print_menu() {
    printf("\nBlockchain Supply Chain Tracking System\n");
    printf("1. Create new blockchain\n");
    printf("2. Add transaction\n");
    printf("3. Mine block\n");
    printf("4. Print blockchain\n");
    printf("5. Verify blockchain\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Blockchain chain;
    int choice;
    char item_id[32];
    char description[256];
    int blockchain_created = 0;
    
    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                if (!blockchain_created) {
                    create_blockchain(&chain);
                    blockchain_created = 1;
                    printf("Blockchain created successfully.\n");
                } else {
                    printf("Blockchain already exists.\n");
                }
                break;
                
            case 2:
                if (!blockchain_created) {
                    printf("Please create blockchain first.\n");
                    break;
                }
                printf("Enter item ID: ");
                fgets(item_id, sizeof(item_id), stdin);
                item_id[strcspn(item_id, "\n")] = 0;
                
                printf("Enter description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;
                
                add_transaction(&chain, item_id, description);
                break;
                
            case 3:
                if (!blockchain_created) {
                    printf("Please create blockchain first.\n");
                    break;
                }
                mine_block(&chain);
                break;
                
            case 4:
                if (!blockchain_created) {
                    printf("Please create blockchain first.\n");
                    break;
                }
                print_blockchain(&chain);
                break;
                
            case 5:
                if (!blockchain_created) {
                    printf("Please create blockchain first.\n");
                    break;
                }
                if (verify_blockchain(&chain)) {
                    printf("Blockchain is valid.\n");
                } else {
                    printf("Blockchain verification failed!\n");
                }
                break;
                
            case 6:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice.\n");
        }
    }
    
    return 0;
}
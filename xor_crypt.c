#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xor_crypt(const char *key, FILE *input, FILE *output) {
    size_t key_len = strlen(key);
    size_t key_index = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        fputc(c ^ key[key_index], output);
        key_index = (key_index + 1) % key_len;
    }
}

void print_menu() {
    printf("File Cryptography Tool\n");
    printf("======================\n");
    printf("1. Encrypt file\n");
    printf("2. Decrypt file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    char mode[10];
    char key[256];
    char input_filename[256];
    char output_filename[256];
    int choice;

    while (1) {
        print_menu();
        scanf("%d", &choice);

        if (choice == 3) {
            break;
        }

        printf("Enter the key: ");
        scanf("%s", key);
        printf("Enter the input file name: ");
        scanf("%s", input_filename);
        printf("Enter the output file name: ");
        scanf("%s", output_filename);

        if (choice == 1) {
            strcpy(mode, "encrypt");
        } else if (choice == 2) {
            strcpy(mode, "decrypt");
        } else {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        FILE *input = fopen(input_filename, "rb");
        if (!input) {
            fprintf(stderr, "Failed to open input file '%s'.\n", input_filename);
            exit(1);
        }

        FILE *output = fopen(output_filename, "wb");
        if (!output) {
            fclose(input);
            fprintf(stderr, "Failed to open output file '%s'.\n", output_filename);
            exit(1);
        }

        xor_crypt(key, input, output);
        printf("File %s successfully.\n", mode);

        fclose(input);
        fclose(output);
    }

    return 0;
}
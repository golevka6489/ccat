#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Function to process and print the contents of a single file
void process_file(const char *filename) {
    FILE *file;
    int c;

    // 1. Print the filename header
    // The format could be customized, e.g., "==> filename <==\n"
    printf("\033[1;31m\n--- %s ---\033[0m\n", filename);

    // 2. Open the file for reading
    file = fopen(filename, "r");

    // Check if the file opened successfully
    if (file == NULL) {
        // Print an error message using the standard error stream
        // strerror(errno) provides a human-readable description of the error
        fprintf(stderr, "ccat: cannot open %s: %s\n", filename, strerror(errno));
        return; // Move to the next file
    }

    // 3. Read the file character by character and print to standard output
    // The loop continues until the end-of-file (EOF) marker is reached
    while ((c = fgetc(file)) != EOF) {
        if (putchar(c) == EOF) {
            // Error handling for output
            fprintf(stderr, "ccat: error writing to stdout\n");
            break;
        }
    }

    // 4. Close the file
    if (fclose(file) == EOF) {
        fprintf(stderr, "ccat: error closing file %s\n", filename);
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Standard Unix utilities return an error code if they fail
    int status = EXIT_SUCCESS;

    // Check if any arguments (filenames) were provided
    if (argc < 2) {
        // If no arguments, we could optionally read from standard input (like cat)
        // For simplicity, we'll just print usage and exit.
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Loop through all command-line arguments, starting at index 1
    // (index 0 is the program name itself)
    for (int i = 1; i < argc; i++) {
        process_file(argv[i]);
    }

    // Add a final newline for clean output after the last file's content
    printf("\n");

    return status;
}

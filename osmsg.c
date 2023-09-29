##define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Syscall numbers
#define SEND_MSG 441
#define GET_MSG 442

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Not enough entries.");
        printf("To Send Message: osmsg -s [sendee] [message]\n");
        printf("To Read your Messages: osmsg -r\n");
        return 1;
    }

    if (strcmp(argv[1], "-s") == 0 && argc >= 4) {
        // Sending a message
        const char* sendee = argv[2];
        const char* message = argv[3];

         if (sendee == NULL || message == NULL) {
            printf( "Invalid sendee or message.\n");
            return 1;
        }


        size_t remaining_space = 256 - strlen(message) - 1; // -1 for the space character

        // Concatenate additional words into the message if provided
        for (int i = 4; i < argc; i++) {
        strncat(message, " ", remaining_space);
        strncat(message, argv[i], remaining_space);
        remaining_space = 256 - strlen(message) - 1; // Update remaining space
            if (remaining_space <= 0) {
                break; // Avoid buffer overflow
            }
        }

        // Get the sender's username using getenv()
        const char* sender = getenv("USER");
        if (!sender) {
            printf("Error getting sender's username");
            return 1;
        }

        long send_result = syscall(SEND_MSG, sendee, message, sender);
        if (send_result == 0) {
            printf("Your message was sent\n");
        } else if (send_result == -1) {
            printf("Error sending message");
        } else {
            printf("Error code: %ld\n", send_result);
        }
    } else if (strcmp(argv[1], "-r") == 0 && argc == 2) {
        // Read messages (message)
        char message[256];
        char sender[15];

        // Get the sendee's username using getenv()
        const char* sendee = getenv("USER");
        if (!sendee) {
            printf("Error getting sendee's username");
            return 1;
        }

        long get_result = syscall(GET_MSG, sendee, message, sender);

        if (get_result == 0) {
            printf("%s said: \"%s\"\n", sender, message);
        } else if (get_result == -1) {
            printf("Empty Inbox :(.\n");
        } else if (get_result == 1) {
            printf("%s said: \"%s\"\n", sender, message);
            printf("You've got more mail!\n");
        } else {
            printf("Error getting messages");
        }
    } else {
        printf("Entries invalid");
        printf("To Send Message: osmsg -s [sendee] [message]\n");
        printf("To Read your Messages: osmsg -r\n");
        return 1;
    }

    return 0;
}

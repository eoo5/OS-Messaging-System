#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Syscall numbers
#define SEND_MSG 441
#define GET_MSG 442
#define MAX_USER_LENGTH 15
#define MAX_MESSAGE_LENGTH 256

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Not enough entries.");
        return 1;
    }

    if (argc >= 4 && strcmp(argv[1], "-s") == 0) {
        // Sending a message
        const char* sendee = argv[2];
        const char* message = argv[3];
        
        // Check for buffer overflow or if the sendee or message is null
            if (message == NULL){
                printf("Invalid sendee or message.\n");
                return 1;
            }
        
            if(strlen(sendee) > MAX_USER_LENGTH || sendee == NULL) { 
                printf( "Invalid sendee.\n");
                return 1;
        }

        // calculate remaining_space to prevent buffer overflow
        size_t remaining_space = MAX_MESSAGE_LENGTH - strlen(message) - 2; // -1 for the space character

        // Concatenate additional words into the message if provided
        for (int i = 4; i < argc; i++) {
            strncat(message, " ", remaining_space);
            strncat(message, argv[i], remaining_space);
            remaining_space = MAX_MESSAGE_LENGTH - strlen(message) - 2; // Update remaining space
            if (remaining_space <= 0) {
                break; // Avoid buffer overflow
            }
        }

        // Get the sender's username 
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
        
    //If reading inbox
    } else if (strcmp(argv[1], "-r") == 0 && argc == 2) {
        // Read messages (message)
        char message[MAX_MESSAGE_LENGTH];
        char sender[MAX_USER_LENGTH];

        // Get the sendee's username using getenv()
        const char* sendee = getenv("USER");
        if (!sendee) {
            printf("Error getting sendee's username");
            return 1;
        }

        long get_result = syscall(GET_MSG, sendee, message, sender);
//Handle inbox result, 0 if one message, -1 if none, 1 if more.
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
        return 1;
    }

    return 0;
}

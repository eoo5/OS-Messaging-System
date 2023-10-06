#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Syscall numbers
#define SEND_MSG 441
#define GET_MSG 442
#define MAX_USER_LENGTH 32
#define MAX_MESSAGE_LENGTH 256

int main(int argc, char* argv[]) {
    
//Catch not enough arguments error.
    if (argc < 2) {
        printf("Not enough entries. Try\n");
        printf("./osmsg.c -s <sendee> <msg>\n");
        printf("./osmsg.c -r\n");
        return 1;
    }

    if (argc >= 4 && strcmp(argv[1], "-s") == 0) {
        // Sending a message
        const char* sendee = argv[2];
        char message[MAX_MESSAGE_LENGTH]; // Allocate a buffer for the message
        strcpy(message, argv[3]); // Copy the initial message so that we can use strncat
        
        // Check for buffer overflow or if the sendee or message is null
            if (message == NULL|| sendee == NULL){
                printf("Invalid sendee or message.\n");
                return 1;
            }
        
            if(strlen(sendee) > MAX_USER_LENGTH || sendee == NULL) { 
                printf( "Invalid sendee.\n");
                return 1;
        }

        // calculate remaining_space to prevent buffer overflow
        size_t remaining_space = MAX_MESSAGE_LENGTH - strlen(message) - 1; // -1 for the space character

        // add words separated by space
        for (int i = 4; i < argc; i++) {
            if (remaining_space <= 0) {
                break; // Avoid buffer overflow
            }
            strncat(message, " ", remaining_space);
            strncat(message, argv[i], remaining_space);
            remaining_space = MAX_MESSAGE_LENGTH - strlen(message) - 1; // Update remaining space
        }

        // Fetch sender's username 
        const char* sender = getenv("USER");
        if (!sender) {
            printf("Error getting sender's username\n");
            return 1;
        }
        //Call send_result
        
        long send_result = syscall(SEND_MSG, sendee, message, sender);
        
        if (send_result == 0) {
            printf("Your message was sent\n");
        } else if (send_result == -1) {
            printf("Error sending message\n");
        } else {
            printf("Error code: %ld\n", send_result);
        }
        
    //If reading inbox and input is valid
    } else if (strcmp(argv[1], "-r") == 0 && argc == 2) {
    
        // Get the sendee's username using getenv()
        const char* sendee = getenv("USER");
        if (!sendee) {
            printf("Error getting sendee's username\n");
            return 1;
        }
        char message[MAX_MESSAGE_LENGTH];
        char sender[MAX_USER_LENGTH];
        while (1) {
        // Read messages (message) and sender

            
        long get_result = syscall(GET_MSG, sendee, message, sender);
//Handle inbox result, 0 if one message, -1 if none, 1 if more.
        if (get_result == 0) {
            printf("%s said: \"%s\"\n", sender, message);
            break;
        } else if (get_result == -1) {
            printf("Empty Inbox :(.\n");
            break;
        } else if (get_result == 1) {
            printf("%s said: \"%s\"\n", sender, message);
            printf("You've got more mail!\n");
        } else {
           printf("Error getting messages (Error code: %ld)\n", get_result);
           break; // Exit the loop on error
        }
      }
    } else {
        printf("Entries invalid\n");
        
        return 1;
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_USERNAME_LENGTH 32
#define MAX_MESSAGE_LENGTH 256

int main() {
    char sender[MAX_USERNAME_LENGTH] = "User1";
    char recipient[MAX_USERNAME_LENGTH] = "User2";
    char message[MAX_MESSAGE_LENGTH] = "Hello, User2!";

    // Send a message
    long send_result = syscall(SYS_cs1550_send_msg, recipient, message, sender);
    if (send_result == 0) {
        printf("Message sent successfully.\n");
    } else {
        perror("Error sending message");
        return 1;
    }

    // Retrieve a message
    char received_message[MAX_MESSAGE_LENGTH];
    char received_sender[MAX_USERNAME_LENGTH];
    long get_result = syscall(SYS_cs1550_get_msg, recipient, received_message, received_sender);
    if (get_result == 0) {
        printf("Received message from %s: %s\n", received_sender, received_message);
    } else if (get_result == -1) {
        printf("No messages for %s.\n", recipient);
    } else {
        perror("Error retrieving message");
        return 1;
    }

    return 0;
}

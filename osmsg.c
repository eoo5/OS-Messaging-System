#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Define your custom syscall numbers
#define CS1550_SEND_MSG 442
#define CS1550_GET_MSG 443

// Custom syscall prototypes
long sys_cs1550_send_msg(const char __user *to, const char __user *msg, const char __user *from);
long sys_cs1550_get_msg(const char __user *to, char __user *msg, char __user *from);

int main() {
    const char *sender = "user1";
    const char *recipient = "user2";
    const char *message = "Hello, user2!";
    char received_message[256];

    // Send a message
    long send_result = sys_cs1550_send_msg(recipient, message, sender);
    if (send_result == 0) {
        printf("Message sent successfully!\n");
    } else {
        printf("Message sending failed (Error code: %ld)\n", send_result);
    }

    // Get a message
    long get_result = sys_cs1550_get_msg(sender, received_message, recipient);
    if (get_result == 0) {
        printf("Received message: %s\n", received_message);
    } else {
        printf("Message retrieval failed (Error code: %ld)\n", get_result);
    }

    return 0;
}


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>
#include <errno.h>

// Define syscall numbers for the custom syscalls
#define CS1550_SEND_MSG_SYSCALL_NUMBER 441
#define CS1550_GET_MSG_SYSCALL_NUMBER 442

int main() {
    long send_result, get_result;

    // Try to make the sys_cs1550_send_msg syscall
    send_result = syscall(CS1550_SEND_MSG_SYSCALL_NUMBER, "recipient", "Hello", "sender");
    if (send_result == -1) {
        if (errno == ENOSYS) {
            printf("sys_cs1550_send_msg does not exist in the kernel.\n");
        } else {
            perror("Error making sys_cs1550_send_msg syscall");
        }
    } else {
        printf("sys_cs1550_send_msg exists in the kernel.\n");
    }

    // Try to make the sys_cs1550_get_msg syscall
    get_result = syscall(CS1550_GET_MSG_SYSCALL_NUMBER, "recipient", "msg", "sender");
    if (get_result == -1) {
        if (errno == ENOSYS) {
            printf("sys_cs1550_get_msg does not exist in the kernel.\n");
        } else {
            perror("Error making sys_cs1550_get_msg syscall");
        }
    } else {
        printf("sys_cs1550_get_msg exists in the kernel.\n");
    }

    return 0;
}

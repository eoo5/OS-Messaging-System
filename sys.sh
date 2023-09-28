#!/bin/bash

# Define the new system call names
SYSCALL_1_NAME="cs1550_send_msg"
SYSCALL_2_NAME="cs1550_get_msg"

# Define the system call numbers
SYSCALL_1_NUMBER=441
SYSCALL_2_NUMBER=442

# Update include/uapi/asm-generic/unistd.h
UNISTD_HEADER="<KERNEL_SOURCE_DIRECTORY>/include/uapi/asm-generic/unistd.h"
sed -i "/#define __NR_syscalls/c\#define __NR_syscalls 443" $UNISTD_HEADER
echo "#define __NR_${SYSCALL_1_NAME} $SYSCALL_1_NUMBER" >> $UNISTD_HEADER
echo "#define __NR_${SYSCALL_2_NAME} $SYSCALL_2_NUMBER" >> $UNISTD_HEADER

# Update arch/x86/entry/syscalls/syscall_64.tbl
SYS_CALL_64_TBL="<KERNEL_SOURCE_DIRECTORY>/arch/x86/entry/syscalls/syscall_64.tbl"
echo "$SYSCALL_1_NUMBER common $SYSCALL_1_NAME sys_$SYSCALL_1_NAME" >> $SYS_CALL_64_TBL
echo "$SYSCALL_2_NUMBER common $SYSCALL_2_NAME sys_$SYSCALL_2_NAME" >> $SYS_CALL_64_TBL

# Update arch/x86/entry/syscalls/syscall_32.tbl
SYS_CALL_32_TBL="<KERNEL_SOURCE_DIRECTORY>/arch/x86/entry/syscalls/syscall_32.tbl"
echo "$SYSCALL_1_NUMBER i386 $SYSCALL_1_NAME sys_$SYSCALL_1_NAME" >> $SYS_CALL_32_TBL
echo "$SYSCALL_2_NUMBER i386 $SYSCALL_2_NAME sys_$SYSCALL_2_NAME" >> $SYS_CALL_32_TBL

# Display a success message
echo "System calls added successfully."

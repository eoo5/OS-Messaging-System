
Messaging System
This code implements a simple messaging system with two system calls: cs1550_send_msg for sending a message and cs1550_get_msg for retrieving a message.

Data Structure
The code uses a linked list to store messages. Each message is represented by the struct Message, which has the following fields:

sender: The username of the sender.
sendee: The username of the recipient.
message: The content of the message.
next: A pointer to the next message in the linked list.

Constants
MAX_MESSAGE_LENGTH: Maximum length of a message.
MAX_USER_LENGTH: Maximum length of a username.


cs1550_send_msg System Call
_______________________________
This system call is responsible for sending a message. It allocates memory for a new message, copies the sender, message, and recipient usernames from user space to kernel space, and inserts the new message at the head of the linked list.

Parameters:
to: Recipient's username.
msg: Message content.
from: Sender's username.

Return Values:
0: Message sent successfully.
-ENOMEM: Memory allocation failure.
-EFAULT: Error copying data from/to user space.


cs1550_get_msg System Call
_______________________________
This system call retrieves a message for a given recipient. It searches the linked list for messages with a matching recipient username and returns the oldest matching message. If a message is found, it is copied to user space, and the message is deleted from the linked list.

Parameters:
to: Recipient's username.
msg: Buffer to store the retrieved message content.
from: Buffer to store the sender's username.
Return Values:
0: Message retrieved successfully.
1: More messages available.
-1: No messages found.
-EFAULT: Error copying data from/to user space.

Notes
The linked list is static (message_list) and resides in kernel space.
Kernel memory allocation is done using kmalloc, and deallocation is done using kfree.
copy_from_user and copy_to_user functions are used to transfer data between user space and kernel space.

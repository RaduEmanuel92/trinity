/*
 * SYSCALL_DEFINE3(socket, int, family, int, type, int, protocol)
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "trinity.h"
#include "sanitise.h"

/* note: will eventually also be called from sanitise_socketcall, and generate_sockets() */
void sanitise_socket(
        unsigned long *family,
        unsigned long *type,
        unsigned long *protocol,
        __unused__ unsigned long *a4,
        __unused__ unsigned long *a5,
        __unused__ unsigned long *a6)
{
	*family = rand() % PF_MAX;
	*type = rand() % TYPE_MAX;
	*protocol = rand() % PROTO_MAX;

	switch (*family) {

	case AF_X25:
		*type = SOCK_SEQPACKET;
		break;

	case AF_INET6:
		if (*type == SOCK_STREAM)
			*protocol = 0;
		break;
	}
}

struct syscall syscall_socket = {
	.name = "socket",
	.num_args = 3,
	.arg1name = "family",
	.arg2name = "type",
	.arg3name = "protocol",
	.sanitise = sanitise_socket,
};

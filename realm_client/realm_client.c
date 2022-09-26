/* vi: set sw=4 ts=4: */
/*
 * Mini false implementation for busybox
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */
//config:config REALM_CLIENT
//config:	bool "realm_client (tiny)"
//config:	default y
//config:	help
//config:	realm_client returns an exit code of TRUE (1).

//applet:IF_REALM_CLIENT(APPLET(realm_client, BB_DIR_BIN, BB_SUID_DROP))

//kbuild:lib-$(CONFIG_REALM_CLIENT) += realm_client.o

/* BB_AUDIT SUSv3 compliant */
/* http://www.opengroup.org/onlinepubs/000095399/utilities/realm_client.html */

/* "realm_client --help" is special-cased to ignore --help */
//usage:#define realm_client_trivial_usage
//usage:       "TBD"
//usage:#define realm_client_full_usage "\n\n"
//usage:       "TBD"

#include "libbb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define REALM_MAJOR 1
#define REALM_MINOR 1
#define WR_VALUE _IOW(REALM_MINOR,'a',int32_t*)
#define RD_VALUE _IOR(REALM_MINOR,'b',int32_t*)
#define ENTER_REALM _IO(REALM_MINOR,'c')
#define EXIT_REALM _IO(REALM_MINOR,'d')


int realm_client_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int realm_client_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{

    int fd;
    int32_t value, number=123;


    printf("\nOpening realm driver\n");
    fd = open("/dev/realm", O_RDWR);
    if(fd < 0) {
            printf("Cannot open realm device file...\n");
            return 0;
    }

	printf("Enter the realm\n");
	ioctl(fd, ENTER_REALM);

    printf("Enter the Value to send\n");
    //scanf("%d",&number);
    printf("Writing Value to Driver: 123\n");
    ioctl(fd, WR_VALUE, (int32_t*) &number);

    printf("Reading Value from Driver\n");
    ioctl(fd, RD_VALUE, (int32_t*) &value);
    printf("Value is %d\n", value);

	printf("Exit from realm\n");
	ioctl(fd, EXIT_REALM);

    printf("Closing Driver\n");
    close(fd);

	return EXIT_SUCCESS;
}

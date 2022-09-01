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

/* This is a NOFORK applet. Be very careful! */

int realm_client_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int realm_client_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	printf("All hope abandon ye who enter the Realm here!\n");
	return EXIT_SUCCESS;
}

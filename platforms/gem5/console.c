// SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
/* Copyright 2020 IBM Corp. */

#include <skiboot.h>
#include <console.h>

#include "gem5.h"

/*
 * The SIM_READ_CONSOLE callout will return -1 if there is no character to read.
 * There's no explicit poll callout so we "poll" by doing a read and stashing
 * the result until we do an actual read.
 */
static int gem5_char = -1;

static bool gem5_console_poll(void)
{
	if (gem5_char < 0)
		gem5_char = callthru0(SIM_READ_CONSOLE_CODE);

	return gem5_char >= 0;
}

static size_t gem5_console_read(char *buf, size_t len)
{
	size_t count = 0;

	while (count < len) {
		if (!gem5_console_poll())
			break;

		buf[count++] = gem5_char;
		gem5_char = -1;
	}

	return count;
}

size_t gem5_console_write(const char *buf, size_t len)
{
	callthru2(SIM_WRITE_CONSOLE_CODE, (unsigned long)buf, len);
	return len;
}

static struct con_ops gem5_con_driver = {
	.poll_read = gem5_console_poll,
	.read = gem5_console_read,
	.write = gem5_console_write,
};

void enable_gem5_console(void)
{
	prlog(PR_NOTICE, "Enabling gem5 console\n");
	set_console(&gem5_con_driver);
}

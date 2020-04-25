// SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
/* Copyright 2020 IBM Corp. */

#ifndef __GEM5_H__
#define __GEM5_H__

static inline unsigned long callthru0(int command)
{
	register uint64_t c asm("r3") = command;
	asm volatile (".long 0x000eaeb0":"=r" (c):"r"(c));
	return c;
}

static inline unsigned long callthru2(int command, unsigned long arg1,
				      unsigned long arg2)
{
	register unsigned long c asm("r3") = command;
	register unsigned long a1 asm("r4") = arg1;
	register unsigned long a2 asm("r5") = arg2;
	asm volatile (".long 0x000eaeb0":"=r" (c):"r"(c), "r"(a1), "r"(a2));
	return c;
}

static inline unsigned long callthru3(int command, unsigned long arg1,
				      unsigned long arg2, unsigned long arg3)
{
	register unsigned long c asm("r3") = command;
	register unsigned long a1 asm("r4") = arg1;
	register unsigned long a2 asm("r5") = arg2;
	register unsigned long a3 asm("r6") = arg3;
	asm volatile (".long 0x000eaeb0":"=r" (c):"r"(c), "r"(a1), "r"(a2),
		      "r"(a3));
	return c;
}

static inline unsigned long callthru4(int command, unsigned long arg1,
				      unsigned long arg2, unsigned long arg3,
				      unsigned long arg4)
{
	register unsigned long c asm("r3") = command;
	register unsigned long a1 asm("r4") = arg1;
	register unsigned long a2 asm("r5") = arg2;
	register unsigned long a3 asm("r6") = arg3;
	register unsigned long a4 asm("r7") = arg4;
	asm volatile (".long 0x000eaeb0":"=r" (c):"r"(c), "r"(a1), "r"(a2),
		      "r"(a3), "r"(a4));
	return c;
}

/* gem5 callthru commands */
#define SIM_WRITE_CONSOLE_CODE	0
#define SIM_EXIT_CODE		1
#define SIM_READ_CONSOLE_CODE	2
#define SIM_GET_TIME_CODE	3
#define SIM_CPU_RESET_CODE	4
#define SIM_CPU_STATE_CODE	5

#endif /* __GEM5_H__ */

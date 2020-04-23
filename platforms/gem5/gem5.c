// SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
/* Copyright 2020 IBM Corp. */

#include <skiboot.h>
#include <device.h>
#include <console.h>
#include <chip.h>
#include <cpu.h>
#include <opal-api.h>
#include <opal-internal.h>
#include <time-utils.h>
#include <time.h>

#include "gem5.h"

static bool gem5_probe(void)
{
	if (!dt_find_by_path(dt_root, "/gem5"))
		return false;

	return true;
}

extern unsigned long callthru_cpu_state(uint32_t state, uint32_t chip_id,
					uint32_t core_id, uint32_t thread_id);

unsigned long callthru_cpu_state(uint32_t state, uint32_t chip_id,
				 uint32_t core_id, uint32_t thread_id)
{
	prlog(PR_DEBUG, "Setting CPU state via gem5, state: %u\n", state);
	return callthru4(SIM_CPU_STATE_CODE, state, chip_id, core_id,
			 thread_id);
}

static int64_t gem5_rtc_read(__be32 *ymd, __be64 *hmsm)
{
	int64_t gem5_time;
	struct tm t;
	time_t mt;
	uint32_t __ymd;
	uint64_t __hmsm;

	if (!ymd || !hmsm)
		return OPAL_PARAMETER;

	gem5_time = callthru0(SIM_GET_TIME_CODE);
	mt = gem5_time >> 32;
	gmtime_r(&mt, &t);
	tm_to_datetime(&t, &__ymd, &__hmsm);

	*ymd = cpu_to_be32(__ymd);
	*hmsm = cpu_to_be64(__hmsm);

	return OPAL_SUCCESS;
}

static void gem5_rtc_init(void)
{
	struct dt_node *np = dt_new(opal_node, "rtc");
	dt_add_property_strings(np, "compatible", "ibm,opal-rtc");

	opal_register(OPAL_RTC_READ, gem5_rtc_read, 2);
}

static void gem5_system_reset_cpu(struct cpu_thread *cpu)
{
	uint32_t core_id;
	uint32_t thread_id;

	core_id = pir_to_core_id(cpu->pir);
	thread_id = pir_to_thread_id(cpu->pir);

	callthru2(SIM_CPU_RESET_CODE, core_id, thread_id);
}

#define SYS_RESET_ALL		-1
#define SYS_RESET_ALL_OTHERS	-2

static int64_t gem5_signal_system_reset(int32_t cpu_nr)
{
	struct cpu_thread *cpu;

	if (cpu_nr < 0) {
		if (cpu_nr < SYS_RESET_ALL_OTHERS)
			return OPAL_PARAMETER;

		for_each_cpu(cpu) {
			if (cpu == this_cpu())
				continue;
			gem5_system_reset_cpu(cpu);

		}
		if (cpu_nr == SYS_RESET_ALL)
			gem5_system_reset_cpu(this_cpu());

		return OPAL_SUCCESS;

	} else {
		cpu = find_cpu_by_server(cpu_nr);
		if (!cpu)
			return OPAL_PARAMETER;

		gem5_system_reset_cpu(cpu);
		return OPAL_SUCCESS;
	}
}

static void gem5_sreset_init(void)
{
	opal_register(OPAL_SIGNAL_SYSTEM_RESET, gem5_signal_system_reset, 1);
}

static void gem5_platform_init(void)
{
	gem5_sreset_init();
	gem5_rtc_init();
}

static int64_t gem5_cec_power_down(uint64_t request __unused)
{
	if (chip_quirk(QUIRK_GEM5_CALLOUTS))
		callthru0(SIM_EXIT_CODE);

	return OPAL_UNSUPPORTED;
}

static int64_t gem5_cec_reboot(void)
{
	if (chip_quirk(QUIRK_GEM5_CALLOUTS))
		callthru0(SIM_EXIT_CODE);

	return OPAL_UNSUPPORTED;
}

static void __attribute__((noreturn)) gem5_terminate(const char *msg __unused)
{
	if (chip_quirk(QUIRK_GEM5_CALLOUTS))
		callthru0(SIM_EXIT_CODE);

	for (;;) ;
}

static int gem5_heartbeat_time(void)
{
	/*
	 * gem5 is slow and has no console input interrupt, so faster
	 * polling is needed to ensure its responsiveness.
	 */
	return 1000;
}

DECLARE_PLATFORM(gem5) = {
	.name			= "gem5",
	.probe			= gem5_probe,
	.init			= gem5_platform_init,
	.cec_power_down 	= gem5_cec_power_down,
	.cec_reboot 		= gem5_cec_reboot,
	.terminate		= gem5_terminate,
	.start_preload_resource	= flash_start_preload_resource,
	.resource_loaded	= flash_resource_loaded,
	.heartbeat_time		= gem5_heartbeat_time,
	.nvram_info		= fake_nvram_info,
	.nvram_start_read	= fake_nvram_start_read,
	.nvram_write		= fake_nvram_write,
};

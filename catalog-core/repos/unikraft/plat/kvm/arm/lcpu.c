/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Wei Chen <wei.chen@arm.com>
 *
 * Copyright (c) 2018, Arm Ltd., All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <uk/plat/lcpu.h>
#include <arm/irq.h>
#include <arm/cpu.h>

void ukplat_lcpu_enable_irq(void)
{
	local_irq_enable();
}

void ukplat_lcpu_disable_irq(void)
{
	local_irq_disable();
}

void ukplat_lcpu_halt_irq(void)
{
	UK_ASSERT(ukplat_lcpu_irqs_disabled());

	/* Note: If priority masking is enabled
	 * interrupts need to be unmasked in the GIC.
	 *
	 * See Linux `cpu_do_idle(void)` implementation
	 */
	halt();
}

unsigned long ukplat_lcpu_save_irqf(void)
{
	unsigned long flags;

	local_irq_save(flags);

	return flags;
}

void ukplat_lcpu_restore_irqf(unsigned long flags)
{
	local_irq_restore(flags);
}

int ukplat_lcpu_irqs_disabled(void)
{
	return irqs_disabled();
}

void ukplat_lcpu_irqs_handle_pending(void)
{
	// TODO
}

void ukplat_lcpu_set_auxsp(__uptr auxsp)
{
	lcpu_get_current()->auxsp = auxsp;
}

__uptr ukplat_lcpu_get_auxsp(void)
{
	return lcpu_get_current()->auxsp;
}

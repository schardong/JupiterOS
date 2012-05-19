/**
 * File: pit.h
 * Author: Guilherme Gonçalves Schardong
 * Definition of Programmable Interrupt Timer.
 * File created on 20 July 2011, 11:37
 */

#ifndef __KERNEL_PIT_H__
#define __KERNEL_PIT_H__

#include <stdint.h>

/**
 * init_pit - Initializes the Programmable Interrupt Timer.
 * @frequency: How many times that the timer will interrupt the processor (Hz).
 */
void k_init_timer(uint32 frequency);

#endif /* __KERNEL_PIT_H__ */

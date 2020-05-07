/* Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include <support.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <encoding.h>
#include "boardsupport.h"

#define HAVE_BOARD_SUPPORT_H

extern int main();

__attribute__((section(".init")))
void _mstart()
{
  asm volatile(
               "_mstart:\n"
               "la t0, trap_entry\n"
               "csrw mtvec, t0\n"
               "li	x1, 0\n"
               "li	x2, 0\n"
               "li	x3, 0\n"
               "li	x4, 0\n"
               "li	x5, 0\n"
               "li	x6, 0\n"
               "li	x7, 0\n"
               "li	x8, 0\n"
               "li	x9, 0\n"
               "li	x10, 0\n"
               "li	x11, 0\n"
               "li	x12, 0\n"
               "li	x13, 0\n"
               "li	x14, 0\n"
               "li	x15, 0\n"
               "li	x16, 0\n"
               "li	x17, 0\n"
               "li	x18, 0\n"
               "li	x19, 0\n"
               "li	x20, 0\n"
               "li	x21, 0\n"
               "li	x22, 0\n"
               "li	x23, 0\n"
               "li	x24, 0\n"
               "li	x25, 0\n"
               "li	x26, 0\n"
               "li	x27, 0\n"
               "li	x28, 0\n"
               "li	x29, 0\n"
               "li	x30, 0\n"
               "li	x31, 0\n"

               /* initialize global pointer */
               "la	gp, _gp\n"

               "init_bss:\n"
               /* init bss section */
               "la	a0, __bss_start\n"
               "la	a1, __bss_end-4\n" /* section end is actually the start of the next section */
               "li	a2, 0x0\n"
               "jal	fill_block\n"

               "init_sbss:\n"
               /* init bss section */
               "la	a0, __sbss_start\n"
               "la	a1, __sbss_end-4\n" /* section end is actually the start of the next section */
               "li	a2, 0x0\n"
               "jal	fill_block\n"

               "write_stack_pattern:\n"
               /* init bss section */
               "la	a0, _stack_end\n"  /* note the stack grows from top to bottom */
               "la	a1, __stack-4\n"   /* section end is actually the start of the next section */
               "li	a2, 0xABABABAB\n"
               "jal	fill_block\n"

               "init_stack:\n"
               /* set stack pointer */
               "la	sp, _stack\n"

               "j	vSyscallInit\n"

               /* When trap is an interrupt, this function is called 
               "interrupt:\n"
               "slli    t0,t0,1\n"
               "srli    t0,t0,1\n"
               "addi    t0,t0,-3\n"
               "beq		t0,x0,softwareInterrupt\n"
               "ld	t0, 0x0(sp)\n"
               "addi	sp, sp, 8\n"*/

               /* Interupt is timer interrupt 
               "j		TIMER_CMP_INT\n"
               "mret\n"*/

               /* Interupt is software interrupt 
               "softwareInterrupt:\n"
               "ld  t0, 0x0(sp)\n"
               "addi  sp, sp, 8\n"
               "mret\n"*/

               /* For when a trap is fired */
               ".align 2\n"
               "trap_entry:\n"
               /* Check for interrupt 
               "addi	sp, sp, -8\n"
               "sd	t0, 0x0(sp)\n"
               "csrr	t0, mcause\n"
               "blt	t0,x0,interrupt\n"
               "ld	t0, 0x0(sp)\n"
               "addi	sp, sp, 8\n"*/

               /* System call and other traps */
               "addi sp, sp, -8*32\n"
               "sd x1, 1*8(sp)\n"
               "sd x2, 2*8(sp)\n"
               "sd x3, 3*8(sp)\n"
               "sd x4, 4*8(sp)\n"
               "sd x5, 5*8(sp)\n"
               "sd x6, 6*8(sp)\n"
               "sd x7, 7*8(sp)\n"
               "sd x8, 8*8(sp)\n"
               "sd x9, 9*8(sp)\n"
               "sd x10, 10*8(sp)\n"
               "sd x11, 11*8(sp)\n"
               "sd x12, 12*8(sp)\n"
               "sd x13, 13*8(sp)\n"
               "sd x14, 14*8(sp)\n"
               "sd x15, 15*8(sp)\n"
               "sd x16, 16*8(sp)\n"
               "sd x17, 17*8(sp)\n"
               "sd x18, 18*8(sp)\n"
               "sd x19, 19*8(sp)\n"
               "sd x20, 20*8(sp)\n"
               "sd x21, 21*8(sp)\n"
               "sd x22, 22*8(sp)\n"
               "sd x23, 23*8(sp)\n"
               "sd x24, 24*8(sp)\n"
               "sd x25, 25*8(sp)\n"
               "sd x26, 26*8(sp)\n"
               "sd x27, 27*8(sp)\n"
               "sd x28, 28*8(sp)\n"
               "sd x29, 29*8(sp)\n"
               "sd x30, 30*8(sp)\n"
               "sd x31, 31*8(sp)\n"

               "csrr a0, mcause\n"
               "csrr a1, mepc\n"

               "mv a2, sp\n"
               "jal ulSyscallTrap\n"

               "csrw mepc, a0\n"

               "ld x1, 1*8(sp)\n"
               "ld x2, 2*8(sp)\n"
               "ld x3, 3*8(sp)\n"
               "ld x4, 4*8(sp)\n"
               "ld x5, 5*8(sp)\n"
               "ld x6, 6*8(sp)\n"
               "ld x7, 7*8(sp)\n"
               "ld x8, 8*8(sp)\n"
               "ld x9, 9*8(sp)\n"
               "ld x10, 10*8(sp)\n"
               "ld x11, 11*8(sp)\n"
               "ld x12, 12*8(sp)\n"
               "ld x13, 13*8(sp)\n"
               "ld x14, 14*8(sp)\n"
               "ld x15, 15*8(sp)\n"
               "ld x16, 16*8(sp)\n"
               "ld x17, 17*8(sp)\n"
               "ld x18, 18*8(sp)\n"
               "ld x19, 19*8(sp)\n"
               "ld x20, 20*8(sp)\n"
               "ld x21, 21*8(sp)\n"
               "ld x22, 22*8(sp)\n"
               "ld x23, 23*8(sp)\n"
               "ld x24, 24*8(sp)\n"
               "ld x25, 25*8(sp)\n"
               "ld x26, 26*8(sp)\n"
               "ld x27, 27*8(sp)\n"
               "ld x28, 28*8(sp)\n"
               "ld x29, 29*8(sp)\n"
               "ld x30, 30*8(sp)\n"
               "ld x31, 31*8(sp)\n"

               "addi sp, sp, 8*32\n"
               "mret\n"

               /* Fills memory blocks */
               "fill_block:\n"
               "sw		a2, 0(a0)\n"
               "bgeu	a0, a1, fb_end\n"
               "addi	a0, a0, 4\n"
               "j		fill_block\n"
               "fb_end:\n"
               "ret\n"
               );
}

uint64_t zeroExtend(long val)
{
	uint64_t ret = val;
#if __riscv_xlen == 32
  ret = (0x00000000ffffffff & val);
#endif
	return ret;
}

volatile uint64_t tohost __attribute__((aligned(64)));
volatile uint64_t fromhost __attribute__((aligned(64)));

/* Exit systemcall */
static void prvSyscallExit(long code)
{
	uint64_t zcode = zeroExtend(code);
	tohost = ((zcode << 1) | 1);
	for(;;) { }
}

/* Starts main function. */
void vSyscallInit(void)
{
  prvSyscallExit(main());
}

/* Relay syscall to host */
static uint64_t prvSyscallToHost(long which, long arg0, long arg1, long arg2)
{
	volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  //    volatile uint64_t oldfromhost;
	magic_mem[0] = zeroExtend(which);
	magic_mem[1] = zeroExtend(arg0);
	magic_mem[2] = zeroExtend(arg1);
	magic_mem[3] = zeroExtend(arg2);
	__sync_synchronize();
  tohost = zeroExtend(magic_mem);
  //    do
  //    {
  //        oldfromhost = fromhost;
  //        fromhost = 0;
  //    } while (oldfromhost == 0);
	return magic_mem[0];
}

/* Trap handeler */
unsigned long ulSyscallTrap(long cause, long epc, long regs[32])
{
	long returnValue = 0;

	if (cause != CAUSE_MACHINE_ECALL) {
		prvSyscallExit(cause);
	} else if (regs[17] == SYS_exit) {
		prvSyscallExit(regs[10]);
	} else {
		returnValue = prvSyscallToHost(regs[17], regs[10], regs[11], regs[12]);
	}

	regs[10] = returnValue;
	return epc + 4;
}

void* memcpy(void* dest, const void* src, size_t len)
{
  const char* s = src;
  char *d = dest;

  if ((((uintptr_t)dest | (uintptr_t)src) & (sizeof(uintptr_t)-1)) == 0) {
    while ((void*)d < (dest + len - (sizeof(uintptr_t)-1))) {
      *(uintptr_t*)d = *(const uintptr_t*)s;
      d += sizeof(uintptr_t);
      s += sizeof(uintptr_t);
    }
  }

  while (d < (char*)(dest + len))
    *d++ = *s++;

  return dest;
}

int memcmp(const void* s1, const void* s2, size_t len)
{
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  long int val;

  if ((((const uintptr_t)s1 | (const uintptr_t)s2) & (sizeof(uintptr_t)-1)) == 0) {
    while (p1 < ((const unsigned char*)s1 + len - (sizeof(uintptr_t)-1))) {
      val = *(const uintptr_t*)p1 - *(const uintptr_t*)p2;
      if (val != 0) {
        return val > 0 ? 1 : -1;
      }
      p1 += sizeof(uintptr_t);
      p2 += sizeof(uintptr_t);
    }
  }

  while (p1 < ((const unsigned char*)s1 + len)) {
    val = *p1 - *p2;
    if (val != 0) {
      return val > 0 ? 1 : -1;
    }
    p1++;
    p2++;
  }
  return 0;
}

void* memset(void* dest, int byte, size_t len)
{
  if ((((uintptr_t)dest | len) & (sizeof(uintptr_t)-1)) == 0) {
    uintptr_t word = byte & 0xFF;
    word |= word << 8;
    word |= word << 16;
    word |= word << 16 << 16;

    uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = word;
  } else {
    char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = byte;
  }
  return dest;
}

size_t strlen(const char *s)
{
  const char *p = s;
  while (*p)
    p++;
  return p - s;
}

int strcmp(const char* s1, const char* s2)
{
  unsigned char c1, c2;

  do {
    c1 = *s1++;
    c2 = *s2++;
  } while (c1 != 0 && c1 == c2);

  return c1 - c2;
}

char* strcpy(char* dest, const char* src)
{
  char* d = dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

/* Fires a syscall */
long syscall(long num, long arg0, long arg1, long arg2)
{
	register long a7 asm("a7") = num;
	register long a0 asm("a0") = arg0;
	register long a1 asm("a1") = arg1;
	register long a2 asm("a2") = arg2;
	asm volatile ("scall":"+r"(a0) : "r"(a1), "r"(a2), "r"(a7));
	return a0;
}

//for debugging
int putchar(int ch)
{
	static char buf[64] __attribute__((aligned(64)));
	static int buflen = 0;

	buf[buflen++] = ch;

	if (ch == '\n' || buflen == sizeof(buf)) {
		syscall(SYS_write, 1, (long) buf, buflen);
		buflen = 0;
	}

	return 0;
}

/* (modified) itoa:  convert n to characters in s */
int itoa(int n, char s[])
{
  int i, sign;

  if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
  i = 0;
  do {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
  } while ((n /= 10) > 0);     /* delete it */
  if (sign < 0)
    s[i++] = '-';
  //s[i] = '\0';
  return i-1;
}

void initialise_board()
{
}

unsigned long cycle_start;

void start_trigger()
{
  cycle_start = read_csr(cycle);
}

void stop_trigger()
{
  unsigned long cycle_stop = read_csr(cycle);
  char str[64], s;
  int i;
  i = itoa(cycle_stop-cycle_start, str);
  putchar('c');
  putchar('y');
  putchar('c');
  putchar('l');
  putchar('e');
  putchar('s');
  putchar('=');
  while(i >= 0)
    putchar(str[i--]);
  putchar('\n');

  //kernel need more time to flush mem?
  for(i=0;i<1000;i++){
    asm("nop");
  }
}



/* Definition of RISC-V target for GNU compiler.
   Copyright (C) 2016-2023 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_RISCV_OPTS_H
#define GCC_RISCV_OPTS_H

enum riscv_abi_type {
  ABI_ILP32,
  ABI_ILP32E,
  ABI_ILP32F,
  ABI_ILP32D,
  ABI_LP64,
  ABI_LP64F,
  ABI_LP64D
};
extern enum riscv_abi_type riscv_abi;

enum riscv_code_model {
  CM_MEDLOW,
  CM_MEDANY,
  CM_PIC
};
extern enum riscv_code_model riscv_cmodel;

enum riscv_isa_spec_class {
  ISA_SPEC_CLASS_NONE,

  ISA_SPEC_CLASS_2P2,
  ISA_SPEC_CLASS_20190608,
  ISA_SPEC_CLASS_20191213
};

extern enum riscv_isa_spec_class riscv_isa_spec;

/* Keep this list in sync with define_attr "tune" in riscv.md.  */
enum riscv_microarchitecture_type {
  generic,
  sifive_7
};
extern enum riscv_microarchitecture_type riscv_microarchitecture;

enum riscv_align_data {
  riscv_align_data_type_xlen,
  riscv_align_data_type_natural
};

/* Where to get the canary for the stack protector.  */
enum stack_protector_guard {
  SSP_TLS,			/* per-thread canary in TLS block */
  SSP_GLOBAL			/* global canary */
};

/* RISC-V auto-vectorization preference.  */
enum riscv_autovec_preference_enum {
  NO_AUTOVEC,
  RVV_SCALABLE,
  RVV_FIXED_VLMAX
};

/* RISC-V auto-vectorization RVV LMUL.  */
enum riscv_autovec_lmul_enum {
  RVV_M1 = 1,
  RVV_M2 = 2,
  RVV_M4 = 4,
  RVV_M8 = 8,
  /* For dynamic LMUL, we compare COST start with LMUL8.  */
  RVV_DYNAMIC = 9
};

enum riscv_multilib_select_kind {
  /* Select multilib by builtin way.  */
  select_by_builtin,
  /* Select multilib by ABI, arch and code model.  */
  select_by_abi_arch_cmodel,
  /* Select multilib by ABI only.  */
  select_by_abi,
};

/* ENTITIES in mode switching.  */
enum riscv_entity
{
  RISCV_VXRM = 0,
  RISCV_FRM,
  MAX_RISCV_ENTITIES
};

#define TARGET_ZICOND_LIKE (TARGET_ZICOND || (TARGET_XVENTANACONDOPS && TARGET_64BIT))

/* Bit of riscv_zvl_flags will set contintuly, N-1 bit will set if N-bit is
   set, e.g. MASK_ZVL64B has set then MASK_ZVL32B is set, so we can use
   popcount to caclulate the minimal VLEN.  */
#define TARGET_MIN_VLEN \
  ((riscv_zvl_flags == 0) \
   ? 0 \
   : 32 << (__builtin_popcount (riscv_zvl_flags) - 1))

/* We only enable VLS modes for VLA vectorization since fixed length VLMAX mode
   is the highest priority choice and should not conflict with VLS modes.  */
#define TARGET_VECTOR_VLS                                                      \
  (TARGET_VECTOR && riscv_autovec_preference == RVV_SCALABLE)

#endif /* ! GCC_RISCV_OPTS_H */

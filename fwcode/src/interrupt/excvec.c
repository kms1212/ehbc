#include <stdint.h>

struct exception_vector {
/* 000 */   void*       initial_sp;
/* 001 */   void*       initial_pc;
/* 002 */   void*       bus_error;
/* 003 */   void*       addr_error;
/* 004 */   void*       illegal_instruction;
/* 005 */   void*       divide_by_zero;
/* 006 */   void*       chk_instruction;
/* 007 */   void*       trap_instruction;
/* 008 */   void*       privilege_violation;
/* 009 */   void*       trace;
/* 010 */   void*       line_1010_emu;
/* 011 */   void*       line_1111_emu;
/* 012 */   void*       __reserved12;
/* 013 */   void*       coproc_protocol_volation;
/* 014 */   void*       format_error;
/* 015 */   void*       uninitialized_interrupt;
/* 016 */   void*       __reserved16;
/* 017 */   void*       __reserved17;
/* 018 */   void*       __reserved18;
/* 019 */   void*       __reserved19;
/* 020 */   void*       __reserved20;
/* 021 */   void*       __reserved21;
/* 022 */   void*       __reserved22;
/* 023 */   void*       __reserved23;
/* 024 */   void*       spurious_interrupt;
/* 025 */   void*       ipl_level1;
/* 026 */   void*       ipl_level2;
/* 027 */   void*       ipl_level3;
/* 028 */   void*       ipl_level4;
/* 029 */   void*       ipl_level5;
/* 030 */   void*       ipl_level6;
/* 031 */   void*       ipl_level7;
/* 032 */   void*       trap_0;
/* 033 */   void*       trap_1;
/* 034 */   void*       trap_2;
/* 035 */   void*       trap_3;
/* 036 */   void*       trap_4;
/* 037 */   void*       trap_5;
/* 038 */   void*       trap_6;
/* 039 */   void*       trap_7;
/* 040 */   void*       trap_8;
/* 041 */   void*       trap_9;
/* 042 */   void*       trap_10;
/* 043 */   void*       trap_11;
/* 044 */   void*       trap_12;
/* 045 */   void*       trap_13;
/* 046 */   void*       trap_14;
/* 047 */   void*       trap_15;
};
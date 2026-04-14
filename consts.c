/**
 * @file consts.c
 * @brief Constants used throughout codebase.
 * @author Cameron Hannay
 */
#include "include.h"


// TODO: Add in more documentation/comments since Old Jim forgot


const uint32_t UNDEFINED;


const uint32_t MAX_5_BIT = 31;
const uint32_t MAX_6_BIT = 63;
const uint32_t MAX_16_BIT = 65535;
const uint32_t MAX_26_BIT = 67108863;


const char* registers[] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};


// Array of instruction definitions for supported MIPS instructions
// Each entry includes the instruction name, type, opcode, funct code (if applicable), and the registers used
// This array is used for instruction decoding and execution in the MIPS simulator
const struct instruction_definition instruction_definitions[] = {
    {
        "ADD",                  // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "100000",               // Funct Code for ADD
        { RD, RS, RT, EMPTY }  // Registers used: add $rd, $rs, $rt
    },

    {
        "ADDI",                 // MIPS instruction name
        I_TYPE,                 // I type instruction
        "001000",               // Opcode for ADDI
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: addi $rt, $rs, imm
    },

    {
        "BNE",                  // MIPS instruction name
        I_TYPE,                 // I type instruction
        "000101",               // Opcode for BNE
        NULL,                   // No funct code for I type instructions
        { RS, RT, IMM, EMPTY } // Registers used: bne $rs, $rt, imm
    },

    {
        "AND",                  // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "100100",               // Funct code for AND
        { RD, RS, RT, EMPTY }  // Registers used: and $rd, $rs, $rt
    },

    {
        "ANDI",                 // MIPS instruction name
        I_TYPE,                 // I type instruction
        "001100",               // Opcode for ANDI
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: andi $rt, $rs, imm
    },

    {
        "BEQ",                  // MIPS instruction name
        I_TYPE,                 // I type instruction
        "000100",               // Opcode for BEQ
        NULL,                   // No funct code for I type instructions
        { RS, RT, IMM, EMPTY } // Registers used: beq $rs, $rt, imm
    },

    {
        "DIV",                  // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "011010",               // Funct code for DIV
        { RS, RT, EMPTY, EMPTY } // Registers used: div $rs, $rt
    },

    {
        "LUI",                  // MIPS instruction name
        I_TYPE,                 // I type instruction
        "001111",               // Opcode for LUI
        NULL,                   // No funct code for I type instructions
        { RT, IMM, EMPTY, EMPTY } // Registers used: lui $rt, imm
    },

    {
        "LW",                   // MIPS instruction name
        I_TYPE,                 // I type instruction
        "100011",               // Opcode for LW
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: lw $rt, imm($rs)
    },

    {
        "MFHI",                 // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "010000",               // Funct code for MFHI
        { RD, EMPTY, EMPTY, EMPTY } // Registers used: mfhi $rd
    },

    {
        "MFLO",                 // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "010010",               // Funct code for MFLO
        { RD, EMPTY, EMPTY, EMPTY } // Registers used: mflo $rd
    },

    {
        "OR",                   // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "100101",               // Funct code for OR
        { RD, RS, RT, EMPTY }  // Registers used: or $rd, $rs, $rt
    },

    {
        "SLT",                  // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "101010",               // Funct code for SLT
        { RD, RS, RT, EMPTY }  // Registers used: slt $rd, $rs, $rt
    },

    {
        "SUB",                  // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "100010",               // Funct code for SUB
        { RD, RS, RT, EMPTY }  // Registers used: sub $rd, $rs, $rt
    },

    {
        "SW",                   // MIPS instruction name
        I_TYPE,                 // I type instruction
        "101011",               // Opcode for SW
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: sw $rt, imm($rs)
    },

    // Newly implemented instructions

    {
        "MULT",                 // MIPS instruction name
        R_TYPE,                 // R type instruction
        "000000",               // Opcode for R type instructions is always 000000
        "011000",               // Funct code for MULT
        { RS, RT, EMPTY, EMPTY } // Registers used: mult $rs, $rt
    },

    {
        "ORI",                  // MIPS instruction name
        I_TYPE,                 // I type instruction
        "001101",               // Opcode for ORI
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: ori $rt, $rs, imm
    },

    {
        "SLTI",                 // MIPS instruction name
        I_TYPE,                 // I type instruction
        "001010",               // Opcode for SLTI
        NULL,                   // No funct code for I type instructions
        { RT, RS, IMM, EMPTY } // Registers used: slti $rt, $rs, imm
    }
};
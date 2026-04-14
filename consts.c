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


const struct instruction_definition instruction_definitions[] = {
    // Three "Golden Standard" Instructions
    // The ADD instruction shows what each part of the instruction defintion means
    {
        "ADD",                  // MIPS instruction name
        R_TYPE,                 // Type of instruction (R, I, or J)
        "000000",               // Opcode
        "100000",               // Funct Code
        { RD, RS, RT, EMPTY }   // Registers
    },                          // This would be read as: add $rd, $rs, $rt


    {
        "ADDI",                // MIPS instruction name
        I_TYPE,                // Instruction Type
        "001000",              // Opcode
        NULL,                  // Funct Code
        { RT, RS, IMM, EMPTY } // Registers
    },


    {
        "BNE",                 // MIPS instruction name
        I_TYPE,                // Instruction Type
        "000101",              // Opcode
        NULL,                  // Funct Code
        { RS, RT, IMM, EMPTY } // Registers
    },


    //TODO: Fix the bugs in the other instructions to restore functionality


    {
        "AND",      			// MIPS instruction name
        R_TYPE,     			// Instruction Type [Changed from I_TYPE]
        "000000",   			// Opcode [Changed from 001000]
        "100100",   			// Funct Code
        { RD, RS, RT, EMPTY } 	// Registers
    },


    {
        "ANDI",        // MIPS instruction name
        I_TYPE,     	// Instruction Type [Changed from r_TYPE]
        "001100",
        NULL,
        { RT, RS, IMM, EMPTY } // Rearranged the order of the registers
    },


    {
        "BEQ",      // MIPS instruction name
        I_TYPE,   // Instruction Type [Changed from r_TYPE]


        "000100", // Opcode [Changed from 000000]
        NULL,     // Removed the function field
        { RS, RT, IMM, EMPTY }
    },


    {
        "DIV",  // MIPS instruction name
        R_TYPE,
        "000000",
        "011010",
        { RS, RT, EMPTY, EMPTY } // Added RT register
    },


    {
        "LUI", // MIPS instruction name
        I_TYPE,
        "001111",
        NULL,
        { RT, IMM, EMPTY, EMPTY } // removed RS register and updated RT register
    },


    {
        "LW",   // MIPS instruction name
        I_TYPE,     // Instruction Type [Changed from R_TYPE]
        "100011",
        NULL,
        { RT, RS, IMM, EMPTY } // rearranged the order of the registers
    },


    {
        "MFHI", // MIPS instruction name
        R_TYPE,
        "000000",
        "010000",   // Updated function code [FROM 010010]
        { RD, EMPTY, EMPTY, EMPTY } // Removed RS register and updated to RD register
    },


    {
        "MFLO",     // MIPS instruction name
        R_TYPE,
        "000000",
        "010010", // Updated function code [from 010000]
        { RD, EMPTY, EMPTY, EMPTY } // Removed RS register and updated to RD register
    },


    {
        "OR", // MIPS instruction name
        R_TYPE,
        "000000", // Updated the opcode [from 001101
        "100101", // Updated function code [from 000000]
        { RD, RS, RT, EMPTY }
    },


    {
        "SLT",  // MIPS instruction name
        R_TYPE,
        "000000",
        "101010", // Funct code [Changed from 101011]
        { RD, RS, RT, EMPTY } // Rearranged the order of the registers
    },


    {
        "SUB",  // MIPS instruction name
        R_TYPE,
        "000000", // Opcode [Changed from 100010]
        "100010", // Funct Code [Changed from 000000]
        { RD, RS, RT, EMPTY } // Added RD register
    },


    {
        "SW",   // MIPS instruction name
        I_TYPE,
        "101001", // Opcode [Changed from 100011]
        NULL,
        { RT, RS, IMM, EMPTY } // Rearranged Register values
    },
   
    // TODO: Implement MULT, ORI, and SLTI instructions once bugs are fixed


    // The following instructions have been newly implemented
    {
        "MULT", 	// MIPS instruction name
        R_TYPE,	// Instruction Type
        "000000", // Opcode
        "011000",	// Funct code
        { RS, RT, EMPTY, EMPTY } // Registers
    },


    {
        "ORI",  // MIPS instruction name
        I_TYPE,
        "001101",
        NULL,
        { RT, RS, IMM, EMPTY }
    },


    {
        "SLTI", // MIPS instruction name
        I_TYPE,
        "001010",
        NULL,
        { RT, RS, IMM, EMPTY}


    }
};

        { RS, IMM, RT, EMPTY }
    }
    
    // TODO: Implement MULT, ORI, and SLTI instructions once bugs are fixed
};
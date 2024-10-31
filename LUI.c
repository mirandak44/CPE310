/*
Name: Miranda Kirtley
Group Members:Aishat Banire, Emily Kissner, Alexis DePue
Code Modified by Miranda: MFHI.c, DIVI.c, LUI.c, LW.c
*/
#include "Instruction.h"

void lui_immd_assm(void) {
    //ensure the command is for LUI
    if (strcmp(OP_CODE, "LUI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //check that the first parameter is a register (Rt)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //check that the second parameter is an immediate value
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    //validate register (Rt) range: should be 0-31
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    //validate immediate value range (should be within 16 bits, 0x0000 - 0xFFFF)
    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    //set the opcode for LUI
    setBits_str(31, "001111");

    //set Rt 
    setBits_num(20, PARAM1.value, 5);

    //set the immediate value in upper 16 bits of the register
    setBits_num(15, PARAM2.value, 16);

    //encoding complete
    state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
    //check if the opcode bits match for LUI (001111)
    if (checkBits(31, "001111") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //retrieve Rt 
    uint32_t Rt = getBits(20, 5);

    //retrieve the 16-bit immediate value
    uint32_t imm16 = getBits(15, 16);

    //set the operation and parameters
    setOp("LUI");
    setParam(1, REGISTER, Rt);  // Set Rt
    setParam(2, IMMEDIATE, imm16);  // Set immediate value

    //decoding complete
    state = COMPLETE_DECODE;
}

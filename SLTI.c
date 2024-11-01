/*
Name: Aishat Banire
Group Members:Miranda Kirtley, Emily Kissner, Alexis DePue
Code Modified by Aishat: SLT.c, SLTI.c, SUB.c, SW.c
*/

#include "Instruction.h"

void slti_immd_assm(void) {
    //Check if the op code matches
    if (strcmp(OP_CODE, "SLTI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //First parameter should be a register rd
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //Second parameter should be a register rs
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //Third parameter should be an immediate value
    if (PARAM3.type != IMMEDIATE) {
        state = MISSING_IMMEDIATE;
        return;
    }

    //Rd should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    //Rs should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    //immediate value should fit in 16 bits
    if (PARAM3.value < -32768 || PARAM3.value > 32767) {
        state = INVALID_IMMEDIATE;
        return;
    }
    // Opcode for SLTI is 8 (001000)
    //set the opcode for SLTI
    setBits_num(31, 8, 6);

    //set the immediate value (must fit in 16 bits)
    setBits_num(15, PARAM3.value, 16); /

    //set Rd
    setBits_num(20, PARAM1.value, 5);

    //set Rs
    setBits_num(25, PARAM2.value, 5);

    state = COMPLETE_ENCODE;
    }

}

void slti_immd_bin(void) {
    //check if the op code bits match
    if (checkBits(31, "001000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //finding values in the binary
    uint32_t Rd = getBits(20, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t immediate = getBits(15, 16); // Get the immediate value

    setOp("SLTI");
    setParam(1, REGISTER, Rd);
    setParam(2, REGISTER, Rs);
    setParam(3, IMMEDIATE, immediate);
        
    state = COMPLETE_DECODE;
    
    }




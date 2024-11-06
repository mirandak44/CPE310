/*
Name: Aishat Banire
Group Members:Miranda Kirtley, Emily Kissner, Alexis DePue
Code Modified by Aishat: SLT.c, SLTI.c, SUB.c, SW.c
*/

#include "Instruction.h"

void slt_reg_assm(void) {
    //check if the op code matches
    if (strcmp(OP_CODE, "SLT") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //first parameter should be a register rd
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //second parameter should be a register rs
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //third parameter should be a register rt
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG;
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

    //Rt should be 31 or less
    if (PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }
    
    //set the opcode for SLT
    setBits_num(31, 0, 6);
    
    //set the funct for SLT
    setBits_str(5, "101010");
    
    //set Rd
    setBits_num(15, PARAM1.value, 5);

    //set Rs
    setBits_num(25, PARAM2.value, 5);

    //set Rt
    setBits_num(20, PARAM3.value, 5);

    // Indicate that the encoding is done
    state = COMPLETE_ENCODE;
  }


void slt_reg_bin(void) {
    // check if the op code bits match
    if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //if the op code bits match read the binary values
    //finding values in the binary
    uint32_t Rd = getBits(15, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);

    
    //Setting Instruction values
    setOp("SLT");
    // destination reg
    setParam(1, REGISTER, Rd);
    // first reg
    setParam(2, REGISTER, Rs);
    // second reg
    setParam(3, REGISTER, Rt);

    state = COMPLETE_DECODE;
}

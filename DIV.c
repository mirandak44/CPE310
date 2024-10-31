/*
Name: Miranda Kirtley
Group Members:Aishat Banire, Emily Kissner, Alexis DePue
Code Modified by Miranda: MFHI.c, DIVI.c, LUI.c, LW.c
*/
#include "Instruction.h"

void div_reg_assm(void) {
	 //check that the op code matches
    if (strcmp(OP_CODE, "DIV") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //check parameter types
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //validate register values
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

     // Encoding the DIV instruction
    setBits_str(31, "000000");    // opcode
    setBits_num(25, PARAM1.value, 5); // Rs
    setBits_num(20, PARAM2.value, 5); // Rt
    setBits_str(5, "011010");     // funct code for DIV

    state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	 //check if the opcode bits match
    if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //extract values from binary
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    
    //set instruction values
    setOp("DIV");
    setParam(1, REGISTER, Rs); // First source register
    setParam(2, REGISTER, Rt); // Second source register

    //indicate decoding is complete
    state = COMPLETE_DECODE;
}



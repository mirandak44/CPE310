/*
Name: Miranda Kirtley
Group Members:Aishat Banire, Emily Kissner, Alexis DePue
Code Modified by Miranda: MFHI.c, DIVI.c, LUI.c, LW.c
*/
#include "Instruction.h"

void mfhi_reg_assm(void) {
    //ensure the command is for MFHI
    if (strcmp(OP_CODE, "MFHI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //check that the first parameter is a register (Rd)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //validate Rd : should be 0-31
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    //set the opcode for R-type (000000)
    setBits_str(31, "000000");

    //set the function code for MFHI (010000)
    setBits_str(5, "010000");

    //set Rd 
    setBits_num(15, PARAM1.value, 5);

    //unused fields in MFHI (for Rs and Rt)
    setBits_num(25, 0, 5); // Rs
    setBits_num(20, 0, 5); // Rt

    //encoding complete
    state = COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) {
    //check if the opcode and function code bits match for MFHI
    if (checkBits(31, "000000") != 0 || checkBits(5, "010000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //retrieve Rd
    uint32_t Rd = getBits(15, 5);

    //set the operation and parameter
    setOp("MFHI");
    setParam(1, REGISTER, Rd);  // Set Rd

    //decoding complete
    state = COMPLETE_DECODE;
}

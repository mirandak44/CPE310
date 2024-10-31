/*
Name: Miranda Kirtley
Group Members:Aishat Banire, Emily Kissner, Alexis DePue
Code Modified by Miranda: MFHI.c, DIVI.c, LUI.c, LW.c
*/
#include "Instruction.h"

void lw_immd_assm(void) {
    //ensure the command is for LW
    if (strcmp(OP_CODE, "LW") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //check that the first parameter is a register (Rt)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //check that the second parameter is an immediate (offset)
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    //check that the third parameter is a register (Rs)
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //validate Rt : should be 0-31
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    //validate Rs (base register): should be 0-31
    if (PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }

    //validate offset range (16-bit signed)
    if (PARAM2.value < -32768 || PARAM2.value > 32767) {
        state = INVALID_IMMED;
        return;
    }

    //set the opcode for LW
    setBits_str(31, "100011");

    //set Rs 
    setBits_num(25, PARAM3.value, 5);

    //set Rt (destination register)
    setBits_num(20, PARAM1.value, 5);

    //set the immediate value (offset)
    setBits_num(15, PARAM2.value, 16);

    //encoding complete
    state = COMPLETE_ENCODE;
}

void lw_immd_bin(void) {
    //check if the opcode bits match for LW (100011)
    if (checkBits(31, "100011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //retrieve Rs
    uint32_t Rs = getBits(25, 5);

    //retrieve Rt 
    uint32_t Rt = getBits(20, 5);

    //retrieve the 16-bit immediate value (offset)
    int32_t offset = getBits(15, 16);  // Interpreted as a signed 16-bit number

    //set the operation and parameters
    setOp("LW");
    setParam(1, REGISTER, Rt);    // Set Rt
    setParam(2, IMMEDIATE, offset); // Set offset
    setParam(3, REGISTER, Rs);     // Set Rs (base register)

    //decoding complete
    state = COMPLETE_DECODE;
}

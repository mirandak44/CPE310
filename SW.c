/*
Name: Aishat Banire
Group Members:Miranda Kirtley, Emily Kissner, Alexis DePue
Code Modified by Aishat: SLT.c, SLTI.c, SUB.c, SW.c
*/
#include "Instruction.h"

void sw_immd_assm(void) {
    //check if opcode matches
    if (strcmp(OP_CODE, "SW") != 0){
        state = WRONG_COMMAND;
        return;
    }

    //first param should be a register rt (the source register)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //second param should be a base register rs (the address register)
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    //third param should be an immediate value (offset)
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    //Rt should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Rs should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    //check the immediate value (it should be a valid offset)
    if (PARAM3.value < -32768 || PARAM3.value > 32767) {
        state = INVALID_IMMED;
        return;
    }

    //Opcode for SW is 35 (in binary: 100011)
    setBits_num(31, 35, 6);

    //set the immediate offset (16 bits)
    setBits_num(15, PARAM3.value, 16);

    //set Rt the source register
    setBits_num(20, PARAM1.value, 5);

    //set Rs the base register
    setBits_num(25, PARAM2.value, 5);

    state = COMPLETE_ENCODE;
    
    }

void sw_immd_bin(void) {
    
    //check if the op code bits match for SW
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
        }

    uint32_t Rt = getBits(20, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t imm = getBits(15, 16);

    //instruction values
    setOp("SW");
    //source register value to store
    setParam(1, REGISTER, Rt);
    //base register
    setParam(2, REGISTER, Rs);
    //immediate offset
    setParam(3, IMMEDIATE, imm);
    
    state = COMPLETE_DECODE;
    }


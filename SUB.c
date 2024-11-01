/*
Name: Aishat Banire
Group Members:Miranda Kirtley, Emily Kissner, Alexis DePue
Code Modified by Aishat: SLT.c, SLTI.c, SUB.c, SW.c
*/

#include "Instruction.h"

void sub_reg_assm(void) {
    //check if the op code matches
    if (strcmp(OP_CODE, "SUB") != 0) {
        state = WRONG_COMMAND;
        return;
      }

    //first parameter should be a register rd (destination)
    if (PARAM1.type != REGISTER) {
          state = MISSING_REG;
          return;
      }

    //second parameter should be a register rs (first source operand)
    if (PARAM2.type != REGISTER) {
          state = MISSING_REG;
          return;
      }

    //third parameter should be a register rt (second source operand)
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
    //Opcode for R-type instructions is 0
    //set the opcode for SUB (0 for R-type)
    setBits_num(31, 0, 6);
    //function code for SUB is 34 (100010 in binary)
    //set the funct code for SUB
    setBits_str(5, "100010");

    //set Rd
    setBits_num(15, PARAM1.value, 5);

    //set Rs
    setBits_num(25, PARAM2.value, 5);

    //set Rt
    setBits_num(20, PARAM3.value, 5);

    //indicate that the encoding is done
    state = COMPLETE_ENCODE;
  }

void sub_reg_bin(void) {
    //check if the op code bits match
    if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    //Finding values in the binary
    uint32_t Rd = getBits(15, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    
    setOp("SUB");
    //destination reg
    setParam(1, REGISTER, Rd);
    setParam(2, REGISTER, Rs);
    setParam(3, REGISTER, Rt);

    state = COMPLETE_DECODE;
    
    }




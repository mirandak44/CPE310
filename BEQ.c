/*
Name: Emily Kissner
Group Members: Aishat Banire, Alexis DePue, Miranda Kirtley
Code Modified by Emily Kissner: ADD.c ADDI.c BEQ.c BNE.c
*/

#include "Instruction.h"

void beq_reg_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "BEQ") != 0) {
        // If the op code doesn't match, this isn't the correct command
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should also be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // Param 3 needs to be an immediate
    if (PARAM3.type != IMMEDIATE) {
        state = MISSING_IMMEDIATE;
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rt should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Rs should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Offset
    if (PARAM3.value < -32768 || PARAM3.value > 32767) {
        state = INVALID_OFFSET;
        return;
    }

    /*
        Putting the binary together
    */

    // Set the opcode
    setBits_num(31, 4, 6); // Assuming "000100" for BEQ

    // Set Rt
    setBits_num(25, PARAM1.value, 5);

    // Set Rs
    setBits_num(20, PARAM2.value, 5);

  // set immediate
    setBits_num(15, PARAM3.value, 16);

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void beq_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
    if (checkBits(31, "000100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Finding values in the binary
    */
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    int16_t offset = (int16_t)getBits(15, 16);  // Sign-extend the offset for branching

    /*
        Setting Instruction values
    */

    setOp("BEQ");
    setParam(1, REGISTER, Rs); 
    setParam(2, REGISTER, Rt); 
    setParam(3, IMMEDIATE, offset);

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}

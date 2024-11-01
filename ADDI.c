/*
Name: Emily Kissner
Group Members: Aishat Banire, Alexis DePue, Miranda Kirtley
Code Modified by Emily Kissner: ADD.c ADDI.c BEQ.c BNE.c
*/

#include "Instruction.h"

void addi_immd_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "ADDI") != 0) {
        // If the op code doesn't match, this isn't the correct command
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // Generally the first parameter should always be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // This is ADDI register, so param 2 needs to be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // Param 3 needs to be an immediate bc ANDI
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
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

    // The immediate value is limited to 16 bits, this is 0xFFFF
    if (PARAM3.value > 0xFFFF || PARAM3.value < -0x8000) {
        state = INVALID_IMMED;
        return;
    }



    /*
        Putting the binary together
    */

    // Set the opcode
    setBits_str(31, "001000");


    // set Rt
    setBits_num(20, PARAM1.value, 5);

    // set Rs
    setBits_num(25, PARAM2.value, 5);

    // set immediate
    setBits_num(0, PARAM3.value & 0xFFFF, 16);

    // tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void addi_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
    if (checkBits(31, "001000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // If the op code bits match, then the rest can be read as correctly

    /*
        Finding values in the binary
    */
    // getBits(start_bit, width)
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    int16_t imm16 = (int16_t)getBits(0, 16);


    /*
        Setting Instruction values
    */

    setOp("ADDI");
    setParam(1, REGISTER, Rt);       // destination
    setParam(2, REGISTER, Rs);       // first source register operand
    setParam(3, IMMEDIATE, imm16);   // second source register operand


    // tell the system the decoding is done
    state = COMPLETE_DECODE;
}


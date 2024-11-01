#include "Instruction.h"

void bne_immd_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "BNE") != 0) {
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

	// The second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
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

	// The immediate
	if (PARAM3.value > 0x7FFF || PARAM3.value < -0x8000) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "000101");

	// Set Rt
	setBits_num(25, PARAM1.value, 5);

	// Set Rs
	setBits_num(20, PARAM2.value, 5);

	// Set the immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void bne_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	int16_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("BNE");
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);
	setParam(3, IMMEDIATE, imm16);

	// Indicate decoding is complete
	state = COMPLETE_DECODE;
}

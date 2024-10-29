/*
Name:Alexis DePue
Group Members:Aishat Banire, Emily Kissner, Miranda Kirtley
Code Modified by Alexis: OR.c, ORI.c, MULT.c, MFLO.c
*/
#include "Instruction.h"

void mult_reg_assm(void) {
	// Checking that the op code matches
		// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "MULT") != 0) {
		// If the op code doesnt match, this isnt the correct command
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

	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}



	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}


	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the funct 
	setBits_str(5, "011000");

	// set Rd
	setBits_num(15, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM2.value, 5);

	// set Rt
	setBits_num(20, PARAM3.value, 5);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) 
	{
		// Check if the op code bits match
		if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
			state = WRONG_COMMAND;
			return;
		}

		// If the op code bits match, then the rest can be read as correctly

		/* Finding values in the binary */
		uint32_t Rd = getBits(15, 5);
		uint32_t Rs = getBits(25, 5);
		uint32_t Rt = getBits(20, 5);

		/* Setting Instruction values */
		setOp("MULT");
		//setCond_num(cond);
		setParam(1, REGISTER, Rd);  // destination register
		setParam(2, REGISTER, Rs);  // First source register operand
		setParam(3, REGISTER, Rt);  // Second source register operand


		// Tell the system the decoding is done
		state = COMPLETE_DECODE;
	}



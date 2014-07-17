/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __RTA_MATH_CMD_H__
#define __RTA_MATH_CMD_H__

extern enum rta_sec_era rta_sec_era;

static const uint32_t math_op1[][2] = {
/*1*/	{ _MATH0,     MATH_SRC0_REG0 },
	{ _MATH1,     MATH_SRC0_REG1 },
	{ _MATH2,     MATH_SRC0_REG2 },
	{ _MATH3,     MATH_SRC0_REG3 },
	{ _SEQINSZ,   MATH_SRC0_SEQINLEN },
	{ _SEQOUTSZ,  MATH_SRC0_SEQOUTLEN },
	{ _VSEQINSZ,  MATH_SRC0_VARSEQINLEN },
	{ _VSEQOUTSZ, MATH_SRC0_VARSEQOUTLEN },
	{ _ZERO,      MATH_SRC0_ZERO },
/*10*/	{ _NONE,      0 }, /* dummy value */
	{ _DPOVRD,    MATH_SRC0_DPOVRD },
	{ _ONE,       MATH_SRC0_ONE }
};

/*
 * Allowed MATH op1 sources for each SEC Era.
 * Values represent the number of entries from math_op1[] that are supported.
 */
static const unsigned math_op1_sz[] = {10, 10, 12, 12, 12, 12, 12, 12};

static const uint32_t math_op2[][2] = {
/*1*/	{ _MATH0,     MATH_SRC1_REG0 },
	{ _MATH1,     MATH_SRC1_REG1 },
	{ _MATH2,     MATH_SRC1_REG2 },
	{ _MATH3,     MATH_SRC1_REG3 },
	{ _ABD,       MATH_SRC1_INFIFO },
	{ _OFIFO,     MATH_SRC1_OUTFIFO },
	{ _ONE,       MATH_SRC1_ONE },
/*8*/	{ _NONE,      0 }, /* dummy value */
	{ _JOBSRC,    MATH_SRC1_JOBSOURCE },
	{ _DPOVRD,    MATH_SRC1_DPOVRD },
	{ _VSEQINSZ,  MATH_SRC1_VARSEQINLEN },
	{ _VSEQOUTSZ, MATH_SRC1_VARSEQOUTLEN },
/*13*/	{ _ZERO,      MATH_SRC1_ZERO }
};

/*
 * Allowed MATH op2 sources for each SEC Era.
 * Values represent the number of entries from math_op2[] that are supported.
 */
static const unsigned math_op2_sz[] = {8, 9, 13, 13, 13, 13, 13, 13};

static const uint32_t math_result[][2] = {
/*1*/	{ _MATH0,     MATH_DEST_REG0 },
	{ _MATH1,     MATH_DEST_REG1 },
	{ _MATH2,     MATH_DEST_REG2 },
	{ _MATH3,     MATH_DEST_REG3 },
	{ _SEQINSZ,   MATH_DEST_SEQINLEN },
	{ _SEQOUTSZ,  MATH_DEST_SEQOUTLEN },
	{ _VSEQINSZ,  MATH_DEST_VARSEQINLEN },
	{ _VSEQOUTSZ, MATH_DEST_VARSEQOUTLEN },
/*9*/	{ _NONE,      MATH_DEST_NONE },
	{ _DPOVRD,    MATH_DEST_DPOVRD }
};

/*
 * Allowed MATH result destinations for each SEC Era.
 * Values represent the number of entries from math_result[] that are
 * supported.
 */
static const unsigned math_result_sz[] = {9, 9, 10, 10, 10, 10, 10, 10};

static inline int rta_math(struct program *program, uint64_t operand1,
			   int type_op1, uint32_t op, uint64_t operand2,
			   int type_op2, uint32_t result, int type_res,
			   int length, uint32_t options)
{
	uint32_t opcode = CMD_MATH;
	uint32_t val = 0;
	int ret = -EINVAL;
	unsigned start_pc = program->current_pc;

	if (type_res != REG_TYPE) {
		pr_err("MATH: Incorrect result type. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if (((op == MATH_FUN_BSWAP) && (rta_sec_era < RTA_SEC_ERA_4)) ||
	    ((op == MATH_FUN_ZBYT) && (rta_sec_era < RTA_SEC_ERA_2))) {
		pr_err("MATH: operation not supported by SEC Era %d. SEC PC: %d; Instr: %d\n",
		       USER_SEC_ERA(rta_sec_era), program->current_pc,
		       program->current_instruction);
		goto err;
	}

	if (options & SWP) {
		if (rta_sec_era < RTA_SEC_ERA_7) {
			pr_err("MATH: operation not supported by SEC Era %d. SEC PC: %d; Instr: %d\n",
			       USER_SEC_ERA(rta_sec_era), program->current_pc,
			       program->current_instruction);
			goto err;
		}

		if ((options & IFB) ||
		    ((type_op1 != IMM_DATA) && (type_op2 != IMM_DATA)) ||
		    ((type_op1 == IMM_DATA) && (type_op2 == IMM_DATA))) {
			pr_err("MATH: SWP - invalid configuration. SEC PC: %d; Instr: %d\n",
			       program->current_pc,
			       program->current_instruction);
			goto err;
		}
	}

	/*
	 * SHLD operation is different from others and we
	 * assume that we can have _NONE as first operand
	 * or _SEQINSZ as second operand
	 */
	if ((op != MATH_FUN_SHLD) && ((operand1 == _NONE) ||
				      (operand2 == _SEQINSZ))) {
		pr_err("MATH: Invalid operand. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	/*
	 * We first check if it is unary operation. In that
	 * case second operand must be _NONE
	 */
	if (((op == MATH_FUN_ZBYT) || (op == MATH_FUN_BSWAP)) &&
	    (operand2 != _NONE)) {
		pr_err("MATH: Invalid operand2. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	/* Write first operand field */
	if (type_op1 == IMM_DATA) {
		opcode |= MATH_SRC0_IMM;
	} else {
		ret = __rta_map_opcode((uint32_t)operand1, math_op1,
				       math_op1_sz[rta_sec_era], &val);
		if (ret < 0) {
			pr_err("MATH: operand1 not supported. SEC PC: %d; Instr: %d\n",
			       program->current_pc,
			       program->current_instruction);
			goto err;
		}
		opcode |= val;
	}

	/* Write second operand field */
	if (type_op2 == IMM_DATA) {
		opcode |= MATH_SRC1_IMM;
	} else {
		ret = __rta_map_opcode((uint32_t)operand2, math_op2,
				       math_op2_sz[rta_sec_era], &val);
		if (ret < 0) {
			pr_err("MATH: operand2 not supported. SEC PC: %d; Instr: %d\n",
			       program->current_pc,
			       program->current_instruction);
			goto err;
		}
		opcode |= val;
	}

	/* Write result field */
	ret = __rta_map_opcode(result, math_result, math_result_sz[rta_sec_era],
			       &val);
	if (ret < 0) {
		pr_err("MATH: result not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}
	opcode |= val;

	/*
	 * as we encode operations with their "real" values, we do not
	 * to translate but we do need to validate the value
	 */
	switch (op) {
	/*Binary operators */
	case (MATH_FUN_ADD):
	case (MATH_FUN_ADDC):
	case (MATH_FUN_SUB):
	case (MATH_FUN_SUBB):
	case (MATH_FUN_OR):
	case (MATH_FUN_AND):
	case (MATH_FUN_XOR):
	case (MATH_FUN_LSHIFT):
	case (MATH_FUN_RSHIFT):
	case (MATH_FUN_SHLD):
	/* Unary operators */
	case (MATH_FUN_ZBYT):
	case (MATH_FUN_BSWAP):
		opcode |= op;
		break;
	default:
		pr_err("MATH: operator is not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		ret = -EINVAL;
		goto err;
	}

	opcode |= options;

	/* Verify length */
	switch (length) {
	case (1):
		opcode |= MATH_LEN_1BYTE;
		break;
	case (2):
		opcode |= MATH_LEN_2BYTE;
		break;
	case (4):
		opcode |= MATH_LEN_4BYTE;
		break;
	case (8):
		opcode |= MATH_LEN_8BYTE;
		break;
	default:
		pr_err("MATH: length is not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		ret = -EINVAL;
		goto err;
	}

	__rta_out32(program, opcode);
	program->current_instruction++;

	/* Write immediate value */
	if ((type_op1 == IMM_DATA) && (type_op2 != IMM_DATA)) {
		__rta_out64(program, (length > 4) && !(options & IFB),
			    operand1);
	} else if ((type_op2 == IMM_DATA) && (type_op1 != IMM_DATA)) {
		__rta_out64(program, (length > 4) && !(options & IFB),
			    operand2);
	} else if ((type_op1 == IMM_DATA) && (type_op2 == IMM_DATA)) {
		__rta_out32(program, lower_32_bits(operand1));
		__rta_out32(program, lower_32_bits(operand2));
	}

	return (int)start_pc;

 err:
	program->first_error_pc = start_pc;
	program->current_instruction++;
	return ret;
}

static inline int rta_mathi(struct program *program, uint64_t operand,
			    int type_op, uint32_t op, uint8_t imm, int type_imm,
			    uint32_t result, int type_res, int length,
			    uint32_t options)
{
	uint32_t opcode = CMD_MATHI;
	uint32_t val = 0;
	int ret = -EINVAL;
	unsigned start_pc = program->current_pc;

	if (rta_sec_era < RTA_SEC_ERA_6) {
		pr_err("MATHI: Command not supported by SEC Era %d. SEC PC: %d; Instr: %d\n",
		       USER_SEC_ERA(rta_sec_era), program->current_pc,
		       program->current_instruction);
		goto err;
	}

	if (type_op == IMM_DATA) {
		pr_err("MATHI: Invalid operand1, cannot be IMM. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if (type_imm != IMM_DATA) {
		pr_err("MATHI: Invalid operand2, must be IMM. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if (type_res != REG_TYPE) {
		pr_err("MATHI: Incorrect result type. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if (((op == MATH_FUN_FBYT) && (options & SSEL))) {
		pr_err("MATHI: Illegal combination - FBYT and SSEL. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if ((options & SWP) && (rta_sec_era < RTA_SEC_ERA_7)) {
		pr_err("MATHI: SWP not supported by SEC Era %d. SEC PC: %d; Instr: %d\n",
		       USER_SEC_ERA(rta_sec_era), program->current_pc,
		       program->current_instruction);
		goto err;
	}

	/* Write first operand field */
	if (!(options & SSEL))
		ret = __rta_map_opcode((uint32_t)operand, math_op1,
				       math_op1_sz[rta_sec_era], &val);
	else
		ret = __rta_map_opcode((uint32_t)operand, math_op2,
				       math_op2_sz[rta_sec_era], &val);
	if (ret < 0) {
		pr_err("MATHI: operand not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}

	if (!(options & SSEL))
		opcode |= val;
	else
		opcode |= (val << (MATHI_SRC1_SHIFT - MATH_SRC1_SHIFT));

	/* Write second operand field */
	opcode |= (imm << MATHI_IMM_SHIFT);

	/* Write result field */
	ret = __rta_map_opcode(result, math_result, math_result_sz[rta_sec_era],
			       &val);
	if (ret < 0) {
		pr_err("MATHI: result not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		goto err;
	}
	opcode |= (val << (MATHI_DEST_SHIFT - MATH_DEST_SHIFT));

	/*
	 * as we encode operations with their "real" values, we do not have to
	 * translate but we do need to validate the value
	 */
	switch (op) {
	case (MATH_FUN_ADD):
	case (MATH_FUN_ADDC):
	case (MATH_FUN_SUB):
	case (MATH_FUN_SUBB):
	case (MATH_FUN_OR):
	case (MATH_FUN_AND):
	case (MATH_FUN_XOR):
	case (MATH_FUN_LSHIFT):
	case (MATH_FUN_RSHIFT):
	case (MATH_FUN_FBYT):
		opcode |= op;
		break;
	default:
		pr_err("MATHI: operator not supported. SEC PC: %d; Instr: %d\n",
		       program->current_pc, program->current_instruction);
		ret = -EINVAL;
		goto err;
	}

	opcode |= options;

	/* Verify length */
	switch (length) {
	case (1):
		opcode |= MATH_LEN_1BYTE;
		break;
	case (2):
		opcode |= MATH_LEN_2BYTE;
		break;
	case (4):
		opcode |= MATH_LEN_4BYTE;
		break;
	case (8):
		opcode |= MATH_LEN_8BYTE;
		break;
	default:
		pr_err("MATHI: length %d not supported. SEC PC: %d; Instr: %d\n",
		       length, program->current_pc,
		       program->current_instruction);
		ret = -EINVAL;
		goto err;
	}

	__rta_out32(program, opcode);
	program->current_instruction++;

	return (int)start_pc;

 err:
	program->first_error_pc = start_pc;
	program->current_instruction++;
	return ret;
}

#endif /* __RTA_MATH_CMD_H__ */

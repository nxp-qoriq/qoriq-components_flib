#ifndef __RTA_STORE_CMD_H__
#define __RTA_STORE_CMD_H__

static const uint32_t store_src_table[31][2] = {
	{ _KEY1SZ,       LDST_CLASS_1_CCB | LDST_SRCDST_WORD_KEYSZ_REG },
	{ _KEY2SZ,       LDST_CLASS_2_CCB | LDST_SRCDST_WORD_KEYSZ_REG },
	{ _DJQDA,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_JQDAR },
	{ _MODE1,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_MODE_REG },
	{ _MODE2,        LDST_CLASS_2_CCB | LDST_SRCDST_WORD_MODE_REG },
	{ _DJQCTRL,      LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_JQCTRL },
	{ _DATA1SZ,      LDST_CLASS_1_CCB | LDST_SRCDST_WORD_DATASZ_REG },
	{ _DATA2SZ,      LDST_CLASS_2_CCB | LDST_SRCDST_WORD_DATASZ_REG },
	{ _DSTAT,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_STAT },
	{ _ICV1SZ,       LDST_CLASS_1_CCB | LDST_SRCDST_WORD_ICVSZ_REG },
	{ _ICV2SZ,       LDST_CLASS_2_CCB | LDST_SRCDST_WORD_ICVSZ_REG },
	{ _DPID,         LDST_CLASS_DECO | LDST_SRCDST_WORD_PID },
	{ _CCTRL,        LDST_SRCDST_WORD_CHACTRL },
	{ _ICTRL,        LDST_SRCDST_WORD_IRQCTRL },
	{ _CLRW,         LDST_SRCDST_WORD_CLRW },
	{ _MATH0,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_MATH0 },
	{ _CSTAT,        LDST_SRCDST_WORD_STAT },
	{ _MATH1,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_MATH1 },
	{ _MATH2,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_MATH2 },
	{ _AAD1SZ,       LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_AAD_SZ },
	{ _MATH3,        LDST_CLASS_DECO | LDST_SRCDST_WORD_DECO_MATH3 },
	{ _IV1SZ,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_CLASS1_IV_SZ },
	{ _PKASZ,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_PKHA_A_SZ },
	{ _PKBSZ,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_PKHA_B_SZ },
	{ _PKESZ,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_PKHA_E_SZ },
	{ _PKNSZ,        LDST_CLASS_1_CCB | LDST_SRCDST_WORD_PKHA_N_SZ },
	{ _CONTEXT1,     LDST_CLASS_1_CCB | LDST_SRCDST_BYTE_CONTEXT },
	{ _CONTEXT2,     LDST_CLASS_2_CCB | LDST_SRCDST_BYTE_CONTEXT },
	{ _DESCBUF,      LDST_CLASS_DECO | LDST_SRCDST_WORD_DESCBUF },
	{ _JOBDESCBUF,   LDST_CLASS_DECO | LDST_SRCDST_WORD_JOBDESCBUF },
	{ _SHAREDESCBUF, LDST_CLASS_DECO | LDST_SRCDST_WORD_SHRDESCBUF }
};


static inline uint32_t store(struct program *program, uintptr_t src,
			     int type_src, uint16_t offset, uint64_t dst,
			     int type_dst, uint32_t length, uint32_t flags)
{
	uint32_t opcode = 0, val;
	uint8_t *tmp, i;
	int8_t ret;

	if (flags & SEQ)
		opcode = CMD_SEQ_STORE;
	else
		opcode = CMD_STORE;

	if (type_src == IMM_DATA)
		flags |= IMMED;

	/* parameters check */
	if ((flags & IMMED) && (flags & SGF)) {
		pr_debug("STORE: Invalid flag. SEC PC: %d; Instr: %d\n",
			program->current_pc, program->current_instraction);
		goto err;
	}
	if ((flags & IMMED) && (offset != 0)) {
		pr_debug("STORE: Invalid flag. SEC PC: %d; Instr: %d\n",
			program->current_pc, program->current_instraction);
		goto err;
	}

	if ((flags & SEQ) && ((src == _JOBDESCBUF) || (src == _SHAREDESCBUF))) {
		pr_debug("STORE: Invalid SRC type. SEC PC: %d; Instr: %d\n",
			program->current_pc, program->current_instraction);
		goto err;
	}

	if (flags & IMMED)
		opcode |= LDST_IMM;

	if ((flags & SGF) || (flags & VLF))
		opcode |= LDST_VLF;

	/* source for data to be stored can be specified as:
	 *    - register location; set in src field[9-15];
	 *    - if immed flag is set, data is set in value field [0-31];
	 *      user can give this value as actual value or pointer to data;
	 */
	if (type_src == REG_TYPE) {
		ret = map_opcode(src, store_src_table,
				sizeof(store_src_table), &val);
		if (ret == -1) {
			pr_debug("STORE: Invalid source. SEC PC: %d; "
					"Instr: %d\n", program->current_pc,
					program->current_instraction);
			goto err;
		}
		opcode |= val;
	}

	opcode |= offset << LDST_OFFSET_SHIFT;
	opcode |= length;

	program->buffer[program->current_pc] = opcode;
	program->current_pc++;
	program->current_instraction++;

	if ((src == _JOBDESCBUF) || (src == _SHAREDESCBUF))
		return program->current_pc;

	/* for STORE, a pointer to where the data will be stored is needed */
	if (!(flags & SEQ)) {
		if (program->ps == 1) {
			program->buffer[program->current_pc++] = high_32b(dst);
			program->buffer[program->current_pc++] = low_32b(dst);
		} else {
			program->buffer[program->current_pc++] = low_32b(dst);
		}
	}

	/* for imm data, place the data here */
	if (flags & IMMED) {
		tmp = (uint8_t *) &program->buffer[program->current_pc];
		for (i = 0; i < length; i++)
			*tmp++ = ((uint8_t *) src)[i];
		program->current_pc += ((length + 3) / 4);
	}

	return program->current_pc;
 err:
	program->first_error_pc = program->current_pc;
	program->current_pc++;
	program->current_instraction++;
	return program->current_pc;
}

#endif /* __RTA_STORE_CMD_H__ */
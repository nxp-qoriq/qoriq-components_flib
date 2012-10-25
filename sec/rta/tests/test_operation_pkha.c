#include <stdio.h>
#include "rta.h"

int test_op_pkha(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;

	PROGRAM_CNTXT_INIT(buff, 0, 0);
	{
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_ADD);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_ADD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL_IM | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_ADD);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_ADD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_SUB_1);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_SUB_1 | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_SUB_2);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_SUB_2 | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL_IM);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL_IM | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL_IM);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL_IM | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL_IM_OM);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_MUL_IM_OM |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL_IM_OM);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_MUL_IM_OM |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_TEQ | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_EXP);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_EXP | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_EXP_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_EXP_TEQ | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_IM);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_IM | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_IM_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXP_IM_TEQ |
			       OP_ALG_PKMODE_OUT_A);

		PKHA_OPERATION(OP_ALG_PKMODE_MOD_AMODN);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_AMODN | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_AMODN);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_AMODN | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_INV);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_INV | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_INV);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_INV | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_ADD);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_ADD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_ADD);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_ADD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_ADD_IM_OM_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_ADD_IM_OM_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_ADD_IM_OM_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_ADD_IM_OM_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_DBL);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_DBL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_DBL);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_DBL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_DBL_IM_OM_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_DBL_IM_OM_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_DBL_IM_OM_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_DBL_IM_OM_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2 |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2 |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ_TEQ);
		PKHA_OPERATION(OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ_TEQ |
			       OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_R2);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_R2 | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_R2);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_R2 | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_RR);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_RR | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_GCD);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_GCD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_GCD);
		PKHA_OPERATION(OP_ALG_PKMODE_F2M_GCD | OP_ALG_PKMODE_OUT_A);
		PKHA_OPERATION(OP_ALG_PKMODE_PRIME_TEST);
		PKHA_OPERATION(OP_ALG_PKMODE_PRIME_TEST | OP_ALG_PKMODE_OUT_A);

		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A_B);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_A_B);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_A_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A_N);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_A_N);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B_A);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_B_A);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_B_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B_N);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_B_N);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_N_A);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_N_A);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_N_B);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_N_B);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_N_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_SSZ_N_E);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A0_B1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A0_B2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A0_B3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A1_B0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A1_B1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A1_B2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A1_B3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A2_B0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A2_B1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A2_B2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A2_B3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A3_B0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A3_B1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A3_B2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_A3_B3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B0_A1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B0_A2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B0_A3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B1_A0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B1_A1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B1_A2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B1_A3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B2_A0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B2_A1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B2_A2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B2_A3);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B3_A0);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B3_A1);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B3_A2);
		PKHA_OPERATION(OP_ALG_PKMODE_COPY_NSZ_B3_A3);

		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_A);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_B);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_AB);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_E);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_AE);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_BE);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_ABE);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_AN);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_BN);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_ABN);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_EN);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_AEN);
		PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_BEN);

		size = PKHA_OPERATION(OP_ALG_PKMODE_CLEARMEM_ALL);
	}

	return size;
}

int prg_buff[1000];

static void print_prog(uint32_t *buff, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%08X\n", buff[i]);
}

int main(int argc, char **argv)
{
	int size;
	printf("OPERATION PKHA program\n");
	size = test_op_pkha((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);
	return 0;
}

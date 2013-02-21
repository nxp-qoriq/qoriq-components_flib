#include <stdio.h>
#include "flib/rta.h"
#include "test_common.h"

enum rta_sec_era rta_sec_era;

int deco_dma(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;
	int data_size = 7040;
	int move_size = 128;	/* how many bytes to load/store at a time */
	uint64_t input = (uint64_t) 0x32a8ce00ull;
	uint64_t output = (uint64_t) 0x6d045800ull;

	LABEL(loop);
	REFERENCE(pjump1);
	LABEL(done_full);
	REFERENCE(pjump2);

	PROGRAM_SET_36BIT_ADDR();

	PROGRAM_CNTXT_INIT(buff, 0);
	/*
	 * Job to perform DMA on CAAM Era 2 (and later) platforms
	 * input/output/data_size configure the data to be moved.  move_size
	 * is to set the 'chunk' size.  Up to a limit, this determines how
	 * fast the movement will take place.  Beyond that limit, the
	 * Descriptor might not work.  move_size must be a multiple of 8.
	 */
	JOB_HDR(SHR_NEVER, 0, 0);
	{
		/*
		 * Set up the ins and outs.  These two Commands could be in a
		 * Job Descriptor (with REO), with the rest of the commands in
		 * a Shared Descriptor.
		 */
		SEQINPTR(input, data_size, WITH(EXT));
		SEQOUTPTR(output, data_size, WITH(EXT));

		/* Calculate how much data there is */
		MATHB(SEQINSZ, ADD, ZERO, VSEQINSZ, 4, 0);
		MATHB(SEQINSZ, ADD, ZERO, VSEQOUTSZ, 4, 0);

		/*
		 * Start the Burster doing reads and writes.  Input data will
		 * go to the Class 1 Alignment Block.
		 */
		SEQFIFOLOAD(MSG1, 0, WITH(VLF | LAST1));
		SEQFIFOSTORE(MSG, 0, 0, WITH(VLF));

		/*
		 * We don't want info-fifo entries to be generated by the MOVEs
		 * from 'ififoab1', as the data is already going to the Class 1
		 * Alignment Block because of the seqfifoload, above.
		 */
		LOAD(IMM(0), DCTRL, LDOFF_DISABLE_AUTO_NFIFO, 0, 0);

		/* Put MOVE length (chunk size) into Math 1 */
		MATHB(ZERO, ADD, IMM(move_size), MATH1, 4, 0);

		/* Put the last MOVE and HALT commands into Math 3 */
		MATHB(ZERO, ADD, ONE, MATH3, 8, 0);
		MOVE(IFIFOAB1, 0, OFIFO, 0, IMM(0), WITH(VLF));
		JUMP(IMM(0), HALT_STATUS, ALL_TRUE, 0);

		SET_LABEL(loop);	/* size each full transfer */
		MATHB(VSEQINSZ, SUB, MATH1, NONE, 4, 0);
		pjump2 =
		    JUMP(IMM(done_full), LOCAL_JUMP, ANY_TRUE,
				    WITH(MATH_N | MATH_Z));

		/* Move a 'full chunk' */
		MOVE(IFIFOAB1, 0, OFIFO, 0, IMM(move_size), WITH(VLF));
		MATHB(VSEQINSZ, SUB, MATH1, VSEQINSZ, 4, 0);
		pjump1 = JUMP(IMM(loop), LOCAL_JUMP, ALL_TRUE, 0);

		SET_LABEL(done_full);	/* Only last partial xfer remaining */
		/*
		 * Update the last MOVE command and move it and JUMP commands
		 * to head of descriptor buffer
		 */
		MATHB(VSEQINSZ, LSHIFT, IMM(32), MATH1, 8, WITH(IFB));
		MATHB(MATH1, OR, MATH3, MATH3, 8, 0);
		MOVE(DESCBUF, 0, MATH3, 0, IMM(8), WITH(WAITCOMP));
		JUMP(IMM(0), LOCAL_JUMP, ALL_TRUE, 0);
	}
	PATCH_JUMP(program, pjump1, loop);
	PATCH_JUMP(program, pjump2, done_full);

	size = PROGRAM_FINALIZE();
	return size;
}

int prg_buff[1000];

int main(int argc, char **argv)
{
	int size;

	printf("DECO DMA example program\n");
	rta_set_sec_era(RTA_SEC_ERA_1);
	size = deco_dma((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);

	return 0;
}

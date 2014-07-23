/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __DESC_ALGO_H__
#define __DESC_ALGO_H__

#include "flib/rta.h"
#include "common.h"

/**
 * DOC: Algorithms - Shared Descriptor Constructors
 *
 * Shared descriptors for algorithms (i.e. not for protocols).
 */

/**
 * cnstr_shdsc_snow_f8 - SNOW/f8 (UEA2) as a shared descriptor
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: points to size to be updated at completion
 * @cipherdata: pointer to block cipher transform definitions
 * @dir: Cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count: UEA2 count value (32 bits)
 * @bearer: UEA2 bearer ID (5 bits)
 * @direction: UEA2 direction (1 bit)
 */
static inline void cnstr_shdsc_snow_f8(uint32_t *descbuf, unsigned *bufsize,
			 struct alginfo *cipherdata, uint8_t dir,
			 uint32_t count, uint8_t bearer, uint8_t direction)
{
	struct program prg;
	struct program *program = &prg;
	uint64_t ct = count;
	uint64_t br = bearer;
	uint64_t dr = direction;
	uint64_t context = (ct << 32) | (br << 27) | (dr << 26);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_ALWAYS, 1, 0);

	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, IMMED);
	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F8, OP_ALG_AAI_F8,
		      OP_ALG_AS_INITFINAL, 0, dir);
	LOAD(IMM(context), CONTEXT1, 0, 8, 0);
	SEQFIFOLOAD(MSG1, 0, VLF | LAST1);
	SEQFIFOSTORE(MSG, 0, 0, VLF);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_snow_f9 - SNOW/f9 (UIA2) as a shared descriptor
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: points to size to be updated at completion
 * @authdata: pointer to authentication transform definitions
 * @dir: cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count: UEA2 count value (32 bits)
 * @fresh: UEA2 fresh value ID (32 bits)
 * @direction: UEA2 direction (1 bit)
 * @datalen: size of data
 */
static inline void cnstr_shdsc_snow_f9(uint32_t *descbuf, unsigned *bufsize,
			 struct alginfo *authdata, uint8_t dir, uint32_t count,
			 uint32_t fresh, uint8_t direction, uint32_t datalen)
{
	struct program prg;
	struct program *program = &prg;
	uint64_t ct = count;
	uint64_t fr = fresh;
	uint64_t dr = direction;
	uint64_t context[2];

	context[0] = (ct << 32) | (dr << 26);
	context[1] = fr << 32;

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_ALWAYS, 1, 0);

	KEY(KEY2, authdata->key_enc_flags, PTR(authdata->key),
	    authdata->keylen, IMMED);
	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F9, OP_ALG_AAI_F9,
		      OP_ALG_AS_INITFINAL, 0, dir);
	LOAD(PTR((uintptr_t)context), CONTEXT2, 0, 16, IMMED);
	SEQFIFOLOAD(BIT_DATA, datalen, CLASS2 | LAST2);
	/* Save lower half of MAC out into a 32-bit sequence */
	SEQSTORE(CONTEXT2, 0, 4, 0);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_cbc_blkcipher - CBC block cipher
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: limit/returned descriptor buffer size
 * @cipherdata: pointer to block cipher transform definitions
 * @iv: IV data; if NULL, "ivlen" bytes from the input frame will be read as IV
 * @ivlen: IV length
 * @dir: DIR_ENCRYPT/DIR_DECRYPT
 */
static inline void cnstr_shdsc_cbc_blkcipher(uint32_t *descbuf,
			       unsigned *bufsize, struct alginfo *cipherdata,
			       uint8_t *iv, uint32_t ivlen, uint8_t dir)
{
	struct program prg;
	struct program *program = &prg;
	const is_aes_dec = (dir == DIR_DEC) && \
			   (cipherdata->algtype == OP_ALG_ALGSEL_AES);
	LABEL(keyjmp);
	LABEL(skipdk);
	REFERENCE(pkeyjmp);
	REFERENCE(pskipdk);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_SERIAL, 1, SC);

	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, SHRD);
	/* Insert Key */
	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, IMMED);

	if (is_aes_dec) {
		ALG_OPERATION(cipherdata->algtype, OP_ALG_AAI_CBC,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_DISABLE, dir);

		pskipdk = JUMP(IMM(skipdk), LOCAL_JUMP, ALL_TRUE, 0);
	}
	SET_LABEL(keyjmp);

	if (is_aes_dec) {
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CBC | OP_ALG_AAI_DK,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_DISABLE, dir);
		SET_LABEL(skipdk);
	} else {
		ALG_OPERATION(cipherdata->algtype, OP_ALG_AAI_CBC,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_DISABLE, dir);
	}

	if (iv)
		/* IV load, convert size */
		LOAD(PTR((uintptr_t)iv), CONTEXT1, 0, ivlen, IMMED);
	else
		/* IV is present first before the actual message */
		SEQLOAD(CONTEXT1, 0, ivlen, 0);

	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, 4, 0);

	/* Insert sequence load/store with VLF */
	SEQFIFOLOAD(MSG1, 0, VLF | LAST1);
	SEQFIFOSTORE(MSG, 0, 0, VLF);

	PATCH_JUMP(pkeyjmp, keyjmp);
	if (is_aes_dec)
		PATCH_JUMP(pskipdk, skipdk);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_hmac - HMAC shared
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: limit/returned descriptor buffer size
 * @authdata: pointer to authentication transform definitions;
 *            message digest algorithm: OP_ALG_ALGSEL_MD5/ SHA1-512.
 * @do_icv: 0 if ICV checking is not desired, any other value if ICV checking
 *          is needed for all the packets processed by this shared descriptor
 * @trunc_len: Length of the truncated ICV to be written in the output buffer, 0
 *             if no truncation is needed
 *
 * Note: There's no support for keys longer than the corresponding digest size,
 * according to the selected algorithm.
 */
static inline void cnstr_shdsc_hmac(uint32_t *descbuf, unsigned *bufsize,
		      struct alginfo *authdata, uint8_t do_icv,
		      uint8_t trunc_len)
{
	struct program prg;
	struct program *program = &prg;
	uint8_t storelen, opicv, dir;
	LABEL(keyjmp);
	LABEL(jmpprecomp);
	REFERENCE(pkeyjmp);
	REFERENCE(pjmpprecomp);

	/* Compute fixed-size store based on alg selection */
	switch (authdata->algtype) {
	case OP_ALG_ALGSEL_MD5:
		storelen = 16;
		break;
	case OP_ALG_ALGSEL_SHA1:
		storelen = 20;
		break;
	case OP_ALG_ALGSEL_SHA224:
		storelen = 28;
		break;
	case OP_ALG_ALGSEL_SHA256:
		storelen = 32;
		break;
	case OP_ALG_ALGSEL_SHA384:
		storelen = 48;
		break;
	case OP_ALG_ALGSEL_SHA512:
		storelen = 64;
		break;
	default:
		return;
	}

	trunc_len = trunc_len && (trunc_len < storelen) ? trunc_len : storelen;

	opicv = do_icv ? ICV_CHECK_ENABLE : ICV_CHECK_DISABLE;
	dir == do_icv ? DIR_DEC : DIR_ENC;

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_SERIAL, 1, SC);

	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, SHRD);
	KEY(KEY2, authdata->key_enc_flags, PTR(authdata->key),
	    storelen, IMMED);

	/* Do operation */
	ALG_OPERATION(authdata->algtype, OP_ALG_AAI_HMAC,
		      OP_ALG_AS_INITFINAL, opicv, dir);

	pjmpprecomp = JUMP(IMM(jmpprecomp), LOCAL_JUMP, ALL_TRUE, 0);
	SET_LABEL(keyjmp);

	ALG_OPERATION(authdata->algtype, OP_ALG_AAI_HMAC_PRECOMP,
		      OP_ALG_AS_INITFINAL, opicv, dir);

	SET_LABEL(jmpprecomp);

	/* compute sequences */
	if (opicv == ICV_CHECK_ENABLE)
		MATHB(SEQINSZ, SUB, IMM(trunc_len), VSEQINSZ, 4, 0);
	else
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);

	/* Do load (variable length) */
	SEQFIFOLOAD(MSG2, 0, VLF | LAST2);

	if (opicv == ICV_CHECK_ENABLE)
		SEQFIFOLOAD(ICV2, trunc_len, LAST2);
	else
		SEQSTORE(CONTEXT2, 0, trunc_len, 0);

	PATCH_JUMP(pkeyjmp, keyjmp);
	PATCH_JUMP(pjmpprecomp, jmpprecomp);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_kasumi_f8 - KASUMI F8 (Confidentiality) as a shared descriptor
 *                         (ETSI "Document 1: f8 and f9 specification")
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: points to size to be updated at completion
 * @cipherdata: pointer to block cipher transform definitions
 * @dir: cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count: count value (32 bits)
 * @bearer: bearer ID (5 bits)
 * @direction: direction (1 bit)
 */
static inline void cnstr_shdsc_kasumi_f8(uint32_t *descbuf, unsigned *bufsize,
			   struct alginfo *cipherdata, uint8_t dir,
			   uint32_t count, uint8_t bearer, uint8_t direction)
{
	struct program prg;
	struct program *program = &prg;
	uint64_t ct = count;
	uint64_t br = bearer;
	uint64_t dr = direction;
	uint64_t context = (ct << 32) | (br << 27) | (dr << 26);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_ALWAYS, 1, 0);

	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, IMMED);
	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F8,
		      OP_ALG_AS_INITFINAL, 0, dir);
	LOAD(IMM(context), CONTEXT1, 0, 8, 0);
	SEQFIFOLOAD(MSG1, 0, VLF | LAST1);
	SEQFIFOSTORE(MSG, 0, 0, VLF);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_kasumi_f9 -  KASUMI F9 (Integrity) as a shared descriptor
 *                          (ETSI "Document 1: f8 and f9 specification")
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: points to size to be updated at completion
 * @authdata: pointer to authentication transform definitions
 * @dir: cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count: count value (32 bits)
 * @fresh: fresh value ID (32 bits)
 * @direction: direction (1 bit)
 * @datalen: size of data
 */
static inline void cnstr_shdsc_kasumi_f9(uint32_t *descbuf, unsigned *bufsize,
			   struct alginfo *authdata, uint8_t dir,
			   uint32_t count, uint32_t fresh, uint8_t direction,
			   uint32_t datalen)
{
	struct program prg;
	struct program *program = &prg;
	uint16_t ctx_offset = 16;
	uint64_t ct = count;
	uint64_t fr = fresh;
	uint64_t dr = direction;
	uint64_t context[3];

	context[0] = (ct << 32) | (dr << 26);
	context[1] = (fr << 32);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_ALWAYS, 1, 0);

	KEY(KEY1, authdata->key_enc_flags, PTR(authdata->key),
	    authdata->keylen, IMMED);
	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F9,
		      OP_ALG_AS_INITFINAL, 0, dir);
	LOAD(PTR((uintptr_t)context), CONTEXT1, 0, 24, IMMED);
	SEQFIFOLOAD(BIT_DATA, datalen, CLASS1 | LAST1);
	/* Save output MAC of DWORD 2 into a 32-bit sequence */
	SEQSTORE(CONTEXT1, ctx_offset, 4, 0);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_crc - CRC32 Accelerator (IEEE 802 CRC32 protocol mode)
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: limit of descriptor buffer size
 */
static inline void cnstr_shdsc_crc(uint32_t *descbuf, unsigned *bufsize)
{
	struct program prg;
	struct program *program = &prg;

	PROGRAM_CNTXT_INIT(descbuf, 0);
	SHR_HDR(SHR_ALWAYS, 1, 0);

	MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_CRC,
		      OP_ALG_AAI_802 | OP_ALG_AAI_DOC,
		      OP_ALG_AS_FINALIZE, 0, DIR_ENC);
	SEQFIFOLOAD(MSG2, 0, VLF | LAST2);
	SEQSTORE(CONTEXT2, 0, 4, 0);

	*bufsize = PROGRAM_FINALIZE();
}

#endif /* __DESC_ALGO_H__ */

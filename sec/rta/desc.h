/*
 * CAAM descriptor composition header
 * Definitions to support CAAM descriptor instruction generation
 *
 * Copyright 2008-2012 Freescale Semiconductor, Inc.
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DESC_H
#define DESC_H

/* Max size of any CAAM descriptor in 32-bit words, inclusive of header */
#define MAX_CAAM_DESCSIZE       64

/* Block size of any entity covered/uncovered with a KEK/TKEK */
#define KEK_BLOCKSIZE           16

/*
 * Supported descriptor command types as they show up
 * inside a descriptor command word.
 */
#define CMD_SHIFT               27
#define CMD_MASK                0xf8000000

#define CMD_KEY                 (0x00 << CMD_SHIFT)
#define CMD_SEQ_KEY             (0x01 << CMD_SHIFT)
#define CMD_LOAD                (0x02 << CMD_SHIFT)
#define CMD_SEQ_LOAD            (0x03 << CMD_SHIFT)
#define CMD_FIFO_LOAD           (0x04 << CMD_SHIFT)
#define CMD_SEQ_FIFO_LOAD       (0x05 << CMD_SHIFT)
#define CMD_STORE               (0x0a << CMD_SHIFT)
#define CMD_SEQ_STORE           (0x0b << CMD_SHIFT)
#define CMD_FIFO_STORE          (0x0c << CMD_SHIFT)
#define CMD_SEQ_FIFO_STORE      (0x0d << CMD_SHIFT)
#define CMD_MOVE_LEN            (0x0e << CMD_SHIFT)
#define CMD_MOVE                (0x0f << CMD_SHIFT)
#define CMD_OPERATION           (0x10 << CMD_SHIFT)
#define CMD_SIGNATURE           (0x12 << CMD_SHIFT)
#define CMD_JUMP                (0x14 << CMD_SHIFT)
#define CMD_MATH                (0x15 << CMD_SHIFT)
#define CMD_DESC_HDR            (0x16 << CMD_SHIFT)
#define CMD_SHARED_DESC_HDR     (0x17 << CMD_SHIFT)
#define CMD_SEQ_IN_PTR          (0x1e << CMD_SHIFT)
#define CMD_SEQ_OUT_PTR         (0x1f << CMD_SHIFT)

#define CMD_SEQ                 (1 << 27)

/* General-purpose class selector for all commands */
#define CLASS_SHIFT             25
#define CLASS_MASK              (0x03 << CLASS_SHIFT)

#define CLASS_NONE              (0x00 << CLASS_SHIFT)
#define CLASS_1                 (0x01 << CLASS_SHIFT)
#define CLASS_2                 (0x02 << CLASS_SHIFT)
#define CLASS_BOTH              (0x03 << CLASS_SHIFT)

/* ICV Check bits for Algo Operation command */
#define ICV_CHECK_OFF 0
#define ICV_CHECK_ON 2

/* Encap Mode check bits for Algo Operation command */
#define DIR_ENCAP 1
#define DIR_DECAP 0

/*
 * Descriptor header command constructs
 * Covers shared, job, and trusted descriptor headers
 */

/*
 * Extended Job Header
 */
#define HDR_EXT                 0x04000000

/*
 * Require SEQ LIODN to be the Same  (JOB HDR)
 */
#define HDR_RSLS                0x02000000

/*
 * Read Input Frame (SHR HDR)
 */
#define HDR_RIF                 0x02000000

/*
 * Do Not Run - marks a descriptor inexecutable if there was
 * a preceding error somewhere
 */
#define HDR_DNR                 0x01000000

/*
 * One - should always be set. Combination of ONE (always
 * set) and ZRO (always clear) forms an endianness sanity check
 */
#define HDR_ONE                 0x00800000

/*
 * ZRO - should never be set. Combination of ONE (always
 * set) and ZRO (always clear) forms an endianness sanity check
 */
#define HDR_ZRO                 0x00008000

/* Start Index or SharedDesc Length */
#define HDR_START_IDX_MASK      0x3f
#define HDR_START_IDX_SHIFT     16

/* If shared descriptor header, 6-bit length */
#define HDR_DESCLEN_SHR_MASK    0x3f

/* If non-shared header, 7-bit length */
#define HDR_DESCLEN_MASK        0x7f

/* This is a TrustedDesc (if not SharedDesc) */
#define HDR_TRUSTED             0x00004000

/* Make into TrustedDesc (if not SharedDesc) */
#define HDR_MAKE_TRUSTED        0x00002000

/* Clear Input FiFO (if SharedDesc) */
#define HDR_CLEAR_IFIFO         0x00002000

/* Save context if self-shared (if SharedDesc) */
#define HDR_SAVECTX             0x00001000

/* Next item points to SharedDesc */
#define HDR_SHARED              0x00001000

/*
 * Reverse Execution Order - execute JobDesc first, then
 * execute SharedDesc (normally SharedDesc goes first).
 */
#define HDR_REVERSE             0x00000800

/* Propogate DNR property to SharedDesc */
#define HDR_PROP_DNR            0x00000800

/* JobDesc/SharedDesc share property */
#define HDR_SD_SHARE_MASK       0x03
#define HDR_SD_SHARE_SHIFT      8
#define HDR_JD_SHARE_MASK       0x07
#define HDR_JD_SHARE_SHIFT      8

#define HDR_SHARE_NEVER         (0x00 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_WAIT          (0x01 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_SERIAL        (0x02 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_ALWAYS        (0x03 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_DEFER         (0x04 << HDR_SD_SHARE_SHIFT)

/* JobDesc/SharedDesc descriptor length */
#define HDR_JD_LENGTH_MASK      0x7f
#define HDR_SD_LENGTH_MASK      0x3f

#define HDREXT_DSELECT_VALID    0x80
#define HDREXT_DSELECT_MASK     0x7F
#define HDREXT_DSELECT_SHIFT    0

/*
 * KEY/SEQ_KEY Command Constructs
 */

/* Key Destination Class: 01 = Class 1, 02 - Class 2  */
#define KEY_DEST_CLASS_SHIFT    25
#define KEY_DEST_CLASS_MASK     (0x03 << KEY_DEST_CLASS_SHIFT)
#define KEY_DEST_CLASS1         (1 << KEY_DEST_CLASS_SHIFT)
#define KEY_DEST_CLASS2         (2 << KEY_DEST_CLASS_SHIFT)

/* Scatter-Gather Table/Variable Length Field */
#define KEY_SGF_SHIFT           24
#define KEY_SGF                 0x01000000
#define KEY_VLF                 0x01000000

/* Immediate - Key follows command in the descriptor */
#define KEY_IMM_SHIFT           23
#define KEY_IMM                 0x00800000

/*
 * Encrypted - Key is encrypted either with the KEK, or
 * with the TDKEK if this TK is set.
 */
#define KEY_ENC_SHIFT           22
#define KEY_ENC                 0x00400000

/*
 * No Write Back - Do not allow key to be FIFO STOREd
 */
#define KEY_NWB_SHIFT           21
#define KEY_NWB                 0x00200000

/*
 * Enhanced Encryption of Key
 */
#define KEY_EKT_SHIFT           20
#define KEY_EKT                 0x00100000

/*
 * Encrypted with Trusted Key
 */
#define KEY_TK_SHIFT            19
#define KEY_TK                  0x00008000

/*
 * KDEST - Key Destination: 0 - class key register,
 * 1 - PKHA 'e', 2 - AFHA Sbox, 3 - MDHA split-key
 */
#define KEY_DEST_SHIFT          16
#define KEY_DEST_MASK           (0x03 << KEY_DEST_SHIFT)

#define KEY_DEST_CLASS_REG      (0x00 << KEY_DEST_SHIFT)
#define KEY_DEST_PKHA_E         (0x01 << KEY_DEST_SHIFT)
#define KEY_DEST_AFHA_SBOX      (0x02 << KEY_DEST_SHIFT)
#define KEY_DEST_MDHA_SPLIT     (0x03 << KEY_DEST_SHIFT)

/* Length in bytes */
#define KEY_LENGTH_MASK         0x000003ff

/*
 * LOAD/SEQ_LOAD/STORE/SEQ_STORE Command Constructs
 */

/*
 * Load/Store Destination: 0 = class independent CCB,
 * 1 = class 1 CCB, 2 = class 2 CCB, 3 = DECO
 */
 /* Data Size for Load/Store commands */
#define LDST_BYTE 0x00
#define LDST_WORD 0x01

#define LDST_CLASS_SHIFT        25
#define LDST_CLASS_MASK         (0x03 << LDST_CLASS_SHIFT)
#define LDST_CLASS_IND_CCB      (0x00 << LDST_CLASS_SHIFT)
#define LDST_CLASS_1_CCB        (0x01 << LDST_CLASS_SHIFT)
#define LDST_CLASS_2_CCB        (0x02 << LDST_CLASS_SHIFT)
#define LDST_CLASS_DECO         (0x03 << LDST_CLASS_SHIFT)

/* Scatter-Gather Table/Variable Length Field */
#define LDST_SGF_SHIFT          24
#define LDST_SGF                0x01000000
#define LDST_VLF		LDST_SGF

/* Immediate - Key follows this command in descriptor    */
#define LDST_IMM_MASK           1
#define LDST_IMM_SHIFT          23
#define LDST_IMM                (LDST_IMM_MASK << LDST_IMM_SHIFT)

/* SRC/DST - Destination for LOAD, Source for STORE   */
#define LDST_SRCDST_SHIFT       16
#define LDST_SRCDST_MASK        (0x7f << LDST_SRCDST_SHIFT)

#define LDST_SRCDST_BYTE_CONTEXT        (0x20 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_KEY            (0x40 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_INFIFO         (0x7c << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_OUTFIFO        (0x7e << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_ALTSOURCE      (0x78 << LDST_SRCDST_SHIFT)

#define LDST_SRCDST_WORD_MODE_REG       (0x00 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_JQCTRL    (0x00 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_KEYSZ_REG      (0x01 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_JQDAR     (0x01 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DATASZ_REG     (0x02 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_STAT      (0x02 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_ICVSZ_REG      (0x03 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PID            (0x04 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CHACTRL        (0x06 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECOCTRL       (0x06 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_IRQCTRL        (0x07 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_PCLOVRD   (0x07 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLRW           (0x08 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH0     (0x08 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_STAT           (0x09 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH1     (0x09 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH2     (0x0a << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLASS1_ICV_SZ  (0x0c << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_AAD_SZ    (0x0b << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH3     (0x0b << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLASS1_IV_SZ   (0x0c << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_ALTDS_CLASS1   (0x0f << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_A_SZ      (0x10 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_B_SZ      (0x11 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_N_SZ      (0x12 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_E_SZ      (0x13 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF        (0x40 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_JOBDESCBUF     (0x41 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_SHRDESCBUF     (0x42 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_SZL  (0x70 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_SZM  (0x71 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_L    (0x72 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_M    (0x73 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_SZL            (0x74 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_SZM            (0x75 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_OFNSR          (0x76 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_IFNSR          (0x77 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO      (0x7a << LDST_SRCDST_SHIFT)

/* Offset in source/destination                        */
#define LDST_OFFSET_SHIFT               8
#define LDST_OFFSET_MASK                (0xff << LDST_OFFSET_SHIFT)

/* Special Offset definitions when dst=deco-ctrl */
#define LDOFF_CHG_SHARE_SHIFT           0
#define LDOFF_CHG_SHARE_MASK            (0x3 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_NEVER           (0x1 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_OK_NO_PROP      (0x2 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_OK_PROP         (0x3 << LDOFF_CHG_SHARE_SHIFT)

#define LDOFF_ENABLE_AUTO_IFIFO         (1 << 2)
#define LDOFF_DISABLE_AUTO_IFIFO        (1 << 3)

#define LDOFF_CHG_NONSEQLIODN_SHIFT     4
#define LDOFF_CHG_NONSEQLIODN_MASK      (0x3 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_SEQ       (0x1 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_NON_SEQ   (0x2 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_TRUSTED   (0x3 << LDOFF_CHG_NONSEQLIODN_SHIFT)

#define LDOFF_CHG_SEQLIODN_SHIFT        6
#define LDOFF_CHG_SEQLIODN_MASK         (0x3 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_SEQ          (0x1 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_NON_SEQ      (0x2 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_TRUSTED      (0x3 << LDOFF_CHG_SEQLIODN_SHIFT)

/* Data length in bytes                                 */
#define LDST_LEN_SHIFT                  0
#define LDST_LEN_MASK                   (0xff << LDST_LEN_SHIFT)

/* Special Length definitions when dst=deco-ctrl */
#define LDLEN_ENABLE_OSL_COUNT          (1 << 7)
#define LDLEN_RST_CHA_OFIFO_PTR         (1 << 6)
#define LDLEN_RST_OFIFO                 (1 << 5)
#define LDLEN_SET_OFIFO_OFF_VALID       (1 << 4)
#define LDLEN_SET_OFIFO_OFF_RSVD        (1 << 3)
#define LDLEN_SET_OFIFO_OFFSET_SHIFT    0
#define LDLEN_SET_OFIFO_OFFSET_MASK     (3 << LDLEN_SET_OFIFO_OFFSET_SHIFT)

/* CCB IRQ Control Register bits */
#define IRQC_CLR_AESA_DONE           0x2
#define IRQC_CLR_DESA_DONE           0x4
#define IRQC_CLR_AFHA_DONE           0x8
#define IRQC_CLR_KFHA_DONE           0x10
#define IRQC_CLR_SF8A_DONE           0x20
#define IRQC_CLR_PKHA_DONE           0x40
#define IRQC_CLR_MDHA_DONE           0x80
#define IRQC_CLR_CRCA_DONE           0x100
#define IRQC_CLR_RNG_DONE            0x200
#define IRQC_CLR_SF9A_DONE           0x400
#define IRQC_CLR_AESA_ERROR          0x20000
#define IRQC_CLR_DESA_ERROR          0x40000
#define IRQC_CLR_AFHA_ERROR          0x80000
#define IRQC_CLR_KFHA_ERROR          0x100000
#define IRQC_CLR_SF8A_ERROR          0x200000
#define IRQC_CLR_PKHA_ERROR          0x400000
#define IRQC_CLR_MDHA_ERROR          0x800000
#define IRQC_CLR_CRCA_ERROR          0x1000000
#define IRQC_CLR_RNG_ERROR           0x2000000
#define IRQC_CLR_SF9A_ERROR          0x4000000

/* CCB Clear Written Register bits */
#define CLRW_CLR_C1MODE              0x1
#define CLRW_CLR_C1DATAS             0x4
#define CLRW_CLR_C1ICV               0x8
#define CLRW_CLR_C1CTX               0x20
#define CLRW_CLR_C1KEY               0x40
#define CLRW_CLR_PK_A                0x1000
#define CLRW_CLR_PK_B                0x2000
#define CLRW_CLR_PK_N                0x4000
#define CLRW_CLR_PK_E                0x8000
#define CLRW_CLR_C2MODE              0x10000
#define CLRW_CLR_C2KEYS              0x20000
#define CLRW_CLR_C2DATAS             0x40000
#define CLRW_CLR_C2CTX               0x200000
#define CLRW_CLR_C2KEY               0x400000
#define CLRW_RESET_CLS2_DONE         0x04000000u /* era 4 */
#define CLRW_RESET_CLS1_DONE         0x08000000u /* era 4 */
#define CLRW_RESET_CLS2_CHA          0x10000000u /* era 4 */
#define CLRW_RESET_CLS1_CHA          0x20000000u /* era 4 */
#define CLRW_RESET_OFIFO             0x40000000u /* era 3 */
#define CLRW_RESET_IFIFO_DFIFO       0x80000000u /* era 3 */

/* CHA Control Register bits */
#define CCTRL_RESET_CHA_ALL          0x1
#define CCTRL_RESET_CHA_AESA         0x2
#define CCTRL_RESET_CHA_DESA         0x4
#define CCTRL_RESET_CHA_AFHA         0x8
#define CCTRL_RESET_CHA_KFHA         0x10
#define CCTRL_RESET_CHA_SF8A         0x20
#define CCTRL_RESET_CHA_PKHA         0x40
#define CCTRL_RESET_CHA_MDHA         0x80
#define CCTRL_RESET_CHA_CRCA         0x100
#define CCTRL_RESET_CHA_RNG          0x200
#define CCTRL_RESET_CHA_SF9A         0x400
#define CCTRL_UNLOAD_PK_A0           0x10000
#define CCTRL_UNLOAD_PK_A1           0x20000
#define CCTRL_UNLOAD_PK_A2           0x40000
#define CCTRL_UNLOAD_PK_A3           0x80000
#define CCTRL_UNLOAD_PK_B0           0x100000
#define CCTRL_UNLOAD_PK_B1           0x200000
#define CCTRL_UNLOAD_PK_B2           0x400000
#define CCTRL_UNLOAD_PK_B3           0x800000
#define CCTRL_UNLOAD_PK_N            0x1000000
#define CCTRL_UNLOAD_PK_A            0x4000000
#define CCTRL_UNLOAD_PK_B            0x8000000
#define CCTRL_UNLOAD_SBOX            0x10000000

/*
 * FIFO_LOAD/FIFO_STORE/SEQ_FIFO_LOAD/SEQ_FIFO_STORE
 * Command Constructs
 */

/*
 * Load Destination: 0 = skip (SEQ_FIFO_LOAD only),
 * 1 = Load for Class1, 2 = Load for Class2, 3 = Load both
 * Store Source: 0 = normal, 1 = Class1key, 2 = Class2key
 */
#define FIFOLD_CLASS_SHIFT           25
#define FIFOLD_CLASS_MASK            (0x03 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_SKIP            (0x00 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_CLASS1          (0x01 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_CLASS2          (0x02 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_BOTH            (0x03 << FIFOLD_CLASS_SHIFT)

#define FIFOST_CLASS_SHIFT           25
#define FIFOST_CLASS_MASK            (0x03 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_NORMAL          (0x00 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_CLASS1KEY       (0x01 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_CLASS2KEY       (0x02 << FIFOST_CLASS_SHIFT)

/*
 * Scatter-Gather Table/Variable Length Field
 * If set for FIFO_LOAD, refers to a SG table. Within
 * SEQ_FIFO_LOAD, is variable input sequence
 */
#define FIFOLDST_SGF_SHIFT           24
#define FIFOLDST_SGF_MASK            (1 << FIFOLDST_SGF_SHIFT)
#define FIFOLDST_VLF_MASK            (1 << FIFOLDST_SGF_SHIFT)
#define FIFOLDST_SGF                 (1 << FIFOLDST_SGF_SHIFT)
#define FIFOLDST_VLF                 (1 << FIFOLDST_SGF_SHIFT)

/* Immediate - Data follows command in descriptor */
#define FIFOLD_IMM_SHIFT             23
#define FIFOLD_IMM_MASK              (1 << FIFOLD_IMM_SHIFT)
#define FIFOLD_IMM                   (1 << FIFOLD_IMM_SHIFT)

/* Continue - Not the last FIFO store to come */
#define FIFOST_CONT_SHIFT            23
#define FIFOST_CONT_MASK             (1 << FIFOST_CONT_SHIFT)
#define FIFOST_CONT                  (1 << FIFOST_CONT_SHIFT)

/*
 * Extended Length - use 32-bit extended length that
 * follows the pointer field. Illegal with IMM set
 */
#define FIFOLDST_EXT_SHIFT           22
#define FIFOLDST_EXT_MASK            (1 << FIFOLDST_EXT_SHIFT)
#define FIFOLDST_EXT                 (1 << FIFOLDST_EXT_SHIFT)

/* Input data type.*/
#define FIFOLD_TYPE_SHIFT            16
#define FIFOLD_CONT_TYPE_SHIFT       19 /* shift past last-flush bits */
#define FIFOLD_TYPE_MASK             (0x3f << FIFOLD_TYPE_SHIFT)

/* Just to Input Data FIFO */
#define FIFOLD_TYPE_DFIFO            (0x0f << FIFOLD_TYPE_SHIFT)

/* PK types */
#define FIFOLD_TYPE_PK               (0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_MASK          (0x30 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_TYPEMASK      (0x0f << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A0            (0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A1            (0x01 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A2            (0x02 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A3            (0x03 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B0            (0x04 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B1            (0x05 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B2            (0x06 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B3            (0x07 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_N             (0x08 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A             (0x0c << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B             (0x0d << FIFOLD_TYPE_SHIFT)

/* Other types. Need to OR in last/flush bits as desired */
#define FIFOLD_TYPE_MSG_MASK         (0x38 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_MSG              (0x10 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_MSG1OUT2         (0x18 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_IV               (0x20 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_BITDATA          (0x28 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_AAD              (0x30 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_ICV              (0x38 << FIFOLD_TYPE_SHIFT)

/* Last/Flush bits for use with "other" types above */
#define FIFOLD_TYPE_ACT_MASK         (0x07 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_NOACTION         (0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_FLUSH1           (0x01 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST1            (0x02 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2FLUSH       (0x03 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2            (0x04 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2FLUSH1      (0x05 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LASTBOTH         (0x06 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LASTBOTHFL       (0x07 << FIFOLD_TYPE_SHIFT)

#define FIFOLDST_LEN_MASK            0xffff
#define FIFOLDST_EXT_LEN_MASK        0xffffffff

/* Output data types */
#define FIFOST_TYPE_SHIFT            16
#define FIFOST_TYPE_MASK             (0x3f << FIFOST_TYPE_SHIFT)

#define FIFOST_TYPE_PKHA_A0          (0x00 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A1          (0x01 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A2          (0x02 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A3          (0x03 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B0          (0x04 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B1          (0x05 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B2          (0x06 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B3          (0x07 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_N           (0x08 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A           (0x0c << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B           (0x0d << FIFOST_TYPE_SHIFT)

#define FIFOST_TYPE_AF_SBOX_JKEK_EKT (0x10 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_AF_SBOX_TKEK_EKT (0x11 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_JKEK_EKT  (0x12 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_TKEK_EKT  (0x13 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_KEK_EKT      (0x14 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_TKEK_EKT     (0x15 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_KEK_EKT    (0x16 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_TKEK_EKT   (0x17 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_KEK_EKT  (0x18 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_TKEK_EKT (0x19 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_INFIFO_KEK_EKT   (0x1A << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_INFIFO_TKEK_EKT  (0x1B << FIFOST_TYPE_SHIFT)

#define FIFOST_TYPE_AF_SBOX_JKEK     (0x20 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_AF_SBOX_TKEK     (0x21 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_JKEK      (0x22 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_TKEK      (0x23 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_KEK          (0x24 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_TKEK         (0x25 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_KEK        (0x26 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_TKEK       (0x27 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_KEK      (0x28 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_TKEK     (0x29 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_INFIFO_KEK       (0x2A << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_INFIFO_TKEK      (0x2B << FIFOST_TYPE_SHIFT)

#define FIFOST_TYPE_MESSAGE_DATA     (0x30 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_RNGSTORE         (0x34 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_RNGFIFO          (0x35 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_META_DATA        (0x3e << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SKIP             (0x3f << FIFOST_TYPE_SHIFT)

/*
 * OPERATION Command Constructs
 */

/* Operation type selectors - OP TYPE */
#define OP_TYPE_SHIFT                24
#define OP_TYPE_MASK                 (0x07 << OP_TYPE_SHIFT)

#define OP_TYPE_UNI_PROTOCOL         (0x00 << OP_TYPE_SHIFT)
#define OP_TYPE_PKHA                 (0x01 << OP_TYPE_SHIFT)
#define OP_TYPE_CLASS1_ALG           (0x02 << OP_TYPE_SHIFT)
#define OP_TYPE_CLASS2_ALG           (0x04 << OP_TYPE_SHIFT)
#define OP_TYPE_DECAP_PROTOCOL       (0x06 << OP_TYPE_SHIFT)
#define OP_TYPE_ENCAP_PROTOCOL       (0x07 << OP_TYPE_SHIFT)

/* ProtocolID selectors - PROTID */
#define OP_PCLID_SHIFT               16
#define OP_PCLID_MASK                (0xff << 16)

#define OP_RSA_DEC_OP_SHIFT          0
#define OP_RSA_DEC_OP_MASK           (0x3 << OP_RSA_DEC_OP_SHIFT)
#define OP_RSA_DEC_OP_ND             (0x0 << OP_RSA_DEC_OP_SHIFT)
#define OP_RSA_DEC_OP_PQD            (0x1 << OP_RSA_DEC_OP_SHIFT)
#define OP_RSA_DEC_OP_PQDPDQC        (0x2 << OP_RSA_DEC_OP_SHIFT)

/* Assuming OP_TYPE = OP_TYPE_UNI_PROTOCOL */
#define OP_PCLID_IKEV1_PRF           (0x01 << OP_PCLID_SHIFT)
#define OP_PCLID_IKEV2_PRF           (0x02 << OP_PCLID_SHIFT)
#define OP_PCLID_SSL30_PRF           (0x08 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS10_PRF           (0x09 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS11_PRF           (0x0a << OP_PCLID_SHIFT)
#define OP_PCLID_TLS12_PRF           (0x0b << OP_PCLID_SHIFT)
#define OP_PCLID_DTLS10_PRF          (0x0c << OP_PCLID_SHIFT)
#define OP_PCLID_PUBLICKEYPAIR       (0x14 << OP_PCLID_SHIFT)
#define OP_PCLID_DSASIGN             (0x15 << OP_PCLID_SHIFT)
#define OP_PCLID_DSAVERIFY           (0x16 << OP_PCLID_SHIFT)
#define OP_PCLID_DIFFIEHELLMAN       (0x17 << OP_PCLID_SHIFT)
#define OP_PCLID_RSAENCRYPT          (0x18 << OP_PCLID_SHIFT)
#define OP_PCLID_RSADECRYPT          (0x19 << OP_PCLID_SHIFT)

/* Assuming OP_TYPE = OP_TYPE_DECAP_PROTOCOL/ENCAP_PROTOCOL */
#define OP_PCLID_IPSEC               (0x01 << OP_PCLID_SHIFT)
#define OP_PCLID_SRTP                (0x02 << OP_PCLID_SHIFT)
#define OP_PCLID_MACSEC              (0x03 << OP_PCLID_SHIFT)
#define OP_PCLID_WIFI                (0x04 << OP_PCLID_SHIFT)
#define OP_PCLID_WIMAX               (0x05 << OP_PCLID_SHIFT)
#define OP_PCLID_SSL30               (0x08 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS10               (0x09 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS11               (0x0a << OP_PCLID_SHIFT)
#define OP_PCLID_TLS12               (0x0b << OP_PCLID_SHIFT)
#define OP_PCLID_DTLS                (0x0c << OP_PCLID_SHIFT)
#define OP_PCLID_DTLS10              (0x0c << OP_PCLID_SHIFT)
#define OP_PCLID_BLOB                (0x0d << OP_PCLID_SHIFT)
#define OP_PCLID_ANTIREPLAY          (0x0f << OP_PCLID_SHIFT)
#define OP_PCLID_3G_DCRC             (0x31 << OP_PCLID_SHIFT)
#define OP_PCLID_3G_RLC_PDU          (0x32 << OP_PCLID_SHIFT)
#define OP_PCLID_3G_RLC_SDU          (0x33 << OP_PCLID_SHIFT)
#define OP_PCLID_LTE_PDCP_USER       (0x42 << OP_PCLID_SHIFT)
#define OP_PCLID_LTE_PDCP_CTRL       (0x43 << OP_PCLID_SHIFT)

/*
 * ProtocolInfo selectors
 */
#define OP_PCLINFO_MASK                 0xffff

/* for OP_PCLID_IPSEC */
#define OP_PCL_IPSEC_CIPHER_MASK        0xff00
#define OP_PCL_IPSEC_AUTH_MASK          0x00ff

#define OP_PCL_IPSEC_DES_IV64           0x0100
#define OP_PCL_IPSEC_DES                0x0200
#define OP_PCL_IPSEC_3DES               0x0300
#define OP_PCL_IPSEC_NULL               0x0B00
#define OP_PCL_IPSEC_AES_CBC            0x0c00
#define OP_PCL_IPSEC_AES_CTR            0x0d00
#define OP_PCL_IPSEC_AES_CCM8           0x0e00
#define OP_PCL_IPSEC_AES_CCM12          0x0f00
#define OP_PCL_IPSEC_AES_CCM16          0x1000
#define OP_PCL_IPSEC_AES_GCM8           0x1200
#define OP_PCL_IPSEC_AES_GCM12          0x1300
#define OP_PCL_IPSEC_AES_GCM16          0x1400
#define OP_PCL_IPSEC_AES_NULL_WITH_GMAC 0x1500

#define OP_PCL_IPSEC_HMAC_NULL          0x0000
#define OP_PCL_IPSEC_HMAC_MD5_96        0x0001
#define OP_PCL_IPSEC_HMAC_SHA1_96       0x0002
#define OP_PCL_IPSEC_AES_XCBC_MAC_96    0x0005
#define OP_PCL_IPSEC_HMAC_MD5_128       0x0006
#define OP_PCL_IPSEC_HMAC_SHA1_160      0x0007
#define OP_PCL_IPSEC_AES_CMAC_96        0x0008
#define OP_PCL_IPSEC_HMAC_SHA2_256_128  0x000c
#define OP_PCL_IPSEC_HMAC_SHA2_384_192  0x000d
#define OP_PCL_IPSEC_HMAC_SHA2_512_256  0x000e

/* For SRTP - OP_PCLID_SRTP */
#define OP_PCL_SRTP_CIPHER_MASK         0xff00
#define OP_PCL_SRTP_AUTH_MASK           0x00ff
#define OP_PCL_SRTP_AES_CTR             0x0d00
#define OP_PCL_SRTP_HMAC_SHA1_160       0x0007

/*
   For SSL, TLS, and DTLS - not every value valid with each protocol
   See http://www.iana.org/assignments/tls-parameters/tls-parameters.xml
 */
#define OP_PCL_TLS_RSA_EXPORT_WITH_RC4_40_MD5           0x0003
#define OP_PCL_TLS_RSA_WITH_RC4_128_MD5                 0x0004
#define OP_PCL_TLS_RSA_WITH_RC4_128_SHA                 0x0005
#define OP_PCL_TLS_RSA_EXPORT_WITH_DES40_CBC_SHA        0x0008
#define OP_PCL_TLS_RSA_WITH_DES_CBC_SHA                 0x0009
#define OP_PCL_TLS_RSA_WITH_3DES_EDE_CBC_SHA            0x000A
#define OP_PCL_TLS_DH_DSS_EXPORT_WITH_DES40_CBC_SHA     0x000B
#define OP_PCL_TLS_DH_DSS_WITH_DES_CBC_SHA              0x000C
#define OP_PCL_TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA         0x000D
#define OP_PCL_TLS_DH_RSA_EXPORT_WITH_DES40_CBC_SHA     0x000E
#define OP_PCL_TLS_DH_RSA_WITH_DES_CBC_SHA              0x000F
#define OP_PCL_TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA         0x0010
#define OP_PCL_TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA    0x0011
#define OP_PCL_TLS_DHE_DSS_WITH_DES_CBC_SHA             0x0012
#define OP_PCL_TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA        0x0013
#define OP_PCL_TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA    0x0014
#define OP_PCL_TLS_DHE_RSA_WITH_DES_CBC_SHA             0x0015
#define OP_PCL_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA        0x0016
#define OP_PCL_TLS_DH_ANON_EXPORT_WITH_RC4_40_MD5       0x0017
#define OP_PCL_TLS_DH_ANON_WITH_RC4_128_MD5             0x0018
#define OP_PCL_TLS_DH_ANON_EXPORT_WITH_DES40_CBC_SHA    0x0019
#define OP_PCL_TLS_DH_ANON_WITH_DES_CBC_SHA             0x001A
#define OP_PCL_TLS_DH_ANON_WITH_3DES_EDE_CBC_SHA        0x001B
#define OP_PCL_TLS_KRB5_WITH_DES_CBC_SHA                0x001E
#define OP_PCL_TLS_KRB5_WITH_3DES_EDE_CBC_SHA           0x001F
#define OP_PCL_TLS_KRB5_WITH_RC4_128_SHA                0x0020
#define OP_PCL_TLS_KRB5_WITH_DES_CBC_MD5                0x0022
#define OP_PCL_TLS_KRB5_WITH_3DES_EDE_CBC_MD5           0x0023
#define OP_PCL_TLS_KRB5_WITH_RC4_128_MD5                0x0024
#define OP_PCL_TLS_KRB5_EXPORT_WITH_DES_CBC_40_SHA      0x0026
#define OP_PCL_TLS_KRB5_EXPORT_WITH_RC4_40_SHA          0x0028
#define OP_PCL_TLS_KRB5_EXPORT_WITH_DES_CBC_40_MD5      0x0029
#define OP_PCL_TLS_KRB5_EXPORT_WITH_RC4_40_MD5          0x002B
#define OP_PCL_TLS_RSA_WITH_AES_128_CBC_SHA             0x002F
#define OP_PCL_TLS_DH_DSS_WITH_AES_128_CBC_SHA          0x0030
#define OP_PCL_TLS_DH_RSA_WITH_AES_128_CBC_SHA          0x0031
#define OP_PCL_TLS_DHE_DSS_WITH_AES_128_CBC_SHA         0x0032
#define OP_PCL_TLS_DHE_RSA_WITH_AES_128_CBC_SHA         0x0033
#define OP_PCL_TLS_DH_ANON_WITH_AES_128_CBC_SHA         0x0034
#define OP_PCL_TLS_RSA_WITH_AES_256_CBC_SHA             0x0035
#define OP_PCL_TLS_DH_DSS_WITH_AES_256_CBC_SHA          0x0036
#define OP_PCL_TLS_DH_RSA_WITH_AES_256_CBC_SHA          0x0037
#define OP_PCL_TLS_DHE_DSS_WITH_AES_256_CBC_SHA         0x0038
#define OP_PCL_TLS_DHE_RSA_WITH_AES_256_CBC_SHA         0x0039
#define OP_PCL_TLS_DH_ANON_WITH_AES_256_CBC_SHA         0x003A
#define OP_PCL_TLS_RSA_WITH_AES_128_CBC_SHA256          0x003C
#define OP_PCL_TLS_RSA_WITH_AES_256_CBC_SHA256          0x003D
#define OP_PCL_TLS_DH_DSS_WITH_AES_128_CBC_SHA256       0x003E
#define OP_PCL_TLS_DH_RSA_WITH_AES_128_CBC_SHA256       0x003F
#define OP_PCL_TLS_DHE_DSS_WITH_AES_128_CBC_SHA256      0x0040
#define OP_PCL_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256      0x0067
#define OP_PCL_TLS_DH_DSS_WITH_AES_256_CBC_SHA256       0x0068
#define OP_PCL_TLS_DH_RSA_WITH_AES_256_CBC_SHA256       0x0069
#define OP_PCL_TLS_DHE_DSS_WITH_AES_256_CBC_SHA256      0x006A
#define OP_PCL_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256      0x006B
#define OP_PCL_TLS_DH_ANON_WITH_AES_128_CBC_SHA256      0x006C
#define OP_PCL_TLS_DH_ANON_WITH_AES_256_CBC_SHA256      0x006D
#define OP_PCL_TLS_PSK_WITH_RC4_128_SHA                 0x008A
#define OP_PCL_TLS_PSK_WITH_3DES_EDE_CBC_SHA            0x008B
#define OP_PCL_TLS_PSK_WITH_AES_128_CBC_SHA             0x008C
#define OP_PCL_TLS_PSK_WITH_AES_256_CBC_SHA             0x008D
#define OP_PCL_TLS_DHE_PSK_WITH_RC4_128_SHA             0x008E
#define OP_PCL_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA        0x008F
#define OP_PCL_TLS_DHE_PSK_WITH_AES_128_CBC_SHA         0x0090
#define OP_PCL_TLS_DHE_PSK_WITH_AES_256_CBC_SHA         0x0091
#define OP_PCL_TLS_RSA_PSK_WITH_RC4_128_SHA             0x0092
#define OP_PCL_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA        0x0093
#define OP_PCL_TLS_RSA_PSK_WITH_AES_128_CBC_SHA         0x0094
#define OP_PCL_TLS_RSA_PSK_WITH_AES_256_CBC_SHA         0x0095
#define OP_PCL_TLS_RSA_WITH_AES_128_GCM_SHA256          0x009C
#define OP_PCL_TLS_RSA_WITH_AES_256_GCM_SHA384          0x009D
#define OP_PCL_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256      0x009E
#define OP_PCL_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384      0x009F
#define OP_PCL_TLS_DH_RSA_WITH_AES_128_GCM_SHA256       0x00A0
#define OP_PCL_TLS_DH_RSA_WITH_AES_256_GCM_SHA384       0x00A1
#define OP_PCL_TLS_DHE_DSS_WITH_AES_128_GCM_SHA256      0x00A2
#define OP_PCL_TLS_DHE_DSS_WITH_AES_256_GCM_SHA384      0x00A3
#define OP_PCL_TLS_DH_DSS_WITH_AES_128_GCM_SHA256       0x00A4
#define OP_PCL_TLS_DH_DSS_WITH_AES_256_GCM_SHA384       0x00A5
#define OP_PCL_TLS_DH_ANON_WITH_AES_128_GCM_SHA256      0x00A6
#define OP_PCL_TLS_DH_ANON_WITH_AES_256_GCM_SHA384      0x00A7
#define OP_PCL_TLS_PSK_WITH_AES_128_GCM_SHA256          0x00A8
#define OP_PCL_TLS_PSK_WITH_AES_256_GCM_SHA384          0x00A9
#define OP_PCL_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256      0x00AA
#define OP_PCL_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384      0x00AB
#define OP_PCL_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256      0x00AC
#define OP_PCL_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384      0x00AD
#define OP_PCL_TLS_PSK_WITH_AES_128_CBC_SHA256          0x00AE
#define OP_PCL_TLS_PSK_WITH_AES_256_CBC_SHA384          0x00AF
#define OP_PCL_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256      0x00B2
#define OP_PCL_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384      0x00B3
#define OP_PCL_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256      0x00B6
#define OP_PCL_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384      0x00B7
#define OP_PCL_TLS_ECDH_ECDSA_WITH_RC4_128_SHA          0xC002
#define OP_PCL_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA     0xC003
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA      0xC004
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA      0xC005
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA         0xC007
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA    0xC008
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA     0xC009
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA     0xC00A
#define OP_PCL_TLS_ECDH_RSA_WITH_RC4_128_SHA            0xC00C
#define OP_PCL_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA       0xC00D
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA        0xC00E
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA        0xC00F
#define OP_PCL_TLS_ECDHE_RSA_WITH_RC4_128_SHA           0xC011
#define OP_PCL_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA      0xC012
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA       0xC013
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA       0xC014
#define OP_PCL_TLS_ECDH_ANON_WITH_RC4_128_SHA           0xC016
#define OP_PCL_TLS_ECDH_ANON_WITH_3DES_EDE_CBC_SHA      0xC017
#define OP_PCL_TLS_ECDH_ANON_WITH_AES_128_CBC_SHA       0xC018
#define OP_PCL_TLS_ECDH_ANON_WITH_AES_256_CBC_SHA       0xC019
#define OP_PCL_TLS_SRP_SHA_WITH_3DES_EDE_CBC_SHA        0xC01A
#define OP_PCL_TLS_SRP_SHA_RSA_WITH_3DES_EDE_CBC_SHA    0xC01B
#define OP_PCL_TLS_SRP_SHA_DSS_WITH_3DES_EDE_CBC_SHA    0xC01C
#define OP_PCL_TLS_SRP_SHA_WITH_AES_128_CBC_SHA         0xC01D
#define OP_PCL_TLS_SRP_SHA_RSA_WITH_AES_128_CBC_SHA     0xC01E
#define OP_PCL_TLS_SRP_SHA_DSS_WITH_AES_128_CBC_SHA     0xC01F
#define OP_PCL_TLS_SRP_SHA_WITH_AES_256_CBC_SHA         0xC020
#define OP_PCL_TLS_SRP_SHA_RSA_WITH_AES_256_CBC_SHA     0xC021
#define OP_PCL_TLS_SRP_SHA_DSS_WITH_AES_256_CBC_SHA     0xC022
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256  0xC023
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384  0xC024
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256   0xC025
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384   0xC026
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256    0xC027
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384    0xC028
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256     0xC029
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384     0xC02A
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256  0xC02B
#define OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384  0xC02C
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256   0xC02D
#define OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384   0xC02E
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256    0xC02F
#define OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384    0xC030
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256     0xC031
#define OP_PCL_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384     0xC032
#define OP_PCL_TLS_ECDHE_PSK_WITH_RC4_128_SHA           0xC033
#define OP_PCL_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA      0xC034
#define OP_PCL_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA       0xC035
#define OP_PCL_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA       0xC036
#define OP_PCL_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256    0xC037
#define OP_PCL_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384    0xC038

#define OP_PCL_TLS_PVT_3DES_EDE_CBC_MD5                 0xff23

#define OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA160              0xff30
#define OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA384              0xff33
#define OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA224              0xff34
#define OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA512              0xff35
#define OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA256              0xff36

#define OP_PCL_TLS_PVT_AES_128_CBC_SHA160               0xff80
#define OP_PCL_TLS_PVT_AES_128_CBC_SHA384               0xff83
#define OP_PCL_TLS_PVT_AES_128_CBC_SHA224               0xff84
#define OP_PCL_TLS_PVT_AES_128_CBC_SHA512               0xff85
#define OP_PCL_TLS_PVT_AES_128_CBC_SHA256               0xff86

#define OP_PCL_TLS_PVT_AES_256_CBC_SHA160               0xff60
#define OP_PCL_TLS_PVT_AES_256_CBC_SHA384               0xff63
#define OP_PCL_TLS_PVT_AES_256_CBC_SHA224               0xff64
#define OP_PCL_TLS_PVT_AES_256_CBC_SHA512               0xff65
#define OP_PCL_TLS_PVT_AES_256_CBC_SHA256               0xff66

#define OP_PCL_TLS_PVT_AES_192_CBC_SHA160               0xff90
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA384               0xff93
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA224               0xff94
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA512               0xff95
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA256               0xff96

#define OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FE             0xfffe
#define OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FF             0xffff

/* Blob protinfos */
#define OP_PCL_BLOB_TKEK_SHIFT       9
#define OP_PCL_BLOB_TKEK             (1 << OP_PCL_BLOB_TKEK_SHIFT)
#define OP_PCL_BLOB_EKT_SHIFT        8
#define OP_PCL_BLOB_EKT              (1 << OP_PCL_BLOB_EKT_SHIFT)
#define OP_PCL_BLOB_REG_SHIFT        4
#define OP_PCL_BLOB_REG_MASK         (0xF << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_MEMORY       (0x0 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_KEY1         (0x1 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_KEY2         (0x3 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_SBOX         (0x5 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_SPLIT        (0x7 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_PKE          (0x9 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_SEC_MEM_SHIFT    3
#define OP_PCL_BLOB_SEC_MEM          (1 << OP_PCL_BLOB_SEC_MEM_SHIFT)
#define OP_PCL_BLOB_BLACK            0x4
#define OP_PCL_BLOB_FORMAT_SHIFT     0
#define OP_PCL_BLOB_FORMAT_MASK      0x3
#define OP_PCL_BLOB_FORMAT_NORMAL    0
#define OP_PCL_BLOB_FORMAT_MASTER_VER  2
#define OP_PCL_BLOB_FORMAT_TEST      3

/* IKE / IKEv2 protinfos */
#define OP_PCL_IKE_HMAC_MD5          0x0100
#define OP_PCL_IKE_HMAC_SHA1         0x0200
#define OP_PCL_IKE_HMAC_AES128_CBC   0x0400
#define OP_PCL_IKE_HMAC_SHA256       0x0500
#define OP_PCL_IKE_HMAC_SHA384       0x0600
#define OP_PCL_IKE_HMAC_SHA512       0x0700
#define OP_PCL_IKE_HMAC_AES128_CMAC  0x0800

/* 802.16 WiMAX protinfos */
#define OP_PCL_WIMAX_NULL_OFDM       0x0001
#define OP_PCL_WIMAX_NULL_OFDMA      0x0031
#define OP_PCL_WIMAX_OFDM            0x0201
#define OP_PCL_WIMAX_OFDMA           0x0231

/* 802.11 WiFi protinfos */
#define OP_PCL_WIFI                  0xac04

/* MacSec protinfos */
#define OP_PCL_MACSEC                0x0001

/* 3G DCRC protinfos */
#define OP_PCL_3G_DCRC_CRC7          0x0710
#define OP_PCL_3G_DCRC_CRC11         0x0B10

/* 3G RLC protinfos */
#define OP_PCL_3G_RLC_NULL           0x0000
#define OP_PCL_3G_RLC_KASUMI         0x0001
#define OP_PCL_3G_RLC_SNOW           0x0002

/* LTE protinfos */
#define OP_PCL_LTE_NULL              0x0000
#define OP_PCL_LTE_SNOW              0x0001
#define OP_PCL_LTE_AES               0x0002

/* PKI unidirectional protocol protinfo bits */
#define OP_PCL_PKPROT_DSA_MSG        0x400
#define OP_PCL_PKPROT_HASH_SHIFT     7
#define OP_PCL_PKPROT_HASH_MASK      (7 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_MD5       (0 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA1      (1 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA224    (2 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA256    (3 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA384    (4 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA512    (5 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_EKT_Z          0x0040
#define OP_PCL_PKPROT_DECRYPT_Z      0x0020
#define OP_PCL_PKPROT_EKT_PRI        0x0010
#define OP_PCL_PKPROT_TEST           0x0008
#define OP_PCL_PKPROT_DECRYPT_PRI    0x0004
#define OP_PCL_PKPROT_ECC            0x0002
#define OP_PCL_PKPROT_F2M            0x0001

/* RSA Protinfo */
#define OP_PCL_RSAPROT_OP_MASK       3
#define OP_PCL_RSAPROT_OP_ENC_F_IN   0
#define OP_PCL_RSAPROT_OP_ENC_F_OUT  1
#define OP_PCL_RSAPROT_OP_DEC_ND     0
#define OP_PCL_RSAPROT_OP_DEC_PQD    1
#define OP_PCL_RSAPROT_OP_DEC_PQDPDQC   2
#define OP_PCL_RSAPROT_FFF_SHIFT     4
#define OP_PCL_RSAPROT_FFF_MASK      (7 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_RED       (0 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_ENC       (1 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_TK_ENC    (5 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_EKT       (3 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_TK_EKT    (7 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_PPP_SHIFT     8
#define OP_PCL_RSAPROT_PPP_MASK      (7 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_RED       (0 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_ENC       (1 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_TK_ENC    (5 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_EKT       (3 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_TK_EKT    (7 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_FMT_PKCSV15   0x1000

/* For non-protocol/alg-only op commands */
#define OP_ALG_TYPE_SHIFT            24
#define OP_ALG_TYPE_MASK             (0x7 << OP_ALG_TYPE_SHIFT)
#define OP_ALG_TYPE_CLASS1           2
#define OP_ALG_TYPE_CLASS2           4

#define OP_ALG_ALGSEL_SHIFT          16
#define OP_ALG_ALGSEL_MASK           (0xff << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SUBMASK        (0x0f << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_AES            (0x10 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_DES            (0x20 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_3DES           (0x21 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_ARC4           (0x30 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_MD5            (0x40 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA1           (0x41 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA224         (0x42 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA256         (0x43 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA384         (0x44 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA512         (0x45 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_RNG            (0x50 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SNOW           (0x60 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SNOW_F8        (0x60 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_KASUMI         (0x70 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_CRC            (0x90 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SNOW_F9        (0xA0 << OP_ALG_ALGSEL_SHIFT)

#define OP_ALG_AAI_SHIFT             4
#define OP_ALG_AAI_MASK              (0x1ff << OP_ALG_AAI_SHIFT)

/* blockcipher AAI set */
#define OP_ALG_AESA_MODE_MASK        (0xF0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AESA_CTR_MASK         (0x0F << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR               (0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD128        (0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD8          (0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD16         (0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD24         (0x03 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD32         (0x04 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD40         (0x05 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD48         (0x06 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD56         (0x07 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD64         (0x08 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD72         (0x09 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD80         (0x0a << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD88         (0x0b << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD96         (0x0c << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD104        (0x0d << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD112        (0x0e << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD120        (0x0f << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC               (0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_ECB               (0x20 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CFB               (0x30 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_OFB               (0x40 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_XTS               (0x50 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CMAC              (0x60 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_XCBC_MAC          (0x70 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CCM               (0x80 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_GCM               (0x90 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC_XCBCMAC       (0xa0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_XCBCMAC       (0xb0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC_CMAC          (0xC0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_CMAC_LTE      (0xD0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_CMAC          (0xE0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CHECKODD          (0x80 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DK                (0x100 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_C2K               (0x200 << OP_ALG_AAI_SHIFT)

/* randomizer AAI set */
#define OP_ALG_AAI_RNG               (0x000 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_NOZERO        (0x010 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_ODD           (0x020 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_PS            (0x040 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_AI            (0x080 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_SK            (0x100 << OP_ALG_AAI_SHIFT)

#define OP_ALG_AAI_RNG_SH_SHIFT      OP_ALG_AAI_SHIFT
#define OP_ALG_AAI_RNG_SH_MASK       (0x003 << OP_ALG_AAI_RNG_SH_SHIFT)
#define OP_ALG_AAI_RNG_SH0           (0x000 << OP_ALG_AAI_RNG_SH_SHIFT)
#define OP_ALG_AAI_RNG_SH1           (0x001 << OP_ALG_AAI_RNG_SH_SHIFT)

/* hmac/smac AAI set */
#define OP_ALG_AAI_HASH              (0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_HMAC              (0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_SMAC              (0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_HMAC_PRECOMP      (0x04 << OP_ALG_AAI_SHIFT)

/* CRC AAI set*/
#define OP_ALG_CRC_POLY_MASK         (0x07 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_IEEE802           (0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_IETF3385          (0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CUST_POLY         (0x04 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DIS               (0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DOS               (0x20 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DOC               (0x40 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_IVZ               (0x80 << OP_ALG_AAI_SHIFT)

/* Kasumi/SNOW AAI set */
#define OP_ALG_AAI_F8                (0xc0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_F9                (0xc8 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_GSM               (0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_EDGE              (0x20 << OP_ALG_AAI_SHIFT)

#define OP_ALG_AS_SHIFT              2
#define OP_ALG_AS_MASK               (0x3 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_UPDATE             (0 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_INIT               (1 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_FINALIZE           (2 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_INITFINAL          (3 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_RNG_GENERATE       (0 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_RNG_INSTANTIATE    (1 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_RNG_RESEED         (2 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_RNG_UNINSTATIATE   (3 << OP_ALG_AS_SHIFT)

#define OP_ALG_ICV_SHIFT             1
#define OP_ALG_ICV_MASK              (1 << OP_ALG_ICV_SHIFT)
#define OP_ALG_ICV_OFF               (0 << OP_ALG_ICV_SHIFT)
#define OP_ALG_ICV_ON                (1 << OP_ALG_ICV_SHIFT)
#define OP_ALG_RNG_PR_SHIFT          1
#define OP_ALG_RNG_PR_MASK           (1 << OP_ALG_RNG_PR_SHIFT)
#define OP_ALG_RNG_PR_OFF            (0 << OP_ALG_RNG_PR_SHIFT)
#define OP_ALG_RNG_PR_ON             (1 << OP_ALG_RNG_PR_SHIFT)

#define OP_ALG_DIR_SHIFT             0
#define OP_ALG_DIR_MASK              1
#define OP_ALG_DECRYPT               0
#define OP_ALG_ENCRYPT               1
#define OP_ALG_RNG_TST_SHIFT         0
#define OP_ALG_RNG_TST_MASK          1
#define OP_ALG_RNG_TST_OFF           0
#define OP_ALG_RNG_TST_ON            1

/* PKHA algorithm type set */
#define OP_ALG_PK                    0x00800000
#define OP_ALG_PK_FUN_MASK           0x3f /* clrmem, modmath, or cpymem */

/* PKHA mode clear memory definitions */
#define OP_ALG_PKMODE_A_RAM          0x80000
#define OP_ALG_PKMODE_B_RAM          0x40000
#define OP_ALG_PKMODE_E_RAM          0x20000
#define OP_ALG_PKMODE_N_RAM          0x10000
#define OP_ALG_PKMODE_RAM_SEG0       0x00040
#define OP_ALG_PKMODE_RAM_SEG1       0x00080
#define OP_ALG_PKMODE_RAM_SEG2       0x00100
#define OP_ALG_PKMODE_RAM_SEG3       0x00200
#define OP_ALG_PKMODE_CLEARMEM       0x00001

/* PKHA mode clear memory functions */
#define OP_ALG_PKMODE_CLEARMEM_ALL   0xF0001
#define OP_ALG_PKMODE_CLEARMEM_ABE   0xE0001
#define OP_ALG_PKMODE_CLEARMEM_ABN   0xD0001
#define OP_ALG_PKMODE_CLEARMEM_AB    0xC0001
#define OP_ALG_PKMODE_CLEARMEM_AEN   0xB0001
#define OP_ALG_PKMODE_CLEARMEM_AE    0xA0001
#define OP_ALG_PKMODE_CLEARMEM_AN    0x90001
#define OP_ALG_PKMODE_CLEARMEM_A     0x80001
#define OP_ALG_PKMODE_CLEARMEM_BEN   0x70001
#define OP_ALG_PKMODE_CLEARMEM_BE    0x60001
#define OP_ALG_PKMODE_CLEARMEM_BN    0x50001
#define OP_ALG_PKMODE_CLEARMEM_B     0x40001
#define OP_ALG_PKMODE_CLEARMEM_EN    0x30001
#define OP_ALG_PKMODE_CLEARMEM_N     0x10001
#define OP_ALG_PKMODE_CLEARMEM_E     0x20001

/* PKHA mode modular-arithmetic qualifying bits */
#define OP_ALG_PKMODE_MOD_IN_MONTY   0x80000
#define OP_ALG_PKMODE_MOD_OUT_MONTY  0x40000
#define OP_ALG_PKMODE_MOD_F2M        0x20000
#define OP_ALG_PKMODE_MOD_R2_IN      0x10000
#define OP_ALG_PKMODE_PRJECTV        0x00800
#define OP_ALG_PKMODE_TIME_EQ        0x400
#define OP_ALG_PKMODE_OUT_B          0x000
#define OP_ALG_PKMODE_OUT_A          0x100

/* PKHA mode modular-arithmetic integer functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_MOD_ADD         0x002
#define OP_ALG_PKMODE_MOD_SUB_1       0x003
#define OP_ALG_PKMODE_MOD_SUB_2       0x004
#define OP_ALG_PKMODE_MOD_MUL         0x005
#define OP_ALG_PKMODE_MOD_MUL_IM     (0x005 | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_MOD_MUL_IM_OM  (0x005 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY)
#define OP_ALG_PKMODE_MOD_EXP         0x006
#define OP_ALG_PKMODE_MOD_EXP_TEQ    (0x006 | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_MOD_EXP_IM     (0x006 | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_MOD_EXP_IM_TEQ (0x006 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_MOD_AMODN       0x007
#define OP_ALG_PKMODE_MOD_INV         0x008
#define OP_ALG_PKMODE_MOD_R2          0x00c
#define OP_ALG_PKMODE_MOD_RR          0x00d
#define OP_ALG_PKMODE_MOD_GCD         0x00e
#define OP_ALG_PKMODE_PRIME_TEST      0x00f

/* PKHA mode modular-arithmetic F2m functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_F2M_ADD        (0x002 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_MUL        (0x005 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_MUL_IM     (0x005 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_F2M_MUL_IM_OM  (0x005 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY)
#define OP_ALG_PKMODE_F2M_EXP        (0x006 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_EXP_TEQ    (0x006 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_F2M_AMODN      (0x007 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_INV        (0x008 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_R2         (0x00c | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_GCD        (0x00e | OP_ALG_PKMODE_MOD_F2M)

/* PKHA mode ECC Integer arithmetic functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_ECC_MOD_ADD    0x009
#define OP_ALG_PKMODE_ECC_MOD_ADD_IM_OM_PROJ \
				     (0x009 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_DBL    0x00a
#define OP_ALG_PKMODE_ECC_MOD_DBL_IM_OM_PROJ \
				     (0x00a | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					| OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_MUL    0x00b
#define OP_ALG_PKMODE_ECC_MOD_MUL_TEQ (0x00b | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2  (0x00b | OP_ALG_PKMODE_MOD_R2_IN)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV \
					    | OP_ALG_PKMODE_TIME_EQ)

/* PKHA mode ECC F2m arithmetic functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_ECC_F2M_ADD    (0x009 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_ADD_IM_OM_PROJ \
				     (0x009 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_DBL    (0x00a | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_DBL_IM_OM_PROJ \
				     (0x00a | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_MUL    (0x00b | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_MUL_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2 \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV \
					    | OP_ALG_PKMODE_TIME_EQ)

/* PKHA mode copy-memory definitions */
#define OP_ALG_PKMODE_SRC_REG_SHIFT     17
#define OP_ALG_PKMODE_SRC_REG_MASK      (7 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_SHIFT     10
#define OP_ALG_PKMODE_DST_REG_LSB_SHIFT 10
#define OP_ALG_PKMODE_DST_REG_MSB_SHIFT 16
#define OP_ALG_PKMODE_DST_REG_MASK       \
				     ((3 << OP_ALG_PKMODE_DST_REG_LSB_SHIFT) | \
				      (1 << OP_ALG_PKMODE_DST_REG_MSB_SHIFT))
#define OP_ALG_PKMODE_SRC_SEG_SHIFT  8
#define OP_ALG_PKMODE_SRC_SEG_MASK   (3 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_SHIFT  6
#define OP_ALG_PKMODE_DST_SEG_MASK   (3 << OP_ALG_PKMODE_DST_SEG_SHIFT)

#define OP_ALG_PKMODE_SRC_REG_A      (0 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_REG_B      (1 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_REG_N      (3 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_A      (0 << OP_ALG_PKMODE_DST_REG_LSB_SHIFT)
#define OP_ALG_PKMODE_DST_REG_B      (1 << OP_ALG_PKMODE_DST_REG_LSB_SHIFT)
#define OP_ALG_PKMODE_DST_REG_E      (2 << OP_ALG_PKMODE_DST_REG_LSB_SHIFT)
#define OP_ALG_PKMODE_DST_REG_N      (3 << OP_ALG_PKMODE_DST_REG_LSB_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_0      (0 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_1      (1 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_2      (2 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_3      (3 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_0      (0 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_1      (1 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_2      (2 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_3      (3 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_CPYMEM_N_SZ    0x10
#define OP_ALG_PKMODE_CPYMEM_SRC_SZ  0x11

/* PKHA mode copy-memory functions - amount based on N SIZE */
#define OP_ALG_PKMODE_COPY_NSZ          0x10
#define OP_ALG_PKMODE_COPY_NSZ_A0_B0    0x410
#define OP_ALG_PKMODE_COPY_NSZ_A0_B1    0x450
#define OP_ALG_PKMODE_COPY_NSZ_A0_B2    0x490
#define OP_ALG_PKMODE_COPY_NSZ_A0_B3    0x4d0

#define OP_ALG_PKMODE_COPY_NSZ_A1_B0    0x510
#define OP_ALG_PKMODE_COPY_NSZ_A1_B1    0x550
#define OP_ALG_PKMODE_COPY_NSZ_A1_B2    0x590
#define OP_ALG_PKMODE_COPY_NSZ_A1_B3    0x5d0

#define OP_ALG_PKMODE_COPY_NSZ_A2_B0    0x610
#define OP_ALG_PKMODE_COPY_NSZ_A2_B1    0x650
#define OP_ALG_PKMODE_COPY_NSZ_A2_B2    0x690
#define OP_ALG_PKMODE_COPY_NSZ_A2_B3    0x6d0

#define OP_ALG_PKMODE_COPY_NSZ_A3_B0    0x710
#define OP_ALG_PKMODE_COPY_NSZ_A3_B1    0x750
#define OP_ALG_PKMODE_COPY_NSZ_A3_B2    0x790
#define OP_ALG_PKMODE_COPY_NSZ_A3_B3    0x7d0

#define OP_ALG_PKMODE_COPY_NSZ_B0_A0    0x20010
#define OP_ALG_PKMODE_COPY_NSZ_B0_A1    0x20050
#define OP_ALG_PKMODE_COPY_NSZ_B0_A2    0x20090
#define OP_ALG_PKMODE_COPY_NSZ_B0_A3    0x200d0

#define OP_ALG_PKMODE_COPY_NSZ_B1_A0    0x20110
#define OP_ALG_PKMODE_COPY_NSZ_B1_A1    0x20150
#define OP_ALG_PKMODE_COPY_NSZ_B1_A2    0x20190
#define OP_ALG_PKMODE_COPY_NSZ_B1_A3    0x201d0

#define OP_ALG_PKMODE_COPY_NSZ_B2_A0    0x20210
#define OP_ALG_PKMODE_COPY_NSZ_B2_A1    0x20250
#define OP_ALG_PKMODE_COPY_NSZ_B2_A2    0x20290
#define OP_ALG_PKMODE_COPY_NSZ_B2_A3    0x202d0

#define OP_ALG_PKMODE_COPY_NSZ_B3_A0    0x20310
#define OP_ALG_PKMODE_COPY_NSZ_B3_A1    0x20350
#define OP_ALG_PKMODE_COPY_NSZ_B3_A2    0x20390
#define OP_ALG_PKMODE_COPY_NSZ_B3_A3    0x203d0

#define OP_ALG_PKMODE_COPY_NSZ_A_B      0x410
#define OP_ALG_PKMODE_COPY_NSZ_A_E      0x810
#define OP_ALG_PKMODE_COPY_NSZ_A_N      0xc10
#define OP_ALG_PKMODE_COPY_NSZ_B_A      0x20010
#define OP_ALG_PKMODE_COPY_NSZ_B_E      0x20810
#define OP_ALG_PKMODE_COPY_NSZ_B_N      0x20c10
#define OP_ALG_PKMODE_COPY_NSZ_N_A      0x60010
#define OP_ALG_PKMODE_COPY_NSZ_N_B      0x60410
#define OP_ALG_PKMODE_COPY_NSZ_N_E      0x60810

/* PKHA mode copy-memory functions - amount based on SRC SIZE */
#define OP_ALG_PKMODE_COPY_SSZ          0x11
#define OP_ALG_PKMODE_COPY_SSZ_A0_B0    0x411
#define OP_ALG_PKMODE_COPY_SSZ_A0_B1    0x451
#define OP_ALG_PKMODE_COPY_SSZ_A0_B2    0x491
#define OP_ALG_PKMODE_COPY_SSZ_A0_B3    0x4d1

#define OP_ALG_PKMODE_COPY_SSZ_A1_B0    0x511
#define OP_ALG_PKMODE_COPY_SSZ_A1_B1    0x551
#define OP_ALG_PKMODE_COPY_SSZ_A1_B2    0x591
#define OP_ALG_PKMODE_COPY_SSZ_A1_B3    0x5d1

#define OP_ALG_PKMODE_COPY_SSZ_A2_B0    0x611
#define OP_ALG_PKMODE_COPY_SSZ_A2_B1    0x651
#define OP_ALG_PKMODE_COPY_SSZ_A2_B2    0x691
#define OP_ALG_PKMODE_COPY_SSZ_A2_B3    0x6d1

#define OP_ALG_PKMODE_COPY_SSZ_A3_B0    0x711
#define OP_ALG_PKMODE_COPY_SSZ_A3_B1    0x751
#define OP_ALG_PKMODE_COPY_SSZ_A3_B2    0x791
#define OP_ALG_PKMODE_COPY_SSZ_A3_B3    0x7d1

#define OP_ALG_PKMODE_COPY_SSZ_B0_A0    0x20011
#define OP_ALG_PKMODE_COPY_SSZ_B0_A1    0x20051
#define OP_ALG_PKMODE_COPY_SSZ_B0_A2    0x20091
#define OP_ALG_PKMODE_COPY_SSZ_B0_A3    0x200d1

#define OP_ALG_PKMODE_COPY_SSZ_B1_A0    0x20111
#define OP_ALG_PKMODE_COPY_SSZ_B1_A1    0x20151
#define OP_ALG_PKMODE_COPY_SSZ_B1_A2    0x20191
#define OP_ALG_PKMODE_COPY_SSZ_B1_A3    0x201d1

#define OP_ALG_PKMODE_COPY_SSZ_B2_A0    0x20211
#define OP_ALG_PKMODE_COPY_SSZ_B2_A1    0x20251
#define OP_ALG_PKMODE_COPY_SSZ_B2_A2    0x20291
#define OP_ALG_PKMODE_COPY_SSZ_B2_A3    0x202d1

#define OP_ALG_PKMODE_COPY_SSZ_B3_A0    0x20311
#define OP_ALG_PKMODE_COPY_SSZ_B3_A1    0x20351
#define OP_ALG_PKMODE_COPY_SSZ_B3_A2    0x20391
#define OP_ALG_PKMODE_COPY_SSZ_B3_A3    0x203d1

#define OP_ALG_PKMODE_COPY_SSZ_A_B      0x411
#define OP_ALG_PKMODE_COPY_SSZ_A_E      0x811
#define OP_ALG_PKMODE_COPY_SSZ_A_N      0xc11
#define OP_ALG_PKMODE_COPY_SSZ_B_A      0x20011
#define OP_ALG_PKMODE_COPY_SSZ_B_E      0x20811
#define OP_ALG_PKMODE_COPY_SSZ_B_N      0x20c11
#define OP_ALG_PKMODE_COPY_SSZ_N_A      0x60011
#define OP_ALG_PKMODE_COPY_SSZ_N_B      0x60411
#define OP_ALG_PKMODE_COPY_SSZ_N_E      0x60811

/*
 * SEQ_IN_PTR Command Constructs
 */

/* Release Buffers */
#define SQIN_RBS                0x04000000

/* Sequence pointer is really a descriptor */
#define SQIN_INL                0x02000000

/* Sequence pointer is a scatter-gather table */
#define SQIN_SGF                0x01000000

/* Appends to a previous pointer */
#define SQIN_PRE                0x00800000

/* Use extended length following pointer */
#define SQIN_EXT                0x00400000

/* Restore sequence with pointer/length */
#define SQIN_RTO                0x00200000

/* Replace job descriptor */
#define SQIN_RJD                0x00100000

/* SEQ OUT PTR */
#define SQIN_SOP                0x00080000

#define SQIN_LEN_SHIFT          0
#define SQIN_LEN_MASK           (0xffff << SQIN_LEN_SHIFT)

/*
 * SEQ_OUT_PTR Command Constructs
 */

/* Sequence pointer is a scatter-gather table */
#define SQOUT_SGF               0x01000000

/* Appends to a previous pointer */
#define SQOUT_PRE               0x00800000

/* Restore sequence with pointer/length */
#define SQOUT_RTO               0x00200000
#define SQOUT_RTO_SHIFT         20
#define SQOUT_RTO_MASK          (0x3 << SQOUT_RTO_SHIFT)
#define SQOUT_RTO_REWIND        (2 << SQOUT_RTO_SHIFT)
#define SQOUT_RTO_REWIND_RESET  (3 << SQOUT_RTO_SHIFT)

/* Write safe */
#define SQOUT_EWS               0x00080000

/* Use extended length following pointer */
#define SQOUT_EXT               0x00400000

#define SQOUT_LEN_SHIFT         0
#define SQOUT_LEN_MASK          (0xffff << SQOUT_LEN_SHIFT)

/*
 * SIGNATURE Command Constructs
 */

/* TYPE field is all that's relevant */
#define SIGN_TYPE_SHIFT         16
#define SIGN_TYPE_MASK          (0x0f << SIGN_TYPE_SHIFT)

#define SIGN_TYPE_FINAL         (0x00 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_FINAL_RESTORE (0x01 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_FINAL_NONZERO (0x02 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_2         (0x0a << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_3         (0x0b << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_4         (0x0c << SIGN_TYPE_SHIFT)

/*
 * MOVE Command Constructs
 */

#define MOVE_AUX_SHIFT          25
#define MOVE_AUX_MASK           (3 << MOVE_AUX_SHIFT)
#define MOVE_AUX_MS             (2 << MOVE_AUX_SHIFT)
#define MOVE_AUX_LS             (1 << MOVE_AUX_SHIFT)

#define MOVE_WAITCOMP_SHIFT     24
#define MOVE_WAITCOMP_MASK      (1 << MOVE_WAITCOMP_SHIFT)
#define MOVE_WAITCOMP           (1 << MOVE_WAITCOMP_SHIFT)

#define MOVE_SRC_SHIFT          20
#define MOVE_SRC_MASK           (0x0f << MOVE_SRC_SHIFT)
#define MOVE_SRC_CLASS1CTX      (0x00 << MOVE_SRC_SHIFT)
#define MOVE_SRC_CLASS2CTX      (0x01 << MOVE_SRC_SHIFT)
#define MOVE_SRC_OUTFIFO        (0x02 << MOVE_SRC_SHIFT)
#define MOVE_SRC_DESCBUF        (0x03 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH0          (0x04 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH1          (0x05 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH2          (0x06 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH3          (0x07 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO         (0x08 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO_CL      (0x09 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO_NO_NFIFO (0x0a << MOVE_SRC_SHIFT)

#define MOVE_DEST_SHIFT         16
#define MOVE_DEST_MASK          (0x0f << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1CTX     (0x00 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2CTX     (0x01 << MOVE_DEST_SHIFT)
#define MOVE_DEST_OUTFIFO       (0x02 << MOVE_DEST_SHIFT)
#define MOVE_DEST_DESCBUF       (0x03 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH0         (0x04 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH1         (0x05 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH2         (0x06 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH3         (0x07 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1INFIFO  (0x08 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2INFIFO  (0x09 << MOVE_DEST_SHIFT)
#define MOVE_DEST_INFIFO        (0x0a << MOVE_DEST_SHIFT)
#define MOVE_DEST_PK_A          (0x0c << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1KEY     (0x0d << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2KEY     (0x0e << MOVE_DEST_SHIFT)
#define MOVE_DEST_ALTSOURCE     (0x0f << MOVE_DEST_SHIFT)

#define MOVE_OFFSET_SHIFT       8
#define MOVE_OFFSET_MASK        (0xff << MOVE_OFFSET_SHIFT)

#define MOVE_LEN_SHIFT          0
#define MOVE_LEN_MASK           (0xff << MOVE_LEN_SHIFT)

#define MOVELEN_MRSEL_SHIFT     0
#define MOVELEN_MRSEL_MASK      (0x3 << MOVE_LEN_SHIFT)
#define MOVELEN_MRSEL_MATH0     (0 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH1     (1 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH2     (2 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH3     (3 << MOVELEN_MRSEL_SHIFT)

/*
 * MATH Command Constructs
 */

#define MATH_IFB_SHIFT          26
#define MATH_IFB_MASK           (1 << MATH_IFB_SHIFT)
#define MATH_IFB                (1 << MATH_IFB_SHIFT)

#define MATH_NFU_SHIFT          25
#define MATH_NFU_MASK           (1 << MATH_NFU_SHIFT)
#define MATH_NFU                (1 << MATH_NFU_SHIFT)

#define MATH_STL_SHIFT          24
#define MATH_STL_MASK           (1 << MATH_STL_SHIFT)
#define MATH_STL                (1 << MATH_STL_SHIFT)

/* Function selectors */
#define MATH_FUN_SHIFT          20
#define MATH_FUN_MASK           (0x0f << MATH_FUN_SHIFT)
#define MATH_FUN_ADD            (0x00 << MATH_FUN_SHIFT)
#define MATH_FUN_ADDC           (0x01 << MATH_FUN_SHIFT)
#define MATH_FUN_SUB            (0x02 << MATH_FUN_SHIFT)
#define MATH_FUN_SUBB           (0x03 << MATH_FUN_SHIFT)
#define MATH_FUN_OR             (0x04 << MATH_FUN_SHIFT)
#define MATH_FUN_AND            (0x05 << MATH_FUN_SHIFT)
#define MATH_FUN_XOR            (0x06 << MATH_FUN_SHIFT)
#define MATH_FUN_LSHIFT         (0x07 << MATH_FUN_SHIFT)
#define MATH_FUN_RSHIFT         (0x08 << MATH_FUN_SHIFT)
#define MATH_FUN_SHLD           (0x09 << MATH_FUN_SHIFT)
#define MATH_FUN_ZBYT           (0x0A << MATH_FUN_SHIFT)
#define MATH_FUN_BYTE_SWAP      (0x0B << MATH_FUN_SHIFT)

/* Source 0 selectors */
#define MATH_SRC0_SHIFT         16
#define MATH_SRC0_MASK          (0x0f << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG0          (0x00 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG1          (0x01 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG2          (0x02 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG3          (0x03 << MATH_SRC0_SHIFT)
#define MATH_SRC0_IMM           (0x04 << MATH_SRC0_SHIFT)
#define MATH_SRC0_PROT          (0x07 << MATH_SRC0_SHIFT)
#define MATH_SRC0_SEQINLEN      (0x08 << MATH_SRC0_SHIFT)
#define MATH_SRC0_SEQOUTLEN     (0x09 << MATH_SRC0_SHIFT)
#define MATH_SRC0_VARSEQINLEN   (0x0a << MATH_SRC0_SHIFT)
#define MATH_SRC0_VARSEQOUTLEN  (0x0b << MATH_SRC0_SHIFT)
#define MATH_SRC0_ZERO          (0x0c << MATH_SRC0_SHIFT)
#define MATH_SRC0_ONE           (0x0f << MATH_SRC0_SHIFT)

/* Source 1 selectors */
#define MATH_SRC1_SHIFT         12
#define MATH_SRC1_MASK          (0x0f << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG0          (0x00 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG1          (0x01 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG2          (0x02 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG3          (0x03 << MATH_SRC1_SHIFT)
#define MATH_SRC1_IMM           (0x04 << MATH_SRC1_SHIFT)
#define MATH_SRC1_PROT          (0x07 << MATH_SRC1_SHIFT)
#define MATH_SRC1_VARSEQINLEN   (0x08 << MATH_SRC1_SHIFT)
#define MATH_SRC1_VARSEQOUTLEN  (0x09 << MATH_SRC1_SHIFT)
#define MATH_SRC1_INFIFO        (0x0a << MATH_SRC1_SHIFT)
#define MATH_SRC1_OUTFIFO       (0x0b << MATH_SRC1_SHIFT)
#define MATH_SRC1_ONE           (0x0c << MATH_SRC1_SHIFT)
#define MATH_SRC1_JOBSOURCE     (0x0d << MATH_SRC1_SHIFT)
#define MATH_SRC1_ZERO          (0x0f << MATH_SRC1_SHIFT)

/* Destination selectors */
#define MATH_DEST_SHIFT         8
#define MATH_DEST_MASK          (0x0f << MATH_DEST_SHIFT)
#define MATH_DEST_REG0          (0x00 << MATH_DEST_SHIFT)
#define MATH_DEST_REG1          (0x01 << MATH_DEST_SHIFT)
#define MATH_DEST_REG2          (0x02 << MATH_DEST_SHIFT)
#define MATH_DEST_REG3          (0x03 << MATH_DEST_SHIFT)
#define MATH_DEST_PROT          (0x07 << MATH_DEST_SHIFT)
#define MATH_DEST_SEQINLEN      (0x08 << MATH_DEST_SHIFT)
#define MATH_DEST_SEQOUTLEN     (0x09 << MATH_DEST_SHIFT)
#define MATH_DEST_VARSEQINLEN   (0x0a << MATH_DEST_SHIFT)
#define MATH_DEST_VARSEQOUTLEN  (0x0b << MATH_DEST_SHIFT)
#define MATH_DEST_NONE          (0x0f << MATH_DEST_SHIFT)

/* Length selectors */
#define MATH_LEN_SHIFT          0
#define MATH_LEN_MASK           (0x0f << MATH_LEN_SHIFT)
#define MATH_LEN_1BYTE          0x01
#define MATH_LEN_2BYTE          0x02
#define MATH_LEN_4BYTE          0x04
#define MATH_LEN_8BYTE          0x08

/*
 * JUMP Command Constructs
 */

#define JUMP_CLASS_SHIFT        25
#define JUMP_CLASS_MASK         (3 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_NONE         0
#define JUMP_CLASS_CLASS1       (1 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_CLASS2       (2 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_BOTH         (3 << JUMP_CLASS_SHIFT)

#define JUMP_JSL_SHIFT          24
#define JUMP_JSL_MASK           (1 << JUMP_JSL_SHIFT)
#define JUMP_JSL                (1 << JUMP_JSL_SHIFT)

#define JUMP_TYPE_SHIFT         21
#define JUMP_TYPE_MASK          (0x07 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_LOCAL         (0x00 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_GOSUB         (0x01 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_NONLOCAL      (0x02 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_RETURN        (0x03 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_HALT          (0x04 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_HALT_USER     (0x06 << JUMP_TYPE_SHIFT)

#define JUMP_TEST_SHIFT         16
#define JUMP_TEST_MASK          (0x03 << JUMP_TEST_SHIFT)
#define JUMP_TEST_ALL           (0x00 << JUMP_TEST_SHIFT)
#define JUMP_TEST_INVALL        (0x01 << JUMP_TEST_SHIFT)
#define JUMP_TEST_ANY           (0x02 << JUMP_TEST_SHIFT)
#define JUMP_TEST_INVANY        (0x03 << JUMP_TEST_SHIFT)

/* Condition codes. JSL bit is factored in */
#define JUMP_COND_SHIFT         8
#define JUMP_COND_MASK          (0x100ff << JUMP_COND_SHIFT)
/* JSL=0 bits */
#define JUMP_COND_PK_0          (0x80 << JUMP_COND_SHIFT)
#define JUMP_COND_PK_GCD_1      (0x40 << JUMP_COND_SHIFT)
#define JUMP_COND_PK_PRIME      (0x20 << JUMP_COND_SHIFT)
#define JUMP_COND_MATH_N        (0x08 << JUMP_COND_SHIFT)
#define JUMP_COND_MATH_Z        (0x04 << JUMP_COND_SHIFT)
#define JUMP_COND_MATH_C        (0x02 << JUMP_COND_SHIFT)
#define JUMP_COND_MATH_NV       (0x01 << JUMP_COND_SHIFT)
/* JSL=01 bits */
#define JUMP_COND_JQP           ((0x80 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_SHRD          ((0x40 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_SELF          ((0x20 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_CALM          ((0x10 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_NIP           ((0x08 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_NIFP          ((0x04 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_NOP           ((0x02 << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_NCP           ((0x01 << JUMP_COND_SHIFT) | JUMP_JSL)

#define JUMP_OFFSET_SHIFT       0
#define JUMP_OFFSET_MASK        (0xff << JUMP_OFFSET_SHIFT)

/*
 * IFIFO ENTRY
 * Data Constructs
 *
 */
#define IFIFOENTRY_DEST_SHIFT        30
#define IFIFOENTRY_DEST_MASK         (3 << IFIFOENTRY_DEST_SHIFT)
#define IFIFOENTRY_DEST_DECO         (0 << IFIFOENTRY_DEST_SHIFT)
#define IFIFOENTRY_DEST_CLASS1       (1 << IFIFOENTRY_DEST_SHIFT)
#define IFIFOENTRY_DEST_CLASS2       (2 << IFIFOENTRY_DEST_SHIFT)
#define IFIFOENTRY_DEST_BOTH         (3 << IFIFOENTRY_DEST_SHIFT)

#define IFIFOENTRY_LC2_SHIFT         29
#define IFIFOENTRY_LC2_MASK          (1 << IFIFOENTRY_LC2_SHIFT)
#define IFIFOENTRY_LC2               (1 << IFIFOENTRY_LC2_SHIFT)

#define IFIFOENTRY_LC1_SHIFT         28
#define IFIFOENTRY_LC1_MASK          (1 << IFIFOENTRY_LC1_SHIFT)
#define IFIFOENTRY_LC1               (1 << IFIFOENTRY_LC1_SHIFT)

#define IFIFOENTRY_FC2_SHIFT         27
#define IFIFOENTRY_FC2_MASK          (1 << IFIFOENTRY_FC2_SHIFT)
#define IFIFOENTRY_FC2               (1 << IFIFOENTRY_FC2_SHIFT)

#define IFIFOENTRY_FC1_SHIFT         26
#define IFIFOENTRY_FC1_MASK          (1 << IFIFOENTRY_FC1_SHIFT)
#define IFIFOENTRY_FC1               (1 << IFIFOENTRY_FC1_SHIFT)

/* Treat this STYPE and AST as one field for encoding/decoding STYPE */
#define IFIFOENTRY_STYPE_SHIFT       24
#define IFIFOENTRY_STYPE_MASK        ((3 << IFIFOENTRY_STYPE_SHIFT) \
					  | IFIFOENTRY_AST_MASK)
#define IFIFOENTRY_STYPE_DFIFO       (0 << IFIFOENTRY_STYPE_SHIFT)
#define IFIFOENTRY_STYPE_OFIFO       (1 << IFIFOENTRY_STYPE_SHIFT)
#define IFIFOENTRY_STYPE_PAD         (2 << IFIFOENTRY_STYPE_SHIFT)
#define IFIFOENTRY_STYPE_SNOOP       (3 << IFIFOENTRY_STYPE_SHIFT)
#define IFIFOENTRY_STYPE_ALTSOURCE   ((0 << IFIFOENTRY_STYPE_SHIFT) \
					  | IFIFOENTRY_AST)

#define IFIFOENTRY_DTYPE_SHIFT       20
#define IFIFOENTRY_DTYPE_MASK        (0xF << IFIFOENTRY_DTYPE_SHIFT)

#define IFIFOENTRY_DTYPE_SBOX        (0x0  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_AAD         (0x1  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_IV          (0x2  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_SAD         (0x3  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_ICV         (0xA  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_SKIP        (0xE  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_MSG         (0xF  << IFIFOENTRY_DTYPE_SHIFT)

#define IFIFOENTRY_DTYPE_PK_A0       (0x0  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_A1       (0x1  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_A2       (0x2  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_A3       (0x3  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_B0       (0x4  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_B1       (0x5  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_B2       (0x6  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_B3       (0x7  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_N        (0x8  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_E        (0x9  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_A        (0xC  << IFIFOENTRY_DTYPE_SHIFT)
#define IFIFOENTRY_DTYPE_PK_B        (0xD  << IFIFOENTRY_DTYPE_SHIFT)

#define IFIFOENTRY_BND_SHIFT         19
#define IFIFOENTRY_BND_MASK          (1 << IFIFOENTRY_BND_SHIFT)
#define IFIFOENTRY_BND               (1 << IFIFOENTRY_BND_SHIFT)

#define IFIFOENTRY_PTYPE_SHIFT       16
#define IFIFOENTRY_PTYPE_MASK        (0x7 << IFIFOENTRY_PTYPE_SHIFT)

#define IFIFOENTRY_PTYPE_ZEROS       (0x0  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_RND_NOZEROS (0x1  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_INCREMENT   (0x2  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_RND         (0x3  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_ZEROS_NZ    (0x4  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_RND_NZ_LZ   (0x5  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_N           (0x6  << IFIFOENTRY_PTYPE_SHIFT)
#define IFIFOENTRY_PTYPE_RND_NZ_N    (0x7  << IFIFOENTRY_PTYPE_SHIFT)

#define IFIFOENTRY_OC_SHIFT          15
#define IFIFOENTRY_OC_MASK           (1 << IFIFOENTRY_OC_SHIFT)
#define IFIFOENTRY_OC                (1 << IFIFOENTRY_OC_SHIFT)

#define IFIFOENTRY_AST_SHIFT         14
#define IFIFOENTRY_AST_MASK          (1 << IFIFOENTRY_OC_SHIFT)
#define IFIFOENTRY_AST               (1 << IFIFOENTRY_OC_SHIFT)

#define IFIFOENTRY_BM_SHIFT          11
#define IFIFOENTRY_BM_MASK           (1 << IFIFOENTRY_BM_SHIFT)
#define IFIFOENTRY_BM                (1 << IFIFOENTRY_BM_SHIFT)

#define IFIFOENTRY_PS_SHIFT          10
#define IFIFOENTRY_PS_MASK           (1 << IFIFOENTRY_PS_SHIFT)
#define IFIFOENTRY_PS                (1 << IFIFOENTRY_PS_SHIFT)

#define IFIFOENTRY_DLEN_SHIFT        0
#define IFIFOENTRY_DLEN_MASK         (0xFFF << IFIFOENTRY_DLEN_SHIFT)

#define IFIFOENTRY_PLEN_SHIFT        0
#define IFIFOENTRY_PLEN_MASK         (0xFF << IFIFOENTRY_PLEN_SHIFT)

/*
 * PDB internal definitions
 */

/* IPSec ESP CBC Encap/Decap Options */
#define PDBOPTS_ESPCBC_ARSNONE     0x00 /* no antireplay window              */
#define PDBOPTS_ESPCBC_ARS32       0x40 /* 32-entry antireplay window        */
#define PDBOPTS_ESPCBC_ARS64       0xc0 /* 64-entry antireplay window        */
#define PDBOPTS_ESPCBC_CKSUM       0x80 /* Enable Checksum Update            */
#define PDBOPTS_ESPCBC_DSC         0x40 /* Copy the DiffServ                 */
#define PDBOPTS_ESPCBC_IVSRC       0x20 /* IV comes from internal random gen */
#define PDBOPTS_ESPCBC_ESN         0x10 /* extended sequence included        */
#define PDBOPTS_ESPCBC_OUTFMT      0x08 /* output only decapsulation (decap) */
#define PDBOPTS_ESPCBC_IPHDRSRC    0x08 /* IP header comes from PDB (encap)  */
#define PDBOPTS_ESPCBC_INCIPHDR    0x04 /* Prepend IP header to output frame */
#define PDBOPTS_ESPCBC_IPVSN       0x02 /* process IPv6 header               */
#define PDBOPTS_ESPCBC_TUNNEL      0x01 /* tunnel mode next-header byte      */

/* The L / N size word of (EC)Diffie-Hellman PDB */
#define DH_PDB_L_SHIFT               7
#define DH_PDB_L_MASK                (0x3FF << DH_PDB_L_SHIFT)
#define DH_PDB_N_SHIFT               0
#define DH_PDB_N_MASK                (0x3F << DH_PDB_N_SHIFT)

/* S/G bits of First word of RSA Encrypt PDB */
#define RSA_PDB_ENC_SGF_F            0x80000000
#define RSA_PDB_ENC_SGF_G            0x40000000
#define RSA_PDB_ENC_SGF_N            0x20000000
#define RSA_PDB_ENC_SGF_E            0x10000000

/* S/G bits of First word of RSA Decrypt PDB (private key form 1) */
#define RSA_PDB_DEC_PRV1_SGF_G       0x80000000
#define RSA_PDB_DEC_PRV1_SGF_F       0x40000000
#define RSA_PDB_DEC_PRV1_SGF_N       0x20000000
#define RSA_PDB_DEC_PRV1_SGF_D       0x10000000

/* S/G bits of First word of RSA Decrypt PDB (private key form 2) */
#define RSA_PDB_DEC_PRV2_SGF_G       0x80000000
#define RSA_PDB_DEC_PRV2_SGF_F       0x40000000
#define RSA_PDB_DEC_PRV2_SGF_D       0x20000000
#define RSA_PDB_DEC_PRV2_SGF_P       0x10000000
#define RSA_PDB_DEC_PRV2_SGF_Q       0x08000000
#define RSA_PDB_DEC_PRV2_SGF_T1      0x04000000
#define RSA_PDB_DEC_PRV2_SGF_T2      0x02000000

/* S/G bits of First word RSA Decrypt PDB (private key form 3) */
#define RSA_PDB_DEC_PRV3_SGF_G       0x80000000
#define RSA_PDB_DEC_PRV3_SGF_F       0x40000000
#define RSA_PDB_DEC_PRV3_SGF_C       0x20000000
#define RSA_PDB_DEC_PRV3_SGF_P       0x10000000
#define RSA_PDB_DEC_PRV3_SGF_Q       0x08000000
#define RSA_PDB_DEC_PRV3_SGF_DP      0x04000000
#define RSA_PDB_DEC_PRV3_SGF_DQ      0x02000000
#define RSA_PDB_DEC_PRV3_SGF_T1      0x01000000
#define RSA_PDB_DEC_PRV3_SGF_T2      0x00800000

/* Size fields of First / last words of RSA PDBs */
#define RSA_PDB_E_SHIFT              12
#define RSA_PDB_E_MASK               (0xFFF << RSA_PDB_E_SHIFT)
#define RSA_PDB_D_SHIFT              12
#define RSA_PDB_D_MASK               (0xFFF << RSA_PDB_D_SHIFT)
#define RSA_PDB_N_SHIFT              0
#define RSA_PDB_N_MASK               (0xFFF << RSA_PDB_N_SHIFT)
#define RSA_PDB_Q_SHIFT              12
#define RSA_PDB_Q_MASK               (0xFFF << RSA_PDB_Q_SHIFT)
#define RSA_PDB_P_SHIFT              0
#define RSA_PDB_P_MASK               (0xFFF << RSA_PDB_P_SHIFT)
#define RSA_PDB_F_SHIFT              0
#define RSA_PDB_F_MASK               (0xFFF << RSA_PDB_F_SHIFT)

/* ARS PDB */
#define ARS_PDB_PN_CHANGED           0x80000000
#define ARS_PDB_LATE_ERROR           0x40000000
#define ARS_PDB_REPLAY_ERROR         0x20000000
#define ARS_PDB_XFLOW_ERROR          0x10000000
#define ARS_PDB_AR_LEN_SHIFT         8
#define ARS_PDB_AR_LEN_MASK          0x00007F00
#define ARS_PDB_PN_LEN_SHIFT         4
#define ARS_PDB_PN_LEN_MASK          0x00000030
#define ARS_PDB_CHECK_UNDER          0x00000008
#define ARS_PDB_CHECK_OVER           0x00000004
#define ARS_PDB_NO_FLOW_ERROR        0x00000002
#define ARS_PDB_NO_LATE_ERROR        0x00000001

#endif	/* DESC_H */

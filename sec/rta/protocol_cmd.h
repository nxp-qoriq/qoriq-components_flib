#ifndef __RTA_PROTOCOL_CMD_H__
#define __RTA_PROTOCOL_CMD_H__

static int32_t ssl_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_TLS_RSA_EXPORT_WITH_RC4_40_MD5:
	case OP_PCL_TLS_RSA_WITH_RC4_128_MD5:
	case OP_PCL_TLS_RSA_WITH_RC4_128_SHA:
	case OP_PCL_TLS_RSA_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_RSA_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DH_DSS_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_DH_DSS_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DH_RSA_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_DH_RSA_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_DHE_DSS_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_DHE_RSA_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DH_ANON_EXPORT_WITH_RC4_40_MD5:
	case OP_PCL_TLS_DH_ANON_WITH_RC4_128_MD5:
	case OP_PCL_TLS_DH_ANON_EXPORT_WITH_DES40_CBC_SHA:
	case OP_PCL_TLS_DH_ANON_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_DH_ANON_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_KRB5_WITH_DES_CBC_SHA:
	case OP_PCL_TLS_KRB5_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_KRB5_WITH_RC4_128_SHA:
	case OP_PCL_TLS_KRB5_WITH_DES_CBC_MD5:
	case OP_PCL_TLS_KRB5_WITH_3DES_EDE_CBC_MD5:
	case OP_PCL_TLS_KRB5_WITH_RC4_128_MD5:
	case OP_PCL_TLS_KRB5_EXPORT_WITH_DES_CBC_40_SHA:
	case OP_PCL_TLS_KRB5_EXPORT_WITH_RC4_40_SHA:
	case OP_PCL_TLS_KRB5_EXPORT_WITH_DES_CBC_40_MD5:
	case OP_PCL_TLS_KRB5_EXPORT_WITH_RC4_40_MD5:
	case OP_PCL_TLS_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DH_DSS_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DH_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DH_ANON_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DH_DSS_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DH_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DH_ANON_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_RSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_RSA_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_DH_DSS_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DH_RSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DH_DSS_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_DH_RSA_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_DH_ANON_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DH_ANON_WITH_AES_256_CBC_SHA256:
	case OP_PCL_TLS_PSK_WITH_RC4_128_SHA:
	case OP_PCL_TLS_PSK_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_PSK_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_PSK_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_DHE_PSK_WITH_RC4_128_SHA:
	case OP_PCL_TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_RSA_PSK_WITH_RC4_128_SHA:
	case OP_PCL_TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_RSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_RSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DH_RSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DH_RSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DHE_DSS_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DH_DSS_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DH_DSS_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DH_ANON_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DH_ANON_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_PSK_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_PSK_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_PSK_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_PSK_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DHE_PSK_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_RSA_PSK_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDH_RSA_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDHE_RSA_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDH_ANON_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDH_ANON_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDH_ANON_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDH_ANON_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_RSA_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_DSS_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_RSA_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_DSS_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_RSA_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_SRP_SHA_DSS_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDHE_PSK_WITH_RC4_128_SHA:
	case OP_PCL_TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_MD5:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA160:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA384:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA224:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA512:
	case OP_PCL_TLS_PVT_3DES_EDE_CBC_SHA256:
	case OP_PCL_TLS_PVT_AES_128_CBC_SHA160:
	case OP_PCL_TLS_PVT_AES_128_CBC_SHA384:
	case OP_PCL_TLS_PVT_AES_128_CBC_SHA224:
	case OP_PCL_TLS_PVT_AES_128_CBC_SHA512:
	case OP_PCL_TLS_PVT_AES_128_CBC_SHA256:
	case OP_PCL_TLS_PVT_AES_256_CBC_SHA160:
	case OP_PCL_TLS_PVT_AES_256_CBC_SHA384:
	case OP_PCL_TLS_PVT_AES_256_CBC_SHA224:
	case OP_PCL_TLS_PVT_AES_256_CBC_SHA512:
	case OP_PCL_TLS_PVT_AES_256_CBC_SHA256:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA160:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA384:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA224:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA512:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA256:
	case OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FE:
	case OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FF:
		return 0;
	}
	return -1;
}

static int32_t ike_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_IKE_HMAC_MD5:
	case OP_PCL_IKE_HMAC_SHA1:
	case OP_PCL_IKE_HMAC_AES128_CBC:
	case OP_PCL_IKE_HMAC_SHA256:
	case OP_PCL_IKE_HMAC_SHA384:
	case OP_PCL_IKE_HMAC_SHA512:
	case OP_PCL_IKE_HMAC_AES128_CMAC:
		return 0;
	}
	return -1;
}

static int32_t ipsec_proto(uint16_t protoinfo)
{
	uint16_t proto_cls1 = protoinfo & 0xff00;
	uint16_t proto_cls2 = protoinfo & 0x00ff;

	switch (proto_cls1) {
	case OP_PCL_IPSEC_AES_CCM8:
	case OP_PCL_IPSEC_AES_CCM12:
	case OP_PCL_IPSEC_AES_CCM16:
	case OP_PCL_IPSEC_AES_GCM8:
	case OP_PCL_IPSEC_AES_GCM12:
		if (proto_cls2 == OP_PCL_IPSEC_HMAC_NULL)
			return 0;
	case OP_PCL_IPSEC_DES_IV64:
	case OP_PCL_IPSEC_DES:
	case OP_PCL_IPSEC_3DES:
	case OP_PCL_IPSEC_NULL:
	case OP_PCL_IPSEC_AES_CBC:
	case OP_PCL_IPSEC_AES_NULL_WITH_GMAC:
		switch (proto_cls2) {
		case OP_PCL_IPSEC_HMAC_MD5_96:
		case OP_PCL_IPSEC_HMAC_SHA1_96:
		case OP_PCL_IPSEC_AES_XCBC_MAC_96:
		case OP_PCL_IPSEC_HMAC_MD5_128:
		case OP_PCL_IPSEC_HMAC_SHA1_160:
		case OP_PCL_IPSEC_AES_CMAC_96:
		case OP_PCL_IPSEC_HMAC_SHA2_256_128:
		case OP_PCL_IPSEC_HMAC_SHA2_384_192:
		case OP_PCL_IPSEC_HMAC_SHA2_512_256:
			return 0;
		}

	}
	return -1;
}

struct proto_map {
	uint32_t optype;
	uint32_t protid;
	int32_t (*protoinfo_func)(uint16_t);
};

static const struct proto_map proto_table[29] = {
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_SSL30_PRF,	  ssl_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS10_PRF,	  ssl_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS11_PRF,	  ssl_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS12_PRF,	  ssl_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DTLS10_PRF,	  ssl_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_IKEV1_PRF,	  ike_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_IKEV2_PRF,	  ike_proto },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_PUBLICKEYPAIR, NULL },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DSASIGN,	  NULL },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DSAVERIFY,	  NULL },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DIFFIEHELLMAN, NULL },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_RSADECRYPT,	  NULL },
	{ OP_TYPE_UNI_PROTOCOL,   OP_PCLID_RSAENCRYPT,	  NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_IPSEC,         ipsec_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_SRTP,	  ipsec_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_SSL30,	  ssl_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS10,	  ssl_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS11,	  ssl_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS12,	  ssl_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_DTLS10,	  ssl_proto },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_MACSEC,        NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_WIFI,          NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_WIMAX,         NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_DCRC,       NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_RLC_PDU,    NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_RLC_SDU,    NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_LTE_PDCP_USER, NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_LTE_PDCP_CTRL, NULL },
	{ OP_TYPE_DECAP_PROTOCOL, OP_PCLID_BLOB,          NULL }
};

static inline uint32_t proto_operation(struct program *program, uint32_t optype,
				       uint32_t protid, uint16_t protoinfo)
{
	uint32_t opcode = CMD_OPERATION;
	uint8_t i, found = 0;

	for (i = 0; i < sizeof(proto_table); i++) {
		/* clear last bit in optype to match also decap proto */
		optype &= ~(1 << OP_TYPE_SHIFT);
		if (optype == proto_table[i].optype) {
			if (proto_table[i].protid == protid) {
				/* nothig else to verify */
				if (proto_table[i].protoinfo_func == NULL) {
					found = 1;
					break;
				}
				/* check protoinfo */
				if (-1 == (*proto_table[i].protoinfo_func)
						(protoinfo)) {
					pr_debug("PROTO_DESC: Bad PROTO Type. "
						      "SEC Program Line: %d\n",
						      program->current_pc);
					goto err;
				}
				found = 1;
				break;
			}
		}
	}
	if (!found) {
		pr_debug("PROTO_DESC: Operation Type Mismatch. "
				"SEC Program Line: %d\n", program->current_pc);
		goto err;
	}

	program->buffer[program->current_pc] = opcode | optype | protid
						      | protoinfo;
	program->current_instraction++;
	return program->current_pc++;
 err:
	program->first_error_pc = program->current_pc;
	program->current_instraction++;
	return program->current_pc++;
}

#endif /* __RTA_PROTOCOL_CMD_H__ */

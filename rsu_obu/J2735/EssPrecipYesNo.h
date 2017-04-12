/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "NTCIP"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_EssPrecipYesNo_H_
#define	_EssPrecipYesNo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EssPrecipYesNo {
	EssPrecipYesNo_precip	= 1,
	EssPrecipYesNo_noPrecip	= 2,
	EssPrecipYesNo_error	= 3
} e_EssPrecipYesNo;

/* EssPrecipYesNo */
typedef long	 EssPrecipYesNo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EssPrecipYesNo;
asn_struct_free_f EssPrecipYesNo_free;
asn_struct_print_f EssPrecipYesNo_print;
asn_constr_check_f EssPrecipYesNo_constraint;
ber_type_decoder_f EssPrecipYesNo_decode_ber;
der_type_encoder_f EssPrecipYesNo_encode_der;
xer_type_decoder_f EssPrecipYesNo_decode_xer;
xer_type_encoder_f EssPrecipYesNo_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _EssPrecipYesNo_H_ */
#include <asn_internal.h>

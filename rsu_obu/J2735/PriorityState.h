/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_PriorityState_H_
#define	_PriorityState_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PriorityState {
	PriorityState_noneActive	= 0,
	PriorityState_none	= 1,
	PriorityState_requested	= 2,
	PriorityState_active	= 3,
	PriorityState_activeButIhibitd	= 4,
	PriorityState_seccess	= 5,
	PriorityState_removed	= 6,
	PriorityState_clearFail	= 7,
	PriorityState_detectFail	= 8,
	PriorityState_detectClear	= 9,
	PriorityState_abort	= 10,
	PriorityState_delayTiming	= 11,
	PriorityState_extendTiming	= 12,
	PriorityState_preemptOverride	= 13,
	PriorityState_adaptiveOverride	= 14,
	PriorityState_reserved	= 15
	/*
	 * Enumeration is extensible
	 */
} e_PriorityState;

/* PriorityState */
typedef long	 PriorityState_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PriorityState;
asn_struct_free_f PriorityState_free;
asn_struct_print_f PriorityState_print;
asn_constr_check_f PriorityState_constraint;
ber_type_decoder_f PriorityState_decode_ber;
der_type_encoder_f PriorityState_encode_der;
xer_type_decoder_f PriorityState_decode_xer;
xer_type_encoder_f PriorityState_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _PriorityState_H_ */
#include <asn_internal.h>
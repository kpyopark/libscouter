/*
 * scouter_types.h
 *
 *  Created on: 2015. 8. 11.
 *      Author: LowFormat
 */

#ifndef SCOUTER_TYPES_H_
#define SCOUTER_TYPES_H_

#include <stdint.h>

// ----------------------- BASIC CONSTANTS ------------------//

// ----------------------- LIMIT ----------------------------//
#define PACK_OBJ_NAME_LENGTH_MAX 		200
#define PACK_OBJ_TYPE_LENGTH_MAX 		20
#define MAP_KEY_STR_LENGTH_MAX 			50
#define PACK_ADDRESS_LENGTH_MAX 		200
#define PACK_VERSION_LENGTH_MAX 		100
#define COMPLEX_TYPE_ARRAY_SIZE_MAX		10
#define TEXT_VALUE_LENGTH_MAX 			100000

#define INITIAL_PACK_BUFFER_SIZE		10000

#ifndef NULL
	#define NULL ((void*)0)
#endif

#ifndef BOOL_TRUE
#define BOOL_TRUE		(1)
#endif

#ifndef BOOL_FALSE
#define BOOL_FALSE		(0)
#endif

// ----------------------- ENUMERATIONS ---------------------//
typedef enum PrimitiveValueType {
	BlobValue		= 0,
	BooleanValue	,
	DecimalValue	,
	DoubleValue		,
	FloatValue		,
	NullValue		,
	TextHashValue	,
	TextValue		,
	IP4Value		,
	ListValue		,
	MapValue		,
	FloatArray		,
	IntArray		,
	TextArray		,
	DoubleSummary	,
	LongSummary
} PrimitiveValueType;

// ----------------------- STRUCTURES -----------------------//

typedef struct DoubleSummaryValue {
	double sum;
	double min;
	double max;
	int32_t count;
} DoubleSummaryValue;

typedef struct LongSummaryValue {
	int64_t sum;
	int64_t min;
	int64_t max;
	int32_t count;
} LongSummaryValue;

typedef union PrimitiveValue {
	uint8_t* blob_value; // blob value
	uint8_t bool_value;
	int64_t long_value;
	double double_value;
	uint32_t hash_value;
	uint32_t ip_value;
	float float_value;
	DoubleSummaryValue dsum_value;
	LongSummaryValue lsum_value;
} PrimitiveValue;

typedef struct ScouterPrimitiveValue {				// For Complex Type. Array. List. Map.
	PrimitiveValueType 	type;
	PrimitiveValue 		value;
	uint8_t				blob_size;					// it contians length of byte stream or text string.
	uint8_t				isCancelled[COMPLEX_TYPE_ARRAY_SIZE_MAX];
	int 				size;
	ScouterValue values[COMPLEX_TYPE_ARRAY_SIZE_MAX];
} ScouterPrimitiveValue;

typedef struct ScouterValue {				// For Complex Type. Array. List. Map.
	PrimitiveValueType 	type;
	PrimitiveValue 		value;
	uint8_t				isCancelled[COMPLEX_TYPE_ARRAY_SIZE_MAX];
	int 				size;
	ScouterPrimitiveValue values[COMPLEX_TYPE_ARRAY_SIZE_MAX];
} ScouterValue;

// ----------------- VALUE INTERFACE FUNCTIONS --------------//

// It should clear all reserved resource of PrimitiveValue.
void clear_value(ScouterValue* pvalue);

#endif /* SCOUTER_TYPES_H_ */

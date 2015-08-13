/****************************************************************************************/
/*
 *	This file contains the read/write/clear method of the scouter value types.
 *
 *
 */
/****************************************************************************************/

#include "scouter_types.h"

// ------------------------------------- UTIL MACROS -------------------------------------//

// -------------------------------- STATIC FUNCTIONS ----------------------------------//

void clear_primitive_value(ScouterPrimitiveValue* pvalue)
{
	if(!pvalue)
		return;

	switch(pvalue->type)
	{
	case 	BlobValue		:
		free(pvalue->value->blob_value);
		break;
	case	BooleanValue	:
	case	DecimalValue	:
	case	DoubleValue		:
	case	FloatValue		:
	case	NullValue		:
	case	TextHashValue	:
		break;
	case	TextValue		:
		free(pvalue->value->blob_value);
		break;
	case	IP4Value		:
	case	DoubleSummary	:
	case	LongSummary		:
	default :
		break;
	}
}


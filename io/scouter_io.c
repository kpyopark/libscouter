/****************************************************************************************/
/*
 *	This file contains the read/write/clear method of the scouter value types.
 *
 *
 */
/****************************************************************************************/

#include "scouter_io.h"

// ------------------------------------- UTIL MACROS -------------------------------------//

// -------------------------------- NETWORK IO FUNCTIONS ----------------------------------//
// CAUTION !!!

int64_t extend_bytes_with_sign(uint64_t src_value, int src_size, int dst_size)
{
	uint64_t dst_value = 0;
	uint8_t* pdst = (uint8_t*)&dst_value;
	uint8_t* psrc = (uint8_t*)&src_value;

	uint8_t upper_byte = 0x00;

	src_value = htonll(src_value);

	int byte_start_position = dst_size - src_size;

	int pos = 0;
	if(psrc[byte_start_position] & 0x80)
	{
		// negative value.
		upper_byte = 0xff;
	}

	for(; pos < dst_size; pos++)
	{
		if(pos < byte_start_position)
		{
			pdst[pos] = upper_byte;
		}
		else
		{
			pdst[pos] = psrc[pos];
		}
	}
	return (int64_t)ntoh(dst_value);
}

void write_byte(PacketBuffer* pbuffer, uint8_t value)
{
	CUR_WRITE_POS(pbuffer) = value;
	FR_WRITE_POS(pbuffer,1);
}

const uint8_t read_byte(PacketBuffer* pbuffer)
{
	uint8_t* cur_position = CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return *cur_position;
}

void write_2_bytes(PacketBuffer* pbuffer, uint16_t value)
{
	value = htonl(value);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 8);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & value;
	FR_WRITE_POS(pbuffer,1);
}

uint16_t read_2_bytes(PacketBuffer* pbuffer)
{
	uint16_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return ntohs(value);
}

uint32_t read_3_bytes(PacketBuffer* pbuffer)
{
	uint64_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return ntohl(value);
}

void write_4_bytes(PacketBuffer* pbuffer, uint32_t value)
{
	value = htonl(value);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 24);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 16);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 8);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & value;
	FR_WRITE_POS(pbuffer,1);
}

uint32_t read_4_bytes(PacketBuffer* pbuffer)
{
	uint32_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return ntohl(value);
}

uint32_t read_5_bytes(PacketBuffer* pbuffer)
{
	uint64_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return ntohll(value);
}

void write_8_bytes(PacketBuffer* pbuffer, uint64_t value)
{
	value = htonll(value);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 56);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 48);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 40);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 32);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 24);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 16);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 8);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & value;
	FR_WRITE_POS(pbuffer,1);
}

uint32_t read_8_bytes(PacketBuffer* pbuffer)
{
	uint32_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	return ntohll(value);
}

void write_blob(PacketBuffer* pbuffer, uint8_t* src, int size)
{
	if(size == 0)
	{
		write_byte(pbuffer, 0x00);
	} else if (size < 0xfe) {
		write_byte(pbuffer, (uint8_t)size);
		WRITE_BYTES(pbuffer, src, size);
	} else if (size <= 0xffff ) {
		write_byte(pbuffer, 0xff);
		write_2_bytes(pbuffer, (uint16_t)size);
		WRITE_BYTES(pbuffer, src, size);
	} else {
		write_byte(pbuffer, 0xfe);
		write_4_bytes(pbuffer, (uint32_t)size);
		WRITE_BYTES(pbuffer, src, size);
	}
}

int read_blob(PacketBuffer* pbuffer, uint8_t** dst)
{
	unsigned int size = *CUR_READ_POS(pbuffer);
	if (!size)
	{
		*dst = NULL;
		return 0;
	}
	else if (size == 0xff)
	{
		size = read_2_bytes(pbuffer);
	}
	else if (size == 0xfe)
	{
		size = read_4_bytes(pbuffer);
	}
	*dst = (uint8_t*)malloc(size);
	if(*dst)
	{
		FR_READ_POS(pbuffer, size);
		return 0;
	}
	READ_BYTES(pbuffer, dst, size);
	return size;
}

float read_float(PacketBuffer* pbuffer)
{
	float fvalue = 0;
	uint32_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = ntohl(value);
	fvalue = *(float*)(&value);
	return fvalue;
}

void write_float(PacketBuffer* pbuffer, float fvalue)
{
	uint32_t value = 0;
	value = *(uint32_t*)(&fvalue);
	value = htonl(value);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 24);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 16);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 8);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & value;
	FR_WRITE_POS(pbuffer,1);
}

double read_double(PacketBuffer* pbuffer)
{
	double lfvalue = 0;
	uint64_t value = *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = value << 8 + *CUR_READ_POS(pbuffer);
	FR_READ_POS(pbuffer, 1);
	value = ntohll(value);
	lfvalue = *(double*)(&value);
	return lfvalue;
}

void write_double(PacketBuffer* pbuffer, double lfvalue)
{
	uint64_t value = 0;
	value = *(uint64_t*)(&lfvalue);
	value = htonll(value);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 56);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 48);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 40);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 32);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 24);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 16);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & (value >> 8);
	FR_WRITE_POS(pbuffer,1);
	CUR_WRITE_POS(pbuffer) = 0xff & value;
	FR_WRITE_POS(pbuffer,1);
}

// --------------------- IO Function without hton/ntoh -------------------------------------------------- //

void write_decimal(PacketBuffer* pbuffer, int64_t dvalue)
{
	if(!dvalue)
	{
		write_byte(pbuffer, 0);
	}
	else if (INT8_MIN <= dvalue && dvalue <= INT8_MAX)
	{
		write_byte(pbuffer, 1);
		write_byte(pbuffer,(uint8_t)dvalue);
	}
	else if (INT16_MIN <= dvalue && dvalue <= INT16_MAX)
	{
		write_byte(pbuffer, 2);
		write_2_bytes(pbuffer, (uint16_t)dvalue);
	}
	else if (INT32_MIN <= dvalue && dvalue <= INT32_MAX)
	{
		write_byte(pbuffer, 4);
		write_4_bytes(pbuffer, (uint32_t)dvalue);
	}
	else
	{
		write_byte(pbuffer, 8);
		write_8_bytes(pbuffer, (uint32_t)dvalue);
	}
}

int64_t read_decimal(PacketBuffer* pbuffer)
{
	int size = read_byte(pbuffer);
	int64_t value;
	switch(size)
	{
	case 0 :
		value = 0;
		break;
	case 1 :
		value = (int64_t)read_byte(pbuffer);
		break;
	case 2 :
		value = (int64_t)read_2_bytes(pbuffer);
		break;
	case 3 :
		value = (int64_t)extend_bytes_with_sign((uint64_t)read_3_bytes(pbuffer), 3, 4);
		break;
	case 4 :
		value = (int64_t)read_4_bytes(pbuffer);
		break;
	case 5 :
		value = (int64_t)extend_bytes_with_sign((uint64_t)read_5_bytes(pbuffer), 5, 8);
		break;
	case 8 :
		value = (int64_t)read_8_bytes(pbuffer);
		break;
	default :
		value = 0;
		break;
	}
	return value;
}

// -------------------------------- FUNCTIONS ----------------------------------//
void write_primitive_value(ScouterPrimitiveValue* pvalue, PacketBuffer* pbuffer)
{
	if(!pvalue)
		return;

	switch(pvalue->type)
	{
	case 	BlobValue		:
		write_blob(pbuffer, pvalue->value.blob_value, pvalue->blob_size);
		break;
	case	BooleanValue	:
		write_byte(pbuffer, pvalue->value.bool_value);
		break;
	case	DecimalValue	:
		write_decimal(pbuffer, pvalue->value.long_value);
		break;
	case	DoubleValue		:
		write_double(pbuffer, pvalue->value.double_value);
		break;
	case	FloatValue		:
	case	NullValue		:
	case	TextHashValue	:
		break;
	case	TextValue		:
		break;
	case	IP4Value		:
	case	DoubleSummary	:
	case	LongSummary		:
	default :
		break;
	}
}

// It should clear all reserved resource of PrimitiveValue.
void clear_value(ScouterValue* pvalue)
{
	if(!pvalue)
		return;

	switch(pvalue->type)
	{
	case 	BlobValue		:
	case	BooleanValue	:
	case	DecimalValue	:
	case	DoubleValue		:
	case	FloatValue		:
	case	NullValue		:
	case	TextHashValue	:
	case	TextValue		:
	case	IP4Value		:
	case	DoubleSummary	:
	case	LongSummary		:
		clear_primitive_value(&pvalue->value);
		break;

	case	ListValue		:
	case	MapValue		:
	case	FloatArray		:
	case	IntArray		:
	case	TextArray		:
	{
		int pos = 0;
		for(; pos < pvalue->size ; pos++ )
		{
			clear_primitive_value(&pvalue->values[pos]);
		}
	}
		break;
	}
}

// return - the size of write into stream.
// This method will increase the write position of the PacketBuffer.
int write_value(ScouterValue* pvalue, PacketBuffer* buffer, int max_size)
{
	if(!pvalue || !buffer)
	{
		return 0;
	}

}

// Read the primitive value from the buffer and copy it.
// This method will increate the read position of the PacketBuffer.
void read_value(ScouterValue* pvalue, PacketBuffer* buffer);


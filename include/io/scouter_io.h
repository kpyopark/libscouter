/*
 * scouter_io.h
 *
 *  Created on: 2015. 8. 13.
 *      Author: LowFormat
 */

#ifndef SCOUTER_IO_H_
#define SCOUTER_IO_H_

#include "scouter_types.h"
#include <stdio.h>
#include <memory.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>

#ifdef WORDS_BIGENDIAN
#define htonll(x)   (x)
#define ntohll(x)   (x)
#else
#define htonll(x)   ((((uint64_t)htonl(x)) << 32) + htonl(x >> 32))
#define ntohll(x)   ((((uint64_t)ntohl(x)) << 32) + ntohl(x >> 32))
#endif

// ------------------------------------- UTIL MACROS -------------------------------------//

#define CUR_WRITE_POS(x)		((x)->pbuffer[(x)->write_position])
#define FR_WRITE_POS(x, y)		(((x)->write_position) += (y))

#define CUR_READ_POS(x)			((x)->pbuffer[(x)->read_position])
#define FR_READ_POS(x, y)		(((x)->read_position) += (y))

#define WRITE_BYTES(pbuffer, src, size)	do { memcpy(CUR_WRITE_POS(pbuffer), (src), size); FR_WRITE_POS(pbuffer, size); } while(0)
#define READ_BYTES(pbuffer, dst, size)	do { memcpy(dst, CUR_READ_POS(pbuffer), size); FR_READ_POS(pbuffer, size); } while(0)
// ------------------------------ STRUCTURES --------------------------------------------//
typedef struct PacketBuffer {
	int write_position;
	int read_position;
	uint8_t pbuffer[INITIAL_PACK_BUFFER_SIZE];
} PacketBuffer;

// -----------------------     INTERFACES -----------------------------------------------//
// return - the size of write into stream.
// This method will increase the write position of the PacketBuffer.
int write_value(ScouterValue* pvalue, PacketBuffer* buffer, int max_size);

// Read the primitive value from the buffer and copy it.
// This method will increate the read position of the PacketBuffer.
void read_value(ScouterValue* pvalue, PacketBuffer* buffer);

// Write Byte Stream into Buffer.
void write_byte_into_buffer(PacketBuffer* buffer, uint8_t* contents, int size);

// Return the current pointer position and increase the read position.
uint8_t* read_byte_from_buffer(PacketBuffer* buffer, int size);




#endif /* SCOUTER_IO_H_ */


#ifndef SCOUTER_PACKET_H_
#define SCOUTER_PACKET_H_


#include "scouter_types.h"

// ----------------------- BASIC CONSTANTS ------------------//

// ----------------------- LIMIT ----------------------------//

// ----------------------- ENUMERATIONS ---------------------//
typedef enum PacketType {
	MAP = 10			,
	XLOG = 21			,
	XLOG_PROFILE = 26	,
	TEXT = 50			,
	PERF_COUNTER = 60	,
	PERF_STATUS = 61	,
	ALERT = 70			,
	OBJECT = 80
} PacketType;

// ----------------------- STRUCTURES -----------------------//
typedef struct PerformanceCounter {
	uint8_t	epoch_time;
	uint8_t obj_name[PACK_OBJ_NAME_LENGTH_MAX];
	uint8_t time_type;
	ScouterValue map_value;
} PerformanceCounter;

typedef union PacketValue {
	PerformanceCounter pcounter;
} PacketValue;

typedef struct ScouterPacket {
	uint8_t 	header[4];
	PacketType	type;
	PacketValue value;
} ScouterPacket;

// ------------------- INTERFACE FUNCTIONS ------------------//
// Clear all values contained in the packet instance. This method will release the resources related with this instance.
void clear_scouter_packet(ScouterPacket* packet);

// Read the scouter value from buffer.
void read_scouter_packet_from_buffer(ScouterPacket* value, PacketBuffer* buffer);

// Write Byte Stream into Buffer.
void write_scouter_packet_into_buffer(ScouterPacket* value, PacketBuffer* buffer);

#endif /* SCOUTER_PACKET_H_ */

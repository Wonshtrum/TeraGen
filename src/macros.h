#ifndef __MACROS_H__
#define __MACROS_H__

#define S_BIND(x) std::bind(&x, std::placeholders::_1)
#define M_BIND(x) std::bind(&x, this, std::placeholders::_1)
#define BIND(x, y) std::bind(&x, &y, std::placeholders::_1)
#define CHUNK_SIZE 16
typedef uint8_t Block;
typedef uint16_t ChunkId;

#endif

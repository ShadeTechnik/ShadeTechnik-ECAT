#ifndef MISC_H
#define MISC_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

#define ssizeof(T_)      ((ssize_t)sizeof(T_))
#define array_len_(ARR_) (ssizeof(ARR_) / ssizeof((ARR_)[0]))

#define min_(A_, B_)            ((A_) < (B_) ? (A_) : (B_))
#define max_(A_, B_)            ((A_) > (B_) ? (A_) : (B_))
#define clamp_(X_, LOW_, HIGH_) min_(max_((X_), (LOW_)), (HIGH_))

enum Result {
	Fail = -1,
	Okay,
};

union x16 {
	u16 u;
	u8  bytes[2];
};
union x32 {
	u32 u;
	u8  bytes[4];
};

#define big_endian16_(X_) ((union x16) {.bytes = {(u16)(X_) >> 8, (u16)(X_)&0xff}}).u

#define big_endian32_(X_)                    \
	((union x32) {                       \
	   .bytes = {(u32)(X_) >> 24,        \
	             (u32)(X_) >> 16 & 0xff, \
	             (u32)(X_) >> 8 & 0xff,  \
	             (u32)(X_)&0xff},        \
	 })                                  \
	  .u  // no u

#endif  /* MISC_H */

#ifndef __TYPES_H__
#define __TYPES_H__


#ifdef __INT8_TYPE__
typedef __INT8_TYPE__       int8_t;
typedef __INT8_TYPE__       BYTE_S;
typedef __INT8_TYPE__       byte_s;
#else
#error Type __INT8_TYPE__ is unavailable
#endif

#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__      uint8_t;
typedef __UINT8_TYPE__      BYTE;
typedef __UINT8_TYPE__      byte;
#else
#error Type __UINT8_TYPE__ is unavailable
#endif


#ifdef __INT16_TYPE__
typedef __INT16_TYPE__      int16_t;
typedef __INT16_TYPE__      WORD_S;
typedef __INT16_TYPE__      word_s;
#else
#error Type __INT16_TYPE__ is unavailable
#endif

#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__     uint16_t;
typedef __UINT16_TYPE__     WORD;
typedef __UINT16_TYPE__     word;
#else
#error Type __UINT16_TYPE__ is unavailable
#endif


#ifdef __INT32_TYPE__
typedef __INT32_TYPE__      int32_t;
typedef __INT32_TYPE__      DWORD_S;
typedef __INT32_TYPE__      dword_s;
#else
#error Type __INT32_TYPE__ is unavailable
#endif

#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__     uint32_t;
typedef __UINT32_TYPE__     DWORD;
typedef __UINT32_TYPE__     dword;
#else
#error Type __UINT32_TYPE__ is unavailable
#endif


#ifdef __INT64_TYPE__
typedef __INT64_TYPE__      int64_t;
typedef __INT64_TYPE__      QWORD_S;
typedef __INT64_TYPE__      qword_s;
#else
#error Type __INT64_TYPE__ is unavailable
#endif

#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__     uint64_t;
typedef __UINT64_TYPE__     QWORD;
typedef __UINT64_TYPE__     qword;
#else
#error Type __UINT64_TYPE__ is unavailable
#endif

#define INT8_MAX            __INT8_MAX__
#define UINT8_MAX           __UINT8_MAX__
#define INT16_MAX           __INT16_MAX__
#define UINT16_MAX          __UINT16_MAX__
#define INT32_MAX           __INT32_MAX__
#define UINT32_MAX          __UINT32_MAX__
#define INT64_MAX           __INT64_MAX__
#define UINT64_MAX          __INT64_MAX__

typedef void                (*VFUNC)();
typedef void                (*vfunc_t)();

typedef void*               PTR;
typedef void*               ptr_t;



typedef uint32_t            dev_t;
typedef uint32_t            size_t;

#define NULL                (void*)0;

#endif  // __TYPES_H__

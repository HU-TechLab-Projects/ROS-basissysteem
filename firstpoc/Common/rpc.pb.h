/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Wed Jul 17 13:19:30 2019. */

#ifndef PB_RPC_PB_H_INCLUDED
#define PB_RPC_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _ack {
    bool ack;
/* @@protoc_insertion_point(struct:ack) */
} ack;

typedef struct _add {
    int32_t a;
    int32_t b;
/* @@protoc_insertion_point(struct:add) */
} add;

typedef struct _singlein {
    int32_t response;
/* @@protoc_insertion_point(struct:singlein) */
} singlein;

/* Default values for struct fields */

/* Initializer values for message structs */
#define add_init_default                         {0, 0}
#define singlein_init_default                    {0}
#define ack_init_default                         {0}
#define add_init_zero                            {0, 0}
#define singlein_init_zero                       {0}
#define ack_init_zero                            {0}

/* Field tags (for use in manual encoding/decoding) */
#define ack_ack_tag                              1
#define add_a_tag                                1
#define add_b_tag                                2
#define singlein_response_tag                    1

/* Struct field encoding specification for nanopb */
extern const pb_field_t add_fields[3];
extern const pb_field_t singlein_fields[2];
extern const pb_field_t ack_fields[2];

/* Maximum encoded size of messages (where known) */
#define add_size                                 22
#define singlein_size                            11
#define ack_size                                 2

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define RPC_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
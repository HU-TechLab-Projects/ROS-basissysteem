/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.3 at Wed Jul 17 15:58:13 2019. */

#include "rpc.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t command_fields[2] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, command, command, command, 0),
    PB_LAST_FIELD
};

const pb_field_t sum_rpc_fields[3] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, sum_rpc, a, a, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, sum_rpc, b, a, 0),
    PB_LAST_FIELD
};

const pb_field_t single_int_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, single_int, response, response, 0),
    PB_LAST_FIELD
};

const pb_field_t ack_nak_fields[2] = {
    PB_FIELD(  1, BOOL    , SINGULAR, STATIC  , FIRST, ack_nak, ack, ack, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */

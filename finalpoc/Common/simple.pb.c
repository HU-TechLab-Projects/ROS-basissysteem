/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.3 at Wed Jul 24 15:12:27 2019. */

#include "simple.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t command_fields[2] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, command, command, command, 0),
    PB_LAST_FIELD
};

const pb_field_t Controller_fields[4] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, Controller, x, x, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, Controller, y, x, 0),
    PB_FIELD(  3, BOOL    , SINGULAR, STATIC  , OTHER, Controller, sw, y, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */

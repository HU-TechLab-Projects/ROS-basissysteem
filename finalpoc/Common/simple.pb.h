/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Wed Jul 24 13:25:15 2019. */

#ifndef PB_SIMPLE_PB_H_INCLUDED
#define PB_SIMPLE_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _Controller {
    int32_t x;
    int32_t y;
    bool sw;
/* @@protoc_insertion_point(struct:Controller) */
} Controller;

/* Default values for struct fields */

/* Initializer values for message structs */
#define Controller_init_default                  {0, 0, 0}
#define Controller_init_zero                     {0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define Controller_x_tag                         1
#define Controller_y_tag                         2
#define Controller_sw_tag                        3

/* Struct field encoding specification for nanopb */
extern const pb_field_t Controller_fields[4];

/* Maximum encoded size of messages (where known) */
#define Controller_size                          24

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SIMPLE_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif

#============================================================================
#
# simple project makefile (just a main file)
#
# (c) Wouter van Ooijen (wouter@voti.nl) 2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
#============================================================================
include nanopb/extra/nanopb.mk

CPPFLAGS = -Wall -Werror -g -O0
CPPFLAGS += -I$(NANOPB_DIR)

FINALPOCCOMMON = finalpoc/Common/
FINALPOCDUE = finalpoc/Due/
FINALPOCNATIVE = finalpoc/Native

NATIVEINCLUDES = -I$(FINALPOCCOMMON) -I$(FINALPOCNATIVE) -INative/

proto: $(FINALPOCCOMMON)simple.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $(FINALPOCCOMMON)simple.proto

proto2: myproto.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. myproto.proto

# pcside: pcside.cpp simple.pb.c $(NANOPB_DIR)/*.c
# 	g++ pcside.cpp simple.pb.c $(NANOPB_DIR)/*.c $(CPPFLAGS) -o pcside

pcside: pcside.cpp proto $(NANOPB_CORE)
	g++ pcside.cpp $(FINALPOCCOMMON)simple.pb.c  $(NANOPB_CORE) $(NATIVEINCLUDES) $(CPPFLAGS) -o pcside


#source files in this project (main.* is automatically assumed)
SOURCES := simple.pb.c pb_common.c pb_decode.c pb_encode.c analogstick.cpp
#SOURCES := simple.pb.cc common.cc port.cc once.cc coded_stream.cc wire_format_lite_inl.cc descriptor.cc generated_message_reflection.cc reflection_ops.cc wire_format.cc

# header files in this project
# HEADERS := simple.pb.h pb_common.h pb_decode.h pb_encode.h analogstick.hpp
HEADERS := due_nanocom.hpp

# other places to look for files for this project
SEARCH  := $(NANOPB_DIR) $(FINALPOCCOMMON) $(FINALPOCDUE) Due

# set RELATIVE to the next higher directory
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/makefile.link

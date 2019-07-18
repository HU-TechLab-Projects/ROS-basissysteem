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

CONSOLE_BAUDRATE = 115200

#final poc varriables and rules
FINALPOCCOMMON 			= finalpoc/Common/
FINALPOCDUE 				= finalpoc/Due/
FINALPOCNATIVE 			= finalpoc/Native/
FINALNATIVEINCLUDES = -I$(FINALPOCCOMMON) -I$(FINALPOCNATIVE) -INative/

finalproto: $(FINALPOCCOMMON)simple.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $(FINALPOCCOMMON)simple.proto

finalpcside: pcside.cpp finalproto $(NANOPB_CORE)
	g++ pcside.cpp $(FINALPOCNATIVE)controllerpcside.cpp $(FINALPOCCOMMON)simple.pb.c  $(NANOPB_CORE) $(FINALNATIVEINCLUDES) $(CPPFLAGS) -o finalpcside


#first poc varriables
FIRSTPOCCOMMON 	= firstpoc/Common/
FIRSTPOCDUE 		= firstpoc/Due/
FIRSTPOCNATIVE 	= firstpoc/Native/
FIRSTNATIVEINCLUDES = -I$(FIRSTPOCCOMMON) -I$(FIRSTPOCNATIVE) -INative/

firstproto: $(FIRSTPOCCOMMON)rpc.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $(FIRSTPOCCOMMON)rpc.proto

firstpcside: pcside.cpp firstproto $(NANOPB_CORE)
	g++ pcside.cpp $(FIRSTPOCNATIVE)ledsmainpcside.cpp $(FIRSTPOCCOMMON)rpc.pb.c $(NANOPB_CORE) $(FIRSTNATIVEINCLUDES) $(CPPFLAGS) -o firstpcside


#source files in this project (main.* is automatically assumed)
#sources for finalpoc
#SOURCES := simple.pb.c pb_common.c pb_decode.c pb_encode.c analogstick.cpp

#sources for firstpoc
SOURCES := rpc.pb.c pb_common.c pb_decode.c pb_encode.c ledsmain.cpp

# header files in this project
# HEADERS := simple.pb.h pb_common.h pb_decode.h pb_encode.h analogstick.hpp
HEADERS := due_nanocom.hpp

# other places to look for files for this project
#search folders for finalpoc
#SEARCH  := $(NANOPB_DIR) $(FINALPOCCOMMON) $(FINALPOCDUE) Due

#searchfolders for first poc
SEARCH := $(NANOPB_DIR) $(FIRSTPOCCOMMON) $(FIRSTPOCDUE) Due

# set RELATIVE to the next higher directory
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/makefile.link

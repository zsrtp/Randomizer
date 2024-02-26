#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>/devkitPPC")
endif

ifeq ($(PLATFORM),wii)
include $(DEVKITPPC)/wii_rules
else ifeq ($(PLATFORM),gcn)
include $(DEVKITPPC)/gamecube_rules
endif

# This will be the resulting .rel file - No spaces
OUTPUT_FILENAME := boot

# DON'T TOUCH UNLESS YOU KNOW WHAT YOU'RE DOING
LIBTP_REL := $(ROOT_DIR)/externals/libtp_rel

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	ELF2REL := $(abspath $(ROOT_DIR)/bin/elf2rel)
else
	ELF2REL := $(abspath $(ROOT_DIR)/bin/elf2rel.exe)
endif

JSON_READ := python3 $(abspath $(ROOT_DIR)/bin/json_read.py)

ifeq ($(VERSION),)
all: gcn wii
gcn: us jp eu
wii: wus0 wus2 wjp weu
us:
	@$(MAKE) --no-print-directory VERSION=us PLATFORM=gcn
jp:
	@$(MAKE) --no-print-directory VERSION=jp PLATFORM=gcn
eu:
	@$(MAKE) --no-print-directory VERSION=eu PLATFORM=gcn
wus0:
	@$(MAKE) --no-print-directory VERSION=wus0 PLATFORM=wii
wus2:
	@$(MAKE) --no-print-directory VERSION=wus2 PLATFORM=wii
wjp:
	@$(MAKE) --no-print-directory VERSION=wjp PLATFORM=wii
weu:
	@$(MAKE) --no-print-directory VERSION=weu PLATFORM=wii

clean:
	@$(MAKE) --no-print-directory clean_target VERSION=us PLATFORM=gcn
	@$(MAKE) --no-print-directory clean_target VERSION=jp PLATFORM=gcn
	@$(MAKE) --no-print-directory clean_target VERSION=eu PLATFORM=gcn
	@$(MAKE) --no-print-directory clean_target VERSION=wus0 PLATFORM=wii
	@$(MAKE) --no-print-directory clean_target VERSION=wus2 PLATFORM=wii
	@$(MAKE) --no-print-directory clean_target VERSION=wjp PLATFORM=wii
	@$(MAKE) --no-print-directory clean_target VERSION=weu PLATFORM=wii

.PHONY: all clean gcn wii us jp eu wus0 wus2 wjp weu
else

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(OUTPUT_FILENAME).$(VERSION)
BUILD		:=	build.$(VERSION)
SOURCES		:=	$(CURDIR)/source $(wildcard $(CURDIR)/source/*) $(LIBTP_REL)/source $(wildcard $(LIBTP_REL)/source/*)
DATA		:=	data
INCLUDES	:=	$(CURDIR)/include $(ROOT_DIR)/include $(LIBTP_REL)/include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ifeq ($(PLATFORM),wii)
MACHDEP_PLATFORM = rvl
else ifeq ($(PLATFORM),gcn)
MACHDEP_PLATFORM = gcn
endif

MACHDEP		= -mno-sdata -m$(MACHDEP_PLATFORM) -DGEKKO -mcpu=750 -meabi -mhard-float

CFLAGS		= -nostdlib -ffunction-sections -fdata-sections -g -Oz -Wall -Werror -Wextra -Wshadow -Wno-address-of-packed-member -Wno-stringop-truncation $(MACHDEP) $(INCLUDE) $(DVD_DEF) -D_PROJECT_NAME='"$(PROJECT_NAME)"' -D_VERSION_MAJOR='$(_VERSION_MAJOR)' -D_VERSION_MINOR='$(_VERSION_MINOR)' -D_VERSION_PATCH='$(_VERSION_PATCH)'  -D_VERSION='"$(_VERSION)"' -D_VARIANT='"$(_VARIANT)"'
CXXFLAGS	= -fno-exceptions -fno-rtti -std=gnu++23 $(CFLAGS)

LDFLAGS		= -r -e _prolog -u _prolog -u _epilog -u _unresolved -Wl,--gc-sections -nostdlib -g $(MACHDEP) -Wl,-Map,$(notdir $@).map

# Platform options
ifeq ($(VERSION),us)
	CFLAGS += -DTP_US -DTP_GUS
	CFLAGS += -D_BUILDID='"$(BUILDID)US"'
	ASFLAGS += -DTP_US -DTP_GUS
else ifeq ($(VERSION),eu)
	CFLAGS += -DTP_EU -DTP_GEU
	CFLAGS += -D_BUILDID='"$(BUILDID)EU"'
	ASFLAGS += -DTP_EU -DTP_GEU
else ifeq ($(VERSION),jp)
	CFLAGS += -DTP_JP -DTP_GJP
	CFLAGS += -D_BUILDID='"$(BUILDID)JP"'
	ASFLAGS += -DTP_JP -DTP_GJP
else ifeq ($(VERSION),wus0)
	CFLAGS += -DTP_US -DTP_WUS0 -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WUS0"'
	ASFLAGS += -DTP_US -DTP_WUS0 -DPLATFORM_WII=1
else ifeq ($(VERSION),wus2)
	CFLAGS += -DTP_US -DTP_WUS2 -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WUS2"'
	ASFLAGS += -DTP_US -DTP_WUS2 -DPLATFORM_WII=1
else ifeq ($(VERSION),weu)
	CFLAGS += -DTP_EU -DTP_WEU -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WEU"'
	ASFLAGS += -DTP_EU -DTP_WEU -DPLATFORM_WII=1
else ifeq ($(VERSION),wjp)
	CFLAGS += -DTP_JP -DTP_WJP -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WJP"'
	ASFLAGS += -DTP_JP -DTP_WJP -DPLATFORM_WII=1
endif


#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= 

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o) $(SFILES:.S=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

# For REL linking
export LDFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.ld)))
# These are already defined from the root's Makefile
#export MAPFILE		:= $(abspath $(ROOT_DIR)/build.$(VERSION)/temp.$(VERSION).lst)
#export MODIDS		:= $(realpath $(ROOT_DIR)/assets/modids.json)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(abspath $(dir))) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD) \
			-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
			-L$(LIBOGC_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean_target

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean_target:
	@echo clean ... $(OUTPUT_FILENAME) $(VERSION)
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol $(OUTPUT).rel

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).rel: $(OUTPUT).elf $(MAPFILE)
$(OUTPUT).elf: $(LDFILES) $(OFILES)

$(OFILES_SOURCES) : $(HFILES)

ifndef SKIP_PACK
# REL linking
%.rel: %.elf
	@echo output ... $(notdir $@)
	@$(ELF2REL) $< -s $(abspath $(MAPFILE)) --rel-id $(shell $(JSON_READ) $(MODIDS) "$(OUTPUT_FILENAME)")
else
# REL linking
%.rel: %.elf
	@echo output ... $(notdir $@)
	@$(ELF2REL) $< -s $(abspath $(MAPFILE)) --rel-id $(shell $(JSON_READ) $(MODIDS) "$(OUTPUT_FILENAME)")
	@echo renaming $(notdir $@) to $(OUTPUT_FILENAME).rel
	@cp $@ $(OUTPUT_FILENAME).rel
endif

#---------------------------------------------------------------------------------
# This rule links in binary data with the .jpg extension
#---------------------------------------------------------------------------------
%.jpg.o	%_jpg.h :	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
endif

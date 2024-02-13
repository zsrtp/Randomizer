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

# Format: YYYYMMDDHHmm + 2 char Game Region
export BUILDID:='"$(shell date +'%Y%m%d%H%M')"'

# Version
export _VERSION_MAJOR:=1
export _VERSION_MINOR:=2
export _VERSION_PATCH:=0
export _VERSION:='"$(_VERSION_MAJOR).$(_VERSION_MINOR).$(_VERSION_PATCH)"'
# Variant: i.e. Public, NoLogic, Race, etc.
#export _VARIANT:= public

# This shows up in the memory card (manager) and can contain spaces
export PROJECT_NAME := Randomizer
# This will be the resulting .gci file - No spaces
OUTPUT_FILENAME := Randomizer


# DON'T TOUCH UNLESS YOU KNOW WHAT YOU'RE DOING
LIBTP_REL := externals/libtp_rel

export ROOT_DIR ?= $(CURDIR)

export GCIPACK := python3 $(realpath ../bin/gcipack.py)
export NANDPACK := python3 $(realpath ../bin/nandpack.py)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	export ELF2REL := $(realpath ../bin/elf2rel)
else
	export ELF2REL := $(realpath ../bin/elf2rel.exe)
endif

JSON_READ := python3 $(realpath ../bin/json_read.py)
MAPPER := python3 $(realpath ../bin/relmapper.py)

DVD ?= ""
ifneq ($(DVD),"")
	export DVD_DEF := "-DDVD"
endif

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
SOURCES		:=	source $(wildcard source/*) $(LIBTP_REL)/source $(wildcard $(LIBTP_REL)/source/*)
DATA		:=	data
INCLUDES	:=	$(CURDIR)/include $(CURDIR)/$(LIBTP_REL)/include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ifeq ($(PLATFORM),wii)
MACHDEP_PLATFORM = rvl
else ifeq ($(PLATFORM),gcn)
MACHDEP_PLATFORM = gcn
endif

MACHDEP		= -mno-sdata -m$(MACHDEP_PLATFORM) -DGEKKO -mcpu=750 -meabi -mhard-float

CFLAGS		= -nostdlib -ffunction-sections -fdata-sections -g -Oz -fvisibility=hidden -Wall -Werror -Wextra -Wshadow -Wno-address-of-packed-member -Wno-stringop-truncation $(MACHDEP) $(INCLUDE) $(DVD_DEF) -D_PROJECT_NAME='"$(PROJECT_NAME)"' -D_VERSION_MAJOR='$(_VERSION_MAJOR)' -D_VERSION_MINOR='$(_VERSION_MINOR)' -D_VERSION_PATCH='$(_VERSION_PATCH)'  -D_VERSION='"$(_VERSION)"' -D_VARIANT='"$(_VARIANT)"'
CXXFLAGS	= -fno-exceptions -fno-rtti -std=gnu++23 $(CFLAGS)

LDFLAGS		= -r -e _prolog -u _prolog -u _epilog -u _unresolved -Wl,--gc-sections,--gc-keep-exported -nostdlib -g $(MACHDEP) -Wl,-Map,$(notdir $@).map

# Platform options
ifeq ($(VERSION),us)
	CFLAGS += -DTP_US -DTP_GUS
	CFLAGS += -D_BUILDID='"$(BUILDID)US"'
	ASFLAGS += -DTP_US -DTP_GUS
	GAMECODE = "GZ2E"
	PRINTVER = "US"
else ifeq ($(VERSION),eu)
	CFLAGS += -DTP_EU -DTP_GEU
	CFLAGS += -D_BUILDID='"$(BUILDID)EU"'
	ASFLAGS += -DTP_EU -DTP_GEU
	GAMECODE = "GZ2P"
	PRINTVER = "EU"
else ifeq ($(VERSION),jp)
	CFLAGS += -DTP_JP -DTP_GJP
	CFLAGS += -D_BUILDID='"$(BUILDID)JP"'
	ASFLAGS += -DTP_JP -DTP_GJP
	GAMECODE = "GZ2J"
	PRINTVER = "JP"
else ifeq ($(VERSION),wus0)
	CFLAGS += -DTP_US -DTP_WUS0 -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WUS0"'
	ASFLAGS += -DTP_US -DTP_WUS0 -DPLATFORM_WII=1
	PACKVER = "us0"
else ifeq ($(VERSION),wus2)
	CFLAGS += -DTP_US -DTP_WUS2 -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WUS2"'
	ASFLAGS += -DTP_US -DTP_WUS2 -DPLATFORM_WII=1
	PACKVER = "us2"
else ifeq ($(VERSION),weu)
	CFLAGS += -DTP_EU -DTP_WEU -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WEU"'
	ASFLAGS += -DTP_EU -DTP_WEU -DPLATFORM_WII=1
	PACKVER = "eu"
else ifeq ($(VERSION),wjp)
	CFLAGS += -DTP_JP -DTP_WJP -DPLATFORM_WII=1
	CFLAGS += -D_BUILDID='"$(BUILDID)WJP"'
	ASFLAGS += -DTP_JP -DTP_WJP -DPLATFORM_WII=1
	PACKVER = "jp"
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

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
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

ifeq ($(PLATFORM),gcn)
BANNER_PREFIX := gc
else ifeq ($(PLATFORM),wii)
BANNER_PREFIX := wii
endif

# For REL linking
export LDFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.ld)))
export MAPFILE		:= $(ROOT_DIR)/$(BUILD)/temp.$(VERSION).lst
export MODIDS		:= $(realpath assets/modids.json)
export BASE_MAPFILE	:= $(realpath assets/$(VERSION).lst)
export BANNERFILE	:= $(realpath assets/$(BANNER_PREFIX)_banner.raw)
export ICONFILE		:= $(realpath assets/icon.raw)

export SUBREL		:= $(notdir $(wildcard subrel/*))
export SUBREL_CLEAN	:= $(addsuffix /clean,$(SUBREL))
export SUBRELS		:= $(foreach dir,$(SUBREL),$(ROOT_DIR)/subrel/$(dir)/$(dir).$(VERSION).rel)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(ROOT_DIR)/$(BUILD) \
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
ifeq ($(PLATFORM),gcn)
clean_target: $(SUBREL_CLEAN)
	@echo clean ... $(VERSION)
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol $(OUTPUT).rel $(OUTPUT).gci
else ifeq ($(PLATFORM),wii)
clean_target: $(SUBREL_CLEAN)
	@echo clean ... $(VERSION)
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol $(OUTPUT).rel $(OUTPUT).bin
endif

$(SUBREL_CLEAN):
	@$(MAKE) -C $(abspath subrel/$(patsubst %/,%,$(dir $@))) clean_target

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
ifeq ($(PLATFORM),gcn)
$(OUTPUT).gci: $(OUTPUT).rel $(BANNERFILE) $(ICONFILE)
else ifeq ($(PLATFORM),wii)
$(OUTPUT).bin: $(OUTPUT).rel $(BANNERFILE)
endif
$(OUTPUT).rel: $(OUTPUT).elf $(MAPFILE) $(SUBREL)
$(OUTPUT).elf: $(LDFILES) $(OFILES)

$(OFILES_SOURCES) : $(HFILES)

$(MAPFILE): $(OUTPUT).elf $(BASE_MAPFILE) $(MODIDS)
	@echo module mapping ... $(notdir $@)
	@$(MAPPER) -o $(MAPFILE) -i $(BASE_MAPFILE) -m $(MODIDS) $(OUTPUT).elf

$(SUBREL): $(MAPFILE)
	@echo making $@ ...
	@$(MAKE) -C $(abspath $(ROOT_DIR)/subrel/$@)
	@echo $@ ... Done

# REL linking
%.rel: %.elf
	@echo output ... $(notdir $@)
	@$(ELF2REL) $< -s $(MAPFILE) --rel-id $(shell $(JSON_READ) $(MODIDS) "$(OUTPUT_FILENAME)")

ifeq ($(PLATFORM),gcn)
%.gci: %.rel
	@echo packing ... $(notdir $@)
	@$(GCIPACK) $< "Custom REL File" "Twilight Princess" "($(PRINTVER)) $(PROJECT_NAME)" $(BANNERFILE) $(ICONFILE) $(GAMECODE) $(addprefix --rel ,$(SUBRELS))
else ifeq ($(PLATFORM),wii)
ifndef SKIP_PACK
%.bin: %.rel
	@echo packing ... $(notdir $@)
	@$(NANDPACK) generate -g $(PACKVER) -l 2 -f "$(PROJECT_NAME)" $< $(BANNERFILE) $@
	@$(NANDPACK) files add $@ $(SUBRELS) $(addprefix --map ,$(foreach subrel,$(SUBRELS),$(notdir $(subrel)):$(notdir $(subrel:%.$(VERSION).rel=%.rel))))
else
%.bin: %.rel
	@echo renaming $(notdir $<) to mod.rel
	@cp $< mod.rel
endif
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
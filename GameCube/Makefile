#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>/devkitPPC")
endif

include $(DEVKITPPC)/gamecube_rules

# Format: YYYYMMDDHHmm + 2 char Game Region
export BUILDID:='"$(shell date +'%Y%m%d%H%M')"'

# Version
export _VERSION_MAJOR:=1
export _VERSION_MINOR:=0
export _VERSION_PATCH:=0
export _VERSION:='"$(_VERSION_MAJOR).$(_VERSION_MINOR).$(_VERSION_PATCH)"'
# Variant: i.e. Public, NoLogic, Race, etc.
export _VARIANT:=public

# This shows up in the memory card (manager) and can contain spaces
export PROJECT_NAME := Randomizer
# This will be the resulting .gci file - No spaces
OUTPUT_FILENAME := Randomizer


# DON'T TOUCH UNLESS YOU KNOW WHAT YOU'RE DOING
LIBTP_REL := externals/libtp_rel

export ROOT_DIR ?= $(CURDIR)

export GCIPACK := python3 $(realpath ../bin/gcipack.py)

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
all: us jp eu
us:
	@$(MAKE) --no-print-directory VERSION=us
jp:
	@$(MAKE) --no-print-directory VERSION=jp
eu:
	@$(MAKE) --no-print-directory VERSION=eu

deploy:
	@status=$$(git status --porcelain); \
	if test "x$${status}" = x; then \
		echo Ready for deployment!; \
		echo Twilight Princess :: $(PROJECT_NAME) > build.log; \
		echo ------------------------- >> build.log; \
		echo Version: $(_VERSION) >> build.log; \
		echo Variant: $(_VARIANT) >> build.log; \
		echo Build ID: $(BUILDID) >> build.log; \
		printf "Build Log:\n\n-----\n" >> build.log; \
		make clean; \
		make all >> build.log; \
		echo ----- >> build.log; \
		echo Done. >> build.log; \
		echo Working directory is dirty; \		echo Ready for deployment!; \
		echo Twilight Princess :: $(PROJECT_NAME) > build.log; \
		echo ------------------------- >> build.log; \
		echo Version: $(_VERSION) >> build.log; \
		echo Variant: $(_VARIANT) >> build.log; \
		echo Build ID: $(BUILDID) >> build.log; \
		printf "Build Log:\n\n-----\n" >> build.log; \
		make clean; \
		make all >> build.log; \
		echo ----- >> build.log; \
		echo Done. >> build.log; \
	else \
		echo Working directory isn\'t clean, cannot release like this...; \
	fi

clean:
	@$(MAKE) --no-print-directory clean_target VERSION=us
	@$(MAKE) --no-print-directory clean_target VERSION=jp
	@$(MAKE) --no-print-directory clean_target VERSION=eu

.PHONY: all clean us jp eu
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

MACHDEP		= -mno-sdata -mgcn -DGEKKO -mcpu=750 -meabi -mhard-float

CFLAGS		= -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -fvisibility=hidden -Wall -Werror -Wno-address-of-packed-member $(MACHDEP) $(INCLUDE) $(DVD_DEF) -D_PROJECT_NAME='"$(PROJECT_NAME)"' -D_VERSION_MAJOR='$(_VERSION_MAJOR)' -D_VERSION_MINOR='$(_VERSION_MINOR)' -D_VERSION_PATCH='$(_VERSION_PATCH)'  -D_VERSION='"$(_VERSION)"' -D_VARIANT='"$(_VARIANT)"'
CXXFLAGS	= -fno-exceptions -fno-rtti -std=gnu++17 $(CFLAGS)

LDFLAGS		= -r -e _prolog -u _prolog -u _epilog -u _unresolved -Wl,--gc-sections,--gc-keep-exported -nostdlib -g $(MACHDEP) -Wl,-Map,$(notdir $@).map

# Platform options
ifeq ($(VERSION),us)
	CFLAGS += -DTP_US
	CFLAGS += -D_BUILDID='"$(BUILDID)US"'
	ASFLAGS += -DTP_US
	GAMECODE = "GZ2E"
	PRINTVER = "US"
else ifeq ($(VERSION),eu)
	CFLAGS += -DTP_EU
	CFLAGS += -D_BUILDID='"$(BUILDID)EU"'
	ASFLAGS += -DTP_EU
	GAMECODE = "GZ2P"
	PRINTVER = "EU"
else ifeq ($(VERSION),jp)
	CFLAGS += -DTP_JP
	CFLAGS += -D_BUILDID='"$(BUILDID)JP"'
	ASFLAGS += -DTP_JP
	GAMECODE = "GZ2J"
	PRINTVER = "JP"
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

# For REL linking
export LDFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.ld)))
export MAPFILE		:= $(ROOT_DIR)/$(BUILD)/temp.$(VERSION).lst
export MODIDS		:= $(realpath assets/modids.json)
export BASE_MAPFILE	:= $(realpath assets/$(VERSION).lst)
export BANNERFILE	:= $(realpath assets/banner.raw)
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
clean_target: $(SUBREL_CLEAN)
	@echo clean ... $(OUTPUT_FILENAME) $(VERSION)
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol $(OUTPUT).rel $(OUTPUT).gci

$(SUBREL_CLEAN):
	@$(MAKE) -C $(abspath subrel/$(patsubst %/,%,$(dir $@))) clean_target

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).gci: $(OUTPUT).rel $(BANNERFILE) $(ICONFILE)
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

%.gci: %.rel
	@echo packing ... $(notdir $@)
	@$(GCIPACK) $< "Custom REL File" "Twilight Princess" "($(PRINTVER)) $(PROJECT_NAME)" $(BANNERFILE) $(ICONFILE) $(GAMECODE) $(addprefix --rel ,$(SUBRELS))

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
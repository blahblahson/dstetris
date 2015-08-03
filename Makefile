PROGNAME = dstetris
OFILES   +=
ADD_LIBS +=

SUBDIRS = data

PATH 		:= $(DEVKITARM)/bin:$(PATH)

#ARM7BIN		:= -7 $(PAPATH)/lib/arm7/arm7.bin
TEXT1 		:= dstetris
TEXT2 		:= 1.1.0
TEXT3 		:= http://pqrs.dk/
ICON 		:= -b $(CURDIR)/../logo.bmp
LOGO		:= -o $(CURDIR)/../logo_wifi.bmp

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif
#---------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb generates a multiboot image
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET	:=	$(shell basename $(CURDIR))
BUILD		:=	build
SOURCES	:=	src data src/bulletpatterns
INCLUDES	:=	include build data 
UTILS := utils

EXPORT_DIR := /c/ndsexamples/
#---------------------------------------------------------------------------------
# ARM7BIN is the path to an arm7 binary other than the default
#	usage: ARM7BIN := -7 binaryName.bin
#
# ICON is the path to an icon to be used int the header plus text
#	usage: ICON := -t iconName.bmp "text line one; text line 2; text line 3"
# 
#---------------------------------------------------------------------------------



#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb-interwork

# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
CFLAGS	:=	-g -Wall -O2 \
 		-mcpu=arm9tdmi -mtune=arm9tdmi -fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM9

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	:=	-g $(ARCH) -mno-fpu -L/opt/devkitpro/devkitARM/lib


#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
# export PATH		:=	/d/dev/ds/devkitARM_r11/bin:/bin
 
#---------------------------------------------------------------------------------
# PATH to ndslib - just make a system variable called NDSLIBPATH and be done with it
#---------------------------------------------------------------------------------
# NDSLIBPATH	:=	/d/dev/ds/ndslib/
 
#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX			:=	arm-eabi-
#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lpng -lz -lfat -lnds9
 
 
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(DEVKITPRO)/libnds
 
 
#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------
 
export OUTPUT	:=	$(CURDIR)/$(TARGET)
 
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
 
export CC		:=	$(PREFIX)gcc
export CXX		:=	$(PREFIX)g++
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy
#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
export LD		:=	$(CXX)
#export LD		:=	$(CC)

DATA := data

DIMGFILES	:=	$(foreach dir,build/data/,$(notdir $(wildcard $(dir)/*.o)))
DOFILES		:=	$(foreach dir,$(DIMGFILES), $(DATA)/$(dir))
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PCXFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pcx)))
BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))
PNGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.png)))
PALFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pal)))
RAWFILES	:=	$(PNGFILES:.png=.raw)
MAPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.map)))
JPEGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.jpg)))
MODFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.mod)))
GIFFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.gif)))
BMPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bmp)))
BINFILES	:=	$(foreach dir,data,$(notdir $(wildcard $(dir)/*.bin)))
 
export OFILES	:=	$(MAPFILES:.map=.o) $(RAWFILES:.raw=.o) $(PALFILES:.pal=.o) $(BINFILES:.bin=.o) $(PCXFILES:.pcx=.o) $(JPEGFILES:.jpg=.o) $(MODFILES:.mod=.o) $(GIFFILES:.gif=.o) $(BMPFILES:.bmp=.o)\
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o) $(DOFILES)
 
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include/nds) \
					-I$(PAPATH)/include/nds\
					-I$(CURDIR)/$(BUILD)
 
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)
 
.PHONY: $(BUILD) clean export

DATS := $(foreach dir,data,$(notdir $(wildcard $(dir))))

#---------------------------------------------------------------------------------
$(BUILD):
	@make data
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
 
#---------------------------------------------------------------------------------
clean:
	rm -fr $(BUILD) *.elf *.*ds*
	rm -rf data/*.raw
	rm png2raw
 
export:
	@echo exporting ...$(TARGET)
	@cp *.nds $(EXPORT_DIR)/$(TARGET).nds

data: png2raw
	@echo 'converting png->raw'
	@$(UTILS)/png2raw.py

png2raw:
	g++ $(UTILS)/png2raw.cpp -lz -lpng -o png2raw

#---------------------------------------------------------------------------------
else
 
DEPENDS	:=	$(OFILES:.o=.d)
 
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).ds.gba	: 	$(OUTPUT).nds

$(OUTPUT).nds	: 	$(OUTPUT).bin

$(OUTPUT).bin	:	$(OUTPUT).elf
 
$(OUTPUT).elf	:	$(OFILES)
 
#---------------------------------------------------------------------------------
%.ds.gba: %.nds
	@echo built ... $(notdir $@)
	@dsbuild $< 
	@cp $(CURDIR)/../$(notdir $@) ../$(notdir $(OUTPUT)).sc.nds 

#---------------------------------------------------------------------------------
%.nds: %.bin
	
	@ndstool -c $@ -9 $(TARGET).bin $(ARM7BIN) $(LOGO) $(ICON) "$(TEXT1);$(TEXT2);$(TEXT3)"


#---------------------------------------------------------------------------------
%.bin: %.elf
	
	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
 
#---------------------------------------------------------------------------------
%.elf:
	@echo $(CURDIR)
	@echo $(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf
	@$(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf
 
 
 
#---------------------------------------------------------------------------------
# Compile Targets for C/C++
#---------------------------------------------------------------------------------
 
#---------------------------------------------------------------------------------
%.o : %.cpp
	@echo $(notdir $<)
	@$(CXX) -MM $(CFLAGS) -o $*.d $<
	@$(CXX) $(CFLAGS) -c $< -o$@
 
#---------------------------------------------------------------------------------
%.o : %.c
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(CFLAGS) -c $< -o$@
 
#---------------------------------------------------------------------------------
%.o : %.s
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(ASFLAGS) -c $< -o$@
 
define bin2o
	cp $(<) $(*).tmp
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm \
	--rename-section .data=.rodata \
	--redefine-sym _binary_$*_tmp_start=$*\
	--redefine-sym _binary_$*_tmp_end=$*_end\
	--redefine-sym _binary_$*_tmp_size=$*_size\
	$(*).tmp $(@)
	echo "extern const u8" $(*)"[];" > $(*).h
	echo "extern const u32" $(*)_size[]";" >> $(*).h
	rm $(*).tmp
endef
 
#---------------------------------------------------------------------------------
%.o	:	%.pcx
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
#%.o	:	%.png
#---------------------------------------------------------------------------------
#	@echo $(notdir $<)
#	$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.raw
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.pal
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)
 
#---------------------------------------------------------------------------------
%.o	:	%.map
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mdl
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mod
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.gif
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.bmp
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

 
-include $(DEPENDS) 

#---------------------------------------------------------------------------------------
endif
   
lib:
	$(DEVKITPRO)/devkitARM/arm-eabi/bin/ar -cr test.a build/*.o

#---------------------------------------------------------------------------------------

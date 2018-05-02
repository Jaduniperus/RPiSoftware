# Made by 0x223252, for RCO purpose only
# All rigth reserved

include .config.mk

FLAGS+= -D'BY_LINUX_MAKEFILE'
LDFLAGS+= -lwiringPi

LAST_HARD_ARCH=null
LAST_MODE=null
LAST_WARNING=null
LAST_GPROF=null
LAST_GDB=null
LAST_LINKAGE=null

LAST_HARD_ARCH=$(shell [ -f ".last_config" ] && cat .last_config | grep HARD_ARCH  | cut -d '=' -f2)
LAST_MODE=$(shell      [ -f ".last_config" ] && cat .last_config | grep MODE       | cut -d '=' -f2)
LAST_WARNING=$(shell   [ -f ".last_config" ] && cat .last_config | grep WARNING    | cut -d '=' -f2)
LAST_GPROF=$(shell     [ -f ".last_config" ] && cat .last_config | grep GPROF      | cut -d '=' -f2)
LAST_GDB=$(shell       [ -f ".last_config" ] && cat .last_config | grep GDB        | cut -d '=' -f2)
LAST_LINKAGE=$(shell   [ -f ".last_config" ] && cat .last_config | grep LINKAGE    | cut -d '=' -f2)

EQ_HARD_ARCH=$(shell [ -f ".last_config" ] && [ "$(HARD_ARCH)" = "$(LAST_HARD_ARCH)" ] && echo true)
EQ_MODE=$(shell      [ -f ".last_config" ] && [      "$(MODE)" = "$(LAST_MODE)"      ] && echo true)
EQ_WARNING=$(shell   [ -f ".last_config" ] && [   "$(WARNING)" = "$(LAST_WARNING)"   ] && echo true)
EQ_GPROF=$(shell     [ -f ".last_config" ] && [     "$(GPROF)" = "$(LAST_GPROF)"     ] && echo true)
EQ_GDB=$(shell       [ -f ".last_config" ] && [       "$(GDB)" = "$(LAST_GDB)"       ] && echo true)
EQ_LINKAGE=$(shell   [ -f ".last_config" ] && [   "$(LINKAGE)" = "$(LAST_LINKAGE)"   ] && echo true)

ifneq ($(EQ_HARD_ARCH),true)
	DEPEND=mrproper
endif

ifneq ($(EQ_MODE),true)
	DEPEND=mrproper
endif

ifneq ($(EQ_WARNING),true)
	DEPEND=mrproper
endif
		
ifneq ($(EQ_GPROF),true)
	DEPEND=mrproper
endif

ifneq ($(EQ_GDB),true)
	DEPEND=mrproper
endif

ifneq ($(EQ_LINKAGE),true)
	DEPEND=mrproper
endif

ifneq ($(HARD_ARCH),natif)
	CXX=$(CROSS_CXX)
	CC=$(CROSS_CC)
	CFLAGS+= $(CROSS_LIB)
	LDFLAGS+= $(CROSS_LINK)
	FLAGS+= $(CROSS_FLAGS)
else
	CFLAGS+= $(LIB)
	LDFLAGS+= $(LINK)
	FLAGS+= $(NATIF_FLAGS)
endif

ifeq ($(MODE),release)	
	FLAGS+= -D'MODE_RELEASE'
else	
	FLAGS+= -D'MODE_DEBUG'
endif

ifeq ($(LINKAGE),static)	
	FLAGS+= -static
endif

ifeq ($(WARNING),all)
	FLAGS+= -Wall -Wshadow -Wextra -fexecptions
else ifeq ($(WARNING), none)
	FLAGS+= -w
endif

ifeq ($(PTHREAD),on)
	FLAGS+= -pthread
endif

ifeq ($(SDL1),on)
	FLAGS+= -lSDL
endif

ifeq ($(SDL2),on)
	FLAGS+= -lSDL2
endif

ifeq ($(GPROF),on)
	FLAGS+= -pg
	LDFLAGS+= -pg
endif

ifeq ($(GDB),on)
	FLAGS+= -g
	LDFLAGS+= -g
endif

ifeq ($(FULL_CPP),on)
	CC=$(CXX)
endif

CPP_SRC=$(shell find ./$(SOURCE_DIR) -name *.cpp)
CPP_OBJ=$(CPP_SRC:.cpp=.o)

C_SRC=$(shell find ./$(SOURCE_DIR) -name *.c)
C_OBJ=$(C_SRC:.c=.o)

OBJ=$(C_OBJ) $(CPP_OBJ)

all: $(ROOT_DIR) cible $(DEPEND) makedeps $(ROOT_DIR)/$(EXEC) .config $(ROOT_DIR)/$(OUTFOLDER)
	@echo "+=======================================+"
	@echo "|	\033[1;92mBuid done\033[0m			|"
	@echo "| for hard_arch : \033[1;92m$(shell file $(ROOT_DIR)/$(EXEC) | cut -d ',' -f2)\033[0m   		|"
	@echo "| in : \033[1;92m$(MODE)\033[0m mode 			|"
	@echo "+=======================================+"

$(ROOT_DIR):
	@$(shell [ -d "$(ROOT_DIR)" ] || mkdir -p "$(ROOT_DIR)" )

$(ROOT_DIR)/$(OUTFOLDER): $(ROOT_DIR)
	@$(shell [ ! -d "$(ROOT_DIR)/$(OUTFOLDER)" ] && mkdir -p "$(ROOT_DIR)/$(OUTFOLDER)" )

cible:
	@echo  > .last_config
	@echo "HARD_ARCH=$(HARD_ARCH)" >> .last_config
	@echo "TARGET=$(TARGET)" >> .last_config
	@echo "MODE=$(MODE)" >> .last_config
	@echo "WARNING=$(WARNING)" >> .last_config
	@echo "GPROF=$(GPROF)" >> .last_config
	@echo "GDB=$(GDB)" >> .last_config
	@echo "LINKAGE=$(LINKAGE)" >> .last_config
	
docs:
	@doxywizard doc/Doxyfile

$(ROOT_DIR)/$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)
%.o: %.cpp
	$(CXX) -c -o $@ $< $(FLAGS) $(CFLAGS)


clean:
	rm -f $(shell find ./$(SOURCE_DIR)/ -name *.o) $(shell find ./$(SOURCE_DIR)/ -name *.so)

cleanDoc:
	rm -f -r doc/html/*
	rm -f -r doc/latex/*
	rm -f -r doc/xml/*
	rm -f -r doc/man/*
	rm -f -r doc/rtf/*

cleanDump:	
	rm -f -r $(ROOT_DIR)/$(OUTFOLDER)/*

mrproper: clean cleanDump cleanDoc
	rm -f $(ROOT_DIR)/$(EXEC)

empty: mrproper
	@echo "#!/bin/bash" > script.sh
	@echo 'rm -r $$(ls -a | grep -v -E "^((configure)|(\.+)|(src)|(patch)|(res)|(.git))$$")' >> script.sh
	@chmod +x script.sh
	@./script.sh

makedeps:
	@makedepend -Y $(C_SRC) $(CPP_SRC) 2> /dev/null

.config:
	@[ ! -f .config ] && echo > .config

printEnv:
	@echo "LAST_HARD_ARCH="$(LAST_HARD_ARCH)
	@echo "LAST_MODE="$(LAST_MODE)
	@echo "LAST_WARNING="$(LAST_WARNING)
	@echo "LAST_GPROF="$(LAST_GPROF)
	@echo "LAST_GDB="$(LAST_GDB)
	@echo "LAST_LINKAGE="$(LAST_LINKAGE)
	@echo "HARD_ARCH="$(HARD_ARCH)
	@echo "MODE="$(MODE)
	@echo "WARNING="$(WARNING)
	@echo "GPROF="$(GPROF)
	@echo "LAST_GDB="$(LAST_GDB)
	@echo "LINKAGE="$(LINKAGE)
	@echo "EQ_HARD_ARCH="$(EQ_HARD_ARCH)
	@echo "EQ_MODE="$(EQ_MODE)
	@echo "EQ_WARNING="$(EQ_WARNING)
	@echo "EQ_GPROF="$(EQ_GPROF)
	@echo "EQ_GDB="$(EQ_GDB)
	@echo "EQ_LINKAGE="$(EQ_LINKAGE)# DO NOT DELETE

# DO NOT DELETE

./src/main.o: /home/pi/Documents/loudspeakerSoftware/src/settings.h
./src/main.o: /home/pi/Documents/loudspeakerSoftware/src/i2cChip.h
./src/main.o: /home/pi/Documents/loudspeakerSoftware/src/spiChip.h
./src/spiChip.o: /home/pi/Documents/loudspeakerSoftware/src/settings.h
./src/spiChip.o: /home/pi/Documents/loudspeakerSoftware/src/spiChip.h
./src/i2cChip.o: /home/pi/Documents/loudspeakerSoftware/src/settings.h
./src/i2cChip.o: /home/pi/Documents/loudspeakerSoftware/src/i2cChip.h
./src/i2cChip.o: /home/pi/Documents/loudspeakerSoftware/src/i2cCommands.h

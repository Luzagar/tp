#
# Generated By: dol2asm
#

M539_TARGET := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard.plf
M539_LDSCRIPT := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard.lcf
M539_MAP := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard.map

M539_CPP_FILES := \
	rel/executor.cpp \
	rel/global_destructor_chain.cpp \
	rel/d/a/obj/d_a_obj_lv5FloorBoard/d_a_obj_lv5FloorBoard.cpp \

M539_O_FILES := \
	$(BUILD_DIR)/rel/executor.o \
	$(BUILD_DIR)/rel/global_destructor_chain.o \
	$(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard/d_a_obj_lv5FloorBoard.o \

M539_LIBS := \

M539_CFLAGS := \
	-sdata 0 \
	-sdata2 0 \

M539_LDFLAGS := \
	-nodefaults \
	-fp hard \
	-proc gekko \
	-linkmode moreram \
	-sdata 0 \
	-sdata2 0 \
	-m _prolog \
	-lcf $(M539_LDSCRIPT) \
	-unused -map $(M539_MAP) \
	-w off \

$(M539_TARGET): $(M539_O_FILES) $(M539_LIBS)
	@echo [539] creating $(M539_TARGET)
	@echo $(M539_LIBS) $(M539_O_FILES) > build/M539_ofiles
	@python3 tools/lcf.py rel 539 --output $(M539_LDSCRIPT)
	@$(LD) -opt_partial -strip_partial $(M539_LDFLAGS) -o $(M539_TARGET) @build/M539_ofiles

$(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard/%.o: rel/d/a/obj/d_a_obj_lv5FloorBoard/%.cpp $(BUILD_DIR)/rel/d/a/obj/d_a_obj_lv5FloorBoard/%.d
	@echo [539] building $@
	@mkdir -p $(@D)
	@$(ICONV) -f UTF-8 -t CP932 < $< > $(basename $@).cpp
	@$(CC) $(CFLAGS) $(M539_CFLAGS) $(DEPFLAGS) -c -o $(dir $@) $(basename $@).cpp
	@if [ -z '$(DISABLE_DEPS)' ]; then tools/transform-dep.py '$(basename $@).d' '$(basename $@).d'; touch -c $@; fi

ifndef DISABLE_DEPS
M539_D_FILES := $(M539_O_FILES:.o=.d)
$(M539_D_FILES):
include $(wildcard $(M539_D_FILES))
endif



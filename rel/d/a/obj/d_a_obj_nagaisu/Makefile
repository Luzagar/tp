#
# Generated By: dol2asm
#

M580_TARGET := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu.plf
M580_LDSCRIPT := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu.lcf
M580_MAP := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu.map

M580_CPP_FILES := \
	rel/executor.cpp \
	rel/d/a/obj/d_a_obj_nagaisu/d_a_obj_nagaisu.cpp \

M580_O_FILES := \
	$(BUILD_DIR)/rel/executor.o \
	$(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu/d_a_obj_nagaisu.o \

M580_LIBS := \

M580_CFLAGS := \
	-sdata 0 \
	-sdata2 0 \

M580_LDFLAGS := \
	-nodefaults \
	-fp hard \
	-proc gekko \
	-linkmode moreram \
	-sdata 0 \
	-sdata2 0 \
	-m _prolog \
	-lcf $(M580_LDSCRIPT) \
	-unused -map $(M580_MAP) \
	-w off \

$(M580_TARGET): $(M580_O_FILES) $(M580_LIBS)
	@echo [580] creating $(M580_TARGET)
	@echo $(M580_LIBS) $(M580_O_FILES) > build/M580_ofiles
	@python3 tools/lcf.py rel 580 --output $(M580_LDSCRIPT)
	@$(LD) -opt_partial -strip_partial $(M580_LDFLAGS) -o $(M580_TARGET) @build/M580_ofiles

$(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu/%.o: rel/d/a/obj/d_a_obj_nagaisu/%.cpp $(BUILD_DIR)/rel/d/a/obj/d_a_obj_nagaisu/%.d
	@echo [580] building $@
	@mkdir -p $(@D)
	@$(ICONV) -f UTF-8 -t CP932 < $< > $(basename $@).cpp
	@$(CC) $(CFLAGS) $(M580_CFLAGS) $(DEPFLAGS) -c -o $(dir $@) $(basename $@).cpp
	@if [ -z '$(DISABLE_DEPS)' ]; then tools/transform-dep.py '$(basename $@).d' '$(basename $@).d'; touch -c $@; fi

ifndef DISABLE_DEPS
M580_D_FILES := $(M580_O_FILES:.o=.d)
$(M580_D_FILES):
include $(wildcard $(M580_D_FILES))
endif



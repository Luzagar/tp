#
# Generated By: dol2asm
#

M657_TARGET := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi.plf
M657_LDSCRIPT := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi.lcf
M657_MAP := $(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi.map

M657_CPP_FILES := \
	rel/executor.cpp \
	rel/d/a/obj/d_a_obj_thashi/d_a_obj_thashi.cpp \

M657_O_FILES := \
	$(BUILD_DIR)/rel/executor.o \
	$(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi/d_a_obj_thashi.o \

M657_LIBS := \

M657_CFLAGS := \
	-sdata 0 \
	-sdata2 0 \

M657_LDFLAGS := \
	-nodefaults \
	-fp hard \
	-proc gekko \
	-linkmode moreram \
	-sdata 0 \
	-sdata2 0 \
	-m _prolog \
	-lcf $(M657_LDSCRIPT) \
	-unused -map $(M657_MAP) \
	-w off \

$(M657_TARGET): $(M657_O_FILES) $(M657_LIBS)
	@echo [657] creating $(M657_TARGET)
	@echo $(M657_LIBS) $(M657_O_FILES) > build/M657_ofiles
	@python3 tools/lcf.py rel 657 --output $(M657_LDSCRIPT)
	@$(LD) -opt_partial -strip_partial $(M657_LDFLAGS) -o $(M657_TARGET) @build/M657_ofiles

$(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi/%.o: rel/d/a/obj/d_a_obj_thashi/%.cpp $(BUILD_DIR)/rel/d/a/obj/d_a_obj_thashi/%.d
	@echo [657] building $@
	@mkdir -p $(@D)
	@$(ICONV) -f UTF-8 -t CP932 < $< > $(basename $@).cpp
	@$(CC) $(CFLAGS) $(M657_CFLAGS) $(DEPFLAGS) -c -o $(dir $@) $(basename $@).cpp
	@if [ -z '$(DISABLE_DEPS)' ]; then tools/transform-dep.py '$(basename $@).d' '$(basename $@).d'; touch -c $@; fi

ifndef DISABLE_DEPS
M657_D_FILES := $(M657_O_FILES:.o=.d)
$(M657_D_FILES):
include $(wildcard $(M657_D_FILES))
endif



#
# Generated By: dol2asm
#

M757_TARGET := $(BUILD_DIR)/rel/d/a/d_a_warp_bug.plf
M757_LDSCRIPT := $(BUILD_DIR)/rel/d/a/d_a_warp_bug.lcf
M757_MAP := $(BUILD_DIR)/rel/d/a/d_a_warp_bug.map

M757_CPP_FILES := \
	rel/executor.cpp \
	rel/d/a/d_a_warp_bug/d_a_warp_bug.cpp \

M757_O_FILES := \
	$(BUILD_DIR)/rel/executor.o \
	$(BUILD_DIR)/rel/d/a/d_a_warp_bug/d_a_warp_bug.o \

M757_LIBS := \

M757_CFLAGS := \
	-sdata 0 \
	-sdata2 0 \

M757_LDFLAGS := \
	-nodefaults \
	-fp hard \
	-proc gekko \
	-linkmode moreram \
	-sdata 0 \
	-sdata2 0 \
	-m _prolog \
	-lcf $(M757_LDSCRIPT) \
	-unused -map $(M757_MAP) \
	-w off \

$(M757_TARGET): $(M757_O_FILES) $(M757_LIBS)
	@echo [757] creating $(M757_TARGET)
	@echo $(M757_LIBS) $(M757_O_FILES) > build/M757_ofiles
	@python3 tools/lcf.py rel 757 --output $(M757_LDSCRIPT)
	@$(LD) -opt_partial -strip_partial $(M757_LDFLAGS) -o $(M757_TARGET) @build/M757_ofiles

$(BUILD_DIR)/rel/d/a/d_a_warp_bug/%.o: rel/d/a/d_a_warp_bug/%.cpp $(BUILD_DIR)/rel/d/a/d_a_warp_bug/%.d
	@echo [757] building $@
	@mkdir -p $(@D)
	@$(ICONV) -f UTF-8 -t CP932 < $< > $(basename $@).cpp
	@$(CC) $(CFLAGS) $(M757_CFLAGS) $(DEPFLAGS) -c -o $(dir $@) $(basename $@).cpp
	@if [ -z '$(DISABLE_DEPS)' ]; then tools/transform-dep.py '$(basename $@).d' '$(basename $@).d'; touch -c $@; fi

ifndef DISABLE_DEPS
M757_D_FILES := $(M757_O_FILES:.o=.d)
$(M757_D_FILES):
include $(wildcard $(M757_D_FILES))
endif



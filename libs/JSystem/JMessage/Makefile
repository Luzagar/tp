#
# Generated By: dol2asm
#

LIBJMESSAGE_A_CPP_FILES := \
	libs/JSystem/JMessage/control.cpp \
	libs/JSystem/JMessage/data.cpp \
	libs/JSystem/JMessage/processor.cpp \
	libs/JSystem/JMessage/resource.cpp \
	libs/JSystem/JMessage/locale.cpp \

LIBJMESSAGE_A_O_FILES := \
	$(BUILD_DIR)/libs/JSystem/JMessage/control.o \
	$(BUILD_DIR)/libs/JSystem/JMessage/data.o \
	$(BUILD_DIR)/libs/JSystem/JMessage/processor.o \
	$(BUILD_DIR)/libs/JSystem/JMessage/resource.o \
	$(BUILD_DIR)/libs/JSystem/JMessage/locale.o \

LIBJMESSAGE_A_CFLAGS := \

LIBJMESSAGE_A_LDFLAGS := \
	-nodefaults \
	-fp hard \
	-proc gekko \
	-linkmode moreram \

$(BUILD_DIR)/libJMessage.a: $(LIBJMESSAGE_A_O_FILES)
	@echo linking... $(BUILD_DIR)/libJMessage.a
	@echo $(LIBJMESSAGE_A_O_FILES) > build/LIBJMESSAGE_A_ofiles
	@$(LD) -xm l $(LIBJMESSAGE_A_LDFLAGS) -o $(BUILD_DIR)/libJMessage.a @build/LIBJMESSAGE_A_ofiles

$(BUILD_DIR)/libs/JSystem/JMessage/%.o: libs/JSystem/JMessage/%.cpp $(BUILD_DIR)/libs/JSystem/JMessage/%.d
	@mkdir -p $(@D)
	@echo building... $<
	@$(ICONV) -f UTF-8 -t CP932 < $< > $(basename $@).cpp
	@$(CC) $(CFLAGS) $(LIBJMESSAGE_A_CFLAGS) $(DEPFLAGS) -c -o $(dir $@) $(basename $@).cpp
	@if [ -z '$(DISABLE_DEPS)' ]; then tools/transform-dep.py '$(basename $@).d' '$(basename $@).d'; touch -c $@; fi

ifndef DISABLE_DEPS
LIBJMESSAGE_A_D_FILES := $(LIBJMESSAGE_A_O_FILES:.o=.d)
$(LIBJMESSAGE_A_D_FILES):
include $(wildcard $(LIBJMESSAGE_A_D_FILES))
endif


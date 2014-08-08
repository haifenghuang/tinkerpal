MAJOR_VERSION=0
MINOR_VERSION=1
PATCH_VERSION=3

HOST_OS=$(shell uname)

BUILD?=build.$(HOST_OS)
STAGING=staging.$(HOST_OS)
BSPS_DIR?=$(STAGING)/bsps

ifeq ($(V),1)
    quiet_=
    Q=
else
    quiet_=quiet_
    Q=@
endif

# Do not:
# o  use make's built-in rules and variables
#    (this increases performance and avoids hard-to-debug behaviour);
# o  print "Entering directory ...";
MAKEFLAGS += -rR --no-print-directory

all : _all

build_dir:
	@mkdir -p $(BUILD)

$(BSPS_DIR)/.fetched:
	@echo "Fetching BSPs"
	@git clone git://github.com/ebirger/tinkerpal_bsps.git $(BSPS_DIR)
	@touch $(BSPS_DIR)/.fetched

FETCH_BSPS:=$(BSPS_DIR)/.fetched

ifeq ($(wildcard $(BUILD)/auto.conf),)
# auto.conf is not ready. Create it and recursively call make once auto.conf is created

_all: build_dir $(BUILD)/auto.conf $(BSPS_DIR)/.fetched
	@make BUILD=$(BUILD)

else

# auto.conf is ready. actually build the target

include $(BUILD)/auto.conf

include scripts/Makefile.toolchain

include scripts/text_to_c.mk

d=.

MK_SUBDIRS=apps main platform mem util boards
MK_SUBDIRS+=$(if $(CONFIG_JS),js)
MK_SUBDIRS+=$(if $(CONFIG_NET),net)
MK_SUBDIRS+=$(if $(CONFIG_USB),usb)
MK_SUBDIRS+=$(if $(CONFIG_GRAPHICS),graphics)
MK_SUBDIRS+=drivers
# vfs must be last since builtin fs aggregates files from other drivers
MK_SUBDIRS+=$(if $(CONFIG_VFS),fs)

include scripts/Rules.mk

include scripts/footer.mk

# Pull in calculated dependencied from previous build
$(call include_deps)

TARGET=$(BUILD)/$(TARGET_NAME)
IMAGE=$(BUILD)/$(IMAGE_NAME)

_all: $(BSPS_DIR)/.fetched $(IMAGE) $(BUILD)/auto.conf
  
clean: 
	$(Q)$(RM) $(TARGET) $(IMAGE) $(OBJS) $(AUTO_GEN_FILES) $(OBJS:.o=.d) $(LINK_DEPS)

endif

include scripts/Makefile.config

ifneq ($(wildcard $(BUILD)),)

distclean: 
	$(RM) -rf $(BUILD)

endif

docs:
	@make BUILD=$(BUILD) -f doc/Makefile

# Build rules

# do not discard intermediate targets
.SECONDARY:

quiet_compile= CC $@
quiet_link= LD $@
quiet_obj_to_bin= GEN $@

$(BUILD)/version_data.h :
	@echo "GEN $@"
	@echo "/* Automatically generated version file, DO NOT MANUALLY EDIT */" > $@
	@echo "#ifndef __TINKERPAL_VERSION_DATA_H___" >> $@
	@echo "#define __TINKERPAL_VERSION_DATA_H___" >> $@
	@echo "#define TINKERPAL_VERSION \"$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)\"" >> $@
	@echo "#define TINKERPAL_MAJOR_VERSION $(MAJOR_VERSION)" >> $@
	@echo "#define TINKERPAL_MINOR_VERSION $(MINOR_VERSION)" >> $@
	@echo "#define TINKERPAL_PATCH_VERSION $(PATCH_VERSION)" >> $@
	@echo "#endif" >> $@

$(BUILD)/descs.h: $(DESCS) $(BUILD)/autoconf.h
	@echo "GEN $@"
	@echo "/* Automatically generated file, DO NOT MANUALLY EDIT */" > $@
	@cat $^ >> $@

$(BUILD)/%.o : %.c $(BUILD)/autoconf.h $(BUILD)/version_data.h $(BUILD)/descs.h
	@echo $($(quiet_)compile)
	@$(call compile)
	@$(call calc_deps)

$(BUILD)/%.o : $(BUILD)/%.c $(BUILD)/autoconf.h $(BUILD)/version_data.h $(BUILD)/descs.h
	@echo $($(quiet_)compile)
	@$(call compile)
	@$(call calc_deps)

$(TARGET) : $(OBJS) $(LINK_DEPS)
	@echo $($(quiet_)link)
	@$(call link)

$(IMAGE) : $(TARGET)
	@echo $($(quiet_)obj_to_bin)
	@$(call obj_to_bin)

define note
	@printf *********************************************************\\n
	@printf $1\\n
	@printf *********************************************************\\n
endef

burn : $(BURNER)
ifneq ($(BURN_CMD),)
	$(if $(BURN_NOTE),$(call note,$(BURN_NOTE)))
	@sudo $(BURN_CMD)
else
	$(error burn command not available)
endif

simulate :
ifneq ($(SIMULATE_CMD),)
	$(if $(SIMULATE_NOTE),$(call note,$(SIMULATE_NOTE)))
	@$(SIMULATE_CMD)
else
	$(error simulate command not available)
endif

.PHONY: build_dir _all docs burn

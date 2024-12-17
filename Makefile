MAKEFLAGS += --no-print-directory

DEPS := ovmf=https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd efi=https://github.com/aurixos/efi/archive/refs/heads/main.zip
DEPS_DIR := deps
TMP_DIR := $(shell mktemp -d)

BIN_DIR := bin
BOOTLOADER_DIR := bootloader

TARGET_BOOTLOADER := $(BIN_DIR)/BOOTX64.efi

OVMF := $(DEPS_DIR)/ovmf/RELEASEX64_OVMF.fd
ROOT_DIR := $(shell pwd)

all: $(TARGET_BOOTLOADER)

.PHONY: cleanup_tmp
cleanup_tmp:
	@rm -rf $(TMP_DIR)

define DOWNLOAD_template
deps-download-$(1):
	@if [ ! -d $(DEPS_DIR)/$(1) ]; then \
		mkdir -p $(DEPS_DIR)/$(1); \
		if [ "$(2)" = ".zip" ]; then \
			curl -Ls $(3) -o $(TMP_DIR)/$(1).zip && \
			unzip -o -q $(TMP_DIR)/$(1).zip -d $(TMP_DIR) && \
			mv $(TMP_DIR)/*/* $(DEPS_DIR)/$(1) && \
			$(MAKE) cleanup_tmp; \
		else \
			curl -Ls $(3) -o $(DEPS_DIR)/$(1)/$(notdir $(3)) || { echo "Error downloading $(3)"; exit 1; }; \
		fi; \
	else \
		echo "Directory $(DEPS_DIR)/$(1) already exists, skipping download"; \
	fi
endef

$(foreach DEP,$(DEPS),$(eval $(call DOWNLOAD_template,$(word 1,$(subst =, ,$(DEP))),$(suffix $(word 2,$(subst =, ,$(DEP)))),$(word 2,$(subst =, ,$(DEP))))))

.PHONY: deps-download-all
deps-download-all: $(foreach DEP,$(DEPS),deps-download-$(word 1,$(subst =, ,$(DEP))))

$(TARGET_BOOTLOADER): $(BOOTLOADER_DIR)/boot.efi | $(BIN_DIR)
	@cp $(BOOTLOADER_DIR)/boot.efi $(TARGET_BOOTLOADER)

$(TARGET_TEST): kernel

$(OVMF): deps-download-ovmf

$(BOOTLOADER_DIR)/boot.efi: bootloader
	@$(MAKE) -C $(BOOTLOADER_DIR) ROOT=$(ROOT_DIR) DEPS_DIR=$(DEPS_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

.PHONY: setup
setup: $(BIN_DIR)

.PHONY: bootloader
bootloader: deps-download-efi
	@$(MAKE) -C $(BOOTLOADER_DIR)

.PHONY: test
test: | $(TARGET_BOOTLOADER) $(OVMF)
	dd if=/dev/zero of=boot.img bs=1M count=64
	mkfs.fat -F 32 -n EFI_SYSTEM boot.img
	mmd -i boot.img ::/EFI ::/EFI/BOOT
	mcopy -i boot.img $(TARGET_BOOTLOADER) ::/EFI/BOOT/BOOTX64.efi
	@qemu-system-x86_64 -m 2G -drive if=pflash,format=raw,readonly=on,file=$(OVMF) -drive if=ide,format=raw,file=boot.img -debugcon stdio

.PHONY: clean
clean:
	@$(MAKE) -C $(BOOTLOADER_DIR) clean
	@rm -rf $(BIN_DIR) mnt boot.img $(DEPS_DIR)

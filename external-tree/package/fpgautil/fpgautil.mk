FPGAUTIL_VERSION = 1.0
FPGAUTIL_SITE = $(BR2_EXTERNAL_EDU_PATH)/package/fpgautil
FPGAUTIL_SITE_METHOD = local

define FPGAUTIL_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define FPGAUTIL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/fpgautil $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))

################################################################################
#
# epa
#
################################################################################

EPA_VERSION = 0.1.0
EPA_SITE = $(BR2_EXTERNAL_EPA_PATH)/..
EPA_SITE_METHOD = local
EPA_LICENSE = MIT
EPA_LICENSE_FILES = LICENSE
EPA_INSTALL_STAGING = NO

define EPA_INSTALL_INIT_CMDS
	# EPA is its own init - no external init system is used.
	rm -f $(TARGET_DIR)/sbin/init
	ln -sf ../usr/bin/epa-init $(TARGET_DIR)/sbin/init
endef

define EPA_POST_INSTALL_TARGET
	$(EPA_INSTALL_INIT_CMDS)
endef

EPA_TARGET_FINALIZE_HOOKS += EPA_POST_INSTALL_TARGET

$(eval $(cmake-package))

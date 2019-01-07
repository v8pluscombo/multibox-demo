KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-v8 = "4.4.35"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-v8"
PREFERRED_PROVIDER_virtual/egl ?= "v8-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "v8-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "v8-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libopencl ?= "v8-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "v8-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "v8-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"

# require conf/machine/include/arm/arch-armv8.inc
require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/v8-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

# Qt
PACKAGECONFIG_GL_pn-qtbase = "no-opengl linuxfb"

# Kodi
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali"

MACHINE_EXTRA_RRECOMMENDS = " \
	ffmpeg \
	ntfs-3g \
	"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "v8"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_v8fastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.v8fastboot8gb.gz ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.fastboot.gz; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/update_bootargs_v8plus.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/update_bootargs_v8plus.bin; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/${MACHINE}/bootargs-8gb.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/v8-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/logo.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"
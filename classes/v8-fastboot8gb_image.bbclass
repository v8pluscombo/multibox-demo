inherit image_types

IMAGE_TYPEDEP_v8fastboot8gb = "ext4"
IMAGE_ROOTFS_SIZE = "1048576"

do_image_v8fastboot8gb[depends] = " \
	android-tools-native:do_populate_sysroot \
	"

IMAGE_CMD_v8fastboot8gb () {
	ext2simg -zv ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.v8fastboot8gb.gz
}
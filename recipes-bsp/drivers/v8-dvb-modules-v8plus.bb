KV = "4.4.35"
SRCDATE = "20181023"

PROVIDES = "virtual/blindscan-dvbs"

require v8-dvb-modules.inc

SRC_URI[md5sum] = "7755cbcbbe3349e515e8be1455cb78ce"
SRC_URI[sha256sum] = "3a154e8dcecca9b9da165bd52a3966e6d556d10839b01ae5e51b83c5abd5e1b1"

COMPATIBLE_MACHINE = "v8plus"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

/usr/bin/turnoff_power
EOF
}

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"

INSANE_SKIP_${PN} += "already-stripped"
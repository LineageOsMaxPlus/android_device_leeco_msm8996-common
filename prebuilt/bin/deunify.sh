#!/sbin/sh
#
# deunify
#

# DEVINFO
DEVINFO=$(cat /dev/block/sde21)

echo "DEVINFO: ${DEVINFO}"

case "$DEVINFO" in
  max_plus*)
    # Move firmware
    mv -f /vendor/firmware/max_plus/* /vendor/firmware/
    ;;

  le_x2*)
    # Remove NFC perms
    rm -f /vendor/etc/permissions/android.hardware.nfc*
    rm -f /vendor/etc/permissions/com.android.nfc*
    rm -f /vendor/etc/permissions/com.nxp.mifare.xml

    # Remove NFC services
    rm -f /vendor/etc/init/android.hardware.nfc*
    rm -f /vendor/etc/init/vendor.nxp.hardware.nfc*

    # Remove SmartcardService
    rm -f /system/etc/permissions/org.simalliance.openmobileapi.xml
    rm -f /system/framework/org.simalliance.openmobileapi.jar
    rm -rf /vendor/app/SmartcardService
    ;;

  le_zl0*)
    # Move firmware
    mv -f /vendor/firmware/zl0/* /vendor/firmware/

    # Remove NFC perms
    rm -f /vendor/etc/permissions/android.hardware.nfc*
    rm -f /vendor/etc/permissions/com.android.nfc*
    rm -f /vendor/etc/permissions/com.nxp.mifare.xml

    # Remove NFC services
    rm -f /vendor/etc/init/android.hardware.nfc*
    rm -f /vendor/etc/init/vendor.nxp.hardware.nfc*

    # Remove SmartcardService
    rm -f /system/etc/permissions/org.simalliance.openmobileapi.xml
    rm -f /system/framework/org.simalliance.openmobileapi.jar
    rm -rf /vendor/app/SmartcardService
    ;;

  *)
    echo "Nothing to do!"
    ;;
esac

exit 0

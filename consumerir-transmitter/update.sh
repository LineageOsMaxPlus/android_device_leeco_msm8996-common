#!/usr/bin/env bash

adb root
adb remount
adb push ./build/outputs/apk/debug/ConsumerirTransmitter.apk /system/priv-app/ConsumerirTransmitter

adb reboot

# GEONIX REV.2.5 (Open-Source Port)

A 40% wireless keyboard supporting BLE, 2.4 GHz, and USB modes.

This is an open-source port of the GEONIX REV.2.5 firmware, replacing the
original closed-source `librdrcommon.a` with
[carlosedp's `rdmctmzt_common` library](https://github.com/carlosedp/qmk_firmware/tree/geonixr2).

* Keyboard Maintainer: [bofhgit](https://github.com/bofhgit)
* Hardware Supported: GEONIX REV.2.5 PCB with ES32 FS026 microcontroller
* Hardware Availability: GEONIX REV.2.5

Make example for this keyboard (after setting up your build environment):

    make geonix40/geonix40_oss:vial

Flashing example for this keyboard:

    make geonix40/geonix40_oss:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (TAB key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB

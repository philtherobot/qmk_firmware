# handlebar

![handlebar](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Philippe Payant](https://github.com/Philippe Payant)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make handlebar:default

Flashing example for this keyboard:

    make handlebar:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

# Firmware

```
qmk --help
qmk new-keyboard
qmk compile -kb handlebar -km default
``` 

I answered that the MCU was Elite-C (option 7). The Elite-C has an Atmega32u4 and flashes with DFU.

I picked split 3x5 (not sure) keyboard layout.

## Flashing instructions

- Launch QMK MSYS.
- To build: `qmk compile -kb handlebar -km default`
- To lint: `qmk lint -kb handlebar`
- Start QMK Toolbox
- File is at `$QMK/handlebar_default.hex`
- Connect the USB
- Wait for QMK Toolbox to see the connection
- Press Reset, wait 8 seconds
- Click `Flash`.

Updated instructions:
- Start QMK Toolbox
- File is at `$QMK/handlebar_default.hex`, select it
- Set Auto Flash
- Plug in the USB in slave side
- It should start flashing right away
- Plug in the USB in the master side
- Press Reset
- 8 seconds later the flashing starts.


> DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
>                 ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)


> I dunno man, that's not it at all!

We are ROW2COL, the diagram is like that:  

```
row -------
          |
            \  switch
          |  
          |    anode
          V    
          |    cathode
col -------
```

> Dude, what were you smoking?

BUT the correct config is COL2ROW (!??)

If I installed them in the right orientation, it will work!

The suggested diagram is to scan columns and read rows, place the diode after the switch, the line facing the row. The QMK explanation says that the scanning column, the line, will be set to "1", so we can assume that's positive voltage.

My board has the diode in this exact orientation, the line is facing the row. It also placed after the switch. The columns go to the pins.

So my diagram is correct, it was my analysis of things that led me to think it was ROW2COL.

```
row -------
          |    anode
          ^
          |    cathode
            /  switch
          |
col -------
```

Rows, top to bottom:
- nums, D4
- top, C6
- home, D7
- bottom, E6
- thumb, B2

Columns, left to right:
- pinky, F5
- ring, F6
- middle, F7
- index, B1
- inner, B3


# TODO

[X] Roll / to .
[X] Move SPC and ENT inward
[X] Add working indicator
[X] Add a `UC_NEXT` key to move through the Unicode input methods
[X] Consider the dash/underscore move to %/^
[X] Consider the quote/dquot move to SYM
[X] Turn off the Elite LEDs
[X] Add QMK_RESET
[X] Debug why sometimes the Caps LED is in the wrong state
[X] Add Ctrl-Tab and Alt-Tab to the Fn layer
[X] Volume and track controls do not work

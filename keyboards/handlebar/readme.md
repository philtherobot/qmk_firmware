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
qmk flash -kb handlebar -km default
``` 

I answered that the MCU was Elite-C (option 7). The Elite-C has an Atmega32u4 and flashes with DFU.

I picked split 3x5 (not sure) keyboard layout.

## Flashing instructions

- Launch QMK MSYS.
- To build: `qmk compile -kb handlebar -km default`
- To lint: `qmk lint -kb handlebar`
- Windows:
  - Start QMK Toolbox
  - File is at `$QMK/handlebar_default.hex`
  - Connect the USB
  - Wait for QMK Toolbox to see the connection
  - Press Reset, wait 8 seconds
  - Click `Flash`.
- Linux:
  - Connect the USB
  - Press Reset, wait 8 seconds
  - `qmk flash -kb handlebar -km default`
 

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


# Test table

Aside from the obvious keys of course...

Ctl + Alt + Del
Alt + spc
Win + D (and other letters such as V and E)
Win + Shf + S
Media keys
Alt + Tab (including holding Alt and repeating Tab)
Alt + Shf + Tab
Ctl + Tab (including holding Ctl and repeating Tab)
Ctl + Shf + Tab
Ctl + Alt + arrows (for multiple cursors)
Ctl + '-' '+' '=' (zooming)
Ctl + [letter, number or Fx]
Ctl + Fx
Shf + Fx
Alt + Fx
PrintScreen
ScrollLock
Pause


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
[X] RAlt cannot be used to access WinCompose
[ ] Indicator when we are on the Linux Unicode mode (UC_NEXT)


# Next generation

Mostly upgrades to handlebar.

See the Naya Create. 

The thumb keys should have their front facing edge sculpted to not have a sharp edge.

For handlebar, Ctrl-Alt is hard, Ctrl and Alt are on the same side. They should be opposed.

I might want to have Win at the thumb, but really, it is not used that much.

Also, I might consider putting Extend at the thumb. That is used a lot anc having a stronger finger, the thumb, for this would a good eregonomic choice.

I want a case this time. 

On the Extent layer, I want to have access to the following normal keys: 
- comma
- dot
- semi-colon
- parens
- braces
- Enter

This is for when I am on the Extend layer, locked, for extensive editing, I can add a few symbols to complete the edits. It never is new identifiers, but commas and braces are often needed. Maybe I should swap Extend and Alt. But this meshes with the changes to Alt and Fn, see below.

Wheel mouse support. Maybe on Extend, on the far left, use "0" and" "\". Or Fn.

## Opposed Ctrl and Alt


The secret sauce to have all the combos doable with two separate hands is to use four keys, versus the minimal three. Basically, you choose one key that is on both sides and the other two are on opposite sides. Easiest is to have Shift both sides:

```
Ctrl  Spc  Shf         _1_ Ent _2_
              ___   Shf
```

Alt can go at either positions "1" or "2".

Ctrl and Shift are already in good positions, Space and Enter have to stay.  Alt has simply to go on the other side:

```
Ctrl  Spc  Shf         Sym Ent Alt
              Fn   Shf
```

Now we want Extend to be on the thumb. We have to kick out Fn, placing Fn at the left pinky. On the Extend layer, Tab is also relocated to the left pink, its historic position.


## Mouse support

I am getting better at navigating without the mouse, but at least in the Telesat environment, the web browsers have no easy keyboard navigation. Tools much as both mouseless software do not play well with Remote Desktop. Some parts of important software such as VS Code do not have great keyboard support. So maybe after some more experimentation and learning (June 2025), we will learn that I do no need the mouse enough after all or that mouse use is still too frequent.

If mouse use is too frequent, we can add a pointing stick. They are cheap. Place it at the right middle finger, right and below the N. Squeeze in a small wheel mouse (it could be a touchpad) left of the J and M, on a diagonal to fit the layout of the right index finger will reach out to it.

A pointing stick needs a "wheel scroll" button. Plan for that.

Mouse buttons, I am not sure yet. Some experimentation needs to take place. But here are two ideas.

One, place vertical buttons at the edge of the right Shift, two could probably fit. 

Or option two, place them on the left side, right of G and V.

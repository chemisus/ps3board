# PS3 Board

Author: Terrence Howard <<chemisus@gmail.com>>

-----------
## Summary

PS3 Board gives the operator the ability to use their PS3 controller as a 
keyboard and mouse combination on their computer.

## Requirements

As of right now, the only computer that the program has been tested on has
the following specs:
* ASUS N53SV-XV1 Laptop
* Fedora 18 (KDE)
* Kernel: 3.8.4-202.fc18.x86_64
* gcc (GCC) 4.7.2

## Compiling

Right now I am currently using Netbeans 7.3 with the c++ plugin.
The additional parameters required to compile are:

    -L/usr/X11R6/lib -lX11

## Usage

At the moment, the controller is not a full replacement for a keyboard.
That being said, as long as you are not writing code with it, it is for
the most part usable.

The following is a basic representation of the controls:
* Enter: [start]
* Escape: [select]
* Control: [R2]
* Shift: [L2]
* Alt: [PS3]
* Up: [D-Up]
* Left: [D-Left]
* Right: [D-Right]
* Down: [D-Down]
* Page Up: [R2 + D-Up]
* Page Down: [R2 + D-Down]
* Home: [R2 + D-Left]
* End: [R2 + D-Right]
* Move Mouse: [Right Analog]
* Left Click: [L3]
* Right Click: [R3]
* Space: [R1]
* Backspace: [L1]

Now, for the fun part: Typing!

The current setup for typing is using a combination of the [Left Analog] and
[Triangle], [Circle], [Square], or [X] buttons.

There are currently two required and one optional steps to provide a keystroke.

0. (optional) Press [R2] or [L1] for Shift or Ctrl functionality.
1. move and hold the [Left Analog] into the correct position (positions to be shown later in the document). 
2. press and release one of the [Triangle], [Circle], [Square], or [X] buttons.
3. (optional) release the [Left Analog] joystick.

### Positions of [Left Analog]

The [Left Analog] has been divided into a table of 3 rows with 3 columns.
The table starts from the **BOTTOM LEFT**, just as a calculator or the number
pad does.

Just so were on the same page as the positions of the [Left Analog], the following
is an ASCII representation:

    7 8 9
    4 5 6
    1 2 3

### Typing

In order to understand how the characters are mapped, you must understand the positions of the [Left Analog].

Each of the four buttons, [Triangle], [Circle], [Square], or [X], currently has nine characters mapped to them.
The character selected out of the nine depends on the position of the [Left Analog] at the time of pressing
the [Triangle], [Circle], [Square], or [X] button.

For example, to enter the letter "t", move the [Left Analog] to the 8th position (directly up) and press [X].
This combination can be referred to as < 8X >, representing the 8th position on the [Left Analog] map and the [X] button.

The following are the shorthand representations for the buttons:

* X = [X]
* T = [Triangle]
* C = [Circle]
* S = [Square]

The following are a few examples of combinations, and their results:

    <8X> t
    <8X> h
    <8X> i
    <8X> s
    [R1] (space)
    <8X> i
    <8X> s
    [R1] (space)
    <8X> a
    [R1] (space)
    <8X> t
    <5X> e
    <3x> s
    <8X> t
    <5C> .

will result in the following: "this is a test."

### Character Maps

The following are the mappings for the buttons:

#### [X]

    a t n
    h e i
    o s r
    
#### [Square]

    l d c
    m u w
    f g y

#### [Circle]

    b k v
    q . x
    p j z

#### [Triangle]

    7 8 9
    4 5 6
    1 2 3

## Shortcuts (copy, paste, save, etc.)

It is possible to do the traditional shortcuts like on a keyboard.

* Hold the control button [R2]
* Move the [Left Analog] into the correct page.
* Press the appropriate mapping.

For example:

    R2 + <2X> --> ctrl+s

## Known Issues

There are of course going to be issues with a new project. Some of the following are ones I hope to soon resolve:

* No zero key available.
* Can not click and focus into another window.


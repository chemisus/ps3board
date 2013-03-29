/* 
 * File:   main.cpp
 * Author: chemisus
 *
 * Created on March 28, 2013, 6:37 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "Pager.h"
#include "CartesianPager.h"
#include "Joystick.h"
#include "JoystickPacket.h"

#define DEVICE "/dev/input/js0"

#define TABLE_BUTTON 1
#define TABLE_SENSOR 2

using namespace std;


/*
 * 
 */
int main(int argc, char** argv)
{
    FILE* stream = fopen(DEVICE, "rb");

    Display *display = XOpenDisplay(0);

    Pager *pager = new CartesianPager();

    Joystick joystick(display, pager);

    JoystickPacket packet;
    
    while (true) {
        if (!feof(stream)) {
            packet.read(stream);

            if (packet.table() == TABLE_BUTTON) {
                joystick.button(packet.event(), packet.value());
            }
            else if (packet.table() == TABLE_SENSOR) {
                joystick.sensor(packet.event(), packet.value());
            }
        }

        joystick.updateMouse();

        XFlush(display);
    }

    XCloseDisplay(display);
    delete pager;
    
    return 0;
}


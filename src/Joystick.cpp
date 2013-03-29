/* 
 * File:   Joystick.cpp
 * Author: chemisus
 * 
 * Created on March 28, 2013, 6:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <math.h>
#include "Pager.h"
#include "CartesianPager.h"
#include "Joystick.h"

#define BUTTON_SELECT 0
#define BUTTON_L3 1
#define BUTTON_R3 2
#define BUTTON_START 3
#define BUTTON_UP 4
#define BUTTON_RIGHT 5
#define BUTTON_DOWN 6
#define BUTTON_LEFT 7
#define BUTTON_L2 8
#define BUTTON_R2 9
#define BUTTON_L1 10
#define BUTTON_R1 11
#define BUTTON_TRIANGLE 12
#define BUTTON_CIRCLE 13
#define BUTTON_X 14
#define BUTTON_SQUARE 15
#define BUTTON_PS3 16

#define SENSOR_LA_H 0
#define SENSOR_LA_V 1
#define SENSOR_RA_H 2
#define SENSOR_RA_V 3

#define STATE_SHIFT 0x1
#define STATE_CTRL 0x4
#define STATE_ALT 0x8

#define MOUSE_H SENSOR_RA_H
#define MOUSE_V SENSOR_RA_V

#define KEY_SHIFT BUTTON_L2
#define KEY_CTRL BUTTON_R2
#define KEY_ALT BUTTON_PS3
#define KEY_HOME BUTTON_LEFT
#define KEY_END BUTTON_RIGHT
#define KEY_PAGEUP BUTTON_UP
#define KEY_PAGEDOWN BUTTON_DOWN
#define KEY_UP BUTTON_UP
#define KEY_DOWN BUTTON_DOWN
#define KEY_LEFT BUTTON_LEFT
#define KEY_RIGHT BUTTON_RIGHT
#define KEY_TAB BUTTON_R1
#define KEY_ENTER BUTTON_START
#define KEY_ESCAPE BUTTON_SELECT
#define KEY_SPACE BUTTON_R1
#define KEY_BACKSPACE BUTTON_L1
#define KEY_CLICK_LEFT BUTTON_L3
#define KEY_CLICK_RIGHT BUTTON_R3

#define PI 3.14159265359
#define PI_8 0.39269908169
#define PI_16 0.19634954084

Joystick::Joystick(Display *display, Pager *pager)
{
    this->display = display;
    this->pager = pager;

    for (int i = 0; i < 17; i++) {
        buttons[i] = false;
    }

    for (int i = 0; i < 27; i++) {
        sensors[i] = 0;
    }
}

Joystick::~Joystick()
{
}

int Joystick::state()
{
    return (pressed(KEY_CTRL) ? STATE_CTRL : 0) |
            (pressed(KEY_SHIFT) ? STATE_SHIFT : 0) |
            (pressed(KEY_ALT) ? STATE_ALT : 0);
}

bool Joystick::pressed(int button)
{
    return buttons[button] == 1;
}

int Joystick::page()
{
    return pager->page(sensors[SENSOR_LA_H], sensors[SENSOR_LA_V]);
}

int Joystick::keycode(int button)
{
    int pad = button - BUTTON_TRIANGLE;
    int shift = buttons[KEY_SHIFT];

    return keycodes[shift][pad][page()];
}

void Joystick::home(bool pressed)
{
    sendKey(XK_Home, 0, pressed);
}

void Joystick::end(bool pressed)
{
    sendKey(XK_End, 0, pressed);
}

void Joystick::pageUp(bool pressed)
{
    sendKey(XK_Page_Up, 0, pressed);
}

void Joystick::pageDown(bool pressed)
{
    sendKey(XK_Page_Down, 0, pressed);
}

void Joystick::left(bool pressed)
{
    sendKey(XK_Left, 0, pressed);
}

void Joystick::right(bool pressed)
{
    sendKey(XK_Right, 0, pressed);
}

void Joystick::up(bool pressed)
{
    sendKey(XK_Up, 0, pressed);
}

void Joystick::down(bool pressed)
{
    sendKey(XK_Down, 0, pressed);
}

void Joystick::tab(bool pressed)
{
    sendKey(XK_Tab, state(), pressed);
}

void Joystick::enter(bool pressed)
{
    sendKey(XK_Return, state(), pressed);
}

void Joystick::escape(bool pressed)
{
    sendKey(XK_Escape, state(), pressed);
}

void Joystick::space(bool pressed)
{
    sendKey(XK_space, state(), pressed);
}

void Joystick::backspace(bool pressed)
{
    sendKey(XK_BackSpace, state(), pressed);
}

void Joystick::clickLeft(bool pressed)
{
    sendClick(1, 0, pressed);
}

void Joystick::clickRight(bool pressed)
{
    sendClick(3, 0, pressed);
}

void Joystick::button(int button, bool value)
{
    buttons[button] = value;

    switch (button) {
    case BUTTON_TRIANGLE:
    case BUTTON_SQUARE:
    case BUTTON_CIRCLE:
    case BUTTON_X:
        sendKey(keycode(button), state(), pressed(button));
        return;
    }

    if (pressed(KEY_CTRL)) {
        switch (button) {
        case KEY_PAGEUP:
            pageUp(pressed(button));
            return;
        case KEY_PAGEDOWN:
            pageDown(pressed(button));
            return;
        case KEY_HOME:
            home(pressed(button));
            return;
        case KEY_END:
            end(pressed(button));
            return;
        case KEY_BACKSPACE:
            backspace(pressed(button));
            return;
        }
    }

    if (pressed(KEY_SHIFT)) {
        switch (button) {
        case KEY_TAB:
            tab(pressed(button));
            return;
        }
    }

    switch (button) {
    case KEY_CLICK_LEFT:
        clickLeft(pressed(button));
        return;
    case KEY_CLICK_RIGHT:
        clickRight(pressed(button));
        return;
    case KEY_UP:
        up(pressed(button));
        return;
    case KEY_DOWN:
        down(pressed(button));
        return;
    case KEY_LEFT:
        left(pressed(button));
        return;
    case KEY_RIGHT:
        right(pressed(button));
        return;
    case KEY_ENTER:
        enter(pressed(button));
        return;
    case KEY_ESCAPE:
        escape(pressed(button));
        return;
    case KEY_SPACE:
        space(pressed(button));
        return;
    case KEY_BACKSPACE:
        backspace(pressed(button));
        return;
    case KEY_SHIFT:
        sendKey(XK_Shift_L, state(), pressed(button));
        return;
    case KEY_CTRL:
        sendKey(XK_Control_L, state(), pressed(button));
        return;
    case KEY_ALT:
        sendKey(XK_Alt_L, state(), pressed(button));
        return;
    }
}

void Joystick::sensor(int sensor, int16_t value)
{
    sensors[sensor] = value;
}

void Joystick::updateMouse()
{
    if (sensors[SENSOR_RA_H] != 0 || sensors[SENSOR_RA_V] != 0) {
        moveMouse(sensors[SENSOR_RA_H] / 3000, sensors[SENSOR_RA_V] / 3000);
    }
}

void Joystick::debug()
{
    for (int i = 0; i < 17; i++) {
        printf("%3d ", i);
    }

    printf(" | state | page \n");

    for (int i = 0; i < 17; i++) {
        printf("%3d ", buttons[i]);
    }

    printf(" | %5d | %4d ", state(), page());

    printf("\n");
}

void Joystick::sendKey(int code, int state, bool pressed)
{
    int types[] = {KeyRelease, KeyPress};

    Window root = XDefaultRootWindow(display);
    int revert;
    XKeyEvent event;
    event.type = types[pressed];
    event.display = display;
    event.root = root;
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 1;
    event.y = 1;
    event.x_root = 1;
    event.y_root = 1;
    event.same_screen = True;
    event.state = state;
    event.keycode = XKeysymToKeycode(display, code);

    XGetInputFocus(display, &event.window, &revert);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *) & event);
}

void Joystick::sendClick(int code, int state, bool pressed)
{
    int types[] = {ButtonRelease, ButtonPress};

    Window root = XDefaultRootWindow(display);
    int revert;
    XButtonEvent event;
    event.type = types[pressed];
    event.display = display;
    event.root = root;
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 1;
    event.y = 1;
    event.x_root = 1;
    event.y_root = 1;
    event.same_screen = True;
    event.state = state;
    event.button = code;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.root, &event.window, &event.x_root, &event.y_root, &event.x, &event.y, &event.state);

    event.subwindow = event.window;

    while (event.subwindow) {
        event.window = event.subwindow;

        XQueryPointer(display, event.window, &event.root, &event.subwindow, &event.x_root, &event.y_root, &event.x, &event.y, &event.state);
    }

    XSendEvent(event.display, event.window, True, 0xfff, (XEvent *) & event);
}

void Joystick::moveMouse(int x, int y)
{
    int src_x = 1;
    int src_y = 1;
    int src_w = 1;
    int src_h = 1;

    XWarpPointer(display, None, None, src_x, src_y, src_w, src_h, x, y);
}

int Joystick::keycodes[4][4][9] = {
    {
        {
         XK_7, XK_8, XK_9,
         XK_4, XK_5, XK_6,
         XK_1, XK_2, XK_3,
        },
        {
         XK_B, XK_K, XK_V,
         XK_Q, XK_period, XK_X,
         XK_P, XK_J, XK_Z,
        },
        {
         XK_A, XK_T, XK_N,
         XK_H, XK_E, XK_I,
         XK_O, XK_S, XK_R,
        },
        {
         XK_L, XK_D, XK_C,
         XK_M, XK_U, XK_W,
         XK_F, XK_G, XK_Y,
        },
    },
    {
        {
         XK_7, XK_8, XK_9,
         XK_4, XK_5, XK_6,
         XK_1, XK_2, XK_3,
        },
        {
         XK_B, XK_K, XK_V,
         XK_Q, XK_period, XK_X,
         XK_P, XK_J, XK_Z,
        },
        {
         XK_A, XK_T, XK_N,
         XK_H, XK_E, XK_I,
         XK_O, XK_S, XK_R,
        },
        {
         XK_L, XK_D, XK_C,
         XK_M, XK_U, XK_W,
         XK_F, XK_G, XK_Y,
        },
    },
    {
        {
         XK_7, XK_8, XK_9,
         XK_4, XK_5, XK_6,
         XK_1, XK_2, XK_3,
        },
        {
         XK_B, XK_K, XK_V,
         XK_Q, XK_period, XK_X,
         XK_P, XK_J, XK_Z,
        },
        {
         XK_A, XK_T, XK_N,
         XK_H, XK_E, XK_I,
         XK_O, XK_S, XK_R,
        },
        {
         XK_L, XK_D, XK_C,
         XK_M, XK_U, XK_W,
         XK_F, XK_G, XK_Y,
        },
    },
    {
        {
         XK_7, XK_8, XK_9,
         XK_4, XK_5, XK_6,
         XK_1, XK_2, XK_3,
        },
        {
         XK_B, XK_K, XK_V,
         XK_Q, XK_period, XK_X,
         XK_P, XK_J, XK_Z,
        },
        {
         XK_A, XK_T, XK_N,
         XK_H, XK_E, XK_I,
         XK_O, XK_S, XK_R,
        },
        {
         XK_L, XK_D, XK_C,
         XK_M, XK_U, XK_W,
         XK_F, XK_G, XK_Y,
        },
    },
};
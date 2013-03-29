/* 
 * File:   Joystick.h
 * Author: chemisus
 *
 * Created on March 28, 2013, 6:54 PM
 */

#ifndef JOYSTICK_H
#define	JOYSTICK_H

class Joystick {
private:
    Display *display;
    bool buttons[17];
    int16_t sensors[27];
    static int keycodes[4][4][9];
    Pager *pager;
    
    int state();
    bool pressed(int button);
    int keycode(int button);
    void sendKey(int code, int state, bool pressed);
    void sendClick(int code, int state, bool pressed);
public:
    Joystick(Display *display, Pager *pager);
    virtual ~Joystick();

    void button(int button, bool value);
    void sensor(int sensor, int16_t value);
    void debug();
    int page();

    void character();
    void home(bool pressed);
    void end(bool pressed);
    void left(bool pressed);
    void right(bool pressed);
    void up(bool pressed);
    void down(bool pressed);
    void pageUp(bool pressed);
    void pageDown(bool pressed);
    void space(bool pressed);
    void backspace(bool pressed);
    void tab(bool pressed);
    void escape(bool pressed);
    void enter(bool pressed);
    void move(bool pressed);
    void clickLeft(bool pressed);
    void clickRight(bool pressed);
    void moveMouse(int x, int y);
    void updateMouse();
    
protected:

    

};

#endif	/* JOYSTICK_H */


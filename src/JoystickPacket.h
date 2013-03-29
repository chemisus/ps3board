/* 
 * File:   JoystickPacket.h
 * Author: chemisus
 *
 * Created on March 29, 2013, 2:25 PM
 */

#ifndef JOYSTICKPACKET_H
#define	JOYSTICKPACKET_H

typedef union {
    char bytes[8];

    struct {
        int32_t tick;
        int16_t value;
        char table;
        char event;
    } data;
} Packet;

class JoystickPacket {
private:
    Packet packet;

public:
    JoystickPacket();
    virtual ~JoystickPacket();

    void read(FILE* stream);

    char event();
    char table();
    int16_t value();
    int32_t tick();
private:

};

#endif	/* JOYSTICKPACKET_H */


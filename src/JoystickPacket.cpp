/* 
 * File:   JoystickPacket.cpp
 * Author: chemisus
 * 
 * Created on March 29, 2013, 2:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "JoystickPacket.h"

JoystickPacket::JoystickPacket()
{
}

JoystickPacket::~JoystickPacket()
{
}


void JoystickPacket::read(FILE* stream)
{
    for (int i = 0; i < 8; i++) {
        packet.bytes[i] = (char) fgetc(stream);
    }
}

char JoystickPacket::event() {
    return packet.data.event;
}

char JoystickPacket::table() {
    return packet.data.table;
}

int16_t JoystickPacket::value() {
    return packet.data.value;
}

int32_t JoystickPacket::tick() {
    return packet.data.tick;
}



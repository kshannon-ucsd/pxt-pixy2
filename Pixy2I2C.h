#ifndef _PIXY2I2C_H
#define _PIXY2I2C_H

#include "TPixy2.h"
#include "pxt.h"

#define PIXY_I2C_DEFAULT_ADDR 0x54
#define PIXY_I2C_MAX_SEND 16 // don't send any more than 16 bytes at a time

namespace String_
{
    String concat(String s, String other);
}

namespace pins
{
    Buffer i2cReadBuffer(int address, int size, bool repeat);
    int i2cWriteBuffer(int address, Buffer buf, bool repeat);
}

class Link2I2C
{
public:
    int8_t open(uint32_t arg) // take I2C address as argument to open
    {
        if (arg == PIXY_DEFAULT_ARGVAL)
            m_addr = PIXY_I2C_DEFAULT_ADDR;
        else
            m_addr = arg;
        return 0;
    }

    void close()
    {
    }

    int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs = NULL)
    {
        uint8_t i;
        if (cs)
            *cs = 0;
        Buffer resp = pins::i2cReadBuffer(m_addr, len, true);
        for (i = 0; i < len; i++)
        {
            buf[i] = resp->data[i];
            if (cs)
                *cs += buf[i];
        }
        return len;
    }

    int16_t send(uint8_t *buf, uint8_t len)
    {
        int8_t i, packet;
        for (i = 0; i < len; i += PIXY_I2C_MAX_SEND)
        {
            if (len - i < PIXY_I2C_MAX_SEND)
                packet = len - i;
            else
                packet = PIXY_I2C_MAX_SEND;
            Buffer req = pxt::mkBuffer(buf + i, packet);
            int resp = pins::i2cWriteBuffer(m_addr, req, true);
            if (resp == MICROBIT_I2C_ERROR) {
                return 0;
            }
        }
        return len;
    }

private:
    uint8_t m_addr;
};

typedef TPixy2<Link2I2C> Pixy2I2C;

#endif
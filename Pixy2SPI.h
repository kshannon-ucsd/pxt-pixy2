#ifndef _PIXY2_H
#define _PIXY2_H

#include "TPixy2.h"
#include "pxt.h"

namespace String_
{
    String concat(String s, String other);
}

namespace pins
{
    void spiTransfer(Buffer command, Buffer response);
    void spiFormat(int bits, int mode);
}

#define PIXY_SPI_CLOCKRATE 2000000

class Link2SPI
{
public:
    int8_t open(uint32_t arg)
    {
        pins::spiFormat(8, 3); // Microbit only supports 8 bits and the Pixy2 runs on SPI mode 3
        return 0;
    }

    void close()
    {
        // I'm not sure if we need to delete and set to null
        // There doesn't seem to be any way to close the SPI in microbit
        // if (NULL != pins::spi)
        // {
        //     delete pins::spi;
        //     pins::spi = NULL;
        // }
    }

    int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs = NULL)
    {
        uint8_t i;
        Buffer req = pins::createBuffer(len); // Automatically set to all 0s
        Buffer resp = pins::createBuffer(len);
        if (cs)
            *cs = 0;
        pins::spiTransfer(req, resp);
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
        Buffer req = pxt::mkBuffer(buf, len);
        Buffer resp = pins::createBuffer(len);
        pins::spiTransfer(req, resp);
        return len;
    }
};

typedef TPixy2<Link2SPI> Pixy2SPI;

#endif
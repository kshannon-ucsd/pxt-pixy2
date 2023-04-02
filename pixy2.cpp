#include "Pixy2.h"

/**
 * Provides access to the Pixy2 camera.
*/
namespace pixy2
{
    Pixy2 *pixy = nullptr;
    Pixy2 *getPixy()
    {
        if (pixy == nullptr)
        {
            pixy = new Pixy2();
            pixy->init();
        }
        return pixy;
    }

    /**
     *  getBlocks() gets all detected blocks in the most recent frame. The new data is then available in the blocks member variable. The returned blocks are sorted by area, with the largest blocks appearing first in the blocks array. It returns an error value (<0) if it fails and the number of detected blocks (>=0) if it succeeds.
     * @param wait Setting wait to false causes getBlocks() to return immediately if no new data is available (polling mode). Setting wait to true (default) causes getBlocks() to block (wait) until the next frame of block data is available. Note, there may be no block data if no objects have been detected.
     * @param sigmap sigmap is a bitmap of all 7 signatures from which you wish to receive block data. For example, if you are only interested in block data from signature 1, you would pass in a value of 1. If you are interested in block data from both signatures 1 and 2, you would pass in a value of 3. If you are interested in block data from signatures 1, 2, and 3, you would pass a value of 7, and so on. The most-significant-bit (128 or 0x80) is used for color-codes. A value of 255 (default) indicates that you are interested in all block data.
     * @param maxblocks maxblocks indicates the maximum number of blocks you wish to receive. For example, passing in a value of 1 would return at most 1 block. A value of 255 (default) indicates that you are interested in all blocks.
    */
    //% help=pixy2/get-blocks
    //% weight=100 blockGap=8
    //% block="get blocks"
    //% blockId=pixy2_get_blocks 
    //% parts="pixy2"
    int getBlocks(bool wait, uint8_t sigmap, uint8_t maxBlocks)
    {
        return getPixy()->getBlocks(wait, sigmap, maxBlocks);
    }
}

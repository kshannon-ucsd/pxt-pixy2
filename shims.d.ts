// Auto-generated. Do not edit.


    /**
     * Provides access to the Pixy2 camera.
     */

declare namespace pixy2 {

    /**
     * getBlocks() gets all detected blocks in the most recent frame. The new data is then available in the blocks member variable. The returned blocks are sorted by area, with the largest blocks appearing first in the blocks array. It returns an error value (<0) if it fails and the number of detected blocks (>=0) if it succeeds.
     * @param wait Setting wait to false causes getBlocks() to return immediately if no new data is available (polling mode). Setting wait to true (default) causes getBlocks() to block (wait) until the next frame of block data is available. Note, there may be no block data if no objects have been detected.
     * @param sigmap sigmap is a bitmap of all 7 signatures from which you wish to receive block data. For example, if you are only interested in block data from signature 1, you would pass in a value of 1. If you are interested in block data from both signatures 1 and 2, you would pass in a value of 3. If you are interested in block data from signatures 1, 2, and 3, you would pass a value of 7, and so on. The most-significant-bit (128 or 0x80) is used for color-codes. A value of 255 (default) indicates that you are interested in all block data.
     * @param maxblocks maxblocks indicates the maximum number of blocks you wish to receive. For example, passing in a value of 1 would return at most 1 block. A value of 255 (default) indicates that you are interested in all blocks.
     */
    //% help=pixy2/get-blocks
    //% weight=100 blockGap=8
    //% block="get blocks"
    //% blockId=pixy2_get_blocks
    //% parts="pixy2" shim=pixy2::getBlocks
    function getBlocks(wait: boolean, sigmap: uint8, maxBlocks: uint8): int32;

    /**
     * getVersion() queries and receives the firmware and hardware version of Pixy2., which is put in the version member variable. It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds. It is called automatically as part of init().
     */
    //% help=pixy2/get-version
    //% weight=99 blockGap=8
    //% block="get version"
    //% blockId=pixy2_get_version
    //% parts="pixy2" shim=pixy2::getVersion
    function getVersion(): int32;

    /**
     * getResolution() gets the width and height of the frames used by the current program. After calling this function, the width and height can be found in the frameWidth and frameHeight member variables. Note, calling changeProg() will call getResolution() automatically and update frameWidth and frameHeight. Pixy2 will automatically change programs if, for example, you call ccc.getBlocks() from the color connected components program followed by line.getMainFeatures() from the line tracking program. These “automatic program changes” will not update frameWidth and frameHeight member variables.
     */
    //% help=pixy2/get-resolution
    //% weight=98 blockGap=8
    //% block="get resolution"
    //% blockId=pixy2_get_resolution
    //% parts="pixy2" shim=pixy2::getResolution
    function getResolution(): int32;

    /**
     * getFPS() gets Pixy2's framerate. The framerate can range between 2 and 62 frames per second depending on the amount of light in the environment and the min frames per second setting in the Camera configuration tab. This function can also serve as a simple indicator of the amount of light in the environment. That is, low framerates necessarily imply lower lighting levels.
     */
    //% help=pixy2/get-fps
    //% weight=97 blockGap=8
    //% block="get fps"
    //% blockId=pixy2_get_fps
    //% parts="pixy2" shim=pixy2::getFPS
    function getFPS(): int32;

    /**
     * setLamp() turns on/off Pixy2's integrated light source. Both arguments are binary, zero or non-zero. It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds. 
     * @param upper The upper argument controls the two white LEDs along the top edge of Pixy2's PCB.
     * @param lower The lower argument sets the RGB LED, causing it to turn on all three color channels at full brightness, resulting in white light. 
     */
    //% help=pixy2/set-lamp
    //% weight=96 blockGap=8
    //% block="set lamp upper %upper|lower %lower"
    //% blockId=pixy2_set_lamp
    //% parts="pixy2" shim=pixy2::setLamp
    function setLamp(upper: boolean, lower: boolean): int32;
}

// Auto-generated. Do not edit. Really.

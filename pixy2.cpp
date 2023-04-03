#include "Pixy2.h"

/**
 * Provides access to the Pixy2 camera.
 */
namespace pixy2
{
    // TODO: Set complicated/unneeded functions to advanced=true so they don't show up in the toolbox
    // -------------- General APIs --------------
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
     * getVersion() queries and receives the firmware and hardware version of Pixy2. and then returns the version member variable. It is called automatically as part of init().
     * @returns It returns Pixy2's version information containing hardware, firmwareMajor, firmwareMinor, firmwareBuild, and firmwareType member variables. If it fails, it returns 0 for all member variables.
     */
    //% help=pixy2/get-version
    //% weight=99 blockGap=8
    //% block="get version"
    //% blockId=pixy2_get_version
    //% parts="pixy2"
    Version getVersion()
    {
        int8_t result = getPixy()->getVersion();
        if (result < 0)
        {
            return {0, 0, 0, 0, 0};
        }
        return *(getPixy()->version);
    }

    /**
     * changeProg() instructs Pixy2 to switch programs. Note, calling changeProg() will call getResolution() automatically and update frameWidth and frameHeight.
     * @param prog It takes a string argument that indicates the name of the program. The argument can be a partial string of the program name as long as it is unique with respect to the other program names.
     * @returns It returns the resolution of the new program containing frameWidth and frameHeight member variables. If it fails, it returns 0 for all member variables.
     */
    //% help=pixy2/change-prog
    //% weight=98 blockGap=8
    //% block="change prog %prog"
    //% blockId=pixy2_change_prog
    //% parts="pixy2"
    Resolution changeProg(String prog)
    {
        const char *str = prog->getUTF8Data();
        int8_t result = getPixy()->changeProg(str);
        if (result < 0)
        {
            return {0, 0};
        }
        return {getPixy()->frameWidth, getPixy()->frameHeight};
    }

    /**
     * setServos() sets the servo positions of servos plugged into Pixy2's two RC servo connectors.
     * @param s0 The servo value ranges between PIXY_RCS_MIN_POS (0) and PIXY_RCS_MAX_POS (1000).
     * @param s1 The servo value ranges between PIXY_RCS_MIN_POS (0) and PIXY_RCS_MAX_POS (1000).
     * @returns It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     */
    //% help=pixy2/set-servos
    //% weight=97 blockGap=8
    //% block="set servos %s0 %s1"
    //% blockId=pixy2_set_servos
    //% parts="pixy2"
    int8_t setServos(uint16_t s0, uint16_t s1)
    {
        return getPixy()->setServos(s0, s1);
    }

    /**
     * setCameraBrightness() sets the relative exposure level of Pixy2's image sensor.
     * @param brightness Higher values result in a brighter (more exposed) image.
     * @returns It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     */
    //% help=pixy2/set-camera-brightness
    //% weight=96 blockGap=8
    //% block="set camera brightness %brightness"
    //% blockId=pixy2_set_camera_brightness
    //% parts="pixy2"
    int8_t setCameraBrightness(uint8_t brightness)
    {
        return getPixy()->setCameraBrightness(brightness);
    }

    /**
     * setLED() sets Pixy2's RGB LED value. It will override Pixy2's own setting of the RGB LED
     * @param r Sets the brightness of the red section of the LED
     * @param g Sets the brightness of the green section of the LED
     * @param b Sets the brightness of the blue section of the LED
     * @returns It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     */
    //% help=pixy2/set-led
    //% weight=95 blockGap=8
    //% block="set led %r %g %b"
    //% blockId=pixy2_set_led
    //% parts="pixy2"
    int8_t setLED(uint8_t r, uint8_t g, uint8_t b)
    {
        return getPixy()->setLED(r, g, b);
    }

    /**
     * setLamp() turns on/off Pixy2's integrated light source. Both arguments are binary, zero or non-zero. It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     * @param upper The upper argument controls the two white LEDs along the top edge of Pixy2's PCB.
     * @param lower The lower argument sets the RGB LED, causing it to turn on all three color channels at full brightness, resulting in white light.
     */
    //% help=pixy2/set-lamp
    //% weight=94 blockGap=8
    //% block="set lamp upper %upper|lower %lower"
    //% blockId=pixy2_set_lamp
    //% parts="pixy2"
    int setLamp(bool upper, bool lower)
    {
        return getPixy()->setLamp((uint8_t)upper, (uint8_t)lower);
    }

    // TODO: Pixy2 will automatically change programs if, for example, you call getBlocks() from the color connected components program followed by getMainFeatures() from the line tracking program. These "automatic program changes" will not update frameWidth and frameHeight member variables. This cpp file changes the behaviour by calling changeProg for any function called in a separate program. Should this behaviour be kept?
    /**
     * getResolution() gets the width and height of the frames used by the current program.
     * @returns It returns the resolution of the new program containing frameWidth and frameHeight member variables. If it fails, it returns 0 for all member variables.
     */
    //% help=pixy2/get-resolution
    //% weight=93 blockGap=8
    //% block="get resolution"
    //% blockId=pixy2_get_resolution
    //% parts="pixy2"
    Resolution getResolution()
    {
        int8_t result = getPixy()->getResolution();
        if (result < 0)
        {
            return {0, 0};
        }
        return {getPixy()->frameWidth, getPixy()->frameHeight};
    }

    /**
     * getFPS() gets Pixy2's framerate. The framerate can range between 2 and 62 frames per second depending on the amount of light in the environment and the min frames per second setting in the Camera configuration tab. This function can also serve as a simple indicator of the amount of light in the environment. That is, low framerates necessarily imply lower lighting levels.
     * @returns It returns Pixy2's framerate.
     */
    //% help=pixy2/get-fps
    //% weight=92 blockGap=8
    //% block="get fps"
    //% blockId=pixy2_get_fps
    //% parts="pixy2"
    int8_t getFPS()
    {
        return getPixy()->getFPS();
    }

    // ------------------------ Color Connected Components APIs ------------------------

    /**
     * cccGetBlocks() gets all detected blocks in the most recent frame. The returned blocks are sorted by area, with the largest blocks appearing first in the blocks array.
     * @param wait Setting wait to false causes cccGetBlocks() to return immediately if no new data is available (polling mode). Setting wait to true (default) causes cccGetBlocks() to block (wait) until the next frame of block data is available. Note, there may be no block data if no objects have been detected.
     * @param sigmap sigmap is a bitmap of all 7 signatures from which you wish to receive block data. For example, if you are only interested in block data from signature 1, you would pass in a value of 1. If you are interested in block data from both signatures 1 and 2, you would pass in a value of 3. If you are interested in block data from signatures 1, 2, and 3, you would pass a value of 7, and so on. The most-significant-bit (128 or 0x80) is used for color-codes. A value of 255 (default) indicates that you are interested in all block data.
     * @param maxblocks maxblocks indicates the maximum number of blocks you wish to receive. For example, passing in a value of 1 would return at most 1 block. A value of 255 (default) indicates that you are interested in all blocks.
     * @returns It returns an array of blocks. If it fails, it returns NULL. Each block contains the following information: m_signature, m_x, m_y, m_width, m_height, m_angle, m_index, m_age.
     */
    //% help=pixy2/ccc-get-blocks
    //% weight=91 blockGap=8
    //% block="ccc get blocks"
    //% blockId=pixy2_ccc_get_blocks
    //% parts="pixy2"
    Block *cccGetBlocks(bool wait, uint8_t sigmap, uint8_t maxBlocks)
    {
        Resolution resolution = changeProg(mkString("color_connected_components"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return NULL;
        }
        int8_t result = getPixy()->ccc.getBlocks(wait, sigmap, maxBlocks);
        if (result < 0)
        {
            return NULL;
        }
        return getPixy()->ccc.blocks;
    }

    // ------------------------ Line Tracking APIs ------------------------

    /**
     * lineGetMainFeatures() gets the latest features including the Vector, any intersection that connects to the Vector, and barcodes.  lineGetMainFeatures() tries to send only the most relevant information. Some notes:
        The line tracking algorithm finds the best Vector candidate and begins tracking it from frame to frame 1). The Vector is often the only feature lineGetMainFeatures() returns.
        Intersections are reported after they meet the filtering constraint. Only intersections that connect to the Vector are reported.
        Barcodes are reported after they meet the filtering constraint.
        Each new barcode and intersection is reported only one time so your program doesn't need to keep track of which features it has/hasn't seen previously.

     * @param features [optional] The features argument is a bitwise-ORing of LINE_VECTOR (1), LINE_INTERSECTION (2), and LINE_BARCODE (4), depending on what features you are interested in. All features, if present, are returned by default.
     * @param wait [optional] Setting wait to false causes lineGetMainFeatures() to return immediately if no new data is available (polling mode). Setting wait to true (default) causes lineGetMainFeatures() to block (wait) until the next frame of line feature data is available, unless the current frame of features hasn't been returned before, in which case, it will return immediately with the current frame's features. Note, there may be no feature data if no features have been detected.
     * @returns It returns the main features containing vectors, intersections, and barcodes.
        Each vector contains the following information: m_x0, m_y0, m_x1, m_y1, m_index, m_flags.
        Each intersection contains the following information: m_x, m_y, m_n, m_reserved, m_intLines.
            m_initLines is an array where each intersection line has m_index, m_reserved, m_angle members.
        Each barcode contains the following information: m_x, m_y, m_flags, m_code.
        If it fails, it returns NULL for all member variables
     */
    //% help=pixy2/get-main-features
    //% weight=90 blockGap=8
    //% block="get main features"
    //% blockId=pixy2_get_main_features
    //% parts="pixy2"
    Features lineGetMainFeatures(uint8_t features = 0x07, bool wait = true)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return {NULL, NULL, NULL};
        }
        int8_t result = getPixy()->line.getMainFeatures(features, wait);
        if (result < 0)
        {
            return {NULL, NULL, NULL};
        }
        return {getPixy()->line.vectors, getPixy()->line.intersections, getPixy()->line.barcodes};
    }

    /**
     * lineGetAllFeatures() returns all lines, intersections and barcodes that the line tracking algorithm detects.
     * @param features [optional] The features argument is a bitwise-ORing of LINE_VECTOR (1), LINE_INTERSECTION (2), and LINE_BARCODE (4), depending on what features you are interested in. All detected features are returned by default
     * @param wait [optional] Setting wait to false causes lineGetAllFeatures() to return immediately if no new data is available (polling mode). Setting wait to true (default) causes lineGetAllFeatures() to block (wait) until the next frame of line feature data is available, unless the current frame of features hasn't been returned before, in which case, it will return immediately with the current frame's features. Note, there may be no feature data if no features have been detected.
     * @returns It returns all features containing vectors, intersections, and barcodes.
        Each vector contains the following information: m_x0, m_y0, m_x1, m_y1, m_index, m_flags.
        Each intersection contains the following information: m_x, m_y, m_n, m_reserved, m_intLines.
            m_initLines is an array where each intersection line has m_index, m_reserved, m_angle members.
        Each barcode contains the following information: m_x, m_y, m_flags, m_code.
        If it fails, it returns NULL for all member variables
     */
    //% help=pixy2/get-all-features
    //% weight=89 blockGap=8
    //% block="get all features"
    //% blockId=pixy2_get_all_features
    //% parts="pixy2"
    Features lineGetAllFeatures(uint8_t features = 0x07, bool wait = true)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return {NULL, NULL, NULL};
        }
        int8_t result = getPixy()->line.getAllFeatures(features, wait);
        if (result < 0)
        {
            return {NULL, NULL, NULL};
        }
        return {getPixy()->line.vectors, getPixy()->line.intersections, getPixy()->line.barcodes};
    }

    /**
     * lineSetMode() function sets various modes in the line tracking algorithm
     * @param mode The mode argument consists of a bitwise-ORing of the following bits:
        LINE_MODE_TURN_DELAYED
            Normally, the line tracking algorithm will choose the straightest path (branch) when encountering an intersection. 2) Setting LINE_MODE_TURN_DELAYED will prevent the line tracking algorithm from choosing the path automatically. This is useful if your program doesn't know beforehand which path it wants to take at the next intersection.
        LINE_MODE_MANUAL_SELECT_VECTOR
            Normally, the line tracking algorithm will choose what it thinks is the best Vector line automatically. Setting LINE_MODE_MANUAL_SELECT_VECTOR will prevent the line tracking algorithm from choosing the Vector automatically. Instead, your program will need to set the Vector by calling setVector().
        LINE_MODE_WHITE_LINE
            Normally, the line tracking algorithm will try to find dark lines on a light background (black lines). Setting LINE_MODE_WHITE_LINE will instruct the line tracking algorithm to look for light lines on a dark background (white lines).
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-line-mode
    //% weight=88 blockGap=8
    //% block="set line mode %mode"
    //% blockId=pixy2_set_line_mode
    //% parts="pixy2"
    int8_t lineSetMode(uint8_t mode)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return -1;
        }
        return getPixy()->line.setMode(mode);
    }

    /**
     * lineSetNextTurn() function tells the line tracking algorithm which path it should take at the next intersection. lineSetNextTurn() will remember the turn angle you give it, and execute it at the next intersection. The line tracking algorithm will then go back to the default turn angle for subsequent intersections. Upon encountering an intersection, the line tracking algorithm will find the path in the intersection that matches the turn angle most closely.
     * @param angle Turn angles are specified in degrees, with 0 being straight ahead, left being 90 and right being -90 (for example), although any valid angle value can be used. Valid angles are between -180 and 180.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-next-turn
    //% weight=87 blockGap=8
    //% block="set next turn %angle"
    //% blockId=pixy2_set_next_turn
    //% parts="pixy2"
    int8_t lineSetNextTurn(int16_t angle)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return -1;
        }
        return getPixy()->line.setNextTurn(angle);
    }

    /**
     * lineSetDefaultTurn() function tells the line tracking algorithm which path to choose by default upon encountering an intersection. The line tracking algorithm will find the path in the intersection that matches the default turn angle most closely. A call to setNextTurn() will supercede the default turn angle for the next intersection.
     * @param angle Turn angles are specified in degrees, with 0 being straight ahead, left being 90 and right being -90 (for example), although any valid angle value can be used. Valid angles are between -180 and 180.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-default-turn
    //% weight=86 blockGap=8
    //% block="set default turn %angle"
    //% blockId=pixy2_set_default_turn
    //% parts="pixy2"
    int8_t lineSetDefaultTurn(int16_t angle)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return -1;
        }
        return getPixy()->line.setDefaultTurn(angle);
    }

    /**
     * If the LINE_MODE_MANUAL_SELECT_VECTOR mode bit is set, the line tracking algorithm will no longer choose the Vector automatically. Instead, lineSetVector() will set the Vector by providing the index of the line.
     * @param index The index of the line to set as the Vector.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-vector
    //% weight=85 blockGap=8
    //% block="set vector %index"
    //% blockId=pixy2_set_vector
    //% parts="pixy2"
    int8_t lineSetVector(uint8_t index)
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return -1;
        }
        return getPixy()->line.setVector(index);
    }

    /**
     * The Vector has a direction. It normally points up, from the bottom of the camera frame to the top of the camera frame for a forward-moving robot. Calling lineReverseVector() will invert the vector. This will typically cause your robot to back-up and change directions.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/reverse-vector
    //% weight=84 blockGap=8
    //% block="reverse vector"
    //% blockId=pixy2_reverse_vector
    //% parts="pixy2"
    int8_t lineReverseVector()
    {
        Resolution resolution = changeProg(mkString("line"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return -1;
        }
        return getPixy()->line.reverseVector();
    }

    // --------------- Video APIs ---------------

    /**
     * videoGetRGB() is currently the only function supported by the video program. It takes an x and y location in the image and returns red, green, blue values of the pixel. The individual values of red, green and blue vary from 0 to 255. Instead of using just one pixel, videoGetRGB() takes a 5×5 section of pixels centered at the x, y location and performs an average of all 25 pixels to obtain a representative result. Locations on the edge or close to the edge of the image are allowed, but will result in fewer pixels being averaged. The width and height values are both available through pixy.frameWidth and pixy.frameHeight, if you don't want to remember their specific values.
     * @param x The x location of the pixel.
     * @param y The y location of the pixel.
     * @param saturate [Optional] The saturate argument when set to true (default) will scale all RGB values such that the greatest of the three values (r, g and b) is maximized (saturated) at 255. When set to false, the unmodified RGB values are returned.
     * @returns It returns the RGB value which contains r, g, b member values, if it succeeds, otherwise it returns 0 for all member values. //TODO: Can this be a bug incase the RGB value is 0,0,0?
     */
    //% help=pixy2/video-get-rgb
    //% weight=83 blockGap=8
    //% block="video get RGB x %x y %y r %r g %g b %b saturate %saturate"
    //% blockId=pixy2_video_get_rgb
    //% parts="pixy2"
    RGB videoGetRGB(uint16_t x, uint16_t y, bool saturate = true)
    {
        Resolution resolution = changeProg(mkString("video"));
        if (resolution.frameWidth == 0 && resolution.frameHeight == 0)
        {
            return {0, 0, 0};
        }
        uint8_t r, g, b;
        getPixy()->video.getRGB(x, y, &r, &g, &b, saturate);
        return {r, g, b};
    }

}

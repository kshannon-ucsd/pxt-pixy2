#include "Pixy2I2C.h"

/**
 * Provides access to the Pixy2 camera.
 */
namespace pixy2
{
    // TODO: Set complicated/unneeded functions to advanced=true so they don't show up in the toolbox
    // -------------- General APIs --------------
    Pixy2I2C *pixy = nullptr;
    ManagedString COMMA = ManagedString(",");
    ManagedString SEMICOLON = ManagedString(";");
    ManagedString PIPE = ManagedString("|");
    ManagedString NEWLINE = ManagedString("\n");
    Pixy2I2C *getPixy()
    {
        if (pixy == nullptr)
        {
            pixy = new Pixy2I2C();
            pixy->init();
        }
        return pixy;
    }

    String convertResolutionToString()
    {
        ManagedString res = ManagedString(getPixy()->frameWidth) + COMMA + ManagedString(getPixy()->frameHeight);
        return PSTR(res);
    }

    String convertVersionToString()
    {
        Version *version = getPixy()->version;
        ManagedString res = ManagedString(version->hardware) + COMMA + ManagedString(version->firmwareMajor) + COMMA + ManagedString(version->firmwareMinor) + COMMA + ManagedString(version->firmwareBuild) + COMMA + ManagedString(version->firmwareType);
        return PSTR(res);
    }

    String convertFeaturesToString(uint8_t features, int8_t result, Vector *vectors, Intersection *intersections, Barcode *barcodes)
    {
        ManagedString vectorsString = ManagedString();
        ManagedString intersectionsString = ManagedString();
        ManagedString barcodesString = ManagedString();
        for (int i = 0; i < result; i++)
        {
            if (features & LINE_VECTOR)
            {
                ManagedString vectorString = ManagedString(vectors[i].m_x0) + COMMA + ManagedString(vectors[i].m_y0) + COMMA + ManagedString(vectors[i].m_x1) + COMMA + ManagedString(vectors[i].m_y1) + COMMA + ManagedString(vectors[i].m_index) + COMMA + ManagedString(vectors[i].m_flags);
                if (i != result - 1)
                    vectorString = vectorString + SEMICOLON;
                vectorsString = vectorsString + vectorString;
            }
            if (features & LINE_INTERSECTION)
            {
                ManagedString intersectionString = ManagedString(intersections[i].m_x) + COMMA + ManagedString(intersections[i].m_y) + COMMA + ManagedString(intersections[i].m_n) + COMMA + ManagedString(intersections[i].m_reserved) + PIPE;
                for (int j = 0; j < intersections[i].m_n; j++)
                {
                    ManagedString intersectionLineString = ManagedString(intersections[i].m_intLines[j].m_index) + COMMA + ManagedString(intersections[i].m_intLines[j].m_reserved) + COMMA + ManagedString(intersections[i].m_intLines[j].m_angle);
                    if (j != intersections[i].m_n - 1)
                        intersectionLineString = intersectionLineString + PIPE;
                    intersectionString = intersectionString + intersectionLineString;
                }
                if (i != result - 1)
                    intersectionString = intersectionString + SEMICOLON;
                intersectionsString = intersectionsString + intersectionString;
            }
            if (features & LINE_BARCODE)
            {
                ManagedString barcodeString = ManagedString(barcodes[i].m_x) + COMMA + ManagedString(barcodes[i].m_y) + COMMA + ManagedString(barcodes[i].m_flags) + COMMA + ManagedString(barcodes[i].m_code);
                if (i != result - 1)
                    barcodeString = barcodeString + SEMICOLON;
                barcodesString = barcodesString + barcodeString;
            }
        }
        return PSTR(vectorsString + NEWLINE + intersectionsString + NEWLINE + barcodesString);
    }

    /**
     * getVersion() queries and receives the firmware and hardware version of Pixy2. and then returns the version member variable. It is called automatically as part of init().
     * @returns It returns Pixy2's version information containing hardware, firmwareMajor, firmwareMinor, firmwareBuild, and firmwareType as comma separated string (in that order). If it fails, it returns null.
     */
    //% help=pixy2/get-version
    //% weight=99 blockGap=8
    //% block="get version"
    //% blockId=pixy2_get_version
    //% parts="pixy2"
    //% group="General"
    String getVersion()
    {
        int8_t result = getPixy()->getVersion();
        if (result < 0)
        {
            return NULL;
        }
        return convertVersionToString();
    }

    /**
     * changeProg() instructs Pixy2 to switch programs. Note, calling changeProg() will call getResolution() automatically and update frameWidth and frameHeight.
     * @param prog It takes a string argument that indicates the name of the program. The argument can be a partial string of the program name as long as it is unique with respect to the other program names.
     * @returns It returns the resolution of the new program containing frameWidth, frameHeight as a string. If it fails, it returns an null.
     */
    //% help=pixy2/change-prog
    //% weight=98 blockGap=8
    //% block="change prog %prog"
    //% blockId=pixy2_change_prog
    //% parts="pixy2"
    //% group="General"
    String changeProg(String prog)
    {
        const char *str = prog->getUTF8Data();
        int8_t result = getPixy()->changeProg(str);
        if (result < 0)
        {
            return NULL;
        }
        return convertResolutionToString();
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
    //% group="General"
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
    //% group="General"
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
    //% group="General"
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
    //% group="General"
    int setLamp(bool upper, bool lower)
    {
        return getPixy()->setLamp((uint8_t)upper, (uint8_t)lower);
    }

    // TODO: Pixy2 will automatically change programs if, for example, you call getBlocks() from the color connected components program followed by getMainFeatures() from the line tracking program. These "automatic program changes" will not update frameWidth and frameHeight member variables. This cpp file changes the behaviour by calling changeProg for any function called in a separate program. Should this behaviour be kept?
    /**
     * getResolution() gets the width and height of the frames used by the current program.
     * @returns It returns the resolution of the new program containing frameWidth, frameHeight as a string. If it fails, it returns an null.
     */
    //% help=pixy2/get-resolution
    //% weight=93 blockGap=8
    //% block="get resolution"
    //% blockId=pixy2_get_resolution
    //% parts="pixy2"
    //% group="General"
    String getResolution()
    {
        int8_t result = getPixy()->getResolution();
        if (result < 0)
        {
            return NULL;
        }
        return convertResolutionToString();
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
    //% group="General"
    int8_t getFPS()
    {
        return getPixy()->getFPS();
    }

    // ------------------------ Color Connected Components APIs ------------------------

    /**
     * Internal use only. This function will be used in pixy2.ts to return the blocks of color connected components as a string.
     */
    //%
    String cccGetBlocksAsString(bool wait, uint8_t sigmap, uint8_t maxBlocks)
    {
        String resolution = changeProg(mkString("color_connected_components"));
        if (resolution == NULL)
        {
            return NULL;
        }
        int8_t result = getPixy()->ccc.getBlocks(wait, sigmap, maxBlocks);
        if (result < 0)
        {
            return NULL;
        }
        Block *blocks = getPixy()->ccc.blocks;
        ManagedString blocksString;
        for (int i = 0; i < result; i++)
        {
            ManagedString blockString = ManagedString(blocks[i].m_signature) + COMMA + ManagedString(blocks[i].m_x) + COMMA + ManagedString(blocks[i].m_y) + COMMA + ManagedString(blocks[i].m_width) + COMMA + ManagedString(blocks[i].m_height) + COMMA + ManagedString(blocks[i].m_angle) + COMMA + ManagedString(blocks[i].m_index) + COMMA + ManagedString(blocks[i].m_age);
            if (i != result - 1)
                blockString = blockString + SEMICOLON;
            blocksString = blocksString + blockString;
        }
        return PSTR(blocksString);
    }

    // ------------------------ Line Tracking APIs ------------------------

    /**
     * Internal use only. This function will be used in pixy2.ts to return the main features of line tracking as a string.
     */
    //%
    String lineGetMainFeaturesAsString(uint8_t features = 0x07, bool wait = true)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
        {
            return NULL;
        }
        int8_t result = getPixy()->line.getMainFeatures(features, wait);
        if (result < 0)
        {
            return NULL;
        }
        return convertFeaturesToString(features, result, getPixy()->line.vectors, getPixy()->line.intersections, getPixy()->line.barcodes);
    }

    /**
     * Internal use only. This function will be used in pixy2.ts to return all features of line tracking as a string.
     */
    //%
    String lineGetAllFeaturesAsString(uint8_t features = 0x07, bool wait = true)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
        {
            return NULL;
        }
        int8_t result = getPixy()->line.getAllFeatures(features, wait);
        if (result < 0)
        {
            return NULL;
        }
        return convertFeaturesToString(features, result, getPixy()->line.vectors, getPixy()->line.intersections, getPixy()->line.barcodes);
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
    //% group="Line Tracking"
    int8_t lineSetMode(uint8_t mode)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
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
    //% group="Line Tracking"
    int8_t lineSetNextTurn(int16_t angle)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
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
    //% group="Line Tracking"
    int8_t lineSetDefaultTurn(int16_t angle)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
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
    //% group="Line Tracking"
    int8_t lineSetVector(uint8_t index)
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
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
    //% group="Line Tracking"
    int8_t lineReverseVector()
    {
        String resolution = changeProg(mkString("line"));
        if (resolution == NULL)
        {
            return -1;
        }
        return getPixy()->line.reverseVector();
    }

    // --------------- Video APIs ---------------

    /**
     * Internal use only. This function will be used in pixy2.ts to return the RGB values as an object
     */
    //%
    String videoGetRGBAsString(uint16_t x, uint16_t y, bool saturate = true)
    {
        String resolution = changeProg(mkString("video"));
        if (resolution == NULL)
        {
            return NULL;
        }
        uint8_t r = 0, g = 0, b = 0;
        getPixy()->video.getRGB(x, y, &r, &g, &b, saturate);
        ManagedString rgb = ManagedString(r) + COMMA + ManagedString(g) + COMMA + ManagedString(b);
        return PSTR(rgb);
    }

}

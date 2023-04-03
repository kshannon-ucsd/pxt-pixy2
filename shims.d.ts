// Auto-generated. Do not edit.


    /**
     * Provides access to the Pixy2 camera.
     */

declare namespace pixy2 {

    /**
     * getVersion() queries and receives the firmware and hardware version of Pixy2. and then returns the version member variable. It is called automatically as part of init().
     * @returns It returns Pixy2's version information containing hardware, firmwareMajor, firmwareMinor, firmwareBuild, and firmwareType as comma separated string (in that order). If it fails, it returns null.
     */
    //% help=pixy2/get-version
    //% weight=99 blockGap=8
    //% block="get version"
    //% blockId=pixy2_get_version
    //% parts="pixy2" shim=pixy2::getVersion
    function getVersion(): string;

    /**
     * changeProg() instructs Pixy2 to switch programs. Note, calling changeProg() will call getResolution() automatically and update frameWidth and frameHeight.
     * @param prog It takes a string argument that indicates the name of the program. The argument can be a partial string of the program name as long as it is unique with respect to the other program names.
     * @returns It returns the resolution of the new program containing frameWidth, frameHeight as a string. If it fails, it returns an null.
     */
    //% help=pixy2/change-prog
    //% weight=98 blockGap=8
    //% block="change prog %prog"
    //% blockId=pixy2_change_prog
    //% parts="pixy2" shim=pixy2::changeProg
    function changeProg(prog: string): string;

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
    //% parts="pixy2" shim=pixy2::setServos
    function setServos(s0: uint16, s1: uint16): int8;

    /**
     * setCameraBrightness() sets the relative exposure level of Pixy2's image sensor.
     * @param brightness Higher values result in a brighter (more exposed) image.
     * @returns It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     */
    //% help=pixy2/set-camera-brightness
    //% weight=96 blockGap=8
    //% block="set camera brightness %brightness"
    //% blockId=pixy2_set_camera_brightness
    //% parts="pixy2" shim=pixy2::setCameraBrightness
    function setCameraBrightness(brightness: uint8): int8;

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
    //% parts="pixy2" shim=pixy2::setLED
    function setLED(r: uint8, g: uint8, b: uint8): int8;

    /**
     * setLamp() turns on/off Pixy2's integrated light source. Both arguments are binary, zero or non-zero. It returns an error value (<0) if it fails and 0 (PIXY_RESULT_OK) if it succeeds.
     * @param upper The upper argument controls the two white LEDs along the top edge of Pixy2's PCB.
     * @param lower The lower argument sets the RGB LED, causing it to turn on all three color channels at full brightness, resulting in white light.
     */
    //% help=pixy2/set-lamp
    //% weight=94 blockGap=8
    //% block="set lamp upper %upper|lower %lower"
    //% blockId=pixy2_set_lamp
    //% parts="pixy2" shim=pixy2::setLamp
    function setLamp(upper: boolean, lower: boolean): int32;

    /**
     * getResolution() gets the width and height of the frames used by the current program.
     * @returns It returns the resolution of the new program containing frameWidth, frameHeight as a string. If it fails, it returns an null.
     */
    //% help=pixy2/get-resolution
    //% weight=93 blockGap=8
    //% block="get resolution"
    //% blockId=pixy2_get_resolution
    //% parts="pixy2" shim=pixy2::getResolution
    function getResolution(): string;

    /**
     * getFPS() gets Pixy2's framerate. The framerate can range between 2 and 62 frames per second depending on the amount of light in the environment and the min frames per second setting in the Camera configuration tab. This function can also serve as a simple indicator of the amount of light in the environment. That is, low framerates necessarily imply lower lighting levels.
     * @returns It returns Pixy2's framerate.
     */
    //% help=pixy2/get-fps
    //% weight=92 blockGap=8
    //% block="get fps"
    //% blockId=pixy2_get_fps
    //% parts="pixy2" shim=pixy2::getFPS
    function getFPS(): int8;

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
    //% parts="pixy2" shim=pixy2::lineSetMode
    function lineSetMode(mode: uint8): int8;

    /**
     * lineSetNextTurn() function tells the line tracking algorithm which path it should take at the next intersection. lineSetNextTurn() will remember the turn angle you give it, and execute it at the next intersection. The line tracking algorithm will then go back to the default turn angle for subsequent intersections. Upon encountering an intersection, the line tracking algorithm will find the path in the intersection that matches the turn angle most closely.
     * @param angle Turn angles are specified in degrees, with 0 being straight ahead, left being 90 and right being -90 (for example), although any valid angle value can be used. Valid angles are between -180 and 180.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-next-turn
    //% weight=87 blockGap=8
    //% block="set next turn %angle"
    //% blockId=pixy2_set_next_turn
    //% parts="pixy2" shim=pixy2::lineSetNextTurn
    function lineSetNextTurn(angle: int16): int8;

    /**
     * lineSetDefaultTurn() function tells the line tracking algorithm which path to choose by default upon encountering an intersection. The line tracking algorithm will find the path in the intersection that matches the default turn angle most closely. A call to setNextTurn() will supercede the default turn angle for the next intersection.
     * @param angle Turn angles are specified in degrees, with 0 being straight ahead, left being 90 and right being -90 (for example), although any valid angle value can be used. Valid angles are between -180 and 180.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-default-turn
    //% weight=86 blockGap=8
    //% block="set default turn %angle"
    //% blockId=pixy2_set_default_turn
    //% parts="pixy2" shim=pixy2::lineSetDefaultTurn
    function lineSetDefaultTurn(angle: int16): int8;

    /**
     * If the LINE_MODE_MANUAL_SELECT_VECTOR mode bit is set, the line tracking algorithm will no longer choose the Vector automatically. Instead, lineSetVector() will set the Vector by providing the index of the line.
     * @param index The index of the line to set as the Vector.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/set-vector
    //% weight=85 blockGap=8
    //% block="set vector %index"
    //% blockId=pixy2_set_vector
    //% parts="pixy2" shim=pixy2::lineSetVector
    function lineSetVector(index: uint8): int8;

    /**
     * The Vector has a direction. It normally points up, from the bottom of the camera frame to the top of the camera frame for a forward-moving robot. Calling lineReverseVector() will invert the vector. This will typically cause your robot to back-up and change directions.
     * @returns It returns 0 if it succeeds, otherwise it returns -1.
     */
    //% help=pixy2/reverse-vector
    //% weight=84 blockGap=8
    //% block="reverse vector"
    //% blockId=pixy2_reverse_vector
    //% parts="pixy2" shim=pixy2::lineReverseVector
    function lineReverseVector(): int8;

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
    //% parts="pixy2" saturate.defl=1 shim=pixy2::videoGetRGB
    function videoGetRGB(x: uint16, y: uint16, saturate?: boolean): string;
}

// Auto-generated. Do not edit. Really.

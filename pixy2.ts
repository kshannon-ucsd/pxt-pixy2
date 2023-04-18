namespace pixy2 {
    interface RGB {
        r: number;
        g: number;
        b: number;
    }

    interface Block {
        m_signature: number;
        m_x: number;
        m_y: number;
        m_width: number;
        m_height: number;
        m_angle: number;
        m_index: number;
        m_age: number;
    }

    interface Vector {
        m_x0: number;
        m_y0: number;
        m_x1: number;
        m_y1: number;
        m_index: number;
        m_flags: number;
    }

    interface IntersectionLine {
        m_index: number;
        m_reserved: number;
        m_angle: number;
    }

    interface Intersection {
        m_x: number;
        m_y: number;
        m_n: number;
        m_reserved: number;
        m_intLines: IntersectionLine[];
    }

    interface Barcode {
        m_x: number;
        m_y: number;
        m_flags: number;
        m_code: number;
    }

    interface Features {
        vectors: Vector[];
        intersections: Intersection[];
        barcodes: Barcode[];
    }

    function convertFeaturesStringToInterface(str: string): Features {
        let featuresArray = str.split("\n");
        let vectors: Vector[] = [];
        let intersections: Intersection[] = [];
        let barcodes: Barcode[] = [];

        featuresArray[0].split(";").forEach((vector: string) => {
            let vectorArray = vector.split(",");
            vectors.push({
                m_x0: parseInt(vectorArray[0]),
                m_y0: parseInt(vectorArray[1]),
                m_x1: parseInt(vectorArray[2]),
                m_y1: parseInt(vectorArray[3]),
                m_index: parseInt(vectorArray[4]),
                m_flags: parseInt(vectorArray[5])
            });
        });

        featuresArray[1].split(";").forEach((intersection: string) => {
            let intersectionArray = intersection.split("|");
            let intersectionLines: IntersectionLine[] = [];
            for (let i = 1; i < intersectionArray.length; i++) {
                let intersectionLineArray = intersectionArray[i].split(",");
                intersectionLines.push({
                    m_index: parseInt(intersectionLineArray[0]),
                    m_reserved: parseInt(intersectionLineArray[1]),
                    m_angle: parseInt(intersectionLineArray[2])
                });
            }
            let intersectionMetaArray = intersectionArray[0].split(",");
            intersections.push({
                m_x: parseInt(intersectionMetaArray[0]),
                m_y: parseInt(intersectionMetaArray[1]),
                m_n: parseInt(intersectionMetaArray[2]),
                m_reserved: parseInt(intersectionMetaArray[3]),
                m_intLines: intersectionLines
            });
        });

        featuresArray[2].split(";").forEach((barcode: string) => {
            let barcodeArray = barcode.split(",");
            barcodes.push({
                m_x: parseInt(barcodeArray[0]),
                m_y: parseInt(barcodeArray[1]),
                m_flags: parseInt(barcodeArray[2]),
                m_code: parseInt(barcodeArray[3])
            });
        });

        return {
            vectors: vectors,
            intersections: intersections,
            barcodes: barcodes
        };
    }

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
    //% group="Color Connected Components"
    export function cccGetBlocks(wait: boolean, sigmap: number, maxblocks: number = 255): Block[] {
        let str = pixy2.cccGetBlocksAsString(wait, sigmap, maxblocks);
        let blocks = str.split(";");
        let blocksArray: Block[] = [];
        for (let i = 0; i < blocks.length; i++) {
            let block = blocks[i].split(",");
            blocksArray.push({
                m_signature: parseInt(block[0]),
                m_x: parseInt(block[1]),
                m_y: parseInt(block[2]),
                m_width: parseInt(block[3]),
                m_height: parseInt(block[4]),
                m_angle: parseInt(block[5]),
                m_index: parseInt(block[6]),
                m_age: parseInt(block[7])
            });
        }
        return blocksArray;
    }

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
    //% group="Line Tracking"
    export function getMainFeatures(features: number, wait: boolean = true): Features {
        return convertFeaturesStringToInterface(pixy2.lineGetMainFeaturesAsString(features, wait));
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
    //% group="Line Tracking"
    export function getAllFeatures(features: number, wait: boolean = true): Features {
        return convertFeaturesStringToInterface(pixy2.lineGetAllFeaturesAsString(features, wait));
    }

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
    //% group="Video"
    export function videoGetRGB(x: number, y: number, saturate: boolean = true): RGB {
        let str = pixy2.videoGetRGBAsString(x, y, saturate);
        let rgb = str.split(",");
        return { r: parseInt(rgb[0]), g: parseInt(rgb[1]), b: parseInt(rgb[2]) };
    }
}
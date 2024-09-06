#pragma once
#include <Arduino.h>

//this library is inspired very stronly by the pixelTypes.h file in the FastLED library. I have rewritten the file to work with 16 bit RGB and RGBW values.

//TODO: 
// - HSV color compatibility
// - Testing

// define the basic color definitions:
struct RGBColor16; // 16 bit rgb color
struct RGBWColor16; // 16 bit rgbw color

// struct HSVColor16;

// /// Forward declaration of hsv2rgb_rainbow here,
// /// to avoid circular dependencies.
// extern void hsv2rgb_rainbow( const HSVColor16& hsv, RGBColor16& rgb);
// extern void hsv2rgbw_rainbow( const HSVColor16& hsv, RGBWColor16& rgbw);

// /// Representation of an HSV pixel (hue, saturation, value (aka brightness)).
// struct HSVColor16 {
//     union {
//         struct {
//             union {
//                 /// Color hue.
//                 /// This is an 8-bit value representing an angle around
//                 /// the color wheel. Where 0 is 0°, and 255 is 358°.
//                 uint16_t hue;
//                 uint16_t h; ///< @copydoc hue
//             };
//             union {
//                 /// Color saturation.
//                 /// This is an 8-bit value representing a percentage.
//                 uint16_t saturation;
//                 uint16_t sat; ///< @copydoc saturation
//                 uint16_t s; ///< @copydoc saturation
//             };
//             union {
//                 /// Color value (brightness).
//                 /// This is an 8-bit value representing a percentage.
//                 uint16_t value;
//                 uint16_t val; ///< @copydoc value
//                 uint16_t v; ///< @copydoc value
//             };
//         };
//         /// Access the hue, saturation, and value data as an array.
//         /// Where:
//         /// * `raw[0]` is the hue
//         /// * `raw[1]` is the saturation
//         /// * `raw[2]` is the value
//         uint16_t raw[3];
//     };

//     /// Array access operator to index into the HSVColor16 object
//     /// @param x the index to retrieve (0-2)
//     /// @returns the HSVColor16::raw value for the given index
//     inline uint16_t& operator[](uint16_t x) __attribute__((always_inline))
//     {
//         return raw[x];
//     }

//     /// @copydoc operator[]
//     inline const uint16_t& operator[](uint16_t x) const __attribute__((always_inline))
//     {
//         return raw[x];
//     }

//     /// Default constructor
//     /// @warning Default values are UNITIALIZED!
//     inline HSVColor16() __attribute__((always_inline)) = default;

//     /// Allow construction from hue, saturation, and value
//     /// @param ih input hue
//     /// @param is input saturation
//     /// @param iv input value
//     inline HSVColor16(uint16_t ih, uint16_t is, uint16_t iv) __attribute__((always_inline))
//         : h(ih)
//         , s(is)
//         , v(iv)
//     {
//     }

//     /// Allow copy construction
//     inline HSVColor16(const HSVColor16& rhs) __attribute__((always_inline)) = default;

//     /// Allow copy construction
//     inline HSVColor16& operator=(const HSVColor16& rhs) __attribute__((always_inline)) = default;

//     /// Assign new HSV values
//     /// @param ih input hue
//     /// @param is input saturation
//     /// @param iv input value
//     /// @returns reference to the HSVColor16 object
//     inline HSVColor16& setHSV(uint16_t ih, uint16_t is, uint16_t iv) __attribute__((always_inline))
//     {
//         h = ih;
//         s = is;
//         v = iv;
//         return *this;
//     }
// };

/// Representation of an RGB pixel (Red, Green, Blue)
struct RGBColor16 {
    union {
        struct {
            union {
                uint16_t r; ///< Red channel value
                uint16_t red; ///< @copydoc r
            };
            union {
                uint16_t g; ///< Green channel value
                uint16_t green; ///< @copydoc g
            };
            union {
                uint16_t b; ///< Blue channel value
                uint16_t blue; ///< @copydoc b
            };
        };
        /// Access the red, green, and blue data as an array.
        /// Where:
        /// * `raw[0]` is the red value
        /// * `raw[1]` is the green value
        /// * `raw[2]` is the blue value
        uint16_t raw[3];
    };

    /// Array access operator to index into the RGBColor16 object
    /// @param x the index to retrieve (0-2)
    /// @returns the RGBColor16::raw value for the given index
    inline uint16_t& operator[](uint16_t x) __attribute__((always_inline))
    {
        return raw[x];
    }

    /// Array access operator to index into the RGBColor16 object
    /// @param x the index to retrieve (0-2)
    /// @returns the RGBColor16::raw value for the given index
    inline const uint16_t& operator[](uint16_t x) const __attribute__((always_inline))
    {
        return raw[x];
    }

    /// Default constructor
    /// @warning Default values are UNITIALIZED!
    inline RGBColor16() __attribute__((always_inline)) = default;

    /// Allow construction from red, green, and blue
    /// @param ir input red value
    /// @param ig input green value
    /// @param ib input blue value
    constexpr RGBColor16(uint16_t ir, uint16_t ig, uint16_t ib) __attribute__((always_inline))
        : r(ir)
        , g(ig)
        , b(ib)
    {
    }

    /// Allow copy construction
    inline RGBColor16(const RGBColor16& rhs) __attribute__((always_inline)) = default;

    /// Allow assignment from one RGB struct to another
    inline RGBColor16& operator=(const RGBColor16& rhs) __attribute__((always_inline)) = default;

    // /// Allow assignment from 32-bit (really 24-bit) 0xRRGGBB color code
    // /// @param colorcode a packed 24 bit color code
    // inline RGBColor16& operator= (const uint32_t colorcode) __attribute__((always_inline))
    // {
    //     r = (colorcode >> 16) & 0xFF;
    //     g = (colorcode >>  8) & 0xFF;
    //     b = (colorcode >>  0) & 0xFF;
    //     return *this;
    // }

    /// Allow assignment from red, green, and blue
    /// @param nr new red value
    /// @param ng new green value
    /// @param nb new blue value
    inline RGBColor16& setRGB(uint16_t nr, uint16_t ng, uint16_t nb) __attribute__((always_inline))
    {
        r = nr;
        g = ng;
        b = nb;
        return *this;
    }

    // /// Allow assignment from hue, saturation, and value
    // /// @param hue color hue
    // /// @param sat color saturation
    // /// @param val color value (brightness)
    // inline RGBColor16& setHSV (uint16_t hue, uint16_t sat, uint16_t val) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( HSVColor16(hue, sat, val), *this);
    //     return *this;
    // }

    // /// Allow assignment from just a hue.
    // /// Saturation and value (brightness) are set automatically to max.
    // /// @param hue color hue
    // inline RGBColor16& setHue (uint16_t hue) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( HSVColor16(hue, 255, 255), *this);
    //     return *this;
    // }

    // /// Allow assignment from HSV color
    // inline RGBColor16& operator= (const HSVColor16& rhs) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( rhs, *this);
    //     return *this;
    // }

    /// Add one RGBColor16 to another, saturating at 0xFF for each channel
    inline RGBColor16& operator+=(const RGBColor16& rhs)
    {
        r = constrain(r + rhs.r, 0, 0xFFFF);
        g = constrain(g + rhs.g, 0, 0xFFFF);
        b = constrain(b + rhs.b, 0, 0xFFFF);
        return *this;
    }

    /// Add a constant to each channel, saturating at 0xFF.
    /// @note This is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. RGBColor16::Red) and an 8-bit one (RGBColor16::Blue)
    inline RGBColor16& addToRGB(uint16_t d)
    {
        r = constrain(r + d, 0, 0xFFFF);
        g = constrain(g + d, 0, 0xFFFF);
        b = constrain(b + d, 0, 0xFFFF);
        return *this;
    }

    /// Subtract one RGBColor16 from another, saturating at 0x00 for each channel
    inline RGBColor16& operator-=(const RGBColor16& rhs)
    {
        r = constrain(r - rhs.r, 0, 0xFFFF);
        g = constrain(r - rhs.g, 0, 0xFFFF);
        b = constrain(r - rhs.b, 0, 0xFFFF);
        return *this;
    }

    /// Subtract a constant from each channel, saturating at 0x00.
    /// @note This is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. RGBColor16::Red) and an 8-bit one (RGBColor16::Blue)
    inline RGBColor16& subtractFromRGB(uint16_t d)
    {
        r = constrain(r - d, 0, 0xFFFF);
        g = constrain(g - d, 0, 0xFFFF);
        b = constrain(b - d, 0, 0xFFFF);
        return *this;
    }

    /// Subtract a constant of '1' from each channel, saturating at 0x00
    inline RGBColor16& operator--() __attribute__((always_inline))
    {
        subtractFromRGB(1);
        return *this;
    }

    /// @copydoc operator--
    inline RGBColor16 operator--(int) __attribute__((always_inline))
    {
        RGBColor16 retval(*this);
        --(*this);
        return retval;
    }

    /// Add a constant of '1' from each channel, saturating at 0xFF
    inline RGBColor16& operator++() __attribute__((always_inline))
    {
        addToRGB(1);
        return *this;
    }

    /// @copydoc operator++
    inline RGBColor16 operator++(int) __attribute__((always_inline))
    {
        RGBColor16 retval(*this);
        ++(*this);
        return retval;
    }

    /// Divide each of the channels by a constant
    inline RGBColor16& operator/=(uint16_t d)
    {
        r /= d;
        g /= d;
        b /= d;
        return *this;
    }

    /// Right shift each of the channels by a constant
    inline RGBColor16& operator>>=(uint16_t d)
    {
        r >>= d;
        g >>= d;
        b >>= d;
        return *this;
    }

    /// Multiply each of the channels by a constant,
    /// saturating each channel at 0xFF.
    inline RGBColor16& operator*=(uint16_t d)
    {
        r = constrain(r * d, 0, 0xFFFF);
        g = constrain(g * d, 0, 0xFFFF);
        b = constrain(b * d, 0, 0xFFFF);
        return *this;
    }

    /// @copydoc operator|=
    inline RGBColor16& operator|=(uint16_t d)
    {
        if (d > r)
            r = d;
        if (d > g)
            g = d;
        if (d > b)
            b = d;
        return *this;
    }

    /// "and" operator brings each channel down to the lower of the two values
    inline RGBColor16& operator&=(const RGBColor16& rhs)
    {
        if (rhs.r < r)
            r = rhs.r;
        if (rhs.g < g)
            g = rhs.g;
        if (rhs.b < b)
            b = rhs.b;
        return *this;
    }

    /// @copydoc operator&=
    inline RGBColor16& operator&=(uint16_t d)
    {
        if (d < r)
            r = d;
        if (d < g)
            g = d;
        if (d < b)
            b = d;
        return *this;
    }

    /// Invert each channel
    inline RGBColor16 operator-() const
    {
        RGBColor16 retval;
        retval.r = 255 - r;
        retval.g = 255 - g;
        retval.b = 255 - b;
        return retval;
    }
};

/// Representation of an RGB pixel (Red, Green, Blue)
struct RGBWColor16 {
    union {
        struct {
            union {
                uint16_t r; ///< Red channel value
                uint16_t red; ///< @copydoc r
            };
            union {
                uint16_t g; ///< Green channel value
                uint16_t green; ///< @copydoc g
            };
            union {
                uint16_t b; ///< Blue channel value
                uint16_t blue; ///< @copydoc b
            };
            union {
                uint16_t w; ///< White channel value
                uint16_t white; ///< @copydoc b
            };
        };
        /// Access the red, green, and blue data as an array.
        /// Where:
        /// * `raw[0]` is the red value
        /// * `raw[1]` is the green value
        /// * `raw[2]` is the blue value
        /// * `raw[3]` is the White value
        uint16_t raw[4];
    };

    /// Array access operator to index into the RGBWColor16 object
    /// @param x the index to retrieve (0-2)
    /// @returns the RGBWColor16::raw value for the given index
    inline uint16_t& operator[](uint16_t x) __attribute__((always_inline))
    {
        return raw[x];
    }

    /// Array access operator to index into the RGBWColor16 object
    /// @param x the index to retrieve (0-2)
    /// @returns the RGBWColor16::raw value for the given index
    inline const uint16_t& operator[](uint16_t x) const __attribute__((always_inline))
    {
        return raw[x];
    }

    /// Default constructor
    /// @warning Default values are UNITIALIZED!
    inline RGBWColor16() __attribute__((always_inline)) = default;

    /// Allow construction from red, green, and blue
    /// @param ir input red value
    /// @param ig input green value
    /// @param ib input blue value
    constexpr RGBWColor16(uint16_t ir, uint16_t ig, uint16_t ib, uint16_t iw) __attribute__((always_inline))
        : r(ir)
        , g(ig)
        , b(ib)
        , w(iw)
    {
    }

    /// Allow copy construction
    inline RGBWColor16(const RGBWColor16& rhs) __attribute__((always_inline)) = default;

    /// Allow assignment from one RGB struct to another
    inline RGBWColor16& operator=(const RGBWColor16& rhs) __attribute__((always_inline)) = default;

    // /// Allow assignment from 32-bit (really 24-bit) 0xRRGGBB color code
    // /// @param colorcode a packed 24 bit color code
    // inline RGBWColor16& operator= (const uint32_t colorcode) __attribute__((always_inline))
    // {
    //     r = (colorcode >> 16) & 0xFF;
    //     g = (colorcode >>  8) & 0xFF;
    //     b = (colorcode >>  0) & 0xFF;
    //     return *this;
    // }

    /// Allow assignment from red, green, and blue
    /// @param nr new red value
    /// @param ng new green value
    /// @param nb new blue value
    /// @param nw new white value
    inline RGBWColor16& setRGBW(uint16_t nr, uint16_t ng, uint16_t nb, uint16_t nw) __attribute__((always_inline))
    {
        r = nr;
        g = ng;
        b = nb,
        w = nw;
        return *this;
    }

    // /// Allow assignment from hue, saturation, and value
    // /// @param hue color hue
    // /// @param sat color saturation
    // /// @param val color value (brightness)
    // inline RGBWColor16& setHSV (uint16_t hue, uint16_t sat, uint16_t val) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( HSVColor16(hue, sat, val), *this);
    //     return *this;
    // }

    // /// Allow assignment from just a hue.
    // /// Saturation and value (brightness) are set automatically to max.
    // /// @param hue color hue
    // inline RGBWColor16& setHue (uint16_t hue) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( HSVColor16(hue, 255, 255), *this);
    //     return *this;
    // }

    // /// Allow assignment from HSV color
    // inline RGBWColor16& operator= (const HSVColor16& rhs) __attribute__((always_inline))
    // {
    //     hsv2rgb_rainbow( rhs, *this);
    //     return *this;
    // }

    /// Add one RGBWColor16 to another, saturating at 0xFF for each channel
    inline RGBWColor16& operator+=(const RGBWColor16& rhs)
    {
        r = constrain(r + rhs.r, 0, 0xFFFF);
        g = constrain(g + rhs.g, 0, 0xFFFF);
        b = constrain(b + rhs.b, 0, 0xFFFF);
        w = constrain(w + rhs.b, 0, 0xFFFF);
        return *this;
    }

    /// Add a constant to each channel, saturating at 0xFF.
    /// @note This is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. RGBWColor16::Red) and an 8-bit one (RGBWColor16::Blue)
    inline RGBWColor16& addToRGBW(uint16_t d)
    {
        r = constrain(r + d, 0, 0xFFFF);
        g = constrain(g + d, 0, 0xFFFF);
        b = constrain(b + d, 0, 0xFFFF);
        w = constrain(w + d, 0, 0xFFFF);
        return *this;
    }

    /// Subtract one RGBWColor16 from another, saturating at 0x00 for each channel
    inline RGBWColor16& operator-=(const RGBWColor16& rhs)
    {
        r = constrain(r - rhs.r, 0, 0xFFFF);
        g = constrain(r - rhs.g, 0, 0xFFFF);
        b = constrain(r - rhs.b, 0, 0xFFFF);
        w = constrain(w - rhs.b, 0, 0xFFFF);
        return *this;
    }

    /// Subtract a constant from each channel, saturating at 0x00.
    /// @note This is NOT an operator+= overload because the compiler
    /// can't usefully decide when it's being passed a 32-bit
    /// constant (e.g. RGBWColor16::Red) and an 8-bit one (RGBWColor16::Blue)
    inline RGBWColor16& subtractFromRGBW(uint16_t d)
    {
        r = constrain(r - d, 0, 0xFFFF);
        g = constrain(g - d, 0, 0xFFFF);
        b = constrain(b - d, 0, 0xFFFF);
        w = constrain(w - d, 0, 0xFFFF);
        return *this;
    }

    /// Subtract a constant of '1' from each channel, saturating at 0x00
    inline RGBWColor16& operator--() __attribute__((always_inline))
    {
        subtractFromRGBW(1);
        return *this;
    }

    /// @copydoc operator--
    inline RGBWColor16 operator--(int) __attribute__((always_inline))
    {
        RGBWColor16 retval(*this);
        --(*this);
        return retval;
    }

    /// Add a constant of '1' from each channel, saturating at 0xFF
    inline RGBWColor16& operator++() __attribute__((always_inline))
    {
        addToRGBW(1);
        return *this;
    }

    /// @copydoc operator++
    inline RGBWColor16 operator++(int) __attribute__((always_inline))
    {
        RGBWColor16 retval(*this);
        ++(*this);
        return retval;
    }

    /// Divide each of the channels by a constant
    inline RGBWColor16& operator/=(uint16_t d)
    {
        r /= d;
        g /= d;
        b /= d;
        w /= d;
        return *this;
    }

    /// Right shift each of the channels by a constant
    inline RGBWColor16& operator>>=(uint16_t d)
    {
        r >>= d;
        g >>= d;
        b >>= d;
        w >>= d;
        return *this;
    }

    /// Multiply each of the channels by a constant,
    /// saturating each channel at 0xFF.
    inline RGBWColor16& operator*=(uint16_t d)
    {
        r = constrain(r * d, 0, 0xFFFF);
        g = constrain(g * d, 0, 0xFFFF);
        b = constrain(b * d, 0, 0xFFFF);
        w = constrain(w * d, 0, 0xFFFF);
        return *this;
    }

    /// @copydoc operator|=
    inline RGBWColor16& operator|=(uint16_t d)
    {
        if (d > r)
            r = d;
        if (d > g)
            g = d;
        if (d > b)
            b = d;
        if (d > w)
            w = d;
        return *this;
    }

    /// "and" operator brings each channel down to the lower of the two values
    inline RGBWColor16& operator&=(const RGBWColor16& rhs)
    {
        if (rhs.r < r)
            r = rhs.r;
        if (rhs.g < g)
            g = rhs.g;
        if (rhs.b < b)
            b = rhs.b;
        if (rhs.w < w)
            w = rhs.w;
        return *this;
    }

    /// @copydoc operator&=
    inline RGBWColor16& operator&=(uint16_t d)
    {
        if (d < r)
            r = d;
        if (d < g)
            g = d;
        if (d < b)
            b = d;
        if (d < w)
            w = d;
        return *this;
    }

    /// Invert each channel
    inline RGBWColor16 operator-() const
    {
        RGBWColor16 retval;
        retval.r = 255 - r;
        retval.g = 255 - g;
        retval.b = 255 - b;
        retval.w = 255 - w;
        return retval;
    }
};
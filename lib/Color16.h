#ifndef COLOR_16_H
#define COLOR_16_H
// Shamelessly mimiced from fastled.io

struct CHSV16 {
    union {
		struct {
		    union {
		        uint16_t hue;
		        uint16_t h; };
		    union {
		        uint16_t saturation;
		        uint16_t sat;
		        uint16_t s; };
		    union {
		        uint16_t value;
		        uint16_t val;
		        uint16_t v; };
		};
		uint16_t raw[3];
	};

    // default values are UNITIALIZED
    inline CHSV16() __attribute__((always_inline))
    {
    }

    // allow construction from H, S, V
    inline CHSV16( uint16_t ih, uint16_t is, uint16_t iv) __attribute__((always_inline))
        : h(ih), s(is), v(iv)
    {
    }

    // allow copy construction
    inline CHSV16(const CHSV16& rhs) __attribute__((always_inline))
    {
        h = rhs.h;
        s = rhs.s;
        v = rhs.v;
    }

    inline CHSV16( const CHSV& rhs) __attribute__((always_inline))
    {
      h = rhs.h << 8;
      s = rhs.s << 8;
      v = rhs.v << 8;
    }

    inline CHSV16& operator= (const CHSV16& rhs) __attribute__((always_inline))
    {
        h = rhs.h;
        s = rhs.s;
        v = rhs.v;
        return *this;
    }

    inline CHSV16& setHSV(uint16_t ih, uint16_t is, uint16_t iv) __attribute__((always_inline))
    {
        h = ih;
        s = is;
        v = iv;
        return *this;
    }
};

#endif

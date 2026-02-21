#ifndef GZ_CAPTURE_H
#define GZ_CAPTURE_H

#include "d/d_drawlist.h"

class gzCapture_c : public dDlst_base_c {
public:
    virtual void draw();
    virtual ~gzCapture_c() {}

    static const u8 CAPTURE_DIM_ALPHA = 128;

    gzCapture_c() {
        mFlag = 0;
        mAlpha = CAPTURE_DIM_ALPHA;
    }

    void setCaptureFlag() { mFlag = 1; }
    void disable() { mFlag = 0; }
    bool isCapturing() { return mFlag != 0; }

private:
    u8 mFlag;
    u8 mAlpha;
};

#endif

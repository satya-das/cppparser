enum SkEncodedOrigin {
    kTopLeft_SkEncodedOrigin     = 1, // Default
    kTopRight_SkEncodedOrigin    = 2, // Reflected across y-axis
    kBottomRight_SkEncodedOrigin = 3, // Rotated 180
    kBottomLeft_SkEncodedOrigin  = 4, // Reflected across x-axis
    kLeftTop_SkEncodedOrigin     = 5, // Reflected across x-axis, Rotated 90 CCW
    kRightTop_SkEncodedOrigin    = 6, // Rotated 90 CW
    kRightBottom_SkEncodedOrigin = 7 // Reflected across x-axis, Rotated 90 CW
};


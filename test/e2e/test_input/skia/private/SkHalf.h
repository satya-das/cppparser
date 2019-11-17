    asm ("fcvtl %[fs].4s, %[hs].4h   \n"   // vcvt_f32_f16(...)
        : [fs] "=w" (fs)                   // =w: write-only NEON register
        : [hs] "w" (hs.fVec));             //  w: read-only NEON register


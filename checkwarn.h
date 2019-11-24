#pragma once

#include "typedef.h"

#define errnoGT 1
#define errnoEQ 2
#define errnoLT 3

extern int checkwarn(const Warn&, const RawValue&);
extern int writeWarn(int, int, const RawValue&, WarnValue&);
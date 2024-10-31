//------------------------------------------------------------------------
// Copyright(c) 2024 Vargason.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace vargason::jaredfilter {
//------------------------------------------------------------------------
static const Steinberg::FUID kStrainerProcessorUID (0x47C5243B, 0x2155562C, 0x895FECB5, 0xFB791EB7);
static const Steinberg::FUID kStrainerControllerUID (0x9D4355F5, 0x19AD5152, 0xB7F3FD3E, 0x7EB868D3);

#define StrainerVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace vargason::jaredfilter

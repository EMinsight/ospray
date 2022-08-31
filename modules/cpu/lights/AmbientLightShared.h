// Copyright 2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "LightShared.h"

#ifdef __cplusplus
namespace ispc {
#endif // __cplusplus

struct AmbientLight
{
  Light super; // inherited light fields
  vec3f radiance; // emitted RGB radiance

#ifdef __cplusplus
  AmbientLight() : radiance(1.f) {}
};
#ifdef OSPRAY_TARGET_SYCL
void *AmbientLight_sample_addr();
void *AmbientLight_eval_addr();
#endif
} // namespace ispc
#else
};
#endif // __cplusplus

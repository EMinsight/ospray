// Copyright 2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "render/Material.h"
// ispc shared
#include "AlloyShared.h"

namespace ospray {
namespace pathtracer {

struct Alloy : public AddStructShared<Material, ispc::Alloy>
{
  Alloy(api::ISPCDevice &device);

  virtual std::string toString() const override;

  virtual void commit() override;

 private:
  MaterialParam3f color;
  MaterialParam3f edgeColor;
  MaterialParam1f roughness;
};

} // namespace pathtracer
} // namespace ospray

#pragma once

#include "Solver/time_stepping/DirectGhostTimeCluster.h"
#ifdef ACL_DEVICE
#include "Solver/time_stepping/GhostTimeClusterWithCopy.h"
#endif // ACL_DEVICE
#include "Parallel/MPI.h"
#include "memory"

namespace seissol::time_stepping {
struct GhostTimeClusterFactory {
  public:
  static std::unique_ptr<AbstractGhostTimeCluster> get(double maxTimeStepSize,
                                                       int timeStepRate,
                                                       int globalTimeClusterId,
                                                       int otherGlobalTimeClusterId,
                                                       const MeshStructure* meshStructure,
                                                       MPI::DataTransferMode mode) {
    switch (mode) {
#ifdef ACL_DEVICE
    case MPI::DataTransferMode::CopyInCopyOutHost: {
      using ghostCluster_t = GhostTimeClusterWithCopy<MPI::DataTransferMode::CopyInCopyOutHost>;
      return std::make_unique<ghostCluster_t>(maxTimeStepSize,
                                              timeStepRate,
                                              globalTimeClusterId,
                                              otherGlobalTimeClusterId,
                                              meshStructure);
    }
    case MPI::DataTransferMode::CopyInCopyOutDevice: {
      using ghostCluster_t =
          GhostTimeClusterWithCopy<MPI::DataTransferMode::CopyInCopyOutDevice>;
      return std::make_unique<ghostCluster_t>(maxTimeStepSize,
                                              timeStepRate,
                                              globalTimeClusterId,
                                              otherGlobalTimeClusterId,
                                              meshStructure);
    }
#endif // ACL_DEVICE
    case MPI::DataTransferMode::Direct: {
      return std::make_unique<DirectGhostTimeCluster>(maxTimeStepSize,
                                                      timeStepRate,
                                                      globalTimeClusterId,
                                                      otherGlobalTimeClusterId,
                                                      meshStructure);
    }
    default: {
      return nullptr;
    }
    }
  }
};
} // namespace seissol::time_stepping
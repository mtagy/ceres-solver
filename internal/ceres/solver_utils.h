// Ceres Solver - A fast non-linear least squares minimizer
// Copyright 2015 Google Inc. All rights reserved.
// http://ceres-solver.org/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: sameeragarwal@google.com (Sameer Agarwal)

#ifndef CERES_INTERNAL_SOLVER_UTILS_H_
#define CERES_INTERNAL_SOLVER_UTILS_H_

#include <algorithm>
#include <string>

#include "ceres/internal/disable_warnings.h"
#include "ceres/internal/export.h"
#include "ceres/iteration_callback.h"
#include "ceres/types.h"

namespace ceres::internal {

template <typename SummaryType>
bool IsSolutionUsable(const SummaryType& summary) {
  return (summary.termination_type == CONVERGENCE ||
          summary.termination_type == NO_CONVERGENCE ||
          summary.termination_type == USER_SUCCESS);
}

template <typename SummaryType>
void SetSummaryFinalCost(SummaryType* summary) {
  summary->final_cost = summary->initial_cost;
  // We need the loop here, instead of just looking at the last
  // iteration because the minimizer maybe making non-monotonic steps.
  for (int i = 0; i < summary->iterations.size(); ++i) {
    const IterationSummary& iteration_summary = summary->iterations[i];
    summary->final_cost = std::min(iteration_summary.cost, summary->final_cost);
  }
}

CERES_NO_EXPORT
std::string VersionString();

}  // namespace ceres::internal

#include "ceres/internal/reenable_warnings.h"

#endif  // CERES_INTERNAL_SOLVER_UTILS_H_

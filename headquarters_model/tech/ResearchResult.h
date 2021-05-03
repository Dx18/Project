#pragma once

namespace headquarters_model::tech {

/** Result of research. */
enum ResearchResult {
  /** Successfully researched. */
  kResearched,
  /** Tech level is already max. */
  kAlreadyMaxLevel,
  /** Not enough resources to research. */
  kNotEnoughResources
};

}

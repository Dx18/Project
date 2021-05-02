#include "WorldEntities.h"

namespace world::entities {

WorldEntities::WorldEntities(std::vector<std::unique_ptr<unit::Unit>> &&player_units,
                             std::vector<std::unique_ptr<unit::Unit>> &&enemy_units)
    : player_units_(std::move(player_units)), enemy_units_(std::move(enemy_units)),
      player_unit_id_to_index_(), player_index_to_unit_id_(),
      enemy_unit_id_to_index_(), enemy_index_to_unit_id_() {
  for (size_t i = 0; i < player_units_.size(); ++i) {
    player_unit_id_to_index_[i] = i;
    player_index_to_unit_id_[i] = i;
  }
  for (size_t i = 0; i < enemy_units_.size(); ++i) {
    enemy_unit_id_to_index_[player_units_.size() + i] = i;
    enemy_index_to_unit_id_[i] = player_units_.size() + i;
  }
}

void WorldEntities::Update(std::chrono::microseconds delta) {
  for (size_t i = 0; i < projectiles_.size(); ++i) {
    projectiles_[i].Update(delta);
    if (!projectiles_[i].IsAlive()) {
      RemoveProjectile(i);
    }
  }
}

size_t WorldEntities::PlayerUnitID(size_t index) const {
  auto iter = player_index_to_unit_id_.find(index);
  if (iter != player_index_to_unit_id_.end()) {
    return iter->second;
  }

  throw std::runtime_error("player's unit with given ID does not exist");
}

size_t WorldEntities::EnemyUnitID(size_t index) const {
  auto iter = enemy_index_to_unit_id_.find(index);
  if (iter != enemy_index_to_unit_id_.end()) {
    return iter->second;
  }

  throw std::runtime_error("enemy's unit with given ID does not exist");
}

unit::Unit &WorldEntities::GetUnit(size_t unit_id) {
  const WorldEntities *const_this = this;
  return const_cast<unit::Unit &>(const_this->GetUnit(unit_id));
}

const unit::Unit &WorldEntities::GetUnit(size_t unit_id) const {
  auto iter = player_unit_id_to_index_.find(unit_id);
  if (iter != player_unit_id_to_index_.end()) {
    return *player_units_[iter->second];
  }

  iter = enemy_unit_id_to_index_.find(unit_id);
  if (iter != enemy_unit_id_to_index_.end()) {
    return *enemy_units_[iter->second];
  }

  throw std::runtime_error("unit with given id does not exist");
}

const std::vector<std::unique_ptr<unit::Unit>> &WorldEntities::PlayerUnits() const {
  return player_units_;
}

const std::vector<std::unique_ptr<unit::Unit>> &WorldEntities::EnemyUnits() const {
  return enemy_units_;
}

size_t WorldEntities::CreateProjectile(const Projectile &projectile) {
  size_t projectile_id = projectile_id_counter_;
  ++projectile_id_counter_;

  projectile_id_to_index_.insert({projectile_id, projectiles_.size()});
  projectile_index_to_id_.insert({projectiles_.size(), projectile_id});
  projectiles_.push_back(projectile);

  return projectile_id;
}

bool WorldEntities::IsProjectileAlive(size_t projectile_id) const {
  auto iter = projectile_id_to_index_.find(projectile_id);
  return iter != projectile_id_to_index_.end() && projectiles_[iter->second].IsAlive();
}

const std::vector<Projectile> &WorldEntities::Projectiles() const {
  return projectiles_;
}

void WorldEntities::RemoveProjectile(size_t index) {
  size_t removed_projectile_id = projectile_index_to_id_[index];
  size_t moved_projectile_id = projectile_index_to_id_[projectiles_.size() - 1];

  projectile_index_to_id_[index] = moved_projectile_id;
  projectile_id_to_index_[moved_projectile_id] = index;
  projectile_index_to_id_.erase(projectiles_.size() - 1);
  projectile_id_to_index_.erase(removed_projectile_id);

  std::swap(projectiles_[index], projectiles_.back());
  projectiles_.pop_back();
}

}

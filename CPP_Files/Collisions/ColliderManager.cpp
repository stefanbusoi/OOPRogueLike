//
// Created by fanel012 on 5/30/25.
//

#include "ColliderManager.hpp"

#include "Collider.h"
#include "CoreFunctionality/Game.hpp"

ColliderManager::ColliderManager():BaseGameObject("Collider Manager",sf::Transform::Identity) {
    m_updateOrder=UpdateOrder::Collisions;
}

void ColliderManager::addGameObjectToGame() {
    BaseGameObject::addGameObjectToGame();
}

void ColliderManager::removeGameObjectFromGame() {
    BaseGameObject::removeGameObjectFromGame();
}


void ColliderManager::init() {
    BaseGameObject::init();
}

void ColliderManager::update(float deltaTime) {
  (void)deltaTime;

  //create a separate list of colliders so it dosen t loop over a list that can be changed
  std::vector<std::shared_ptr<Collider>> colliders;
  for (auto collider: Game::getInstance()->getColliders()){
    colliders.push_back(dynamic_pointer_cast<Collider>(collider->shared_from_this()));
  }

  for (const auto& Collider1:colliders) {
    std::shared_ptr<BaseGameObject> parent1 = Collider1->getParent().lock();
    for (const auto &Collider2: colliders) {
      std::shared_ptr<BaseGameObject> parent2 = Collider2->getParent().lock();

      //if this is inside colliders
      if (!Game::getInstance()->getColliders().contains(Collider1.get())) {
        break;
      }

      //if the first object is static the collision shoudn t be checked
      std::shared_ptr<PhysicObject> Physics1 = parent1->getGameObjectOfType<PhysicObject>();
      if (Physics1 == nullptr)
        continue;

      //If is inside colliders
      if (!Game::getInstance()->getColliders().contains(Collider2.get())) {
        continue;
      }

      //if the parent is the same don t check collisions
      if (parent2->getId() == parent1->getId())
        continue;

      //check if the collision shoud happen;
      if (Collider::ColliderMatrix[(int) Collider2->getColliderMask()][(int) Collider1->getColliderMask()] == 0)
        continue;
      auto collisionData = Collider::checkCollision(*Collider1, *Collider2);

      std::weak_ptr<PhysicObject> Physics2Weak = parent2->getGameObjectOfType<PhysicObject>();
      if (collisionData.collided == true) {
        //If Physics2Weak is expired then the second object is static
        if (Physics2Weak.expired()) {
          //Collision if only the first object is dynamic
          sf::Vector2f relativeVelocity = Physics1->getSpeed();

          float velocityAlongNormal = relativeVelocity.dot(collisionData.normal);

          float e = Physics1->getElasticity();

          float invMass1 = 1.0f / Physics1->getMass();

          float j = -(1 + e) * velocityAlongNormal;

          sf::Vector2f impulse = j * collisionData.normal;
          Physics1->setSpeed(Physics1->getSpeed() + invMass1 * impulse);

          parent1->globalMoveTransform(-collisionData.normal * collisionData.penetration);
        } else {
          //collision only if both objects are dynamics
          std::shared_ptr<PhysicObject> Physics2 = Physics2Weak.lock();
          float totalWeight = Physics1->getMass() + Physics2->getMass();
          if (totalWeight == 0) totalWeight = 1;

          float move1 = Physics2->getMass() / totalWeight;
          float move2 = Physics1->getMass() / totalWeight;

          sf::Vector2f speed1 = Physics1->getSpeed();
          sf::Vector2f speed2 = Physics2->getSpeed();
          sf::Vector2f relativeVelocity = speed2 - speed1;

          float velocityAlongNormal = relativeVelocity.dot(collisionData.normal);

          float e = std::min(Physics1->getElasticity(), Physics2->getElasticity());

          float invMass1 = 1.0f / Physics1->getMass();
          float invMass2 = 1.0f / Physics2->getMass();

          float j = -(1 + e) * velocityAlongNormal;
          j /= invMass1 + invMass2;

          sf::Vector2f impulse = j * collisionData.normal;
          Physics1->setSpeed(Physics1->getSpeed() - invMass1 * impulse);
          Physics2->setSpeed(Physics2->getSpeed() + invMass2 * impulse);

          parent1->globalMoveTransform(-collisionData.normal * collisionData.penetration * move1);
          parent2->globalMoveTransform(collisionData.normal * collisionData.penetration * move2);
        }
        Collider1->getOnCollide().callFunction(*Collider1, *Collider2);
        Collider2->getOnCollide().callFunction(*Collider2, *Collider1);
      } //If collided==true;
    } //For each Game Object
  }
}



//
// Created by stefa on 5/4/2025.
//

#include "Firearm.hpp"

#include "../Game.hpp"
#include "../Render/ShapeRenderer.hpp"
#include "../UtilityiesFunctions.hpp"

void Firearm::Fire() {
    if (lastShot+m_timer<=CurrentTimer) {
        auto* bullet=Game::getInstance()->EmplaceClone(*bulletPrefab);
        bullet->GlobalMoveTransform(-Utils::getPosition(bullet->getGlobalTransform())+Utils::getPosition(getGlobalTransform()));
        lastShot=CurrentTimer;
        bullet->getLocalTransform().rotate(-Utils::getAngle(getGlobalTransform())+sf::degrees(180.0f));
        for (auto i:bullet->getChildrens()) {
            PhysicObject* x=dynamic_cast<PhysicObject*>(i);
            if (x!=nullptr) {
                sf::Vector2f bulletSpeed;
                bulletSpeed={1000.0f,0.0f};
                bulletSpeed=bulletSpeed.rotatedBy(-Utils::getAngle(getGlobalTransform())+sf::degrees(90.0f));
                x->SetSpeed(bulletSpeed);
                break;
            }
        }
    }
}

void Firearm::update(float deltaTime) {
    CurrentTimer += deltaTime;
}

Firearm::Firearm(const std::string &name, sf::Transform transform):GameObject(name,transform,nullptr) {
    lastShot=0;
    m_timer=0.5;
    CurrentTimer=0;
    sf::Transform BulletTransform;
    BulletTransform.translate({0.0f,-2.f});
    BulletTransform.scale({10.f,10.f});
    bulletPrefab=new GameObject("Bullet",BulletTransform);
    sf::Transform BulletTransformHitbox;
    BulletTransformHitbox.scale({0.3f,0.3f});
    auto col=bulletPrefab->EmplaceGameObject<Collider>(CollisionType::Dynamic,ColliderMask::Bullets,GeometryShape::Circle,BulletTransformHitbox);
    col->getOnCollide()=[](Collider& ths,Collider& col) {
        GameObject* ph = nullptr;
        GameObject* cl = nullptr;
        auto parent=ths.getParent();
        for (auto i:parent->getChildrens()) {
            if (dynamic_cast<PhysicObject*>(i)) {
                ph=dynamic_cast<PhysicObject*>(i);
            }
            if (dynamic_cast<Collider*>(i)) {
                cl=dynamic_cast<Collider*>(i);
            }
        }
        Game::getInstance()->MarkForDeletion(cl);
        Game::getInstance()->MarkForDeletion(ph);

        ths.getParent()->SetParent(col.getParent());

    };
    bulletPrefab->EmplaceGameObject<ShapeRenderer>("CircleRenderer",BulletTransform, "Assets/arrow.png", RenderOrder::Player,GeometryShape::Square);
    bulletPrefab->EmplaceGameObject<PhysicObject>(40.0f,0.0f);
    sf::Transform tr=sf::Transform::Identity;
    tr.translate(sf::Vector2f(0.0f,40.0f)).scale(sf::Vector2f(100.f, -130.0f));
    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, std::filesystem::path("Assets/bow_arrow.png"), RenderOrder::PostProcessing,GeometryShape::Square);
}


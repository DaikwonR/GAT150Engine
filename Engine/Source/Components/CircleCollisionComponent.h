#pragma once
#include "CollisionComponent.h"

class CircleCollisionComponent : public CollisionComponent
{
public:
	

private:
	CLASS_DECLARATION(CircleCollisionComponent)
	CLASS_PROTOTYPE(CircleCollisionComponent)
	// Inherited via CollisionComponent
	void Initialize() override;
	void Update(float dt) override;
	bool CheckCollision(const CollisionComponent* collision) override;

public:
	float radius = 0;
};

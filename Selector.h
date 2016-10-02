#pragma once
#include "Entity.h"
#include "Interpolate.h"
struct EventDetails;
class Selector :
	public Entity
{
public:
	Selector(EntityManager* entityManager);
	~Selector();

	void move(const Direction dir) override;
	void draw(sf::RenderWindow& window) override;
	void update(const float deltaTime) override;

private:

	void applyTexture();
	int m_xMovement;
	int m_yMovement;

	bool m_holdingJewel;

	void reactToInput(EventDetails* eventDetails);
	void selectJewel();
	void placeJewel();
	std::string m_placedSelectorName;
	sf::Texture* m_placedSelectorTexture;
	sf::Sprite m_placedSelector;
	Interpolate m_interpolate;
	sf::Vector2f m_newPos;
};


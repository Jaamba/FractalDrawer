#pragma once
#include <SFML/Graphics.hpp>

class Function : public sf::Drawable {
protected:
	int m_resX;
	int m_resY;

	sf::VertexArray m_vertexes;

public:
	Function(int resX, int resY) :
		m_resX(resX), m_resY(resY), m_vertexes(sf::PrimitiveType::Points, resX*resY) {

		if (m_resX < 0 || m_resY < 0) throw "Error: Resolution cannot be less than 0";
	}

	//virtual deconstructor in abstract class
	virtual ~Function() {}

	virtual void assignPoints(const sf::Vector2<double>& upLeft, const sf::View& view) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#include "Function.h"
#include <SFML/Graphics.hpp>
 
void Function::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw the vertex array
	target.draw(m_vertexes, states);
}
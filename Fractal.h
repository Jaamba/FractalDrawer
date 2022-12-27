#pragma once
#include <SFML/Graphics.hpp>
#include "Function.h"

class Fractal : public Function {
	private:
		unsigned int m_iterations;

	public:
		Fractal(int resX, int resY, unsigned int iterations) : Function(resX, resY), m_iterations(iterations) {
			m_vertexes.resize(0);
		}
		void setPrecision(unsigned int precision);
		unsigned int getPrecision();

		//assigns the points of the fractal starting from the left corner of a view: resX*resY points are always drawn
		virtual void assignPoints(const sf::Vector2<double>& upLeft, const sf::View& view) override;
};

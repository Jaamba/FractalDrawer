#include "Fractal.h"
#include <iostream>

void Fractal::assignPoints(const sf::Vector2<double>& upLeft, const sf::View& view) {
	m_vertexes.clear();
	sf::Vector2f viewSize = view.getSize();

	int t = -1;
	for (double i = 0; i <= viewSize.x; i+=(double)(viewSize.x/m_resX)) {
		for (double k = 0; k <= viewSize.y; k+=(double)(viewSize.y / m_resY)) {

			sf::Vector2<double> currentPoint(upLeft.x +  i, upLeft.y +  k);
			sf::Vector2<double> currentPointScaled(currentPoint.x / (m_resX / 3) - 1.5f, currentPoint.y / (m_resY / 3) - 1.5f);

			//if (currentPointScaled.x < -2 || currentPointScaled.x > 0.47f) continue;
			//if (currentPointScaled.y < -1.12f || currentPointScaled.y > 1.12f) continue;

			unsigned int n = 0;
			double x = 0;
			double y = 0;
			while (x*x + y*y <= 4) {
				double xTmp = x * x - y * y + currentPointScaled.x;
				y = 2 * x * y + currentPointScaled.y;
				x = xTmp;
				
				if (++n > m_iterations) {
					break; continue;
				}
			}

			m_vertexes.append(sf::Vector2f(currentPoint.x, currentPoint.y));
			m_vertexes[++t].color = sf::Color(n*n, n, n*n);
		}
	}
}

void Fractal::setPrecision(unsigned int precision) {
	m_iterations = precision;
}
unsigned int Fractal::getPrecision() {
	return m_iterations;
}
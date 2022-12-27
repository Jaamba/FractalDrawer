#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fractal.h"

//#define DEBUG_INFO

int main(int argc, char* argv[]) {

	//variables
	constexpr int screenWidth = 900;
	constexpr int screenHeight = 900;
	constexpr int resX = screenWidth;
	constexpr int resY = screenHeight;
	constexpr float zoomSpeed = 1.1f;
	const sf::Color axysColor = sf::Color::White;
	const sf::Vector2f zoomBounds(0.00001f, 1000.0f);
	constexpr int fractalPrecision = 100;
	
	int zoom = 1;
	sf::Vector2i lastMousePosition = sf::Mouse::getPosition();
	static sf::Vector2f deltaMouse{};
	float currentZoom{1};
	sf::Vector2<double> upLeftP{};

	//defines window and settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractal drawer", sf::Style::Close, settings);

	//defines view
	sf::View view(window.getDefaultView());

	//defines the x-axys and the y-axys
	sf::VertexArray axys;
	axys.setPrimitiveType(sf::PrimitiveType::Lines);
	//x-axys:
	sf::Vertex left(sf::Vector2f(0, screenHeight / 2), axysColor);
	sf::Vertex right(sf::Vector2f(screenWidth, screenHeight / 2), axysColor);
	axys.append(left);
	axys.append(right);
	//y-axys
	sf::Vertex up(sf::Vector2f(screenWidth/2, screenHeight), axysColor);
	sf::Vertex down(sf::Vector2f(screenWidth/2, 0), axysColor);
	axys.append(up);
	axys.append(down);

	Fractal f(resX, resY, 50);
	f.assignPoints(upLeftP, view);

	while (window.isOpen()) {
		upLeftP = sf::Vector2<double>(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y/2);


		//Event handling
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}

			//zoom system:
			if (event.type == sf::Event::MouseWheelMoved) {
				zoom += event.mouseWheel.delta;

				//uses a formula to calculate the new zoom
				float newZoom = powf(zoomSpeed, zoom);
				currentZoom = newZoom;

				if (currentZoom < zoomBounds.x || currentZoom > zoomBounds.y) continue;

				//redraws the four axys
				sf::Vector2f currentLeftPos = axys[0].position;
				axys[0].position = sf::Vector2f(currentLeftPos.x - 
					(newZoom*screenWidth - view.getSize().x)/2 , currentLeftPos.y);
				sf::Vector2f currentRightPos = axys[1].position;
				axys[1].position = sf::Vector2f(currentRightPos.x + 
					(newZoom*screenWidth - view.getSize().x)/2, currentRightPos.y);
				sf::Vector2f currentUpPos = axys[2].position;
				axys[2].position = sf::Vector2f(currentUpPos.x, currentUpPos.y + 
					(newZoom*screenHeight - view.getSize().y)/2);
				sf::Vector2f currentDownPos = axys[3].position;
				axys[3].position = sf::Vector2f(currentDownPos.x, currentDownPos.y - 
					(newZoom * screenHeight - view.getSize().y)/2);


				//sets the actual size
				view.setSize(sf::Vector2f(newZoom * screenWidth, newZoom * screenHeight));
				upLeftP = sf::Vector2<double>(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);

				//redraws the fractal and sets its precision
				f.setPrecision(fractalPrecision - zoom);
				f.assignPoints(upLeftP, view);
			}

			//movement control
			if (event.type == sf::Event::MouseMoved) {
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

					//calculates the offset between this and the last frame
					deltaMouse.x = (lastMousePosition.x - event.mouseMove.x)*currentZoom;
					deltaMouse.y = (lastMousePosition.y - event.mouseMove.y)*currentZoom;

					//sets the view new position
					view.setCenter(sf::Vector2f(view.getCenter().x + deltaMouse.x, view.getCenter().y + deltaMouse.y));
					
					//redraws the four axys
					sf::Vector2f currentLeftPos = axys[0].position;
					axys[0].position = sf::Vector2f(currentLeftPos.x + deltaMouse.x, screenHeight/2);
					sf::Vector2f currentRightPos = axys[1].position;
					axys[1].position = sf::Vector2f(currentRightPos.x + deltaMouse.x, screenHeight/2);
					sf::Vector2f currentUpPos = axys[2].position;
					axys[2].position = sf::Vector2f(screenWidth/2, currentUpPos.y + deltaMouse.y);
					sf::Vector2f currentDownPos = axys[3].position;
					axys[3].position = sf::Vector2f(screenWidth/2, currentDownPos.y + deltaMouse.y);

					//redraws the fractal
					upLeftP = sf::Vector2<double>(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
					f.assignPoints(upLeftP, view);
				}

				//sets the current position as last for the next frame
				lastMousePosition.x = event.mouseMove.x;
				lastMousePosition.y = event.mouseMove.y;
			}

		} window.clear();

		window.setView(view);

		window.draw(f);
		window.draw(axys);
		
		window.display(); //end-frame actions
	}


	return 0;
}
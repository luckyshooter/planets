#include <SFML/Graphics.hpp>
#include "planet.h"

using namespace sf;

int main()
{
	sf::RenderWindow window(VideoMode(1680, 1050), "SFML works!",sf::Style::Fullscreen);
	sf::CircleShape shape(5.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(5, 5);
	std::vector<planet> liste;
	float mx, my;
	float kraft;
	float kraftx;
	float krafty;
	float time;
	float winkel;
	bool compute=false;
	Clock uhr;
	while (window.isOpen())
	{
		sf::Event event;
		time = 2*uhr.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					compute = !compute;
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				planet input;
				mx = event.mouseButton.x;
				my = event.mouseButton.y;
				input.posx = mx;
				input.posy = my;
				input.vx = 0;
				input.vy = 0;
				input.m = 4200000;
				if (liste.size()%4 == 0)
				{
					input.vx = 1000.0f;
				}
				if (liste.size() % 4 == 1)
				{
					input.vx = -1000.0f;
				}
				if (liste.size() % 4 == 2)
				{
					input.vy = 2000.0f;
				}
				if (liste.size() % 4 == 3)
				{
					input.vy = -2000.0f;
				}
				if (liste.size() == 0)
				{
					input.vx = 0;
					input.m = input.m * 100;
				}
				liste.push_back(input);
			}
		}
		if (compute)
		{
			for (size_t i = 0;i < liste.size();i++)
			{
				liste[i].forcex = 0;
				liste[i].forcey = 0;
				for (size_t k = 0;k < liste.size();k++)
				{
					if ((k != i)/*&&((liste[k].posx - liste[i].posx>1))||(liste[k].posx - liste[i].posx < -1)*/)
					{
						//winkel = std::atan ((std::abs(liste[k].posy - liste[i].posy))/(std::abs(liste[k].posx - liste[i].posx)));
						winkel = std::acos((abs(liste[k].posx-liste[i].posx))/(sqrt((liste[k].posx-liste[i].posx)*(liste[k].posx-liste[i].posx)+((liste[k].posy-liste[i].posy)*(liste[k].posy - liste[i].posy)))));
						kraft = (liste[k].m) / (((liste[k].posx - liste[i].posx)*(liste[k].posx - liste[i].posx)) + ((liste[k].posy - liste[i].posy)*(liste[k].posy - liste[i].posy)));
						kraftx = kraft*std::cos(winkel);
						krafty = kraft*std::sin(winkel);
						if (liste[i].posx < liste[k].posx)
						{
							liste[i].forcex += kraftx;
						}
						else
						{
							liste[i].forcex -= kraftx;
						}
						if (liste[i].posy < liste[k].posy)
						{
							liste[i].forcey += krafty;
						}
						else
						{
							liste[i].forcey -= krafty;
						}
					}
				}
				liste[i].posx = liste[i].posx + liste[i].vx*time + 0.5f*liste[i].forcex*time*time;
				liste[i].vx = liste[i].vx + liste[i].forcex*time;
				liste[i].posy += liste[i].vy*time + 0.5f*liste[i].forcey*time*time;
				liste[i].vy += liste[i].forcey*time;
			}
		}
		window.clear();
		for (size_t i = 0;i < liste.size();i++)
		{
			shape.setPosition(liste[i].posx, liste[i].posy);
			if (i % 4 == 0) shape.setFillColor(Color::Green);
			if (i % 4 == 1) shape.setFillColor(Color::Red);
			if (i % 4 == 2) shape.setFillColor(Color::Yellow);
			if (i % 4 == 3) shape.setFillColor(Color::Magenta);
			window.draw(shape);
		}
		window.draw(shape);
		window.display();
	}

	return 0;
}
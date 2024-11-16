// standard cpp
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <fstream>
#include <vector>

// sfml libraries
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

// creating struct to define position in the plane

struct windowRes
{
	size_t w;
	size_t h;
};

struct fontInfo
{
	std::string	fontName;
	size_t		size;
	size_t		r;
	size_t		g;
	size_t		b;
};

struct positionXY 
{
	int x;
	int y;
};

struct speedXY 
{
	float dx;
	float dy;
};

struct RGBcode 
{
	int r;
	int b;
	int g;
};


class Circle : public sf::CircleShape 
{
private:
	sf::Vector2f	spd;
	std::string	m_shapeName;
	sf::Font	m_font;
	fontInfo	m_fontInfo;

	void hitLeft(const windowRes& window) 
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if (x <= 0) 
		{
			this->spd.x *= -1;	
		}
	}

	void hitTop(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if (y <= 0) 
		{
			this->spd.y *= -1;	
		}	
	}

	void hitRight(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if ((x + 2 * this->getRadius()) >= window.w) 
		{
			this->spd.x *= -1;	
		}	
	}

	void hitBottom(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if ((y + 2 * this->getRadius()) >= window.h) 
		{
			this->spd.y *= -1;	
		}
	}
public:
	// constructor
	Circle(float r, std::string name) 
		:sf::CircleShape(r), 
		m_shapeName(name)
	{};
	
	void describe() const
	{
		std::cout << "Circle Radius: " << this->getRadius() << std::endl;
	}

	void setSpeed(const sf::Vector2f& spd)
	{
		this->spd = spd;
	}

	sf::Vector2f getSpeed() const
	{
		return this->spd;
	}

	void hitCorner(const windowRes& window) 
	{
		this->hitLeft(window);
		this->hitTop(window);
		this->hitRight(window);
		this->hitBottom(window);

	}
	sf::Text drawText() const
	{
		// First I need to get the font before I can draw the text into the screen
		// in sfml library, there is no standard font included.

		sf::Text shapeT;

		sf::Vector2f curPos = this->getPosition();

	//	std::cout << this->getRadius() << std::endl;
	//	std::cout << float(sizeof(this->m_shapeName)/2.0) << std::endl;

		float newX = this->getRadius() + curPos.x - 3*this->m_shapeName.length();
		float newY = this->getRadius() + curPos.y - float(this->m_fontInfo.size)/2;

		sf::Vector2f newPos(newX, newY);

		shapeT.setFont(this->m_font);
		shapeT.setPosition(newPos);
		shapeT.setString(this->m_shapeName);
		shapeT.setCharacterSize(this->m_fontInfo.size);

		return shapeT;

	}

	void getFont(const sf::Font& myFont, const fontInfo& myFontInfo)
	{
		//loading font to draw it in the canvas
		this->m_font = myFont;
		this->m_fontInfo = myFontInfo;
	}
	
};

class Rect: public sf::RectangleShape 
{
private:
	sf::Vector2f	spd;
	std::string	m_shapeName;
	sf::Font	m_font;
	fontInfo	m_fontInfo;


	void hitLeft(const windowRes& window) 
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if (x <= 0) 
		{
			this->spd.x *= -1;	
		}
	}

	void hitTop(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;

		if (y <= 0) 
		{
			this->spd.y *= -1;	
		}	
	}

	void hitRight(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;
		
		sf::Vector2f size = getSize();
		float w = size.x, h = size.y;

		if ((x + w) >= window.w) 
		{
			this->spd.x *= -1;	
		}	
	}

	void hitBottom(const windowRes& window)
	{
		sf::Vector2f pos = this->getPosition();	
		float x = pos.x, y = pos.y;
	
		sf::Vector2f size = getSize();
		float w = size.x, h = size.y;

		if ((y + h) >= window.h) 
		{
			this->spd.y *= -1;	
		}
	}

public:
	// constructor
	Rect(float w, float h, std::string name) 
		:sf::RectangleShape(sf::Vector2f(w, h)), 
		m_shapeName(name)
	{};
	
	void describe() const
	{
		sf::Vector2f	coords	= this->getSize();
		float		w	= coords.x;
		float		h	= coords.y;

		std::cout << "Width: " << w << std::endl;
		std::cout << "Heigth: " << h << std::endl;
	}

	void setSpeed(const sf::Vector2f& spd)
	{
		this->spd = spd;
	}

	sf::Vector2f getSpeed() const
	{
		return this->spd;
	}

	void hitCorner(const windowRes& window) 
	{
		this->hitLeft(window);
		this->hitTop(window);
		this->hitRight(window);
		this->hitBottom(window);
	}

	sf::Text drawText() const
	{
		sf::Text shapeT;

		sf::Vector2f curPos = this->getPosition();
		sf::Vector2f shapeSize = this->getSize();

		sf::Vector2f getNewPos(curPos.x + shapeSize.x/2 - 4*float(this->m_shapeName.length()), curPos.y + shapeSize.y/2 - shapeT.getCharacterSize()/2.0);

		shapeT.setFont(this->m_font);
		shapeT.setString(this->m_shapeName);
		shapeT.setPosition(getNewPos);
		shapeT.setCharacterSize(this->m_fontInfo.size);

		return shapeT;

	}

	void getFont(const sf::Font& myFont, const fontInfo& myFontInfo)
	{
		//loading font to draw it in the canvas
		this->m_font = myFont;
		this->m_fontInfo = myFontInfo;
	}
	
	
};

void readConfigFile(std::string fileName, windowRes& a_wr, fontInfo& a_font, std::vector<Circle>& a_circles, std::vector<Rect>& a_rectangles)
{

	std::string type;

	std::ifstream fin(fileName);
	while (fin >> type) 
	{
		if (type == "Window") 
		{
			fin >> a_wr.w >> a_wr.h;					
		}
		else if (type == "Font") 
		{
			fin >> a_font.fontName >> a_font.size >> a_font.r >> a_font.g >> a_font.b;	
		}
		else if (type == "Circle") 
		{
			std::string	name;
			positionXY	pos;	
			speedXY		spd;
			RGBcode		rgb;
			int		radius;

			fin >> name >> pos.x >> pos.y >> spd.dx >> spd.dy >> rgb.r >> rgb.g >> rgb.b >> radius;

			Circle  circle(radius, name);

			// circle initial features
			circle.setFillColor(sf::Color(rgb.r, rgb.g, rgb.b));
			circle.setPosition(sf::Vector2f(pos.x, pos.y));
			circle.setSpeed(sf::Vector2f(spd.dx, spd.dy));

			a_circles.push_back(circle);
		}
		else if (type == "Rectangle") 
		{
			std::string	name;
			positionXY	pos;	
			speedXY		spd;
			RGBcode		rgb;
			float		w;
			float		h;

			fin >> name >> pos.x >> pos.y >> spd.dx >> spd.dy >> rgb.r >> rgb.g >> rgb.b >> w >> h;
			
			Rect	rect(w, h, name);

			// rect initial features
			rect.setFillColor(sf::Color(rgb.r, rgb.g, rgb.b));
			rect.setPosition(sf::Vector2f(pos.x, pos.y));
			rect.setSpeed(sf::Vector2f(spd.dx, spd.dy));


			a_rectangles.push_back(rect);
		}
		else
		{
			continue;
		}
	}
}


int main()
{
//	Circle	circle1("Circle", {1,1}, {2,2}, {0,0,0}, 10);
//	Rect	rect1("Rect", {1,1}, {2,2}, {0,0,0}, 10, 15);
//
//	circle1.describe();	
//	rect1.describe();	
	
	windowRes		wr;
	fontInfo		font;
	std::vector<Circle>	circles;
	std::vector<Rect>	rectangles;

	readConfigFile("config.txt", wr, font, circles, rectangles);

	sf::Font techFont;

//	std::cout << font.fontName << std::endl;
	if(!techFont.loadFromFile(font.fontName))
	{
		std::cout << "Error loading the font file" << std::endl;
	}

	sf::RenderWindow window(sf::VideoMode(wr.w, wr.h), "SFML Works!")	;
//	window.setFramerateLimit(60);
	//shape.setFillColor(circles[1].getRGB());
	//shape.setPosition(circles[1].getPos());

	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}	
		}

		window.clear();
		
		for (Circle& c : circles) 
		{
			//first thing, load the font
			c.getFont(techFont, font);

			sf::Vector2f nextPos = c.getPosition() + c.getSpeed();
			c.setPosition(nextPos.x, nextPos.y);
			c.hitCorner(wr);
			window.draw(c);
			window.draw(c.drawText());
			//c.describe();	
		}

		for (Rect& r : rectangles) {
			// first load
			r.getFont(techFont, font);
			
			sf::Vector2f nextPos = r.getPosition() + r.getSpeed();
			r.setPosition(nextPos.x, nextPos.y);
			r.hitCorner(wr);
			window.draw(r);
			window.draw(r.drawText());
		}

		window.display();
	}

	return 0;
}

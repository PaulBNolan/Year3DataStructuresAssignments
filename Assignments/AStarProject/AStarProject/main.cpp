#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <SFML/Graphics.hpp>
#include <time.h>

#include "Graph.h"

typedef GraphArc<pair<std::string, int>, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;
sf::RenderWindow window(sf::VideoMode(1560, 1400), "A* Project");

sf::Font m_font;

Graph<pair<std::string, int>, int> graph(30);

std::pair<string, int> nodeL;
std::map<string, int> nodeM;

Node* startN;
Node* endN;

std::vector<Node*> path;

sf::CircleShape m_cities[30];
std::string m_cityNames[30];
sf::Text m_cityText[30];
sf::Text m_cityCost[30];

sf::Vertex m_routes[37][2];
sf::Text m_routeCost[37];

sf::Vector2f m_cityPosition[30];

std::string m_startPoint[37], m_endPoint[37];
sf::Vector2f m_weightPosition[37];

sf::Vector2f m_cityCenter[30];

int radius = 45;

bool m_startPointFound = false;
bool m_endPointFound = false;
bool m_pathReady = false;
bool m_pathFinished = false;

int m_startNode = 0;
int m_endNode = 0;


sf::RectangleShape m_startButton;
sf::Text m_startLabel;

sf::RectangleShape m_clearButton;
sf::Text m_clearLabel;


sf::Mouse m_mouse;
sf::Time m_time;
sf::Clock m_clock;
int m_timer;
int m_timeMarker = 1;

void functionTest();
void setUpGraph();
void detectMouse();
void usePath();
void resetGraph();
void render();

void visit(Node * node) {
	cout << "Visiting: " << node->data().first << endl;
}

int main()
{
	if (!m_font.loadFromFile("Fonts/arial.ttf"))
	{
		// Error...
	}

	functionTest();
	setUpGraph();
	while (window.isOpen())
	{
		m_time = m_clock.getElapsedTime();
		m_timer = m_time.asSeconds();

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		detectMouse();

		if (m_pathReady == true && m_timeMarker == m_timer)
		{
			usePath();
			m_timeMarker++;
		}
		render();
	}
}

void functionTest()
{
	int i = 0;
	ifstream myfile;
	myfile.open("ProjectNodes.txt");
	int x, y;
	while (myfile >> nodeL.first >> x >> y)
	{
		m_cityNames[i] = nodeL.first;
		m_cityText[i].setString(m_cityNames[i]);

		m_cityPosition[i] = sf::Vector2f(x * 3, y * 3);

		m_cityCenter[i] = sf::Vector2f(m_cityPosition[i].x + radius, m_cityPosition[i].y + radius);

		m_cityText[i].setFont(m_font);
		m_cityText[i].setFillColor(sf::Color::Red);
		m_cityText[i].setCharacterSize(45);
		m_cityText[i].setPosition(sf::Vector2f(m_cityPosition[i].x + radius - m_cityText[i].getGlobalBounds().width, m_cityPosition[i].y));

		m_cityCost[i].setFont(m_font);
		m_cityCost[i].setFillColor(sf::Color::Black);
		m_cityCost[i].setCharacterSize(30);
		m_cityCost[i].setString("0");
		m_cityCost[i].setPosition(sf::Vector2f(m_cityPosition[i].x + radius - m_cityText[i].getGlobalBounds().width, m_cityPosition[i].y + radius));

		graph.addNode(nodeL, i, x, y);
		nodeM[nodeL.first] = i;
		i++;
	}

	myfile.close();
	myfile.open("ProjectArcs.txt");

	std::string start, end;

	int j = 0;
	int cost;
	while (myfile >> start >> end >> cost)
	{
		if (j == 0 || m_endPoint[j - 1] != start && m_startPoint[j - 1] != end)
		{
			m_startPoint[j] = start;
			m_endPoint[j] = end;
			m_routeCost[j].setString(to_string(cost));
			j++;
		}

		std::cout << start << " " << end << " " << cost << std::endl;
		graph.addArc(nodeM[start], nodeM[end], cost);
	}
	myfile.close();
}

void setUpGraph()
{
	for (int i = 0; i < 30; i++)
	{
		m_cities[i].setFillColor(sf::Color::Blue);
		m_cities[i].setRadius(radius);
		m_cities[i].setPosition(m_cityPosition[i]);
	}

	for (int i = 0; i < 37; i++)
	{
		bool startFound = false;
		bool endFound = false;
		bool lineFound = false;

		sf::Vector2f m_startPosition;

		sf::Vector2f m_endPosition;

		for (int j = 0; j < 30; j++)
		{
			if (m_cityNames[j] == m_startPoint[i] && startFound == false)
			{
				startFound = true;

				m_startPosition = m_cityCenter[j];
			}

			if (m_cityNames[j] == m_endPoint[i] && endFound == false)
			{
				endFound = true;

				m_endPosition = m_cityCenter[j];
			}

			if (startFound == true && endFound == true && lineFound == false)
			{
				m_routes[i][0] = sf::Vertex(m_startPosition,sf::Color::Red);
				m_routes[i][1] = sf::Vertex(m_endPosition,sf::Color::Red);

				//std::cout << i << std::endl;
				m_routeCost[i].setFont(m_font);

				m_weightPosition[i] = 
					sf::Vector2f(m_endPosition.x - ((m_endPosition.x - m_startPosition.x) / 2) - m_routeCost[i].getGlobalBounds().width / 2, 
						m_endPosition.y - ((m_endPosition.y - m_startPosition.y) / 2) - m_routeCost[i].getGlobalBounds().height / 2);
				m_routeCost[i].setPosition(m_weightPosition[i]);

				lineFound = true;
			}
		}
	}

	m_startButton.setPosition(0, 1210);
	m_startButton.setFillColor(sf::Color::Yellow);
	m_startButton.setSize(sf::Vector2f(window.getSize().x / 2, 190));

	m_startLabel.setFont(m_font);
	m_startLabel.setCharacterSize(60);
	m_startLabel.setFillColor(sf::Color::Red);
	m_startLabel.setString("Start");
	m_startLabel.setPosition(sf::Vector2f(((window.getSize().x / 4) - m_startLabel.getGlobalBounds().width / 2), 1220));

	m_clearButton.setPosition(window.getSize().x / 2, 1210);
	m_clearButton.setFillColor(sf::Color::Cyan);
	m_clearButton.setSize(sf::Vector2f(window.getSize().x / 2, 190));

	m_clearLabel.setFont(m_font);
	m_clearLabel.setCharacterSize(60);
	m_clearLabel.setFillColor(sf::Color::White);
	m_clearLabel.setString("Clear");
	m_clearLabel.setPosition(sf::Vector2f(((window.getSize().x / 4) * 3 - m_clearLabel.getGlobalBounds().width / 2), 1220));
}

void detectMouse()
{
	if (m_mouse.isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < 30; i++)
		{
			if (m_mouse.getPosition(window).x > m_cityPosition[i].x && m_mouse.getPosition(window).x < m_cityPosition[i].x + radius * 2
				&&
				m_mouse.getPosition(window).y > m_cityPosition[i].y && m_mouse.getPosition(window).y < m_cityPosition[i].y + radius * 2)
			{
				if (m_startPointFound == false)
				{
					m_cities[i].setFillColor(sf::Color::Green);
					m_startPointFound = true;
					m_startNode = i;
					startN = graph.nodeIndex(m_startNode);
				}
				else if (m_endPointFound == false && i != m_startNode)
				{
					m_cities[i].setFillColor(sf::Color::Yellow);
					m_endPointFound = true;
					m_endNode = i;

					endN = graph.nodeIndex(m_endNode);

					graph.aStar(startN, endN, visit, path);
				}
			}
				
		}

		if (m_mouse.getPosition(window).x > m_startButton.getPosition().x && m_mouse.getPosition(window).x < m_startButton.getPosition().x + m_startButton.getGlobalBounds().width
			&&
			m_mouse.getPosition(window).y > m_startButton.getPosition().y && m_mouse.getPosition(window).y < m_startButton.getPosition().y + m_startButton.getGlobalBounds().height)
		{
			if (m_endPointFound == true && m_startPointFound == true)
			{
				m_pathReady = true;
				m_clock.restart();
			}
		}

		if (m_mouse.getPosition(window).x > m_clearButton.getPosition().x && m_mouse.getPosition(window).x < m_clearButton.getPosition().x + m_clearButton.getGlobalBounds().width
			&&
			m_mouse.getPosition(window).y > m_clearButton.getPosition().y && m_mouse.getPosition(window).y < m_clearButton.getPosition().y + m_clearButton.getGlobalBounds().height)
		{
			if (m_pathFinished == true)
			{
				resetGraph();
			}
		}
	}
}

void usePath()
{
		//visit(path.back());

		for (int i = 0; i < 30; i++)
		{
			if (path.back()->data().first == m_cityNames[i])
			{
				m_cities[i].setFillColor(sf::Color::White);

				m_cityCost[i].setString(to_string(path.back()->data().second));
			}
		}

		if (path.size() == 1)
		{
			std::cout << "Pathsize: " << path.front()->data().second << std::endl;
			m_pathFinished = true;
			m_pathReady = false;
		}
		path.pop_back();
}

void resetGraph()
{
	m_startPointFound = false;
	m_endPointFound = false;

	m_pathFinished = false;

	for (int i = 0; i < 30; i++)
	{
		m_cities[i].setFillColor(sf::Color::Blue);
		m_cityCost[i].setString("0");
	}
	m_timeMarker = 1;
}

void render()
{
	window.clear();

	for (int i = 0; i < 37; i++)
	{
		window.draw(m_routes[i], 8, sf::Lines);

		window.draw(m_routeCost[i]);
	}

	for (int i = 0; i < 30; i++)
	{
		window.draw(m_cities[i]);
		window.draw(m_cityText[i]);
		window.draw(m_cityCost[i]);
	}
	window.draw(m_startButton);
	window.draw(m_startLabel);
	window.draw(m_clearButton);
	window.draw(m_clearLabel);
	window.display();
}
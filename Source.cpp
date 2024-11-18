#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Renderer.h"
#include "PhysicsWorld.h"

#define Window_W 800
#define Window_H 600

// uncomment collider type in particle.h
int main()
{
    Renderer renderer;
    sf::RenderWindow window(sf::VideoMode(Window_W, Window_H), "Main Window");
    /*for circle collider uncomment this
    int r = 20;
    CircleShape circle(r);
    circle.setFillColor(sf::Color::Red);
    CircleShape circle2(r);
    circle2.setFillColor(sf::Color::Green);

    Collider collider1(r);
    Collider collider2(r);
    renderer.AddDrawable(&circle);
    renderer.AddDrawable(&circle2);
    */
    /*for aabb collider uncomment this

    RectangleShape rect1(sf::Vector2f(40, 60));
    rect1.setFillColor(sf::Color::Red);
    RectangleShape rect2(sf::Vector2f(40, 60));
    rect2.setFillColor(sf::Color::Green);

    AABBCollider collider1(Vector2d(rect1.getPoint(0).x, rect1.getPoint(0).y), Vector2d(rect1.getPoint(2).x, rect1.getPoint(2).y));
    AABBCollider collider2(Vector2d(rect2.getPoint(0).x, rect2.getPoint(0).y), Vector2d(rect2.getPoint(2).x, rect2.getPoint(2).y));
    renderer.AddDrawable(&rect1);
    renderer.AddDrawable(&rect2);
    */

    /*for Sat collider */
    ConvexShape conv1(5);
    conv1.setFillColor(sf::Color(255,0,0,100));
    ConvexShape conv2(5);
    conv2.setFillColor(sf::Color::Green);
    //setting pentagons points
    vector<Vector2d> points =
    {
        Vector2d(150,100),
        Vector2d(115.45,147.55),
        Vector2d(59.55,129.39),
        Vector2d(59.55,70.61),
        Vector2d(115.45,52.45)
    };
    for (int i = 0; i < 5; i++)
    {
        conv1.setPoint(i, Vector2f(points[i].x, points[i].y));
    }
    vector<Vector2d> points2 =
    {
        Vector2d(150,200),
        Vector2d(115.45,247.55),
        Vector2d(59.55,229.39),
        Vector2d(59.55,170.61),
        Vector2d(115.45,152.45)
    };
    int x = points2.size();
    for (int i = 0; i < 5; i++)
    {
        conv2.setPoint(i, Vector2f(points2[i].x, points2[i].y));
    }
    SATCollider collider1(points);
    SATCollider collider2(points2);
    renderer.AddDrawable(&conv1);
    renderer.AddDrawable(&conv2);
    
    
    
    /*comment this in case SAT in use
    Particle partical1(Vector2d(Window_W / 2, Window_H / 8));
    partical1.collider = &collider1;
    partical1.addForce(Vector2d(0, 9.8));
    partical1.Update(0);
    Particle partical2(Vector2d(Window_W / 2, 6 * Window_H / 8));
    partical2.collider = &collider2;
    partical2.addForce(Vector2d(0, -9.8));
    partical2.Update(0);
    */

    /*just for sat collider*/
    Particle partical1(Vector2d(conv1.getPoint(0).x, conv1.getPoint(0).y));
    partical1.collider = &collider1;
    partical1.addForce(Vector2d(0, 9.8));
    partical1.Update(0);
    Particle partical2(Vector2d(conv2.getPoint(0).x, conv2.getPoint(0).y));
    partical2.collider = &collider2;
    partical2.addForce(Vector2d(0, -9.8));
    partical2.Update(0);
    
    

    PhysicsWorld pWorld;
    pWorld.addParticle(&partical2);
    pWorld.addParticle(&partical1);

    float dt = 0;
    sf::Clock clock;
    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check for all window events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        pWorld.Update(dt);
        dt = clock.restart().asSeconds();
        /*for circle collider
        circle.setPosition(partical1.postion);
        circle2.setPosition(partical2.postion);
        */
        /* for aabb
        rect1.setPosition(partical1.postion);
        rect2.setPosition(partical2.postion);
        */
        /* for SAT*/
        conv1.setPosition(partical1.postion);
        conv2.setPosition(partical2.postion);
        

        window.clear();

        renderer.Render(&window);

        {
            Font font;
            if (!font.loadFromFile("./resources/rfont.ttf"))
            {
                printf("can not load font");
            }
            Text speedText;
            speedText.setFont(font);
            speedText.setCharacterSize(50);
            speedText.setFillColor(sf::Color::White);
            speedText.setPosition(0, 0);
            speedText.setString("Speed Vector: " + std::to_string((int)partical1.velocity.x) + " , " + std::to_string((int)partical1.velocity.y));
            window.draw(speedText);
        }
        window.display();
    }

    return 0;
}
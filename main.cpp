#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

int carsCount = 12;
int window_w = 1300;
int window_h = 1100;
int car_w = 140;
int car_h = 80;
int player_w = 70;
int player_h = 70;
int stick_width_scale = 120;
bool PlayerOnStick = false;
int gameover = 0;

class Car : public sf::RectangleShape

{
private:
    int speed;
    char direction;
    char status = 'i'; //o:out i:in
public:
    void setStatus(char c)
    {
        status = c;
    }
    char getStatus()
    {
        return status;
    }
    void setSpeed(int s)
    {
        speed = s;
    }
    int getSpeed()
    {
        return speed;
    }
    void setDirection(char d)
    {
        direction = d;
    }
    char getDirection()
    {
        return direction;
    }
};

class Stick : public sf::RectangleShape
{
private:
    int speed;
    char status;    //o:out i:in
    char direction; //R:right L:left
public:
    void setStatus(char c)
    {
        status = c;
    }
    char getStatus()
    {
        return status;
    }
    void setSpeed(int s)
    {
        speed = s;
    }
    int getSpeed()
    {
        return speed;
    }
    void setDirection(int d)
    {
        direction = d;
    }
    int getDirection()
    {
        return direction;
    }
};

void moveCars(std::vector<Car> &cars)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (int i = 0; i < carsCount; i++)
        {
            if (cars[i].getStatus() == 'i')
            {
                if (cars[i].getDirection() == 'R')
                {
                    if (cars[i].getPosition().x >= window_w)
                    {
                        cars[i].setStatus('o');
                    }
                    else
                    {
                        cars[i].move(cars[i].getSpeed(), 0);
                    }
                }
                else if (cars[i].getDirection() == 'L')
                {
                    if (cars[i].getPosition().x <= -car_w)
                    {
                        cars[i].setStatus('o');
                    }
                    else
                    {
                        cars[i].move(-cars[i].getSpeed(), 0);
                    }
                }
            }
        }
    }
}

void moveSticks(std::vector<Stick> &sticks1, std::vector<Stick> &sticks2, std::vector<Stick> &sticks3, std::vector<Stick> &sticks4, sf::RectangleShape *player)
{

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        bool isPlayerOnStick = false;
        for (int i = 0; i < 3; i++)
        {
            if (sticks1[i].getStatus() == 'i')
            {
                if (sticks1[i].getPosition().x >= window_w)
                {
                    sticks1[i].setStatus('o');
                }
                else
                {
                    sticks1[i].move(sticks1[i].getSpeed(), 0);
                }

                //check if player is on stick
                if ((player->getPosition().y == sticks1[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks1[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks1[i].getPosition().x + sticks1[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (window_w - 5 - (player->getPosition().x + player_w) < sticks1[i].getSpeed())
                    {
                        player->move(window_w - 5 - (player->getPosition().x + player_w), 0);
                    }
                    else
                    {
                        player->move(sticks1[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks2[i].getStatus() == 'i')
            {
                if (sticks2[i].getPosition().x <= -sticks2[i].getSize().x)
                {
                    sticks2[i].setStatus('o');
                }
                else
                {
                    sticks2[i].move(-sticks2[i].getSpeed(), 0);
                }
                //check if player is on stick
                if ((player->getPosition().y == sticks2[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks2[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks2[i].getPosition().x + sticks2[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (player->getPosition().x - 5 < sticks2[i].getSpeed())
                    {
                        player->move(-(player->getPosition().x - 5), 0);
                    }
                    else
                    {
                        player->move(-sticks2[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks3[i].getStatus() == 'i')
            {
                if (sticks3[i].getPosition().x >= window_w)
                {
                    sticks3[i].setStatus('o');
                }
                else
                {
                    sticks3[i].move(sticks3[i].getSpeed(), 0);
                }
            }
            //check if player is on stick
            if ((player->getPosition().y == sticks3[i].getPosition().y + 5) &&
                ((player->getPosition().x >= sticks3[i].getPosition().x - (player_w / 2)) &&
                 (player->getPosition().x + player_w <= sticks3[i].getPosition().x + sticks3[i].getSize().x + (player_w / 2))))
            {
                isPlayerOnStick = true;
                if (window_w - 5 - (player->getPosition().x + player_w) < sticks3[i].getSpeed())
                {
                    player->move(window_w - 5 - (player->getPosition().x + player_w), 0);
                }
                else
                {
                    player->move(sticks3[i].getSpeed(), 0);
                }
            }
            //
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks4[i].getStatus() == 'i')
            {
                if (sticks4[i].getPosition().x <= -sticks4[i].getSize().x)
                {
                    sticks4[i].setStatus('o');
                }
                else
                {
                    sticks4[i].move(-sticks4[i].getSpeed(), 0);
                }
                //check if player is on stick
                if ((player->getPosition().y == sticks4[i].getPosition().y + 5) &&
                    ((player->getPosition().x >= sticks4[i].getPosition().x - (player_w / 2)) &&
                     (player->getPosition().x + player_w <= sticks4[i].getPosition().x + sticks4[i].getSize().x + (player_w / 2))))
                {
                    isPlayerOnStick = true;
                    if (player->getPosition().x - 5 < sticks4[i].getSpeed())
                    {
                        player->move(-(player->getPosition().x - 5), 0);
                    }
                    else
                    {
                        player->move(-sticks4[i].getSpeed(), 0);
                    }
                }
                //
            }
        }
        //ckeck if player has fallen in water
        if (player->getPosition().y >= 100 && player->getPosition().y <= 500)
        {
            if (!isPlayerOnStick)
            {
                gameover = 1;
            }
        }
    }
}

void createNewCarSet(std::vector<Car> &cars)
{
    int setNum = 0;
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            if (cars[setNum * 4 + i].getStatus() == 'o')
            {
                int speed = (rand() % 8) + 10; //10-17
                printf("%d ", speed);
                char direction = (i % 2 == 0) ? 'R' : 'L';
                if (direction == 'R')
                {
                    cars[setNum * 4 + i].setPosition(-car_w, cars[setNum * 4 + i].getPosition().y);
                }
                else if (direction == 'L')
                {
                    cars[setNum * 4 + i].setPosition(window_w, cars[setNum * 4 + i].getPosition().y);
                }
                cars[setNum * 4 + i].setSpeed(speed);
                cars[setNum * 4 + i].setStatus('i');
                cars[setNum * 4 + i].setDirection(direction);
            }
        }
        setNum++;
        if (setNum == 3)
        {
            setNum = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void createNewStickLine1(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(-sticks[i].getSize().x, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('R');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine2(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(window_w, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('L');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine3(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(-sticks[i].getSize().x, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('R');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

void createNewStickLine4(std::vector<Stick> &sticks)
{
    int replacingDelay = ((rand() % 3) + 3) * 1000; //3000-5000millisec
    int speed = (rand() % 5) + 11;                  //11-15
    int width = ((rand() % 4) + 1) * stick_width_scale;
    int i = 0;
    while (true)
    {
        if (sticks[i].getStatus() == 'o')
        {
            sticks[i].setSize(sf::Vector2f(width, car_h));
            sticks[i].setPosition(window_w, sticks[i].getPosition().y);
            sticks[i].setSpeed(speed);
            sticks[i].setStatus('i');
            sticks[i].setDirection('L');
        }
        i++;
        if (i == 3)
        {
            i = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(replacingDelay));
    }
}

int main()
{
    using namespace sf;
    using namespace std;
    RenderWindow window(sf::VideoMode(window_w, window_h), "SFML works!");

    vector<Car> cars;
    vector<Stick> sticks1;
    vector<Stick> sticks2;
    vector<Stick> sticks3;
    vector<Stick> sticks4;
    RectangleShape player;

    srand(time(NULL));

    for (int i = 0; i < carsCount; i++)
    {
        Car car;
        car.setFillColor(sf::Color::Red);
        car.setSize(Vector2f(car_w, car_h));
        car.setStatus('o');
        car.setPosition(0, window_h - (((i % 4) + 2) * 100) + 10);
        cars.push_back(car);
    }

    for (int i = 0; i < 3; i++)
    {
        Stick stick;
        stick.setFillColor(sf::Color::Green);
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, window_h - 700 + 10);
        sticks1.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        Stick stick;
        stick.setFillColor(sf::Color::Green);
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, window_h - 800 + 10);
        sticks2.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        Stick stick;
        stick.setFillColor(sf::Color::Green);
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, window_h - 900 + 10);
        sticks3.push_back(stick);
    }

    for (int i = 0; i < 3; i++)
    {
        Stick stick;
        stick.setFillColor(sf::Color::Green);
        stick.setSize(Vector2f(100, car_h));
        stick.setStatus('o');
        stick.setPosition(0, window_h - 1000 + 10);
        sticks4.push_back(stick);
    }

    player.setSize(Vector2f(player_w, player_h));
    player.setPosition((window_w - player_w) / 2, window_h - player_h - 15);
    player.setFillColor(sf::Color::Magenta);

    std::thread thread_set_cars(&createNewCarSet, ref(cars));
    std::thread thread_set_sticks1(&createNewStickLine1, ref(sticks1));
    std::thread thread_set_sticks2(&createNewStickLine2, ref(sticks2));
    std::thread thread_set_sticks3(&createNewStickLine3, ref(sticks3));
    std::thread thread_set_sticks4(&createNewStickLine4, ref(sticks4));
    std::thread thread_move_cars(&moveCars, ref(cars));
    std::thread thread_move_sticks(&moveSticks, ref(sticks1), ref(sticks2), ref(sticks3), ref(sticks4), &player);

    int c = 0;
    while (window.isOpen())
    {

        for (int i = 0; i < carsCount; i++)
        {
            if (cars[i].getStatus() == 'i')
            {
                if ((((player.getPosition().x <= cars[i].getPosition().x) && (player.getPosition().x + player_w - cars[i].getPosition().x >= 0)) ||
                     ((player.getPosition().x >= cars[i].getPosition().x) && (cars[i].getPosition().x + car_w - player.getPosition().x >= 0))) &&
                    (((player.getPosition().y <= cars[i].getPosition().y) && (player.getPosition().y + player_h - cars[i].getPosition().y >= 0)) ||
                     ((player.getPosition().y >= cars[i].getPosition().y) && (cars[i].getPosition().y + car_h - player.getPosition().y >= 0))))
                {
                    //accident
                    gameover = 1;
                    break;
                }
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (player.getPosition().y != 15)
                    {
                        player.move(0, -100);
                    }
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if (player.getPosition().y != window_h - player_h - 15)
                    {
                        player.move(0, 100);
                    }
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (window_w - 5 - (player.getPosition().x + player_w) < 100)
                    {
                        player.move(window_w - 5 - (player.getPosition().x + player_w), 0);
                    }
                    else
                    {
                        player.move(100, 0);
                    }
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (player.getPosition().x - 5 < 100)
                    {
                        player.move(-(player.getPosition().x - 5), 0);
                    }
                    else
                    {
                        player.move(-100, 0);
                    }
                }
            }
        }

        window.clear();
        //background
        Texture checkedl;
        Sprite checkedline;
        if (!checkedl.loadFromFile("beach1.jpg"))
            cout << "Failed loading";
        checkedline.setTexture(checkedl); //checked line pos 0
        checkedline.setPosition(0, 500);
        window.draw(checkedline);
                Texture checkel1;
        Sprite checkel1ine;
        if (!checkel1.loadFromFile("checked.jpg"))
            cout << "Failed loading";
        checkel1ine.setTexture(checkel1); //beach line pos 500
        checkel1ine.setPosition(0, 0);
        window.draw(checkel1ine);
        Texture taroad100;
        Sprite aroad100;
        if (!taroad100.loadFromFile("aroad.jpg"))
            cout << "Failed loading";
        aroad100.setTexture(taroad100); //road 600
        aroad100.setPosition(0, 600);
        window.draw(aroad100);
        Texture taroad200;
        Sprite aroad200;
        if (!taroad200.loadFromFile("aroad200.jpg"))
            cout << "Failed loading";
        aroad200.setTexture(taroad200); //road 700
        aroad200.setPosition(0, 700);
        window.draw(aroad200);
        Texture taroad300;
        Sprite aroad300;
        if (!taroad300.loadFromFile("aroad.jpg"))
            cout << "Failed loading";
        aroad300.setTexture(taroad300); //road8 800 
        aroad300.setPosition(0, 800);
        window.draw(aroad300);
        Texture taroad400;
        Sprite aroad400;
        if (!taroad400.loadFromFile("aroad200.jpg"))
            cout << "Failed loading";
        aroad400.setTexture(taroad400); //road 900
        aroad400.setPosition(0, 900);
        window.draw(aroad400);
        Texture tsea;
        Sprite sea;
        if (!tsea.loadFromFile("sea.png"))
            cout << "Failed loading";
        sea.setTexture(tsea); //road100
        sea.setPosition(0, 0);
        window.draw(sea);

        for (int i = 0; i < carsCount; i++)
        {
            if (cars[i].getStatus() == 'i')
            {
                window.draw(cars[i]);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks1[i].getStatus() == 'i')
            {
                window.draw(sticks1[i]);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks2[i].getStatus() == 'i')
            {
                window.draw(sticks2[i]);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks3[i].getStatus() == 'i')
            {
                window.draw(sticks3[i]);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sticks4[i].getStatus() == 'i')
            {
                window.draw(sticks4[i]);
            }
        }
        window.draw(player);
        window.display();

        if (gameover == 1)
        {
            break;
        }
    }

    return 0;
}

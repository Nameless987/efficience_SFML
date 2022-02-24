#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include<windows.h>

using namespace sf;
using namespace std;
#define PI 3.14159265

const char* nameProject = "Project_2";

Font font;
Text text;
RenderWindow window(VideoMode(1920, 1080), nameProject, Style::Fullscreen);
RenderTexture texture;
Event event;
Mouse mouse;
Clock gameClock;

bool fullscreen = true;

bool pause;

struct point{
    float x;
    float y;
    float w;
    float h;
    float vx;
    float vy;
    float r;
    int id;
    CircleShape body;
};

vector<point> player;

point newPlayer;

struct rect{
    float x, y, w, h;
    vector<point> points;
 
    RectangleShape body;
};

struct quadTree{
    quadTree *NE;
    quadTree *NW;
    quadTree *SE;
    quadTree *SW;
 
    rect box;
    //void insert(point p){
    //    if()
    //}
};

float dist(float a, float b, float c, float d){
    return sqrt(pow((c-a), 2) + pow((d-b), 2));
}

int main(){
    window.setFramerateLimit(60);

    int count = 0;

    srand(time(NULL));

    VertexArray circles(PrimitiveType::Triangles);

    if (!texture.create(1920, 1080))
        return -1;
    
    for(int i=0; i<100000; i++){
        player.push_back(newPlayer);
        player[i].id = i;
        //player[i].w=rand()%1+1;
        //player[i].h=rand()%1+1;
        player[i].r = rand()%1+2;
        player[i].vx=rand()%200-100;
        player[i].vy=rand()%200-100;
        player[i].body.setFillColor(Color(255, 0, 0, 255));
        player[i].body.setRadius(player[i].r);
        player[i].x=rand()%(window.getSize().x-int(2*player[i].r))+player[i].r;
        player[i].y=rand()%(window.getSize().y-int(2*player[i].r))+player[i].r;
        //player[i].body.setSize(Vector2f(player[i].w, player[i].h));
    }

    while(window.isOpen()){
        window.clear();
        //circles.clear();

        while(window.pollEvent(event)){
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Enter) && (!fullscreen)) {
				fullscreen = true;
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));
			}
            else if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape) && (fullscreen)) {
				fullscreen = false;
				window.create(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));
			}
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space) && (fullscreen)) {
                pause = !pause;
			}
            if(event.type == Event::Closed){
                window.close();
            }
        }
        float dt = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
     
        for(int i=0; i<player.size(); i++){
            if(fullscreen && !pause){
                player[i].x+=player[i].vx*dt;
                player[i].y+=player[i].vy*dt;
                if(player[i].x < player[i].r){
                    player[i].x += 2*(player[i].r-player[i].x);
                    player[i].vx *= -1;
                }
                else if(player[i].x > window.getSize().x-player[i].r){
                    player[i].x += 2*(window.getSize().x-player[i].r-player[i].x);
                    player[i].vx *= -1;
                }
                if(player[i].y < player[i].r){
                    player[i].y += 2*(player[i].r-player[i].y);
                    player[i].vy *= -1;
                }
                else if(player[i].y > window.getSize().y-player[i].r){
                    player[i].y += 2*(window.getSize().y-player[i].r-player[i].y);
                    player[i].vy *= -1;
                }
            }
            player[i].body.setPosition(player[i].x-player[i].r, player[i].y-player[i].r);
            //count = 0;
            //for(int j=0; j<player.size(); j++){
            //    if(i!=j && (dist(player[i].x+player[i].r, player[i].y+player[i].r, player[j].x+player[j].r, player[j].y+player[j].r)<(player[i].r+player[j].r))){
            //        player[i].body.setFillColor(Color::Blue);
            //        player[j].body.setFillColor(Color::Blue);
            //        break;
            //    }
            //    else if(i!=j){
            //        count += 1;
            //    }
            //}
            //if(count == player.size()-1){
            //    player[i].body.setFillColor(Color::Red);
            //}
            //texture.draw(player[i].body);
            //int NumPoints = 10;
            //for (int n = 0; n < NumPoints; n++)
            //    {
            //        circles.append(sf::Vertex(Vector2f(int(player[i].x), int(player[i].y)), Color::Red));
//
            //        static const float pi = 3.141592654f;
//
            //        {
            //            float angle = (n+1) * 2 * pi / NumPoints - pi / 2;
            //            float x = std::cos(angle) * player[i].r;
            //            float y = std::sin(angle) * player[i].r;
            //            circles.append(sf::Vertex(Vector2f(int(player[i].x), int(player[i].y)) + sf::Vector2f(player[i].r/2 + x, player[i].r/2 + y), Color::Red));
            //        }
//
            //        {
            //            float angle = (n+2) * 2 * pi / NumPoints - pi / 2;
            //            float x = std::cos(angle) * player[i].r;
            //            float y = std::sin(angle) * player[i].r;
            //            circles.append(sf::Vertex(Vector2f(int(player[i].x), int(player[i].y)) + sf::Vector2f(player[i].r/2 + x, player[i].r/2 + y), Color::Red));
            //        }
            //    }
            window.draw(player[i].body);
        }

        //texture.display();
        //Sprite sprite(texture.getTexture());
        //window.draw(circles);
        
        window.display();
    }

    return 0;
}
// Alex Byrne refactoring 
//C00297124

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int Width=600; // changed veriable name W to width
const int Hight=480; // changed veriable name H to Hight
int speed = 4;
bool field[Width][Hight]={0};

struct player
{ int x,y,direction; //changed veriable name from dir to direction
  Color color;
  player(Color c)
  {
    x=rand() % Width;
    y=rand() % Hight;
    color=c;
    direction=rand() % 4;
  }
  void tick()
  {
    if (direction==0) y+=1;
    if (direction==1) x-=1;
    if (direction==2) x+=1;
    if (direction==3) y-=1;

    if (x>= Width) x=0;  if (x<0) x= Width -1;
    if (y>= Hight) y=0;  if (y<0) y= Hight -1;
  }

  Vector3f getColor()
  {return Vector3f(color.r,color.g,color.b);}
};

int tron()
{
    srand(time(0));

    RenderWindow window(VideoMode(Width, Hight), "The Tron Game!");
    window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("images/tron/background.jpg");
    Sprite sBackground(texture);

    player p1(Color::Red), p2(Color::Green); 

    Sprite sprite;
    RenderTexture render; //changed veriable name from t to render
    render.create(Width, Hight);
    render.setSmooth(true);
    sprite.setTexture(render.getTexture());
    render.clear();  render.draw(sBackground);

    bool Game=1;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) if (p1.direction!=2) p1.direction=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (p1.direction!=1)  p1.direction=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) if (p1.direction!=0) p1.direction=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) if (p1.direction!=3) p1.direction=0;

        if (Keyboard::isKeyPressed(Keyboard::A)) if (p2.direction!=2) p2.direction=1;
        if (Keyboard::isKeyPressed(Keyboard::D)) if (p2.direction!=1)  p2.direction=2;
        if (Keyboard::isKeyPressed(Keyboard::W)) if (p2.direction!=0) p2.direction=3;
        if (Keyboard::isKeyPressed(Keyboard::S)) if (p2.direction!=3) p2.direction=0;

        if (!Game)    continue;

        for(int i=0;i<speed;i++)
        {
            p1.tick(); p2.tick();
            if (field[p1.x][p1.y]==1) Game=0; 
            if (field[p2.x][p2.y]==1) Game=0;
            field[p1.x][p1.y]=1; 
            field[p2.x][p2.y]=1;
    
            CircleShape c(3);
            c.setPosition(p1.x,p1.y); c.setFillColor(p1.color);    render.draw(c);
            c.setPosition(p2.x,p2.y); c.setFillColor(p2.color);    render.draw(c);
            render.display(); 
        }

       ////// draw  ///////
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

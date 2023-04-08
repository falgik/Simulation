#include <SFML/Graphics.hpp>
#include "program.h"

using namespace sf;

Program prog;



int main()
{
    RenderWindow window(VideoMode(800,600), "Use up/down arrows to change food spawn times", Style::Close);
    window.setFramerateLimit(60);
    Event ev;

   
    srand(time(0));
    prog.init(window.getSize());

    while (window.isOpen())
    {

        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }

        prog.update();

        window.clear(Color(70,70,70));
        prog.draw(window);
        window.display();
    }

    return 0;
}
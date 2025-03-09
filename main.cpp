#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 506, 284 }), "My window");

    //Background texture setting
    sf::Texture backgroundTex("AnonimusConvertedGif.png");
    sf::Sprite background(backgroundTex);
    background.setPosition({ 0.f, 0.f });
    //-----------------------------------

    //worm sprite setting
    sf::Texture wormTex("earthworm-jim.png");
    sf::Sprite worm(wormTex);
    worm.setPosition({ 0.f, 0.f });
    //-----------------------------------

    sf::SoundBuffer buffer("backgrdMusic.wav");
    sf::Sound sound(buffer);
    sound.play();

    //initializating variable to count number of iterations
    size_t iteration = 0;
    //-----------------------------------------------------

    // run the program as long as the window is open
    while (window.isOpen())
    {
        iteration++;

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            
        }

        //handeling cases of background sprite 
        if ((iteration) % 6 == 0)
        {
            background.move({ 5*506.f, -284.f });
        }
        else
        {
            background.move({ -506.f, 0.f });
        }

        if (iteration == 81)
        {
            background.move({ 3 * 506.f , 13 * 284.f });
            iteration = 0;
        }

        Sleep(80); //sets 30 ms so that background look nice
        //------------------------------------------------------
 
        window.draw(background);
        //window.draw(worm);

        window.display();
    }
}
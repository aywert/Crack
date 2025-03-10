#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <stdio.h>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 506, 284 }), "My window");

    //Background sprite setting

    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile("AnonimusConvertedGif.png"))
    {
        printf("BackgroundTex wasn't initialized due to mistake in openning AnonimusConvertedGif.png");
    }
    sf::Sprite background(backgroundTex);
    background.setPosition({ 0.f, 0.f });
    //-----------------------------------

    //Button sprite setting
    sf::Texture bloodTex;
    if (!bloodTex.loadFromFile("Blood.png"))
    {
        printf("BloodTex wasn't initialized due to mistake in openning Blood.png");
    }
    sf::Sprite button(bloodTex);
    button.setPosition({ 150.f, 200.f });
    //-----------------------------------

    //Setting font and output string
    sf::Font font;
    if (!font.openFromFile("SehnsuchtFont.ttf"))
    {
        printf("BackgroundTex wasn't initialized due to mistake in openning SehnsuchtFont.ttf");
    }

    sf::Text text(font); // a font is required to make a text object
    text.setString("Crack Me"); // set the string to display
    text.setCharacterSize(24); //set the character size in pixels, not points!
    text.setFillColor(sf::Color::White); // set the color
    text.setPosition({ 165.f, 205.f });
    //-------------------------------------------

    //Soundtrack setting
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("backgrdMusic.wav"))
    {
        printf("Buffer wasn't initialized due to mistake in openning backgrdMusic.wav");
    }
 
    sf::Sound sound(buffer);
    sound.play();
    //End of soundteack setting

    //initializating variable to count number of iterations
    size_t iteration = 0;
    bool OnButton = false;
    bool ButtonIsPressed = false;
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
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }

            
            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (150 <= mouseMoved->position.x && mouseMoved->position.x <= 350 && 200 <= mouseMoved->position.y && mouseMoved->position.y <= 280)
                {
                    OnButton = true;
                    int x = mouseMoved->position.x;
                    int y = mouseMoved->position.y;
                    printf("%d %d\n", x, y);

                    button.setColor(sf::Color(0, 255, 0)); // green


                    
                    //button.setColor(sf::Color(255, 255, 255, 128)); // half transparent
                }

                else
                {
                    if (OnButton == true)
                    {
                        button.setColor(sf::Color(225, 0, 0));
                        OnButton = false;
                    }
                }
            }

            if (OnButton && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                ButtonIsPressed = true;
                // left mouse button is pressed: shoot
            }

            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left && OnButton && ButtonIsPressed)
                {
                    printf("Start Crack\n");
                }

                else
                {
                    ButtonIsPressed = false;
                }
            }

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
        window.clear();
        window.draw(background);
        window.draw(button);
        window.draw(text);
        window.display();
    }
}
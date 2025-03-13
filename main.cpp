#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

const char* FileName = "..\\..\\..\\..\\DOSBox\\TOHACK\\HK.COM";


enum CrackStatus
{
    SuccCrack = 0,
    FailCrack = 1,
};

int IsOnSprtite(int x, int y);
CrackStatus CrackCode(void);

//------------Constants---------------
const unsigned int Width        = 506;
const unsigned int Height       = 284;

const unsigned int PngColomns   = 6;
const unsigned int PngStrings   = 14;
const int NumOfFrames           = 81;

const int ShiftFrameBackX = (PngColomns - 1) * Width;
const int ShiftFrameBackY = (PngStrings - 1) * Height;

const int MlsPerFrame = 80;

int ByteToChange = 20;
//------------------------------------

int FrameX = 0;
int FrameY = 0;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ Width, Height }), "My window");

    //Background sprite setting
    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile("AnonimusConvertedGif.png"))
    {
        printf("BackgroundTex wasn't initialized due to mistake in openning AnonimusConvertedGif.png");
        return 0;
    }
    sf::Sprite background(backgroundTex);
    background.setPosition({ 0.f, 0.f });
    //-----------------------------------

    //Button sprite setting
    sf::Texture bloodTex;
    if (!bloodTex.loadFromFile("Blood.png"))
    {
        printf("BloodTex wasn't initialized due to mistake in openning Blood.png");
        return 0;
    }
    sf::Sprite button(bloodTex);
    button.setPosition({ 150.f, 200.f });
    //-----------------------------------

    //Setting font and output string
    sf::Font font;
    if (!font.openFromFile("SehnsuchtFont.ttf"))
    {
        printf("Font wasn't initialized due to mistake in openning SehnsuchtFont.ttf");
        return 0;
    }

    sf::Text text(font); // a font is required to make a text object
    text.setString("Crack Me"); // set the string to display
    text.setCharacterSize(24); //set the character size in pixels, not points!
    text.setFillColor(sf::Color::White); // set the color
    text.setPosition({ 165.f, 205.f });
    //-------------------------------------------

    //Soundtrack setting
    sf::SoundBuffer music;
    if (!music.loadFromFile("backgrdMusic.wav"))
    {
        printf("Buffer wasn't initialized due to mistake in openning backgrdMusic.wav");
        return 0;
    }
 
    sf::Sound sound(music);
    sound.play();
    //End of soundteack setting

    //initializating variable to count number of iterations
    size_t iteration = 0;
    bool OnButton        = false;
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
                if (150 <= mouseMoved->position.x && mouseMoved->position.x <= 350 && 
                    200 <= mouseMoved->position.y && mouseMoved->position.y <= 280)
                {
                    OnButton = true;
                    int x = mouseMoved->position.x;
                    int y = mouseMoved->position.y;
                    printf("%d %d\n", x, y);

                    button.setColor(sf::Color::Green);      // green
                }

                else
                {
                    if (OnButton == true)
                    {
                        button.setColor(sf::Color::Red);    // red
                        OnButton = false;
                    }
                }
            }

            if (OnButton && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                ButtonIsPressed = true;

            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left && OnButton && ButtonIsPressed)
                {
                    printf("Initialising Crack\n");
                    if (CrackCode() == FailCrack)
                        printf("Please try again unable to crack due to a mistake\n");
                    else
                        printf("Cracked\n");
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
            FrameX -= ShiftFrameBackX;  //background.move({ 5*506.f, -284.f });
            FrameY += Height;
        }
        else
            FrameX += Width;            //background.move({ -506.f, 0.f });

        if (iteration == NumOfFrames)
        {
            FrameX -=  3 * Width;       //background.move({ 3 * 506.f , 13 * 284.f });
            FrameY -= ShiftFrameBackY;
            iteration = 0;
        }

        background.setTextureRect(sf::IntRect({ FrameX, FrameY }, { Width, Height }));

        Sleep(MlsPerFrame);              //sets 80 ms so that background look nice
        //--------------------------------------------------

        window.clear();
        window.draw(background);            //draw backdround to buffer
        window.draw(button);                //draw blood button to buffer
        window.draw(text);                  //draw "Crack me" string to buffer
        window.display();
    }
}

CrackStatus CrackCode(void)
{
    FILE* FileToHack;
    if (fopen_s(&FileToHack, FileName, "rb")) // returns zero if file is succesfully opened
        return FailCrack;
    else
    {
        struct stat file_inf = {};
        stat(FileName, &file_inf);

        unsigned char* buffer = (unsigned char*)calloc((size_t)file_inf.st_size + 1, sizeof(unsigned char));

        if (!buffer)
            return FailCrack;

        size_t read = fread(buffer, sizeof(unsigned char), (size_t)file_inf.st_size, FileToHack);
        printf("read = %zu\n", read);
        if (read != 0)
            buffer[ByteToChange] = 0;

        fclose(FileToHack);

        if (fopen_s(&FileToHack, FileName, "wb")) // returns zero if couldn`t open file
        {
            printf("broke here\n");
            return FailCrack;
        }

        size_t written = fwrite(buffer, sizeof(unsigned char), (size_t)file_inf.st_size, FileToHack);
        printf("written = %zu\n", written);

        fclose(FileToHack);
        return SuccCrack;
    }
}

#include "application.hpp"


namespace td {
    Application::Application() {
        window_.create(sf::VideoMode(1280, 720), "Druidic Defense");
        gui_.setWindow(window_);
    }

    int Application::run() {
        LaunchMainMenu();
        bool inMainMenu = true;

        while (window_.isOpen()) {

            if(inMainMenu) {
                
            }

            sf::Event event;
            while (window_.pollEvent(event)) {
                gui_.handleEvent(event);

                if (event.type == sf::Event::Closed) window_.close();

                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window_.close();

                //if ( event.type == sf::Event::MouseButtonReleased )
                //window.close();
            }

            window_.clear();
    
            gui_.draw();
    
            window_.display();
        }
        return 0;
    }

    void Application::LaunchMainMenu() {
        gui_.removeAllWidgets();

        tgui::Button::Ptr button_start = tgui::Button::create();
        gui_.add(button_start);

        button_start->setPosition("50%","50%");
        button_start->setOrigin(0.5f, 0.5f);
        button_start->setSize("20%","8%");

        button_start->getRenderer()->setBackgroundColor(sf::Color(205,133,63,255));
        button_start->getRenderer()->setBackgroundColorHover(sf::Color(205,133,63,255));
        button_start->getRenderer()->setBorderColor(sf::Color(139,69,19,255));
        button_start->getRenderer()->setBorderColorHover(sf::Color(139,69,19,255));
        button_start->getRenderer()->setRoundedBorderRadius(8.0f);
        button_start->getRenderer()->setBorders(5);

        tgui::Button::Ptr button_options = tgui::Button::copy(button_start);
        tgui::Button::Ptr button_quit = tgui::Button::copy(button_start);
        gui_.add(button_options);
        gui_.add(button_quit);

        button_options->setPosition("50%","60%");
        button_quit->setPosition("50%","70%");
        button_start->setText("Start Game");
        button_options->setText("Options");
        button_quit->setText("Quit Game");

        button_options->getRenderer()->setBorderColorFocused(sf::Color(255,0,0,255));
    }

    void Application::drawShopGui() {
        tgui::Button::Ptr button = tgui::Button::create();
        
        gui_.add(button);
        button->setPosition(200,200);
        button->setSize(80,100);

        button->getRenderer()->setBackgroundColor(sf::Color(205,133,63,255));
        button->getRenderer()->setBackgroundColorHover(sf::Color(205,133,63,255));
        button->getRenderer()->setBorderColor(sf::Color(139,69,19,255));
        button->getRenderer()->setBorderColorHover(sf::Color(139,69,19,255));
        button->getRenderer()->setRoundedBorderRadius(8.0f);

        button->setText("880");
    }




} // namespace td
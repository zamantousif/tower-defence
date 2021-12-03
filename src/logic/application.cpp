
#include "application.hpp"
#include <string>
#include <unistd.h>


namespace td {
    Application::Application() {
        window_.create(sf::VideoMode(1280, 720), "Druidic Defense");
        gui_.setWindow(window_);
        state_ = types::kMainMenu;
    }

    int Application::run() {
        LaunchMainMenu();
        sf::Texture main_menu_bg_texture;
        main_menu_bg_texture.loadFromFile("Assets/Title_Screen.png", sf::IntRect(0, 0, 1920, 1080));
        sf::Sprite main_menu_bg_sprite;
        main_menu_bg_sprite.setTexture(main_menu_bg_texture);

        while (window_.isOpen()) {
            sf::Event event;
            while (window_.pollEvent(event)) {
                gui_.handleEvent(event);

                if (event.type == sf::Event::Closed) window_.close();
            }

            if (state_ == types::kMainMenu) {
                HandleMainMenu();
                main_menu_bg_sprite.setScale(sf::Vector2f(window_.getSize().x/1920, window_.getSize().y/1080));
                window_.draw(main_menu_bg_sprite);
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
        tgui::Button::Ptr button_options = tgui::Button::create();
        tgui::Button::Ptr button_quit = tgui::Button::create();
        gui_.add(button_start, "button_start");
        gui_.add(button_options, "button_options");
        gui_.add(button_quit, "button_quit");

        button_start->setPosition("50%","50%");
        button_start->setOrigin(0.5f, 0.5f);
        button_start->setSize("20%","8%");
        button_options->setPosition("50%","60%");
        button_options->setOrigin(0.5f, 0.5f);
        button_options->setSize("20%","8%");
        button_quit->setPosition("50%","70%");
        button_quit->setOrigin(0.5f, 0.5f);
        button_quit->setSize("20%","8%");

        button_start->setText("Start Game");
        button_options->setText("Options");
        button_quit->setText("Quit Game");

        StyleButtonBrown(button_start);
        StyleButtonBrown(button_options);
        StyleButtonBrown(button_quit);

        button_options->getRenderer()->setBorderColorFocused(sf::Color(255,0,0,255));
    }

    void Application::HandleMainMenu() {
        tgui::Button::Ptr button_quit = gui_.get<tgui::Button>("button_quit");
        button_quit->onPress([&]{ window_.close(); });
    }

    void Application::StyleButtonBrown(tgui::Button::Ptr button) {
        button->getRenderer()->setBackgroundColor(sf::Color(205,133,63,255));
        button->getRenderer()->setBackgroundColorHover(sf::Color(205,133,63,255));
        button->getRenderer()->setBorderColor(sf::Color(139,69,19,255));
        button->getRenderer()->setBorderColorHover(sf::Color(139,69,19,255));
        button->getRenderer()->setRoundedBorderRadius(8.0f);
        button->getRenderer()->setBorders(5);
        button->setTextSize(20);
    }

    void Application::QuitPressed() {
        window_.close();
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
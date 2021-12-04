
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
        LaunchMainMenuGui();
        sf::Texture main_menu_bg_texture;
        main_menu_bg_texture.loadFromFile("Assets/Title_Screen.png");
        sf::Sprite main_menu_bg_sprite;
        main_menu_bg_sprite.setTexture(main_menu_bg_texture);

        sf::Texture blank_texture;   //placeholder
        blank_texture.create(400,1080);
        sf::Sprite blank_sprite;     //placeholder
        blank_sprite.setTexture(blank_texture);
        blank_sprite.setColor(sf::Color(205,133,63,255));
        blank_sprite.setPosition(sf::Vector2f(window_.getSize().x*1520/1920, 0.f));

        //load font to use with sf::Text

        while (window_.isOpen()) {
            sf::Event event;
            while (window_.pollEvent(event)) {
                gui_.handleEvent(event);

                if (event.type == sf::Event::Closed) window_.close();
            }

            window_.clear();

            if (state_ == types::kMainMenu) {  //this if-else mess will be changed to a switch/case with individual functions
                HandleMainMenuGui();
                main_menu_bg_sprite.setScale(sf::Vector2f(window_.getSize().x/1920, window_.getSize().y/1080));
                window_.draw(main_menu_bg_sprite);

            } else if (state_ == types::kMapSelect) {
                HandleMapSelectGui();
                //draw background here
                sf::Text select_text;
                select_text.setString("Select Map");
                select_text.setFillColor(sf::Color(139,69,19,255));
                select_text.setCharacterSize(60);
                select_text.setOrigin(select_text.getLocalBounds().width/2, select_text.getLocalBounds().height/2);
                select_text.setPosition(sf::Vector2f(window_.getSize().x/960, window_.getSize().y/200));
                window_.draw(select_text);  //doesn't work because a font isn't loaded

            } else if (state_ == types::kGame) {
                HandleGameGui();
                window_.draw(blank_sprite);
                //run gametick
                //draw map
                //render game objects
            }

            gui_.draw();
    
            window_.display();
        }
        return 0;
    }

    void Application::LaunchMainMenuGui() {
        gui_.removeAllWidgets();
        state_ = types::kMainMenu;

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

        button_options->getRenderer()->setBorderColorFocused(sf::Color(255,255,0,255));
        button_options->getRenderer()->setBorderColorDownFocused(sf::Color(255,255,0,255));
    }

    void Application::HandleMainMenuGui() {
        tgui::Button::Ptr button_start = gui_.get<tgui::Button>("button_start");
        tgui::Button::Ptr button_options = gui_.get<tgui::Button>("button_options");
        tgui::Button::Ptr button_quit = gui_.get<tgui::Button>("button_quit");
        button_start->onPress([&]{ LaunchMapSelectGui(); });
        button_quit->onPress([&]{ window_.close(); });
    }

    void Application::LaunchMapSelectGui() {
        gui_.removeAllWidgets();
        state_ = types::kMapSelect;

        tgui::Button::Ptr button_map1 = tgui::Button::create();
        tgui::Button::Ptr button_map2 = tgui::Button::create();
        tgui::Button::Ptr button_exit = tgui::Button::create();
        gui_.add(button_map1, "button_map1");
        gui_.add(button_map2, "button_map2");
        gui_.add(button_exit, "button_exit");

        button_map1->setPosition("38%","50%");
        button_map1->setOrigin(0.5f, 0.5f);
        button_map1->setSize("20%","35%");
        button_map2->setPosition("62%","50%");
        button_map2->setOrigin(0.5f, 0.5f);
        button_map2->setSize("20%","35%");
        button_exit->setPosition("10%","15%");
        button_exit->setOrigin(0.5f, 0.5f);
        button_exit->setSize("16%","8%");

        button_exit->setText("Exit");

        StyleButtonBrown(button_map1);
        StyleButtonBrown(button_map2);
        StyleButtonBrown(button_exit);
    }

    void Application::HandleMapSelectGui() {
        tgui::Button::Ptr button_map1 = gui_.get<tgui::Button>("button_map1");
        tgui::Button::Ptr button_map2 = gui_.get<tgui::Button>("button_map2");
        tgui::Button::Ptr button_exit = gui_.get<tgui::Button>("button_exit");
        button_map1->onPress([&]{ LaunchGame("map1"); });
        button_map2->onPress([&]{ LaunchGame("map2"); });
        button_exit->onPress([&]{ LaunchMainMenuGui(); });
    }

    void Application::LaunchGame(std::string map_name) {
        LaunchGameGui();
        //new game
        //load corresponding map into game
    }

    void Application::LaunchGameGui() {
        gui_.removeAllWidgets();
        state_ = types::kGame;

        tgui::Button::Ptr button_tower_ba = tgui::Button::create();  //basic tower
        tgui::Button::Ptr button_tower_bo = tgui::Button::create();  //bomb tower
        tgui::Button::Ptr button_tower_fr = tgui::Button::create();  //frigid stump
        tgui::Button::Ptr button_tower_th = tgui::Button::create();  //thorn eruptor
        tgui::Button::Ptr button_tower_sn = tgui::Button::create();  //sniper
        tgui::Button::Ptr button_tower_ci = tgui::Button::create();  //cinder stump
        tgui::Button::Ptr button_pause = tgui::Button::create();
        tgui::Button::Ptr button_start_wave = tgui::Button::create();
        
        gui_.add(button_tower_ba);
        gui_.add(button_tower_bo);
        gui_.add(button_tower_fr);
        gui_.add(button_tower_th);
        gui_.add(button_tower_sn);
        gui_.add(button_tower_ci);
        gui_.add(button_pause);
        gui_.add(button_start_wave);

        StyleButtonBrown(button_tower_ba);
        StyleButtonBrown(button_tower_bo);
        StyleButtonBrown(button_tower_fr);
        StyleButtonBrown(button_tower_th);
        StyleButtonBrown(button_tower_sn);
        StyleButtonBrown(button_tower_ci);
        StyleButtonBrown(button_pause);
        StyleButtonBrown(button_start_wave);

        button_tower_ba->setPosition("80%", "13%");
        button_tower_bo->setPosition("86.5%", "13%");
        button_tower_fr->setPosition("93%", "13%");
        button_tower_th->setPosition("80%", "27%");
        button_tower_sn->setPosition("86.5%", "27%");
        button_tower_ci->setPosition("93%", "27%");
        button_pause->setPosition("95%", "2%");
        button_start_wave->setPosition("80.5%", "90%");

        button_tower_ba->setSize("6%", "13%");
        button_tower_bo->setSize("6%", "13%");
        button_tower_fr->setSize("6%", "13%");
        button_tower_th->setSize("6%", "13%");
        button_tower_sn->setSize("6%", "13%");
        button_tower_ci->setSize("6%", "13%");
        button_pause->setSize("4%", "7.5%");
        button_start_wave->setSize("18%", "7%");

        button_start_wave->setText("Start Wave");

    }

    void Application::HandleGameGui() {
        tgui::Button::Ptr button_tower_ba = gui_.get<tgui::Button>("button_tower_ba");
        tgui::Button::Ptr button_tower_bo = gui_.get<tgui::Button>("button_tower_bo");
        tgui::Button::Ptr button_tower_fr = gui_.get<tgui::Button>("button_tower_fr");
        tgui::Button::Ptr button_tower_th = gui_.get<tgui::Button>("button_tower_th");
        tgui::Button::Ptr button_tower_sn = gui_.get<tgui::Button>("button_tower_sn");
        tgui::Button::Ptr button_tower_ci = gui_.get<tgui::Button>("button_tower_ci");
        tgui::Button::Ptr button_pause = gui_.get<tgui::Button>("button_pause");
        tgui::Button::Ptr button_start_wave = gui_.get<tgui::Button>("button_start_wave");

        //button_pause->onPress([&]{ CreatePauseGui(); });
        //button_start_wave->onPress([&]{ game_.StartWave(); });
    }

    void Application::StyleButtonBrown(tgui::Button::Ptr button) {
        auto button_renderer = button->getRenderer();
        button_renderer->setBackgroundColor(sf::Color(205,133,63,255));
        button_renderer->setBackgroundColorHover(sf::Color(205,133,63,255));
        button_renderer->setBorderColor(sf::Color(139,69,19,255));
        button_renderer->setBorderColorHover(sf::Color(139,69,19,255));
        button_renderer->setBackgroundColorDown(sf::Color(185,115,53,255));
        button_renderer->setBorderColorDown(sf::Color(139,69,19,255));
        button_renderer->setBorderColorFocused(sf::Color(139,69,19,255));
        button_renderer->setRoundedBorderRadius(8.0f);
        button_renderer->setBorders(5);
        button->setTextSize(20);
    }


} // namespace td
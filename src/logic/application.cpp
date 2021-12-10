
#include "application.hpp"
#include <string>
#include <stdio.h>


namespace td {
    Application::Application() {
        window_x_ = 1280;
        window_y_ = 720;
        window_.create(sf::VideoMode(window_x_, window_y_), "Druidic Defense");

        gui_.setWindow(window_);

        font_.loadFromFile("../Assets/arial.TTF");
    }

    int Application::run() {
        LoadTextures();
        LaunchMainMenuGui();

        while (window_.isOpen()) {  //main loop
            sf::Event event;
            while (window_.pollEvent(event)) {
                gui_.handleEvent(event);

                if (event.type == sf::Event::Closed) window_.close();

                /*
                //handle click events when buying towers
                if (state_ == types::kGame && buying_tower_ != nullptr && event.type == sf::Event::MouseButtonPressed) {
                    float mouse_x = event.mouseButton.x*(1920.f/window_.getSize().x);
                    float mouse_y = event.mouseButton.y*(1080.f/window_.getSize().y)
                    if (mouse_x >= 1520) {
                        //gui was clicked while buying tower
                        delete(buying_tower_);
                        buying_tower_ = nullptr;
                    } else {
                        //position on the map was clicked while buying a tower
                        if (!CheckCollision()) {
                            game_.buyTower(buying_tower_);
                            buying_tower_ = nullptr;
                        } else {
                            sf::Sound buubuu;
                            buubuu.LoadFromFile("../Assets/Sounds/buubuu.wmv");
                            buubuu.setVolume(volume_);
                            buubuu.play();
                        }
                    }
                }

                if (state_ == types::kGame && buying_tower_ == nullptr && event.type == sf::Event::MouseButtonPressed) {
                    float mouse_x = event.mouseButton.x*(1920.f/window_.getSize().x);
                    float mouse_y = event.mouseButton.y*(1080.f/window_.getSize().y)
                    for (auto tower : game_.getTowers()) {
                        if ( tower->getHitbox() <= sqrt(pow(mouse_x, tower->getPosition().x, 2) + pow(mouse_y, tower->getPosition().y, 2)) ) {
                            upgrading_tower_ = tower;
                            LaunchUpgradeGui();
                            break;
                        }
                    }
                }
                **/
            }

            window_.clear();

            switch (state_) {
                case types::kGame:
                    HandleGame();
                    break;
                case types::kMainMenu:
                    HandleMainMenu();
                    break;
                case types::kOptions:
                    HandleOptions();
                    break;
                case types::kMapSelect:
                    HandleMapSelect();
                    break;
                case types::kPause:
                    HandlePause();
                    break;
                case types::kUpgrade:
                    HandleUpgrade();
                    break;
            }

            gui_.draw();

            switch (state_) {   //draw things that need to be drawn on top of the gui
                case types::kGame:
                    DrawShopElements();
                    break;
                case types::kPause:
                    DrawShopElements();
                    break;
                case types::kUpgrade:
                    DrawShopElements();
                    break;
                default:
                break;
            }
    
            window_.display();

        }  //main loop end

        for (auto string_texture_pair : textures_) {  //deletes textures
            delete(string_texture_pair.second);
        }
        return 0;
    }

    void Application::LoadTextures() {
        sf::Texture* main_menu_bg_texture = new sf::Texture();
        main_menu_bg_texture->loadFromFile("../Assets/title_screen.png");
        textures_["main_menu_bg"] = main_menu_bg_texture;

        sf::Texture* map_select_bg = new sf::Texture();
        map_select_bg->loadFromFile("../Assets/map_select_bg.jpg");
        textures_["map_select_bg"] = map_select_bg;
    
        sf::Texture* shop_bg = new sf::Texture();
        shop_bg->loadFromFile("../Assets/shop_background.jpg");
        textures_["shop_bg"] = shop_bg;

        sf::Texture* map1 = new sf::Texture();
        map1->loadFromFile("../Assets/map1.jpg");
        textures_["map1"] = map1;
    
        sf::Texture* upgrade_1 = new sf::Texture();
        upgrade_1->loadFromFile("../Assets/upgrade_1.jpg");
        textures_["upgrade_1"] = upgrade_1;

        sf::Texture* upgrade_2 = new sf::Texture();
        upgrade_2->loadFromFile("../Assets/upgrade_2.jpg");
        textures_["upgrade_2"] = upgrade_2;

        sf::Texture* upgrade_3 = new sf::Texture();
        upgrade_3->loadFromFile("../Assets/upgrade_3.jpg");
        textures_["upgrade_3"] = upgrade_3;

        sf::Texture* upgrade_4 = new sf::Texture();
        upgrade_4->loadFromFile("../Assets/upgrade_4.jpg");
        textures_["upgrade_4"] = upgrade_4;

        sf::Texture* pause_icon = new sf::Texture();
        pause_icon->loadFromFile("../Assets/pause_icon.png");
        textures_["pause_icon"] = pause_icon;

        sf::Texture* arrow_left = new sf::Texture();
        arrow_left->loadFromFile("../Assets/arrow_left.png");
        textures_["arrow_left"] = arrow_left;

        sf::Texture* arrow_right = new sf::Texture();
        arrow_right->loadFromFile("../Assets/arrow_right.png");
        textures_["arrow_right"] = arrow_right;

        sf::Texture* red_rectangle = new sf::Texture();
        red_rectangle->loadFromFile("../Assets/red_rectangle.jpg");
        textures_["red_rectangle"] = red_rectangle;

        sf::Texture* yellow_rectangle = new sf::Texture();
        yellow_rectangle->loadFromFile("../Assets/yellow_rectangle.jpg");
        textures_["yellow_rectangle"] = yellow_rectangle;

        sf::Texture* white_rectangle = new sf::Texture();
        white_rectangle->loadFromFile("../Assets/white_rectangle.jpg");
        textures_["white_rectangle"] = white_rectangle;



    }

    void Application::LaunchMainMenuGui() {
        if(state_ == types::kMainMenu) {
            return;
        }
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
    }

    void Application::HandleMainMenu() {
        HandleMainMenuGui();
        sf::Sprite main_menu_bg;
        main_menu_bg.setTexture(*textures_["main_menu_bg"], true);
        ScaleSprite(main_menu_bg);
        window_.draw(main_menu_bg);
    }

    void Application::HandleMainMenuGui() {
        tgui::Button::Ptr button_start = gui_.get<tgui::Button>("button_start");
        tgui::Button::Ptr button_options = gui_.get<tgui::Button>("button_options");
        tgui::Button::Ptr button_quit = gui_.get<tgui::Button>("button_quit");
        button_start->onPress([&]{ LaunchMapSelectGui(); });
        button_options->onPress([&]{ LaunchOptionsGui(); });
        button_quit->onPress([&]{ window_.close(); });
    }

    void Application::LaunchMapSelectGui() {
        if(state_ == types::kMapSelect) {
            return;
        }
        gui_.removeAllWidgets();
        state_ = types::kMapSelect;

        tgui::Button::Ptr button_map1 = tgui::Button::create();
        tgui::Button::Ptr button_map2 = tgui::Button::create();
        tgui::Button::Ptr button_exit = tgui::Button::create();
        gui_.add(button_map1, "button_map1");
        gui_.add(button_map2, "button_map2");
        gui_.add(button_exit, "button_exit");

        button_map1->setPosition("36%","50%");
        button_map1->setOrigin(0.5f, 0.5f);
        button_map1->setSize("24%","35%");
        button_map2->setPosition("64%","50%");
        button_map2->setOrigin(0.5f, 0.5f);
        button_map2->setSize("24%","35%");
        button_exit->setPosition("10%","15%");
        button_exit->setOrigin(0.5f, 0.5f);
        button_exit->setSize("16%","8%");

        button_exit->setText("Exit");

        StyleButtonBrown(button_map1);
        StyleButtonBrown(button_map2);
        StyleButtonBrown(button_exit);

        button_map1->getRenderer()->setTexture(*textures_["map1"]);
    }

    void Application::HandleMapSelect() {
        HandleMapSelectGui();
        
        sf::Sprite map_select_bg;
        map_select_bg.setTexture(*textures_["map_select_bg"], true);
        ScaleSprite(map_select_bg);
        window_.draw(map_select_bg);

        sf::Text select_text("Select Map", font_, 60);
        select_text.setFillColor(sf::Color(139,69,19,255));
        select_text.setOrigin(select_text.getLocalBounds().width/2, select_text.getLocalBounds().height/2);
        select_text.setPosition(sf::Vector2f(window_x_/2, window_y_/5));
        window_.draw(select_text);
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
        LaunchUpgradeGui();  //temporary test
        game_ = Game();

        //TODO: load corresponding map into game (variable could be file path instead of map name)

        //load map texture based on map.getBackgroundImagePath()
    }

    void Application::LaunchGameGui() {
        if(state_ == types::kGame) {
            return;
        }
        state_ = types::kGame;
        gui_.removeAllWidgets();

        tgui::Button::Ptr button_tower_ba = tgui::Button::create();  //basic tower
        tgui::Button::Ptr button_pause = tgui::Button::create();
        tgui::Button::Ptr button_start_wave = tgui::Button::create();

        button_tower_ba->getRenderer()->setBorderColorFocused(sf::Color(255,255,0,255));
        button_tower_ba->getRenderer()->setBorderColorDownFocused(sf::Color(255,255,0,255));
        button_tower_ba->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));
        button_tower_ba->getRenderer()->setBackgroundColorDisabled(sf::Color(165,100,35,255));
        button_pause->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));
        button_pause->getRenderer()->setBackgroundColorDisabled(sf::Color(165,100,35,255));
        button_pause->getRenderer()->setTexture(*textures_["pause_icon"]);
        button_start_wave->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));
        button_start_wave->getRenderer()->setBackgroundColorDisabled(sf::Color(165,100,35,255));
        StyleButtonBrown(button_tower_ba);
        StyleButtonBrown(button_pause);
        StyleButtonBrown(button_start_wave);

        tgui::Button::Ptr button_tower_bo = tgui::Button::copy(button_tower_ba);  //bomb tower
        tgui::Button::Ptr button_tower_fr = tgui::Button::copy(button_tower_ba);  //frigid stump
        tgui::Button::Ptr button_tower_th = tgui::Button::copy(button_tower_ba);  //thorn eruptor
        tgui::Button::Ptr button_tower_sn = tgui::Button::copy(button_tower_ba);  //sniper
        tgui::Button::Ptr button_tower_ci = tgui::Button::copy(button_tower_ba);  //cinder stump

        button_tower_ba->setPosition("80.1%", "13%");
        button_tower_bo->setPosition("86.6%", "13%");
        button_tower_fr->setPosition("93.1%", "13%");
        button_tower_th->setPosition("80.1%", "27%");
        button_tower_sn->setPosition("86.6%", "27%");
        button_tower_ci->setPosition("93.1%", "27%");
        button_pause->setPosition("95.1%", "2%");
        button_start_wave->setPosition("80.6%", "90%");

        button_tower_ba->setSize("6%", "13%");
        button_tower_bo->setSize("6%", "13%");
        button_tower_fr->setSize("6%", "13%");
        button_tower_th->setSize("6%", "13%");
        button_tower_sn->setSize("6%", "13%");
        button_tower_ci->setSize("6%", "13%");
        button_pause->setSize("4%", "7.5%");
        button_start_wave->setSize("18%", "7%");

        button_start_wave->setText("Start Wave");

        gui_.add(button_tower_ba, "button_tower_ba");
        gui_.add(button_tower_bo, "button_tower_bo");
        gui_.add(button_tower_fr, "button_tower_fr");
        gui_.add(button_tower_th, "button_tower_th");
        gui_.add(button_tower_sn, "button_tower_sn");
        gui_.add(button_tower_ci, "button_tower_ci");
        gui_.add(button_pause, "button_pause");
        gui_.add(button_start_wave, "button_start_wave");
    }

    void Application::HandleGame() {
        
        sf::Sprite map_sprite;
        map_sprite.setTexture(*textures_["map1"], true);  //TODO: change map1 to map
        ScaleSprite(map_sprite);
        window_.draw(map_sprite);

        HandleGameGui();

        //game_.value().update();

        DrawGameElements();

        if (buying_tower_ != nullptr) {
            int mouse_x = sf::Mouse::getPosition().x;
            int mouse_y = sf::Mouse::getPosition().y;

            
            //draws range circle of buying_tower_
            sf::CircleShape range_circle = sf::CircleShape(buying_tower_->getRange(), 40);
            range_circle.setOrigin(buying_tower_->getRange(), buying_tower_->getRange());
            ScaleSprite(range_circle);
            range_circle.setPosition(mouse_x, mouse_y);
            //if (game_.value().CheckCollision(sf::Vector2f(mouse_x*1920/window_x_, mouse_y*1080/window_y_), buying_tower_->getRange())) {    //TODO: add proper 
                range_circle.setFillColor(sf::Color(100,100,100,70));
            //} else {
            //    range_circle.setFillColor(sf::Color(150,0,0,70));
            //}
            window_.draw(range_circle);

            sf::Sprite buying_tower_sprite;
            buying_tower_sprite.setTexture(*buying_tower_->getTexture());
            buying_tower_sprite.setPosition(buying_tower_->getPosition());
            buying_tower_sprite.setOrigin(buying_tower_sprite.getLocalBounds().width/2, buying_tower_sprite.getLocalBounds().height/2);
            ScaleSprite(buying_tower_sprite);
            window_.draw(buying_tower_sprite);
            
        }

        sf::Sprite shop_bg;
        shop_bg.setTexture(*textures_["shop_bg"], true);
        shop_bg.setPosition(sf::Vector2f(window_x_*1520.f/1920.f, 0.f));
        ScaleSprite(shop_bg);
        window_.draw(shop_bg);
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

        bool do_once = true;  //tgui buttons have a bad habit of triggering multiple times, this fixes that

        button_pause->onPress([&]{ LaunchPauseGui(); });
        //button_start_wave->onPress([&]{ if (!game_.getRoundOngoing()) game_.StartWave(); });
        /*
        button_tower_ba->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("basic_tower", textures_["basic_tower"]);
                                      do_once = false; });
        button_tower_bo->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("bomb_tower", textures_["bomb_tower"]);
                                      do_once = false; });
        button_tower_fr->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("frigid_stump", textures_["frigid_stump"]);
                                      do_once = false; });
        button_tower_th->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("basic_tower", textures_["basic_tower"]);
                                      do_once = false; });
        button_tower_sn->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("sniper_tower", textures_["sniper_tower"]);
                                      do_once = false; });
        button_tower_ci->onPress([&] {if (do_once) buying_tower_ = game_.StartBuying("cinder_stump", textures_["cinder_stump"]);
                                      do_once = false; });
        */

        //if (game_.round_active) {
        //    button_start_wave->setEnabled(false);
        //} else {
        //    button_start_wave->setEnabled(true);
        //}

        static std::string title_string = "";
        static std::string desc_string = "";

        button_tower_ba->onMouseEnter([&]{ if (title_string == "") title_string = "Seed Shooter"; });
        button_tower_bo->onMouseEnter([&]{ if (title_string == "") title_string = "Coconut Cannon"; });
        button_tower_fr->onMouseEnter([&]{ if (title_string == "") title_string = "Frigid Stump"; });
        button_tower_th->onMouseEnter([&]{ if (title_string == "") title_string = "Thorn Eruptor"; });
        button_tower_sn->onMouseEnter([&]{ if (title_string == "") title_string = "Sniper"; });
        button_tower_ci->onMouseEnter([&]{ if (title_string == "") title_string = "Cinder Stump"; });

        button_tower_ba->onMouseEnter([&]{ if (desc_string == "") desc_string = "Seed Shooter"; });
        button_tower_bo->onMouseEnter([&]{ if (desc_string == "") desc_string = "Coconut Cannon"; });
        button_tower_fr->onMouseEnter([&]{ if (desc_string == "") desc_string = "The magic crystal atop this\nstump slows down foes in\nan area around the tower.\nUpgrading the tower\nfurther increases\nslowing amount.\nTier 4 variant also\nmakes enemies in range\nmore vulnerable to\ndamage from your other\ntowers."; });
        button_tower_th->onMouseEnter([&]{ if (desc_string == "") desc_string = "Thorn Eruptor"; });
        button_tower_sn->onMouseEnter([&]{ if (desc_string == "") desc_string = "Sniper"; });
        button_tower_ci->onMouseEnter([&]{ if (desc_string == "") desc_string = "Cinder Stump"; });

        button_tower_ba->onMouseLeave([&]{ title_string = ""; desc_string = ""; });
        button_tower_bo->onMouseLeave([&]{ title_string = ""; desc_string = ""; });
        button_tower_fr->onMouseLeave([&]{ title_string = ""; desc_string = ""; });
        button_tower_th->onMouseLeave([&]{ title_string = ""; desc_string = ""; });
        button_tower_sn->onMouseLeave([&]{ title_string = ""; desc_string = ""; });
        button_tower_ci->onMouseLeave([&]{ title_string = ""; desc_string = ""; });

        sf::Text tower_title(title_string, font_, 26);
        tower_title.setOrigin(tower_title.getGlobalBounds().width/2, 0);
        tower_title.setPosition(sf::Vector2f(window_x_/(1920.f/1720.f), window_y_/(1080.f/460.f)));
        tower_title.setFillColor(sf::Color(255,255,255,255));
        tower_title.setOutlineColor(sf::Color(50,50,50,255));
        tower_title.setOutlineThickness(1);
        window_.draw(tower_title);

        sf::Text tower_desc(desc_string, font_, 20);
        tower_desc.setPosition(sf::Vector2f(window_x_/(1920.f/1540.f), window_y_/(1080.f/520.f)));
        tower_desc.setFillColor(sf::Color(255,255,255,255));
        tower_desc.setOutlineColor(sf::Color(50,50,50,255));
        tower_desc.setOutlineThickness(1);
        window_.draw(tower_desc);

        //code for buying towers
    }

    void Application::CloseGame() {
        //delete(game_);
        LaunchMainMenuGui();
    }

    void Application::LaunchOptionsGui() { 
        if(state_ == types::kOptions) {
            return;
        }
        gui_.removeAllWidgets();
        state_ = types::kOptions;

        tgui::Button::Ptr button_return = tgui::Button::create();
        tgui::Button::Ptr button_background = tgui::Button::create(); //used as a background
        tgui::Slider::Ptr slider_volume = tgui::Slider::create();
        tgui::Slider::Ptr slider_music_volume = tgui::Slider::create();
        tgui::ToggleButton::Ptr button_auto_start = tgui::ToggleButton::create();
        tgui::Button::Ptr music_text = tgui::Button::create();        //using an invisible button for text ensures it's in the right position

        gui_.add(button_background, "button_background");
        gui_.add(button_return, "button_return");
        gui_.add(button_auto_start, "button_auto_start");
        gui_.add(slider_volume, "slider_volume");
        gui_.add(slider_music_volume, "slider_music_volume");
        gui_.add(music_text);
        
        music_text->setEnabled(false);
        music_text->getRenderer()->setBackgroundColorDisabled(sf::Color(0,0,0,0));
        music_text->getRenderer()->setBorderColorDisabled(sf::Color(0,0,0,0));
        music_text->getRenderer()->setTextColorDisabled(sf::Color(129,59,16,255));
        music_text->setTextSize(21);
        music_text->setOrigin(0.5f, 0.5f);

        tgui::Button::Ptr sound_text = tgui::Button::copy(music_text);
        tgui::Button::Ptr options_text = tgui::Button::copy(music_text);
        gui_.add(sound_text);
        gui_.add(options_text);

        music_text->setText("Music Volume");
        sound_text->setText("Sound Volume");
        options_text->setText("Options");
        sound_text->setPosition("40.5%", "40%");
        music_text->setPosition("40.5%", "56%");
        options_text->setPosition("50%", "30%");
        options_text->setTextSize(37);

        StyleButtonBrown(button_return);

        auto slider_renderer = slider_volume->getSharedRenderer();
        slider_renderer->setTrackColor(sf::Color(195,123,53,255));
        slider_renderer->setTrackColorHover(sf::Color(195,123,53,255));
        slider_renderer->setThumbColor(sf::Color(139,69,19,255));
        slider_renderer->setThumbColorHover(sf::Color(139,69,19,255));

        auto button_renderer = button_auto_start->getRenderer();
        button_renderer->setBackgroundColor(sf::Color(195,123,53,255));
        button_renderer->setBackgroundColorHover(sf::Color(195,123,53,255));
        button_renderer->setBackgroundColorDown(sf::Color(0,100,0,255));
        button_renderer->setBorderColor(sf::Color(139,69,19,255));
        button_renderer->setBorderColorHover(sf::Color(139,69,19,255));
        button_renderer->setBorderColorDown(sf::Color(0,60,0,255));
        button_renderer->setBorderColorFocused(sf::Color(139,69,19,255));
        button_renderer->setBackgroundColorDownHover(sf::Color(0,100,0,255));
        button_renderer->setRoundedBorderRadius(8.0f);
        button_renderer->setBorders(5);
        button_auto_start->setTextSize(15);

        button_background->setEnabled(false);
        button_background->setOrigin(0.5f, 0.5f);
        button_background->getRenderer()->setRoundedBorderRadius(8.0f);
        button_background->getRenderer()->setBorders(5);
        button_background->getRenderer()->setBackgroundColorDisabled(sf::Color(205,133,63,255));
        button_background->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));

        button_return->setPosition("65%", "25%");
        button_background->setPosition("50%", "50%");
        button_auto_start->setPosition("60%", "50%");
        slider_volume->setPosition("33%", "44%");
        slider_music_volume->setPosition("33%", "60%");

        button_return->setSize("10%", "8%");
        button_background->setSize("50%", "50%");
        button_auto_start->setSize("8%", "12%");
        slider_volume->setSize("15%", "5%");
        slider_music_volume->setSize("15%", "5%");

        button_auto_start->setText("Auto Start\nRounds");
        button_return->setText("Return");

        slider_volume->setMinimum(0.f);
        slider_volume->setMaximum(100.f);
        slider_volume->setValue(volume_);
        slider_music_volume->setMinimum(0.f);
        slider_music_volume->setMaximum(100.f);
        slider_music_volume->setValue(music_volume_);

        //if (game_.auto_start_) {
        //    button_auto_start->setDown(true);
        //}
    }

    void Application::HandleOptions() {
        HandleOptionsGui();
        sf::Sprite main_menu_bg;
        main_menu_bg.setTexture(*textures_["main_menu_bg"], true);
        ScaleSprite(main_menu_bg);
        window_.draw(main_menu_bg);
    }

    void Application::HandleOptionsGui() {
        tgui::Button::Ptr button_return = gui_.get<tgui::Button>("button_return");
        tgui::ToggleButton::Ptr button_auto_start = gui_.get<tgui::ToggleButton>("button_auto_start");
        tgui::Slider::Ptr slider_volume = gui_.get<tgui::Slider>("slider_volume");
        tgui::Slider::Ptr slider_music_volume = gui_.get<tgui::Slider>("slider_music_volume");

        button_return->onPress(&Application::LaunchMainMenuGui, this);
        volume_ = slider_volume->getValue();
        music_volume_ = slider_music_volume->getValue();
        if (button_auto_start->isDown()) {
            //game_.auto_start_ = true;
        } else {
            //game_.auto_start_ = false;
        }

    }

    void Application::LaunchPauseGui() {
        if(state_ == types::kPause) {
            return;
        }
        state_ = types::kPause;

        for (auto widget : gui_.getWidgets()) {  //disables the gui of the game
            widget->setEnabled(false);
        }

        tgui::Button::Ptr button_return = tgui::Button::create();
        tgui::Button::Ptr button_background = tgui::Button::create(); //used as a background
        tgui::Button::Ptr button_off_menu = tgui::Button::create();   //massive invisible button outside menu
        tgui::Slider::Ptr slider_volume = tgui::Slider::create();
        tgui::Slider::Ptr slider_music_volume = tgui::Slider::create();
        tgui::ToggleButton::Ptr button_auto_start = tgui::ToggleButton::create();
        tgui::Button::Ptr music_text = tgui::Button::create();        //using an invisible button for text ensures it's in the right position

        gui_.add(button_background, "button_background");
        gui_.add(button_off_menu, "button_off_menu");
        gui_.add(button_return, "button_return");
        gui_.add(button_auto_start, "button_auto_start");
        gui_.add(slider_volume, "slider_volume");
        gui_.add(slider_music_volume, "slider_music_volume");
        gui_.add(music_text);
        
        music_text->setEnabled(false);
        music_text->getRenderer()->setBackgroundColorDisabled(sf::Color(0,0,0,0));
        music_text->getRenderer()->setBorderColorDisabled(sf::Color(0,0,0,0));
        music_text->getRenderer()->setTextColorDisabled(sf::Color(129,59,16,255));
        music_text->setTextSize(21);
        music_text->setOrigin(0.5f, 0.5f);

        tgui::Button::Ptr sound_text = tgui::Button::copy(music_text);
        tgui::Button::Ptr options_text = tgui::Button::copy(music_text);
        gui_.add(sound_text);
        gui_.add(options_text);

        music_text->setText("Music Volume");
        sound_text->setText("Sound Volume");
        options_text->setText("Paused");
        sound_text->setPosition("40.5%", "40%");
        music_text->setPosition("40.5%", "56%");
        options_text->setPosition("50%", "30%");
        options_text->setTextSize(37);

        StyleButtonBrown(button_return);
        tgui::Button::Ptr button_main_menu = tgui::Button::copy(button_return);
        gui_.add(button_main_menu, "button_main_menu");

        auto slider_renderer = slider_volume->getSharedRenderer();
        slider_renderer->setTrackColor(sf::Color(195,123,53,255));
        slider_renderer->setTrackColorHover(sf::Color(195,123,53,255));
        slider_renderer->setThumbColor(sf::Color(139,69,19,255));
        slider_renderer->setThumbColorHover(sf::Color(139,69,19,255));

        auto button_renderer = button_auto_start->getRenderer();
        button_renderer->setBackgroundColor(sf::Color(195,123,53,255));
        button_renderer->setBackgroundColorHover(sf::Color(195,123,53,255));
        button_renderer->setBackgroundColorDown(sf::Color(0,100,0,255));
        button_renderer->setBorderColor(sf::Color(139,69,19,255));
        button_renderer->setBorderColorHover(sf::Color(139,69,19,255));
        button_renderer->setBorderColorDown(sf::Color(0,60,0,255));
        button_renderer->setBorderColorFocused(sf::Color(139,69,19,255));
        button_renderer->setBackgroundColorDownHover(sf::Color(0,100,0,255));
        button_renderer->setRoundedBorderRadius(8.0f);
        button_renderer->setBorders(5);
        button_auto_start->setTextSize(15);

        button_off_menu->getRenderer()->setBackgroundColor(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBackgroundColorDown(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBackgroundColorHover(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBorders(0);

        button_background->setEnabled(false);
        button_background->setOrigin(0.5f, 0.5f);
        button_background->getRenderer()->setRoundedBorderRadius(8.0f);
        button_background->getRenderer()->setBorders(5);

        button_return->setPosition("65%", "25%");
        button_main_menu->setPosition("25%", "25%");
        button_off_menu->setPosition(0,0);
        button_background->setPosition("50%", "50%");
        button_auto_start->setPosition("60%", "50%");
        slider_volume->setPosition("33%", "44%");
        slider_music_volume->setPosition("33%", "60%");

        button_return->setSize("10%", "8%");
        button_main_menu->setSize("10%", "8%");
        button_off_menu->setSize("100%", "100%");
        button_background->setSize("50%", "50%");
        button_auto_start->setSize("8%", "12%");
        slider_volume->setSize("15%", "5%");
        slider_music_volume->setSize("15%", "5%");

        button_background->getRenderer()->setBackgroundColorDisabled(sf::Color(205,133,63,255));
        button_background->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));

        button_auto_start->setText("Auto Start\nRounds");
        button_return->setText("Continue");
        button_main_menu->setText("Quit");

        slider_volume->setMinimum(0.f);
        slider_volume->setMaximum(100.f);
        slider_volume->setValue(volume_);
        slider_music_volume->setMinimum(0.f);
        slider_music_volume->setMaximum(100.f);
        slider_music_volume->setValue(music_volume_);

        //if (game_.auto_start_) {
        //    button_auto_start->setDown(true);
        //}
    }

    void Application::HandlePause() {
        HandlePauseGui();

        sf::Sprite map_sprite;
        map_sprite.setTexture(*textures_["map1"], true);  //TODO: pull map name from game_.getMap()
        ScaleSprite(map_sprite);
        window_.draw(map_sprite);

        sf::Sprite shop_bg;
        shop_bg.setTexture(*textures_["shop_bg"], true);
        shop_bg.setPosition(sf::Vector2f(window_x_*1520.f/1920.f, 0.f));
        ScaleSprite(shop_bg);
        window_.draw(shop_bg);

        //DrawGameObjects();

    }

    void Application::HandlePauseGui() {
        tgui::Button::Ptr button_return = gui_.get<tgui::Button>("button_return");
        tgui::Button::Ptr button_main_menu = gui_.get<tgui::Button>("button_main_menu");
        tgui::Button::Ptr button_off_menu = gui_.get<tgui::Button>("button_off_menu");
        tgui::ToggleButton::Ptr button_auto_start = gui_.get<tgui::ToggleButton>("button_auto_start");
        tgui::Slider::Ptr slider_volume = gui_.get<tgui::Slider>("slider_volume");
        tgui::Slider::Ptr slider_music_volume = gui_.get<tgui::Slider>("slider_music_volume");

        button_return->onPress(&Application::LaunchGameGui, this);
        button_main_menu->onPress(&Application::CloseGame, this);
        button_off_menu->onPress(&Application::LaunchGameGui, this);
        volume_ = slider_volume->getValue();
        music_volume_ = slider_music_volume->getValue();
        if (button_auto_start->isDown()) {
            //game_.auto_start_ = true;
        } else {
            //game_.auto_start_ = false;
        }
    }

    void Application::LaunchUpgradeGui() {
        if (state_ == types::kUpgrade) {
            return;
        }
        state_ = types::kUpgrade;

        tgui::Button::Ptr button_off_menu = tgui::Button::create();   //massive invisible button outside menu
        button_off_menu->getRenderer()->setBackgroundColor(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBackgroundColorDown(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBackgroundColorHover(sf::Color(0,0,0,0));
        button_off_menu->getRenderer()->setBorders(0);
        button_off_menu->setSize("100%", "100%");
        button_off_menu->setPosition(0,0);
        gui_.add(button_off_menu, "button_off_menu");

        tgui::Button::Ptr button_background = tgui::Button::create();
        tgui::Button::Ptr button_target_left = tgui::Button::create();
        tgui::Button::Ptr button_target_right = tgui::Button::create();
        tgui::Button::Ptr button_targeting_text = tgui::Button::create(); //box that displays tower's current targeting
        tgui::Button::Ptr button_upgrade = tgui::Button::create();
        tgui::Button::Ptr button_sell = tgui::Button::create();

        gui_.add(button_background, "button_background");
        gui_.add(button_target_left, "button_target_left");
        gui_.add(button_target_right, "button_target_right");
        gui_.add(button_targeting_text, "button_targeting_text");
        gui_.add(button_upgrade, "button_upgrade");
        gui_.add(button_sell, "button_sell");

        button_background->setEnabled(false);
        button_background->getRenderer()->setRoundedBorderRadius(8.0f);
        button_background->getRenderer()->setBorders(5);
        button_background->getRenderer()->setBackgroundColorDisabled(sf::Color(205,133,63,255));
        button_background->getRenderer()->setBorderColorDisabled(sf::Color(139,69,19,255));

        StyleButtonBrown(button_target_left);
        StyleButtonBrown(button_target_right);
        StyleButtonBrown(button_targeting_text);
        button_target_left->getRenderer()->setRoundedBorderRadius(0);
        button_target_left->getRenderer()->setTexture(*textures_["arrow_left"]);
        button_target_right->getRenderer()->setRoundedBorderRadius(0);
        button_target_right->getRenderer()->setTexture(*textures_["arrow_right"]);
        button_targeting_text->getRenderer()->setRoundedBorderRadius(0);
        button_targeting_text->getRenderer()->setTextColor(sf::Color(20,20,20,255));
        button_targeting_text->setTextSize(20);
        
        button_upgrade->getRenderer()->setBorders(3);
        button_upgrade->getRenderer()->setBorderColor(sf::Color(10,63,10,255));
        button_upgrade->getRenderer()->setBorderColorDown(sf::Color(10,63,10,255));
        button_upgrade->getRenderer()->setBorderColorFocused(sf::Color(10,63,10,255));
        button_upgrade->getRenderer()->setTextColor(sf::Color(10,10,10,255));
        button_upgrade->setTextSize(22);

        button_sell->getRenderer()->setBorders(3);
        button_sell->getRenderer()->setBorderColor(sf::Color(50,0,0,255));
        button_sell->getRenderer()->setBorderColorDown(sf::Color(50,0,0,255));
        button_sell->getRenderer()->setBorderColorFocused(sf::Color(50,0,0,255));
        button_sell->getRenderer()->setBackgroundColor(sf::Color(180,0,0,255));
        button_sell->getRenderer()->setBackgroundColorDown(sf::Color(140,0,0,255));
        button_sell->getRenderer()->setBackgroundColorHover(sf::Color(180,0,0,255));
        button_sell->getRenderer()->setBackgroundColorFocused(sf::Color(180,0,0,255));
        button_sell->getRenderer()->setTextColor(sf::Color(0,0,0,255));
        button_sell->getRenderer()->setTextColorDown(sf::Color(0,0,0,255));
        button_sell->setTextSize(25);
        button_sell->setText("Sell");

        button_background->setPosition("80.6%", "42%");
        button_background->setSize("18%", "43%");
        
        button_target_left->setPosition(bindLeft(button_background) + "2%", bindTop(button_background) + "2%");
        button_target_right->setPosition(bindLeft(button_background) + "13%", bindTop(button_background) + "2%");
        button_targeting_text->setPosition(bindLeft(button_background) + "5%", bindTop(button_background) + "2%");
        button_upgrade->setPosition(bindLeft(button_background) + "1%", bindTop(button_background) + "16%");
        button_sell->setPosition(bindLeft(button_background) + "1%", bindTop(button_background) + "32%");

        button_target_left->setSize("3.5%", "6%");
        button_target_right->setSize("3.5%", "6%");
        button_targeting_text->setSize("8.2%", "6%");
        button_upgrade->setSize("16%", "8%");
        button_sell->setSize("16%", "8%");
    }

    void Application::HandleUpgrade() {
        HandleUpgradeGui();

        sf::Sprite map_sprite;
        map_sprite.setTexture(*textures_["map1"], true);  //TODO: pull map name from game_.getMap().getName()
        ScaleSprite(map_sprite);
        window_.draw(map_sprite);

        //draw range circle of upgrading_tower_
        //sf::CircleShape range_circle(upgrading_tower_->getRange(), 40);
        //range_circle.setOrigin(upgrading_tower_->getRange(), upgrading_tower_->getRange());
        //ScaleSprite(range_circle);
        //range_circle.setPosition(upgrading_tower_->getPosition());
        //range_circle.setFillColor(sf::Color(100,100,100,70));
        //window_.draw(range_circle);

        sf::Sprite shop_bg;
        shop_bg.setTexture(*textures_["shop_bg"], true);
        shop_bg.setPosition(sf::Vector2f(window_x_*1520.f/1920.f, 0.f));
        ScaleSprite(shop_bg);
        window_.draw(shop_bg);

        //render game objects
    }

    void Application::HandleUpgradeGui() {
        tgui::Button::Ptr button_off_menu = gui_.get<tgui::Button>("button_off_menu");
        tgui::Button::Ptr button_target_left = gui_.get<tgui::Button>("button_target_left");
        tgui::Button::Ptr button_target_right = gui_.get<tgui::Button>("button_target_right");
        tgui::Button::Ptr button_targeting_text = gui_.get<tgui::Button>("button_targeting_text");
        tgui::Button::Ptr button_upgrade = gui_.get<tgui::Button>("button_upgrade");
        tgui::Button::Ptr button_sell = gui_.get<tgui::Button>("button_sell");
        
        bool do_once = true;  //tgui buttons have a bad habit of triggering multiple times, this fixes that
        
        button_off_menu->onPress(&Application::LaunchGameGui, this);  //TODO: add upgrading_tower_ = nullptr;
        //button_target_left->onPress([&] {if (do_once) TargetingSwitchRight(); do_once = false; });
        //button_target_right->onPress([&] {if (do_once) TargetingSwitchLeft(); do_once = false; });
        //button_upgrade->onPress([&] {if (do_once) game_->UpgradeTower(upgrading_tower_); do_once = false; });
        //button_sell->onPress([&] {if (do_once) game_->SellTower(upgrading_tower_); do_once = false; upgrading_tower_ = nullptr; });
        
        /*
        switch (upgrading_tower_.getTargeting()) {    //make text match tower's value
            case types::kFirst:
                */button_targeting_text->setText("First");/*
                break;
            case types::kLast:
                button_targeting_text->setText("Last");
                break;
            case types::kClose:
                button_targeting_text->setText("Close");
                break;
            case types::kStrong:
                button_targeting_text->setText("Strong");
                break;
        }

        switch (upgrading_tower_.getLevel()) {    //make text match tower's value
            case 1:
                button_upgrade->getRenderer()->setTexture(*textures_["upgrade_1"]);
                button_upgrade->setText("Upgrade\n" + std::to_string(upgrading_tower_.getUpgradeCost()));
                break;
            case 2:
                button_upgrade->getRenderer()->setTexture(*textures_["upgrade_2"]);
                button_upgrade->setText("Upgrade\n" + std::to_string(upgrading_tower_.getUpgradeCost()));
                break;
            case 3:
                */button_upgrade->getRenderer()->setTexture(*textures_["upgrade_3"]);
                button_upgrade->setText("Upgrade\n(" + std::to_string(320) + ")");/*
                button_upgrade->setText("Upgrade\n" + std::to_string(upgrading_tower_.getUpgradeCost()));
                break;
            case 4:
                button_upgrade->getRenderer()->setTexture(*textures_["upgrade_4"]);
                button_upgrade->setText("Max level");
                break;
        }
        */
    }

    /**
    void Application::TargetingSwitchRight() {
        switch (upgrading_tower_.getTargeting()) {
            case types::kFirst:
                upgrading_tower_.setTargeting(types::kLast);
                break;
            case types::kLast:
                upgrading_tower_.setTargeting(types::kClose);
                break;
            case types::kClose:
                upgrading_tower_.setTargeting(types::kStrong);
                break;
            case types::kStrong:
                upgrading_tower_.setTargeting(types::kFirst);
                break;
        }
    }

    void Application::TargetingSwitchLeft() {
        switch (upgrading_tower_.getTargeting()) {
            case types::kFirst:
                upgrading_tower_.setTargeting(types::kStrong);
                break;
            case types::kLast:
                upgrading_tower_.setTargeting(types::kFirst);
                break;
            case types::kClose:
                upgrading_tower_.setTargeting(types::kLast);
                break;
            case types::kStrong:
                upgrading_tower_.setTargeting(types::kClose);
                break;
        }
    }
    **/

    void Application::DrawGameElements() {
        /*
        for (auto tower : game_.getTowers()) {
            sf::Sprite tower_sprite;
            tower_sprite.setTexture(tower.getTexture());
            ScaleSprite(tower_sprite);
            tower_sprite.scale(sf::Vector2f(tower.getHitboxRadius()/100.f, tower.getHitboxRadius()/100.f));
            tower_sprite.setOrigin(tower.getHitboxRadius(), tower.getHitboxRadius());
            tower_sprite.setPosition(1920/window_x_*tower.getPosition().x, 1080/window_y_*tower.getPosition().y);
            tower_sprite.setRotation(tower.getRotation());
            window_.draw(tower_sprite);
        }

        for (auto projectile : game_.getEnemies()) {
            sf::Sprite projectile_sprite;
            projectile_sprite.setTexture(projectile.getTexture());
            ScaleSprite(projectile_sprite);
            projectile_sprite.scale(sf::Vector2f(projectile.getHitboxRadius()/100.f, projectile.getHitboxRadius()/100.f));
            projectile_sprite.setOrigin(projectile.getHitboxRadius(), projectile.getHitboxRadius());
            projectile_sprite.setPosition(1920/window_x_*projectile.getPosition().x, 1080/window_y_*projectile.getPosition().y);
            projectile_sprite.setRotation(projectile.getRotation());
            window_.draw(projectile_sprite);
        }

        for (auto enemy : game_.getEnemies()) {
            sf::Sprite enemy_sprite;
            enemy_sprite.setTexture(enemy.getTexture());
            ScaleSprite(enemy_sprite);
            enemy_sprite.scale(sf::Vector2f(enemy.getHitboxRadius()/100.f, enemy.getHitboxRadius()/100.f));
            enemy_sprite.setOrigin(1920/window_x_*enemy.getHitboxRadius(), 1080/window_y_*enemy.getHitboxRadius());
            enemy_sprite.setPosition(1920/window_x_*enemy.getPosition().x, 1080/window_y_*enemy.getPosition().y);
            enemy_sprite.setRotation(enemy.getRotation());
            window_.draw(enemy_sprite);

            sf::Sprite health_bar_base;
            health_bar_base.setTexture(textures_["white_rectangle"]);
            ScaleSprite(health_bar_base);
            health_bar_base.setPosition(enemy_sprite.getPosition() - sf::Vector2f(36.f, 1.3f*1080/window_y_*enemy.getHitboxRadius()));
            window_.draw(health_bar_base);

            sf::Sprite health_bar_;
            if (enemy.isArmored()) {
                health_bar_.setTexture(textures_["yellow_rectangle"]);
            } else {
                health_bar_.setTexture(textures_["red_rectangle"]);
            }
            ScaleSprite(health_bar_);
            health_bar_.setPosition(enemy_sprite.getPosition() - sf::Vector2f(36.f, 1.3f*1080/window_y_*enemy.getHitboxRadius()));
            health_bar_.scale(enemy.getHealth()/enemy.getMaxHealth(), 1);
            window_.draw(health_bar_);
        }

        */
    }

    void Application::DrawShopElements() {
        sf::Text round_text("Round\n", font_, 22);   //round counter in the top right
        round_text.setOutlineColor(sf::Color(0,0,0,255));
        round_text.setFillColor(sf::Color(255,255,255,255));
        round_text.setOutlineThickness(2);
        round_text.setPosition(sf::Vector2f(window_x_/(1920.f/1500.f), window_y_/60.f));
        round_text.setOrigin(round_text.getLocalBounds().width, 0);
        window_.draw(round_text);

        sf::Text round_text2 = round_text;
        std::string round_string2 = std::to_string(3) + "/" + std::to_string(20);  //TODO: replace numbers with game_.getRound() etc
        round_text2.setString(round_string2);
        round_text2.setOrigin(round_text.getGlobalBounds().width, 0);
        round_text2.setPosition(sf::Vector2f(window_x_/(1920.f/1500.f), window_y_/20.f));
        window_.draw(round_text2);

        sf::Text money_text(std::to_string(420), font_, 25);   //money counter //TODO: change to game_.getMoney()
        money_text.setFillColor(sf::Color(0,150,0,255));
        money_text.setOutlineColor(sf::Color(0,100,0,255));
        money_text.setOutlineThickness(1);
        money_text.setPosition(sf::Vector2f(window_x_/(1920.f/1600.f), window_y_/(1080.f/20.f)));
        window_.draw(money_text);

        sf::Text lives_text(std::to_string(100), font_, 25);   //lives counter //TODO: change to game_.getLives()
        lives_text.setFillColor(sf::Color(150,0,0,255));
        lives_text.setOutlineColor(sf::Color(100,0,0,255));
        lives_text.setOutlineThickness(1);
        lives_text.setPosition(sf::Vector2f(window_x_/(1920.f/1600.f), window_y_/(1080.f/70.f)));
        window_.draw(lives_text);

        sf::Text price_text1(std::to_string(200), font_, 23);   //price of basic tower //TODO: change to correct value
        price_text1.setFillColor(sf::Color(0,150,0,255));
        price_text1.setOutlineColor(sf::Color(0,100,0,255));
        price_text1.setOutlineThickness(1);
        price_text1.setPosition(sf::Vector2f(window_x_/(1920.f/1611.f), window_y_/(1080.f/230.f)));
        price_text1.setOrigin(round_text.getGlobalBounds().width/2, 0);
        window_.draw(price_text1);

        sf::Text price_text2 = price_text1;
        price_text2.setString("300");   //TODO
        price_text2.setPosition(sf::Vector2f(window_x_/(1920.f/1737.f), window_y_/(1080.f/230.f)));
        window_.draw(price_text2);

        sf::Text price_text3 = price_text1;
        price_text3.setString("400");   //TODO
        price_text3.setPosition(sf::Vector2f(window_x_/(1920.f/1862.f), window_y_/(1080.f/230.f)));
        window_.draw(price_text3);

        sf::Text price_text4 = price_text1;
        price_text4.setString("500");   //TODO
        price_text4.setPosition(sf::Vector2f(window_x_/(1920.f/1611.f), window_y_/(1080.f/381.f)));
        window_.draw(price_text4);

        sf::Text price_text5 = price_text1;
        price_text5.setString("600");   //TODO
        price_text5.setPosition(sf::Vector2f(window_x_/(1920.f/1737.f), window_y_/(1080.f/381.f)));
        window_.draw(price_text5);

        sf::Text price_text6 = price_text1;
        price_text5.setString("700");   //TODO
        price_text5.setPosition(sf::Vector2f(window_x_/(1920.f/1862.f), window_y_/(1080.f/381.f)));
        window_.draw(price_text5);

        //TODO: draw tower icons

    }

    void Application::StyleButtonBrown(tgui::Button::Ptr button) {
        auto button_renderer = button->getRenderer();
        button_renderer->setBackgroundColor(sf::Color(205,133,63,255));
        button_renderer->setBackgroundColorHover(sf::Color(205,133,63,255));
        button_renderer->setBackgroundColorDown(sf::Color(185,115,53,255));
        button_renderer->setBorderColor(sf::Color(139,69,19,255));
        button_renderer->setBorderColorHover(sf::Color(139,69,19,255));
        button_renderer->setBorderColorDown(sf::Color(139,69,19,255));
        button_renderer->setBorderColorFocused(sf::Color(139,69,19,255));
        button_renderer->setRoundedBorderRadius(8.0f);
        button_renderer->setBorders(5);
        button->setTextSize(20);
    }

    void Application::ScaleSprite(sf::Transformable& sprite) {
        sprite.setScale(sf::Vector2f(window_x_/1920.f, window_y_/1080.f));
    }


} // namespace td
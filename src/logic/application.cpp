
#include "application.hpp"

#include <stdio.h>
#include "constants.hpp"
#include <string>

namespace td {
Application::Application() {
  window_x_ = 1280;
  window_y_ = 720;
  window_.create(sf::VideoMode(window_x_, window_y_), "Druidic Defense");

  gui_.setWindow(window_);

  font_.loadFromFile("../assets/arial.TTF");
}

Application::~Application() {
  if (game_) {
    delete(game_.value().getMap());
  }
}

int Application::run() {
  LoadTextures();
  LaunchMainMenuGui();

  sf::Music music;
  music.openFromFile("../assets/sounds/space_jazz.wav");
  music.setLoop(true);
  music.play();

  while (window_.isOpen()) {  // main loop
    sf::Event event;

    //Handle all sfml window events
    while (window_.pollEvent(event)) {
      gui_.handleEvent(event);

      if (event.type == sf::Event::Closed) window_.close();

      // handle clicking on towers in order to open the upgrade menu
      if (state_ == types::kGame && !buying_tower_ &&
          event.type == sf::Event::MouseButtonPressed) {
        float mouse_x = event.mouseButton.x * (1920.f / window_.getSize().x);
        float mouse_y = event.mouseButton.y * (1080.f / window_.getSize().y);

        for (Tower& tower : game_.value().getTowers()) {
          if (tower.getHitboxRadius() >=
              EuclideanDistance(tower.getPosition(),
                                types::Position(mouse_x, mouse_y))) {
            upgrading_tower_ = &tower;
            LaunchUpgradeGui();
            break;
          }
        }
      }

      // handle click events when buying towers
      if (state_ == types::kGame && buying_tower_ &&
          event.type == sf::Event::MouseButtonPressed) {
        float mouse_x = event.mouseButton.x * (1920.f / window_.getSize().x);
        float mouse_y = event.mouseButton.y * (1080.f / window_.getSize().y);
        if (mouse_x >= 1520) {
          // gui was clicked while buying tower
          buying_tower_ = {};
        } else {
          // position on the map was clicked while buying a tower
          if (!game_.value().CheckTowerPlacementCollision(buying_tower_.value())) {
            game_.value().AddTower(buying_tower_.value());
            buying_tower_ = {};
          } else { /*
               sf::Sound buubuu;
               buubuu.LoadFromFile("../Assets/Sounds/buubuu.wmv");
               buubuu.setVolume(volume_);
               buubuu.play(); */
          }
        }
      }
    }

    window_.clear();

    //Handle game logic and rendering of bottom-layer
    //things based on which state the application is in
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

    // draw things that need to be drawn on top of the gui
    switch (state_) {
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

    music.setVolume(music_volume_);

    window_.display();

  }  // main loop end

  for (auto string_texture_pair : textures_) {  // deletes textures
    delete (string_texture_pair.second);
  }
  return 0;
}

void Application::LoadTextures() {
  sf::Texture* main_menu_bg_texture = new sf::Texture();
  main_menu_bg_texture->loadFromFile("../assets/title_screen.jpg");
  textures_["main_menu_bg"] = main_menu_bg_texture;

  sf::Texture* map_select_bg = new sf::Texture();
  map_select_bg->loadFromFile("../assets/map_select_bg.jpg");
  textures_["map_select_bg"] = map_select_bg;

  sf::Texture* shop_bg = new sf::Texture();
  shop_bg->loadFromFile("../assets/shop_background.jpg");
  textures_["shop_bg"] = shop_bg;

  sf::Texture* map1 = new sf::Texture();
  map1->loadFromFile("../assets/map1.jpg");
  textures_["map1"] = map1;

  sf::Texture* map2 = new sf::Texture();
  map2->loadFromFile("../assets/map2.jpg");
  textures_["map2"] = map2;

  sf::Texture* upgrade_1 = new sf::Texture();
  upgrade_1->loadFromFile("../assets/upgrade_1.jpg");
  textures_["upgrade_1"] = upgrade_1;

  sf::Texture* upgrade_2 = new sf::Texture();
  upgrade_2->loadFromFile("../assets/upgrade_2.jpg");
  textures_["upgrade_2"] = upgrade_2;

  sf::Texture* upgrade_3 = new sf::Texture();
  upgrade_3->loadFromFile("../assets/upgrade_3.jpg");
  textures_["upgrade_3"] = upgrade_3;

  sf::Texture* upgrade_4 = new sf::Texture();
  upgrade_4->loadFromFile("../assets/upgrade_4.jpg");
  textures_["upgrade_4"] = upgrade_4;

  sf::Texture* pause_icon = new sf::Texture();
  pause_icon->loadFromFile("../assets/pause_icon.png");
  textures_["pause_icon"] = pause_icon;

  sf::Texture* arrow_left = new sf::Texture();
  arrow_left->loadFromFile("../assets/arrow_left.png");
  textures_["arrow_left"] = arrow_left;

  sf::Texture* arrow_right = new sf::Texture();
  arrow_right->loadFromFile("../assets/arrow_right.png");
  textures_["arrow_right"] = arrow_right;

  sf::Texture* red_rectangle = new sf::Texture();
  red_rectangle->loadFromFile("../assets/red_rectangle.jpg");
  textures_["red_rectangle"] = red_rectangle;

  sf::Texture* yellow_rectangle = new sf::Texture();
  yellow_rectangle->loadFromFile("../assets/yellow_rectangle.jpg");
  textures_["yellow_rectangle"] = yellow_rectangle;

  sf::Texture* white_rectangle = new sf::Texture();
  white_rectangle->loadFromFile("../assets/white_rectangle.jpg");
  textures_["white_rectangle"] = white_rectangle;

  sf::Texture* basic_tower = new sf::Texture();
  basic_tower->loadFromFile("../assets/towers/basic_tower.png");
  textures_["basic_tower"] = basic_tower;

  sf::Texture* bomb_tower = new sf::Texture();
  bomb_tower->loadFromFile("../assets/towers/bomb_tower.png");
  textures_["bomb_tower"] = bomb_tower;

  sf::Texture* slowing_tower = new sf::Texture();
  slowing_tower->loadFromFile("../assets/towers/slowing_tower.png");
  textures_["slowing_tower"] = slowing_tower;

  sf::Texture* melting_tower = new sf::Texture();
  melting_tower->loadFromFile("../assets/towers/melting_tower.png");
  textures_["melting_tower"] = melting_tower;

  sf::Texture* thorn_eruptor = new sf::Texture();
  thorn_eruptor->loadFromFile("../assets/towers/thorn_eruptor.png");
  textures_["thorn_eruptor"] = thorn_eruptor;

  sf::Texture* sniper_tower = new sf::Texture();
  sniper_tower->loadFromFile("../assets/towers/sniper_tower.png");
  textures_["sniper_tower"] = sniper_tower;

  sf::Texture* basic_projectile = new sf::Texture();
  basic_projectile->loadFromFile("../assets/projectiles/basic_projectile.png");
  textures_["basic_projectile"] = basic_projectile;

  sf::Texture* bomb_tower_projectile = new sf::Texture();
  bomb_tower_projectile->loadFromFile("../assets/projectiles/bomb_tower_projectile.png");
  textures_["bomb_tower_projectile"] = bomb_tower_projectile;

  sf::Texture* thorn_eruptor_projectile = new sf::Texture();
  thorn_eruptor_projectile->loadFromFile("../assets/projectiles/thorn_eruptor_projectile.png");
  textures_["thorn_eruptor_projectile"] = thorn_eruptor_projectile;

  sf::Texture* bomb_tower_explosion = new sf::Texture();
  bomb_tower_explosion->loadFromFile("../assets/projectiles/bomb_tower_explosion.png");
  textures_["bomb_tower_explosion"] = bomb_tower_explosion;
  
  sf::Texture* cockroach = new sf::Texture();
  cockroach->loadFromFile("../assets/enemies/cockroach.png");
  textures_["cockroach"] = cockroach;

  sf::Texture* fly = new sf::Texture();
  fly->loadFromFile("../assets/enemies/fly.png");
  textures_["fly"] = fly;

  sf::Texture* beetle = new sf::Texture();
  beetle->loadFromFile("../assets/enemies/beetle.png");
  textures_["beetle"] = beetle;

  sf::Texture* dragonfly = new sf::Texture();
  dragonfly->loadFromFile("../assets/enemies/dragonfly.png");
  textures_["dragonfly"] = dragonfly;
}

void Application::LaunchMainMenuGui() {
  if (state_ == types::kMainMenu) {
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

  button_start->setPosition("50%", "50%");
  button_start->setOrigin(0.5f, 0.5f);
  button_start->setSize("20%", "8%");
  button_options->setPosition("50%", "60%");
  button_options->setOrigin(0.5f, 0.5f);
  button_options->setSize("20%", "8%");
  button_quit->setPosition("50%", "70%");
  button_quit->setOrigin(0.5f, 0.5f);
  button_quit->setSize("20%", "8%");

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
  button_start->onPress([&] { LaunchMapSelectGui(); });
  button_options->onPress([&] { LaunchOptionsGui(); });
  button_quit->onPress([&] { window_.close(); });
}

void Application::LaunchMapSelectGui() {
  if (state_ == types::kMapSelect) {
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

  button_map1->setPosition("36%", "50%");
  button_map1->setOrigin(0.5f, 0.5f);
  button_map1->setSize("24%", "35%");
  button_map2->setPosition("64%", "50%");
  button_map2->setOrigin(0.5f, 0.5f);
  button_map2->setSize("24%", "35%");
  button_exit->setPosition("10%", "15%");
  button_exit->setOrigin(0.5f, 0.5f);
  button_exit->setSize("16%", "8%");

  button_exit->setText("Exit");

  StyleButtonBrown(button_map1);
  StyleButtonBrown(button_map2);
  StyleButtonBrown(button_exit);

  button_map1->getRenderer()->setTexture(*textures_["map1"]);
  button_map2->getRenderer()->setTexture(*textures_["map2"]);
}

void Application::HandleMapSelect() {
  HandleMapSelectGui();

  sf::Sprite map_select_bg;
  map_select_bg.setTexture(*textures_["map_select_bg"], true);
  ScaleSprite(map_select_bg);
  window_.draw(map_select_bg);

  sf::Text select_text("Select Map", font_, 60);
  select_text.setFillColor(sf::Color(139, 69, 19, 255));
  select_text.setOrigin(select_text.getLocalBounds().width / 2,
                        select_text.getLocalBounds().height / 2);
  select_text.setPosition(sf::Vector2f(window_x_ / 2.0f, window_y_ / 5.0f));
  window_.draw(select_text);
}

void Application::HandleMapSelectGui() {
  tgui::Button::Ptr button_map1 = gui_.get<tgui::Button>("button_map1");
  tgui::Button::Ptr button_map2 = gui_.get<tgui::Button>("button_map2");
  tgui::Button::Ptr button_exit = gui_.get<tgui::Button>("button_exit");
  button_map1->onPress([&] { LaunchGame("map1"); });
  button_map2->onPress([&] { LaunchGame("map2"); });
  button_exit->onPress([&] { LaunchMainMenuGui(); });
}

void Application::LaunchGame(const std::string& map_name) {
  if (state_ == types::kGame) {
    return;
  }
  LaunchGameGui();

  sf::Texture* map_texture = new sf::Texture();
  map_texture->loadFromFile("../assets/" + map_name + ".jpg");
  textures_["map"] = map_texture;

  Map* map = Map::LoadFromFile("../assets/maps/" + map_name + ".json");

  game_ = Game(map, "../assets/rounds.json", textures_);
  game_.value().setAutoStart(auto_start_);  
}

void Application::LaunchGameGui() {
  if (state_ == types::kGame) {
    return;
  }
  state_ = types::kGame;
  gui_.removeAllWidgets();

  tgui::Button::Ptr button_tower_ba = tgui::Button::create();  // basic tower
  tgui::Button::Ptr button_pause = tgui::Button::create();
  tgui::Button::Ptr button_start_wave = tgui::Button::create();

  button_tower_ba->getRenderer()->setBorderColorFocused(
      sf::Color(255, 255, 0, 255));
  button_tower_ba->getRenderer()->setBorderColorDownFocused(
      sf::Color(255, 255, 0, 255));
  button_tower_ba->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));
  button_tower_ba->getRenderer()->setBackgroundColorDisabled(
      sf::Color(165, 100, 35, 255));
  button_pause->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));
  button_pause->getRenderer()->setBackgroundColorDisabled(
      sf::Color(165, 100, 35, 255));
  button_pause->getRenderer()->setTexture(*textures_["pause_icon"]);
  button_start_wave->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));
  button_start_wave->getRenderer()->setBackgroundColorDisabled(
      sf::Color(165, 100, 35, 255));
  StyleButtonBrown(button_tower_ba);
  StyleButtonBrown(button_pause);
  StyleButtonBrown(button_start_wave);

  tgui::Button::Ptr button_tower_bo =
      tgui::Button::copy(button_tower_ba);  // bomb tower
  tgui::Button::Ptr button_tower_fr =
      tgui::Button::copy(button_tower_ba);  // slowing tower
  tgui::Button::Ptr button_tower_th =
      tgui::Button::copy(button_tower_ba);  // thorn eruptor
  tgui::Button::Ptr button_tower_sn =
      tgui::Button::copy(button_tower_ba);  // sniper
  tgui::Button::Ptr button_tower_ci =
      tgui::Button::copy(button_tower_ba);  // melting tower

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
  map_sprite.setTexture(*textures_["map"], true);
  ScaleSprite(map_sprite);
  window_.draw(map_sprite);

  game_.value().Update();

  DrawGameElements();

  if (buying_tower_) {  // if a tower is currently being bought
    float mouse_x = (sf::Mouse::getPosition().x - window_.getPosition().x) *
                    (float)window_x_ / window_.getSize().x;
    float mouse_y = (sf::Mouse::getPosition().y - window_.getPosition().y) *
                    (float)window_y_ / window_.getSize().y;

    if (mouse_x < 1520.f * window_x_ / 1920 && mouse_x > 0 && mouse_y < window_y_ && mouse_y > 0) {
      // draws range circle of buying_tower_
      sf::CircleShape range_circle =
          sf::CircleShape(buying_tower_.value().getRange(), 40);
      range_circle.setOrigin(buying_tower_.value().getRange(),
                             buying_tower_.value().getRange());
      ScaleSprite(range_circle);
      range_circle.setPosition(static_cast<float>(mouse_x),
                               static_cast<float>(mouse_y));
      if (!game_.value().CheckTowerPlacementCollision(buying_tower_.value())) {
        range_circle.setFillColor(sf::Color(100, 100, 100, 120));
      } else {
        range_circle.setFillColor(sf::Color(150,0,0,120));
      }
      window_.draw(range_circle);

      buying_tower_.value().setPosition(types::Position(
          mouse_x * 1920.f / window_x_, mouse_y * 1080.f / window_y_));

      sf::Sprite buying_tower_sprite;
      buying_tower_sprite.setTexture(*buying_tower_.value().getTexture());
      buying_tower_sprite.setPosition(
          buying_tower_.value().getPosition().x * window_x_ / 1920.f,
          buying_tower_.value().getPosition().y * window_y_ / 1080.f);
      buying_tower_sprite.setOrigin(
          buying_tower_sprite.getLocalBounds().width / 2,
          buying_tower_sprite.getLocalBounds().height / 2);
      ScaleSprite(buying_tower_sprite);
      buying_tower_sprite.setRotation(buying_tower_.value().getRotation()*180.f/PI+90);
      buying_tower_sprite.scale(
          buying_tower_.value().getHitboxRadius()*1.33f * 2 / 1000,
          buying_tower_.value().getHitboxRadius()*1.33f * 2 / 1000);
      window_.draw(buying_tower_sprite);
    }
  }

  sf::Sprite shop_bg;
  shop_bg.setTexture(*textures_["shop_bg"], true);
  shop_bg.setPosition(sf::Vector2f(window_x_ * 1520.f / 1920.f, 0.f));
  ScaleSprite(shop_bg);
  window_.draw(shop_bg);

  HandleGameGui();

  if (game_.value().IsGameWon() || game_.value().IsOutOfLives()) {
    static sf::Clock end_timer;
    sf::Text end_text("GAME OVER", font_, 80);
    end_text.setFillColor(sf::Color(180,0,0,255));
    if (game_.value().IsGameWon()) {
      end_text.setString("YOU WIN");
      end_text.setFillColor(sf::Color(224,224,255));
    }
    end_text.setOrigin(end_text.getLocalBounds().width / 2,
                          end_text.getLocalBounds().height / 2);
    end_text.setPosition(sf::Vector2f(window_x_ / 2.0f, window_y_ / 2.0f));
    end_text.setOutlineThickness(2);
    window_.draw(end_text);
    if (end_timer.getElapsedTime().asMilliseconds() > 5000) {
      CloseGame();
    }
  }
}

void Application::HandleGameGui() {
  tgui::Button::Ptr button_tower_ba = gui_.get<tgui::Button>("button_tower_ba");
  tgui::Button::Ptr button_tower_bo = gui_.get<tgui::Button>("button_tower_bo");
  tgui::Button::Ptr button_tower_fr = gui_.get<tgui::Button>("button_tower_fr");
  tgui::Button::Ptr button_tower_th = gui_.get<tgui::Button>("button_tower_th");
  tgui::Button::Ptr button_tower_sn = gui_.get<tgui::Button>("button_tower_sn");
  tgui::Button::Ptr button_tower_ci = gui_.get<tgui::Button>("button_tower_ci");
  tgui::Button::Ptr button_pause = gui_.get<tgui::Button>("button_pause");
  tgui::Button::Ptr button_start_wave =
      gui_.get<tgui::Button>("button_start_wave");

  static bool do_once = true;  // tgui buttons have a bad habit of triggering
                               // multiple times, this fixes that

  button_pause->onPress([&] { LaunchPauseGui(); });
  button_start_wave->onPress([&] {
    if (!game_.value().IsRoundInProgress()) {
      game_.value().StartRound(game_.value().getCurrentRoundIndex()+1);
    }
  });

  button_tower_ba->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "basic_tower", textures_["basic_tower"], textures_["basic_projectile"]);
    do_once = false;
  });

  button_tower_bo->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "bomb_tower", textures_["bomb_tower"], textures_["bomb_tower_projectile"], textures_["bomb_tower_explosion"]);
    do_once = false;
  });

  button_tower_fr->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "slowing_tower", textures_["slowing_tower"], nullptr);
    do_once = false;
  });

  button_tower_th->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "thorn_eruptor", textures_["thorn_eruptor"],
          textures_["thorn_eruptor_projectile"]);
    do_once = false;
  });

  button_tower_sn->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "sniper_tower", textures_["sniper_tower"], nullptr);
    do_once = false;
  });

  button_tower_ci->onPress([&] {
    if (do_once)
      buying_tower_ = game_.value().StartBuyingTower(
          "melting_tower", textures_["melting_tower"], nullptr);
    do_once = false;
  });

  do_once = true;

   if (game_.value().IsRoundInProgress()) {
      button_start_wave->setEnabled(false); 
  } else {
      button_start_wave->setEnabled(true);
  }

  static std::string title_string = "";
  static std::string desc_string = "";

  button_tower_ba->onMouseEnter([&] {
    if (title_string == "") title_string = "Seed Shooter";
  });
  button_tower_bo->onMouseEnter([&] {
    if (title_string == "") title_string = "Coconut Cannon";
  });
  button_tower_fr->onMouseEnter([&] {
    if (title_string == "") title_string = "Frigid Stump";
  });
  button_tower_th->onMouseEnter([&] {
    if (title_string == "") title_string = "Thorn Eruptor";
  });
  button_tower_sn->onMouseEnter([&] {
    if (title_string == "") title_string = "Sniper";
  });
  button_tower_ci->onMouseEnter([&] {
    if (title_string == "") title_string = "Cinder Stump";
  });

  button_tower_ba->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "A Basic tower that shoots\nseeds at enemies within it's\nrange. "
          "Medium damage\nand range.\nTier 4 variant gains\ntriple shot.";
  });
  button_tower_bo->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "Shoots massive coconuts\nthat hurl through enemies.\nEffective "
          "against\narmored enemies.\nTier 4 upgrade doubles\nthe "
          "size of the\ncoconut.";
  });
  button_tower_fr->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "The magic crystal atop this\nstump slows down foes in\nan area "
          "around the tower.\nUpgrading the tower\nfurther increases\nslowing "
          "amount.";
  });
  button_tower_th->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "Shoots a barrage of thorns\nat all enemies within it's\nrange. "
          "Faster fire rate\nthe more enemies there\nare in the tower's range.\nUpgrading improves\ndamage "
          "and range.\nTier 4 variant shoots\ntwice each time.";
  });
  button_tower_sn->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "Slow-shooting high-damage\ntower with extreme range.\nGreat against "
          "strong foes.\nDeals extra damage to\narmored enemies.";
  });
  button_tower_ci->onMouseEnter([&] {
    if (desc_string == "")
      desc_string =
          "The magic crystal atop this\nstump emits blazing heat\nwhich "
          "damages all enemies\nin the area around it.\nLow range.\nTier 4 "
          "variant melts\nthrough armor.";
  });

  button_tower_ba->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });
  button_tower_bo->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });
  button_tower_fr->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });
  button_tower_th->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });
  button_tower_sn->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });
  button_tower_ci->onMouseLeave([&] {
    title_string = "";
    desc_string = "";
  });

  sf::Text tower_title(title_string, font_, 26);
  tower_title.setOrigin(tower_title.getGlobalBounds().width / 2, 0);
  tower_title.setPosition(sf::Vector2f(window_x_ / (1920.f / 1720.f),
                                       window_y_ / (1080.f / 460.f)));
  tower_title.setFillColor(sf::Color(255, 255, 255, 255));
  tower_title.setOutlineColor(sf::Color(50, 50, 50, 255));
  tower_title.setOutlineThickness(1);
  window_.draw(tower_title);

  sf::Text tower_desc(desc_string, font_, 20);
  tower_desc.setPosition(sf::Vector2f(window_x_ / (1920.f / 1540.f),
                                      window_y_ / (1080.f / 520.f)));
  tower_desc.setFillColor(sf::Color(255, 255, 255, 255));
  tower_desc.setOutlineColor(sf::Color(50, 50, 50, 255));
  tower_desc.setOutlineThickness(1);
  window_.draw(tower_desc);
}

void Application::CloseGame() {
  // TODO: make sure that memory management is fine
  if (state_ == types::kMainMenu) {
    return;
  }
  delete(game_.value().getMap());
  textures_.erase("map");
  game_ = {};
  LaunchMainMenuGui();
}

void Application::LaunchOptionsGui() {
  if (state_ == types::kOptions) {
    return;
  }
  gui_.removeAllWidgets();
  state_ = types::kOptions;

  tgui::Button::Ptr button_return = tgui::Button::create();
  tgui::Button::Ptr button_background =
      tgui::Button::create();  // used as a background
  tgui::Slider::Ptr slider_volume = tgui::Slider::create();
  tgui::Slider::Ptr slider_music_volume = tgui::Slider::create();
  tgui::ToggleButton::Ptr button_auto_start = tgui::ToggleButton::create();
  tgui::Button::Ptr music_text =
      tgui::Button::create();  // using an invisible button for text ensures
                               // it's in the right position

  gui_.add(button_background, "button_background");
  gui_.add(button_return, "button_return");
  gui_.add(button_auto_start, "button_auto_start");
  gui_.add(slider_volume, "slider_volume");
  gui_.add(slider_music_volume, "slider_music_volume");
  gui_.add(music_text);

  music_text->setEnabled(false);
  music_text->getRenderer()->setBackgroundColorDisabled(sf::Color(0, 0, 0, 0));
  music_text->getRenderer()->setBorderColorDisabled(sf::Color(0, 0, 0, 0));
  music_text->getRenderer()->setTextColorDisabled(sf::Color(129, 59, 16, 255));
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
  slider_renderer->setTrackColor(sf::Color(195, 123, 53, 255));
  slider_renderer->setTrackColorHover(sf::Color(195, 123, 53, 255));
  slider_renderer->setThumbColor(sf::Color(139, 69, 19, 255));
  slider_renderer->setThumbColorHover(sf::Color(139, 69, 19, 255));

  auto button_renderer = button_auto_start->getRenderer();
  button_renderer->setBackgroundColor(sf::Color(195, 123, 53, 255));
  button_renderer->setBackgroundColorHover(sf::Color(195, 123, 53, 255));
  button_renderer->setBackgroundColorDown(sf::Color(0, 100, 0, 255));
  button_renderer->setBorderColor(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorHover(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorDown(sf::Color(0, 60, 0, 255));
  button_renderer->setBorderColorFocused(sf::Color(139, 69, 19, 255));
  button_renderer->setBackgroundColorDownHover(sf::Color(0, 100, 0, 255));
  button_renderer->setRoundedBorderRadius(8.0f);
  button_renderer->setBorders(5);
  button_auto_start->setTextSize(15);

  button_background->setEnabled(false);
  button_background->setOrigin(0.5f, 0.5f);
  button_background->getRenderer()->setRoundedBorderRadius(8.0f);
  button_background->getRenderer()->setBorders(5);
  button_background->getRenderer()->setBackgroundColorDisabled(
      sf::Color(205, 133, 63, 255));
  button_background->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));

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

   if (auto_start_) {
      button_auto_start->setDown(true);
  }
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
  tgui::ToggleButton::Ptr button_auto_start =
      gui_.get<tgui::ToggleButton>("button_auto_start");
  tgui::Slider::Ptr slider_volume = gui_.get<tgui::Slider>("slider_volume");
  tgui::Slider::Ptr slider_music_volume =
      gui_.get<tgui::Slider>("slider_music_volume");

  button_return->onPress(&Application::LaunchMainMenuGui, this);
  volume_ = slider_volume->getValue();
  music_volume_ = slider_music_volume->getValue();
  if (button_auto_start->isDown()) {
    auto_start_ = true;
  } else {
    auto_start_ = false;
  }
}

void Application::LaunchPauseGui() {
  if (state_ == types::kPause) {
    return;
  }
  state_ = types::kPause;

  for (auto widget : gui_.getWidgets()) {  // disables the gui of the game
    widget->setEnabled(false);
  }

  tgui::Button::Ptr button_return = tgui::Button::create();
  tgui::Button::Ptr button_background =
      tgui::Button::create();  // used as a background
  tgui::Button::Ptr button_off_menu =
      tgui::Button::create();  // massive invisible button outside menu
  tgui::Slider::Ptr slider_volume = tgui::Slider::create();
  tgui::Slider::Ptr slider_music_volume = tgui::Slider::create();
  tgui::ToggleButton::Ptr button_auto_start = tgui::ToggleButton::create();
  tgui::Button::Ptr music_text =
      tgui::Button::create();  // using an invisible button for text ensures
                               // it's in the right position

  gui_.add(button_background, "button_background");
  gui_.add(button_off_menu, "button_off_menu");
  gui_.add(button_return, "button_return");
  gui_.add(button_auto_start, "button_auto_start");
  gui_.add(slider_volume, "slider_volume");
  gui_.add(slider_music_volume, "slider_music_volume");
  gui_.add(music_text);

  music_text->setEnabled(false);
  music_text->getRenderer()->setBackgroundColorDisabled(sf::Color(0, 0, 0, 0));
  music_text->getRenderer()->setBorderColorDisabled(sf::Color(0, 0, 0, 0));
  music_text->getRenderer()->setTextColorDisabled(sf::Color(129, 59, 16, 255));
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
  slider_renderer->setTrackColor(sf::Color(195, 123, 53, 255));
  slider_renderer->setTrackColorHover(sf::Color(195, 123, 53, 255));
  slider_renderer->setThumbColor(sf::Color(139, 69, 19, 255));
  slider_renderer->setThumbColorHover(sf::Color(139, 69, 19, 255));

  auto button_renderer = button_auto_start->getRenderer();
  button_renderer->setBackgroundColor(sf::Color(195, 123, 53, 255));
  button_renderer->setBackgroundColorHover(sf::Color(195, 123, 53, 255));
  button_renderer->setBackgroundColorDown(sf::Color(0, 100, 0, 255));
  button_renderer->setBorderColor(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorHover(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorDown(sf::Color(0, 60, 0, 255));
  button_renderer->setBorderColorFocused(sf::Color(139, 69, 19, 255));
  button_renderer->setBackgroundColorDownHover(sf::Color(0, 100, 0, 255));
  button_renderer->setRoundedBorderRadius(8.0f);
  button_renderer->setBorders(5);
  button_auto_start->setTextSize(15);

  button_off_menu->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBackgroundColorDown(sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBackgroundColorHover(
      sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBorders(0);

  button_background->setEnabled(false);
  button_background->setOrigin(0.5f, 0.5f);
  button_background->getRenderer()->setRoundedBorderRadius(8.0f);
  button_background->getRenderer()->setBorders(5);

  button_return->setPosition("65%", "25%");
  button_main_menu->setPosition("25%", "25%");
  button_off_menu->setPosition(0, 0);
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

  button_background->getRenderer()->setBackgroundColorDisabled(
      sf::Color(205, 133, 63, 255));
  button_background->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));

  button_auto_start->setText("Auto Start\nRounds");
  button_return->setText("Continue");
  button_main_menu->setText("Quit");

  slider_volume->setMinimum(0.f);
  slider_volume->setMaximum(100.f);
  slider_volume->setValue(volume_);
  slider_music_volume->setMinimum(0.f);
  slider_music_volume->setMaximum(100.f);
  slider_music_volume->setValue(music_volume_);

  if (auto_start_) {
      button_auto_start->setDown(true);
  }
}

void Application::HandlePause() {
  HandlePauseGui();

  sf::Sprite map_sprite;
  map_sprite.setTexture(*textures_["map"],
                        true);
  ScaleSprite(map_sprite);
  window_.draw(map_sprite);

  DrawGameElements();

  sf::Sprite shop_bg;
  shop_bg.setTexture(*textures_["shop_bg"], true);
  shop_bg.setPosition(sf::Vector2f(window_x_ * 1520.f / 1920.f, 0.f));
  ScaleSprite(shop_bg);
  window_.draw(shop_bg);
}

void Application::HandlePauseGui() {
  tgui::Button::Ptr button_return = gui_.get<tgui::Button>("button_return");
  tgui::Button::Ptr button_main_menu =
      gui_.get<tgui::Button>("button_main_menu");
  tgui::Button::Ptr button_off_menu = gui_.get<tgui::Button>("button_off_menu");
  tgui::ToggleButton::Ptr button_auto_start =
      gui_.get<tgui::ToggleButton>("button_auto_start");
  tgui::Slider::Ptr slider_volume = gui_.get<tgui::Slider>("slider_volume");
  tgui::Slider::Ptr slider_music_volume =
      gui_.get<tgui::Slider>("slider_music_volume");

  button_main_menu->onPress(&Application::CloseGame, this);
  button_return->onPress([&] {LaunchGameGui(); game_.value().Unpause();} );
  button_off_menu->onPress([&] {LaunchGameGui(); game_.value().Unpause();} );
  volume_ = slider_volume->getValue();
  music_volume_ = slider_music_volume->getValue();
  if (button_auto_start->isDown()) {
    game_.value().setAutoStart(true);
    auto_start_ = true;
  } else {
    game_.value().setAutoStart(false);
    auto_start_ = false;
  }
}

void Application::LaunchUpgradeGui() {
  if (state_ == types::kUpgrade) {
    return;
  }
  state_ = types::kUpgrade;

  tgui::Button::Ptr button_off_menu =
      tgui::Button::create();  // massive invisible button outside menu
  button_off_menu->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBackgroundColorDown(sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBackgroundColorHover(
      sf::Color(0, 0, 0, 0));
  button_off_menu->getRenderer()->setBorders(0);
  button_off_menu->setSize("100%", "100%");
  button_off_menu->setPosition(0, 0);
  gui_.add(button_off_menu, "button_off_menu");

  tgui::Button::Ptr button_background = tgui::Button::create();
  tgui::Button::Ptr button_target_left = tgui::Button::create();
  tgui::Button::Ptr button_target_right = tgui::Button::create();
  tgui::Button::Ptr button_targeting_text =
      tgui::Button::create();  // box that displays tower's current targeting
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
  button_background->getRenderer()->setBackgroundColorDisabled(
      sf::Color(205, 133, 63, 255));
  button_background->getRenderer()->setBorderColorDisabled(
      sf::Color(139, 69, 19, 255));

  StyleButtonBrown(button_target_left);
  StyleButtonBrown(button_target_right);
  StyleButtonBrown(button_targeting_text);
  button_target_left->getRenderer()->setRoundedBorderRadius(0);
  button_target_left->getRenderer()->setTexture(*textures_["arrow_left"]);
  button_target_right->getRenderer()->setRoundedBorderRadius(0);
  button_target_right->getRenderer()->setTexture(*textures_["arrow_right"]);
  button_targeting_text->getRenderer()->setRoundedBorderRadius(0);
  button_targeting_text->getRenderer()->setBackgroundColorDown(
      sf::Color(205, 133, 63, 255));
  button_targeting_text->getRenderer()->setTextColor(
      sf::Color(20, 20, 20, 255));
  button_targeting_text->setTextSize(20);

  button_upgrade->getRenderer()->setBorders(3);
  button_upgrade->getRenderer()->setBorderColor(sf::Color(10, 63, 10, 255));
  button_upgrade->getRenderer()->setBorderColorDown(sf::Color(10, 63, 10, 255));
  button_upgrade->getRenderer()->setBorderColorFocused(
      sf::Color(10, 63, 10, 255));
  button_upgrade->getRenderer()->setTextColor(sf::Color(10, 10, 10, 255));
  button_upgrade->setTextSize(22);

  button_sell->getRenderer()->setBorders(3);
  button_sell->getRenderer()->setBorderColor(sf::Color(50, 0, 0, 255));
  button_sell->getRenderer()->setBorderColorDown(sf::Color(50, 0, 0, 255));
  button_sell->getRenderer()->setBorderColorFocused(sf::Color(50, 0, 0, 255));
  button_sell->getRenderer()->setBackgroundColor(sf::Color(180, 0, 0, 255));
  button_sell->getRenderer()->setBackgroundColorDown(sf::Color(140, 0, 0, 255));
  button_sell->getRenderer()->setBackgroundColorHover(
      sf::Color(180, 0, 0, 255));
  button_sell->getRenderer()->setBackgroundColorFocused(
      sf::Color(180, 0, 0, 255));
  button_sell->getRenderer()->setTextColor(sf::Color(0, 0, 0, 255));
  button_sell->getRenderer()->setTextColorDown(sf::Color(0, 0, 0, 255));
  button_sell->setTextSize(25);

  button_background->setPosition("80.6%", "42%");
  button_background->setSize("18%", "43%");

  button_target_left->setPosition(bindLeft(button_background) + "2%",
                                  bindTop(button_background) + "2%");
  button_target_right->setPosition(bindLeft(button_background) + "13%",
                                   bindTop(button_background) + "2%");
  button_targeting_text->setPosition(bindLeft(button_background) + "5%",
                                     bindTop(button_background) + "2%");
  button_upgrade->setPosition(bindLeft(button_background) + "1%",
                              bindTop(button_background) + "16%");
  button_sell->setPosition(bindLeft(button_background) + "1%",
                           bindTop(button_background) + "32%");

  button_target_left->setSize("3.5%", "6%");
  button_target_right->setSize("3.5%", "6%");
  button_targeting_text->setSize("8.2%", "6%");
  button_upgrade->setSize("16%", "8%");
  button_sell->setSize("16%", "8%");
}

void Application::HandleUpgrade() {

  HandleUpgradeGui();

  sf::Sprite map_sprite;
  map_sprite.setTexture(*textures_["map"], true);
  ScaleSprite(map_sprite);
  window_.draw(map_sprite);

  game_.value().Update();

  // draw range circle of upgrading_tower_
  sf::CircleShape range_circle(upgrading_tower_->getRange(), 40);
  range_circle.setOrigin(upgrading_tower_->getRange(),
                         upgrading_tower_->getRange());
  ScaleSprite(range_circle);
  range_circle.setPosition(upgrading_tower_->getPosition().x*window_x_/1920.f, upgrading_tower_->getPosition().y*window_y_/1080.f);
  range_circle.setFillColor(sf::Color(100, 100, 100, 120));
  window_.draw(range_circle);
  DrawGameElements();

  sf::Sprite shop_bg;
  shop_bg.setTexture(*textures_["shop_bg"], true);
  shop_bg.setPosition(sf::Vector2f(window_x_ * 1520.f / 1920.f, 0.f));
  ScaleSprite(shop_bg);
  window_.draw(shop_bg);

}

void Application::HandleUpgradeGui() {
  tgui::Button::Ptr button_off_menu = gui_.get<tgui::Button>("button_off_menu");
  tgui::Button::Ptr button_target_left =
      gui_.get<tgui::Button>("button_target_left");
  tgui::Button::Ptr button_target_right =
      gui_.get<tgui::Button>("button_target_right");
  tgui::Button::Ptr button_targeting_text =
      gui_.get<tgui::Button>("button_targeting_text");
  tgui::Button::Ptr button_upgrade = gui_.get<tgui::Button>("button_upgrade");
  tgui::Button::Ptr button_sell = gui_.get<tgui::Button>("button_sell");

  static bool do_once = false;  // tgui buttons have a bad habit of triggering
                                // multiple times, this fixes that



  button_off_menu->onPress([&] {
    LaunchGameGui();
    upgrading_tower_ = nullptr;
  });

  button_target_left->onPress([&] {
    if (do_once) TargetingSwitchLeft();
    do_once = false;
  });

  button_target_right->onPress([&] {
    if (do_once) TargetingSwitchRight();
    do_once = false;
  });

  button_upgrade->onPress([&] {
    if (do_once) game_.value().UpgradeTower(upgrading_tower_);
    do_once = false;
  });
  
  switch (upgrading_tower_->getTargeting()) {  // make text match tower's value
    case types::kFirst:
      button_targeting_text->setText("First");
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
    case types::kArea:
      button_targeting_text->setText("Area");
      break;
  }

  switch (upgrading_tower_->getLevel()) {  // make upgrade price and button
                                           // background match tower's level
    case 1:
      button_upgrade->getRenderer()->setTexture(*textures_["upgrade_1"]);
      button_upgrade->setText(
          "Upgrade\n(" + std::to_string(upgrading_tower_->getUpgradeCost()) + 
          ")");
      break;
    case 2:
      button_upgrade->getRenderer()->setTexture(*textures_["upgrade_2"]);
      button_upgrade->setText(
          "Upgrade\n(" + std::to_string(upgrading_tower_->getUpgradeCost()) +
          ")");
      break;
    case 3:
      button_upgrade->getRenderer()->setTexture(*textures_["upgrade_3"]);
      button_upgrade->setText(
          "Upgrade\n(" + std::to_string(upgrading_tower_->getUpgradeCost()) +
          ")");
      break;
    case 4:
      button_upgrade->getRenderer()->setTexture(*textures_["upgrade_4"]);
      button_upgrade->setText("Max level");
      break;
  }

  button_sell->setText("Sell\n(+" + std::to_string((upgrading_tower_->getMoneySpent()*3/4)) + ")");

  button_sell->onPress([&] {
    if (do_once) game_.value().SellTower(upgrading_tower_);
    do_once = false;
    upgrading_tower_ = nullptr;
    LaunchGameGui();
  });
  do_once = true;

  //if game should end
  if (game_.value().IsGameWon() || game_.value().IsOutOfLives()) {
    upgrading_tower_ = nullptr;
    LaunchGameGui();
  }
}

void Application::TargetingSwitchRight() {
  switch (upgrading_tower_->getTargeting()) {
    case types::kFirst:
      upgrading_tower_->setTargeting(types::kLast);
      break;
    case types::kLast:
      upgrading_tower_->setTargeting(types::kClose);
      break;
    case types::kClose:
      upgrading_tower_->setTargeting(types::kStrong);
      break;
    case types::kStrong:
      upgrading_tower_->setTargeting(types::kFirst);
      break;
    case types::kArea:
      break;
  }
}

void Application::TargetingSwitchLeft() {
  switch (upgrading_tower_->getTargeting()) {
    case types::kFirst:
      upgrading_tower_->setTargeting(types::kStrong);
      break;
    case types::kLast:
      upgrading_tower_->setTargeting(types::kFirst);
      break;
    case types::kClose:
      upgrading_tower_->setTargeting(types::kLast);
      break;
    case types::kStrong:
      upgrading_tower_->setTargeting(types::kClose);
      break;
    case types::kArea:
      break;
  }
}

void Application::DrawGameElements() {
  for (Tower& tower : game_.value().getTowers()) {
    sf::Sprite tower_sprite;
    tower_sprite.setTexture(*tower.getTexture());
    tower_sprite.setOrigin(tower_sprite.getLocalBounds().width / 2,
                           tower_sprite.getLocalBounds().height / 2);
    tower_sprite.setPosition(window_x_ / 1920.f * tower.getPosition().x,
                             window_y_ / 1080.f * tower.getPosition().y);
    ScaleSprite(tower_sprite);
    tower_sprite.scale(sf::Vector2f(tower.getHitboxRadius() *1.33f / 500.f,
                                    tower.getHitboxRadius() *1.33f / 500.f));
    tower_sprite.setRotation(tower.getRotation()*360/2/PI+90);
    window_.draw(tower_sprite);
  }

  for (Projectile& projectile : game_.value().getProjectiles()) {
    sf::Sprite projectile_sprite;
    projectile_sprite.setTexture(*projectile.getTexture());
    ScaleSprite(projectile_sprite);
    projectile_sprite.scale(sf::Vector2f(projectile.getHitboxRadius() / 100.f,
                                         projectile.getHitboxRadius() / 100.f));
    projectile_sprite.setOrigin(projectile_sprite.getLocalBounds().width / 2,
                           projectile_sprite.getLocalBounds().height / 2);
    projectile_sprite.setPosition(
         window_x_ / 1920.f * projectile.getPosition().x,
         window_y_ / 1080.f * projectile.getPosition().y);
    projectile_sprite.setRotation(projectile.getRotation()*360/2/PI+90);
    window_.draw(projectile_sprite);
  }

  for (Enemy& enemy : game_.value().getEnemies()) {
    sf::Sprite enemy_sprite;
    enemy_sprite.setTexture(*enemy.getTexture());
    ScaleSprite(enemy_sprite);
    enemy_sprite.scale(sf::Vector2f(enemy.getHitboxRadius() / 100.f,
                                    enemy.getHitboxRadius() / 100.f));
    enemy_sprite.setOrigin(enemy_sprite.getLocalBounds().width / 2,
                           enemy_sprite.getLocalBounds().height / 2);
    enemy_sprite.setPosition(window_x_ / 1920.0f * enemy.getPosition().x,
                             window_y_ / 1080.0f * enemy.getPosition().y);
    enemy_sprite.setRotation(enemy.getRotation()*360/2/PI+90);
    window_.draw(enemy_sprite);

    sf::Sprite health_bar_base;
    health_bar_base.setTexture(*textures_["white_rectangle"]);
    ScaleSprite(health_bar_base);
    health_bar_base.scale(0.6, 0.2);
    health_bar_base.setOrigin(health_bar_base.getLocalBounds().width / 2,
                           health_bar_base.getLocalBounds().height / 2);
    health_bar_base.setPosition(
        enemy_sprite.getPosition() -
        sf::Vector2f(0, 0.9f * 1080 / window_y_ * enemy.getHitboxRadius()));
    window_.draw(health_bar_base);

    sf::Sprite health_bar_;
    if (enemy.isArmored()) {
      health_bar_.setTexture(*textures_["yellow_rectangle"]);
    } else {
      health_bar_.setTexture(*textures_["red_rectangle"]);
    }
    ScaleSprite(health_bar_);
    health_bar_.scale(0.6, 0.2);
    health_bar_.setPosition(
        health_bar_base.getPosition()
        - types::Position(
        0.6*window_x_ / 1920.f*health_bar_base.getLocalBounds().width / 2, 
        0.2*window_y_ / 1080.f*health_bar_base.getLocalBounds().height / 2));
    health_bar_.scale((float)enemy.getHealth() / enemy.getMaxHealth(), 1);
    window_.draw(health_bar_);
  }
}

void Application::DrawShopElements() {
  sf::Text round_text("Round\n", font_, 22);  // round counter in the top right
  round_text.setOutlineColor(sf::Color(0, 0, 0, 255));
  round_text.setFillColor(sf::Color(255, 255, 255, 255));
  round_text.setOutlineThickness(2);
  round_text.setPosition(
      sf::Vector2f(window_x_ / (1920.f / 1500.f), window_y_ / 60.f));
  round_text.setOrigin(round_text.getLocalBounds().width, 0);
  window_.draw(round_text);

  sf::Text round_text2 = round_text;
  std::string round_string2 =
      std::to_string(game_.value().getCurrentRoundIndex()) + "/" +
      std::to_string(game_.value().getMaxRoundIndex());
  round_text2.setString(round_string2);
  round_text2.setOrigin(round_text.getGlobalBounds().width, 0);
  round_text2.setPosition(
      sf::Vector2f(window_x_ / (1920.f / 1500.f), window_y_ / 20.f));
  window_.draw(round_text2);

  sf::Text money_text(std::to_string(game_.value().getMoney()), font_, 25);
  money_text.setFillColor(sf::Color(0, 150, 0, 255));
  money_text.setOutlineColor(sf::Color(0, 100, 0, 255));
  money_text.setOutlineThickness(1);
  money_text.setPosition(
      sf::Vector2f(window_x_ / (1920.f / 1600.f), window_y_ / (1080.f / 20.f)));
  window_.draw(money_text);

  sf::Text lives_text(std::to_string(game_.value().getLives()), font_, 25);
  lives_text.setFillColor(sf::Color(150, 0, 0, 255));
  lives_text.setOutlineColor(sf::Color(100, 0, 0, 255));
  lives_text.setOutlineThickness(1);
  lives_text.setPosition(
      sf::Vector2f(window_x_ / (1920.f / 1600.f), window_y_ / (1080.f / 70.f)));
  window_.draw(lives_text);

  sf::Text price_text1(
      std::to_string(kCostBasicTower), font_,
      23);  // price of basic tower
  price_text1.setFillColor(sf::Color(0, 150, 0, 255));
  price_text1.setOutlineColor(sf::Color(0, 100, 0, 255));
  price_text1.setOutlineThickness(1);
  price_text1.setPosition(sf::Vector2f(window_x_ / (1920.f / 1611.f),
                                       window_y_ / (1080.f / 230.f)));
  price_text1.setOrigin(round_text.getGlobalBounds().width / 2, 0);
  window_.draw(price_text1);

  sf::Text price_text2 = price_text1;  //price of bomb tower
  price_text2.setString(std::to_string(kCostBombTower));
  price_text2.setPosition(sf::Vector2f(window_x_ / (1920.f / 1737.f),
                                       window_y_ / (1080.f / 230.f)));
  window_.draw(price_text2);

  sf::Text price_text3 = price_text1;  //price of slowing_tower
  price_text3.setString(std::to_string(kCostSlowingTower));
  price_text3.setPosition(sf::Vector2f(window_x_ / (1920.f / 1862.f),
                                       window_y_ / (1080.f / 230.f)));
  window_.draw(price_text3);

  sf::Text price_text4 = price_text1;
  price_text4.setString(std::to_string(kCostThornEruptor));
  price_text4.setPosition(sf::Vector2f(window_x_ / (1920.f / 1611.f),
                                       window_y_ / (1080.f / 381.f)));
  window_.draw(price_text4);

  sf::Text price_text5 = price_text1;
  price_text5.setString(std::to_string(kCostHighDamageTower));
  price_text5.setPosition(sf::Vector2f(window_x_ / (1920.f / 1737.f),
                                       window_y_ / (1080.f / 381.f)));
  window_.draw(price_text5);

  sf::Text price_text6 = price_text1;
  price_text5.setString(std::to_string(kCostMeltingTower));
  price_text5.setPosition(sf::Vector2f(window_x_ / (1920.f / 1862.f),
                                       window_y_ / (1080.f / 381.f)));
  window_.draw(price_text5);

  sf::Sprite basic_tower_icon;
  basic_tower_icon.setTexture(*textures_["basic_tower"]);
  ScaleSprite(basic_tower_icon);
  basic_tower_icon.scale(0.08f, 0.08f);
  basic_tower_icon.setPosition(1555.0f * window_x_ / 1920.0f,
                               155 * window_x_ / 1920.0f);
  window_.draw(basic_tower_icon);

  sf::Sprite bomb_tower_icon;
  bomb_tower_icon.setTexture(*textures_["bomb_tower"]);
  ScaleSprite(bomb_tower_icon);
  bomb_tower_icon.scale(0.08f, 0.08f);
  bomb_tower_icon.setPosition(1680.0f * window_x_ / 1920.0f,
                              150.0f * window_x_ / 1920.0f);
  window_.draw(bomb_tower_icon);

  sf::Sprite slowing_tower_icon;
  slowing_tower_icon.setTexture(*textures_["slowing_tower"]);
  ScaleSprite(slowing_tower_icon);
  slowing_tower_icon.scale(0.08f, 0.08f);
  slowing_tower_icon.setPosition(1805.0f * window_x_ / 1920.0f,
                                 150.0f * window_x_ / 1920.0f);
  window_.draw(slowing_tower_icon);

  sf::Sprite thorn_eruptor_icon;
  thorn_eruptor_icon.setTexture(*textures_["thorn_eruptor"]);
  ScaleSprite(thorn_eruptor_icon);
  thorn_eruptor_icon.scale(0.08f, 0.08f);
  thorn_eruptor_icon.setPosition(1555.0f * window_x_ / 1920.0f,
                                 300.0f * window_x_ / 1920.0f);
  window_.draw(thorn_eruptor_icon);

  sf::Sprite sniper_tower_icon;
  sniper_tower_icon.setTexture(
      *textures_["sniper_tower"]);
  ScaleSprite(sniper_tower_icon);
  sniper_tower_icon.scale(0.08f, 0.08f);
  sniper_tower_icon.setPosition(1680.0f * window_x_ / 1920.0f,
                                300.0f * window_x_ / 1920.0f);
  window_.draw(sniper_tower_icon);

  sf::Sprite melting_tower_icon;
  melting_tower_icon.setTexture(*textures_["melting_tower"]);
  ScaleSprite(melting_tower_icon);
  melting_tower_icon.scale(0.08f, 0.08f);
  melting_tower_icon.setPosition((1805.0f * window_x_ / 1920.0f),
                                 300.0f * window_x_ / 1920.0f);
  window_.draw(melting_tower_icon);
}

void Application::StyleButtonBrown(tgui::Button::Ptr button) {
  auto button_renderer = button->getRenderer();
  button_renderer->setBackgroundColor(sf::Color(205, 133, 63, 255));
  button_renderer->setBackgroundColorHover(sf::Color(205, 133, 63, 255));
  button_renderer->setBackgroundColorDown(sf::Color(185, 115, 53, 255));
  button_renderer->setBorderColor(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorHover(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorDown(sf::Color(139, 69, 19, 255));
  button_renderer->setBorderColorFocused(sf::Color(139, 69, 19, 255));
  button_renderer->setRoundedBorderRadius(8.0f);
  button_renderer->setBorders(5);
  button->setTextSize(20);
}

void Application::ScaleSprite(sf::Transformable& sprite) {
  sprite.setScale(sf::Vector2f(window_x_ / 1920.f, window_y_ / 1080.f));
}

}  // namespace td

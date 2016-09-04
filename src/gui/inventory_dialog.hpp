#ifndef HEADER_SUPERTUX_GUI_INVENTORY_HPP
#define HEADER_SUPERTUX_GUI_INVENTORY_HPP

#include <SDL.h>
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include "sprite/sprite_ptr.hpp"
#include <algorithm>
#include "control/controller.hpp"
#include "video/drawing_context.hpp"
#include "video/renderer.hpp"
#include "video/video_system.hpp"
#include "sprite/sprite.hpp"
#include "sprite/sprite_manager.hpp"

class Controller;
class DrawingContext;
struct InvItem;
class InventoryItem;
struct InvItem {
  std::string name;
  std::string plural;
  SpritePtr sprite;
  int anm;
  InventoryItem& item;
  std::string description;
  InvItem(InventoryItem& it):
    name(),
    plural(name+"s"),
    sprite(),
    anm(0),
    item(it),
    description("The fireflower is a powerup, which makes Tux shoot fire balls. \n If you find more firedlowers!")
  {

  };

};
class InventoryDialog
{
  private:

    std::vector<std::unique_ptr<InvItem>> inventory;
    int m_active_item;
    int m_rows,m_cols;
    std::vector<Rectf> items;

  public:
    InventoryDialog();
    void event(const SDL_Event& event);
    void process_input(const Controller& controller);
    void draw(DrawingContext& context);
    void update();
    void deactivate();
    void showInformation(int itemnr);

    bool passive = true;
};

#endif

#ifndef HEADER_SUPERTUX_GUI_INVENTORY_HPP
#define HEADER_SUPERTUX_GUI_INVENTORY_HPP

#include <SDL.h>
#include <functional>
#include <string>
#include <vector>
#include "sprite/sprite_ptr.hpp"


#include "math/sizef.hpp"

class Controller;
class DrawingContext;


class InventoryDialog
{
  private:
    struct InvItem {
      std::string name;
      std::string plural;
      SpritePtr sprite;
      std::function<void ()> callback;
      std::string description;
    };
    std::vector<InvItem> inventory;
    int m_active_item;
    int m_rows,m_cols;

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

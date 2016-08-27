#include "gui/inventory_dialog.hpp"
#include <algorithm>

#include "control/controller.hpp"
#include "gui/menu_manager.hpp"
#include "gui/menu.hpp"
#include "gui/mousecursor.hpp"
#include "supertux/resources.hpp"
#include "supertux/colorscheme.hpp"
#include "video/drawing_context.hpp"
#include "video/renderer.hpp"
#include "video/video_system.hpp"


InventoryDialog::InventoryDialog():
  inventory(),
  m_active_item(2),
  m_rows(2),
  m_cols(6)
{

}


void
InventoryDialog::event(const SDL_Event& event)
{

}

void
InventoryDialog::process_input(const Controller& controller)
{
  if(passive)
    return;
  if(controller.pressed(Controller::RIGHT))
  {
    if(m_active_item != (m_rows*m_cols-1))
      m_active_item++;
  }
  if(controller.pressed(Controller::LEFT))
  {
    if(m_active_item != 0)
      m_active_item--;
  }
  if ((controller.pressed(Controller::SWITCH_POWERUP)))
  {
    log_debug << "Exiting" << std::endl;
    deactivate();
  }
}

void InventoryDialog::draw(DrawingContext& context)
{
  std::string m_text = "Inventory";
  Sizef text_size = Sizef(Resources::normal_font->get_text_width(m_text),
                      Resources::normal_font->get_text_height(m_text));
  Rectf bg_rect(Vector((SCREEN_WIDTH/2 - text_size.width/2 - 200) ,
                       (SCREEN_HEIGHT/2 - text_size.height/2 - 100) ),
                Sizef(text_size.width+400,
                      text_size.height + 200));

  // draw background rect
  context.draw_filled_rect(bg_rect.grown(12.0f),
                       Color(0.2f, 0.3f, 0.4f,  0.8 ),
                       16.0f,
                       LAYER_GUI-10);

  context.draw_filled_rect(bg_rect.grown(8.0f),
                       Color(0.6f, 0.7f, 0.8f, 0.5 ),
                       16.0f,
                       LAYER_GUI-10);

  // draw text
  context.draw_text(Resources::normal_font, m_text,
                Vector(bg_rect.p1.x + bg_rect.get_width()/2.0f,
                       bg_rect.p1.y),
                ALIGN_CENTER, LAYER_GUI);
  // Draw horizontal line under text
  context.draw_filled_rect(Vector(bg_rect.p1.x-5, bg_rect.p1.y + text_size.height + 10),
                       Vector(bg_rect.get_width()+15, 4),
                       Color(0.6f, 0.7f, 1.0f, 1.0f), LAYER_GUI);
  context.draw_filled_rect(Vector(bg_rect.p1.x-5, bg_rect.p1.y + text_size.height + 10),
                       Vector(bg_rect.get_width()+15, 2),
                       Color(1.0f, 1.0f, 1.0f, 1.0f), LAYER_GUI);

  int rows = m_rows;
  int cols = m_cols;
  int colwidth = 50;

  int starty =  bg_rect.p1.y + text_size.height + 30;
  int startx =  bg_rect.p1.x;
  int colabstand = (((bg_rect.p2.x-bg_rect.p1.x)-(cols*colwidth))/(cols-1));
  if(colabstand < 0)
    throw std::runtime_error("Incorrect number of columns, can't display");
  int y_abstand = (((bg_rect.p2.y-starty)-(rows*colwidth))/rows);
  if(y_abstand < 0)
    throw std::runtime_error("Incorrect number of rows, can't display");

  int y = starty;
  for(int i = 0;i<rows;i++)
  {
    int x = startx;
    for(int j = 0;j<cols;j++)
    {

      Rectf item_rect(Vector(x,y),
                    Sizef(colwidth,colwidth));
      if((i*m_cols+j) == m_active_item)
      {
        // Mark the active item yellow ;-)
       context.draw_filled_rect(item_rect.grown(3.0f),
                                Color(0.0f, 0.0f, 0.0f,  1.0 ),
                               18.0f,
                               LAYER_GUI-10);
                    }
      // draw background rect
      context.draw_filled_rect(item_rect.grown(2.0f),
                           Color(0.2f, 0.3f, 0.4f,  0.8 ),
                           16.0f,
                           LAYER_GUI-10);
      x += colabstand+colwidth;
    }
    y += y_abstand+colwidth;
  }

}

void InventoryDialog::showInformation(int itemnr)
{

}

void InventoryDialog::update()
{

}

void InventoryDialog::deactivate()
{
  MenuManager::instance().set_inventory_dialog(nullptr);
}

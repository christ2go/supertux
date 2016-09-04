#include "gui/inventory_dialog.hpp"
#include "gui/menu_manager.hpp"
#include "gui/menu.hpp"
#include "gui/mousecursor.hpp"
#include "supertux/resources.hpp"
#include "supertux/colorscheme.hpp"
#include "math/sizef.hpp"
#include "supertux/game_manager.hpp"
InventoryDialog::InventoryDialog() :
        inventory(),
        m_active_item(0),
        m_rows(2),
        m_cols(6),
        items()
{
        // Load Inventory items from
        /*i->description = "When Tux is equipped with a fireflower he can shoot.";
           i->name = "Fireflower";
           i->plural = "Fireflowers";
           i->anm = 289;*/


        auto dict = GameManager::current()->get_dictionary();
        for(const auto& item:dict->getInventoryItems())
        {
                std::unique_ptr<InvItem> i(new InvItem(*item.get()));
                i->sprite = SpriteManager::current()->create("images/inventory/fireflower/fireflower.sprite");
                inventory.push_back(std::move(i));
        }
}


void
InventoryDialog::event(const SDL_Event& event)
{
        // Check the event type
        if(event.type == SDL_MOUSEMOTION)
        {
                // Check if current mouse position contains any
                int i = 0;
                for(const auto& rect:items)
                {
                        Vector mouse_pos = VideoSystem::current()->get_renderer().to_logical(event.motion.x, event.motion.y);
                        float x = mouse_pos.x;
                        float y = mouse_pos.y;

                        if(rect.contains(Vector(x,y)))
                        {
                                m_active_item = i;
                        }
                        i++;
                }
        }



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
        if(controller.pressed(Controller::DOWN))
        {
                if(((signed int) m_active_item+m_cols) < (signed int) items.size())
                        m_active_item += m_cols;
        }
        if(controller.pressed(Controller::UP))
        {
                if(((signed int) m_active_item-m_cols) >= 0)
                        m_active_item -= m_cols;
        }
        if ((controller.pressed(Controller::SWITCH_POWERUP)))
        {
                deactivate();
        }
}

void InventoryDialog::draw(DrawingContext& context)
{
        std::string m_text = "Inventory";
        Sizef text_size = Sizef(Resources::normal_font->get_text_width(m_text),
                                Resources::normal_font->get_text_height(m_text));
        Rectf bg_rect(Vector((SCREEN_WIDTH/2 - text_size.width/2 - 200),
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
        items.clear();
        if(y_abstand < 0)
                throw std::runtime_error("Incorrect number of rows, can't display");

        int y = starty;
        for(int i = 0; i<rows; i++)
        {
                int x = startx;
                for(int j = 0; j<cols; j++)
                {

                        Rectf item_rect(Vector(x,y),
                                        Sizef(colwidth,colwidth));
                        items.push_back(item_rect);
                        if((i*m_cols+j) == m_active_item)
                        {
                                // Mark the active item yellow ;-)
                                context.draw_filled_rect(item_rect.grown(3.0f),
                                                         Color(0.0f, 0.0f, 0.0f,  1.0 ),
                                                         18.0f,
                                                         LAYER_GUI-10);
                                //
                                if ((unsigned int)(i*cols+j) < inventory.size() && !inventory[i*cols+j]->description.empty())
                                {
                                  log_debug << "Musnt't draw" << std::endl;
                                        int text_width  = (int) Resources::small_font->get_text_width(inventory[i*cols+j]->description);
                                        int text_height = (int) Resources::normal_font->get_text_height(inventory[i*cols+j]->description);

                                        Rectf text_rect(bg_rect.p1.x-text_width/2,
                                                        SCREEN_HEIGHT - 48 - text_height/2 - 1,
                                                        bg_rect.p2.x+text_width/2 ,
                                                        SCREEN_HEIGHT - 48 + text_height/2 + 1);

                                        context.draw_filled_rect(Rectf(text_rect.p1 - Vector(2,2),
                                                                       text_rect.p2 + Vector(2,2)),
                                                                 Color(0.2f, 0.3f, 0.4f, 0.8f),
                                                                 16.0f,
                                                                 LAYER_GUI-10);

                                        context.draw_filled_rect(text_rect,
                                                                 Color(0.6f, 0.7f, 0.8f, 0.5f),
                                                                 16.0f,
                                                                 LAYER_GUI-10);

                                        context.draw_text(Resources::normal_font, inventory[i*cols+j]->description,
                                                          Vector((text_rect.p2.x+text_rect.p1.x)/2, SCREEN_HEIGHT - 48 - text_height/2),
                                                          ALIGN_CENTER, LAYER_GUI);
                                }

                        }
                        // draw background rect
                        context.draw_filled_rect(item_rect.grown(2.0f),
                                                 Color(0.2f, 0.3f, 0.4f,  0.8 ),
                                                 16.0f,
                                                 LAYER_GUI-10);
                        x += colabstand+colwidth;

                        // Check
                        if((unsigned int)(i*cols+j) < inventory.size())
                        {
                                // Display the item
                                inventory[i*cols+j]->sprite->draw(context,Vector(item_rect.p1.x,item_rect.p1.y),LAYER_GUI);
                                if(inventory[i*cols+j]->anm > 1)
                                {
                                        std::ostringstream stringStream;
                                        stringStream << inventory[i*cols+j]->anm << "x";
                                        m_text = stringStream.str();
                                        text_size = Sizef(Resources::small_font->get_text_width(m_text),
                                                          Resources::small_font->get_text_height(m_text));
                                        context.draw_text(Resources::small_font, m_text,
                                                          Vector(item_rect.p2.x-text_size.width,item_rect.p2.y-text_size.height),
                                                          ALIGN_CENTER, LAYER_GUI);

                                }
                        }
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

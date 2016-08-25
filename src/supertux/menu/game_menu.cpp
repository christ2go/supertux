//  SuperTux
//  Copyright (C) 2009 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "supertux/menu/game_menu.hpp"

#include "gui/menu.hpp"
#include "gui/menu_item.hpp"
#include "gui/menu_manager.hpp"
#include "supertux/game_session.hpp"
#include "supertux/level.hpp"
#include "supertux/menu/menu_storage.hpp"
#include "supertux/menu/options_menu.hpp"
#include "supertux/screen_manager.hpp"
#include "util/gettext.hpp"
#include "gui/dialog.hpp"

GameMenu::GameMenu():
  m_powerups(),
  next_powerup(0)
{
  Level* level = GameSession::current()->get_current_level();

  add_label(level->name);
  add_hl();
  add_entry(MNID_CONTINUE, _("Continue"));
  add_entry(MNID_RESETLEVEL, _("Restart Level"));
  add_submenu(_("Options"), MenuStorage::INGAME_OPTIONS_MENU);
  m_powerups.clear();
  m_powerups.push_back("Fireflower");
  m_powerups.push_back("Iceflower");
  m_powerups.push_back("Earthflower");
  m_powerups.push_back("Airflower");
  next_powerup = 0;
  MenuItem* magnification = add_string_select(MNID_SELECTPOWERUP, _("Next powerup"), &next_powerup, m_powerups);
  magnification->set_help(_("Select the powerup you want to load."));
  add_entry(MNID_USEPOWERUP, _("Use powerup"));
  add_hl();
  add_entry(MNID_ABORTLEVEL, _("Abort Level"));
}

void
GameMenu::menu_action(MenuItem* item)
{
  switch (item->id)
  {
    case MNID_CONTINUE:
      MenuManager::instance().clear_menu_stack();
      GameSession::current()->toggle_pause();
      break;

    case MNID_RESETLEVEL:
      MenuManager::instance().clear_menu_stack();
      GameSession::current()->toggle_pause();
      GameSession::current()->reset_button = true;
      break;

    case MNID_ABORTLEVEL:
      GameSession::current()->abort_level();
      break;
    case MNID_USEPOWERUP:
    {
      /*auto dict = GameManager::current()->get_dictionary();
      Player* player = Sector::current()->player;
      bool rval;

      // Display error dialogue
      if(false == true)
      {
        std::unique_ptr<Dialog> dialog(new Dialog);
        dialog->set_text(_("Error:\n") + _("You don't have such a powerup stored!"));
        dialog->add_button(_("Ok"));
        MenuManager::instance().set_dialog(std::move(dialog));
      }
      */
    }

  }
}

/* EOF */

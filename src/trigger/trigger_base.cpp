//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
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

#include "trigger/trigger_base.hpp"

#include "object/player.hpp"
#include "sprite/sprite.hpp"

TriggerBase::TriggerBase(const ReaderMapping& mapping)
    : MovingObject(mapping),
      m_sprite(),
      m_lasthit(false),
      m_hit(false),
      m_losetouch_listeners() {
  set_group(COLGROUP_TOUCHABLE);
}

TriggerBase::TriggerBase()
    : m_sprite(), m_lasthit(false), m_hit(false), m_losetouch_listeners() {
  set_group(COLGROUP_TOUCHABLE);
}

TriggerBase::~TriggerBase() {
  // unregister remove_listener hooks, so nobody will try to call us after we've
  // been destroyed
  for (auto& p : m_losetouch_listeners) {
    p->del_remove_listener(this);
  }
  m_losetouch_listeners.clear();
}

void TriggerBase::update(float) {
  if (m_lasthit && !m_hit) {
    for (auto& p : m_losetouch_listeners) {
      event(*p, EVENT_LOSETOUCH);
      p->del_remove_listener(this);
    }
    m_losetouch_listeners.clear();
  }
  m_lasthit = m_hit;
  m_hit = false;
}

void TriggerBase::draw(DrawingContext& context) {
  if (!m_sprite.get()) return;

  m_sprite->draw(context.color(), get_pos(), LAYER_TILES + 1);
}

HitResponse TriggerBase::collision(GameObject& other, const CollisionHit&) {
  auto player = dynamic_cast<Player*>(&other);
  if (player) {
    m_hit = true;
    if (!m_lasthit) {
      m_losetouch_listeners.push_back(player);
      player->add_remove_listener(this);
      event(*player, EVENT_TOUCH);
    }
  }

  return ABORT_MOVE;
}

void TriggerBase::object_removed(GameObject* object) {
  m_losetouch_listeners.erase(std::remove(m_losetouch_listeners.begin(),
                                          m_losetouch_listeners.end(), object),
                              m_losetouch_listeners.end());
}

/* EOF */

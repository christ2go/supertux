//  SuperTux -- ExposedObject class
//  Copyright (C) 2016 Tobias Markus <tobbi.bugs@googlemail.com>
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

#ifndef HEADER_SUPERTUX_SCRIPTING_EXPOSED_OBJECT_HPP
#define HEADER_SUPERTUX_SCRIPTING_EXPOSED_OBJECT_HPP

#include "scripting/scripting.hpp"
#include "scripting/squirrel_util.hpp"
#include "supertux/script_interface.hpp"
#include "util/log.hpp"
#include <sqrat.h>

/**
 * @class ExposedObject
 * This class binds a certain GameObject class to a scripting class.
 * To bind a game object class to a scripting class, extend the GameObject
 * class as shown in the following example:
 * \code{.cpp}
 * public ExposedObject<Gradient, scripting::Gradient>
 * \endcode
 *
 * and instantiate it in each constructor with the <i>this</i> pointer, like this:
 * \code{.cpp}
 * Gradient::Gradient(const ReaderMapping& reader) :
 *  ExposedObject<Gradient, scripting::Gradient>(this)
 * \endcode
 * @param class S: GameObject class (e.g. Gradient)
 * @param class T: Scripting class (e.g. scripting::Gradient)
 */
template<class S>
class ExposedObject : public ScriptInterface
{
private:
  /**
 * The parent object that is exposed to the script interface
 */
  S* m_parent;

public:
  /**
   * Constructor
   * @param parent GameObject
   */
  ExposedObject(S* parent) :
    m_parent(parent)
  {
  }

  /**
   * Exposes the parent GameObject to the script Interface
   * @param vm The squirrel virtual machine to expose the object on
   * @param table_idx Index of the table to expose the object on
   */
  void expose(Sqrat::Table t,S* object)
  {
    auto name = m_parent->get_name();
    if (name.empty())
    {
      return;
    }

    log_debug << "Exposing " << object->get_class() << " object " << name << std::endl;

    t.SetInstance(name,object);
  }

  /**
   * Un-exposes the parent GameObject to the script Interface
   * @param vm The squirrel virtual machine to un-expose the object on
   * @param table_idx Index of the table to un-expose the object on
   */
  void unexpose(Sqrat::Table t)
  {
    auto name = m_parent->get_name();
    if (name.empty())
    {
      return;
    }

    t.SetInstance(name,NULL);
  }

private:
  ExposedObject(const ExposedObject&) = delete;
  ExposedObject& operator=(const ExposedObject&) = delete;
};

#endif

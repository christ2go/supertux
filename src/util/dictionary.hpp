//  SuperTux
//  Copyright (C) 2016 Christian Hagemeier <christian@hagemeier.ch>
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

#ifndef HEADER_SUPERTUX_UTIL_DICTIONARY_HPP
#define HEADER_SUPERTUX_UTIL_DICTIONARY_HPP
#include <squirrel.h>
#include <vector>
#include <map>
#include <boost/any.hpp>
#include "util/log.hpp"
#include "util/writer.hpp"
#include <memory>
#include "util/sqarrayser.hpp"
#include "util/sqdictser.hpp"
#include "physfs/ifile_streambuf.hpp"
#include "util/file_system.hpp"
#include "util/log.hpp"
#include "util/reader_document.hpp"
#include "util/reader_mapping.hpp"
#include "util/reader_collection.hpp"
#include "storage/StorageContainer.hpp"

class InventoryItem;
class sqdict;
class sqarr;
class StorageContainer;

using std::auto_ptr;

enum dictionaryTypes {
    DICT_STRING = 0, DICT_FLOAT, DICT_INT,DICT_BOOL, DICT_ARR, DICT_TABLE
};


class dictionaryItem {
  /**
   * This class represents an item in the dictionary.
   */
  public:
    std::string key;
    dictionaryTypes type;
    std::unique_ptr<boost::any> item;
    std::string value;
    std::unique_ptr<sqarr> valarr;
    std::unique_ptr<sqdict> valdict;
    dictionaryItem():
        key(),
        type(),
        item(),
        value(),
        valarr(),
        valdict() {
    };
};


class dictionary {
  private:
    std::map<std::string,std::shared_ptr<dictionaryItem>> m_table; // Hashtable with variable size
    dictionaryItem* add(const std::string& key,std::unique_ptr<boost::any> value);
    dictionaryItem* createTableEntry(const std::string& key);
  public:
    /**
     * This method is used for saving the dictionary to the disk.
     * @return True if the save was successfull.
     */
    bool save();
    /**
     * Adds an integer value into the dictionary.
     * @param key   The string under which the key is to be stored.
     * @param value The integer value to be stored.
     */
    void add(const std::string& key,int value);
    /**
     * Adds a string value into the dictionary.
     * If a value with that key already exists, it is overwritten.
     * @param key   The string under which the key is to be stored.
     * @param value The string value to be stored.
     */
    void add(const std::string& key,std::string value);
    /**
     * Adds an float value into the dictionary.
     * If a value with that key already exists, it is overwritten.
     * @param key   The string under which the key is to be stored.
     * @param value The float value to be stored.
     */
    void add(const std::string& key,float value);
    /**
     * Adds a boolean value into the dictionary.
     * If a value with that key already exists, it is overwritten.
     * @param key   The string under which the key is to be stored.
     * @param value The boolean value to be stored.
     */
    void add(const std::string& key,bool value);
    /**
     * Adds an array value into the dictionary.
     * If a value with that key already exists, it is overwritten.
     * @param key   The string under which the key is to be stored.
     * @param value The sqdict reference value to be stored.
     */
    void add(const std::string& key,std::unique_ptr<sqarr> value);
    void add(const std::string& key,std::unique_ptr<sqdict> value);
    /**
     * Sets the file name, under which the dictionary will be stored
     * by the save method. Overwrittes previous filenames.
     * @param filename [description]
     */
    void setFilename(const std::string& filename);
    /**
     * Returns a Storable with the given name,
     * which is stored in the StorageContainer.
     * @param  name The storables name
     * @return      A Pointer to the Storable, if a Storable with that name exists.
     */
    Storable* getStorable(const std::string& name);
    /**
     * Returns the filename, under which the dictionary is currently
     * going to be saved
     * @return filename
     */
    std::string getFilename(){
      return m_filename;
    };
    /**
     * Gets a dictionarys item.
     * @param  The items key
     * @return A pointer to the dictionaryItem, if it exists, else null.
     */
    dictionaryItem* get(const std::string& key);
    /**
     * Constructs a dictionary.
     * @param The filename
     */
    dictionary(const std::string& filename);

    dictionary(void); // Initialize empty
    /**
     * Convert strings to a dictionary type.
     * Used for loading dictionaries.
     * @param  type The types name.
     * @return      The type names type represenation.
     */
    static dictionaryTypes str2type(const std::string& type);
    /**
     * Returns a vector of the current InventoryItems.
     */
    std::vector<std::shared_ptr<InventoryItem>> getInventoryItems();

  private:
    /**
     * Returns a dictionaryItem's type
     * @param  i the item
     * @return   the typename
     */
    static std::string getTypename(dictionaryItem* i);
    std::string m_filename;
    std::unique_ptr<Writer> m_writer;
    std::unique_ptr<StorageContainer> m_collectItems;
    void saveItems();
    void saveItem(const dictionaryItem* item);
    void load();
};

#endif

/*

Copyright (C) 2017 Jayesh Salvi, Blue Math Software Inc.

This file is part of ekpassword.

ekpassword is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ekpassword is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with ekpassword. If not, see <http://www.gnu.org/licenses/>.

*/

#include <vector>
#include <string>

class DataStore {

public:

  class Entry {
  public:
    std::string hostname;
    std::string username;
    std::string password;
    std::string category;

    Entry(const std::string& ihostname,
          const std::string& iusername,
          const std::string& ipassword,
          const std::string& icategory=""):
      hostname(ihostname),
      username(iusername),
      password(ipassword),
      category(icategory)
    {}
  };

  typedef std::vector<Entry> EntryList;

private:
  std::string m_filepath;
  EntryList m_entries;
  std::string m_encpassword;

public:
  DataStore(
    const std::string& filepath,
    const std::string& password);

  void save();
  void load();

  void addEntry(const Entry& entry);
  void removeEntry(const unsigned int index);
  const EntryList& listEntries();

};

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

#include "datastore.h"
#include "encdec.h"

DataStore::DataStore(const std::string &filepath, const std::string &password)
{
  m_filepath = filepath;

  // Compute SHA256 hash of password
  m_encpassword = computeSHA256(password);

}

const DataStore::EntryList& DataStore::listEntries() {
  return m_entries;
}

void DataStore::load() {
  // Read the file

  // Use password to decrypt the file

}

void DataStore::save() {

}

void DataStore::addEntry(const Entry &entry) {
  auto encEntry = entry;
  // TODO encrypt password in entry
  m_entries.push_back(encEntry);
}

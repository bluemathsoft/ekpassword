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

#include <fstream>

using std::ios;

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
  std::stringstream ss;
  ss << toJSON();
  std::string plainstr = ss.str();

  unsigned char *iv = (unsigned char *)"0123456789012345"; // TODO : no hardcoding
  unsigned char *key = (unsigned char *)m_encpassword.c_str();
  unsigned char *plaintext = (unsigned char*)plainstr.c_str();
  unsigned char *ciphertext = new unsigned char[2*plainstr.size()];

  size_t cipherlen = encrypt(
    plaintext, plainstr.length(), key, iv, ciphertext);

  // ---
  // Write encrypted text to binary file
  //
  std::ofstream encofs;
  encofs.open(m_filepath,ios::out|ios::binary|ios::trunc);
  if(encofs.is_open()) {
    encofs << ciphertext; // TODO : use cipherlen
  } else {
    std::cerr << "Failed to open file to write" << std::endl;
  }
  encofs.close();
  // ---
}

void DataStore::addEntry(const Entry &entry) {
  auto encEntry = entry;
  // TODO encrypt password in entry
  m_entries.push_back(encEntry);
}

const json DataStore::toJSON() {
  json j = json::array();
  for(DataStore::Entry entry : m_entries) {
    j.push_back(entry.toJSON());
  }
  return j;
}

void DataStore::fromJSON(const json &) {

}

const json DataStore::Entry::toJSON() {
  json j;
  j["hostname"] = m_hostname;
  j["username"] = m_username;
  j["password"] = m_password;
  j["category"] = m_category;
  return j;
}

void DataStore::Entry::fromJSON(const json &) {

}

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

#include "tdatastore.h"

CPPUNIT_TEST_SUITE_REGISTRATION(DataStoreTest);

void
DataStoreTest::setUp()
{
}

void
DataStoreTest::tearDown()
{
}

void
DataStoreTest::testConstructor()
{
  DataStore dstore("/tmp/somepath.enc");
  CPPUNIT_ASSERT(true);
}

void DataStoreTest::testOps()
{
  DataStore dstore("/tmp/somepath.enc");
  dstore.load();

  CPPUNIT_ASSERT(dstore.listEntries().size() == 0);

  DataStore::Entry entry("http://www.google.com","john.doe@gmail.com","pass123");
  dstore.addEntry(entry);

  CPPUNIT_ASSERT(dstore.listEntries().size() == 1);
}

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

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "encdec.h"
#include "json.h"
#include "args.h"

using std::ios;

using json = nlohmann::json;

void computePasswordSHA256(const char *string, char outputBuffer[65])
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, string, strlen(string));
  SHA256_Final(hash, &sha256);
  int i = 0;
  for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(outputBuffer + (i * 2), "%02x", hash[i]); // TODO: use snprintf
  }
  outputBuffer[64] = 0;
}

int main (int argc, char *argv[])
{

  args::ArgumentParser parser("ekstore CLI", "");
  args::HelpFlag helpOpt(parser,"help","Display this help menu",{'h',"help"});

  args::Flag addOpt(
        parser,"add","Add entry",{"add"});
  args::Flag removeOpt(
        parser,"remove","Remove entry",{"remove"});
  args::Flag listOpt(
        parser,"list","List entries",{"list"});

  args::ValueFlag<std::string> urlOpt(
        parser,"url","URL of website to store password for",{"url"});

  try {
    parser.ParseCLI(argc, argv);
  } catch(args::Help) {
    std::cout << parser;
    return 0;
  } catch(args::ParseError e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  if(addOpt) {
    std::string url = args::get(urlOpt);
    if(url.length() <= 0) {
      std::cerr << "Missing URL" << std::endl;
      return 1;
    }
    std::cout << "Adding " << std::endl;
    std::cout << "URL " << url << std::endl;
    return 0;
  }
  if(removeOpt) {
    std::string url = args::get(urlOpt);
    if(url.length() <= 0) {
      std::cerr << "Missing URL" << std::endl;
      return 1;
    }
    std::cout << "Removing " << std::endl;
    std::cout << "URL " << url << std::endl;
    return 0;
  }
  if(listOpt) {
    std::cout << "List all entries (TODO) " << std::endl;
    return 0;
  }


  std::string plainpassword;
  std::cout << "Enter Password: ";
  std::cin >> plainpassword;

  char passwordsha[65];
  computePasswordSHA256(plainpassword.c_str(), passwordsha);

  std::cout << "Password SHA " << std::string(passwordsha) << std::endl;

  return 0;


  /* Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";


  std::stringstream plainss;
  plainss << "[";
  plainss << "  {";
  plainss << "    \"url\" : \"https://google.com\",";
  plainss << "    \"password\" : \"12345\"";
  plainss << "  }";
  plainss << "]";

  std::string plainstr = plainss.str();

  unsigned char *plaintext = (unsigned char*) plainstr.c_str();

  unsigned char *ciphertext = new unsigned char[2*plainstr.size()];


  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  ciphertext_len = encrypt(plaintext, strlen ((char *)plaintext), key, iv,
                            ciphertext);


  // ---
  // Write encrypted text to binary file
  //
  std::ofstream encofs;
  encofs.open("ekdatabase.enc",ios::out|ios::binary|ios::trunc);
  if(encofs.is_open()) {
    encofs << ciphertext;
  } else {
    std::cerr << "Failed to open file to write" << std::endl;
  }
  encofs.close();
  // ---



  // ---
  // Read encrypted text from binary file
  //
  std::ifstream encifs("ekdatabase.enc",ios::binary|ios::in);
  if(encifs.is_open()) {
    encifs.seekg(0,encifs.end);
    size_t filesize = encifs.tellg();
    encifs.seekg(0,encifs.beg);

    unsigned char *readciphertext = new unsigned char[filesize];
    unsigned char *decryptedtext = new unsigned char[filesize];

    encifs.read((char*)readciphertext, filesize);
    encifs.close();

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
      decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';

    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

    json jsonobj;
    std::stringstream ss((char *)decryptedtext);
    jsonobj << ss;

    json::iterator it = jsonobj.begin();
    while(it != jsonobj.end()) {
      std::cout << (*it)["url"] << std::endl;
      std::cout << (*it)["password"] << std::endl;
      it++;
    }


    delete[] readciphertext;
    delete[] decryptedtext;

  } else {
    std::cerr << "Failed to open file to read" << std::endl;
  }
  // ---

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}

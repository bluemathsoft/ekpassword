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
#include <string.h>
#include <sstream>
#include "encdec.h"

int main (void)
{
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

  unsigned char *decryptedtext = new unsigned char[2*plainstr.size()];

  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
                            ciphertext);

  /* Do something useful with the ciphertext here */
  printf("Ciphertext is:\n");
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

  /* Decrypt the ciphertext */
  decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  printf("Decrypted text is:\n");
  printf("%s\n", decryptedtext);

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}

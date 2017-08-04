/*

Copyright (C) 2017 Jayesh Salvi, Blue Math Software Inc.

This file is part of ekpassword.

bluemath is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

bluemath is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with bluemath. If not, see <http://www.gnu.org/licenses/>.

*/

/*
#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>

void encrypt(
  const char *indata,
  size_t indata_len,
  char *outdata,
  int *outLen2)
{
  int outLen1 = 0;
  unsigned char ckey[] =  "password";
  unsigned char ivec[] = "donotchangethis!";

  //Set up encryption
  EVP_CIPHER_CTX ctx;
  EVP_EncryptInit(&ctx,EVP_aes_256_cbc(),ckey,ivec);
  EVP_EncryptUpdate(&ctx,outdata,&outLen1,indata,indata_len);
  std::cout << "outlen1 " << outLen1 << std::endl;
  EVP_EncryptFinal(&ctx,outdata + outLen1,outLen2);
}

int main(int argc, char *argv[])
{

  std::string msg("This is my secret text");

  char *encmsg = (char*)malloc(msg.length() * 2);
  int encmsglen;

  encrypt(msg.c_str(), msg.length(), encmsg, &encmsglen);

  std::cout << msg.length() << std::endl;
  std::cout << encmsglen << std::endl;

  return 0;
}

*/

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
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

  /* Message to be encrypted */
  unsigned char *plaintext =
                (unsigned char *)"The quick brown fox jumps over the lazy dog";

  /* Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, dependant on the
   * algorithm and mode
   */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

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

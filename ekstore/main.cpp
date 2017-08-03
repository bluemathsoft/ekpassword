
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

/*
openssl library is required.
For ubuntu it can be installed with: sudo apt-get install libssl-dev
compiling: $gcc sha1.c -lssl -lcrypto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
 

void stringHash(char *string) {
  int i;
  unsigned char result[SHA_DIGEST_LENGTH];
  SHA1(string, strlen(string), result);
  for(i = 0; i < SHA_DIGEST_LENGTH; i++)
    printf("%02x%c", result[i], i < (SHA_DIGEST_LENGTH-1) ? ' ' : '\n');
}

void getFileHash(char *fileName){

unsigned char result[2*SHA_DIGEST_LENGTH];
unsigned char hash[SHA_DIGEST_LENGTH];
int i;
FILE *f = fopen(fileName,"rb");
SHA_CTX mdContent;
int bytes;
unsigned char data[1024];

if(f == NULL){
    printf("%s couldn't open file\n",fileName);
    exit(1);
}

SHA1_Init(&mdContent);
while((bytes = fread(data, 1, 1024, f)) != 0){

    SHA1_Update(&mdContent, data, bytes);
}

SHA1_Final(hash,&mdContent);

for(i=0;i<SHA_DIGEST_LENGTH;i++){
    printf("%02x",hash[i]);
}
printf("\n");
/** if you want to see the plain text of the hash */
//for(i=0; i < SHA_DIGEST_LENGTH;i++){
//    sprintf((char *)&(result[i*2]), "%02x",hash[i]);
//}
//printf("%s\n",result);

fclose(f);
}

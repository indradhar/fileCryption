#include<stdio.h>
#if defined(_WIN64)//Microsoft Windows (64-bit)
#include<conio.h>
#define CLRSC cls
#elif defined(_WIN32)//Microsoft Windows (32-bit)
#include<conio.h>
#define CLRSC "cls"
#endif
#if defined(__linux__)//For gcc/linux
#define CLRSC "clear"
#endif
#if defined(__unix__)//For gcc/unix
#define CLRSC "clear"
#endif
#include<stdlib.h>
#include "header.h"

int main()
{
  int i,j,type_of_op,crypt_type,object_type,no_of_algos,no_of_objects;
  char algos[6][30]={"mono alphabetic cipher","key file encryption","AES","SHA-1","RSA","go back"};
  char objects[3][10]={"string","file","goto menu"};
  no_of_algos=sizeof(algos)/sizeof(algos[0]);
  no_of_objects=sizeof(objects)/sizeof(objects[0]);

  /*

  type of operations
    1->encryption / cryptographic hash
    2->decryption
    3->exit

  encryption or decryptions types
    1->mono alphabetic cipher
    2->key file encryption
    3->AES
    4->SHA-1
    5->RSA
    6->go back
    
  type of objects
    1->string
    2->file
    3->goto menu

  */

  while(1) {
    system(CLRSC);
    printf("choose one of the following operations to perform:\n");
    printf("1->encryption / cryptographic hash\n2->decryption\n3->exit\n");
    while(1)
    {
      printf("INPUT: ");
      if(scanf("%d",&type_of_op)==0)
        getchar();
      if(type_of_op>=1 && type_of_op<=2)
        break;
      else if(type_of_op==3)
        return 0;
      else
        printf("\n!!!! PLEASE ENTER CORRECT OPTION NUMBER !!!!!\n");
        
    }
    
    printf("\n");
    system(CLRSC);
    printf("choose any one cryptographic method from the following:\n");
    for(i=0;i<no_of_algos;i++)
    {
     printf("%d->%s\n",i+1,algos[i]);
    }
    printf("\n");
    while(1)
    {
      printf("INPUT: ");
      if(scanf("%d",&crypt_type)==0)
        getchar();
      if(crypt_type>=1 && crypt_type<=no_of_algos)
        break;
      else
        printf("\n!!!! PLEASE ENTER CORRECT OPTION NUMBER !!!!!\n");

    }
    if(crypt_type==6)
      continue;
    printf("\n");
    system(CLRSC);
    printf("choose one type of object from the following:\n");
    for(i=0;i<no_of_objects;i++)
    {
    printf("%d->%s\n",i+1,objects[i]);
    }
    printf("\n");
    while(1)
    {
      printf("INPUT: ");
      if(scanf("%d",&object_type)==0)
        getchar();
      //scanf("%d",&object_type);
      if(object_type>=1 && object_type<=no_of_objects)
        break;
      else
        printf("\n!!!! PLEASE ENTER CORRECT OPTION NUMBER !!!!!\n");
    }

  getchar();
    if(object_type==3)
      continue;

if(type_of_op==1)
{
  switch(crypt_type)
  {
    case 1:
            ma_cipher_encrypt(object_type);
            break;
    case 2:
            keyFile_encry(object_type);
            break;
    case 3:
            break;
    case 4:
            if(object_type==1) {
              printf("Please enter string to hash(max length:2048) :");
              char sth1[2048];
              scanf("%2048s",sth1);
              stringHash(sth1);
             }
            else if(object_type==2) {
              printf("Please enter file path(max path length:2048) :");
              char sth2[2048];
              scanf("%2048s",sth2);
              getFileHash(sth2);
              break;
            }

  }
}
else if(type_of_op==2)
{
  switch(crypt_type)
  {
    case 1:
            ma_cipher_decrypt(object_type);
            break;
    case 2:
            keyFile_decry(object_type);
            break;
    case 3:
            break;
    case 4:
            printf("Not a valid option\n(good luck, if you mean it)\n");
            break;
  }


}

  }
  return 0;
}

#include<stdio.h>
#if defined(_WIN64)//Microsoft Windows (64-bit)
#include<conio.h>
#elif defined(_WIN32)//Microsoft Windows (32-bit)
#include<conio.h>
#endif
#include<stdlib.h>
#include "header.h"

int main()
{
  int i,j,type_of_op,crypt_type,object_type,no_of_algos,no_of_objects;
  char algos[4][15]={"ceaser cipher","AES","RSA","SHA-1"};
  char objects[3][10]={"string","file","goto main-menu"};
  no_of_algos=sizeof(algos)/sizeof(algos[0]);
  no_of_objects=sizeof(objects)/sizeof(objects[0]);
  
  /*
  
  type of operations
    1->encryption / cryptographic hash
    2->decryption
    3->exit

  encryption or decryptions types
    1->ceaser cipher
    2->aes
    3->rsa
    4->SHA-1
    5->go back //**TO BE ADDED**
  type of objects
    1->string
    2->file
    3->goto to main-menu //**TO BE ADDED**

  */

  while(1) {
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
      scanf("%d",&crypt_type);
      if(crypt_type>=1 && crypt_type<=no_of_algos)
        break;
      else
        printf("\n!!!! PLEASE ENTER CORRECT OPTION NUMBER !!!!!\n");

    }
    printf("\n");
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
      scanf("%d",&object_type);
      if(object_type>=1 && object_type<=no_of_objects)
        break;

      else
        printf("\n!!!! PLEASE ENTER CORRECT OPTION NUMBER !!!!!\n");

    }
  }
  return 0;
}

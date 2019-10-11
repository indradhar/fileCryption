#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main()
{
  int i,j,type_of_op,crypt_type,object_type,no_of_algos,no_of_objects;
  char algos[3][15]={"ceaser cipher","AES","RSA"};
  char objects[2][10]={"string","file"};
  no_of_algos=sizeof(algos)/sizeof(algos[0]);
  no_of_objects=sizeof(objects)/sizeof(objects[0]);
  
  /*
  type of operations
    1->encryption
    2->decryption

  encryption or decryptions types
    1->ceaser cipher
    2->aes
    3->rsa
  type of objects
    1->string
    2->file

  */

  while(1) {
    printf("choose one of the following operations to perform:\n");
    printf("1->encryption\n2->decryption\n");
    while(1)
    {
      printf("INPUT: ");
      if(scanf("%d",&type_of_op)==0)
        getchar();
      if(type_of_op>=1 && type_of_op<=2)
        break;
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

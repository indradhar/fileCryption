#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LIMIT 1025
int randNumber(int lower,int upper)
{
  int num = (rand() %
           (upper - lower + 1)) + lower;
  return num;
}

void keyFile_encrypt_string(char *str)
{
    FILE *fk;
    char key_file_name[11];
    int i,j,random;
    for(i=0;i<10;i++)
    {
      key_file_name[i]='A'+randNumber(0,25);
    }

    fk=fopen(key_file_name,"w");//opening a file with random randNumber
    if(fk==NULL)
    {
      printf("ERROR:unable to perform file hnadling operations!! exiting......\n");
      exit(0);
    }

    for(i=0;i<strlen(str);i++)
    {
      random=randNumber(1,100);
      str[i]=str[i]+random;
      fprintf(fk, "%d ",random );
    }
    fclose(fk);
    printf("\n the key used to encrypt is strored in file named \" %s \" in the current directory\n",key_file_name);

}


void keyFile_encrypt_file(char *file_name)
{
      FILE *fs,*fd,*fk;
      char c,key_file_name[11];
      int i,j,random;

      for(i=0;i<10;i++)
      {
        key_file_name[i]='A'+randNumber(0,25);
      }

      fs=fopen(file_name,"r");
      fd=fopen("dest.txt","w");
      fk=fopen(key_file_name,"w");


      do
       {

            c = fgetc(fs);

            if (feof(fs))
                break ;
            random=randNumber(1,100);
            c=c+random;
            fputc(c,fd);
            fprintf(fk, "%d ",random );
       }  while(1);

       fclose(fs);
       fclose(fd);
       fclose(fk);
       remove(file_name);
       rename("dest.txt",file_name);
       printf("\nthe file successfully encrypted!\n");
       printf("\n the key used to encrypt is strored in file named \" %s \" in the current directory\n",key_file_name);

}

void keyFile_decrypt_string(char *str,char *key_file_name)
{
    FILE *fk=fopen(key_file_name,"r");
    char c;
    int i,key;

    if(fk==NULL)
    {
      printf("ERROR:unable to perform file handling operations!, exiting....");
      exit(0);
    }


    for(i=0;i<strlen(str);i++)
    {
        fscanf(fk,"%d",&key);
        str[i]=str[i]-key;
    }
    printf("the decrypted string is \" %s \"",str);
    fclose(fk);
}

void keyFile_decrypt_file(char *file_name,char *key_file_name)
{
  FILE *fs,*fd,*fk;
  char c;
  int key;
  fs=fopen(file_name,"r");
  fd=fopen("dest.txt","w");
  fk=fopen(key_file_name,"r");

  if(fk==NULL || fs==NULL || fd==NULL )
  {
    printf("ERROR:unable to perform file handling operations!, exiting....");
    exit(0);
  }

  do {
          c=fgetc(fs);

          if(feof(fs))
            break;

          key=fscanf(fk,"%d",&key);

          c=c-key;
          fputc(c,fd);


  } while(1);

  fclose(fs);
  fclose(fd);
  fclose(fk);
  remove(file_name);
  rename("dest.txt",file_name);

  printf("the file is successfully decrypted!");
  
}



void keyFile_encry(int object_type)
{
  int i,j;
  char str[MAX_LIMIT],file_name[MAX_LIMIT];
  switch(object_type)
  {
    case 1:
          printf("please enter a string of length atmost 1024 characters\nINPUT: ");
          fgets(str,MAX_LIMIT-1,stdin);
          keyFile_encrypt_string(str);
          printf("tne encrypted string is:\' %s \'",str);

    case 2:
            printf("please enter a absolute path of file that is to be encrypted\nINPUT: ");
            fgets(file_name,MAX_LIMIT-1,stdin);
            keyFile_encrypt_file(file_name);


  }
}

void keyFile_decry(int object_type)
{

    char key_file_name[11],str[MAX_LIMIT],file_name[MAX_LIMIT];


    switch(object_type)
    {
      case 1:
            printf("Enter the string that is to be decrypted \nINPUT: ");
            fgets(str,MAX_LIMIT-1,stdin);
            printf("Enter absolute path to keyFile that is used encrypt the given encrypted string\nINPUT:  ");
            fgets(key_file_name,10,stdin);
            keyFile_decrypt_string(str,key_file_name);
            printf("the decrypted string is : \" %s \" ",str);
     case 2:
            printf("Enter the absolute path of the file that is to be decrypted\nINPUT: ");
            fgets(file_name,MAX_LIMIT-1,stdin);
            printf("Enter absolute path to keyFile that is used encrypt the given encrypted file\nINPUT:  ");
            fgets(key_file_name,10,stdin);
            keyFile_decrypt_file(file_name,key_file_name);

    }
}

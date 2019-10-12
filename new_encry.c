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
{   fflush(stdin);
    FILE *fk,*fw;
    char key_file_name[11],string_file_name[18];
    char temp[]={"_string"};
    int i,j,random;
    for(i=0;i<10;i++)
    {
      key_file_name[i]='A'+randNumber(0,25);
    }
    strcpy(string_file_name,key_file_name);
    for(i=0;i<strlen(temp);i++)
    {
      string_file_name[i+10]=temp[i];
    }
    fk=fopen(key_file_name,"w");//opening a file with random randNumber
    if(fk==NULL)
    {
      printf("ERROR:unable to perform file hnadling operations!! exiting......\n");
      exit(0);
    }

    for(i=0;i<strlen(str);i++)
    {
      random=randNumber(1,25);
      str[i]=str[i]+random;
      fprintf(fk, "%d ",random );
    }
    // writting the string into a file.
    fw=fopen(string_file_name,"w");
    fputs(str,fw);
    fclose(fk);
    fclose(fw);
    printf("\n the key used to encrypt is strored in file named \" %s \" in the current directory\n",key_file_name);
    printf("the encrypted string is stored in the file named \"%s\"\n",string_file_name);
}


void keyFile_encrypt_file(char *file_name)
{     fflush(stdin);
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
            random=randNumber(1,25);
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
{   fflush(stdin);
    FILE *fk=fopen(key_file_name,"r");
    char c;
    int i,key;

    if(fk==NULL)
    {
      printf("ERROR:unable to perform file handling operations!, exiting....\n");
      exit(0);
    }


    for(i=0;i<strlen(str);i++)
    {
        fscanf(fk,"%d",&key);
        str[i]=str[i]-key;
    }
    printf("the decrypted string is \" %s \"\n",str);
    fclose(fk);
}

void keyFile_decrypt_file(char *file_name,char *key_file_name)
{ fflush(stdin);
  FILE *fs,*fd,*fk;
  char c;
  int key;
  fs=fopen(file_name,"r");
  fd=fopen("dest.txt","w");
  fk=fopen(key_file_name,"r");

  if(fk==NULL || fs==NULL || fd==NULL )
  {
    printf("ERROR:unable to perform file handling operations!, exiting....\n");
    exit(0);
  }

  do {
          c=fgetc(fs);

          if(feof(fs))
            break;

          fscanf(fk,"%d",&key);
          // printf("key= %d\n",key);
          c=c-key;
          fputc(c,fd);


  } while(1);

  fclose(fs);
  fclose(fd);
  fclose(fk);
  remove(file_name);
  rename("dest.txt",file_name);

  printf("the file is successfully decrypted!\n");

}



void keyFile_encry(int object_type)
{
  int i,j;
  char str[MAX_LIMIT],file_name[MAX_LIMIT];
  fflush(stdin);
  switch(object_type)
  {
    case 1:
          printf("please enter a string of length atmost 1024 characters\nINPUT: ");
          fgets(str,MAX_LIMIT-1,stdin);
          str[strlen(str)-1]='\0'; //to remove '\n' at the end of the string
          keyFile_encrypt_string(str);
          printf("tne encrypted string is:\' %s \'",str);
          break;

    case 2:
            printf("please enter a absolute path of file that is to be encrypted\nINPUT: ");
            fgets(file_name,MAX_LIMIT-1,stdin);
            file_name[strlen(file_name)-1]='\0'; // to remove the '\n' at the end
            keyFile_encrypt_file(file_name);
            break;


  }
}

void keyFile_decry(int object_type)
{
    fflush(stdin);
    char key_file_name[12],str[MAX_LIMIT],file_name[MAX_LIMIT];


    switch(object_type)
    {
      case 1:
            printf("Enter the string that is to be decrypted \nINPUT: ");
            fgets(str,MAX_LIMIT-1,stdin);
            str[strlen(str)-1]='\0';
            printf("Enter absolute path to keyFile that is used encrypt the given encrypted string\nINPUT:  ");
            fgets(key_file_name,12,stdin);
            key_file_name[strlen(key_file_name)-1]='\0'; // to remove the '\n' at the end
            printf("key_file_name: %s \n",key_file_name);
            keyFile_decrypt_string(str,key_file_name);
            printf("the decrypted string is : \" %s \" ",str);
            break;
     case 2:
            printf("Enter the absolute path of the file that is to be decrypted\nINPUT: ");
            fgets(file_name,MAX_LIMIT-1,stdin);
            file_name[strlen(file_name)-1]='\0'; // to remove the '\n' at the end
            printf("Enter absolute path to keyFile that is used encrypt the given encrypted file\nINPUT:  ");
            fgets(key_file_name,12,stdin);
            key_file_name[strlen(key_file_name)-1]='\0'; // to remove the '\n' at the end
            printf("key_file_name: %s \n",key_file_name);
            keyFile_decrypt_file(file_name,key_file_name);
            break;

    }
}

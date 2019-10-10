#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LIMIT 1024
void shuffle(char *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          char t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
void ma_encrypt_string(char *str,char *encryption_key)
{
  int i;
  for(i=0;i<strlen(str);i++)
  {
    if(str[i]>='a' && str[i]<='Z')
    {
      str[i]=encryption_key[str[i]-'a'];
    }
    else if(str[i]>='A' && str[i]<='Z')
    {
      str[i]=encryption_key[str[i]-'A'];
    }

  }
}

void ma_cipher_encrypt(int object_type)
{ char str[MAX_LIMIT];
  char file_name[MAX_LIMIT];
  char encryption_key[26];
  char buffer[1025];
  FILE *fs,*fd;

  int i,j;
  for(i=0;i<26;i++)
  {
    encryption_key[i]='A'+i;
  }
  shuffle(encryption_key,26);// this is being done to generate random encryption key for each and every user.

  switch(object_type)
  {
    case 1:
          printf("please enter a string within 1024 characters: \nINPUT:");
          fgets(str,MAX_LIMIT-1,stdin);
          ma_encrypt_string(str,encryption_key);
          printf("The encrypted string is : %s",str);
          printf("use this \'%s\' key to decrypt the string",encryption_key);

    case 2:
          printf("please enter a path(absolute) to required file:\nINPUT: ");
          fgets(file_name,MAX_LIMIT,stdin);
          fs=fopen(file_name,'r');
          fd=fopen("dest.txt",'w');
          if(fd==NULL || fs==NULL)
          {
            printf("ERROR:unable to do file handling!!");
            exit(0);
          }
          else
          {
            while(fgets(buffer,1024,fs)!=NULL)
            {
              ma_encrypt_string(buffer,encryption_key);
              fputs(buffer,fd);
            }
            fclose(fs);
            fclose(fd);
            remove(file_name);
            rename("dest.txt",file_name);
          }

  }
}

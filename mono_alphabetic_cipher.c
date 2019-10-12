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
{ //printf("check1");
  int i;
  for(i=0;i<strlen(str);i++)
  {
    if(str[i]>='a' && str[i]<='z')
    { //printf("check3");
      str[i]=encryption_key[str[i]-'a'];
    }
    else if(str[i]>='A' && str[i]<='Z')
    {
      str[i]=encryption_key[str[i]-'A'];
    }
    

  }
  //printf("check2");
  //printf("**%s**",str);
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
fflush(stdin);
  switch(object_type)
  {
    case 1:
          printf("please enter a string within 1024 characters: \nINPUT:");
          fgets(str,MAX_LIMIT-1,stdin);
          // printf("len=%d\n",strlen(str));
          str[strlen(str)-1]='\0';//to remove '\n' at last 
          ma_encrypt_string(str,encryption_key);
          printf("The encrypted string is : \"%s\" \n",str);
          printf("use this \'%s\' key to decrypt the string",encryption_key);
          break;

    case 2:
          printf("please enter a path(absolute) to required file:\nINPUT: ");
          fgets(file_name,MAX_LIMIT,stdin);
          file_name[strlen(file_name)-1]='\0'; //to remove '\n' at last
          // printf("file_name= %s",file_name);
          fs=fopen(file_name,"r");
          fd=fopen("dest.txt","w");
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
            printf("successfully encrypted the file!\n");
            printf("use this \'%s\' key to decrypt the file\n",encryption_key);
          }
          break;

  }
}

  void ma_decrypt_string(char *buffer,char *decryption_key)
{   int i;
    for(i=0;i<strlen(buffer);i++)
    {
        if(buffer[i]>='A' && buffer[i]<='Z')
        {
          buffer[i]=decryption_key[buffer[i]-'A'];
        }
    }
}

void ma_cipher_decrypt(int object_type)
{ char encryption_key[26];
  char decryption_key[26],str[MAX_LIMIT],file_name[MAX_LIMIT],buffer[1025];
  int i,idx;
  FILE *fs,*fd;

  printf("please enter the encryption key that used for encryption\nINPUT: ");
  scanf("%s",encryption_key);
  getchar();// to clear the buffer(stdin)
  for(i=0;i<26;i++)
  {
    idx=encryption_key[i]-'A';
    decryption_key[idx]='a'+i;
  }
  switch(object_type)
  {
    case 1:
            printf("please enter the encrypted string to decrypt! \n INPUT: ");
            fgets(str,MAX_LIMIT-1,stdin);
            str[strlen(str)-1]='\0'; //to remove '\n' at last
            ma_decrypt_string(str,decryption_key);
            printf("the decrypted string is :\"%s\"\n",str);
            break;
    case 2:
            printf("please enter the file name that is to decrypted\nINPUT: ");
            fgets(file_name,MAX_LIMIT-1,stdin);
            file_name[strlen(file_name)-1]='\0'; //to remove '\n' at last
            printf("file_name= %s\n",file_name);
            fs=fopen(file_name,"r");
            fd=fopen("dest.txt","w");
            if(fs==NULL || fd==NULL)
            {
              printf("ERROR:unable to perform file handling!!\n");
              exit(0);
            }
            while(fgets(buffer,1024,fs)!=NULL)
            {
              ma_decrypt_string(buffer,decryption_key);
              fputs(buffer,fd);
            }
            fclose(fs);
            fclose(fd);
            remove(file_name);
            rename("dest.txt",file_name);
            printf("successfully decrypted the file!\n\n");
            break;

  }

}

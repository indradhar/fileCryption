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
  FILE *fs,*fd;
  
}





void keyFile_encry(int object_type)
{
  FILE *fs,*fd;
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

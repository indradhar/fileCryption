#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <string.h>

void handleErrors(void);
void aesFileE(char* nam);
void aesFileD(char *nam);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *aad,
            int aad_len, unsigned char *key, unsigned char *iv,
            unsigned char *ciphertext, unsigned char *tag);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *aad,
            int aad_len, unsigned char *tag, unsigned char *key, unsigned char *iv,
            unsigned char *plaintext);

void aesStringEnc(char *str) {
	    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();     

    /* Set up the key and iv. Do I need to say to not hard code these in a real application? :-) */

    /* A 256 bit key */
	time_t t;
	srand((unsigned) time(&t));

    //static unsigned char key[] = "01234567890123456789012345678901";
	static unsigned char key[32];
	printf("Key:");
	for(int c1c=0;c1c<32;c1c++) {
		int tmp;
		key[c1c]=tmp=(char)((char)(rand()%10)+'0');
		printf("%c",tmp);
	}
	printf("\n");
    /* A 128 bit IV */
    //static unsigned char iv[] = "0123456789012345";
   	static unsigned char iv[16];
	printf("iv:");
	for(int c1c=0;c1c<16;c1c++) {
		int tmp;
		iv[c1c]=tmp=(char)((char)(rand()%10)+'0');
		printf("%c",tmp);
	}
	printf("\n");
    /* Message to be encrypted */
    unsigned char plaintext[strlen(str)];
for(int i=0;i<strlen(str);i++) {
	plaintext[i]=str[i];
}

    /* Some additional data to be authenticated */
    static unsigned char aad[] = "AAD-data";

    /* Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, dependant on the
     * algorithm and mode
     */
    unsigned char ciphertext[2048];

    /* Buffer for the decrypted text */
    unsigned char decryptedtext[2048];

    /* Buffer for the tag */
    unsigned char tag[16];

    int decryptedtext_len = 0, ciphertext_len = 0;

    /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, strlen(plaintext), aad, strlen(aad), key, iv, ciphertext, tag);

    /* Do something useful with the ciphertext here */
    printf("Ciphertext is:\n");
    BIO_dump_fp(stdout, ciphertext, ciphertext_len);
	
    printf("Tag is:\n");
    BIO_dump_fp(stdout, tag, 16);

    /* Mess with stuff */
    /* ciphertext[0] ^= 1; */
    /* tag[0] ^= 1; */
FILE *f = fopen("data","wb");
printf("Also: tag and encrypted-text are saved in this directory in file named data.\n");
fwrite(tag,1,16,f);
fwrite(ciphertext,1,ciphertext_len,f);
fclose(f);
    // Decrypt the ciphertext 
//printf(">>%s<<>>%d %s %ld<<>>%s<<>>%s<<>>%s<<\n",ciphertext, ciphertext_len, aad, strlen(aad), tag, key, iv);
   /* decryptedtext_len = decrypt(ciphertext, ciphertext_len, aad, strlen(aad), tag, key, iv, decryptedtext);

    if(decryptedtext_len < 0)
    {
        
        printf("Decrypted text failed to verify\n");
    }
    else
    {
        
        decryptedtext[decryptedtext_len] = '\0';

        
        printf("Decrypted text is:\n");
        printf("%s\n", decryptedtext);
    }
*/
    
    ERR_free_strings();

}

void aesStringDec(char *str, char *ke, char *iiv) {
	    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();     

    /* Set up the key and iv. Do I need to say to not hard code these in a real application? :-) */


    //static unsigned char keya[] = "01234567890123456789012345678901";
	static unsigned char keya[32];
	//strcpy(keya, ke);
for(int i=0;i<32;i++) {
keya[i]=ke[i];
}
	//scanf("%s",keya);
	/*static unsigned char key[32];
	//printf("Key:");
	for(int c1c=0;c1c<32;c1c++) {
key[c1c]=ke[c1c];
	}*/
	//printf("\n");
    /* A 128 bit IV */
    static unsigned char iva[16];// = "0123456789012345";
	//strcpy(iva, iiv);
for(int i=0;i<16;i++) {
iva[i]=iiv[i];
}
//printf("/ke1:%s/ke2:%s/iv1:%s/iv2:%s/",keya,ke,iva,iiv);
    /*static unsigned char iv[16];
	//printf("iv:");
	for(int c1c=0;c1c<16;c1c++) {
iv[c1c]=iiv[c1c];
	}*/ 
	//printf("\n");
    /* Message to be encrypted */

    /* Some additional data to be authenticated */
    static unsigned char aad2[] = "AAD-data";

    /* Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, dependant on the
     * algorithm and mode
     */
    unsigned char ciphertext[2048];

    /* Buffer for the decrypted text */
    unsigned char decryptedtext[2048];

    /* Buffer for the tag */
    unsigned char tag[16];

    int decryptedtext_len = 0, ciphertext_len = 0;


    /* Mess with stuff */
    /* ciphertext[0] ^= 1; */
    /* tag[0] ^= 1; */
FILE *f = fopen(str,"rb");
//printf("Also: tag and encrypted-text are saved in this directory in file named data.\n");
fseek(f, 0, SEEK_END);
int sz = ftell(f);
fseek(f, 0, SEEK_SET);
fread(tag,1,16,f);
//printf("\n%s\n",tag);
fread(ciphertext,1,sz-16,f);
//printf("\n%s\n",ciphertext);
fclose(f);
/*FILE *fr = fopen("hell","wb");
fwrite(tag,1,16,fr);
fwrite(ciphertext,1,sz-16,fr);
fclose(fr);
*/
    // Decrypt the ciphertext 
//printf(">>%s<<>>%d %s %ld %s %s %s<<\n",ciphertext, sz-16, aad2, strlen(aad2), tag, keya, iva);
    decryptedtext_len = decrypt(ciphertext, sz-16, aad2, strlen(aad2), tag, keya, iva, decryptedtext);

    if(decryptedtext_len < 0)
    {
        /* Verify error */
        printf("Decrypted text failed to verify\n");
    }
    else
    {
        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        printf("Decrypted text is:\n");
        printf("%s\n", decryptedtext);
    }

    /* Remove error strings */
    ERR_free_strings();

}


//int main(int arc, char *argv[])
//{
	//char st1[1024],keyb[33],ivb[17],keyd[32],ivd[16];
	//scanf("%s",st1);
	//aesStringEnc(st1);
   	//scanf("%s",keyb);
   	//scanf("%s",ivb);
	//for(int i=0;i<32;i++) {
	//keyd[i]=keyb[i];
	//}
	//for(int i=0;i<16;i++) {
	//ivd[i]=ivb[i];
	//}
	//aesStringDec("data",keyd,ivd);
	//aesFileE("t4");
	//aesFileD("TEMF");
    //return 0;
//}

void handleErrors(void)
{
    unsigned long errCode;

    printf("An error occurred\n");
    while(errCode = ERR_get_error())
    {
        char *err = ERR_error_string(errCode, NULL);
        printf("%s\n", err);
    }
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *aad,
            int aad_len, unsigned char *key, unsigned char *iv,
            unsigned char *ciphertext, unsigned char *tag)
{
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, ciphertext_len = 0;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the encryption operation. */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        handleErrors();

    /* Set IV length if default 12 bytes (96 bits) is not appropriate */
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 16, NULL))
        handleErrors();

    /* Initialise key and IV */
    if(1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

    /* Provide any AAD data. This can be called zero or more times as
     * required
     */
    if(aad && aad_len > 0)
    {
        if(1 != EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_len))
            handleErrors();
    }

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(plaintext)
    {
        if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
            handleErrors();

        ciphertext_len = len;
    }

    /* Finalise the encryption. Normally ciphertext bytes may be written at
     * this stage, but this does not occur in GCM mode
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    /* Get the tag */
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag))
        handleErrors();

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *aad,
            int aad_len, unsigned char *tag, unsigned char *key, unsigned char *iv,
            unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, plaintext_len = 0, ret;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    /* Initialise the decryption operation. */
    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        handleErrors();

    /* Set IV length. Not necessary if this is 12 bytes (96 bits) */
    if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 16, NULL))
        handleErrors();

    /* Initialise key and IV */
    if(!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

    /* Provide any AAD data. This can be called zero or more times as
     * required
     */
    if(aad && aad_len > 0)
    {
        if(!EVP_DecryptUpdate(ctx, NULL, &len, aad, aad_len))
            handleErrors();
    }

    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if(ciphertext)
    {
        if(!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
            handleErrors();

        plaintext_len = len;
    }

    /* Set expected tag value. Works in OpenSSL 1.0.1d and later */
    if(!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag))
        handleErrors();

    /* Finalise the decryption. A positive return value indicates success,
     * anything else is a failure - the plaintext is not trustworthy.
     */
    ret = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    if(ret > 0)
    {
        /* Success */
        plaintext_len += len;
        return plaintext_len;
    }
    else
    {
        /* Verify failed */
        return -1;
    }
}
void aesFileE(char *nam) {
	
	OpenSSL_add_all_algorithms();
    	ERR_load_crypto_strings();
	time_t t;
	srand((unsigned) time(&t));

    //static unsigned char key[] = "01234567890123456789012345678901";
	static unsigned char key[32];
	printf("Key:");
	for(int c1c=0;c1c<32;c1c++) {
		int tmp;
		key[c1c]=tmp=(char)((char)(rand()%10)+'0');
		printf("%c",tmp);
	}
	printf("\n");
    /* A 128 bit IV */
    //static unsigned char iv[] = "0123456789012345";
   	static unsigned char iv[16];
	printf("iv:");
	for(int c1c=0;c1c<16;c1c++) {
		int tmp;
		iv[c1c]=tmp=(char)((char)(rand()%10)+'0');
		printf("%c",tmp);
	}
	printf("\n");

    /* Message to be encrypted */
    unsigned char plaintext[128];
//for(int i=0;i<strlen(str);i++) {
//	plaintext[i]=str[i];
//}

    /* Some additional data to be authenticated */
    static unsigned char aad[] = "AAD-data";

    /* Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, dependant on the
     * algorithm and mode
     */


    /* Buffer for the decrypted text */
    unsigned char decryptedtext[2048];



    int decryptedtext_len = 0;
FILE *f = fopen(nam,"rb");
FILE *fr = fopen("TEMF","wb");
fseek(f, 0, SEEK_END);
int sz = ftell(f);
printf("ptsz:%d\n",sz);
int nte=sz%128,ntf=sz/128;
fseek(f, 0, SEEK_SET);
while(ntf>0) {
	fread(plaintext,1,128,f);
    unsigned char ciphertext[2048];
     int ciphertext_len = 0;
    /* Buffer for the tag */
    unsigned char tag[16];
    /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, 128, aad, strlen(aad), key, iv, ciphertext, tag);
fwrite(tag,1,16,fr);
fwrite(ciphertext,1,ciphertext_len,fr);
ntf--;
}
if(nte>0) {
fread(plaintext,1,nte,f);
unsigned char ciphertext[2048];
     int ciphertext_len = 0;
    /* Buffer for the tag */
    unsigned char tag[16];
    /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, nte, aad, strlen(aad), key, iv, ciphertext, tag);
fwrite(tag,1,16,fr);
fwrite(ciphertext,1,ciphertext_len,fr);
}

fclose(f);
fclose(fr);
remove(nam);
rename("TEMF",nam);

    /* Do something useful with the ciphertext here */
    //printf("Ciphertext is:\n");
    //BIO_dump_fp(stdout, ciphertext, ciphertext_len);
	
    //printf("Tag is:\n");
    //BIO_dump_fp(stdout, tag, 16);
 
    
    ERR_free_strings();

}
void aesFileD(char *nam) {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();     

	char keyf[33],ivf[17];
    
	static unsigned char keye[32];
	printf("Please enter key:");
	scanf("%s",keyf);
for(int i=0;i<32;i++) {
keye[i]=keyf[i];
}

    /* A 128 bit IV */
    static unsigned char ive[16];
	printf("Please enter iv:");
	scanf("%s",ivf);	
for(int i=0;i<16;i++) {
ive[i]=ivf[i];
}

   
    /* Some additional data to be authenticated */
    static unsigned char aad2[] = "AAD-data";

    /* Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, dependant on the
     * algorithm and mode
     */
    unsigned char ciphertext[2048];

    /* Buffer for the decrypted text */


    /* Buffer for the tag */
    unsigned char tag[16];

    int ciphertext_len = 128;


    /* Mess with stuff */
    /* ciphertext[0] ^= 1; */
    /* tag[0] ^= 1; */

FILE *f = fopen(nam,"rb");
FILE *fr = fopen("DECT","wb");

fseek(f, 0, SEEK_END);
int sze = ftell(f);
int ntes=sze%(128+16);
//printf("byt:%d\n",sze);
fseek(f, 0, SEEK_SET);
int vasd=0;
while((fread(tag,1,16,f)>0)&&vasd<(sze/(128+16))) {
fread(ciphertext,1,128,f);
int decryptedtext_len = 0;
    unsigned char decryptedtext[2048];
    // Decrypt the ciphertext 
//printf(">>%s<<>>%d %s %ld %s %s %s<<\n",ciphertext, sz-16, aad2, strlen(aad2), tag, keya, iva);
    decryptedtext_len = decrypt(ciphertext, 128, aad2, strlen(aad2), tag, keyf, ivf, decryptedtext);
fwrite(decryptedtext,1,128,fr);
    if(decryptedtext_len < 0)
    {
        /* Verify error */
        printf("Decrypted text failed to verify\n");
    }
    else
    {
        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        printf("Decrypted text is:\n");
        printf("%s\n", decryptedtext);
    }
vasd++;
}
if(ntes!=0) {
//printf("ntes-16:%d\n",ntes-16);
//fread(tag,1,16,f); ALREADY READ
fread(ciphertext,1,ntes,f);
int decryptedtext_len = 0;
    unsigned char decryptedtext[2048];
    // Decrypt the ciphertext 
//printf(">>%s<<>>%d %s %ld %s %s %s<<\n",ciphertext, sz-16, aad2, strlen(aad2), tag, keya, iva);
    decryptedtext_len = decrypt(ciphertext,ntes-16, aad2, strlen(aad2), tag, keyf, ivf, decryptedtext);
fwrite(decryptedtext,1,ntes-16,fr);
    if(decryptedtext_len < 0)
    {
        /* Verify error */
        printf("Decrypted text failed to verify\n");
    }
    else
    {
        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        //printf("Decrypted text is:\n");
        //printf("%s\n", decryptedtext);
    }

}
fclose(f);
fclose(fr);
remove(nam);
rename("DECT",nam);
    /* Remove error strings */
    ERR_free_strings();



}


void stringHash(char *string);
void getFileHash(char *fileName);
void shuffle(char *array, size_t n);
void ma_encrypt_string(char *str,char *encryption_key);
void ma_cipher_encrypt(int object_type);
void ma_decrypt_string(char *buffer,char *decryption_key);
void ma_cipher_decrypt(int object_type);
int randNumber(int lower,int upper);
void keyFile_encrypt_string(char *str);
void keyFile_encrypt_file(char *file_name);
void keyFile_decrypt_string(char *str,char *key_file_name);
void keyFile_decrypt_file(char *file_name,char *key_file_name);
void keyFile_encry(int object_type);
void keyFile_decry(int object_type);
void aesStringEnc(char *str);
void aesStringDec(char *str, char *ke, char *iiv);
void aesFileE(char* nam);
void aesFileD(char *nam);

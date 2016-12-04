#include "allivault-api.h"

#include <string.h>

#include <stdio.h>
#include <iostream>
#include <chrono>

#include <boost/filesystem.hpp>
#include "cppconn/sqlstring.h"

#include "ALLIVaultCoreP/ALLIVaultCoreP.h"
#include "ALLIVaultCoreP/ALLIUserAccount.h"
#include "ALLIVaultCoreP/ALLIAppInit.h"

#include "openssl/aes.h"

#include "openssl/evp.h"

#include "libssh2/libssh2.h"
#include "git2/common.h"

#include "ALLIVaultCoreP/ALLINewUserP.h"
#include "ALLIVaultCoreP/ALLIUtilsP.h"
#include <android/log.h>

static boost::filesystem::path *homePath, pub_key_path;

static std::string repo_path(const std::string &host, const std::string &path) {
  return std::string("ssh://") + host + path;
}



JNIEXPORT jstring JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_getMessage(JNIEnv* env,
                                                                jobject thiz ) {
#define ABI "unknown"
  return env->NewStringUTF("Hello from JNI ! Compiled with ABI " ABI ".");
}

JNIEXPORT jstring JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_getLibGit2Version
        (JNIEnv *env, jclass cls) {
  int major, minor, rev;
  major = 1;
  minor = 2;
  rev = 3;
  git_libgit2_version(&major, &minor, &rev);
  allivault_core_version(&major, &minor, &rev);
  const char *ver = libssh2_version(0);
  boost::filesystem::path pc = "/efg/uvw";
  pc.string();
  boost::filesystem::path pd =  boost::filesystem::path(pc);
  pd.empty();
  pc /= pd;

  homePath = new boost::filesystem::path("abc");
  homePath->native();
  //ALLIVaultCore::Helpers::ALLIAppInit::appInitialize(*homePath);

  std::string (*uni_fn_ptr)(const std::string &, const std::string &);
  uni_fn_ptr = &repo_path;
  //ALLIVaultCore::FrontEnd::ALLINewUserP *userNewP = new ALLIVaultCore::FrontEnd::ALLINewUserP(uni_fn_ptr);
  const boost::filesystem::path *homeDir = ALLIVaultCore::Helpers::ALLIUtilsP::getHomeFolderPath();
  const char *homeDir_ch = ALLIVaultCore::Helpers::ALLIUtilsP::convertBoostPathToUTF8String(*homeDir).c_str();
  sql::SQLString sqlstr = "hello";

  char version[15];
  sprintf(version, "%d.%d.%d", major, minor, rev);

  // XXX: returning ssh2 version!
  return env->NewStringUTF(homeDir_ch);
}


// openssl demo code, https://github.com/saju/misc/blob/master/misc/openssl_aes.c
/**
 * Create an 256 bit key and IV using the supplied key_data. salt can be added for taste.
 * Fills in the encryption and decryption ctx objects and returns 0 on success
 **/
int aes_init(const unsigned char *key_data, int key_data_len, const unsigned char *salt, EVP_CIPHER_CTX *e_ctx,
             EVP_CIPHER_CTX *d_ctx)
{
  int i, nrounds = 5;
  unsigned char key[32], iv[32];

  /*
   * Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
   * nrounds is the number of times the we hash the material. More rounds are more secure but
   * slower.
   */
  i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
  if (i != 32) {
    printf("Key size is %d bits - should be 256 bits\n", i);
    return -1;
  }

  EVP_CIPHER_CTX_init(e_ctx);
  EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
  EVP_CIPHER_CTX_init(d_ctx);
  EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);

  return 0;
}

/*
 * Encrypt *len bytes of data
 * All data going in & out is considered binary (unsigned char[])
 */
unsigned char *aes_encrypt(EVP_CIPHER_CTX *e, unsigned char *plaintext, int *len)
{
  /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
  int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
  unsigned char *ciphertext = (unsigned char *)malloc(c_len);

  /* allows reusing of 'e' for multiple encryption cycles */
  EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL);

  /* update ciphertext, c_len is filled with the length of ciphertext generated,
    *len is the size of plaintext in bytes */
  EVP_EncryptUpdate(e, ciphertext, &c_len, plaintext, *len);

  /* update ciphertext with the final remaining bytes */
  EVP_EncryptFinal_ex(e, ciphertext+c_len, &f_len);

  *len = c_len + f_len;
  return ciphertext;
}

/*
 * Decrypt *len bytes of ciphertext
 */
unsigned char *aes_decrypt(EVP_CIPHER_CTX *e, unsigned char *ciphertext, int *len)
{
  /* plaintext will always be equal to or lesser than length of ciphertext*/
  int p_len = *len, f_len = 0;
  unsigned char *plaintext = (unsigned char *)malloc(p_len);

  EVP_DecryptInit_ex(e, NULL, NULL, NULL, NULL);
  EVP_DecryptUpdate(e, plaintext, &p_len, ciphertext, *len);
  EVP_DecryptFinal_ex(e, plaintext+p_len, &f_len);

  *len = p_len + f_len;
  return plaintext;
}


/*
 * Class:     com_allivault_cloudsafe_playground_Apis
 * Method:    aesEncrypt
 * Signature: ([BI)[B
 */
JNIEXPORT jbyteArray JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_aesEncrypt(JNIEnv *env, jclass cls,
                                                                jbyteArray input, jint xxlen) {

  int length = env->GetArrayLength(input);
  unsigned char* buf = (unsigned char *)malloc(length);
  reinterpret_cast<jbyte*>(buf);

  env->GetByteArrayRegion(input, 0, length, reinterpret_cast<jbyte*>(buf));

  // encrypt the input data
  int len = length;
  EVP_CIPHER_CTX en, de;
  unsigned int salt[] = {12345, 54321};
  unsigned char password [] = "This is my string";
  unsigned char const *key_data = &password[0];
  int key_data_len = 7;
  /* gen key and iv. init the cipher ctx object */
  if (aes_init(key_data, key_data_len, (const unsigned char *)&salt, &en, &de)) {
    free(buf);
    return env->NewByteArray(0);
  }

  unsigned char *ciphertext;
  ciphertext = aes_encrypt(&en, buf, &len);
  jbyteArray array = env->NewByteArray(len);
  env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(ciphertext));

  free(buf);
  free(ciphertext);
  return array;
}

/*
 * Class:     com_allivault_cloudsafe_playground_Apis
 * Method:    aesDecrypt
 * Signature: ([BI)[B
 */
JNIEXPORT jbyteArray JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_aesDecrypt(JNIEnv *env, jclass cls,
                                                                jbyteArray input, jint xxlen) {
  int length = env->GetArrayLength (input);
  unsigned char* buf = (unsigned char *)malloc(length);
  env->GetByteArrayRegion(input, 0, length, reinterpret_cast<jbyte*>(buf));

  EVP_CIPHER_CTX en, de;
  unsigned int salt[] = {12345, 54321};
  unsigned char myString [] = "This is my string";
  unsigned char const *key_data = &myString[0];
  int key_data_len = 7;

  // decryption
  int len = length;
  /* gen key and iv. init the cipher ctx object */
  if (aes_init(key_data, key_data_len, (const unsigned char *)&salt, &en, &de)) {
    free(buf);
    return env->NewByteArray(0);
  }

  __android_log_print(ANDROID_LOG_INFO, "Apis", "before decrypt: %d", len);
  char *plaintext;
  plaintext = (char *)aes_decrypt(&de, buf, &len);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "after decrypt: %d: %s", len, plaintext);

  jbyteArray array = env->NewByteArray(len);
  env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(plaintext));

  free(buf);
  free(plaintext);
  return array;
}

JNIEXPORT jboolean JNICALL
        Java_com_allivault_cloudsafe_playground_AllivaultApi_createRSAKeyPair(JNIEnv *env, jclass cls,
                                                                        jstring uname) {
  const char *userName = env->GetStringUTFChars(uname, 0);
  ALLIVaultCore::FrontEnd::ALLINewUserP *alliNewUserP = new ALLIVaultCore::FrontEnd::ALLINewUserP(&repo_path);
  std::string uname_utf8(userName);
  boost::filesystem::path pubKeyPath;
  bool ret = alliNewUserP->createRSAKeyPair(uname_utf8, pubKeyPath);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "calling createRSAKeyPair, and the result is %d, the public key path is %s",
  ret, pubKeyPath.string().c_str());
  pub_key_path = pubKeyPath;
}

JNIEXPORT jboolean JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_createUserAccountOnServer(JNIEnv *env,
                                                                               jclass type,
                                                                               jstring userName_,
                                                                               jstring passWord_,
                                                                               jstring fullName_,
                                                                               jstring emailAddress_,
                                                                               jstring publicKeyFile_,
                                                                               jlong curTime,
                                                                               jlong expirationTime,
                                                                               jlong quotaSize) {
  const char *userName = env->GetStringUTFChars(userName_, 0);
  const char *passWord = env->GetStringUTFChars(passWord_, 0);
  const char *fullName = env->GetStringUTFChars(fullName_, 0);
  const char *emailAddress = env->GetStringUTFChars(emailAddress_, 0);
  const char *publicKeyFile = env->GetStringUTFChars(publicKeyFile_, 0);

  // TODO

  env->ReleaseStringUTFChars(userName_, userName);
  env->ReleaseStringUTFChars(passWord_, passWord);
  env->ReleaseStringUTFChars(fullName_, fullName);
  env->ReleaseStringUTFChars(emailAddress_, emailAddress);
  env->ReleaseStringUTFChars(publicKeyFile_, publicKeyFile);

  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>createUserAccountOnServer");
  ALLIVaultCore::Helpers::ALLIUserAccount account;
  account.set_userName(std::string(userName));
  account.set_passwdSha1(passWord);
  account.set_fullName(fullName);
  const std::string e("hello");
  account.set_emailAddress("abc");
  account.set_publicKeyFile(boost::filesystem::path(pub_key_path));

  std::chrono::time_point<std::chrono::system_clock> td = std::chrono::system_clock::from_time_t(curTime);
  account.set_today(td);
  account.set_expiration(td);
  account.set_quotaSize(quotaSize);

  ALLIVaultCore::FrontEnd::ALLINewUserP *alliNewUserP = new ALLIVaultCore::FrontEnd::ALLINewUserP(&repo_path);
//  alliNewUserP->processNewUser("a-user");

  bool ret = alliNewUserP->createUserAccount(account);

  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>createUserAccountOnServer returns %d", ret);
  return ret;
}

JNIEXPORT void JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_processNewUser(JNIEnv *env, jclass type,
                                                                    jstring userName_) {
  const char *userName = env->GetStringUTFChars(userName_, 0);

  // TODO

  env->ReleaseStringUTFChars(userName_, userName);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>processNewUser");
}

JNIEXPORT void JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_appInitialize(JNIEnv *env, jclass type,
                                                                    jstring rootPath) {
  const char *rp = env->GetStringUTFChars(rootPath, 0);
  boost::filesystem::path rootDir(rp);
  ALLIVaultCore::Helpers::ALLIAppInit::appInitialize(rootDir);
}

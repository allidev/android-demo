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
#include "ALLIVaultCoreP/ALLINewMachineP.h"
#include "ALLIVaultCoreP/ALLIReachabilityP.h"
#include "ALLIVaultCoreP/ALLIPublicKeyPairP.h"
#include "ALLIVaultCoreP/ALLIExistingUserP.h"
#include "ALLIVaultCoreP/ALLINewMachineStateP.h"
#include "ALLIVaultCoreP/ALLIUtilsP.h"
#include "ALLIVaultCoreP/ALLIEXTSecPlainFolderP.h"
#include "ALLIVaultCoreP/ALLIEXTSecMBPlainFolderP.h"
#include "ALLIVaultCoreP/AliyunOssP.h"
#include "ALLIVaultCoreP/ALLIFolderIndex.h"
#include "ALLIVaultCoreP/new_machine_event_args.h"
#include "ALLIVaultCoreP/ALLINewMachineProgressStatusP.h"
#include "ALLIVaultCoreP/ALLISharingGroupBaseP.h"
#include "ALLIVaultCorep/ALLIEXTSharingPlainFolderP.h"
#include <android/log.h>
#include <cpprest/http_client.h>

static boost::filesystem::path *homePath, pub_key_path;

static std::string repo_path(const std::string &path, const std::string &host) {
  return std::string("ssh://") + host + path;
}


JavaVM *g_vm;
// cached refs for later callbacks
jclass g_clazz_appStatusUpdated;
jmethodID g_mid_appStatusUpdated;


extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
  {
    return -1;
  }

  cpprest_init(vm);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "%s", "we just init cpprest.");
  g_vm = vm;
  return JNI_VERSION_1_6;
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
  __android_log_print(ANDROID_LOG_INFO, "Apis", "checking if public key exists, and the result is %d, the public key path is %s",
                      boost::filesystem::exists(pubKeyPath), pubKeyPath.string().c_str());
  boost::filesystem::path priKeyPath = pubKeyPath.parent_path();
  priKeyPath /= "test574_rsa.pem";
  __android_log_print(ANDROID_LOG_INFO, "Apis", "checking if private key exists, and the result is %d, the private key path is %s",
                      boost::filesystem::exists(priKeyPath), priKeyPath.string().c_str());
  pub_key_path = pubKeyPath;
  delete alliNewUserP;
  env->ReleaseStringUTFChars(uname, userName);
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
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>createUserAccountOnServer");
  ALLIVaultCore::Helpers::ALLIUserAccount account;
  std::string uname(userName);
  account.set_userName(uname);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>username is %s", userName);
  std::string passwdSha1;
  std::string passwd_utf8(passWord);
  bool ret = ALLIVaultCore::Helpers::ALLIUtilsP::getPasswordSha1(uname, passwd_utf8, passwdSha1);
  account.set_passwdSha1(passwdSha1);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>password is %s", passwdSha1.c_str());
  account.set_fullName(fullName);
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>fullname is %s", fullName);
  const std::string e("hello");
  std::string email(emailAddress);
  account.set_emailAddress(email);
  account.set_publicKeyFile(boost::filesystem::path(pub_key_path));

  ALLIVaultCore::FrontEnd::ALLINewUserP *alliNewUserP = new ALLIVaultCore::FrontEnd::ALLINewUserP(&repo_path);
//  alliNewUserP->processNewUser("a-user");

  ret = alliNewUserP->createUserAccount(account);

  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>createUserAccountOnServer returns %d", ret);
  delete alliNewUserP;

  env->ReleaseStringUTFChars(userName_, userName);
  env->ReleaseStringUTFChars(passWord_, passWord);
  env->ReleaseStringUTFChars(fullName_, fullName);
  env->ReleaseStringUTFChars(emailAddress_, emailAddress);
  env->ReleaseStringUTFChars(publicKeyFile_, publicKeyFile);

  return ret;
  //return false;
}

std::unique_ptr<ALLIVaultCore::FrontEnd::ALLIExistingUserP> existUser;

JNIEXPORT void JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_processNewUser(JNIEnv *env, jclass type,
                                                                    jstring userName_) {
  const char *userName = env->GetStringUTFChars(userName_, 0);

  // TODO
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>processNewUser");
  ALLIVaultCore::FrontEnd::ALLINewUserP *alliNewUserP = new ALLIVaultCore::FrontEnd::ALLINewUserP(&repo_path);
  std::string uname(userName);
  existUser = std::unique_ptr<ALLIVaultCore::FrontEnd::ALLIExistingUserP>(new ALLIVaultCore::FrontEnd::ALLIExistingUserP);
  alliNewUserP->setExistingUser(*existUser);
  alliNewUserP->processNewUser(uname);
  delete alliNewUserP;
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>processNewUser completed.");

  env->ReleaseStringUTFChars(userName_, userName);
}

static void machNewStatusUpdatedCallback(void *sender, ALLIVaultCore::FrontEnd::new_machine_event_args &args)
{
  std::string fu = args.filesUpdate;
  std::string su = args.statusUpdate;
  ALLIVaultCore::Helpers::ALLINMStatusP nms = args.nmstatus;
  __android_log_print(ANDROID_LOG_INFO, "Apis", "Files udpate is %s.\n", fu.c_str());
  __android_log_print(ANDROID_LOG_INFO, "Apis", "Status Update is %s.\n", su.c_str());
  __android_log_print(ANDROID_LOG_INFO, "Apis", "New machine status is %d.\n", nms);
}

void appStatusUpdatedCallback(void *sender, ALLIVaultCore::FrontEnd::exist_user_event_args &e)
{
  JNIEnv *g_env;
  // double check it's all ok
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
  if (getEnvStat == JNI_EDETACHED)
  {
    if (g_vm->AttachCurrentThread(&g_env, NULL) != 0)
    {
      __android_log_print(ANDROID_LOG_INFO, "Apis", "==>Failed to attach.\n");
      return;
    }
    __android_log_print(ANDROID_LOG_INFO, "Apis", "==>VM attached to current thread.\n");
  }
  else if (getEnvStat == JNI_EVERSION)
  {
    __android_log_print(ANDROID_LOG_INFO, "Apis", "==>Version not supported.\n");
    return;
  }

  g_env->CallStaticVoidMethod(g_clazz_appStatusUpdated, g_mid_appStatusUpdated);
  g_vm->DetachCurrentThread();
}

JNIEXPORT void JNICALL
        Java_com_allivault_cloudsafe_playground_AllivaultApi_batchActionsForNewMachine(JNIEnv *env, jclass type)
{
  // TODO
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>batchActionsForNewMachine started");
  std::unique_ptr<ALLIVaultCore::FrontEnd::ALLINewMachineP> machNew(new ALLIVaultCore::FrontEnd::ALLINewMachineP(
          nullptr));
  machNew->username = "test580";
  machNew->openServerRepositoryForEncryptedRepo();
  machNew->openServerRepositoryForMBEncryptedRepo();
  machNew->chkHost = &ALLIVaultCore::Engine::ALLIReachabilityP::currentReachabilityStatusS;
  std::unique_ptr<ALLIVaultCore::Helpers::ALLIPublicKeyPairP> keyPair{ new ALLIVaultCore::Helpers::ALLIPublicKeyPairP(machNew->username) };
  boost::filesystem::path currpath("/data/local/tmp");
  keyPair->importKeyPair(currpath);
  machNew->nmState = new ALLIVaultCore::Helpers::ALLINewMachineStateP();
  machNew->nmState->isNewMachineInSession = true;
  existUser = std::unique_ptr<ALLIVaultCore::FrontEnd::ALLIExistingUserP>{new ALLIVaultCore::FrontEnd::ALLIExistingUserP};
  existUser->connectAppStatusUpdated([](void *sender, ALLIVaultCore::FrontEnd::exist_user_event_args &e)
                                     {
                                         appStatusUpdatedCallback(sender, e);
                                     });
  machNew->setExistingUser(*existUser);
/*
  machNew->connectDownloadOneFileEx([=](const std::string &filePath, const boost::filesystem::path &localPath, void *)
                                    {
                                        ALLIVaultCore::Engine::AliyunOssP oss("xvault");
                                        return oss.downloadFile(filePath, localPath);
                                    });
*/
  boost::signals2::connection connMachNew = machNew->connectMachNewStatusUpdated(&machNewStatusUpdatedCallback);
  machNew->batchActionsForNewMachine();
  connMachNew.disconnect();
  ALLIVaultCore::ALLIEXTSecPlainFolderP *plainFolder = existUser->getPlainFolder();
  std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFolderIndex> list = plainFolder->getFolderContentList();
  for (const auto & rec : list)
  {
    std::string fpath = rec.first;
    ALLIVaultCore::Engine::ALLIFolderIndex meta = rec.second;
    std::string fullpath = meta.get_col2();
    unsigned long long fsize = meta.get_col6();
    time_t mtime = meta.get_col7();
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The file is %s, with %llu bytes.\n", fullpath.c_str(), fsize);
    std::string dest;
    //existUser.downloadOneFileForSyncFolder(fpath, dest);
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The dest file absolute path is %s.\n", dest.c_str());
  }
  std::string json = plainFolder->getFolderContentListJson();
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>The file list contains %s.", json.c_str());
//  existUser.deleteFileForSyncFolder("folder1/test2.txt");
//  existUser.renameFileForSyncFolder("ALLINewUserP.h", "ALLINewUserP-1.h");
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>Start to process mailbox folder.\n");
  ALLIVaultCore::ALLIEXTSecMBPlainFolderP *mbPlainFolder = existUser->getMBPlainFolder();
  list = mbPlainFolder->getFolderContentList();
  printf("The number of files is %lu.\n", list.size());
  for (const auto & rec : list)
  {
    std::string fpath = rec.first;
    ALLIVaultCore::Engine::ALLIFolderIndex meta = rec.second;
    std::string fullpath = meta.get_col2();
    unsigned long long fsize = meta.get_col6();
    time_t mtime = meta.get_col7();
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The file is %s, with %llu bytes.\n", fullpath.c_str(), fsize);
    std::string dest;
    existUser->downloadOneFileForMailbox(fpath, dest);
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The dest file absolute path is %s.\n", dest.c_str());
  }
  existUser->checkSharingGroupsSync();
  std::unordered_set<running_sharing_group_t> runningGroups = existUser->getSharingGroups();
  for (auto const &oneRunning : runningGroups)
  {
    ALLIVaultCore::ALLIEXTFolderP *ptr = (ALLIVaultCore::ALLIEXTFolderP *)oneRunning[ALLIVaultCore::Helpers::SHARING_PLAIN_FOLDER_POS];
    ALLIVaultCore::ALLIEXTSharingPlainFolderP *shPlainFolder = dynamic_cast<ALLIVaultCore::ALLIEXTSharingPlainFolderP *>(ptr);
    list = shPlainFolder->getFolderContentList();
    std::string list_str = shPlainFolder->getFolderContentListJson();
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The file list is %s.\n", list_str.c_str());
    std::string huname = shPlainFolder->getHostUserName();
    std::string gname = shPlainFolder->getGroupName();
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The host username is %s and the group name is %s.\n", huname.c_str(), gname.c_str());
    list = shPlainFolder->getFolderContentList();
    __android_log_print(ANDROID_LOG_INFO, "Apis", "The number of files is %lu.\n", list.size());
    for (const auto & rec : list)
    {
      std::string fpath = rec.first;
      ALLIVaultCore::Engine::ALLIFolderIndex meta = rec.second;
      std::string fullpath = meta.get_col2();
      unsigned long long fsize = meta.get_col6();
      time_t mtime = meta.get_col7();
      __android_log_print(ANDROID_LOG_INFO, "Apis", "The file is %s, with %llu bytes.\n", fullpath.c_str(), fsize);
      std::string dest;
      existUser->downloadOneFileForSharingGroup(huname, gname, fpath, dest);
      __android_log_print(ANDROID_LOG_INFO, "Apis", "The dest file absolute path is %s.\n", dest.c_str());
    }
  }
  __android_log_print(ANDROID_LOG_INFO, "Apis", "==>batchActionsForNewMachine done.");
}

JNIEXPORT void JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_appInitialize(JNIEnv *env, jclass type,
                                                                    jstring rootPath) {
  const char *rp = env->GetStringUTFChars(rootPath, 0);

  boost::filesystem::path rootDir(rp);
  ALLIVaultCore::Helpers::ALLIAppInit::appInitialize(rootDir);

  env->ReleaseStringUTFChars(rootPath, rp);
}

JNIEXPORT jboolean JNICALL
Java_com_allivault_cloudsafe_playground_AllivaultApi_registerAppStatusUpdated(JNIEnv *env, jclass clazz)
{
  jboolean ret = true;
  // convert local to global reference
  // (local will die after this method call)
  // save refs for callback
  g_clazz_appStatusUpdated = reinterpret_cast<jclass>(env->NewGlobalRef(clazz));
  if (g_clazz_appStatusUpdated == NULL)
  {
    ret = false;
    return ret;
  }

  g_mid_appStatusUpdated = env->GetStaticMethodID(g_clazz_appStatusUpdated, "appStatusUpdatedCallback", "()V");
  if (g_mid_appStatusUpdated == NULL)
  {
    ret = false;
  }
  return ret;
}
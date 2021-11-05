//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   dirs.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-09-09



#include "dirs.h"
#ifdef _WIN32
#include <process.h>
#include <conio.h>
#include <ShlObj.h>
#else
#include <fcntl.h>

#include <unistd.h>
#include <dirent.h>
#endif

#include <stdio.h>
#include <fstream>


namespace fv::utils {

    namespace {

        using namespace std::string_view_literals;

        constexpr auto NAME_ALLOWED_CHARS = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890@_+-. [](){}"sv);

        namespace Directories {
#ifdef _WIN32
            constexpr auto AppBase = TEXT("FotoVentus\\"sv);
            constexpr auto SubNest = TEXT("data"sv);
#elif __APPLE__
            constexpr auto AppBase = "Library/Application Support/Fotoventus"sv;
            constexpr auto SubNest = TEXT("data"sv);
#else
            constexpr auto AppBase = ".fotoventus/data"sv;
            constexpr auto SubNest = TEXT("data"sv);
#endif
        }

    }

    // -

size_t Dirs::fileSize(const t_tstr& dir, const t_tstr& filename) {
    t_tstr file = dir;
    fv::utils::concat(file, filename);
    std::ifstream in(file.c_str(), std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

bool Dirs::isFileExist(const t_tstr& dir, const t_tstr& filename, bool canBeEmpty) {
       
       t_tstr file = dir;
       fv::utils::concat(file, filename);
       
#ifdef _WIN32
       struct _stat st;
       memset(&st, 0, sizeof(struct _stat));
       return (_tstat(file.c_str(), &st) == 0) && (((st.st_mode) & S_IFMT) == S_IFREG) && (canBeEmpty || (st.st_size != 0));
#else
       struct stat st;
       memset(&st, 0, sizeof(struct stat));
       return (stat(file.c_str(), &st) == 0) && S_ISREG(st.st_mode) && (canBeEmpty || (st.st_size != 0));
#endif
   }
   



    std::filesystem::path Dirs::getBaseDir()
    {
        auto path = getUserDataDir();
        path /= Directories::AppBase;
        return path;
    }

    std::filesystem::path Dirs::getLogDir()
    {
        return getBaseDir();
    }

    std::filesystem::path Dirs::getNestDir()
    {
        auto path = getBaseDir();
        path /= Directories::SubNest;
        return path;
    }

   
    bool Dirs::isDirValid(const std::filesystem::path& dirname) {
        const auto& native = dirname.native();
        return !native.empty() && (native.find_first_not_of(NAME_ALLOWED_CHARS) == std::filesystem::path::string_type::npos);
    }

    std::filesystem::path Dirs::getUserDataDir() {
#ifdef _WIN32
        TCHAR appDataDir[MAX_PATH];
        appDataDir[0] = TEXT('\0');
        if (FAILED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appDataDir))) {
            throw std::runtime_error("SHGetFolderPath(CSIDL_LOCAL_APPDATA) failed.");
        }
        appDataDir[ARRAYSIZE(appDataDir) - 1] = TEXT('\0');
        return { appDataDir };
#else
        const char* homePath = getenv("HOME");
        if (homePath == NULL) {
            throw std::runtime_error("getenv(HOME) failed.");
        }
        return { homePath };
#endif
    }


void Dirs::mkdirUtf8(const std::string& path) {
#ifdef _WIN32
      t_tstr nativePath;
      utils::iconv::utf8_to_t(path, nativePath);
      
      if (!CreateDirectory(nativePath.c_str(), NULL) && (GetLastError() != ERROR_ALREADY_EXISTS)) {
          throw std::runtime_error("cannot create working directory");
      }
#else
      if ((::mkdir(path.c_str(), 0755) == -1) && (errno != EEXIST)) {
          throw std::runtime_error("cannot create working directory");
      }
#endif
  }


 
    void Dirs::removeDir(const t_tstr& dir) {
        if (!dir.empty()) {
            
#ifdef _WIN32
            asw::files::remove_directory(dir.c_str(), true);
#else
            t_tstr cmdline;
            cmdline = "rm -rf \"";
            cmdline += dir;
            cmdline += "\"";
            if (system(cmdline.c_str()) != 0) {
                throw std::runtime_error("Failed remove dir.");
            }
#endif
        }
    }


    
    std::list<t_tstr> Dirs::listDir(const t_tstr& searchLocation) {
        
        std::list<t_tstr> locations;
        t_tstr rootDir;
        t_tstr name;
        t_tstr suffix;
        t_tstr search;
        
        rootDir = searchLocation;
        
       
#ifdef _WIN32
            search = rootDir;
            utils::fs::concat(search, t_tstr(TEXT("*")));
            
            WIN32_FIND_DATA data;
            HANDLE hSearch = FindFirstFile(search.c_str(), &data);
            if (hSearch != INVALID_HANDLE_VALUE) {
                do {
                    
                    // "." or ".."
                    if ((data.cFileName[0] == '.') && ((data.cFileName[1] == '\0') || ((data.cFileName[1] == '.') && (data.cFileName[2] == '\0')))) {
                        continue;
                    }
                    
                    search = rootDir;
                    utils::fs::concat(search, data.cFileName);
                    
                    if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                        
                        name = data.cFileName;
                        if (!suffix.empty()) {
                            name += suffix;
                        }
                        
                        locations.push_back(name);
                    }
                    
                } while (FindNextFile(hSearch, &data));
                
                FindClose(hSearch);
                hSearch = INVALID_HANDLE_VALUE;
            }
#else
            struct dirent* dent;
            DIR* dirSearch = opendir(rootDir.c_str());
            if (dirSearch != NULL) {
                
                struct stat st;
                
                while((dent = readdir(dirSearch)) != NULL) {
                    
                    // "." or ".."
                    if ((dent->d_name[0] == '.') && ((dent->d_name[1] == '\0') || ((dent->d_name[1] == '.') && (dent->d_name[2] == '\0')))) {
                        continue;
                    }
                    
                    search = rootDir;
                    concat(search, dent->d_name);
                    
                    memset(&st, 0, sizeof(struct stat));
                    if (stat(search.c_str(), &st) != 0) {
                        continue;
                    }
                    
                    if (S_ISDIR(st.st_mode)) {
                        
                        name = dent->d_name;
                        if (!suffix.empty()) {
                            name += suffix;
                        }
                        
                        locations.push_back(name);
                    }
                }
                
                closedir(dirSearch);
                dirSearch = NULL;
            }
#endif
           
        
        
        return locations;
    }



}

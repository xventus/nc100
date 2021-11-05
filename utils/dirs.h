//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   dirs.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-09-09


#pragma once
#include "../include/crosstypes.h"
#ifdef _WIN32
#include <ShlObj_core.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif
#include <system_error>
#include <stdexcept>
#include <string_view>
#include <cstdlib>
#include <filesystem>
#include <list>

namespace fv::utils {


#ifdef _WIN32
    static const char pathSeparator = static_cast<const char>('\\');    ///< default path-separator character
#else
    static const char pathSeparator = static_cast<const char>('/');     ///< default path-separator character
#endif
    
    /**
     * Tests whether the character is a path separator.
     * @param ch Character to test.
     * @return true if the character is a path separator or false otherwise.
     */
    template<typename T>
    inline bool isPathSeparator(const T ch) {
#ifdef _WIN32
        return (ch == '/') || (ch == '\\');
#else
        return ch == '/';
#endif
    }
    
    template<class T>
    inline T& concat(T& path, const T& element) {
        if (!element.empty()) {
            if (path.length() > 0) {
                if (!isPathSeparator(path.at(path.length() - 1))) {
                    path += pathSeparator;
                }
            }
            path += element;
        }
        return path;
    }

    template<class T>
    inline T& concat(T& path, const typename T::value_type* element) {
        if (element != NULL) {
            if (path.length() > 0) {
                if (!isPathSeparator(path.at(path.length() - 1))) {
                    path += pathSeparator;
                }
            }
            path += element;
        }
        return path;
    }
    
    template<class str_t>
    inline str_t& terminateWithSeparator(str_t& path) {
        if ((path.length() > 0) && !isPathSeparator(path.at(path.length() - 1))) {
            path += pathSeparator;
        }
        return path;
    }


    class Dirs {
    public:

        static std::filesystem::path getBaseDir();

        static std::filesystem::path getLogDir();

        static std::filesystem::path getNestDir();

        static bool isDirValid(const std::filesystem::path& dirname);
        
        static bool isFileExist(const t_tstr& dir, const t_tstr& filename, bool canBeEmpty);
        
        static size_t fileSize(const t_tstr& dir, const t_tstr& filename);
        
        static void mkdirUtf8(const std::string& path);
        
        static std::list<t_tstr> listDir(const t_tstr& searchLocation);
        
        static void removeDir(const t_tstr& dir);
        
       
        

    private:

        static std::filesystem::path getUserDataDir();

    };

}

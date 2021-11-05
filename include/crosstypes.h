//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   crosstypes.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <tchar.h>
#endif
#include <iostream>

#ifndef _WIN32

typedef char TCHAR;

#ifndef TEXT
#define TEXT(x)             x
#endif
#endif

#include <string>

#ifdef _UNICODE
using t_tstr = std::wstring;
using tostream = std::wostream;
#else
using t_tstr = std::string;
using tostream = std::ostream;
#endif

#ifndef _WIN32
#ifndef _tmain
#define _tmain    main
#endif
#ifndef TCHAR
#define TCHAR char
#endif
#endif

#ifdef _UNICODE
        using t_sstream = std::wstringstream;
#define to_tstring(x) std::to_wstring(x)
#else
        using t_sstream = std::stringstream;
#define to_tstring(x) std::to_string(x)
#endif


// standard streams
#ifdef UNICODE

//! Standard output stream
#define tcout std::wcout

//! Standard output stream for errors
#define tcerr std::wcerr

//! Standard output stream for logging
#define tclog std::wclog

//! Standard input stream
#define tcin std::wcin

#else // <- UNICODE

//! Standard output stream
#define tcout std::cout

//! Standard output stream for errors
#define tcerr std::cerr

//! Standard output stream for logging
#define tclog std::clog

//! Standard input stream
#define tcin std::cin

#endif // <- !UNICODE

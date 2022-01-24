// -------------------------------------------------------------------------
/// @file utils.h
/// @author Mykhailo Lytvyn (mikhailo.lytvyn@gmail.com)
/// @date 11.01.2022
/// @brief
// -------------------------------------------------------------------------
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <windows.h>

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string lastErrorAsString(DWORD errorMessageID);

#endif // UTILS_H

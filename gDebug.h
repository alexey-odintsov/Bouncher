#ifndef GDEBUGH
#define GDEBUGH

#include <windows.h>
#include <string.h>
#include <stdio.h>

void ErrorMessage(char *title, const char *fmt, ...);
void ClearLog();
void Log(const char *msg, ...);

#endif
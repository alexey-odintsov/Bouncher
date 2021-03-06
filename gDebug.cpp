/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gDebug.h"

/************************************************************************************************
* Show error message dialog                                                                     *
************************************************************************************************/
void ErrorMessage(char *title, const char *fmt, ...)
{
    char errstr[256];
    va_list ap;

    va_start(ap, fmt);
      vsprintf(errstr, fmt, ap);
    va_end(ap);

    // show dialog
    MessageBox(NULL, errstr, title, MB_OK);
}

void ClearLog()
{
	FILE	*file;
	file = fopen("debug.log", "w");
	fclose(file);
}

/************************************************************************************************
* Log message to log file                                                                       *
************************************************************************************************/
void Log(const char *msg, ...)
{
    char	errstr[256];
    va_list	ap;
	FILE	*file;

    va_start(ap, msg);
      vsprintf(errstr, msg, ap);
    va_end(ap);

	file = fopen("debug.log", "a");
	fseek(file, 0L, SEEK_END);

	fprintf(file, errstr);

	fclose(file);
}

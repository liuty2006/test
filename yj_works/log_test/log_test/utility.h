#ifndef INC_UTILITY_H
#define INC_UTILITY_H

#include <windows.h>
#include <time.h>

//
#include <string>
#include <vector>

//
#define BUFSIZE_MAX 1024

void inline Log(const char *fmt, ...)
{
    //
    va_list args;
    char buf[BUFSIZE_MAX] = {'\0'};
    va_start(args, fmt);
    vsprintf_s(buf, fmt, args);

    //
    time_t rawtime;
    struct tm timeinfo;

    time ( &rawtime );
	localtime_s(&timeinfo, &rawtime);
    //timeinfo = localtime_s ( &rawtime );

    //
    char pszLog[BUFSIZE_MAX] = {0};
    sprintf_s(pszLog, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, buf);

    // output to console.
    printf("%s", pszLog);

	FILE *fp;
	fopen_s(&fp, "D:\\log.txt", "a");
	if (fp != NULL) {
		//
		fwrite(pszLog, strlen(pszLog), sizeof(char), fp);
		fclose(fp);
	}
}

#ifdef _DEBUG
#define TRACE_YJ Log
#else
//#define TRACE_YC {}
#define TRACE_YJ Log
#endif


//TRACE_YC("HTTP_YJ::posts_start - %s", strUrl.c_str());

#endif // INC_UTILITY_H

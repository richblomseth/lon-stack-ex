//	Start.c	implementing IsiStart
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include <stdio.h>
#include <stdarg.h>
#include "isi_int.h"
#include <time.h>

static FILE *fpIsiTracefile = NULL;
LonBool printTimeStamp = TRUE;

/*
 *  Function: IsiSetTracefile
 *  Sets the filename to use for the trace logging.  When the pFilename is NULL, trace logging stops and a previously opened 
 *  tracefile is closed. 
 *  
 *  Parameters:
 *  pFilename - the filename for the trace logging.  Sets to NULL to stop the trace logging.
 *  append    - if it is set to true, it means to open file for writing at the end of the file (appending) without removing the EOF marker
 *              before writing new data to the file; creates the file first if it doesn't exist.
 *              if it is set to false, it means to open an empty trace file for writing. If the given file exists, 
 *              its contents are destroyed.
 *
 *  Returns:     
 *  none 
 *
 */
void IsiSetTracefile(const char* pFilename, LonBool append)
{
    // close the previous trace log (if exists)
    if (fpIsiTracefile != NULL)
    {
        fclose(fpIsiTracefile);
        fpIsiTracefile = NULL;
    }
    if (pFilename != NULL)
    {
        const char *openStr = append ? "a" : "w";
        fpIsiTracefile = fopen(pFilename, openStr);
        if (fpIsiTracefile != NULL && append)
        {	// insert a separator
        	fprintf(fpIsiTracefile, "\n\n\t===\n\n");
        }
    }
}

/*=============================================================================
 *                           SUPPORT FUNCTIONS                                *
 *===========================================================================*/
void _IsiAPIDebug(const char * fmt, ...)
{
    va_list args;

    if (fpIsiTracefile != NULL)
    {
        if (printTimeStamp)
        {
            // Print time stamp
            char *pAsctimeStr;  
            char *pos;

            time_t dateTime;
            time(&dateTime);  // Get time in seconds
            pAsctimeStr = asctime(localtime(&dateTime));  // get local time as string
            // Remove the \n 
            pos = strchr(pAsctimeStr, '\n');
            *pos = '\0';
            fprintf(fpIsiTracefile, "[%s]", pAsctimeStr);
        }

        va_start(args, fmt);
        vfprintf(fpIsiTracefile, fmt, args);
        va_end(args);
        fflush(fpIsiTracefile);
    }
}

void _IsiAPIDump(const char* prefix, void* me, unsigned bytes, const char* postfix)
{
	unsigned char* data = (unsigned char *)me;
	char* buffer = (char*)malloc(strlen(prefix) + bytes * 3 + strlen(postfix) + 5);
	LonBool timestamp = printTimeStamp;

	printTimeStamp = FALSE;

	strcpy(buffer, prefix);
	while (bytes--) {
		sprintf(buffer + strlen(buffer), "%02X.", (unsigned)*data++);
	}
	sprintf(buffer + strlen(buffer) - 1, "%s", postfix);
	_IsiAPIDebug(buffer);

	printTimeStamp = timestamp;

	free(buffer);
}


//	end of trace.c

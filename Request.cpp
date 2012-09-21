/////////////////////////////////////////////////////////////////////
//
// CFX_EXECUTE - Cold Fusion custom tag
//
// Copyright 2001, 2004, 2012 by Lewis A. Sellers. All Rights Reserved.
// http://www.intrafoundation.com
//
// Version History:
/*
v1.4b August 24th 2012
Extensive debugging. All examples now work.

v1.4a August 22nd 2012
Rebuild for 64-bit.
Added CLEAR argument. 
http://kb.microfocus.com/display/4/kb/article.aspx?aid=35267

v1.4 November 18th 2004
Recompiled.
Permanently integrated old ASCII v1.3 Log class.
Added installer.

v1.3 July 29th 2004. Linked in to INMAL Log class (commons) and
cleaned up a few lines of code, added _snprintfs etc.

v1.2 April 20th 2004
Added CLog. etc. See main documentation for version history.

v1.1 March 4th 2004
*/

#include "stdafx.h" 	// Standard MFC libraries
#include "cfx.h"		// CFX Custom Tag API

//
#include "process.h"
#include "io.h"
#include <fcntl.h>
#include "errno.h"

// _stat
#include "sys\stat.h"

//
#include "Log.h"

//
#define MAX_COMMAND 		1024
#define MAX_DWORDEXPANSION	32

int static counter=0;

// (embedded copyright)
const char* szcopyright="CFX_Execute 1.4c August 30th 2012. Copyright (c) 1999-2004, 2012 by Lewis A. Sellers. http://www.intrafoundation.com";

//
void ProcessTagRequest( CCFXRequest* pRequest ) 
{
	try
	{
		counter++; // tracking how many calls the dll has had while loaded

		// init our logging class
		CLog log;

		//
		LPCSTR lpname = pRequest->GetAttribute("NAME");

		LPCSTR lparguments = pRequest->GetAttribute("ARGUMENTS");
		
		LPCSTR lpoutputfile = pRequest->GetAttribute("OUTPUTFILE");
		LPCSTR lpvariable = pRequest->GetAttribute("VARIABLE"); //new
		LPCSTR lptimeout = pRequest->GetAttribute("TIMEOUT");

		LPCSTR lpclear = pRequest->GetAttribute("CLEAR"); //new 8-23-2012
				
		// reset vars to blank just in case a hard error causes an exception before
		// we can actually set them at the end of the function.
		pRequest->SetVariable( "ExecuteError", "") ;
		pRequest->SetVariable( "ExecuteReturnCode", "") ;
		pRequest->SetVariable( "Execute", "");

		/*
		char tmp[1024];
		_snprintf (tmp, 1000, "(call # %d) lpname=%s lparguments=%s [%s]",
			counter,
			lpname,
			lparguments,
			szcopyright
			);
		pRequest->SetVariable( "ExecuteError", tmp); */

		//
		if(lpvariable!=NULL && strlen(lpvariable)>0)
		{
			pRequest->SetVariable( lpvariable, "") ;
		}

		//
		if(
			(lpname==NULL || strlen(lpname)==0) &&
			(lparguments==NULL || strlen(lparguments)==0)
		)
		{
			log.Error(
			__FILE__,
			__LINE__,
			"ProcessTagRequest",
			"No executable name or arguments passed.");
			pRequest->SetVariable( "ExecuteError", log.Errors());
		}
		else
		{
			//
			bool bclear=true;
			if(lpclear!=NULL && strlen(lpclear)>0)
			{
				if(_stricmp(lpclear,"No")==0)
					bclear=false;
			}
			if(bclear==true) log.Clear();

			//
			int timeout;
			if(lptimeout==NULL)
				timeout=5;
			else
				timeout=atoi(lptimeout);
			if(timeout==0) timeout=5;
			timeout=timeout*1000;

			//
			bool boutput_file=false;
			bool boutput_variable=false;
			bool boutput_display=false;
			if( (lpoutputfile!=NULL) && (strlen(lpoutputfile)>0) )
				boutput_file=true;
			if(lpvariable!=NULL && strlen(lpvariable)>0)
				boutput_variable=true;
			if(boutput_variable==false && boutput_file==false)
				boutput_display=true;

			//
			char szfile[MAX_PATH];
			char szcommandtext[MAX_COMMAND];

			// if user specifies a file for output use, that...
			if(boutput_file)
			{
				strcpy(szfile,lpoutputfile);
				_snprintf(szcommandtext,MAX_COMMAND,"%s %s > %s",lpname,lparguments,lpoutputfile);
			}
			else
			{ // otherwise just create a temporary file
				char sztmp[MAX_PATH];
				GetTempPath(MAX_PATH,sztmp);
				GetTempFileName(sztmp,"cfx",0,szfile);
				_snprintf(szcommandtext,MAX_COMMAND,"%s %s > %s",lpname,lparguments,szfile);
			}
			pRequest->SetVariable( "Execute", szcommandtext);

			// prepare to call CreateProcess...
			SECURITY_ATTRIBUTES sa; // = {0};
			memset(&sa,0,sizeof(SECURITY_ATTRIBUTES));
			sa.nLength = sizeof( sa );
			sa.bInheritHandle = TRUE;
			
			HANDLE outfile;
			outfile = CreateFile( 
				szfile,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_WRITE,
				&sa,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				0);
			
			//
			STARTUPINFO StartInfo;
			memset(&StartInfo,0,sizeof(STARTUPINFO));
			GetStartupInfo(&StartInfo);
			StartInfo.dwFlags = StartInfo.dwFlags | STARTF_USESTDHANDLES;
			StartInfo.cb = sizeof(STARTUPINFO);
			StartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE); //stdin; //(HANDLE)_fileno( stdin );
			StartInfo.hStdOutput = outfile; //(HANDLE)_fileno( stdout ); //outfile; //stdout;
			StartInfo.hStdError = outfile; //(HANDLE)_fileno( stderr );
			
			PROCESS_INFORMATION ProcInfo;
			memset(&ProcInfo,0,sizeof(PROCESS_INFORMATION));

			// DO IT. spawn off a process with our executable command...
			BOOL bcp;
			if(lpname==NULL || strlen(lpname)==0) //call with blank/null lpname
				bcp=CreateProcess(
				NULL,
				(char *)lparguments,
				NULL, //lpProcessAttributes
				NULL, //lpThreadAttributes
				TRUE, //bInheritHandles
				NORMAL_PRIORITY_CLASS, //0, //DETACHED_PROCESS | NORMAL_PRIORITY_CLASS, CREATE_NEW_CONSOLE,
				NULL, //lpEnvironment
				NULL, //lpCurrentDirectory
				(LPSTARTUPINFO)&StartInfo,
				(LPPROCESS_INFORMATION)&ProcInfo
				);
			else //normal call with Name
				bcp=CreateProcess(
				lpname,
				(char *)lparguments,
				NULL, //lpProcessAttributes
				NULL, //lpThreadAttributes
				TRUE, //bInheritHandles
				NORMAL_PRIORITY_CLASS, //0, //DETACHED_PROCESS | NORMAL_PRIORITY_CLASS, CREATE_NEW_CONSOLE,
				NULL, //lpEnvironment
				NULL, //lpCurrentDirectory
				(LPSTARTUPINFO)&StartInfo,
				(LPPROCESS_INFORMATION)&ProcInfo
				);
			if(!bcp)
			{ //WAIT_FAILED. Format and return error message if it didn't work...
				LPVOID lpMsgBuf;
					
				FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL);
					
				log.Error(
					__FILE__,
					__LINE__,
					"ProcessTagRequest",
					"Could not create process (%s) with arguments (%s): Error (%d) %s",
					lpname,
					(char *)lparguments,
					GetLastError(),
					lpMsgBuf
					);
					
				LocalFree(lpMsgBuf);
					
				//
				CloseHandle(outfile);
			}
			else
			{
				// if CreateProcess worked, we wait the specified time for the
				// process to terminate naturally...
				DWORD ret=WaitForSingleObject(ProcInfo.hThread,timeout);
				if(ret==WAIT_TIMEOUT)
				{ // process is still running....
					// so try to forcibly kill it.
					BOOL btp=TerminateProcess(ProcInfo.hProcess,0);
					if(btp) // killed
						log.Error(
						__FILE__,
						__LINE__,
						"ProcessTagRequest",
						"Process timed out: %d seconds. Process forcibly terminated: PID=%d.",
						(timeout/1000),
						ProcInfo.dwProcessId);
					else // tried to kill it, but it wouldn't die.
						log.Error(
						__FILE__,
						__LINE__,
						"ProcessTagRequest",
						"Process timed out: %d seconds. Attempt to forcibly terminated process failed: PID=%d.",
						(timeout/1000),
						ProcInfo.dwProcessId);
				}
				else if(ret==WAIT_ABANDONED)
				{ //the process stopped but... something went wrong
					// and it terminated uncleanly
					log.Error(
						__FILE__,
						__LINE__,
						"ProcessTagRequest",
						"Child process terminated and abandoned mutex.");
				}
				else if(ret==WAIT_OBJECT_0)
				{ //" Object in signalled state. (NOT AN ERROR)."
					// process exited before timeout and returned a proper code
					DWORD exitcode=0;
					BOOL bec=GetExitCodeProcess(ProcInfo.hProcess,&exitcode);
					char tmp[MAX_DWORDEXPANSION];
					_snprintf(tmp,MAX_DWORDEXPANSION,"%d",exitcode);
					pRequest->SetVariable( "ExecuteReturnCode", tmp);
				}
				else
				{ //other unknown error happened...
					log.Error(
						__FILE__,
						__LINE__,
						"ProcessTagRequest",
						"An error occured while waiting for process to complete. WaitForSingleObject returned DWORD %d.",ret);
				}
				
				// close down the thread handle... 
				BOOL tch=CloseHandle(ProcInfo.hThread);
				if(!tch)
					log.Error(
					__FILE__,
					__LINE__,
					"ProcessTagRequest",
					"Thread (%u) could not be closed.",ProcInfo.dwThreadId);
				
				// close down the process handle
				BOOL pch=CloseHandle(ProcInfo.hProcess);
				if(!pch)
					log.Error(
					__FILE__,
					__LINE__,
					"ProcessTagRequest",
					"Process (%u) could not be closed.",ProcInfo.dwProcessId);
				
				// close output file
				CloseHandle(outfile);
				
				// now that the process has run, return the output...
				if(boutput_display || boutput_variable)
				{ // if to variable or display...
					//get file size
					long filesize=0;
					struct _stat statbuf;
					int result=_stat( szfile, &statbuf);
					if( result == -1 )
					{
						log.Error(
							__FILE__,
							__LINE__,
							"ProcessTagRequest",
							"Query for size of file (%s) vi _stat failed.",szfile);
					}
					else
					{
						// the size of the output file. needed to create a temp mem buffer.
						filesize=statbuf.st_size;
						
						//
						if(filesize<=0)
							log.Error(
							__FILE__,
							__LINE__,
							"ProcessTagRequest",
							"Size of file (%s) is reported at %d bytes. Could not open.",szfile,filesize);
						else // if(filesize>0)
						{
							FILE *streamfh=fopen(szfile,"rb");
							if(streamfh==NULL)
								log.Error(
								__FILE__,
								__LINE__,
								"ProcessTagRequest",
								"File stream could not be opened on file (%s).",szfile);
							else
							{
								//
								char *buffer=new char[filesize+sizeof(DWORD)];
								if(buffer==NULL)
									log.Error(
									__FILE__,
									__LINE__,
									"ProcessTagRequest",
									"Memory could not be allocated (%d bytes) to read in temporary file (%s).",
									filesize+sizeof(DWORD),szfile);
								else
								{
									fread(buffer,1,filesize,streamfh);
									*(buffer+filesize)='\0';
									
									if(boutput_display)
										pRequest->Write(buffer);
									if(boutput_variable && lpvariable!=NULL)
										pRequest->SetVariable( lpvariable, buffer);
									
									delete[] buffer;
									buffer=NULL;
								}
								
								if(fclose(streamfh)!=0)
									log.Error(
									__FILE__,
									__LINE__,
									"ProcessTagRequest",
									"File stream (%d) could not be closed on file (%s).",streamfh,szfile);
							}
						}
					}
				
					// no outputfile specified, so we used a temporary name...
					if(boutput_file==false)
					{ // delete the temp file
						if(DeleteFile(szfile)==0)
						{
							log.Error(
								__FILE__,
								__LINE__,
								"ProcessTagRequest",
								"Temporary file (%s) could not be deleted.",szfile);
						}
					}

				}
			}

			// return collected error log
			pRequest->SetVariable( "ExecuteError", log.Errors());
		}
	}
	
	// Catch Cold Fusion exceptions & re-raise them
	catch( CCFXException* e )
	{
		pRequest->ReThrowException( e ) ;
	}
	
	// Catch ALL other exceptions and throw them as 
	// Cold Fusion exceptions (DO NOT REMOVE! -- 
	// this prevents the server from crashing in 
	// case of an unexpected exception)
	catch( ... )
	{
		pRequest->ThrowException( 
			"Error occurred in tag CFX_Execute",
			"Unexpected error occurred while processing tag." ) ;
	}
}

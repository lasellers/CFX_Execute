// execute.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "execute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExecuteApp

BEGIN_MESSAGE_MAP(CExecuteApp, CWinApp)
	//{{AFX_MSG_MAP(CExecuteApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExecuteApp construction

CExecuteApp::CExecuteApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CExecuteApp object

CExecuteApp theApp;

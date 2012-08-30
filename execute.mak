# Microsoft Developer Studio Generated NMAKE File, Based on execute.dsp
!IF "$(CFG)" == ""
CFG=execute - Win32 Debug
!MESSAGE No configuration specified. Defaulting to execute - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "execute - Win32 Release" && "$(CFG)" != "execute - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "execute.mak" CFG="execute - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "execute - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "execute - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "execute - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\execute.dll"


CLEAN :
	-@erase "$(INTDIR)\execute.obj"
	-@erase "$(INTDIR)\execute.pch"
	-@erase "$(INTDIR)\execute.res"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\execute.dll"
	-@erase "$(OUTDIR)\execute.exp"
	-@erase "$(OUTDIR)\execute.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\execute.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\execute.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\execute.pdb" /machine:I386 /def:".\execute.def" /out:"$(OUTDIR)\execute.dll" /implib:"$(OUTDIR)\execute.lib" 
DEF_FILE= \
	".\execute.def"
LINK32_OBJS= \
	"$(INTDIR)\execute.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\execute.res"

"$(OUTDIR)\execute.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "execute - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\execute.dll"


CLEAN :
	-@erase "$(INTDIR)\execute.obj"
	-@erase "$(INTDIR)\execute.pch"
	-@erase "$(INTDIR)\execute.res"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\execute.dll"
	-@erase "$(OUTDIR)\execute.exp"
	-@erase "$(OUTDIR)\execute.ilk"
	-@erase "$(OUTDIR)\execute.lib"
	-@erase "$(OUTDIR)\execute.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\execute.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\execute.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\execute.pdb" /debug /machine:I386 /def:".\execute.def" /out:"$(OUTDIR)\execute.dll" /implib:"$(OUTDIR)\execute.lib" /pdbtype:sept 
DEF_FILE= \
	".\execute.def"
LINK32_OBJS= \
	"$(INTDIR)\execute.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\execute.res"

"$(OUTDIR)\execute.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("execute.dep")
!INCLUDE "execute.dep"
!ELSE 
!MESSAGE Warning: cannot find "execute.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "execute - Win32 Release" || "$(CFG)" == "execute - Win32 Debug"
SOURCE=.\execute.cpp

"$(INTDIR)\execute.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\execute.pch"


SOURCE=.\execute.rc

"$(INTDIR)\execute.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Log.cpp

!IF  "$(CFG)" == "execute - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\execute.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "execute - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\execute.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Request.cpp

"$(INTDIR)\Request.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\execute.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "execute - Win32 Release"

CPP_SWITCHES=/nologo /G6 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\execute.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "execute - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\execute.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\execute.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


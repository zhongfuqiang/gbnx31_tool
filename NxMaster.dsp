# Microsoft Developer Studio Project File - Name="NxMaster" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NxMaster - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NxMaster.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NxMaster.mak" CFG="NxMaster - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NxMaster - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NxMaster - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NxMaster - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NxMaster - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NxMaster - Win32 Release"
# Name "NxMaster - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\CJColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\CJColorPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CJFlatComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPre_AFN0C_FN90_NOT_ELEC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreA00F1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F10.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F17.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F25_33.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F26.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F27.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F28.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F29.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F3.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F30.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F33.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F34.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F35.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F4.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F49.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F5.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F6.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F7.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F9.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn0aF2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn0AF7Q.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPrePn.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreSingle.cpp
# End Source File
# Begin Source File

SOURCE=.\FontColorTree.cpp
# End Source File
# Begin Source File

SOURCE=.\Gbnx_31.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlSock.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRichEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\NxConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\NxMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\NxMaster.rc
# End Source File
# Begin Source File

SOURCE=.\NxMasterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NxRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\PupText.cpp
# End Source File
# Begin Source File

SOURCE=.\Qgdw3761api.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSock.cpp
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabDlgPack.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDlgPreMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDlgPreTml.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDlgTask.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDlgUnpack.cpp
# End Source File
# Begin Source File

SOURCE=.\Terminal.cpp
# End Source File
# Begin Source File

SOURCE=.\Terminal.h
# End Source File
# Begin Source File

SOURCE=.\TerminalSock.cpp
# End Source File
# Begin Source File

SOURCE=.\XPTabCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\CJColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\CJColorPopup.h
# End Source File
# Begin Source File

SOURCE=.\CJFlatComboBox.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgPre_AFN0C_FN90_NOT_ELEC.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreA00F1.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F1.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F10.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F17.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F2.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F25_33.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F26.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F27.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F28.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F29.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F3.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F30.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F33.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F34.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F35.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F4.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F49.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F5.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F6.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F7.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn04F9.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn0aF2.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreAfn0AF7Q.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrePn.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreSingle.h
# End Source File
# Begin Source File

SOURCE=.\FontColorTree.h
# End Source File
# Begin Source File

SOURCE=.\Gbnx_31.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlSock.h
# End Source File
# Begin Source File

SOURCE=.\MyRichEdit.h
# End Source File
# Begin Source File

SOURCE=.\NxConfig.h
# End Source File
# Begin Source File

SOURCE=.\NxMaster.h
# End Source File
# Begin Source File

SOURCE=.\NxMasterDlg.h
# End Source File
# Begin Source File

SOURCE=.\NxRuler.h
# End Source File
# Begin Source File

SOURCE=.\NxRulerTypes.h
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=.\PupText.h
# End Source File
# Begin Source File

SOURCE=.\Qgdw3761api.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerSock.h
# End Source File
# Begin Source File

SOURCE=.\ShadeButtonST.h
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgPack.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgPreMaster.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgPreTml.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgTask.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgUnpack.h
# End Source File
# Begin Source File

SOURCE=.\TerminalSock.h
# End Source File
# Begin Source File

SOURCE=.\XPTabCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\07.ico
# End Source File
# Begin Source File

SOURCE=.\res\515.ico
# End Source File
# Begin Source File

SOURCE=".\res\520 - ∏±±æ.ico"
# End Source File
# Begin Source File

SOURCE=.\res\520.ico
# End Source File
# Begin Source File

SOURCE=.\res\6.ico
# End Source File
# Begin Source File

SOURCE=.\res\7.ico
# End Source File
# Begin Source File

SOURCE=.\res\afn.ico
# End Source File
# Begin Source File

SOURCE=.\res\afn1.ico
# End Source File
# Begin Source File

SOURCE=".\res\Applications NetProbe.ico"
# End Source File
# Begin Source File

SOURCE=.\res\ARW07LT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ARW07RT.ICO
# End Source File
# Begin Source File

SOURCE=".\res\broken-connection.ico"
# End Source File
# Begin Source File

SOURCE=.\res\check.ico
# End Source File
# Begin Source File

SOURCE=.\res\clock.ico
# End Source File
# Begin Source File

SOURCE=.\res\d.ico
# End Source File
# Begin Source File

SOURCE=.\res\down.ico
# End Source File
# Begin Source File

SOURCE=.\res\empty.ico
# End Source File
# Begin Source File

SOURCE=.\res\facebook.ico
# End Source File
# Begin Source File

SOURCE=.\res\file.ico
# End Source File
# Begin Source File

SOURCE=.\res\flickr.ico
# End Source File
# Begin Source File

SOURCE=".\res\green-upper-G.ico"
# End Source File
# Begin Source File

SOURCE=.\res\heckout.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon26.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon27.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_afn.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_che.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_fn3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Left6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\list_normal.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\mixx.ico
# End Source File
# Begin Source File

SOURCE=.\res\move.ico
# End Source File
# Begin Source File

SOURCE=.\res\mute.ico
# End Source File
# Begin Source File

SOURCE=.\res\mute1.ico
# End Source File
# Begin Source File

SOURCE=.\res\note.ico
# End Source File
# Begin Source File

SOURCE=.\res\notification1.ico
# End Source File
# Begin Source File

SOURCE=.\res\notification2.ico
# End Source File
# Begin Source File

SOURCE=.\res\NxMaster.ico
# End Source File
# Begin Source File

SOURCE=.\res\NxMaster.rc2
# End Source File
# Begin Source File

SOURCE=.\res\private.ico
# End Source File
# Begin Source File

SOURCE=".\res\red-upper-F.ico"
# End Source File
# Begin Source File

SOURCE=".\res\red-upper-S.ico"
# End Source File
# Begin Source File

SOURCE=".\res\red-upper-T.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Right6_32x32x256.ico
# End Source File
# Begin Source File

SOURCE=.\res\rning.ico
# End Source File
# Begin Source File

SOURCE=.\res\Run.ico
# End Source File
# Begin Source File

SOURCE=.\res\security_normal.ico
# End Source File
# Begin Source File

SOURCE=.\res\shoppingcart.ico
# End Source File
# Begin Source File

SOURCE=.\res\statusDone.ico
# End Source File
# Begin Source File

SOURCE=.\res\statusNotDone.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\technorati.ico
# End Source File
# Begin Source File

SOURCE=.\res\Thesisor.ico
# End Source File
# Begin Source File

SOURCE=.\res\ttraveler.ico
# End Source File
# Begin Source File

SOURCE=.\res\tumblr.ico
# End Source File
# Begin Source File

SOURCE=.\res\twitter.ico
# End Source File
# Begin Source File

SOURCE=".\res\two-feet.ico"
# End Source File
# Begin Source File

SOURCE=.\res\up.ico
# End Source File
# Begin Source File

SOURCE=.\res\volume.ico
# End Source File
# Begin Source File

SOURCE=".\res\yellow-upper-F.ico"
# End Source File
# Begin Source File

SOURCE=".\res\…Ë÷√.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

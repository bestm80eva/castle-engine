/*
  Copyright 2013 Jan Adamec, Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------

  This include file should be used in C/C++ projects. It contains all
  functions exported from the library.

  Windows: add castlelib_win_loader.cpp file to your project and call
      CGE_LoadLibrary first to enable to Castle Game Engine funtions.

  iOS: castlelib will be statically linked to your app, so just include
      this file and you are ready to go.
*/


#ifndef CGE_LIBRARY_INCLUDED
#define CGE_LIBRARY_INCLUDED

enum ECgeShiftState
{
    ecgessShift = 1,
    ecgessAlt   = 2,
    ecgessCtrl  = 4,
};

enum ECgeNavigationType
{
    ecgenavWalk         = 0,
    ecgenavFly          = 1,
    ecgenavExamine      = 2,
    ecgenavArchitecture = 3,
};

enum ECgeTouchCtlInterface
{
    ecgetciNone              = 0,
    ecgetciCtlWalkCtlRotate  = 1,
    ecgetciCtlWalkDragRotate = 2,
};

enum ECgeMouseCursor
{
    ecgecursorDefault   = 0,
    ecgecursorWait      = 1,
    ecgecursorHand      = 2,
    ecgecursorText      = 3,
    ecgecursorNone      = 4,
};

enum ECgeLibCallbackCode
{
    ecgelibNeedsDisplay     = 0,    // app should repaint the view (content changed)
    ecgelibSetMouseCursor   = 1,    // sends ECgeMouseCursor in iParam1
};

typedef int (__cdecl *TCgeLibraryCallbackProc)(int /*ECgeLibCallbackCode*/eCode, int iParam1, int iParam2);


//-----------------------------------------------------------------------------
extern void CGE_LoadLibrary();	// function defined in the loader CPP file

//-----------------------------------------------------------------------------
extern void CGE_Init();     // init the library, this function must be called first (required)
extern void CGE_Close();

extern void CGE_SetRenderParams(unsigned uiViewWidth, unsigned uiViewHeight);   // let the library know about the viewport size (required)
extern void CGE_Render();                                                       // paints the 3d scene into the context
extern void CGE_SetLibraryCallbackProc(TCgeLibraryCallbackProc pProc);          // set callback function
extern void CGE_OnIdle();                                                       // let the 3d engine perform the animations, etc

extern void CGE_OnMouseDown(int x, int y, bool bLeftBtn, unsigned uiShift);     // uiShift is the combination of ECgeShiftState
extern void CGE_OnMouseMove(int x, int y, unsigned uiShift);
extern void CGE_OnMouseUp(int x, int y, bool bLeftBtn, unsigned uiShift);
extern void CGE_OnMouseWheel(float zDelta, bool bVertical, unsigned uiShift);

extern void CGE_LoadSceneFromFile(const char *szFile);                          // name od the file has to be utf-8 encoded

extern int CGE_GetViewpointsCount();
extern void CGE_GetViewpointName(int iViewpointIdx, char *szName, int nBufSize);    // szName is buffer of size nBufSize, and is filled with utf-8 encoded string
extern void CGE_MoveToViewpoint(int iViewpointIdx, bool bAnimated);

extern int CGE_GetCurrentNavigationType();
extern void CGE_SetNavigationType(int /*ECgeNavigationType*/ eNewType);

extern void CGE_UpdateTouchInterface(int /*ECgeTouchCtlInterface*/ eMode);

#endif //CGE_LIBRARY_INCLUDED
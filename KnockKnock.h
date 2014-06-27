// KnockKnock.h : main header file for the KNOCKKNOCK application
//

#if !defined(AFX_KNOCKKNOCK_H__8C85C2B3_47F8_47E6_8E00_13C40CEB1E95__INCLUDED_)
#define AFX_KNOCKKNOCK_H__8C85C2B3_47F8_47E6_8E00_13C40CEB1E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKnockKnockApp:
// See KnockKnock.cpp for the implementation of this class
//

class CKnockKnockApp : public CWinApp
{
public:
	CKnockKnockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnockKnockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKnockKnockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KNOCKKNOCK_H__8C85C2B3_47F8_47E6_8E00_13C40CEB1E95__INCLUDED_)

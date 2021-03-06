// IPCPlayerDemoDlg.cpp : implementation file
//

#include "stdafx.h"

#include "shlwapi.h"

#include "winver.h"

#include <Afxmt.h>

#include <math.h>

#include "About.h"

#include "IPCSdkFuncDemoDlg.h"

#include "LogViewDlg.h"

#include "IPCamera.h"

#include "SystemSetting.h"

#include "UpdateSeviceDlg.h"

#include "ActiveDlg.h"

#include "CameraConfigSetting.h"

#include "EventSet.h"

#include "PlanSet.h"

#include "AudioDialog.h"

#include "TransDlg.h"

#include "PtzPositionParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  TIME_FOCUS 1

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

/////////////////////////////////////////////////////////////////////////////
// CIPCPlayerDemoDlg dialog

CIPCPlayerDemoDlg::CIPCPlayerDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CIPCPlayerDemoDlg::IDD, pParent)
    , m_EdtPresetName(_T("")),m_occupation(0)
	, m_3D_X(0)
	, m_3D_Y(0)
	, m_3D_Width(0)
	, m_3D_Height(0)
	,m_bStartSharpen(FALSE)
{
     ;
    //{{AFX_DATA_INIT(CIPCPlayerDemoDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CIPCPlayerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	;

	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_PRESET_LIST, m_ctrlPresetList);

	DDX_Text(pDX, IDC_EDIT_RECORDING_PATH, m_RecordingPath);

	//{{AFX_DATA_MAP(CIPCPlayerDemoDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_PRESET_STRING, m_EdtPresetName);
	DDX_Control(pDX, IDC_CMB_POINT, m_cmb_point);
	DDX_Radio  (pDX, IDC_RADIO_AUTO, m_occupation);
	DDX_Control(pDX, IDC_COMBO_FOCUS, m_cmbFocus);
	DDX_Text(pDX, IDC_EDIT_3D_X, m_3D_X);
	DDV_MinMaxInt(pDX, m_3D_X, -100, 100);
	DDX_Text(pDX, IDC_EDIT_3D_Y, m_3D_Y);
	DDV_MinMaxInt(pDX, m_3D_Y, -100, 100);
	DDX_Text(pDX, IDC_EDIT_3D_WIDTH, m_3D_Width);
	DDV_MinMaxInt(pDX, m_3D_Width, -100, 100);
	DDX_Text(pDX, IDC_EDIT_3D_HEIGHT, m_3D_Height);
	DDV_MinMaxInt(pDX, m_3D_Height, -100, 100);
	DDX_Control(pDX, IDC_SLIDER_SHARPEN_DEGREE, m_sliderSharDegree);
}

BEGIN_MESSAGE_MAP(CIPCPlayerDemoDlg, CDialog)
    //{{AFX_MSG_MAP(CIPCPlayerDemoDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_MOVE()

    ON_WM_HSCROLL()
    //}}AFX_MSG_MAP


    ON_MESSAGE(IPC_MSG_VIDEOWNDMOVE,OnVideoWndMove)
    
    ON_MESSAGE(IPC_MSG_LOGSAVING,OnLogSaving)

    ON_MESSAGE(WM_AUDIO_DISCONNECTION,OnSDKDisconnection)
    

    ON_BN_CLICKED(IDC_BUTTON1, &CIPCPlayerDemoDlg::OnBnClickedPtzZoomIn)
    ON_BN_CLICKED(IDC_BUTTON2, &CIPCPlayerDemoDlg::OnBnClickedPtzZoomOut)
    ON_BN_CLICKED(IDC_BUTTON_UP, &CIPCPlayerDemoDlg::OnBnClickedButtonUp)
    ON_BN_CLICKED(IDC_BUTTON_DOWN, &CIPCPlayerDemoDlg::OnBnClickedButtonDown)
    ON_BN_CLICKED(IDC_BUTTON_LEFT, &CIPCPlayerDemoDlg::OnBnClickedButtonLeft)
    ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CIPCPlayerDemoDlg::OnBnClickedButtonRight)
    ON_BN_CLICKED(IDC_BUTTON3, &CIPCPlayerDemoDlg::OnBnClickedPtzHome)
    ON_BN_CLICKED(IDC_BUTTON_SETPRESET, &CIPCPlayerDemoDlg::OnBnClickedButtonSetpreset)
    ON_BN_CLICKED(IDC_BUTTON_GOTO, &CIPCPlayerDemoDlg::OnBnClickedButtonGoto)

//////////////////////////////////////////////////////////////////////////
    ON_BN_CLICKED(IDC_CHECK_DPTZ, &CIPCPlayerDemoDlg::OnCheckBoxSelected)
    ON_BN_CLICKED(IDC_CHECK_JPEG_SAVING, &CIPCPlayerDemoDlg::OnCheckBoxSelected)
    ON_BN_CLICKED(IDC_BUTTON4, &CIPCPlayerDemoDlg::OnBnClickedPtzFocusIn)
    ON_BN_CLICKED(IDC_BUTTON5, &CIPCPlayerDemoDlg::OnBnClickedPtzFocusOut)
    ON_BN_CLICKED(IDC_USER_LOG_BTN, &CIPCPlayerDemoDlg::OnBnClickedUserLogBtn)
    ON_BN_CLICKED(IDC_BUTTON_SYSTEMSETTING, &CIPCPlayerDemoDlg::OnBnClickedButtonSystemsetting)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CIPCPlayerDemoDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_PANEL, &CIPCPlayerDemoDlg::OnBnClickedButtonEventpanel)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ACTIVEX, &CIPCPlayerDemoDlg::OnBnClickedButtonShowActivex)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_SETTING, &CIPCPlayerDemoDlg::OnBnClickedButtonConfigSetting)
	ON_BN_CLICKED(IDC_BUTTON_PLAN, &CIPCPlayerDemoDlg::OnBnClickedButtonPlan)
    ON_BN_CLICKED(IDC_BUTTON_AUDIO, &CIPCPlayerDemoDlg::OnBnClickedButtonAudio)
    ON_BN_CLICKED(IDC_BUTTON_PTZ_OPT, &CIPCPlayerDemoDlg::OnBnClickedButtonPtzOpt)
	ON_BN_CLICKED(IDC_BTN_LEFTBORDER, &CIPCPlayerDemoDlg::OnBnClickedBtnLeftborder)
	ON_BN_CLICKED(IDC_BTN_RIGHTBORDER, &CIPCPlayerDemoDlg::OnBnClickedBtnRightborder)
	ON_BN_CLICKED(IDC_START_LINRSCAN, &CIPCPlayerDemoDlg::OnBnClickedStartLinrscan)
	ON_BN_CLICKED(IDC_STOP_LINESCAN, &CIPCPlayerDemoDlg::OnBnClickedStopLinescan)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CIPCPlayerDemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CIPCPlayerDemoDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BUTTON_LEFTUP, &CIPCPlayerDemoDlg::OnBnClickedButtonLeftup)
	ON_BN_CLICKED(IDC_BUTTON_RIGHTUP, &CIPCPlayerDemoDlg::OnBnClickedButtonRightup)
	ON_BN_CLICKED(IDC_BUTTON_LEFTDOWN, &CIPCPlayerDemoDlg::OnBnClickedButtonLeftdown)
	ON_BN_CLICKED(IDC_BUTTON_RIGHTDOWN, &CIPCPlayerDemoDlg::OnBnClickedButtonRightdown)
	ON_BN_CLICKED(IDC_BUTTON6, &CIPCPlayerDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_TEST_TRIGGER_ALARM_OUTPUT, &CIPCPlayerDemoDlg::OnBnClickedButtonTestTriggerAlarmOutput)
	ON_CBN_SELCHANGE(IDC_COMBO_FOCUS, &CIPCPlayerDemoDlg::OnCbnSelchangeComboFocus)
	ON_BN_CLICKED(IDC_RADIO_AUTO, &CIPCPlayerDemoDlg::OnBnClickedRadioAuto)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, &CIPCPlayerDemoDlg::OnBnClickedRadioManual)
	ON_BN_CLICKED(IDC_BUTTON_3D_POSITION_TAKE_EFFECT, &CIPCPlayerDemoDlg::OnBnClickedButton3dPositionTakeEffect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PTZ_POSITION_PARAM, &CIPCPlayerDemoDlg::OnBnClickedButtonPtzPositionParam)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCPlayerDemoDlg message handlers
VOID CIPCPlayerDemoDlg::Init_PTZ_Range(INT hMin,INT hMax,INT vMin,INT vMax) 
{
    CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_HSPEED);

    pSlidCtrl->SetRange(hMin,hMax,TRUE);//设置滑动条范围

    pSlidCtrl->SetPos(50);//设置滑动条位置

    m_HSpeed = 50 ;

    pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_VSPEED);

    //0~0x3f 再加上 0xff 高速
    pSlidCtrl->SetRange(hMin,hMax,TRUE);//设置滑动条范围

    pSlidCtrl->SetPos(50);//设置滑动条位置

    m_VSpeed = 50 ;
    
}
void CIPCPlayerDemoDlg::SetCurrentWnd(HWND hWnd) 
{
     ;

    m_SelectedWindow = hWnd ;
}
BOOL CIPCPlayerDemoDlg::OnInitDialog()
{
     ;

    CDialog::OnInitDialog();

    // IDM_ABOUTBOX must be in the system command range.

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);

    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);

    if (pSysMenu != NULL)
    {
        CString strAboutMenu;

        strAboutMenu.LoadString(IDS_ABOUTBOX);

        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);

            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);            // Set big icon

    SetIcon(m_hIcon, FALSE);        // Set small icon
    
	m_cmb_point.SetTopIndex(0);
	for(int i=1;i<=8; i++)
	{
		CString sText;
		sText.Format(_T("%d"),i);
		INT index = m_cmb_point.InsertString(i-1,sText);
		m_cmb_point.SetItemData(index,i);
	}
	m_cmb_point.SetCurSel(0);
	

    m_lIndex = -1;

    m_lState = 0;

    ShowWindow(SW_SHOWMAXIMIZED);

    CRect    rc;

    GetClientRect(&rc);

    DivideWnd(IPC_VIDEOWND_MAX);

    CRect    rcWnd;

    for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
    {
        rcWnd = m_rcWnd[i];

        m_VideoWnd[i].Create(i,rcWnd,this);

        m_VideoWnd[i].SetMainFrame(this) ;
    }
    
    ipcInitialize() ;

    //ipcEnableVideoResize(TRUE) ;

    INT lCurSel ;
    TCHAR szTemp[128]={0} ;

    for( int i = 1;i<256;i++ )
    {
        sprintf(szTemp,TEXT("%d"),i) ;

        lCurSel = m_ctrlPresetList.AddString(szTemp);

        m_ctrlPresetList.SetItemData(lCurSel,i);
    }

    m_ctrlPresetList.SetCurSel(0);

    TCHAR* lpPath = (TCHAR*)new TCHAR[1024] ;

    CONST TCHAR* lpcPath = NULL ;

    GetModuleFileName(0,lpPath,MAX_PATH) ;

    lpcPath = PathFindFileName(lpPath) ;

	m_RecordingPath = (std::basic_string<TCHAR>(lpPath,lpcPath).c_str());

    delete[] lpPath ;

    m_IsDptz = FALSE ;

    ((CButton*)GetDlgItem(IDC_CHECK_DPTZ))-> SetCheck(m_IsDptz); 

    Init_PTZ_Range(0,100,0,100) ;
    //CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_HSPEED);

    //pSlidCtrl->SetRange(0,63,TRUE);//设置滑动条范围

    //pSlidCtrl->SetPos(0);//设置滑动条位置

    //m_HSpeed = 0 ;

    //pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_VSPEED);

    //pSlidCtrl->SetRange(0,255,TRUE);//设置滑动条范围

    //pSlidCtrl->SetPos(0);//设置滑动条位置

    //m_VSpeed = 50 ;

    m_IsSavingJPEG = TRUE ;

    ((CButton*)GetDlgItem(IDC_CHECK_JPEG_SAVING))-> SetCheck(m_IsSavingJPEG); 

    UpdateData(FALSE) ;

    {
        TCHAR szFilePath[MAX_PATH]={0} ;

        GetModuleFileName(NULL,szFilePath,MAX_PATH) ;

        TCHAR* lpName = PathFindFileName(szFilePath) ;

        CString strVer ;

#define MODULE_VERSION_INFO_2LOG(name) strcpy(lpName,name);\
    strVer = GetSpecifyFileVersion( szFilePath ) ;\
    GetUserLogMgr().push( TEXT(name),TEXT("VERSION"),strVer ) ;\
    XINFO("%s - %s",name,strVer.GetBuffer())


    }

	m_cmbFocus.InsertString(0,_T("全自动模式"));
	m_cmbFocus.InsertString(1,_T("自动聚焦锁定模式"));
	m_cmbFocus.SetCurSel(0);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FOCUS)->EnableWindow(TRUE);
	m_bStartUpdateServer = false ;

    return TRUE;  // return TRUE  unless you set the focus to a control

}
CString CIPCPlayerDemoDlg::GetSpecifyFileVersion(LPCTSTR lpszFileName)
{
    CString strRet = _T("");
    DWORD    dwHandle;
    DWORD    dwFileVersionInfoSize = GetFileVersionInfoSize((LPTSTR)lpszFileName, &dwHandle);
    if (!dwFileVersionInfoSize)
        return strRet;

    LPVOID    lpData = (LPVOID)new BYTE[dwFileVersionInfoSize];
    if (!lpData)
        return strRet;

    try
    {
        if (!GetFileVersionInfo((LPTSTR)lpszFileName, dwHandle, dwFileVersionInfoSize, lpData))
            throw FALSE;

        LPVOID    lpInfo;
        UINT        unInfoLen;
        if (VerQueryValue(lpData, _T("\\"), &lpInfo, &unInfoLen))
        {
            VS_FIXEDFILEINFO fileInfo;
            if (unInfoLen == sizeof(fileInfo))
            {
                memcpy(&fileInfo, lpInfo, unInfoLen);
                strRet.Format(_T("%d.%d.%d.%d"), (fileInfo.dwFileVersionMS & 0xFFFF0000) >> 16, fileInfo.dwFileVersionMS & 0x0000FFFF, \
                    (fileInfo.dwFileVersionLS & 0xFFFF0000) >> 16, fileInfo.dwFileVersionLS & 0x0000FFFF);
            }
        }
    }
    catch (BOOL)
    {
        delete[] lpData;
        lpData = NULL ;
    }
        if(lpData)
        {
            delete[] lpData;
            lpData = NULL ;
        }

    return strRet;
}


void CIPCPlayerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
     ;

    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
    
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPCPlayerDemoDlg::OnPaint() 
{
     ;

    CPaintDC dc(this); // device context for painting
    
    CDC    *pDC = &dc;

    if (IsIconic())
    {
    //    CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
    
        int cyIcon = GetSystemMetrics(SM_CYICON);

        CRect rect;

        GetClientRect(&rect);

        int x = (rect.Width() - cxIcon + 1) / 2;

        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIPCPlayerDemoDlg::OnQueryDragIcon()
{
     ;

    return (HCURSOR) m_hIcon;
}
void CIPCPlayerDemoDlg::CloseAllVideoWnd()
{
    for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
    {
        m_VideoWnd[i].Close() ;
    } ;
}

void CIPCPlayerDemoDlg::OnDestroy() 
{
    CloseAllVideoWnd() ;
    
    ipcUnInitialize() ;

    CDialog::OnDestroy();

    //IPC_Player_UnInitialize();

}

void CIPCPlayerDemoDlg::OnCancel() 
{
     ;

    if ( MessageBox(TEXT("Would you exit the application ?\t"),TEXT("System prompt"),MB_ICONQUESTION | MB_OKCANCEL ) != IDOK )
    {
        return ;
    }

    CDialog::OnCancel();
}

void CIPCPlayerDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
     if( cx < 400 || cy < 400 )
     {
         return ;
     }

    CDialog::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
    
    if ( !::IsWindow(m_hWnd) )
    {
        return;
    }

    DivideWnd(IPC_VIDEOWND_MAX);

    for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
    {
        if ( !::IsWindow(m_VideoWnd[i].GetSafeHwnd()) )
        {
            continue;
        }

        m_VideoWnd[i].MoveWindow(m_rcWnd[i]);

        if ( m_lState >= 1 )
        {
            if ( m_lIndex >= 0 ) 
            {
                if ( m_lIndex == i )
                {
                    CRect    rc;
    
                    GetClientRect(&rc);

                    m_VideoWnd[i].MoveWindow(&rc);

                    m_VideoWnd[i].ShowWindow(SW_SHOW);
                }
                else
                {
                    m_VideoWnd[i].ShowWindow(SW_HIDE);
                }
            }
            else
            {
                m_VideoWnd[i].ShowWindow(SW_SHOW);

                m_VideoWnd[i].Refresh() ;
            }            
        }
        else
        {
            m_VideoWnd[i].ShowWindow(SW_SHOW);
        }
    }//for    
    
}


BOOL CIPCPlayerDemoDlg::DivideWnd(int nNum)
{
     ;

    if ( ( nNum <= 0 ) || ( nNum > IPC_VIDEOWND_MAX ) )
    {
        return FALSE;
    }

    CRect        rc;
    
    GetClientRect(&rc);

    CRect        rcWnd;

    int        nRow    = (int)sqrt((double)nNum);
    
    int        nColoum = nRow;
    
    int        nWidth  = (rc.Width() - IPC_LAYOUT_OFFSET) / nColoum;
    
    int        nHeight = rc.Height() / nRow;

    int        nID = 0;
    
    for ( int i = 0;i < nRow;i ++ )
    {
        for ( int j = 0;j < nColoum;j ++ )
        {
            nID = i * nColoum + j;
    
            m_rcWnd[nID].left   = j * nWidth + IPC_LAYOUT_OFFSET;

            m_rcWnd[nID].top    = i * nHeight;

            m_rcWnd[nID].right  = m_rcWnd[nID].left + nWidth;

            m_rcWnd[nID].bottom = m_rcWnd[nID].top  + nHeight;
        }
    }

    return TRUE;
}

LRESULT CIPCPlayerDemoDlg::OnLogSaving(WPARAM wParam, LPARAM lParam)
{
     ;

    std::basic_string<TCHAR> filepath = m_RecordingPath + TEXT("\\user.log") ;

    m_UserLogMgr.tofile(filepath.c_str()) ;

    return TRUE ;
}


LRESULT CIPCPlayerDemoDlg::OnVideoWndMove(WPARAM wParam, LPARAM lParam)
{
    HWND m_Owner = m_hWnd ;

    long    lIndex = wParam;
    
    long    lState = lParam;    
    
    if ( lIndex < 0 )
    {
        return 0;
    }    

    m_lIndex = lIndex;
    
    m_lState = lState;

    if ( lState <= 0 )
    {
        for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
        {
            ::SetParent(m_VideoWnd[i].m_hWnd,m_Owner ) ;

            m_VideoWnd[i].MoveWindow(m_rcWnd[i]);
    
            m_VideoWnd[i].ShowWindow(SW_SHOW);

            m_VideoWnd[i].Refresh() ;
        }
    }
    else if ( lState <= 1 )
    {                    
        for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
        {
            m_VideoWnd[i].ShowWindow(SW_HIDE);
        }        
        
        CRect    rc;

        GetClientRect(&rc);

        rc.left = rc.left + IPC_LAYOUT_OFFSET;

        int     nFullWidth=GetSystemMetrics(SM_CXSCREEN);     

        int     nFullHeight=GetSystemMetrics(SM_CYSCREEN);     

        rc.left = 0 ;
        rc.top = 0 ;
        rc.right = nFullWidth ;
        rc.bottom = nFullHeight ;

        ::SetParent(m_VideoWnd[lIndex].m_hWnd,NULL ) ;

        ::SetWindowPos(m_VideoWnd[lIndex].m_hWnd,HWND_TOPMOST,0,0,nFullWidth,nFullHeight,SWP_NOMOVE|SWP_NOSIZE);


        m_VideoWnd[lIndex].MoveWindow(rc);

        m_VideoWnd[lIndex].ShowWindow(SW_SHOW);

        m_VideoWnd[lIndex].Refresh() ;
    }

    return 0 ;
}

void CIPCPlayerDemoDlg::OnMove(int x, int y) 
{
     ;

    CDialog::OnMove(x, y);
    
    // TODO: Add your message handler code here
    
    for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
    {        
        if ( !::IsWindow( m_VideoWnd[i].GetSafeHwnd() ) )
        {
            continue;
        }

        if ( !m_VideoWnd[i].IsWindowVisible() ) 
        {
            continue;
        }

        m_VideoWnd[i].Invalidate(TRUE);
    }
}

CUserLogMgr& CIPCPlayerDemoDlg::GetUserLogMgr() 
{
     ;

    return m_UserLogMgr ;
}

CVideoWnd* CIPCPlayerDemoDlg::GetSelectedWindowClass()
{
     ;

    CVideoWnd* ret = NULL ;

    for ( int i = 0;i < IPC_VIDEOWND_MAX;i ++ )
    {        
        if ( !::IsWindow( m_VideoWnd[i].GetSafeHwnd() ) )
        {
            continue;
        }

        if ( !m_VideoWnd[i].IsWindowVisible() ) 
        {
            continue;
        }

        HWND hCurrentWnd = m_SelectedWindow ;

        if ( hCurrentWnd != m_VideoWnd[i].m_hWnd ) 
        {
            continue;
        }
        
        ret = &m_VideoWnd[i] ;

        break ;
    }
    return ret ;
}
void CIPCPlayerDemoDlg::OnBnClickedPtzZoomIn()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_zoom(1) ;

        }else{
            //PTZ//!todo:!需要定义ptz的速度区间，暂用100
            
            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_zoom(1,ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedPtzZoomOut()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_zoom(-1) ;

        }else{
            //PTZ//!todo:!需要定义ptz的速度区间，暂用100

            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_zoom(0,ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonUp()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_up(50) ;
    
        }else{
            //PTZ
            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_up( ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;

        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonDown()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_down(50) ;
        }else{
            //PTZ
            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_down( ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonLeft()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_left(50) ;
        }else{
            //PTZ
            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_left( ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonRight()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_right(50) ;
        }else{
            //PTZ
            static BOOL ctrl_start_stop = FALSE ;

            lpVideoWnd->Ptz_right( ctrl_start_stop,m_HSpeed,m_VSpeed) ;

            ctrl_start_stop=!ctrl_start_stop ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedPtzHome()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_home() ;
        }else{
            //PTZ
            lpVideoWnd->Ptz_home(m_HSpeed,m_VSpeed) ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonSetpreset()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    int preset_num    = m_ctrlPresetList.GetItemData(m_ctrlPresetList.GetCurSel());

    if( lpVideoWnd )
    {
        UpdateData() ;

        CONST CHAR* lpPresetName = m_EdtPresetName.GetString() ;

        if( m_EdtPresetName.GetLength() == 0 )
        {
            lpPresetName = "无" ;
        }

        if( m_IsDptz )    
        {

            lpVideoWnd->Dptz_set_preset(preset_num,lpPresetName) ;

        }else{
            //PTZ
            lpVideoWnd->Ptz_set_preset(preset_num,lpPresetName) ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedButtonGoto()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    int preset_num    = m_ctrlPresetList.GetItemData(m_ctrlPresetList.GetCurSel());

    if( lpVideoWnd )
    {
        if( m_IsDptz )    
        {
            lpVideoWnd->Dptz_goto_preset(preset_num) ;

        }else{
            //PTZ
            lpVideoWnd->Ptz_goto_preset(preset_num,m_HSpeed,m_VSpeed) ;
        }

        lpVideoWnd->Invalidate(TRUE);

    }

}

void CIPCPlayerDemoDlg::OnBnClickedPtzFocusIn()
{
	;

	UpdateData();
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{
		//
		if(1 == m_occupation)
		{
			if( m_IsDptz )
			{
				static BOOL dptz_ctrl_start_stop = FALSE ;

				lpVideoWnd->Dptz_focus(FALSE,dptz_ctrl_start_stop) ;

				dptz_ctrl_start_stop =!dptz_ctrl_start_stop ;
			}
			//lpVideoWnd->Dptz_zoom(1) ;
			else
			{
				//PTZ
				//!todo:!需要定义ptz的速度区间，暂用100
				static BOOL ctrl_start_stop = FALSE ;

				lpVideoWnd->Ptz_focus(FALSE,ctrl_start_stop,m_HSpeed,m_VSpeed) ;

				ctrl_start_stop=!ctrl_start_stop ;
				SetTimer(TIME_FOCUS,100,NULL);
			}
		}

		lpVideoWnd->Invalidate(TRUE);

	}

}

void CIPCPlayerDemoDlg::OnBnClickedPtzFocusOut()
{
	;
	UpdateData();
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{

		if(1 == m_occupation)
		{
			if(m_IsDptz)
			{
				static BOOL dptz_ctrl_start_stop = FALSE ;

				lpVideoWnd->Dptz_focus(TRUE,dptz_ctrl_start_stop) ;

				dptz_ctrl_start_stop =!dptz_ctrl_start_stop ;
			}

			//lpVideoWnd->Dptz_zoom(-1) ;
			else
			{
				//PTZ
				//!todo:!需要定义ptz的速度区间，暂用100
				static BOOL ctrl_start_stop = FALSE ;

				lpVideoWnd->Ptz_focus(TRUE,ctrl_start_stop,m_HSpeed,m_VSpeed) ;

				ctrl_start_stop=!ctrl_start_stop ;
				 SetTimer(TIME_FOCUS,100,NULL);
			}
		}

		lpVideoWnd->Invalidate(TRUE);

	}

}

void CIPCPlayerDemoDlg::OnCheckBoxSelected()
{
     ;

    UpdateData() ;

    m_IsDptz = ((CButton*)GetDlgItem(IDC_CHECK_DPTZ))-> GetCheck(); 

    m_IsSavingJPEG = ((CButton*)GetDlgItem(IDC_CHECK_JPEG_SAVING))-> GetCheck(); 

}

void CIPCPlayerDemoDlg::OnHScroll(UINT sbCode, UINT iPos, CScrollBar* pSbar)
{
     ;

    CDialog::OnHScroll(sbCode,iPos,pSbar);

    CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_HSPEED);

     m_HSpeed = pSlidCtrl->GetPos();

    DOUBLE iMin = pSlidCtrl->GetRangeMin() ;

    DOUBLE iMax = pSlidCtrl->GetRangeMax() ;

    m_HSpeed_Scale = (iMax-iMax)/(m_HSpeed) ;

    pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_VSPEED);

    m_VSpeed = pSlidCtrl->GetPos();

    iMin = pSlidCtrl->GetRangeMin() ;

    iMax = pSlidCtrl->GetRangeMax() ;

    m_VSpeed_Scale = (iMax-iMax)/(m_VSpeed) ;

	CWnd *pSlidWnd=GetDlgItem(IDC_SLIDER_SHARPEN_DEGREE);
	if(pSlidWnd == pSbar)
	{
		AutoJudgeProSharpen();
	}
	

}

int CIPCPlayerDemoDlg::AutoJudgeProSharpen()
{
	int Pos = m_sliderSharDegree.GetPos(); //获得滑块的当前位置
	m_fSharDegree = Pos/20.0f;
	CString strTmp;
	strTmp.Format(_T("%d%%"),Pos);
	SetDlgItemText(IDC_STATIC_SHARPEN_DEGREE,strTmp);
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	if(NULL != lpVideoWnd )
	{
		if(Pos == 0)  //关闭锐化
		{
			lpVideoWnd->StopImageSharpen();
			m_bStartSharpen = FALSE;
		}
		else if(!m_bStartSharpen)
		{
			lpVideoWnd->StartImageSharpen(m_fSharDegree);
			m_bStartSharpen = TRUE;
		}
		else
		{
			lpVideoWnd->ChangeSharpenDegree(m_fSharDegree);
			m_bStartSharpen = TRUE;

		}
		return 0;

	}
	return -1;

}

void CIPCPlayerDemoDlg::OnBnClickedUserLogBtn()
{
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if(NULL != lpVideoWnd )
	{

		CLogViewDlg    dlgLogView(lpVideoWnd->GetSdkHandle(),this) ;

		if ( IDOK != dlgLogView.DoModal() )
		{
		}
	}
}

void CIPCPlayerDemoDlg::OnBnClickedButtonSystemsetting()
{
     ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        CSystemSettingDlg dlgSystemSettingView(lpVideoWnd->GetSdkHandle(), lpVideoWnd, this) ;

		dlgSystemSettingView.InitializeCallBack() ;

        if ( IDOK != dlgSystemSettingView.DoModal() )
        {
        }
		dlgSystemSettingView.UnInitializeCallBack() ;

    }
    
}

void CIPCPlayerDemoDlg::OnBnClickedButtonUpdate()
{
	 ;
   CUpdateSeviceDlg dlg(this) ;

   dlg.DoModal() ;

   m_bStartUpdateServer = dlg.IsStartUpdateService() ;

}

void CIPCPlayerDemoDlg::OnBnClickedButtonEventpanel()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	 ;

	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if (NULL == lpVideoWnd)
	{
		XINFO("CIPCPlayerDemoDlg::OnBnClickedButtonEventpanle --  GetSelectedWindowClass() == null");

		return ;
	}
	CEventSet dlgEventSet(this, lpVideoWnd->GetSdkHandle()) ;

	if ( IDOK != dlgEventSet.DoModal() )
	{
	}

	//OnTestSetEvent(lpVideoWnd, 1) ;

	//OnTestGetEvent(lpVideoWnd) ;

	//OnTestSetMDEvent(lpVideoWnd) ;

	//OnTestGetMDEvent(lpVideoWnd) ;

	//OnTestEnableEvent(lpVideoWnd) ;

	//OnTestIsEnableEvent(lpVideoWnd) ;

	//return ;

}

void CIPCPlayerDemoDlg::OnTestSetEvent(CVideoWnd* pWnd, int nActiveType)
{

}

void CIPCPlayerDemoDlg::OnTestGetEvent( CVideoWnd* pWnd )
{
	
}

void CIPCPlayerDemoDlg::OnTestEnableEvent( CVideoWnd* pWnd )
{

}

void CIPCPlayerDemoDlg::OnTestIsEnableEvent( CVideoWnd* pWnd )
{
	

}


void CIPCPlayerDemoDlg::OnBnClickedButtonShowActivex()
{
	CActiveDlg dlg(this);
	dlg.DoModal();
}

void CIPCPlayerDemoDlg::OnTestPropertySet( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}

	IPC_IMGIRIS iris;
	iris.iris_type = 1;
	iris.iris_quty = 100;
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_DCIRIS_GROUP, 0, (char*)&iris) ;

	IPC_IMGSHUTTER shutter;
	shutter.shutter_min = 64000;
	shutter.shutter_max = 68266667;
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_SHUTTER_GROUP, 0, (char*)&shutter) ;

	//IPC_IMGPM pm;
	//pm.pm_left = 0;
	//pm.pm_top = 0;
	//pm.pm_w = 10;
	//pm.pm_h = 10;
	//pm.pm_color = 0;
	//pm.pm_action = 0;
	//IPC_SetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_PM_GROUP, 0, (char*)&pm) ;

	IPC_SNTEXT text;
	text.text_streamID = 0;
	text.text_enable = 1;
	strcpy(text.text_content, "IPC text") ;
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_ENCODE_SN_TEXT_GROUP, 0, (char*)&text) ;

	/*IPC_ENCSN enc;
	enc.sn_type = 1;
	enc.sn_stream = 0;
	enc.sn_fps = 8533333;
	enc.sn_width = 1280;
	enc.sn_height = 720;
	enc.sn_rotate = 0;
	enc.SNPROPERTY.H264.sn_brc = 0;
	enc.SNPROPERTY.H264.sn_m = 1;
	enc.SNPROPERTY.H264.sn_n = 1;
	enc.SNPROPERTY.H264.sn_idrInterval = 1;
	enc.SNPROPERTY.H264.BPS.CBR.sn_cbr = 10000;
	IPC_SetConfig(pWnd->GetSdkHandle(), IPC_ENCODE_ENC_SN_GROUP, 0, (char*)&enc) ;*/

	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_EXPOSURE_MODE, 0, NULL) ;//2
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_AE_TARGET_RATION, 25, NULL) ;//400
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_MAX_GAIN, 30, NULL) ;//60
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_WBC, 0, NULL) ;//9
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_DN_MODE, 0, NULL) ;//2
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_BACKLIGHT_COMP, 1, NULL) ;//0
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_LOCAL_EXPOSURE, 1, NULL) ;//5
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_MCTF_STRENGTH, 255, NULL) ;//255
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_SLOW_SHUTTER, 1, NULL) ;//0
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_AE_PREFERENCE, 0, NULL) ;//2
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_VIDEO_METERING_MODE, 0, NULL) ;//3
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_ENCODE_ENC_MODE, 0, NULL) ;//2
	ipcSetConfig(pWnd->GetSdkHandle(), IPC_ENCODE_SN_TIME_ENABLE0, 1, NULL) ;//0

}

void CIPCPlayerDemoDlg::OnTestPropertyGet( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}
	
}

void CIPCPlayerDemoDlg::OnTestSetMDEvent( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}
	
}

void CIPCPlayerDemoDlg::OnTestGetMDEvent( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}
}

void CIPCPlayerDemoDlg::OnTestSystemSet( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}
	
}

void CIPCPlayerDemoDlg::OnTestSystemGet( CVideoWnd* pWnd )
{
	if (NULL == pWnd)
	{
		return ;
	}

}

void CIPCPlayerDemoDlg::OnBnClickedButtonConfigSetting()
{
	// TODO:
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if(NULL != lpVideoWnd )
	{
		CCameraConfigSetting dlgConfigSettingView(lpVideoWnd->GetSdkHandle(), lpVideoWnd, this) ;

		dlgConfigSettingView.InitializeCallBack() ;

		if ( IDOK != dlgConfigSettingView.DoModal() )
		{
		}
		dlgConfigSettingView.UnInitializeCallBack() ;

	}

}

void CIPCPlayerDemoDlg::OnBnClickedButtonPlan()
{
	// TODO: 
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if(NULL != lpVideoWnd )
	{
		CPlanSet plan(this, lpVideoWnd->GetSdkHandle()) ;
		plan.DoModal() ;
	}
	
}

void CIPCPlayerDemoDlg::OnBnClickedButtonAudio()
{
    CAudioDialog dlg(this) ;

    dlg.DoModal() ;

    
}

INT WINAPI MyAudioCallback(ipcHandle,INT type,const unsigned char* data,INT size,LPVOID context)
{//当失败发生时请析构语音对讲功能

    CIPCPlayerDemoDlg* lpThis = (CIPCPlayerDemoDlg*)context ;

    int i = 0 ;

    if( type == 2 )
    {//本端
        i=0 ;
    }

    if( type ==1)
    {//远端
        i = 1 ;
    }

    if( type ==-2)
    {
        //本端发送失败
        PostMessage(lpThis->m_hWnd,lpThis->WM_AUDIO_DISCONNECTION,0,0) ;
    }

    if( type == -1)
    {
        //接收远端失败
    }
    return i ;
}

int CIPCPlayerDemoDlg::AudioOpen(void)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {

        ipcSetAudioCallback(lpVideoWnd->GetSdkHandle(),MyAudioCallback,this) ;

        //--ipcAudioDone(lpVideoWnd->GetSdkHandle()) ;
        if( -1 == ipcAudioInit(lpVideoWnd->GetSdkHandle()) )
        {        
            AfxMessageBox(_T("初始化失败，设备可能已经被占用"));
            return -1;
        }

        if ( ipcSUCCESS == ipcAudioPlay(lpVideoWnd->GetSdkHandle()) )
		{
			AfxMessageBox(_T("启动语音对讲成功"));
		}
		else
		{
			ipcAudioDone(lpVideoWnd->GetSdkHandle());
			AfxMessageBox(_T("启动语音对讲失败"));
			return -1;
		}
    }
    return 0;
}

int CIPCPlayerDemoDlg::AudioEnumDevice(IPC_AudioDevice* device,int* size)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        ipcEnumAudioDevice(lpVideoWnd->GetSdkHandle(),device,(LONG*)size) ;
    }
    return *size ;
}

int CIPCPlayerDemoDlg::SetAudioDevice(IPC_AudioDevice ad) 
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        return ipcSetAudioDevice(lpVideoWnd->GetSdkHandle(),ad) ;
    }
    return 0 ;
}

int CIPCPlayerDemoDlg::GetAudioDeviceName(CString& str)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        IPC_AudioDevice ad ;

        memset(&ad,0,sizeof(ad)) ;

        ipcGetAudioDevice(lpVideoWnd->GetSdkHandle(),&ad) ;

        str = ad.sDevName ;
    }
    return 0 ;
}

int CIPCPlayerDemoDlg::AudioClose(void)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        if ( ipcSUCCESS != ipcAudioStop(lpVideoWnd->GetSdkHandle()) )
		{
			AfxMessageBox(_T("停止语音对讲失败"));
			return -1;
		}

        ipcAudioDone(lpVideoWnd->GetSdkHandle());
    }
    return 0;
}

int CIPCPlayerDemoDlg::SetAudioFormat(INT fmt) 
{
    dwAudioFmt = fmt ;
    return 0 ;
}

int CIPCPlayerDemoDlg::AudioOption()
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    IPC_AUDIOCONF_t ac ;

    ac.audio_enable = 1 ;
    ac.audio_in_vol = 50 ;
    ac.audio_out_enable = 1 ;
    ac.audio_out_vol = 50 ;
    ac.codec_fmt = dwAudioFmt ;
    ac.echo_canceller_enable = 1 ;

    if(NULL != lpVideoWnd )
    {
        ipcAudioSetting(lpVideoWnd->GetSdkHandle(),1,&ac) ;
    }

    return 0;
}

int CIPCPlayerDemoDlg::AudioVolume(int vol)
{

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    IPC_AUDIOCONF_t ac ;

    ac.audio_enable = 1 ;
    ac.audio_in_vol = vol ;
    ac.audio_out_enable = 1 ;
    ac.audio_out_vol = vol ;
    ac.codec_fmt = dwAudioFmt ;
    ac.echo_canceller_enable = 1 ;

    if(NULL != lpVideoWnd )
    {
        ipcAudioSetting(lpVideoWnd->GetSdkHandle(),1,&ac) ;
    }
    return 0 ;
}

int CIPCPlayerDemoDlg::GetAudioVolume()
{
    long volume = 0 ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        ipcGetVolume(lpVideoWnd->GetSdkHandle(),1,&volume) ;
    }

    return volume ;
}

LRESULT CIPCPlayerDemoDlg::OnSDKDisconnection(WPARAM wParam, LPARAM lParam)
{
    //AudioClose() ;
    ::MessageBoxA(0,"连接断开，请关闭音频",0,0) ;
    return 0 ;
}
void CIPCPlayerDemoDlg::OnBnClickedButtonPtzOpt()
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        CTransDlg td(this) ;

        td.DoModal() ;
    }
}

int CIPCPlayerDemoDlg::TransPropSet(DWORD protocol, DWORD address, DWORD baudrate, DWORD databit, DWORD stopbit, DWORD parity)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        IPC_COMM_PROP cp ;

        cp.byBaudRate = baudrate ;

        cp.byDataBit = databit ;

        cp.byParity = parity ;

        cp.byStopBit = stopbit ;

        if( ipcSUCCESS == ipcSetPTZTransProp(lpVideoWnd->GetSdkHandle(),protocol,address,&cp) )
        {
            return 0 ;
        }
    }
    MessageBoxA("设置失败") ;
    return -1;
}

int CIPCPlayerDemoDlg::TransPropGet(DWORD* protocol, DWORD* address, DWORD* baudrate, DWORD* databit, DWORD* stopbit, DWORD* parity)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        IPC_COMM_PROP cp ;

        if( ipcSUCCESS == ipcGetPTZTransProp(lpVideoWnd->GetSdkHandle(),protocol,address,&cp) )
        {
            *baudrate = cp.byBaudRate ;

            *databit = cp.byDataBit ;

            *parity = cp.byParity ;

            *stopbit = cp.byStopBit ;

            return 0;
        }
    }
    MessageBoxA("读取失败") ;
    return -1;
}

int CIPCPlayerDemoDlg::TransDataSend(unsigned char* data, int len)
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        if( ipcSUCCESS == ipcSetPTZTrans(lpVideoWnd->GetSdkHandle(),data,len) )
        {
            MessageBoxA("成功: 数据发送完毕。") ;
            return 0;
        }
    }

    return -1;

}

int CIPCPlayerDemoDlg::GetPtzPositionInfo(int* x, int* y, int* z, int* xSpeed,int* ySpeed)
{
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	IPC_PTZ_POSITION_PARAM pos ;
	memset(&pos, 0, sizeof(IPC_PTZ_POSITION_PARAM)) ;
	if(NULL != lpVideoWnd )
	{
		if (0 != ipcPTZPositionControl(lpVideoWnd->GetSdkHandle(), IPC_CMD_PTZ_GET_ABS_POSITION, &pos))
		{
			MessageBoxA("获取失败 !\t");
			return -1;
		}
		*x = pos.xPosition;
		*y = pos.yPosition;
		*z = pos.zPosition;
		*xSpeed = pos.xSpeed;
		*ySpeed = pos.ySpeed;
	}
	return 0;
}
int CIPCPlayerDemoDlg::GetAllPresetInfo()
{
    INT iRet = -1 ;

    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if(NULL != lpVideoWnd )
    {
        DWORD capacity = 0 ;

        CHAR szTemp[512]={0} ;

        std::string str ;

        if( ipcSUCCESS == ipcPTZGetCapacity(lpVideoWnd->GetSdkHandle(),&capacity) )
        {
            LPIPC_PRESET lpItem = new IPC_PRESET[capacity] ;

            iRet = ipcPTZGetAllPreset(lpVideoWnd->GetSdkHandle(),capacity,lpItem) ;

            for( int i = 0 ;i< capacity;i++ )
            {
                sprintf( szTemp,"idx=%d,enable=%d,name='%s'  ",lpItem[i].index,lpItem[i].enable,lpItem[i].name ) ;

                str+=szTemp ;
            }
            itoa(capacity,szTemp,10) ;
            ::MessageBoxA(0,str.c_str(),szTemp,0) ;
        }
    }

    return iRet ;
}
void CIPCPlayerDemoDlg::OnBnClickedBtnLeftborder()
{
	INT iRet = -1 ;
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
    if(NULL != lpVideoWnd )
    {
        if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_SET_LEFTBORDER,0,0,0) )
        {
            ::MessageBoxA(0,"控制失败","提示",0) ;
        }
    }
}

void CIPCPlayerDemoDlg::OnBnClickedBtnRightborder()
{
    INT iRet = -1 ;
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
    if(NULL != lpVideoWnd )
    {
        if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_SET_RIGHTBORDER,0,0,0) )
        {
            ::MessageBoxA(0,"控制失败","提示",0) ;
        }
    }
}

void CIPCPlayerDemoDlg::OnBnClickedStartLinrscan()
{
	INT iRet = -1 ;
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
    if(NULL != lpVideoWnd )
    {
        if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_AUTO_SCAN,0,50,0) )
        {
            ::MessageBoxA(0,"控制失败","提示",0) ;
        }
    }
}

void CIPCPlayerDemoDlg::OnBnClickedStopLinescan()
{
	INT iRet = -1 ;
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
    if(NULL != lpVideoWnd )
    {
        if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_AUTO_SCAN,1,0,0) )
        {
            ::MessageBoxA(0,"控制失败","提示",0) ;
        }
    }
}

void CIPCPlayerDemoDlg::OnBnClickedBtnOpen()
{
	INT sel = m_cmb_point.GetCurSel();
	if(sel <0) return ;

	INT nPoint = m_cmb_point.GetItemData(sel);

	INT iRet = -1 ;
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	if(NULL != lpVideoWnd )
	{
		if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_AUXIOPEN,nPoint,0,0) )
		{
			::MessageBoxA(0,"控制失败","提示",0) ;
		}
	}

}

void CIPCPlayerDemoDlg::OnBnClickedBtnClose()
{
	INT sel = m_cmb_point.GetCurSel();
	if(sel <0) return ;

	INT nPoint = m_cmb_point.GetItemData(sel);

	INT iRet = -1 ;
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	if(NULL != lpVideoWnd )
	{
		if( ipcSUCCESS != ipcPTZControl(lpVideoWnd->GetSdkHandle(),0,IPC_CMD_PTZ_AUXICLOSE,nPoint,0,0) )
		{
			::MessageBoxA(0,"控制失败","提示",0) ;
		}
	}
}

void CIPCPlayerDemoDlg::OnBnClickedButtonLeftup()
{
	 
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{

		static BOOL ctrl_start_stop = FALSE ;

		lpVideoWnd->Ptz_leftup( ctrl_start_stop,m_HSpeed,m_VSpeed) ;

		ctrl_start_stop=!ctrl_start_stop ;

		lpVideoWnd->Invalidate(TRUE);

	}
	
}

void CIPCPlayerDemoDlg::OnBnClickedButtonRightup()
{
	 
	 CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	 if( lpVideoWnd )
	 {
		 static BOOL ctrl_start_stop = FALSE ;
		 lpVideoWnd->Ptz_rightup( ctrl_start_stop,m_HSpeed,m_VSpeed) ;
		 ctrl_start_stop=!ctrl_start_stop ;
		 lpVideoWnd->Invalidate(TRUE);

	 }
}

 
void CIPCPlayerDemoDlg::OnBnClickedButtonLeftdown()
{
	 
	 CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	 if( lpVideoWnd )
	 {
		 static BOOL ctrl_start_stop = FALSE ;
		 lpVideoWnd->Ptz_leftdown( ctrl_start_stop,m_HSpeed,m_VSpeed) ;
		 ctrl_start_stop=!ctrl_start_stop ;
		 lpVideoWnd->Invalidate(TRUE);
	 }
}

void CIPCPlayerDemoDlg::OnBnClickedButtonRightdown()
{
	  CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

    if( lpVideoWnd )
    {
       static BOOL ctrl_start_stop = FALSE ;
        lpVideoWnd->Ptz_rightdown( ctrl_start_stop,m_HSpeed,m_VSpeed) ;
       ctrl_start_stop=!ctrl_start_stop ;
        lpVideoWnd->Invalidate(TRUE);
    }
}

void CIPCPlayerDemoDlg::OnBnClickedButton6()
{
    CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
    if( lpVideoWnd )
    {
      
        lpVideoWnd->Ptz_rotaion(m_HSpeed,m_VSpeed) ;
      
        lpVideoWnd->Invalidate(TRUE);
    }
}

void CIPCPlayerDemoDlg::OnBnClickedButtonTestTriggerAlarmOutput()
{
	INT sel = m_cmb_point.GetCurSel();
	if(sel <0) return ;

	INT nPoint = m_cmb_point.GetItemData(sel);

	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	if(NULL != lpVideoWnd )
	{
		if( ipcSUCCESS != ipcTriggerAlarmOutput(lpVideoWnd->GetSdkHandle(), 0, 10000 ) )
		{
			::MessageBoxA(0,"触发警报输出失败","提示",0) ;
		}
		else
		{
			::MessageBoxA(0,"触发警报输出成功","提示",0) ;
		}
	}
}

void CIPCPlayerDemoDlg::OnCbnSelchangeComboFocus()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{
		if(0 == m_cmbFocus.GetCurSel())
		{
			lpVideoWnd->setFocusMode(1);
		}
		else if(1 == m_cmbFocus.GetCurSel())
		{
			lpVideoWnd->setFocusMode(2);
		}


	}

}

void CIPCPlayerDemoDlg::OnBnClickedRadioAuto()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FOCUS)->EnableWindow(TRUE);
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{
		if(0 == m_cmbFocus.GetCurSel())
		{
			lpVideoWnd->setFocusMode(1);
		}
		else if(1 == m_cmbFocus.GetCurSel())
		{
			lpVideoWnd->setFocusMode(2);
		}


	}

}

void CIPCPlayerDemoDlg::OnBnClickedRadioManual()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_FOCUS)->EnableWindow(FALSE);
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if( lpVideoWnd )
	{

		lpVideoWnd->setFocusMode(0);
	}
}


void CIPCPlayerDemoDlg::OnBnClickedButton3dPositionTakeEffect()
{
	UpdateData( TRUE );

	INT sel = m_cmb_point.GetCurSel();
	if(sel <0) return ;

	INT nPoint = m_cmb_point.GetItemData(sel);

	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;
	if(NULL != lpVideoWnd )
	{
		IPC_PTZ3DCTRL Ptz3DParam;
		Ptz3DParam.iX = m_3D_X;
		Ptz3DParam.iY = m_3D_Y;
		Ptz3DParam.iW = m_3D_Width;
		Ptz3DParam.iH = m_3D_Height;

		if( ipcSUCCESS != ipcPtz3DCtrl(lpVideoWnd->GetSdkHandle(), Ptz3DParam ) )
		{
			::MessageBoxA(0,"3D控制失败","提示",0) ;
		}
	}
}

void CIPCPlayerDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;


	switch(nIDEvent)
	{
	case TIME_FOCUS:
		if( lpVideoWnd )
		{
			KillTimer(TIME_FOCUS);
			lpVideoWnd->Ptz_focus(FALSE,TRUE,0,0) ;
		}

		break;
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CIPCPlayerDemoDlg::OnBnClickedButtonPtzPositionParam()
{
	// TODO: Add your control notification handler code here
	CVideoWnd* lpVideoWnd = GetSelectedWindowClass() ;

	if(NULL != lpVideoWnd )
	{
		CPtzPositionParamDlg pd(this) ;

		pd.DoModal() ;
	}
}
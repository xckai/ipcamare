// LoginDlg.cpp : implementation file
//

#include "stdafx.h"

#include "IPCSdkFuncDemo.h"

#include "UpdateSeviceDlg.h"


#include "IPCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateSeviceDlg dialog


CUpdateSeviceDlg::CUpdateSeviceDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUpdateSeviceDlg::IDD, pParent)
{
    m_SevicePort = 8990;
	m_bStartUpdateService = false ; 
 
}


void CUpdateSeviceDlg::DoDataExchange(CDataExchange* pDX)
{
     CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CUpdateSeviceDlg)
    //DDX_Control(pDX, IDC_LIST_USER_LOG, m_listLogView);
    //}}AFX_DATA_MAP
    DDX_Text(pDX,IDC_EDIT_SEVICE_PORT,m_SevicePort);
}


BEGIN_MESSAGE_MAP(CUpdateSeviceDlg, CDialog)
    //{{AFX_MSG_MAP(CUpdateSeviceDlg)
    //}}AFX_MSG_MAP
    //ON_BN_CLICKED(IDOK, &CUpdateSeviceDlg::OnBnClickedOk)

    ON_BN_CLICKED(IDC_BUTTON_SEVICE_START, &CUpdateSeviceDlg::OnBnClickedStart)
    ON_BN_CLICKED(IDC_BUTTON_SEVICE_STOP, &CUpdateSeviceDlg::OnBnClickedStop)

	ON_BN_CLICKED(IDOK_UPDATE, &CUpdateSeviceDlg::OnBnClickedUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateSeviceDlg message handlers


BOOL CUpdateSeviceDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

 
    return TRUE;  // return TRUE unless you set the focus to a control
}

void CUpdateSeviceDlg::OnOK() 
{
    CDialog::OnOK();
}

void CUpdateSeviceDlg::OnBnClickedStart()
{
    UpdateData() ;
    ipcUpdateServiceStart(m_SevicePort) ;
	m_bStartUpdateService = true;
}
void CUpdateSeviceDlg::OnBnClickedStop()
{
    ipcUpdateServiceStop() ;
	m_bStartUpdateService = false;
}

bool CUpdateSeviceDlg::IsStartUpdateService()
{
	return m_bStartUpdateService;
}

void CUpdateSeviceDlg::OnBnClickedUpdate()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnOK() ;
}

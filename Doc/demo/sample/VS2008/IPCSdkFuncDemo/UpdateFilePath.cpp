// UpdateFilePath.cpp : 实现文件
//

#include "stdafx.h"
#include "IPCSdkFuncDemo.h"
#include "UpdateFilePath.h"


// CUpdateFilePath 对话框

IMPLEMENT_DYNAMIC(CUpdateFilePath, CDialog)

CUpdateFilePath::CUpdateFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateFilePath::IDD, pParent)
{

}

CUpdateFilePath::~CUpdateFilePath()
{
}

void CUpdateFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_IP,m_strIP);
	DDX_Text(pDX,IDC_EDIT_FILE_PATH, m_strPath) ;
	//DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
}


BEGIN_MESSAGE_MAP(CUpdateFilePath, CDialog)
	ON_BN_CLICKED(IDOK, &CUpdateFilePath::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdateFilePath::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CUpdateFilePath::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUpdateFilePath 消息处理程序

void CUpdateFilePath::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	UpdateData(TRUE);
	OnOK();
}

void CUpdateFilePath::OnBnClickedButton1()
{
	CFileDialog dlgfile(TRUE);

	if (IDOK == dlgfile.DoModal())
	{
		m_strPath = dlgfile.GetPathName() ; 
		UpdateWindow();
		UpdateData(FALSE);
	}
}

void CUpdateFilePath::GetUpdateFilePath( CString& strPath_ )
{
	strPath_ = m_strPath;
}

void CUpdateFilePath::SetUpdateIp( CString& strIp )
{
	m_strIP = strIp ;
}

void CUpdateFilePath::OnBnClickedCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnCancel();
}

// LoginDlg.cpp : implementation file
//

#include "stdafx.h"

#include "SystemSetting.h"

#include "IPCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg dialog


CSystemSettingDlg::CSystemSettingDlg(LPVOID hSdk_, CVideoWnd* pVideoWnd_, CWnd* pParent /*=NULL*/)
: CDialog(CSystemSettingDlg::IDD, pParent)
, m_strSystemData1(_T(""))
, m_strSystemData2(_T(""))
, m_strSystemData3(_T(""))
, m_strSystemData4(_T(""))
, m_dwSystemSetData1(0)
, m_dwSystemSetData2(0)
, m_dwSystemSetData3(0)
, m_dwSystemSetData4(0)
, m_strSystemData5(_T(""))
, m_strSystemSetData5(_T(""))
, m_strSystemData6(_T(""))
, m_strSystemData7(_T(""))
, m_strSystemData8(_T(""))
, m_strSystemSetData6(_T(""))
, m_strSystemSetData7(_T(""))
, m_strSystemSetData8(_T(""))
, m_strSystemData9(_T(""))
, m_strSystemData10(_T(""))
, m_strSystemData11(_T(""))
, m_strSystemData12(_T(""))
, m_strSystemSetData9(_T(""))
, m_strSystemSetData10(_T(""))
, m_strSystemSetData11(_T(""))
, m_strSystemSetData12(_T(""))
{
     ;

    m_systemsettingValue = "" ;

    m_hSdkHandle = hSdk_ ;

	m_pVideoWnd = pVideoWnd_ ;

    m_cmd = 0 ;
}

CSystemSettingDlg::~CSystemSettingDlg()
{
	UnInitializeCallBack();
	m_pVideoWnd = NULL ;
}

void CSystemSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	 ;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemSettingDlg)
	DDX_Control(pDX, IDC_COMBO_SYSTEMSETTING, m_cmdList);
	//DDX_Text(pDX,IDC_EDIT_SYSTEMSETTING,m_systemsettingValue) ;
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA1, m_strSystemData1);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA2, m_strSystemData2);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA3, m_strSystemData3);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA4, m_strSystemData4);

	DDX_Text(pDX, IDC_EDIT_SYSTEM1, m_dwSystemSetData1);
	//DDV_MinMaxLong(pDX, m_dwSystemSetData1, 1, 65535);

	DDX_Text(pDX, IDC_EDIT_SYSTEM2, m_dwSystemSetData2);
	//DDV_MinMaxLong(pDX, m_dwSystemSetData2, 1, 65535);

	DDX_Text(pDX, IDC_EDIT_SYSTEM3, m_dwSystemSetData3);
	//DDV_MinMaxLong(pDX, m_dwSystemSetData3, 1, 65535);

	DDX_Text(pDX, IDC_EDIT_SYSTEM4, m_dwSystemSetData4);
	//DDV_MinMaxLong(pDX, m_dwSystemSetData4, 1, 65535);

	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA5, m_strSystemData5);

	DDX_Text(pDX, IDC_EDIT_SYSTEM5, m_strSystemSetData5);
	//DDV_MaxChars(pDX, m_strSystemSetData5, 256);

	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA6, m_strSystemData6);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA7, m_strSystemData7);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA8, m_strSystemData8);

	DDX_Text(pDX, IDC_EDIT_SYSTEM6, m_strSystemSetData6);
	//DDV_MaxChars(pDX, m_strSystemSetData6, 256);

	DDX_Text(pDX, IDC_EDIT_SYSTEM7, m_strSystemSetData7);
	DDV_MaxChars(pDX, m_strSystemSetData7, 256);

	DDX_Text(pDX, IDC_EDIT_SYSTEM8, m_strSystemSetData8);
	//DDV_MaxChars(pDX, m_strSystemSetData8, 256);

	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA9, m_strSystemData9);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA10, m_strSystemData10);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA11, m_strSystemData11);
	DDX_Text(pDX, IDC_EDIT_SYSTEM_DATA12, m_strSystemData12);

	DDX_Text(pDX, IDC_EDIT_SYSTEM9, m_strSystemSetData9);
	//DDV_MaxChars(pDX, m_strSystemSetData9, 256);
	DDX_Text(pDX, IDC_EDIT_SYSTEM10, m_strSystemSetData10);
	//DDV_MaxChars(pDX, m_strSystemSetData10, 256);
	DDX_Text(pDX, IDC_EDIT_SYSTEM11, m_strSystemSetData11);
	//DDV_MaxChars(pDX, m_strSystemSetData11, 256);
	DDX_Text(pDX, IDC_EDIT_SYSTEM12, m_strSystemSetData12);
	//DDV_MaxChars(pDX, m_strSystemSetData12, 256);
}


BEGIN_MESSAGE_MAP(CSystemSettingDlg, CDialog)
    //{{AFX_MSG_MAP(CSystemSettingDlg)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_SYSTEMSETTING_SET, &CSystemSettingDlg::OnBnClickedButtonSystemsettingSet)
    ON_BN_CLICKED(IDC_BUTTON_SYSTEMSETTING_GET, &CSystemSettingDlg::OnBnClickedButtonSystemsettingGet)
	ON_CBN_SELCHANGE(IDC_COMBO_SYSTEMSETTING, &CSystemSettingDlg::OnCbnSelchangeComboSystemsetting)
	ON_BN_CLICKED(IDC_RADIO_SYSTEM_DISABLE, &CSystemSettingDlg::OnBnClickedRadioSystemDisable)
	ON_BN_CLICKED(IDC_RADIO_SYSTEM_ABLE, &CSystemSettingDlg::OnBnClickedRadioSystemAble)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CSystemSettingDlg::OnBnClickedButtonRestart)
	//ON_BN_CLICKED(IDC_BUTTON_DEFAULT, &CSystemSettingDlg::OnBnClickedButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_WAITING, &CSystemSettingDlg::OnBnClickedButtonWaiting)
	ON_BN_CLICKED(IDC_BUTTON_WAKEUP, &CSystemSettingDlg::OnBnClickedButtonWakeup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg message handlers


BOOL CSystemSettingDlg::OnInitDialog() 
{
     ;

    CDialog::OnInitDialog();

    DWORD lCurSel = 0 ;

 	lCurSel = m_cmdList.AddString("SETGET_IPINFO");
 	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SETGET_IPINFO);

 	lCurSel = m_cmdList.AddString("SETGET_SMTP");
 	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SETGET_SMTPINFO);

	lCurSel = m_cmdList.AddString("SETGET_FTPINFO");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SETGET_FTPINFO);

	lCurSel = m_cmdList.AddString("UPNP");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SETGET_UPNPINFO);

	lCurSel = m_cmdList.AddString("SETGET_DATEINFO");
	m_cmdList.SetItemData(lCurSel,  IPC_SYSTEM_SETGET_DATEINFO);

	lCurSel = m_cmdList.AddString("更新设备时间");
	m_cmdList.SetItemData(lCurSel,  IPC_SYSTEM_SETGET_DATEINFOEX);

	lCurSel = m_cmdList.AddString("GET_RTP_ADDR1");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_RTP_ADDR);

	lCurSel = m_cmdList.AddString("GET_RTP_ADDR2");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_RTP_ADDR2);

	lCurSel = m_cmdList.AddString("GET_RTP_ADDR3");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_RTP_ADDR3);

	lCurSel = m_cmdList.AddString("GET_RTP_ADDR4");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_RTP_ADDR4);

	lCurSel = m_cmdList.AddString("GET_SD_STATUS");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SD_STATUS);

	lCurSel = m_cmdList.AddString("GET_SD_RW");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SD_RW);

	lCurSel = m_cmdList.AddString("GET_SD_SPACE");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SD_SPACE);

	lCurSel = m_cmdList.AddString("GET_SD_FREE_SAPCE");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SD_FREE_SAPCE);

	lCurSel = m_cmdList.AddString("SET_SD_CMD");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SET_SD_CMD);

	lCurSel = m_cmdList.AddString("GET_DEVICE_NAME");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_DEVICE_NAME);

	lCurSel = m_cmdList.AddString("GET_DEVICE_MANUFACTURER");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_DEVICE_MANUFACTURER);

	lCurSel = m_cmdList.AddString("GET_FW_VERSION");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_FW_VERSION);
	lCurSel = m_cmdList.AddString("GET_HW_VERSION");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_HW_VERSION);
    lCurSel = m_cmdList.AddString("GET_DEVICE_SN");
    m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_DEVICE_SN);
    

	lCurSel = m_cmdList.AddString("GET_REC_FILES");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_REC_FILES);

	lCurSel = m_cmdList.AddString("SET_REC_DEL_FILES");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SET_REC_DEL_FILES);

	lCurSel = m_cmdList.AddString("SET_REC_UPLOAD_FILES");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_SET_REC_UPLOAD_FILES);

	lCurSel = m_cmdList.AddString("设备GB支持能力");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SUPPORT_GB);

	lCurSel = m_cmdList.AddString("设备rtsp支持能力");
	m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_GET_SUPPORT_RTSP);

 	//lCurSel = m_cmdList.AddString("UPNP_ENABLE");
 	//m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_UPNP_ENABLE);

 	//lCurSel = m_cmdList.AddString("UPNP_PORT");
 	//m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_UPNP_PORT);

 	//lCurSel = m_cmdList.AddString("UPNP_NAME");
 	//m_cmdList.SetItemData(lCurSel, IPC_SYSTEM_UPNP_NAME);


	CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;

	m_cmdList.SetCurSel(0) ;

	DisableAll() ;

    return TRUE;  // return TRUE unless you set the focus to a control
}


void CSystemSettingDlg::OnBnClickedButtonSystemsettingSet()
{
// 	OnTestSystemSettingGroupSet() ;
// 
// 	OnTestSysTemSettingSet() ;
// 	return ;
    UpdateData() ;
 
    m_cmd = m_cmdList.GetItemData(m_cmdList.GetCurSel()) ;
 
 	switch (m_cmd)
 	{
 	case IPC_SYSTEM_SETGET_IPINFO:
 		{
			IPC_SYSIPINFO ipInfo ;
			memset(&ipInfo, 0, sizeof(IPC_SYSIPINFO)) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;
 			if (IDC_RADIO_SYSTEM_ABLE == nCurSel) //不需要设置
 			{
				ipInfo.dhcp_enable = 1;
				
 			}
 			else if (IDC_RADIO_SYSTEM_DISABLE == nCurSel) // 都需要设置
 			{
				ipInfo.dhcp_enable = 0;
				strcpy(ipInfo.ip_addr, m_strSystemSetData5.GetBuffer()) ;
				strcpy(ipInfo.network_mask, m_strSystemSetData6.GetBuffer()) ;
				strcpy(ipInfo.dns_addr, m_strSystemSetData7.GetBuffer()) ;
				strcpy(ipInfo.dns_backup_addr, m_strSystemSetData8.GetBuffer()) ;
				strcpy(ipInfo.gateway_addr, m_strSystemSetData9.GetBuffer()) ;
				//strcpy(ipInfo.mac_addr, )

 			}

			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_IPINFO, 0, (const char*)&ipInfo) ;
 		}break ;
 	case IPC_SYSTEM_SETGET_SMTPINFO:
 		{
			IPC_SYSSMTP smtp;
			memset(&smtp, 0, sizeof(IPC_SYSSMTP)) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;

 			if (IDC_RADIO_SYSTEM_ABLE == nCurSel) //需要设置
 			{
				smtp.smtp_auth_enable = 1;
				strcpy(smtp.smtp_addr, m_strSystemSetData5.GetBuffer()) ;
				smtp.smtp_port = m_dwSystemSetData1 ;
				smtp.smtp_auth_enable = m_dwSystemSetData2;
				if (m_dwSystemSetData2 == 1)
				{
					strcpy(smtp.smtp_auth_name, m_strSystemSetData6.GetBuffer()) ;
					strcpy(smtp.smtp_auth_password, m_strSystemSetData7.GetBuffer()) ;
					smtp.smtp_auth_model = m_dwSystemSetData3 ;
				}
				strcpy(smtp.smtp_sender, m_strSystemSetData8.GetBuffer()) ;
				strcpy(smtp.smtp_receiver, m_strSystemSetData9.GetBuffer()) ;
				strcpy(smtp.smtp_cc, m_strSystemSetData10.GetBuffer()) ;
				strcpy(smtp.smtp_subject, m_strSystemSetData11.GetBuffer()) ;
				strcpy(smtp.smtp_content, m_strSystemSetData12.GetBuffer()) ;
 			}
 			else if (IDC_RADIO_SYSTEM_DISABLE == nCurSel) // 都bu需要设置
 			{
				smtp.smtp_auth_enable = 0;
 			}

			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_SMTPINFO, 0, (const char*)&smtp) ;
 		}break ;
 	case IPC_SYSTEM_SETGET_FTPINFO:
 		{
			IPC_SYSFTP ftp;
			memset(&ftp, 0, sizeof(IPC_SYSFTP)) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;

 			if (IDC_RADIO_SYSTEM_ABLE == nCurSel) //需要设置
 			{
				ftp.ftp_enable = 1 ;
				strcpy(ftp.ftp_addr, m_strSystemSetData5.GetBuffer()) ;
				strcpy(ftp.ftp_user, m_strSystemSetData6.GetBuffer()) ;
				strcpy(ftp.ftp_password, m_strSystemSetData7.GetBuffer()) ;
				ftp.ftp_port = m_dwSystemSetData1 ;
 			}
 			else if (IDC_RADIO_SYSTEM_DISABLE == nCurSel) // 都bu需要设置
 			{
				ftp.ftp_enable = 0 ;
 			}

			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_FTPINFO, 0, (const char*)&ftp) ;
 		}break;
 	case IPC_SYSTEM_SETGET_DATEINFO:
 		{
			IPC_SYSDATEINFO dateInfo;
			memset(&dateInfo, 0, sizeof(IPC_SYSDATEINFO)) ;

			dateInfo.sync_mode = m_dwSystemSetData1 ;

 			if ( m_dwSystemSetData1 == 0 )
 			{
				strcpy(dateInfo.ntp_addr, m_strSystemSetData7.GetBuffer()) ;
 			}
 			else if ( (m_dwSystemSetData1 == 1) || (m_dwSystemSetData1 == 2) )
 			{
				strcpy(dateInfo.time_date, m_strSystemSetData5.GetBuffer()) ;
				strcpy(dateInfo.time_time, m_strSystemSetData6.GetBuffer()) ;
 			}
 
 			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_DATEINFO, 0, (const char*)&dateInfo) ;	
 		}break ;
	case IPC_SYSTEM_SETGET_DATEINFOEX:
		{
			IPC_SYSDATEINFOEX dateInfo;
			memset(&dateInfo, 0, sizeof(IPC_SYSDATEINFOEX)) ;

			dateInfo.sync_mode = m_dwSystemSetData1 ;
			strcpy(dateInfo.timeZone, m_strSystemSetData8.GetBuffer()) ;

			if ( m_dwSystemSetData1 == 0 )
			{
				strcpy(dateInfo.ntp_addr, m_strSystemSetData7.GetBuffer()) ;
				dateInfo.interval = m_dwSystemSetData2 ;
			}
			else if ( (m_dwSystemSetData1 == 1) || (m_dwSystemSetData1 == 2) )
			{
				strcpy(dateInfo.time_date, m_strSystemSetData5.GetBuffer()) ;
				strcpy(dateInfo.time_time, m_strSystemSetData6.GetBuffer()) ;
			}
			else if (m_dwSystemSetData1 == 3)
			{
				strcpy(dateInfo.ntp_addr, m_strSystemSetData7.GetBuffer()) ;
				dateInfo.interval = m_dwSystemSetData2 ;
			}

			int nRet = ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_DATEINFOEX, 0, (CHAR*)&dateInfo) ;
			if (nRet != 0)
			{
				MessageBox(_T("更新时间"), _T("失败"), 0);  
			}
			else
			{
				MessageBox(_T("更新时间"), _T("成功"), 0);  
			}
		}break ;
	case IPC_SYSTEM_SETGET_UPNPINFO:
		{
			IPC_SYSUPNPINFO upnp;
			memset(&upnp, 0, sizeof(IPC_SYSUPNPINFO)) ;

			upnp.enable = m_dwSystemSetData1 ;
			upnp.port = m_dwSystemSetData2 ;
			strcpy(upnp.name, m_strSystemSetData5.GetBuffer()) ;

			ipcSetSystemSetting(m_hSdkHandle, m_cmd, 0, (const char*)&upnp) ;
		}break ;
 	case IPC_SYSTEM_SET_SD_CMD:
 		{
 			ipcSetSystemSetting(m_hSdkHandle, m_cmd, m_dwSystemSetData1, NULL) ;
 		}break ;
 	case IPC_SYSTEM_SET_REC_DEL_FILES:
 		{
 			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SET_REC_DEL_FILES, 0, m_strSystemSetData5.GetBuffer()) ;
 		}break;
 	case IPC_SYSTEM_SET_REC_UPLOAD_FILES:
 		{
 			ipcSetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SET_REC_UPLOAD_FILES, 0, m_strSystemSetData5.GetBuffer()) ;
 		}break ;
 	default:
 		{
 		
 		}break;
 	}
 
    // IPC_SetSystemSetting(m_hSdkHandle,m_cmd,m_systemsettingValue.GetBuffer()) ;


}

void CSystemSettingDlg::OnBnClickedButtonSystemsettingGet()
{
  //  UpdateData() ;
	//OnTestSystemSettingGet() ;
	//return;

    m_cmd = m_cmdList.GetItemData(m_cmdList.GetCurSel()) ;

	switch (m_cmd)
	{
	case IPC_SYSTEM_SETGET_IPINFO:
		{	
			IPC_SYSIPINFO ipInfo;
			memset(&ipInfo, 0, sizeof(IPC_SYSIPINFO)) ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&ipInfo) ;

			if (ipInfo.dhcp_enable == 1)
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
			}
			else
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;

				m_strSystemSetData5 = ipInfo.ip_addr ;
				m_strSystemSetData6 = ipInfo.network_mask ;
				m_strSystemSetData7 = ipInfo.dns_addr ;
				m_strSystemSetData8 = ipInfo.dns_backup_addr ;
				m_strSystemSetData9 = ipInfo.gateway_addr ;
			}

			UpdateData(FALSE) ;
		}break ;
	case IPC_SYSTEM_SETGET_SMTPINFO:
		{
			IPC_SYSSMTP smtp;
			memset(&smtp, 0, sizeof(IPC_SYSSMTP)) ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&smtp) ;

			if (smtp.smtp_enable == 0)
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, FALSE) ;
			}
			else if (smtp.smtp_enable == 1 )
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, TRUE) ;

				m_strSystemSetData5 = smtp.smtp_addr ;
				m_dwSystemSetData1 = smtp.smtp_port;
				m_dwSystemSetData2 = smtp.smtp_auth_enable;
				if (m_dwSystemSetData2 == 1)
				{
					m_strSystemSetData6 = smtp.smtp_auth_name ;
					m_strSystemSetData7 = smtp.smtp_auth_password ;
					m_dwSystemSetData3 = smtp.smtp_auth_model ;
				}
				m_strSystemSetData8 =smtp.smtp_sender ;
				m_strSystemSetData9 = smtp.smtp_receiver ;
				m_strSystemSetData10 = smtp.smtp_cc ;
				m_strSystemSetData11 = smtp.smtp_subject;
				m_strSystemSetData12 = smtp.smtp_content ;
			}

			UpdateData(FALSE) ;
		}break;
	case IPC_SYSTEM_SETGET_FTPINFO:
		{
			IPC_SYSFTP ftp;
			memset(&ftp, 0, sizeof(IPC_SYSFTP)) ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&ftp) ;

			if (ftp.ftp_enable == 0)
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
			}
			else if (ftp.ftp_enable == 1 )
			{
				CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;

				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;

				m_strSystemSetData5 = ftp.ftp_addr ;
				m_strSystemSetData6 = ftp.ftp_user ;
				m_strSystemSetData7 = ftp.ftp_password ;
				m_dwSystemSetData1 = ftp.ftp_port;
			}

			UpdateData(FALSE) ;
		}break;
	case IPC_SYSTEM_SETGET_DATEINFO:
		{
			IPC_SYSDATEINFO dateInfo;
			memset(&dateInfo, 0, sizeof(IPC_SYSDATEINFO)) ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&dateInfo) ;

			m_dwSystemSetData1 = dateInfo.sync_mode ;

			//if ( m_dwSystemSetData1 == 0 )
			//{
			m_strSystemSetData7 = dateInfo.ntp_addr ;
			//}
			//else if ( (m_dwSystemSetData1 == 1) || (m_dwSystemSetData1 == 2) )
			//{
			m_strSystemSetData5 = dateInfo.time_date ;
			m_strSystemSetData6 = dateInfo.time_time ;
			//}

			UpdateData(FALSE) ;	
		}break ;
	case IPC_SYSTEM_SETGET_DATEINFOEX:
		{
			IPC_SYSDATEINFOEX dateInfo;
			memset(&dateInfo, 0, sizeof(IPC_SYSDATEINFOEX)) ;

			ipcGetSystemSetting(m_hSdkHandle, IPC_SYSTEM_SETGET_DATEINFOEX, 0, (CHAR*)&dateInfo) ;

			m_dwSystemSetData1 = dateInfo.sync_mode ;
			m_dwSystemSetData2 = dateInfo.interval ;

			m_strSystemSetData7 = dateInfo.ntp_addr ;
			m_strSystemSetData5 = dateInfo.time_date ;
			m_strSystemSetData6 = dateInfo.time_time ;
			m_strSystemSetData8 = dateInfo.timeZone ;

			UpdateData(FALSE) ;	
		}break ;
	case IPC_SYSTEM_SETGET_UPNPINFO:
		{
			IPC_SYSUPNPINFO upnp;
			memset(&upnp, 0, sizeof(IPC_SYSUPNPINFO)) ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&upnp) ;

			m_dwSystemSetData1 = upnp.enable ;
			m_dwSystemSetData2 = upnp.port ;
			m_strSystemSetData5 = upnp.name ;

			UpdateData(FALSE) ;
		}break ;
	case IPC_SYSTEM_GET_SD_STATUS:
	case IPC_SYSTEM_GET_SD_RW:
	case IPC_SYSTEM_GET_SD_SPACE:
	case IPC_SYSTEM_GET_SD_FREE_SAPCE:
//	case IPC_SYSTEM_UPNP_ENABLE:
//	case IPC_SYSTEM_UPNP_PORT:
		{
			DWORD dwValue =0 ;

			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, (CHAR*)&dwValue) ;
			m_dwSystemSetData1 = dwValue ;

			UpdateData(FALSE) ;
		}break ;		
	case IPC_SYSTEM_GET_RTP_ADDR:				
	case IPC_SYSTEM_GET_RTP_ADDR2:				
	case IPC_SYSTEM_GET_RTP_ADDR3:			
	case IPC_SYSTEM_GET_RTP_ADDR4:				
	case IPC_SYSTEM_GET_DEVICE_NAME:
	case IPC_SYSTEM_GET_DEVICE_MANUFACTURER:
	case IPC_SYSTEM_GET_FW_VERSION:
	case IPC_SYSTEM_GET_HW_VERSION:
    case IPC_SYSTEM_GET_DEVICE_SN:
	case IPC_SYSTEM_GET_REC_FILES:
//	case IPC_SYSTEM_UPNP_NAME:
		{
			char str[256]= {0} ;
			ipcGetSystemSetting(m_hSdkHandle, m_cmd, 0, str) ;
			m_strSystemSetData5 = str ;
			UpdateData(FALSE) ;
		}break ;
	case IPC_SYSTEM_GET_SUPPORT_GB:
		{
			DWORD	dwEnable = 0 ;
			ipcGetSystemSetting(m_hSdkHandle, IPC_SYSTEM_GET_SUPPORT_GB, 0, (CHAR*)&dwEnable) ;
			if (dwEnable != 0)
			{
				m_strSystemSetData5 = _T("支持") ;
			}
			else
			{
				m_strSystemSetData5 = _T("不支持") ;
			}
			UpdateData(FALSE) ;
		}break ;
	case IPC_SYSTEM_GET_SUPPORT_RTSP:
		{
			DWORD	dwEnable = 0 ;
			ipcGetSystemSetting(m_hSdkHandle, IPC_SYSTEM_GET_SUPPORT_RTSP, 0, (CHAR*)&dwEnable) ;
			if (dwEnable != 0)
			{
				m_strSystemSetData5 = _T("支持") ;
			}
			else
			{
				m_strSystemSetData5 = _T("不支持") ;
			}
			UpdateData(FALSE) ;
		}break ;
	}

   // IPC_GetSystemSetting(m_hSdkHandle, m_cmd) ;
}

void CSystemSettingDlg::OnCbnSelchangeComboSystemsetting()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	 ;
	DisableAll() ;
	m_cmd = m_cmdList.GetItemData(m_cmdList.GetCurSel()) ;

 	switch (m_cmd)
 	{
 	case IPC_SYSTEM_SETGET_IPINFO:
 		{	
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_DISABLE)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_ABLE)->m_hWnd, TRUE) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;
 			if (IDC_RADIO_SYSTEM_DISABLE == nCurSel) // 都需要设置
 			{
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
 			}
 			
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, TRUE) ;
 		
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 
 			m_strSystemData5 = _T("IP_ADDR(字符串)");
 			m_strSystemData6 = _T("NETWORK_MASK(字符串)");
 			m_strSystemData7 = _T("DNS_ADDR(字符串)");
 			m_strSystemData8 = _T("DNS_BACKUP_ADDR(字符串)");
 			m_strSystemData9 = _T("GATEWAY_ADDR(字符串)");
 			m_strSystemData10 = _T("MAC_ADDR(字符串)") ;
 
 		}break ;
 	case IPC_SYSTEM_SETGET_SMTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_DISABLE)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_ABLE)->m_hWnd, TRUE) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;
 			if (IDC_RADIO_SYSTEM_ABLE == nCurSel) // 都需要设置
 			{
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, TRUE) ;
 			}
 
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 
 			m_strSystemData5 = _T("ADDR(字符串)");
 			m_strSystemData1 = _T("PORT(整数)");
 			m_strSystemData2 = _T("AUTHORITY_ENABLE(整数)");
 			m_strSystemData6 = _T("AUTH_NAME(字符串)");
 			m_strSystemData7 = _T("AUTH_PASSWORD(字符串)");
 			m_strSystemData3 = _T("AUTH_MODE(整数)") ;
 			m_strSystemData8 = _T("SENDER(字符串)");
 			m_strSystemData9 = _T("RECEIVER(字符串)");
 			m_strSystemData10 = _T("CC(字符串)") ;
 			m_strSystemData11 = _T("SUBJECT(字符串)");
 			m_strSystemData12 = _T("CONTENT(字符串)") ;	
 		}break;
 	case IPC_SYSTEM_SETGET_FTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_DISABLE)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_ABLE)->m_hWnd, TRUE) ;
 			int nCurSel = GetCheckedRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE) ;
 			if (IDC_RADIO_SYSTEM_ABLE == nCurSel) // 都需要设置
 			{
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 				::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 			}
 
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			
 			m_strSystemData1 = _T("PORT(整数)");
 			m_strSystemData5 = _T("ADDR(字符串)");
 			m_strSystemData6 = _T("USER(字符串)");
 			m_strSystemData7 = _T("PASSWORD(字符串)");
 			
 		}break;
 	case IPC_SYSTEM_SETGET_DATEINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			
 			m_strSystemData1 = _T("SYNC_MODE(0,1,2)") ;
 			m_strSystemData5 = _T("DATE") ;
 			m_strSystemData6 = _T("TIME") ;
 			m_strSystemData7 = _T("NTP_ADDR") ;
 
 		}break ;
	case IPC_SYSTEM_SETGET_DATEINFOEX:
		{
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;

			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;

			m_strSystemData1 = _T("同步类型") ;
			m_strSystemData2 = _T("时间间隔") ;
			m_strSystemData5 = _T("日期") ;
			m_strSystemData6 = _T("时间") ;
			m_strSystemData7 = _T("NTP服务器地址") ;
			m_strSystemData8 = _T("时区") ;

		}break ;
	case IPC_SYSTEM_SETGET_UPNPINFO:
		{
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
			m_strSystemData1 = _T("UPNP_ENABLE");

			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
			m_strSystemData2 = _T("UPNP_PORT");
	
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
			m_strSystemData5 = _T("UPNP_NAME");

			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
		}break ;
 	case IPC_SYSTEM_GET_RTP_ADDR:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("RTP_ADDR");
 		}break ;
 	case IPC_SYSTEM_GET_RTP_ADDR2:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("RTP_ADDR2");
 		}break ;
 	case IPC_SYSTEM_GET_RTP_ADDR3:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("RTP_ADDR3");
 		}break ;
 	case IPC_SYSTEM_GET_RTP_ADDR4:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("RTP_ADDR4");
 		}break ;
 	case IPC_SYSTEM_GET_SD_STATUS:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData1 = _T("SD_STATUS");
 		}break ;
 	case IPC_SYSTEM_GET_SD_RW:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData1 = _T("SD_RW");
 		}break ;
 	case IPC_SYSTEM_GET_SD_SPACE:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData1 = _T("SD_SPACE");
 		}break ;
 	case IPC_SYSTEM_GET_SD_FREE_SAPCE:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData1 = _T("FREE_SAPCE");
 		}break ;
 	case IPC_SYSTEM_SET_SD_CMD:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			m_strSystemData1 = _T("SD_CMD(整数)");
 		}break ;
 	case IPC_SYSTEM_GET_DEVICE_NAME:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("DEVICE_NAME");
 		}break ;
 	case IPC_SYSTEM_GET_DEVICE_MANUFACTURER:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("MANUFACTURER");
 
 		}break ;
 	case IPC_SYSTEM_GET_FW_VERSION:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("FW_VERSION");
 		}break ;
 	case IPC_SYSTEM_GET_HW_VERSION:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("HW_VERSION");
 		}break ;
    case IPC_SYSTEM_GET_DEVICE_SN:
        {
            ::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
            ::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
            m_strSystemData5 = _T("SN_VERSION");
        }break ;
        
 	case IPC_SYSTEM_GET_REC_FILES:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("REC_FILES");
 
 		}break ;
 	case IPC_SYSTEM_SET_REC_DEL_FILES:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("REC_DEL_FILES");
 		}break ;
 	case IPC_SYSTEM_SET_REC_UPLOAD_FILES:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
 			m_strSystemData5 = _T("REC_UPLOAD_FILES");
 		}break;
	case IPC_SYSTEM_GET_SUPPORT_RTSP:
		{
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
			m_strSystemData5 = _T("RTSP能力");
		}break;
	case IPC_SYSTEM_GET_SUPPORT_GB:
		{
			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
			::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
			m_strSystemData5 = _T("GB能力");
		}break ;
	//case IPC_SYSTEM_UPNP_ENABLE:
	//	{
	//		::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
	//		m_strSystemData1 = _T("UPNP_ENABLE");

	//	}break ;
	//case IPC_SYSTEM_UPNP_PORT:
	//	{
	//		::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
	//		m_strSystemData1 = _T("UPNP_PORT");
	//	}break ;
	//case IPC_SYSTEM_UPNP_NAME:
	//	{
	//		::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, TRUE) ;
	//		::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, TRUE) ;
	//		m_strSystemData5 = _T("UPNP_NAME");
	//	}break ;
 	default:
 		{
 
 		}break;
 	}
 	UpdateData(FALSE) ;
}

void CSystemSettingDlg::DisableAll()
{
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM4)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, FALSE) ;

	::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_DISABLE)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_RADIO_SYSTEM_ABLE)->m_hWnd, FALSE) ;

	::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_SET)->m_hWnd, FALSE) ;
	::EnableWindow(GetDlgItem(IDC_BUTTON_SYSTEMSETTING_GET)->m_hWnd, FALSE) ;

	m_strSystemData1		= _T("") ;
	m_strSystemData2		= _T("") ;
	m_strSystemData3		= _T("") ;
	m_strSystemData4		= _T("") ;
	m_strSystemData5		= _T("") ;
	m_strSystemData6		= _T("") ;
	m_strSystemData7		= _T("") ;
	m_strSystemData8		= _T("") ;
	m_strSystemData9		= _T("") ;
	m_strSystemData10		= _T("") ;
	m_strSystemData11		= _T("") ;
	m_strSystemData12		= _T("") ;

	m_dwSystemSetData1		= 0 ;
	m_dwSystemSetData2		= 0 ;
	m_dwSystemSetData3		= 0 ;
	m_dwSystemSetData4		= 0 ;
	m_strSystemSetData5		= _T("") ;
	m_strSystemSetData6		= _T("") ;
	m_strSystemSetData7		= _T("") ;
	m_strSystemSetData8		= _T("") ;
	m_strSystemSetData9		= _T("") ;
	m_strSystemSetData10		= _T("") ;
	m_strSystemSetData11		= _T("") ;
	m_strSystemSetData12		= _T("") ;
	UpdateData(FALSE) ;
}

void CSystemSettingDlg::OnBnClickedRadioSystemDisable()
{
	// TODO: 
 	switch (m_cmd)
 	{
 	case IPC_SYSTEM_SETGET_IPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
 		}break ;
 	case IPC_SYSTEM_SETGET_SMTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, FALSE) ;
 		}break ;
 	case IPC_SYSTEM_SETGET_FTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
 		}break;
 	default:
 		{
 		}break;
 	}
 }

 void CSystemSettingDlg::OnBnClickedRadioSystemAble()
 {
 	// TODO: 
 
 	switch (m_cmd)
 	{
 	case IPC_SYSTEM_SETGET_IPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
 		}break ;
 	case IPC_SYSTEM_SETGET_SMTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, TRUE) ;
 			
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, TRUE) ;
 		}break;
 	case IPC_SYSTEM_SETGET_FTPINFO:
 		{
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 			::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
 		}break;
 	default:
 		{
 		}break;
 	}
}

BOOL CSystemSettingDlg::InitializeCallBack()
{
	 ;

	if (NULL != m_pVideoWnd)
	{
		m_pVideoWnd->RegisterSystemSettingCallBack(this) ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CSystemSettingDlg::UnInitializeCallBack()
{
	 ;

	if (NULL != m_pVideoWnd)
	{
		m_pVideoWnd->RegisterSystemSettingCallBack(NULL) ;
		return TRUE;
	}

	return FALSE ;
}

void CSystemSettingDlg::OnContextResult( LPVOID lpConText)
{
	
	return ;
 	if (NULL != lpConText)
 	{
 		LPIPC_COMMAND_CONTEXT lpCmdContext = (LPIPC_COMMAND_CONTEXT)lpConText ;

/////////
#define CHECK_SYSTEM_COMMAND(name) case name:                                    \
		{                                                                       \
		if(lpCmdContext->cmd == IPC_CMD_GET_PROPERTY)                                 \
		{                                                                        \
		MessageBox(_T(#name), _T("获取失败"), 0);                            \
		}else{                                                                  \
		MessageBox(_T(#name), _T("设置失败"), 0);                            \
		}                                                                       \
		}break;
////////
		if (lpCmdContext->result != 0)
		{
			switch (lpCmdContext->subtype)
			{
				CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SETGET_IPINFO)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SETGET_SMTPINFO)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SETGET_DATEINFO)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SETGET_FTPINFO)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SETGET_UPNPINFO)

					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_RTP_ADDR)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_RTP_ADDR2)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_RTP_ADDR3)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_RTP_ADDR4)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_SD_STATUS)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_SD_RW)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_SD_SPACE)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_SD_FREE_SAPCE)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_DEVICE_NAME)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_DEVICE_MANUFACTURER)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_FW_VERSION)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_HW_VERSION)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_REC_FILES)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_GET_DEVICE_SN)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SET_SD_CMD)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SET_REC_DEL_FILES)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SET_REC_UPLOAD_FILES)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_UPNP_ENABLE)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_UPNP_PORT)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_UPNP_NAME)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SET_DEVICE_RESTART)
					CHECK_SYSTEM_COMMAND(IPC_SYSTEM_SET_RESTORE_DEFAULT)
			}
			return ;
		}
 		if (lpCmdContext->cmd == IPC_CMD_GET_PROPERTY)
 		{
 			switch (lpCmdContext->subtype)
 			{
 			case IPC_SYSTEM_SETGET_IPINFO:
 				{	
					IPC_SYSIPINFO ipInfo;
					memset(&ipInfo, 0, sizeof(IPC_SYSIPINFO)) ;
					memcpy(&ipInfo, lpCmdContext->data, lpCmdContext->len) ;

					if (ipInfo.dhcp_enable == 1)
					{
						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;

						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
					}
					else
					{
						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;

						m_strSystemSetData5 = ipInfo.ip_addr ;
						m_strSystemSetData6 = ipInfo.network_mask ;
						m_strSystemSetData7 = ipInfo.dns_addr ;
						m_strSystemSetData8 = ipInfo.dns_backup_addr ;
						m_strSystemSetData9 = ipInfo.gateway_addr ;
					}

					UpdateData(FALSE) ;
 				}break ;
 			case IPC_SYSTEM_SETGET_SMTPINFO:
 				{
					IPC_SYSSMTP smtp;
					memset(&smtp, 0, sizeof(IPC_SYSSMTP)) ;
					memcpy(&smtp, lpCmdContext->data, lpCmdContext->len) ;

					if (smtp.smtp_enable == 0)
					{
						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;

						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, FALSE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, FALSE) ;
					}
					else if (smtp.smtp_enable == 1 )
					{
						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;

						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM2)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM3)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM8)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM9)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM10)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM11)->m_hWnd, TRUE) ;
						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM12)->m_hWnd, TRUE) ;

						m_strSystemSetData5 = smtp.smtp_addr ;
						m_dwSystemSetData1 = smtp.smtp_port;
						m_dwSystemSetData2 = smtp.smtp_auth_enable;
						if (m_dwSystemSetData2 == 1)
						{
							m_strSystemSetData6 = smtp.smtp_auth_name ;
							m_strSystemSetData7 = smtp.smtp_auth_password ;
							m_dwSystemSetData3 = smtp.smtp_auth_model ;
						}
						m_strSystemSetData8 =smtp.smtp_sender ;
						m_strSystemSetData9 = smtp.smtp_receiver ;
						m_strSystemSetData10 = smtp.smtp_cc ;
						m_strSystemSetData11 = smtp.smtp_subject;
						m_strSystemSetData12 = smtp.smtp_content ;
					}
 
 					UpdateData(FALSE) ;
 				}break;
 			case IPC_SYSTEM_SETGET_FTPINFO:
 				{
					IPC_SYSFTP ftp;
					memset(&ftp, 0, sizeof(IPC_SYSFTP)) ;
					memcpy(&ftp, lpCmdContext->data, lpCmdContext->len) ;
 					
 					if (ftp.ftp_enable == 0)
 					{
 						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_DISABLE) ;
 
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, FALSE) ;
 
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, FALSE) ;
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, FALSE) ;
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, FALSE) ;
 					}
 					else if (ftp.ftp_enable == 1 )
 					{
 						CheckRadioButton(IDC_RADIO_SYSTEM_DISABLE, IDC_RADIO_SYSTEM_ABLE, IDC_RADIO_SYSTEM_ABLE) ;
 
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM1)->m_hWnd, TRUE) ;
 
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM5)->m_hWnd, TRUE) ;
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM6)->m_hWnd, TRUE) ;
 						::EnableWindow(GetDlgItem(IDC_EDIT_SYSTEM7)->m_hWnd, TRUE) ;
						
						m_strSystemSetData5 = ftp.ftp_addr ;
						m_strSystemSetData6 = ftp.ftp_user ;
						m_strSystemSetData7 = ftp.ftp_password ;
						m_dwSystemSetData1 = ftp.ftp_port;
 					}
 
 					UpdateData(FALSE) ;
 				}break;
			case IPC_SYSTEM_SETGET_DATEINFO:
				{
					IPC_SYSDATEINFO dateInfo;
					memset(&dateInfo, 0, sizeof(IPC_SYSDATEINFO)) ;
					memcpy(&dateInfo, lpCmdContext->data, lpCmdContext->len) ;

					m_dwSystemSetData1 = dateInfo.sync_mode ;

					//if ( m_dwSystemSetData1 == 0 )
					//{
						m_strSystemSetData7 = dateInfo.ntp_addr ;
					//}
					//else if ( (m_dwSystemSetData1 == 1) || (m_dwSystemSetData1 == 2) )
					//{
						m_strSystemSetData5 = dateInfo.time_date ;
						m_strSystemSetData6 = dateInfo.time_time ;
					//}

					UpdateData(FALSE) ;	
				}break ;
 			case IPC_SYSTEM_GET_SD_STATUS:
 			case IPC_SYSTEM_GET_SD_RW:
 			case IPC_SYSTEM_GET_SD_SPACE:
 			case IPC_SYSTEM_GET_SD_FREE_SAPCE:
			case IPC_SYSTEM_UPNP_ENABLE:
			case IPC_SYSTEM_UPNP_PORT:
 				{
 					DWORD dwValue =0 ;
 
 					memcpy(&dwValue, lpCmdContext->data, lpCmdContext->len);
 
 					m_dwSystemSetData1 = dwValue ;
 
 					UpdateData(FALSE) ;
 				}break ;		
 			case IPC_SYSTEM_GET_RTP_ADDR:				
 			case IPC_SYSTEM_GET_RTP_ADDR2:				
 			case IPC_SYSTEM_GET_RTP_ADDR3:			
 			case IPC_SYSTEM_GET_RTP_ADDR4:				
 			case IPC_SYSTEM_GET_DEVICE_NAME:
 			case IPC_SYSTEM_GET_DEVICE_MANUFACTURER:
 			case IPC_SYSTEM_GET_FW_VERSION:
 			case IPC_SYSTEM_GET_HW_VERSION:
            case IPC_SYSTEM_GET_DEVICE_SN:
 			case IPC_SYSTEM_GET_REC_FILES:
			case IPC_SYSTEM_UPNP_NAME:
 				{
 					 m_strSystemSetData5 = (char*)(&(lpCmdContext->data)) ;
 					 UpdateData(FALSE) ;
 				}break ;
 			}
 		}
 	}
}
void CSystemSettingDlg::OnBnClickedButtonRestart()
{
	// TODO: 重启设备
	ipcDeviceRestart(m_hSdkHandle) ;
}

void CSystemSettingDlg::OnBnClickedButtonDefault()
{
	// TODO: 恢复初始设置
	//IPC_RestoreDefaultSetting(m_hSdkHandle) ;
}

void CSystemSettingDlg::OnBnClickedButtonWaiting()
{
	// TODO: 
	INT nRet = ipcDeviceStandby(m_hSdkHandle) ;
}

void CSystemSettingDlg::OnBnClickedButtonWakeup()
{
	// TODO: 
	INT nRet = ipcDeviceWakeup(m_hSdkHandle) ;
}

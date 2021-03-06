// PlanSet.cpp : 实现文件
//

#include "stdafx.h"
#include "IPCSdkFuncDemo.h"
#include "PlanSet.h"


// CPlanSet 对话框

IMPLEMENT_DYNAMIC(CPlanSet, CDialog)

CPlanSet::CPlanSet(CWnd* pParent /*=NULL*/)
	: CDialog(CPlanSet::IDD, pParent)
	, m_startTime(0)
	, m_endTime(0)
{

}

CPlanSet::CPlanSet( CWnd* pParent, LPVOID handle_ )
	: CDialog(CPlanSet::IDD, pParent)
	, m_startTime(0)
	, m_endTime(0)
{
	_handle = handle_ ;

	//m_sTime = {0} ;
	//m_eTime = {0} ;
	memset(m_sTime, 0, sizeof(DWORD)*7*8) ;
	memset(m_eTime, 0, sizeof(DWORD)*7*8) ;
	_planType = 0 ;
}

CPlanSet::~CPlanSet()
{
}

void CPlanSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PLAN_TYPE, m_ctlPlanType);
	DDX_Control(pDX, IDC_COMBO2, m_ctlTimeIndex);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, m_endTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_ctlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_ctlEndTime);
	DDX_Control(pDX, IDC_COMBO_PLAN_DAY, m_ctlPlanDate);
}
BOOL CPlanSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD lCurSel = 0 ;

	lCurSel = m_ctlPlanType.AddString("视频异常布防");
	m_ctlPlanType.SetItemData(lCurSel, IPC_PLAN_CAMERATAMPERING);

	lCurSel = m_ctlPlanType.AddString("移动侦测布防");
	m_ctlPlanType.SetItemData(lCurSel, IPC_PLAN_MONTIONDETECTION);

	lCurSel = m_ctlPlanType.AddString("报警输入布防");
	m_ctlPlanType.SetItemData(lCurSel, IPC_PLAN_INPUTPORT);

	lCurSel = m_ctlPlanType.AddString("定时录像");
	m_ctlPlanType.SetItemData(lCurSel, IPC_PLAN_RECORD);

	m_ctlPlanType.SetCurSel(0) ;

	lCurSel = 0 ;
	lCurSel = m_ctlTimeIndex.AddString("时段1");
	m_ctlTimeIndex.SetItemData(lCurSel, 0);

	lCurSel = m_ctlTimeIndex.AddString("时段2");
	m_ctlTimeIndex.SetItemData(lCurSel, 1);

	lCurSel = m_ctlTimeIndex.AddString("时段3");
	m_ctlTimeIndex.SetItemData(lCurSel, 2);

	lCurSel = m_ctlTimeIndex.AddString("时段4");
	m_ctlTimeIndex.SetItemData(lCurSel, 3);

	lCurSel = m_ctlTimeIndex.AddString("时段5");
	m_ctlTimeIndex.SetItemData(lCurSel, 4);

	lCurSel = m_ctlTimeIndex.AddString("时段6");
	m_ctlTimeIndex.SetItemData(lCurSel, 5);

	lCurSel = m_ctlTimeIndex.AddString("时段7");
	m_ctlTimeIndex.SetItemData(lCurSel, 6);

	lCurSel = m_ctlTimeIndex.AddString("时段8");
	m_ctlTimeIndex.SetItemData(lCurSel, 7);

	m_ctlTimeIndex.SetCurSel(0) ;

	lCurSel = 0 ;
	lCurSel = m_ctlPlanDate.AddString("星期日");
	m_ctlPlanDate.SetItemData(lCurSel, 0);

	lCurSel = m_ctlPlanDate.AddString("星期一");
	m_ctlPlanDate.SetItemData(lCurSel, 1);

	lCurSel = m_ctlPlanDate.AddString("星期二");
	m_ctlPlanDate.SetItemData(lCurSel, 2);

	lCurSel = m_ctlPlanDate.AddString("星期三");
	m_ctlPlanDate.SetItemData(lCurSel, 3);

	lCurSel = m_ctlPlanDate.AddString("星期四");
	m_ctlPlanDate.SetItemData(lCurSel, 4);

	lCurSel = m_ctlPlanDate.AddString("星期五");
	m_ctlPlanDate.SetItemData(lCurSel, 5);

	lCurSel = m_ctlPlanDate.AddString("星期六");
	m_ctlPlanDate.SetItemData(lCurSel, 6);

	m_ctlPlanDate.SetCurSel(0) ;

	CTime st(2012, 2, 16, 0, 0, 0) ;
	CTime et(2012, 2, 16, 0, 0, 0) ;
	m_ctlStartTime.SetTime(&st) ;
	m_ctlEndTime.SetTime(&et) ;

	return TRUE ;
}

BEGIN_MESSAGE_MAP(CPlanSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPlanSet::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAN_TYPE, &CPlanSet::OnCbnSelchangeComboPlanType)
	ON_BN_CLICKED(IDC_BUTTON_PLAN_SET, &CPlanSet::OnBnClickedButtonPlanSet)
	ON_BN_CLICKED(IDC_BUTTON_PLAN_GET, &CPlanSet::OnBnClickedButtonPlanGet)
END_MESSAGE_MAP()


// CPlanSet 消息处理程序

void CPlanSet::OnBnClickedButton1()
{
	// TODO: 
	UpdateData(TRUE) ;

	m_ctlStartTime.GetTime(m_startTime) ;
	m_ctlEndTime.GetTime(m_endTime) ;
	
	DWORD weekday = m_ctlPlanDate.GetItemData(m_ctlPlanDate.GetCurSel()) ;
	DWORD index = m_ctlTimeIndex.GetItemData(m_ctlTimeIndex.GetCurSel()) ;

	m_sTime[weekday][index] = m_startTime.GetHour()*3600 + m_startTime.GetMinute()*60 + m_startTime.GetSecond() ;
	m_eTime[weekday][index] = m_endTime.GetHour()*3600 + m_endTime.GetMinute()*60 + m_endTime.GetSecond();
}


void CPlanSet::OnCbnSelchangeComboPlanType()
{
	// TODO: 
	_planType = m_ctlPlanType.GetItemData(m_ctlPlanType.GetCurSel()) ;
}

void CPlanSet::OnBnClickedButtonPlanSet()
{
	// 
	switch (_planType)
	{
	case IPC_PLAN_RECORD:
		{
			if (ipcSetTimingRecord(_handle, 0, 0, m_sTime, m_eTime) == 0)
			{
				MessageBox(_T("设置成功"), _T("定时录像"), 0) ;
			}
			else
			{
				MessageBox(_T("设置失败"), _T("定时录像"), 0) ;
			}
		}
		break;
	case IPC_PLAN_CAMERATAMPERING:
		{
			if (ipcSetCameraUnusualPlan(_handle, m_sTime, m_eTime) == 0)
			{
				MessageBox(_T("设置成功"), _T("视频异常布防"), 0) ;	
			}
			else
			{
				MessageBox(_T("设置失败"), _T("视频异常布防"), 0) ;
			}
		}
		break;
	case IPC_PLAN_MONTIONDETECTION:
		{
			if (ipcSetMontionDetectionPlan(_handle, m_sTime, m_eTime) == 0)
			{
				MessageBox(_T("设置成功"), _T("移动侦测布防"), 0) ;
			}
			else
			{
				MessageBox(_T("设置失败"), _T("移动侦测布防"), 0) ;
			}
		}
		break;
	case IPC_PLAN_INPUTPORT:
		{
			if (ipcSetInputPlan(_handle, m_sTime, m_eTime) == 0)
			{
				MessageBox(_T("设置成功"), _T("报警出入布防"), 0) ;
			}
			else
			{
				MessageBox(_T("设置失败"), _T("报警出入布防"), 0) ;
			}
		}
		break;
	}
}

void CPlanSet::OnBnClickedButtonPlanGet()
{
	// TODO: 
	switch (_planType)
	{
	case IPC_PLAN_RECORD:
		{
			DWORD stream;
			DWORD location;
			if (ipcGetTimingRecord(_handle, &stream, &location, (DWORD**)m_sTime, (DWORD**)m_eTime) == 0)
			{
				MessageBox(_T("获取成功"), _T("定时录像"), 0) ;
			}
			else
			{
				MessageBox(_T("获取失败"), _T("定时录像"), 0) ;
			}
		}
		break;
	case IPC_PLAN_CAMERATAMPERING:
		{
			if (ipcGetCameraUnusualPlan(_handle, (DWORD**)m_sTime, (DWORD**)m_eTime) == 0)
			{
				MessageBox(_T("获取成功"), _T("视频异常布防"), 0) ;
			}
			else
			{
				MessageBox(_T("获取失败"), _T("视频异常布防"), 0) ;
			}
		}
		break;
	case IPC_PLAN_MONTIONDETECTION:
		{
			if (ipcGetMontionDetectionPlan(_handle, (DWORD**)m_sTime, (DWORD**)m_eTime) == 0)
			{
				MessageBox(_T("获取成功"), _T("移动侦测布防"), 0) ;
			}
			else
			{
				MessageBox(_T("获取失败"), _T("移动侦测布防"), 0) ;
			}
		}
		break;
	case IPC_PLAN_INPUTPORT:
		{
			if (ipcGetInputPlan(_handle, (DWORD**)m_sTime, (DWORD**)m_eTime) == 0)
			{
				MessageBox(_T("获取成功"), _T("报警输入布防"), 0) ;
			}
			else
			{
				MessageBox(_T("获取失败"), _T("报警输入布防"), 0) ;
			}
		}
		break;
	}
}

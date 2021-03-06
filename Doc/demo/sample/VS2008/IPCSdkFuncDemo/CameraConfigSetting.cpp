// CameraConfigSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "IPCSdkFuncDemo.h"
#include "CameraConfigSetting.h"


// CCameraConfigSetting 对话框

IMPLEMENT_DYNAMIC(CCameraConfigSetting, CDialog)

CCameraConfigSetting::CCameraConfigSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraConfigSetting::IDD, pParent)
	, m_dwEdit1(0)
	, m_dwEdit2(_T(""))
	, m_strStatic1(_T(""))
	, m_strStatic2(_T(""))
	, m_strStatic3(_T(""))
	, m_strStatic4(_T(""))
	, m_strStatic5(_T(""))
 	, m_strStatic6(_T(""))
	, m_strStatic7(_T(""))
	, m_strStatic8(_T(""))
	, m_strStatic9(_T(""))
	, m_strStatic10(_T(""))
	, m_strStatic11(_T(""))
	, m_strStatic12(_T(""))
	, m_dwEdit3(_T(""))
	, m_dwEdit4(0)
	, m_dwEdit5(0)
	, m_dwEdit6(0)
	, m_dwEdit7(0)
	, m_dwEdit8(0)
	, m_dwEdit9(0)
	, m_dwEdit10(0)
	, m_dwEdit11(0)
	, m_dwEdit12(0)
	, m_strStatic13(_T(""))
	, m_strStatic14(_T(""))
	, m_dwEdit13(0)
	, m_dwEdit14(0)
{
	m_cmd = 0;
}

CCameraConfigSetting::CCameraConfigSetting( LPVOID hSdk_, CVideoWnd* pVideoWnd_, CWnd* pParent /*= NULL*/ )
	: CDialog(CCameraConfigSetting::IDD, pParent)
	, m_dwEdit1(0)
	, m_dwEdit2(_T(""))
	, m_strStatic1(_T(""))
	, m_strStatic2(_T(""))
	, m_strStatic3(_T(""))
	, m_strStatic4(_T(""))
	, m_strStatic5(_T(""))
	, m_strStatic6(_T(""))
	, m_strStatic7(_T(""))
	, m_strStatic8(_T(""))
	, m_strStatic9(_T(""))
	, m_strStatic10(_T(""))
	, m_strStatic11(_T(""))
	, m_strStatic12(_T(""))
	, m_dwEdit3(_T(""))
	, m_dwEdit4(0)
	, m_dwEdit5(0)
	, m_dwEdit6(0)
	, m_dwEdit7(0)
	, m_dwEdit8(0)
	, m_dwEdit9(0)
	, m_dwEdit10(0)
	, m_dwEdit11(0)
	, m_dwEdit12(0)
	, m_strStatic13(_T(""))
	, m_strStatic14(_T(""))
	, m_dwEdit13(0)
	, m_dwEdit14(0)
{
	m_cmd = 0;

	m_pVideoWnd = pVideoWnd_ ;
	m_hSdkHandle = hSdk_ ;
}

CCameraConfigSetting::~CCameraConfigSetting()
{
	UnInitializeCallBack();
	m_pVideoWnd = NULL ;
}

void CCameraConfigSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_1, m_dwEdit1);
	DDX_Text(pDX, IDC_EDIT_2, m_dwEdit2);
	DDX_Text(pDX, IDC_STATIC_1, m_strStatic1);
	DDX_Text(pDX, IDC_STATIC_2, m_strStatic2);
	DDX_Text(pDX, IDC_STATIC_3, m_strStatic3);
	DDX_Text(pDX, IDC_STATIC_4, m_strStatic4);
	DDX_Text(pDX, IDC_STATIC_5, m_strStatic5);
	DDX_Text(pDX, IDC_STATIC_6, m_strStatic6);
	DDX_Text(pDX, IDC_STATIC_7, m_strStatic7);
	DDX_Text(pDX, IDC_STATIC_8, m_strStatic8);
	DDX_Text(pDX, IDC_STATIC_9, m_strStatic9);
	DDX_Text(pDX, IDC_STATIC_10, m_strStatic10);
	DDX_Text(pDX, IDC_STATIC_11, m_strStatic11);
	DDX_Text(pDX, IDC_STATIC_12, m_strStatic12);
	DDX_Text(pDX, IDC_EDIT_3, m_dwEdit3);
	DDX_Text(pDX, IDC_EDIT_4, m_dwEdit4);
	DDX_Text(pDX, IDC_EDIT_5, m_dwEdit5);
	DDX_Text(pDX, IDC_EDIT_6, m_dwEdit6);
	DDX_Text(pDX, IDC_EDIT_7, m_dwEdit7);
	DDX_Text(pDX, IDC_EDIT_8, m_dwEdit8);
	DDX_Text(pDX, IDC_EDIT_9, m_dwEdit9);
	DDX_Text(pDX, IDC_EDIT_10, m_dwEdit10);
	DDX_Text(pDX, IDC_EDIT_11, m_dwEdit11);
	DDX_Text(pDX, IDC_EDIT_12, m_dwEdit12);
	DDX_Control(pDX, IDC_COMBO1, m_ctlConfigList);
	DDX_Text(pDX, IDC_STATIC_13, m_strStatic13);
	DDX_Text(pDX, IDC_STATIC_14, m_strStatic14);
	DDX_Text(pDX, IDC_EDIT_13, m_dwEdit13);
	DDX_Text(pDX, IDC_EDIT_14, m_dwEdit14);
}



BEGIN_MESSAGE_MAP(CCameraConfigSetting, CDialog)
	ON_BN_CLICKED(IDC_CONFIG_SET, &CCameraConfigSetting::OnBnClickedConfigSet)
	ON_BN_CLICKED(IDC_CONFIG_GET, &CCameraConfigSetting::OnBnClickedConfigGet)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCameraConfigSetting::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BOOL CCameraConfigSetting::InitializeCallBack()
{
	 ;

	if (NULL != m_pVideoWnd)
	{
		m_pVideoWnd->RegisterCameraConfigCallBack(this) ;
		return TRUE ;
	}
	return FALSE ;
}

BOOL CCameraConfigSetting::UnInitializeCallBack()
{
	 ;

	if (NULL != m_pVideoWnd)
	{
		m_pVideoWnd->RegisterCameraConfigCallBack(NULL) ;
		return TRUE;
	}

	return FALSE ;
}

void CCameraConfigSetting::OnContextResult( LPVOID lpConText )
{

}

void CCameraConfigSetting::OnBnClickedConfigGet()
{
    INT streamID = m_pVideoWnd->GetStreamID() ;

	// TODO:
	if (m_cmd == 0)
	{
		return ;
	}
	//if (m_cmd == IPCCMD_PTZ_PROTOCOL)
	//{
	//	DWORD dwProtocol = 0 ;
	//	ipcGetPTZProtocol(m_hSdkHandle, &dwProtocol) ;

	//	m_dwEdit1 = dwProtocol ;
	//	UpdateData(FALSE) ;
	//}

	switch (m_cmd)
	{
	case IPC_ENCODE_ENC_SN_GROUP:
		{
			IPC_ENCSN sn;
			memset(&sn, 0, sizeof(IPC_ENCSN)) ;

			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &sn) ;
			
			m_dwEdit6 = sn.sn_type;
			m_dwEdit1 = sn.sn_stream ;
			m_dwEdit2.Format("%d", sn.sn_fps) ;
			//m_dwEdit2 = sn.sn_fps ;
			//m_dwEdit3 = sn.sn_width ;
			m_dwEdit3.Format("%d", sn.sn_width) ;
			m_dwEdit4 = sn.sn_height ;
			m_dwEdit5 = sn.sn_rotate ;

			m_dwEdit7 = sn.sn_h264.sn_brc ;
			m_dwEdit8 = sn.sn_h264.sn_m;
			m_dwEdit9 = sn.sn_h264.sn_n ;
			m_dwEdit10 = sn.sn_h264.sn_idrInterval ;
	
			m_dwEdit11 = sn.sn_h264.sn_cbr ;
	
			m_dwEdit12 = sn.sn_h264.sn_vbr_min ;
			m_dwEdit13 = sn.sn_h264.sn_vbr_max ;

			m_dwEdit14 = sn.sn_quality ;
			UpdateData(FALSE) ;
		}break ;
	case IPC_ENCODE_SN_TEXT_GROUP:
		{
			IPC_SNTEXT text;
			memset(&text, 0, sizeof(IPC_SNTEXT)) ;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &text) ;

			//m_dwEdit2 = text.text_enable;
			m_dwEdit2.Format("%d", text.text_enable) ;
			m_dwEdit1 = text.text_streamID ;
			m_dwEdit3 = text.text_content ;
			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_IRCUT_GROUP:
		{
			IPC_IMGIRCUT ircut ;
			memset(&ircut, 0, sizeof(IPC_IMGIRCUT)) ;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &ircut) ;

			m_dwEdit1 = ircut.ircut_DurTime ;
			m_dwEdit2.Format("%d", ircut.ircut_DayToNightThr) ;
			m_dwEdit3.Format("%d", ircut.ircut_NightToDayThr) ;
			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_SHUTTER_GROUP:
		{
			IPC_IMGSHUTTER shutter;
			memset(&shutter, 0, sizeof(IPC_IMGSHUTTER)) ;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &shutter) ;

			m_dwEdit1 = shutter.shutter_min ;
			m_dwEdit2.Format("%d", shutter.shutter_max) ;
			//m_dwEdit2 = shutter.shutter_max ;

			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_DCIRIS_GROUP:
		{
			IPC_IMGIRIS iris;
			memset(&iris, 0, sizeof(iris)) ;
			if (ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &iris) != 0)
			{
				MessageBox(_T("获取IPC_VIDEO_DCIRIS_GROUP属性"), _T("失败"), 0); 
			}
			
			m_dwEdit1 = iris.iris_type ;
			//m_dwEdit2 = iris.iris_quty ;
			m_dwEdit2.Format("%d", iris.iris_quty) ;
			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_PM_GROUP:
		{
			IPC_IMGPM pm[4];
			memset(pm, 0, sizeof(IPC_IMGPM)*4) ;
			ipcGetPictMask(m_hSdkHandle, pm) ;

			m_dwEdit1 = pm[0].pm_left;
			m_dwEdit2.Format("%d", pm[0].pm_top) ;
			//m_dwEdit2 = pm[0].pm_top ;
			//m_dwEdit3 = pm[0].pm_w ;
			m_dwEdit3.Format("%d", pm[0].pm_w) ;
			m_dwEdit4 = pm[0].pm_h ;
			m_dwEdit5 = pm[0].pm_color ;
			m_dwEdit6 = pm[0].enable_flag ;

			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_IMGPRO_GROUP:
		{
			IPC_IMGPRO img;
			memset(&img, 0, sizeof(IPC_IMGPRO)) ;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &img) ;

			m_dwEdit1 = img.img_saturation ;
			m_dwEdit2.Format("%ld", img.img_brightness) ;
			//m_dwEdit2 = img.img_brightness ;
			//m_dwEdit3 = img.img_hue ;
			m_dwEdit3.Format("%ld", img.img_hue) ;
			m_dwEdit4 = img.img_contrast ;
			m_dwEdit5 = img.img_sharpness ;

			UpdateData(FALSE) ;

		}break ;
	case IPC_ENCODE_ENC_ENC_GROUP:
		{
			IPC_ENCENC enc ;
			memset(&enc, 0, sizeof(IPC_ENCENC)) ;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &enc) ;
		
			m_dwEdit1 = enc.enc_streamID ;
			//m_dwEdit2 = enc.enc_type ;
			m_dwEdit2.Format("%d", enc.enc_type) ;
			//m_dwEdit3 = enc.enc_fbs ;
			m_dwEdit3.Format("%d", enc.enc_fbs) ;
			m_dwEdit4 = enc.enc_brcMode ;
			m_dwEdit5 = enc.enc_cbrAVG ;
			m_dwEdit6 = enc.enc_vbr_min ;
			m_dwEdit7 = enc.enc_vbr_max ;
		
			UpdateData(FALSE) ;
		}break ;
	case IPC_VIDEO_EXPOSURE_MODE:
	case IPC_VIDEO_AE_TARGET_RATION:
	case IPC_VIDEO_MAX_GAIN:
	case IPC_VIDEO_WBC:
	case IPC_VIDEO_DN_MODE:
	case IPC_VIDEO_BACKLIGHT_COMP:
	case IPC_VIDEO_LOCAL_EXPOSURE:
	case IPC_VIDEO_MCTF_STRENGTH:
	case IPC_VIDEO_SLOW_SHUTTER:
	case IPC_VIDEO_AE_PREFERENCE:
	case IPC_VIDEO_METERING_MODE:
	case IPC_ENCODE_ENC_MODE:
	case IPC_ENCODE_SN_TIME_ENABLE0:

    case IPC_VIDEO_WBC_CUSTOM_R_GAIN:
    case IPC_VIDEO_WBC_CUSTOM_B_GAIN:
    case IPC_ENCODE_PROPERTY_SN_MJPEG_LEVEL_STREAM0:
		{
			LONG lValue = 0;
			ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &lValue) ;
			m_dwEdit1 = lValue ;

			UpdateData(FALSE) ;
		}break ;
    case IPC_VIDEO_AF_ENABLE:
        {

            LONG lValue = 0;

            ipcGetConfig(m_hSdkHandle, m_cmd, streamID, &lValue) ;

            m_dwEdit1 = lValue ;

            UpdateData(FALSE) ;
        }
    case IPC_VIDEO_MJPEG_QUALITY:
		{
		}break ;
    case IPC_ENCODE_STR_I_INTERVAL:
        {
            LONG lValue = 0;
            ipcGetIDRInterval(m_hSdkHandle,streamID,(DWORD*)&lValue) ;
            m_dwEdit1 = lValue ;

            UpdateData(FALSE) ;
        }break;

	}
}
// CCameraConfigSetting 消息处理程序

void CCameraConfigSetting::OnBnClickedConfigSet()
{
	// TODO: 

	UpdateData(TRUE) ;
	if (m_cmd == 0)
	{
		return ;
	}
	if (NULL == m_pVideoWnd)
	{
		return ;
	}
	INT streamID = m_pVideoWnd->GetStreamID() ;
	switch (m_cmd)
	{
	case IPC_ENCODE_ENC_SN_GROUP:
		{
			IPC_ENCSN sn;
			memset(&sn, 0, sizeof(IPC_ENCSN)) ;
			sn.sn_type = m_dwEdit6 ;
			sn.sn_stream = m_dwEdit1 ;
			sn.sn_fps = atoi(m_dwEdit2.GetString()) ;
			sn.sn_width = atoi(m_dwEdit3.GetString()) ;
			sn.sn_height = m_dwEdit4 ;
			sn.sn_rotate = m_dwEdit5 ;
			sn.sn_h264.sn_brc = m_dwEdit7 ;
			sn.sn_h264.sn_m = m_dwEdit8;
			sn.sn_h264.sn_n = m_dwEdit9 ;
			sn.sn_h264.sn_idrInterval = m_dwEdit10 ;
			sn.sn_h264.sn_cbr = m_dwEdit11 ;
			sn.sn_h264.sn_vbr_min = m_dwEdit12 ;
			sn.sn_h264.sn_vbr_max = m_dwEdit13 ;
			sn.sn_quality = m_dwEdit14 ;

			ipcSetConfig(m_hSdkHandle, IPC_ENCODE_ENC_SN_GROUP, streamID, (const char*)&sn) ;
		}break ;
	case IPC_ENCODE_SN_TEXT_GROUP:
		{
			IPC_SNTEXT text;
			memset(&text, 0, sizeof(IPC_SNTEXT)) ;

			text.text_enable = atoi(m_dwEdit2.GetString());
			text.text_streamID = m_dwEdit1 ;
			strcpy(text.text_content, m_dwEdit3.GetBuffer()) ;

			ipcSetConfig(m_hSdkHandle, IPC_ENCODE_SN_TEXT_GROUP, streamID, (const char*)&text) ;
		}break ;
	case IPC_VIDEO_IRCUT_GROUP:
		{
			IPC_IMGIRCUT ircut ;
			memset(&ircut, 0, sizeof(IPC_IMGIRCUT)) ;

			ircut.ircut_DurTime = m_dwEdit1 ;
			ircut.ircut_DayToNightThr = atoi(m_dwEdit2.GetString())  ;
			ircut.ircut_NightToDayThr = atoi(m_dwEdit3.GetString())  ;

			ipcSetConfig(m_hSdkHandle, IPC_VIDEO_IRCUT_GROUP, streamID, (const char*)&ircut) ;
		}break ;
	case IPC_VIDEO_SHUTTER_GROUP:
		{
			IPC_IMGSHUTTER shutter;
			memset(&shutter, 0, sizeof(IPC_IMGSHUTTER)) ;

			shutter.shutter_min = m_dwEdit1 ;
			shutter.shutter_max = atoi(m_dwEdit2.GetString()) ;
			ipcSetConfig(m_hSdkHandle, IPC_VIDEO_SHUTTER_GROUP, streamID, (const char*)&shutter) ;
		}break ;
	case IPC_VIDEO_DCIRIS_GROUP:
		{
			IPC_IMGIRIS iris;
			memset(&iris, 0, sizeof(iris)) ;
			iris.iris_type = m_dwEdit1 ;
			iris.iris_quty = atoi(m_dwEdit2.GetString()) ;
			if (ipcSetConfig(m_hSdkHandle, IPC_VIDEO_DCIRIS_GROUP, streamID, (const char*)&iris) == 0)
			{
				MessageBox(_T("IPC_VIDEO_DCIRIS_GROUP成功"), _T("设置"), 0); 
			}
			else
			{
				MessageBox(_T("IPC_VIDEO_DCIRIS_GROUP失败"), _T("设置"), 0); 
			}
		}break ;
		case IPC_VIDEO_PM_GROUP:
		{
			IPC_IMGPM pm[4];
			memset(&pm, 0, sizeof(IPC_IMGPM)*4) ;
			pm[0].pm_index = 1 ;
			pm[0].pm_left = m_dwEdit1;
			pm[0].pm_top = atoi(m_dwEdit2.GetString()) ;
			pm[0].pm_w = atoi(m_dwEdit3.GetString()) ;
			pm[0].pm_h = m_dwEdit4 ;
			pm[0].pm_color = m_dwEdit5 ;
			pm[0].enable_flag = m_dwEdit6 ;

			pm[1].pm_index = 2 ;
			pm[1].pm_left = 2;
			pm[1].pm_top = 2 ;
			pm[1].pm_w = 22 ;
			pm[1].pm_h = 22 ;
			pm[1].pm_color = 2 ;
			pm[1].enable_flag = 1 ;

			pm[2].pm_index = 3 ;
			pm[2].pm_left = 3;
			pm[2].pm_top = 3 ;
			pm[2].pm_w = 33 ;
			pm[2].pm_h = 33 ;
			pm[2].pm_color = 3 ;
			pm[2].enable_flag = 1 ;

			pm[3].pm_index = 4 ;
			pm[3].pm_left = 4;
			pm[3].pm_top = 4 ;
			pm[3].pm_w = 44 ;
			pm[3].pm_h = 44 ;
			pm[3].pm_color = 4 ;
			pm[3].enable_flag = 1 ;


			ipcSetPictMask(m_hSdkHandle, pm) ;
		}break ;
	case IPC_VIDEO_IMGPRO_GROUP:
		{
			IPC_IMGPRO img;
			memset(&img, 0, sizeof(IPC_IMGPRO)) ;
			img.img_saturation = m_dwEdit1;
			img.img_brightness = atoi(m_dwEdit2.GetString()) ;
			img.img_hue = atoi(m_dwEdit3.GetString()) ;
			img.img_contrast = m_dwEdit4 ;
			img.img_sharpness = m_dwEdit5 ;

			if (ipcSetConfig(m_hSdkHandle, IPC_VIDEO_IMGPRO_GROUP, streamID, (const char*)&img) == 0)
			{
				MessageBox(_T("IPC_VIDEO_DCIRIS_GROUP成功"), _T("设置"), 0); 	
			}
			else
			{
				MessageBox(_T("IPC_VIDEO_DCIRIS_GROUP失败"), _T("设置"), 0); 
			}
		}break ;
	case IPC_VIDEO_EXPOSURE_MODE:
	case IPC_VIDEO_AE_TARGET_RATION:
	case IPC_VIDEO_MAX_GAIN:
	case IPC_VIDEO_WBC:
	case IPC_VIDEO_DN_MODE:
	case IPC_VIDEO_BACKLIGHT_COMP:
	case IPC_VIDEO_LOCAL_EXPOSURE:
	case IPC_VIDEO_MCTF_STRENGTH:
	case IPC_VIDEO_SLOW_SHUTTER:
	case IPC_VIDEO_AE_PREFERENCE:
	case IPC_VIDEO_METERING_MODE:
	case IPC_ENCODE_ENC_MODE:
	case IPC_ENCODE_SN_TIME_ENABLE0:

    case IPC_ENCODE_PROPERTY_SN_MJPEG_LEVEL_STREAM0:
    case IPC_VIDEO_WBC_CUSTOM_R_GAIN:
    case IPC_VIDEO_WBC_CUSTOM_B_GAIN:
		{
			ipcSetConfig(m_hSdkHandle, m_cmd, streamID, (const char*)&m_dwEdit1) ;
		}break ;
    case IPC_VIDEO_AF_ENABLE:
        {
            //BOOL bIsPTZMode = m_pVideoWnd->GetPTZMode() ;
            //if( bIsPTZMode )    
            //{
            //    DWORD dwMode = 1 ;
            //    ipcSetConfig(m_pVideoWnd->GetSdkHandle(), IPCVIDEO_PTZ_MODE,streamID , (char*)&dwMode) ;
            //}else{
            //    DWORD dwMode = 0 ;
            //    ipcSetConfig(m_pVideoWnd->GetSdkHandle(), IPCVIDEO_PTZ_MODE, streamID, (char*)&dwMode) ;
            //}

            ipcSetConfig(m_hSdkHandle, m_cmd, streamID, (const char*)&m_dwEdit1) ;

        }break;
    
    case IPC_VIDEO_MJPEG_QUALITY:
		{
			ipcSetImageQuant( m_hSdkHandle, streamID, m_dwEdit1 ) ;
		}break ;
    case IPC_ENCODE_STR_I_INTERVAL:
        {
            ipcSetIDRInterval(m_hSdkHandle,streamID,m_dwEdit1) ;
        }break;
    case IPC_ENCODE_STR_FORCE_I:
        {
            ipcForceIDR(m_hSdkHandle,streamID) ;
        }break;

	default:
		break;
	}

}
BOOL CCameraConfigSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD lCurSel = 0 ;

// 	lCurSel = m_ctlConfigList.AddString("饱和度");
// 	m_ctlConfigList.SetItemData(lCurSel, IPCVIDEO_SATURATION);
// 
// 	lCurSel = m_ctlConfigList.AddString("亮度");
// 	m_ctlConfigList.SetItemData(lCurSel, IPCVIDEO_BRIGHTNESS);
// 
// 	lCurSel = m_ctlConfigList.AddString("色度");
// 	m_ctlConfigList.SetItemData(lCurSel, IPCVIDEO_HUE);
// 
// 	lCurSel = m_ctlConfigList.AddString("对比度");
// 	m_ctlConfigList.SetItemData(lCurSel, IPCVIDEO_CONTRAST);
// 
// 	lCurSel = m_ctlConfigList.AddString("锐度");
// 	m_ctlConfigList.SetItemData(lCurSel, IPCVIDEO_SHARPNESS);

	lCurSel = m_ctlConfigList.AddString("IrCut昼夜模式") ;
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_IRCUT_GROUP) ;

	lCurSel = m_ctlConfigList.AddString("当前预览码流属性");
	m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_ENC_ENC_GROUP);

	lCurSel = m_ctlConfigList.AddString("抗闪烁模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_EXPOSURE_MODE);

	lCurSel = m_ctlConfigList.AddString("曝光目标系数");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_AE_TARGET_RATION);

	lCurSel = m_ctlConfigList.AddString("SenSor最大增益");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_MAX_GAIN);

	lCurSel = m_ctlConfigList.AddString("白平衡设置");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_WBC);

	lCurSel = m_ctlConfigList.AddString("夜晚模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_DN_MODE);

	lCurSel = m_ctlConfigList.AddString("背光补偿");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_BACKLIGHT_COMP);

	lCurSel = m_ctlConfigList.AddString("局部曝光模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_LOCAL_EXPOSURE);

	lCurSel = m_ctlConfigList.AddString("3D降噪");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_MCTF_STRENGTH);

	lCurSel = m_ctlConfigList.AddString("图像属性") ;
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_IMGPRO_GROUP) ;

	lCurSel = m_ctlConfigList.AddString("自动曝光设置中SlowShutter");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_SLOW_SHUTTER);

	lCurSel = m_ctlConfigList.AddString("自动曝光的偏好");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_AE_PREFERENCE);

	lCurSel = m_ctlConfigList.AddString("自动曝光设置中测光模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_METERING_MODE);

	lCurSel = m_ctlConfigList.AddString("编码模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_ENC_MODE);

	lCurSel = m_ctlConfigList.AddString("显示码流1当前时间");
	m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_SN_TIME_ENABLE0);

	lCurSel = m_ctlConfigList.AddString("DC IRIS模式");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_DCIRIS_GROUP);

	lCurSel = m_ctlConfigList.AddString("电子快门时间范畴");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_SHUTTER_GROUP);

	lCurSel = m_ctlConfigList.AddString("视频遮挡");
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_PM_GROUP);

	lCurSel = m_ctlConfigList.AddString("显示信息叠加");
	m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_SN_TEXT_GROUP);

	lCurSel = m_ctlConfigList.AddString("视频编码");
	m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_ENC_SN_GROUP);

	lCurSel = m_ctlConfigList.AddString("MJPEG编码质量") ;
	m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_MJPEG_QUALITY) ;

	//lCurSel = m_ctlConfigList.AddString("云台协议") ;
	//m_ctlConfigList.SetItemData(lCurSel, IPCCMD_PTZ_PROTOCOL) ;

    lCurSel = m_ctlConfigList.AddString("I帧间隔") ;
    m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_STR_I_INTERVAL) ;

    lCurSel = m_ctlConfigList.AddString("强制I帧") ;
    m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_STR_FORCE_I) ;

    lCurSel = m_ctlConfigList.AddString("自动聚焦");
    m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_AF_ENABLE);

    lCurSel = m_ctlConfigList.AddString("码流1MJPEG压缩等级");
    m_ctlConfigList.SetItemData(lCurSel, IPC_ENCODE_PROPERTY_SN_MJPEG_LEVEL_STREAM0);


    lCurSel = m_ctlConfigList.AddString("白平衡自定义模式红色增益");
    m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_WBC_CUSTOM_R_GAIN);

    lCurSel = m_ctlConfigList.AddString("白平衡自定义模式蓝色增益");
    m_ctlConfigList.SetItemData(lCurSel, IPC_VIDEO_WBC_CUSTOM_B_GAIN);



    m_ctlConfigList.SetCurSel(0) ;

	_hideAllBtn() ;

	return TRUE ;
}


void CCameraConfigSetting::_hideAllBtn()
{
	::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_4)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_5)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_6)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_7)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_8)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_9)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_10)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_11)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_12)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_13)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_EDIT_14)->m_hWnd, SW_HIDE) ;

	::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_4)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_5)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_6)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_7)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_8)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_9)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_10)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_11)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_12)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_13)->m_hWnd, SW_HIDE) ;
	::ShowWindow(GetDlgItem(IDC_STATIC_14)->m_hWnd, SW_HIDE) ;

}


void CCameraConfigSetting::OnCbnSelchangeCombo1()
{
	// TODO:
	_hideAllBtn() ;
	m_cmd = m_ctlConfigList.GetItemData(m_ctlConfigList.GetCurSel()) ;
	switch (m_cmd)
	{
	case IPC_ENCODE_ENC_ENC_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_6)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_7)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_6)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_7)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("码流ID:") ;
			m_strStatic2 = _T("编码格式:") ;
			m_strStatic3 = _T("编码帧率:") ;
			m_strStatic4 = _T("比特率控制:") ;
			m_strStatic5 = _T("比特率平均值:") ;
			m_strStatic6 = _T("最小比特率:") ;
			m_strStatic7 = _T("最大比特率:") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
			m_dwEdit3 = _T("0") ;
			m_dwEdit4 = 0 ;
			m_dwEdit5 = 0 ;
			m_dwEdit6 = 0 ;
			m_dwEdit7 = 0 ;

		}break;
	case IPC_ENCODE_ENC_SN_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_6)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_7)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_8)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_9)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_10)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_11)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_12)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_13)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_14)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_6)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_7)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_8)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_9)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_10)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_11)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_12)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_13)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_14)->m_hWnd, SW_SHOW) ;
			
			m_strStatic1 = _T("码流ID:") ;
			m_strStatic2 = _T("编码帧率:") ;
			m_strStatic3 = _T("宽:") ;
			m_strStatic4 = _T("高:") ;
			m_strStatic5 = _T("镜像/翻转:") ;
			m_strStatic6 = _T("编码格式:") ;
			m_strStatic7 = _T("比特率控制:") ;
			m_strStatic8 = _T("M:") ;
			m_strStatic9 = _T("N:") ;
			m_strStatic10 = _T("IDR间隔:") ;
			m_strStatic11 = _T("比特率平均值:") ;
			m_strStatic12 = _T("最小比特率（bps）:") ;
			m_strStatic13 = _T("最大比特率（bps）:") ;
			m_strStatic14 = _T("MJPEG编码质量（bps）:") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
			m_dwEdit3 = _T("0") ;
			m_dwEdit4 = 0 ;
			m_dwEdit5 = 0 ;
			m_dwEdit6 = 0 ;
			m_dwEdit7 = 0 ;
			m_dwEdit8 = 0 ;
			m_dwEdit9 = 0 ;
			m_dwEdit10 = 0 ;
			m_dwEdit11 = 0 ;
			m_dwEdit12 = 0 ;
			m_dwEdit13 = 0 ;
			m_dwEdit14 = 0 ;

		}break ;
	case IPC_ENCODE_SN_TEXT_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("码流ID :") ;
			m_strStatic2 = _T("是否显示字符") ;
			m_strStatic3 = _T("文字") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
			m_dwEdit3 = _T("0") ;
		}break ;
	case IPC_VIDEO_IRCUT_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("等待时间:") ;
			m_strStatic2 = _T("白天转夜晚:") ;
			m_strStatic3 = _T("夜晚转白天:") ;


			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
			m_dwEdit3 = _T("0") ;

		}break ;
	case IPC_VIDEO_SHUTTER_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			
			m_strStatic1 = _T("最小值:") ;
			m_strStatic2 = _T("最大值:") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
		}break ;
	case IPC_VIDEO_DCIRIS_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("DC Iris模式:") ;
			m_strStatic2 = _T("占空值:") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;

		}break ;
	case IPC_VIDEO_PM_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_EDIT_6)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_6)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("起始X坐标:") ;
			m_strStatic2 = _T("起始Y坐标:") ;
			m_strStatic3 = _T("宽:") ;
			m_strStatic4 = _T("高:") ;
			m_strStatic5 = _T("区域颜色:") ;
			m_strStatic6 = _T("遮挡动作:") ;

			m_dwEdit1 = 0 ;
			m_dwEdit2 = _T("0") ;
			m_dwEdit3 = _T("0") ;
			m_dwEdit4 = 0 ;
			m_dwEdit5 = 0 ;
			m_dwEdit6 = 0 ;
		}break ;
	case IPC_VIDEO_EXPOSURE_MODE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("抗闪烁模式:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_AE_TARGET_RATION:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("曝光目标系数:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_MAX_GAIN:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("SenSor最大增益:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_WBC:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("白平衡设置:") ;
			m_dwEdit1 = 0 ;
			
		}break ;
	case IPC_VIDEO_DN_MODE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("夜晚模式:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_BACKLIGHT_COMP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("背光补偿:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_LOCAL_EXPOSURE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("局部曝光模式:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_MCTF_STRENGTH:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("3D降噪:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_IMGPRO_GROUP:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_EDIT_2)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_2)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_EDIT_3)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_3)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_EDIT_4)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_4)->m_hWnd, SW_SHOW) ;

			::ShowWindow(GetDlgItem(IDC_EDIT_5)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_5)->m_hWnd, SW_SHOW) ;
			
			m_strStatic1 = _T("饱和度:") ;
			m_dwEdit1 = 0 ;

			m_strStatic2 = _T("亮度:") ;
			m_dwEdit2 = _T("0") ;

			m_strStatic3 = _T("色度:") ;
			m_dwEdit3 = _T("0") ;

			m_strStatic4 = _T("对比度:") ;
			m_dwEdit4 = 0 ;

			m_strStatic5 = _T("锐度:") ;
			m_dwEdit5 = 0 ;
		}break ;
	//case IPCVIDEO_SATURATION:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("饱和度:") ;
	//		m_dwEdit1 = 0 ;
	//	}break ;
	//case IPCVIDEO_BRIGHTNESS:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("亮度:") ;
	//		m_dwEdit1 = 0 ;
	//	}break ;
	//case IPCVIDEO_HUE:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("色度:") ;
	//		m_dwEdit1 = 0 ;
	//	}break ;
	//case IPCVIDEO_CONTRAST:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("对比度:") ;
	//		m_dwEdit1 = 0 ;
	//	}break ;
	//case IPCVIDEO_SHARPNESS:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("锐度:") ;
	//		m_dwEdit1 = 0 ;
	//	}break ;
	case IPC_VIDEO_SLOW_SHUTTER:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("SlowShutter:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_AE_PREFERENCE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("偏好:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_VIDEO_METERING_MODE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("测光模式:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_ENCODE_ENC_MODE:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("编码模式:") ;
			m_dwEdit1 = 0 ;
		}break ;
	case IPC_ENCODE_SN_TIME_ENABLE0:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("是否显示时间:") ;
			m_dwEdit1 = 0 ;
		}break ;
    case IPC_VIDEO_AF_ENABLE:
        {
            ::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
            ::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

            m_strStatic1 = _T("自动聚焦:") ;
            m_dwEdit1 = 0 ;            
        }break ;
    case IPC_ENCODE_PROPERTY_SN_MJPEG_LEVEL_STREAM0:
        {
            ::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
            ::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

            m_strStatic1 = _T("MJPEG编码质量级别:") ;
            m_dwEdit1 = 0 ;
        }break ;
    case IPC_VIDEO_WBC_CUSTOM_R_GAIN:
        {
            ::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
            ::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

            m_strStatic1 = _T("白平衡自定义模式，红增益:") ;
            m_dwEdit1 = 0 ;
        }break ;
    case IPC_VIDEO_WBC_CUSTOM_B_GAIN:
        {
            ::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
            ::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

            m_strStatic1 = _T("白平衡自定义模式，蓝增益:") ;
            m_dwEdit1 = 0 ;
        }break ;
    case IPC_VIDEO_MJPEG_QUALITY:
		{
			::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
			::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

			m_strStatic1 = _T("编码质量:") ;
			m_dwEdit1 = 0 ;
		}break ;
	//case IPCCMD_PTZ_PROTOCOL:
	//	{
	//		::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
	//		::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

	//		m_strStatic1 = _T("云台协议:") ;
	//		m_dwEdit1 = 0 ;
	//	}
	//	break;
    case IPC_ENCODE_STR_I_INTERVAL:
        {
            ::ShowWindow(GetDlgItem(IDC_EDIT_1)->m_hWnd, SW_SHOW) ;
            ::ShowWindow(GetDlgItem(IDC_STATIC_1)->m_hWnd, SW_SHOW) ;

            m_strStatic1 = _T("I帧间隔:") ;

        }break;
	}

	UpdateData(FALSE) ;
}

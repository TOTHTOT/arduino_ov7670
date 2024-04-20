
// serial_port_ov7670Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "serial_port_ov7670.h"
#include "serial_port_ov7670Dlg.h"
#include "afxdialogex.h"
#include "afx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include <thread>


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cserialportov7670Dlg 对话框



Cserialportov7670Dlg::Cserialportov7670Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERIAL_PORT_OV7670_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cserialportov7670Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// 绑定id
	DDX_Control(pDX, serial_port_list_cbb_id, serial_port_list_cbb);
	DDX_Control(pDX, refresh_btn_id, refresh_btn);
	DDX_Control(pDX, connect_btn_id, connect_btn);
	DDX_Control(pDX, disconnect_btn_id, disconnect_btn);

	disconnect_btn.EnableWindow(false);

}

BEGIN_MESSAGE_MAP(Cserialportov7670Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(refresh_btn_id, &Cserialportov7670Dlg::onclick_refresh_btn)
	ON_BN_CLICKED(connect_btn_id, &Cserialportov7670Dlg::onclick_connect_btn)
	ON_BN_CLICKED(disconnect_btn_id, &Cserialportov7670Dlg::onclick_disconnecte_btn)
END_MESSAGE_MAP()


// Cserialportov7670Dlg 消息处理程序

BOOL Cserialportov7670Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cserialportov7670Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cserialportov7670Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cserialportov7670Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**
 * @name: onclick_refresh_btn
 * @msg: 刷新 combox 内容
 * @return {*}
 * @author: TOTHTOT
 * @Date: 2024-04-20 18:05:11
 */
void Cserialportov7670Dlg::onclick_refresh_btn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE(_T("onclick_refresh_btn()\n"));
	const int COM_NUM = 15;//最大串口数
	int i = 1;
	for (i = 1; i <= COM_NUM; i++)//循环COM_NUM次，串口数最多的情况
	{
		//形成原始设备名称
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);
		//尝试打开该端口
		BOOL bSuccess = FALSE;
		HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

		//添加串口号
		CString strPortID;
		strPortID.Empty();
		strPortID.AppendFormat((CString)"COM%d", i);

		if (hPort == INVALID_HANDLE_VALUE)
			//串口打开失败
		{
			DWORD dwError = GetLastError();

			if (dwError == ERROR_ACCESS_DENIED)
			{
				bSuccess = TRUE;
			}
			int nDelIndex = serial_port_list_cbb.FindStringExact(-1, strPortID);
			if (nDelIndex != CB_ERR)//串口存在列表中，则删除串口
				serial_port_list_cbb.DeleteString(nDelIndex);
		}
		else
		{
			//该端口已成功打开
			bSuccess = TRUE;
			//不要忘记关闭端口，因为我们不会对它做任何事情
			CloseHandle(hPort);
			if (serial_port_list_cbb.FindStringExact(-1, strPortID) == CB_ERR)//若串口不存在，则添加串口
				serial_port_list_cbb.AddString(strPortID);
		}
	}
}


uint8_t Cserialportov7670Dlg::send_get_image_cmd()
{
	DWORD bytesWritten;
	if (!WriteFile(hSerial, GET_IMAGE_CMD, strlen(GET_IMAGE_CMD), &bytesWritten, NULL))
	{
		TRACE("Failed to write to serial port.\n");
		CloseHandle(hSerial);
		return 1;
	}

	return 0;
}

uint8_t Cserialportov7670Dlg::send_app_down_cmd()
{
	DWORD bytesWritten;
	if (!WriteFile(hSerial, APP_EXIT_CMD, strlen(APP_EXIT_CMD), &bytesWritten, NULL))
	{
		TRACE("Failed to write to serial port.\n");
		CloseHandle(hSerial);
		return 1;
	}

	return 0;
}

// 串口接收线程函数
void Cserialportov7670Dlg::SerialReceiveThread()
{
	// 设置串口超时参数
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = MAXDWORD;  // 读取间隔超时，设置为MAXDWORD表示不使用
	timeouts.ReadTotalTimeoutConstant = 10;    // 读取总超时时间，设置为0表示非阻塞
	timeouts.ReadTotalTimeoutMultiplier = 1;  // 读取总超时时间的乘数，设置为0表示非阻塞
	timeouts.WriteTotalTimeoutConstant = 0;   // 写入总超时时间，设置为0表示非阻塞
	timeouts.WriteTotalTimeoutMultiplier = 0; // 写入总超时时间的乘数，设置为0表示非阻塞
	SetCommTimeouts(hSerial, &timeouts);
	TRACE("SerialReceiveThread start\n");
	// 接收数据
	while (is_running)
	{
		char buffer[20*1024];
		DWORD bytesRead;

		if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
		{
			if (bytesRead > 0)
			{
				buffer[bytesRead] = '\0';
				TRACE("Received data: %s", buffer);
			}
			//else
			//{
			//	TRACE("time out\n");
			//}
		}
		else
		{
			// 处理读取错误
			DWORD error = GetLastError();
			if (error != ERROR_IO_PENDING)
			{
				TRACE("Error reading from serial port. Code: ", error);
				break;
			}
		}
		//TRACE("running\n");
		send_get_image_cmd();
		Sleep(100);
	}
}

void Cserialportov7670Dlg::onclick_connect_btn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE(_T("onclick_connect_btn()\n"));

	//获取端口号
	CString strPortID;
	serial_port_list_cbb.GetWindowText(strPortID);

	if (strPortID.GetLength() <= 0)
	{
		TRACE("Failed to get serial port name.\n");
		return;
	}

	TRACE("strPortID = %s\n", strPortID);
	hSerial = CreateFile(strPortID, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		TRACE("Failed to open serial port.\n");
		return ;
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		TRACE("Failed to get serial port parameters.\n");
		CloseHandle(hSerial);
		return ;
	}

	dcbSerialParams.BaudRate = CBR_256000;  // 设置波特率为9600
	dcbSerialParams.ByteSize = 8;          // 设置数据位为8位
	dcbSerialParams.StopBits = ONESTOPBIT; // 设置停止位为1位
	dcbSerialParams.Parity = NOPARITY;     // 不使用校验位

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		TRACE("Failed to set serial port parameters.\n");
		CloseHandle(hSerial);
		return ;
	}
	is_running = true;
	// 创建串口接收线程
	receiveThread = std::thread(&Cserialportov7670Dlg::SerialReceiveThread, this);

	send_get_image_cmd();
	connect_btn.EnableWindow(false);
	disconnect_btn.EnableWindow(true); 
}


void Cserialportov7670Dlg::onclick_disconnecte_btn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (hSerial != INVALID_HANDLE_VALUE)
	{
		is_running = false;
		
		// 等待接收线程退出
		receiveThread.join();
		
		send_app_down_cmd();
		// 关闭串口
		CloseHandle(hSerial);

		connect_btn.EnableWindow(true);
		disconnect_btn.EnableWindow(false);
	}
}

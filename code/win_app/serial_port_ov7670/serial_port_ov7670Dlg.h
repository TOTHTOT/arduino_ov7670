
// serial_port_ov7670Dlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm_com.h"
#include <thread>

#define WIDTH 320
#define HEIGHT 240
// Cserialportov7670Dlg 对话框
class Cserialportov7670Dlg : public CDialogEx
{
// 构造
public:
	Cserialportov7670Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	std::thread receiveThread; // 用于接收数据的线程对象
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_PORT_OV7670_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox serial_port_list_cbb;
	CButton connect_btn;
	CButton disconnect_btn;
	CButton refresh_btn;
	CStatic image_stt;
	CBitmap image_bitmap;

#define GET_IMAGE_CMD "get_image"
#define APP_EXIT_CMD "app_down"
	bool is_running;


	// 串口通信
	HANDLE hSerial;
	afx_msg void onclick_refresh_btn();
	afx_msg uint8_t send_get_image_cmd();
	afx_msg uint8_t send_app_down_cmd();
	afx_msg void SerialReceiveThread();
	afx_msg void OnReceiveSerialData(uint8_t* image_buf);

private:
	CString recv_str;
public:
	afx_msg void onclick_connect_btn();
	afx_msg void onclick_disconnecte_btn();
	afx_msg void OnStnClickedsttid();
};

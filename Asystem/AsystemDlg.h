// AsystemDlg.h: 头文件
//

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <afx.h>
// CAsystemDlg 对话框
class CAsystemDlg : public CDialogEx
{
	// 构造
public:
	CAsystemDlg(CWnd *pParent = nullptr); // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_ASYSTEM_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV 支持

	// 实现
protected:
	HICON m_hIcon;
	CFont m_Font;
	CFont m_Font1;
	CToolTipCtrl m_ToolTip; // 工具提示控件

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public: // 定义变量
	afx_msg void OnBnClickedAddB();
	afx_msg void OnBnClickedSearchB();
	afx_msg void OnBnClickedModifyB();
	afx_msg void OnBnClickedDeleteB();
	CString m_Class;
	CString m_Name;
	CString m_Number;
	CString m_Sex;
	CString m_Phone;
	CListCtrl m_List;
	afx_msg void OnBnClickedBclearall();
	afx_msg void OnBnClickedBclearin();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEnumber();
	afx_msg void OnLbnSelchangeLall();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};

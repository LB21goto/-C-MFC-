// AsystemDlg.cpp: 实现文件
#include "pch.h"
#include "framework.h"
#include "Asystem.h"
#include "AsystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// 用于应用程序"关于"菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_ABOUTBOX
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CAsystemDlg 对话框

CAsystemDlg::CAsystemDlg(CWnd *pParent /*=nullptr*/)
	: CDialogEx(IDD_ASYSTEM_DIALOG, pParent), m_Name(_T("")), m_Number(_T("")), m_Sex(_T("")), m_Phone(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsystemDlg::DoDataExchange(CDataExchange *pDX) // 框内数据交换
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Eclass, m_Class);
	DDX_Text(pDX, IDC_Ename, m_Name);
	DDX_Text(pDX, IDC_Enumber, m_Number);
	DDX_Text(pDX, IDC_Esex, m_Sex);
	DDX_Text(pDX, IDC_Ephone, m_Phone);
	DDX_Control(pDX, IDC_LIST2, m_List);
}

BEGIN_MESSAGE_MAP(CAsystemDlg, CDialogEx) // 按钮点击映射
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_Add_B, &CAsystemDlg::OnBnClickedAddB)
ON_BN_CLICKED(IDC_Search_B, &CAsystemDlg::OnBnClickedSearchB)
ON_BN_CLICKED(IDC_Modify_B, &CAsystemDlg::OnBnClickedModifyB)
ON_BN_CLICKED(IDC_Delete_B, &CAsystemDlg::OnBnClickedDeleteB)
ON_BN_CLICKED(IDC_Bclearall, &CAsystemDlg::OnBnClickedBclearall)
ON_BN_CLICKED(IDC_Bclearin, &CAsystemDlg::OnBnClickedBclearin)
ON_BN_CLICKED(IDCANCEL, &CAsystemDlg::OnBnClickedCancel)
/*ON_EN_CHANGE(IDC_Enumber, &CAsystemDlg::OnEnChangeEnumber)*/
/*ON_LBN_SELCHANGE(IDC_LAll, &CAsystemDlg::OnLbnSelchangeLall)*/
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CAsystemDlg::OnLvnItemchangedList2)
ON_WM_MOUSEMOVE() // 添加鼠标移动消息处理
END_MESSAGE_MAP()

// CAsystemDlg 消息处理程序
// 设置结构体数组用于保存数据
struct Msg
{
	CString Class;
	CString Name;
	CString Number;
	CString Sex;
	CString Phone;
	Msg *next;
} *msg = new Msg;

void change(int *i)
{
	if (*i == 5)
		*i = 1;
	else if (*i < 5)
		*i = *i + 1;
} // 数字为结构体内数据类数

CString All; // 用于保存个人信息的字符串
Msg *index;	 // 设置递增指针用于添加

BOOL CAsystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置报表模式（必须）
	m_List.ModifyStyle(0, LVS_REPORT);

	// 创建工具提示控件
	m_ToolTip.Create(this, TTS_ALWAYSTIP);
	m_ToolTip.SetDelayTime(TTDT_AUTOPOP, 5000); // 显示时间
	m_ToolTip.SetDelayTime(TTDT_INITIAL, 500);	// 初始延迟
	m_ToolTip.SetMaxTipWidth(300);				// 提示框最大宽度

	// 为每个控件添加提示文本
	m_ToolTip.AddTool(GetDlgItem(IDC_Add_B), _T("添加新的联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Search_B), _T("指定学号搜索已有联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Modify_B), _T("修改指定学号联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Delete_B), _T("删除指定学号联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Bclearall), _T("清空所有联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Bclearin), _T("清空输入框"));

	m_ToolTip.Activate(TRUE);

	// 将"关于..."菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
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
	SetIcon(m_hIcon, TRUE);	 // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 字体大小
	// 创建新字体(此为主标题
	m_Font.CreateFont(
		50,			  // 字体高度
		20,			  // 字体宽度
		0,			  // 倾斜角度
		0,			  // 方向角度
		FW_NORMAL,	  // 字体粗细
		FALSE,		  // 是否斜体
		FALSE,		  // 是否下划线
		0,			  // 是否删除线
		ANSI_CHARSET, // 字符集
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")); // 字体名称
	// 此为表格内字体
	m_Font1.CreateFont(
		24,			  // 字体高度
		11,			  // 字体宽度
		0,			  // 倾斜角度
		0,			  // 方向角度
		FW_NORMAL,	  // 字体粗细
		FALSE,		  // 是否斜体
		FALSE,		  // 是否下划线
		0,			  // 是否删除线
		ANSI_CHARSET, // 字符集
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("宋体")); // 字体名称

	// 获取 Static 控件并设置字体（list2默认大小合适，暂不使用
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
	/*GetDlgItem(IDC_LIST2)->SetFont(&m_Font1);*/

	int i = 1;
	msg->next = NULL;
	fstream File;
	string str;		 // 用于保存获取的行
	stringstream ss; // 把保存的行给予字符串流
	string item;	 // 把字符串流分割出的字符串给予item
	CString citem;

	// 初始化表格
	m_List.ModifyStyle(0, LVS_REPORT);								  // 设置为报表模式
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 网格线 + 整行选择

	// 添加列
	// 此为表格第一行自定义类名
	m_List.InsertColumn(0, _T("Class"), LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 65);
	m_List.InsertColumn(2, _T("ID"), LVCFMT_LEFT, 140);
	m_List.InsertColumn(3, _T("Sex"), LVCFMT_LEFT, 65);
	m_List.InsertColumn(4, _T("Phone"), LVCFMT_LEFT, 140);
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 打开CSV文件
	File.open("message.csv", ios::in);
	if (!File.is_open())
	{
		AfxMessageBox(_T("无法打开文件！"));
		return FALSE;
	}
	// 跳过标题行（第一行）
	getline(File, str);
	int nRow = 0; // 表格行索引

	// 读取数据行
	while (getline(File, str))
	{
		// 创建新节点并添加到链表
		index = msg;
		while (index->next != NULL)
		{
			index = index->next;
		}
		Msg *node = new Msg;
		node->next = NULL;
		index->next = node;
		index = index->next;

		// 解析CSV行数据
		ss.clear();
		ss << str;
		i = 1; // 重置列计数器

		// 插入新行到表格
		int nItem = m_List.InsertItem(nRow, _T("")); // 先插入空行
		while (getline(ss, item, ','))
		{
			citem = item.c_str();

			// 填充链表节点
			switch (i)
			{
			case 1:
				index->Class = citem;
				break;
			case 2:
				index->Name = citem;
				break;
			case 3:
				index->Number = citem;
				break;
			case 4:
				index->Sex = citem;
				break;
			case 5:
				index->Phone = citem;
				break;
			}

			// 填充表格数据（列索引是i-1）
			m_List.SetItemText(nItem, i - 1, citem);
			change(&i); // 你的列计数器递增函数
		}
		nRow++;
	}

	File.close();
	return TRUE;
}

void CAsystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAsystemDlg::OnPaint()
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

// 当用户拖动最小化窗口时系统调用此函数取得光标
// 显示。
HCURSOR CAsystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAsystemDlg::OnBnClickedAddB() // 添加功能***
{									// TODO: 在此添加控件通知处理程序代码
	// 重置index
	index = msg;
	while (index->next != NULL)
	{
		index = index->next;
	}
	UpdateData(TRUE); // 传入数据
	Msg *search = msg->next;
	if (m_Name != "" && m_Number != "")
	{ // 必须输入学号与姓名
		if (search != NULL)
		{
			while (search != NULL && m_Number != search->Number && search->next != NULL)
			{
				search = search->next;
			}
			if (m_Number == search->Number)
				return; // 出现重复学号不予处理
		}
		Msg *node = new Msg; // 利用链表存储信息
		node->next = NULL;
		index->next = node;
		index = index->next;
		index->Class = m_Class;
		index->Name = m_Name;
		index->Number = m_Number;
		index->Sex = m_Sex;
		index->Phone = m_Phone;
		CString All = m_Class + _T(",") + m_Name + _T(",") + m_Number + _T(",") + m_Sex + _T(",") + m_Phone + _T(",");

		// 在 CListCtrl 中添加新行
		int nItem = m_List.InsertItem(m_List.GetItemCount(), m_Class);
		// 设置其他列的值
		m_List.SetItemText(nItem, 1, m_Name);
		m_List.SetItemText(nItem, 2, m_Number);
		m_List.SetItemText(nItem, 3, m_Sex);
		m_List.SetItemText(nItem, 4, m_Phone);
		UpdateData(FALSE); // 显示数据
		MessageBox(_T("添加成功"));
	}
}

void CAsystemDlg::OnBnClickedSearchB() // 查找功能***
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); // 将控件中的数据更新到成员变量

	Msg *search = msg->next;			   // 从链表的第一个节点开始搜索
	if (m_Number != L"" && search != NULL) // 确保学号不为空且链表不为空
	{
		while (search != NULL && m_Number != search->Number) // 根据学号查找
		{
			search = search->next;
		}
		if (search != NULL && (m_Name == L"" || m_Name == search->Name)) // 如果找到匹配的学号，并且姓名匹配（或未输入姓名）
		{
			// 构造要显示的字符串
			CString All = search->Class + _T(",") + search->Name + _T(",") + search->Number + _T(",") + search->Sex + _T(",") + search->Phone + _T(",");

			// 清空 CListCtrl
			m_List.DeleteAllItems();
			// 在 CListCtrl 中插入新行
			int nItem = m_List.InsertItem(m_List.GetItemCount(), search->Class); // 插入新行，第一列显示 Class
			m_List.SetItemText(nItem, 1, search->Name);
			m_List.SetItemText(nItem, 2, search->Number);
			m_List.SetItemText(nItem, 3, search->Sex);
			m_List.SetItemText(nItem, 4, search->Phone);

			// 更新成员变量
			m_Class = search->Class;
			m_Name = search->Name;
			m_Number = search->Number;
			m_Sex = search->Sex;
			m_Phone = search->Phone;

			MessageBox(_T("查找成功"));
		}
		else
		{
			MessageBox(_T("未找到匹配项"));
		}
	}
	UpdateData(FALSE); // 将成员变量中的数据更新到控件
}

void CAsystemDlg::OnBnClickedModifyB() // 修改功能***
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);		 // 从控件中获取数据
	Msg *search = msg->next; // 假设 msg 是链表的头节点

	if (search != NULL && m_Number != "") // 只需要输入学号即可进行修改
	{
		while (m_Number != search->Number && search->next != NULL)
		{
			search = search->next;
		}

		if (m_Number == search->Number) // 找到匹配的学号
		{
			// 更新链表中的数据
			search->Class = m_Class;
			search->Name = m_Name;
			search->Number = m_Number;
			search->Sex = m_Sex;
			search->Phone = m_Phone;

			// 更新 CListCtrl 中的显示
			int nItem = -1;
			for (int i = 0; i < m_List.GetItemCount(); i++) // 遍历 CListCtrl 中的所有项
			{
				CString itemNumber;
				m_List.GetItemText(i, 2);	// 假设学号在第3列（索引2）
				if (itemNumber == m_Number) // 找到匹配的学号
				{
					nItem = i;
					break;
				}
			}
			if (nItem != -1) // 如果找到了匹配的项
			{
				// 更新 CListCtrl 中的每一列
				m_List.SetItemText(nItem, 0, m_Class);	// 假设班级在第1列（索引0）
				m_List.SetItemText(nItem, 1, m_Name);	// 假设姓名在第2列（索引1）
				m_List.SetItemText(nItem, 2, m_Number); // 假设学号在第3列（索引2）
				m_List.SetItemText(nItem, 3, m_Sex);	// 假设性别在第4列（索引3）
				m_List.SetItemText(nItem, 4, m_Phone);	// 假设电话在第5列（索引4）
			}
			MessageBox(L"修改成功");
		}
		else
		{
			MessageBox(L"未找到匹配的学号");
		}
	}
	else
	{
		MessageBox(L"请输入学号");
	}
	UpdateData(FALSE); // 更新数据
}

void CAsystemDlg::OnBnClickedDeleteB() // 删除功能***
{
	// TODO: 在此添加控件通知处理程序代码
	// 在链表中查找对应的节点
	UpdateData(TRUE);
	Msg *search = msg->next; // 指向链表的第一个有效节点
	Msg *pri = msg;			 // 指向链表的头节点（哑节点）

	while (search != NULL)
	{
		if (search->Number == m_Number)
		{
			// 找到对应的节点，删除链表中的节点
			pri->next = search->next;
			delete search;
			break;
		}
		pri = search;
		search = search->next;
	}

	// 在列表控件中查找对应的项
	int itemCount = m_List.GetItemCount();
	for (int i = 0; i < itemCount; ++i)
	{
		CString itemNumber = m_List.GetItemText(i, 2); // 假设第一列存储学号
		if (itemNumber == m_Number)
		{
			// 找到对应的项，删除列表控件中的项
			m_List.DeleteItem(i);
			break;
		}
	}
	UpdateData(FALSE);
}

void CAsystemDlg::OnBnClickedBclearall()
{
	//// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_List.DeleteAllItems();
	Msg *search = msg->next;
	Msg *p;
	msg->next = NULL;
	while (search != NULL)
	{
		p = search;
		search = search->next;
		delete p;
	}
	UpdateData(FALSE);
}

void CAsystemDlg::OnBnClickedBclearin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Class = L"";
	m_Name = L"";
	m_Number = L"";
	m_Sex = L"";
	m_Phone = L"";
	UpdateData(FALSE);
}

void CAsystemDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	fstream File;
	Msg *search = msg->next;
	string column("Class,Name,ID,Sex,Phone");
	string row;
	File.open("message.csv", ios::out);
	File << column << "\n";
	while (search != NULL)
	{
		All = search->Class + _T(",") + search->Name + _T(",") + search->Number + _T(",") + search->Sex + _T(",") + search->Phone + _T(",");
		row = CT2A(All.GetString());
		File << row << "\n";
		search = search->next;
	}
	File.close();
	MessageBox(L"通讯录操作已保存");
	CDialogEx::OnCancel();
}

void CAsystemDlg::OnEnChangeEnumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志"或"运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CAsystemDlg::OnLbnSelchangeLall()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAsystemDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

// 添加鼠标移动消息处理函数
void CAsystemDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG msg;
	msg.hwnd = m_hWnd;
	msg.message = WM_MOUSEMOVE;
	msg.wParam = nFlags;
	msg.pt = point;
	msg.lParam = MAKELPARAM(point.x, point.y);

	m_ToolTip.RelayEvent(&msg);
	CDialogEx::OnMouseMove(nFlags, point);
}

// 添加PreTranslateMessage函数实现
BOOL CAsystemDlg::PreTranslateMessage(MSG *pMsg)
{
	if (m_ToolTip.GetSafeHwnd())
		m_ToolTip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}

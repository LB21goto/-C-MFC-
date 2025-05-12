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
	: CDialogEx(IDD_ASYSTEM_DIALOG, pParent), m_Name(_T("")), m_ID(_T("")), m_Sex(_T("")), m_Phone(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsystemDlg::DoDataExchange(CDataExchange *pDX) // 框内数据交换
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Eclass, m_Class);
	DDX_Text(pDX, IDC_Ename, m_Name);
	DDX_Text(pDX, IDC_EID, m_ID);
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
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CAsystemDlg::OnLvnItemchangedList2)
ON_WM_MOUSEMOVE() // 添加鼠标移动消息处理
ON_EN_CHANGE(IDC_Enumber, &CAsystemDlg::OnEnChangeEnumber)
ON_BN_CLICKED(IDC_BUTTON1, &CAsystemDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CAsystemDlg 消息处理程序
Msg *msg = new Msg;	 // 此为头结点，不可能不创
Msg *tail = new Msg; // 此为尾结点，不可能不创

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
	msg = new Msg; // 创建头结点
	msg->next = NULL;
	tail = new Msg; // 创建尾结点
	tail->next = NULL;
	// 创建工具提示控件（鼠标悬停动作
	m_ToolTip.Create(this, TTS_ALWAYSTIP);
	m_ToolTip.SetDelayTime(TTDT_AUTOPOP, 5000); // 显示时间
	m_ToolTip.SetDelayTime(TTDT_INITIAL, 500);	// 初始延迟
	m_ToolTip.SetMaxTipWidth(300);				// 提示框最大宽度

	// 为每个控件添加提示文本
	m_ToolTip.AddTool(GetDlgItem(IDC_Add_B), _T("添加新的联系人"));
	m_ToolTip.AddTool(GetDlgItem(IDC_Search_B), _T("搜索已有联系人"));
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
		_T("Arial"));
	// 获取 Static 控件并设置字体（list2默认大小合适，暂不使用
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);

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

	// 从文件加载数据
	fstream File;
	File.open("message.csv", ios::in);
	if (!File.is_open())
	{
		// 如果文件不存在，创建新文件
		File.open("message.csv", ios::out);
		if (File.is_open())
		{
			File << "Class,Name,ID,Sex,Phone\n";
			File.close();
		}
		return TRUE;
	}

	string str;
	getline(File, str); // 跳过标题行

	Msg *tail = msg; // 用于追加节点
	while (getline(File, str))
	{
		stringstream ss(str);
		string item;
		Msg *newNode = new Msg;
		newNode->next = NULL;

		// 读取每个字段
		if (getline(ss, item, ','))
			newNode->Class = CString(item.c_str());
		if (getline(ss, item, ','))
			newNode->Name = CString(item.c_str());
		if (getline(ss, item, ','))
			newNode->ID = CString(item.c_str());
		if (getline(ss, item, ','))
			newNode->Sex = CString(item.c_str());
		if (getline(ss, item, ','))
			newNode->Phone = CString(item.c_str());

		// 添加到链表
		tail->next = newNode;
		tail = newNode;

		// 添加到表格显示
		int nItem = m_List.InsertItem(m_List.GetItemCount(), newNode->Class);
		m_List.SetItemText(nItem, 1, newNode->Name);
		m_List.SetItemText(nItem, 2, newNode->ID);
		m_List.SetItemText(nItem, 3, newNode->Sex);
		m_List.SetItemText(nItem, 4, newNode->Phone);
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
	// index
	index = msg;
	while (index->next != NULL)
	{
		index = index->next;
	}
	UpdateData(TRUE); // 传入数据
	Msg *search = msg->next;
	if (m_Name != "" && m_ID != "")
	{ // 输入学号与姓名
		if (search != NULL)
		{
			while (search != NULL && m_ID != search->ID && search->next != NULL)
			{
				search = search->next;
			}
			if (m_ID == search->ID)
				return; // 出现重复学号不予处理
		}
		Msg *node = new Msg; // 利用链表存储信息
		node->next = NULL;
		index->next = node;
		index = index->next;
		index->Class = m_Class;
		index->Name = m_Name;
		index->ID = m_ID;
		index->Sex = m_Sex;
		index->Phone = m_Phone;
		CString All = m_Class + _T(",") + m_Name + _T(",") + m_ID + _T(",") + m_Sex + _T(",") + m_Phone + _T(",");

		// 在 CListCtrl 中添加新行
		int nItem = m_List.InsertItem(m_List.GetItemCount(), m_Class);
		// 设置其他列的值
		m_List.SetItemText(nItem, 1, m_Name);
		m_List.SetItemText(nItem, 2, m_ID);
		m_List.SetItemText(nItem, 3, m_Sex);
		m_List.SetItemText(nItem, 4, m_Phone);
		UpdateData(FALSE); // 显示数据
		MessageBox(_T("添加成功"));
	}
}

void CAsystemDlg::OnBnClickedSearchB() // 查找功能***
{
	UpdateData(TRUE); // 将控件中的数据更新到成员变量

	Msg *search = msg->next; // 从链表的第一个节点开始搜索
	bool found = false;

	// 清空 CListCtrl，准备显示搜索结果
	m_List.DeleteAllItems();
	int nRow = 0;

	// 遍历链表搜索匹配项
	while (search != NULL)
	{
		bool match = false;
		// 按学号搜索
		if (m_ID != L"" && m_ID == search->ID)
		{
			match = true;
		}
		// 按姓名搜索
		else if (m_Name != L"" && m_Name == search->Name)
		{
			match = true;
		}
		// 按电话搜索
		else if (m_Phone != L"" && m_Phone == search->Phone)
		{
			match = true;
		}

		if (match)
		{
			// 在 CListCtrl 中插入匹配的行
			int nItem = m_List.InsertItem(nRow, search->Class);
			m_List.SetItemText(nItem, 1, search->Name);
			m_List.SetItemText(nItem, 2, search->ID);
			m_List.SetItemText(nItem, 3, search->Sex);
			m_List.SetItemText(nItem, 4, search->Phone);
			nRow++;
			found = true;
		}
		search = search->next;
	}

	if (found)
	{
		MessageBox(_T("查找成功"));
	}
	else
	{
		MessageBox(_T("未找到匹配项"));
		// 恢复显示所有数据
		search = msg->next;
		nRow = 0;
		while (search != NULL)
		{
			int nItem = m_List.InsertItem(nRow, search->Class);
			m_List.SetItemText(nItem, 1, search->Name);
			m_List.SetItemText(nItem, 2, search->ID);
			m_List.SetItemText(nItem, 3, search->Sex);
			m_List.SetItemText(nItem, 4, search->Phone);
			nRow++;
			search = search->next;
		}
	}
	UpdateData(FALSE);
}

void CAsystemDlg::OnBnClickedModifyB() // 修改功能
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);		 // 从控件中获取数据
	Msg *search = msg->next; // 假设 msg 是链表的头节点

	if (search != NULL && m_ID != "") // 只需要输入学号即可进行修改
	{
		while (m_ID != search->ID && search->next != NULL)
		{
			search = search->next;
		}

		if (m_ID == search->ID) // 找到匹配的学号
		{
			// 更新链表中的数据
			search->Class = m_Class;
			search->Name = m_Name;
			search->ID = m_ID;
			search->Sex = m_Sex;
			search->Phone = m_Phone;

			// 更新 CListCtrl 中的显示
			int nItem = -1;
			for (int i = 0; i < m_List.GetItemCount(); i++) // 遍历 CListCtrl 中的所有项
			{
				CString itemID;
				m_List.GetItemText(i, 2); // 假设学号在第3列（索引2）
				if (itemID == m_ID)		  // 找到匹配的学号
				{
					nItem = i;
					break;
				}
			}
			if (nItem != -1) // 如果找到了匹配的项
			{
				// 更新 CListCtrl 中的每一列
				m_List.SetItemText(nItem, 0, m_Class); // 假设班级在第1列（索引0）
				m_List.SetItemText(nItem, 1, m_Name);  // 假设姓名在第2列（索引1）
				m_List.SetItemText(nItem, 2, m_ID);	   // 假设学号在第3列（索引2）
				m_List.SetItemText(nItem, 3, m_Sex);   // 假设性别在第4列（索引3）
				m_List.SetItemText(nItem, 4, m_Phone); // 假设电话在第5列（索引4）
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

void CAsystemDlg::OnBnClickedDeleteB() // 删除功能
{
	// TODO: 在此添加控件通知处理程序代码
	// 在链表中查找对应的节点
	UpdateData(TRUE);
	Msg *search = msg->next; // 指向链表的第一个有效节点
	Msg *pri = msg;			 // 指向链表的头节点（哑节点）

	while (search != NULL)
	{
		if (search->ID == m_ID)
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
		CString itemID = m_List.GetItemText(i, 2); // 假设第一列存储学号
		if (itemID == m_ID)
		{
			// 找到对应的项，删除列表控件中的项
			m_List.DeleteItem(i);
			break;
		}
	}
	MessageBox(L"删除完毕");
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
	m_ID = L"";
	m_Sex = L"";
	m_Phone = L"";
	UpdateData(FALSE);
}

void CAsystemDlg::OnBnClickedCancel()
{
	fstream File;
	File.open("message.csv", ios::out);
	// 写入表头
	File << "Class,Name,ID,Sex,Phone\n";

	// 从第一个有效节点开始保存
	Msg *search = msg->next;
	while (search != NULL)
	{
		CStringA strClass(search->Class);
		CStringA strName(search->Name);
		CStringA strID(search->ID);
		CStringA strSex(search->Sex);
		CStringA strPhone(search->Phone);

		// 写入
		File << strClass.GetString() << ","
			 << strName.GetString() << ","
			 << strID.GetString() << ","
			 << strSex.GetString() << ","
			 << strPhone.GetString() << "\n";

		search = search->next; // 往复循环
	}
	File.close();
	MessageBox(L"通讯录操作已保存");
	CDialogEx::OnCancel();
}

void CAsystemDlg::OnEnChangeEID()
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

void CAsystemDlg::OnEnChangeEnumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志"或"运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CAsystemDlg::OnBnClickedButton1() // reset功能
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 清空表格所有内容
	m_List.DeleteAllItems();

	// 从链表中重新读取数据
	Msg *current = msg->next;
	int nRow = 0;

	// 重新填充表格
	while (current != NULL)
	{
		// 插入新行并设置第一列
		int nItem = m_List.InsertItem(nRow, current->Class);
		// 设置其他列的值
		m_List.SetItemText(nItem, 1, current->Name);
		m_List.SetItemText(nItem, 2, current->ID);
		m_List.SetItemText(nItem, 3, current->Sex);
		m_List.SetItemText(nItem, 4, current->Phone);

		current = current->next;
		nRow++;
	}
	UpdateData(FALSE);
}


// MFC_C4_1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_C4_1.h"
#include "MFC_C4_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
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


// CMFC_C4_1Dlg ��ȭ ����



CMFC_C4_1Dlg::CMFC_C4_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_C4_1_DIALOG, pParent)
	, m_Edit1(_T(""))
	, m_Edit2(_T(""))
	, m_bCheck(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_C4_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}

BEGIN_MESSAGE_MAP(CMFC_C4_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_CHECK1, &CMFC_C4_1Dlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK1, &CMFC_C4_1Dlg::OnClickedCheck1)
ON_BN_CLICKED(IDC_BUTTON_Wi_Right, &CMFC_C4_1Dlg::OnClickedButtonWiRight)
ON_BN_CLICKED(IDC_BUTTON_Wi_Left, &CMFC_C4_1Dlg::OnClickedButtonWiLeft)
ON_BN_CLICKED(IDC_BUTTON_Lef_Down, &CMFC_C4_1Dlg::OnClickedButtonLefDown)
ON_BN_CLICKED(IDC_BUTTON_Lef_Up, &CMFC_C4_1Dlg::OnClickedButtonLefUp)
ON_BN_CLICKED(IDC_BUTTON_Rig_Down, &CMFC_C4_1Dlg::OnClickedButtonRigDown)
ON_BN_CLICKED(IDC_BUTTON_Rig_Up, &CMFC_C4_1Dlg::OnClickedButtonRigUp)
ON_BN_CLICKED(IDC_BUTTON_Are_Right, &CMFC_C4_1Dlg::OnClickedButtonAreRight)
ON_BN_CLICKED(IDC_BUTTON_Are_Left, &CMFC_C4_1Dlg::OnClickedButtonAreLeft)
END_MESSAGE_MAP()


// CMFC_C4_1Dlg �޽��� ó����

BOOL CMFC_C4_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_C4_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_C4_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_C4_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_C4_1Dlg::OnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bCheck)
		m_bCheck = TRUE;
	else
		m_bCheck = FALSE;
}


void CMFC_C4_1Dlg::OnClickedButtonWiRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (!m_Edit1.IsEmpty())
	{
		if (!m_bCheck)
			m_Edit2.Append(m_Edit1);
		else
		{
			m_Edit2.Append(m_Edit1);
			m_Edit1.Empty();
		}
	}
	else
		AfxMessageBox(_T("����Ʈ ���ڿ� ���ڿ��� �����ϴ�."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonWiLeft()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (!m_Edit2.IsEmpty())
	{
		if (!m_bCheck)
			m_Edit1.Append(m_Edit2);
		else
		{
			m_Edit1.Append(m_Edit2);
			m_Edit2.Empty();
		}
	}
	else
		AfxMessageBox(_T("����Ʈ ���ڿ� ���ڿ��� �����ϴ�."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonLefDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (!m_Edit1.IsEmpty())
	{
		if (!m_bCheck)
			m_List.AddString(m_Edit1);
		else
		{
			m_List.AddString(m_Edit1);
			m_Edit1.Empty();
		}
	}
	else
		AfxMessageBox(_T("����Ʈ ���ڿ� ���ڿ��� �����ϴ�."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonLefUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strSelText;
	int index = m_List.GetCurSel();
	if (index != LB_ERR)
	{
		if (!m_bCheck)
		{
			m_List.GetText(index, strSelText);
			m_Edit1.Append(strSelText);
		}
		else
		{
			m_List.GetText(index, strSelText);
			m_Edit1.Append(strSelText);
			m_List.DeleteString(index);
		}
	}
	else
		AfxMessageBox(_T("����Ʈ �ڽ����� �������� �����ϼ���"));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonRigDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	if (!m_Edit2.IsEmpty())
	{
		if (!m_bCheck)
			m_Combo.AddString(m_Edit2);
		else
		{
			m_Combo.AddString(m_Edit2);
			m_Edit2.Empty();
		}
	}
	else
		AfxMessageBox(_T("����Ʈ ���ڿ� ���ڿ��� �����ϴ�."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonRigUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strComboText;
	int index = m_Combo.GetCurSel();
	if (index != LB_ERR)
	{
		if (!m_bCheck)
		{
			m_Combo.GetLBText(index, strComboText);
			m_Edit2.Append(strComboText);
		}
		else
		{
			m_Combo.GetLBText(index, strComboText);
			m_Edit2.Append(strComboText);
			m_Combo.DeleteString(index);
		}
	}
	else
		AfxMessageBox(_T("�޺��ڽ����� �������� �����ϼ���."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonAreRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString strListText;
	int index = m_List.GetCurSel();
	if (index != LB_ERR)
	{
		if (!m_bCheck)
		{
			m_List.GetText(index, strListText);
			m_Combo.AddString(strListText);
		}
		else
		{
			m_List.GetText(index, strListText);
			m_Combo.AddString(strListText);
			m_List.DeleteString(index);
		}
	}
	else
		AfxMessageBox(_T("����Ʈ �ڽ����� �������� �����ϼ���."));
	UpdateData(FALSE);
}


void CMFC_C4_1Dlg::OnClickedButtonAreLeft()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString StrComboText;
	int index = m_Combo.GetCurSel();
	if (index != LB_ERR)
	{
		if (!m_bCheck)
		{
			m_Combo.GetLBText(index, StrComboText);
			m_List.AddString(StrComboText);
		}
		else
		{
			m_Combo.GetLBText(index, StrComboText);
			m_List.AddString(StrComboText);
			m_Combo.DeleteString(index);
		}
	}
	else
		AfxMessageBox(_T("�޺��ڽ����� �������� �����ϼ���"));
	UpdateData(FALSE);
}

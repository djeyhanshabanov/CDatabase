// CDatabaseDlg.cpp : implementation file

#include "pch.h"
#include "framework.h"
#include "CDatabase.h"
#include "CDatabaseDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// Implementation
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


// CCDatabaseDlg dialog



CCDatabaseDlg::CCDatabaseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDATABASE_DIALOG, pParent)
	, m_Name(_T(""))
	, m_Surname(_T(""))
	, m_PhoneNum(_T(""))
	, m_EmailAddress(_T(""))
	, m_Id(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
	DDX_Text(pDX, IDC_EDIT_ID, m_Id);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_SURNAME, m_Surname);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUM, m_PhoneNum);
	DDX_Text(pDX, IDC_EDIT_EMAIL_ADDRESS, m_EmailAddress);
	DDX_Control(pDX, IDC_EDIT_ID, m_Id1);
	DDX_Control(pDX, IDC_EDIT_NAME, m_Name1);
	DDX_Control(pDX, IDC_EDIT_SURNAME, m_Surname1);
	DDX_Control(pDX, IDC_EDIT_PHONE_NUM, m_PhoneNum1);
	DDX_Control(pDX, IDC_EDIT_EMAIL_ADDRESS, m_EmailAddress1);
}

BEGIN_MESSAGE_MAP(CCDatabaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCDatabaseDlg::OnLvnItemchangedList)
	ON_EN_CHANGE(IDC_EDIT_ID, &CCDatabaseDlg::OnEnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CCDatabaseDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_SURNAME, &CCDatabaseDlg::OnEnChangeEditSurname)
	ON_EN_CHANGE(IDC_EDIT_PHONE_NUM, &CCDatabaseDlg::OnEnChangeEditPhoneNum)
	ON_EN_CHANGE(IDC_EDIT_EMAIL_ADDRESS, &CCDatabaseDlg::OnEnChangeEditEmailAddress)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CCDatabaseDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, &CCDatabaseDlg::OnBnClickedUpdateButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CCDatabaseDlg::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_DATA, &CCDatabaseDlg::OnBnClickedButtonDeleteAllData)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCDatabaseDlg::OnLvnItemchangedList)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCDatabaseDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_READ_DATA, &CCDatabaseDlg::OnBnClickedReadData)
END_MESSAGE_MAP()


// CCDatabaseDlg message handlers

BOOL CCDatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon




	return TRUE;               // return TRUE  unless you set the focus to a control
}


void CCDatabaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CCDatabaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CCDatabaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCDatabaseDlg::OnEnChangeEditId()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CCDatabaseDlg::OnEnChangeEditName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCDatabaseDlg::OnEnChangeEditSurname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCDatabaseDlg::OnEnChangeEditPhoneNum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCDatabaseDlg::OnEnChangeEditEmailAddress()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


////////////// ADDING DATA TO DATABASE //////////////
void CCDatabaseDlg::OnBnClickedAddButton()
{
	CString str1 = _T("");
	CString str2 = _T("");
	CString str3 = _T("");
	CString str4 = _T("");

	m_Name1.GetWindowTextW(str1);
	m_Surname1.GetWindowTextW(str2);
	m_PhoneNum1.GetWindowTextW(str3);
	m_EmailAddress1.GetWindowTextW(str4);

	CDatabase database;
	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	sMc.Format(_T("."));
	/////////////////////////////////////
	CString sFile = _T("J:\\userdb.mdb");
	/////////////////////////////////////
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	int iRec = 0;
	try
	{
			database.Open(NULL, false, false, sDsn);
			
			CRecordset recset(&database);
			
			SqlString.Format(L"INSERT INTO usertable(uname, usurname, uphonenum, uemailaddress) VALUES('%s', '%s', '%s', '%s')", str1,str2,str3,str4);
			
			database.ExecuteSQL(SqlString);

			SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

			SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

			ResetListControl();

			m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

			m_ListControl.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
			m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
			m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
			m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
			m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

			while (!recset.IsEOF()) {
				recset.GetFieldValue(_T("ID"), userid);
				recset.GetFieldValue(_T("uname"), username);
				recset.GetFieldValue(_T("usurname"), usersurname);
				recset.GetFieldValue(_T("uphonenum"), userphonenumber);
				recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

				iRec = m_ListControl.InsertItem(0, userid);
				m_ListControl.SetItemText(0, 1, username);
				m_ListControl.SetItemText(0, 2, usersurname);
				m_ListControl.SetItemText(0, 3, userphonenumber);
				m_ListControl.SetItemText(0, 4, useremailaddress);

				recset.MoveNext();
			}
			database.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
}


////////////// UPDATING DATA FROM DATABASE //////////////
void CCDatabaseDlg::OnBnClickedUpdateButton()
{
	CString str1 = _T("");
	CString str2 = _T("");
	CString str3 = _T("");
	CString str4 = _T("");
	CString str5 = _T("");

	m_Name1.GetWindowTextW(str1);
	m_Surname1.GetWindowTextW(str2);
	m_PhoneNum1.GetWindowTextW(str3);
	m_EmailAddress1.GetWindowTextW(str4);
	m_Id1.GetWindowTextW(str5);

	CDatabase database;
	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	sMc.Format(_T("."));
	/////////////////////////////////////
	CString sFile = _T("J:\\userdb.mdb");
	/////////////////////////////////////
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	int iRec = 0;
	try
	{
		database.Open(NULL, false, false, sDsn);

		CRecordset recset(&database);

		SqlString.Format(L"UPDATE usertable SET uname= '%s', usurname= '%s', uphonenum= '%s', uemailaddress= '%s' WHERE ID= %s", str1, str2, str3, str4, str5);
		
		database.ExecuteSQL(SqlString);

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		ResetListControl();

		m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		m_ListControl.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
		m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

		while (!recset.IsEOF()) {
			recset.GetFieldValue(_T("ID"), userid);
			recset.GetFieldValue(_T("uname"), username);
			recset.GetFieldValue(_T("usurname"), usersurname);
			recset.GetFieldValue(_T("uphonenum"), userphonenumber);
			recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

			iRec = m_ListControl.InsertItem(0, userid);
			m_ListControl.SetItemText(0, 1, username);
			m_ListControl.SetItemText(0, 2, usersurname);
			m_ListControl.SetItemText(0, 3, userphonenumber);
			m_ListControl.SetItemText(0, 4, useremailaddress);

			recset.MoveNext();
		}
		database.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
}

////////////// DELETING DATA FROM DATABASE //////////////
void CCDatabaseDlg::OnBnClickedDeleteButton()
{
	CString str5 = _T("");
	m_Id1.GetWindowTextW(str5);

	CDatabase database;
	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	sMc.Format(_T("."));
	/////////////////////////////////////
	CString sFile = _T("J:\\userdb.mdb");
	/////////////////////////////////////
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	int iRec = 0;
	try
	{
		database.Open(NULL, false, false, sDsn);

		CRecordset recset(&database);

		SqlString.Format(L"DELETE FROM usertable WHERE ID= %s" ,str5);

		database.ExecuteSQL(SqlString);

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		ResetListControl();

		m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		m_ListControl.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
		m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

		while (!recset.IsEOF()) {
			recset.GetFieldValue(_T("ID"), userid);
			recset.GetFieldValue(_T("uname"), username);
			recset.GetFieldValue(_T("usurname"), usersurname);
			recset.GetFieldValue(_T("uphonenum"), userphonenumber);
			recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

			iRec = m_ListControl.InsertItem(0, userid);
			m_ListControl.SetItemText(0, 1, username);
			m_ListControl.SetItemText(0, 2, usersurname);
			m_ListControl.SetItemText(0, 3, userphonenumber);
			m_ListControl.SetItemText(0, 4, useremailaddress);

			recset.MoveNext();
		}
		database.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
}

////////////// DELETING ALL DATA FROM DATABASE //////////////
void CCDatabaseDlg::OnBnClickedButtonDeleteAllData()
{
	CDatabase database;
	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	sMc.Format(_T("."));
	/////////////////////////////////////
	CString sFile = _T("J:\\userdb.mdb");
	/////////////////////////////////////
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	int iRec = 0;
	try
	{
		database.Open(NULL, false, false, sDsn);

		CRecordset recset(&database);

		SqlString.Format(L"DELETE FROM usertable");

		database.ExecuteSQL(SqlString);

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		ResetListControl();

		m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		m_ListControl.InsertColumn(0, L"ID", LVCFMT_LEFT, 111);
		m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

		while (!recset.IsEOF()) {
			recset.GetFieldValue(_T("ID"), userid);
			recset.GetFieldValue(_T("uname"), username);
			recset.GetFieldValue(_T("usurname"), usersurname);
			recset.GetFieldValue(_T("uphonenum"), userphonenumber);
			recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

			iRec = m_ListControl.InsertItem(0, userid);
			m_ListControl.SetItemText(0, 1, username);
			m_ListControl.SetItemText(0, 2, usersurname);
			m_ListControl.SetItemText(0, 3, userphonenumber);
			m_ListControl.SetItemText(0, 4, useremailaddress);

			recset.MoveNext();
		}
		database.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
}


////////////// LIST CONTROL //////////////
void CCDatabaseDlg::OnLvnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

////////////// LIST CONTROL //////////////
void CCDatabaseDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	int row = m_ListControl.GetSelectionMark();

	m_Id1.SetWindowText(m_ListControl.GetItemText(row, 0));
	m_Name1.SetWindowText(m_ListControl.GetItemText(row, 1));
	m_Surname1.SetWindowText(m_ListControl.GetItemText(row, 2));
	m_PhoneNum1.SetWindowText(m_ListControl.GetItemText(row, 3));
	m_EmailAddress1.SetWindowText(m_ListControl.GetItemText(row, 4));

	*pResult = 0;
}

////////////// RESET LIST CONTROL //////////////
void CCDatabaseDlg::ResetListControl()
{
	m_ListControl.DeleteAllItems();
	int iNbrOfColumns;
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ListControl.GetDlgItem(0);
	if (pHeader) {
		iNbrOfColumns = pHeader->GetItemCount();
	}
	for (int i = iNbrOfColumns; i >= 0; i--) {
		m_ListControl.DeleteColumn(i);
	}
}


void CCDatabaseDlg::OnBnClickedReadData()
{
	CDatabase database;
	CString SqlString;
	CString userid, username, usersurname, userphonenumber, useremailaddress;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn, sMc;
	sMc.Format(_T("."));
	/////////////////////////////////////
	CString sFile = _T("J:\\userdb.mdb");
	/////////////////////////////////////
	int iRec = 0;
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s;", sDriver, sFile);

	try
	{
		database.Open(NULL, false, false, sDsn);

		CRecordset recset(&database);

		SqlString = "SELECT ID, uname, usurname, uphonenum, uemailaddress " "FROM usertable";

		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		ResetListControl();

		m_ListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

		m_ListControl.InsertColumn(0, L"ID",  LVCFMT_LEFT, 111);  
		m_ListControl.InsertColumn(1, L"Name", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(2, L"Surname", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(3, L"Phone number", LVCFMT_CENTER, 200);
		m_ListControl.InsertColumn(4, L"E-mail address", LVCFMT_CENTER, 200);

		while (!recset.IsEOF()) {
			recset.GetFieldValue(_T("ID"), userid);
			recset.GetFieldValue(_T("uname"), username);
			recset.GetFieldValue(_T("usurname"), usersurname);
			recset.GetFieldValue(_T("uphonenum"), userphonenumber);
			recset.GetFieldValue(_T("uemailaddress"), useremailaddress);

			iRec = m_ListControl.InsertItem(0, userid);
			m_ListControl.SetItemText(0, 1, username);
			m_ListControl.SetItemText(0, 2, usersurname);
			m_ListControl.SetItemText(0, 3, userphonenumber);
			m_ListControl.SetItemText(0, 4, useremailaddress);

			recset.MoveNext();
		}
		database.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
	}
}

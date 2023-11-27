#include "SoftwareDefinitions.h"

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <winbase.h>
#include <tchar.h>
#include <strsafe.h>


#define BUFSIZE 1024

const wchar_t szWinName_C1[] = L"MyWin";										// ��� ������ ����



LRESULT CALLBACK WindowFunc_C1(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hinst;

void PrintError(LPCTSTR errDesc);


///// WinMain /////
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	//������� ���� C1
	HWND hwnd;																	// ���������� ���� C1
	MSG msg;																	// ��������� ��������� Windows C1
	WNDCLASSEX wcl;																// ���������, ������������ ����� ���� C1	


	//�������� ���� C3
	HWND hwnd_�3;																// ����������  ���� C3
	MSG msg_�3;																	// ��������� ��������� Windows C3
	WNDCLASSEX wcl_C3;															// ���������, ������������ ����� ���� C3	


	/////////////// ���� C1 ///////////////
	/* ����������� ������ ���� C1 */

	hinst = hThisInst;
	wcl.hInstance = hThisInst;													// ������ � ������ �����������
	wcl.lpszClassName = szWinName_C1;											// ��� ������ ����
	wcl.lpfnWndProc = WindowFunc_C1;											// ������� �������
	wcl.style = 0;																// ������������ ����� ���� �� ���������
	wcl.cbSize = sizeof(WNDCLASSEX);											// ��������� �������

	// WNDCLASSEX
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);								// ������� ������
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);									// ���������

	// ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);									// ����� �������
	wcl.lpszMenuName = NULL;													// ���� ���
	wcl.cbClsExtra = 0;															// �������������� ���������� ���
	wcl.cbWndExtra = 0;															// �������������� ���������� ���	
	wcl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 150, 40));				// ��������� ���� ����


	/* ����������� ������ ���� �1 */
	if (!RegisterClassEx(&wcl))
	{
		return 0;
	}

	/* ������ ���� ���� */
	hwnd = CreateWindow(
		szWinName_C1,															// ��� ������ ����
		L"API application Window C1",											// ���������
		WS_OVERLAPPEDWINDOW,													// ����� ���� - ����������
		// ������� � �������
		CW_USEDEFAULT,															// ���������� X - �������� Windows
		CW_USEDEFAULT,															// ���������� Y - �������� Windows
		CW_USEDEFAULT,															// ������ - �������� Windows
		CW_USEDEFAULT,															// ������ - �������� Windows
		HWND_DESKTOP,															// ��� ������������� ����
		NULL,																	// ��� ����
		hThisInst,																// ������ � ������ ����������� ���������
		NULL																	// �������������� ��������� �����������
	);

	/* ����� ���� C1 */
	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	/* �������� ����� ��������� ��������� C1 */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);													// ��������� ������������� ����������
		DispatchMessage(&msg);													// ������� ���������� Windows
	}
	return msg.wParam;









}



/* ������� ������� ��������� ���������, ���������� �� ������� ���������. C1 */
LRESULT CALLBACK WindowFunc_C1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;

	//�������� ���� C2
	HWND hwnd_�2;																// ����������  ���� C2
	MSG msg_�2;																	// ��������� ��������� Windows C2
	WNDCLASSEX wcl_�2;															// ���������, ������������ ����� ���� C2	



	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hTempFile = INVALID_HANDLE_VALUE;

	BOOL fSuccess = FALSE;
	DWORD dwRetVal = 0;
	UINT uRetVal = 0;

	DWORD dwBytesRead = 0;
	BOOL bIsBin = FALSE;

	TCHAR szTempFileName[MAX_PATH];
	TCHAR lpTempPathBuffer[MAX_PATH];
	char  chBuffer[BUFSIZE];
	wchar_t  chBuffer_2[BUFSIZE];
	char  chBuffer_3[BUFSIZE];
	LPCTSTR errMsg;


	///// LAB 4 
	const wchar_t lpFileName[] = L"D:\\New\\MYFILE_2.txt";							// ��� ����� 
	const wchar_t lpFileName_2[] = L"D:\\New\\MyFile_2.txt";						// ��� ����� 
	WCHAR lpFileName_3[MAX_PATH] = L"";													// ��� ����� 
	const wchar_t lpFileName_4[MAX_PATH] = L"D:\\New\\MyFile_3.txt";				// ��� ����� 
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;							// �������� ������ ������ � ������: ������ � ������
	DWORD dwShareMode = 0;															// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
	LPSECURITY_ATTRIBUTES  lpSecurityAttributes = NULL;								// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
	DWORD dwCreationDisposition = OPEN_EXISTING;									// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;								// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������, ��� �� ����� �������������� ��� ����������� ������ �������)
	HANDLE fileTemplate = NULL;														// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������
	HANDLE newFile;																	// ������ �����
	HANDLE newFile_2;																// ������ �����
	HANDLE newFile_3;																// ������ �����
	OVERLAPPED oOverlap_1;															// ��������� ��� ������������ ������
	//OVERLAPPED oOverlap_2;														// ��������� ��� ������������ ������


	oOverlap_1.Offset = 0;															// ����� ����� � ������ �������, � ������� ����������� ������ �����-������, ��� ������� �������������.
	oOverlap_1.OffsetHigh = 0;														// ������������������� ����� ������� �����, � ������� ����������� ������ �����-������, ��� ������� �������������.
	oOverlap_1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);						// ���������� �������, ��� �������� ������� ��������� ���������� ��������� ����� ���������� ��������. 
																						// ������������ ������ ���������������� ���� ������� �� ���� ��� ����������� ����������� ������� � ������� ������� CreateEvent ����� ��������� ���� ��������� � ����� ��������������� �������. 
																						// ����� ��� ������� ����� ������������ ��� ������������� ������������� �������� �����-������ ��� ����������.

	//oOverlap_2.Offset = 0;
	//oOverlap_2.OffsetHigh = 0;
	//oOverlap_2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	LPDWORD lpNumberOfBytesRead = 0;

	///// ������ � ����
	char DataBuffer[] = "This is some test data to write to the file";				// �����, ������� ����� ������� � ����. ��� ������ - ������������ ������ ��������
	const wchar_t str[] = L"This is some test data to write to the file";			// �����, ������� ����� ������� � ����. ��� ������ - ����������� ������ �������� (������������)
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);								// ���������� �������� (����), ������� ����������� �������� � ����. ������� ��������� ������ ������ - ���������� �������� � ������
	DWORD dwBytesWritten = 0;														// ������� �������� (����), ���������� (����������) � ����
	BOOL bErrorFlag = FALSE;														// ���� ��������� ������ - ��������� ��� ������������ ������� ���������� �������




	///// �������� �����
	OPENFILENAMEA ofn;																// ���������, ����������� ��� ������������ ���������� �������� �����

	char szFile[1024];																// ����� - ������ ������ ��������, � ������� ����� ��������� ����� ������ � �������� �������� ������ / ������
	char fileName_bin[MAX_PATH] = "";												// ������ �������� ��� �������� ����� �����

	ZeroMemory(&ofn, sizeof(ofn));													// ����������� ZeroMemory ��� ������� ����� ������ �� ����� ����� ����������������. ��������� ���� ������ ������
	ofn.lStructSize = sizeof(OPENFILENAME);											// ����� ��������� � ������. ����������� sizeof (OPENFILENAME) ��� ����� ���������
	ofn.hwndOwner = NULL;															// ���������� ����, �������� ����������� ���������� ����. ��� ����� ���� ����� ���������� ���������� ���� ��� �������� NULL, ���� � ����������� ���� ��� ���������
	ofn.lpstrFilter = "MyFile_3\0*.*\0Text\0*.TXT\0*.txt\0";						// �����, ���������� ���� ����� �������, ����������� ��������� NULL. ��������� ������ � ������ ������ ������������� ����� ��������� NULL
	ofn.lpstrCustomFilter = NULL;													// ����������� �����, ���������� ���� ����� �������, ����������� ��������� NULL, ��� ���������� ������� �������, ���������� �������������. ���� ���� ������� ����� �������� NULL, ���������� ���� �� ��������� ���������������� ������� ��������
	ofn.nMaxCustFilter = NULL;														// ������ (� ��������) ������, ������������� lpstrCustomFilter. ����� ����� ������ ������ ���������� �� ����� 40 ��������. ���� ������� ������������, ���� lpstrCustomFilter ����� �������� NULL ��� ��������� �� ������ NULL 
	ofn.nFilterIndex = 1;															// ������ �������� ���������� ������� � �������� ���������� ���� ������
	ofn.lpstrFile = (LPSTR)lpFileName_3;											// ��� �����, ������������ ��� ������������� �������� ���������� ���������� ����� �����. ���� ������������� �� ���������, ������ ������ ����� ������ ������ ����� �������� NULL 
	ofn.nMaxFile = MAX_PATH;														// ������ (� ��������) ������, �� ������� ��������� lpstrFile. ����� ������ ���� ���������� ������� ��� �������� ������ ���� � ����� ����� ��� �����, ������� ����������� ������ NULL 
	ofn.lpstrFileTitle = NULL;														// ��� � ���������� ���������� ����� (��� �������� � ����). ���� ������� ����� ����� �������� NULL
	ofn.lpstrInitialDir = NULL;														// �������� �������. �������� ������ ���������� �������� ������� �� ������ ��������
	ofn.lpstrTitle = NULL;															// ������, ���������� � ��������� ����������� ����. ���� ���� ������� ����� �������� NULL, ������� ���������� ��������� �� ��������� (�� ���� ��������� ��� ��� �������)
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;								// ����� ������� ������, ������� ����� ������������ ��� ������������� ����������� ���� 
	ofn.nFileOffset = 9;															// ������������� �� ���� �������� � �������� �� ������ ���� �� ����� ����� � ������, �� ������� ��������� lpstrFile
	ofn.nFileExtension = 18;														// ������������� �� ���� �������� � �������� �� ������ ���� �� ���������� ����� ����� � ������, �� ������� ��������� lpstrFile
	ofn.lpstrDefExt = NULL;															// ���������� �� ���������. GetOpenFileName � GetSaveFileName ��������� ��� ���������� � ����� �����, ���� ������������ �� ������� ������ ����������.���� ���� ���� ����� �������� NULL � ������������ �� ������� ������ ����������, ���������� �� �����������
	ofn.FlagsEx = NULL;																// ����� ������� ������, ������� ����� ������������ ��� ������������� ����������� ����. � ��������� ����� ���� ������� ����� ���� ����� ���� ��� ���������� �����





	switch (message)
	{
	case WM_KEYDOWN:															// ������� �������


		/////////////////////// ���������� ����� ///////////////////////

		if (wParam == 0x4F)														// 0x4F = key "O"  - Open file
		{
			//��������� ���� � ����� ��������� ���������� ��������� (�����������)
			newFile = CreateFile(
				L"D:\\NEW\\MYFILE_2.TXT",								// ��� �����
				GENERIC_READ,											// �������� ������ ������ � ������: ������ ������
				NULL,													// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
				NULL,													// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
				OPEN_EXISTING,											// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
				FILE_ATTRIBUTE_NORMAL,									// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
				NULL);													// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������


			if (newFile == INVALID_HANDLE_VALUE)
			{
				DWORD erroCode = GetLastError();								// �������, ������� ���������� ��������� ��������� �� ������. � ������ ������� ������������ ��� ��������� ������ ������, ��-�� ������� �� ������� ��������� �������� CreateFile()
				return (0);
			}
			else
			{

				CloseHandle(newFile);											// �������, ����������� ������� �������� ���� (����������� ���������� �������)
			}



		}
		else if (wParam == 0x52)												// 0x52 = key "R"  - Read file
		{
			newFile = CreateFile(
				lpFileName,												// ��� �����
				dwDesiredAccess,										// �������� ������ ������ � ������: ������ ������
				dwShareMode,											// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
				lpSecurityAttributes,									// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
				dwCreationDisposition,									// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
				dwFlagsAndAttributes,									// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
				fileTemplate);											// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������



			if (newFile != INVALID_HANDLE_VALUE)
			{
				//������ �������� ����
				bErrorFlag = ReadFile(
					newFile,										// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_READ
					chBuffer,										// ��������� �� �����, ������� ��������� ����������� ������ �� �����
					1023,											// ����� ������, ������� �������� �� �����: chBuffer - 1
					lpNumberOfBytesRead,							// ��������� �� ����������, ������� �������� ����� ����������� ������
					NULL);											// ��������� �� ��������� OVERLAPPED. ��� ��������� ��������� �����, ���� �������� hFile ���������� � ��������� FILE_FLAG_OVERLAPPED

				if (bErrorFlag)
				{
					// ����� �������� ���, ������� ��� ��������� ������� �������� ���� ����� ��������� �����-���� ������, ��������� �������������
				}

				CloseHandle(newFile);											// �������, ����������� ������� �������� ���� (����������� ���������� �������)
			}
			else
			{
				return (0);
			}
		}
		else if (wParam == 0x57)												// 0x57 = key "W"  - Write file
		{

			newFile = CreateFile(
				lpFileName,														// ��� �����
				dwDesiredAccess,												// �������� ������ ������ � ������: ������ ������
				dwShareMode,													// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
				lpSecurityAttributes,											// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
				dwCreationDisposition,											// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
				dwFlagsAndAttributes,											// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
				fileTemplate);													// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������

			if (newFile != INVALID_HANDLE_VALUE)
			{
				bErrorFlag = WriteFile(
					newFile,													// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_WRITE
					DataBuffer,													// ��������� �� �����, ���������� ������ ��� ������ � ����
					dwBytesToWrite,												// ����� ������, ������������ � ���� ��� ����������
					&dwBytesWritten,											// ��������� �� ����������, ������� �������� ���������� ������, ���������� ��� ������������� ����������� ��������� hFile (� ����� ������ - newFile)
					NULL);														// ��������� �� ��������� OVERLAPPED ���������, ���� �������� (� ����� ������ - newFile) ��� ������ � FILE_FLAG_OVERLAPPED
				CloseHandle(newFile);											// �������, ����������� ������� �������� ���� (����������� ���������� �������)
			}

		}


		/////////////////////// ����������� ����� ///////////////////////
		else if (wParam == 0x41)												// 0x57 = key "A"  - Write file
		{

			newFile = CreateFile(
				lpFileName,												// ��� �����
				dwDesiredAccess,										// �������� ������ ������ � ������: ������ ������
				dwShareMode,											// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
				lpSecurityAttributes,									// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
				dwCreationDisposition,									// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
				dwFlagsAndAttributes,									// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
				fileTemplate);											// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������



			if (newFile != INVALID_HANDLE_VALUE)
			{
				bErrorFlag = ReadFile(
					newFile,										// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_READ
					chBuffer,										// ��������� �� �����, ������� ��������� ����������� ������ �� �����
					1023,											// ����� ������, ������� �������� �� �����: chBuffer - 1
					lpNumberOfBytesRead,							// ��������� �� ����������, ������� �������� ����� ����������� ������
					&oOverlap_1);									// ��������� �� ��������� OVERLAPPED. ��� ��������� ��������� �����, ���� �������� hFile (newFile) ���������� � ��������� FILE_FLAG_OVERLAPPED
				CloseHandle(newFile);											// �������, ����������� ������� �������� ���� (����������� ���������� �������)
			}

		}



		/////////////////////// �������� ����� ///////////////////////

		if (wParam == 0x42)														// "B"
		{
			GetOpenFileNameA(&ofn);											// �������, ����������� ������� ���� �� ���������� �������� � ����� ���� ������ � �������

			if (GetOpenFileNameA(&ofn) == true)									// �������, ����������� ���������(�������) ���� � ��������� �������� � ����� ���� ������ � �������
			{
				//��������� ���� MyFile_3.txt ��� ����������� ������ ������ � ���� � ��������� �������
				newFile_3 = CreateFile(
					lpFileName_4,									// ��� �����
					dwDesiredAccess,								// �������� ������ ������ � ������: ������ ������
					dwShareMode,									// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
					lpSecurityAttributes,							// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
					dwCreationDisposition,							// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
					dwFlagsAndAttributes,							// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
					fileTemplate);									// ���������� ���������� ����� ������� � ������ ������� GENERIC_READ. ���� ������� ������������� �������� ����� � ����������� �������� ��� ������������ �����: NULL - ������ �����������


				if (bIsBin)														// �������� - �������� �� ���� ��������
				{
					bErrorFlag = WriteFile(
						newFile_3,									// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_WRITE
						DataBuffer,										// ��������� �� �����, ���������� ������ ��� ������ � ����
						dwBytesToWrite,								// ����� ������, ������������ � ���� ��� ����������
						&dwBytesWritten,							// ��������� �� ����������, ������� �������� ���������� ������, ���������� ��� ������������� ����������� ��������� hFile (� ����� ������ - newFile)
						0);											// ��������� �� ��������� OVERLAPPED ���������, ���� �������� (� ����� ������ - newFile) ��� ������ � FILE_FLAG_OVERLAPPED
					CloseHandle(newFile_3);
				}
				else
				{
					int i = 13;
					swprintf_s(chBuffer_2, 1024, L"%d", i);
					WriteFile(newFile_3, &str, wcslen(str) * 2, &dwBytesWritten, 0);
					CloseHandle(newFile_3);
				}






				ZeroMemory(&chBuffer_3, sizeof(chBuffer_3));
				//��������� ���� MyFile_3.txt ��� ������������ �������������� ������ �� ���� � ����������������� ���
				newFile_3 = CreateFile(
					lpFileName_4,										// ��� �����
					dwDesiredAccess,									// �������� ������ ������ � ������: ������ ������
					dwShareMode,										// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
					lpSecurityAttributes,								// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
					dwCreationDisposition,								// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
					dwFlagsAndAttributes,								// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
					fileTemplate);
				// ���������� ������ �����
				int iLength = GetFileSize(newFile_3, NULL);



				SetFilePointer(newFile_3, 0, NULL, FILE_BEGIN);			// ������������� ��������� ����� �� ������ �����

				ReadFile(												// ��������� �� ���� ������
					newFile_3,										// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_READ
					chBuffer,										// ��������� �� �����, ������� ��������� ����������� ������ �� �����
					1023,											// ����� ������, ������� �������� �� �����: chBuffer - 1
					lpNumberOfBytesRead,							// ��������� �� ����������, ������� �������� ����� ����������� ������
					NULL);

				int i = 0;
				int k = 0;
				// ����������� ������ � ������� � ����������������� ����
				while (i < iLength)
				{
					k += sprintf_s(chBuffer_3 + k, 1023 - k, "%x ", (unsigned char)chBuffer[i]);
					i++;
				}
				CloseHandle(newFile_3);

				//���������� � ���� MyFile_2.txt ����������������� ���
				newFile_2 = CreateFile(
					lpFileName_2,										// ��� �����
					dwDesiredAccess,									// �������� ������ ������ � ������: ������ ������
					dwShareMode,										// ����� ������ ������� � �����: "0"- ����������� ����� ������ � ����� 
					lpSecurityAttributes,								// ��������� SECURITY_ATTRIBUTES: �������� NULL - ���������� �� ����� ������������� �������� ��������� ���������� (�������� �� ���������)
					dwCreationDisposition,								// ��������, ����������� � ������ ��� �����������, ������� ���������� ��� �� ����������: OPEN_EXISTING - ��������� ����, ������ ���� �� ����������
					dwFlagsAndAttributes,								// � ����������� �� ���������� �������� ���������� �������� �����: FILE_ATTRIBUTE_NORMAL - � ����� �� ������ ������ �������� (�������� �� ���������)
					fileTemplate);

				bErrorFlag = WriteFile(
					newFile_2,											// ���������� �����, ������� ��������. ���������� ����� ������ ����, ������ � ������ ������� GENERIC_WRITE
					&chBuffer_3,										// ��������� �� �����, ���������� ������ ��� ������ � ����
					(DWORD)strlen(chBuffer_3),							// ����� ������, ������������ � ���� ��� ����������
					&dwBytesWritten,									// ��������� �� ����������, ������� �������� ���������� ������, ���������� ��� ������������� ����������� ��������� hFile (� ����� ������ - newFile)
					0);													// ��������� �� ��������� OVERLAPPED ���������, ���� �������� (� ����� ������ - newFile) ��� ������ � FILE_FLAG_OVERLAPPED
				CloseHandle(newFile_2);
			}
		}
		break;
	case WM_CHAR:																// ���������� ��������� �� ����������

		break;
	case WM_RBUTTONDOWN:														// ���������� ������� ������ ������ ����

		break;
	case WM_DESTROY:															// ���������� ���������
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0L;
}

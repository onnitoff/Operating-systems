#include "SoftwareDefinitions.h"

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <winbase.h>
#include <tchar.h>
#include <strsafe.h>


#define BUFSIZE 1024

const wchar_t szWinName_C1[] = L"MyWin";										// Имя класса окна



LRESULT CALLBACK WindowFunc_C1(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hinst;

void PrintError(LPCTSTR errDesc);


///// WinMain /////
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	//Главное окни C1
	HWND hwnd;																	// Дескриптор окна C1
	MSG msg;																	// Структура сообщения Windows C1
	WNDCLASSEX wcl;																// Структура, определяющая класс окна C1	


	//Дочернее окно C3
	HWND hwnd_С3;																// Дескриптор  окна C3
	MSG msg_С3;																	// Структура сообщения Windows C3
	WNDCLASSEX wcl_C3;															// Структура, определяющая класс окна C3	


	/////////////// Окно C1 ///////////////
	/* Определение класса окна C1 */

	hinst = hThisInst;
	wcl.hInstance = hThisInst;													// Работа с данным экземпляром
	wcl.lpszClassName = szWinName_C1;											// Имя класса окна
	wcl.lpfnWndProc = WindowFunc_C1;											// Оконная функция
	wcl.style = 0;																// Использовать стиль окна по умолчанию
	wcl.cbSize = sizeof(WNDCLASSEX);											// Установка размера

	// WNDCLASSEX
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);								// Большие иконки
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);									// Маленькие

	// иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);									// Стиль курсора
	wcl.lpszMenuName = NULL;													// Меню нет
	wcl.cbClsExtra = 0;															// Дополнительной информации нет
	wcl.cbWndExtra = 0;															// Дополнительной информации нет	
	wcl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 150, 40));				// Установка фона окна


	/* Регистрация класса окна С1 */
	if (!RegisterClassEx(&wcl))
	{
		return 0;
	}

	/* Создаём само окно */
	hwnd = CreateWindow(
		szWinName_C1,															// Имя класса окна
		L"API application Window C1",											// Заголовок
		WS_OVERLAPPEDWINDOW,													// Стиль окна - нормальный
		// Размеры и позиции
		CW_USEDEFAULT,															// Координата X - выбирает Windows
		CW_USEDEFAULT,															// Координата Y - выбирает Windows
		CW_USEDEFAULT,															// Ширина - выбирает Windows
		CW_USEDEFAULT,															// Высота - выбирает Windows
		HWND_DESKTOP,															// Нет родительского окна
		NULL,																	// Нет меню
		hThisInst,																// Работа с данным экземпляром программы
		NULL																	// Дополнительные аргументы отсутствуют
	);

	/* Вывод окна C1 */
	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	/* Создание цикла обработки сообщений C1 */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);													// Разрешить использование клавиатуры
		DispatchMessage(&msg);													// Вернуть управление Windows
	}
	return msg.wParam;









}



/* Оконная функция обработки сообщений, полученных из очереди сообщений. C1 */
LRESULT CALLBACK WindowFunc_C1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;

	//Дочернее окно C2
	HWND hwnd_С2;																// Дескриптор  окна C2
	MSG msg_С2;																	// Структура сообщения Windows C2
	WNDCLASSEX wcl_С2;															// Структура, определяющая класс окна C2	



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
	const wchar_t lpFileName[] = L"D:\\New\\MYFILE_2.txt";							// Имя файла 
	const wchar_t lpFileName_2[] = L"D:\\New\\MyFile_2.txt";						// Имя файла 
	WCHAR lpFileName_3[MAX_PATH] = L"";													// Имя файла 
	const wchar_t lpFileName_4[MAX_PATH] = L"D:\\New\\MyFile_3.txt";				// Имя файла 
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;							// Параметр режима работы с файлом: чтение и запись
	DWORD dwShareMode = 0;															// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
	LPSECURITY_ATTRIBUTES  lpSecurityAttributes = NULL;								// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
	DWORD dwCreationDisposition = OPEN_EXISTING;									// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;								// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию, так же может использоваться для синхронного метода доступа)
	HANDLE fileTemplate = NULL;														// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует
	HANDLE newFile;																	// Объект файла
	HANDLE newFile_2;																// Объект файла
	HANDLE newFile_3;																// Объект файла
	OVERLAPPED oOverlap_1;															// Структура для асинхронного метода
	//OVERLAPPED oOverlap_2;														// Структура для асинхронного метода


	oOverlap_1.Offset = 0;															// Часть файла в нижнем порядке, с которой запускается запрос ввода-вывода, как указано пользователем.
	oOverlap_1.OffsetHigh = 0;														// Высокоупорядоченная часть позиции файла, с которой запускается запрос ввода-вывода, как указано пользователем.
	oOverlap_1.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);						// Дескриптор события, для которого система установит сигнальное состояние после завершения операции. 
																						// Пользователь должен инициализировать этот элемент до нуля или допустимого дескриптора события с помощью функции CreateEvent перед передачей этой структуры в любые перекрывающиеся функции. 
																						// Затем это событие можно использовать для синхронизации одновременных запросов ввода-вывода для устройства.

	//oOverlap_2.Offset = 0;
	//oOverlap_2.OffsetHigh = 0;
	//oOverlap_2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	LPDWORD lpNumberOfBytesRead = 0;

	///// ЗАПИСЬ В ФАЙЛ
	char DataBuffer[] = "This is some test data to write to the file";				// Текст, который будет записан в файл. Тип данных - динамический массив символов
	const wchar_t str[] = L"This is some test data to write to the file";			// Текст, который будет записан в файл. Тип данных - статический массив символов (неизменяемый)
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);								// Количество символов (байт), которые потребуется записать в файл. Функция получения длинны строки - количества символов в строке
	DWORD dwBytesWritten = 0;														// Счетчик символов (байт), переданных (записанных) в файл
	BOOL bErrorFlag = FALSE;														// Флаг состояния ошибки - необходим для отслеживания статуса выполнения функции




	///// БИНАРНЫЕ ФАЙЛЫ
	OPENFILENAMEA ofn;																// Структура, необходимая для формирования параметров будущего файла

	char szFile[1024];																// Буфер - пустой массив символов, в который будут выгружены байты данных в прцоессе операции чтения / записи
	char fileName_bin[MAX_PATH] = "";												// Массив символов для хранения имени файла

	ZeroMemory(&ofn, sizeof(ofn));													// Используйте ZeroMemory для очистки блока памяти на любом языке программирования. Заполняет блок памяти нулями
	ofn.lStructSize = sizeof(OPENFILENAME);											// Длина структуры в байтах. Используйте sizeof (OPENFILENAME) для этого параметра
	ofn.hwndOwner = NULL;															// Дескриптор окна, которому принадлежит диалоговое окно. Это может быть любой допустимый дескриптор окна или значение NULL, если у диалогового окна нет владельца
	ofn.lpstrFilter = "MyFile_3\0*.*\0Text\0*.TXT\0*.txt\0";						// Буфер, содержащий пары строк фильтра, завершаемых значением NULL. Последняя строка в буфере должна заканчиваться двумя символами NULL
	ofn.lpstrCustomFilter = NULL;													// Статический буфер, содержащий пару строк фильтра, завершаемых значением NULL, для сохранения шаблона фильтра, выбранного пользователем. Если этот элемент имеет значение NULL, диалоговое окно не сохраняет пользовательские шаблоны фильтров
	ofn.nMaxCustFilter = NULL;														// Размер (в символах) буфера, определяемого lpstrCustomFilter. Длина этого буфера должна составлять не менее 40 символов. Этот элемент игнорируется, если lpstrCustomFilter имеет значение NULL или указывает на строку NULL 
	ofn.nFilterIndex = 1;															// Индекс текущего выбранного фильтра в элементе управления Типы файлов
	ofn.lpstrFile = (LPSTR)lpFileName_3;											// Имя файла, используемое для инициализации элемента управления изменением имени файла. Если инициализация не требуется, первый символ этого буфера должен иметь значение NULL 
	ofn.nMaxFile = MAX_PATH;														// Размер (в символах) буфера, на который указывает lpstrFile. Буфер должен быть достаточно большим для хранения строки пути и имени файла или строк, включая завершающий символ NULL 
	ofn.lpstrFileTitle = NULL;														// Имя и расширение выбранного файла (без сведений о пути). Этот элемент может иметь значение NULL
	ofn.lpstrInitialDir = NULL;														// Исходный каталог. Алгоритм выбора начального каталога зависит от разных платформ
	ofn.lpstrTitle = NULL;															// Строка, помещаемая в заголовок диалогового окна. Если этот элемент имеет значение NULL, система использует заголовок по умолчанию (то есть сохранить как или открыть)
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;								// Набор битовых флагов, который можно использовать для инициализации диалогового окна 
	ofn.nFileOffset = 9;															// Отсчитываемое от нуля смещение в символах от начала пути до имени файла в строке, на которую указывает lpstrFile
	ofn.nFileExtension = 18;														// Отсчитываемое от нуля смещение в символах от начала пути до расширения имени файла в строке, на которую указывает lpstrFile
	ofn.lpstrDefExt = NULL;															// Расширение по умолчанию. GetOpenFileName и GetSaveFileName добавляют это расширение к имени файла, если пользователю не удается ввести расширение.Если этот член имеет значение NULL и пользователю не удается ввести расширение, расширение не добавляется
	ofn.FlagsEx = NULL;																// Набор битовых флагов, который можно использовать для инициализации диалогового окна. В настоящее время этот элемент может быть равен нулю или следующему флагу





	switch (message)
	{
	case WM_KEYDOWN:															// Нажатие клавиши


		/////////////////////// СИНХРОННЫЙ МЕТОД ///////////////////////

		if (wParam == 0x4F)														// 0x4F = key "O"  - Open file
		{
			//Открываем файл с явным указанием параметров структуры (дескриптора)
			newFile = CreateFile(
				L"D:\\NEW\\MYFILE_2.TXT",								// Имя файла
				GENERIC_READ,											// Параметр режима работы с файлом: только чтение
				NULL,													// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
				NULL,													// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
				OPEN_EXISTING,											// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
				FILE_ATTRIBUTE_NORMAL,									// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
				NULL);													// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует


			if (newFile == INVALID_HANDLE_VALUE)
			{
				DWORD erroCode = GetLastError();								// Функция, которая возвращает последнее сообщение об ошибке. В данном примере используется для получения номера ошибки, из-за которой не удалось выполнить функцияю CreateFile()
				return (0);
			}
			else
			{

				CloseHandle(newFile);											// Функция, позволяющая закрыть открытый файл (освобождает выделенные ресурсы)
			}



		}
		else if (wParam == 0x52)												// 0x52 = key "R"  - Read file
		{
			newFile = CreateFile(
				lpFileName,												// Имя файла
				dwDesiredAccess,										// Параметр режима работы с файлом: только чтение
				dwShareMode,											// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
				lpSecurityAttributes,									// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
				dwCreationDisposition,									// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
				dwFlagsAndAttributes,									// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
				fileTemplate);											// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует



			if (newFile != INVALID_HANDLE_VALUE)
			{
				//ЧИТАЕМ ОТКРЫТЫЙ ФАЙЛ
				bErrorFlag = ReadFile(
					newFile,										// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_READ
					chBuffer,										// Указатель на буфер, который принимает прочитанные данные из файла
					1023,											// Число байтов, которые читаются из файла: chBuffer - 1
					lpNumberOfBytesRead,							// Указатель на переменную, которая получает число прочитанных байтов
					NULL);											// Указатель на структуру OVERLAPPED. Эта структура требуется тогда, если параметр hFile создавался с атрибутом FILE_FLAG_OVERLAPPED

				if (bErrorFlag)
				{
					// Здесь помещаем код, который при неудачной попытке прочесть файл будет выполнять какую-либо логику, описанную разработчиком
				}

				CloseHandle(newFile);											// Функция, позволяющая закрыть открытый файл (освобождает выделенные ресурсы)
			}
			else
			{
				return (0);
			}
		}
		else if (wParam == 0x57)												// 0x57 = key "W"  - Write file
		{

			newFile = CreateFile(
				lpFileName,														// Имя файла
				dwDesiredAccess,												// Параметр режима работы с файлом: только чтение
				dwShareMode,													// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
				lpSecurityAttributes,											// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
				dwCreationDisposition,											// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
				dwFlagsAndAttributes,											// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
				fileTemplate);													// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует

			if (newFile != INVALID_HANDLE_VALUE)
			{
				bErrorFlag = WriteFile(
					newFile,													// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_WRITE
					DataBuffer,													// Указатель на буфер, содержащий данные для записи в файл
					dwBytesToWrite,												// Число байтов, записываемых в файл или устройство
					&dwBytesWritten,											// Указатель на переменную, которая получает количество байтов, записанных при использовании синхронного параметра hFile (в нашем случае - newFile)
					NULL);														// Указатель на структуру OVERLAPPED требуется, если параметр (в нашем случае - newFile) был открыт с FILE_FLAG_OVERLAPPED
				CloseHandle(newFile);											// Функция, позволяющая закрыть открытый файл (освобождает выделенные ресурсы)
			}

		}


		/////////////////////// АСИНХРОННЫЙ МЕТОД ///////////////////////
		else if (wParam == 0x41)												// 0x57 = key "A"  - Write file
		{

			newFile = CreateFile(
				lpFileName,												// Имя файла
				dwDesiredAccess,										// Параметр режима работы с файлом: только чтение
				dwShareMode,											// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
				lpSecurityAttributes,									// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
				dwCreationDisposition,									// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
				dwFlagsAndAttributes,									// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
				fileTemplate);											// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует



			if (newFile != INVALID_HANDLE_VALUE)
			{
				bErrorFlag = ReadFile(
					newFile,										// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_READ
					chBuffer,										// Указатель на буфер, который принимает прочитанные данные из файла
					1023,											// Число байтов, которые читаются из файла: chBuffer - 1
					lpNumberOfBytesRead,							// Указатель на переменную, которая получает число прочитанных байтов
					&oOverlap_1);									// Указатель на структуру OVERLAPPED. Эта структура требуется тогда, если параметр hFile (newFile) создавался с атрибутом FILE_FLAG_OVERLAPPED
				CloseHandle(newFile);											// Функция, позволяющая закрыть открытый файл (освобождает выделенные ресурсы)
			}

		}



		/////////////////////// БИНАРНЫЕ ФАЙЛЫ ///////////////////////

		if (wParam == 0x42)														// "B"
		{
			GetOpenFileNameA(&ofn);											// Функция, позволяющая выбрать файл из выбранного каталога в общем окне работы с файлами

			if (GetOpenFileNameA(&ofn) == true)									// Функция, позволяющая сохранить(создать) файл в выбранном каталоге в общем окне работы с файлами
			{
				//Открываем файл MyFile_3.txt для последующей записи текста в него в текстовом формате
				newFile_3 = CreateFile(
					lpFileName_4,									// Имя файла
					dwDesiredAccess,								// Параметр режима работы с файлом: только чтение
					dwShareMode,									// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
					lpSecurityAttributes,							// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
					dwCreationDisposition,							// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
					dwFlagsAndAttributes,							// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
					fileTemplate);									// Допустимый дескриптор файла шаблона с правом доступа GENERIC_READ. Файл шаблона предоставляет атрибуты файла и расширенные атрибуты для создаваемого файла: NULL - шаблон отсутствует


				if (bIsBin)														// Проверка - является ли файл бинарным
				{
					bErrorFlag = WriteFile(
						newFile_3,									// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_WRITE
						DataBuffer,										// Указатель на буфер, содержащий данные для записи в файл
						dwBytesToWrite,								// Число байтов, записываемых в файл или устройство
						&dwBytesWritten,							// Указатель на переменную, которая получает количество байтов, записанных при использовании синхронного параметра hFile (в нашем случае - newFile)
						0);											// Указатель на структуру OVERLAPPED требуется, если параметр (в нашем случае - newFile) был открыт с FILE_FLAG_OVERLAPPED
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
				//Открываем файл MyFile_3.txt для последующего преобразования текста из него в шестнадцатиричный код
				newFile_3 = CreateFile(
					lpFileName_4,										// Имя файла
					dwDesiredAccess,									// Параметр режима работы с файлом: только чтение
					dwShareMode,										// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
					lpSecurityAttributes,								// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
					dwCreationDisposition,								// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
					dwFlagsAndAttributes,								// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
					fileTemplate);
				// определяем длинну файла
				int iLength = GetFileSize(newFile_3, NULL);



				SetFilePointer(newFile_3, 0, NULL, FILE_BEGIN);			// устанавливаем указатель файла на начало файла

				ReadFile(												// считываем из него данные
					newFile_3,										// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_READ
					chBuffer,										// Указатель на буфер, который принимает прочитанные данные из файла
					1023,											// Число байтов, которые читаются из файла: chBuffer - 1
					lpNumberOfBytesRead,							// Указатель на переменную, которая получает число прочитанных байтов
					NULL);

				int i = 0;
				int k = 0;
				// форматируем строку и выводим в шестнадцатеричном виде
				while (i < iLength)
				{
					k += sprintf_s(chBuffer_3 + k, 1023 - k, "%x ", (unsigned char)chBuffer[i]);
					i++;
				}
				CloseHandle(newFile_3);

				//Записываем в файл MyFile_2.txt шестнадцатиричный код
				newFile_2 = CreateFile(
					lpFileName_2,										// Имя файла
					dwDesiredAccess,									// Параметр режима работы с файлом: только чтение
					dwShareMode,										// Режим общего доступа к файлу: "0"- отсутствует общий доступ к файлу 
					lpSecurityAttributes,								// Структура SECURITY_ATTRIBUTES: значение NULL - дескриптор не может наследоваться никакими дочерними процессами (значение по умолчанию)
					dwCreationDisposition,								// Действие, выполняемое с файлом или устройством, которые существуют или не существуют: OPEN_EXISTING - открывает файл, только если он существуют
					dwFlagsAndAttributes,								// В зависимости от выбранного атрибута определяет свойства файла: FILE_ATTRIBUTE_NORMAL - в файле не заданы другие атрибуты (значение по умолчанию)
					fileTemplate);

				bErrorFlag = WriteFile(
					newFile_2,											// Дескриптор файла, который читается. Дескриптор файла должен быть, создан с правом доступа GENERIC_WRITE
					&chBuffer_3,										// Указатель на буфер, содержащий данные для записи в файл
					(DWORD)strlen(chBuffer_3),							// Число байтов, записываемых в файл или устройство
					&dwBytesWritten,									// Указатель на переменную, которая получает количество байтов, записанных при использовании синхронного параметра hFile (в нашем случае - newFile)
					0);													// Указатель на структуру OVERLAPPED требуется, если параметр (в нашем случае - newFile) был открыт с FILE_FLAG_OVERLAPPED
				CloseHandle(newFile_2);
			}
		}
		break;
	case WM_CHAR:																// Символьное сообщение от клавиатуры

		break;
	case WM_RBUTTONDOWN:														// Обработчик нажатия правой кнопки мыши

		break;
	case WM_DESTROY:															// Завершение программы
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0L;
}

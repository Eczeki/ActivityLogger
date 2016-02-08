#include "WindowRecorder.h"


WindowRecorder::WindowRecorder()
{
	stopped = false;
	newWindow = false;
	pastWindowName = "";
	timeStart = time(0);
	timeInSeconds = 0.0;	

	trackedPrograms();
}

WindowRecorder::~WindowRecorder()
{
	delete recorder;
}

/* Reads the config.txt file and stores the programs that the user wants to track in a map */
void WindowRecorder::trackedPrograms()
{
	std::ifstream in;
	std::string program;
	in.open("config.txt");

	if (in.is_open())
	{
		/* Read each program name from the config file and store it in the map */
		while (std::getline(in, program))
		{
			programMap[program] = 0;
		}

		in.close();
	}
	
}

/* Takes a screenshot of the whole user screen area and stores the image in a BMP */
void WindowRecorder::takeScreenshot(std::string name)
{
	RECT rect;
	HDC screen = CreateDC(TEXT("DISPLAY"), 0, 0, 0);
	HDC dest = CreateCompatibleDC(screen);
	std::cout << programMap[name] << std::endl;
	name.append(std::to_string(programMap[name]++) + ".bmp");

#ifdef UNICODE	
	std::wstring newString = stringToWstring(name);	
	wchar_t *out = (wchar_t *)newString.c_str();
#else
	char* out = _strdup(name.c_str());
#endif
	
	GetWindowRect(GetDesktopWindow(), &rect);

	HBITMAP bmp = CreateCompatibleBitmap(screen, rect.right, rect.bottom);
	SelectObject(dest, bmp);
	BitBlt(dest, 0, 0, rect.right, rect.bottom, screen, 0, 0, SRCCOPY);

	CreateBMPFile(GetDesktopWindow(), (LPTSTR)out, CreateBitmapInfoStruct(GetDesktopWindow(), bmp), bmp, dest);

	DeleteDC(screen);	
}

/* Converts string to wstring. Credit: http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode */
std::wstring WindowRecorder::stringToWstring(const std::string &s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

/* Creates a Bitmap of a window. Credit: https://msdn.microsoft.com/en-us/library/windows/desktop/dd145119(v=vs.85).aspx */
PBITMAPINFO WindowRecorder::CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		std::cout << "Error retrieving bitmap color" << std::endl;

    // Convert the color format to a count of bits.  
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure  
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
    // data structures.)  

     if (cClrBits < 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 

    // Initialize the fields in the BITMAPINFO structure.  

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

    // If the bitmap is not compressed, set the BI_RGB flag.  
    pbmi->bmiHeader.biCompression = BI_RGB; 

    // Compute the number of bytes in the array of color  
    // indices and store the result in biSizeImage.  
    // The width must be DWORD aligned unless the bitmap is RLE 
    // compressed. 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the  
    // device colors are important.  
     pbmi->bmiHeader.biClrImportant = 0; 
     return pbmi; 
}

void WindowRecorder::CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE *hp;                   // byte pointer  
	DWORD dwTmp;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits)
		std::cout << "Global Alloc" << std::endl;

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		std::cout << "Get DIB" << std::endl;
	}

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		std::cout << "Create file" << std::endl;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		std::cout << "Write File" << std::endl;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		std::cout << "Writefile" << std::endl;

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		std::cout << "Writefile" << std::endl;

	// Close the .BMP file.  
	if (!CloseHandle(hf))
		std::cout << "Closehandle" << std::endl;

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}

void WindowRecorder::start()
{
	/* start thread */
	recorder = new std::thread(&WindowRecorder::outputWindowName, this);
}

void WindowRecorder::stop()
{
	stopped = true;
}

/* Returns true if there's a change of window */
bool WindowRecorder::windowChange()
{
	bool tmp = newWindow;	
	newWindow = false;	
	return tmp;
}

void WindowRecorder::recordKeystroke(char keystroke)
{
	data.addKeystroke(keystroke);
}

void WindowRecorder::outputWindowName()
{
	char name[300];
	HWND currentWindowHWND;
	std::ofstream out;
	bool start = false;
	while (!stopped)
	{		
		currentWindowHWND = GetForegroundWindow();
		GetWindowTextA(currentWindowHWND, name, 300);		
		windowName = std::string(name);
		timeInSeconds = difftime(time(0), timeStart);

		if (pastWindowName != windowName)
		{
			newWindow = true;
			pastWindowName = windowName;
			
			if (windowName == "")
			{
				continue;
			}

			data.setWindowName(pastWindowName);
			//std::cout << pastWindowName << std::endl;

			/* Program is being tracked so take a screenshot */
			if (programMap.find(pastWindowName) != programMap.end())
			{
				std::cout << "taking screen" << std::endl;
				takeScreenshot(pastWindowName);
				data.incrementScreenshotNum();
			}

			data.increaseTimeSpentInWindow(timeInSeconds/60);
			/* @TODO: Fix keystrokes not being displayed under the proper window */
			/* Output data to log */
			out.open("log.txt", std::ofstream::app);

			std::cout << data.toString();
			out << data.toString();
					
			out.close();
			data.resetAll();		/* Clear all data */
			timeStart = time(0);	/* Reset the timer */
		}
	}
}

std::string WindowRecorder::getWindowName()
{
	return windowName;
}

double WindowRecorder::getTime()
{
	return timeInSeconds;
}
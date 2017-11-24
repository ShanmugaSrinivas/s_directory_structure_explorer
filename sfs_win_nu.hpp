#ifndef SFS_WIN_NU_HPP
#define SFS_WIN_NU_HPP
#ifndef UNICODE
#ifndef _UNICODE
#ifdef _WIN32

#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <iostream>

#pragma comment(lib, "User32.lib")

using namespace std;

wstring s2ws(string &str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo( size_needed, 0 );
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

class file
{
public:
	string name,
		alternative_name;
	unsigned long long size;
	bool is_directory;
	bool is_file()
	{
		return !is_directory;
	}
	bool is_dir()
	{
		return is_directory;
	}
};

class open_folder
{
public:
	string path;
	HANDLE hFind;
	WIN32_FIND_DATA ffd;
	file f;
	open_folder()
	{
		hFind=INVALID_HANDLE_VALUE;
	}
	~open_folder()
	{
		FindClose(hFind);
	}
	int open(string path_arg)
	{
		if(path_arg.length()>(MAX_PATH-3))
		{
			cout << "\nERROR: PATH LENGTH > (MAX_PATH-3).";
			return -1;
		}
		path=path_arg;
		hFind = FindFirstFile((path+"\\*").c_str(), &ffd);
		if(hFind==INVALID_HANDLE_VALUE)
		{
			cout << "\nERROR: FOLDER NOT FOUND ON PATH: " << path;
			return -2;
		}
		f.name=ffd.cFileName;
		f.alternative_name=ffd.cAlternateFileName;
		*((unsigned int *)((char *)&f.size))=ffd.nFileSizeLow;
		*((unsigned int *)((char *)&f.size+4))=ffd.nFileSizeHigh;
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			f.is_directory=true;
		else
			f.is_directory=false;
		return 0;
	}
	int load_next()
	{
		if(FindNextFile(hFind, &ffd)==0)
		{
			DWORD dwError = GetLastError();
			if(dwError != ERROR_NO_MORE_FILES)
			{
				cout << "\nERROR: AT FindNextFile. RETURNING GetLastError=" << dwError;
				return dwError;
			}
			return -1;
		}
		else
		{
			f.name=ffd.cFileName;
			f.alternative_name=ffd.cAlternateFileName;
			*((unsigned int *)((char *)&f.size))=ffd.nFileSizeLow;
			*((unsigned int *)((char *)&f.size+4))=ffd.nFileSizeHigh;
			if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				f.is_directory=true;
			else
				f.is_directory=false;
			return 0;
		}
	}
};
#endif
#endif
#endif
#endif

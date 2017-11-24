#ifndef SFS_LINUX_NU_HPP
#define SFS_LINUX_NU_HPP
#ifndef UNICODE
#ifndef _UNICODE
#ifdef linux

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

class file
{
public:
	string name;
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
	DIR *dp;
	struct dirent *ep;
	string path;
	file f;
	open_folder()
	{
		dp=NULL;
		ep=NULL;
	}
	~open_folder()
	{
		(void) closedir (dp);
	}
	int open(string path_arg)
	{
		path=path_arg;
		dp = opendir (path.c_str());
		if(dp==NULL)
		{
			cout << "\nERROR: FOLDER NOT FOUND ON PATH: " << path;
			return -2;
		}
		if(ep = readdir (dp))
		{
			f.name=ep->d_name;
			if(ep->d_type==DT_REG)
			 	f.is_directory=false;
			else if(ep->d_type==DT_DIR)
			 	f.is_directory=true;
			else
			{
				cout << "\nERROR: (d_type!=DT_REG && d_type!=DT_DIR). EXITING...\n";
				exit(-1);
			}
			return 0;
		}
		else
			return -1;
	}
	int load_next()
	{
		if(ep = readdir (dp))
		{
			f.name=ep->d_name;
			if(ep->d_type==DT_REG)
				f.is_directory=false;
			else if(ep->d_type==DT_DIR)
				f.is_directory=true;
			else
			{
				cout << "\nERROR: (d_type!=DT_REG && d_type!=DT_DIR). EXITING...\n";
				exit(-1);
			}
			return 0;
		}
		else
			return -1;
	}
};
#endif
#endif
#endif
#endif

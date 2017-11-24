#include "sfs_linux_nu.hpp"
#include "sfs_win_nu.hpp"
#include "sfs_win_u.hpp"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("\nUsage: %s <directory name>\n", argv[0]);
		return (-1);
	}
	open_folder o_fol;
	o_fol.open(argv[1]);

	int count=0;
	do
	{
		if (o_fol.f.is_dir())
		{
			cout << "\n\t" << o_fol.f.name << "\t<DIR>";
		}
		else
		{
			#ifdef _WIN32
			cout << "\n\t" << o_fol.f.name << "\t\t" << o_fol.f.size;
			#else
			cout << "\n\t" << o_fol.f.name;
			#endif
		}
		count++;
		//cout << "\ncount=" << count;
	}while (o_fol.load_next()==0);
	cout << endl;
	return 0;
}

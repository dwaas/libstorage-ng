
#include <iostream>

#include <storage/SystemInfo/SystemInfo.h>

using namespace std;
using namespace storage;


void
test_cmddmsetupinfo(SystemInfo& systeminfo)
{
    try
    {
	const CmdDmsetupInfo& cmddmsetupinfo = systeminfo.getCmdDmsetupInfo();
	cout << "CmdDmsetupInfo success" << endl;
	cout << cmddmsetupinfo << endl;
    }
    catch (const exception& e)
    {
	cerr << "CmdDmsetupInfo failed" << endl;
    }
}


int
main()
{
    set_logger(get_logfile_logger());

    SystemInfo systeminfo;

    test_cmddmsetupinfo(systeminfo);
}

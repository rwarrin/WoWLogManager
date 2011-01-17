#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {
	time_t timeNow;
	struct tm *ts;
	char outputpath[256];
	char configpath[256];
	char inputfilepath[256];
	char filename[256];

	timeNow = time(NULL);
	ts = localtime(&timeNow);
	strftime(filename, sizeof(filename), "WoWCombatLog_%m-%d-%Y_%I-%M-%S-%p.txt", ts);

	std::ifstream config;
	config.open("config");

	if(config.fail()) {
		cout << "Failed to open 'config'.  Terminating application\n";
		cout << "Please make sure the file exists in the same directory as the application.\n";
		cin.get();
		return 1;
	}

	config.getline(configpath, 256, '\n');

	cout << "Using path: " << configpath << endl;

	strcpy(inputfilepath, configpath);
	strcpy(outputpath, configpath);

	strcat(inputfilepath, "WoWCombatLog.txt");
	strcat(outputpath, filename);

	if(CopyFile(inputfilepath, outputpath, false) != 0) {
		cout << "Successfully created new combat log! \n " << outputpath << endl;
	}
	else {
		cout << "Failed to create new combat log!  Error " << GetLastError() << endl;
		cin.get();
		return 1;
	}

	cout << "Deleting old combat log.\n";
	DeleteFile(inputfilepath);

	cout << "Press ENTER to close.\n";
	cin.get();
	return 0;
}
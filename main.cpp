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
		cout << "Press ENTER to quit.\n";
		cin.get();
		return 1;
	}

	config.getline(configpath, 256, '\n');
	config.close();

	cout << "Using path:\n\t" << configpath << "\n\n";

	strcpy(inputfilepath, configpath);
	strcpy(outputpath, configpath);

	strcat(inputfilepath, "WoWCombatLog.txt");
	strcat(outputpath, filename);

	ifstream combatlog;
	combatlog.open(inputfilepath);

	if(combatlog.fail()) {
		cout << "Could not find a combat log at:\n\t" << inputfilepath << "\n\n";
	}
	combatlog.close();

	if(CopyFile(inputfilepath, outputpath, false) != 0) {
		cout << "Successfully created new combat log! \n\t" << outputpath << "\n\n";
	}
	else {
		cout << "Failed to create new combat log!\n\tError " << GetLastError() << "\n\n";
		cout << "Press ENTER to quit.\n";
		cin.get();
		return 1;
	}

	cout << "Deleting old combat log.\n";
	int deleteSuccess = NULL;
	deleteSuccess = DeleteFile(inputfilepath);

	if(deleteSuccess != 0) {
		cout << "Successfully deleted old combatlog.\n";
	}
	else {
		cout << "Failed to delete old combatlog.  You need to delete it yourself.\n";
	}

	cout << "Press ENTER to quit.\n";
	cin.get();
	return 0;
}
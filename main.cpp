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
		printf("Failed to open 'config'.  Terminating application\n");
		printf("Please make sure the file exists in the same directory as the application.\n");
		cin.get();
		return 1;
	}

	config.getline(configpath, 256, '\n');

	strcpy(inputfilepath, configpath);
	strcpy(outputpath, configpath);

	strcat(inputfilepath, "WoWCombatLog.txt");
	strcat(outputpath, filename);

	if(CopyFile(inputfilepath, outputpath, false) != 0) {
		printf("\nSuccessfully created new combat log!\n");
	}
	else {
		printf("\nFailed to create new combat log!  Error %d", GetLastError());
		cin.get();
		return 1;
	}

	DeleteFile(inputfilepath);

	return 0;
}
#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <fstream>

using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpcmdline, int ncmdshow) {
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
		MessageBox(NULL, "Failed to open config.\nPlease make sure the file exists in the application directory.\n\nPress OK to exit.", "Error", MB_ICONERROR | MB_OK);
		return 1;
	}

	config.getline(configpath, 256, '\n');
	config.close();

	strcpy(inputfilepath, configpath);
	strcpy(outputpath, configpath);

	strcat(inputfilepath, "WoWCombatLog.txt");
	strcat(outputpath, filename);

	ifstream combatlog;
	combatlog.open(inputfilepath);

	if(combatlog.fail()) {
		char errorMessage[256] = "Could not find a combat log at '";
		strcat(errorMessage, inputfilepath);
		strcat(errorMessage, "'.");
		MessageBox(NULL, errorMessage, "Error", MB_ICONWARNING | MB_OK);
	}
	combatlog.close();

	if(CopyFile(inputfilepath, outputpath, false) != 0) {
		char successMessage[256] = "Successfully created a new combat log at '";
		strcat(successMessage, outputpath);
		strcat(successMessage, "'.");
		MessageBox(NULL, successMessage, "", MB_ICONINFORMATION | MB_OK);
	}
	else {
		MessageBox(NULL, "Failed to create new combat log.\nAborting.", "Error", MB_ICONERROR | MB_OK);
		return 1;
	}

	int deleteSuccess = NULL;
	deleteSuccess = DeleteFile(inputfilepath);

	if(deleteSuccess != 0) {
		MessageBox(NULL, "Successfully removed old combatlog file.", "", MB_ICONINFORMATION | MB_OK);
	}
	else {
		MessageBox(NULL, "Failed to delete old combatlog file.  Did you forget to close World of Warcraft?\nYou will need to remove the old combatlog manually or new logs will\nbe appended to the end.\n\nThe file cannot be deleted while it is open for writing by another application.\nNext time try closing World of Warcraft before running this application.", "Error", MB_ICONWARNING | MB_OK);
	}

	return 0;
}
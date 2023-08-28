#include "Settings.h"
#include <stdio.h>
#include <shlobj_core.h>

VOID SaveConfig()
{
	CHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		strcat(path, "\\ConfigK.cfg");

		auto file = fopen(path, "wb");
		if (file)
		{
			fwrite(&Settings, sizeof(Settings), 1, file);
			fclose(file);
		}
		else
		{
			// Handle error
		}
	}
}
VOID LoadSavedConfig()
{
	CHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		strcat(path, "\\ConfigK.cfg");

		auto file = fopen(path, "rb");
		if (file)
		{
			fseek(file, 0, SEEK_END);
			auto size = ftell(file);

			if (size == sizeof(Settings))
			{
				fseek(file, 0, SEEK_SET);
				fread(&Settings, sizeof(Settings), 1, file);
				fclose(file);
			}
			else
			{
				fclose(file);				
			}
		}
	}
}
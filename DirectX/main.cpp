#include "AppWindow.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	AppWindow app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}

	return 0;
}
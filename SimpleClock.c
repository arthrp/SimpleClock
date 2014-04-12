#include "inkview.h"
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define TIME_STR_LENGTH 100
#define DATE_STR_LENGTH 300
#define UPDATE_INTERVAL_MS 1000

ifont *clockFont;
char timeString[TIME_STR_LENGTH];
char dateString[DATE_STR_LENGTH];
struct tm *timeInfo;
int isFirstUpdate = TRUE;

void showClock()
{
	ClearScreen();
	SetFont(clockFont, BLACK);
	
	time_t currentTime = time(NULL);
	timeInfo = localtime(&currentTime);
	strftime(timeString,TIME_STR_LENGTH,"%H : %M : %S",timeInfo);
	strftime(dateString,DATE_STR_LENGTH,"%d %b %Y",timeInfo);
	
	DrawString(ScreenWidth()/3, 2, timeString);
	DrawString(ScreenWidth()/3, 100, dateString);
	isFirstUpdate ? FullUpdate() : SoftUpdate();
	
	SetHardTimer("SIMPLE_CLOCK",showClock,UPDATE_INTERVAL_MS);
}

int simpleClockHandler(int type, int par1, int par2)
{
	if (type == EVT_INIT){
		clockFont = OpenFont("DroidSans",48,1);
	}
	if (type == EVT_SHOW){
		showClock();
		isFirstUpdate = FALSE;
	}
	if (type == EVT_KEYPRESS)
		CloseApp();
	
	return 0;
}

int main(int argc, char **argv)
{
	SetAutoPowerOff(FALSE);
	
	InkViewMain(simpleClockHandler);
	return 0;
}

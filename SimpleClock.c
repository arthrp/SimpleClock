#include "inkview.h"
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define TIME_STR_LENGTH 100
#define DATE_STR_LENGTH 300
#define UPDATE_INTERVAL_MS 1000
#define FONT_SIZE 72
#define APPROX_STR_WIDTH_PX 360

ifont *clockFont;
char timeString[TIME_STR_LENGTH];
char dateString[DATE_STR_LENGTH];
struct tm *timeInfo;
int isFirstUpdate = TRUE;
int xOffset = 0;

void showClock()
{
	ClearScreen();
	SetFont(clockFont, BLACK);
	
	time_t currentTime = time(NULL);
	timeInfo = localtime(&currentTime);
	strftime(timeString,TIME_STR_LENGTH,"%H : %M : %S",timeInfo);
	strftime(dateString,DATE_STR_LENGTH,"%d %b %Y",timeInfo);
	
	DrawString(xOffset, 2, timeString);
	DrawString(xOffset, 100, dateString);
	isFirstUpdate ? FullUpdate() : SoftUpdate();
	
	SetHardTimer("SIMPLE_CLOCK",showClock,UPDATE_INTERVAL_MS);
}

int simpleClockHandler(int type, int par1, int par2)
{
	if (type == EVT_INIT){
		clockFont = OpenFont("DroidSans",FONT_SIZE,1);
		xOffset = (ScreenWidth() - APPROX_STR_WIDTH_PX)/2;
	}
	else if (type == EVT_SHOW){
		showClock();
		isFirstUpdate = FALSE;
	}
	else if (type == EVT_KEYPRESS)
		CloseApp();
	
	return 0;
}

int main(int argc, char **argv)
{
	SetAutoPowerOff(FALSE);
	
	InkViewMain(simpleClockHandler);
	return 0;
}

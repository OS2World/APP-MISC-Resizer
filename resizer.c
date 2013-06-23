/* Window Resizer - by Darrell Spice, Jr.     September 16, 2000
|| finds the window passed and change it's size
|| http://home.houston.rr.com/spiceware/
*/

#define INCL_WINFRAMEMGR
#define INCL_WINWINDOWMGR
#define INCL_WINMESSAGEMGR
#define INCL_WINSYS
#include <os2.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    /* handles for Anchor Block, Window, Enumoration, and Mesage Queue */
    HAB hab;
    HWND hwnd;
    HENUM henum;
    HMQ hmq;

    /* window title and search for title */
    char title[MAXNAMEL + 1];
    char searchfor[MAXNAMEL + 1];

    /* screen and window dimensions */
    int screenx;
    int screeny;
    int windowx;
    int windowy;

    /* window size rectangle */
    RECTL rcl;

    /* window size multiplier */
    int multiplier;

    /* set default window and size */
    strcpy(searchfor, "Entrepreneur");
    multiplier = 2;

    /* get passed parameters, change to defaults if invalid */
    if (argc > 1) strcpy(searchfor, argv[1]);
    if (argc > 2) multiplier = atoi(argv[2]);
    if (strlen(searchfor) == 0) strcpy(searchfor, "Entrepreneur");
    if (multiplier < 1) multiplier = 2;

    /* get Anchor Block and create Message Queue */
    hab = WinInitialize(0);
    if (!(hmq = WinCreateMsgQueue (hab, 0))) return(1);

    /* get screen dimensions - used to center resized window */
    screenx = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
    screeny = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

    /* ask for list of windows */
    henum = WinBeginEnumWindows(HWND_DESKTOP);
    while((hwnd = WinGetNextWindow(henum)) != NULLHANDLE)
    {
        WinQueryWindowText(hwnd, strlen(searchfor)+1, title);
        if (strcmp(title, searchfor)==0)
        {
            /* get frame window size */
            WinQueryWindowRect (hwnd, &rcl);

            /* calculate client window size */
            WinCalcFrameRect(hwnd, &rcl, TRUE);

            /* calculate new client window size */
            rcl.xRight = (rcl.xRight - rcl.xLeft) * multiplier;
            rcl.yTop = (rcl.yTop - rcl.yBottom) * multiplier;
            rcl.xLeft = 0;
            rcl.yBottom = 0;

            /* calculate new frame window size */
            WinCalcFrameRect(hwnd, &rcl, FALSE);

            /* send window position & size change request */
            windowx = rcl.xRight - rcl.xLeft;
            windowy = rcl.yTop - rcl.yBottom;
            WinSetWindowPos(hwnd, NULLHANDLE,
                     (screenx - windowx)/2,
                     (screeny - windowy )/2,
                     windowx ,
                     windowy ,
                     SWP_SIZE|SWP_MOVE|SWP_ACTIVATE|SWP_SHOW);
        }
    }

    /* clean up */
    WinEndEnumWindows(henum);
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
    return 0;
}



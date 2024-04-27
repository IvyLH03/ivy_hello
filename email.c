#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#define URL_LENGTH 50
#define URL_NUM 10
#define BUFSIZE 1024



char urls[][URL_LENGTH] = {
    "https://mail.google.com/",
    "https://outlook.office365.com/mail/",
    };

int url_num = sizeof(urls) / (URL_LENGTH * sizeof(char));

// copied form https://learn.microsoft.com/en-us/troubleshoot/windows-server/performance/obtain-console-window-handle
HWND GetConsoleHwnd(void)
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                        // WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                        // WindowTitle.

    // Fetch current window title.

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.

    wsprintf(pszNewWindowTitle,"%d/%d",
                GetTickCount(),
                GetCurrentProcessId());

    // Change current window title.

    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.

    Sleep(40);

    // Look for NewWindowTitle.

    hwndFound=FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}

void open_urls() {
    // 调用ShellExecute函数以默认浏览器打开URL
    //ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    for(int i = 0; i < url_num; i++) {
        printf("Opening: %s\n", urls[i]);
        ShellExecute(NULL, "open", urls[i], NULL, NULL, SW_SHOWNORMAL);
    }
    sleep(1);
    HWND hwnd =  GetConsoleHwnd();
    ShowWindow(hwnd, SW_MINIMIZE);
    ShowWindow(hwnd, SW_RESTORE);
}

void hello_message() {
    printf("Hello %s\n", getenv("USERNAME"));
}

void window_init() {
    
}

int main(int argc, char * argv[]) {
    window_init();
    hello_message();
    open_urls();
    
    getchar();
    return 0;
}
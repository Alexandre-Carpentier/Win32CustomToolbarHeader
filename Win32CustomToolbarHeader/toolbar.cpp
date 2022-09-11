#include "toolbar.h"

HWND CreateCustomToolbar(HWND hWndParent)
{

    // Create the toolbar window.
    HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 0, 0,
        hWndParent, NULL, GetModuleHandle(NULL), nullptr);

    if (hWndToolbar == NULL)
        return NULL;

    // define an custom image list ptr
    HIMAGELIST hCustomImageList = NULL;

    // Set the number of images
    const int nElements = 5;

    // Create the custom image list.
    hCustomImageList = ImageList_Create(32, 32,                   // Dimensions of individual bitmaps.  
        ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
        nElements, 10);

    // Load image list into toolbar
    HIMAGELIST hCustomImageListOld = (HIMAGELIST)SendMessage(hWndToolbar, TB_SETIMAGELIST, 0, (LPARAM)hCustomImageList);
    if (NULL == hCustomImageListOld)
    {
        //ErrorExit();
        DWORD dwErr = ::GetLastError();
    }

    HBITMAP hbmp1 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_SHARED);
    //ImageList_Add(hCustomImageList, hbmp1, 0);  // without transparency
    ImageList_AddMasked(hCustomImageList, hbmp1, CLR_DEFAULT);// with transparency
    DeleteObject(hbmp1);

    HBITMAP hbmp2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_SHARED);
    //ImageList_Add(hCustomImageList, hbmp2, NULL);
    ImageList_AddMasked(hCustomImageList, hbmp2, CLR_DEFAULT);
    DeleteObject(hbmp2);

    HBITMAP hbmp3 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADTRANSPARENT | LR_SHARED);
    //ImageList_Add(hCustomImageList, hbmp3, NULL);
    ImageList_AddMasked(hCustomImageList, hbmp3, CLR_DEFAULT);
    DeleteObject(hbmp3);

    HBITMAP hbmp4 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADTRANSPARENT | LR_SHARED);
    //ImageList_Add(hCustomImageList, hbmp4, NULL);
    ImageList_AddMasked(hCustomImageList, hbmp4, CLR_DEFAULT);
    DeleteObject(hbmp4);

    HBITMAP hbmp5 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADTRANSPARENT | LR_SHARED);
    //ImageList_Add(hCustomImageList, hbmp5, NULL);
    ImageList_AddMasked(hCustomImageList, hbmp5, CLR_DEFAULT);
    DeleteObject(hbmp5);

    // Fail if not all of the images were added. 
    if (ImageList_GetImageCount(hCustomImageList) < nElements)
        return FALSE;

    // Populate array of button describing structures
    TBBUTTON tbb[nElements];
    SecureZeroMemory(tbb, nElements * sizeof(TBBUTTON));

    tbb[0].iBitmap = 0;// (index img; imglist num)
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = BTNS_BUTTON;
    tbb[0].idCommand = IDC_CONNECTMODE;
    tbb[0].iString = SendMessage(hWndToolbar, TB_ADDSTRING, 0, (LPARAM)TEXT("Connecter\0"));

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = BTNS_BUTTON;
    tbb[1].idCommand = IDC_NEW;
    tbb[1].iString = SendMessage(hWndToolbar, TB_ADDSTRING, 0, (LPARAM)TEXT("Nouveau\0"));

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = BTNS_BUTTON;
    tbb[2].idCommand = IDC_LOAD;
    tbb[2].iString = SendMessage(hWndToolbar, TB_ADDSTRING, 0, (LPARAM)TEXT("Charger\0"));

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = BTNS_BUTTON;
    tbb[3].idCommand = IDC_SAVE;
    tbb[3].iString = SendMessage(hWndToolbar, TB_ADDSTRING, 0, (LPARAM)TEXT("Sauvegarder\0"));

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = BTNS_BUTTON;
    tbb[4].idCommand = IDC_EXPERTMODE;
    tbb[4].iString = SendMessage(hWndToolbar, TB_ADDSTRING, 0, (LPARAM)TEXT("Oscilloscope\0"));

    // Compatibility mandatory
    SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

    // Load the button structs into the toolbar to create the buttons
    SendMessage(hWndToolbar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);

    // Resize properly and display
    SendMessage(hWndToolbar, TB_SETBUTTONSIZE, 0, MAKELPARAM(64, 64));

    SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
    ShowWindow(hWndToolbar, TRUE);

    return hWndToolbar;
}
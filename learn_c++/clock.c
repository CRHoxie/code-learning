/*
 * 轻量级番茄钟 + 计算器 (Win32 API)
 * 编译 (MinGW): gcc -mwindows -o tomato.exe tomato.c -lgdi32 -luser32
 * 功能:
 *   - 黑色背景翻页时钟 (HH:MM:SS)
 *   - 双击客户区弹出菜单，包含番茄钟和计算器
 *   - 番茄钟: 25分钟倒计时，开始/暂停/重置
 *   - 计算器: 简单四则运算
 */

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 菜单和控件 ID
#define IDM_TOMATO      1001
#define IDM_CALC        1002
#define IDM_EXIT        1003

#define ID_BTN_START    1010
#define ID_BTN_PAUSE    1011
#define ID_BTN_RESET    1012

#define ID_CALC_BASE    2000
#define ID_CALC_CLEAR   2100

// 全局变量
HINSTANCE g_hInst;

// 番茄钟窗口
HWND g_hTomatoWnd = NULL;
HWND g_hTomatoStatic = NULL;
int  g_tomatoRemaining = 25 * 60;   // 剩余秒数
BOOL g_tomatoRunning = FALSE;

// 计算器窗口
HWND g_hCalcWnd = NULL;
HWND g_hCalcEdit = NULL;
char g_calcDisplay[256] = "0";
double g_calcAccum = 0.0;
char g_calcOp = 0;
BOOL g_calcNewNumber = TRUE;
BOOL g_calcError = FALSE;

// 计算器按钮标签 (4x4)
const char* calc_button_labels[16] = {
    "7", "8", "9", "/",
    "4", "5", "6", "*",
    "1", "2", "3", "-",
    "0", ".", "=", "+"
};

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK TomatoProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CalcProc(HWND, UINT, WPARAM, LPARAM);
void DrawFlipClock(HDC hdc, RECT *rc);
void UpdateTomatoDisplay(void);
void HandleCalcInput(char ch);
void UpdateCalcDisplay(void);
void ClearCalc(void);
HWND CreateTomatoWindow(HWND parent);
HWND CreateCalcWindow(HWND parent);

// 主窗口过程
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, 1, 1000, NULL);  // 每秒更新时钟
            return 0;

        case WM_TIMER:
            if (wParam == 1)
                InvalidateRect(hwnd, NULL, FALSE);  // 触发重绘
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
            DrawFlipClock(hdc, &rc);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_LBUTTONDBLCLK: {  // 双击弹出菜单
            POINT pt;
            GetCursorPos(&pt);
            HMENU hMenu = CreatePopupMenu();
            AppendMenuA(hMenu, MF_STRING, IDM_TOMATO, "番茄钟");
            AppendMenuA(hMenu, MF_STRING, IDM_CALC, "计算器");
            AppendMenuA(hMenu, MF_SEPARATOR, 0, NULL);
            AppendMenuA(hMenu, MF_STRING, IDM_EXIT, "退出");
            SetForegroundWindow(hwnd);
            TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
            DestroyMenu(hMenu);
            return 0;
        }

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_TOMATO:
                    CreateTomatoWindow(hwnd);
                    break;
                case IDM_CALC:
                    CreateCalcWindow(hwnd);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hwnd);
                    break;
            }
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

// 绘制翻页时钟样式的时间
void DrawFlipClock(HDC hdc, RECT *rc) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    int digits[6] = {
        st.wHour / 10, st.wHour % 10,
        st.wMinute / 10, st.wMinute % 10,
        st.wSecond / 10, st.wSecond % 10
    };

    int totalW = rc->right - rc->left;
    int totalH = rc->bottom - rc->top;

    // 根据窗口大小计算数字块尺寸
    int blockH = totalH * 4 / 10;
    if (blockH < 40) blockH = 40;
    if (blockH > 200) blockH = 200;
    int blockW = blockH * 6 / 10;
    int gap = blockW * 15 / 100;
    int colonW = blockW * 3 / 10;

    int totalBlocksW = 6 * blockW + 5 * gap + 2 * colonW;
    int x0 = (totalW - totalBlocksW) / 2;
    int y0 = (totalH - blockH) / 2;

    // 创建字体
    HFONT hFont = CreateFontA(
        blockH * 7 / 10, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, VARIABLE_PITCH, "Arial");
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

    int x = x0;
    for (int i = 0; i < 6; i++) {
        RECT blockRect = { x, y0, x + blockW, y0 + blockH };

        // 绘制带边框的黑色数字块
        HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blackBrush);
        HPEN whitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, whitePen);
        RoundRect(hdc, blockRect.left, blockRect.top, blockRect.right, blockRect.bottom, 10, 10);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(whitePen);

        // 绘制数字
        char num[2] = { '0' + digits[i], '\0' };
        DrawTextA(hdc, num, -1, &blockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        x += blockW;

        // 数字块之间的间距或冒号
        if (i < 5) {
            if (i == 1 || i == 3) {
                RECT colonRect = { x, y0, x + colonW, y0 + blockH };
                DrawTextA(hdc, ":", -1, &colonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                x += colonW;
                x += gap;
            } else {
                x += gap;
            }
        }
    }

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

// 更新番茄钟显示
void UpdateTomatoDisplay(void) {
    if (g_hTomatoStatic && IsWindow(g_hTomatoStatic)) {
        char buf[16];
        int mins = g_tomatoRemaining / 60;
        int secs = g_tomatoRemaining % 60;
        sprintf(buf, "%02d:%02d", mins, secs);
        SetWindowTextA(g_hTomatoStatic, buf);
    }
}

// 创建番茄钟窗口
HWND CreateTomatoWindow(HWND parent) {
    if (g_hTomatoWnd && IsWindow(g_hTomatoWnd)) {
        SetForegroundWindow(g_hTomatoWnd);
        return g_hTomatoWnd;
    }

    HWND hwnd = CreateWindowExA(
        0, "TomatoTimerWindow", "番茄钟",
        WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 220,
        parent, NULL, g_hInst, NULL);
    g_hTomatoWnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}

// 番茄钟窗口过程
LRESULT CALLBACK TomatoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 创建时间显示
            HFONT hFont = CreateFontA(
                48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY, VARIABLE_PITCH, "Arial");
            g_hTomatoStatic = CreateWindowExA(
                0, "STATIC", "25:00",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                60, 30, 200, 80, hwnd, NULL, g_hInst, NULL);
            SendMessageA(g_hTomatoStatic, WM_SETFONT, (WPARAM)hFont, TRUE);

            // 创建按钮
            CreateWindowExA(0, "BUTTON", "开始",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                30, 140, 70, 40, hwnd, (HMENU)ID_BTN_START, g_hInst, NULL);
            CreateWindowExA(0, "BUTTON", "暂停",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                125, 140, 70, 40, hwnd, (HMENU)ID_BTN_PAUSE, g_hInst, NULL);
            CreateWindowExA(0, "BUTTON", "重置",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                220, 140, 70, 40, hwnd, (HMENU)ID_BTN_RESET, g_hInst, NULL);

            g_tomatoRemaining = 25 * 60;
            g_tomatoRunning = FALSE;
            SetTimer(hwnd, 1, 1000, NULL);
            return 0;
        }

        case WM_TIMER:
            if (wParam == 1 && g_tomatoRunning) {
                if (g_tomatoRemaining > 0) {
                    g_tomatoRemaining--;
                    UpdateTomatoDisplay();
                    if (g_tomatoRemaining == 0) {
                        g_tomatoRunning = FALSE;
                        MessageBeep(MB_ICONEXCLAMATION);
                        MessageBoxA(hwnd, "番茄钟结束！", "提示", MB_OK);
                    }
                }
            }
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_START:
                    g_tomatoRunning = TRUE;
                    break;
                case ID_BTN_PAUSE:
                    g_tomatoRunning = FALSE;
                    break;
                case ID_BTN_RESET:
                    g_tomatoRemaining = 25 * 60;
                    g_tomatoRunning = FALSE;
                    UpdateTomatoDisplay();
                    break;
            }
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, 1);
            g_hTomatoWnd = NULL;
            g_hTomatoStatic = NULL;
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

// 创建计算器窗口
HWND CreateCalcWindow(HWND parent) {
    if (g_hCalcWnd && IsWindow(g_hCalcWnd)) {
        SetForegroundWindow(g_hCalcWnd);
        return g_hCalcWnd;
    }

    HWND hwnd = CreateWindowExA(
        0, "CalcWindow", "计算器",
        WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 260, 300,
        parent, NULL, g_hInst, NULL);
    g_hCalcWnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}

// 更新计算器显示
void UpdateCalcDisplay(void) {
    if (g_hCalcEdit && IsWindow(g_hCalcEdit)) {
        if (strlen(g_calcDisplay) == 0)
            strcpy(g_calcDisplay, "0");
        SetWindowTextA(g_hCalcEdit, g_calcDisplay);
    }
}

// 清除计算器状态
void ClearCalc(void) {
    g_calcAccum = 0.0;
    g_calcOp = 0;
    g_calcNewNumber = TRUE;
    g_calcError = FALSE;
    strcpy(g_calcDisplay, "0");
    UpdateCalcDisplay();
}

// 执行四则运算
double DoCalc(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                g_calcError = TRUE;
                return 0;
            }
            return a / b;
        default: return b;
    }
}

// 处理计算器按钮输入
void HandleCalcInput(char ch) {
    if (ch >= '0' && ch <= '9') {
        if (g_calcNewNumber) {
            strcpy(g_calcDisplay, "");
            g_calcNewNumber = FALSE;
        }
        if (strlen(g_calcDisplay) < 20) {
            int len = strlen(g_calcDisplay);
            g_calcDisplay[len] = ch;
            g_calcDisplay[len + 1] = '\0';
        }
        UpdateCalcDisplay();
    }
    else if (ch == '.') {
        if (g_calcNewNumber) {
            strcpy(g_calcDisplay, "0.");
            g_calcNewNumber = FALSE;
        }
        else if (!strchr(g_calcDisplay, '.')) {
            strcat(g_calcDisplay, ".");
        }
        UpdateCalcDisplay();
    }
    else if (ch == '=') {
        if (g_calcOp != 0 && !g_calcNewNumber) {
            double current = atof(g_calcDisplay);
            double result = DoCalc(g_calcAccum, current, g_calcOp);
            if (g_calcError) {
                strcpy(g_calcDisplay, "Error");
                g_calcError = FALSE;
                g_calcOp = 0;
                g_calcNewNumber = TRUE;
            }
            else {
                sprintf(g_calcDisplay, "%.10g", result);
                g_calcOp = 0;
                g_calcNewNumber = TRUE;
            }
            UpdateCalcDisplay();
        }
    }
    else { // 运算符 + - * /
        if (!g_calcNewNumber) {
            double current = atof(g_calcDisplay);
            if (g_calcOp != 0) {
                double result = DoCalc(g_calcAccum, current, g_calcOp);
                if (g_calcError) {
                    strcpy(g_calcDisplay, "Error");
                    g_calcError = FALSE;
                    g_calcOp = 0;
                    g_calcNewNumber = TRUE;
                    UpdateCalcDisplay();
                    return;
                }
                sprintf(g_calcDisplay, "%.10g", result);
            }
            g_calcAccum = atof(g_calcDisplay);
        }
        g_calcOp = ch;
        g_calcNewNumber = TRUE;
        UpdateCalcDisplay();
    }
}

// 计算器窗口过程
LRESULT CALLBACK CalcProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 编辑框显示
            g_hCalcEdit = CreateWindowExA(
                WS_EX_CLIENTEDGE, "EDIT", "0",
                WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
                10, 10, 190, 40, hwnd, NULL, g_hInst, NULL);

            // 清除按钮
            CreateWindowExA(0, "BUTTON", "C",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                210, 10, 40, 40, hwnd, (HMENU)ID_CALC_CLEAR, g_hInst, NULL);

            // 4x4 计算器按钮
            int idx = 0;
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    int x = 10 + c * 55;
                    int y = 60 + r * 45;
                    CreateWindowExA(
                        0, "BUTTON", calc_button_labels[idx],
                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                        x, y, 50, 40, hwnd,
                        (HMENU)(UINT_PTR)(ID_CALC_BASE + idx),
                        g_hInst, NULL);
                    idx++;
                }
            }

            ClearCalc();
            return 0;
        }

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id >= ID_CALC_BASE && id < ID_CALC_BASE + 16) {
                const char* label = calc_button_labels[id - ID_CALC_BASE];
                HandleCalcInput(label[0]);
            }
            else if (id == ID_CALC_CLEAR) {
                ClearCalc();
            }
            return 0;
        }

        case WM_DESTROY:
            g_hCalcWnd = NULL;
            g_hCalcEdit = NULL;
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

// 程序入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    // 显式忽略未使用的参数，消除编译警告
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    g_hInst = hInstance;

    // 注册主窗口类
    WNDCLASSEXA wcMain = { 0 };
    wcMain.cbSize = sizeof(WNDCLASSEXA);
    wcMain.lpfnWndProc = WndProc;
    wcMain.hInstance = hInstance;
    wcMain.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcMain.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcMain.lpszClassName = "TomatoClockMain";
    RegisterClassExA(&wcMain);

    // 注册番茄钟窗口类
    WNDCLASSEXA wcTomato = { 0 };
    wcTomato.cbSize = sizeof(WNDCLASSEXA);
    wcTomato.lpfnWndProc = TomatoProc;
    wcTomato.hInstance = hInstance;
    wcTomato.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcTomato.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcTomato.lpszClassName = "TomatoTimerWindow";
    RegisterClassExA(&wcTomato);

    // 注册计算器窗口类
    WNDCLASSEXA wcCalc = { 0 };
    wcCalc.cbSize = sizeof(WNDCLASSEXA);
    wcCalc.lpfnWndProc = CalcProc;
    wcCalc.hInstance = hInstance;
    wcCalc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcCalc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcCalc.lpszClassName = "CalcWindow";
    RegisterClassExA(&wcCalc);

    // 创建主窗口
    HWND hwndMain = CreateWindowExA(
        0, "TomatoClockMain", "番茄钟",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 400,
        NULL, NULL, hInstance, NULL);

    if (!hwndMain)
        return 0;

    // 消息循环
    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
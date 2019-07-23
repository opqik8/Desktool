#include "tool.h"


namespace tool {

    HWND UnderE::Progman=nullptr;
    HWND UnderE::MiddleW=nullptr;
    HWND UnderE::SHELLDLL=nullptr;

    bool UnderE::put(wstring&& window_name){
        HWND w = ::FindWindow(nullptr, window_name.c_str());
        if (w == nullptr){
            qDebug()<<"FAIL.3";
            return false;
        }
        return put(w);
    }
    bool UnderE::put(WId handle){
        return put(reinterpret_cast<HWND>(handle));
    }


    bool UnderE::put(HWND app){


        ///最底层方案(放在管理器中) 并不可行 不能win+tab
        //-SendMessage(MiddleW, 16, 0, 0); //关闭生成的WorkerW
        //-SetParent(app, Progman);//将窗口放在最底层


        ///中间WorkerW层方案
        /*
            这种方案不可交互
            关闭的时候不能马上消失
        */
        SetParent(app, MiddleW);//将窗口放在中间新生成的那个workerw层


        //shelldll 方案
        //SetParent(app,UnderE::SHELLDLL);


        return true;
    }


    bool UnderE::init(){
        UnderE::Progman = ::FindWindow(_T("Progman"), _T("Program Manager"));
        if (UnderE::Progman == nullptr){
            qDebug()<<"FAIL.1";
            return false;
        }
        //SendMessageW(UnderE::Progman, 0x052c, 1, 0); //关闭WorkerW
        SendMessageW(UnderE::Progman, 0x052c, 0, 0); //生成WorkerW
        EnumWindows(&UnderE::EnumWindowsProc,0);
        return true;
    }

    BOOL CALLBACK UnderE::EnumWindowsProc(HWND hwnd,LPARAM lParam)
    {
        lParam = 0;//消除警告
        char window_class_name[256]={0};
        GetClassNameA(hwnd, window_class_name, sizeof(window_class_name));//获取窗口类名

        //筛选所有WorkerW
        if (strcmp(window_class_name,"WorkerW")!=0)
            return TRUE;

        if (IsWindowVisible(hwnd)){ //ps 有多个workerw
            HWND window_hwnd = FindWindowExA(hwnd, 0, "SHELLDLL_DefView", nullptr);
            if (window_hwnd != nullptr){
                UnderE::SHELLDLL = FindWindowExA(window_hwnd, 0, "SysListView32", nullptr);
                return TRUE;
            }else{
                //筛选出 可见的WorkerW 并且没有 shelldll子窗口的WorkerW
                UnderE::MiddleW = hwnd;
                if (UnderE::SHELLDLL==nullptr)
                    //如果找不到SHELLDLL就再找找
                    return TRUE;
                else
                    return FALSE;
            }
        }
        return TRUE;
    }
    bool UnderE::refresh(){
        ShowWindow(UnderE::MiddleW,SW_HIDE);
        ShowWindow(UnderE::MiddleW,SW_SHOW);
        return true;
    }

    bool Effect::blur(HWND handle,
                      ACCENT_STATE state,
                      uint32_t color,
                      uint32_t show,
                      uint32_t unknow){
        HMODULE hUser = GetModuleHandle(L"user32.dll");
        if (hUser)
        {
            pfnSetWindowCompositionAttribute
                    setWindowCompositionAttribute =
                (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
            if (setWindowCompositionAttribute)
            {
                ACCENT_POLICY accent = { state, show,color,unknow };
                WINDOWCOMPOSITIONATTRIBDATA data;
                data.Attrib = WCA_ACCENT_POLICY;
                data.pvData = &accent;
                data.cbData = sizeof(accent);
                setWindowCompositionAttribute(handle, &data);
            }
            return false;
        }
        return false;
    }

}

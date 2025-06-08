#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <ctime>
#include <xdl.h>
#include <android/log.h>
#include <sys/system_properties.h>
#include <sys/sysinfo.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "Struct/Gui.hpp"
#include "Struct/main.h"
#include "Icon/Font.h"
#include "ImGui/Toggle.h"
#include "zygisk.hpp"
#include "Chams.h"
#include <dlfcn.h>
#include "Unity/Il2cpp.h"
#include <pthread.h>
#include <unistd.h>
#include <inttypes.h> // Untuk PRIxPTR
#include <thread>
#include "KittyMemory/MemoryPatch.h"
#include <unistd.h>
int tabb = 0;
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h> // Untuk sleep()
#include <sys/ptrace.h>
#include <unistd.h>
#include <string.h>
#include <asm/unistd.h>
#include <sys/syscall.h>
#include "curl/json.hpp"
#include "Jni_Stuff.h"
#include "Unity/Tools.h"
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdio>
#endif

#define targetLib "libil2cpp.so"


uintptr_t G_IL2CPP;

uintptr_t il2cppMap;
using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;

void hack();

class MyModule : public zygisk::ModuleBase {
 public:
  void onLoad(Api *api, JNIEnv *env) override {
    this->api_ = api;
    this->env_ = env;
    genv = env;
  }
  void preAppSpecialize(AppSpecializeArgs *args) override {
    static constexpr const char *packages[] = {
        "com.dts.freefiremax", "com.dts.freefireth"
    }; // Game Package Names
    const char *process = env_->GetStringUTFChars(args->nice_name, nullptr);
    for (const auto *package: packages) {
      is_game_ = (strcmp(process, package) == 0);
      if (is_game_) {
        break;
      }
    }
    env_->ReleaseStringUTFChars(args->nice_name, process);
  }
  void postAppSpecialize(const AppSpecializeArgs *args) override {
    if (is_game_) {
       genv->GetJavaVM(&jvm);
      std::thread{hack}.detach();
    }
  }
 private:
  Api *api_ = nullptr;
  JNIEnv *env_ = nullptr;
  bool is_game_ = false;
};



std::string getDeviceName() {
    char buffer[128];
    std::string deviceName = "Unknown Device";
    FILE* pipe = popen("getprop ro.product.model", "r");
    if (pipe) {
        if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            deviceName = buffer;
        }
        pclose(pipe);
    }

    return deviceName;
}
std::string getDeviceArchitecture() {
    char buffer[128];
    std::string arch = "Unknown Arch";

    FILE* pipe = popen("getprop ro.product.cpu.abi", "r");
    if (pipe) {
        if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            arch = buffer;
        }
        pclose(pipe);
    }

    return arch;
}

void openTelegramGroup() {
#ifdef _WIN32
    ShellExecuteA(0, "open", "https://t.me/+NcpFJLXEWphjOGRl", 0, 0, SW_SHOWNORMAL);
#else
    system("xdg-open https://t.me/+NcpFJLXEWphjOGRl");
#endif
}




struct My_Patches {
    MemoryPatch Rguest ;
    // etc...
} hexPatches;
static bool resetguest = false;
static bool FixCrash = true;
static bool NoRecoil = false;
//static bool BypassESP = true;
static bool User = true;
float (*old_Recoil)(void *instance);
float _Recoil(void *instance) {
    if (instance != NULL) {
        if (NoRecoil) {
            return -5.0f; // Int Hook Value = 999,999,999
        }
    }
    return old_Recoil(instance);
}


typedef void* (*CreateReportPlayer_t)(int from, uint64_t id, const char* nickName);
CreateReportPlayer_t old_Blacklist;
void* _Blacklist(int from, uint64_t id, const char* nickName) {
    return 0;
}

typedef void (*SetReportData_t)(uint64_t matchId, uint32_t groupId, uint32_t gameMode, uint32_t matchMode);
SetReportData_t old_Blacklist2;
void _Blacklist2(uint64_t matchId, uint32_t groupId, uint32_t gameMode, uint32_t matchMode) {
    return;
}

typedef void* (*get_ReportedPlayerTimeDict_t)();
get_ReportedPlayerTimeDict_t old_Blacklist3;
void* _Blacklist3() {
    return 0;
}

typedef void* (*CreateAddToBlackList_t)(int from, uint64_t id, const char* nickName);
CreateAddToBlackList_t old_Blacklist4;
void* _Blacklist4(int from, uint64_t id, const char* nickName) {
    return 0;
}




typedef bool (*get_CrashlyticsInited_t)();
get_CrashlyticsInited_t old_Bypas;
bool _Bypas() {
    if (FixCrash) {
        return false;
    }

    return old_Bypas();
}



struct System_Byte_array {
    uint8_t data[256];  // Ukuran atau tipe data yang disesuaikan sesuai kebutuhan
};

// Pointer untuk fungsi asli
System_Byte_array* (*orig_GCommon_Checker_DhkJNj_XPEfaiU)();

// Objek valid untuk menghindari blacklist
static System_Byte_array valid_data = {};  // Menggunakan objek statis

System_Byte_array* GCommon_Checker_DhkJNj_XPEfaiU() {
    return &valid_data;  // Mengembalikan pointer ke objek valid
}


void (*orig_DetectAndroidApplications) (void *_this);
void _DetectAndroidApplications(void *_this)
{
      
        return ;
    
}


bool(*orig_FuckRoom) (void *thiz, void *obj, void *clazz);
bool hook_FuckRoom(void *thiz, void *obj, void *clazz)
{
      
        return false;
  }




void (*orig_ffano_B_cT_yz_Eu_xgy_) (monoString * uPoQR_K, monoString * gFTUXOL);
void ffano_B_cT_yz_Eu_xgy_(monoString * uPoQR_K, monoString * gFTUXOL)
{
      
        return ;
    
}

bool (*old_Bypas7)(void *instance);
bool _Bypas7(void *instance) {
    if (instance != NULL) {
        if (FixCrash) {
            return false;
        }
    }
    return old_Bypas7(instance);
}

void (*_COW_GamePlay_h_dIJ____RbxVMMU) (void **teste, void *tqUoxHk);
void COW_GamePlay_h_dIJ____RbxVMMU(void **teste, void *tqUoxHk)
{
      
    
        return ;
    
}

bool (*old_Bypas8)(void *instance);
bool _Bypas8(void *instance) {
    if (instance != NULL) {
        if (FixCrash) {
            return false;
        }
    }
    return old_Bypas8(instance);
}

/*

typedef void (*SetGraphicsQuality_t)(void* AOENOBEDJAJ);
SetGraphicsQuality_t old_Bypasesp;
void _Bypasesp(void* AOENOBEDJAJ) {
    if (BypassESP) {
        return;
    }
    old_Bypasesp(AOENOBEDJAJ);
}


int (*old_Bypasesp2)(void *instance);
int _Bypasesp2(void *instance) {
    if (instance != NULL) {
        if (BypassESP) {
            return 3; // Int Hook Value = 999,999,999
        }
    }
    return old_Bypasesp2(instance);
}



// Tambahkan typedef agar tidak error
typedef int Int32;
typedef void Player;

// get_Owner Hook
typedef Player* (*get_Owner_t)();
get_Owner_t old_Bypasuser;


Player* _Bypasuser() {
    Player* owner = old_Bypasuser();

    if (User) {
        return nullptr;
    }

    return owner;
}

// setUserInfo Hook
typedef Int32 (*setUserInfo_t)(const char* roleName, const char* roleAccount, const char* roleId);
setUserInfo_t old_Bypasuser2;

Int32 _Bypasuser2(const char* roleName, const char* roleAccount, const char* roleId) {
    if (User) {
        return 0;
    }

    return old_Bypasuser2(roleName, roleAccount, roleId);
}
*/
bool (*old_Bypasuser3)(void *instance);
bool _Bypasuser3(void *instance) {
    if (instance != NULL) {
        if (User) {
            return false; // Int Hook Value = 999,999,999
        }
    }
    return old_Bypasuser3(instance);
}

bool (*old_Bypasuser4)(void *instance);
bool _Bypasuser4(void *instance) {
    if (instance != NULL) {
        if (User) {
            return false; // Int Hook Value = 999,999,999
        }
    }
    return old_Bypasuser4(instance);
}

bool (*old_Bypasuser5)(void *instance);
bool _Bypasuser5(void *instance) {
    if (instance != NULL) {
        if (User) {
            return false; // Int Hook Value = 999,999,999
        }
    }
    return old_Bypasuser5(instance);
}

bool (*old_Bypasuser6)(void *instance);
bool _Bypasuser6(void *instance) {
    if (instance != NULL) {
        if (User) {
            return true; // Int Hook Value = 999,999,999
        }
    }
    return old_Bypasuser6(instance);
}

bool(*Prazall)(void* _this);
bool _Prazal(void* _this) {
      
        return 0;
    
}
    

void(*Bypass)(void* _this);
void _Bypass(void* _this){
    
        return ;
    
}

bool(*BypassESP)(void* _this);
bool _BypassESP(void* _this) {
    
    return true;
}
bool(*Bypassup)(void* _this);
bool _Bypassup(void* _this)
{ 
    return true;
}

//========BYPASS========\\

void SetDarkGrayTheme()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.01f, 0.01f, 0.01f, 0.40f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.20f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.20f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(1.00f, 0.00f, 0.00f, 1.00f); // Warna merah solid
    colors[ImGuiCol_HeaderHovered]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f); // Warna merah solid
    colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f); // Warna merah solid
    colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImLerp(colors[ImGuiCol_Header],       colors[ImGuiCol_TitleBgActive], 0.80f);
    colors[ImGuiCol_TabHovered]             = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_TabActive]              = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
    colors[ImGuiCol_TabUnfocused]           = ImLerp(colors[ImGuiCol_Tab],          colors[ImGuiCol_TitleBg], 0.80f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImLerp(colors[ImGuiCol_TabActive],    colors[ImGuiCol_TitleBg], 0.40f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

   
    // Mengatur kelengkungan


// Membuat UI lebih melengkung
style->WindowRounding = 10.0f;
style->ChildRounding = 10.0f;
style->FrameRounding = 9.0f;
style->PopupRounding = 9.0f;
//style->ScrollbarRounding = 20.0f;
style->TabRounding = 5.0f;

// Mengatur ukuran Title Bar lebih besar
style->WindowPadding = ImVec2(20.0f, 9.0f); // Tinggikan padding untuk title bar
style->FramePadding = ImVec2(13.0f, 6.0f);  // Membuat elemen lebih besar
style->WindowTitleAlign = ImVec2(0.5f, 0.5f); // Memusatkan teks title

// Menyesuaikan ukuran teks title agar lebih besar


// Opsi tambahan agar UI lebih rapi
style->FrameBorderSize = 1.0f;
style->ScrollbarSize = 15.0f;
style->TabBorderSize = 1.0f;
}


static bool isMenuOpen = false;  // Status menu
static ImVec2 buttonPos = ImVec2(50, 200); // Geser lebih ke kiri & 


// ========================= \\

uintptr_t il2cpp_base = 0;
void *getRealAddr(ulong offset) {
    return reinterpret_cast<void*>(il2cpp_base + offset);
};


bool clearMousePos = true;
bool initImGui = false;

inline EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
inline EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &g_GlWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &g_GlHeight);

    if (!g_IsSetup) {
        prevWidth = g_GlWidth;
        prevHeight = g_GlHeight;
        SetupImgui();
        
        g_IsSetup = true;
    }

    ImGuiIO &io = ImGui::GetIO();
    SetDarkGrayTheme();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);
    ImGui::NewFrame();
    int touchCount = (((int (*)())(Class_Input__get_touchCount))());
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields(*)(int))(Class_Input__GetTouch))(0);
        float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;
        switch (touch.m_Phase) {
            case TouchPhase::Began:
            case TouchPhase::Stationary:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                io.MouseDown[0] = true;
                break;
            case TouchPhase::Ended:
            case TouchPhase::Canceled:
                io.MouseDown[0] = false;
                clearMousePos = true;
                break;
            case TouchPhase::Moved:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                break;
            default:
                break;
        }
    }
 DrawESP(g_GlWidth, g_GlHeight);

ImGui::SetNextWindowSize(ImVec2((float) g_GlWidth * 0.36f, (float) g_GlHeight * 0.60f), ImGuiCond_Once);
if (ImGui::Begin(OBFUSCATE("Zenith Syndicate Free Fire"), 0, ImGuiWindowFlags_NoBringToFrontOnFocus)) {
    static bool isLogin = false, logginIn = false;
static std::string err;
static const char *manualKey = "FREEFIREKEY"; 

if (!isLogin) {
    ImGui::Text(OBFUSCATE("Please Login!"));

    ImGui::PushItemWidth(-1);
    static char s[64];
    strncpy(s, manualKey, sizeof s);
    ImGui::InputText("##key", s, sizeof s, ImGuiInputTextFlags_ReadOnly);
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(-1);
    if (ImGui::Button(OBFUSCATE("Login"), ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
        err = Login(s);
        if (err.find("Key valid!") != std::string::npos) {
            isLogin = true;
        }
    }
    ImGui::PopItemWidth();

    if (!err.empty() && err.find("Key valid!") == std::string::npos) {
        ImGui::Text("Error: %s", err.c_str());
    }

if (ImGui::Button("Telegram Channel", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
        openTelegramGroup();
        }
    ImGui::Text("Device Info:");
    ImGui::BulletText("Model: %s", getDeviceName().c_str());
    ImGui::BulletText("Architecture: %s", getDeviceArchitecture().c_str());  
    ImGui::PopItemWidth();
} else {



ImGui::BeginChild("LeftPanel", ImVec2(400, 550), true);
ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "Esp");
ImGui::Spacing();
ImGui::Checkbox(OBFUSCATE("Show Esp"), &Enable);
ImGui::Checkbox(OBFUSCATE("Esp Line"), &Config.ESP.Line);
ImGui::Checkbox(OBFUSCATE("Esp Box"), &Config.ESP.Box);
ImGui::Checkbox(OBFUSCATE("Esp Health"), &Config.ESP.Health);
ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "Fov Aimbot");
ImGui::SliderFloat(OBFUSCATE("##Fov"), &Fov_Aim, 0.0f, 500.0f, "%.f");
ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "Range Aimbot");
ImGui::SliderFloat(OBFUSCATE("##Range"), &Aimdis, 0.0f, 500.0f, "%.f");
ImGui::EndChild();

// Geser Panel Kanan lebih ke kanan
ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 180); // Geser ke kanan 30px
ImGui::SameLine();

// Panel Kanan
ImGui::BeginChild("RightPanel", ImVec2(400, 550), true);
 ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "Aim");
ImGui::Checkbox("Reset Guest", &resetguest);
if (resetguest) {
    hexPatches.Rguest.Modify();
} else {
    hexPatches.Rguest.Restore();
}
ImGui::Checkbox("No Recoil", &NoRecoil);
ImGui::Checkbox("Aimbot", &Aimbot);
ImGui::TextColored(ImVec4(1.00f, 0.00f, 0.00f, 1.00f), "Aim Target");
ImGui::Combo("##aimTarget", &AimTarget, "Head\0Body\0");
if (ImGui::Checkbox("None", &aimNone)) {
    if (aimNone) {
        aimFire = false;
        aimScope = false;
        AimWhen = 0;
    }
}
if (ImGui::Checkbox("Fire", &aimFire)) {
    if (aimFire) {
        aimNone = false;
        aimScope = false;
        AimWhen = 1;
    }
}
if (ImGui::Checkbox("Scope", &aimScope)) {
    if (aimScope) {
        aimNone = false;
        aimFire = false;
        AimWhen = 2;
    }
ImGui::EndChild(); // End Panel Kanan
ImGui::End(); // End Window Utama
}
 }
 }
   ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return old_eglSwapBuffers(dpy, surface);
}




typedef unsigned long DWORD;
static uintptr_t libBase;


inline void StartGUI() {
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (ptr_eglSwapBuffer != nullptr) {
        DobbyHook((void *)ptr_eglSwapBuffer, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);
        LOGD("GUI started successfully");
    }
}


void hack_thread(pid_t pid) {
   
    for (int i = 0; i < 10; i++) {
        il2cpp_base = get_module_base(pid, "libil2cpp.so");
        if (il2cpp_base != 0) break;
        sleep(5); // Coba tidur sebentar dan cek lagi
    }

    if (il2cpp_base == 0) {
        return; // Jika tidak ditemukan, hentikan thread
    }

while (!il2cppMap) {
        il2cppMap = Tools::GetBaseAddress(targetLib);
        sleep(10);
    }

    LOGI("G_IL2CPP found, attaching...");
Il2CppAttach(targetLib);


    //ResetGuest

    hexPatches.Rguest = MemoryPatch::createWithHex(RstGuest,"200080D2C0035FD6"); 
	DobbyHook((void *) Recoil, (void *) _Recoil, (void **) &old_Recoil);	

	
    DobbyHook((void *) Report1, (void *) _Blacklist, (void **) &old_Blacklist);
    DobbyHook((void *) Report2, (void *) _Blacklist2, (void **) &old_Blacklist2);
    DobbyHook((void *) Report3, (void *) _Blacklist3, (void **) &old_Blacklist3);
    DobbyHook((void *) Report4, (void *) _Blacklist4, (void **) &old_Blacklist4);

    DobbyHook((void *) Bypas, (void *) _Bypas, (void **) &old_Bypas);
    //DobbyHook((void *) Bypas2, (void *) GCommon_Checker_DhkJNj_XPEfaiU, (void **) &orig_GCommon_Checker_DhkJNj_XPEfaiU);
    DobbyHook((void *) Bypas3, (void *) _DetectAndroidApplications, (void **) &orig_DetectAndroidApplications);
    DobbyHook((void *) Bypas4, (void *) hook_FuckRoom, (void **) &orig_FuckRoom);
    DobbyHook((void *) Bypas5, (void *) ffano_B_cT_yz_Eu_xgy_, (void **) &orig_ffano_B_cT_yz_Eu_xgy_);
    DobbyHook((void *) Bypas6, (void *) COW_GamePlay_h_dIJ____RbxVMMU, (void **) &_COW_GamePlay_h_dIJ____RbxVMMU);
    DobbyHook((void *) Bypas7, (void *) _Bypas7, (void **) &old_Bypas7);
    DobbyHook((void *) Bypas8, (void *) _Bypas8, (void **) &old_Bypas8);
   
    DobbyHook((void *) BypasEsp, (void *) _BypassESP, (void **) &BypassESP);
    DobbyHook((void *) BypasEsp2, (void *) _BypassESP, (void **) &BypassESP);
    
    DobbyHook((void *) Bypass, (void *) _Bypass, (void **) &Bypass);
    DobbyHook((void *) Bypass2, (void *) _Bypass, (void **) &Bypass);
    
    DobbyHook((void *) BypasUser3, (void *) _Bypasuser3, (void **) &old_Bypasuser3);
    DobbyHook((void *) BypasUser4, (void *) _Bypasuser4, (void **) &old_Bypasuser4);
    DobbyHook((void *) BypasUser5, (void *) _Bypasuser5, (void **) &old_Bypasuser5);
    DobbyHook((void *) BypasUser6, (void *) _Bypasuser6, (void **) &old_Bypasuser6);
        
    DobbyHook((void *) Prazal, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal2, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal3, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal4, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal5, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal6, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal7, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal8, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal9, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal10, (void *) _Prazal, (void **) &Prazall);
    DobbyHook((void *) Prazal11, (void *) _Prazal, (void **) &Prazall);
 

    DobbyHook((void *) Zesyn2, (void *) _Bypassup, (void **) &Bypassup);
    DobbyHook((void *) Zesyn3, (void *) _Bypassup, (void **) &Bypassup);
    DobbyHook((void *) Zesyn4, (void *) _Bypassup, (void **) &Bypassup);
    DobbyHook((void *) Zesyn5, (void *) _Bypassup, (void **) &Bypassup);
    DobbyHook((void *) Zesyn6, (void *) _Bypassup, (void **) &Bypassup);
    DobbyHook((void *) Zesyn7, (void *) _Bypassup, (void **) &Bypassup);
StartGUI();
}





    
void hack() {
     LOGD("Inject Ok");
    std::thread thread_hack(hack_thread, getpid());
    thread_hack.detach();
    
}

REGISTER_ZYGISK_MODULE(MyModule)


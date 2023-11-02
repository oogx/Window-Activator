#include "Drawing.h"
#include <stdio.h>
#include <string>
LPCSTR Drawing::WindowName = "Window's Activator";
ImVec2 Drawing::WindowSize = { 500, 300 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::UiOpen = true;

BOOL IsRunAsAdministrator() {
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid( &NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup)) {
        dwError = GetLastError();
        goto Cleanup;
    }
    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin)) {
        dwError = GetLastError();
        goto Cleanup;
    }
Cleanup:
    if (pAdministratorsGroup) {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }
    if (ERROR_SUCCESS != dwError) {
        throw dwError;
    }
    return fIsRunAsAdmin;
}
void Drawing::Draw() {
	if ( UiOpen == true ) {
		ImGui::SetNextWindowSize(WindowSize);
        ImGui::Begin(WindowName, &UiOpen, WindowFlags); {
            if (IsRunAsAdministrator() == TRUE) {
                if (ImGui::Button("Activate Windows")) {
                    int WindowsVersion = system("wmic os get Caption");
                    char str[10];
                    sprintf_s(str, "%d", WindowsVersion);
                    std::string windowsstring(str);
                    if (windowsstring.find("pro")) {
                        system("slmgr /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX");
                        system("slmgr /skms kms8.msguides.com");
                        system("slmgr /ato");
                    }
                    else if (windowsstring.find("Home")) {
                        system("slmgr /ipk TX9XD-98N7V-6WMQ6-BX7FG-H8Q99");
                        system("slmgr /skms kms8.msguides.com");
                        system("slmgr /ato");
                    }
                    else if (windowsstring.find("Education")) {
                        system("slmgr /ipk NW6C2-QMPVW-D7KKK-3GKT6-VCFB2");
                        system("slmgr /skms kms8.msguides.com");
                        system("slmgr /ato");
                    }
                    else if (windowsstring.find("Enterprise")) {
                        system("slmgr /ipk NPPR9-FWDCX-D2C8J-H872K-2YT43");
                        system("slmgr /skms kms8.msguides.com");
                        system("slmgr /ato");
                    }
                }
                if (ImGui::Button("Check If It's Successful")) {
                    system("slmgr /xpr");
                }
                ImGui::Text("If the activation is successful");
                ImGui::Text("Reboot your computer");
            }
            else {
                ImGui::Text("Rerun the app with admin permissions");
            }
        };
        ImGui::End();
	}
}
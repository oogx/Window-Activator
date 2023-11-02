#define DRAWING_H
#include <Windows.h>
#include "../../Dependencies/ImGui/imgui.h"
class Drawing {
private:
	static LPCSTR WindowName;
	static ImVec2 WindowSize;
	static ImGuiWindowFlags WindowFlags;
	static bool UiOpen;

public:
	static void Draw();
};
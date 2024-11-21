#include "EColorPickerScreen.h"

EColorPickerScreen::EColorPickerScreen()
{
	isActive = false;
}

void EColorPickerScreen::update()
{
	if (!isActive) return;

	ImGui::Begin("Color Picker");
	if (ImGui::Button("X", ImVec2(20, 20))) {
		isActive = false;
	}
	ImGui::ColorPicker4("Color Picker", colors, 3);

	ImGui::End();
}

EColorPickerScreen::~EColorPickerScreen()
{
}

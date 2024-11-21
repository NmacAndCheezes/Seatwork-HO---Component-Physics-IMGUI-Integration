#include "CreditsScreen.h"


CreditsScreen::CreditsScreen()
{
	img = new ImageUI("./Assets/Textures/dlsu_logo.png");
	isActive = false;

}

void CreditsScreen::update()
{
	if (!isActive) return;
	
	ImGui::Begin("About");

	if (ImGui::Button("X", ImVec2(20, 20))) {
		isActive = false;
	}
	ImGui::Image((ImTextureID)(intptr_t)img->getShaderResourceView(), ImVec2(img->Width(), img->Height()));
	ImGui::Text("This engine was made by Nathan Macabanti\n");
	ImGui::Text("Acknowledgement: In partial requirement of HO - UI Screens\n");
	ImGui::Text("\nver 0.01\n");
	ImGui::End();
}

CreditsScreen::~CreditsScreen()
{
}

#include "menu.h"
#include "server.h" 
#include "imgui.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
#include <Windows.h>

#include "server.h"




void SendPostRequest(const std::string& url, const std::string& json_data) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

void ApplyCustomStyle() {
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    colors[ImGuiCol_Button] = ImVec4(0.96f, 0.81f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.96f, 0.81f, 0.81f, 1.00f);

    colors[ImGuiCol_ButtonHovered] = ImVec4(0.96f, 0.74f, 0.74f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.96f, 0.66f, 0.66f, 1.00f);

    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void ShowMenu() {
    ApplyCustomStyle();

    ImGui::Begin("example host");

    ImVec4 buttonTextColor = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    ImGui::PushStyleColor(ImGuiCol_Text, buttonTextColor);
    if (ImGui::Button("button 1")) {
        SendPostRequest("http://127.0.0.1:5000/update_status", "{\"button\": \"button 1\"}");
    }
    ImGui::PopStyleColor();

    ImGui::PushStyleColor(ImGuiCol_Text, buttonTextColor);
    if (ImGui::Button("button 2")) {
        SendPostRequest("http://127.0.0.1:5000/update_status", "{\"button\": \"button 2\"}");
    }
    ImGui::PopStyleColor();

    ImGui::PushStyleColor(ImGuiCol_Text, buttonTextColor);
    if (ImGui::Button("button 3")) {
        SendPostRequest("http://127.0.0.1:5000/update_status", "{\"button\": \"button 3\"}");
    }
    ImGui::PopStyleColor();

    ImGui::End();
}


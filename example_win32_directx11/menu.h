#pragma once
#include "imgui.h"
#include <string>

// Function declarations
void ShowMenu();
void ApplyCustomStyle();
void SendPostRequest(const std::string& url, const std::string& json_data);
extern void InitializeServerAndBrowser();  // Use extern to declare the function
extern void StartServer();                 // Use extern if needed here as well

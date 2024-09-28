# CrowXImGui

CrowXImGui is a custom framework that integrates an ImGui-based user interface with a WebSocket server using the Crow framework. Allowing a real-time comm between the UI and a web client for dynamic work

## Features
- customizable and interactive user interface using imgui framework.
- real-time communication through WebSocket routes managed by Crow.
- data exchange between server and client using JSON.

## Requirements
- Visual Studio 2019 or later
- C++17 or later
- [Crow](https://github.com/CrowCpp/Crow) (WebSocket library)
- [nlohmann/json](https://github.com/nlohmann/json) (JSON parsing library)
- [ImGui](https://github.com/ocornut/imgui) (for GUI)

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/lztossy/CrowXImGui.git
cd CrowXImGui

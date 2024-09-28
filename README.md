# CrowXImGui

CrowXImGui is a cfw (custom-framework that uses an imgui-based user interface with a websocket server using the crow framework. It provides a real-time comm interface between the UI and a client, allowing dynamic updates

## Requirements
- Visual Studio 2019 or later
- C++17 or later
- [Crow](https://github.com/CrowCpp/Crow) (WebSocket library)
- [nlohmann/json](https://github.com/nlohmann/json) (JSON parsing library)
- [ASIO](https://think-async.com/Asio/) (Standalone ASIO for networking)
- [cURL](https://curl.se/) (For HTTP requests)
- [ImGui](https://github.com/ocornut/imgui) (for GUI)

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/CrowXImGui.git
cd CrowXImGui
```

### 2. Set Up Dependencies
- **Crow**: Download and place `crow_all.h` in the `include` directory.
- **nlohmann/json**: Download and place `json.hpp` in the `include` directory.
- **ASIO**: Download standalone ASIO and place the `asio` directory in the `include` directory.
- **cURL**: Download cURL, and add the `include` and `lib` files to the respective project directories.
- **ImGui**: Download ImGui and add the necessary source and header files to the project.

### 3. Configure Visual Studio
- Include directories:
  ```
  CrowXImGui/include
  ```
- Library directories:
  ```
  CrowXImGui/lib
  ```
- Linker input:
  ```
  curl.lib
  ws2_32.lib
  crypt32.lib
  ```

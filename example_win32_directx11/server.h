#pragma once

#include <string>
#include <mutex>
#include <unordered_set>
#include "../include/crow.h" // Ensure correct path to crow.h

// Declare global variables using extern
extern std::string status_message;
extern std::mutex status_mutex;
extern std::mutex connections_mutex;
extern std::unordered_set<crow::websocket::connection*> active_connections;

// Function declarations
void StartCrowServer();
void BroadcastMessage(const std::string& message);

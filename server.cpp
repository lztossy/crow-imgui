#include "server.h"
#include <iostream>

std::string status_message = "awaiting action";
std::mutex status_mutex;
std::mutex connections_mutex;
std::unordered_set<crow::websocket::connection*> active_connections;

void BroadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(connections_mutex);
    for (auto* conn : active_connections) {
        conn->send_text(message);
    }
}

void StartCrowServer() {
    crow::SimpleApp app;  

    CROW_ROUTE(app, "/")
        ([]() {
        return R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>host</title>
                <style>
                    body {
                        font-family: Arial, sans-serif;
                        background-color: #000;
                        color: #0F0;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        height: 100vh;
                        margin: 0;
                    }
                    #console {
                        background-color: #111;
                        padding: 20px;
                        border: 1px solid #0F0;
                        border-radius: 5px;
                        width: 500px;
                        text-align: center;
                    }
                </style>
            </head>
            <body>
                <div id="console">
                    <h2 id="status">awaiting action</h2>
                </div>
                <script>
                    // Create a new WebSocket connection
                    var socket = new WebSocket('ws://' + window.location.host + '/ws');
                    
                    // Update the status text when receiving a message
                    socket.onmessage = function(event) {
                        var data = JSON.parse(event.data);
                        document.getElementById('status').textContent = data.status_message;
                    };
                </script>
            </body>
            </html>
        )";
            });

    CROW_ROUTE(app, "/update_status").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req) {
        auto json_body = crow::json::load(req.body);
        if (!json_body) {
            return crow::response(400, "Invalid JSON");
        }

        std::string button = json_body["button"].s();
        std::string new_status = "status 100: received " + button;

        {
            std::lock_guard<std::mutex> lock(status_mutex);
            status_message = new_status;
        }

        BroadcastMessage(crow::json::wvalue({ {"status_message", new_status} }).dump());

        crow::json::wvalue response;
        response["message"] = "Status updated successfully";

        return crow::response(200, response);
            });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onaccept([](const crow::request& req, void** userdata) {
        std::cout << "WebSocket connection request accepted.\n";
        return true;
            })
        .onopen([&](crow::websocket::connection& conn) {
        std::cout << "WebSocket connected\n";
        {
            std::lock_guard<std::mutex> lock(connections_mutex);
            active_connections.insert(&conn);
        }
            })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t code) {
        std::cout << "WebSocket closed: " << reason << " with code " << code << "\n";
        {
            std::lock_guard<std::mutex> lock(connections_mutex);
            active_connections.erase(&conn);
        }
            })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
        if (is_binary) {
            std::cout << "Received binary message\n";
        }
        else {
            std::cout << "Received text message: " << data << "\n";
        }
            })
        .onerror([&](crow::websocket::connection& conn, const std::string& error_message) {
        std::cerr << "WebSocket error: " << error_message << "\n";
            });

    app.port(5000).multithreaded().run();
}

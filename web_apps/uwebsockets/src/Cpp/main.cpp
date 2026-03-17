#include "Link.h"
#include "Logic.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // 1. Instantiate the Link as a shared_ptr
    auto myLink = std::make_shared<Link>();

    // 2. Start the connection process
    std::cout << "[Main] Starting Link..." << std::endl;
    myLink->start("wss://xrplcluster.com");

    int messageCount = 0;
    bool connected = false;

    // 3. Main event loop
    while (!myLink->is_stopped()) {
        // Drive the io_context to process async operations
        myLink->poll();

        std::string msg;
        // Process all available messages from the queue
        while (myLink->messageQueue.try_pop(msg)) {
            if (msg == "CONNECTED") {
                if (!connected) {
                    connected = true;
                    std::cout << "[Main] Connection successful! Subscribing..." << std::endl;
                    myLink->sendmsg(R"({"command": "server_info"})");
                }
            } else if (msg == "STOP") {
                // The stop message is now just a signal to break the outer loop
                goto end_loop; // break out of both loops
            } else {
                messageCount++;
                auto j = nlohmann::json::parse(msg);
                if (j.contains("error")) {
                    std::cout << "[Message] " << msg << "\n" << std::endl;
                }
                
                std::cout << "[Main] Message Count: " << messageCount << " (Queue Size: " << myLink->messageQueue.size() << ")" << std::endl;
            }
        }
        
        // Prevent busy-waiting and give the CPU a break
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

end_loop:;
    if (connected) {
        std::cout << "[Main] Final message count: " << messageCount << std::endl;
    } else {
        std::cerr << "[Main] Connection failed to establish." << std::endl;
    }
    
    std::cout << "[Main] Exiting." << std::endl;
    return 0;
}

#include "FaultHandler.hpp"
#include <iostream>
#include <thread>

int main() {
    // Get the singleton instance of FaultHandler
    FaultHandler* faultHandler = FaultHandler::instance();

    // Ensure necessary folders and files are created
    faultHandler->FoldercheckAndFileCreate();

    // Simulate storing DTCs for different modules
    faultHandler->store_dtc_with_counter("DTC001", "RADAR", "SensorFailure", "Radar sensor not responding");
    faultHandler->store_dtc_with_counter("DTC002", "CAMERA", "CalibrationError", "Camera misaligned");
    faultHandler->store_dtc_with_counter("DTC003", "ETHERNET", "ConnectionLost", "Ethernet link dropped");

    // Simulate handling a DTC event
    faultHandler->handle_dtc_event("DTC001", "RADAR");

    // Log DTCs to a file
    faultHandler->log_dtc_to_file("RADAR");
    faultHandler->log_dtc_to_file("CAMERA");

    // Load DTCs from a file (if applicable)
    faultHandler->load_dtc_from_file();

    std::cout << "FaultHandler simulation completed." << std::endl;

    return 0;
}

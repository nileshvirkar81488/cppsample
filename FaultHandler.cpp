#include "FaultHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

// Static member definition
FaultHandler* FaultHandler::m_faultinstance = nullptr;

FaultHandler* FaultHandler::instance() {
    if (m_faultinstance == nullptr) {
        m_faultinstance = new FaultHandler();
    }
    return m_faultinstance;
}

FaultHandler::FaultHandler() {
    std::cout << "FaultHandler initialized" << std::endl;
}

void FaultHandler::store_dtc_with_counter(const std::string& dtc_id, const std::string& module_name, 
                                        const std::string& fault_type, const std::string& description) {
    std::lock_guard<std::mutex> lock(dtc_mutex);
    
    // Check if DTC already exists
    auto it = std::find_if(dtc_list.begin(), dtc_list.end(), 
                          [&dtc_id](const DTCEntry& entry) { return entry.dtc_id == dtc_id; });
    
    if (it != dtc_list.end()) {
        // Update existing DTC
        it->last_occurrence = std::time(nullptr);
        it->event_counter++;
        it->active = true;
    } else {
        // Create new DTC entry
        DTCEntry entry;
        entry.dtc_id = dtc_id;
        entry.fault_type = fault_type;
        entry.description = description;
        entry.first_occurrence = std::time(nullptr);
        entry.last_occurrence = std::time(nullptr);
        entry.event_counter = 1;
        entry.active = true;
        
        dtc_list.push_back(entry);
    }
    
    std::cout << "Stored DTC: " << dtc_id << " for module: " << module_name << std::endl;
}

void FaultHandler::log_dtc_to_file(const std::string& module_name) {
    std::lock_guard<std::mutex> lock(dtc_mutex);
    
    std::string filename = "dtc_log_" + module_name + ".txt";
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        for (const auto& entry : dtc_list) {
            file << "DTC ID: " << entry.dtc_id 
                 << ", Type: " << entry.fault_type
                 << ", Description: " << entry.description
                 << ", Count: " << entry.event_counter
                 << ", Active: " << (entry.active ? "Yes" : "No") << std::endl;
        }
        file.close();
        std::cout << "Logged DTCs to file: " << filename << std::endl;
    }
}

void FaultHandler::load_dtc_from_file() {
    std::cout << "Loading DTCs from file..." << std::endl;
    // Implementation for loading DTCs from file
    // This is a stub implementation
}

void FaultHandler::FoldercheckAndFileCreate() {
    // Create necessary directories for logging
    std::filesystem::create_directories("logs");
    std::cout << "Checked and created necessary folders" << std::endl;
}

void FaultHandler::handle_dtc_event(const std::string& dtc_id, const std::string& module_name) {
    std::cout << "Handling DTC event: " << dtc_id << " for module: " << module_name << std::endl;
    
    if (module_name == "RADAR") {
        radar_error_handler(dtc_id);
    } else if (module_name == "CAMERA") {
        camera_error_handler(dtc_id);
    } else if (module_name == "CAN") {
        CAN_error_handler(dtc_id);
    } else if (module_name == "ETHERNET") {
        ETH_error_handler(dtc_id);
    }
}

void FaultHandler::radar_error_handler(const std::string& dtc_id) {
    std::cout << "Radar error handler called for DTC: " << dtc_id << std::endl;
}

void FaultHandler::camera_error_handler(const std::string& dtc_id) {
    std::cout << "Camera error handler called for DTC: " << dtc_id << std::endl;
}

void FaultHandler::CAN_error_handler(const std::string& dtc_id) {
    std::cout << "CAN error handler called for DTC: " << dtc_id << std::endl;
}

void FaultHandler::ETH_error_handler(const std::string& dtc_id) {
    std::cout << "Ethernet error handler called for DTC: " << dtc_id << std::endl;
}

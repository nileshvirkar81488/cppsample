/**
 * @class FaultHandler
 * @brief The FaultHandler class manages diagnostic trouble codes (DTCs) and system fault handling.
 * 
 * This class is responsible for detecting, logging, and managing faults for different system components 
 * such as radar, cameras, and LiDAR. It maintains a list of detected DTCs, tracks their occurrences, 
 * and ensures persistent logging for analysis.
 * 
 * The class follows a Singleton design pattern to ensure that only one instance of FaultHandler 
 * exists throughout the system.
 * 
 * Features:
 * - Stores and logs DTCs with event counters.
 * - Loads and persists fault data to a log file.
 * - Handles error events for different sensor modules.
 * - Ensures thread-safe operations using mutex locks.
 * 
 * @date 25-Mar-2025
 * @author Eduri Lavanya, Srivathsan P
 */

#ifndef FAULTHANDLER_HPP
#define FAULTHANDLER_HPP
 
#include <vector>
#include <string>
#include <ctime>
#include <atomic>
#include <unordered_map>
#include <mutex>

#include <ctime>

#include <chrono>

#include <iomanip>
#include <filesystem>
#include "common/Declarations.hpp"
 
struct DTCEntry {

    std::string dtc_id;

    std::string fault_type;

    std::string description;

    std::time_t first_occurrence;

    std::time_t last_occurrence;

    int event_counter;

    bool active;
    

};
 
class FaultHandler {

public:

    // Delete copy constructor & assignment operator to prevent duplication
    FaultHandler(const FaultHandler&) = delete;
    FaultHandler& operator=(const FaultHandler&) = delete;

    static FaultHandler *instance();
    static FaultHandler* m_faultinstance;
 
    

    FaultHandler();

    void store_dtc_with_counter(const std::string& dtc_id, const std::string& module_name, const std::string& fault_type, const std::string& description);

    void log_dtc_to_file(const std::string& module_name);

    void load_dtc_from_file();

    void FoldercheckAndFileCreate();

    void handle_dtc_event(const std::string& dtc_id, const std::string& module_name);
 
private:

    std::vector<DTCEntry> dtc_list;
    std::unordered_map<std::string, int> dtc_log_occurrences;


    std::unordered_map<std::string, int> dtc_counters;
    std::mutex dtc_mutex;

    std::mutex mtx;
 
    void radar_error_handler(const std::string& dtc_id);

    void camera_error_handler(const std::string& dtc_id);
    void CAN_error_handler(const std::string& dtc_id);
    void ETH_error_handler(const std::string& dtc_id);

    const std::string cam_mod_name = "CAMERA";

};
 
#endif // FAULTHANDLER_HPP

 

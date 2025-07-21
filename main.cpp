#include <iostream>
#include <string>
#include "auth.hpp"
#include "json.hpp"
#include <curl/curl.h>
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void login() {
    std::string username, password;
    std::cout << "\n=== Login ===\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    // Prepare JSON POST data
    json post_data = {
        {"name", username},
        {"pass", password},
        {"hwid", "S-1-5-21-2072451449-1836442460-3661576764-1001"},
        {"projectsecretid", "737a0a50fb7a4451ec5f476e3e571113"},
        {"userid", "687bb018225ff98025e361d1"},
        {"special_token", "ad8985011eef8f0f1470b8a76af85cecd9d439859961d77808b32673e09325ae"},
        {"type", "login"}
    };

    CURL* curl = curl_easy_init();
    std::string readBuffer;
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, "https://mclxkey.vercel.app/api"); // Replace with your actual URL
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        if (res != CURLE_OK) {
            std::cout << "\nLogin request failed: " << curl_easy_strerror(res) << std::endl;
            return;
        }
    } else {
        std::cout << "\nFailed to initialize cURL." << std::endl;
        return;
    }

    // Parse server response
    json j = json::parse(readBuffer);
    MCLXKeyAuth::AuthResponse result;
    result.success = j["success"].get<bool>();
    if (result.success) {
        result.message = "Login successful";
        result.user.id = j["user"]["id"].get<std::string>();
        result.user.name = j["user"]["name"].get<std::string>();
        result.user.username = j["user"]["username"].get<std::string>();
        result.user.expireDate = j["user"]["expireDate"].get<std::string>();
        std::cout << "\nLogin successful!\n";
        std::cout << "User Info:" << std::endl;
        std::cout << "  ID: " << result.user.id << std::endl;
        std::cout << "  Name: " << result.user.name << std::endl;
        std::cout << "  Username: " << result.user.username << std::endl;
        std::cout << "  Expire Date: " << result.user.expireDate << std::endl;
    } else {
        if (j.contains("message")) {
            result.message = j["message"].get<std::string>();
            std::cout << "\nLogin failed: " << result.message << std::endl;
        } else {
            std::cout << "\nLogin failed." << std::endl;
        }
    }
}

void signup() {
    std::cout << "\n=== Sign Up ===\n";
    std::cout << "Sign up functionality is not implemented yet." << std::endl;
}

int main() {
    while (true) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Login\n2. Sign Up\n0. Exit\nChoose option: ";
        std::string option;
        std::getline(std::cin, option);
        if (option == "1") {
            login();
        } else if (option == "2") {
            signup();
        } else if (option == "0") {
            break;
        } else {
            std::cout << "Invalid option. Try again." << std::endl;
        }
    }
    return 0;
}

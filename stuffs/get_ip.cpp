#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <cstdio>
using namespace std;

std::string get_ip() {
    std::array<char, 128> buffer;
    std::string result;
    // Dùng lệnh shell để lấy IP
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("hostname -I | awk '{print $1}'", "r"), pclose);
    if (!pipe) return "No IP";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    // loại bỏ ký tự newline
    if (!result.empty() && result.back() == '\n') result.pop_back();
    return result;
}

int main(){
    cout << get_ip();
}

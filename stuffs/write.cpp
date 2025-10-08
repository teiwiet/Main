#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <csignal>
#include <cstdlib>

using namespace std;

void write_backlight(int value) {
    ofstream out("/sys/class/backlight/intel_backlight/bl_power");
    if (!out.is_open()) {
        cerr << "Không thể mở file backlight! Hãy chạy với quyền root.\n";
        exit(1);
    }
    out << value;
    out.close();
}

void cleanup(int sig) {
    cout << "\nNhận tín hiệu " << sig << ", bật lại màn hình...\n";
    write_backlight(0); // 0 = bật sáng
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);   // Ctrl + C
    signal(SIGTERM, cleanup);  // kill
    signal(SIGHUP, cleanup);   // terminal đóng

    cout << "Chương trình đang chạy nền... (Ctrl+C để dừng)\n";

    while (true) {
        write_backlight(1); // 1 = tắt màn hình
        cout << "Đã tắt màn hình, chờ 10 giây...\n";
        this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}


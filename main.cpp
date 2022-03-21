#include <iostream>
#include <thread>
#include <mutex>

// Синхронизация

// Происходит обращение к общему ресурсу
// => поведение не определено
// Неопределённое поведение -- это плохо.

// Примитивы сихронизации решают эту проблему.

std::mutex sign;

void print_word(const std::string& word) {
    std::lock_guard guard(sign);
    std::cout << "The" << ' ' << "word" << ' ' <<
        "is" << ' ' << word << '!' << std::endl;
}

int main() {
    std::thread other(print_word, "OTHER");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    print_word("MAIN");
    other.join();
    return 0;
}

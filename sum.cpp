#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>

std::mutex mutex;
std::mutex cout_mutex;

void add_n_times(int& sum, int amount) {

    for(auto i = 0; i < amount; i++) {
        mutex.lock();
        sum += 1; // Защищённый мьютексом код (т.е. всегда выполняющийся
                  // последовательно
        mutex.unlock();
    }

}

void add_n_times_alternative(int& sum, int amount) {
    for(auto i = 0; i < amount; i++) {
        // RAII
        auto one = std::sin(i) * std::sin(i) +
                std::cos(i) * std::cos(i);
        {
            std::lock_guard cout_guard(cout_mutex);
            std::cout << i << ": " << one << std::endl;
        }
        {
            std::lock_guard guard(mutex);
            sum += one;
        }
    }
}




int main() {
    int sum = 0;
    const int amount = 10;
    std::thread other(add_n_times_alternative, std::ref(sum), amount);
    add_n_times_alternative(sum, amount);
    other.join();
    std::cout << sum << "==" << 2 * amount << std::endl;
}
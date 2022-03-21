#include <thread>
#include <iostream>
#include <atomic>

// Операция называется атомарной, если на уровне
// процессора она выполняется за 1 действие

// Переменная называется атомарной, если
// операции с ней являются атомарными.

// на самом деле машинной атомарности достичь нельзя,
// но всё равно другие потоки вмешаться в выполнение
// этих операций не могут.

void add_n_times(std::atomic<int>& sum, int amount) {
    for(auto i = 0; i < amount; i++) {
        sum += 1;
    }
}

int main() {
    std::atomic<int> sum = 0;
    const int amount = 300000;
    std::thread other(add_n_times, std::ref(sum), amount);
    add_n_times(sum, amount);
    other.join();
    std::cout << sum << " == " << 2 * amount;
}
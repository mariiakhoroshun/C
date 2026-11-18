#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stdexcept>
#include <cmath>

namespace task19_1 {

struct Customer {
    int id;
    double arrival_time;
    double service_time;
};

struct SimulationResult {
    std::vector<double> wait_times;
    int min_service_customer;
    int max_wait_customer;
};

SimulationResult simulate_queue(const std::vector<double>& service_times) {
    if (service_times.empty()) {
        throw std::invalid_argument("Number of customers must be positive");
    }

    int n = static_cast<int>(service_times.size());
    std::queue<Customer> line;

    for (int i = 0; i < n; ++i) {
        if (service_times[i] < 0.0) {
            throw std::invalid_argument("Service time cannot be negative");
        }
        Customer c;
        c.id = i + 1;
        c.arrival_time = static_cast<double>(i);
        c.service_time = service_times[i];
        line.push(c);
    }

    SimulationResult result;
    result.wait_times.reserve(n);
    result.min_service_customer = 1;
    result.max_wait_customer = 1;

    double seller_free_time = 0.0;
    double min_service = service_times[0];
    double max_wait = -1.0;

    while (!line.empty()) {
        Customer current = line.front();
        line.pop();

        double start_service = (seller_free_time > current.arrival_time)
            ? seller_free_time
            : current.arrival_time;
        double wait_time = start_service - current.arrival_time;
        seller_free_time = start_service + current.service_time;

        result.wait_times.push_back(wait_time);

        if (current.service_time < min_service) {
            min_service = current.service_time;
            result.min_service_customer = current.id;
        }
        if (wait_time > max_wait) {
            max_wait = wait_time;
            result.max_wait_customer = current.id;
        }
    }

    return result;
}

void print_result(const SimulationResult& result) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Time spent in queue (c_1 .. c_n): [";
    for (std::size_t i = 0; i < result.wait_times.size(); ++i) {
        std::cout << result.wait_times[i];
        if (i + 1 < result.wait_times.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    std::cout << "Customer with minimum service time: #" << result.min_service_customer << std::endl;
    std::cout << "Customer with maximum time in queue: #" << result.max_wait_customer << std::endl;
}

}

void test_queue_simulation() {
    std::vector<double> s1 = {3.0, 2.0, 4.0};
    task19_1::SimulationResult r1 = task19_1::simulate_queue(s1);
    bool t1 = (r1.wait_times.size() == 3 &&
               std::fabs(r1.wait_times[0] - 0.0) < 1e-9 &&
               std::fabs(r1.wait_times[1] - 2.0) < 1e-9 &&
               std::fabs(r1.wait_times[2] - 3.0) < 1e-9 &&
               r1.min_service_customer == 2 &&
               r1.max_wait_customer == 3);

    std::vector<double> s2 = {0.5, 0.5, 2.0};
    task19_1::SimulationResult r2 = task19_1::simulate_queue(s2);
    bool t2 = (r2.wait_times.size() == 3 &&
               std::fabs(r2.wait_times[0] - 0.0) < 1e-9 &&
               std::fabs(r2.wait_times[1] - 0.0) < 1e-9 &&
               std::fabs(r2.wait_times[2] - 0.0) < 1e-9 &&
               r2.min_service_customer == 1 &&
               r2.max_wait_customer == 1);

    std::vector<double> s3 = {2.5, 0.5, 0.5, 3.0};
    task19_1::SimulationResult r3 = task19_1::simulate_queue(s3);
    bool t3 = (r3.wait_times.size() == 4 &&
               std::fabs(r3.wait_times[0] - 0.0) < 1e-9 &&
               std::fabs(r3.wait_times[1] - 1.5) < 1e-9 &&
               std::fabs(r3.wait_times[2] - 1.0) < 1e-9 &&
               std::fabs(r3.wait_times[3] - 0.5) < 1e-9 &&
               r3.min_service_customer == 2 &&
               r3.max_wait_customer == 2);

    std::vector<double> s4 = {4.2};
    task19_1::SimulationResult r4 = task19_1::simulate_queue(s4);
    bool t4 = (r4.wait_times.size() == 1 &&
               std::fabs(r4.wait_times[0] - 0.0) < 1e-9 &&
               r4.min_service_customer == 1 &&
               r4.max_wait_customer == 1);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (continuous queue): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (no waiting time): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (mixed busy and idle seller): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (single customer): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_queue_simulation();

    int n = 0;
    std::cout << "Enter number of customers n: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid number of customers." << std::endl;
        return 1;
    }

    std::vector<double> service_times(n);
    std::cout << "Enter service times t_1 .. t_n in minutes (e.g. 2.5 0.5 0.5 3.0): ";
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> service_times[i]) || service_times[i] < 0.0) {
            std::cout << "Invalid service time." << std::endl;
            return 1;
        }
    }

    try {
        task19_1::SimulationResult result = task19_1::simulate_queue(service_times);
        task19_1::print_result(result);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
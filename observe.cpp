#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

class Observer
{
public:
    Observer(){};
    virtual ~Observer(){};
    virtual void update()=0;
};

class ObserverA: public Observer {
public:
    ObserverA(){};
    ~ObserverA(){};
    void update() {
        std::cout << "ObserverA notified!\n";
    }
};

class ObserverB: public Observer {
public:
    ObserverB(){};
    ~ObserverB(){};
    void update() {
        std::cout << "ObserverB notified!\n";
    }
};

class Timer {

private:
    std::vector<Observer*> observers;
    bool running;
    std::mutex mutex;

public:
    Timer() : running(false) {}

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void start(int interval) {
        if (running) {
            std::cout << "Timer is already running.\n";
            return;
        }

        running = true;
        std::thread([this, interval]() {
            while (running) {

                auto start1 = std::chrono::high_resolution_clock::now();

                std::this_thread::sleep_for(std::chrono::milliseconds(interval));

                std::lock_guard<std::mutex> lock(mutex);
                for (const auto& observer : observers)
                    observer->update();
                
                auto end1 = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
                std::cout << "Actual wait: " << duration.count() << " ms" << std::endl;

            }
        }).detach();
    }

    void stop() {
        running = false;
    }
};

int main() {
    Timer timer;

    Observer* obs1= new ObserverA();
    Observer* obs2= new ObserverB();

    timer.addObserver(obs1);
    timer.addObserver(obs2);

    timer.start(1000);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    timer.stop();

    return 0;
}

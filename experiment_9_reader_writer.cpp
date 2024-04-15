#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class ReadersWriters {
private:
    mutex mtx;
    int readers_count;

public:
    ReadersWriters() : readers_count(0) {}

    void start_read() {
        mtx.lock();
        readers_count++;
        if (readers_count == 1) {
            // First reader, lock the resource
            cout << "Resource locked for reading" << endl;
        }
        mtx.unlock();

        // Reading the shared resource
        cout << "Reader is reading" << endl;

        mtx.lock();
        readers_count--;
        if (readers_count == 0) {
            // Last reader, unlock the resource
            cout << "Resource unlocked" << endl;
        }
        mtx.unlock();
    }

    void start_write() {
        mtx.lock();
        // Lock the resource for writing
        cout << "Resource locked for writing" << endl;
        // Simulating writing by delaying
        this_thread::sleep_for(chrono::milliseconds(1000));
        // Unlock the resource after writing
        cout << "Resource unlocked" << endl;
        mtx.unlock();
    }
};

void reader_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Reading
        rw.start_read();
        // Simulating some delay for reading
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void writer_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Writing
        rw.start_write();
        // Simulating some delay for writing
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    ReadersWriters rw;

    // Creating reader threads
    thread readers[2];
    for (int i = 0; i < 2; ++i) {
        readers[i] = thread(reader_thread, ref(rw), i);
    }

    // Creating writer threads
    thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer_thread, ref(rw), i);
    }

    // Joining reader threads
    for (int i = 0; i < 2; ++i) {
        readers[i].join();
    }

    // Joining writer threads
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}

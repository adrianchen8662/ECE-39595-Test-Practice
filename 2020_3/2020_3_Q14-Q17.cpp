#include <thread>
#include <mutex>
#include <lock_guard>
#include <iostream>

const int MAXTHREADS = 2;
std::mutex m2;
int globalCount = 0;
std::thread* threads[MAXTHREADS];

void run1(int iters) {
    for (int i = 0; i < iters; i++) {
        std::lock_guard<std::mutex> lk(m2);
        int j = globalCount;
        usleep(10);
        globalCount = j+1;
    }
}

void run2(int iters) {
    std::mutex m1;
    for (int i = 0; i < iters; i++) {
        std::lock_guard<std::mutex> lk(m1);
        int j = globalCount;
        usleep(10);
        globalCount = j+1;
    }
}

void run3(int iters) {
    for (int i = 0; i < iters; i++) {
        int j = globalCount;
        usleep(10);
        globalCount = j+1;
    }
}

void joinAndReset(int run) {
    for (int threadNum = 0;
        threadNum < MAXTHREADS;
        threadNum++) {
        threads[threadNum]->join( );
    }
    std::cout << "run" << run << ": ";
    st d::cout << globalCount << std::endl;
    globalCount = 0;
}

int main(int argc, char *argv[]) {
    int numIters = 1000;

    for (int threadNum = 0; threadNum < MAXTHREADS;
            threadNum++) {
        threads[threadNum] = new std::thread(run1, numIters);
    }
    joinAndReset(1); // S1
    
    for (int threadNum = 0; threadNum < MAXTHREADS;
            threadNum++) {
        threads[threadNum] = new std::thread(run2, numIters);
    }
    joinAndReset(2); // S2
    
    for (int threadNum = 0; threadNum < MAXTHREADS;
            threadNum++) {
        threads[threadNum] = new std::thread(run3, numIters);
    }
    joinAndReset(3); // S3
    
    for (int threadNum = 0; threadNum < MAXTHREADS;
            threadNum++) {
        threads[threadNum] = new std::thread(run3, numIters);
    threads[threadNum]->join( );
    }
    std::cout << "run4: " << globalCount << std::endl; // S4
}

// Q14 - When S1 executes, the value of globalCount printed is:
// 2. equal to 2000
/*
    2
    mutex m2 is in global scope, so it protects global count. There is synchronization
*/
// Q15 - When S2 executes, the value of globalCount printed is:
// 3. less than or equal to 2000
/*
    3
    mutex m1 is in local scope which does not protect globalCount. 
*/

// Q16 - When S3 executes, the value of globalCount printed is:
// 3. less than or equal to 2000
/*
    3
    No synchronization
*/

// Q17 - When S4 executes, the value of globalCount printed is:
// 2. equal to 2000 
/*
    2
    Join after each thread to wait
*/
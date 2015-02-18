/**
 * Semaphore example, written in C++ May 4, 2014
 * Compiled on OSX 10.9, using:
 * g++ -std=c++11 semaphore.cpp
 **/

#include <iostream>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
 
std::mutex mtx;             // mutex for critical section
std::condition_variable cv; // condition variable for critical section  
bool ready = false;         // tell threads to run
int current = 0;            // current count

/* Prints the thread id / max number of threads */
void print_num(int num, int max) {
  std::unique_lock<std::mutex> lck(mtx);
  while(num != current || !ready){ cv.wait(lck); }
  current++;
  std::cout << "Thread: ";
  std::cout << num + 1 << " / " << max;
  std::cout << " current count is: ";
  std::cout << current << std::endl;
  
  /* Notify threads to check for their turn */
  cv.notify_all();
}

/* Changes ready to true, and begins the threads printing */
void run(){
  std::unique_lock<std::mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}
 
int main (){

  int threadnum = 15;
  std::thread threads[15];

  /* spawn threadnum threads */
  for (int id = 0; id < threadnum; id++)
    threads[id] = std::thread(print_num, id, threadnum);

  std::cout << "\nRunning " << threadnum;
  std::cout << " in parallel: \n" << std::endl;

  run(); // Run the semaphores

  /* Merge all threads to the main thread */
  for(int id = 0; id < threadnum; id++)
    threads[id].join();

  std::cout << "\nCompleted semaphore example!\n";
  std::cout << std::endl;

  return 0;
}

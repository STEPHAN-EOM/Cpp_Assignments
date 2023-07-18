/**
 * @file assignment5a.cc
 * @brief Skeleton code for 5614 assignment 5 Part 1.
 * @author Chanho Eom
 * @date 16-May-2023
 */

#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include <random>
#include <algorithm>
#include <thread>
#include <future>
#include <atomic>


// You can use this global to make it easy to switch
// const auto policy = std::launch::async;  
const auto policy = std::launch::deferred;   


int main(void)
{
    const int n {50'000'000};
    std::atomic<double> dot_prod {0};  // I used atomic to prevent reordering of code around the timings
    std::random_device rd {};
    std::default_random_engine eng{rd()};
    // Note using std::ref to wrap engine in a referece_wrapper. See Assignment doc
    auto ui = std::bind(std::normal_distribution<>{}, std::ref(eng));

    std::vector<double> v1(n);
    std::vector<double> v2(n);
    std::generate(std::begin(v1), std::end(v1), ui);
    std::generate(std::begin(v2), std::end(v2), ui);

    // You can use this print command to indicate the policy
    // std::cout << "using std::launch::async" << std::endl;
    std::cout << "using std::launch::deferred" << std::endl;

    auto hardware_threads = std::thread::hardware_concurrency();
    std::cout << "Num hardware threads = " << hardware_threads << '\n';
    unsigned available_threads = 3;

    auto partial_dot = [](auto it, auto it2, auto it3){return std::inner_product(it, it2, it3, 0.0);};

    /* --------------------------------Serial version-------------------------------------------------------*/

    auto start = std::chrono::steady_clock::now();
    dot_prod = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0.0);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Dot product (serial). Answer = " << dot_prod << "\nElapsed time : " 
	<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";


    /* ------------------------------ task based --------------------------------------------------------*/
    start = std::chrono::steady_clock::now();

    /* Add code to do spawn three async tasks here. You can use the lamda expression partial_dot from above */
    
    // Vector to store futures for tasks
    std::vector<std::future<double>> futures;

    // Determine the chunk size for each thread
    std::size_t chunk_size = v1.size() / available_threads;
    
    for (unsigned i = 0; i < available_threads; ++i){
        auto it = std::next(std::begin(v1), i * chunk_size);
        auto it2 = std::next(it, chunk_size);
        auto it3 = std::next(std::begin(v2), i * chunk_size);
        
        // Parallel computation using std::async
        futures.push_back(std::async(policy, partial_dot, it, it2, it3));
    }

    double sum = 0;
    for (auto& future : futures){
        // Accumulate the results obtained from the futures
        sum += future.get();
    }
    
    // Assign the final result to the atomic variable
    dot_prod = sum;

    end = std::chrono::steady_clock::now();
    std::cout << "Dot product parallel async: dot_prod = " << dot_prod << "\nElapsed time : "
	<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";

    /* ------------------------------ packaged_tasks --------------------------------------------------------*/


    start = std::chrono::steady_clock::now();

    /*
     * Add code to do spawn three threads to run three packaged tasks here. You can use the lamda expression partial_dot from above 
     * You will need to create the packaged tasks and then move each one into a thread 
     */
  
    std::vector<std::packaged_task<double()>> tasks;        // Vector to store packaged tasks
    std::vector<std::thread> threads;                       // Vector to store threads
    std::vector<std::future<double>> futures_packaged;      // Vector to store futures for packaed tasks

    for (unsigned i = 0; i < available_threads; ++i){
        auto it = std::next(std::begin(v1), i * chunk_size);
        auto it2 = std::next(it, chunk_size);
        auto it3 = std::next(std::begin(v2), i * chunk_size);

        std::packaged_task<double()> task([partial_dot, it, it2, it3]() {
            return partial_dot(it, it2, it3);               // Create a packaged task w/ the partial_dot lambda
        });

        tasks.push_back(std::move(task));                           // Move the task into the vector
        futures_packaged.push_back(tasks.back().get_future());      // Get the future associated w/ the task
        threads.emplace_back(std::move(tasks.back()));              // Move the task into the thread
    }

    sum = 0;
    for (auto& thread : threads) {
        thread.join();          // Wait for all threads to complete              
    }


    for (auto& future : futures_packaged) {
        sum += future.get();    // Accumulate the results obtained from each packaged task
    }
    dot_prod = sum;

    end = std::chrono::steady_clock::now();
    std::cout << "Dot Product parallel threads & packaged task  = " << dot_prod << "\nElapsed time : " 
	<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";

    /* --------------------------------------std::async-------------------------------------*/
    start = std::chrono::steady_clock::now();

    // Vector to store futures for async tasks
    std::vector<std::future<double>> async_futures;

    for (unsigned i = 0; i < available_threads; ++i){
        auto it = std::next(std::begin(v1), i * chunk_size);
        auto it2 = std::next(it, chunk_size);
        auto it3 = std::next(std::begin(v2), i * chunk_size);

        // Create async tasks for each chunk
        async_futures.push_back(std::async(policy, partial_dot, it, it2, it3));     
    }

    sum = 0;
    for (auto& future : async_futures){
        // Accumulate the results obtained from each async task
        sum += future.get();
    }
    dot_prod = sum; 

    end = std::chrono::steady_clock::now();
    std::cout << "Dot product parallel std::async: dot_prod = " << dot_prod << "\nElapsed time : " 
	<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";


    return 0;
}

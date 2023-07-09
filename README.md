------------------------------------------------------------Client-Server Socket Program in C-----------------------------------------------------------------
This repository contains a client-server socket program implemented in C. The program demonstrates various server designs to handle concurrent client requests and compute the factorial of the received number. It also measures metrics such as processing time, CPU utilization, and memory utilization for performance evaluation.

-----Features

1)Client Program

* Sequential Client: Generates 20 requests sequentially. Each request is an integer ranging from 1 to 20. The response received from the server is displayed on the terminal. The connection is closed after 20 requests.
* Concurrent Client: Supports multiple parallel threads for concurrent requests. The number of concurrent client programs can be configured, and each program runs in its own thread.

2)Server Programs

* Sequential Server: Handles client requests sequentially. Opens a new file when the first client connects. For each client request, it computes the factorial of the received number, stores the result along with the client ID (IP address and port number) in the file, and sends the result back to the client. The file is closed when all client connections are closed.
* Concurrent Server with Multiple Processes: Uses the fork system call to achieve concurrency. It can handle multiple client requests simultaneously by creating child processes for each request.
* Concurrent Server with Multiple Threads: Uses pthreads library to handle concurrent client requests. Each request is processed in a separate thread, allowing efficient parallel execution.
* Non-blocking Server:
    -> Using select() System Call: Implements a non-blocking server that can manage up to 10 clients using the select() system call. It efficiently monitors multiple client connections and handles their requests.
    -> Using poll() System Call: Implements a non-blocking server that can manage up to 10 clients using the poll() system call. It provides a scalable solution for handling multiple client connections simultaneously.
    -> Using epoll API: Implements a non-blocking server that can manage up to 10 clients using the epoll API. It leverages the advanced features of epoll for efficient event-driven I/O operations.

3)Metrics Observation

* The program measures the following metrics:
    Time required by the server to process all concurrent client requests.
    Server process's CPU utilization, which can be monitored using the "top" or "htop" command.
    Server process's memory utilization, which can be monitored using the "top" command.


4)Results and Justification

* The obtained results are analyzed and justified based on the performance metrics observed in (3).

  
5) Usage
   * Compile the client and server programs separately using a C compiler such as GCC.
   * Run the server program first, specifying the desired server design (e.g., sequential, concurrent with multiple processes, concurrent with multiple threads, non-blocking using select, poll, or epoll).
   * In separate terminal windows or tabs, run the client program(s) to generate requests. For sequential client, execute it once; for concurrent client, specify the number of parallel threads/clients to run.
   * Observe the program outputs, including response messages, processing time, CPU utilization, and memory utilization.
   * Analyze the results and justify the observed performance metrics.
   

   Note: Make sure to update any necessary IP addresses or port numbers in the source code before running the programs.
   IF YOU HAVE ANY DOUBT AND CONCERT RELATED TO THIS PRPOJECT PING ME AT: mohdshakir02003@gmail.com

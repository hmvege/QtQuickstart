import multiprocessing as mp
import random
import string
import numpy as np
import time


def example1():

    # Define an output queue
    output = mp.Queue()

    # define a example function
    def rand_string(length, output):
        """Generates a random string of numbers, lower- and uppercase chars."""
        rand_str = ''.join(random.choice(
            string.ascii_lowercase
            + string.ascii_uppercase
            + string.digits)
            for i in range(length))
        output.put(rand_str)

    # Setup a list of processes that we want to run
    processes = [mp.Process(target=rand_string, args=(5, output))
                 for x in range(4)]

    # Run processes
    for p in processes:
        p.start()

    # Exit the completed processes
    for p in processes:
        p.join()

    # Get process results from the output queue
    results = [output.get() for p in processes]

    print(results)


def example2():
    # Define an output queue
    output = mp.Queue()

    # define a example function
    def rand_string(length, pos, output):
        """Generates a random string of numbers, lower- and uppercase chars."""
        rand_str = ''.join(random.choice(
            string.ascii_lowercase
            + string.ascii_uppercase
            + string.digits)
            for i in range(length))
        output.put((pos, rand_str))

    # Setup a list of processes that we want to run
    processes = [mp.Process(target=rand_string, args=(5, x, output))
                 for x in range(4)]

    # Run processes
    for p in processes:
        p.start()

    # Exit the completed processes
    for p in processes:
        p.join()

    # Get process results from the output queue
    results = [output.get() for p in processes]

    print(results)


def example3():
    def worker():
        name = mp.current_process().name
        print(name, 'Starting')
        time.sleep(0.5)
        print(name, 'Exiting')

    def my_service():
        name = mp.current_process().name
        print(name, 'Starting')
        time.sleep(0.5)
        print(name, 'Exiting')

    # Running working 1
    worker_1 = mp.Process(name='worker 1', target=worker)
    print("BEFORE: Is worker_1 alive:     ", worker_1.is_alive())

    worker_1.start()
    print("DURING: Is worker_1 alive:     ", worker_1.is_alive())

    worker_1.terminate()
    print("TERMINATED: Is worker_1 alive: ", worker_1.is_alive())

    worker_1.join()
    print("JOINED: Is worker_1 alive:     ", worker_1.is_alive())

    # Running the rest of the workers
    service = mp.Process(name='my_service', target=my_service)
    worker_2 = mp.Process(target=worker)  # use default name
    worker_2.start()
    service.start()
    worker_2.join()
    service.join()

def example4():
    processes = 4

    arr = np.arange(1000)

    global f
    def f(x):
        return (x+1)*2

    with mp.Pool(processes) as p:
        print (p.map(f, arr))

def example5():
    processes = 4

    arr = np.arange(100)

    global f_send
    def f_send(connection):
        connection.send([42, None, "hello"])
        print("Packet sent.")
        connection.close()

    global f_reqv
    def f_reqv(connection):
        res = connection.recv()
        print("Received: ", res)
        connection.close()

    parent_conn, child_conn = mp.Pipe()
    p1 = mp.Process(target=f_send, args=(child_conn,))
    p2 = mp.Process(target=f_reqv, args=(parent_conn,))
    p1.start()
    p2.start()
    # print(parent_conn.recv())   # packet already received
    p1.join()
    p2.join()

def example6():

    global f
    def f(l, i):
        l.acquire() # Locks process
        try:
            print('hello world', i)
        finally:
            l.release()

    lock = mp.Lock()

    for num in range(10):
        mp.Process(target=f, args=(lock, num)).start()



if __name__ == '__main__':
    random.seed(123)
    # example1()
    # example2()
    # example3()
    # example4()
    # example5()
    example6()

import threading

class FibonacciThread(threading.Thread):
    def run(self):
        first_number, second_number = 0, 1
        while first_number <= 10000:
            print("Fibonacci:", a)
            first_number, second_number = second_number, first_number + second_number

class SquareThread(threading.Thread):
    def run(self):
        square_number = 1
        while square_number <= 10000:
            print("Square:", square_number * square_number)
            square_number += 1

class CubeThread(threading.Thread):
    def run(self):
        cube_number = 1
        while cube_number <= 10000:
            print("Cube:", cube_number * cube_number * cube_number)
            cube_number += 1

# Create instances of the threads
fibonacci_thread = FibonacciThread()
square_thread = SquareThread()
cube_thread = CubeThread()

# Start the threads
fibonacci_thread.start()
square_thread.start()
cube_thread.start()

# Wait for the threads to finish
fibonacci_thread.join()
square_thread.join()
cube_thread.join()

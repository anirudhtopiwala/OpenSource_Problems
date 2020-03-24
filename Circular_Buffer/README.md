# Circular Buffer
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview
Here I have my own implementation of [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer). The basic idea is that it behaves as an endless queue. The last element of queue is connected to the first one. It is commonly used in keyboard when there is a lag between key strokes and processing time. This can be observed below:

<p align="center">
<img src="https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Circular_Buffer/assests/Circular_Buffer_Animation.gif">
</p>
Image taken from Google Images.

 **A major difference in my implementation from the above implementation of circular buffer is that when the buffer is full, new elements do not wait for the buffer to become empty again, but overwrite the oldest elements in the buffer.**

I have implemented this by two methods.
* **Using Dequeue STL:** Here I have used dequeue to mimic the characteristics of a circular buffer. The implementation can be found [here](https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Circular_Buffer/src/Circular_Buffer_Deque.cpp).
* **Using Contiguous Container:** Here I have used a fixed size vector to mimic a circular buffer. The implementation can be found [here](https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Circular_Buffer/src/Circular_Buffer.cpp).

The vector implementation is more optimal than using dequeue. This is because when using dequeue, the first and last element of the queue are constantly created and deleted. This has more memory overhead than just overwriting elements which is done in the vector implementation. 

The two main things to keep in mind for vector implementation are:
* To move **ahead** one step in circular queue:   **current_pos = (current_pos + 1) % max_sz**

* To move **behind** one step in circular queue: **current_pos = (current_pos + max_sz -1) % max_sz**

# Queue Simulator for AoI

A simple queue simulator on the basis of [queuing theory](https://www.britannica.com/science/queuing-theory) that calculates the average Age of Information<sup>1</sup> (AoI). It provides the queue disciplines FIFO and PS for a single queue. Customers' arrival and service times are generated from the exponential distribution based on the arrival or service rate respectively.

<sup>1</sup>: Yates et al., "Age of Information: An Introduction and Survey," 2021. Available: https://arxiv.org/pdf/2007.08564

## Usage

The program takes the number of arriving customers as an input argument. If no argument is provided, the default value of 10 million customers is used. The arrival rate is set to 0.5 while the service rate is 1.
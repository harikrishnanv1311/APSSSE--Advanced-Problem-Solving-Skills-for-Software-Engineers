# APSSSE--Advanced-Problem-Solving-Skills-for-Software-Engineers

# A simple C library for integers of arbitrary length (intal).

An intal is a nonnegative integer of arbitrary length, but it is sufficient for your implementation to support up to 1000 decimal digits. The integer is stored as a null-terminated string of ASCII characters. An intal is represented as a string of decimal digits ('0' thru '9') that are stored in the big-endian style. That is, the most significant digit is at the head of the string. An integer 25, for example, is stored in a string s as '2' at s[0], '5' at s[1], and null char at s[2].

## Purpose of this library: 
Unlike Python and other programming languages where you don't have a limit for the size of a variable of a certain type, languages like C do have a limit.
So this library considers these values as a string and performs calculations easily.

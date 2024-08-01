

# Introduction to Cryptology: Generic Attacks on SuffixMAC

## Cryptography Lab Assignment - SuffixMAC smht48

This repository contains the implementation and solutions for the cryptography lab assignment focused on Generic Attacks on SuffixMAC. The lab explores the construction and vulnerabilities of the SuffixMAC, a message authentication code derived from hash functions. Specifically, we implemented the `smht48` MAC function, conducted an exhaustive search for low-weight keys, and explored existential forgery attacks using collisions.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Implementation Details](#implementation-details)
3. [Installation and Compilation](#installation-and-compilation)
4. [Usage](#usage)
5. [Testing](#testing)
6. [Results](#results)

## Project Overview

### SuffixMAC smht48

The SuffixMAC is a method of transforming a hash function into a Message Authentication Code (MAC). The construction uses a hash function `H` to generate a MAC for a message `m` using a key `k`. In this project, we implement a toy version, `smht48`, using the provided toy hash function `ht48`.

**Function Signature:**

```c
void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]);
```

**Inputs:**
- `k`: A 48-bit key stored as an array of 6 bytes.
- `blen`: The byte length of `m`, stored as a 64-bit value.
- `m`: The message to be hashed, with an integral number of bytes.
- `h`: Placeholder for the 48-bit resulting tag, stored as an array of 6 bytes.

## Implementation Details

The project includes the following components:
1. **smht48 Implementation**: The core SuffixMAC function.
2. **Key Recovery (keyrec)**: A function to find a specific key using an exhaustive search.
3. **Collision Search (colsearch)**: A function to find message collisions for the hash function.
4. **Existential Forgery (smht48ef)**: A function demonstrating existential forgery using collisions.

## Installation and Compilation

To compile the project, use the provided Makefile. Ensure that you have a compatible C compiler installed.

### Makefile Usage

- **Build the project:**
  ```sh
  make all
  ```

- **Clean the build:**
  ```sh
  make clean
  ```

- **Run the main program:**
  ```sh
  make run
  ```

- **Test the implementation:**
  ```sh
  make test
  ```

## Usage

After compiling, the executable will be generated in the `bin` directory. You can run the executable to see the outputs of different functions and test cases.

```sh
./bin/crypto_lab
```

## Testing

The project includes several test cases to verify the implementation:
1. **Test Vectors for smht48**: To validate the correctness of the SuffixMAC implementation.
2. **Key Recovery Tests**: To check the performance and accuracy of the key recovery function.
3. **Collision Search and Forgery Tests**: To demonstrate the collision finding and existential forgery capabilities.

## Results

The results of the implementation, including the time taken for key recovery and collision search, as well as the accuracy of the forgery attacks, are documented in the report.



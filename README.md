

# Introduction to Cryptology: Generic Attacks on SuffixMAC

## Overview

This repository contains the implementation and solutions for the cryptography lab assignment focused on Generic Attacks on SuffixMAC. The lab explores the construction and vulnerabilities of the SuffixMAC, a message authentication code derived from hash functions. Specifically, we implemented the `smht48` MAC function, conducted an exhaustive search for low-weight keys, and explored existential forgery attacks using collisions.

## Contents

- **Problem Interpretation**: A brief interpretation of the problem statement and the goals of the lab.
- **SuffixMAC smht48**:
  - **Q1**: Implementation of the `smht48` function.
  - **Q2**: Verification of the implementation using provided test vectors.
- **Exhaustive Search for a Low-weight Key**:
  - **Q3**: Implementation of the `keyrec` function to find a key with a given tag.
  - **Q4**: Discussion on how a key-recovery attack can lead to a universal forgery attack and vice versa.
- **Existential Forgeries from Collisions**:
  - **Q5**: Explanation of how collisions in the hash function lead to existential forgeries in SuffixMAC.
  - **Q6**: Implementation of the `colsearch` function for finding collisions and the `smht48ef` function for generating existential forgeries.

## Implementation Details

### 1. The SuffixMAC `smht48`

The `smht48` function is a generic transformation of a hash function into a MAC. It appends a secret key to the message before hashing. In this implementation, we use a toy version called `ht48` as the underlying hash function. The function signature and implementation details are provided in the source code.

### 2. Key Recovery (`keyrec`)

The `keyrec` function performs an exhaustive search to find a key of specific bit weight that produces a given tag for a fixed message. This task demonstrates the vulnerability of SuffixMAC to exhaustive search attacks, especially when additional information about the key (like its bit weight) is known.

### 3. Existential Forgery Attacks

Existential forgery attacks exploit the collision resistance weakness in the underlying hash function `ht48`. By finding two different messages that produce the same hash output, we can forge valid MACs for new messages without knowing the secret key.

## Usage

To run the implementation, compile the source files and execute the main program. Ensure that your environment supports C programming and has the necessary permissions to execute the compiled binary.

### Compilation

```bash
gcc -o cryptolab smht48.c keyrec.c colsearch.c
```

### Execution

```bash
./cryptolab
```

## Results

The solutions include:
- The correct implementation and verification of the `smht48` function.
- Successful recovery of a key using the `keyrec` function.
- Demonstration of existential forgery attacks using the `colsearch` and `smht48ef` functions.

## Contributing

If you find any issues or have suggestions for improvement, feel free to open an issue or submit a pull request. Contributions are welcome!


## Contact

For any inquiries, please contact [Manar Shehazi](mailto:your.email@example.com).

---

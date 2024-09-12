# xStation5 API C++ Library

[![Test xapi-cpp](https://github.com/MPogotsky/xapi-cpp/blob/main/.github/workflows/cmakeLinux.yml/badge.svg)](https://github.com/MPogotsky/xapi-cpp/blob/main/.github/workflows/test-xapi-cpp.yml)

The xStation5 API C++ library provides a simple and easy-to-use API for interacting with the xStation5 trading platform. With this library, you can connect to the xStation5 platform, retrieve market data, and execute trades.

This library may be used for [XTB](https://www.xtb.com) xStation5 accounts.

API documentation: <http://developers.xstore.pro/documentation>

## Disclaimer

This xStation5 API C++ library is not affiliated with, endorsed by, or in any way officially connected to the xStation5 trading platform or its parent company. The library is provided as-is and is not guaranteed to be suitable for any particular purpose. The use of this library is at your own risk, and the author(s) of this library will not be liable for any damages arising from the use or misuse of this library. Please refer to the license file for more information.


## Requirements

Make sure to list all necessary dependencies and tools required to build and install the library.

- **C++ Compiler**: Any C++20-compliant compiler (e.g., GCC, Clang)
- **CMake**: Version 3.22 or higher
- **Boost**: Version 1.83.0 or higher
- **OpenSSL**: Version 3.0.2 or higher

### Installing Dependencies

If you are using a package manager like `apt`, `brew`, include the commands for installing dependencies:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake libssl-dev
```

#### Boost 1.83.0 Installation

To install Boost 1.83.0 (or higher), you have two options.

##### Manual install

1. Go to the [Boost website](https://www.boost.org/users/download/) and download the latest version of Boost.
2. Extract the downloaded file to a directory of your choice.
3. Open a terminal and navigate to the extracted Boost directory.
4. Run the following commands to build and install Boost:

    ```bash
    ./bootstrap.sh
    ./b2 install
    ```

5. Wait for the installation process to complete.

If the installation was successful, you should see the Boost version number displayed.

##### Install via PPA

You can also install Boost via PPA. Follow these steps:

1. Run the following command to add the PPA repository:

    ```bash
    sudo add-apt-repository ppa:mhier/libboost-latest
    ```

2. Update the package list:

    ```bash
    sudo apt update
    ```

3. Install the required Boost packages:

    ```bash
    sudo apt install libboost-system1.83-dev libboost-url1.83-dev libboost-json1.   83-dev
    ```

### Build & Install

Step-by-step guide to build the project using CMake.

1. Clone repo:

    ```bash
    sudo apt update
    ```

2. Create a build directory and navigate into it:

    ```bash
    mkdir build
    cd build
    ```

3. Run CMake to configure and build the project:

    ```bash
    cmake ..
    cmake --build . 
    ```

4. Run CMake command to install library:

    ```bash
    cmake --install . 
    ```

### Runing Tests
To build the tests, follow these steps:

1. Navigate to the `build` directory.
2. Run the following commands to configure and build the tests using CMake:

    ```bash
    cmake -DBUILD_TESTS=ON ..
    cmake --build .
    ```

    Once the build process is complete, you will have the tests ready to run.

    Use command below to run unit tests:

    ```bash
    test/tests
    ```

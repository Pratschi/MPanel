# Compiling on Linux
## Dependencies
* System Dependencies:
    * `GCC` 7.1+ (9.0+ recommended)
    * `CMake` 3.20+
    * `Ninja` 1.10+
* C++ Libraries
    * `yaml-cpp`

## Compilation
Run `scripts/linux-configure.sh` to configure the environment.

Run `scripts/linux-build.sh` to compile and build the project to `builds/MPanel`.

<br><br>

# Compiling with WSL (Windows)
Install the `Windows Subsystem for Linux` (WSL) using the [Official WSL Installation Guide](https://learn.microsoft.com/windows/wsl/install).

Install your preferred Linux distribution, and then, follow the [Linux Compilation Guide](#compiling-on-linux).

<br><br>

# Compiling with Docker (Windows/Linux/MacOS)
## Dependencies
* Docker App
* `WSL` / `Hyper-V` (If on Windows)

## Installation
Install the `Docker Desktop App` via the [Official Documentation](https://docs.docker.com/get-started/get-docker/)

Then, in a terminal session, move to the `MPanel` folder.

And create the docker image by running:
```
docker build -t mpanel-builder .
```

This will create an Ubuntu 24.04 Docker Image with all the required dependencies, by using the `Dockerfile` given at the project root.

## Compilation
We'll use the same scripts as the Linux installation.

Configure the compilation environment using:
```
docker run --rm --user "$(id -u):$(id -g)" -v "$PWD:/src" -w /src mpanel-builder bash scripts/linux-configure.sh
```

And compile with:
```
docker run --rm --user "$(id -u):$(id -g)" -v "$PWD:/src" -w /src mpanel-builder bash scripts/linux-build.sh
```
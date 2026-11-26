# Compilation
# Compiling for Linux
## Compiling on Linux
### Dependencies
* `GCC` 7.1+ (9.0+ recommended)
* `CMake` 3.20+
* `Ninja`

### Installation
* **Debian:** `sudo apt install build-essential cmake ninja-build`
* **Arch:** `sudo pacman -Syu --needed gcc cmake ninja`
* **Fedora:** `sudo dnf install gcc-c++ cmake ninja-build`

### Compilation
1. Clone the repository (`git clone https://github.com/Pratschi/MPanel`) or Download the Source Code
2. Navigate to the `MPanel/` folder.
3. Run `scripts/linux-configure.sh` to configure the environment.
4. Run `scripts/linux-build.sh` to compile and build the project to `build/MPanel`.

*Alternatively, you can use `scripts/linux-full.sh` to do everything at once.*

---

## Compiling on WSL (Windows)
Install the `Windows Subsystem for Linux`:
1. Run `wsl --install` (*requires to restart windows*)
2. See your installed Distributions (Ubuntu should be installed by default) with `wsl --list`
3. If no Distributions are installed:
    * Run `wsl --list --online` to see available ones
    * Run `wsl --install DistroName` to install one
4. Run it with `wsl -d DistroName` to run it

Now, follow the [Linux Compilation Guide](#compiling-on-linux) above to compile.

# Compiling for Windows
### Dependencies
* `CMake` 3.20+
* `Ninja`

### Compiling
1. Clone the repository (`git clone https://github.com/Pratschi/MPanel`) or Download the Source Code
2. Navigate to the `MPanel` folder.
3. Run `scripts\windows-configure.bat` to configure the environment.
4. Run `scripts\windows-build.bat` to compile and build the project to `build\MPanel`.

*Alternatively, you can use `scripts\windows-full.bat` to do everything at once.*
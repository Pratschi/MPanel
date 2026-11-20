# MPanel CHANGELOG
# v0.0.1
Initial test release, to check the correct functionality of the [Release Workflow](docs/Workflows.md#release).

There's nothing interesting in this release. It's just a basic C++ program that outputs:
```txt
MPanel Service Utility - v0.1
See https://mpanel.com/ for more information.
```

## v0.0.1 Git repository
Added `.gitignore`.

## v0.0.1 Compilation
Created `CMakeLists.txt` and `Dockerfile`.
Created 3 Linux Scripts:
* `linux-configure.sh`: Configures the project (CMake)
* `linux-build.sh`: Builds the project
* `linux-full.sh`: Configures, Builds and Runs the project.


## v0.0.1 Documentation
`docs/Compilation.md` - Created
* Dependencies
* Compiling on Linux / WSL / Docker

## v0.0.1 Workflows
`Build`
* Builds the proyect every commit and stores the executable.
`Release`
* Creates a *Github release* when a tag `v*` is created. (for example, `v0.0.1`)

<br><br><br>

# v0.0.2
## v0.0.2 Documentation
`docs/Workflows.md` - Created
* Added information for `Build` & `Release` workflows.

`CURRENT_CHANGELOG.md` - Created
* Included as *release notes* on *Github Release*.
* See [`v0.0.2 Workflows/Release`](#v002-workflows)

## v0.0.2 Workflows
`Build`
* Now, the build workflow also affects the `Beta` Branch.
* Always compiles on *Ubuntu 24.04* instead of *latest*.
* Moved from `checkout@v4` to `v5`
`Release`
* Always compiles on *Ubuntu 24.04* instead of *latest*.
* Now includes *Release Notes* taken from `CURRENT_CHANGELOG.md`

## v0.0.2 Readme
Added *Badges* and *Documentation Docs*.

## v0.0.2 Changelog
Added all `v0.0.1` version information.

Added version on each Title to quote them more easily.
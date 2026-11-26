# Workflows
## Build App
Location: `.github/workflows/build.yml`
* **Runs:** Every commit
* **Objective:** Look for compilation errors
* **Generates:** `MPanel-linux-x86_64`, `MPanel-windows-x86_64.exe`

## Publish Release
Location: `.github/workflows/release.yml`
* **Runs:** When new tag is created (starting with v*)
* **Objective:** Create Github Release draft and Attach Binaries
* **Generates:** Release Draft with Pre-Generated Changelog, with `MPanel-linux-x86_64` and `MPanel-windows-x86_64.exe` attached.
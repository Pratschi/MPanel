# Workflows
## Build App
Location: `.github/workflows/build.yml`
* **Runs:** Every commit
* **Objective:** Look for compilation errors
* **Generates:** `mpanel-VERSION-linux-x86_64`, `mpanel-VERSION-windows-x86_64.exe`, and `mpanel-VERSION-linux_debian-amd64.deb`

## Publish Release
Location: `.github/workflows/release.yml`
* **Runs:** When new tag is created (starting with v*)
* **Objective:** Create Github Release draft and Attach Binaries
* **Generates:** Release Draft with Pre-Generated Changelog, with `mpanel-VERSION-linux-x86_64`, `mpanel-VERSION-windows-x86_64.exe`, and `mpanel-VERSION-linux_debian-amd64.deb` attached.
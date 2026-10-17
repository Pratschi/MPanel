# Workflows
## Build App
Location: ```.github/workflows/build.yml```
* **Runs:** Every commit
* **Objective:** Look for compilation errors
* **Generates:** ```build/MPanel/MPanel-linux-x86_64```

## Publish Release
Location: ```.github/workflows/release.yml```
* **Runs:** When new tag is created (starting with v*)
* **Objective:** Attach Binary to the Release
* **Generates:** Release with Full Changelog, source and ```MPanel-linux-x86_64```
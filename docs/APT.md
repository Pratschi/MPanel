# Creating an APT Repository
## 1. Dependencies
Install Dependencies (Debian):
```bash
sudo apt update
sudo apt install -y reprepro dpkg-dev gnupg curl
```

## 2. Creating the Signing Key
Run:
```bash
gpg --full-generate-key
```

And select:
* 4 (RSA sign-only)
* 4096 (Max size)
* 0 (Infinite)
* y (Accept)
* Pratschi (Name)
* pratschigamer@gmail.com (Email Adress)
* (blank, no comment)
* O (Okay)

And get the key's fingerprint under by using `gpg --fingerprint pratschigamer@gmail.com`)

## 3. Setup Folder
Crate the APT Folder:
```bash
mkdir -p apt/conf
```

And edit `apt/conf/distributions` to:
```
Origin: MPanel
Label: MPanel
Suite: stable
Codename: stable
Architectures: amd64
Components: main
Description: MPanel APT repository
SignWith: INSERT_KEY_FINGERPRINT_HERE
```

Finally, export the public key with:
```bash
gpg --armor --export INSERT_KEY_FINGERPRINT_HERE > apt/mpanel-archive.asc
```

## 4. Setting up the Package
Create these folders beside the `apt/` folder:
```bash
mkdir -p build/mpanel/DEBIAN
mkdir -p build/mpanel/usr/local/bin
```

Then copy the MPanel Executable:
```bash
install -m 0755 /path/to/executable/mpanel build/mpanel/usr/local/bin/mpanel
```

Edit the Package Control in `build/mpanel/DEBIAN/control`:
```
Package: mpanel
Version: VERSION
Section: utils
Priority: optional
Architecture: amd64
Maintainer: Pratschi <pratschigamer@gmail.com>
Description: A Service and App for Servers that allows for their easy management.
```

## 5. Building the Package
Build the package with:
```bash
dpkg-deb --build build/mpanel mpanel-VERSION-linux_debian-amd64.deb
```

Add the package to the repository with:
```bash
reprepro -b apt includedeb stable mpanel-VERSION-linux_debian-amd64.deb
```

## 6. Adding the Repo
On your client, add the signing key:
```bash
curl -fsSL https://pratschi.github.io/MPanel/apt/mpanel-archive.asc | sudo gpg --dearmor -o /usr/share/keyrings/mpanel-archive.gpg
```

Then, edit `/etc/apt/sources.list.d/mpanel.list` with:
```
deb [arch=amd64 signed-by=/usr/share/keyrings/mpanel-archive.gpg] https://pratschi.github.io/MPanel/apt stable main
```

And finally, install with:
```bash
sudo apt update
sudo apt install mpanel
```
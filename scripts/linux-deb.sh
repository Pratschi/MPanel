#!/usr/bin/env bash

set -euo pipefail

die() {
    printf 'Error: %s\n' "$*" >&2
    exit 1
}

if [[ $# -ne 1 ]]; then
    die "Usage: $0 /path/to/MPanel"
fi

binary="$1"
[[ -f "$binary" ]] || die "Executable not found: $binary"
binary="$(realpath -- "$binary")"

command -v dpkg-deb >/dev/null 2>&1 || die "dpkg-deb is required."
command -v dpkg >/dev/null 2>&1 || die "dpkg is required."

package_root="$(mktemp -d)"
trap 'rm -rf -- "$package_root"' EXIT

mkdir -p "$package_root/DEBIAN" "$package_root/usr/local/bin"
install -m 0755 "$binary" "$package_root/usr/local/bin/mpanel"

version_output="$("$package_root/usr/local/bin/mpanel" --version)"
case "$version_output" in
    "MPanel v"*) version="${version_output#MPanel v}" ;;
    *) die "Could not read the MPanel version from: $version_output" ;;
esac

[[ -n "$version" ]] || die "The MPanel version is empty."
dpkg --validate-version "$version" || die "Invalid Debian package version: $version"

cat > "$package_root/DEBIAN/control" <<EOF
Package: mpanel
Version: $version
Section: utils
Priority: optional
Architecture: amd64
Maintainer: Pratschi <pratschigamer@gmail.com>
Description: A Service and App for Servers that allows for their easy management.
EOF

output="$PWD/mpanel_${version}_amd64.deb"
dpkg-deb --build --root-owner-group "$package_root" "$output"
printf 'Created %s\n' "$output"

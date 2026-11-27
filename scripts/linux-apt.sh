#!/usr/bin/env bash

set -euo pipefail

die() {
    printf 'Error: %s\n' "$*" >&2
    exit 1
}

force_downgrade=false
if [[ "${1:-}" == "--force-downgrade" ]]; then
    force_downgrade=true
    shift
fi

if [[ $# -ne 1 ]]; then
    die "Usage: $0 [--force-downgrade] /path/to/mpanel-VERSION-linux_debian-amd64.deb"
fi

package="$1"
[[ -f "$package" ]] || die "Debian package not found: $package"
package="$(realpath -- "$package")"

command -v dpkg-deb >/dev/null 2>&1 || die "dpkg-deb is required."
command -v dpkg >/dev/null 2>&1 || die "dpkg is required."
command -v reprepro >/dev/null 2>&1 || die "reprepro is required."

package_name="$(dpkg-deb --field "$package" Package)"
architecture="$(dpkg-deb --field "$package" Architecture)"
version="$(dpkg-deb --field "$package" Version)"

[[ "$package_name" == "mpanel" ]] || die "Expected package 'mpanel', got '$package_name'."
[[ "$architecture" == "amd64" ]] || die "Expected architecture 'amd64', got '$architecture'."
[[ -n "$version" ]] || die "The package has no version."

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd -- "$script_dir/.." && pwd)"
apt_dir="$repo_root/.github/pages/apt"
[[ -f "$apt_dir/conf/distributions" ]] || die "APT repository configuration not found: $apt_dir/conf/distributions"

current_listing="$(reprepro -b "$apt_dir" list stable mpanel)"
current_version="$(awk -F': mpanel ' 'NF > 1 { split($2, fields, " "); print fields[1]; exit }' <<< "$current_listing")"

if [[ -n "$current_version" ]]; then
    if [[ "$current_version" == "$version" ]]; then
        printf 'mpanel %s is already in stable.\n' "$version"
        exit 0
    fi

    if dpkg --compare-versions "$version" lt "$current_version"; then
        if [[ "$force_downgrade" != true ]]; then
            die "Version $version is older than stable's $current_version. Use --force-downgrade to replace it."
        fi

        reprepro -b "$apt_dir" remove stable mpanel
    fi
fi

reprepro -b "$apt_dir" includedeb stable "$package"

updated_listing="$(reprepro -b "$apt_dir" list stable mpanel)"
updated_version="$(awk -F': mpanel ' 'NF > 1 { split($2, fields, " "); print fields[1]; exit }' <<< "$updated_listing")"
[[ "$updated_version" == "$version" ]] || die "APT repository still contains mpanel $updated_version; failed to add $version."

printf 'Added mpanel %s to %s\n' "$version" "$apt_dir"

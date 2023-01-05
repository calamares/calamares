# CHANGELOG

Calamares Core `v3.3.0_alpha2_1` -> `v3.3.0_alpha3_4` ChangeLog

### For Users

- In the *Advanced* page (the `netinstall` module) all duplicate package names now share the same selection state. This means that if you see the same package under multiple categories, all duplicates will update when you either click on those packages directly or when you indirectly select/deselect them by clicking on a *group*

- The *Advanced* page (the `netinstall` module) now has a *Reset to Defaults* functionality

- `adobe-source-han-sans-otc-fonts` and `adobe-source-han-serif-otc-fonts` added to properly display Chinese, Japanese, and Korean fonts in the installer

- Drives mounted/auto-mounted from the ISO are now automatically unmounted before the installer launch, allowing the partition page in the installer to provide all possible options for those drives.


### For Developers

- GitHub CI for stable releases complete with GitHub-built Arch Linux packages, ChangeLog fetched from CHANGELOG.md, and MD5 CheckSums

- GitHub CI for unstable pre-releases complete with GitHub-built Arch Linux packages, ChangeLog fetched from commit history, and MD5 CheckSums

- Revamped and updated documentation
  
- Revamped and simplified build scripts for three packaging modes - `local`, `git`, and `stable`
  
- Updated *PKGBUILDs* to prevent the annoying replacement offers for the installer packages during system updates
# Users module

The users module take care of managing the users that will be created on the installed system.

## Configuration of the module

The following settings are available in **users.conf**:

  - ```defaultGroups```: list of groups every user will be added to.
  - ```autologinGroup```: group to add the user with autologin to, if any.
  - ```doAutologin```: allow for users with autologin (at most one per system). Defaults to false.
  - ```sudoersGroup```: group for sudoers usage.
  - ```setRootPassword```: allow to set the root password in the installed system. Defaults to false.
  - ```availableShells```: comma-separated list of available shells for new users. If not present, new users will not have any explicit shell in /etc/passwd, therefore the system default (usually, /bin/bash) will be used.
  - ```avatarFilePath```: path where to copy user avatars to; ~ can be used to represent the user's home directory. If not present or empty, we won't allow users to set avatars.


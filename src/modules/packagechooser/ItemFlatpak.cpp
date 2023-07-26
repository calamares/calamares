#include <sys/wait.h>
#include <unistd.h>

#include "ItemFlatpak.h"

PackageItem
fromFlatpak( AppStream::Pool& pool, const QVariantMap& item_map )
{
   PackageItemFlatpak item(fromAppStream(pool, item_map));

   item.backend = QString("flatpak");
   // check if it is installed
   int status;
   int pid = fork();
   if (0 == pid)
   {
      execlp("flatpak", "flatpak", "info", item.id, NULL);
   }
   waitpid(pid, &status, 0);

   if (WEXITSTATUS(status) == 0)
   {
     item.installed = true;
   }
   else
   {
     item.installed = false;
   }

   return item;
}

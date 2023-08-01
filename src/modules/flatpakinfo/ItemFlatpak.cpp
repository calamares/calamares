#include <sys/wait.h>
#include <unistd.h>
#include <QVariantMap>

#include "utils/Logger.h"
#include "utils/Variant.h"
#include "ItemFlatpak.h"

PackageItem
fromFlatpak( const QVariantMap& item_map )
{
   // check if it is installed
   PackageItem item(CalamaresUtils::getString( item_map, "appstream" ));
   int status;
   int pid = fork();
   if (0 == pid)
   {
      execlp("flatpak", "flatpak", "info", item.getAppStreamId().toStdString().c_str(), NULL);
   }
   waitpid(pid, &status, 0);

   if (WEXITSTATUS(status) == 0)
   {
     item.setInstalled(true);
   }
   else
   {
     item.setInstalled(false);
   }

   return item;
}

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="cs_CZ" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="71"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>&lt;strong&gt;Zaváděcí prostředí&lt;/strong&gt; tohoto systému.&lt;br&gt;&lt;br&gt;Starší x86 systémy podporují pouze &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Moderní systémy obvykle používají &lt;strong&gt;UEFI&lt;/strong&gt;, ale pokud jsou spuštěné v režimu kompatibility, mohou se zobrazovat jako BIOS.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="81"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Systém byl spuštěn se zaváděcím prostředím &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Aby byl systém zaváděn prostředím EFI je třeba, aby instalátor nasadil na &lt;strong&gt; EFI systémový oddíl&lt;/strong&gt;aplikaci pro zavádění systému, jako &lt;strong&gt;GRUB&lt;/strong&gt; nebo &lt;strong&gt;systemd-boot&lt;/strong&gt;. To proběhne automaticky, tedy pokud si nezvolíte ruční dělení datového úložiště – v takovém případě si EFI systémový oddíl volíte nebo vytváříte sami.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="93"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Systém byl spuštěn se zaváděcím prostředím &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Aby byl systém zaváděn prostředím BIOS je třeba, aby instalátor vpravil zavaděč systému, jako &lt;strong&gt;GRUB&lt;/strong&gt;, buď na začátek oddílu nebo (lépe) do &lt;strong&gt;hlavního zaváděcího záznamu (MBR)&lt;/strong&gt; na začátku tabulky oddílů. To proběhne automaticky, tedy pokud si nezvolíte ruční dělení datového úložiště – v takovém případě si zavádění nastavujete sami.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="68"/>
      <source>Master Boot Record of %1</source>
      <translation>Hlavní zaváděcí záznam (MBR) na %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="102"/>
      <source>Boot Partition</source>
      <translation>Zaváděcí oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="109"/>
      <source>System Partition</source>
      <translation>Systémový oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="139"/>
      <source>Do not install a boot loader</source>
      <translation>Neinstalovat zavaděč systému</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="157"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="70"/>
      <source>Blank Page</source>
      <translation>Prázdná stránka</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="24"/>
      <source>GlobalStorage</source>
      <translation>Globální úložiště</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="34"/>
      <source>JobQueue</source>
      <translation>Zpracovává se</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="44"/>
      <source>Modules</source>
      <translation>Moduly</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="57"/>
      <source>Type:</source>
      <translation>Typ:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="64"/>
      <location filename="../src/calamares/DebugWindow.ui" line="78"/>
      <source>none</source>
      <translation>žádný</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="71"/>
      <source>Interface:</source>
      <translation>Rozhraní:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="93"/>
      <source>Tools</source>
      <translation>Nástroje</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="106"/>
      <source>Reload Stylesheet</source>
      <translation>Znovunačíst sešit se styly</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="113"/>
      <source>Widget Tree</source>
      <translation>Strom widgetu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="231"/>
      <source>Debug information</source>
      <translation>Ladící informace</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="94"/>
      <source>Set up</source>
      <translation>Nastavit</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="94"/>
      <source>Install</source>
      <translation>Instalovat</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="42"/>
      <source>Job failed (%1)</source>
      <translation>Úloha se nezdařila (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="43"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Byl výslovně vyžádán nezdar naprogramované úlohy.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="118"/>
      <source>Done</source>
      <translation>Hotovo</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Example job (%1)</source>
      <translation>Úloha pro ukázku (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="56"/>
      <source>Run command '%1' in target system.</source>
      <translation>Spustit v cílovém systému příkaz „%1“.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="56"/>
      <source> Run command '%1'.</source>
      <translation>Spustit příkaz „%1“</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="63"/>
      <source>Running command %1 %2</source>
      <translation>Spouštění příkazu %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="213"/>
      <source>Running %1 operation.</source>
      <translation>Spouštění %1 operace.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="242"/>
      <source>Bad working directory path</source>
      <translation>Chybný popis umístění pracovní složky</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="243"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Pracovní složku %1 pro Python skript %2 se nedaří otevřít pro čtení.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="249"/>
      <source>Bad main script file</source>
      <translation>Nesprávný soubor s hlavním skriptem</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="250"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Hlavní soubor s python skriptem %1 pro úlohu %2 se nedaří otevřít pro čtení..</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="318"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost.Python chyba ve skriptu „%1“.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="76"/>
      <source>Loading ...</source>
      <translation>Načítání…</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="97"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML Step &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="261"/>
      <source>Loading failed.</source>
      <translation>Načítání se nezdařilo.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="106"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>Kontrola požadavků pro modul &lt;i&gt;%1&lt;/i&gt; dokončena.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="127"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Čeká se na %n modul</numerusform>
        <numerusform>Čeká se na %n moduly</numerusform>
        <numerusform>Čeká se na %n modulů</numerusform>
        <numerusform>Čeká se na %n moduly</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="128"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n sekundu)</numerusform>
        <numerusform>(%n sekundy)</numerusform>
        <numerusform>(%n sekund)</numerusform>
        <numerusform>(%n sekundy)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="133"/>
      <source>System-requirements checking is complete.</source>
      <translation>Kontrola požadavků na systém dokončena.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Setup Failed</source>
      <translation>Nastavení se nezdařilo</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Installation Failed</source>
      <translation>Instalace se nezdařila</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="154"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Chcete vyvěsit záznam událostí při instalaci na web?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="167"/>
      <source>Error</source>
      <translation>Chyba</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="174"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="521"/>
      <source>&amp;Yes</source>
      <translation>&amp;Ano</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="175"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="522"/>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="181"/>
      <source>&amp;Close</source>
      <translation>&amp;Zavřít</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>Install Log Paste URL</source>
      <translation>URL pro vložení záznamu událostí při instalaci</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="195"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Nahrání se nezdařilo. Na web nebylo nic vloženo.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="211"/>
      <source>Calamares Initialization Failed</source>
      <translation>Inicializace Calamares se nezdařila</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="212"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 nemůže být nainstalováno. Calamares se nepodařilo načíst všechny nastavené moduly. Toto je problém způsobu použití Calamares ve vámi používané distribuci.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt; Následující moduly se nepodařilo načíst:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>Continue with setup?</source>
      <translation>Pokračovat s instalací?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>Continue with installation?</source>
      <translation>Pokračovat v instalaci?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Instalátor %1 provede změny na datovém úložišti, aby bylo nainstalováno %2.&lt;br/&gt;&lt;strong&gt;Změny nebude možné vrátit zpět.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Instalátor %1 provede změny na datovém úložišti, aby bylo nainstalováno %2.&lt;br/&gt;&lt;strong&gt;Změny nebude možné vrátit zpět.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="338"/>
      <source>&amp;Set up now</source>
      <translation>Na&amp;stavit nyní</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="338"/>
      <source>&amp;Install now</source>
      <translation>&amp;Spustit instalaci</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="346"/>
      <source>Go &amp;back</source>
      <translation>Jít &amp;zpět</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>&amp;Set up</source>
      <translation>Na&amp;stavit</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>&amp;Install</source>
      <translation>Na&amp;instalovat</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Nastavení je dokončeno. Ukončete nastavovací program.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Instalace je dokončena. Ukončete instalátor.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="400"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Zrušit nastavení bez změny v systému.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="401"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Zrušení instalace bez provedení změn systému.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="411"/>
      <source>&amp;Next</source>
      <translation>&amp;Další</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="416"/>
      <source>&amp;Back</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="422"/>
      <source>&amp;Done</source>
      <translation>&amp;Hotovo</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="441"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Storno</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Cancel setup?</source>
      <translation>Zrušit nastavování?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Cancel installation?</source>
      <translation>Přerušit instalaci?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="515"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Opravdu chcete přerušit instalaci?
Instalační program bude ukončen a všechny změny ztraceny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="517"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Opravdu chcete instalaci přerušit?
Instalační program bude ukončen a všechny změny ztraceny.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="301"/>
      <source>Unknown exception type</source>
      <translation>Neznámý typ výjimky</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="319"/>
      <source>unparseable Python error</source>
      <translation>Chyba při zpracovávání (parse) Python skriptu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="363"/>
      <source>unparseable Python traceback</source>
      <translation>Chyba při zpracovávání (parse) Python záznamu volání funkcí (traceback).</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="370"/>
      <source>Unfetchable Python error.</source>
      <translation>Chyba při načítání Python skriptu.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="34"/>
      <source>Install log posted to:
%1</source>
      <translation>Záznam událostí instalace vyvěšen na:
%1</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="110"/>
      <source>Show debug information</source>
      <translation>Zobrazit ladící informace</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="164"/>
      <source>&amp;Back</source>
      <translation>&amp;Zpět</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="176"/>
      <source>&amp;Next</source>
      <translation>&amp;Další</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="189"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Storno</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="311"/>
      <source>%1 Setup Program</source>
      <translation>Instalátor %1</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="312"/>
      <source>%1 Installer</source>
      <translation>%1 instalátor</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="46"/>
      <source>Gathering system information...</source>
      <translation>Shromažďování informací o systému…</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="156"/>
      <source>Select storage de&amp;vice:</source>
      <translation>&amp;Vyberte úložné zařízení:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="157"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1088"/>
      <source>Current:</source>
      <translation>Stávající:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="158"/>
      <source>After:</source>
      <translation>Po:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="334"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself. Having a GPT partition table and &lt;strong&gt;fat32 512Mb /boot partition is a must for UEFI installs&lt;/strong&gt;, either use an existing without formatting or create one.</source>
      <translation>&lt;strong&gt;Ruční rozdělení&lt;/strong&gt;&lt;br/&gt;Můžete si sami vytvořit nebo změnit velikost oddílů. Pro UEFI instalace je zapotřebí mít GPT tabulku oddílů a &lt;strong&gt;512 MB oddíl /boot se souborovým systémem FAT32&lt;/strong&gt; – buď nevytvářejte znovu a použijte existující, nebo takovou vytvořte.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="833"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Zrecyklovat %1 na oddíl pro domovské složky %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Vyberte oddíl, který chcete zmenšit, poté posouváním na spodní liště změňte jeho velikost.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 bude zmenšen na %2MiB a nový %3MiB oddíl pro %4 bude vytvořen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1030"/>
      <source>Boot loader location:</source>
      <translation>Umístění zavaděče:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1079"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Vyberte oddíl na který nainstalovat&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1135"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Nebyl nalezen žádný EFI systémový oddíl. Vraťte se zpět a nastavte %1 pomocí ručního rozdělení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1144"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>Pro zavedení %2 se využije EFI systémový oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1152"/>
      <source>EFI system partition:</source>
      <translation>EFI systémový oddíl:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Zdá se, že na tomto úložném zařízení není žádný operační systém. Jak chcete postupovat?&lt;br/&gt;Než budou provedeny jakékoli změny na úložných zařízeních, bude zobrazen jejich přehled a budete požádáni o jejich potvrzení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1275"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1313"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1336"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1362"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Vymazat datové úložiště&lt;/strong&gt;&lt;br/&gt;Touto volbou budou &lt;font color="red"&gt;smazána&lt;/font&gt; všechna data, která se na něm nyní nacházejí.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1309"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1332"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1358"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Nainstalovat vedle&lt;/strong&gt;&lt;br/&gt;Instalátor zmenší oddíl a vytvoří místo pro %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1283"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1318"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1340"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1366"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Nahradit oddíl&lt;/strong&gt;&lt;br/&gt;Původní oddíl bude nahrazen %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1303"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Na tomto úložném zařízení bylo nalezeno %1. Jak chcete postupovat?&lt;br/&gt;Než budou provedeny jakékoli změny na úložných zařízeních, bude zobrazen jejich přehled a budete požádáni o jejich potvrzení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1327"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Na tomto úložném zařízení se už nachází operační systém. Jak chcete postupovat?&lt;br/&gt;Než budou provedeny jakékoli změny na úložných zařízeních, bude zobrazen jejich přehled a budete požádáni o jejich potvrzení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1353"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Na tomto úložném zařízení se už nachází několik operačních systémů. Jak chcete postupovat?&lt;br/&gt;Než budou provedeny jakékoli změny na úložných zařízeních, bude zobrazen jejich přehled změn a budete požádáni o jejich potvrzení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1507"/>
      <source>No Swap</source>
      <translation>Žádný odkládací prostor (swap)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1512"/>
      <source>Reuse Swap</source>
      <translation>Použít existující odkládací prostor</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1515"/>
      <source>Swap (no Hibernate)</source>
      <translation>Odkládací prostor (bez uspávání na disk)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1518"/>
      <source>Swap (with Hibernate)</source>
      <translation>Odkládací prostor (s uspáváním na disk)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1521"/>
      <source>Swap to file</source>
      <translation>Odkládat do souboru</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="50"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Odpojit souborové systémy před zahájením dělení %1 na oddíly</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="57"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Odpojují se souborové systémy před zahájením dělení %1 na oddíly</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="232"/>
      <source>Cleared all mounts for %1</source>
      <translation>Všechny souborové systémy na %1 odpojeny</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
      <source>Clear all temporary mounts.</source>
      <translation>Odpojit všechny dočasné přípojné body.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Odpojují se všechny dočasné přípojné body.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="61"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Nepodařilo získat seznam dočasných přípojných bodů.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="102"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Všechny přípojné body odpojeny.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="154"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="167"/>
      <source>Could not run command.</source>
      <translation>Nedaří se spustit příkaz.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>Příkaz bude spuštěn v prostředí hostitele a potřebuje znát popis umístění kořene souborového systému. rootMountPoint ale není zadaný.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="168"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Příkaz potřebuje znát uživatelské jméno, to ale zadáno nebylo.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="348"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Nastavit model klávesnice na %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="355"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Nastavit rozložení klávesnice na %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="279"/>
      <source>The system language will be set to %1.</source>
      <translation>Jazyk systému bude nastaven na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="280"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>Formát zobrazení čísel, data a času bude nastaven dle národního prostředí %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="313"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Nastavit časové pásmo na %1/%2.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="47"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Síťová instalace. (vypnuto: nesprávné nastavení)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="49"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Síťová instalace. (Vypnuto: Obdrženy neplatné údaje skupin)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="51"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation>Instalace ze sítě. (Vypnuto: vnitřní chyba)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Síťová instalace. (Vypnuto: Nedaří se stáhnout seznamy balíčků – zkontrolujte připojení k síti)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="56"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Počítač nesplňuje minimální požadavky pro instalaci %1.&lt;br/&gt;Instalace nemůže pokračovat &lt;a href="#details"&gt;Podrobnosti…&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Počítač nesplňuje minimální požadavky pro instalaci %1.&lt;br/&gt;Instalace nemůže pokračovat &lt;a href="#details"&gt;Podrobnosti…&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="67"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Počítač nesplňuje některé doporučené požadavky pro instalaci %1.&lt;br/&gt;Instalace může pokračovat, ale některé funkce mohou být vypnuty.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="71"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Počítač nesplňuje některé doporučené požadavky pro instalaci %1.&lt;br/&gt;Instalace může pokračovat, ale některé funkce mohou být vypnuty.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="81"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Tento program vám položí několik dotazů, aby na základě odpovědí příslušně nainstaloval %2 na váš počítač.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="245"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="246"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="251"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="252"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="128"/>
      <source>Contextual Processes Job</source>
      <translation>Úloha kontextuálních procesů</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
      <source>Create a Partition</source>
      <translation>Vytvořit oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
      <source>Si&amp;ze:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
      <source>Partition &amp;Type:</source>
      <translation>&amp;Typ oddílu:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
      <source>&amp;Primary</source>
      <translation>&amp;Primární</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
      <source>E&amp;xtended</source>
      <translation>&amp;Rozšířený</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;Souborový systém:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
      <source>LVM LV name</source>
      <translation>Název LVM logického svazku</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Přípojný bod:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
      <source>Flags:</source>
      <translation>Příznaky:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="74"/>
      <source>En&amp;crypt</source>
      <translation>Š&amp;ifrovat</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="159"/>
      <source>Logical</source>
      <translation>Logický</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="164"/>
      <source>Primary</source>
      <translation>Primární</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="181"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="271"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Tento přípojný bod už je používán – vyberte jiný.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="47"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Vytvořit nový %2MiB oddíl na %4 (%3) se souborovým systémem %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="58"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Vytvořit nový &lt;strong&gt;%2MiB&lt;/strong&gt; oddíl na &lt;strong&gt;%4&lt;/strong&gt; (%3) se souborovým systémem &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="70"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Vytváří se nový %1 oddíl na %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="82"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Instalátoru se nepodařilo vytvořit oddíl na datovém úložišti „%1“.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
      <source>Create Partition Table</source>
      <translation>Vytvořit tabulku oddílů</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Vytvoření nové tabulky oddílů vymaže všechna stávající data na jednotce.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Jaký typ tabulky oddílů si přejete vytvořit?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID Partition Table (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="48"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Vytvořit novou %1 tabulku oddílů na %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="56"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Vytvořit novou &lt;strong&gt;%1&lt;/strong&gt; tabulku oddílů na &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="66"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Vytváří se nová %1 tabulka oddílů na %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="84"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Instalátoru se nepodařilo vytvořit tabulku oddílů na %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
      <source>Create user %1</source>
      <translation>Vytvořit uživatele %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Vytvořit uživatele &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
      <source>Creating user %1.</source>
      <translation>Vytváří se účet pro uživatele %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
      <source>Sudoers dir is not writable.</source>
      <translation>Nedaří se zapsat do složky sudoers.d.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="89"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Nepodařilo se vytvořit soubor pro sudoers tak, aby do něj šlo zapsat.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Nepodařilo se změnit přístupová práva (chmod) na souboru se sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="107"/>
      <source>Cannot open groups file for reading.</source>
      <translation>Nepodařilo se otevřít soubor groups pro čtení.</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="37"/>
      <source>Create Volume Group</source>
      <translation>Vytvořit skupinu svazků</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named %1.</source>
      <translation>Vytvořit novou skupinu svazků nazvanou %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Vytvořit novou skupinu svazků nazvanou &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="49"/>
      <source>Creating new volume group named %1.</source>
      <translation>Vytváří se nová skupina svazků nazvaná %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Instalátoru se nepodařilo vytvořit skupinu svazků nazvanou „%1“.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="45"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Deaktivovat skupinu svazků nazvanou %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="39"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Deaktivovat skupinu svazků nazvanou &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Instalátoru se nepodařilo deaktivovat skupinu svazků nazvanou %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
      <source>Delete partition %1.</source>
      <translation>Smazat oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="47"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Smazat oddíl &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="54"/>
      <source>Deleting partition %1.</source>
      <translation>Odstraňuje se oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="65"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Instalátoru se nepodařilo odstranit oddíl %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Na tomto zařízení je tabulka oddílů &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="115"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Vybrané úložné zařízení je &lt;strong&gt;loop&lt;/strong&gt; zařízení.&lt;br&gt;&lt;br&gt; Nejedná se o vlastní tabulku oddílů, je to pseudo zařízení, které zpřístupňuje soubory blokově. Tento typ nastavení většinou obsahuje jediný systém souborů.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="122"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Instalační program na zvoleném zařízení &lt;strong&gt;nezjistil žádnou tabulku oddílů&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Toto zařízení buď žádnou tabulku nemá nebo je porušená nebo neznámého typu.&lt;br&gt; Instalátor může vytvořit novou tabulku oddílů – buď automaticky nebo přes ruční rozdělení jednotky.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="132"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Toto je doporučený typ tabulky oddílů pro moderní systémy, které se spouští pomocí &lt;strong&gt;UEFI&lt;/strong&gt; zaváděcího prostředí.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="138"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Tento typ tabulky oddílů je vhodný pro starší systémy, které jsou spouštěny z prostředí &lt;strong&gt;BIOS&lt;/strong&gt;. Více se dnes využívá GPT.&lt;br&gt;&lt;strong&gt;Upozornění:&lt;/strong&gt; Tabulka oddílů MBR je zastaralý standard z dob MS-DOS.&lt;br&gt;Lze vytvořit pouze 4 &lt;em&gt;primární&lt;/em&gt; oddíly, a z těchto 4, jeden může být &lt;em&gt;rozšířeným&lt;/em&gt; oddílem, který potom může obsahovat více &lt;em&gt;logických&lt;/em&gt; oddílů.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Typ &lt;strong&gt;tabulky oddílů&lt;/strong&gt;, který je na vybraném úložném zařízení.&lt;br&gt;&lt;br&gt;Jedinou možností jak změnit typ tabulky oddílů je smazání a opětovné vytvoření nové tabulky oddílů, tím se smažou všechna data na daném úložném zařízení.&lt;br&gt;Tento instalátor ponechá stávající typ tabulky oddílů, pokud si sami nenavolíte jeho změnu.&lt;br&gt;Pokud si nejste jisti, na moderních systémech se upřednostňuje GPT.</translation>
    </message>
  </context>
  <context>
    <name>DeviceModel</name>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="93"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 – %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="104"/>
      <source>%1 - (%2)</source>
      <extracomment>device[name] - (device-node[name])</extracomment>
      <translation>%1 – (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="136"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Zapsat nastavení LUKS pro Dracut do %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="140"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Přeskočit zápis nastavení LUKS pro Dracut: oddíl „/“ není šifrovaný</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="157"/>
      <source>Failed to open %1</source>
      <translation>Nepodařilo se otevřít %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
      <source>Dummy C++ Job</source>
      <translation>Výplňová úloha C++</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
      <source>Edit Existing Partition</source>
      <translation>Upravit existující oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
      <source>Content:</source>
      <translation>Obsah:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
      <source>&amp;Keep</source>
      <translation>&amp;Zachovat</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
      <source>Format</source>
      <translation>Formátovat</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Varování: Formátování oddílu vymaže všechna data.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Přípojný bod:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
      <source>Si&amp;ze:</source>
      <translation>&amp;Velikost:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;Souborový systém:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
      <source>Flags:</source>
      <translation>Příznaky:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="278"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Tento přípojný bod je už používán – vyberte jiný.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
      <source>En&amp;crypt system</source>
      <translation>Z&amp;ašifrovat systém</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
      <source>Passphrase</source>
      <translation>Heslová fráze</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
      <source>Confirm passphrase</source>
      <translation>Potvrzení heslové fráze</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="153"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Zadejte stejnou heslovou frázi do obou kolonek.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="142"/>
      <source>Set partition information</source>
      <translation>Nastavit informace o oddílu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="168"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Nainstalovat %1 na &lt;strong&gt;nový&lt;/strong&gt; %2 systémový oddíl.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="174"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nastavit &lt;strong&gt;nový&lt;/strong&gt; %2 oddíl s přípojným bodem &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="184"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nainstalovat %2 na %3 systémový oddíl &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="191"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Nastavit %3 oddíl &lt;strong&gt;%1&lt;/strong&gt; s přípojným bodem &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="204"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nainstalovat zavaděč do &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="213"/>
      <source>Setting up mount points.</source>
      <translation>Nastavují se přípojné body.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Restartovat nyní</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="53"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Instalace je u konce.&lt;/h1&gt;&lt;br/&gt;%1 byl nainstalován na váš počítač.&lt;br/&gt;Nyní ho můžete restartovat a přejít do čerstvě nainstalovaného systému, nebo můžete pokračovat v práci ve stávajícím prostředím %2, spuštěným z instalačního média.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="57"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Když je tato kolonka zaškrtnutá, systém se restartuje jakmile kliknete na &lt;span style="font-style:italic;"&gt;Hotovo&lt;/span&gt; nebo zavřete instalátor.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="63"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Instalace je u konce.&lt;/h1&gt;&lt;br/&gt;%1 bylo nainstalováno na váš počítač.&lt;br/&gt;Nyní ho můžete restartovat a přejít do čerstvě nainstalovaného systému, nebo můžete pokračovat v práci ve stávajícím prostředím %2, spuštěným z instalačního média.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="68"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Když je tato kolonka zaškrtnutá, systém se restartuje jakmile kliknete na &lt;span style="font-style:italic;"&gt;Hotovo&lt;/span&gt; nebo zavřete instalátor.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="125"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Instalace se nezdařila&lt;/h1&gt;&lt;br/&gt;%1 nebyl instalován na váš počítač.&lt;br/&gt;Hlášení o chybě: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="131"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Instalace se nezdařila&lt;/h1&gt;&lt;br/&gt;%1 nebylo nainstalováno na váš počítač.&lt;br/&gt;Hlášení o chybě: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="76"/>
      <source>Finish</source>
      <translation>Dokončit</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="134"/>
      <source>Setup Complete</source>
      <translation>Nastavení dokončeno</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="134"/>
      <source>Installation Complete</source>
      <translation>Instalace dokončena</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="136"/>
      <source>The setup of %1 is complete.</source>
      <translation>Nastavení %1 je dokončeno.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="137"/>
      <source>The installation of %1 is complete.</source>
      <translation>Instalace %1 je dokončena.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="45"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Formátovat oddíl %1 (souborový systém: %2, velikost %3 MiB) na %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="56"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Naformátovat &lt;strong&gt;%3MiB&lt;/strong&gt; oddíl &lt;strong&gt;%1&lt;/strong&gt; souborovým systémem &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="67"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Vytváření souborového systému %2 na oddílu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="81"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Instalátoru se nepodařilo vytvořit souborový systém na oddílu %1 jednotky datového úložiště „%2“.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="159"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>má alespoň %1 GiB dostupného prostoru</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Nedostatek místa na úložišti. Je potřeba nejméně %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="171"/>
      <source>has at least %1 GiB working memory</source>
      <translation>má alespoň %1 GiB operační paměti</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="173"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Systém nemá dostatek operační paměti. Je potřeba nejméně %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="182"/>
      <source>is plugged in to a power source</source>
      <translation>je připojený ke zdroji napájení</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="183"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Systém není připojen ke zdroji napájení.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="190"/>
      <source>is connected to the Internet</source>
      <translation>je připojený k Internetu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="191"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Systém není připojený k Internetu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="198"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>instalátor je spuštěný s právy správce systému (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="201"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Nastavovací program není spuštěn s právy správce systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="202"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Instalační program není spuštěn s právy správce systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="210"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>má obrazovku dostatečně velkou pro zobrazení celého instalátoru</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="213"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Rozlišení obrazovky je příliš malé pro zobrazení nastavovacího programu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="214"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Rozlišení obrazovky je příliš malé pro zobrazení instalátoru.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="51"/>
      <source>Collecting information about your machine.</source>
      <translation>Shromažďují se informací o stroji.</translation>
    </message>
  </context>
  <context>
    <name>IDJob</name>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="38"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="47"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="59"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="67"/>
      <source>OEM Batch Identifier</source>
      <translation>Identifikátor OEM série</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="48"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nedaří se vytvořit složky &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nedaří se otevřít soubor &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="68"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nedaří se zapsat do souboru &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="40"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Vytváření initramfs pomocí mkinitcpio.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="37"/>
      <source>Creating initramfs.</source>
      <translation>Vytváření initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
      <source>Konsole not installed</source>
      <translation>Konsole není nainstalované.</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Nainstalujte KDE Konsole a zkuste to znovu!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Spouštění skriptu: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="47"/>
      <source>Script</source>
      <translation>Skript</translation>
    </message>
  </context>
  <context>
    <name>KeyboardPage</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="213"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Nastavit model klávesnice na %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="217"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Nastavit rozložení klávesnice na %1/%2.</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Klávesnice</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="54"/>
      <source>Keyboard</source>
      <translation>Klávesnice</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="32"/>
      <source>System locale setting</source>
      <translation>Místní a jazykové nastavení systému</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="39"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Místní a jazykové nastavení systému ovlivňuje jazyk a znakovou sadu některých prvků rozhraní příkazového řádku.&lt;br/&gt;Stávající nastavení je &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="63"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Storno</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="64"/>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="22"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licenční ujednání&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Souhlasím s výše uvedenými podmínkami.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>Pročtěte si Smlouvy s koncovými uživatelem (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>Tato nastavovací procedura nainstaluje proprietární software, který je předmětem licenčních podmínek.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>Pokud s podmínkami nesouhlasíte, instalační procedura nemůže pokračovat.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="164"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>Pro poskytování dalších funkcí a vylepšení pro uživatele, tato nastavovací procedura nainstaluje i proprietární software, který je předmětem licenčních podmínek.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="169"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>Pokud nesouhlasíte s podmínkami, proprietární software nebude nainstalován a namísto toho budou použity opensource alternativy.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="52"/>
      <source>License</source>
      <translation>Licence</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="96"/>
      <source>URL: %1</source>
      <translation>URL: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="117"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;%1 ovladač&lt;/strong&gt;&lt;br/&gt;od %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 ovladač grafiky&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;od %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="130"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 doplněk prohlížeče&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;od %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="136"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 kodek&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;od %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="142"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 balíček&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;od %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="148"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;od %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="171"/>
      <source>File: %1</source>
      <translation>Soubor: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Hide license text</source>
      <translation>Skrýt text licence</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Show the license text</source>
      <translation>Zobrazit text licence</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="198"/>
      <source>Open license agreement in browser.</source>
      <translation>Otevřít licenční ujednání v prohlížeči.</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="127"/>
      <source>Region:</source>
      <translation>Oblast:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="128"/>
      <source>Zone:</source>
      <translation>Pásmo:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="129"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>&amp;Change...</source>
      <translation>&amp;Změnit…</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="262"/>
      <source>The system language will be set to %1.</source>
      <translation>Jazyk systému bude nastaven na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="263"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>Formát zobrazení čísel, data a času bude nastaven dle národního prostředí %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="270"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Nastavit časové pásmo na %1/%2.&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="95"/>
      <source>Location</source>
      <translation>Poloha</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="100"/>
      <source>Location</source>
      <translation>Poloha</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="39"/>
      <source>Configuring LUKS key file.</source>
      <translation>Nastavování souboru s klíčem pro LUKS šifrování.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="156"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="164"/>
      <source>No partitions are defined.</source>
      <translation>Nejsou definovány žádné oddíly.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="192"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="199"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="207"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Chyba nastavení šifrovaného kořenového oddílu</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="193"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Kořenový oddíl %1 je LUKS, ale nebyla nastavena žádná heslová fráze.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="200"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Nedaří se vytvořit LUKS klíč pro kořenový oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="208"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>Nedaří se nastavit LUKS klíč pro oddíl %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="46"/>
      <source>Generate machine-id.</source>
      <translation>Vytvořit identifikátor stroje.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="62"/>
      <source>Configuration Error</source>
      <translation>Chyba nastavení</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="63"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Pro MachineId není nastaven žádný kořenový přípojný bod.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="238"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Package selection</source>
      <translation>Výběr balíčků</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Office software</source>
      <translation>Aplikace pro kancelář</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Office package</source>
      <translation>Balíček s kancelářským software</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Browser software</source>
      <translation>Aplikace pro procházení webu</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Browser package</source>
      <translation>Balíček s webovým prohlížečem</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Web browser</source>
      <translation>Webový prohlížeč</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Kernel</source>
      <translation>Jádro systému</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Services</source>
      <translation>Služby</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Login</source>
      <translation>Uživatelské jméno</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Desktop</source>
      <translation>Desktop</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="73"/>
      <source>Applications</source>
      <translation>Aplikace</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="74"/>
      <source>Communication</source>
      <translation>Komunikace</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="75"/>
      <source>Development</source>
      <translation>Vývoj</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="76"/>
      <source>Office</source>
      <translation>Kancelář</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="77"/>
      <source>Multimedia</source>
      <translation>Multimédia</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="78"/>
      <source>Internet</source>
      <translation>Internet</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="79"/>
      <source>Theming</source>
      <translation>Motivy vzhledu</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="80"/>
      <source>Gaming</source>
      <translation>Hry</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="81"/>
      <source>Utilities</source>
      <translation>Nástroje</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="34"/>
      <source>Notes</source>
      <translation>Poznámky</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="28"/>
      <source>Ba&amp;tch:</source>
      <translation>&amp;Série:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="38"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Sem zadejte identifikátor série. Toto bude uloženo v cílovém systému.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;Nastavení pro OEM&lt;/h1&gt;&lt;p&gt;Calamares tato nastavení použije při nastavování cílového systému.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="121"/>
      <source>OEM Configuration</source>
      <translation>Nastavení pro OEM</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="126"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nastavit identifikátor OEM série na &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="62"/>
      <source>Timezone: %1</source>
      <translation>Časová zóna: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="77"/>
      <source>To be able to select a timezone, make sure you are connected to the internet. Restart the installer after connecting. You can fine-tune Language and Locale settings below.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="57"/>
      <source>Password is too short</source>
      <translation>Heslo je příliš krátké</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="73"/>
      <source>Password is too long</source>
      <translation>Heslo je příliš dlouhé</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="149"/>
      <source>Password is too weak</source>
      <translation>Heslo je příliš slabé</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="157"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Chyba přidělování paměti při nastavování „%1“</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
      <source>Memory allocation error</source>
      <translation>Chyba při přidělování paměti</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
      <source>The password is the same as the old one</source>
      <translation>Heslo je stejné jako to přechozí</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
      <source>The password is a palindrome</source>
      <translation>Heslo je palindrom (je stejné i pozpátku)</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
      <source>The password differs with case changes only</source>
      <translation>Heslo se liší pouze změnou velikosti písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
      <source>The password is too similar to the old one</source>
      <translation>Heslo je příliš podobné tomu předchozímu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
      <source>The password contains the user name in some form</source>
      <translation>Heslo obsahuje nějakou formou uživatelské jméno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Heslo obsahuje obsahuje nějakou formou slova ze jména uživatele</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="177"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Heslo obsahuje nějakou formou slova, která není možné použít</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="181"/>
      <source>The password contains less than %1 digits</source>
      <translation>Heslo obsahuje méně než %1 číslic</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
      <source>The password contains too few digits</source>
      <translation>Heslo obsahuje příliš málo číslic</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>The password contains less than %1 uppercase letters</source>
      <translation>Heslo obsahuje méně než %1 velkých písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Heslo obsahuje příliš málo velkých písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
      <source>The password contains less than %1 lowercase letters</source>
      <translation>Heslo obsahuje méně než %1 malých písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Heslo obsahuje příliš málo malých písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password contains less than %1 non-alphanumeric characters</source>
      <translation>Heslo obsahuje méně než %1 speciálních znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Heslo obsahuje příliš málo speciálních znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password is shorter than %1 characters</source>
      <translation>Heslo je kratší než %1 znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
      <source>The password is too short</source>
      <translation>Heslo je příliš krátké</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password is just rotated old one</source>
      <translation>Heslo je jen některé z předchozích</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains less than %1 character classes</source>
      <translation>Heslo obsahuje méně než %1 druhů znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password does not contain enough character classes</source>
      <translation>Heslo není tvořeno dostatečným počtem druhů znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains more than %1 same characters consecutively</source>
      <translation>Heslo obsahuje více než %1 stejných znaků za sebou</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="230"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Heslo obsahuje příliš mnoho stejných znaků za sebou</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="234"/>
      <source>The password contains more than %1 characters of the same class consecutively</source>
      <translation>Heslo obsahuje více než %1 znaků ze stejné třídy za sebou</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="238"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Heslo obsahuje příliš mnoho znaků stejného druhu za sebou</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains monotonic sequence longer than %1 characters</source>
      <translation>Heslo obsahuje monotónní posloupnost delší než %1 znaků</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Heslo obsahuje příliš dlouhou monotónní posloupnost</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>No password supplied</source>
      <translation>Nebylo zadáno žádné heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Nedaří se získat náhodná čísla ze zařízení generátoru náhodných čísel (RNG)</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="254"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Vytvoření hesla se nezdařilo – úroveň nahodilosti je příliš nízká</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="260"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Heslo je slovníkové – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password fails the dictionary check</source>
      <translation>Heslo je slovníkové</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
      <source>Unknown setting - %1</source>
      <translation>Neznámé nastavení – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
      <source>Unknown setting</source>
      <translation>Neznámé nastavení</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Chybná celočíselná hodnota nastavení – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>Bad integer value</source>
      <translation>Chybná celočíselná hodnota</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="284"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Nastavení %1 není typu celé číslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>Setting is not of integer type</source>
      <translation>Nastavení není typu celé číslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Setting %1 is not of string type</source>
      <translation>Nastavení %1 není typu řetězec</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>Setting is not of string type</source>
      <translation>Nastavení není typu řetězec</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="300"/>
      <source>Opening the configuration file failed</source>
      <translation>Nepodařilo se otevřít soubor s nastaveními</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The configuration file is malformed</source>
      <translation>Soubor s nastaveními nemá správný formát</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="304"/>
      <source>Fatal failure</source>
      <translation>Fatální nezdar</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown error</source>
      <translation>Neznámá chyba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="581"/>
      <source>Password is empty</source>
      <translation>Heslo není vyplněné</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="20"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="40"/>
      <source>Product Name</source>
      <translation>Název produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="53"/>
      <source>TextLabel</source>
      <translation>TextovýPopisek</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="69"/>
      <source>Long Product Description</source>
      <translation>Podrobnější popis produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="34"/>
      <source>Package Selection</source>
      <translation>Výběr balíčků</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="35"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Vyberte produkt ze seznamu. Ten vybraný bude nainstalován.</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="70"/>
      <source>Packages</source>
      <translation>Balíčky</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Name</source>
      <translation>Název</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Description</source>
      <translation>Popis</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
      <source>Keyboard Model:</source>
      <translation>Model klávesnice:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
      <source>Type here to test your keyboard</source>
      <translation>Klávesnici vyzkoušíte psaním sem</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
      <source>What is your name?</source>
      <translation>Jak se jmenujete?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="51"/>
      <source>Your Full Name</source>
      <translation>Vaše celé jméno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="120"/>
      <source>What name do you want to use to log in?</source>
      <translation>Jaké jméno chcete používat pro přihlašování do systému?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="144"/>
      <source>login</source>
      <translation>uživatelské jméno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="219"/>
      <source>What is the name of this computer?</source>
      <translation>Jaký je název tohoto počítače?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="243"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Pod tímto názvem se bude počítač případně zobrazovat ostatním počítačům v síti.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="246"/>
      <source>Computer Name</source>
      <translation>Název počítače</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="321"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Zvolte si heslo pro ochranu svého účtu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="345"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="370"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Zadání hesla zopakujte i do kontrolní kolonky, abyste měli jistotu, že jste napsali, co zamýšleli (že nedošlo k překlepu). Dobré heslo se bude skládat z písmen, číslic a interpunkce a mělo by být alespoň osm znaků dlouhé. Heslo byste také měli pravidelně měnit (prevence škod z jeho případného prozrazení).&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="351"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="521"/>
      <source>Password</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="376"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="546"/>
      <source>Repeat Password</source>
      <translation>Zopakování zadání hesla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="451"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Když je toto zaškrtnuto, je prověřována odolnost hesla a nebude umožněno použít snadno prolomitelné heslo.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="454"/>
      <source>Require strong passwords.</source>
      <translation>Vyžaduje odolné heslo.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="461"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Při spouštění systému se přihlašovat automaticky (bez zadávání hesla).</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="468"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Použít stejné heslo i pro účet správce systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="491"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Zvolte si heslo pro účet správce systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="515"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="540"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Zadání hesla zopakujte i do kontrolní kolonky, abyste měli jistotu, že jste napsali, co zamýšleli (že nedošlo k překlepu).&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Root</source>
      <translation>Kořenový (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="200"/>
      <source>Home</source>
      <translation>Složky uživatelů (home)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>Boot</source>
      <translation>Zaváděcí (boot)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
      <source>EFI system</source>
      <translation>EFI systémový</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Odkládání str. z oper. paměti (swap)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="209"/>
      <source>New partition for %1</source>
      <translation>Nový oddíl pro %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition</source>
      <translation>Nový oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="230"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1 %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="168"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="208"/>
      <source>Free Space</source>
      <translation>Volné místo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="172"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="212"/>
      <source>New partition</source>
      <translation>Nový oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="305"/>
      <source>Name</source>
      <translation>Název</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>File System</source>
      <translation>Souborový systém</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>Mount Point</source>
      <translation>Přípojný bod</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>Size</source>
      <translation>Velikost</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
      <source>Storage de&amp;vice:</source>
      <translation>Úložné zařízení</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
      <source>&amp;Revert All Changes</source>
      <translation>V&amp;rátit všechny změny</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
      <source>New Partition &amp;Table</source>
      <translation>Nová &amp;tabulka oddílů</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
      <source>Cre&amp;ate</source>
      <translation>Vytv&amp;ořit</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
      <source>&amp;Edit</source>
      <translation>&amp;Upravit</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
      <source>&amp;Delete</source>
      <translation>&amp;Smazat</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
      <source>New Volume Group</source>
      <translation>Nová skupina svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
      <source>Resize Volume Group</source>
      <translation>Změnit velikost skupiny svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
      <source>Deactivate Volume Group</source>
      <translation>Deaktivovat skupinu svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
      <source>Remove Volume Group</source>
      <translation>Odebrat skupinu svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Zavaděč systému &amp;nainstalovat na:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="211"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Opravdu chcete na %1 vytvořit novou tabulku oddílů?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="240"/>
      <source>Can not create new partition</source>
      <translation>Nedaří se vytvořit nový oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>Tabulka oddílů na %1 už obsahuje %2 hlavních oddílů a proto už není možné přidat další. Odeberte jeden z hlavních oddílů a namísto něj vytvořte rozšířený oddíl.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="77"/>
      <source>Gathering system information...</source>
      <translation>Shromažďování informací o systému…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="131"/>
      <source>Partitions</source>
      <translation>Oddíly</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="169"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Nainstalovat %1 &lt;strong&gt;vedle&lt;/strong&gt; dalšího operačního systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="174"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Smazat&lt;/strong&gt; obsah jednotky a nainstalovat %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="178"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Nahradit&lt;/strong&gt; oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="182"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;Ruční&lt;/strong&gt; dělení úložiště.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="195"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Nainstalovat %1 &lt;strong&gt;vedle&lt;/strong&gt; dalšího operačního systému na disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="202"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Vymazat&lt;/strong&gt; obsah jednotky &lt;strong&gt;%2&lt;/strong&gt; (%3) a nainstalovat %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="208"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Nahradit&lt;/strong&gt; oddíl na jednotce &lt;strong&gt;%2&lt;/strong&gt; (%3) %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="215"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;Ruční&lt;/strong&gt; dělení jednotky &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="224"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Jednotka &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="250"/>
      <source>Current:</source>
      <translation>Stávající:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="267"/>
      <source>After:</source>
      <translation>Potom:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="434"/>
      <source>No EFI system partition configured</source>
      <translation>Není nastavený žádný EFI systémový oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="435"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Pro spuštění %1 je potřeba EFI systémový oddíl.&lt;br/&gt;&lt;br/&gt;Pro nastavení EFI systémového oddílu se vraťte zpět a vyberte nebo vytvořte oddíl typu FAT32 s příznakem &lt;strong&gt;%3&lt;/strong&gt; a přípojným bodem &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Je možné pokračovat bez nastavení EFI systémového oddílu, ale systém nemusí jít spustit.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="449"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation>Pro spuštění %1 je potřeba EFI systémový oddíl.&lt;br/&gt;&lt;br/&gt;Byl nastaven oddíl s přípojným bodem &lt;strong&gt;%2&lt;/strong&gt; ale nemá nastaven příznak &lt;strong&gt;%3&lt;/strong&gt;.&lt;br/&gt;Pro nastavení příznaku se vraťte zpět a upravte oddíl.&lt;br/&gt;&lt;br/&gt;Je možné pokračovat bez nastavení příznaku, ale systém nemusí jít spustit.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="448"/>
      <source>EFI system partition flag not set</source>
      <translation>Příznak EFI systémového oddílu není nastavený</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="475"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Volba použít GPT i pro BIOS zavádění (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="476"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>GPT tabulka oddílů je nejlepší volbou pro všechny systémy. Tento instalátor podporuje takové uspořádání i pro zavádění v režimu BIOS firmware.&lt;br/&gt;&lt;br/&gt;Pro nastavení GPT tabulky oddílů v případě BIOS, (pokud už není provedeno) jděte zpět a nastavte tabulku oddílů na, dále vytvořte 8 MB oddíl (bez souborového systému s příznakem &lt;strong&gt;bios_grub&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Tento oddíl je zapotřebí pro spuštění %1 na systému s BIOS firmware/režimem a GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="504"/>
      <source>Boot partition not encrypted</source>
      <translation>Zaváděcí oddíl není šifrován</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="505"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Kromě šifrovaného kořenového oddílu byl vytvořen i nešifrovaný oddíl zavaděče.&lt;br/&gt;&lt;br/&gt;To by mohl být bezpečnostní problém, protože na nešifrovaném oddílu jsou důležité soubory systému.&lt;br/&gt;Pokud chcete, můžete pokračovat, ale odemykání souborového systému bude probíhat později při startu systému.&lt;br/&gt;Pro zašifrování oddílu zavaděče se vraťte a vytvořte ho vybráním možnosti &lt;strong&gt;Šifrovat&lt;/strong&gt; v okně při vytváření oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="722"/>
      <source>has at least one disk device available.</source>
      <translation>má k dispozici alespoň jedno zařízení pro ukládání dat.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="723"/>
      <source>There are no partitions to install on.</source>
      <translation>Nejsou zde žádné oddíly na které by se dalo nainstalovat.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Úloha vzhledu a dojmu z Plasma</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Nedaří se vybrat balíček KDE Plasma Look-and-Feel</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="70"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Zvolte vzhled a chování KDE Plasma desktopu. Tento krok je také možné přeskočit a nastavit až po instalaci systému. Kliknutí na výběr vyvolá zobrazení náhledu daného vzhledu a chování.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="76"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Zvolte vzhled a chování KDE Plasma desktopu. Tento krok je také možné přeskočit a nastavit až po instalaci systému. Kliknutí na výběr vyvolá zobrazení náhledu daného vzhledu a chování.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
      <source>Look-and-Feel</source>
      <translation>Vzhled a dojem z</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="84"/>
      <source>Saving files for later ...</source>
      <translation>Ukládání souborů pro pozdější využití…</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="122"/>
      <source>No files configured to save for later.</source>
      <translation>U žádných souborů nebylo nastaveno, že mají být uloženy pro pozdější využití.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="176"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Ne všechny nastavené soubory bylo možné zachovat.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="422"/>
      <source>
There was no output from the command.</source>
      <translation>
Příkaz neposkytl žádný výstup.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>
Output:
</source>
      <translation>
Výstup:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="427"/>
      <source>External command crashed.</source>
      <translation>Vnější příkaz byl neočekávaně ukončen.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Příkaz &lt;i&gt;%1&lt;/i&gt; byl neočekávaně ukončen.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="433"/>
      <source>External command failed to start.</source>
      <translation>Vnější příkaz se nepodařilo spustit.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Příkaz &lt;i&gt;%1&lt;/i&gt; se nepodařilo spustit.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="438"/>
      <source>Internal error when starting command.</source>
      <translation>Vnitřní chyba při spouštění příkazu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="439"/>
      <source>Bad parameters for process job call.</source>
      <translation>Chybné parametry volání úlohy procesu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="443"/>
      <source>External command failed to finish.</source>
      <translation>Vnější příkaz se nepodařilo dokončit.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="444"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Příkaz &lt;i&gt;%1&lt;/i&gt; se nepodařilo dokončit do %2 sekund.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="451"/>
      <source>External command finished with errors.</source>
      <translation>Vnější příkaz skončil s chybami.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="452"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Příkaz &lt;i&gt;%1&lt;/i&gt; skončil s návratovým kódem %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Label.cpp" line="41"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="40"/>
      <source>unknown</source>
      <translation>neznámý</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="42"/>
      <source>extended</source>
      <translation>rozšířený</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="44"/>
      <source>unformatted</source>
      <translation>nenaformátovaný</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="46"/>
      <source>swap</source>
      <translation>odkládací oddíl</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="91"/>
      <source>Default Keyboard Model</source>
      <translation>Výchozí model klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="133"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="168"/>
      <source>Default</source>
      <translation>Výchozí</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="73"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="81"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="85"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="102"/>
      <source>File not found</source>
      <translation>Soubor nenalezen</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="74"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Je třeba, aby &lt;pre&gt;%1&lt;/pre&gt;byl úplný popis umístění. </translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="103"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nepodařilo se vytvořit nový náhodný soubor &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="79"/>
      <source>No product</source>
      <translation>Žádný produkt</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="87"/>
      <source>No description provided.</source>
      <translation>Nebyl poskytnut žádný popis.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="47"/>
      <source>(no mount point)</source>
      <translation>(žádný přípojný bod)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="51"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Nerozdělené prázné místo nebo neznámá tabulka oddílů</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="49"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="43"/>
      <source>Remove live user from target system</source>
      <translation>Odebrat uživatele živé relace z cílového systému</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="45"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Odebrat skupinu svazků nazvanou %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="39"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Odebrat skupinu svazků nazvanou &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Instalátoru se nepodařilo odebrat skupinu svazků nazvanou „%1“.</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="140"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Vyberte, kam nainstalovat %1.&lt;br/&gt;&lt;font color="red"&gt;Upozornění: &lt;/font&gt;tímto smažete všechny soubory ve vybraném oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="166"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Vybraná položka se nezdá být platným oddílem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="174"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 nemůže být instalován na místo bez oddílu. Vyberte existující oddíl.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="184"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 nemůže být instalován na rozšířený oddíl. Vyberte existující primární nebo logický oddíl.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 nemůže být instalován na tento oddíl.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="201"/>
      <source>Data partition (%1)</source>
      <translation>Datový oddíl (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="217"/>
      <source>Unknown system partition (%1)</source>
      <translation>Neznámý systémový oddíl (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="222"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 systémový oddíl (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="233"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Oddíl %1 je příliš malý pro %2. Vyberte oddíl s kapacitou alespoň %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="256"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;EFI systémový oddíl nenalezen. Vraťte se, zvolte ruční rozdělení jednotky, a nastavte %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="284"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="308"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 bude instalován na %2.&lt;br/&gt;&lt;font color="red"&gt;Upozornění: &lt;/font&gt;všechna data v oddílu %2 budou ztracena.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="276"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>Pro zavedení %2 se využije EFI systémový oddíl %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="292"/>
      <source>EFI system partition:</source>
      <translation>EFI systémový oddíl:</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="47"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="49"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="57"/>
      <source>Resize Filesystem Job</source>
      <translation>Úloha změny velikosti souborového systému</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>Invalid configuration</source>
      <translation>Neplatné nastavení</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="171"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>Úloha změny velikosti souborového systému nemá platné nastavení a nebude spuštěna.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="177"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore není k dispozici</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="178"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>Kalamares nemůže spustit KPMCore pro úlohu změny velikosti souborového systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="208"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="234"/>
      <source>Resize Failed</source>
      <translation>Změna velikosti se nezdařila</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>Souborový systém %1 nebyl na tomto systému nalezen a jeho velikost proto nemůže být změněna.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="188"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>Zařízení %1 nebylo na tomto systému nalezeno a proto nemůže být jeho velikost změněna.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="209"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>Velikost souborového systému %1 není možné změnit.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="197"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="210"/>
      <source>The device %1 cannot be resized.</source>
      <translation>Velikost zařízení %1 nelze měnit.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="218"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>Velikost souborového systému %1 je třeba změnit, ale není to možné.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="219"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>Velikost zařízení %1 je třeba změnit, ale není to možné</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="49"/>
      <source>Resize partition %1.</source>
      <translation>Změnit velikost oddílu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="56"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>Změnit velikost &lt;strong&gt;%2MiB&lt;/strong&gt; oddílu &lt;strong&gt;%1&lt;/strong&gt; na &lt;strong&gt;%3MiB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="67"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Změna velikosti %2MiB oddílu %1 na %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="86"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Instalátoru se nepodařilo změnit velikost oddílu %1 na jednotce „%2“.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="39"/>
      <source>Resize Volume Group</source>
      <translation>Změnit velikost skupiny svazků</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="54"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>Změnit skupinu svazků nazvanou %1 z %2 na %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Změnit velikost skupiny nazvané &lt;strong&gt;%1&lt;/strong&gt; z &lt;strong&gt;%&lt;/strong&gt; na &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="69"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Instalátoru se nepodařilo změnit velikost skupiny svazků zvanou „%1“.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="142"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>Nejlepších výsledků se dosáhne, pokud tento počítač bude:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="143"/>
      <source>System requirements</source>
      <translation>Požadavky na systém</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="265"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Počítač nesplňuje minimální požadavky pro instalaci %1.&lt;br/&gt;Instalace nemůže pokračovat &lt;a href="#details"&gt;Podrobnosti…&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="269"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Počítač nesplňuje minimální požadavky pro instalaci %1.&lt;br/&gt;Instalace nemůže pokračovat &lt;a href="#details"&gt;Podrobnosti…&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="276"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Počítač nesplňuje některé doporučené požadavky pro instalaci %1.&lt;br/&gt;Instalace může pokračovat, ale některé funkce mohou být vypnuty.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="280"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Počítač nesplňuje některé doporučené požadavky pro instalaci %1.&lt;br/&gt;Instalace může pokračovat, ale některé funkce mohou být vypnuty.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="289"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Tento program vám položí několik dotazů, aby na základě odpovědí příslušně nainstaloval %2 na váš počítač.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
      <source>Scanning storage devices...</source>
      <translation>Skenování úložných zařízení…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
      <source>Partitioning</source>
      <translation>Dělení jednotky</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="46"/>
      <source>Set hostname %1</source>
      <translation>Nastavit název počítače %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="53"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nastavit název počítače &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="60"/>
      <source>Setting hostname %1.</source>
      <translation>Nastavuje se název počítače %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="131"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="138"/>
      <source>Internal Error</source>
      <translation>Vnitřní chyba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="155"/>
      <source>Cannot write hostname to target system</source>
      <translation>Název počítače se nedaří zapsat do cílového systému</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Nastavit model klávesnice na %1, rozložení na %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="351"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Zápis nastavení klávesnice pro virtuální konzoli se nezdařil.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="352"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="356"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="363"/>
      <source>Failed to write to %1</source>
      <translation>Zápis do %1 se nezdařil</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="355"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Zápis nastavení klávesnice pro grafický server X11 se nezdařil.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="362"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Zápis nastavení klávesnice do existující složky /etc/default se nezdařil.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
      <source>Set flags on partition %1.</source>
      <translation>Nastavit příznaky na oddílu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="58"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>Nastavit příznaky na %1MiB %2 oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="62"/>
      <source>Set flags on new partition.</source>
      <translation>Nastavit příznaky na novém oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Vymazat příznaky z oddílu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Odstranit příznaky z %1MiB &lt;strong&gt;%2&lt;/strong&gt; oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="84"/>
      <source>Clear flags on new partition.</source>
      <translation>Vymazat příznaky z nového oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Nastavit příznak oddílu &lt;strong&gt;%1&lt;/strong&gt; jako &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Označit %1MiB &lt;strong&gt;%2&lt;/strong&gt; oddíl jako &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nastavit příznak &lt;strong&gt;%1&lt;/strong&gt; na novém oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Mazání příznaků oddílu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="123"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Odstraňování příznaků na %1MiB &lt;strong&gt;%2&lt;/strong&gt; oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="128"/>
      <source>Clearing flags on new partition.</source>
      <translation>Mazání příznaků na novém oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nastavování příznaků &lt;strong&gt;%2&lt;/strong&gt; na oddílu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="142"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Nastavování příznaků &lt;strong&gt;%3&lt;/strong&gt; na %1MiB &lt;strong&gt;%2&lt;/strong&gt; oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Nastavování příznaků &lt;strong&gt;%1&lt;/strong&gt; na novém oddílu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="165"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Instalátoru se nepodařilo nastavit příznak na oddílu %1</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="49"/>
      <source>Set password for user %1</source>
      <translation>Nastavit heslo pro uživatele %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="56"/>
      <source>Setting password for user %1.</source>
      <translation>Nastavuje se heslo pro uživatele %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <source>Bad destination system path.</source>
      <translation>Chybný popis cílového umístění systému.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="91"/>
      <source>rootMountPoint is %1</source>
      <translation>Přípojný bod kořenového souborového systému (root) je %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot disable root account.</source>
      <translation>Nedaří se zakázat účet správce systému (root).</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>passwd terminated with error code %1.</source>
      <translation>Příkaz passwd ukončen s chybovým kódem %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="106"/>
      <source>Cannot set password for user %1.</source>
      <translation>Nepodařilo se nastavit heslo uživatele %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>usermod terminated with error code %1.</source>
      <translation>Příkaz usermod ukončen s chybovým kódem %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
      <source>Set timezone to %1/%2</source>
      <translation>Nastavit časové pásmo na %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Není přístup k vybranému popisu umístění časové zóny.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Bad path: %1</source>
      <translation>Chybný popis umístění: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <translation>Časovou zónu se nedaří nastavit.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Odkaz se nepodařilo vytvořit, cíl: %1; název odkazu: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
      <source>Cannot set timezone,</source>
      <translation>Nedaří se nastavit časovou zónu, </translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Soubor /etc/timezone se nedaří otevřít pro zápis</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="46"/>
      <source>Shell Processes Job</source>
      <translation>Úloha shellových procesů</translation>
    </message>
  </context>
  <context>
    <name>SlideCounter</name>
    <message>
      <location filename="../src/qml/calamares/slideshow/SlideCounter.qml" line="36"/>
      <source>%L1 / %L2</source>
      <extracomment>slide counter, %1 of %2 (numeric)</extracomment>
      <translation>%L1 / %L2</translation>
    </message>
  </context>
  <context>
    <name>SummaryPage</name>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="57"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Toto je přehled událostí které nastanou po spuštění instalačního procesu.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="60"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Toto je přehled událostí které nastanou po spuštění instalačního procesu.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
      <source>Summary</source>
      <translation>Souhrn</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="46"/>
      <source>Installation feedback</source>
      <translation>Zpětná vazba z instalace</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="58"/>
      <source>Sending installation feedback.</source>
      <translation>Posílání zpětné vazby z instalace.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="75"/>
      <source>Internal error in install-tracking.</source>
      <translation>Vnitřní chyba v install-tracking.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="76"/>
      <source>HTTP request timed out.</source>
      <translation>Překročen časový limit HTTP požadavku.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="202"/>
      <source>KDE user feedback</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="214"/>
      <source>Configuring KDE user feedback.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="236"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="242"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="237"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="243"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="120"/>
      <source>Machine feedback</source>
      <translation>Zpětná vazba stroje</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="132"/>
      <source>Configuring machine feedback.</source>
      <translation>Nastavování zpětné vazby stroje</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="155"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="161"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Chyba v nastavení zpětné vazby stroje.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="156"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Nepodařilo se správně nastavit zpětnou vazbu stroje, chyba skriptu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="162"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Nepodařilo se správně nastavit zpětnou vazbu stroje, chyba Calamares %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
      <source>Placeholder</source>
      <translation>Výplň</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Kliknutím sem se dozvíte více o zpětné vazbě od uživatelů&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="58"/>
      <source>Feedback</source>
      <translation>Zpětná vazba</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="149"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Pokud bude tento počítač používat více lidí, můžete přidat uživatelské účty po dokončení instalace.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="155"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Pokud bude tento počítač používat více lidí, můžete přidat uživatelské účty po dokončení instalace.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="395"/>
      <source>Your username is too long.</source>
      <translation>Vaše uživatelské jméno je příliš dlouhé.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="402"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Je třeba, aby uživatelské jméno začínalo na malé písmeno nebo podtržítko.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="409"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Je možné použít pouze malá písmena, číslice, podtržítko a spojovník.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="445"/>
      <source>Your hostname is too short.</source>
      <translation>Název stroje je příliš krátký.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="450"/>
      <source>Your hostname is too long.</source>
      <translation>Název stroje je příliš dlouhý.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="457"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Je možné použít pouze písmena, číslice, podtržítko a spojovník.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="474"/>
      <source>Your passwords do not match!</source>
      <translation>Zadání hesla se neshodují!</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="76"/>
      <source>Users</source>
      <translation>Uživatelé</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="241"/>
      <source>Key</source>
      <translation>Klíč</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="245"/>
      <source>Value</source>
      <translation>Hodnota</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
      <source>Create Volume Group</source>
      <translation>Vytvořit skupinu svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
      <source>List of Physical Volumes</source>
      <translation>Seznam fyzických svazků</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
      <source>Volume Group Name:</source>
      <translation>Název skupiny svazků:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
      <source>Volume Group Type:</source>
      <translation>Typ skupiny svazků:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
      <source>Physical Extent Size:</source>
      <translation>Velikost fyzického bloku dat:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
      <source>Total Size:</source>
      <translation>Celková velikost:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
      <source>Used Size:</source>
      <translation>Využitá velikost:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
      <source>Total Sectors:</source>
      <translation>Celkem sektorů:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
      <source>Quantity of LVs:</source>
      <translation>Počet logických svazků:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulář</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="94"/>
      <source>Select application and system language</source>
      <translation>Vybrat jazyk pro aplikace a systém</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="136"/>
      <source>&amp;About</source>
      <translation>&amp;O projektu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
      <source>Open donations website</source>
      <translation>Otevřít webovou stránku po poskytnutí daru</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="149"/>
      <source>&amp;Donate</source>
      <translation>&amp;Darovat</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="159"/>
      <source>Open help and support website</source>
      <translation>Otevřít webovou stránku s nápovědou a podporou</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="162"/>
      <source>&amp;Support</source>
      <translation>&amp;Podpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="172"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Otevřít webovou stránku se správou hlášení problémů</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="175"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Známé problémy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="185"/>
      <source>Open release notes website</source>
      <translation>Otevřít webovou stránku s poznámkami k vydání</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="188"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Poznámky k vydání</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="225"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vítejte v Calamares,  instalačním programu (nejen) pro %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="226"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vítejte v instalátoru pro %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="231"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vítejte v Calamares,  instalačním programu (nejen) pro %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="232"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vítejte v instalátoru %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="237"/>
      <source>%1 support</source>
      <translation>%1 podpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="244"/>
      <source>About %1 setup</source>
      <translation>O nastavování %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="244"/>
      <source>About %1 installer</source>
      <translation>O instalátoru %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Poděkování &lt;a href="https://calamares.io/team/"&gt;týmu Calamares&lt;/a&gt; a &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;týmu překladatelů Calamares&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; vývoj je sponzorován &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; – Liberating Software.</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="50"/>
      <source>Welcome</source>
      <translation>Vítejte</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="57"/>
      <source>Welcome</source>
      <translation>Vítejte</translation>
    </message>
  </context>
  <context>
    <name>about</name>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="56"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;
                        &lt;strong&gt;%2&lt;br/&gt;
                        for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;
                        Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;
                        Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;
                        Thanks to &lt;a href='https://calamares.io/team/'&gt;the Calamares team&lt;/a&gt; 
                        and the &lt;a href='https://www.transifex.com/calamares/calamares/'&gt;Calamares 
                        translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;
                        &lt;a href='https://calamares.io/'&gt;Calamares&lt;/a&gt; 
                        development is sponsored by &lt;br/&gt;
                        &lt;a href='http://www.blue-systems.com/'&gt;Blue Systems&lt;/a&gt; - 
                        Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="105"/>
      <source>Back</source>
      <translation>Zpět</translation>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="59"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="120"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="174"/>
      <source>Back</source>
      <translation>Zpět</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="25"/>
      <source>Keyboard Model</source>
      <translation>Model klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="26"/>
      <source>Pick your preferred keyboard model or use the default one based on the detected hardware</source>
      <translation>Vyberte vámi upřednostňovaný model klávesnice nebo použijte ten výchozí, založený na zjištěném hardware</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="41"/>
      <source>Refresh</source>
      <translation>Načíst znovu</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="51"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="163"/>
      <source>Layouts</source>
      <translation>Rovzržení</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="79"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="139"/>
      <source>Keyboard Layout</source>
      <translation>Rozvržení klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="101"/>
      <source>Models</source>
      <translation>Modely</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="109"/>
      <source>Variants</source>
      <translation>Varianty</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="189"/>
      <source>Test your keyboard</source>
      <translation>Vyzkoušejte si svou klávesnici</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="98"/>
      <source>System language set to %1</source>
      <translation>Jazyk systému nastaven na %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="106"/>
      <source>Numbers and dates locale set to %1</source>
      <translation>Místní formát čísel a data nastaven na %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="112"/>
      <source>Change</source>
      <translation>Změnit</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="61"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Toto je příklad poznámek k vydání.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>release_notes</name>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="54"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;This an example QML file, showing options in RichText with Flickable content.&lt;/p&gt;

            &lt;p&gt;QML with RichText can use HTML tags, Flickable content is useful for touchscreens.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;This is bold text&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;This is italic text&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;This is underlined text&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;This text will be center-aligned.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;This is strikethrough&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Code example:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Lists:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU systems&lt;/li&gt;
                &lt;li&gt;AMD CPU systems&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;The vertical scrollbar is adjustable, current width set to 10.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Toto je ukázka QML souboru, zobrazující možnosti formátovaného textu s pohyblivým (flickable) obsahem.&lt;/p&gt;

            &lt;p&gt;QML s formátovaným textem může využívat HTML značky, pohyblivý obsah je užitečný pro dotykové obrazovky.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Toto je tučný text&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;Toto je skloněný text (kurzíva)&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;Toto je podtržený text&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Tento text bude zarovnán na střed.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;Toto je přeškrtnuté&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Ukázka zobrazení zdrojového kódu:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;/b&gt;Seznam:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;systémy s procesorem Intel&lt;/li&gt;
                &lt;li&gt;systémy s procesorem AMD&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Svislý posuvník je přizpůsobitelný, stávající výška je nastavena na 10.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="85"/>
      <source>Back</source>
      <translation>Zpět</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="44"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Vítejte v instalátoru %1 &lt;quote&gt;%2&lt;/quote&gt;&lt;/h3&gt;
            &lt;p&gt;Tato aplikace vám položí několik otázek a na základě odpovědí příslušně nainstaluje %1 na váš počítač.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="75"/>
      <source>About</source>
      <translation>O projektu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="89"/>
      <source>Support</source>
      <translation>Podpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="100"/>
      <source>Known issues</source>
      <translation>Známé problémy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="111"/>
      <source>Release notes</source>
      <translation>Poznámky k vydání</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="123"/>
      <source>Donate</source>
      <translation>Podpořit vývoj darem</translation>
    </message>
  </context>
</TS>

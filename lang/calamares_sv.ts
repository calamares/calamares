<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="sv" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="71"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>Systemets &lt;strong&gt;startmiljö&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Äldre x86-system stöder endast &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Moderna system stöder vanligen &lt;strong&gt;EFI&lt;/strong&gt;, men kan också vara i kompatibilitetsläge för BIOS.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="81"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Detta system startades med en &lt;strong&gt;EFI-miljö&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;För att ställa in start från en EFI-miljö måste en starthanterare användas, t.ex. &lt;strong&gt;GRUB&lt;/strong&gt; eller &lt;strong&gt;systemd-boot&lt;/strong&gt; på en &lt;strong&gt;EFI-systempartition&lt;/strong&gt;. Detta sker automatiskt, såvida du inte väljer att partitionera manuellt. Då måste du själv installera en starthanterare.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="93"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Detta system startades med en &lt;strong&gt;BIOS-miljö&lt;/strong&gt;. &lt;br&gt;&lt;br&gt;För att ställa in start från en BIOS-miljö måste en starthanterare som t.ex. &lt;strong&gt;GRUB&lt;/strong&gt; installeras, antingen i början av en partition eller på &lt;strong&gt;huvudstartsektorn (MBR)&lt;/strong&gt; i början av partitionstabellen. Detta sker automatiskt, såvida du inte väljer manuell partitionering. Då måste du själv installera en starthanterare.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="68"/>
      <source>Master Boot Record of %1</source>
      <translation>Master Boot Record på %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="102"/>
      <source>Boot Partition</source>
      <translation>Startpartition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="109"/>
      <source>System Partition</source>
      <translation>Systempartition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="139"/>
      <source>Do not install a boot loader</source>
      <translation>Installera inte någon starthanterare</translation>
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
      <translation>Tom sida</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="24"/>
      <source>GlobalStorage</source>
      <translation>GlobalStorage</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="34"/>
      <source>JobQueue</source>
      <translation>JobQueue</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="44"/>
      <source>Modules</source>
      <translation>Moduler</translation>
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
      <translation>ingen</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="71"/>
      <source>Interface:</source>
      <translation>Gränssnitt:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="93"/>
      <source>Tools</source>
      <translation>Verktyg</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="106"/>
      <source>Reload Stylesheet</source>
      <translation>Ladda om stilmall</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="113"/>
      <source>Widget Tree</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="231"/>
      <source>Debug information</source>
      <translation>Avlusningsinformation</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="92"/>
      <source>Set up</source>
      <translation>Inställningar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="92"/>
      <source>Install</source>
      <translation>Installera</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="39"/>
      <source>Job failed (%1)</source>
      <translation>Uppgiften misslyckades (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="40"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="114"/>
      <source>Done</source>
      <translation>Klar</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="27"/>
      <source>Example job (%1)</source>
      <translation>Exempel jobb (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source>Run command '%1' in target system.</source>
      <translation>Kör kommandot '%1'. på målsystem.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source> Run command '%1'.</source>
      <translation>Kör kommandot '%1'.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="59"/>
      <source>Running command %1 %2</source>
      <translation>Kör kommando %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="210"/>
      <source>Running %1 operation.</source>
      <translation>Kör %1-operation</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="239"/>
      <source>Bad working directory path</source>
      <translation>Arbetskatalogens sökväg är ogiltig</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="240"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Arbetskatalog %1 för pythonuppgift %2 är inte läsbar.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="246"/>
      <source>Bad main script file</source>
      <translation>Ogiltig huvudskriptfil</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="247"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Huvudskriptfil %1 för pythonuppgift %2 är inte läsbar.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="315"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost.Python-fel i uppgift "%'1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="76"/>
      <source>Loading ...</source>
      <translation>Laddar ...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="97"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML steg &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="261"/>
      <source>Loading failed.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="164"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Väntar på %n modul(er).</numerusform>
        <numerusform>Väntar på %n modul(er).</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="165"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n sekund(er))</numerusform>
        <numerusform>(%n sekund(er))</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="170"/>
      <source>System-requirements checking is complete.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Setup Failed</source>
      <translation>Inställningarna misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Installation Failed</source>
      <translation>Installationen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="154"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="167"/>
      <source>Error</source>
      <translation>Fel</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="174"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="518"/>
      <source>&amp;Yes</source>
      <translation>&amp;Ja</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="175"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>&amp;No</source>
      <translation>&amp;Nej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="181"/>
      <source>&amp;Close</source>
      <translation>&amp;Stäng</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>Install Log Paste URL</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="195"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Sändningen misslyckades. Ingenting sparades på webbplatsen.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="211"/>
      <source>Calamares Initialization Failed</source>
      <translation>Initieringen av Calamares misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="212"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Följande moduler kunde inte hämtas:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="328"/>
      <source>Continue with setup?</source>
      <translation>Fortsätt med installation?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="328"/>
      <source>Continue with installation?</source>
      <translation>Vill du fortsätta med installationen?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="333"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1-installeraren är på väg att göra ändringar för att installera %2.&lt;br/&gt;&lt;strong&gt;Du kommer inte att kunna ångra dessa ändringar.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="336"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Installera nu </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="336"/>
      <source>&amp;Install now</source>
      <translation>&amp;Installera nu</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>Go &amp;back</source>
      <translation>Gå &amp;bakåt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Set up</source>
      <translation>&amp;Installera</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Install</source>
      <translation>&amp;Installera</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="394"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Installationen är klar. Du kan avsluta installationsprogrammet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Installationen är klar. Du kan avsluta installationshanteraren.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Avbryt inställningarna utan att förändra systemet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Avbryt installationen utan att förändra systemet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>&amp;Next</source>
      <translation>&amp;Nästa</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="413"/>
      <source>&amp;Back</source>
      <translation>&amp;Bakåt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Done</source>
      <translation>&amp;Klar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="438"/>
      <source>&amp;Cancel</source>
      <translation>Avbryt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel setup?</source>
      <translation>Avbryt inställningarna?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel installation?</source>
      <translation>Avbryt installation?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="512"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Är du säker på att du vill avsluta installationen i förtid?
Alla ändringar kommer att gå förlorade.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="297"/>
      <source>Unknown exception type</source>
      <translation>Okänd undantagstyp</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="315"/>
      <source>unparseable Python error</source>
      <translation>Otolkbart Pythonfel</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="359"/>
      <source>unparseable Python traceback</source>
      <translation>Otolkbar Python-traceback</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="366"/>
      <source>Unfetchable Python error.</source>
      <translation>Ohämtbart Pythonfel</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="34"/>
      <source>Install log posted to:
%1</source>
      <translation>Installationslogg postad till:
%1</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="106"/>
      <source>Show debug information</source>
      <translation>Visa avlusningsinformation</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="172"/>
      <source>&amp;Back</source>
      <translation>&amp;Bakåt</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="184"/>
      <source>&amp;Next</source>
      <translation>&amp;Nästa</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="197"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Avsluta</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="281"/>
      <source>%1 Setup Program</source>
      <translation>%1 Installationsprogram</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="282"/>
      <source>%1 Installer</source>
      <translation>%1-installationsprogram</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="46"/>
      <source>Gathering system information...</source>
      <translation>Samlar systeminformation...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="156"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Välj lagringsenhet:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="157"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1088"/>
      <source>Current:</source>
      <translation>Nuvarande:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="158"/>
      <source>After:</source>
      <translation>Efter:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="334"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself. Having a GPT partition table and &lt;strong&gt;fat32 512Mb /boot partition is a must for UEFI installs&lt;/strong&gt;, either use an existing without formatting or create one.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="833"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Återanvänd %1 som hempartition för %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Välj en partition att minska, sen dra i nedre fältet för att ändra storlek&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 kommer att förminskas till %2MiB och en ny %3MiB partition kommer att skapas för %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1030"/>
      <source>Boot loader location:</source>
      <translation>Sökväg till starthanterare:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1079"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Välj en partition att installera på&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1135"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Ingen EFI-partition kunde inte hittas på systemet. Gå tillbaka och partitionera din lagringsenhet manuellt för att ställa in %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1144"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-partitionen %1 kommer att användas för att starta %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1152"/>
      <source>EFI system partition:</source>
      <translation>EFI-partition:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet ser inte ut att ha ett operativsystem installerat. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring görs på lagringseneheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1275"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1313"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1336"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1362"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Rensa lagringsenhet&lt;/strong&gt;&lt;br/&gt;Detta kommer &lt;font color="red"&gt;radera&lt;/font&gt; all existerande data på den valda lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1309"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1332"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1358"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Installera på sidan om&lt;/strong&gt;&lt;br/&gt;Installationshanteraren kommer krympa en partition för att göra utrymme för %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1283"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1318"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1340"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1366"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Ersätt en partition&lt;/strong&gt;&lt;br/&gt;Ersätter en partition med %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1303"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har %1 på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring görs på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1327"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har redan ett operativsystem på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring sker på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1353"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har flera operativsystem på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring sker på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1507"/>
      <source>No Swap</source>
      <translation>Ingen Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1512"/>
      <source>Reuse Swap</source>
      <translation>Återanvänd Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1515"/>
      <source>Swap (no Hibernate)</source>
      <translation>Swap (utan viloläge)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1518"/>
      <source>Swap (with Hibernate)</source>
      <translation>Swap (med viloläge)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1521"/>
      <source>Swap to file</source>
      <translation>Använd en fil som växlingsenhet</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="50"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Rensa monteringspunkter för partitionering på %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="57"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Rensar monteringspunkter för partitionering på %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="232"/>
      <source>Cleared all mounts for %1</source>
      <translation>Rensade alla monteringspunkter för %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
      <source>Clear all temporary mounts.</source>
      <translation>Rensa alla tillfälliga monteringspunkter.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Rensar alla tillfälliga monteringspunkter.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="61"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Kunde inte hämta tillfälliga monteringspunkter.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="102"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Rensade alla tillfälliga monteringspunkter</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="150"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="163"/>
      <source>Could not run command.</source>
      <translation>Kunde inte köra kommandot.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="151"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Kommandot behöver veta användarnamnet, men inget användarnamn är definerat.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="348"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Sätt tangenbordsmodell till %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="355"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Sätt tangentbordslayout till %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="279"/>
      <source>The system language will be set to %1.</source>
      <translation>Systemspråket kommer ändras till %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="280"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="313"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Sätt tidszon till %1/%2.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="47"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Nätverksinstallation. (Inaktiverad: inkorrekt konfiguration)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="49"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="51"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation>Nätverksinstallation. (Inaktiverad: internt fel)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Nätverksinstallation. (Inaktiverad: Kan inte hämta paketlistor, kontrollera nätverksanslutningen)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="54"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Datorn uppfyller inte minimikraven för inställning av %1.&lt;br/&gt;Inga inställningar kan inte göras. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="58"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Denna dator uppfyller inte minimikraven för att installera %1.&lt;br/&gt;Installationen kan inte fortsätta. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="65"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Några av kraven för inställning av %1 uppfylls inte av datorn.&lt;br/&gt;Inställningarna kan ändå göras men vissa funktioner kommer kanske inte att kunna användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="69"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Denna dator uppfyller inte alla rekommenderade krav för att installera %1.&lt;br/&gt;Installationen kan fortsätta, men alla alternativ och funktioner kanske inte kan användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="79"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Detta program kommer att ställa dig några frågor och installera %2 på din dator.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="230"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till Calamares installationsprogrammet för %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="231"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1 installation.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="236"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till installationsprogrammet Calamares för %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="237"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1-installeraren.&lt;/h1&gt;</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="128"/>
      <source>Contextual Processes Job</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
      <source>Create a Partition</source>
      <translation>Skapa en partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
      <source>Si&amp;ze:</source>
      <translation>Storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
      <source>Partition &amp;Type:</source>
      <translation>Partitions&amp;typ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
      <source>&amp;Primary</source>
      <translation>&amp;Primär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
      <source>E&amp;xtended</source>
      <translation>Utökad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
      <source>LVM LV name</source>
      <translation>LVM LV namn</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Monteringspunkt:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
      <source>Flags:</source>
      <translation>Flaggor:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="74"/>
      <source>En&amp;crypt</source>
      <translation>Kr%yptera</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="159"/>
      <source>Logical</source>
      <translation>Logisk</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="164"/>
      <source>Primary</source>
      <translation>Primär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="181"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="271"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Monteringspunkt används redan. Välj en annan.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="47"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Skapa ny %2MiB partition på %4 (%3) med filsystem %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="58"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa ny &lt;strong&gt;%2MiB&lt;/strong&gt;partition på &lt;strong&gt;%4&lt;/strong&gt; (%3) med filsystem &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="70"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Skapar ny %1 partition på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="82"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Installationsprogrammet kunde inte skapa partition på disk '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
      <source>Create Partition Table</source>
      <translation>Skapa partitionstabell</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Skapa en ny partitionstabell och ta bort alla befintliga data på disken.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Vilken typ av partitionstabell vill du skapa?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID-partitionstabell (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="48"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Skapa ny %1 partitionstabell på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="56"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Skapa ny &lt;strong&gt;%1&lt;/strong&gt; partitionstabell på &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="66"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Skapar ny %1 partitionstabell på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="84"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Installationsprogrammet kunde inte skapa en partitionstabell på %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
      <source>Create user %1</source>
      <translation>Skapar användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa användare &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
      <source>Creating user %1.</source>
      <translation>Skapar användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
      <source>Sudoers dir is not writable.</source>
      <translation>Sudoerkatalogen är inte skrivbar.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="89"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Kunde inte skapa sudoerfil för skrivning.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Kunde inte chmodda sudoerfilen.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="107"/>
      <source>Cannot open groups file for reading.</source>
      <translation>Kunde inte öppna gruppfilen för läsning.</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="37"/>
      <source>Create Volume Group</source>
      <translation>Skapa volymgrupp</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named %1.</source>
      <translation>Skapa ny volymgrupp med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa ny volymgrupp med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="49"/>
      <source>Creating new volume group named %1.</source>
      <translation>Skapa ny volymgrupp med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Installationsprogrammet kunde inte skapa en volymgrupp med namnet '%1'.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="45"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Deaktivera volymgruppen med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="39"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Deaktivera volymgruppen med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Installationsprogrammet kunde inte deaktivera volymgruppen med namnet %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
      <source>Delete partition %1.</source>
      <translation>Ta bort partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="47"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ta bort partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="54"/>
      <source>Deleting partition %1.</source>
      <translation>Tar bort partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="65"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Installationsprogrammet kunde inte ta bort partition %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Denna enhet har en &lt;strong&gt;%1&lt;/strong&gt; partitionstabell.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="115"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="122"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="132"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Det här är den rekommenderade typen av partitionstabell för moderna system med en startpartition av typen &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="138"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Typen av &lt;strong&gt;partitionstabell&lt;/strong&gt; på den valda lagringsenheten.&lt;br&gt;&lt;br&gt;Det enda sättet attt ändra typen av partitionstabell är genom att radera och återskapa partitionstabellen från början, vilket förstör all data på lagringsenheten.&lt;br&gt;Installationshanteraren kommer behålla den nuvarande partitionstabellen om du inte väljer något annat.&lt;br&gt;På moderna system är GPT att föredra.</translation>
    </message>
  </context>
  <context>
    <name>DeviceModel</name>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="93"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="104"/>
      <source>%1 - (%2)</source>
      <extracomment>device[name] - (device-node[name])</extracomment>
      <translation>%1 - (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="136"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Skriv LUKS konfiguration för Dracut till %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="140"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Skippa att skriva LUKS konfiguration för Dracut "/" partition är inte krypterad</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="157"/>
      <source>Failed to open %1</source>
      <translation>Kunde inte öppna %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
      <source>Dummy C++ Job</source>
      <translation>Exempel C++ jobb</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
      <source>Edit Existing Partition</source>
      <translation>Ändra befintlig partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
      <source>Content:</source>
      <translation>Innehåll:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
      <source>&amp;Keep</source>
      <translation>Behåll</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
      <source>Format</source>
      <translation>Format</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Varning: Formatering av partitionen kommer att radera alla data.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Monteringspunkt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
      <source>Si&amp;ze:</source>
      <translation>Storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
      <source>Flags:</source>
      <translation>Flaggor:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="278"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Monteringspunkt används redan. Välj en annan.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
      <source>En&amp;crypt system</source>
      <translation>Kryptera system</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
      <source>Passphrase</source>
      <translation>Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
      <source>Confirm passphrase</source>
      <translation>Bekräfta lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="153"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Vänligen skriv samma lösenord i båda fälten.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="139"/>
      <source>Set partition information</source>
      <translation>Ange partitionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="165"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Installera %1 på &lt;strong&gt;ny&lt;/strong&gt; %2 system partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="171"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa &lt;strong&gt; ny &lt;/strong&gt; %2 partition med monteringspunkt &lt;strong&gt; %1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="181"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installera %2 på %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="188"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Skapa %3 partition &lt;strong&gt;%1&lt;/strong&gt; med monteringspunkt &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="201"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installera uppstartshanterare på &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="210"/>
      <source>Setting up mount points.</source>
      <translation>Ställer in monteringspunkter.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
      <source>&amp;Restart now</source>
      <translation>Sta&amp;rta om nu</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Allt klart.&lt;/h1&gt;&lt;br/&gt;%1 har installerats på din dator.&lt;br/&gt;Du kan nu börja använda ditt nya system.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="58"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="66"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Klappat och klart.&lt;/h1&gt;&lt;br/&gt;%1 har installerats på din dator.&lt;br/&gt;Du kan nu starta om till ditt nya system, eller fortsätta att använda %2 i liveläge.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="71"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="133"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installationen misslyckades&lt;/h1&gt; &lt;br/&gt;%1 har inte blivit installerad på din dator. &lt;br/&gt;Felmeddelandet var: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="139"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installationen misslyckades&lt;/h1&gt; &lt;br/&gt;%1 har inte blivit installerad på din dator. &lt;br/&gt;Felmeddelandet var: %2</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="78"/>
      <source>Finish</source>
      <translation>Slutför</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="132"/>
      <source>Setup Complete</source>
      <translation>Inställningarna är klara</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="133"/>
      <source>Installation Complete</source>
      <translation>Installationen är klar</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="135"/>
      <source>The setup of %1 is complete.</source>
      <translation>Inställningarna för %1 är klara.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="136"/>
      <source>The installation of %1 is complete.</source>
      <translation>Installationen av %1 är klar.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="45"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Formatera partition %1 (filsystem: %2, storlek: %3 MiB) på %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="56"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Formatera &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; med filsystem &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="67"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Formatera partition %1 med filsystem %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="81"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Installationsprogrammet misslyckades att formatera partition %1 på disk '%2'.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="126"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>har minst %1 GiB tillgängligt på hårddisken</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="128"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Det finns inte tillräckligt med hårddiskutrymme. Minst %1 GiB krävs.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="137"/>
      <source>has at least %1 GiB working memory</source>
      <translation>har minst %1 GiB arbetsminne</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="139"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Systemet har inte tillräckligt med fungerande minne. Minst %1 GiB krävs.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="148"/>
      <source>is plugged in to a power source</source>
      <translation>är ansluten till en strömkälla</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Systemet är inte anslutet till någon strömkälla.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>is connected to the Internet</source>
      <translation>är ansluten till internet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="157"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Systemet är inte anslutet till internet.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="164"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>körs installationsprogammet med administratörsrättigheter (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="167"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Installationsprogammet körs inte med administratörsrättigheter.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Installationsprogammet körs inte med administratörsrättigheter.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="176"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>har en tillräckligt stor skärm för att visa hela installationsprogrammet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Skärmen är för liten för att visa installationsprogrammet.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Skärmen är för liten för att visa installationshanteraren.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="51"/>
      <source>Collecting information about your machine.</source>
      <translation>Samlar in information om din maskin.</translation>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="48"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte skapa mappar &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte öppna fil &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="68"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte skriva till fil &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="40"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Skapar initramfs med mkinitcpio.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="37"/>
      <source>Creating initramfs.</source>
      <translation>Skapar initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
      <source>Konsole not installed</source>
      <translation>Konsole inte installerat</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Installera KDE Konsole och försök igen!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Kör skript: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
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
      <translation>Sätt tangenbordsmodell till %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="217"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Sätt tangentbordslayout till %1/%2.</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Tangentbord</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="54"/>
      <source>Keyboard</source>
      <translation>Tangentbord</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="32"/>
      <source>System locale setting</source>
      <translation>Systemspråksinställning</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="39"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Systemspråket påverkar vilket språk och teckenuppsättning somliga kommandoradsprogram använder.&lt;br/&gt;Det nuvarande språket är &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="63"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Avsluta</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="64"/>
      <source>&amp;OK</source>
      <translation>&amp;Okej</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="22"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licensavtal&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Jag accepterar villkoren och avtalet ovan.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="164"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="169"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="52"/>
      <source>License</source>
      <translation>Licens</translation>
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
      <translation>&lt;strong&gt;%1-drivrutin&lt;/strong&gt;&lt;br/&gt;från %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 grafikdrivrutin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="130"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 insticksprogram&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="136"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="142"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1-paket&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="148"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="171"/>
      <source>File: %1</source>
      <translation>Fil: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Hide license text</source>
      <translation>Dölj licens text </translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Show the license text</source>
      <translation>Visa licens text</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="198"/>
      <source>Open license agreement in browser.</source>
      <translation>Öppna licensavtal i en webbläsare.</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="127"/>
      <source>Region:</source>
      <translation>Region:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="128"/>
      <source>Zone:</source>
      <translation>Zon:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="129"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>&amp;Change...</source>
      <translation>Ändra...</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="262"/>
      <source>The system language will be set to %1.</source>
      <translation>Systemspråket kommer ändras till %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="263"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="270"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Sätt tidszon till %1/%2.&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="95"/>
      <source>Location</source>
      <translation>Plats</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="100"/>
      <source>Location</source>
      <translation>Plats</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="39"/>
      <source>Configuring LUKS key file.</source>
      <translation>Konfigurerar LUKS nyckel fil.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="156"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="164"/>
      <source>No partitions are defined.</source>
      <translation>Inga partitioner är definerade.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="192"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="199"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="207"/>
      <source>Encrypted rootfs setup error</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="193"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Root partition %1 är LUKS men ingen lösenfras har ställts in.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="200"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Kunde inte skapa LUKS nyckelfil för root partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="208"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>Kunde inte konfigurera LUKS nyckelfil på partition %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="46"/>
      <source>Generate machine-id.</source>
      <translation>Generera maskin-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="62"/>
      <source>Configuration Error</source>
      <translation>Konfigurationsfel</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="63"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Ingen root monteringspunkt är satt för MachineId.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Package selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Office software</source>
      <translation>Kontors programvara</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Office package</source>
      <translation>Kontors paket</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Browser software</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Browser package</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Web browser</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Kernel</source>
      <translation>Kärna</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Services</source>
      <translation>Tjänster</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Login</source>
      <translation>Inloggning</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Desktop</source>
      <translation>Skrivbord</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="73"/>
      <source>Applications</source>
      <translation>Program</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="74"/>
      <source>Communication</source>
      <translation>Kommunikation</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="75"/>
      <source>Development</source>
      <translation>Utveckling</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="76"/>
      <source>Office</source>
      <translation>Kontorsprogram</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="77"/>
      <source>Multimedia</source>
      <translation>Multimedia</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="78"/>
      <source>Internet</source>
      <translation>Internet</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="79"/>
      <source>Theming</source>
      <translation>Teman</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="80"/>
      <source>Gaming</source>
      <translation>Gaming</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="81"/>
      <source>Utilities</source>
      <translation>Verktyg</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="34"/>
      <source>Notes</source>
      <translation>Anteckningar</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="28"/>
      <source>Ba&amp;tch:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="38"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM-konfiguration&lt;/h1&gt;&lt;p&gt;Calamares kommer att använda OEM inställningar när målsystemet konfigureras.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="121"/>
      <source>OEM Configuration</source>
      <translation>OEM Konfiguration</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="126"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="57"/>
      <source>Password is too short</source>
      <translation>Lösenordet är för kort </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="73"/>
      <source>Password is too long</source>
      <translation>Lösenordet är för långt </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="149"/>
      <source>Password is too weak</source>
      <translation>Lösenordet är för svagt </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="157"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
      <source>Memory allocation error</source>
      <translation>Minnesallokerings fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
      <source>The password is the same as the old one</source>
      <translation>Lösenordet är samma som det gamla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
      <source>The password is a palindrome</source>
      <translation>Lösenordet är en palindrom</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
      <source>The password differs with case changes only</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
      <source>The password is too similar to the old one</source>
      <translation>Lösenordet liknar för mycket det gamla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
      <source>The password contains the user name in some form</source>
      <translation>Lösenordet innehåller ditt användarnamn i någon form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="177"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Lösenordet innehåller förbjudna ord i någon form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="181"/>
      <source>The password contains less than %1 digits</source>
      <translation>Lösenordet innehåller mindre än %1 siffror</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
      <source>The password contains too few digits</source>
      <translation>Lösenordet innehåller för få siffror</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>The password contains less than %1 uppercase letters</source>
      <translation>Lösenordet innehåller mindre än %1 stora bokstäver</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Lösenordet innehåller för få stora bokstäver</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
      <source>The password contains less than %1 lowercase letters</source>
      <translation>Lösenordet innehåller mindre än %1 små bokstäver</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Lösenordet innehåller för få små bokstäver</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password contains less than %1 non-alphanumeric characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Lösenordet innehåller för få icke-alfanumeriska tecken</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password is shorter than %1 characters</source>
      <translation>Lösenordet är kortare än %1 tecken</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
      <source>The password is too short</source>
      <translation>Detta lösenordet är för kort </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password is just rotated old one</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains less than %1 character classes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password does not contain enough character classes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains more than %1 same characters consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="230"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Lösenordet innehåller för många liknande tecken efter varandra</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="234"/>
      <source>The password contains more than %1 characters of the same class consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="238"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains monotonic sequence longer than %1 characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>No password supplied</source>
      <translation>Inget lösenord angivit</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="254"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="260"/>
      <source>The password fails the dictionary check - %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password fails the dictionary check</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
      <source>Unknown setting - %1</source>
      <translation>Okänd inställning - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
      <source>Unknown setting</source>
      <translation>Okänd inställning</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>Bad integer value of setting - %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>Bad integer value</source>
      <translation>Dåligt heltals värde</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="284"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Inställning %1 är inte av heltals typ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>Setting is not of integer type</source>
      <translation>Inställning är inte av heltals typ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Setting %1 is not of string type</source>
      <translation>Inställning %1 är inte av sträng typ </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>Setting is not of string type</source>
      <translation>Inställning %1 är inte av sträng typ </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="300"/>
      <source>Opening the configuration file failed</source>
      <translation>Öppnande av konfigurationsfilen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The configuration file is malformed</source>
      <translation>Konfigurationsfilen är felaktig</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="304"/>
      <source>Fatal failure</source>
      <translation>Fatalt fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown error</source>
      <translation>Okänt fel </translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="581"/>
      <source>Password is empty</source>
      <translation>Lösenordet är blankt</translation>
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
      <translation>Produktnamn</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="53"/>
      <source>TextLabel</source>
      <translation>TextLabel</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="69"/>
      <source>Long Product Description</source>
      <translation>Lång produktbeskrivning</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="34"/>
      <source>Package Selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="35"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="70"/>
      <source>Packages</source>
      <translation>Paket</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Name</source>
      <translation>Namn</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Description</source>
      <translation>Beskrivning</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
      <source>Keyboard Model:</source>
      <translation>Tangentbordsmodell:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
      <source>Type here to test your keyboard</source>
      <translation>Skriv här för att testa ditt tangentbord</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
      <source>What is your name?</source>
      <translation>Vad heter du?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="51"/>
      <source>Your Full Name</source>
      <translation>Ditt Fullständiga namn </translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="120"/>
      <source>What name do you want to use to log in?</source>
      <translation>Vilket namn vill du använda för att logga in?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="144"/>
      <source>login</source>
      <translation>inloggning</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="219"/>
      <source>What is the name of this computer?</source>
      <translation>Vad är namnet på datorn?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="243"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Detta namn används om du gör datorn synlig för andra i ett nätverk.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="246"/>
      <source>Computer Name</source>
      <translation>Datornamn</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="321"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Välj ett lösenord för att hålla ditt konto säkert.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="345"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="370"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel. Ett bra lösenord innehåller en blandning av bokstäver, nummer och interpunktion, bör vara minst åtta tecken långt, och bör ändras regelbundet.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="351"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="521"/>
      <source>Password</source>
      <translation>Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="376"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="546"/>
      <source>Repeat Password</source>
      <translation>Repetera Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="451"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="454"/>
      <source>Require strong passwords.</source>
      <translation>Kräv starkt lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="461"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Logga in automatiskt utan att fråga efter lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="468"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Använd samma lösenord för administratörskontot.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="491"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Välj ett lösenord för administratörskontot.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="515"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="540"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Root</source>
      <translation>Root</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="200"/>
      <source>Home</source>
      <translation>Hem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>Boot</source>
      <translation>Boot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
      <source>EFI system</source>
      <translation>EFI-system</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="209"/>
      <source>New partition for %1</source>
      <translation>Ny partition för %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition</source>
      <translation>Ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="230"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1  %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="168"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="208"/>
      <source>Free Space</source>
      <translation>Ledigt utrymme</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="172"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="212"/>
      <source>New partition</source>
      <translation>Ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="305"/>
      <source>Name</source>
      <translation>Namn</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>File System</source>
      <translation>Filsystem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>Mount Point</source>
      <translation>Monteringspunkt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>Size</source>
      <translation>Storlek</translation>
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
      <translation>Lagringsenhet:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
      <source>&amp;Revert All Changes</source>
      <translation>Återställ alla ändringar</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
      <source>New Partition &amp;Table</source>
      <translation>Ny partitions&amp;tabell</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
      <source>Cre&amp;ate</source>
      <translation>Skapa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
      <source>&amp;Edit</source>
      <translation>Ändra</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
      <source>&amp;Delete</source>
      <translation>Ta bort</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
      <source>New Volume Group</source>
      <translation>Ny volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
      <source>Resize Volume Group</source>
      <translation>Ändra storlek på volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
      <source>Deactivate Volume Group</source>
      <translation>Deaktivera volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
      <source>Remove Volume Group</source>
      <translation>Ta bort volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Installera uppstartshanterare på:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="211"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Är du säker på att du vill skapa en ny partitionstabell på %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="240"/>
      <source>Can not create new partition</source>
      <translation>Kan inte skapa ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="77"/>
      <source>Gathering system information...</source>
      <translation>Samlar systeminformation...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="131"/>
      <source>Partitions</source>
      <translation>Partitioner</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="168"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Installera %1 &lt;strong&gt;bredvid&lt;/strong&gt; ett annat operativsystem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="173"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Rensa&lt;/strong&gt; disken och installera %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="177"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Ersätt&lt;/strong&gt; en partition med %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="181"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;Manuell&lt;/strong&gt; partitionering.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="194"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Installera %1 &lt;strong&gt;bredvid&lt;/strong&gt; ett annat operativsystem på disken &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="201"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Rensa&lt;/strong&gt; disken &lt;strong&gt;%2&lt;/strong&gt; (%3) och installera %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="207"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Ersätt&lt;/strong&gt; en partition på disken &lt;strong&gt;%2&lt;/strong&gt; (%3) med %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="214"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;Manuell&lt;/strong&gt; partitionering på disken &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="223"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="249"/>
      <source>Current:</source>
      <translation>Nuvarande:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="266"/>
      <source>After:</source>
      <translation>Efter:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="432"/>
      <source>No EFI system partition configured</source>
      <translation>Ingen EFI system partition konfigurerad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="433"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="447"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="446"/>
      <source>EFI system partition flag not set</source>
      <translation>EFI system partitionsflagga inte satt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="473"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Alternativ för att använda GPT på BIOS</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="474"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="502"/>
      <source>Boot partition not encrypted</source>
      <translation>Boot partition inte krypterad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="503"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="720"/>
      <source>has at least one disk device available.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="721"/>
      <source>There are no partitions to install on.</source>
      <translation>Det finns inga partitioner att installera på.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="76"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
      <source>Look-and-Feel</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="84"/>
      <source>Saving files for later ...</source>
      <translation>Sparar filer tills senare ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="122"/>
      <source>No files configured to save for later.</source>
      <translation>Inga filer konfigurerade att spara till senare.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="176"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Inte alla av konfigurationsfilerna kunde bevaras.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>
There was no output from the command.</source>
      <translation>
Det kom ingen utdata från kommandot.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="419"/>
      <source>
Output:
</source>
      <translation>
Utdata:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>External command crashed.</source>
      <translation>Externt kommando kraschade.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; kraschade.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>External command failed to start.</source>
      <translation>Externt kommando misslyckades med att starta</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="430"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; misslyckades med att starta. </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Internal error when starting command.</source>
      <translation>Internt fel under kommandostart.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="435"/>
      <source>Bad parameters for process job call.</source>
      <translation>Ogiltiga parametrar för processens uppgiftsanrop.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="439"/>
      <source>External command failed to finish.</source>
      <translation>Fel inträffade när externt kommando kördes.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="440"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; misslyckades att slutföras på %2 sekunder.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="447"/>
      <source>External command finished with errors.</source>
      <translation>Externt kommando kördes färdigt med fel.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="448"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt;avslutades under körning med avslutningskod %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Label.cpp" line="37"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="63"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="36"/>
      <source>unknown</source>
      <translation>okänd</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="38"/>
      <source>extended</source>
      <translation>utökad</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="40"/>
      <source>unformatted</source>
      <translation>oformaterad</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="42"/>
      <source>swap</source>
      <translation>swap</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="91"/>
      <source>Default Keyboard Model</source>
      <translation>Standardtangentbordsmodell</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="133"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="168"/>
      <source>Default</source>
      <translation>Standard</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="73"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="81"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="85"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="102"/>
      <source>File not found</source>
      <translation>Filen hittades inte </translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="74"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="103"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Kunde inte skapa ny slumpmässig fil &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="79"/>
      <source>No product</source>
      <translation>Ingen produkt</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="87"/>
      <source>No description provided.</source>
      <translation>Ingen beskrivning tillhandahålls.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="47"/>
      <source>(no mount point)</source>
      <translation>(ingen monteringspunkt)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="51"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Opartitionerat utrymme eller okänd partitionstabell</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="43"/>
      <source>Remove live user from target system</source>
      <translation>Tar bort live användare från målsystemet</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="45"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Ta bort volymgrupp med namnet %1. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="39"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ta bort volymgrupp med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Installationsprogrammet misslyckades att ta bort en volymgrupp med namnet '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="139"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Välj var du vill installera %1.&lt;br/&gt;&lt;font color="red"&gt;Varning: &lt;/font&gt;detta kommer att radera alla filer på den valda partitionen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="165"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Det valda alternativet verkar inte vara en giltig partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="173"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 kan inte installeras i tomt utrymme. Välj en existerande partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="183"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 kan inte installeras på en utökad partition. Välj en existerande primär eller logisk partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="193"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 kan inte installeras på den här partitionen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="200"/>
      <source>Data partition (%1)</source>
      <translation>Datapartition (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
      <source>Unknown system partition (%1)</source>
      <translation>Okänd systempartition (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="221"/>
      <source>%1 system partition (%2)</source>
      <translation>Systempartition för %1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="232"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Partitionen %1 är för liten för %2. Välj en partition med minst storleken %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="255"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="266"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="283"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="307"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 kommer att installeras på %2.&lt;br/&gt;&lt;font color="red"&gt;Varning: &lt;/font&gt;all data på partition %2 kommer att gå förlorad.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="275"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-systempartitionen %1 kommer att användas för att starta %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="291"/>
      <source>EFI system partition:</source>
      <translation>EFI-systempartition:</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="57"/>
      <source>Resize Filesystem Job</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>Invalid configuration</source>
      <translation>Ogiltig konfiguration</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="171"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="177"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore inte tillgänglig</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="178"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="208"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="234"/>
      <source>Resize Failed</source>
      <translation>Storleksändringen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="188"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="209"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="197"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="210"/>
      <source>The device %1 cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="218"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="219"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="49"/>
      <source>Resize partition %1.</source>
      <translation>Ändra storlek på partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="56"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>Ändra &lt;strong&gt;%2MiB&lt;/strong&gt;-partitionen &lt;strong&gt;%1&lt;/strong&gt; till &lt;strong&gt;%3MB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="67"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Ändrar storlek på partitionen %1 från %2MB till %3MB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="86"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Installationsprogrammet misslyckades med att ändra storleken på partition %1 på disk '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="39"/>
      <source>Resize Volume Group</source>
      <translation>Ändra storlek på volymgrupp</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="54"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Byt storlek på volymgrupp med namn &lt;strong&gt;%1&lt;/strong&gt;  från &lt;strong&gt;%2&lt;/strong&gt;till &lt;strong&gt;%3&lt;/strong&gt;. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="69"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Installationsprogrammet misslyckades att byta storlek på en volymgrupp med namn '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="140"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>För bästa resultat, vänligen se till att datorn:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="141"/>
      <source>System requirements</source>
      <translation>Systemkrav</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="261"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Datorn uppfyller inte minimikraven för inställning av %1.&lt;br/&gt;Inga inställningar kan inte göras. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="265"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Denna dator uppfyller inte minimikraven för att installera %1.&lt;br/&gt;Installationen kan inte fortsätta. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="272"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Några av kraven för inställning av %1 uppfylls inte av datorn.&lt;br/&gt;Inställningarna kan ändå göras men vissa funktioner kommer kanske inte att kunna användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="276"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Denna dator uppfyller inte alla rekommenderade krav för att installera %1.&lt;br/&gt;Installationen kan fortsätta, men alla alternativ och funktioner kanske inte kan användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="285"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Detta program kommer att ställa dig några frågor och installera %2 på din dator.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
      <source>Scanning storage devices...</source>
      <translation>Skannar lagringsenheter...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
      <source>Partitioning</source>
      <translation>Partitionering</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="46"/>
      <source>Set hostname %1</source>
      <translation>Ange värdnamn %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="53"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ange värdnamn &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="60"/>
      <source>Setting hostname %1.</source>
      <translation>Anger värdnamn %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="131"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="138"/>
      <source>Internal Error</source>
      <translation>Internt fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="155"/>
      <source>Cannot write hostname to target system</source>
      <translation>Kan inte skriva värdnamn till målsystem</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Sätt tangentbordsmodell till %1, layout till %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="351"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration för konsolen.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="352"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="356"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="363"/>
      <source>Failed to write to %1</source>
      <translation>Misslyckades med att skriva %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="355"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration för X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="362"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration till den existerande katalogen /etc/default.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
      <source>Set flags on partition %1.</source>
      <translation>Sätt flaggor på partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="58"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>Sätt flaggor på %1MiB %2 partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="62"/>
      <source>Set flags on new partition.</source>
      <translation>Sätt flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rensa flaggor på partition &lt;strong&gt;%1&lt;/strong&gt;,</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Rensa flaggor på %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="84"/>
      <source>Clear flags on new partition.</source>
      <translation>Rensa flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Flagga partition &lt;strong&gt;%1&lt;/strong&gt; som &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Flagga %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition som &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Flagga ny partition som &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rensar flaggor på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="123"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Rensa flaggor på %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="128"/>
      <source>Clearing flags on new partition.</source>
      <translation>Rensar flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sätter flaggor &lt;strong&gt;%2&lt;/strong&gt; på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="142"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Sätter flaggor &lt;strong&gt;%3&lt;/strong&gt; på  %11MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Sätter flaggor &lt;strong&gt;%1&lt;/strong&gt; på ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="165"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Installationsprogrammet misslyckades med att sätta flaggor på partition %1. </translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="49"/>
      <source>Set password for user %1</source>
      <translation>Ange lösenord för användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="56"/>
      <source>Setting password for user %1.</source>
      <translation>Ställer in lösenord för användaren %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <source>Bad destination system path.</source>
      <translation>Ogiltig systemsökväg till målet.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="91"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMonteringspunkt är %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot disable root account.</source>
      <translation>Kunde inte inaktivera root konto.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd stoppades med felkod %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="106"/>
      <source>Cannot set password for user %1.</source>
      <translation>Kan inte ställa in lösenord för användare %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod avslutade med felkod %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
      <source>Set timezone to %1/%2</source>
      <translation>Sätt tidszon till %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Kan inte komma åt vald tidszonssökväg.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Bad path: %1</source>
      <translation>Ogiltig sökväg: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <translation>Kan inte ställa in tidszon.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Skapande av länk misslyckades, mål: %1; länknamn: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
      <source>Cannot set timezone,</source>
      <translation>Kan inte ställa in tidszon,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Kunde inte öppna /etc/timezone för skrivning</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="46"/>
      <source>Shell Processes Job</source>
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="60"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Detta är en överblick av vad som kommer att ske när du startar installationsprocessen.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
      <source>Summary</source>
      <translation>Översikt</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="42"/>
      <source>Installation feedback</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="54"/>
      <source>Sending installation feedback.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Internal error in install-tracking.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="72"/>
      <source>HTTP request timed out.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingMachineNeonJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="80"/>
      <source>Machine feedback</source>
      <translation>Maskin feedback</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="92"/>
      <source>Configuring machine feedback.</source>
      <translation>Konfigurerar maskin feedback</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="117"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="123"/>
      <source>Error in machine feedback configuration.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="118"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Kunde inte konfigurera maskin feedback korrekt, script fel %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Kunde inte konfigurera maskin feedback korrekt, Calamares fel  %1.</translation>
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
      <translation>Platshållare</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
      <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="49"/>
      <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="51"/>
      <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="54"/>
      <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="64"/>
      <source>Feedback</source>
      <translation>Feedback</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="149"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Om mer än en person skall använda datorn så kan du skapa flera användarkonton när inställningarna är klara.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="155"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Om mer än en person skall använda datorn så kan du skapa flera användarkonton när installationen är klar.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="395"/>
      <source>Your username is too long.</source>
      <translation>Ditt användarnamn är för långt.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="402"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Ditt användarnamn måste börja med en liten bokstav eller ett understreck.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="409"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Endast små bokstäver, nummer, understreck och bindestreck är tillåtet.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="445"/>
      <source>Your hostname is too short.</source>
      <translation>Ditt värdnamn är för kort.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="450"/>
      <source>Your hostname is too long.</source>
      <translation>Ditt värdnamn är för långt.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="457"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Endast bokstäver, nummer, understreck och bindestreck är tillåtet. </translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="474"/>
      <source>Your passwords do not match!</source>
      <translation>Lösenorden överensstämmer inte!</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="76"/>
      <source>Users</source>
      <translation>Användare</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="241"/>
      <source>Key</source>
      <translation>Nyckel</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="245"/>
      <source>Value</source>
      <translation>Värde</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
      <source>Create Volume Group</source>
      <translation>Skapa volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
      <source>List of Physical Volumes</source>
      <translation>Lista på fysiska volymer</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
      <source>Volume Group Name:</source>
      <translation>Volymgrupp namn:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
      <source>Volume Group Type:</source>
      <translation>Volymgrupp typ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
      <source>Physical Extent Size:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
      <source>Total Size:</source>
      <translation>Total storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
      <source>Used Size:</source>
      <translation>Använd storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
      <source>Total Sectors:</source>
      <translation>Totala sektorer:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
      <source>Quantity of LVs:</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="94"/>
      <source>Select application and system language</source>
      <translation>Välj program och system språk </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="136"/>
      <source>&amp;About</source>
      <translation>Om, &amp;A</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
      <source>Open donations website</source>
      <translation>Besök webbplatsen för donationer</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="149"/>
      <source>&amp;Donate</source>
      <translation>&amp;Donera</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="159"/>
      <source>Open help and support website</source>
      <translation>Besök webbplatsen för hjälp och support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="162"/>
      <source>&amp;Support</source>
      <translation>&amp;Support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="172"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Besök webbplatsen för problem och felsökning</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="175"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Kända problem</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="185"/>
      <source>Open release notes website</source>
      <translation>Besök webbplatsen för versionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="188"/>
      <source>&amp;Release notes</source>
      <translation>Versionsinformation, &amp;R</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="228"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till Calamares installationsprogrammet för %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="229"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1 installation.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="234"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till installationsprogrammet Calamares för %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1-installeraren.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="240"/>
      <source>%1 support</source>
      <translation>%1-support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>About %1 setup</source>
      <translation>Om inställningarna för %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>About %1 installer</source>
      <translation>Om %1-installationsprogrammet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="250"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="60"/>
      <source>Welcome</source>
      <translation>Välkommen</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="64"/>
      <source>Welcome</source>
      <translation>Välkommen</translation>
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
      <translation>Bakåt</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="25"/>
      <source>Keyboard Model</source>
      <translation>Tangentbordsmodell</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="26"/>
      <source>Pick your preferred keyboard model or use the default one based on the detected hardware</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="41"/>
      <source>Refresh</source>
      <translation>Ladda om</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="51"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="163"/>
      <source>Layouts</source>
      <translation>Layouter</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="79"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="139"/>
      <source>Keyboard Layout</source>
      <translation>Tangentbordslayout</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="101"/>
      <source>Models</source>
      <translation>Modeller</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="109"/>
      <source>Variants</source>
      <translation>Varianter</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="189"/>
      <source>Test your keyboard</source>
      <translation>Testa ditt tangentbord</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="61"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Detta är exempel versionsinformation.</translation>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="85"/>
      <source>Back</source>
      <translation>Bakåt</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="44"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="71"/>
      <source>About</source>
      <translation>Om</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="85"/>
      <source>Support</source>
      <translation>Support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="96"/>
      <source>Known issues</source>
      <translation>Kända problem</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="107"/>
      <source>Release notes</source>
      <translation>Versionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="119"/>
      <source>Donate</source>
      <translation>Donera</translation>
    </message>
  </context>
</TS>

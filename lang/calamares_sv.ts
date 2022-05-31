<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="sv" version="2.1">
  <context>
    <name>AboutData</name>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="17"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt; &lt;br/&gt; &lt;strong&gt;%2&lt;br/&gt; för %3&lt;/strong&gt; &lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="20"/>
      <source>Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>Tack till &lt;a href="https://calamares.io/team/"&gt;Calamares-teamet&lt;/a&gt; och &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares översättar-team&lt;/a&gt;. &lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt;utveckling är sponsrad av &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="38"/>
      <source>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</source>
      <extracomment>Copyright year-year Name &lt;email-address&gt;</extracomment>
      <translation>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>AutoMountManagementJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/AutoMountManagementJob.cpp" line="22"/>
      <source>Manage auto-mount settings</source>
      <translation>Hantera inställningar för automatisk montering</translation>
    </message>
  </context>
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="62"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>Systemets &lt;strong&gt;startmiljö&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Äldre x86-system stöder endast &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Moderna system stöder vanligen &lt;strong&gt;EFI&lt;/strong&gt;, men kan också vara i kompatibilitetsläge för BIOS.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="72"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Detta system startades med en &lt;strong&gt;EFI-miljö&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;För att ställa in start från en EFI-miljö måste en starthanterare användas, t.ex. &lt;strong&gt;GRUB&lt;/strong&gt; eller &lt;strong&gt;systemd-boot&lt;/strong&gt; på en &lt;strong&gt;EFI-systempartition&lt;/strong&gt;. Detta sker automatiskt, såvida du inte väljer att partitionera manuellt. Då måste du själv installera en starthanterare.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="84"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Detta system startades med en &lt;strong&gt;BIOS-miljö&lt;/strong&gt;. &lt;br&gt;&lt;br&gt;För att ställa in start från en BIOS-miljö måste en starthanterare som t.ex. &lt;strong&gt;GRUB&lt;/strong&gt; installeras, antingen i början av en partition eller på &lt;strong&gt;huvudstartsektorn (MBR)&lt;/strong&gt; i början av partitionstabellen. Detta sker automatiskt, såvida du inte väljer manuell partitionering. Då måste du själv installera en starthanterare.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
      <source>Master Boot Record of %1</source>
      <translation>Master Boot Record på %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="92"/>
      <source>Boot Partition</source>
      <translation>Startpartition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="99"/>
      <source>System Partition</source>
      <translation>Systempartition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="129"/>
      <source>Do not install a boot loader</source>
      <translation>Installera inte någon starthanterare</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="147"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="61"/>
      <source>Blank Page</source>
      <translation>Tom sida</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>GlobalStorage</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>JobQueue</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Moduler</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Typ:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>ingen</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Gränssnitt:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="102"/>
      <source>Crashes Calamares, so that Dr. Konqui can look at it.</source>
      <translation>Kraschar Calamares, så att Dr. Konqui kan titta på det.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="115"/>
      <source>Reloads the stylesheet from the branding directory.</source>
      <translation>Laddar om stilmall från branding katalogen.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="141"/>
      <source>Uploads the session log to the configured pastebin.</source>
      <translation>Laddar upp sessionsloggen till den konfigurerade pastebin.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="144"/>
      <source>Send Session Log</source>
      <translation>Skicka Session Logg</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="118"/>
      <source>Reload Stylesheet</source>
      <translation>Ladda om stilmall</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="128"/>
      <source>Displays the tree of widget names in the log (for stylesheet debugging).</source>
      <translation>Visar trädet med widgetnamn i loggen (för stilmalls felsökning).</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="131"/>
      <source>Widget Tree</source>
      <translation>Widgetträd</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="239"/>
      <source>Debug information</source>
      <translation>Avlusningsinformation</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Set up</source>
      <translation>Inställningar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Install</source>
      <translation>Installera</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Uppgiften misslyckades (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Programmerat jobbfel begärdes uttryckligen.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="203"/>
      <source>Done</source>
      <translation>Klar</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Exempel jobb (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="42"/>
      <source>Run command '%1' in target system.</source>
      <translation>Kör kommandot '%1'. på målsystem.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="42"/>
      <source> Run command '%1'.</source>
      <translation>Kör kommandot '%1'.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="49"/>
      <source>Running command %1 %2</source>
      <translation>Kör kommando %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Running %1 operation.</source>
      <translation>Kör %1-operation</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="262"/>
      <source>Bad working directory path</source>
      <translation>Arbetskatalogens sökväg är ogiltig</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="263"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Arbetskatalog %1 för pythonuppgift %2 är inte läsbar.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="269"/>
      <source>Bad main script file</source>
      <translation>Ogiltig huvudskriptfil</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="270"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Huvudskriptfil %1 för pythonuppgift %2 är inte läsbar.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="343"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost.Python-fel i uppgift "%'1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="67"/>
      <source>Loading ...</source>
      <translation>Laddar ...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="88"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML steg &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="268"/>
      <source>Loading failed.</source>
      <translation>Laddning misslyckades.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="94"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>Kontroll av krav för modul &lt;i&gt;%1&lt;/i&gt; är färdig.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="118"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Väntar på %n modul(er).</numerusform>
        <numerusform>Väntar på %n modul(er).</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="119"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n sekund(er))</numerusform>
        <numerusform>(%n sekund(er))</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="124"/>
      <source>System-requirements checking is complete.</source>
      <translation>Kontroll av systemkrav är färdig</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
      <source>Setup Failed</source>
      <translation>Inställningarna misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
      <source>Installation Failed</source>
      <translation>Installationen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="163"/>
      <source>Error</source>
      <translation>Fel</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
      <source>&amp;Yes</source>
      <translation>&amp;Ja</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
      <source>&amp;No</source>
      <translation>&amp;Nej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="92"/>
      <source>&amp;Close</source>
      <translation>&amp;Stäng</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="184"/>
      <source>Install Log Paste URL</source>
      <translation>URL till installationslogg</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="166"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Sändningen misslyckades. Ingenting sparades på webbplatsen.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="178"/>
      <source>Install log posted to

%1

Link copied to clipboard</source>
      <translation>Installationslogg postad till

%1

Länken kopierades till urklipp</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>Calamares Initialization Failed</source>
      <translation>Initieringen av Calamares misslyckades</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="190"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 kan inte installeras. Calamares kunde inte ladda alla konfigurerade moduler. Detta är ett problem med hur Calamares används av distributionen.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Följande moduler kunde inte hämtas:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="310"/>
      <source>Continue with setup?</source>
      <translation>Fortsätt med installation?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="310"/>
      <source>Continue with installation?</source>
      <translation>Vill du fortsätta med installationen?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="312"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1-installeraren är på väg att göra ändringar på disk för att installera %2.&lt;br/&gt;&lt;strong&gt;Du kommer inte att kunna ångra dessa ändringar.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="315"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1-installeraren är på väg att göra ändringar för att installera %2.&lt;br/&gt;&lt;strong&gt;Du kommer inte att kunna ångra dessa ändringar.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="318"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Installera nu </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="318"/>
      <source>&amp;Install now</source>
      <translation>&amp;Installera nu</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="326"/>
      <source>Go &amp;back</source>
      <translation>Gå &amp;bakåt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="376"/>
      <source>&amp;Set up</source>
      <translation>&amp;Installera</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="376"/>
      <source>&amp;Install</source>
      <translation>&amp;Installera</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="378"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Installationen är klar. Du kan avsluta installationsprogrammet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="379"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Installationen är klar. Du kan avsluta installationshanteraren.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="381"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Avbryt inställningarna utan att förändra systemet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="382"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Avbryt installationen utan att förändra systemet.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Next</source>
      <translation>&amp;Nästa</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>&amp;Back</source>
      <translation>&amp;Bakåt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="403"/>
      <source>&amp;Done</source>
      <translation>&amp;Klar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="422"/>
      <source>&amp;Cancel</source>
      <translation>Avbryt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>Cancel setup?</source>
      <translation>Avbryt inställningarna?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>Cancel installation?</source>
      <translation>Avbryt installation?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="496"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Vill du verkligen avbryta den nuvarande uppstartsprocessen? Uppstartsprogrammet kommer avsluta och alla ändringar kommer förloras.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="498"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Är du säker på att du vill avsluta installationen i förtid?
Alla ändringar kommer att gå förlorade.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="302"/>
      <source>Unknown exception type</source>
      <translation>Okänd undantagstyp</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="320"/>
      <source>unparseable Python error</source>
      <translation>Otolkbart Pythonfel</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="364"/>
      <source>unparseable Python traceback</source>
      <translation>Otolkbar Python-traceback</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="371"/>
      <source>Unfetchable Python error.</source>
      <translation>Ohämtbart Pythonfel</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="369"/>
      <source>%1 Setup Program</source>
      <translation>%1 Installationsprogram</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="370"/>
      <source>%1 Installer</source>
      <translation>%1-installationsprogram</translation>
    </message>
  </context>
  <context>
    <name>ChangeFilesystemLabelJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="32"/>
      <source>Set filesystem label on %1.</source>
      <translation>Sätt filsystem etikett på %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="39"/>
      <source>Set filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Sätt filsystem etikett &lt;strong&gt;%1&lt;/strong&gt; på partition &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="70"/>
      <source>The installer failed to update partition table on disk '%1'.</source>
      <translation>Installationsprogrammet misslyckades med att uppdatera partitionstabellen på disk '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="38"/>
      <source>Gathering system information...</source>
      <translation>Samlar systeminformation...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="18"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="139"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Välj lagringsenhet:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="140"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1029"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1077"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1174"/>
      <source>Current:</source>
      <translation>Nuvarande:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="141"/>
      <source>After:</source>
      <translation>Efter:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1732"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Manuell partitionering&lt;/strong&gt;&lt;br/&gt;Du kan själv skapa och ändra storlek på partitionerna.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="894"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Återanvänd %1 som hempartition för %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1030"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Välj en partition att minska, sen dra i nedre fältet för att ändra storlek&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1048"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 kommer att förminskas till %2MiB och en ny %3MiB partition kommer att skapas för %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1106"/>
      <source>Boot loader location:</source>
      <translation>Sökväg till starthanterare:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1165"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Välj en partition att installera på&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1226"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Ingen EFI-partition kunde inte hittas på systemet. Gå tillbaka och partitionera din lagringsenhet manuellt för att ställa in %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1234"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-partitionen %1 kommer att användas för att starta %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1242"/>
      <source>EFI system partition:</source>
      <translation>EFI-partition:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1402"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet ser inte ut att ha ett operativsystem installerat. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring görs på lagringseneheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1407"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1444"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1466"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1491"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Rensa lagringsenhet&lt;/strong&gt;&lt;br/&gt;Detta kommer &lt;font color="red"&gt;radera&lt;/font&gt; all existerande data på den valda lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1411"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1440"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1462"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1487"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Installera på sidan om&lt;/strong&gt;&lt;br/&gt;Installationshanteraren kommer krympa en partition för att göra utrymme för %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1415"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1449"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1470"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1495"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Ersätt en partition&lt;/strong&gt;&lt;br/&gt;Ersätter en partition med %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1434"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har %1 på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring görs på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1457"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har redan ett operativsystem på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring sker på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1482"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Denna lagringsenhet har flera operativsystem på sig. Vad vill du göra?&lt;br/&gt;Du kommer kunna granska och bekräfta dina val innan någon ändring sker på lagringsenheten.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1554"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>Denna lagringsenhet har redan ett operativsystem installerat på sig, men partitionstabellen &lt;strong&gt;%1&lt;/strong&gt; skiljer sig från den som behövs &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1577"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <translation>Denna lagringsenhet har en av dess partitioner &lt;strong&gt;monterad&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1582"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <translation>Denna lagringsenhet är en del av en &lt;strong&gt;inaktiv RAID&lt;/strong&gt;enhet.    </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1701"/>
      <source>No Swap</source>
      <translation>Ingen Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1710"/>
      <source>Reuse Swap</source>
      <translation>Återanvänd Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1713"/>
      <source>Swap (no Hibernate)</source>
      <translation>Swap (utan viloläge)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1716"/>
      <source>Swap (with Hibernate)</source>
      <translation>Swap (med viloläge)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1719"/>
      <source>Swap to file</source>
      <translation>Använd en fil som växlingsenhet</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="272"/>
      <source>Successfully unmounted %1.</source>
      <translation>Framgångsrikt avmonterade %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="279"/>
      <source>Successfully disabled swap %1.</source>
      <translation>Framgångsrikt inaktiverade swap %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="305"/>
      <source>Successfully cleared swap %1.</source>
      <translation>Framgångsrikt rensade swap %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="319"/>
      <source>Successfully closed mapper device %1.</source>
      <translation>Framgångsrikt stängde krypterad enhet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="332"/>
      <source>Successfully disabled volume group %1.</source>
      <translation>Framgångsrikt inaktiverade volymgrupp %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="371"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Rensa monteringspunkter för partitionering på %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="377"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Rensar monteringspunkter för partitionering på %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="396"/>
      <source>Cleared all mounts for %1</source>
      <translation>Rensade alla monteringspunkter för %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="33"/>
      <source>Clear all temporary mounts.</source>
      <translation>Rensa alla tillfälliga monteringspunkter.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Rensar alla tillfälliga monteringspunkter.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="70"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Rensade alla tillfälliga monteringspunkter</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="142"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>Could not run command.</source>
      <translation>Kunde inte köra kommandot.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="143"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>Kommandot körs på värden och behöver känna till sökvägen till root, men rootMonteringspunkt är inte definierat.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="156"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Kommandot behöver veta användarnamnet, men inget användarnamn är definerat.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="360"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Sätt tangenbordsmodell till %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="367"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Sätt tangentbordslayout till %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="359"/>
      <source>Set timezone to %1/%2.</source>
      <translation>Sätt tidszon till %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="397"/>
      <source>The system language will be set to %1.</source>
      <translation>Systemspråket kommer ändras till %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="404"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>Systemspråket för siffror och datum kommer sättas till %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Nätverksinstallation. (Inaktiverad: inkorrekt konfiguration)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="55"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Nätverksinstallation. (Inaktiverad: Fick felaktig gruppdata)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="57"/>
      <source>Network Installation. (Disabled: Internal error)</source>
      <translation>Nätverksinstallation. (Inaktiverad: internt fel)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="61"/>
      <source>Network Installation. (Disabled: No package list)</source>
      <translation>Nätverksinstallation. (Inaktiverad: Ingen paketlista)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="77"/>
      <source>Package selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="59"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Nätverksinstallation. (Inaktiverad: Kan inte hämta paketlistor, kontrollera nätverksanslutningen)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="56"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Datorn uppfyller inte minimikraven för inställning av %1.&lt;br/&gt;Inga inställningar kan inte göras. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Denna dator uppfyller inte minimikraven för att installera %1.&lt;br/&gt;Installationen kan inte fortsätta. &lt;a href="#details"&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="67"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Några av kraven för inställning av %1 uppfylls inte av datorn.&lt;br/&gt;Inställningarna kan ändå göras men vissa funktioner kommer kanske inte att kunna användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="71"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Denna dator uppfyller inte alla rekommenderade krav för att installera %1.&lt;br/&gt;Installationen kan fortsätta, men alla alternativ och funktioner kanske inte kan användas.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="81"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Detta program kommer att ställa dig några frågor och installera %2 på din dator.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="269"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till Calamares installationsprogram för %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="270"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1 installation&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="274"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till Calamares installationsprogram för %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="275"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Välkommen till %1-installeraren&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="236"/>
      <source>Your username is too long.</source>
      <translation>Ditt användarnamn är för långt.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="252"/>
      <source>'%1' is not allowed as username.</source>
      <translation>'%1' är inte tillåtet som användarnamn.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="242"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Ditt användarnamn måste börja med en liten bokstav eller ett understreck.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="246"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Endast små bokstäver, nummer, understreck och bindestreck är tillåtet.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="301"/>
      <source>Your hostname is too short.</source>
      <translation>Ditt värdnamn är för kort.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="305"/>
      <source>Your hostname is too long.</source>
      <translation>Ditt värdnamn är för långt.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="311"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>'%1' är inte tillåtet som värdnamn.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="316"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Endast bokstäver, nummer, understreck och bindestreck är tillåtet. </translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="585"/>
      <source>Your passwords do not match!</source>
      <translation>Lösenorden överensstämmer inte!</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="599"/>
      <source>OK!</source>
      <translation>OK!</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>Setup Failed</source>
      <translation>Inställningarna misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>Installation Failed</source>
      <translation>Installationen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="147"/>
      <source>The setup of %1 did not complete successfully.</source>
      <translation>Installationen av %1 slutfördes inte korrekt.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="148"/>
      <source>The installation of %1 did not complete successfully.</source>
      <translation>Installationen av %1 slutfördes inte korrekt.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="152"/>
      <source>Setup Complete</source>
      <translation>Inställningarna är klara</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="153"/>
      <source>Installation Complete</source>
      <translation>Installationen är klar</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="154"/>
      <source>The setup of %1 is complete.</source>
      <translation>Inställningarna för %1 är klara.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="155"/>
      <source>The installation of %1 is complete.</source>
      <translation>Installationen av %1 är klar.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="111"/>
      <source>Package Selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="113"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Välj en produkt från listan. Den valda produkten kommer att installeras.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="243"/>
      <source>Packages</source>
      <translation>Paket</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="249"/>
      <source>Install option: &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>Installations alternativ: &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="249"/>
      <source>None</source>
      <translation>Ingen</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="94"/>
      <source>Summary</source>
      <translation>Översikt</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="98"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Detta är en översikt över vad som kommer hända när du startar installationsprocessen.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="103"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Detta är en överblick av vad som kommer att ske när du startar installationsprocessen.</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="119"/>
      <source>Contextual Processes Job</source>
      <translation>Kontextuellt processjobb</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Skapa en partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>Storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Partitions&amp;typ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>Primar&amp;y</source>
      <translation>Primä&amp;r</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>Utökad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM LV namn</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Monteringspunkt:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="191"/>
      <source>Flags:</source>
      <translation>Flaggor:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="224"/>
      <source>Label for the filesystem</source>
      <translation>Etikett för filsystem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="234"/>
      <source>FS Label:</source>
      <translation>FS Etikett:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
      <source>En&amp;crypt</source>
      <translation>Kr%yptera</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="194"/>
      <source>Logical</source>
      <translation>Logisk</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="199"/>
      <source>Primary</source>
      <translation>Primär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="218"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="91"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Monteringspunkt används redan. Välj en annan.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="96"/>
      <source>Mountpoint must start with a &lt;tt&gt;/&lt;/tt&gt;.</source>
      <translation>Monteringspunkt måste starta med ett &lt;tt&gt;/&lt;/tt&gt;.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="187"/>
      <source>Create new %1MiB partition on %3 (%2) with entries %4.</source>
      <translation>Skapa ny %1MiB partition på  %3 (%2) med poster %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="195"/>
      <source>Create new %1MiB partition on %3 (%2).</source>
      <translation>Skapa ny %1MiB partition på %3 (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="202"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Skapa ny %2MiB partition på %4 (%3) med filsystem %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="219"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2) with entries &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>Skapa ny &lt;strong&gt;%1MiB&lt;/strong&gt; partition på &lt;strong&gt;%3&lt;/strong&gt; (%2) med poster &lt;em&gt;%4&lt;/em&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="228"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2).</source>
      <translation>Skapa ny &lt;strong&gt;%1MiB&lt;/strong&gt; partition på &lt;strong&gt;%3&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="235"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa ny &lt;strong&gt;%2MiB&lt;/strong&gt;partition på &lt;strong&gt;%4&lt;/strong&gt; (%3) med filsystem &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="260"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="263"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Skapar ny %1 partition på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="280"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Installationsprogrammet kunde inte skapa partition på disk '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Skapa partitionstabell</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Skapa en ny partitionstabell och ta bort alla befintliga data på disken.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Vilken typ av partitionstabell vill du skapa?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID-partitionstabell (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="41"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Skapa ny %1 partitionstabell på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Skapa ny &lt;strong&gt;%1&lt;/strong&gt; partitionstabell på &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="59"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Skapar ny %1 partitionstabell på %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="88"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Installationsprogrammet kunde inte skapa en partitionstabell på %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="35"/>
      <source>Create user %1</source>
      <translation>Skapar användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="42"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa användare &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="125"/>
      <source>Preserving home directory</source>
      <translation>Bevara hemkatalogen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="49"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="142"/>
      <source>Creating user %1</source>
      <translation>Skapar användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="150"/>
      <source>Configuring user %1</source>
      <translation>Konfigurerar användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="158"/>
      <source>Setting file permissions</source>
      <translation>Ställer in filbehörigheter</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <translation>Skapa volymgrupp</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="32"/>
      <source>Create new volume group named %1.</source>
      <translation>Skapa ny volymgrupp med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Skapa ny volymgrupp med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="44"/>
      <source>Creating new volume group named %1.</source>
      <translation>Skapa ny volymgrupp med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="51"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Installationsprogrammet kunde inte skapa en volymgrupp med namnet '%1'.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="38"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Deaktivera volymgruppen med namnet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="32"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Deaktivera volymgruppen med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Installationsprogrammet kunde inte deaktivera volymgruppen med namnet %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
      <source>Delete partition %1.</source>
      <translation>Ta bort partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="80"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ta bort partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="87"/>
      <source>Deleting partition %1.</source>
      <translation>Tar bort partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="102"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Installationsprogrammet kunde inte ta bort partition %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="143"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Denna enhet har en &lt;strong&gt;%1&lt;/strong&gt; partitionstabell.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="97"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Detta är en &lt;strong&gt;loop&lt;/strong&gt;enhet.&lt;br&gt;&lt;br&gt;Det är en pseudo-enhet som inte har någon partitionstabell, och som gör en fil tillgänglig som en blockenhet. Denna typ av upplägg innehåller vanligtvis ett enda filsystem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Installationsprogrammet &lt;strong&gt;kan inte hitta någon partitionstabell&lt;/strong&gt; på den valda lagringsenheten.&lt;br&gt;&lt;br&gt;Antingen har enheten ingen partitionstabell, eller så är partitionstabellen trasig eller av okänd typ.&lt;br&gt;Installationsprogrammet kan skapa en ny partitionstabell åt dig, antingen automatiskt, eller genom sidan för manuell partitionering.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="91"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Det här är den rekommenderade typen av partitionstabell för moderna system med en startpartition av typen &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="80"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Denna partitionstabell är endast lämplig på äldre system som startar från en &lt;strong&gt;BIOS&lt;/strong&gt;-startmiljö. GPT rekommenderas i de flesta andra fall.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Varning:&lt;/strong&gt; MBR-partitionstabellen är en föråldrad standard från MS-DOS-tiden.&lt;br&gt;Endast 4 &lt;em&gt;primära&lt;/em&gt; partitioner kan skapas, och av dessa 4 kan en vara en &lt;em&gt;utökad&lt;/em&gt; partition, som i sin tur kan innehålla många &lt;em&gt;logiska&lt;/em&gt; partitioner.</translation>
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
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="82"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="93"/>
      <source>%1 - (%2)</source>
      <extracomment>device[name] - (device-node[name])</extracomment>
      <translation>%1 - (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="117"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Skriv LUKS konfiguration för Dracut till %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Skippa att skriva LUKS konfiguration för Dracut "/" partition är inte krypterad</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <translation>Kunde inte öppna %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="36"/>
      <source>Dummy C++ Job</source>
      <translation>Exempel C++ jobb</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Ändra befintlig partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Con&amp;tent:</source>
      <translation>Inne&amp;håll:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>Behåll</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Format</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Varning: Formatering av partitionen kommer att radera alla data.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Monteringspunkt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source>Si&amp;ze:</source>
      <translation>Storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="139"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="146"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="159"/>
      <source>Flags:</source>
      <translation>Flaggor:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="179"/>
      <source>Label for the filesystem</source>
      <translation>Etikett för filsystem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="189"/>
      <source>FS Label:</source>
      <translation>FS Etikett:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="259"/>
      <source>Passphrase for existing partition</source>
      <translation>Lösenfras för existerande partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="260"/>
      <source>Partition %1 could not be decrypted with the given passphrase.&lt;br/&gt;&lt;br/&gt;Edit the partition again and give the correct passphraseor delete and create a new encrypted partition.</source>
      <translation>Partition %1 kunde inte dekrypteras med den angivna lösenfrasen. &lt;br/&gt;&lt;br/&gt;Redigera partitionen igen och ange den korrekta lösenfrasen eller ta bort och skapa en ny krypterad partition</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Kryptera system</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="43"/>
      <source>Your system does not seem to support encryption well enough to encrypt the entire system. You may enable encryption, but performance may suffer.</source>
      <translation>Ditt system verkar inte stödja kryptering tillräckligt bra för att kryptera hela systemet. Du kan aktivera kryptering, men prestandan kan bli lidande.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="59"/>
      <source>Passphrase</source>
      <translation>Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="69"/>
      <source>Confirm passphrase</source>
      <translation>Bekräfta lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="156"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="166"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Vänligen skriv samma lösenord i båda fälten.</translation>
    </message>
  </context>
  <context>
    <name>ErrorDialog</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="40"/>
      <source>Details:</source>
      <translation>Detaljer:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="56"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Vill du ladda upp installationsloggen på webben?</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="172"/>
      <source>Set partition information</source>
      <translation>Ange partitionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="201"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition with features &lt;em&gt;%3&lt;/em&gt;</source>
      <translation>Installera %1 på &lt;strong&gt;ny&lt;/strong&gt; %2 system partition med funktioner &lt;em&gt;%3&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="209"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Installera %1 på &lt;strong&gt;ny&lt;/strong&gt; %2 system partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="218"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt; and features &lt;em&gt;%3&lt;/em&gt;.</source>
      <translation>Skapa &lt;strong&gt;ny&lt;/strong&gt;%2  partition med monteringspunkt &lt;strong&gt;%1&lt;/strong&gt; och funktioner &lt;em&gt;%3&lt;/em&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="226"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;%3.</source>
      <translation>Skapa &lt;strong&gt;ny&lt;/strong&gt; %2 partition med monteringspunkt &lt;strong&gt;%1&lt;/strong&gt;%3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="240"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt; with features &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>Installera %2 på %3 system partition &lt;strong&gt;%1&lt;/strong&gt; med funktioner &lt;em&gt;%4&lt;/em&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="259"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt; and features &lt;em&gt;%4&lt;/em&gt;.</source>
      <translation>Skapa %3 partition &lt;strong&gt;%1&lt;/strong&gt;med monteringspunkt &lt;strong&gt;%2&lt;/strong&gt;och funktioner &lt;em&gt;%4&lt;/em&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="268"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;%4.</source>
      <translation>Skapa %3 partition &lt;strong&gt;%1&lt;/strong&gt; med monteringspunkt &lt;strong&gt;%2&lt;/strong&gt; %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="249"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installera %2 på %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="283"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installera uppstartshanterare på &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="292"/>
      <source>Setting up mount points.</source>
      <translation>Ställer in monteringspunkter.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="18"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>Sta&amp;rta om nu</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="75"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Allt klart.&lt;/h1&gt;&lt;br/&gt;%1 har installerats på din dator.&lt;br/&gt;Du kan nu börja använda ditt nya system.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="79"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;När denna ruta är ikryssad kommer systemet starta om omedelbart när du klickar på &lt;span style="font-style:italic;"&gt;Klar&lt;/span&gt; eller stänger installationsprogrammet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="87"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Klappat och klart.&lt;/h1&gt;&lt;br/&gt;%1 har installerats på din dator.&lt;br/&gt;Du kan nu starta om till ditt nya system, eller fortsätta att använda %2 i liveläge.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="92"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;När denna ruta är ikryssad kommer systemet starta om omedelbart när du klickar på &lt;span style="font-style:italic;"&gt;Klar&lt;/span&gt; eller stänger installationsprogrammet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="105"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installationen misslyckades&lt;/h1&gt; &lt;br/&gt;%1 har inte blivit installerad på din dator. &lt;br/&gt;Felmeddelandet var: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="113"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installationen misslyckades&lt;/h1&gt; &lt;br/&gt;%1 har inte blivit installerad på din dator. &lt;br/&gt;Felmeddelandet var: %2</translation>
    </message>
  </context>
  <context>
    <name>FinishedQmlViewStep</name>
    <message>
      <location filename="../src/modules/finishedq/FinishedQmlViewStep.cpp" line="35"/>
      <source>Finish</source>
      <translation>Slutför</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="46"/>
      <source>Finish</source>
      <translation>Slutför</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="39"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Formatera partition %1 (filsystem: %2, storlek: %3 MiB) på %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="50"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Formatera &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; med filsystem &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
      <source>%1 (%2)</source>
      <comment>partition label %1 (device path %2)</comment>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="65"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Formatera partition %1 med filsystem %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="76"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Installationsprogrammet misslyckades att formatera partition %1 på disk '%2'.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>har minst %1 GiB tillgängligt på hårddisken</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="158"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Det finns inte tillräckligt med hårddiskutrymme. Minst %1 GiB krävs.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="166"/>
      <source>has at least %1 GiB working memory</source>
      <translation>har minst %1 GiB arbetsminne</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Systemet har inte tillräckligt med fungerande minne. Minst %1 GiB krävs.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="177"/>
      <source>is plugged in to a power source</source>
      <translation>är ansluten till en strömkälla</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="178"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Systemet är inte anslutet till någon strömkälla.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="185"/>
      <source>is connected to the Internet</source>
      <translation>är ansluten till internet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="186"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Systemet är inte anslutet till internet.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="193"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>körs installationsprogammet med administratörsrättigheter (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="197"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Installationsprogammet körs inte med administratörsrättigheter.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="198"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Installationsprogammet körs inte med administratörsrättigheter.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="206"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>har en tillräckligt stor skärm för att visa hela installationsprogrammet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="210"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Skärmen är för liten för att visa installationsprogrammet.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="211"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Skärmen är för liten för att visa installationshanteraren.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="42"/>
      <source>Collecting information about your machine.</source>
      <translation>Samlar in information om din maskin.</translation>
    </message>
  </context>
  <context>
    <name>IDJob</name>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="30"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="39"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="52"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="59"/>
      <source>OEM Batch Identifier</source>
      <translation>OEM-batchidentifierare</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte skapa mappar &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte öppna fil &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Kunde inte skriva till fil &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="32"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Skapar initramfs med mkinitcpio.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="28"/>
      <source>Creating initramfs.</source>
      <translation>Skapar initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="46"/>
      <source>Konsole not installed</source>
      <translation>Konsole inte installerat</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="47"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Installera KDE Konsole och försök igen!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="118"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Kör skript: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="41"/>
      <source>Script</source>
      <translation>Skript</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <translation>Tangentbord</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Tangentbord</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System locale setting</source>
      <translation>Systemspråksinställning</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Systemspråket påverkar vilket språk och teckenuppsättning somliga kommandoradsprogram använder.&lt;br/&gt;Det nuvarande språket är &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Avsluta</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;OK</source>
      <translation>&amp;Okej</translation>
    </message>
  </context>
  <context>
    <name>LOSHJob</name>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="36"/>
      <source>Configuring encrypted swap.</source>
      <translation>Konfigurerar krypterad swap.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="88"/>
      <source>No target system available.</source>
      <translation>Inget målsystem tillgängligt.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="96"/>
      <source>No rootMountPoint is set.</source>
      <translation>Ingen rootMonteringspunkt är satt</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="101"/>
      <source>No configFilePath is set.</source>
      <translation>Ingen konfigurations filsökväg är satt.</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="18"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licensavtal&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="135"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Jag accepterar villkoren och avtalet ovan.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="137"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>Vänligen läs igenom licensavtalen för slutanvändare (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="142"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>Denna installationsprocess kommer installera proprietär mjukvara för vilken särskilda licensvillkor gäller.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="145"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>Om du inte accepterar villkoren kan inte installationsproceduren fortsätta.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="150"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>Denna installationsprocess kan installera proprietär mjukvara för vilken särskilda licensvillkor gäller, för att kunna erbjuda ytterligare funktionalitet och förbättra användarupplevelsen.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="155"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>Om du inte godkänner villkoren kommer inte proprietär mjukvara att installeras, och alternativ med öppen källkod kommer användas istället.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="43"/>
      <source>License</source>
      <translation>Licens</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="88"/>
      <source>URL: %1</source>
      <translation>URL: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="109"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;%1-drivrutin&lt;/strong&gt;&lt;br/&gt;från %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 grafikdrivrutin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 insticksprogram&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1-paket&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;från %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <translation>Fil: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide license text</source>
      <translation>Dölj licens text </translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <translation>Visa licens text</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open license agreement in browser.</source>
      <translation>Öppna licensavtal i en webbläsare.</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <translation>Region:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <translation>Zon:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change...</source>
      <translation>Ändra...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <translation>Plats</translation>
    </message>
  </context>
  <context>
    <name>LocaleTests</name>
    <message>
      <location filename="../src/libcalamares/locale/Tests.cpp" line="273"/>
      <source>Quit</source>
      <translation>Avsluta</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="76"/>
      <source>Location</source>
      <translation>Plats</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="33"/>
      <source>Configuring LUKS key file.</source>
      <translation>Konfigurerar LUKS nyckel fil.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="235"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="243"/>
      <source>No partitions are defined.</source>
      <translation>Inga partitioner är definerade.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="279"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="286"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="300"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Fel vid inställning av krypterat rootfs</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="280"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Root partition %1 är LUKS men ingen lösenfras har ställts in.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="287"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Kunde inte skapa LUKS nyckelfil för root partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="301"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>Kunde inte konfigurera LUKS nyckelfil på partition %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="37"/>
      <source>Generate machine-id.</source>
      <translation>Generera maskin-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="53"/>
      <source>Configuration Error</source>
      <translation>Konfigurationsfel</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="54"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Ingen root monteringspunkt är satt för MachineId.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="237"/>
      <source>Timezone: %1</source>
      <translation>Tidszon: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation>Snälla välj din föredragna plats på kartan så installationsprogrammet kan föreslå nationella inställningar
 och tidszons inställningar åt dig. Du kan finjustera de föreslagna inställningarna nedan. 
Sök på kartan genom att dra
  för att flytta och använd +/- knapparna för att zooma in/ut eller så använder du musens scrollhjul för att zooma.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="50"/>
      <source>Package selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
      <source>Office software</source>
      <translation>Kontors programvara</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
      <source>Office package</source>
      <translation>Kontors paket</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="53"/>
      <source>Browser software</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Browser package</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Web browser</source>
      <translation>Webbläsare</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Kernel</source>
      <comment>label for netinstall module, Linux kernel</comment>
      <translation>Kärna</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Services</source>
      <comment>label for netinstall module, system services</comment>
      <translation>Tjänster</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Login</source>
      <comment>label for netinstall module, choose login manager</comment>
      <translation>Inloggning</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Desktop</source>
      <comment>label for netinstall module, choose desktop environment</comment>
      <translation>Skrivbord</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Communication</source>
      <comment>label for netinstall module</comment>
      <translation>Kommunikation</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Development</source>
      <comment>label for netinstall module</comment>
      <translation>Utveckling</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Office</source>
      <comment>label for netinstall module</comment>
      <translation>Kontorsprogram</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Multimedia</source>
      <comment>label for netinstall module</comment>
      <translation>Multimedia</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Internet</source>
      <comment>label for netinstall module</comment>
      <translation>Internet</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Theming</source>
      <comment>label for netinstall module</comment>
      <translation>Teman</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Gaming</source>
      <comment>label for netinstall module</comment>
      <translation>Gaming</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Utilities</source>
      <comment>label for netinstall module</comment>
      <translation>Verktyg</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Applications</source>
      <translation>Program</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Anteckningar</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Gr&amp;upp:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Ange en batch-identifierare här. Den kommer lagras på målsystemet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM-konfiguration&lt;/h1&gt;&lt;p&gt;Calamares kommer att använda OEM inställningar när målsystemet konfigureras.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="122"/>
      <source>OEM Configuration</source>
      <translation>OEM Konfiguration</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="128"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Sätt OEM-batchidentifierare till &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="41"/>
      <source>Select your preferred Region, or use the default settings.</source>
      <translation>Välj din föredragna Region, eller använd standardinställningarna.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="99"/>
      <location filename="../src/modules/localeq/Offline.qml" line="175"/>
      <location filename="../src/modules/localeq/Offline.qml" line="219"/>
      <source>Timezone: %1</source>
      <translation>Tidszon: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="116"/>
      <source>Select your preferred Zone within your Region.</source>
      <translation>Välj din föredragna Zon inom din region.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="188"/>
      <source>Zones</source>
      <translation>Zoner</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="235"/>
      <source>You can fine-tune Language and Locale settings below.</source>
      <translation>Du kan finjustera språk och Nationella inställningar nedan.</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="51"/>
      <source>Password is too short</source>
      <translation>Lösenordet är för kort </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
      <source>Password is too long</source>
      <translation>Lösenordet är för långt </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>Password is too weak</source>
      <translation>Lösenordet är för svagt </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Minnesallokerings fel då '%1' skulle ställas in</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
      <source>Memory allocation error</source>
      <translation>Minnesallokerings fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
      <source>The password is the same as the old one</source>
      <translation>Lösenordet är samma som det gamla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="203"/>
      <source>The password is a palindrome</source>
      <translation>Lösenordet är en palindrom</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
      <source>The password differs with case changes only</source>
      <translation>Endast stora och små bokstäver skiljer lösenorden åt</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="207"/>
      <source>The password is too similar to the old one</source>
      <translation>Lösenordet liknar för mycket det gamla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
      <source>The password contains the user name in some form</source>
      <translation>Lösenordet innehåller ditt användarnamn i någon form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="211"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Lösenordet innehåller ord från användarens namn i någon form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Lösenordet innehåller förbjudna ord i någon form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="221"/>
      <source>The password contains too few digits</source>
      <translation>Lösenordet innehåller för få siffror</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="228"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Lösenordet innehåller för få stora bokstäver</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="232"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Lösenordet innehåller färre än %n små bokstäver</numerusform>
        <numerusform>Lösenordet innehåller färre än %n små bokstäver</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Lösenordet innehåller för få små bokstäver</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="242"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Lösenordet innehåller för få icke-alfanumeriska tecken</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="249"/>
      <source>The password is too short</source>
      <translation>Detta lösenordet är för kort </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="258"/>
      <source>The password does not contain enough character classes</source>
      <translation>Lösenordet innehåller inte tillräckligt många teckenklasser</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Lösenordet innehåller för många liknande tecken efter varandra</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Lösenordet innehåller för många tecken från samma klass i rad</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Lösenord innehåller mindre än %n siffror</numerusform>
        <numerusform>Lösenordet innehåller mindre än %n siffror</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Lösenord innehåller mindre än %n stora bokstäver</numerusform>
        <numerusform>Lösenordet innehåller mindre än %n stora bokstäver</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>Lösenord innehåller färre än %n icke alfanumeriska tecken</numerusform>
        <numerusform>Lösenordet innehåller färre än %n icke alfanumeriska tecken</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="246"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Lösenord är kortare än %n tecken</numerusform>
        <numerusform>Lösenordet är kortare än %n tecken</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Lösenordet är en roterad version av det förra</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Lösenord innehåller färre än %n teckenklasser</numerusform>
        <numerusform>Lösenordet innehåller färre än %n teckenklasser</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="262"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Lösenord innehåller fler än %n likadana tecken i rad</numerusform>
        <numerusform>Lösenordet innehåller fler än %n likadana tecken i rad</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Lösenord innehåller fler än %n tecken från samma klass i rad</numerusform>
        <numerusform>Lösenordet innehåller fler än %n tecken från samma klass i rad</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>Lösenord innehåller en monoton sekvens längre än %n tecken</numerusform>
        <numerusform>Lösenordet innehåller en monoton sekvens längre än %n tecken</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="286"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Lösenordet innehåller en för lång monoton teckensekvens</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>No password supplied</source>
      <translation>Inget lösenord angivit</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="291"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Kan inte hämta slumptal från slumptalsgeneratorn</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Lösenordsgenerering misslyckades - för lite entropi tillgänglig för givna inställningar</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Lösenordet klarar inte ordlistekontrollen - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="301"/>
      <source>The password fails the dictionary check</source>
      <translation>Lösenordet klarar inte ordlistekontrollen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="305"/>
      <source>Unknown setting - %1</source>
      <translation>Okänd inställning - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="307"/>
      <source>Unknown setting</source>
      <translation>Okänd inställning</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="311"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Dåligt heltals värde på inställning - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="313"/>
      <source>Bad integer value</source>
      <translation>Dåligt heltals värde</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="317"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Inställning %1 är inte av heltals typ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="319"/>
      <source>Setting is not of integer type</source>
      <translation>Inställning är inte av heltals typ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="323"/>
      <source>Setting %1 is not of string type</source>
      <translation>Inställning %1 är inte av sträng typ </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="325"/>
      <source>Setting is not of string type</source>
      <translation>Inställning %1 är inte av sträng typ </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="327"/>
      <source>Opening the configuration file failed</source>
      <translation>Öppnande av konfigurationsfilen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="329"/>
      <source>The configuration file is malformed</source>
      <translation>Konfigurationsfilen är felaktig</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="331"/>
      <source>Fatal failure</source>
      <translation>Fatalt fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="333"/>
      <source>Unknown error</source>
      <translation>Okänt fel </translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="830"/>
      <source>Password is empty</source>
      <translation>Lösenordet är blankt</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="24"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="50"/>
      <source>Product Name</source>
      <translation>Produktnamn</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="63"/>
      <source>TextLabel</source>
      <translation>TextLabel</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="79"/>
      <source>Long Product Description</source>
      <translation>Lång produktbeskrivning</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Paketval</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Välj en produkt från listan. Den valda produkten kommer att installeras.</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="205"/>
      <source>Name</source>
      <translation>Namn</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="205"/>
      <source>Description</source>
      <translation>Beskrivning</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard Model:</source>
      <translation>Tangentbordsmodell:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="135"/>
      <source>Type here to test your keyboard</source>
      <translation>Skriv här för att testa ditt tangentbord</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Vad heter du?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Ditt Fullständiga namn </translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Vilket namn vill du använda för att logga in?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>inloggning</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Vad är namnet på datorn?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Detta namn används om du gör datorn synlig för andra i ett nätverk.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Datornamn</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Välj ett lösenord för att hålla ditt konto säkert.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel. Ett bra lösenord innehåller en blandning av bokstäver, nummer och interpunktion, bör vara minst åtta tecken långt, och bör ändras regelbundet.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Repetera Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>När den här rutan är förkryssad kommer kontroll av lösenordsstyrka att genomföras, och du kommer inte kunna använda ett svagt lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Kräv starkt lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Logga in automatiskt utan att fråga efter lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Använd samma lösenord för administratörskontot.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Välj ett lösenord för administratörskontot.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="189"/>
      <source>Root</source>
      <translation>Root</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
      <source>Home</source>
      <translation>Hem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Boot</source>
      <translation>Boot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>EFI system</source>
      <translation>EFI-system</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="206"/>
      <source>Swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="210"/>
      <source>New partition for %1</source>
      <translation>Ny partition för %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="214"/>
      <source>New partition</source>
      <translation>Ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="238"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1  %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="157"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="201"/>
      <source>Free Space</source>
      <translation>Ledigt utrymme</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="161"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="205"/>
      <source>New partition</source>
      <translation>Ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="298"/>
      <source>Name</source>
      <translation>Namn</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="300"/>
      <source>File System</source>
      <translation>Filsystem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="302"/>
      <source>File System Label</source>
      <translation>Filsystem etikett</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="304"/>
      <source>Mount Point</source>
      <translation>Monteringspunkt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="306"/>
      <source>Size</source>
      <translation>Storlek</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Lagringsenhet:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>Återställ alla ändringar</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Ny partitions&amp;tabell</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Skapa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>Ändra</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>Ta bort</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Ny volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Ändra storlek på volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Deaktivera volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Ta bort volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Installera uppstartshanterare på:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="228"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Är du säker på att du vill skapa en ny partitionstabell på %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="263"/>
      <source>Can not create new partition</source>
      <translation>Kan inte skapa ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="264"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>Partitionstabellen på %1 har redan %2 primära partitioner och inga fler kan läggas till. Var god ta bort en primär partition och lägg till en utökad partition istället.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="56"/>
      <source>Gathering system information...</source>
      <translation>Samlar systeminformation...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="111"/>
      <source>Partitions</source>
      <translation>Partitioner</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="254"/>
      <source>Unsafe partition actions are enabled.</source>
      <translation>Osäkra partitionsåtgärder är aktiverade.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="257"/>
      <source>Partitioning is configured to &lt;b&gt;always&lt;/b&gt; fail.</source>
      <translation>Partitionering är konfigurerad till att &lt;b&gt;alltid&lt;/b&gt; misslyckas.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="260"/>
      <source>No partitions will be changed.</source>
      <translation>Inga partitioner kommer att ändras.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="300"/>
      <source>Current:</source>
      <translation>Nuvarande:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="318"/>
      <source>After:</source>
      <translation>Efter:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="529"/>
      <source>No EFI system partition configured</source>
      <translation>Ingen EFI system partition konfigurerad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="533"/>
      <source>EFI system partition configured incorrectly</source>
      <translation>EFI-systempartitionen felaktigt konfigurerad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="538"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a suitable filesystem.</source>
      <translation>En EFI-systempartition krävs för att starta %1 &lt;br/&gt;&lt;br/&gt;För att konfigurera en EFI-systempartition, gå tillbaka och välj eller skapa ett lämpligt filsystem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="549"/>
      <source>The filesystem must be mounted on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Filsystemet måste vara monterat på &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="555"/>
      <source>The filesystem must have type FAT32.</source>
      <translation>Filsystemet måste vara av typ FAT32.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="563"/>
      <source>The filesystem must be at least %1 MiB in size.</source>
      <translation>Filsystemet måste vara minst %1 MiB i storlek.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="569"/>
      <source>The filesystem must have flag &lt;strong&gt;%1&lt;/strong&gt; set.</source>
      <translation>Filsystemet måste ha flagga &lt;strong&gt;%1&lt;/strong&gt; satt.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="575"/>
      <source>You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Du kan fortsätta utan att ställa in en EFI-systempartition men ditt system kanske inte startar.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="593"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Alternativ för att använda GPT på BIOS</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="594"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;%2&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>En GPT-partitionstabell är det bästa alternativet för alla system. Det här installationsprogrammet stöder också en sådan installation för BIOS-system. &lt;br/&gt;&lt;br/&gt;för att konfigurera en GPT-partitionstabell i BIOS, (om du inte redan har gjort det) gå tillbaka och ställ in partitionstabellen till GPT, skapa sedan en 8 MB oformaterad partition med &lt;strong&gt;%2&lt;/strong&gt; flaggan aktiverad.&lt;br/&gt;&lt;br/&gt;En oformaterad 8 MB partition krävs för att starta %1 på ett BIOS-system med GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="626"/>
      <source>Boot partition not encrypted</source>
      <translation>Boot partition inte krypterad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="627"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>En separat uppstartspartition skapades tillsammans med den krypterade rootpartitionen, men uppstartspartitionen är inte krypterad.&lt;br/&gt;&lt;br/&gt;Det finns säkerhetsproblem med den här inställningen, eftersom viktiga systemfiler sparas på en okrypterad partition.&lt;br/&gt;Du kan fortsätta om du vill, men upplåsning av filsystemet kommer hända senare under uppstart av systemet.&lt;br/&gt;För att kryptera uppstartspartitionen, gå tillbaka och återskapa den, och välj &lt;strong&gt;Kryptera&lt;/strong&gt; i fönstret när du skapar partitionen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="718"/>
      <source>has at least one disk device available.</source>
      <translation>har åtminstone en diskenhet tillgänglig.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="719"/>
      <source>There are no partitions to install on.</source>
      <translation>Det finns inga partitioner att installera på.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Jobb för Plasmas utseende och känsla</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Kunde inte välja KDE Plasma-paket för utseende och känsla</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="79"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Var god välj ett utseende och känsla för KDE Plasma skrivbordet. Du kan hoppa över detta steget och ställa in utseende och känsla när systemet är installerat. Klicka på ett val för utseende och känsla för att få en förhandsgranskning av det valet.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="84"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Var god välj ett utseende och känsla för KDE Plasma skrivbordet. Du kan hoppa över detta steget och ställa in utseende och känsla när systemet är installerat. Klicka på ett val för utseende och känsla för att få en förhandsgranskning av det valet.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <translation>Utseende och känsla</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="53"/>
      <source>Saving files for later ...</source>
      <translation>Sparar filer tills senare ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="61"/>
      <source>No files configured to save for later.</source>
      <translation>Inga filer konfigurerade att spara till senare.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="85"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Inte alla av konfigurationsfilerna kunde bevaras.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="309"/>
      <source>
There was no output from the command.</source>
      <translation>
Det kom ingen utdata från kommandot.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="310"/>
      <source>
Output:
</source>
      <translation>
Utdata:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="314"/>
      <source>External command crashed.</source>
      <translation>Externt kommando kraschade.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="315"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; kraschade.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="320"/>
      <source>External command failed to start.</source>
      <translation>Externt kommando misslyckades med att starta</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="321"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; misslyckades med att starta. </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="325"/>
      <source>Internal error when starting command.</source>
      <translation>Internt fel under kommandostart.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="326"/>
      <source>Bad parameters for process job call.</source>
      <translation>Ogiltiga parametrar för processens uppgiftsanrop.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="330"/>
      <source>External command failed to finish.</source>
      <translation>Fel inträffade när externt kommando kördes.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="331"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt; misslyckades att slutföras på %2 sekunder.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="338"/>
      <source>External command finished with errors.</source>
      <translation>Externt kommando kördes färdigt med fel.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="339"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Kommando &lt;i&gt;%1&lt;/i&gt;avslutades under körning med avslutningskod %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Translation.cpp" line="145"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="33"/>
      <source>unknown</source>
      <translation>okänd</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="35"/>
      <source>extended</source>
      <translation>utökad</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="37"/>
      <source>unformatted</source>
      <translation>oformaterad</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="39"/>
      <source>swap</source>
      <translation>swap</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="130"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="167"/>
      <source>Default</source>
      <translation>Standard</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="72"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="76"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>File not found</source>
      <translation>Filen hittades inte </translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="65"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Sökväg &lt;pre&gt;%1&lt;/pre&gt; måste vara en absolut sökväg.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="83"/>
      <source>Directory not found</source>
      <translation>Katalog hittades inte</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="84"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="94"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Kunde inte skapa ny slumpmässig fil &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="74"/>
      <source>No product</source>
      <translation>Ingen produkt</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="82"/>
      <source>No description provided.</source>
      <translation>Ingen beskrivning tillhandahålls.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="44"/>
      <source>(no mount point)</source>
      <translation>(ingen monteringspunkt)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="40"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Opartitionerat utrymme eller okänd partitionstabell</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Denna dator uppfyller inte alla rekommenderade krav för att installera %1.
&lt;br/&gt;Installationen kan fortsätta, men alla alternativ och funktioner kanske inte kan användas.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="34"/>
      <source>Remove live user from target system</source>
      <translation>Tar bort live användare från målsystemet</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="38"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Ta bort volymgrupp med namnet %1. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="32"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ta bort volymgrupp med namnet &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Installationsprogrammet misslyckades att ta bort en volymgrupp med namnet '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="128"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Välj var du vill installera %1.&lt;br/&gt;&lt;font color="red"&gt;Varning: &lt;/font&gt;detta kommer att radera alla filer på den valda partitionen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="150"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Det valda alternativet verkar inte vara en giltig partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="158"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 kan inte installeras i tomt utrymme. Välj en existerande partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 kan inte installeras på en utökad partition. Välj en existerande primär eller logisk partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 kan inte installeras på den här partitionen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="184"/>
      <source>Data partition (%1)</source>
      <translation>Datapartition (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="204"/>
      <source>Unknown system partition (%1)</source>
      <translation>Okänd systempartition (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="208"/>
      <source>%1 system partition (%2)</source>
      <translation>Systempartition för %1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="220"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Partitionen %1 är för liten för %2. Välj en partition med minst storleken %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="242"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Kan inte hitta en EFI-systempartition någonstans på detta system. Var god gå tillbaka och använd manuell partitionering för att installera %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="253"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="269"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="294"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 kommer att installeras på %2.&lt;br/&gt;&lt;font color="red"&gt;Varning: &lt;/font&gt;all data på partition %2 kommer att gå förlorad.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-systempartitionen %1 kommer att användas för att starta %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="277"/>
      <source>EFI system partition:</source>
      <translation>EFI-systempartition:</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="38"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Denna dator uppfyller inte minimikraven för att installera %1.&lt;br/&gt;
Installationen kan inte fortsätta.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Denna dator uppfyller inte alla rekommenderade krav för att installera %1.
&lt;br/&gt;Installationen kan fortsätta, men alla alternativ och funktioner kanske inte kan användas.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="45"/>
      <source>Resize Filesystem Job</source>
      <translation>Jobb för storleksförändring av filsystem</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="168"/>
      <source>Invalid configuration</source>
      <translation>Ogiltig konfiguration</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>Jobbet för storleksförändring av filsystem har en felaktig konfiguration och kommer inte köras.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="174"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore inte tillgänglig</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="175"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>Calamares kan inte starta KPMCore för jobbet att ändra filsystemsstorlek.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="183"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="192"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="203"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="212"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="230"/>
      <source>Resize Failed</source>
      <translation>Storleksändringen misslyckades</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="185"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>Kunde inte hitta filsystemet %1 på systemet, och kan inte ändra storlek på det.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>Kunde inte hitta enheten %1 på systemet, och kan inte ändra storlek på den.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="194"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="205"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>Det går inte att ändra storlek på filsystemet %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The device %1 cannot be resized.</source>
      <translation>Det går inte att ändra storlek på enheten %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>Filsystemet %1 måste ändra storlek, men storleken kan inte ändras.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>Enheten %1 måste ändra storlek, men storleken kan inte ändras</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="41"/>
      <source>Resize partition %1.</source>
      <translation>Ändra storlek på partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>Ändra &lt;strong&gt;%2MiB&lt;/strong&gt;-partitionen &lt;strong&gt;%1&lt;/strong&gt; till &lt;strong&gt;%3MB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="59"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Ändrar storlek på partitionen %1 från %2MB till %3MB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="77"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Installationsprogrammet misslyckades med att ändra storleken på partition %1 på disk '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <translation>Ändra storlek på volymgrupp</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="28"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>Ändra storlek på volymgruppen som heter %1 från %2 till %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Byt storlek på volymgrupp med namn &lt;strong&gt;%1&lt;/strong&gt;  från &lt;strong&gt;%2&lt;/strong&gt;till &lt;strong&gt;%3&lt;/strong&gt;. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Installationsprogrammet misslyckades att byta storlek på en volymgrupp med namn '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="138"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>För bästa resultat, vänligen se till att datorn:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="139"/>
      <source>System requirements</source>
      <translation>Systemkrav</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Scanning storage devices...</source>
      <translation>Skannar lagringsenheter...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Partitioning</source>
      <translation>Partitionering</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="36"/>
      <source>Set hostname %1</source>
      <translation>Ange värdnamn %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="43"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ange värdnamn &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="50"/>
      <source>Setting hostname %1.</source>
      <translation>Anger värdnamn %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="124"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="131"/>
      <source>Internal Error</source>
      <translation>Internt fel</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="142"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="159"/>
      <source>Cannot write hostname to target system</source>
      <translation>Kan inte skriva värdnamn till målsystem</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="55"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Sätt tangentbordsmodell till %1, layout till %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration för konsolen.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="397"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="414"/>
      <source>Failed to write to %1</source>
      <translation>Misslyckades med att skriva %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="396"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration för X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="413"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Misslyckades med att skriva tangentbordskonfiguration till den existerande katalogen /etc/default.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="45"/>
      <source>Set flags on partition %1.</source>
      <translation>Sätt flaggor på partition %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="51"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>Sätt flaggor på %1MiB %2 partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="55"/>
      <source>Set flags on new partition.</source>
      <translation>Sätt flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rensa flaggor på partition &lt;strong&gt;%1&lt;/strong&gt;,</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="73"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Rensa flaggor på %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="77"/>
      <source>Clear flags on new partition.</source>
      <translation>Rensa flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="82"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Flagga partition &lt;strong&gt;%1&lt;/strong&gt; som &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Flagga %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition som &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Flagga ny partition som &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="110"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rensar flaggor på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="116"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Rensa flaggor på %1MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
      <source>Clearing flags on new partition.</source>
      <translation>Rensar flaggor på ny partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="126"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sätter flaggor &lt;strong&gt;%2&lt;/strong&gt; på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="135"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Sätter flaggor &lt;strong&gt;%3&lt;/strong&gt; på  %11MiB &lt;strong&gt;%2&lt;/strong&gt;partition.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="142"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Sätter flaggor &lt;strong&gt;%1&lt;/strong&gt; på ny partition</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="156"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Installationsprogrammet misslyckades med att sätta flaggor på partition %1. </translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="40"/>
      <source>Set password for user %1</source>
      <translation>Ange lösenord för användare %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="47"/>
      <source>Setting password for user %1.</source>
      <translation>Ställer in lösenord för användaren %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>Bad destination system path.</source>
      <translation>Ogiltig systemsökväg till målet.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="82"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMonteringspunkt är %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="88"/>
      <source>Cannot disable root account.</source>
      <translation>Kunde inte inaktivera root konto.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd stoppades med felkod %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot set password for user %1.</source>
      <translation>Kan inte ställa in lösenord för användare %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod avslutade med felkod %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="34"/>
      <source>Set timezone to %1/%2</source>
      <translation>Sätt tidszon till %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="62"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Kan inte komma åt vald tidszonssökväg.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="63"/>
      <source>Bad path: %1</source>
      <translation>Ogiltig sökväg: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot set timezone.</source>
      <translation>Kan inte ställa in tidszon.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Skapande av länk misslyckades, mål: %1; länknamn: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="77"/>
      <source>Cannot set timezone,</source>
      <translation>Kan inte ställa in tidszon,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="78"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Kunde inte öppna /etc/timezone för skrivning</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="182"/>
      <source>Preparing groups.</source>
      <translation>Förbereder grupper.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="194"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="199"/>
      <source>Could not create groups in target system</source>
      <translation>Kunde inte skapa grupper på målsystemet</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="200"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>Dessa grupper saknas på målsystemet: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="34"/>
      <source>Configure &lt;pre&gt;sudo&lt;/pre&gt; users.</source>
      <translation>Konfigurerar &lt;pre&gt;sudo&lt;/pre&gt; användare.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="71"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Kunde inte chmodda sudoerfilen.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="76"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Kunde inte skapa sudoerfil för skrivning.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="40"/>
      <source>Shell Processes Job</source>
      <translation>Jobb för skalprocesser</translation>
    </message>
  </context>
  <context>
    <name>SlideCounter</name>
    <message>
      <location filename="../src/qml/calamares/slideshow/SlideCounter.qml" line="27"/>
      <source>%L1 / %L2</source>
      <extracomment>slide counter, %1 of %2 (numeric)</extracomment>
      <translation>%L1 / %L2</translation>
    </message>
  </context>
  <context>
    <name>StandardButtons</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="23"/>
      <source>&amp;OK</source>
      <translation>&amp;Okej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="24"/>
      <source>&amp;Yes</source>
      <translation>&amp;Ja</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="25"/>
      <source>&amp;No</source>
      <translation>&amp;Nej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="26"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Avsluta</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="27"/>
      <source>&amp;Close</source>
      <translation>&amp;Stäng</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="101"/>
      <source>Installation feedback</source>
      <translation>Installationsåterkoppling</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="107"/>
      <source>Sending installation feedback.</source>
      <translation>Skickar installationsåterkoppling</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="125"/>
      <source>Internal error in install-tracking.</source>
      <translation>Internt fel i install-tracking.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="126"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP-begäran tog för lång tid.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="193"/>
      <source>KDE user feedback</source>
      <translation>KDE användarfeedback </translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="199"/>
      <source>Configuring KDE user feedback.</source>
      <translation>Konfigurerar KDE användarfeedback.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="221"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="229"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>Fel vid konfigurering av KDE användarfeedback.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="222"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>Kunde inte konfigurera KDE användarfeedback korrekt, script fel %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="230"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>Kunde inte konfigurera KDE användarfeedback korrekt, Calamares fel  %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
      <source>Machine feedback</source>
      <translation>Maskin feedback</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="142"/>
      <source>Configuring machine feedback.</source>
      <translation>Konfigurerar maskin feedback</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="165"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="174"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Fel vid konfigurering av maskin feedback</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="167"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Kunde inte konfigurera maskin feedback korrekt, script fel %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="176"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Kunde inte konfigurera maskin feedback korrekt, Calamares fel  %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="18"/>
      <source>Form</source>
      <translation>Form</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Platshållare</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Klicka här för att inte &lt;span style=" font-weight:600;"&gt; skicka någon information alls om din installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt; Klicka här för information om användarfeedback &lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>Spårning hjälper %1 att se hur ofta den är installerad, vilken hårdvara den är installerad på och vilka program som används. För att se vad som skickas, Klicka på hjälp ikonen vad sidan av varje område för att se vad som skickas.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Genom att välja detta, kommer du skicka information om din installation och hårdvara. Denna information kommer &lt;b&gt;enbart skickas en gång&lt;/b&gt; efter att installationen slutförts.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Genom att välja detta, kommer du periodiskt skicka information om din &lt;b&gt;maskin&lt;/b&gt;installation, hårdvara och program, till %1</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Genom att välja detta, kommer du regelbundet skicka information om din &lt;b&gt;användar&lt;/b&gt;installation, hårdvara, program och dina program användningsmönster till %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <translation>Feedback</translation>
    </message>
  </context>
  <context>
    <name>UmountJob</name>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="39"/>
      <source>Unmount file systems.</source>
      <translation>Avmontera filsystem.</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="124"/>
      <source>No target system available.</source>
      <translation>Inget målsystem tillgängligt.</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="132"/>
      <source>No rootMountPoint is set.</source>
      <translation>Ingen rootMonteringspunkt är satt</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="190"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Om mer än en person skall använda datorn så kan du skapa flera användarkonton när inställningarna är klara.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="196"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Om mer än en person skall använda datorn så kan du skapa flera användarkonton när installationen är klar.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="35"/>
      <source>Users</source>
      <translation>Användare</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Användare</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Nyckel</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Värde</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Skapa volymgrupp</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Lista på fysiska volymer</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Volymgrupp namn:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Volymgrupp typ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Storlek på fysisk volymdel (PE):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Total storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Använd storlek:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Totala sektorer:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Antal LV:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="18"/>
      <source>Form</source>
      <translation>Formulär</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Välj program och system språk </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>&amp;About</source>
      <translation>&amp;Om</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="150"/>
      <source>Open donations website</source>
      <translation>Besök webbplatsen för donationer</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>&amp;Donate</source>
      <translation>&amp;Donera</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="163"/>
      <source>Open help and support website</source>
      <translation>Besök webbplatsen för hjälp och support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>&amp;Support</source>
      <translation>&amp;Support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Besök webbplatsen för problem och felsökning</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Kända problem</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="189"/>
      <source>Open release notes website</source>
      <translation>Besök webbplatsen för versionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="192"/>
      <source>&amp;Release notes</source>
      <translation>Versionsinformation, &amp;R</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="216"/>
      <source>%1 support</source>
      <translation>%1-support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>About %1 setup</source>
      <translation>Om inställningarna för %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>About %1 installer</source>
      <translation>Om %1-installationsprogrammet</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="40"/>
      <source>Welcome</source>
      <translation>Välkommen</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="46"/>
      <source>Welcome</source>
      <translation>Välkommen</translation>
    </message>
  </context>
  <context>
    <name>ZfsJob</name>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="101"/>
      <source>Create ZFS pools and datasets</source>
      <translation>Skapa ZFS pools och datasets</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="162"/>
      <source>Failed to create zpool on </source>
      <translation>Misslyckades att skapa zpool på</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="180"/>
      <source>Configuration Error</source>
      <translation>Konfigurationsfel</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="181"/>
      <source>No partitions are available for ZFS.</source>
      <translation>Inga partitioner är tillgängliga för ZFS.</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <source>Internal data missing</source>
      <translation>Intern data saknas</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="257"/>
      <source>Failed to create zpool</source>
      <translation>Misslyckades med att skapa zpool</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="329"/>
      <source>Failed to create dataset</source>
      <translation>Misslyckades med att skapa dataset</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="330"/>
      <source>The output was: </source>
      <translation>Utdatan var:</translation>
    </message>
  </context>
  <context>
    <name>about</name>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="79"/>
      <source>Back</source>
      <translation>Bakåt</translation>
    </message>
  </context>
  <context>
    <name>calamares-sidebar</name>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="79"/>
      <source>Show debug information</source>
      <translation>Visa avlusningsinformation</translation>
    </message>
  </context>
  <context>
    <name>finishedq</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>Installationen är klar</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <translation>%1 har installerats på din dator. &lt;br/&gt;
            Du kan nu starta om i ditt nya system eller fortsätta använda Live-miljön. </translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="65"/>
      <source>Close Installer</source>
      <translation>Stäng installationsprogrammet</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="71"/>
      <source>Restart System</source>
      <translation>Starta om System</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <translation>&lt;p&gt;En fullständig logg över installationen är tillgänglig som installation.log i hemkatalogen av Live användaren.&lt;br/&gt;
            Denna logg är kopierad till /var/log/installation.log på målsystemet.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>finishedq@mobile</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>Installationen är klar</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart your device.</source>
      <translation>%1 har nu installerats på din dator.&lt;br/&gt;
            Du kan nu starta om din enhet.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="65"/>
      <source>Close</source>
      <translation>Stäng</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="71"/>
      <source>Restart</source>
      <translation>Starta om</translation>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="50"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Språk&lt;/h1&gt; &lt;/br&gt;
Systemspråket påverkar vilket språk och teckenuppsättning somliga kommandoradsprogram använder. Den nuvarande inställningen är &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="123"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Nationella inställningar&lt;/h1&gt; &lt;/br&gt;
Systems nationella inställningar påverkar nummer och datumformat. Den nuvarande inställningen är &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="189"/>
      <source>Back</source>
      <translation>Bakåt</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="60"/>
      <source>To activate keyboard preview, select a layout.</source>
      <translation>Välj en layout för att aktivera förhandsgranskning av tangentbord.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="86"/>
      <source>Keyboard Model:</source>
      <translation>Tangentbordsmodell:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="256"/>
      <source>Layouts</source>
      <translation>Layouter</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="265"/>
      <source>Type here to test your keyboard</source>
      <translation>Skriv här för att testa ditt tangentbord</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="180"/>
      <source>Variants</source>
      <translation>Varianter</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="81"/>
      <source>Change</source>
      <translation>Ändra</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Detta är exempel versionsinformation.</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice är ett kraftfull och gratis Office paket, som används av miljontals människor runt om i världen. Det innehåller flera program som gör det till de mest mångsidiga Office paketet som är gratis och öppen källkod på marknaden.&lt;br/&gt;
                    Standard alternativ.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Om du inte vill installera ett office paket, bara välj Inget Office paket. Du kan alltid lägga till ett (eller mer) senare på ditt installerade system om behovet uppstår.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Inget Office paket</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>Skapa en minimal skrivbordsinstallation, ta bort alla extra program och välj senare på vad du vill lägga till i ditt system. Exempel på vad som inte kommer att finnas på en sådan installation, det kommer inte att finnas något Office paket, inga mediaspelare, ingen bildvisare eller utskriftsstöd. Det kommer bara att finnas en skrivbordsmiljö, filbläddrare, pakethanterare, textredigerare och enkel webbläsare.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimal installation</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>Välj ett alternativ för din installation, eller använd standard: LibreOffice ingår.</translation>
    </message>
  </context>
  <context>
    <name>release_notes</name>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="45"/>
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
            &lt;p&gt;Detta är en exempelfil för QML, som visar inställningar för RichText och innehåll som är Flickable.&lt;/p&gt;

            &lt;p&gt;QML med RichText kan använda HTML-taggar. Innehåll som är Flickable är användbart på pekskärmar.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Detta är fet text&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;Detta är kursiv text&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;Detta är understruken text&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Denna text är centrerad.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;Detta är överstruket&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Kodexample:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Listor:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;System med Intel-processor&lt;/li&gt;
                &lt;li&gt;System med AMD-processor&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Den vertikala rullningslisten är justerbar, nuvarande bredd är satt till 10.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>Bakåt</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="43"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Välj ditt användarnamn och inloggningsuppgifter för att logga in och utföra admin-uppgifter</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="56"/>
      <source>What is your name?</source>
      <translation>Vad heter du?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="63"/>
      <source>Your Full Name</source>
      <translation>Ditt Fullständiga namn </translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Vilket namn vill du använda för att logga in?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login Name</source>
      <translation>Inloggningsnamn</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="116"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Om mer än en person skall använda datorn så kan du skapa flera användarkonton efter installationen. </translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="129"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Endast små bokstäver, nummer, understreck och bindestreck är tillåtet.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="138"/>
      <source>root is not allowed as username.</source>
      <translation>root är inte tillåtet som användarnamn.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="147"/>
      <source>What is the name of this computer?</source>
      <translation>Vad är namnet på datorn?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="153"/>
      <source>Computer Name</source>
      <translation>Datornamn</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="180"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Detta namn kommer användas om du gör datorn synlig för andra i ett nätverk.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="202"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost är inte tillåtet som värdnamn.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="211"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Välj ett lösenord för att hålla ditt konto säkert.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="221"/>
      <source>Password</source>
      <translation>Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="238"/>
      <source>Repeat Password</source>
      <translation>Repetera Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="265"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel. Ett bra lösenord innehåller en blandning av bokstäver, nummer och interpunktion, bör vara minst åtta tecken långt, och bör ändras regelbundet.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="410"/>
      <source>Validate passwords quality</source>
      <translation>Validera lösenords kvalite</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="420"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>När den här rutan är förkryssad kommer kontroll av lösenordsstyrka att genomföras, och du kommer inte kunna använda ett svagt lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="402"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Logga in automatiskt utan att fråga efter ett lösenord.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="193"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>Endast bokstäver, nummer, understreck och bindestreck är tillåtet, minst två tecken.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="297"/>
      <source>Reuse user password as root password</source>
      <translation>Återanvänd användarlösenord som root lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="305"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Använd samma lösenord för administratörskontot.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Välj ett root lösenord för att hålla ditt konto säkert.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="328"/>
      <source>Root Password</source>
      <translation>Root Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="346"/>
      <source>Repeat Root Password</source>
      <translation>Repetera Root Lösenord</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="372"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Ange samma lösenord två gånger, så att det kan kontrolleras för stavfel.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="35"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Välkommen till %2 installationsprogram för &lt;quote&gt;%1&lt;/quote&gt;&lt;/h3&gt;
            &lt;p&gt;Detta program kommer ställa några frågor och installera %1 på din dator.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="66"/>
      <source>About</source>
      <translation>Om</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Support</source>
      <translation>Support</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Known issues</source>
      <translation>Kända problem</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="102"/>
      <source>Release notes</source>
      <translation>Versionsinformation</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="114"/>
      <source>Donate</source>
      <translation>Donera</translation>
    </message>
  </context>
</TS>

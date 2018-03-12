<?xml version="1.0" ?><!DOCTYPE TS><TS language="da" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>Systemets &lt;strong&gt;bootmiljø&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Ældre x86-systemer understøtter kun &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Moderne systemer bruger normalt &lt;strong&gt;EFI&lt;/strong&gt;, men kan også vises som BIOS hvis det startes i kompatibilitetstilstand.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>Systemet blev startet med et &lt;strong&gt;EFI&lt;/strong&gt;-bootmiljø.&lt;br&gt;&lt;br&gt;For at konfigurere opstart fra et EFI-miljø, bliver installationsprogrammet nødt til at installere et bootloaderprogram, såsom &lt;strong&gt;GRUB&lt;/strong&gt; eller &lt;strong&gt;systemd-boot&lt;/strong&gt; på en &lt;strong&gt;EFI-systempartition&lt;/strong&gt;. Det sker automatisk, med mindre du vælger manuel partitionering, hvor du i så fald skal vælge eller oprette den selv.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>Systemet blev startet med et &lt;strong&gt;BIOS&lt;/strong&gt;-bootmiljø.&lt;br&gt;&lt;br&gt;For at konfigurere opstart fra et BIOS-miljø, bliver installationsprogrammet nødt til at installere en bootloader, såsom &lt;strong&gt;GRUB&lt;/strong&gt;, enten i begyndelsen af en partition eller på &lt;strong&gt;Master Boot Record&lt;/strong&gt; nær begyndelsen af partitionstabellen (foretrukket). Det sker automatisk, med mindre du vælger manuel partitionering, hvor du i så fald skal opsætte den selv.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>Master Boot Record af %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>Bootpartition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>Systempartition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>Installér ikke en bootloader</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="125"/>
        <source>%1 (%2)</source>
        <translation>%1 (%2)</translation>
    </message>
</context>
<context>
    <name>Calamares::DebugWindow</name>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>Globalt lager</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>Jobkø</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>Moduler</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation>Type:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation>ingen</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation>Grænseflade:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation>Værktøjer</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation>Fejlretningsinformation</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="77"/>
        <source>Install</source>
        <translation>Installation</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="86"/>
        <source>Done</source>
        <translation>Færdig</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="51"/>
        <source>Run command %1 %2</source>
        <translation>Kør kommando %1 %2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="60"/>
        <source>Running command %1 %2</source>
        <translation>Kører kommando %1 %2</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="265"/>
        <source>Running %1 operation.</source>
        <translation>Kører %1-handling.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="280"/>
        <source>Bad working directory path</source>
        <translation>Ugyldig arbejdsmappesti</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="281"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>Arbejdsmappen %1 til python-jobbet %2 er ikke læsbar.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="291"/>
        <source>Bad main script file</source>
        <translation>Ugyldig primær skriptfil</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="292"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>Primær skriptfil %1 til python-jobbet %2 er ikke læsbar.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="368"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>Boost.Python-fejl i job &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="73"/>
        <source>&amp;Back</source>
        <translation>&amp;Tilbage</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Next</source>
        <translation>&amp;Næste</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="279"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Annullér</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="280"/>
        <source>Cancel installation without changing the system.</source>
        <translation>Annullér installation uden at ændre systemet.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="291"/>
        <source>Cancel installation?</source>
        <translation>Annullér installationen?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="292"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>Vil du virkelig annullere den igangværende installationsproces?
Installationsprogrammet vil stoppe og alle ændringer vil gå tabt.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="297"/>
        <source>&amp;Yes</source>
        <translation>&amp;Ja</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="298"/>
        <source>&amp;No</source>
        <translation>&amp;Nej</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="162"/>
        <source>&amp;Close</source>
        <translation>&amp;Luk</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="212"/>
        <source>Continue with setup?</source>
        <translation>Fortsæt med opsætningen?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="213"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>%1-installationsprogrammet er ved at foretage ændringer til din disk for at installere %2. &lt;br/&gt;&lt;strong&gt;Det vil ikke være muligt at fortryde ændringerne.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
        <source>&amp;Install now</source>
        <translation>&amp;Installér nu</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="219"/>
        <source>Go &amp;back</source>
        <translation>Gå &amp;tilbage</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="248"/>
        <source>&amp;Done</source>
        <translation>&amp;Færdig</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="249"/>
        <source>The installation is complete. Close the installer.</source>
        <translation>Installationen er fuldført. Luk installationsprogrammet.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="159"/>
        <source>Error</source>
        <translation>Fejl</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
        <source>Installation Failed</source>
        <translation>Installation mislykkedes</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="270"/>
        <source>Unknown exception type</source>
        <translation>Ukendt undtagelsestype</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="284"/>
        <source>unparseable Python error</source>
        <translation>Python-fejl som ikke kan fortolkes</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="324"/>
        <source>unparseable Python traceback</source>
        <translation>Python-traceback som ikke kan fortolkes</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="329"/>
        <source>Unfetchable Python error.</source>
        <translation>Python-fejl som ikke kan hentes.</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>%1-installationsprogram</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="111"/>
        <source>Show debug information</source>
        <translation>Vis fejlretningsinformation</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>Computeren imødekommer ikke minimumsystemkravene for at installere %1.&lt;br/&gt;Installationen kan ikke fortsætte. &lt;a href=&quot;#details&quot;&gt;Detaljer...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>Computeren imødekommer ikke nogle af de anbefalede systemkrav for at installere %1.&lt;br/&gt;Installationen kan fortsætte, men nogle funktionaliteter kan være deaktiveret.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>Programmet vil stille dig nogle spørgsmål og opsætte %2 på din computer.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>For at få det bedste resultat sørg venligst for at computeren:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation>Systemkrav</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="128"/>
        <source>After:</source>
        <translation>Efter:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="235"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;Manuel partitionering&lt;/strong&gt;&lt;br/&gt;Du kan selv oprette og ændre størrelse på partitioner.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="998"/>
        <source>Boot loader location:</source>
        <translation>Placering af bootloader:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="942"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>%1 vil blive skrumpet til %2 MB og en ny %3 MB partition vil blive oprettet for %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="126"/>
        <source>Select storage de&amp;vice:</source>
        <translation>Vælg lageren&amp;hed:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="127"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="924"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="970"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1049"/>
        <source>Current:</source>
        <translation>Nuværende:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="795"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation>Genbrug %1 som hjemmepartition til %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="925"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Vælg en partition der skal mindskes, træk herefter den nederste bjælke for at ændre størrelsen&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1040"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Vælg en partition at installere på&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1096"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>En EFI-partition blev ikke fundet på systemet. Gå venligst tilbage og brug manuel partitionering til at opsætte %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1105"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>EFI-systempartitionen ved %1 vil blive brugt til at starte %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1113"/>
        <source>EFI system partition:</source>
        <translation>EFI-systempartition:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1200"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Lagerenheden ser ikke ud til at indeholde et styresystem. Hvad ønsker du at gøre?&lt;br/&gt;Du vil få mulighed for at se og bekræfte dine valg før der sker ændringer til lagerenheden.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1205"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1242"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1288"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;Slet disk&lt;/strong&gt;&lt;br/&gt;Det vil &lt;font color=&quot;red&quot;&gt;slette&lt;/font&gt; alt data på den valgte lagerenhed.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Lagerenheden har %1 på sig. Hvad ønsker du at gøre?&lt;br/&gt;Du vil få mulighed for at se og bekræfte dine valg før det sker ændringer til lagerenheden.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1209"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1238"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1260"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1284"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;Installér ved siden af&lt;/strong&gt;&lt;br/&gt;Installationsprogrammet vil mindske en partition for at gøre plads til %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1213"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1247"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1268"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1292"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;Erstat en partition&lt;/strong&gt;&lt;br/&gt;Erstatter en partition med %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1255"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Lagerenheden indeholder allerede et styresystem. Hvad ønsker du at gøre?&lt;br/&gt;Du vil få mulighed for at se og bekræfte dine valg før der sker ændringer til lagerenheden.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Lagerenheden indeholder flere styresystemer. Hvad ønsker du at gøre?&lt;br/&gt;Du vil få mulighed for at se og bekræfte dine valg før der sker ændringer til lagerenheden.</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="45"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>Ryd monteringspunkter for partitioneringshandlinger på %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="53"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>Rydder monteringspunkter for partitioneringshandlinger på %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="190"/>
        <source>Cleared all mounts for %1</source>
        <translation>Ryddede alle monteringspunkter til %1</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation>Ryd alle midlertidige monteringspunkter.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation>Rydder alle midlertidige monteringspunkter.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>Kan ikke få liste over midlertidige monteringspunkter.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation>Rydder alle midlertidige monteringspunkter.</translation>
    </message>
</context>
<context>
    <name>CommandList</name>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="113"/>
        <source>Could not run command.</source>
        <translation>Kunne ikke køre kommando.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="114"/>
        <source>No rootMountPoint is defined, so command cannot be run in the target environment.</source>
        <translation>Der er ikke defineret nogen rootMountPoint, så kommandoen kan ikke køre i målmiljøet.</translation>
    </message>
</context>
<context>
    <name>ContextualProcessJob</name>
    <message>
        <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="75"/>
        <source>Contextual Processes Job</source>
        <translation>Kontekstuelt procesjob</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>Opret en partition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>Partitions&amp;type:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>&amp;Primær</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>&amp;Udvidet</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>LVM LV name</source>
        <translation>LVM LV-navn</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
        <source>Flags:</source>
        <translation>Flag:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Monteringspunkt:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>&amp;Størrelse:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="68"/>
        <source>En&amp;crypt</source>
        <translation>Kryp&amp;tér</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="177"/>
        <source>Logical</source>
        <translation>Logisk</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="182"/>
        <source>Primary</source>
        <translation>Primær</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="199"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="288"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>Monteringspunktet er allerede i brug. Vælg venligst et andet.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>Opret en ny %2 MB partition på %4 (%3) med %1-filsystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Opret en ny &lt;strong&gt;%2 MB&lt;/strong&gt; partition på &lt;strong&gt;%4&lt;/strong&gt; (%3) med &lt;strong&gt;%1&lt;/strong&gt;-filsystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>Opretter ny %1-partition på %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>Installationsprogrammet kunne ikke oprette partition på disk &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>Opret partitionstabel</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>Oprettelse af en ny partitionstabel vil slette alle data på disken.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>Hvilken slags partitionstabel vil du oprette?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>GUID-partitiontabel (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="45"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>Opret en ny %1-partitionstabel på %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="52"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Opret en ny &lt;strong&gt;%1&lt;/strong&gt;-partitionstabel på &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="62"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>Opretter ny %1-partitionstabel på %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="72"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>Installationsprogrammet kunne ikke oprette en partitionstabel på %1.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
        <source>Create user %1</source>
        <translation>Opret bruger %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="57"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Opret bruger &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="64"/>
        <source>Creating user %1.</source>
        <translation>Opretter bruger %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="80"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Sudoers mappe er skrivebeskyttet.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="84"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>Kan ikke oprette sudoers fil til skrivning.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="92"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>Kan ikke chmod sudoers fil.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
        <source>Cannot open groups file for reading.</source>
        <translation>Kan ikke åbne gruppernes fil til læsning.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
        <source>Cannot create user %1.</source>
        <translation>Kan ikke oprette bruger %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="161"/>
        <source>useradd terminated with error code %1.</source>
        <translation>useradd stoppet med fejlkode %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="170"/>
        <source>Cannot add user %1 to groups: %2.</source>
        <translation>Kan ikke tilføje bruger %1 til grupperne: %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="173"/>
        <source>usermod terminated with error code %1.</source>
        <translation>usermod stoppet med fejlkode %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="183"/>
        <source>Cannot set home directory ownership for user %1.</source>
        <translation>Kan ikke sætte hjemmemappens ejerskab for bruger %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="185"/>
        <source>chown terminated with error code %1.</source>
        <translation>chown stoppet med fejlkode %1.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
        <source>Delete partition %1.</source>
        <translation>Slet partition %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Slet partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
        <source>Deleting partition %1.</source>
        <translation>Sletter partition %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>Installationsprogrammet kunne ikke slette partition %1.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>Typen af &lt;strong&gt;partitionstabel&lt;/strong&gt; på den valgte lagerenhed.&lt;br&gt;&lt;br&gt;Den eneste måde at ændre partitionstabeltypen, er at slette og oprette partitionstabellen igen, hvilket vil destruere al data på lagerenheden.&lt;br&gt;Installationsprogrammet vil beholde den nuværende partitionstabel medmindre du specifikt vælger andet.&lt;br&gt;Hvis usikker, er GPT foretrukket på moderne systemer.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>Enheden har en &lt;strong&gt;%1&lt;/strong&gt; partitionstabel.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation>Dette er en &lt;strong&gt;loop&lt;/strong&gt;-enhed.&lt;br&gt;&lt;br&gt;Det er en pseudo-enhed uden en partitionstabel, der gør en fil tilgængelig som en blokenhed. Denne slags opsætning indeholder typisk kun et enkelt filsystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>Installationsprogrammet &lt;strong&gt;kan ikke finde en partitionstabel&lt;/strong&gt; på den valgte lagerenhed.&lt;br&gt;&lt;br&gt;Enten har enheden ikke nogen partitionstabel, eller partitionstabellen er ødelagt eller også er den af en ukendt type.&lt;br&gt;Installationsprogrammet kan oprette en ny partitionstabel for dig, enten automatisk, eller igennem den manuelle partitioneringsside.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;Dette er den anbefalede partitionstabeltype til moderne systemer som starter fra et &lt;strong&gt;EFI&lt;/strong&gt;-bootmiljø.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation>&lt;br&gt;&lt;br&gt;Partitionstabeltypen anbefales kun på ældre systemer der starter fra et &lt;strong&gt;BIOS&lt;/strong&gt;-bootmiljø. GPT anbefales i de fleste tilfælde.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Advarsel:&lt;/strong&gt; MBR-partitionstabeltypen er en forældet MS-DOS-æra standard.&lt;br&gt;Kun 4 &lt;em&gt;primære&lt;/em&gt; partitioner var tilladt, og ud af de fire kan én af dem være en &lt;em&gt;udvidet&lt;/em&gt; partition, som igen må indeholde mange &lt;em&gt;logiske&lt;/em&gt; partitioner.</translation>
    </message>
</context>
<context>
    <name>DeviceModel</name>
    <message>
        <location filename="../src/modules/partition/core/DeviceModel.cpp" line="80"/>
        <source>%1 - %2 (%3)</source>
        <translation>%1 - %2 (%3)</translation>
    </message>
</context>
<context>
    <name>DracutLuksCfgJob</name>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="131"/>
        <source>Write LUKS configuration for Dracut to %1</source>
        <translation>Skriv LUKS-konfiguration for Dracut til %1</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="133"/>
        <source>Skip writing LUKS configuration for Dracut: &quot;/&quot; partition is not encrypted</source>
        <translation>Spring skrivning af LUKS-konfiguration over for Dracut: &quot;/&quot;-partitionen er ikke krypteret</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="149"/>
        <source>Failed to open %1</source>
        <translation>Kunne ikke åbne %1</translation>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
        <source>Dummy C++ Job</source>
        <translation>Dummy C++-job</translation>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>Redigér eksisterende partition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>Indhold:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>&amp;Behold</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>Formatér</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>Advarsel: Formatering af partitionen vil slette alle eksisterende data.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Monteringspunkt:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>Stø&amp;rrelse:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation>Fi&amp;lsystem:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation>Flag:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="307"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>Monteringspunktet er allerede i brug. Vælg venligst et andet.</translation>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation>Kryp&amp;tér system</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation>Adgangskode</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation>Bekræft adgangskode</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation>Indtast venligst samme adgangskode i begge bokse.</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="123"/>
        <source>Set partition information</source>
        <translation>Sæt partitionsinformation</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="147"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>Installér %1 på &lt;strong&gt;ny&lt;/strong&gt; %2-systempartition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="151"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Opsæt den &lt;strong&gt;nye&lt;/strong&gt; %2 partition med monteringspunkt &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="159"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Installér %2 på %3-systempartition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="164"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Opsæt %3 partition &lt;strong&gt;%1&lt;/strong&gt; med monteringspunkt &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="176"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Installér bootloader på &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="186"/>
        <source>Setting up mount points.</source>
        <translation>Opsætter monteringspunkter.</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style=&quot; font-style:italic;&quot;&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Når boksen er tilvalgt, vil dit system genstarte med det samme når du klikker på &lt;span style=&quot; font-style:italic;&quot;&gt;Færdig&lt;/span&gt; eller lukker installationsprogrammet.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
        <source>&amp;Restart now</source>
        <translation>&amp;Genstart nu</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="52"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;Færdig.&lt;/h1&gt;&lt;br/&gt;%1 er blevet installeret på din computer.&lt;br/&gt;Du kan nu genstarte for at komme ind i dit nye system eller fortsætte med at bruge %2 live-miljøet.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="110"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation>&lt;h1&gt;Installation mislykkede&lt;/h1&gt;&lt;br/&gt;%1 er ikke blevet installeret på din computer.&lt;br/&gt;Fejlmeddelelsen var: %2.</translation>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation>Færdig</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation>Installation fuldført</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation>Installationen af %1 er fuldført.</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>Formatér partition %1 (filsystem: %2, størrelse: %3 MB) på %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Formatér &lt;strong&gt;%3 MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; med &lt;strong&gt;%2&lt;/strong&gt;-filsystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>Formatterer partition %1 med %2-filsystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>Installationsprogrammet kunne ikke formatere partition %1 på disk &apos;%2&apos;.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
        <source>Konsole not installed</source>
        <translation>Konsole er ikke installeret</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
        <source>Please install KDE Konsole and try again!</source>
        <translation>Installér venligst KDE Konsole og prøv igen!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>Eksekverer skript: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>Skript</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="220"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>Sæt tastaturmodel til %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="222"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>Sæt tastaturlayout til %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>Tastatur</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>Systemets lokalitetsindstilling</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Systemets lokalitetsindstilling har indflydelse på sproget og tegnsættet for nogle kommandolinje-brugerelementer.&lt;br/&gt;Den nuværende indstilling er &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Annullér</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="67"/>
        <source>&amp;OK</source>
        <translation>&amp;OK</translation>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="88"/>
        <source>I accept the terms and conditions above.</source>
        <translation>Jeg accepterer de ovenstående vilkår og betingelser.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="115"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;Licensaftale&lt;/h1&gt;Opsætningsproceduren installerer proprietær software der er underlagt licenseringsvilkår.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="118"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>Gennemgå venligst slutbrugerlicensaftalerne (EULA&apos;er) ovenfor.&lt;br/&gt;Hvis du ikke er enig med disse vilkår, kan opsætningsproceduren ikke fortsætte.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="124"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;Licensaftale&lt;/h1&gt;Opsætningsproceduren kan installere proprietær software der er underlagt licenseringsvilkår, for at kunne tilbyde yderligere funktionaliteter og forbedre brugeroplevelsen.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="129"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>Gennemgå venligst slutbrugerlicensaftalerne (EULA&apos;er) ovenfor.&lt;br/&gt;Hvis du ikke er enig med disse vilkår vil der ikke blive installeret proprietær software, og open source-alternativer vil blive brugt i stedet.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;af %2</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="166"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;%1 grafikdriver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;af %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="172"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 browser-plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;af %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="178"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;af %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="184"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 pakke&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;af %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="190"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;af %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="202"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;vis licensaftalen&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>Licens</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation>Systemsproget vil blive sat til %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation>Lokalitet for tal og datoer vil blive sat til %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation>Region:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation>Zone:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>&amp;Skift...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>Sæt tidszone til %1/%2.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="480"/>
        <source>%1 (%2)</source>
        <extracomment>Language (Country)</extracomment>
        <translation>%1 (%2)</translation>
    </message>
</context>
<context>
    <name>LocaleViewStep</name>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="52"/>
        <source>Loading location data...</source>
        <translation>Indlæser placeringsdata...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="169"/>
        <source>Location</source>
        <translation>Placering</translation>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="72"/>
        <source>Name</source>
        <translation>Navn</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="73"/>
        <source>Description</source>
        <translation>Beskrivelse</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="94"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation>Netværksinstallation. (Deaktiveret: Kunne ikke hente pakkelister, tjek din netværksforbindelse)</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="104"/>
        <source>Network Installation. (Disabled: Received invalid groups data)</source>
        <translation>Netværksinstallation. (Deaktiveret: Modtog ugyldige gruppers data)</translation>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
        <source>Package selection</source>
        <translation>Valg af pakke</translation>
    </message>
</context>
<context>
    <name>PWQ</name>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
        <source>Password is too short</source>
        <translation>Adgangskoden er for kort</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="89"/>
        <source>Password is too long</source>
        <translation>Adgangskoden er for lang</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="155"/>
        <source>Password is too weak</source>
        <translation>Adgangskoden er for svag</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
        <source>Memory allocation error when setting &apos;%1&apos;</source>
        <translation>Fejl ved allokering af hukommelse ved sættelse af &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
        <source>Memory allocation error</source>
        <translation>Fejl ved allokering af hukommelse</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
        <source>The password is the same as the old one</source>
        <translation>Adgangskoden er den samme som den gamle</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
        <source>The password is a palindrome</source>
        <translation>Adgangskoden er et palindrom</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
        <source>The password differs with case changes only</source>
        <translation>Adgangskoden har kun ændringer i store/små bogstaver</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
        <source>The password is too similar to the old one</source>
        <translation>Adgangskoden minder for meget om den gamle</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="176"/>
        <source>The password contains the user name in some form</source>
        <translation>Adgangskoden indeholder i nogen form brugernavnet</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="178"/>
        <source>The password contains words from the real name of the user in some form</source>
        <translation>Adgangskoden indeholder i nogen form ord fra brugerens rigtige navn</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="180"/>
        <source>The password contains forbidden words in some form</source>
        <translation>Adgangskoden indeholder i nogen form forbudte ord</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="183"/>
        <source>The password contains less than %1 digits</source>
        <translation>Adgangskoden indeholder færre end %1 cifre</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
        <source>The password contains too few digits</source>
        <translation>Adgangskoden indeholder for få cifre</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="187"/>
        <source>The password contains less than %1 uppercase letters</source>
        <translation>Adgangskoden indeholder færre end %1 bogstaver med stort</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
        <source>The password contains too few uppercase letters</source>
        <translation>Adgangskoden indeholder for få bogstaver med stort</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
        <source>The password contains less than %1 lowercase letters</source>
        <translation>Adgangskoden indeholder færre end %1 bogstaver med småt</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="192"/>
        <source>The password contains too few lowercase letters</source>
        <translation>Adgangskoden indeholder for få bogstaver med småt</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
        <source>The password contains less than %1 non-alphanumeric characters</source>
        <translation>Adgangskoden indeholder færre end %1 ikke-alfanumeriske tegn</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
        <source>The password contains too few non-alphanumeric characters</source>
        <translation>Adgangskoden indeholder for få ikke-alfanumeriske tegn</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
        <source>The password is shorter than %1 characters</source>
        <translation>Adgangskoden er kortere end %1 tegn</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="200"/>
        <source>The password is too short</source>
        <translation>Adgangskoden er for kort</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
        <source>The password is just rotated old one</source>
        <translation>Adgangskoden er blot det gamle hvor der er byttet om på tegnene</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
        <source>The password contains less than %1 character classes</source>
        <translation>Adgangskoden indeholder færre end %1 tegnklasser</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
        <source>The password does not contain enough character classes</source>
        <translation>Adgangskoden indeholder ikke nok tegnklasser</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
        <source>The password contains more than %1 same characters consecutively</source>
        <translation>Adgangskoden indeholder flere end %1 af de samme tegn i træk</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
        <source>The password contains too many same characters consecutively</source>
        <translation>Adgangskoden indeholder for mange af de samme tegn i træk</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
        <source>The password contains more than %1 characters of the same class consecutively</source>
        <translation>Adgangskoden indeholder flere end %1 tegn af den samme klasse i træk</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
        <source>The password contains too many characters of the same class consecutively</source>
        <translation>Adgangskoden indeholder for mange tegn af den samme klasse i træk</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="217"/>
        <source>The password contains monotonic sequence longer than %1 characters</source>
        <translation>Adgangskoden indeholder monoton sekvens som er længere end %1 tegn</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
        <source>The password contains too long of a monotonic character sequence</source>
        <translation>Adgangskoden indeholder en monoton tegnsekvens som er for lang</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="220"/>
        <source>No password supplied</source>
        <translation>Der er ikke angivet nogen adgangskode</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
        <source>Cannot obtain random numbers from the RNG device</source>
        <translation>Kan ikke få tilfældige tal fra RNG-enhed</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="224"/>
        <source>Password generation failed - required entropy too low for settings</source>
        <translation>Generering af adgangskode mislykkedes - krævede entropi er for lav til indstillinger</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="229"/>
        <source>The password fails the dictionary check - %1</source>
        <translation>Adgangskoden bestod ikke ordbogstjekket - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="231"/>
        <source>The password fails the dictionary check</source>
        <translation>Adgangskoden bestod ikke ordbogstjekket</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
        <source>Unknown setting - %1</source>
        <translation>Ukendt indstilling - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
        <source>Unknown setting</source>
        <translation>Ukendt indstilling</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
        <source>Bad integer value of setting - %1</source>
        <translation>Ugyldig heltalsværdi til indstilling - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
        <source>Bad integer value</source>
        <translation>Ugyldig heltalsværdi</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
        <source>Setting %1 is not of integer type</source>
        <translation>Indstillingen %1 er ikke en helttalsstype</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
        <source>Setting is not of integer type</source>
        <translation>Indstillingen er ikke en helttalsstype</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
        <source>Setting %1 is not of string type</source>
        <translation>Indstillingen %1 er ikke en strengtype</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
        <source>Setting is not of string type</source>
        <translation>Indstillingen er ikke en strengtype</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
        <source>Opening the configuration file failed</source>
        <translation>Åbningen af konfigurationsfilen mislykkedes</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
        <source>The configuration file is malformed</source>
        <translation>Konfigurationsfilen er forkert udformet</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
        <source>Fatal failure</source>
        <translation>Fatal fejl</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
        <source>Unknown error</source>
        <translation>Ukendt fejl</translation>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>Tastaturmodel:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>Skriv her for at teste dit tastatur</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>Hvad er dit navn?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>Hvilket navn skal bruges til at logge ind?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>font-weight: normal</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Hvis mere end én person bruger computeren, kan du opsætte flere konti efter installationen.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>Vælg en adgangskode for at beskytte din konto.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Skriv den samme adgangskode to gange, så det kan blive tjekket for skrivefejl. En god adgangskode indeholder en blanding af bogstaver, tal og specialtegn, og bør være mindst 8 tegn langt og bør skiftes jævnligt.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>Hvad er navnet på computeren?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Navnet bruges, hvis du gør computeren synlig for andre på et netværk.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>Log ind automatisk uden at spørge efter adgangskoden.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>Brug den samme adgangskode til administratorkontoen.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>Vælg en adgangskode til administratorkontoen.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Skriv den samme adgangskode to gange, så det kan blive tjekket for skrivefejl.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation>Rod</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation>Hjem</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation>Boot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation>EFI-system</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation>Swap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation>Ny partition til %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation>Ny partition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="224"/>
        <source>%1  %2</source>
        <translation>%1  %2</translation>
    </message>
</context>
<context>
    <name>PartitionModel</name>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="137"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="169"/>
        <source>Free Space</source>
        <translation>Ledig plads</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="141"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="173"/>
        <source>New partition</source>
        <translation>Ny partition</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="257"/>
        <source>Name</source>
        <translation>Navn</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="259"/>
        <source>File System</source>
        <translation>Filsystem</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="261"/>
        <source>Mount Point</source>
        <translation>Monteringspunkt</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="263"/>
        <source>Size</source>
        <translation>Størrelse</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>Lageren&amp;hed:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>&amp;Tilbagefør alle ændringer</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>Ny partitions&amp;tabel</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>&amp;Create</source>
        <translation>&amp;Opret</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>&amp;Redigér</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>&amp;Slet</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="148"/>
        <source>Install boot &amp;loader on:</source>
        <translation>Installér boot&amp;loader på:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="168"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>Er du sikker på, at du vil oprette en ny partitionstabel på %1?</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="70"/>
        <source>Gathering system information...</source>
        <translation>Indsamler systeminformation...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="121"/>
        <source>Partitions</source>
        <translation>Partitioner</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="158"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>Installér %1 &lt;strong&gt;ved siden af&lt;/strong&gt; et andet styresystem.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="162"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>&lt;strong&gt;Slet&lt;/strong&gt; disk og installér %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="166"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>&lt;strong&gt;Erstat&lt;/strong&gt; en partition med %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>&lt;strong&gt;Manuel&lt;/strong&gt; partitionering.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="184"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Installér %1 &lt;strong&gt;ved siden af&lt;/strong&gt; et andet styresystem på disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="190"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation>&lt;strong&gt;Slet&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) og installér %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="196"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>&lt;strong&gt;Erstat&lt;/strong&gt; en partition på disk &lt;strong&gt;%2&lt;/strong&gt; (%3) med %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="203"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation>&lt;strong&gt;Manuel&lt;/strong&gt; partitionering på disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="211"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="239"/>
        <source>Current:</source>
        <translation>Nuværende:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="256"/>
        <source>After:</source>
        <translation>Efter:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="399"/>
        <source>No EFI system partition configured</source>
        <translation>Ingen EFI-systempartition konfigureret</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation>En EFI-systempartition er nødvendig for at starte %1.&lt;br/&gt;&lt;br/&gt;For at konfigurere en EFI-systempartition skal du gå tilbage og vælge eller oprette et FAT32-filsystem med &lt;strong&gt;esp&lt;/strong&gt;-flaget aktiveret og monteringspunkt &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Du kan fortsætte uden at opsætte en EFI-systempartition, men dit system vil muligvis ikke kunne starte.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="413"/>
        <source>EFI system partition flag not set</source>
        <translation>EFI-systempartitionsflag ikke sat</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation>En EFI-systempartition er nødvendig for at starte %1.&lt;br/&gt;&lt;br/&gt;En partition var konfigureret med monteringspunkt &lt;strong&gt;%2&lt;/strong&gt;, men dens &lt;strong&gt;esp&lt;/strong&gt;-flag var ikke sat.&lt;br/&gt;For at sætte flaget skal du gå tilbage og redigere partitionen.&lt;br/&gt;&lt;br/&gt;Du kan fortsætte uden at konfigurere flaget, men dit system vil muligvis ikke kunne starte.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="448"/>
        <source>Boot partition not encrypted</source>
        <translation>Bootpartition ikke krypteret</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="449"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation>En separat bootpartition blev opsat sammen med en krypteret rodpartition, men bootpartitionen er ikke krypteret.&lt;br/&gt;&lt;br/&gt;Der er sikkerhedsmæssige bekymringer med denne slags opsætning, da vigtige systemfiler er gemt på en ikke-krypteret partition.&lt;br/&gt;Du kan fortsætte hvis du vil, men oplåsning af filsystemet sker senere under systemets opstart.&lt;br/&gt;For at kryptere bootpartitionen skal du gå tilbage og oprette den igen, vælge &lt;strong&gt;Kryptér&lt;/strong&gt; i partitionsoprettelsesvinduet.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfJob</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
        <source>Plasma Look-and-Feel Job</source>
        <translation>Plasma udseende og fremtoning-job</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
        <source>Could not select KDE Plasma Look-and-Feel package</source>
        <translation>Kunne ikke vælge KDE Plasma udseende og fremtoning-pakke</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfPage</name>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="20"/>
        <source>Placeholder</source>
        <translation>Pladsholder</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="64"/>
        <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed.</source>
        <translation>Vælg venligst et udseende og fremtoning til KDE Plasma-skrivebordet. Du kan også springe trinnet over og konfigurere udseendet og fremtoningen når systemet er installeret.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfViewStep</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="51"/>
        <source>Look-and-Feel</source>
        <translation>Udseende og fremtoning</translation>
    </message>
</context>
<context>
    <name>ProcessResult</name>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="263"/>
        <source>
There was no output from the command.</source>
        <translation>
Der var ikke nogen output fra kommandoen.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="264"/>
        <source>
Output:
</source>
        <translation>
Output:
</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="267"/>
        <source>External command crashed.</source>
        <translation>Ekstern kommando holdt op med at virke.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="268"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
        <translation>Kommandoen &lt;i&gt;%1&lt;/i&gt; holdte op med at virke.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="273"/>
        <source>External command failed to start.</source>
        <translation>Ekstern kommando kunne ikke starte.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="274"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
        <translation>Kommandoen &lt;i&gt;%1&lt;/i&gt; kunne ikke starte.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="278"/>
        <source>Internal error when starting command.</source>
        <translation>Intern fejl ved start af kommando.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="279"/>
        <source>Bad parameters for process job call.</source>
        <translation>Ugyldige parametre til kald af procesjob.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="282"/>
        <source>External command failed to finish.</source>
        <translation>Ekstern kommando blev ikke færdig.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="283"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
        <translation>Kommandoen &lt;i&gt;%1&lt;/i&gt; blev ikke færdig på %2 sekunder.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="289"/>
        <source>External command finished with errors.</source>
        <translation>Ekstern kommando blev færdig med fejl.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="290"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
        <translation>Kommandoen &lt;i&gt;%1&lt;/i&gt; blev færdig med afslutningskoden %2.</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>Standardtastaturmodel</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>Standard</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="204"/>
        <source>unknown</source>
        <translation>ukendt</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="206"/>
        <source>extended</source>
        <translation>udvidet</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="208"/>
        <source>unformatted</source>
        <translation>uformatteret</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="210"/>
        <source>swap</source>
        <translation>swap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>Upartitioneret plads eller ukendt partitionstabel</translation>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation>Vælg hvor %1 skal installeres.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Advarsel: &lt;/font&gt;Det vil slette alle filer på den valgte partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>Det valgte emne ser ikke ud til at være en gyldig partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1 kan ikke installeres på tom plads. Vælg venligst en eksisterende partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1 kan ikke installeres på en udvidet partition. Vælg venligst en eksisterende primær eller logisk partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>%1 kan ikke installeres på denne partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation>Datapartition (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation>Ukendt systempartition (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation>%1-systempartition (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Partitionen %1 er for lille til %2. Vælg venligst en partition med mindst %3 GiB plads.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;En EFI-systempartition kunne ikke findes på systemet. Gå venligst tilbage og brug manuel partitionering til at opsætte %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 vil blive installeret på %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Advarsel: &lt;/font&gt;Al data på partition %2 vil gå tabt.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>EFI-systempartitionen ved %1 vil blive brugt til at starte %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation>EFI-systempartition:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="68"/>
        <source>Gathering system information...</source>
        <translation>Indsamler systeminformation...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="116"/>
        <source>has at least %1 GB available drive space</source>
        <translation>har mindst %1 GB ledig plads på drevet</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>Der er ikke nok ledig plads på drevet. Mindst %1 GB er påkrævet.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="126"/>
        <source>has at least %1 GB working memory</source>
        <translation>har mindst %1 GB arbejdshukommelse</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="128"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>Systemet har ikke nok arbejdshukommelse. Mindst %1 GB er påkrævet.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="136"/>
        <source>is plugged in to a power source</source>
        <translation>er tilsluttet en strømkilde</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="137"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>Systemet er ikke tilsluttet en strømkilde.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="144"/>
        <source>is connected to the Internet</source>
        <translation>er forbundet til internettet</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="145"/>
        <source>The system is not connected to the Internet.</source>
        <translation>Systemet er ikke forbundet til internettet.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="153"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>Installationsprogrammet kører ikke med administratorrettigheder.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="161"/>
        <source>The screen is too small to display the installer.</source>
        <translation>Skærmen er for lille til at vise installationsprogrammet.</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
        <source>Resize partition %1.</source>
        <translation>Ændr størrelse på partition %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation>Ændr størrelse af &lt;strong&gt;%2 MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; til &lt;strong&gt;%3 MB&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation>Ændrer nu størrelsen af %2 MB partition %1 til %3 MB.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>Installationsprogrammet kunne ikke ændre størrelse på partition %1 på disk &apos;%2&apos;.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation>Skanner lagerenheder...</translation>
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
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
        <source>Set hostname %1</source>
        <translation>Sæt værtsnavn %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sæt værtsnavn &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
        <source>Setting hostname %1.</source>
        <translation>Sætter værtsnavn %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="61"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="68"/>
        <source>Internal Error</source>
        <translation>Intern fejl</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="75"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="86"/>
        <source>Cannot write hostname to target system</source>
        <translation>Kan ikke skrive værtsnavn til destinationssystem</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>Sæt tastaturmodel til %1, layout til %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="318"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>Kunne ikke skrive tastaturkonfiguration for den virtuelle konsol.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="319"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="323"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="329"/>
        <source>Failed to write to %1</source>
        <translation>Kunne ikke skrive til %1</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>Kunne ikke skrive tastaturkonfiguration for X11.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="328"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation>Kunne ikke skrive tastaturkonfiguration til eksisterende /etc/default-mappe.</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
        <source>Set flags on partition %1.</source>
        <translation>Sæt flag på partition %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation>Sæt flag på %1 MB %2 partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Set flags on new partition.</source>
        <translation>Sæt flag på ny partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Ryd flag på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Ryd flag på %1 MB &lt;strong&gt;%2&lt;/strong&gt; partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
        <source>Clear flags on new partition.</source>
        <translation>Ryd flag på ny partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Flag partition &lt;strong&gt;%1&lt;/strong&gt; som &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="85"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation>Flag %1 MB &lt;strong&gt;%2&lt;/strong&gt; partition som &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Flag ny partition som &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Rydder flag på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Rydder flag på %1 MB &lt;strong&gt;%2&lt;/strong&gt; partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
        <source>Clearing flags on new partition.</source>
        <translation>Rydder flag på ny partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sætter flag &lt;strong&gt;%2&lt;/strong&gt; på partition &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Sætter flag &lt;strong&gt;%3&lt;/strong&gt; på %1 MB &lt;strong&gt;%2&lt;/strong&gt; partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation>Sætter flag &lt;strong&gt;%1&lt;/strong&gt; på ny partition.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>Installationsprogrammet kunne ikke sætte flag på partition %1.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation>Sæt adgangskode for bruger %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation>Sætter adgangskode for bruger %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation>Ugyldig destinationssystemsti.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation>rodMonteringsPunkt er %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="123"/>
        <source>Cannot disable root account.</source>
        <translation>Kan ikke deaktivere root-konto.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="124"/>
        <source>passwd terminated with error code %1.</source>
        <translation>passwd stoppet med fejlkode %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="139"/>
        <source>Cannot set password for user %1.</source>
        <translation>Kan ikke sætte adgangskode for bruger %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation>usermod stoppet med fejlkode %1.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>Sæt tidszone til %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>Kan ikke tilgå den valgte tidszonesti.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>Ugyldig sti: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>Kan ikke sætte tidszone.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>Oprettelse af link mislykkedes, destination: %1; linknavn: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation>Kan ikke sætte tidszone,</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>Kan ikke åbne /etc/timezone til skrivning</translation>
    </message>
</context>
<context>
    <name>ShellProcessJob</name>
    <message>
        <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="51"/>
        <source>Shell Processes Job</source>
        <translation>Skal-procesjob</translation>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/modules/summary/SummaryPage.cpp" line="49"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation>Dette er et overblik over hvad der vil ske når du starter installationsprocessen.</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>Opsummering</translation>
    </message>
</context>
<context>
    <name>TrackingInstallJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
        <source>Installation feedback</source>
        <translation>Installationsfeedback</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="53"/>
        <source>Sending installation feedback.</source>
        <translation>Sender installationsfeedback</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="88"/>
        <source>Internal error in install-tracking.</source>
        <translation>Intern fejl i installationssporing.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="89"/>
        <source>HTTP request timed out.</source>
        <translation>HTTP-anmodning fik timeout.</translation>
    </message>
</context>
<context>
    <name>TrackingMachineNeonJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="104"/>
        <source>Machine feedback</source>
        <translation>Maskinfeedback</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="114"/>
        <source>Configuring machine feedback.</source>
        <translation>Konfigurer maskinfeedback.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="133"/>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
        <source>Error in machine feedback configuration.</source>
        <translation>Fejl i maskinfeedback-konfiguration.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="134"/>
        <source>Could not configure machine feedback correctly, script error %1.</source>
        <translation>Kunne ikke konfigurere maskinfeedback korrekt, script-fejl %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="137"/>
        <source>Could not configure machine feedback correctly, Calamares error %1.</source>
        <translation>Kunne ikke konfigurere maskinfeedback korrekt, Calamares-fejl %1.</translation>
    </message>
</context>
<context>
    <name>TrackingPage</name>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
        <source>Placeholder</source>
        <translation>Pladsholder</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=&quot; font-weight:600;&quot;&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Vælges dette sender du &lt;span style=&quot; font-weight:600;&quot;&gt;slet ikke nogen information&lt;/span&gt; om din installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="123"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="185"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="247"/>
        <source>TextLabel</source>
        <translation>Tekstetiket</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="133"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="195"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="257"/>
        <source>...</source>
        <translation>...</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;placeholder&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#2980b9;&quot;&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;placeholder&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#2980b9;&quot;&gt;Klik her for mere information om brugerfeedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
        <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
        <translation>Installationssporing hjælper %1 til at se hvor mange brugere de har, hvilket hardware de installere %1 på og (med de sidste to valgmuligheder nedenfor), hente information om fortrukne programmer løbende. Klik venligst på hjælp-ikonet ved siden af hvert område, for at se hvad der vil blive sendt.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="45"/>
        <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
        <translation>Vælges dette sender du information om din installation og hardware. Informationen vil &lt;b&gt;første blive sendt&lt;/b&gt; efter installationen er færdig.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="46"/>
        <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
        <translation>Vælges dette sender du &lt;b&gt;periodisk&lt;/b&gt; information om din installation, hardware og programmer, til %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="47"/>
        <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
        <translation>Vælges dette sender du &lt;b&gt;regelmæssigt&lt;/b&gt; information om din installation, hardware, programmer og anvendelsesmønstre, til %1.</translation>
    </message>
</context>
<context>
    <name>TrackingViewStep</name>
    <message>
        <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="59"/>
        <source>Feedback</source>
        <translation>Feedback</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="289"/>
        <source>Your username is too long.</source>
        <translation>Dit brugernavn er for langt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="295"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>Dit brugernavn indeholder ugyldige tegn. Kun små bogstaver og tal er tilladt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too short.</source>
        <translation>Dit værtsnavn er for kort.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="339"/>
        <source>Your hostname is too long.</source>
        <translation>Dit værtsnavn er for langt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="345"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>Dit værtsnavn indeholder ugyldige tegn. Kun bogstaver, tal og tankestreger er tilladt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="373"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="417"/>
        <source>Your passwords do not match!</source>
        <translation>Dine adgangskoder er ikke ens!</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="51"/>
        <source>Users</source>
        <translation>Brugere</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation>Formular</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>&amp;Sprog:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>&amp;Udgivelsesnoter</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>&amp;Kendte problemer</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>&amp;Support</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>&amp;Om</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Velkommen til %1-installationsprogrammet.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Velkommen til Calamares-installationsprogrammet for %1.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation>Om %1-installationsprogrammet</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;til %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Ophavsret 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Ophavsret 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Tak til: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg og &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares oversætterteam&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; udvikling er sponsoreret af &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="201"/>
        <source>%1 support</source>
        <translation>%1 support</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="51"/>
        <source>Welcome</source>
        <translation>Velkommen</translation>
    </message>
</context>
</TS>
<?xml version="1.0" ?><!DOCTYPE TS><TS language="fi_FI" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>%1:n MBR</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>Käynnistysosio</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>Järjestelmäosio</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="125"/>
        <source>%1 (%2)</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>Calamares::DebugWindow</name>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="77"/>
        <source>Install</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="89"/>
        <source>Done</source>
        <translation>Valmis</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="51"/>
        <source>Run command %1 %2</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="60"/>
        <source>Running command %1 %2</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="89"/>
        <source>External command crashed</source>
        <translation>Ulkoinen komento kaatui</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="90"/>
        <source>Command %1 crashed.
Output:
%2</source>
        <translation>Komento %1 kaatui.
Tuloste:
%2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="95"/>
        <source>External command failed to start</source>
        <translation>Ulkoisen komennon käynnistys epäonnistui</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="96"/>
        <source>Command %1 failed to start.</source>
        <translation>Komennon %1 käynnistys epäonnistui.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="100"/>
        <source>Internal error when starting command</source>
        <translation>Sisäinen virhe suoritettaessa komentoa</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="101"/>
        <source>Bad parameters for process job call.</source>
        <translation>Huonot parametrit prosessin kutsuun.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="104"/>
        <source>External command failed to finish</source>
        <translation>Ulkoista komentoa ei voitu ajaa loppuun</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="105"/>
        <source>Command %1 failed to finish in %2s.
Output:
%3</source>
        <translation>Komento %1 epäonnistui ajassa %2s.
Tuloste:
%3</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="111"/>
        <source>External command finished with errors</source>
        <translation>Ulkoinen komento päättyi virheeseen</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="112"/>
        <source>Command %1 finished with exit code %2.
Output:
%3</source>
        <translation>Komennon %1 suoritus loppui koodilla %2.
Tuloste:
%3</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="265"/>
        <source>Running %1 operation.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="280"/>
        <source>Bad working directory path</source>
        <translation>Epäkelpo työskentelyhakemiston polku</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="281"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>Työkansio %1 pythonin työlle %2 ei ole luettavissa.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="291"/>
        <source>Bad main script file</source>
        <translation>Huono pää-skripti tiedosto</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="292"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>Pääskriptitiedosto %1 pythonin työlle %2 ei ole luettavissa.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="368"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>Boost.Python virhe työlle &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="73"/>
        <source>&amp;Back</source>
        <translation>&amp;Takaisin</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Next</source>
        <translation>&amp;Seuraava</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="300"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Peruuta</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="301"/>
        <source>Cancel installation without changing the system.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="99"/>
        <source>Cancel installation?</source>
        <translation>Peruuta asennus?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="100"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>Oletko varma että haluat peruuttaa käynnissä olevan asennusprosessin? 
Asennusohjelma sulkeutuu ja kaikki muutoksesi katoavat.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="105"/>
        <source>&amp;Yes</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="106"/>
        <source>&amp;No</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="183"/>
        <source>&amp;Close</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="233"/>
        <source>Continue with setup?</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="234"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="239"/>
        <source>&amp;Install now</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="240"/>
        <source>Go &amp;back</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="269"/>
        <source>&amp;Done</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="270"/>
        <source>The installation is complete. Close the installer.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="180"/>
        <source>Error</source>
        <translation>Virhe</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="181"/>
        <source>Installation Failed</source>
        <translation>Asennus Epäonnistui</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="263"/>
        <source>Unknown exception type</source>
        <translation>Tuntematon poikkeustyyppi</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="276"/>
        <source>unparseable Python error</source>
        <translation>jäsentämätön Python virhe</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="292"/>
        <source>unparseable Python traceback</source>
        <translation>jäsentämätön Python jäljitys</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="296"/>
        <source>Unfetchable Python error.</source>
        <translation>Python virhettä ei voitu hakea.</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="45"/>
        <source>%1 Installer</source>
        <translation>%1 Asennusohjelma</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="112"/>
        <source>Show debug information</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>CheckFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="39"/>
        <source>Checking file system on partition %1.</source>
        <translation>Tarkistetaan tiedostojärjestelmän osiota %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="77"/>
        <source>The file system check on partition %1 failed.</source>
        <translation>Tiedostojärjestelmän tarkistus osiolla %1 epäonnistui.</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="128"/>
        <source>After:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="235"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="978"/>
        <source>Boot loader location:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="922"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="126"/>
        <source>Select storage de&amp;vice:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="127"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="904"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="950"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1029"/>
        <source>Current:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="775"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="905"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1020"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1076"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1085"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1093"/>
        <source>EFI system partition:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1177"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1182"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1219"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1241"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1265"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1209"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1186"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1215"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1237"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1261"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1190"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1224"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1245"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1269"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1256"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="45"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>Poista osiointitoimenpiteitä varten tehdyt liitokset kohteesta %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="53"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="190"/>
        <source>Cleared all mounts for %1</source>
        <translation>Kaikki liitokset poistettu kohteesta %1</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation>Poista kaikki väliaikaiset liitokset.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation>Poistettu kaikki väliaikaiset liitokset.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>Luo levyosio</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>Osion &amp;Tyyppi:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>&amp;Ensisijainen</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>&amp;Laajennettu</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="178"/>
        <source>Flags:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Liitoskohta:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>K&amp;oko:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
        <source>En&amp;crypt</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="162"/>
        <source>Logical</source>
        <translation>Looginen</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="167"/>
        <source>Primary</source>
        <translation>Ensisijainen</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="184"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="269"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="50"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="61"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="73"/>
        <source>Creating new %1 partition on %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="85"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>Asennusohjelma epäonnistui osion luonnissa levylle &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="94"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Ei pystytty avaamaan laitetta &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="104"/>
        <source>Could not open partition table.</source>
        <translation>Osiotaulukkoa ei voitu avata.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="128"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>Asennusohjelma epäonnistui tiedostojärjestelmän luonnissa osiolle %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="136"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>Asennusohjelman epäonnistui päivittää osio levyllä &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>Luo Osiotaulukko</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>Uuden osiotaulukon luominen poistaa kaikki olemassa olevat tiedostot levyltä.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>Minkälaisen osiotaulukon haluat luoda?</translation>
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
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="50"/>
        <source>Create new %1 partition table on %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="57"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="67"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="77"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>Asennusohjelma epäonnistui osiotaulukon luonnissa kohteeseen %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="85"/>
        <source>Could not open device %1.</source>
        <translation>Laitetta %1 ei voitu avata.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
        <source>Create user %1</source>
        <translation>Luo käyttäjä %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="57"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="64"/>
        <source>Creating user %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="80"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Ei voitu kirjoittaa Sudoers -hakemistoon.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="84"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>Ei voida luoda sudoers -tiedostoa kirjoitettavaksi.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="92"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>Ei voida tehdä käyttöoikeuden muutosta sudoers -tiedostolle.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
        <source>Cannot open groups file for reading.</source>
        <translation>Ei voida avata ryhmätiedostoa luettavaksi.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
        <source>Cannot create user %1.</source>
        <translation>Käyttäjää %1 ei voi luoda.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="161"/>
        <source>useradd terminated with error code %1.</source>
        <translation>useradd päättyi virhekoodilla %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="170"/>
        <source>Cannot add user %1 to groups: %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="173"/>
        <source>usermod terminated with error code %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="183"/>
        <source>Cannot set home directory ownership for user %1.</source>
        <translation>Ei voida asettaa kotihakemiston omistusoikeutta käyttäjälle %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="185"/>
        <source>chown terminated with error code %1.</source>
        <translation>chown päättyi virhekoodilla %1.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="43"/>
        <source>Delete partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="51"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="59"/>
        <source>Deleting partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>Asennusohjelma epäonnistui osion %1 poistossa.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="74"/>
        <source>Partition (%1) and device (%2) do not match.</source>
        <translation>Osio (%1) ja laite (%2) eivät täsmää.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="86"/>
        <source>Could not open device %1.</source>
        <translation>Ei voitu avata laitetta %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="95"/>
        <source>Could not open partition table.</source>
        <translation>Osiotaulukkoa ei voitu avata.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation type="unfinished"/>
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
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="133"/>
        <source>Skip writing LUKS configuration for Dracut: &quot;/&quot; partition is not encrypted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="149"/>
        <source>Failed to open %1</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
        <source>Dummy C++ Job</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>Muokkaa olemassa olevaa osiota</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>Sisältö:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>Alusta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>Varoitus: Osion alustus tulee poistamaan kaikki olemassa olevat tiedostot.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Liitoskohta:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="307"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="167"/>
        <source>Set partition information</source>
        <translation>Aseta osion tiedot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="191"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="195"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="203"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="208"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="220"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="230"/>
        <source>Setting up mount points.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>Lomake</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="77"/>
        <source>&amp;Restart now</source>
        <translation>&amp;Käynnistä uudelleen</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="52"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;Kaikki tehty.&lt;/h1&gt;&lt;br/&gt;%1 on asennettu tietokoneellesi.&lt;br/&gt;Voit joko uudelleenkäynnistää uuteen kokoonpanoosi, tai voit jatkaa %2 live-ympäristön käyttöä.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="110"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="49"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>Alusta osio %1 (tiedostojärjestelmä: %2, koko: %3 MB) levyllä %4</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="60"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="71"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="83"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>Levyn &apos;%2&apos; osion %1 alustus epäonnistui.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="91"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Ei voitu avata laitetta &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="100"/>
        <source>Could not open partition table.</source>
        <translation>Osiointitaulua ei voitu avata.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="124"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>Asennusohjelma on epäonnistunut tiedostojärjestelmän luonnissa osiolle %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="133"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>Asennusohjelma on epäonnistunut osiointitaulun päivityksessä levylle &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="69"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="84"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="96"/>
        <source>Konsole not installed</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="70"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="85"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="97"/>
        <source>Please install the kde konsole and try again!</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="220"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>Aseta näppäimiston malli %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="222"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>Aseta näppäimiston asetelmaksi %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>Näppäimistö</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>Järjestelmän maa-asetus</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="67"/>
        <source>&amp;OK</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="88"/>
        <source>I accept the terms and conditions above.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="115"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="118"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="124"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="129"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="166"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="172"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="178"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="184"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="190"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="202"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation>Alue:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation>Vyöhyke:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>&amp;Vaihda...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>Aseta aikavyöhyke %1/%2.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="480"/>
        <source>%1 (%2)</source>
        <extracomment>Language (Country)</extracomment>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LocaleViewStep</name>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="52"/>
        <source>Loading location data...</source>
        <translation>Ladataan sijainnin tietoja...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="169"/>
        <source>Location</source>
        <translation>Sijainti</translation>
    </message>
</context>
<context>
    <name>MoveFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="66"/>
        <source>Move file system of partition %1.</source>
        <translation>Siirrä osion %1 tiedostojärjestelmä.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="80"/>
        <source>Could not open file system on partition %1 for moving.</source>
        <translation>Ei voitu avata tiedostojärjestelmää osiolla %1 siirtämiseen.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="86"/>
        <source>Could not create target for moving file system on partition %1.</source>
        <translation>Ei voitu luoda kohdetta tiedostojärjestelmän siirtoon osiolle %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="95"/>
        <source>Moving of partition %1 failed, changes have been rolled back.</source>
        <translation>Osion %1 siirtäminen epäonnistui, muutokset on palautettu aikaisempaan versioon.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="101"/>
        <source>Moving of partition %1 failed. Roll back of the changes have failed.</source>
        <translation>Osion %1 siirtäminen epäonnistui. Muutosten palauttaminen epäonnistui.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="113"/>
        <source>Updating boot sector after the moving of partition %1 failed.</source>
        <translation>Käynnistyslohkon päivitys epäonnistui osion %1 siirtämisen jälkeen.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="127"/>
        <source>The logical sector sizes in the source and target for copying are not the same. This is currently unsupported.</source>
        <translation>Loogisten sektoreiden koot eivät täsmää lähde ja kohde sektorissa. Tämä ei ole toistaiseksi tuettu toiminto.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="201"/>
        <source>Source and target for copying do not overlap: Rollback is not required.</source>
        <translation>Kopioimisen lähde ja kohde eivät mene limittäin. Palauttaminen ei ole tarpeellista.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="225"/>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="233"/>
        <source>Could not open device %1 to rollback copying.</source>
        <translation>Laitetta %1 ei voitu avata palautuskopiointia varten.</translation>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="79"/>
        <source>Name</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="80"/>
        <source>Description</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="97"/>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="104"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
        <source>Package selection</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>Lomake</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>Näppäimistön malli:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>Kirjoita tähän testaksesi näppäimistöäsi.</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>Lomake</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>Mikä on nimesi?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>Mitä nimeä haluat käyttää sisäänkirjautumisessa?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>fontin koko: normaali</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;jos enemmän kuin yksi henkilö käyttää tätä tietokonetta, voit lisätä lisää tilejä asennuksen jälkeen.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>Valitse salasana pitääksesi tilisi turvallisena.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Syötä salasana kahdesti välttääksesi kirjoitusvirheitä. Hyvän salasanan tulee sisältää sekoitetusti kirjaimia, numeroita ja erikoismerkkejä. Salasanan täytyy olla vähintään kahdeksan merkin mittainen ja tulee vaihtaa säännöllisin väliajoin.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>Mikä on tämän tietokoneen nimi?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Tätä nimeä tullaan käyttämään mikäli asetat tietokoneen näkyviin muille verkossa.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>Valitse salasana pääkäyttäjän tilille.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Syötä salasana kahdesti välttääksesi kirjoitusvirheitä.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="224"/>
        <source>%1  %2</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>PartitionModel</name>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="137"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="169"/>
        <source>Free Space</source>
        <translation>Vapaa tila</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="141"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="173"/>
        <source>New partition</source>
        <translation>Uusi osiointi</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="257"/>
        <source>Name</source>
        <translation>Nimi</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="259"/>
        <source>File System</source>
        <translation>Tiedostojärjestelmä</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="261"/>
        <source>Mount Point</source>
        <translation>Liitoskohta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="263"/>
        <source>Size</source>
        <translation>Koko</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>Lomake</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>&amp;Peru kaikki muutokset</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>Uusi osiointi&amp;taulukko</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>&amp;Create</source>
        <translation>&amp;Luo</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>&amp;Muokkaa</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>&amp;Poista</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="148"/>
        <source>Install boot &amp;loader on:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="161"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>Oletko varma, että haluat luoda uuden osion %1?</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="70"/>
        <source>Gathering system information...</source>
        <translation>Kerätään järjestelmän tietoja...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="121"/>
        <source>Partitions</source>
        <translation>Osiot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="158"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="162"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="166"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="184"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="190"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="196"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="203"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="211"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="239"/>
        <source>Current:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="256"/>
        <source>After:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="399"/>
        <source>No EFI system partition configured</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="413"/>
        <source>EFI system partition flag not set</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="448"/>
        <source>Boot partition not encrypted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="449"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>Oletus näppäimistömalli</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>Oletus</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="210"/>
        <source>unknown</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="212"/>
        <source>extended</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="214"/>
        <source>unformatted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="216"/>
        <source>swap</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="67"/>
        <source>Gathering system information...</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="111"/>
        <source>has at least %1 GB available drive space</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="113"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="121"/>
        <source>has at least %1 GB working memory</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="123"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="131"/>
        <source>is plugged in to a power source</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="132"/>
        <source>The system is not plugged in to a power source.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="139"/>
        <source>is connected to the Internet</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="140"/>
        <source>The system is not connected to the Internet.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="148"/>
        <source>The installer is not running with administrator rights.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="156"/>
        <source>The screen is too small to display the installer.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ResizeFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="76"/>
        <source>Resize file system on partition %1.</source>
        <translation>Muuta tiedostojärjestelmän kokoa osiolla %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="91"/>
        <source>Parted failed to resize filesystem.</source>
        <translation>Parted epäonnistui osion koon muutoksessa.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="101"/>
        <source>Failed to resize filesystem.</source>
        <translation>Osion koon muutos epäonnistui.</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="187"/>
        <source>Resize partition %1.</source>
        <translation>Muuta osion kokoa %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="194"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="205"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="232"/>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="298"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>Asennusohjelma epäonnistui osion %1 koon muuttamisessa levyllä &apos;%2&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="237"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Laitetta ei voi avata %1.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
        <source>Partitioning</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
        <source>Set hostname %1</source>
        <translation>Aseta isäntänimi %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
        <source>Setting hostname %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="61"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="68"/>
        <source>Internal Error</source>
        <translation>Sisäinen Virhe</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="75"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="86"/>
        <source>Cannot write hostname to target system</source>
        <translation>Ei voida kirjoittaa isäntänimeä kohdejärjestelmään.</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>Aseta näppäimistön malliksi %1, asetelmaksi %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="320"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>Virtuaalikonsolin näppäimistöasetuksen tallentaminen epäonnistui.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
        <source>Failed to write to %1</source>
        <translation>Kirjoittaminen epäonnistui kohteeseen %1</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="324"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>X11 näppäimistöasetuksen tallentaminen epäonnistui.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="330"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="48"/>
        <source>Set flags on partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="51"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="55"/>
        <source>Set flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="66"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="70"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
        <source>Clear flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="78"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="84"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="90"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="102"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="106"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="110"/>
        <source>Clearing flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="114"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="120"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="126"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="148"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="157"/>
        <source>Could not open partition table on device &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="169"/>
        <source>Could not find partition &apos;%1&apos;.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetPartGeometryJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="144"/>
        <source>Update geometry of partition %1.</source>
        <translation>Päivitä osion %1 geometria.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="156"/>
        <source>Failed to change the geometry of the partition.</source>
        <translation>Osion geometrian muuttaminen epäonnistui.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation>Aseta salasana käyttäjälle %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation>Huono kohteen järjestelmäpolku</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation>rootMountPoint on %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="123"/>
        <source>Cannot disable root account.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="124"/>
        <source>passwd terminated with error code %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="139"/>
        <source>Cannot set password for user %1.</source>
        <translation>Salasanaa ei voi asettaa käyttäjälle %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation>usermod päättyi virhekoodilla %1.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>Aseta aikavyöhykkeeksi %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>Ei pääsyä valittuun aikavyöhykkeen polkuun.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>Huono polku: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>Aikavyöhykettä ei voi asettaa.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>Linkin luominen kohteeseen %1 epäonnistui; linkin nimi: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/modules/summary/SummaryPage.cpp" line="49"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>Yhteenveto</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="287"/>
        <source>Your username is too long.</source>
        <translation>Käyttäjänimesi on liian pitkä.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="293"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="331"/>
        <source>Your hostname is too short.</source>
        <translation>Isäntänimesi on liian lyhyt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="337"/>
        <source>Your hostname is too long.</source>
        <translation>Isäntänimesi on liian pitkä.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="343"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>Isäntänimesi sisältää epäkelpoja merkkejä. Vain kirjaimet, numerot ja väliviivat ovat sallittuja.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="371"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="415"/>
        <source>Your passwords do not match!</source>
        <translation>Salasanasi eivät täsmää!</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="494"/>
        <source>Password is too short</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="513"/>
        <source>Password is too long</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="50"/>
        <source>Users</source>
        <translation>Käyttäjät</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="201"/>
        <source>%1 support</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="51"/>
        <source>Welcome</source>
        <translation type="unfinished"/>
    </message>
</context>
</TS>
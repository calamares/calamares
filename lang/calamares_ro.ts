<?xml version="1.0" ?><!DOCTYPE TS><TS language="ro" version="2.1">
<context>
    <name>AlongsidePage</name>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="77"/>
        <source>Choose partition to shrink:</source>
        <translation>Alegeți partiția de micșorat:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="78"/>
        <source>Allocate drive space by dragging the divider below:</source>
        <translation>Alocați spațiu pe disc trăgând despărțitorul:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="121"/>
        <source>With this operation, the partition &lt;strong&gt;%1&lt;/strong&gt; which contains %4 will be shrunk to %2MB and a new %3MB partition will be created for %5.</source>
        <translation>Cu această operație, partiția &lt;strong&gt;%1&lt;/strong&gt;, cu mărimea de %4, va fi redusă la %2MB și se va crea o nouă partiție de %3MB pentru %5.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="198"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>O partiție de sistem EFI nu se găsește nicăieri pe acest sistem. Vă rugăm să reveniți și să utilizați partiționarea manuală pentru a seta %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="208"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>Partiția de sistem EFI de pe %1 va fi folosită pentru a începe %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/AlongsidePage.cpp" line="218"/>
        <source>EFI system partition:</source>
        <translation>Partiție de sistem EFI</translation>
    </message>
</context>
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="61"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>&lt;strong&gt;Mediul de boot&lt;/strong&gt; al acestui sistem.&lt;br&gt;&lt;br&gt;Sisteme x86 mai vechi suportă numai &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Sisteme moderne folosesc de obicei &lt;strong&gt;EFI&lt;/strong&gt;, dar ar putea fi afișate ca BIOS dacă au fost configurate în modul de compatibilitate.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="75"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>Acest sistem a fost pornit într-un mediu de boot &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Pentru a configura pornirea dintr-un mediu EFI, acest program de instalare trebuie să creeze o aplicație pentru boot-are, cum ar fi &lt;strong&gt;GRUB&lt;/strong&gt; sau &lt;strong&gt;systemd-boot&lt;/strong&gt; pe o &lt;strong&gt;partiție de sistem EFI&lt;/strong&gt;. Acest pas este automat, cu excepția cazului în care alegeți partiționarea manuală.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="87"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>Sistemul a fost pornit într-un mediu de boot &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Pentru a configura pornirea de la un mediu BIOS, programul de instalare trebuie să instaleze un mediu de boot, cum ar fi &lt;strong&gt;GRUB&lt;/strong&gt; fie la începutul unei partiții sau pe &lt;strong&gt;Master Boot Record&lt;/strong&gt; în partea de început a unei tabele de partiții (preferabil). Acesta este un pas automat, cu excepția cazului în care alegeți partiționarea manuală.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>Master boot record (MBR) al %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>Partiție de boot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>Partiție de sistem</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>Nu instala un bootloader</translation>
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
        <translation>Stocare globală</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>Coadă de sarcini</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>Module</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Tools</source>
        <translation>Unelte</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="102"/>
        <source>Debug information</source>
        <translation>Informație pentru depanare</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="77"/>
        <source>Install</source>
        <translation>Instalează</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="89"/>
        <source>Done</source>
        <translation>Gata</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="51"/>
        <source>Run command %1 %2</source>
        <translation>Rulează comanda %1 %2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="60"/>
        <source>Running command %1 %2</source>
        <translation>Se rulează comanda %1 %2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="89"/>
        <source>External command crashed</source>
        <translation>Comandă externă a avut o pană</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="90"/>
        <source>Command %1 crashed.
Output:
%2</source>
        <translation>Comanda %1 în pană.
Rezultat:
%2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="95"/>
        <source>External command failed to start</source>
        <translation>Comanda externă nu a pornit</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="96"/>
        <source>Command %1 failed to start.</source>
        <translation>Comanda %1 nu a pornit.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="100"/>
        <source>Internal error when starting command</source>
        <translation>Eroare internă în pornirea comenzii</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="101"/>
        <source>Bad parameters for process job call.</source>
        <translation>Parametri proști pentru apelul sarcinii de proces.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="104"/>
        <source>External command failed to finish</source>
        <translation>Comanda externă nu s-a terminat</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="105"/>
        <source>Command %1 failed to finish in %2s.
Output:
%3</source>
        <translation>Comanda %1 nu s-a terminat în %2s.
Rezultat:
%3</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="111"/>
        <source>External command finished with errors</source>
        <translation>Comanda externă s-a terminat cu erori</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="112"/>
        <source>Command %1 finished with exit code %2.
Output:
%3</source>
        <translation>Comanda %1 s-a terminat cu codul de ieșire %2.
Rezultat:
%3</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="241"/>
        <source>Running %1 operation.</source>
        <translation>Se rulează operațiunea %1.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="254"/>
        <source>Bad working directory path</source>
        <translation>Calea dosarului de lucru este proastă</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="255"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>Dosarul de lucru %1 pentru sarcina python %2 nu este citibil.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="265"/>
        <source>Bad main script file</source>
        <translation>Fișierul script principal este prost</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="266"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>Fișierul script peincipal %1 pentru sarcina Python %2 nu este citibil.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="311"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>Eroare Boost.Python în sarcina „%1”.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="65"/>
        <source>&amp;Back</source>
        <translation>&amp;Înapoi</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="66"/>
        <source>&amp;Next</source>
        <translation>&amp;Următorul</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="67"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="295"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Anulează</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
        <source>Cancel installation?</source>
        <translation>Anulez instalarea?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>Doriți să anulați procesul curent de instalare?
Programul de instalare va ieși, iar toate modificările vor fi pierdute.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="224"/>
        <source>Continue with setup?</source>
        <translation>Continuați configurarea?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="225"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>Programul de instalare %1 este pregătit să facă schimbări pe discul dumneavoastră pentru a instala %2.&lt;br/&gt;&lt;strong&gt;Nu veți putea anula aceste schimbări.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="232"/>
        <source>&amp;Install now</source>
        <translation>&amp;Instalează acum</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="233"/>
        <source>Go &amp;back</source>
        <translation>Î&amp;napoi</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="264"/>
        <source>&amp;Quit</source>
        <translation>&amp;Ieșire</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="170"/>
        <source>Error</source>
        <translation>Eroare</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="171"/>
        <source>Installation Failed</source>
        <translation>Instalare eșuată</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="234"/>
        <source>Unknown exception type</source>
        <translation>Tip de excepție necunoscut</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="247"/>
        <source>unparseable Python error</source>
        <translation>Eroare Python neanalizabilă</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="263"/>
        <source>unparseable Python traceback</source>
        <translation>Traceback Python neanalizabil</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="267"/>
        <source>Unfetchable Python error.</source>
        <translation>Eroare Python nepreluabilă</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>Program de instalare %1</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="98"/>
        <source>Show debug information</source>
        <translation>Arată informația de depanare</translation>
    </message>
</context>
<context>
    <name>CheckFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="34"/>
        <source>Checking file system on partition %1.</source>
        <translation>Se verifică sistemul de fișiere pe partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="58"/>
        <source>The file system check on partition %1 failed.</source>
        <translation>Verificarea sistemului de fișiere pe %1 a eșuat.</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="95"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>Acest calculator nu satisface cerințele minimale pentru instalarea %1.&lt;br/&gt;Instalarea nu poate continua. &lt;a href=&quot;#details&quot;&gt;Detalii...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>Acest calculator nu satisface unele din cerințele recomandate pentru instalarea %1.&lt;br/&gt;Instalarea poate continua, dar unele funcții ar putea fi dezactivate.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="142"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>Acest program vă va pune mai multe întrebări și va seta %2 pe calculatorul dumneavoastră.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="166"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>Pentru rezultate optime, asigurați-vă că acest calculator:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="194"/>
        <source>System requirements</source>
        <translation>Cerințe de sistem</translation>
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
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="117"/>
        <source>After:</source>
        <translation>După:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="223"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;Partiționare manuală&lt;/strong&gt;&lt;br/&gt;Puteți crea sau redimensiona partițiile.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="808"/>
        <source>Boot loader location:</source>
        <translation>Locație boot loader:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="755"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>%1 va fi micșorată la %2MB și o nouă partiție %3MB va fi creată pentru %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="115"/>
        <source>Select storage de&amp;vice:</source>
        <translation>Selectează dispoziti&amp;vul de stocare:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="116"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="740"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="779"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="855"/>
        <source>Current:</source>
        <translation>Actual:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="741"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Selectează o partiție de micșorat, apoi trageți bara din jos pentru a redimensiona&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="846"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Selectează o partiție pe care să se instaleze&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="901"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>O partiție de sistem EFI nu poate fi găsită nicăieri în acest sistem. Vă rugăm să reveniți și să partiționați manual pentru a seta %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="911"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>Partiția de sistem EFI de la %1 va fi folosită pentru a porni %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="920"/>
        <source>EFI system partition:</source>
        <translation>Partiție de sistem EFI:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1005"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Acest dispozitiv de stocare nu pare să aibă un sistem de operare instalat. Ce doriți să faceți?&lt;br/&gt;Veți putea revedea și confirma alegerile făcute înainte să fie realizate schimbări pe dispozitivul de stocare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1010"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1050"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1074"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1112"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;Șterge discul&lt;/strong&gt;&lt;br/&gt;Aceasta va &lt;font color=&quot;red&quot;&gt;șterge&lt;/font&gt; toate datele prezente pe dispozitivul de stocare selectat.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1039"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Acest dispozitiv de stocare are %1. Ce doriți să faceți?&lt;br/&gt;Veți putea revedea și confirma alegerile făcute înainte să fie realizate schimbări pe dispozitivul de stocare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1014"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1045"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1069"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1107"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;Instalează laolaltă&lt;/strong&gt;&lt;br/&gt;Instalatorul va micșora o partiție pentru a face loc pentru %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1019"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1055"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1078"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1116"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;Înlocuiește o partiție&lt;/strong&gt;&lt;br/&gt;Înlocuiește o partiție cu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1064"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Acest dispozitiv de stocare are deja un sistem de operare instalat. Ce doriți să faceți?&lt;br/&gt;Veți putea revedea și confirma alegerile făcute înainte de se realiza schimbări pe dispozitivul de stocare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1102"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Acest dispozitiv de stocare are mai multe sisteme de operare instalate. Ce doriți să faceți?&lt;br/&gt;Veți putea revedea și confirma alegerile făcute înainte de a se realiza schimbări pe dispozitivul de stocare.</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="44"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>Eliminați montările pentru operațiunea de partiționare pe %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="52"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>Se elimină montările pentru operațiunile de partiționare pe %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="171"/>
        <source>Cleared all mounts for %1</source>
        <translation>S-au eliminat toate punctele de montare pentru %1</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
        <source>Clear all temporary mounts.</source>
        <translation>Elimină toate montările temporare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="47"/>
        <source>Clearing all temporary mounts.</source>
        <translation>Se elimină toate montările temporare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="58"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>Nu se poate obține o listă a montărilor temporare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="97"/>
        <source>Cleared all temporary mounts.</source>
        <translation>S-au eliminat toate montările temporare.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>Creează o partiție</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Partition &amp;Type:</source>
        <translation>&amp;Tip de partiție:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="50"/>
        <source>&amp;Primary</source>
        <translation>&amp;Primară</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="60"/>
        <source>E&amp;xtended</source>
        <translation>E&amp;xtinsă</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="89"/>
        <source>Fi&amp;le System:</source>
        <translation>Sis&amp;tem de fișiere:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="181"/>
        <source>Flags:</source>
        <translation>Flags:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="118"/>
        <source>&amp;Mount Point:</source>
        <translation>Punct de &amp;Montare</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="164"/>
        <source>Si&amp;ze:</source>
        <translation>Mă&amp;rime:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="174"/>
        <source> MB</source>
        <translation> MB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="136"/>
        <source>Logical</source>
        <translation>Logică</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="141"/>
        <source>Primary</source>
        <translation>Primară</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="158"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="48"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>Creează o nouă partiție de %2MB pe %4 (3%) cu sistemul de operare %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="59"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Creează o nouă partiție de &lt;strong&gt;%2MB&lt;/strong&gt; pe &lt;strong&gt;%4&lt;/strong&gt; (%3) cu sistemul de fișiere &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="71"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>Se creează  nouă partiție %1 pe %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="83"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>Programul de instalare nu a putut crea partiția pe discul „%1”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="92"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Nu se poate deschide dispozitivul „%1”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="102"/>
        <source>Could not open partition table.</source>
        <translation>Nu se poate deschide tabela de partiții.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="126"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>Programul de instalare nu a putut crea sistemul de fișiere pe partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="134"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>Programul de instalare nu a putut actualiza tabela de partiții pe discul „%1”.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>Creează tabelă de partiții</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>Crearea unei tabele de partiții va șterge toate datele de pe disc.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>Ce fel de tabelă de partiții doriți să creați?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>Înregistrare de boot principală (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>Tabelă de partiții GUID (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>Creați o nouă tabelă de partiții %1 pe %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="56"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Creați o nouă tabelă de partiții &lt;strong&gt;%1&lt;/strong&gt; pe &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="66"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>Se creează o nouă tabelă de partiții %1 pe %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="76"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>Programul de instalare nu a putut crea o tabelă de partiții pe %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="84"/>
        <source>Could not open device %1.</source>
        <translation>Nu se poate deschide dispozitivul %1.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="49"/>
        <source>Create user %1</source>
        <translation>Creează utilizatorul %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="56"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Creează utilizatorul &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="63"/>
        <source>Creating user %1.</source>
        <translation>Se creează utilizator %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="79"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Nu se poate scrie în dosarul sudoers.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>Nu se poate crea fișierul sudoers pentru scriere.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="91"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>Nu se poate chmoda fișierul sudoers.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="97"/>
        <source>Cannot open groups file for reading.</source>
        <translation>Nu se poate deschide fișierul groups pentru citire.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="136"/>
        <source>Cannot create user %1.</source>
        <translation>Nu se poate crea utilizatorul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="138"/>
        <source>useradd terminated with error code %1.</source>
        <translation>useradd s-a terminat cu codul de eroare %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="143"/>
        <source>Cannot set full name for user %1.</source>
        <translation>Nu se poate seta numele complet pentru utilizatorul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="145"/>
        <source>chfn terminated with error code %1.</source>
        <translation>chfn s-a terminat cu codul de eroare %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="155"/>
        <source>Cannot set home directory ownership for user %1.</source>
        <translation>Nu se poate seta apartenența dosarului home pentru utilizatorul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="157"/>
        <source>chown terminated with error code %1.</source>
        <translation>chown s-a terminat cu codul de eroare %1.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="42"/>
        <source>Delete partition %1.</source>
        <translation>Șterge partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="50"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Șterge partiția &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="58"/>
        <source>Deleting partition %1.</source>
        <translation>Se șterge partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="67"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>Programul de instalare nu a putut șterge partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
        <source>Partition (%1) and device (%2) do not match.</source>
        <translation>Partiția (%1) și dispozitivul (%2) nu se potrivesc.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="85"/>
        <source>Could not open device %1.</source>
        <translation>Nu se poate deschide dispozitivul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="94"/>
        <source>Could not open partition table.</source>
        <translation>Nu se poate deschide tabela de partiții.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="63"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>Tipul de &lt;strong&gt;tabelă de partiții&lt;/strong&gt; de pe dispozitivul de stocare selectat.&lt;br&gt;&lt;br&gt;Singura metodă de a schimba tipul de tabelă de partiții este ștergerea și recrearea acesteia de la zero, ceea de distruge toate datele de pe dispozitivul de stocare.&lt;br&gt;Acest program de instalare va păstra tabela de partiții actuală cu excepția cazului în care alegeți altfel.&lt;br&gt;Dacă nu sunteți sigur, GPT este preferabil pentru sistemele moderne.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>Acest dispozitiv are o tabelă de partiții &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation>Acesta este un dispozitiv de tip &lt;strong&gt;loop&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Este un pseudo-dispozitiv fără tabelă de partiții care face un fișier accesibil ca un dispozitiv de tip bloc. Această schemă conține de obicei un singur sistem de fișiere.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>Programul de instalare &lt;strong&gt;nu poate detecta o tabelă de partiții&lt;/strong&gt; pe dispozitivul de stocare selectat.&lt;br&gt;&lt;br&gt;Dispozitivul fie nu are o tabelă de partiții, sau tabela de partiții este coruptă sau de un tip necunoscut.&lt;br&gt;Acest program de instalare poate crea o nouă tabelă de partiție în mod automat sau prin intermediul paginii de partiționare manuală.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;Acesta este tipul de tabelă de partiții recomandat pentru sisteme moderne ce pornesc de pe un mediu de boot &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation>&lt;br&gt;&lt;br&gt;Această tabelă de partiții este recomandabilă doar pentru sisteme mai vechi care pornesc de la un mediu de boot &lt;strong&gt;BIOS&lt;/strong&gt;. GPT este recomandabil în cele mai multe cazuri.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Atenție:&lt;/strong&gt; tabela de partiții MBR partition este un standard învechit din epoca MS-DOS.&lt;br&gt;Acesta permite doar 4 partiții &lt;em&gt;primare&lt;/em&gt;, iar din acestea 4 doar una poate fi de tip &lt;em&gt;extins&lt;/em&gt;, care la rândul ei mai poate conține un număr mare de partiții &lt;em&gt;logice&lt;/em&gt;.</translation>
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
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>Editează partiție existentă</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>Conținut:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>&amp;Păstrează</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>Formatează</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>Atenție: Formatarea partiției va șterge toate datele existente.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>Punct de &amp;Montare:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>Mă&amp;rime</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="132"/>
        <source>Fi&amp;le System:</source>
        <translation>Sis&amp;tem de fișiere:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="145"/>
        <source>Flags:</source>
        <translation>Flags:</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="88"/>
        <source>Set partition information</source>
        <translation>Setează informația pentru partiție</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="111"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>Instalează %1 pe &lt;strong&gt;noua&lt;/strong&gt; partiție de sistem %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="116"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Setează &lt;strong&gt;noua&lt;/strong&gt; partiție %2 cu punctul de montare &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="124"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Instalează %2 pe partiția de sistem %3 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="130"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Setează partiția %3 &lt;strong&gt;%1&lt;/strong&gt; cu punctul de montare &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="142"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Instalează bootloader-ul pe &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="152"/>
        <source>Setting up mount points.</source>
        <translation>Se setează puncte de montare.</translation>
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
        <location filename="../src/modules/finished/FinishedPage.ui" line="77"/>
        <source>&amp;Restart now</source>
        <translation>&amp;Repornește acum</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="50"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;Gata.&lt;/h1&gt;&lt;br/&gt;%1 a fost instalat pe calculatorul dumneavoastră.&lt;br/&gt;Puteți reporni noul sistem, sau puteți continua să folosiți sistemul de operare portabil %2.</translation>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="43"/>
        <source>Finish</source>
        <translation>Termină</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="48"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>Formatează partiția %1 (sistem de fișiere: %2, mărime: %3 MB) pe %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="59"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Formatează  partiția &lt;strong&gt;%1&lt;/strong&gt;, de &lt;strong&gt;%3MB&lt;/strong&gt; cu sistemul de fișiere &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="70"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>Se formatează partiția %1 cu sistemul de fișiere %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="82"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>Programul de instalare nu a putut formata partiția %1 pe discul „%2”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="90"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Nu se poate deschide dispozitivul „%1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="99"/>
        <source>Could not open partition table.</source>
        <translation>Nu se poate deschide tabela de partiții.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="107"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>Programul de instalare nu a putut crea sistemul de fișiere pe partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="115"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>Programul de instalare nu a putut actualiza tabela de partiții pe discul „%1”.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="69"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="84"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="96"/>
        <source>Konsole not installed</source>
        <translation>Konsole nu este instalat</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="70"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="85"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="97"/>
        <source>Please install the kde konsole and try again!</source>
        <translation>Vă rugăm să instalați kde konsole și încercați din nou!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>Se execută scriptul: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>Script</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="201"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>Setează modelul tastaturii la %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="203"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>Setează aranjamentul de tastatură la %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="49"/>
        <source>Keyboard</source>
        <translation>Tastatură</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="33"/>
        <source>System locale setting</source>
        <translation>Setările de localizare</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="40"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Setările de localizare ale sistemului afectează limba și setul de caractere folosit pentru unele elemente de interfață la linia de comandă.&lt;br/&gt;Setările actuale sunt &lt;strong&gt;%1&lt;/strong&gt;.</translation>
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
        <translation>Sunt de acord cu termenii și condițiile de mai sus.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="115"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;Acord de licențiere&lt;/h1&gt;Această procedură va instala software proprietar supus unor termeni de licențiere.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="118"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>Vă rugăm să citiți Licența de utilizare (EULA) de mai sus.&lt;br&gt;Dacă nu sunteți de acord cu termenii, procedura de instalare nu poate continua.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="124"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;Acord de licențiere&lt;/h1&gt;Această procedură de instalare poate instala software proprietar supus unor termeni de licențiere, pentru a putea oferi funcții suplimentare și pentru a îmbunătăți experiența utilizatorilor.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="129"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>Vă rugăm să citiți Licența de utilizare (EULA) de mai sus.&lt;br/&gt;Dacă nu sunteți de acord cu termenii, softwareul proprietar nu va fi instalat și se vor folosi alternative open-source în loc.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;de %2</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="166"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;%1 driver grafic&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;de %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="172"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 plugin de browser&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;de %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="178"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;de %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="184"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 pachet&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;de %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="190"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;de %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="202"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;vezi acordul de licențiere&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>Licență</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="158"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="169"/>
        <source>The system locale is set to %1.</source>
        <translation>Sistemul are localizarea setată pentru %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="166"/>
        <source>Region:</source>
        <translation>Regiune:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="167"/>
        <source>Zone:</source>
        <translation>Zonă:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="172"/>
        <source>&amp;Change...</source>
        <translation>S&amp;chimbă</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="271"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>Setează fusul orar la %1/%2.&lt;br/&gt;</translation>
    </message>
</context>
<context>
    <name>LocaleViewStep</name>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="48"/>
        <source>Loading location data...</source>
        <translation>Se încarcă datele locației...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="82"/>
        <source>Location</source>
        <translation>Locație</translation>
    </message>
</context>
<context>
    <name>MoveFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="66"/>
        <source>Move file system of partition %1.</source>
        <translation>Mută sistemul de fișiere al partiției %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="80"/>
        <source>Could not open file system on partition %1 for moving.</source>
        <translation>Nu s-a putut deschide sistemul de fișiere pe partiția %1 pentru mutare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="86"/>
        <source>Could not create target for moving file system on partition %1.</source>
        <translation>Nu s-a putut crea ținta pentru mutarea sistemului de fișiere pe partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="95"/>
        <source>Moving of partition %1 failed, changes have been rolled back.</source>
        <translation>Mutarea partiției %1 a eșuat, schimbările au fost anulate.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="101"/>
        <source>Moving of partition %1 failed. Roll back of the changes have failed.</source>
        <translation>Mutarea partiției %1 a eșuat. Anularea schimbărilor a eșuat.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="113"/>
        <source>Updating boot sector after the moving of partition %1 failed.</source>
        <translation>Se actualizează sectorul de boot după eșecul mutării partiției %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="127"/>
        <source>The logical sector sizes in the source and target for copying are not the same. This is currently unsupported.</source>
        <translation>Mărimile sectoarelor logice din sursa și ținta copierii nu sunt identice. Nu există suport momentan.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="197"/>
        <source>Source and target for copying do not overlap: Rollback is not required.</source>
        <translation>Sursa și ținta copierii nu se suprapun: nu este necesară retragerea schimbărilor.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="221"/>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="229"/>
        <source>Could not open device %1 to rollback copying.</source>
        <translation>Nu se poate deschide dispozitivul %1 pentru retragerea copierii.</translation>
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
        <translation>Modelul tastaturii:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>Tastați aici pentru a testa tastatura</translation>
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
        <translation>Cum vă numiți?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>Ce nume doriți să utilizați pentru logare?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="197"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>grosimea fontului: normală</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Dacă mai multe persoane vor utiliza acest calculator, puteți seta mai multe conturi după instalare.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>Alegeți o parolă pentru a menține contul în siguranță.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Introduceți parola de 2 ori pentru a se verifica greșelile de tipar. O parolă bună va conține o combinație de litere, numere și punctuație, ar trebui să aibă cel puțin 8 caractere și ar trebui schimbată la intervale regulate.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>Care este numele calculatorului?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Numele va fi folosit dacă faceți acest calculator vizibil pentru alții pe o rețea.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>Autentifică-mă automat, fără a-mi cere parola.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>Folosește aceeași parolă pentru contul de administrator.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>Alege o parolă pentru contul de administrator.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Introduceți parola de 2 ori pentru a se verifica greșelile de tipar.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="191"/>
        <source>Root</source>
        <translation>Root</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="194"/>
        <source>Home</source>
        <translation>Home</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Boot</source>
        <translation>Boot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="199"/>
        <source>EFI system</source>
        <translation>Sistem EFI</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>Swap</source>
        <translation>Swap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>New partition for %1</source>
        <translation>Noua partiție pentru %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="220"/>
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
        <translation>Spațiu liber</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="141"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="173"/>
        <source>New partition</source>
        <translation>Partiție nouă</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="242"/>
        <source>Name</source>
        <translation>Nume</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="244"/>
        <source>File System</source>
        <translation>Sistem de fișiere</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="246"/>
        <source>Mount Point</source>
        <translation>Punct de montare</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="248"/>
        <source>Size</source>
        <translation>Mărime</translation>
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
        <translation>Dispoziti&amp;v de stocare:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>&amp;Retrage toate schimbările</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="84"/>
        <source>New Partition &amp;Table</source>
        <translation>&amp;Tabelă nouă de partiții</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="104"/>
        <source>&amp;Create</source>
        <translation>&amp;Crează</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
        <source>&amp;Edit</source>
        <translation>&amp;Editează</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
        <source>&amp;Delete</source>
        <translation>&amp;Șterge</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="145"/>
        <source>Install boot &amp;loader on:</source>
        <translation>Instalează boot&amp;loaderul pe:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="147"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>Sigur doriți să creați o nouă tabelă de partiție pe %1?</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="67"/>
        <source>Gathering system information...</source>
        <translation>Se adună informații despre sistem...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="106"/>
        <source>Partitions</source>
        <translation>Partiții</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="143"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>Instalează %1 &lt;strong&gt;laolaltă&lt;/strong&gt; cu un alt sistem de operare.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="148"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>&lt;strong&gt;Șterge&lt;/strong&gt; discul și instalează %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="153"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>&lt;strong&gt;Înlocuiește&lt;/strong&gt; o partiție cu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="158"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>Partiționare &lt;strong&gt;manuală&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Instalează %1 &lt;strong&gt;laolaltă&lt;/strong&gt; cu un alt sistem de operare pe discul &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="178"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation>&lt;strong&gt;Șterge&lt;/strong&gt; discul &lt;strong&gt;%2&lt;/strong&gt; (%3) și instalează %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="185"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>&lt;strong&gt;Înlocuiește&lt;/strong&gt; o partiție pe discul &lt;strong&gt;%2&lt;/strong&gt; (%3) cu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="192"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation>Partiționare &lt;strong&gt;manuală&lt;/strong&gt; a discului &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="200"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation>Discul &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="228"/>
        <source>Current:</source>
        <translation>Actual:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="244"/>
        <source>After:</source>
        <translation>După:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="386"/>
        <source>No EFI system partition configured</source>
        <translation>Nicio partiție de sistem EFI nu a fost configurată</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="387"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation>Este necesară o partiție de sistem EFI pentru a porni %1.&lt;br/&gt;&lt;br/&gt;Pentru a configura o partiție de sistem EFI, reveniți și selectați sau creați o partiție FAT32 cu flag-ul &lt;strong&gt;esp&lt;/strong&gt; activat și montată la &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Puteți continua și fără configurarea unei partiții de sistem EFI, dar este posibil ca sistemul să nu pornească.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="401"/>
        <source>EFI system partition flag not set</source>
        <translation>Flag-ul de partiție de sistem pentru EFI nu a fost setat</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="402"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation>O partiție de sistem EFI este necesară pentru a porni %1.&lt;br/&gt;&lt;br/&gt;A fost configurată o partiție cu punct de montare la &lt;strong&gt;%2&lt;/strong&gt; dar flag-ul &lt;strong&gt;esp&lt;/strong&gt; al acesteia nu a fost setat.&lt;br/&gt;Pentru a seta flag-ul, reveniți și editați partiția.&lt;br/&gt;&lt;br/&gt;Puteți continua și fără setarea flag-ului, dar este posibil ca sistemul să nu pornească.</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>Modelul tastaturii implicit</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>Implicit</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="160"/>
        <source>unknown</source>
        <translation>necunoscut</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="162"/>
        <source>extended</source>
        <translation>extins</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="164"/>
        <source>unformatted</source>
        <translation>neformatat</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>Spațiu nepartiționat sau tabelă de partiții necunoscută</translation>
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
        <translation>Selectați locul în care să instalați %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Atenție: &lt;/font&gt;aceasta va șterge toate fișierele de pe partiția selectată.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="161"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>Elementul selectat nu pare a fi o partiție validă.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="169"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1 nu poate fi instalat în spațiul liber. Vă rugăm să alegeți o partiție existentă.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="180"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1 nu poate fi instalat pe o partiție extinsă. Vă rugăm selectați o partiție primară existentă sau o partiție logică.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="191"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>%1 nu poate fi instalat pe această partiție.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="198"/>
        <source>Data partition (%1)</source>
        <translation>Partiție de date (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="215"/>
        <source>Unknown system partition (%1)</source>
        <translation>Partiție de sistem necunoscută (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="220"/>
        <source>%1 system partition (%2)</source>
        <translation>%1 partiție de sistem (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="231"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Partiția %1 este prea mică pentru %2. Vă rugăm selectați o partiție cu o capacitate de cel puțin %3 GiB.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="255"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;O partiție de sistem EFI nu a putut fi găsită nicăieri pe sistem. Vă rugăm să reveniți și să utilizați partiționarea manuală pentru a seta %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="311"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 va fi instalat pe %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Atenție: &lt;/font&gt;toate datele de pe partiția %2 se vor pierde.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="277"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>Partiția de sistem EFI de la %1 va fi folosită pentru a porni %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="295"/>
        <source>EFI system partition:</source>
        <translation>Partiție de sistem EFI:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="57"/>
        <source>Gathering system information...</source>
        <translation>Se adună informații despre sistem...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="98"/>
        <source>has at least %1 GB available drive space</source>
        <translation>are cel puțin %1 spațiu disponibil</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="100"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>Nu este suficient spațiu disponibil. Sunt necesari cel puțin %1 GB.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="108"/>
        <source>has at least %1 GB working memory</source>
        <translation>are cel puțin %1 GB de memorie utilizabilă</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="110"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>Sistemul nu are suficientă memorie utilizabilă. Sunt necesari cel puțin %1 GB.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>is plugged in to a power source</source>
        <translation>este alimentat cu curent</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="119"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>Sistemul nu este alimentat cu curent.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="126"/>
        <source>is connected to the Internet</source>
        <translation>este conectat la Internet</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="127"/>
        <source>The system is not connected to the Internet.</source>
        <translation>Sistemul nu este conectat la Internet.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="135"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>Programul de instalare nu rulează cu privilegii de administrator.</translation>
    </message>
</context>
<context>
    <name>ResizeFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="76"/>
        <source>Resize file system on partition %1.</source>
        <translation>Redimensionează sistemul de fișiere pe partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="91"/>
        <source>Parted failed to resize filesystem.</source>
        <translation>Parted n-a redimensionat sistemul de fișiere.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="101"/>
        <source>Failed to resize filesystem.</source>
        <translation>Nu s-a redimensional sistemul de fișiere.</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="187"/>
        <source>Resize partition %1.</source>
        <translation>Redimensionează partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="194"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation>Redimensionează partiția &lt;strong&gt;%1&lt;/strong&gt; de la&lt;strong&gt;%2MB&lt;/strong&gt; la &lt;strong&gt;%3MB&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="205"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation>Se redimensionează partiția %1 de la %2MG la %3MB.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="232"/>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="298"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>Programul de instalare nu a redimensionat partiția %1 pe discul „%2”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="237"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Nu se poate deschide dispozitivul „%1”.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="83"/>
        <source>Scanning storage devices...</source>
        <translation>Se scanează dispozitivele de stocare...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Partitioning</source>
        <translation>Partiționare</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
        <source>Set hostname %1</source>
        <translation>Setează hostname %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Setați un hostname &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
        <source>Setting hostname %1.</source>
        <translation>Se setează hostname %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="61"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="68"/>
        <source>Internal Error</source>
        <translation>Eroare internă</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="75"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="86"/>
        <source>Cannot write hostname to target system</source>
        <translation>Nu se poate scrie hostname pe sistemul țintă</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="57"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>Setează modelul de tastatură la %1, cu aranjamentul %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="284"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>Nu s-a reușit scrierea configurației de tastatură pentru consola virtuală.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="285"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="289"/>
        <source>Failed to write to %1</source>
        <translation>Nu s-a reușit scrierea %1</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="288"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>Nu s-a reușit scrierea configurației de tastatură pentru X11.</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="47"/>
        <source>Set flags on partition %1.</source>
        <translation>Setează flag-uri pentru partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Șterge flag-urile partiției &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="59"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Marchează partiția &lt;strong&gt;%1&lt;/strong&gt; cu flag-ul &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Se șterg flag-urile pentru partiția &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Se setează flag-urile &lt;strong&gt;%2&lt;/strong&gt; pentru partiția &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="90"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>Programul de instalare a eșuat în setarea flag-urilor pentru partiția %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>Nu s-a putut deschide dispozitivul „%1”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Could not open partition table on device &apos;%1&apos;.</source>
        <translation>Nu s-a putut deschide tabela de partiții pentru dispozitivul „%1”.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="119"/>
        <source>Could not find partition &apos;%1&apos;.</source>
        <translation>Nu a fost găsită partiția „%1”.</translation>
    </message>
</context>
<context>
    <name>SetPartGeometryJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="144"/>
        <source>Update geometry of partition %1.</source>
        <translation>Actualizează geometria partiției %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="156"/>
        <source>Failed to change the geometry of the partition.</source>
        <translation>Nu se poate schimba geometria partiției.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="42"/>
        <source>Set password for user %1</source>
        <translation>Setează parola pentru utilizatorul %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="49"/>
        <source>Setting password for user %1.</source>
        <translation>Se setează parola pentru utilizatorul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="59"/>
        <source>Bad destination system path.</source>
        <translation>Cale de sistem destinație proastă.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="60"/>
        <source>rootMountPoint is %1</source>
        <translation>rootMountPoint este %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="74"/>
        <source>Cannot set password for user %1.</source>
        <translation>Nu se poate seta parola pentru utilizatorul %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="76"/>
        <source>usermod terminated with error code %1.</source>
        <translation>usermod s-a terminat cu codul de eroare %1.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>Setează fusul orar la %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>Nu se poate accesa calea fusului selectat.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>Cale proastă: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>Nu se poate seta fusul orar.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>Crearea legăturii eșuată, ținta: %1; numele legăturii: 2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="95"/>
        <source>Cannot set timezone,</source>
        <translation>Nu se poate seta fusul orar,</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>Nu se poate deschide /etc/timezone pentru scriere</translation>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/modules/summary/SummaryPage.cpp" line="46"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation>Acesta este un rezumat a ce se va întâmpla după ce începeți procedura de instalare.</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>Sumar</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="268"/>
        <source>Your username is too long.</source>
        <translation>Numele de utilizator este prea lung.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="278"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>Numele de utilizator conține caractere invalide. Folosiți doar litere mici și numere.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="322"/>
        <source>Your hostname is too short.</source>
        <translation>Hostname este prea scurt.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too long.</source>
        <translation>Hostname este prea lung.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="344"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>Hostname conține caractere invalide. Folosiți doar litere, numere și cratime.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="375"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="408"/>
        <source>Your passwords do not match!</source>
        <translation>Parolele nu se potrivesc!</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
        <source>Users</source>
        <translation>Utilizatori</translation>
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
        <translation>&amp;Limbă:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>&amp;Note asupra ediției</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>&amp;Probleme cunoscute</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>&amp;Suport</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>&amp;Despre</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="56"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Bine ați venit la programul de instalare pentru %1.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="70"/>
        <source>About %1 installer</source>
        <translation>Despre programul de instalare %1</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="72"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2015 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;pentru %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2015 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Mulțumim: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Philip Müller, Pier Luigi Fiorini, Rohan Garg și &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;echipei traducătorilor Calamares&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; dezvoltarea este sponsorizată de &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="195"/>
        <source>%1 support</source>
        <translation>%1 suport</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="50"/>
        <source>Welcome</source>
        <translation>Bine ați venit</translation>
    </message>
</context>
</TS>
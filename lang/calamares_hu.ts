<?xml version="1.0" ?><!DOCTYPE TS><TS language="hu" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>A rendszer &lt;strong&gt;indító környezete.&lt;/strong&gt; &lt;br&gt;&lt;br&gt;Régebbi x86 alapú rendszerek csak &lt;strong&gt;BIOS&lt;/strong&gt;&lt;br&gt;-t támogatják. A modern rendszerek gyakran &lt;strong&gt;EFI&lt;/strong&gt;-t használnak, de lehet, hogy BIOS-ként látható ha kompatibilitási módban fut az indító környezet. </translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>A rendszer &lt;strong&gt;EFI&lt;/strong&gt; indító környezettel lett indítva.&lt;br&gt;&lt;br&gt;Annak érdekében, hogy az EFI környezetből indíthassunk a telepítőnek telepítenie kell a rendszerbetöltő alkalmazást pl. &lt;strong&gt;GRUB&lt;/strong&gt; vagy &lt;strong&gt;systemd-boot&lt;/strong&gt; az &lt;strong&gt;EFI Rendszer Partíción.&lt;/strong&gt; Ez automatikus kivéve ha kézi partícionálást választottál ahol neked kell kiválasztani vagy létrehozni.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>A rendszer &lt;strong&gt;BIOS&lt;/strong&gt; környezetből lett indítva. &lt;br&gt;&lt;br&gt;Azért, hogy el lehessen indítani a rendszert egy BIOS környezetből a telepítőnek telepítenie kell egy indító környezetet mint pl. &lt;strong&gt;GRUB&lt;/strong&gt;. Ez telepíthető a partíció elejére vagy a &lt;strong&gt;Master Boot Record&lt;/strong&gt;-ba. javasolt a partíciós tábla elejére (javasolt). Ez automatikus kivéve ha te kézi partícionálást választottál ahol neked kell telepíteni.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>Mester Boot Record - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>Indító partíció</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>Rendszer Partíció</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>Ne telepítsen rendszerbetöltőt</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="125"/>
        <source>%1 (%2)</source>
        <translation>%1 (%2)</translation>
    </message>
</context>
<context>
    <name>Calamares::BlankViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="69"/>
        <source>Blank Page</source>
        <translation>Üres oldal</translation>
    </message>
</context>
<context>
    <name>Calamares::DebugWindow</name>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>Tárolás</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>Feladatok</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>Modulok</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation>Típus:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation>semelyik</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation>Interfész:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation>Eszközök</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation>Hibakeresési információk</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="79"/>
        <source>Install</source>
        <translation>Telepít</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="101"/>
        <source>Done</source>
        <translation>Kész</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
        <source>Run command %1 %2</source>
        <translation>Parancs futtatása %1 %2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="61"/>
        <source>Running command %1 %2</source>
        <translation>Parancs futtatása %1 %2</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="273"/>
        <source>Running %1 operation.</source>
        <translation>Futó %1 műveletek.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="288"/>
        <source>Bad working directory path</source>
        <translation>Rossz munkakönyvtár útvonal</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="289"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>Munkakönyvtár %1 a python folyamathoz %2 nem olvasható.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="299"/>
        <source>Bad main script file</source>
        <translation>Rossz alap script fájl</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="300"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>Alap script fájl %1 a python folyamathoz %2 nem olvasható.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="376"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>Boost. Python hiba ebben a folyamatban &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Back</source>
        <translation>&amp;Vissza</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="279"/>
        <source>&amp;Next</source>
        <translation>&amp;Következő</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="288"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Mégse</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="77"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="289"/>
        <source>Cancel installation without changing the system.</source>
        <translation>Kilépés a telepítőből a rendszer megváltoztatása nélkül.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="179"/>
        <source>Calamares Initialization Failed</source>
        <translation>A Calamares előkészítése meghiúsult</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="180"/>
        <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
        <translation>A(z) %1 nem telepíthető. A Calamares nem tudta betölteni a konfigurált modulokat. Ez a probléma abból fakad, ahogy a disztribúció a Calamarest használja.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="185"/>
        <source>&lt;br/&gt;The following modules could not be loaded:</source>
        <translation>&lt;br/&gt;A következő modulok nem tölthetőek be:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="277"/>
        <source>&amp;Install</source>
        <translation>&amp;Telepítés</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="325"/>
        <source>Cancel installation?</source>
        <translation>Abbahagyod a telepítést?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="326"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>Biztos abba szeretnéd hagyni a telepítést?
Minden változtatás elveszik, ha kilépsz a telepítőből.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="331"/>
        <source>&amp;Yes</source>
        <translation>&amp;Igen</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
        <source>&amp;No</source>
        <translation>&amp;Nem</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="163"/>
        <source>&amp;Close</source>
        <translation>&amp;Bezár</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="237"/>
        <source>Continue with setup?</source>
        <translation>Folytatod a telepítéssel?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="238"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>A %1 telepítő változtatásokat fog elvégezni, hogy telepítse a következőt: %2.&lt;br/&gt;&lt;strong&gt;A változtatások visszavonhatatlanok lesznek.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="243"/>
        <source>&amp;Install now</source>
        <translation>&amp;Telepítés most</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="244"/>
        <source>Go &amp;back</source>
        <translation>Menj &amp;vissza</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="283"/>
        <source>&amp;Done</source>
        <translation>&amp;Befejez</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="284"/>
        <source>The installation is complete. Close the installer.</source>
        <translation>A telepítés befejeződött, Bezárhatod a telepítőt.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
        <source>Error</source>
        <translation>Hiba</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="161"/>
        <source>Installation Failed</source>
        <translation>Telepítés nem sikerült</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="270"/>
        <source>Unknown exception type</source>
        <translation>Ismeretlen kivétel típus</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="284"/>
        <source>unparseable Python error</source>
        <translation>nem egyeztethető Python hiba</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="324"/>
        <source>unparseable Python traceback</source>
        <translation>nem egyeztethető Python visszakövetés</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="329"/>
        <source>Unfetchable Python error.</source>
        <translation>Összehasonlíthatatlan Python hiba.</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>%1 Telepítő</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="111"/>
        <source>Show debug information</source>
        <translation>Hibakeresési információk mutatása</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;
Telepítés nem folytatható. &lt;a href=&quot;#details&quot;&gt;Részletek...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;Telepítés folytatható de néhány tulajdonság valószínűleg nem lesz elérhető.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>Ez a program fel fog tenni néhány kérdést és %2 -t telepíti a számítógépre.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>A legjobb eredményért győződjünk meg, hogy ez a számítógép:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation>Rendszer követelmények</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="131"/>
        <source>After:</source>
        <translation>Utána:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="238"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;Manuális partícionálás&lt;/strong&gt;&lt;br/&gt;Létrehozhat vagy átméretezhet partíciókat.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1001"/>
        <source>Boot loader location:</source>
        <translation>Rendszerbetöltő helye:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="945"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>%1 lesz zsugorítva %2MB méretűre és egy új %3MB méretű partíció lesz létrehozva itt %4</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="129"/>
        <source>Select storage de&amp;vice:</source>
        <translation>Válassz tároló eszközt:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="130"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="927"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1052"/>
        <source>Current:</source>
        <translation>Aktuális:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="798"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation>%1 partíció használata mint home partíció a %2 -n</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="928"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Válaszd ki a partíciót amit zsugorítani akarsz és egérrel méretezd át.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1043"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Válaszd ki a telepítésre szánt partíciót &lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1099"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>Nem található EFI partíció a rendszeren. Menj vissza a manuális partícionáláshoz és állíts be %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1108"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>A %1 EFI rendszer partíció lesz használva %2 indításához.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1116"/>
        <source>EFI system partition:</source>
        <translation>EFI rendszerpartíció:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Úgy tűnik ezen a tárolóeszközön nincs operációs rendszer. Mit szeretnél csinálni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1237"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1274"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1320"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;Lemez törlése&lt;/strong&gt;&lt;br/&gt;Ez &lt;font color=&quot;red&quot;&gt;törölni&lt;/font&gt; fogja a lemezen levő összes adatot.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Ezen a tárolóeszközön %1 található. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1241"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1292"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1316"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;Meglévő mellé telepíteni&lt;/strong&gt;&lt;br/&gt;A telepítő zsugorítani fogja a partíciót, hogy elférjen a %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1245"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1324"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a következővel: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1287"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Ez a tárolóeszköz már tartalmaz egy operációs rendszert. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1311"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>A tárolóeszközön több operációs rendszer található. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="46"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>%1 csatolás törlése partícionáláshoz</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="54"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>%1 csatolás törlése partícionáláshoz</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="191"/>
        <source>Cleared all mounts for %1</source>
        <translation>%1 minden csatolása törölve</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation>Minden ideiglenes csatolás törlése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation>Minden ideiglenes csatolás törlése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>Nem lehet lekérni az ideiglenes csatolási listát</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation>Minden ideiglenes csatolás törölve</translation>
    </message>
</context>
<context>
    <name>CommandList</name>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="127"/>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="138"/>
        <source>Could not run command.</source>
        <translation>A parancsot nem lehet futtatni.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="128"/>
        <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
        <translation>A parancs a gazdakörnyezetben fut, és ismernie kell a gyökér útvonalát, de nincs rootMountPoint megadva.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="139"/>
        <source>The command needs to know the user&apos;s name, but no username is defined.</source>
        <translation>A parancsnak tudnia kell a felhasználónevet, de az nincs megadva.</translation>
    </message>
</context>
<context>
    <name>ContextualProcessJob</name>
    <message>
        <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="117"/>
        <source>Contextual Processes Job</source>
        <translation>Környezetfüggő folyamatok feladat</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>Partíció Létrehozása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation>MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>Partíció &amp;típus:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>&amp;Elsődleges</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>K&amp;iterjesztett</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation>Fájlrendszer:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>LVM LV name</source>
        <translation>LVM LV név</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
        <source>Flags:</source>
        <translation>Zászlók:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Csatolási pont:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>Mé&amp;ret:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="72"/>
        <source>En&amp;crypt</source>
        <translation>Titkosítás</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="151"/>
        <source>Logical</source>
        <translation>Logikai</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="156"/>
        <source>Primary</source>
        <translation>Elsődleges</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="173"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="262"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>A csatolási pont már használatban van. Kérlek, válassz másikat.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>Új %2MB- os partíció létrehozása a %4 (%3) eszközön %1 fájlrendszerrel.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Új &lt;strong&gt;%2MB&lt;/strong&gt;- os partíció létrehozása a &lt;/strong&gt;%4&lt;/strong&gt; (%3) eszközön &lt;strong&gt;%1&lt;/strong&gt; fájlrendszerrel.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>Új %1 partíció létrehozása a következőn: %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>A telepítő nem tudta létrehozni a partíciót ezen a lemezen &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>Partíciós tábla létrehozása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>Új partíciós tábla létrehozásával az összes létező adat törlődni fog a lemezen.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>Milyen típusú partíciós táblát szeretnél létrehozni?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>GUID Partíciós Tábla (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>Új %1 partíciós tábla létrehozása a következőn: %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="54"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Új &lt;strong&gt;%1 &lt;/strong&gt; partíciós tábla létrehozása a következőn: &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="64"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>Új %1 partíciós tábla létrehozása a következőn: %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="82"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>A telepítőnek nem sikerült létrehoznia a partíciós táblát a lemezen %1.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
        <source>Create user %1</source>
        <translation>%1 nevű felhasználó létrehozása</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt; nevű felhasználó létrehozása.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
        <source>Creating user %1.</source>
        <translation>%1 nevű felhasználó létrehozása</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="81"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Sudoers mappa nem írható.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="85"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>Nem lehet sudoers fájlt létrehozni írásra.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="93"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>Nem lehet a sudoers fájlt &quot;chmod&quot; -olni.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="99"/>
        <source>Cannot open groups file for reading.</source>
        <translation>Nem lehet a groups fájlt megnyitni olvasásra.</translation>
    </message>
</context>
<context>
    <name>CreateVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
        <source>Create new volume group named %1.</source>
        <translation>Új kötetcsoport létrehozása: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="45"/>
        <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Új kötetcsoport létrehozása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="52"/>
        <source>Creating new volume group named %1.</source>
        <translation>Új kötetcsoport létrehozása: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="65"/>
        <source>The installer failed to create a volume group named &apos;%1&apos;.</source>
        <translation>A telepítő nem tudta létrehozni a kötetcsoportot: „%1”.</translation>
    </message>
</context>
<context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="34"/>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
        <source>Deactivate volume group named %1.</source>
        <translation>A kötetcsoport deaktiválása: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="41"/>
        <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Kötetcsoport deaktiválása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="61"/>
        <source>The installer failed to deactivate a volume group named %1.</source>
        <translation>A telepítőnek nem sikerült deaktiválnia a kötetcsoportot: %1.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
        <source>Delete partition %1.</source>
        <translation>%1 partíció törlése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>A következő partíció törlése: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
        <source>Deleting partition %1.</source>
        <translation>%1 partíció törlése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>A telepítő nem tudta törölni a %1 partíciót.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>A &lt;strong&gt;partíciós tábla&lt;/strong&gt; típusa a kiválasztott tárolóeszközön.&lt;br&gt;&lt;br&gt;Az egyetlen lehetőség a partíciós tábla változtatására ha töröljük és újra létrehozzuk a partíciós táblát, ami megsemmisít minden adatot a tárolóeszközön.&lt;br&gt;A telepítő megtartja az aktuális partíciós táblát ha csak másképp nem döntesz.&lt;br&gt;Ha nem vagy benne biztos a legtöbb modern rendszernél GPT az elterjedt.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>Az ezköz tartalmaz egy &lt;strong&gt;%1&lt;/strong&gt; partíciós táblát.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation>A választott tárolóeszköz egy &lt;strong&gt;loop&lt;/strong&gt;  eszköz.&lt;br&gt;&lt;br&gt;Ez nem egy partíciós tábla, ez egy pszeudo eszköz ami lehetővé teszi a hozzáférést egy fájlhoz, úgy mint egy blokk eszköz. Ez gyakran csak egy fájlrendszert tartalmaz.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>A telepítő &lt;strong&gt;nem talált partíciós táblát&lt;/strong&gt; a választott tárolóeszközön.&lt;br&gt;&lt;br&gt; Az eszköz nem tartalmaz partíciós táblát vagy sérült vagy  ismeretlen típusú.&lt;br&gt;  A telepítő létre tud hozni újat automatikusan vagy te magad kézi partícionálással.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;Ez az ajánlott partíciós tábla típus modern rendszerekhez ami &lt;strong&gt;EFI&lt;/strong&gt;  indító környezettel indul.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation>&lt;br&gt;&lt;br&gt;Ez a partíciós tábla típus régebbi rendszerekhez javasolt amik &lt;strong&gt;BIOS&lt;/strong&gt; indító környezetből indulnak. Legtöbb esetben azonban GPT használata javasolt. &lt;br&gt;&lt;strong&gt;Figyelem:&lt;/strong&gt; az MSDOS partíciós tábla egy régi sztenderd lényeges korlátozásokkal. &lt;br&gt;Maximum 4 &lt;em&gt;elsődleges&lt;/em&gt; partíció hozható létre és abból a 4-ből egy lehet &lt;em&gt;kiterjesztett&lt;/em&gt; partíció.</translation>
    </message>
</context>
<context>
    <name>DeviceModel</name>
    <message>
        <location filename="../src/modules/partition/core/DeviceModel.cpp" line="83"/>
        <source>%1 - %2 (%3)</source>
        <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/DeviceModel.cpp" line="89"/>
        <source>%1 - (%2)</source>
        <translation>%1 – (%2)</translation>
    </message>
</context>
<context>
    <name>DracutLuksCfgJob</name>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="131"/>
        <source>Write LUKS configuration for Dracut to %1</source>
        <translation>Dracut LUKS konfiguráció mentése ide %1</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="133"/>
        <source>Skip writing LUKS configuration for Dracut: &quot;/&quot; partition is not encrypted</source>
        <translation>Dracut LUKS konfiguráció mentésének kihagyása: &quot;/&quot; partíció nincs titkosítva.</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="149"/>
        <source>Failed to open %1</source>
        <translation>Hiba történt %1  megnyitásakor</translation>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="47"/>
        <source>Dummy C++ Job</source>
        <translation>Teszt C++ job</translation>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>Meglévő partíció szerkesztése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>Tartalom:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>&amp;megtart</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>Formázás</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>Figyelem: A partíció formázása az összes meglévő adatot törölni fogja.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Csatolási pont:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>&amp;méret:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation>MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation>&amp;fájlrendszer</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation>Zászlók:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="269"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>A csatolási pont már használatban van. Kérlek, válassz másikat.</translation>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation>Rendszer titkosítása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation>Jelszó</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation>Jelszó megerősítés</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation>Írd be ugyanazt a jelmondatot mindkét dobozban.</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="132"/>
        <source>Set partition information</source>
        <translation>Partíció információk beállítása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="156"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>%1 telepítése az &lt;strong&gt;új&lt;/strong&gt; %2 partícióra.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="160"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;Új&lt;/strong&gt; %2 partíció beállítása &lt;strong&gt;%1&lt;/strong&gt; csatolási ponttal.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="168"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>%2 telepítése %3 &lt;strong&gt;%1&lt;/strong&gt; rendszer partícióra.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="173"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>%3 partíció beállítása &lt;strong&gt;%1&lt;/strong&gt; &lt;strong&gt;%2&lt;/strong&gt; csatolási ponttal.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="185"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Rendszerbetöltő telepítése ide &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="195"/>
        <source>Setting up mount points.</source>
        <translation>Csatlakozási pontok létrehozása</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style=&quot; font-style:italic;&quot;&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Ha ez be van jelölve, akkor a rendszer azonnal újraindul, ha a &lt;span style=&quot; font-style:italic;&quot;&gt;Kész&lt;/span&gt;-re kattint, vagy bezárja a telepítőt.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
        <source>&amp;Restart now</source>
        <translation>Új&amp;raindítás most</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="51"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;Sikeres művelet.&lt;/h1&gt;&lt;br/&gt;%1 telepítve lett a számítógépére.&lt;br/&gt;Újraindítás után folytathatod az %2 éles környezetben.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="109"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation>&lt;h1&gt;A telepítés hibába ütközött.&lt;/h1&gt;&lt;br/&gt;%1 nem lett telepítve a számítógépre.&lt;br/&gt;A hibaüzenet: %2.</translation>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation>Befejezés</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation>A telepítés befejeződött.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation>A %1 telepítése elkészült.</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>Partíció formázása %1 (fájlrendszer: %2, méret: %3 MB) a %4 -on.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%3MB&lt;/strong&gt; partíció formázása &lt;strong&gt;%1&lt;/strong&gt; a következő fájlrendszerrel &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>%1 partíció formázása %2 fájlrendszerrel.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>A telepítő nem tudta formázni a %1 partíciót a %2 lemezen.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
        <source>Konsole not installed</source>
        <translation>Konsole nincs telepítve</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
        <source>Please install KDE Konsole and try again!</source>
        <translation>Kérlek telepítsd a KDE Konsole-t és próbáld újra!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>Script végrehajása: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>Szkript</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="219"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>Billentyűzet típus beállítása %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="221"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>Billentyűzet kiosztás beállítása %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>Billentyűzet</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>Területi beállítások</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>A nyelvi beállítás kihat a nyelvi és karakter beállításokra a parancssori elemeknél.&lt;br/&gt;A jelenlegi beállítás &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Mégse</translation>
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
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="89"/>
        <source>I accept the terms and conditions above.</source>
        <translation>Elfogadom a fentebbi felhasználási feltételeket.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="116"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;Licensz&lt;/h1&gt;A telepítő szabadalmaztatott szoftvert fog telepíteni. Információ a licenszben.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="119"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>Kérlek, olvasd el a fenti végfelhasználói licenszfeltételeket (EULAs)&lt;br/&gt;Ha nem értesz egyet a feltételekkel, akkor a telepítés nem folytatódik.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="125"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;Licensz&lt;/h1&gt;A telepítő szabadalmaztatott szoftvert fog telepíteni. Információ a licenszben.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="130"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>Kérlek, olvasd el a fenti végfelhasználói licenszfeltételeket (EULAs)&lt;br/&gt;Ha nem értesz egyet a feltételekkel, akkor a szabadalmaztatott program telepítése nem folytatódik és nyílt forrású program lesz telepítve helyette.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="160"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt; %2 -ból/ -ből</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="167"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;%1 grafikus driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="173"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 böngésző plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="179"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 kodek&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="185"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 csomag&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot; &gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="191"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="203"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;a licensz elolvasása&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>Licensz</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation>A rendszer területi beállítása %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation>A számok és dátumok területi beállítása %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation>Régió:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation>Zóna:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>&amp;Változtat...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>Időzóna beállítása %1/%2.&lt;br/&gt;</translation>
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
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="60"/>
        <source>Loading location data...</source>
        <translation>Hely adatok betöltése...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="175"/>
        <source>Location</source>
        <translation>Hely</translation>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="64"/>
        <source>Name</source>
        <translation>Név</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="65"/>
        <source>Description</source>
        <translation>Leírás</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="86"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation>Hálózati telepítés. (Kikapcsolva: A csomagokat nem lehet letölteni, ellenőrizd a hálózati kapcsolatot)</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="96"/>
        <source>Network Installation. (Disabled: Received invalid groups data)</source>
        <translation>Hálózati Telepítés. (Letiltva: Hibás adat csoportok fogadva)</translation>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
        <source>Package selection</source>
        <translation>Csomag választása</translation>
    </message>
</context>
<context>
    <name>PWQ</name>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="63"/>
        <source>Password is too short</source>
        <translation>Túl rövid jelszó</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="85"/>
        <source>Password is too long</source>
        <translation>Túl hosszú jelszó</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="151"/>
        <source>Password is too weak</source>
        <translation>A jelszó túl gyenge</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="158"/>
        <source>Memory allocation error when setting &apos;%1&apos;</source>
        <translation>Memóriafoglalási hiba a(z) „%1” beállításakor</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
        <source>Memory allocation error</source>
        <translation>Memóriafoglalási hiba</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
        <source>The password is the same as the old one</source>
        <translation>A jelszó ugyanaz, mint a régi</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
        <source>The password is a palindrome</source>
        <translation>A jelszó egy palindrom</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
        <source>The password differs with case changes only</source>
        <translation>A jelszó csak kis- és nagybetűben tér el</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
        <source>The password is too similar to the old one</source>
        <translation>A jelszó túlságosan hasonlít a régire</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
        <source>The password contains the user name in some form</source>
        <translation>A jelszó tartalmazza felhasználónevet valamilyen formában</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
        <source>The password contains words from the real name of the user in some form</source>
        <translation>A jelszó tartalmazza a felhasználó valódi nevét valamilyen formában</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="176"/>
        <source>The password contains forbidden words in some form</source>
        <translation>A jelszó tiltott szavakat tartalmaz valamilyen formában</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="179"/>
        <source>The password contains less than %1 digits</source>
        <translation>A jelszó kevesebb mint %1 számjegyet tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="180"/>
        <source>The password contains too few digits</source>
        <translation>A jelszó túl kevés számjegyet tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="183"/>
        <source>The password contains less than %1 uppercase letters</source>
        <translation>A jelszó kevesebb mint %1 nagybetűt tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
        <source>The password contains too few uppercase letters</source>
        <translation>A jelszó túl kevés nagybetűt tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="187"/>
        <source>The password contains less than %1 lowercase letters</source>
        <translation>A jelszó kevesebb mint %1 kisbetűt tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
        <source>The password contains too few lowercase letters</source>
        <translation>A jelszó túl kevés kisbetűt tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
        <source>The password contains less than %1 non-alphanumeric characters</source>
        <translation>A jelszó kevesebb mint %1 nem alfanumerikus karaktert tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="192"/>
        <source>The password contains too few non-alphanumeric characters</source>
        <translation>A jelszó túl kevés nem alfanumerikus karaktert tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
        <source>The password is shorter than %1 characters</source>
        <translation>A jelszó rövidebb mint %1 karakter</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
        <source>The password is too short</source>
        <translation>A jelszó túl rövid</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
        <source>The password is just rotated old one</source>
        <translation>A jelszó egy újra felhasznált régi jelszó</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
        <source>The password contains less than %1 character classes</source>
        <translation>A jelszó kevesebb mint %1 karaktert tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
        <source>The password does not contain enough character classes</source>
        <translation>A jelszó nem tartalmaz elég karakterosztályt</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
        <source>The password contains more than %1 same characters consecutively</source>
        <translation>A jelszó több mint %1 egyező karaktert tartalmaz egymás után</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
        <source>The password contains too many same characters consecutively</source>
        <translation>A jelszó túl sok egyező karaktert tartalmaz egymás után</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
        <source>The password contains more than %1 characters of the same class consecutively</source>
        <translation>A jelszó több mint %1 karaktert tartalmaz ugyanabból a karakterosztályból egymás után</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
        <source>The password contains too many characters of the same class consecutively</source>
        <translation>A jelszó túl sok karaktert tartalmaz ugyanabból a karakterosztályból egymás után</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
        <source>The password contains monotonic sequence longer than %1 characters</source>
        <translation>A jelszó %1 karakternél hosszabb monoton sorozatot tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
        <source>The password contains too long of a monotonic character sequence</source>
        <translation>A jelszó túl hosszú monoton karaktersorozatot tartalmaz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="216"/>
        <source>No password supplied</source>
        <translation>Nincs jelszó megadva</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
        <source>Cannot obtain random numbers from the RNG device</source>
        <translation>Nem nyerhetőek ki véletlenszámok az RNG eszközből</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="220"/>
        <source>Password generation failed - required entropy too low for settings</source>
        <translation>A jelszó előállítás meghiúsult – a szükséges entrópia túl alacsony a beállításokhoz</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
        <source>The password fails the dictionary check - %1</source>
        <translation>A jelszó megbukott a szótárellenőrzésen – %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="227"/>
        <source>The password fails the dictionary check</source>
        <translation>A jelszó megbukott a szótárellenőrzésen</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="231"/>
        <source>Unknown setting - %1</source>
        <translation>Ismeretlen beállítás – %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
        <source>Unknown setting</source>
        <translation>Ismeretlen beállítás</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
        <source>Bad integer value of setting - %1</source>
        <translation>Hibás egész érték a beállításnál – %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
        <source>Bad integer value</source>
        <translation>Hibás egész érték</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
        <source>Setting %1 is not of integer type</source>
        <translation>A(z) %1 beállítás nem egész típusú</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
        <source>Setting is not of integer type</source>
        <translation>A beállítás nem egész típusú</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
        <source>Setting %1 is not of string type</source>
        <translation>A(z) %1 beállítás nem karakterlánc típusú</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
        <source>Setting is not of string type</source>
        <translation>A beállítás nem karakterlánc típusú</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="261"/>
        <source>Opening the configuration file failed</source>
        <translation>A konfigurációs fájl megnyitása meghiúsult</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
        <source>The configuration file is malformed</source>
        <translation>A konfigurációs fájl rosszul formázott</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
        <source>Fatal failure</source>
        <translation>Végzetes hiba</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
        <source>Unknown error</source>
        <translation>Ismeretlen hiba</translation>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>Billentyűzet modell:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>Gépelj itt a billentyűzet teszteléséhez</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>Mi a neved?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>Milyen felhasználónévvel szeretnél bejelentkezni?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>betű-súly: normál</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Ha több mint egy személy használja a számítógépet akkor létrehozhatsz több felhasználói fiókot a telepítés után.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>Adj meg jelszót a felhasználói fiókod védelmére.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Írd be a jelszót kétszer így ellenőrizve lesznek a gépelési hibák. A jó jelszó tartalmazzon kis és nagy betűket, számokat és legalább 8 karakter hosszúságú. Ajánlott megváltoztatni rendszeres időközönként.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>Mi legyen a számítógép neve?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Ez a név lesz használva ha a számítógép látható a hálózaton.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>Jelszó megkérdezése nélküli automatikus bejelentkezés.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>Ugyanaz a jelszó használata az adminisztrátor felhasználóhoz.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>Adj meg jelszót az adminisztrátor felhasználói fiókhoz.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Írd be a jelszót kétszer így ellenőrizve lesznek a gépelési hibák.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation>Root</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation>Home</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation>Boot</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation>EFI rendszer</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation>Swap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation>Új partíció %1 -ra/ -re</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation>Új partíció</translation>
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
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="138"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="170"/>
        <source>Free Space</source>
        <translation>Szabad terület</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="142"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="174"/>
        <source>New partition</source>
        <translation>Új partíció</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="258"/>
        <source>Name</source>
        <translation>Név</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="260"/>
        <source>File System</source>
        <translation>Fájlrendszer</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="262"/>
        <source>Mount Point</source>
        <translation>Csatolási pont</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="264"/>
        <source>Size</source>
        <translation>Méret</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>Eszköz:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>&amp;Módosítások visszavonása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>Új partíciós &amp;tábla</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>Cre&amp;ate</source>
        <translation>&amp;Létrehozás</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>&amp;Szerkeszt</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>&amp;Töröl</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
        <source>New Volume Group</source>
        <translation>Új kötetcsoport</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
        <source>Resize Volume Group</source>
        <translation>Kötetcsoport átméretezése</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
        <source>Deactivate Volume Group</source>
        <translation>Kötetcsoport deaktiválása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
        <source>Remove Volume Group</source>
        <translation>Kötetcsoport eltávolítása</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
        <source>I&amp;nstall boot loader on:</source>
        <translation>Rendszerbetöltő &amp;telepítése ide:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="217"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>Biztos vagy benne, hogy létrehozol egy új partíciós táblát itt %1 ?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
        <source>Can not create new partition</source>
        <translation>Nem hozható létre új partíció</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="242"/>
        <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
        <translation>A(z) %1 lemezen lévő partíciós táblában már %2 elsődleges partíció van, és több nem adható hozzá. Helyette távolítson el egy elsődleges partíciót, és adjon hozzá egy kiterjesztett partíciót.</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="71"/>
        <source>Gathering system information...</source>
        <translation>Rendszerinformációk gyűjtése...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="122"/>
        <source>Partitions</source>
        <translation>Partíciók</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="159"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>%1 telepítése más operációs rendszer &lt;strong&gt;mellé&lt;/strong&gt; .</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>&lt;strong&gt;Lemez törlés&lt;/strong&gt;és %1 telepítés.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a következővel: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="172"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>&lt;strong&gt;Kézi&lt;/strong&gt; partícionálás.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="185"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>%1 telepítése más operációs rendszer &lt;strong&gt;mellé&lt;/strong&gt; a &lt;strong&gt;%2&lt;/strong&gt; (%3) lemezen.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="191"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation>&lt;strong&gt;%2 lemez törlése&lt;/strong&gt; (%3) és %1 telepítés.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="197"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a &lt;strong&gt;%2&lt;/strong&gt; lemezen(%3) a következővel: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="204"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation>&lt;strong&gt;Kézi&lt;/strong&gt; telepítés a &lt;strong&gt;%1&lt;/strong&gt; (%2) lemezen.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="212"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation>Lemez &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="240"/>
        <source>Current:</source>
        <translation>Aktuális:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="257"/>
        <source>After:</source>
        <translation>Utána:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>No EFI system partition configured</source>
        <translation>Nincs EFI rendszer partíció beállítva</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="401"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation>EFI rendszerpartíciónak léteznie kell %1 indításához.&lt;br/&gt;&lt;br/&gt; Az EFI rendszer beállításához lépj vissza és hozz létre FAT32 fájlrendszert &lt;strong&gt;esp&lt;/strong&gt; zászlóval és &lt;strong&gt;%2&lt;/strong&gt; csatolási ponttal beállítva.&lt;br/&gt;&lt;br/&gt; Folytathatod a telepítést EFI rendszerpartíció létrehozása nélkül is, de lehet, hogy a rendszer nem indul majd.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>EFI system partition flag not set</source>
        <translation>EFI partíciós zászló nincs beállítva</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="415"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation>EFI rendszerpartíciónak léteznie kell %1 indításához.&lt;br/&gt;&lt;br/&gt; A csatolási pont &lt;strong&gt;%2&lt;/strong&gt; beállítása sikerült a partíción de a zászló nincs beállítva. A beálíltásához lépj vissza szerkeszteni a partíciót..&lt;br/&gt;&lt;br/&gt; Folytathatod a telepítést zászló beállítása nélkül is, de lehet, hogy a rendszer nem indul el majd.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="450"/>
        <source>Boot partition not encrypted</source>
        <translation>Indító partíció nincs titkosítva</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="451"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation>Egy külön indító partíció lett beállítva egy titkosított root partícióval, de az indító partíció nincs titkosítva.br/&gt;&lt;br/&gt;Biztonsági aggályok merülnek fel ilyen beállítás mellet, mert fontos fájlok nem titkosított partíción vannak tárolva. &lt;br/&gt;Ha szeretnéd, folytathatod így, de a fájlrendszer zárolása meg fog történni az indítás után. &lt;br/&gt; Az indító partíció titkosításához lépj vissza és az újra létrehozáskor válaszd a &lt;strong&gt;Titkosít&lt;/strong&gt; opciót.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfJob</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
        <source>Plasma Look-and-Feel Job</source>
        <translation>Plasma kinézet feladat</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
        <source>Could not select KDE Plasma Look-and-Feel package</source>
        <translation>A KDE Plasma kinézeti csomag nem válaszható ki</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfPage</name>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="20"/>
        <source>Placeholder</source>
        <translation>Helytartó</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="67"/>
        <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
        <translation>Válasszon egy kinézetet a KDE Plasma asztali környezethez. Ki is hagyhatja ezt a lépést, és beállíthatja a kinézetet, ha a telepítés elkészült. A kinézetválasztóra kattintva élő előnézetet kaphat a kinézetről.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfViewStep</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
        <source>Look-and-Feel</source>
        <translation>Kinézet</translation>
    </message>
</context>
<context>
    <name>PreserveFiles</name>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="85"/>
        <source>Saving files for later ...</source>
        <translation>Fájlok mentése későbbre …</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="123"/>
        <source>No files configured to save for later.</source>
        <translation>Nincsenek fájlok beállítva elmentésre későbbre</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="177"/>
        <source>Not all of the configured files could be preserved.</source>
        <translation>Nem az összes beállított fájl örízhető meg.</translation>
    </message>
</context>
<context>
    <name>ProcessResult</name>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="271"/>
        <source>
There was no output from the command.</source>
        <translation>
A parancsnak nem volt kimenete.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="272"/>
        <source>
Output:
</source>
        <translation>
Kimenet:
</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="275"/>
        <source>External command crashed.</source>
        <translation>Külső parancs összeomlott.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="276"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
        <translation>Parancs &lt;i&gt;%1&lt;/i&gt; összeomlott.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="281"/>
        <source>External command failed to start.</source>
        <translation>A külső parancsot nem sikerült elindítani.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="282"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
        <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancsot nem sikerült elindítani.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="286"/>
        <source>Internal error when starting command.</source>
        <translation>Belső hiba a parancs végrehajtásakor.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="287"/>
        <source>Bad parameters for process job call.</source>
        <translation>Hibás paraméterek a folyamat hívásához.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="290"/>
        <source>External command failed to finish.</source>
        <translation>Külső parancs nem fejeződött be.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="291"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
        <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancsot nem sikerült befejezni %2 másodperc alatt.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="297"/>
        <source>External command finished with errors.</source>
        <translation>A külső parancs hibával fejeződött be.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="298"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
        <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancs hibakóddal lépett ki: %2.</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>Alapértelmezett billentyűzet</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>Alapértelmezett</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="207"/>
        <source>unknown</source>
        <translation>ismeretlen</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="209"/>
        <source>extended</source>
        <translation>kiterjesztett</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="211"/>
        <source>unformatted</source>
        <translation>formázatlan</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="213"/>
        <source>swap</source>
        <translation>Swap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>Nem particionált, vagy ismeretlen partíció</translation>
    </message>
</context>
<context>
    <name>RemoveVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="34"/>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
        <source>Remove Volume Group named %1.</source>
        <translation>A kötetcsoport eltávolítása: %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="41"/>
        <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Kötetcsoport eltávolítása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="61"/>
        <source>The installer failed to remove a volume group named &apos;%1&apos;.</source>
        <translation>A telepítő nem tudta eltávolítani a kötetcsoportot: „%1”.</translation>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation>Válaszd ki az telepítés helyét %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Figyelmeztetés: &lt;/font&gt;minden fájl törölve lesz a kiválasztott partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>A kiválasztott elem nem tűnik érvényes partíciónak.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1 nem telepíthető, kérlek válassz egy létező partíciót.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1 nem telepíthető a kiterjesztett partícióra. Kérlek, válassz egy létező elsődleges vagy logikai partíciót.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>Nem lehet telepíteni a következőt %1 erre a partícióra.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation>Adat partíció (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation>Ismeretlen rendszer partíció (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation>%1 rendszer partíció (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;A partíció %1 túl kicsi a következőhöz %2. Kérlek, válassz egy legalább %3 GB- os partíciót.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Az EFI rendszerpartíció nem található a rendszerben. Kérlek, lépj vissza és állítsd be manuális partícionálással %1- et.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 installálva lesz a következőre: %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Figyelmeztetés: &lt;/font&gt;a partíción %2 minden törölve lesz.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>A %2 indításához az EFI rendszer partíciót használja a következőn: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation>EFI rendszer partíció:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="68"/>
        <source>Gathering system information...</source>
        <translation>Rendszerinformációk gyűjtése...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>has at least %1 GB available drive space</source>
        <translation>Legalább %1 GB lemezterület elérhető</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="120"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>Nincs elég lemezterület. Legalább %1GB szükséges.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="128"/>
        <source>has at least %1 GB working memory</source>
        <translation>Legalább %1 GB elérhető memória</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="130"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>A rendszernek nincs elég memóriája. Legalább %1 GB szükséges.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="138"/>
        <source>is plugged in to a power source</source>
        <translation>csatlakoztatva van külső áramforráshoz</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="139"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>A rendszer nincs csatlakoztatva külső áramforráshoz</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="146"/>
        <source>is connected to the Internet</source>
        <translation>csatlakozik az internethez</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="147"/>
        <source>The system is not connected to the Internet.</source>
        <translation>A rendszer nem csatlakozik az internethez.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="155"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>A telepítő nem adminisztrátori jogokkal fut.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="163"/>
        <source>The screen is too small to display the installer.</source>
        <translation>A képernyőméret túl kicsi a telepítő megjelenítéséhez.</translation>
    </message>
</context>
<context>
    <name>ResizeFSJob</name>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="130"/>
        <source>Resize Filesystem Job</source>
        <translation>Fájlrendszer átméretezési feladat</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="238"/>
        <source>Invalid configuration</source>
        <translation>Érvénytelen konfiguráció</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="239"/>
        <source>The file-system resize job has an invalid configuration and will not run.</source>
        <translation>A fájlrendszer átméretezési feladat konfigurációja érvénytelen, és nem fog futni.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="253"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="263"/>
        <source>KPMCore not Available</source>
        <translation>A KPMCore nem érhető el</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="254"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="264"/>
        <source>Calamares cannot start KPMCore for the file-system resize job.</source>
        <translation>A Calamares nem tudja elindítani a KPMCore-t a fájlrendszer átméretezési feladathoz.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="272"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="281"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="294"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="303"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="320"/>
        <source>Resize Failed</source>
        <translation>Az átméretezés meghiúsult</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="273"/>
        <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
        <translation>A(z) %1 fájlrendszer nem található a rendszeren, és nem méretezhető át.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="274"/>
        <source>The device %1 could not be found in this system, and cannot be resized.</source>
        <translation>A(z) %1 eszköz nem található a rendszeren, és nem méretezhető át.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="282"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="295"/>
        <source>The filesystem %1 cannot be resized.</source>
        <translation>A(z) %1 fájlrendszer nem méretezhető át.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="283"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="296"/>
        <source>The device %1 cannot be resized.</source>
        <translation>A(z) %1 eszköz nem méretezhető át.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="304"/>
        <source>The filesystem %1 must be resized, but cannot.</source>
        <translation>A(z) %1 fájlrendszert át kell méretezni, de nem lehet.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="305"/>
        <source>The device %1 must be resized, but cannot</source>
        <translation>A(z) %1 eszközt át kell méretezni, de nem lehet</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
        <source>Resize partition %1.</source>
        <translation>A %1 partíció átméretezése.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation>&lt;strong&gt;%2MB&lt;/strong&gt; partíció átméretezése &lt;strong&gt;%1&lt;/strong a következőre:&lt;strong&gt;%3MB&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation>%2MB partíció átméretezése %1 -ról/ -ről %3MB- ra/ -re.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>A telepítő nem tudta átméretezni a(z) %1 partíciót a(z) &apos;%2&apos; lemezen.</translation>
    </message>
</context>
<context>
    <name>ResizeVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="55"/>
        <source>Resize volume group named %1 from %2 to %3.</source>
        <translation>A(z) %1 kötet átméretezése ekkoráról: %2, ekkorára: %3.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
        <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation>A(z) &lt;strong&gt;%1&lt;/strong&gt; kötet átméretezése ekkoráról: &lt;strong&gt;%2&lt;/strong&gt;, ekkorára: &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="70"/>
        <source>The installer failed to resize a volume group named &apos;%1&apos;.</source>
        <translation>A telepítő nem tudta átméretezni a kötetcsoportot: „%1”.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation>Eszközök keresése...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
        <source>Partitioning</source>
        <translation>Partícionálás</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="38"/>
        <source>Set hostname %1</source>
        <translation>Hálózati név beállítása a %1 -en</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="45"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Hálózati név beállítása a következőhöz: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="52"/>
        <source>Setting hostname %1.</source>
        <translation>Hálózati név beállítása a %1 -hez</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="62"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="69"/>
        <source>Internal Error</source>
        <translation>Belső hiba</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="76"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="87"/>
        <source>Cannot write hostname to target system</source>
        <translation>Nem lehet a hálózati nevet írni a célrendszeren</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>Billentyűzet beállítása %1, elrendezés %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>Hiba történt a billentyűzet virtuális konzolba való beállításakor</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="326"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="332"/>
        <source>Failed to write to %1</source>
        <translation>Hiba történt %1 -re történő íráskor</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>Hiba történt a billentyűzet X11- hez való beállításakor</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation>Hiba történt a billentyűzet konfiguráció alapértelmezett /etc/default mappába valló elmentésekor.</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
        <source>Set flags on partition %1.</source>
        <translation>Zászlók beállítása a partíción %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation>Jelzők beállítása a %1MB %2 partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Set flags on new partition.</source>
        <translation>Jelzők beállítása az új partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Zászlók törlése a partíción: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Jelzők törlése a %1MB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
        <source>Clear flags on new partition.</source>
        <translation>Jelzők törlése az új partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Zászlók beállítása &lt;strong&gt;%1&lt;/strong&gt; ,mint &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="85"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation>Jelzők beállítása %1MB &lt;strong&gt;%2&lt;/strong&gt; a partíción mint &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Jelző beállítása mint &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Zászlók törlése a partíción: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Jelzők törlése a %1MB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
        <source>Clearing flags on new partition.</source>
        <translation>jelzők törlése az új partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Zászlók beállítása &lt;strong&gt;%2&lt;/strong&gt; a &lt;strong&gt;%1&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Jelzők beállítása &lt;strong&gt;%3&lt;/strong&gt; a %1MB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation>Jelzők beállítása az új &lt;strong&gt;%1&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="144"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>A telepítőnek nem sikerült a zászlók beállítása a partíción %1.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation>%1 felhasználó jelszó beállítása</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation>%1 felhasználói jelszó beállítása</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation>Rossz célrendszer elérési út</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation>rootMountPoint is %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="123"/>
        <source>Cannot disable root account.</source>
        <translation>A root account- ot nem lehet inaktiválni.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="124"/>
        <source>passwd terminated with error code %1.</source>
        <translation>passwd megszakítva %1 hibakóddal.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="139"/>
        <source>Cannot set password for user %1.</source>
        <translation>Nem lehet a %1 felhasználó jelszavát beállítani.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation>usermod megszakítva %1 hibakóddal.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>Időzóna beállítása %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>A választott időzóna útvonal nem hozzáférhető.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>Rossz elérési út: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>Nem lehet az időzónát beállítani.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>Link létrehozása nem sikerült: %1, link év: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation>Nem lehet beállítani az időzónát .</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>Nem lehet megnyitni írásra: /etc/timezone</translation>
    </message>
</context>
<context>
    <name>ShellProcessJob</name>
    <message>
        <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="51"/>
        <source>Shell Processes Job</source>
        <translation>Parancssori folyamatok feladat</translation>
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
        <location filename="../src/modules/summary/SummaryPage.cpp" line="49"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation>Ez áttekintése annak, hogy mi fog történni, ha megkezded a telepítést.</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>Összefoglalás</translation>
    </message>
</context>
<context>
    <name>TrackingInstallJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
        <source>Installation feedback</source>
        <translation>Visszajelzés a telepítésről</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="53"/>
        <source>Sending installation feedback.</source>
        <translation>Telepítési visszajelzés küldése.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="88"/>
        <source>Internal error in install-tracking.</source>
        <translation>Hiba a telepítő nyomkövetésben.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="89"/>
        <source>HTTP request timed out.</source>
        <translation>HTTP kérés ideje lejárt.</translation>
    </message>
</context>
<context>
    <name>TrackingMachineNeonJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="104"/>
        <source>Machine feedback</source>
        <translation>Gépi visszajelzés</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="114"/>
        <source>Configuring machine feedback.</source>
        <translation>Gépi visszajelzés konfigurálása.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="133"/>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
        <source>Error in machine feedback configuration.</source>
        <translation>Hiba a gépi visszajelzés konfigurálásában.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="134"/>
        <source>Could not configure machine feedback correctly, script error %1.</source>
        <translation>Gépi visszajelzés konfigurálása nem megfelelő, script hiba %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="137"/>
        <source>Could not configure machine feedback correctly, Calamares error %1.</source>
        <translation>Gépi visszajelzés konfigurálása nem megfelelő,.
Calamares hiba %1.</translation>
    </message>
</context>
<context>
    <name>TrackingPage</name>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
        <source>Placeholder</source>
        <translation>Helytartó</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=&quot; font-weight:600;&quot;&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Ezt kiválasztva te&lt;span style=&quot; font-weight:600;&quot;&gt;nem tudsz küldeni információt&lt;/span&gt;a telepítésről.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="123"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="185"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="247"/>
        <source>TextLabel</source>
        <translation>Szöveges címke</translation>
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
        <translation>&lt;html&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;placeholder&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#2980b9;&quot;&gt; Kattints ide bővebb információért a felhasználói visszajelzésről &lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;head/&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
        <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
        <translation>A telepítés nyomkövetése %1 segít látni, hogy hány felhasználója van, milyen eszközre , %1 és (az alábbi utolsó két opcióval), folyamatosan kapunk információt az előnyben részesített alkalmazásokról. Hogy lásd mi lesz elküldve kérlek kattints a súgó ikonra a mező mellett.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="45"/>
        <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
        <translation>Ezt kiválasztva információt fogsz küldeni a telepítésről és a számítógépről. Ez az információ &lt;b&gt;csak egyszer lesz &lt;/b&gt;elküldve telepítés után.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="46"/>
        <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
        <translation>Ezt kiválasztva információt fogsz küldeni &lt;b&gt;időközönként&lt;/b&gt; a telepítésről, számítógépről, alkalmazásokról ide %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="47"/>
        <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
        <translation>Ezt kiválasztva&lt;b&gt; rendszeresen&lt;/b&gt; fogsz információt küldeni a telepítésről, számítógépről, alkalmazásokról és használatukról ide %1.</translation>
    </message>
</context>
<context>
    <name>TrackingViewStep</name>
    <message>
        <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="59"/>
        <source>Feedback</source>
        <translation>Visszacsatolás</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="289"/>
        <source>Your username is too long.</source>
        <translation>A felhasználónév túl hosszú.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="295"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>A felhasználónév érvénytelen karaktereket tartalmaz. Csak kis kezdőbetűk és számok érvényesek.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too short.</source>
        <translation>A hálózati név túl rövid.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="339"/>
        <source>Your hostname is too long.</source>
        <translation>A hálózati név túl hosszú.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="345"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>A hálózati név érvénytelen karaktereket tartalmaz. Csak betűk, számok és kötőjel érvényes.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="373"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="417"/>
        <source>Your passwords do not match!</source>
        <translation>A két jelszó nem egyezik!</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="53"/>
        <source>Users</source>
        <translation>Felhasználók</translation>
    </message>
</context>
<context>
    <name>VolumeGroupBaseDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
        <source>VolumeGroupDialog</source>
        <translation>Kötetcsoport párbeszédablak</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
        <source>List of Physical Volumes</source>
        <translation>Fizikai kötetek listája</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
        <source>Volume Group Name:</source>
        <translation>Kötetcsoport neve:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
        <source>Volume Group Type:</source>
        <translation>Kötetcsoport típusa:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
        <source>Physical Extent Size:</source>
        <translation>Fizikai kiterjedés mérete:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
        <source> MiB</source>
        <translation>MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
        <source>Total Size:</source>
        <translation>Teljes méret:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="92"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="112"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="132"/>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="152"/>
        <source>---</source>
        <translation>---</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
        <source>Used Size:</source>
        <translation>Használt méret:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
        <source>Total Sectors:</source>
        <translation>Szektorok összesen:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
        <source>Quantity of LVs:</source>
        <translation>Logkai kötetek száma:</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation>Adatlap</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>&amp;Nyelv:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>&amp;Kiadási megjegyzések</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>&amp;Ismert hibák</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>&amp;Támogatás</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>&amp;Névjegy</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Üdvözlet a %1 telepítőben.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Üdvözlet a Calamares %1 telepítőjében.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation>A %1 telepítőről</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Köszönet: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg és a &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares fordítócsapat&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;A &lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; fejlesztését a &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; támogatja.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="290"/>
        <source>%1 support</source>
        <translation>%1 támogatás</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="52"/>
        <source>Welcome</source>
        <translation>Üdvözlet</translation>
    </message>
</context>
</TS>
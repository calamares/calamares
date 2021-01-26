<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="hu" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="62"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>A rendszer &lt;strong&gt;indító környezete.&lt;/strong&gt; &lt;br&gt;&lt;br&gt;Régebbi x86 alapú rendszerek csak &lt;strong&gt;BIOS&lt;/strong&gt;&lt;br&gt;-t támogatják. A modern rendszerek gyakran &lt;strong&gt;EFI&lt;/strong&gt;-t használnak, de lehet, hogy BIOS-ként látható ha kompatibilitási módban fut az indító környezet. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="72"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>A rendszer &lt;strong&gt;EFI&lt;/strong&gt; indító környezettel lett indítva.&lt;br&gt;&lt;br&gt;Annak érdekében, hogy az EFI környezetből indíthassunk a telepítőnek telepítenie kell a rendszerbetöltő alkalmazást pl. &lt;strong&gt;GRUB&lt;/strong&gt; vagy &lt;strong&gt;systemd-boot&lt;/strong&gt; az &lt;strong&gt;EFI Rendszer Partíción.&lt;/strong&gt; Ez automatikus kivéve ha kézi partícionálást választottál ahol neked kell kiválasztani vagy létrehozni.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="84"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>A rendszer &lt;strong&gt;BIOS&lt;/strong&gt; környezetből lett indítva. &lt;br&gt;&lt;br&gt;Azért, hogy el lehessen indítani a rendszert egy BIOS környezetből a telepítőnek telepítenie kell egy indító környezetet mint pl. &lt;strong&gt;GRUB&lt;/strong&gt;. Ez telepíthető a partíció elejére vagy a &lt;strong&gt;Master Boot Record&lt;/strong&gt;-ba. javasolt a partíciós tábla elejére (javasolt). Ez automatikus kivéve ha te kézi partícionálást választottál ahol neked kell telepíteni.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="58"/>
      <source>Master Boot Record of %1</source>
      <translation>Mester Boot Record - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="91"/>
      <source>Boot Partition</source>
      <translation>Indító partíció</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="98"/>
      <source>System Partition</source>
      <translation>Rendszer Partíció</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="128"/>
      <source>Do not install a boot loader</source>
      <translation>Ne telepítsen rendszerbetöltőt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="146"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="61"/>
      <source>Blank Page</source>
      <translation>Üres oldal</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>Tárolás</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>Feladatok</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Modulok</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Típus:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>semelyik</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Interfész:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="97"/>
      <source>Tools</source>
      <translation>Eszközök</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="110"/>
      <source>Reload Stylesheet</source>
      <translation>Stílusok újratöltése</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="117"/>
      <source>Widget Tree</source>
      <translation>Modul- fa</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="217"/>
      <source>Debug information</source>
      <translation>Hibakeresési információk</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Set up</source>
      <translation>Összeállítás</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Install</source>
      <translation>Telepít</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Művelet nem sikerült (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Kifejezetten kért programozott műveleti hiba.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="196"/>
      <source>Done</source>
      <translation>Kész</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Mintapélda (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source>Run command '%1' in target system.</source>
      <translation>'%1' parancs futtatása a cél rendszeren.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source> Run command '%1'.</source>
      <translation>'%1' parancs futtatása.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="50"/>
      <source>Running command %1 %2</source>
      <translation>Parancs futtatása %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="192"/>
      <source>Running %1 operation.</source>
      <translation>Futó %1 műveletek.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="221"/>
      <source>Bad working directory path</source>
      <translation>Rossz munkakönyvtár útvonal</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="222"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Munkakönyvtár %1 a python folyamathoz %2 nem olvasható.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="228"/>
      <source>Bad main script file</source>
      <translation>Rossz alap script fájl</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="229"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Alap script fájl %1 a python folyamathoz %2 nem olvasható.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="297"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost. Python hiba ebben a folyamatban "%1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="67"/>
      <source>Loading ...</source>
      <translation>Betöltés ...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="88"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML lépés &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="268"/>
      <source>Loading failed.</source>
      <translation>A betöltés sikertelen.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="94"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>Követelmények ellenőrzése a &lt;i&gt;%1&lt;/i&gt;modulhoz kész.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="115"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Várakozás a %n modulokra.</numerusform>
        <numerusform>Várakozás %n modulokra. </numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="116"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n másodperc)</numerusform>
        <numerusform>(%n másodperc)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="121"/>
      <source>System-requirements checking is complete.</source>
      <translation>Rendszerkövetelmények ellenőrzése kész.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Setup Failed</source>
      <translation>Telepítési hiba</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Installation Failed</source>
      <translation>Telepítés nem sikerült</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="151"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="164"/>
      <source>Error</source>
      <translation>Hiba</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="171"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="518"/>
      <source>&amp;Yes</source>
      <translation>&amp;Igen</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="172"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>&amp;No</source>
      <translation>&amp;Nem</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="178"/>
      <source>&amp;Close</source>
      <translation>&amp;Bezár</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>Install Log Paste URL</source>
      <translation>Telepítési napló beillesztési URL-je.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="208"/>
      <source>Calamares Initialization Failed</source>
      <translation>A Calamares előkészítése meghiúsult</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="209"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>A(z) %1 nem telepíthető. A Calamares nem tudta betölteni a konfigurált modulokat. Ez a probléma abból fakad, ahogy a disztribúció a Calamarest használja.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="215"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;A következő modulok nem tölthetőek be:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with setup?</source>
      <translation>Folytatod a telepítéssel?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with installation?</source>
      <translation>Folytatja a telepítést?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="329"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>A %1 telepítő változtatásokat fog végrehajtani a lemezen a %2 telepítéséhez. &lt;br/&gt;&lt;strong&gt;Ezután már nem tudja visszavonni a változtatásokat.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>A %1 telepítő változtatásokat fog elvégezni, hogy telepítse a következőt: %2.&lt;br/&gt;&lt;strong&gt;A változtatások visszavonhatatlanok lesznek.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Telepítés most</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Install now</source>
      <translation>&amp;Telepítés most</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>Go &amp;back</source>
      <translation>Menj &amp;vissza</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Set up</source>
      <translation>&amp;Telepítés</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Install</source>
      <translation>&amp;Telepítés</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="394"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Telepítés sikerült. Zárja be a telepítőt.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>A telepítés befejeződött, Bezárhatod a telepítőt.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Telepítés megszakítása a rendszer módosítása nélkül.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Kilépés a telepítőből a rendszer megváltoztatása nélkül.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>&amp;Next</source>
      <translation>&amp;Következő</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="413"/>
      <source>&amp;Back</source>
      <translation>&amp;Vissza</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Done</source>
      <translation>&amp;Befejez</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="438"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Mégse</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel setup?</source>
      <translation>Megszakítja a telepítést?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel installation?</source>
      <translation>Abbahagyod a telepítést?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="512"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Valóban megszakítod a telepítési eljárást?
A telepítő ki fog lépni és minden változtatás elveszik.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Biztos abba szeretnéd hagyni a telepítést?
Minden változtatás elveszik, ha kilépsz a telepítőből.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="288"/>
      <source>Unknown exception type</source>
      <translation>Ismeretlen kivétel típus</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="306"/>
      <source>unparseable Python error</source>
      <translation>nem egyeztethető Python hiba</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="350"/>
      <source>unparseable Python traceback</source>
      <translation>nem egyeztethető Python visszakövetés</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="357"/>
      <source>Unfetchable Python error.</source>
      <translation>Összehasonlíthatatlan Python hiba.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="25"/>
      <source>Install log posted to:
%1</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="101"/>
      <source>Show debug information</source>
      <translation>Hibakeresési információk mutatása</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="155"/>
      <source>&amp;Back</source>
      <translation>&amp;Vissza</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="167"/>
      <source>&amp;Next</source>
      <translation>&amp;Következő</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="180"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Mégse</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="304"/>
      <source>%1 Setup Program</source>
      <translation>%1 Program telepítése</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="305"/>
      <source>%1 Installer</source>
      <translation>%1 Telepítő</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="37"/>
      <source>Gathering system information...</source>
      <translation>Rendszerinformációk gyűjtése...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="120"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Válassz tároló eszközt:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="121"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1092"/>
      <source>Current:</source>
      <translation>Aktuális:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="122"/>
      <source>After:</source>
      <translation>Utána:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="299"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Manuális partícionálás&lt;/strong&gt;&lt;br/&gt;Létrehozhat vagy átméretezhet partíciókat.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="822"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>%1 partíció használata mint home partíció a %2 -n</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Válaszd ki a partíciót amit zsugorítani akarsz és egérrel méretezd át.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="975"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 zsugorítva lesz %2MiB -re és új %3MiB partíció lesz létrehozva itt %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1031"/>
      <source>Boot loader location:</source>
      <translation>Rendszerbetöltő helye:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1083"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Válaszd ki a telepítésre szánt partíciót &lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1142"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Nem található EFI partíció a rendszeren. Menj vissza a manuális partícionáláshoz és állíts be %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1150"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>A %1 EFI rendszer partíció lesz használva %2 indításához.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1158"/>
      <source>EFI system partition:</source>
      <translation>EFI rendszerpartíció:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1291"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Úgy tűnik ezen a tárolóeszközön nincs operációs rendszer. Mit szeretnél csinálni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1333"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1355"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1380"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Lemez törlése&lt;/strong&gt;&lt;br/&gt;Ez &lt;font color="red"&gt;törölni&lt;/font&gt; fogja a lemezen levő összes adatot.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1329"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1351"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1376"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Meglévő mellé telepíteni&lt;/strong&gt;&lt;br/&gt;A telepítő zsugorítani fogja a partíciót, hogy elférjen a %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1304"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1338"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1359"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1384"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a következővel: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1323"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Ezen a tárolóeszközön %1 található. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1346"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Ez a tárolóeszköz már tartalmaz egy operációs rendszert. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1371"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>A tárolóeszközön több operációs rendszer található. Mit szeretnél tenni?&lt;br/&gt;Lehetőséged lesz átnézni és megerősíteni a választásod mielőtt bármilyen változtatás történik a tárolóeszközön.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1443"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1466"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1471"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1598"/>
      <source>No Swap</source>
      <translation>Swap nélkül</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1606"/>
      <source>Reuse Swap</source>
      <translation>Swap újrahasználata</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1609"/>
      <source>Swap (no Hibernate)</source>
      <translation>Swap (nincs hibernálás)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1612"/>
      <source>Swap (with Hibernate)</source>
      <translation>Swap (hibernálással)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1615"/>
      <source>Swap to file</source>
      <translation>Swap fájlba</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="42"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>%1 csatolás törlése partícionáláshoz</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="49"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>%1 csatolás törlése partícionáláshoz</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="224"/>
      <source>Cleared all mounts for %1</source>
      <translation>%1 minden csatolása törölve</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="32"/>
      <source>Clear all temporary mounts.</source>
      <translation>Minden ideiglenes csatolás törlése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="39"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Minden ideiglenes csatolás törlése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="51"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Nem lehet lekérni az ideiglenes csatolási listát</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="92"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Minden ideiglenes csatolás törölve</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="142"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>Could not run command.</source>
      <translation>A parancsot nem lehet futtatni.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="143"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>A parancs a gazdakörnyezetben fut, és ismernie kell a gyökér útvonalát, de nincs rootMountPoint megadva.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="156"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>A parancsnak tudnia kell a felhasználónevet, de az nincs megadva.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="326"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Billentyűzet típus beállítása %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="333"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Billentyűzet kiosztás beállítása %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="334"/>
      <source>Set timezone to %1/%2.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="372"/>
      <source>The system language will be set to %1.</source>
      <translation>A rendszer területi beállítása %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="379"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>A számok és dátumok területi beállítása %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="38"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="40"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Hálózati Telepítés. (Letiltva: Hibás adat csoportok fogadva)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="42"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="44"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Hálózati telepítés. (Kikapcsolva: A csomagokat nem lehet letölteni, ellenőrizd a hálózati kapcsolatot)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="50"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez. &lt;br/&gt;A telepítés nem folytatható. &lt;a href="#details"&gt;Részletek...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="54"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;
Telepítés nem folytatható. &lt;a href="#details"&gt;Részletek...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="61"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Ez a számítógép nem felel meg néhány követelménynek a %1 telepítéséhez. &lt;br/&gt;A telepítés folytatható de előfordulhat néhány képesség nem lesz elérhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="65"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;Telepítés folytatható de néhány tulajdonság valószínűleg nem lesz elérhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="75"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Ez a program fel fog tenni néhány kérdést és %2 -t telepíti a számítógépre.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="244"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="245"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="250"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="251"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="212"/>
      <source>Your username is too long.</source>
      <translation>A felhasználónév túl hosszú.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="218"/>
      <source>'%1' is not allowed as username.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="225"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="229"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="274"/>
      <source>Your hostname is too short.</source>
      <translation>A hálózati név túl rövid.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="278"/>
      <source>Your hostname is too long.</source>
      <translation>A hálózati név túl hosszú.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="284"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="290"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="527"/>
      <source>Your passwords do not match!</source>
      <translation>A két jelszó nem egyezik!</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="119"/>
      <source>Contextual Processes Job</source>
      <translation>Környezetfüggő folyamatok feladat</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Partíció Létrehozása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>Mé&amp;ret:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Partíció &amp;típus:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>&amp;Primary</source>
      <translation>&amp;Elsődleges</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>K&amp;iterjesztett</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>Fájlrendszer:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM LV név</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Csatolási pont:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="192"/>
      <source>Flags:</source>
      <translation>Zászlók:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
      <source>En&amp;crypt</source>
      <translation>Titkosítás</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="161"/>
      <source>Logical</source>
      <translation>Logikai</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="166"/>
      <source>Primary</source>
      <translation>Elsődleges</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="185"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="265"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>A csatolási pont már használatban van. Kérlek, válassz másikat.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="38"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Új partíció létrehozása %2MiB partíción a %4 (%3) %1 fájlrendszerrel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="49"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Új &lt;strong&gt;%2MiB &lt;/strong&gt;partíció létrehozása itt &lt;strong&gt;%4&lt;/strong&gt; (%3) fájlrendszer típusa &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="61"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Új %1 partíció létrehozása a következőn: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="73"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>A telepítő nem tudta létrehozni a partíciót ezen a lemezen '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Partíciós tábla létrehozása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Új partíciós tábla létrehozásával az összes létező adat törlődni fog a lemezen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Milyen típusú partíciós táblát szeretnél létrehozni?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID Partíciós Tábla (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="39"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Új %1 partíciós tábla létrehozása a következőn: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Új &lt;strong&gt;%1 &lt;/strong&gt; partíciós tábla létrehozása a következőn: &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="57"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Új %1 partíciós tábla létrehozása a következőn: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="75"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>A telepítőnek nem sikerült létrehoznia a partíciós táblát a lemezen %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="36"/>
      <source>Create user %1</source>
      <translation>%1 nevű felhasználó létrehozása</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="43"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; nevű felhasználó létrehozása.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="126"/>
      <source>Preserving home directory</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="143"/>
      <source>Creating user %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="151"/>
      <source>Configuring user %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
      <source>Setting file permissions</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <translation>Kötetcsoport létrehozása</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="31"/>
      <source>Create new volume group named %1.</source>
      <translation>Új kötetcsoport létrehozása: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Új kötetcsoport létrehozása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Creating new volume group named %1.</source>
      <translation>Új kötetcsoport létrehozása: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="55"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>A telepítő nem tudta létrehozni a kötetcsoportot: „%1”.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="36"/>
      <source>Deactivate volume group named %1.</source>
      <translation>A kötetcsoport deaktiválása: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="30"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Kötetcsoport deaktiválása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>A telepítőnek nem sikerült deaktiválnia a kötetcsoportot: %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="31"/>
      <source>Delete partition %1.</source>
      <translation>%1 partíció törlése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="38"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>A következő partíció törlése: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="45"/>
      <source>Deleting partition %1.</source>
      <translation>%1 partíció törlése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>A telepítő nem tudta törölni a %1 partíciót.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="97"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Az ezköz tartalmaz egy &lt;strong&gt;%1&lt;/strong&gt; partíciós táblát.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>A választott tárolóeszköz egy &lt;strong&gt;loop&lt;/strong&gt;  eszköz.&lt;br&gt;&lt;br&gt;Ez nem egy partíciós tábla, ez egy pszeudo eszköz ami lehetővé teszi a hozzáférést egy fájlhoz, úgy mint egy blokk eszköz. Ez gyakran csak egy fájlrendszert tartalmaz.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="111"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>A telepítő &lt;strong&gt;nem talált partíciós táblát&lt;/strong&gt; a választott tárolóeszközön.&lt;br&gt;&lt;br&gt; Az eszköz nem tartalmaz partíciós táblát vagy sérült vagy  ismeretlen típusú.&lt;br&gt;  A telepítő létre tud hozni újat automatikusan vagy te magad kézi partícionálással.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Ez az ajánlott partíciós tábla típus modern rendszerekhez ami &lt;strong&gt;EFI&lt;/strong&gt;  indító környezettel indul.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="127"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Ez a partíciós tábla típus régebbi rendszerekhez javasolt amik &lt;strong&gt;BIOS&lt;/strong&gt; indító környezetből indulnak. Legtöbb esetben azonban GPT használata javasolt. &lt;br&gt;&lt;strong&gt;Figyelem:&lt;/strong&gt; az MSDOS partíciós tábla egy régi sztenderd lényeges korlátozásokkal. &lt;br&gt;Maximum 4 &lt;em&gt;elsődleges&lt;/em&gt; partíció hozható létre és abból a 4-ből egy lehet &lt;em&gt;kiterjesztett&lt;/em&gt; partíció.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="140"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>A &lt;strong&gt;partíciós tábla&lt;/strong&gt; típusa a kiválasztott tárolóeszközön.&lt;br&gt;&lt;br&gt;Az egyetlen lehetőség a partíciós tábla változtatására ha töröljük és újra létrehozzuk a partíciós táblát, ami megsemmisít minden adatot a tárolóeszközön.&lt;br&gt;A telepítő megtartja az aktuális partíciós táblát ha csak másképp nem döntesz.&lt;br&gt;Ha nem vagy benne biztos a legtöbb modern rendszernél GPT az elterjedt.</translation>
    </message>
  </context>
  <context>
    <name>DeviceModel</name>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="84"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="95"/>
      <source>%1 - (%2)</source>
      <extracomment>device[name] - (device-node[name])</extracomment>
      <translation>%1 – (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="117"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Dracut LUKS konfiguráció mentése ide %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Dracut LUKS konfiguráció mentésének kihagyása: "/" partíció nincs titkosítva.</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <translation>Hiba történt %1  megnyitásakor</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="37"/>
      <source>Dummy C++ Job</source>
      <translation>Teszt C++ job</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Meglévő partíció szerkesztése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Content:</source>
      <translation>Tartalom:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>&amp;megtart</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Formázás</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Figyelem: A partíció formázása az összes meglévő adatot törölni fogja.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Csatolási pont:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="123"/>
      <source>Si&amp;ze:</source>
      <translation>&amp;méret:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="133"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="140"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;fájlrendszer</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="153"/>
      <source>Flags:</source>
      <translation>Zászlók:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="275"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>A csatolási pont már használatban van. Kérlek, válassz másikat.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Rendszer titkosítása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="46"/>
      <source>Passphrase</source>
      <translation>Jelszó</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="56"/>
      <source>Confirm passphrase</source>
      <translation>Jelszó megerősítés</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="104"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="114"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Írd be ugyanazt a jelmondatot mindkét dobozban.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="138"/>
      <source>Set partition information</source>
      <translation>Partíció információk beállítása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="164"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>%1 telepítése az &lt;strong&gt;új&lt;/strong&gt; %2 partícióra.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="170"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;Új&lt;/strong&gt; %2 partíció beállítása &lt;strong&gt;%1&lt;/strong&gt; csatolási ponttal.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="180"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>%2 telepítése %3 &lt;strong&gt;%1&lt;/strong&gt; rendszer partícióra.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="187"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>%3 partíció beállítása &lt;strong&gt;%1&lt;/strong&gt; &lt;strong&gt;%2&lt;/strong&gt; csatolási ponttal.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="200"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rendszerbetöltő telepítése ide &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="209"/>
      <source>Setting up mount points.</source>
      <translation>Csatlakozási pontok létrehozása</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>Új&amp;raindítás most</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="44"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Minden kész.&lt;/h1&gt;&lt;br/&gt;%1 telepítve lett a számítógépére. &lt;br/&gt;Most már használhatja az új rendszert.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Ezt bejelölve a rendszer újra fog indulni amikor a &lt;span style="font-style:italic;"&gt;Kész&lt;/span&gt; gombra kattint vagy bezárja a telepítőt.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt; </translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Sikeres művelet.&lt;/h1&gt;&lt;br/&gt;%1 telepítve lett a számítógépére.&lt;br/&gt;Újraindítás után folytathatod az %2 éles környezetben.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="59"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Ezt bejelölve a rendszer újra fog indulni amikor a &lt;span style="font-style:italic;"&gt;Kész&lt;/span&gt;gombra kattint vagy bezárja a telepítőt.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="116"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Telepítés nem sikerült&lt;/h1&gt;&lt;br/&gt;%1 nem lett telepítve a számítógépére. &lt;br/&gt;A hibaüzenet: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="122"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;A telepítés hibába ütközött.&lt;/h1&gt;&lt;br/&gt;%1 nem lett telepítve a számítógépre.&lt;br/&gt;A hibaüzenet: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="67"/>
      <source>Finish</source>
      <translation>Befejezés</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Setup Complete</source>
      <translation>Telepítés Sikerült</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Installation Complete</source>
      <translation>A telepítés befejeződött.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="127"/>
      <source>The setup of %1 is complete.</source>
      <translation>A telepítésből %1 van kész.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="128"/>
      <source>The installation of %1 is complete.</source>
      <translation>A %1 telepítése elkészült.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="36"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Partíció formázása %1 (fájlrendszer: %2, méret: %3 MiB) itt %4</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="47"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%3MiB&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; partíció formázása &lt;strong&gt;%2&lt;/strong&gt; fájlrendszerrel.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="58"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>%1 partíció formázása %2 fájlrendszerrel.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="72"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>A telepítő nem tudta formázni a %1 partíciót a %2 lemezen.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>legalább %1 GiB lemezterület elérhető</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="151"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Nincs elég lemezterület. Legalább %1 GiB szükséges.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>has at least %1 GiB working memory</source>
      <translation>legalább %1 GiB memória elérhető</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>A rendszer nem tartalmaz elég memóriát. Legalább %1 GiB szükséges.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="171"/>
      <source>is plugged in to a power source</source>
      <translation>csatlakoztatva van külső áramforráshoz</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="172"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>A rendszer nincs csatlakoztatva külső áramforráshoz</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>is connected to the Internet</source>
      <translation>csatlakozik az internethez</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The system is not connected to the Internet.</source>
      <translation>A rendszer nem csatlakozik az internethez.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="187"/>
      <source>is running the installer as an administrator (root)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="190"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>A telepítő program nem adminisztrátori joggal fut.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="191"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>A telepítő nem adminisztrátori jogokkal fut.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="199"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="202"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>A képernyő mérete túl kicsi a telepítő program megjelenítéséhez.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="203"/>
      <source>The screen is too small to display the installer.</source>
      <translation>A képernyőméret túl kicsi a telepítő megjelenítéséhez.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="42"/>
      <source>Collecting information about your machine.</source>
      <translation type="unfinished"/>
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
      <translation>OEM Batch azonosító</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nem sikerült létrehozni a könyvtárakat &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Sikertelen fájl megnyitás &lt;code&gt;%1&lt;/code&gt;. </translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Sikertelen fájl írás &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>initramfs létrehozása mkinitcpio utasítással.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="28"/>
      <source>Creating initramfs.</source>
      <translation>initramfs létrehozása.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Konsole not installed</source>
      <translation>Konsole nincs telepítve</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Kérlek telepítsd a KDE Konsole-t és próbáld újra!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="102"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Script végrehajása: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="41"/>
      <source>Script</source>
      <translation>Szkript</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <translation>Billentyűzet</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Billentyűzet</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System locale setting</source>
      <translation>Területi beállítások</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>A nyelvi beállítás kihat a nyelvi és karakter beállításokra a parancssori elemeknél.&lt;br/&gt;A jelenlegi beállítás &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Mégse</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licenszszerződés&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="136"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Elfogadom a fentebbi felhasználási feltételeket.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="138"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="143"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="146"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="43"/>
      <source>License</source>
      <translation>Licensz</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="88"/>
      <source>URL: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="109"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt; %2 -ból/ -ből</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 grafikus driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 böngésző plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 kodek&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 csomag&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey" &gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;%2 -ból/ -ből&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide license text</source>
      <translation>Licensz szöveg elrejtése</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open license agreement in browser.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <translation>Régió:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <translation>Zóna:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change...</source>
      <translation>&amp;Változtat...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <translation>Hely</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="76"/>
      <source>Location</source>
      <translation>Hely</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="28"/>
      <source>Configuring LUKS key file.</source>
      <translation>LUKS kulcs fájl konfigurálása.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="168"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="176"/>
      <source>No partitions are defined.</source>
      <translation>Nincsenek partíciók definiálva.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="211"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="218"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="226"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Titkosított rootfs telepítési hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="212"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>A %1 root partíció LUKS de beállítva nincs kulcs.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="219"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Nem sikerült létrehozni a LUKS kulcs fájlt a %1 root partícióhoz</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="227"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="37"/>
      <source>Generate machine-id.</source>
      <translation>Gépazonosító előállítása.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="53"/>
      <source>Configuration Error</source>
      <translation>Konfigurációs hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="54"/>
      <source>No root mount point is set for MachineId.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="243"/>
      <source>Timezone: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="264"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="47"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Package selection</source>
      <translation>Csomag választása</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Office software</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Office package</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Browser software</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Browser package</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Web browser</source>
      <translation>Böngésző</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Kernel</source>
      <translation>Kernel</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Services</source>
      <translation>Szolgáltatások</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Login</source>
      <translation>Bejelentkezés</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Desktop</source>
      <translation>Asztal</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Applications</source>
      <translation>Alkalmazások</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Communication</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Development</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Office</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Multimedia</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Internet</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Theming</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Gaming</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Utilities</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Ba&amp;amp;tch:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Gépelje ide a batch azonosítót. Ez a célrendszeren lesz tárolva.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM konfiguráció&lt;/h1&gt; &lt;p&gt;A Calamares az OEM beállításokat fogja használni a célrendszer konfigurációjához.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="122"/>
      <source>OEM Configuration</source>
      <translation>OEM konfiguráció</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="128"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Állítsa az OEM Batch azonosítót erre: &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="37"/>
      <source>Select your preferred Region, or use the default one based on your current location.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="94"/>
      <location filename="../src/modules/localeq/Offline.qml" line="169"/>
      <location filename="../src/modules/localeq/Offline.qml" line="213"/>
      <source>Timezone: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="111"/>
      <source>Select your preferred Zone within your Region.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="182"/>
      <source>Zones</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="229"/>
      <source>You can fine-tune Language and Locale settings below.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="51"/>
      <source>Password is too short</source>
      <translation>Túl rövid jelszó</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
      <source>Password is too long</source>
      <translation>Túl hosszú jelszó</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>Password is too weak</source>
      <translation>A jelszó túl gyenge</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Memóriafoglalási hiba a(z) „%1” beállításakor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
      <source>Memory allocation error</source>
      <translation>Memóriafoglalási hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
      <source>The password is the same as the old one</source>
      <translation>A jelszó ugyanaz, mint a régi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="203"/>
      <source>The password is a palindrome</source>
      <translation>A jelszó egy palindrom</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
      <source>The password differs with case changes only</source>
      <translation>A jelszó csak kis- és nagybetűben tér el</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="207"/>
      <source>The password is too similar to the old one</source>
      <translation>A jelszó túlságosan hasonlít a régire</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
      <source>The password contains the user name in some form</source>
      <translation>A jelszó tartalmazza felhasználónevet valamilyen formában</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="211"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>A jelszó tartalmazza a felhasználó valódi nevét valamilyen formában</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
      <source>The password contains forbidden words in some form</source>
      <translation>A jelszó tiltott szavakat tartalmaz valamilyen formában</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="221"/>
      <source>The password contains too few digits</source>
      <translation>A jelszó túl kevés számjegyet tartalmaz</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="228"/>
      <source>The password contains too few uppercase letters</source>
      <translation>A jelszó túl kevés nagybetűt tartalmaz</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="232"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
      <source>The password contains too few lowercase letters</source>
      <translation>A jelszó túl kevés kisbetűt tartalmaz</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="242"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>A jelszó túl kevés nem alfanumerikus karaktert tartalmaz</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="249"/>
      <source>The password is too short</source>
      <translation>A jelszó túl rövid</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="258"/>
      <source>The password does not contain enough character classes</source>
      <translation>A jelszó nem tartalmaz elég karakterosztályt</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>A jelszó túl sok egyező karaktert tartalmaz egymás után</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>A jelszó túl sok karaktert tartalmaz ugyanabból a karakterosztályból egymás után</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
      <source>The password contains fewer than %n digits</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="246"/>
      <source>The password is shorter than %n characters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
      <source>The password is a rotated version of the previous one</source>
      <translation type="unfinished"/>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
      <source>The password contains fewer than %n character classes</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="262"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="286"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>A jelszó túl hosszú monoton karaktersorozatot tartalmaz</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>No password supplied</source>
      <translation>Nincs jelszó megadva</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="291"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Nem nyerhetőek ki véletlenszámok az RNG eszközből</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>A jelszó előállítás meghiúsult – a szükséges entrópia túl alacsony a beállításokhoz</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>A jelszó megbukott a szótárellenőrzésen – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="301"/>
      <source>The password fails the dictionary check</source>
      <translation>A jelszó megbukott a szótárellenőrzésen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="305"/>
      <source>Unknown setting - %1</source>
      <translation>Ismeretlen beállítás – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="307"/>
      <source>Unknown setting</source>
      <translation>Ismeretlen beállítás</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="311"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Hibás egész érték a beállításnál – %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="313"/>
      <source>Bad integer value</source>
      <translation>Hibás egész érték</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="317"/>
      <source>Setting %1 is not of integer type</source>
      <translation>A(z) %1 beállítás nem egész típusú</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="319"/>
      <source>Setting is not of integer type</source>
      <translation>A beállítás nem egész típusú</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="323"/>
      <source>Setting %1 is not of string type</source>
      <translation>A(z) %1 beállítás nem karakterlánc típusú</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="325"/>
      <source>Setting is not of string type</source>
      <translation>A beállítás nem karakterlánc típusú</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="327"/>
      <source>Opening the configuration file failed</source>
      <translation>A konfigurációs fájl megnyitása meghiúsult</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="329"/>
      <source>The configuration file is malformed</source>
      <translation>A konfigurációs fájl rosszul formázott</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="331"/>
      <source>Fatal failure</source>
      <translation>Végzetes hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="333"/>
      <source>Unknown error</source>
      <translation>Ismeretlen hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="775"/>
      <source>Password is empty</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="24"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="44"/>
      <source>Product Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="57"/>
      <source>TextLabel</source>
      <translation>Szöveges címke</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="73"/>
      <source>Long Product Description</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="61"/>
      <source>Packages</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Name</source>
      <translation>Név</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Description</source>
      <translation>Leírás</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard Model:</source>
      <translation>Billentyűzet modell:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="135"/>
      <source>Type here to test your keyboard</source>
      <translation>Gépelj itt a billentyűzet teszteléséhez</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Mi a neved?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Milyen felhasználónévvel szeretnél bejelentkezni?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Mi legyen a számítógép neve?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ez a név lesz használva ha a számítógép látható a hálózaton.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Adj meg jelszót a felhasználói fiókod védelmére.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Írd be a jelszót kétszer így ellenőrizve lesznek a gépelési hibák. A jó jelszó tartalmazzon kis és nagy betűket, számokat és legalább 8 karakter hosszúságú. Ajánlott megváltoztatni rendszeres időközönként.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Jelszó megkérdezése nélküli automatikus bejelentkezés.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Ugyanaz a jelszó használata az adminisztrátor felhasználóhoz.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Adj meg jelszót az adminisztrátor felhasználói fiókhoz.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Írd be a jelszót kétszer így ellenőrizve lesznek a gépelési hibák.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="190"/>
      <source>Root</source>
      <translation>Root</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="194"/>
      <source>Home</source>
      <translation>Home</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
      <source>Boot</source>
      <translation>Boot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
      <source>EFI system</source>
      <translation>EFI rendszer</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition for %1</source>
      <translation>Új partíció %1 -ra/ -re</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="215"/>
      <source>New partition</source>
      <translation>Új partíció</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="239"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1  %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="159"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="199"/>
      <source>Free Space</source>
      <translation>Szabad terület</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="163"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="203"/>
      <source>New partition</source>
      <translation>Új partíció</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="296"/>
      <source>Name</source>
      <translation>Név</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="298"/>
      <source>File System</source>
      <translation>Fájlrendszer</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="300"/>
      <source>Mount Point</source>
      <translation>Csatolási pont</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="302"/>
      <source>Size</source>
      <translation>Méret</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Eszköz:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>&amp;Módosítások visszavonása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Új partíciós &amp;tábla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>&amp;Létrehozás</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Szerkeszt</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>&amp;Töröl</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Új kötetcsoport</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Kötetcsoport átméretezése</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Kötetcsoport deaktiválása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Kötetcsoport eltávolítása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Rendszerbetöltő &amp;telepítése ide:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="219"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Biztos vagy benne, hogy létrehozol egy új partíciós táblát itt %1 ?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="254"/>
      <source>Can not create new partition</source>
      <translation>Nem hozható létre új partíció</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="255"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>A(z) %1 lemezen lévő partíciós táblában már %2 elsődleges partíció van, és több nem adható hozzá. Helyette távolítson el egy elsődleges partíciót, és adjon hozzá egy kiterjesztett partíciót.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="70"/>
      <source>Gathering system information...</source>
      <translation>Rendszerinformációk gyűjtése...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="125"/>
      <source>Partitions</source>
      <translation>Partíciók</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>%1 telepítése más operációs rendszer &lt;strong&gt;mellé&lt;/strong&gt; .</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Lemez törlés&lt;/strong&gt;és %1 telepítés.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="170"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a következővel: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="174"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;Kézi&lt;/strong&gt; partícionálás.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="187"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>%1 telepítése más operációs rendszer &lt;strong&gt;mellé&lt;/strong&gt; a &lt;strong&gt;%2&lt;/strong&gt; (%3) lemezen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="194"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;%2 lemez törlése&lt;/strong&gt; (%3) és %1 telepítés.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="200"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;A partíció lecserélése&lt;/strong&gt; a &lt;strong&gt;%2&lt;/strong&gt; lemezen(%3) a következővel: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="207"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;Kézi&lt;/strong&gt; telepítés a &lt;strong&gt;%1&lt;/strong&gt; (%2) lemezen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="216"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Lemez &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="242"/>
      <source>Current:</source>
      <translation>Aktuális:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="260"/>
      <source>After:</source>
      <translation>Utána:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="427"/>
      <source>No EFI system partition configured</source>
      <translation>Nincs EFI rendszer partíció beállítva</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="428"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="442"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="441"/>
      <source>EFI system partition flag not set</source>
      <translation>EFI partíciós zászló nincs beállítva</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="468"/>
      <source>Option to use GPT on BIOS</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="469"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="497"/>
      <source>Boot partition not encrypted</source>
      <translation>Indító partíció nincs titkosítva</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="498"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Egy külön indító partíció lett beállítva egy titkosított root partícióval, de az indító partíció nincs titkosítva.br/&gt;&lt;br/&gt;Biztonsági aggályok merülnek fel ilyen beállítás mellet, mert fontos fájlok nem titkosított partíción vannak tárolva. &lt;br/&gt;Ha szeretnéd, folytathatod így, de a fájlrendszer zárolása meg fog történni az indítás után. &lt;br/&gt; Az indító partíció titkosításához lépj vissza és az újra létrehozáskor válaszd a &lt;strong&gt;Titkosít&lt;/strong&gt; opciót.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="627"/>
      <source>has at least one disk device available.</source>
      <translation>legalább egy lemez eszköz elérhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="628"/>
      <source>There are no partitions to install on.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Plasma kinézet feladat</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>A KDE Plasma kinézeti csomag nem válaszható ki</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="79"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Kérem válasszon kinézetet a KDE Plasma felülethez, Kihagyhatja ezt a lépést és konfigurálhatja a kinézetet a rendszer telepítése után. A listában a kinézetet kiválasztva egy élő előnézetet fog látni az adott témáról.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="84"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Válasszon egy kinézetet a KDE Plasma asztali környezethez. Ki is hagyhatja ezt a lépést, és beállíthatja a kinézetet, ha a telepítés elkészült. A kinézetválasztóra kattintva élő előnézetet kaphat a kinézetről.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <translation>Kinézet</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="79"/>
      <source>Saving files for later ...</source>
      <translation>Fájlok mentése későbbre …</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="118"/>
      <source>No files configured to save for later.</source>
      <translation>Nincsenek fájlok beállítva elmentésre későbbre</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="172"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Nem az összes beállított fájl örízhető meg.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="412"/>
      <source>
There was no output from the command.</source>
      <translation>
A parancsnak nem volt kimenete.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="413"/>
      <source>
Output:
</source>
      <translation>
Kimenet:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="417"/>
      <source>External command crashed.</source>
      <translation>Külső parancs összeomlott.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Parancs &lt;i&gt;%1&lt;/i&gt; összeomlott.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>External command failed to start.</source>
      <translation>A külső parancsot nem sikerült elindítani.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancsot nem sikerült elindítani.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>Internal error when starting command.</source>
      <translation>Belső hiba a parancs végrehajtásakor.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>Bad parameters for process job call.</source>
      <translation>Hibás paraméterek a folyamat hívásához.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="433"/>
      <source>External command failed to finish.</source>
      <translation>Külső parancs nem fejeződött be.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancsot nem sikerült befejezni %2 másodperc alatt.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="441"/>
      <source>External command finished with errors.</source>
      <translation>A külső parancs hibával fejeződött be.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="442"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>A(z) &lt;i&gt;%1&lt;/i&gt; parancs hibakóddal lépett ki: %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Label.cpp" line="29"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="28"/>
      <source>unknown</source>
      <translation>ismeretlen</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="30"/>
      <source>extended</source>
      <translation>kiterjesztett</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="32"/>
      <source>unformatted</source>
      <translation>formázatlan</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="34"/>
      <source>swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="130"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="167"/>
      <source>Default</source>
      <translation>Alapértelmezett</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="72"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="76"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>File not found</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="65"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="83"/>
      <source>Directory not found</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="84"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="94"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="70"/>
      <source>No product</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="78"/>
      <source>No description provided.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="40"/>
      <source>(no mount point)</source>
      <translation>(nincs csatolási pont)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="41"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Nem particionált, vagy ismeretlen partíció</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="34"/>
      <source>Remove live user from target system</source>
      <translation>Éles felhasználó eltávolítása a cél rendszerből</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="36"/>
      <source>Remove Volume Group named %1.</source>
      <translation>A kötetcsoport eltávolítása: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="30"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Kötetcsoport eltávolítása: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>A telepítő nem tudta eltávolítani a kötetcsoportot: „%1”.</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="127"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Válaszd ki az telepítés helyét %1.&lt;br/&gt;&lt;font color="red"&gt;Figyelmeztetés: &lt;/font&gt;minden fájl törölve lesz a kiválasztott partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="149"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>A kiválasztott elem nem tűnik érvényes partíciónak.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="157"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 nem telepíthető, kérlek válassz egy létező partíciót.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="167"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 nem telepíthető a kiterjesztett partícióra. Kérlek, válassz egy létező elsődleges vagy logikai partíciót.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="177"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>Nem lehet telepíteni a következőt %1 erre a partícióra.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="183"/>
      <source>Data partition (%1)</source>
      <translation>Adat partíció (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="203"/>
      <source>Unknown system partition (%1)</source>
      <translation>Ismeretlen rendszer partíció (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="207"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 rendszer partíció (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="218"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;A partíció %1 túl kicsi a következőhöz %2. Kérlek, válassz egy legalább %3 GB- os partíciót.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="240"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Az EFI rendszerpartíció nem található a rendszerben. Kérlek, lépj vissza és állítsd be manuális partícionálással %1- et.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="251"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="292"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 installálva lesz a következőre: %2.&lt;br/&gt;&lt;font color="red"&gt;Figyelmeztetés: &lt;/font&gt;a partíción %2 minden törölve lesz.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="259"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>A %2 indításához az EFI rendszer partíciót használja a következőn: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="275"/>
      <source>EFI system partition:</source>
      <translation>EFI rendszer partíció:</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="38"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="46"/>
      <source>Resize Filesystem Job</source>
      <translation>Fájlrendszer átméretezési feladat</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>Invalid configuration</source>
      <translation>Érvénytelen konfiguráció</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>A fájlrendszer átméretezési feladat konfigurációja érvénytelen, és nem fog futni.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="175"/>
      <source>KPMCore not Available</source>
      <translation>A KPMCore nem érhető el</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="176"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>A Calamares nem tudja elindítani a KPMCore-t a fájlrendszer átméretezési feladathoz.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="184"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="193"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="204"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="231"/>
      <source>Resize Failed</source>
      <translation>Az átméretezés meghiúsult</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>A(z) %1 fájlrendszer nem található a rendszeren, és nem méretezhető át.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>A(z) %1 eszköz nem található a rendszeren, és nem méretezhető át.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>A(z) %1 fájlrendszer nem méretezhető át.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The device %1 cannot be resized.</source>
      <translation>A(z) %1 eszköz nem méretezhető át.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>A(z) %1 fájlrendszert át kell méretezni, de nem lehet.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="215"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>A(z) %1 eszközt át kell méretezni, de nem lehet</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="40"/>
      <source>Resize partition %1.</source>
      <translation>A %1 partíció átméretezése.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="47"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%2MiB&lt;/strong&gt;&lt;strong&gt;%1&lt;/strong&gt; partíció átméretezése erre &lt;strong&gt;%3MiB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="58"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>%1 partíción %2MiB átméretezése erre %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="77"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>A telepítő nem tudta átméretezni a(z) %1 partíciót a(z) '%2' lemezen.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <translation>Kötetcsoport átméretezése</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="27"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>A(z) %1 kötet átméretezése ekkoráról: %2, ekkorára: %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>A(z) &lt;strong&gt;%1&lt;/strong&gt; kötet átméretezése ekkoráról: &lt;strong&gt;%2&lt;/strong&gt;, ekkorára: &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="60"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>A telepítő nem tudta átméretezni a kötetcsoportot: „%1”.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="133"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>A legjobb eredményért győződjünk meg, hogy ez a számítógép:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="134"/>
      <source>System requirements</source>
      <translation>Rendszer követelmények</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="256"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez. &lt;br/&gt;A telepítés nem folytatható. &lt;a href="#details"&gt;Részletek...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="260"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;
Telepítés nem folytatható. &lt;a href="#details"&gt;Részletek...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="267"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Ez a számítógép nem felel meg néhány követelménynek a %1 telepítéséhez. &lt;br/&gt;A telepítés folytatható de előfordulhat néhány képesség nem lesz elérhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="271"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Ez a számítógép nem felel meg a minimum követelményeknek a %1 telepítéséhez.&lt;br/&gt;Telepítés folytatható de néhány tulajdonság valószínűleg nem lesz elérhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="280"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Ez a program fel fog tenni néhány kérdést és %2 -t telepíti a számítógépre.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Scanning storage devices...</source>
      <translation>Eszközök keresése...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Partitioning</source>
      <translation>Partícionálás</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
      <source>Set hostname %1</source>
      <translation>Hálózati név beállítása a %1 -en</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Hálózati név beállítása a következőhöz: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
      <source>Setting hostname %1.</source>
      <translation>Hálózati név beállítása a %1 -hez</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="122"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="129"/>
      <source>Internal Error</source>
      <translation>Belső hiba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="137"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <source>Cannot write hostname to target system</source>
      <translation>Nem lehet a hálózati nevet írni a célrendszeren</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="55"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Billentyűzet beállítása %1, elrendezés %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Hiba történt a billentyűzet virtuális konzolba való beállításakor</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="397"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="414"/>
      <source>Failed to write to %1</source>
      <translation>Hiba történt %1 -re történő íráskor</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="396"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Hiba történt a billentyűzet X11- hez való beállításakor</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="413"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Hiba történt a billentyűzet konfiguráció alapértelmezett /etc/default mappába valló elmentésekor.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="43"/>
      <source>Set flags on partition %1.</source>
      <translation>Zászlók beállítása a partíción %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>flags beállítása a %1MiB %2 partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="53"/>
      <source>Set flags on new partition.</source>
      <translation>Jelzők beállítása az új partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Zászlók törlése a partíción: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>flags eltávolítása a %1MiB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition.</source>
      <translation>Jelzők törlése az új partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Zászlók beállítása &lt;strong&gt;%1&lt;/strong&gt; ,mint &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partíción mint &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="96"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Jelző beállítása mint &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="108"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Zászlók törlése a partíción: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="114"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Flag-ek eltávolítása a %1MiB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="119"/>
      <source>Clearing flags on new partition.</source>
      <translation>jelzők törlése az új partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="124"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Zászlók beállítása &lt;strong&gt;%2&lt;/strong&gt; a &lt;strong&gt;%1&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Flag-ek beállítása &lt;strong&gt;%3&lt;/strong&gt; a %1MiB &lt;strong&gt;%2&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Jelzők beállítása az új &lt;strong&gt;%1&lt;/strong&gt; partíción.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="156"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>A telepítőnek nem sikerült a zászlók beállítása a partíción %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="40"/>
      <source>Set password for user %1</source>
      <translation>%1 felhasználó jelszó beállítása</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="47"/>
      <source>Setting password for user %1.</source>
      <translation>%1 felhasználói jelszó beállítása</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>Bad destination system path.</source>
      <translation>Rossz célrendszer elérési út</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="82"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMountPoint is %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="88"/>
      <source>Cannot disable root account.</source>
      <translation>A root account- ot nem lehet inaktiválni.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd megszakítva %1 hibakóddal.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot set password for user %1.</source>
      <translation>Nem lehet a %1 felhasználó jelszavát beállítani.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod megszakítva %1 hibakóddal.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="34"/>
      <source>Set timezone to %1/%2</source>
      <translation>Időzóna beállítása %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="62"/>
      <source>Cannot access selected timezone path.</source>
      <translation>A választott időzóna útvonal nem hozzáférhető.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="63"/>
      <source>Bad path: %1</source>
      <translation>Rossz elérési út: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot set timezone.</source>
      <translation>Nem lehet az időzónát beállítani.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Link létrehozása nem sikerült: %1, link év: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="77"/>
      <source>Cannot set timezone,</source>
      <translation>Nem lehet beállítani az időzónát .</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="78"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Nem lehet megnyitni írásra: /etc/timezone</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="166"/>
      <source>Preparing groups.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="178"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="183"/>
      <source>Could not create groups in target system</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="184"/>
      <source>These groups are missing in the target system: %1</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="33"/>
      <source>Configure &lt;pre&gt;sudo&lt;/pre&gt; users.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="55"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Nem lehet a sudoers fájlt "chmod" -olni.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="60"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Nem lehet sudoers fájlt létrehozni írásra.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="41"/>
      <source>Shell Processes Job</source>
      <translation>Parancssori folyamatok feladat</translation>
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
    <name>SummaryPage</name>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="48"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Összefoglaló arról mi fog történni a telepítés során.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="50"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Ez áttekintése annak, hogy mi fog történni, ha megkezded a telepítést.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="36"/>
      <source>Summary</source>
      <translation>Összefoglalás</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="37"/>
      <source>Installation feedback</source>
      <translation>Visszajelzés a telepítésről</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
      <source>Sending installation feedback.</source>
      <translation>Telepítési visszajelzés küldése.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="60"/>
      <source>Internal error in install-tracking.</source>
      <translation>Hiba a telepítő nyomkövetésben.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="61"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP kérés ideje lejárt.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="122"/>
      <source>KDE user feedback</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="128"/>
      <source>Configuring KDE user feedback.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="150"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="156"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="151"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="157"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Machine feedback</source>
      <translation>Gépi visszajelzés</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="77"/>
      <source>Configuring machine feedback.</source>
      <translation>Gépi visszajelzés konfigurálása.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Hiba a gépi visszajelzés konfigurálásában.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="101"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Gépi visszajelzés konfigurálása nem megfelelő, script hiba %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="107"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Gépi visszajelzés konfigurálása nem megfelelő,.
Calamares hiba %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Helytartó</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt; Kattints ide bővebb információért a felhasználói visszajelzésről &lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;head/&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="86"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="91"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="94"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="98"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <translation>Visszacsatolás</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="156"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ha egynél több személy használja a számítógépet akkor létrehozhat több felhasználói fiókot telepítés után.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="162"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ha egynél több személy használja a számítógépet akkor létrehozhat több felhasználói fiókot telepítés után.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="39"/>
      <source>Users</source>
      <translation>Felhasználók</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Felhasználók</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Érték</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Kötetcsoport létrehozása</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Fizikai kötetek listája</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Kötetcsoport neve:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Kötetcsoport típusa:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Fizikai kiterjedés mérete:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Teljes méret:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Használt méret:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Szektorok összesen:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Logkai kötetek száma:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="18"/>
      <source>Form</source>
      <translation>Adatlap</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>&amp;About</source>
      <translation>&amp;Névjegy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="150"/>
      <source>Open donations website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>&amp;Donate</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="163"/>
      <source>Open help and support website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>&amp;Support</source>
      <translation>&amp;Támogatás</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
      <source>Open issues and bug-tracking website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Ismert hibák</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="189"/>
      <source>Open release notes website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="192"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Kiadási megjegyzések</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="216"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Üdvözli önt a Calamares telepítő itt %1!&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="217"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Köszöntjük a %1 telepítőben!&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="222"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Üdvözlet a Calamares %1 telepítőjében.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Üdvözlet a %1 telepítőben.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="228"/>
      <source>%1 support</source>
      <translation>%1 támogatás</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 setup</source>
      <translation>A %1 telepítőről.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 installer</source>
      <translation>A %1 telepítőről</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="238"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="41"/>
      <source>Welcome</source>
      <translation>Üdvözlet</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="48"/>
      <source>Welcome</source>
      <translation>Üdvözlet</translation>
    </message>
  </context>
  <context>
    <name>about</name>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="47"/>
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
      <location filename="../src/modules/welcomeq/about.qml" line="96"/>
      <source>Back</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="46"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="106"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="158"/>
      <source>Back</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="45"/>
      <source>Keyboard Model</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="377"/>
      <source>Layouts</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="148"/>
      <source>Keyboard Layout</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="60"/>
      <source>Click your preferred keyboard model to select layout and variant, or use the default one based on the detected hardware.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="253"/>
      <source>Models</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="260"/>
      <source>Variants</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="276"/>
      <source>Keyboard Variant</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="386"/>
      <source>Test your keyboard</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="81"/>
      <source>Change</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="36"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="52"/>
      <source>What is your name?</source>
      <translation>Mi a neved?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="59"/>
      <source>Your Full Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Milyen felhasználónévvel szeretnél bejelentkezni?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="103"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="118"/>
      <source>What is the name of this computer?</source>
      <translation>Mi legyen a számítógép neve?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="125"/>
      <source>Computer Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="140"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="155"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Adj meg jelszót a felhasználói fiókod védelmére.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="166"/>
      <source>Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="185"/>
      <source>Repeat Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="204"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="216"/>
      <source>Validate passwords quality</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="226"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="234"/>
      <source>Log in automatically without asking for the password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="243"/>
      <source>Reuse user password as root password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="253"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Ugyanaz a jelszó használata az adminisztrátor felhasználóhoz.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="268"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="279"/>
      <source>Root Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="298"/>
      <source>Repeat Root Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="35"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="66"/>
      <source>About</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Support</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Known issues</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="102"/>
      <source>Release notes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="114"/>
      <source>Donate</source>
      <translation type="unfinished"/>
    </message>
  </context>
</TS>

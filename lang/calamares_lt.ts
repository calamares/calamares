<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="lt" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="62"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>Šios sistemos &lt;strong&gt;paleidimo aplinka&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Senesnės x86 sistemos palaiko tik &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Šiuolaikinės sistemos, dažniausiai, naudoja &lt;strong&gt;EFI&lt;/strong&gt;, tačiau, jeigu jos yra paleistos suderinamumo veiksenoje, taip pat gali būti rodomos kaip BIOS.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="72"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Ši sistema buvo paleista su &lt;strong&gt;EFI&lt;/strong&gt; paleidimo aplinka.&lt;br&gt;&lt;br&gt;Tam, kad sukonfigūruotų paleidimą iš EFI aplinkos, ši diegimo programa, &lt;strong&gt;EFI sistemos skaidinyje&lt;/strong&gt;, privalo išskleisti paleidyklės programą, kaip, pavyzdžiui, &lt;strong&gt;GRUB&lt;/strong&gt; ar &lt;strong&gt;systemd-boot&lt;/strong&gt;. Tai vyks automatiškai, nebent pasirinksite rankinį skaidymą ir tokiu atveju patys turėsite pasirinkti arba sukurti skaidinį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="84"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Ši sistema buvo paleista su &lt;strong&gt;BIOS&lt;/strong&gt; paleidimo aplinka.&lt;br&gt;&lt;br&gt;Tam, kad sukonfigūruotų paleidimą iš BIOS aplinkos, ši diegimo programa, arba skaidinio pradžioje, arba &lt;strong&gt;Paleidimo įraše (MBR)&lt;/strong&gt;, šalia skaidinių lentelės pradžios (pageidautina), privalo įdiegti paleidyklę, kaip, pavyzdžiui, &lt;strong&gt;GRUB&lt;/strong&gt;. Tai vyks automatiškai, nebent pasirinksite rankinį skaidymą ir tokiu atveju, viską turėsite nusistatyti patys.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="58"/>
      <source>Master Boot Record of %1</source>
      <translation> %1 paleidimo įrašas (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="91"/>
      <source>Boot Partition</source>
      <translation>Paleidimo skaidinys</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="98"/>
      <source>System Partition</source>
      <translation>Sistemos skaidinys</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="128"/>
      <source>Do not install a boot loader</source>
      <translation>Nediegti paleidyklės</translation>
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
      <translation>Tuščias puslapis</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>VisuotinisKaupiklis</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>UžduotiesEilė</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Moduliai</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Tipas:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>nėra</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Sąsaja:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="97"/>
      <source>Tools</source>
      <translation>Įrankiai</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="110"/>
      <source>Reload Stylesheet</source>
      <translation>Iš naujo įkelti stilių aprašą</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="117"/>
      <source>Widget Tree</source>
      <translation>Valdiklių medis</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="217"/>
      <source>Debug information</source>
      <translation>Derinimo informacija</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Set up</source>
      <translation>Sąranka</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Install</source>
      <translation>Diegimas</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Užduotis patyrė nesėkmę (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Užprogramuota užduoties nesėkmė buvo aiškiai užklausta.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="196"/>
      <source>Done</source>
      <translation>Atlikta</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Pavyzdinė užduotis (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source>Run command '%1' in target system.</source>
      <translation>Paleisti paskirties sistemoje komandą „%1“.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source> Run command '%1'.</source>
      <translation>Paleisti komandą „%1“.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="50"/>
      <source>Running command %1 %2</source>
      <translation>Vykdoma komanda %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="192"/>
      <source>Running %1 operation.</source>
      <translation>Vykdoma %1 operacija.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="221"/>
      <source>Bad working directory path</source>
      <translation>Netinkama darbinio katalogo vieta</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="222"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Darbinis %1 python katalogas  dėl %2 užduoties yra neskaitomas</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="228"/>
      <source>Bad main script file</source>
      <translation>Prastas pagrindinio skripto failas</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="229"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Pagrindinis scenarijus %1  dėl python %2 užduoties yra neskaitomas</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="297"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost.Python klaida užduotyje "%1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="67"/>
      <source>Loading ...</source>
      <translation>Įkeliama...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="88"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML &lt;i&gt;%1&lt;/i&gt; žingsnis.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="268"/>
      <source>Loading failed.</source>
      <translation>Įkėlimas nepavyko.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="94"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>Reikalavimų tikrinimas &lt;i&gt;%1&lt;/i&gt; moduliui yra užbaigtas.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="115"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Laukiama %n modulio.</numerusform>
        <numerusform>Laukiama %n modulių.</numerusform>
        <numerusform>Laukiama %n modulių.</numerusform>
        <numerusform>Laukiama %n modulio.</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="116"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n sekundė)</numerusform>
        <numerusform>(%n sekundės)</numerusform>
        <numerusform>(%n sekundžių)</numerusform>
        <numerusform>(%n sekundė)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="121"/>
      <source>System-requirements checking is complete.</source>
      <translation>Sistemos reikalavimų tikrinimas yra užbaigtas.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Setup Failed</source>
      <translation>Sąranka patyrė nesėkmę</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Installation Failed</source>
      <translation>Diegimas nepavyko</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="151"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Ar norėtumėte įdėti diegimo žurnalą į saityną?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="164"/>
      <source>Error</source>
      <translation>Klaida</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="171"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="518"/>
      <source>&amp;Yes</source>
      <translation>&amp;Taip</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="172"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>&amp;No</source>
      <translation>&amp;Ne</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="178"/>
      <source>&amp;Close</source>
      <translation>&amp;Užverti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>Install Log Paste URL</source>
      <translation>Diegimo žurnalo įdėjimo URL</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Įkėlimas buvo nesėkmingas. Nebuvo atlikta jokio įdėjimo į saityną.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="208"/>
      <source>Calamares Initialization Failed</source>
      <translation>Calamares inicijavimas nepavyko</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="209"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>Nepavyksta įdiegti %1. Calamares nepavyko įkelti visų sukonfigūruotų modulių. Tai yra problema, susijusi su tuo, kaip distribucija naudoja diegimo programą Calamares.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="215"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Nepavyko įkelti šių modulių:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with setup?</source>
      <translation>Tęsti sąranką?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with installation?</source>
      <translation>Tęsti diegimą?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="329"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 sąrankos programa, siekdama nustatyti %2, ketina atlikti pakeitimus diske.&lt;br/&gt;&lt;strong&gt;Šių pakeitimų nebegalėsite atšaukti.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 diegimo programa, siekdama įdiegti %2, ketina atlikti pakeitimus diske.&lt;br/&gt;&lt;strong&gt;Šių pakeitimų nebegalėsite atšaukti.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Set up now</source>
      <translation>Nu&amp;statyti dabar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Install now</source>
      <translation>Į&amp;diegti dabar</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>Go &amp;back</source>
      <translation>&amp;Grįžti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Set up</source>
      <translation>Nu&amp;statyti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Install</source>
      <translation>Į&amp;diegti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="394"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Sąranka užbaigta. Užverkite sąrankos programą.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Diegimas užbaigtas. Užverkite diegimo programą.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Atsisakyti sąrankos, nieko sistemoje nekeičiant.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Atsisakyti diegimo, nieko sistemoje nekeičiant.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>&amp;Next</source>
      <translation>&amp;Toliau</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="413"/>
      <source>&amp;Back</source>
      <translation>&amp;Atgal</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Done</source>
      <translation>A&amp;tlikta</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="438"/>
      <source>&amp;Cancel</source>
      <translation>A&amp;tsisakyti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel setup?</source>
      <translation>Atsisakyti sąrankos?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel installation?</source>
      <translation>Atsisakyti diegimo?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="512"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Ar tikrai norite atsisakyti dabartinio sąrankos proceso?
Sąrankos programa užbaigs darbą ir visi pakeitimai bus prarasti.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Ar tikrai norite atsisakyti dabartinio diegimo proceso?
Diegimo programa užbaigs darbą ir visi pakeitimai bus prarasti.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="288"/>
      <source>Unknown exception type</source>
      <translation>Nežinomas išimties tipas</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="306"/>
      <source>unparseable Python error</source>
      <translation>Nepalyginama Python klaida</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="350"/>
      <source>unparseable Python traceback</source>
      <translation>Nepalyginamas Python atsekimas</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="357"/>
      <source>Unfetchable Python error.</source>
      <translation>Neatgaunama Python klaida.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="25"/>
      <source>Install log posted to:
%1</source>
      <translation>Diegimo žurnalas paskelbtas į:
%1</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="101"/>
      <source>Show debug information</source>
      <translation>Rodyti derinimo informaciją</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="155"/>
      <source>&amp;Back</source>
      <translation>&amp;Atgal</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="167"/>
      <source>&amp;Next</source>
      <translation>&amp;Toliau</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="180"/>
      <source>&amp;Cancel</source>
      <translation>A&amp;tsisakyti</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="304"/>
      <source>%1 Setup Program</source>
      <translation>%1 sąrankos programa</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="305"/>
      <source>%1 Installer</source>
      <translation>%1 diegimo programa</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="37"/>
      <source>Gathering system information...</source>
      <translation>Renkama sistemos informacija...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="120"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Pasirinkite atminties įr&amp;enginį:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="121"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1092"/>
      <source>Current:</source>
      <translation>Dabartinis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="122"/>
      <source>After:</source>
      <translation>Po:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="299"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Rankinis skaidymas&lt;/strong&gt;&lt;br/&gt;Galite patys kurti ar keisti skaidinių dydžius.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="822"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Pakartotinai naudoti %1 kaip namų skaidinį, skirtą %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Pasirinkite, kurį skaidinį sumažinti, o tuomet vilkite juostą, kad pakeistumėte skaidinio dydį&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="975"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 bus sumažintas iki %2MiB ir naujas %3MiB skaidinys bus sukurtas sistemai %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1031"/>
      <source>Boot loader location:</source>
      <translation>Paleidyklės vieta:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1083"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Pasirinkite kuriame skaidinyje įdiegti&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1142"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Šioje sistemoje niekur nepavyko rasti EFI skaidinio. Prašome grįžti ir naudoti rankinį skaidymą, kad nustatytumėte %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1150"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>%2 paleidimui bus naudojamas EFI sistemos skaidinys, esantis ties %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1158"/>
      <source>EFI system partition:</source>
      <translation>EFI sistemos skaidinys:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1291"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Atrodo, kad šiame įrenginyje nėra operacinės sistemos. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1333"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1355"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1380"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Ištrinti diską&lt;/strong&gt;&lt;br/&gt;Tai &lt;font color="red"&gt;ištrins&lt;/font&gt; visus, pasirinktame atminties įrenginyje, esančius duomenis.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1329"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1351"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1376"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Įdiegti šalia&lt;/strong&gt;&lt;br/&gt;Diegimo programa sumažins skaidinį, kad atlaisvintų vietą sistemai %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1304"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1338"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1359"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1384"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Pakeisti skaidinį&lt;/strong&gt;&lt;br/&gt;Pakeičia skaidinį ir įrašo %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1323"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Šiame atminties įrenginyje jau yra %1. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1346"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Šiame atminties įrenginyje jau yra operacinė sistema. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1371"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Šiame atminties įrenginyje jau yra kelios operacinės sistemos. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1443"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>Šiame atminties įrenginyje jau yra operacinė sistema, bet skaidinių lentelė &lt;strong&gt;%1&lt;/strong&gt; yra kitokia nei reikiama &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1466"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <translation>Vienas iš šio atminties įrenginio skaidinių yra &lt;strong&gt;prijungtas&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1471"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <translation>Šis atminties įrenginys yra &lt;strong&gt;neaktyvaus RAID&lt;/strong&gt; įrenginio dalis.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1598"/>
      <source>No Swap</source>
      <translation>Be sukeitimų skaidinio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1606"/>
      <source>Reuse Swap</source>
      <translation>Iš naujo naudoti sukeitimų skaidinį</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1609"/>
      <source>Swap (no Hibernate)</source>
      <translation>Sukeitimų skaidinys (be užmigdymo)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1612"/>
      <source>Swap (with Hibernate)</source>
      <translation>Sukeitimų skaidinys (su užmigdymu)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1615"/>
      <source>Swap to file</source>
      <translation>Sukeitimų failas</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="42"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Išvalyti prijungimus, siekiant atlikti skaidymo operacijas skaidiniuose %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="49"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Išvalomi prijungimai, siekiant atlikti skaidymo operacijas skaidiniuose %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="224"/>
      <source>Cleared all mounts for %1</source>
      <translation>Visi %1 prijungimai išvalyti</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="32"/>
      <source>Clear all temporary mounts.</source>
      <translation>Išvalyti visus laikinuosius prijungimus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="39"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Išvalomi visi laikinieji prijungimai.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="51"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Nepavyksta gauti laikinųjų prijungimų sąrašo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="92"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Visi laikinieji prijungimai išvalyti.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="142"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>Could not run command.</source>
      <translation>Nepavyko paleisti komandos.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="143"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>Komanda yra vykdoma serverio aplinkoje ir turi žinoti šaknies kelią, tačiau nėra apibrėžtas joks rootMountPoint.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="156"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Komanda turi žinoti naudotojo vardą, tačiau nebuvo apibrėžtas joks naudotojo vardas.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="326"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Nustatyti klaviatūros modelį kaip %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="333"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Nustatyti klaviatūros išdėstymą kaip %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="334"/>
      <source>Set timezone to %1/%2.</source>
      <translation>Nustatyti laiko juostą į %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="372"/>
      <source>The system language will be set to %1.</source>
      <translation>Sistemos kalba bus nustatyta į %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="379"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>Skaičių ir datų lokalė bus nustatyta į %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="38"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Tinklo diegimas. (Išjungtas: Neteisinga konfigūracija)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="40"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Tinklo diegimas. (Išjungtas: Gauti neteisingi grupių duomenys)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="42"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation>Tinklo diegimas. (Išjungtas: vidinė klaida)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="44"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Tinklo diegimas. (Išjungta: Nepavyksta gauti paketų sąrašus, patikrinkite savo tinklo ryšį)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="50"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Šis kompiuteris netenkina minimalių %1 nustatymo reikalavimų.&lt;br/&gt;Sąranka negali būti tęsiama. &lt;a href="#details"&gt;Išsamiau...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="54"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Šis kompiuteris netenkina minimalių %1 diegimo reikalavimų.&lt;br/&gt;Diegimas negali būti tęsiamas. &lt;a href="#details"&gt;Išsamiau...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="61"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Šis kompiuteris netenkina kai kurių %1 nustatymui rekomenduojamų reikalavimų.&lt;br/&gt;Sąranką galima tęsti, tačiau kai kurios funkcijos gali būti išjungtos.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="65"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Šis kompiuteris netenkina kai kurių %1 diegimui rekomenduojamų reikalavimų.&lt;br/&gt;Diegimą galima tęsti, tačiau kai kurios funkcijos gali būti išjungtos.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="75"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Programa užduos kelis klausimus ir padės įsidiegti %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="244"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;/h1&gt;Jus sveikina Calamares sąrankos programa, skirta %1 sistemai.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="245"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina %1 sąranka&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="250"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina Calamares diegimo programa, skirta %1 sistemai&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="251"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina %1 diegimo programa&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="212"/>
      <source>Your username is too long.</source>
      <translation>Jūsų naudotojo vardas yra pernelyg ilgas.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="218"/>
      <source>'%1' is not allowed as username.</source>
      <translation>„%1“ neleidžiama naudoti kaip naudotojo vardą.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="225"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Jūsų naudotojo vardas privalo prasidėti mažąja raide arba pabraukimo brūkšniu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="229"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yra leidžiamos tik mažosios raidės, skaitmenys, pabraukimo brūkšniai ir brūkšneliai.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="274"/>
      <source>Your hostname is too short.</source>
      <translation>Jūsų kompiuterio vardas yra pernelyg trumpas.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="278"/>
      <source>Your hostname is too long.</source>
      <translation>Jūsų kompiuterio vardas yra pernelyg ilgas.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="284"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>„%1“ neleidžiama naudoti kaip kompiuterio vardą.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="290"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yra leidžiamos tik raidės, skaitmenys, pabraukimo brūkšniai ir brūkšneliai.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="527"/>
      <source>Your passwords do not match!</source>
      <translation>Jūsų slaptažodžiai nesutampa!</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="119"/>
      <source>Contextual Processes Job</source>
      <translation>Konteksto procesų užduotis</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Sukurti skaidinį</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>D&amp;ydis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Skaidinio tipas:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>&amp;Primary</source>
      <translation>&amp;Pirminis</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>Iš&amp;plėstinė</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>Fai&amp;lų sistema:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM LV pavadinimas</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Prijungimo vieta:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="192"/>
      <source>Flags:</source>
      <translation>Vėliavėlės:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
      <source>En&amp;crypt</source>
      <translation>Užši&amp;fruoti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="161"/>
      <source>Logical</source>
      <translation>Loginis</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="166"/>
      <source>Primary</source>
      <translation>Pirminis</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="185"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="265"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Prijungimo taškas jau yra naudojamas. Prašome pasirinkti kitą.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="38"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Sukurti naują %2MiB skaidinį diske %4 (%3) su %1 failų sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="49"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sukurti naują &lt;strong&gt;%2MiB&lt;/strong&gt; skaidinį diske &lt;strong&gt;%4&lt;/strong&gt; (%3) su &lt;strong&gt;%1&lt;/strong&gt; failų sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="61"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Kuriamas naujas %1 skaidinys ties %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="73"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Diegimo programai nepavyko sukurti skaidinio diske '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Sukurti skaidinių lentelę</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Naujos skaidinių lentelės kūrimas ištrins visus, diske esančius, duomenis.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Kokio tipo skaidinių lentelę norite sukurti?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Paleidimo Įrašas (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID Skaidinių lentelė (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="39"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Sukurti naują %1 skaidinių lentelę ties %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Sukurti naują &lt;strong&gt;%1&lt;/strong&gt; skaidinių lentelę diske &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="57"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Kuriama nauja %1 skaidinių lentelė ties %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="75"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Diegimo programai nepavyko %1 sukurti skaidinių lentelės.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="36"/>
      <source>Create user %1</source>
      <translation>Sukurti naudotoją %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="43"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sukurti naudotoją &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="126"/>
      <source>Preserving home directory</source>
      <translation>Išsaugomas namų katalogas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="143"/>
      <source>Creating user %1</source>
      <translation>Kuriamas naudotojas %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="151"/>
      <source>Configuring user %1</source>
      <translation>Konfigūruojamas naudotojas %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
      <source>Setting file permissions</source>
      <translation>Nustatomi failų leidimai</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <translation>Sukurti tomų grupę</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="31"/>
      <source>Create new volume group named %1.</source>
      <translation>Sukurti naują tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sukurti naują tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Creating new volume group named %1.</source>
      <translation>Kuriama nauja tomų grupė, pavadinimu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="55"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Diegimo programai nepavyko sukurti tomų grupės pavadinimu „%1“.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="36"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Pasyvinti tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="30"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Pasyvinti tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Diegimo programai nepavyko pasyvinti tomų grupės, pavadinimu "%1".</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="31"/>
      <source>Delete partition %1.</source>
      <translation>Ištrinti skaidinį %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="38"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ištrinti skaidinį &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="45"/>
      <source>Deleting partition %1.</source>
      <translation>Ištrinamas skaidinys %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Diegimo programai nepavyko ištrinti skaidinio %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="97"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Šiame įrenginyje yra &lt;strong&gt;%1&lt;/strong&gt; skaidinių lentelė.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Tai yra &lt;strong&gt;ciklo&lt;/strong&gt; įrenginys.&lt;br&gt;&lt;br&gt;Tai pseudo-įrenginys be skaidinių lentelės, kuris failą padaro prieinamą kaip bloko įrenginį. Tokio tipo sąrankoje, dažniausiai, yra tik viena failų sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="111"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Šiai diegimo programai, pasirinktame atminties įrenginyje, &lt;strong&gt;nepavyko aptikti skaidinių lentelės&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Arba įrenginyje nėra skaidinių lentelės, arba ji yra pažeista, arba nežinomo tipo.&lt;br&gt;Ši diegimo programa gali jums sukurti skaidinių lentelę automatiškai arba per rankinio skaidymo puslapį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Tai yra rekomenduojamas skaidinių lentelės tipas, skirtas šiuolaikinėms sistemoms, kurios yra paleidžiamos iš &lt;strong&gt;EFI&lt;/strong&gt; paleidimo aplinkos.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="127"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Šį skaidinių lentelės tipą yra patartina naudoti tik senesnėse sistemose, kurios yra paleidžiamos iš &lt;strong&gt;BIOS&lt;/strong&gt; paleidimo aplinkos. Visais kitais atvejais yra rekomenduojamas GPT tipas.&lt;br&gt;&lt;strong&gt;Įspėjimas:&lt;/strong&gt; MBR skaidinių lentelė yra pasenusio MS-DOS eros standarto.&lt;br&gt;Gali būti kuriami tik 4 &lt;em&gt;pirminiai&lt;/em&gt; skaidiniai, o iš tų 4, vienas gali būti &lt;em&gt;išplėstas&lt;/em&gt; skaidinys, kuriame savo ruožtu gali būti daug &lt;em&gt;loginių&lt;/em&gt; skaidinių.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="140"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Pasirinktame atminties įrenginyje esančios, &lt;strong&gt;skaidinių lentelės&lt;/strong&gt; tipas.&lt;br&gt;&lt;br&gt;Vienintelis būdas kaip galima pakeisti skaidinių lentelės tipą yra ištrinti ir iš naujo sukurti skaidinių lentelę, kas savo ruožtu ištrina visus atminties įrenginyje esančius duomenis.&lt;br&gt;Ši diegimo programa paliks esamą skaidinių lentelę, nebent aiškiai pasirinksite kitaip.&lt;br&gt;Jeigu nesate tikri, šiuolaikinėse sistemose pirmenybė yra teikiama GPT tipui.</translation>
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
      <translation>%1 - (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="117"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Dracut skirtąją LUKS konfigūraciją įrašyti į %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Praleisti LUKS konfigūracijos, kuri yra skirta Dracut, įrašymą: "/" skaidinys nėra užšifruotas</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <translation>Nepavyko atverti %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="37"/>
      <source>Dummy C++ Job</source>
      <translation>Fiktyvi C++ užduotis</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Keisti jau esamą skaidinį</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Content:</source>
      <translation>Turinys:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>Išsa&amp;ugoti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Formatuoti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Įspėjimas: Formatuojant skaidinį, sunaikinami visi jame esantys duomenys.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Prijungimo vieta:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="123"/>
      <source>Si&amp;ze:</source>
      <translation>Dy&amp;dis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="133"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="140"/>
      <source>Fi&amp;le System:</source>
      <translation>Fai&amp;lų sistema:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="153"/>
      <source>Flags:</source>
      <translation>Vėliavėlės:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="275"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Prijungimo taškas jau yra naudojamas. Prašome pasirinkti kitą.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Užš&amp;ifruoti sistemą</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="46"/>
      <source>Passphrase</source>
      <translation>Slaptafrazė</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="56"/>
      <source>Confirm passphrase</source>
      <translation>Patvirtinkite slaptafrazę</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="104"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="114"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Prašome abiejuose langeliuose įrašyti tą pačią slaptafrazę.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="138"/>
      <source>Set partition information</source>
      <translation>Nustatyti skaidinio informaciją</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="164"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Įdiegti %1 &lt;strong&gt;naujame&lt;/strong&gt; %2 sistemos skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="170"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nustatyti &lt;strong&gt;naują&lt;/strong&gt; %2 skaidinį su prijungimo tašku &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="180"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Diegti %2 sistemą, %3 sistemos skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="187"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Nustatyti %3 skaidinį &lt;strong&gt;%1&lt;/strong&gt; su prijungimo tašku &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="200"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Diegti paleidyklę skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="209"/>
      <source>Setting up mount points.</source>
      <translation>Nustatomi prijungimo taškai.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Paleisti iš naujo dabar</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="44"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Viskas atlikta.&lt;/h1&gt;&lt;br/&gt;%1 sistema jūsų kompiuteryje jau nustatyta.&lt;br/&gt;Dabar galite pradėti naudotis savo naująja sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Pažymėjus šį langelį, jūsų sistema nedelsiant pasileis iš naujo, kai spustelėsite &lt;span style="font-style:italic;"&gt;Atlikta&lt;/span&gt; ar užversite sąrankos programą.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Viskas atlikta.&lt;/h1&gt;&lt;br/&gt;%1 sistema jau įdiegta.&lt;br/&gt;Galite iš naujo paleisti kompiuterį dabar ir naudotis savo naująja sistema; arba galite tęsti naudojimąsi %2 sistema demonstracinėje aplinkoje.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="59"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Pažymėjus šį langelį, jūsų sistema nedelsiant pasileis iš naujo, kai spustelėsite &lt;span style="font-style:italic;"&gt;Atlikta&lt;/span&gt; ar užversite diegimo programą.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="116"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Sąranka nepavyko&lt;/h1&gt;&lt;br/&gt;%1 nebuvo nustatyta jūsų kompiuteryje.&lt;br/&gt;Klaidos pranešimas buvo: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="122"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Diegimas nepavyko&lt;/h1&gt;&lt;br/&gt;%1 nebuvo įdiegta jūsų kompiuteryje.&lt;br/&gt;Klaidos pranešimas buvo: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="67"/>
      <source>Finish</source>
      <translation>Pabaiga</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Setup Complete</source>
      <translation>Sąranka užbaigta</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Installation Complete</source>
      <translation>Diegimas užbaigtas</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="127"/>
      <source>The setup of %1 is complete.</source>
      <translation>%1 sąranka yra užbaigta.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="128"/>
      <source>The installation of %1 is complete.</source>
      <translation>%1 diegimas yra užbaigtas.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="36"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Formatuoti skaidinį %1 (failų sistema: %2, dydis: %3 MiB) diske %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="47"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Formatuoti &lt;strong&gt;%3MiB&lt;/strong&gt; skaidinį &lt;strong&gt;%1&lt;/strong&gt; su &lt;strong&gt;%2&lt;/strong&gt; failų sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="58"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Formatuojamas skaidinys %1 su %2 failų sistema.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="72"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Diegimo programai nepavyko formatuoti „%2“ disko skaidinio %1.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>turi bent %1 GiB laisvos vietos diske</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="151"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Neužtenka vietos diske. Reikia bent %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>has at least %1 GiB working memory</source>
      <translation>turi bent %1 GiB darbinės atminties</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Sistemai neužtenka darbinės atminties. Reikia bent %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="171"/>
      <source>is plugged in to a power source</source>
      <translation>prijungta prie maitinimo šaltinio</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="172"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Sistema nėra prijungta prie maitinimo šaltinio.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>is connected to the Internet</source>
      <translation>prijungta prie Interneto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Sistema nėra prijungta prie Interneto.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="187"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>vykdo diegimo programą pagrindinio naudotojo (root) teisėmis</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="190"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Sąrankos programa yra vykdoma be administratoriaus teisių.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="191"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Diegimo programa yra vykdoma be administratoriaus teisių.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="199"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>turi ekraną, pakankamai didelį, kad rodytų visą diegimo programą</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="202"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Ekranas yra per mažas, kad būtų parodyta sąrankos programa.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="203"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Ekranas yra per mažas, kad būtų parodyta diegimo programa.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="42"/>
      <source>Collecting information about your machine.</source>
      <translation>Renkama informacija apie jūsų kompiuterį.</translation>
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
      <translation>OEM partijos identifikatorius</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepavyko sukurti katalogų &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepavyko atverti failo &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepavyko rašyti į failą &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Sukuriama initramfs naudojant mkinitcpio.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="28"/>
      <source>Creating initramfs.</source>
      <translation>Sukuriama initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Konsole not installed</source>
      <translation>Konsole neįdiegta</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Įdiekite KDE Konsole ir bandykite dar kartą!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="102"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Vykdomas scenarijus: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="41"/>
      <source>Script</source>
      <translation>Scenarijus</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <translation>Klaviatūra</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Klaviatūra</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System locale setting</source>
      <translation>Sistemos lokalės nustatymas</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Sistemos lokalės nustatymas įtakoja, kai kurių komandų eilutės naudotojo sąsajos elementų, kalbos ir simbolių rinkinį.&lt;br/&gt;Dabar yra nustatyta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Atsisakyti</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;OK</source>
      <translation>&amp;Gerai</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licencijos sutartis&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="136"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Sutinku su aukščiau išdėstytomis nuostatomis ir sąlygomis.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="138"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>Peržiūrėkite galutinio naudotojo licencijos sutartis (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="143"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>Ši sąranka įdiegs nuosavybinę programinę įrangą, kuriai yra taikomos licencijavimo nuostatos.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="146"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>Jeigu nesutinkate su nuostatomis, sąrankos procedūra negali būti tęsiama.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>Tam, kad pateiktų papildomas ypatybes ir pagerintų naudotojo patirtį, ši sąrankos procedūra gali įdiegti nuosavybinę programinę įrangą, kuriai yra taikomos licencijavimo nuostatos.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>Jeigu nesutiksite su nuostatomis, nuosavybinė programinė įranga nebus įdiegta, o vietoj jos, bus naudojamos atvirojo kodo alternatyvos.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="43"/>
      <source>License</source>
      <translation>Licencija</translation>
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
      <translation>&lt;strong&gt;%1 tvarkyklė&lt;/strong&gt;&lt;br/&gt;iš %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 grafikos tvarkyklė&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 naršyklės papildinys&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 kodekas&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 paketas&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <translation>Failas: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide license text</source>
      <translation>Slėpti licencijos tekstą</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <translation>Rodyti licencijos tekstą</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open license agreement in browser.</source>
      <translation>Atverti licencijos sutartį naršyklėje.</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <translation>Regionas:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <translation>Sritis:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change...</source>
      <translation>K&amp;eisti...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <translation>Vieta</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="76"/>
      <source>Location</source>
      <translation>Vieta</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="28"/>
      <source>Configuring LUKS key file.</source>
      <translation>Konfigūruojamas LUKS raktų failas.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="168"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="176"/>
      <source>No partitions are defined.</source>
      <translation>Nėra jokių apibrėžtų skaidinių.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="211"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="218"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="226"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Šifruoto rootfs sąrankos klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="212"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Šaknies skaidinys %1 yra LUKS, tačiau nebuvo nustatyta jokia slaptafrazė.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="219"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Nepavyko šakniniam skaidiniui %1 sukurti LUKS rakto failo. </translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="227"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>Nepavyko konfigūruoti LUKS rakto failo skaidinyje %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="37"/>
      <source>Generate machine-id.</source>
      <translation>Generuoti machine-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="53"/>
      <source>Configuration Error</source>
      <translation>Konfigūracijos klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="54"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Nenustatytas joks šaknies prijungimo taškas, skirtas MachineId.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="243"/>
      <source>Timezone: %1</source>
      <translation>Laiko juosta: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="264"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation>Pasirinkite žemėlapyje pageidaujamą vietą, kad diegimo programa galėtų jums pasiūlyti
            lokalės ir laiko juostos nustatymus. Žemiau galite derinti pasiūlytus nustatymus. Tempkite norėdami judinti žemėlapį
            ir didinkite/mažinkite naudodami mygtukus +/- arba mastelio keitimui naudokite pelės ratuką.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="47"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Package selection</source>
      <translation>Paketų pasirinkimas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Office software</source>
      <translation>Raštinės programinė įranga</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Office package</source>
      <translation>Raštinės paketas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Browser software</source>
      <translation>Naršyklės programinė įranga</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Browser package</source>
      <translation>Naršyklės paketas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Web browser</source>
      <translation>Saityno naršyklė</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Kernel</source>
      <translation>Branduolys</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Services</source>
      <translation>Tarnybos</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Login</source>
      <translation>Prisijungimas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Desktop</source>
      <translation>Darbalaukis</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Applications</source>
      <translation>Programos</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Communication</source>
      <translation>Komunikacija</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Development</source>
      <translation>Plėtojimas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Office</source>
      <translation>Raštinė</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Multimedia</source>
      <translation>Multimedija</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Internet</source>
      <translation>Internetas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Theming</source>
      <translation>Apipavidalinimas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Gaming</source>
      <translation>Žaidimai</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Utilities</source>
      <translation>Paslaugų programos</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Pastabos</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Par&amp;tija:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Čia įveskite partijos identifikatorių. Jis bus saugomas paskirties sistemoje.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM konfigūracija&lt;/h1&gt;&lt;p&gt;Konfigūruojant paskirties sistemą, Calamares naudos OEM nustatymus.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="122"/>
      <source>OEM Configuration</source>
      <translation>OEM konfigūracija</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="128"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nustatyti OEM partijos identifikatorių į &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="37"/>
      <source>Select your preferred Region, or use the default one based on your current location.</source>
      <translation>Pasirinkite pageidaujamą regioną arba naudokite numatytąjį, kuris remiasi jūsų dabartine vieta.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="94"/>
      <location filename="../src/modules/localeq/Offline.qml" line="169"/>
      <location filename="../src/modules/localeq/Offline.qml" line="213"/>
      <source>Timezone: %1</source>
      <translation>Laiko juosta: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="111"/>
      <source>Select your preferred Zone within your Region.</source>
      <translation>Pasirinkite pageidaujamą sritį regiono ribose.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="182"/>
      <source>Zones</source>
      <translation>Sritys</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="229"/>
      <source>You can fine-tune Language and Locale settings below.</source>
      <translation>Žemiau galite derinti kalbos ir lokalės nustatymus.</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="51"/>
      <source>Password is too short</source>
      <translation>Slaptažodis yra per trumpas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
      <source>Password is too long</source>
      <translation>Slaptažodis yra per ilgas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>Password is too weak</source>
      <translation>Slaptažodis yra per silpnas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Atminties paskirstymo klaida, nustatant "%1"</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
      <source>Memory allocation error</source>
      <translation>Atminties paskirstymo klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
      <source>The password is the same as the old one</source>
      <translation>Slaptažodis yra toks pats kaip ir senas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="203"/>
      <source>The password is a palindrome</source>
      <translation>Slaptažodis yra palindromas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
      <source>The password differs with case changes only</source>
      <translation>Slaptažodyje skiriasi tik raidžių dydis</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="207"/>
      <source>The password is too similar to the old one</source>
      <translation>Slaptažodis pernelyg panašus į senąjį</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
      <source>The password contains the user name in some form</source>
      <translation>Slaptažodyje tam tikru pavidalu yra naudotojo vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="211"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Slaptažodyje tam tikra forma yra žodžiai iš tikrojo naudotojo vardo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Slaptažodyje tam tikra forma yra uždrausti žodžiai</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="221"/>
      <source>The password contains too few digits</source>
      <translation>Slaptažodyje yra per mažai skaitmenų</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="228"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Slaptažodyje yra per mažai didžiųjų raidžių</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="232"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n mažoji raidė</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n mažosios raidės</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n mažųjų raidžių</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n mažoji raidė</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Slaptažodyje yra per mažai mažųjų raidžių</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="242"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Slaptažodyje yra per mažai neraidinių ir neskaitinių simbolių</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="249"/>
      <source>The password is too short</source>
      <translation>Slaptažodis yra per trumpas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="258"/>
      <source>The password does not contain enough character classes</source>
      <translation>Slaptažodyje nėra pakankamai simbolių klasių</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Slaptažodyje yra per daug tokių pačių simbolių iš eilės</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Slaptažodyje yra per daug tos pačios klasės simbolių iš eilės</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n skaitmuo</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n skaitmenys</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n skaitmenų</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n skaitmuo</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n didžioji raidė</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n didžiosios raidės</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n didžiųjų raidžių</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n didžioji raidė</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n neraidinis ir neskaitinis simbolis</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n neraidiniai ir neskaitiniai simboliai</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n neraidinių ir neskaitinių simbolių</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n neraidinis ir neskaitinis simbolis</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="246"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolis</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simboliai</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolių</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolis</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Šis slaptažodis yra apversta senojo slaptažodžio versija</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolių klasė</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolių klasės</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolių klasių</numerusform>
        <numerusform>Slaptažodyje yra mažiau nei %n simbolių klasė</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="262"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Slaptažodyje yra daugiau nei %n toks pats simbolis iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n tokie patys simboliai iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n tokių pačių simbolių iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n toks pats simbolis iš eilės</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Slaptažodyje yra daugiau nei %n tos pačios klasės simbolis iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n tos pačios klasės simboliai iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n tos pačios klasės simbolių iš eilės</numerusform>
        <numerusform>Slaptažodyje yra daugiau nei %n tos pačios klasės simbolis iš eilės</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>Slaptažodyje yra ilgesnė nei %n simbolio monotoninė seka</numerusform>
        <numerusform>Slaptažodyje yra ilgesnė nei %n simbolių monotoninė seka</numerusform>
        <numerusform>Slaptažodyje yra ilgesnė nei %n simbolių monotoninė seka</numerusform>
        <numerusform>Slaptažodyje yra ilgesnė nei %n simbolio monotoninė seka</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="286"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Slaptažodyje yra per ilga monotoninių simbolių seka</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>No password supplied</source>
      <translation>Nepateiktas joks slaptažodis</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="291"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Nepavyksta gauti atsitiktinių skaičių iš RNG įrenginio</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Slaptažodžio generavimas nepavyko - reikalinga entropija nustatymams yra per maža</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Slaptažodis nepraeina žodyno patikros - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="301"/>
      <source>The password fails the dictionary check</source>
      <translation>Slaptažodis nepraeina žodyno patikros</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="305"/>
      <source>Unknown setting - %1</source>
      <translation>Nežinomas nustatymas - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="307"/>
      <source>Unknown setting</source>
      <translation>Nežinomas nustatymas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="311"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Bloga nustatymo sveikojo skaičiaus reikšmė - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="313"/>
      <source>Bad integer value</source>
      <translation>Bloga sveikojo skaičiaus reikšmė</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="317"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Nustatymas %1 nėra sveikojo skaičiaus tipo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="319"/>
      <source>Setting is not of integer type</source>
      <translation>Nustatymas nėra sveikojo skaičiaus tipo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="323"/>
      <source>Setting %1 is not of string type</source>
      <translation>Nustatymas %1 nėra eilutės tipo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="325"/>
      <source>Setting is not of string type</source>
      <translation>Nustatymas nėra eilutės tipo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="327"/>
      <source>Opening the configuration file failed</source>
      <translation>Konfigūracijos failo atvėrimas nepavyko</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="329"/>
      <source>The configuration file is malformed</source>
      <translation>Konfigūracijos failas yra netaisyklingas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="331"/>
      <source>Fatal failure</source>
      <translation>Lemtingoji klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="333"/>
      <source>Unknown error</source>
      <translation>Nežinoma klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="775"/>
      <source>Password is empty</source>
      <translation>Slaptažodis yra tuščias</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="24"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="44"/>
      <source>Product Name</source>
      <translation>Produkto pavadinimas</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="57"/>
      <source>TextLabel</source>
      <translation>Teksto etiketė</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="73"/>
      <source>Long Product Description</source>
      <translation>Ilgas produkto aprašas</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Paketų pasirinkimas</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Pasirinkite iš sąrašo produktą. Pasirinktas produktas bus įdiegtas.</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="61"/>
      <source>Packages</source>
      <translation>Paketai</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Name</source>
      <translation>Pavadinimas</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Description</source>
      <translation>Aprašas</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard Model:</source>
      <translation>Klaviatūros modelis:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="135"/>
      <source>Type here to test your keyboard</source>
      <translation>Rašykite čia ir išbandykite savo klaviatūrą</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Koks jūsų vardas?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Jūsų visas vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Kokį vardą norite naudoti prisijungimui?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>prisijungimas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Koks šio kompiuterio vardas?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Šis vardas bus naudojamas, jeigu padarysite savo kompiuterį matomą kitiems naudotojams tinkle.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Kompiuterio vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Apsaugokite savo paskyrą slaptažodžiu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus. Stiprus slaptažodis yra raidžių, skaičių ir punktuacijos ženklų mišinys, jis turi būti mažiausiai aštuonių simbolių, be to, turėtų būti reguliariai keičiamas.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Slaptažodis</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Pakartokite slaptažodį</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Pažymėjus šį langelį, bus atliekamas slaptažodžio stiprumo tikrinimas ir negalėsite naudoti silpną slaptažodį.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Reikalauti stiprių slaptažodžių.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Prisijungti automatiškai, neklausiant slaptažodžio.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Naudoti tokį patį slaptažodį administratoriaus paskyrai.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Pasirinkite slaptažodį administratoriaus paskyrai.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="190"/>
      <source>Root</source>
      <translation>Šaknies</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="194"/>
      <source>Home</source>
      <translation>Namų</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
      <source>Boot</source>
      <translation>Paleidimo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
      <source>EFI system</source>
      <translation>EFI sistema</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Sukeitimų (swap)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition for %1</source>
      <translation>Naujas skaidinys, skirtas %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="215"/>
      <source>New partition</source>
      <translation>Naujas skaidinys</translation>
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
      <translation>Laisva vieta</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="163"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="203"/>
      <source>New partition</source>
      <translation>Naujas skaidinys</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="296"/>
      <source>Name</source>
      <translation>Pavadinimas</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="298"/>
      <source>File System</source>
      <translation>Failų sistema</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="300"/>
      <source>Mount Point</source>
      <translation>Prijungimo vieta</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="302"/>
      <source>Size</source>
      <translation>Dydis</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Atminties įre&amp;nginys:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>&amp;Sugrąžinti visus pakeitimus</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Nauja skaidinių &amp;lentelė</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Su&amp;kurti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Keisti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>Iš&amp;trinti</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Nauja tomų grupė</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Keisti tomų grupės dydį</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Pasyvinti tomų grupę</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Šalinti tomų grupę</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Į&amp;diegti paleidyklę skaidinyje:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="219"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Ar tikrai %1 norite sukurti naują skaidinių lentelę?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="254"/>
      <source>Can not create new partition</source>
      <translation>Nepavyksta sukurti naują skaidinį</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="255"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>Skaidinių lentelėje ties %1 jau yra %2 pirminiai skaidiniai ir daugiau nebegali būti pridėta. Pašalinkite vieną pirminį skaidinį ir vietoj jo, pridėkite išplėstą skaidinį.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="70"/>
      <source>Gathering system information...</source>
      <translation>Renkama sistemos informacija...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="125"/>
      <source>Partitions</source>
      <translation>Skaidiniai</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Diegti %1 &lt;strong&gt;šalia&lt;/strong&gt; kitos operacinės sistemos.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Ištrinti&lt;/strong&gt; diską ir diegti %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="170"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Pakeisti&lt;/strong&gt; skaidinį, įrašant %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="174"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;Rankinis&lt;/strong&gt; skaidymas.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="187"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Įdiegti %1 &lt;strong&gt;šalia&lt;/strong&gt; kitos operacinės sistemos diske &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="194"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Ištrinti&lt;/strong&gt; diską &lt;strong&gt;%2&lt;/strong&gt; (%3) ir diegti %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="200"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Pakeisti&lt;/strong&gt; skaidinį diske &lt;strong&gt;%2&lt;/strong&gt; (%3), įrašant %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="207"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;Rankinis&lt;/strong&gt; skaidymas diske &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="216"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Diskas &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="242"/>
      <source>Current:</source>
      <translation>Dabartinis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="260"/>
      <source>After:</source>
      <translation>Po:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="427"/>
      <source>No EFI system partition configured</source>
      <translation>Nėra sukonfigūruoto EFI sistemos skaidinio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="428"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>EFI sistemos skaidinys yra būtinas, norint paleisti %1.&lt;br/&gt;&lt;br/&gt;Norėdami sukonfigūruoti EFI sistemos skaidinį, grįžkite atgal ir pasirinkite arba sukurkite FAT32 failų sistemą su įjungta &lt;strong&gt;%3&lt;/strong&gt; vėliavėle ir &lt;strong&gt;%2&lt;/strong&gt; prijungimo tašku.&lt;br/&gt;&lt;br/&gt;Jūs galite tęsti ir nenustatę EFI sistemos skaidinio, tačiau tokiu atveju, gali nepavykti paleisti jūsų sistemos.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="442"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation>EFI sistemos skaidinys yra būtinas, norint paleisti %1.&lt;br/&gt;&lt;br/&gt;Skaidinys buvo sukonfigūruotas su prijungimo tašku &lt;strong&gt;%2&lt;/strong&gt;, tačiau jo &lt;strong&gt;%3&lt;/strong&gt; vėliavėlė yra nenustatyta.&lt;br/&gt;Norėdami nustatyti vėliavėlę, grįžkite atgal ir taisykite skaidinį.&lt;br/&gt;&lt;br/&gt;Jūs galite tęsti ir nenustatę vėliavėlės, tačiau tokiu atveju, gali nepavykti paleisti jūsų sistemos.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="441"/>
      <source>EFI system partition flag not set</source>
      <translation>Nenustatyta EFI sistemos skaidinio vėliavėlė</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="468"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Parinktis naudoti GPT per BIOS</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="469"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>GPT skaidinių lentelė yra geriausias variantas visoms sistemoms. Ši diegimo programa palaiko tokią sąranką taip pat ir BIOS sistemoms.&lt;br/&gt;&lt;br/&gt;Norėdami konfigūruoti GPT skaidinių lentelę BIOS sistemoje, (jei dar nesate to padarę) grįžkite atgal ir nustatykite skaidinių lentelę į GPT, toliau, sukurkite 8 MB neformatuotą skaidinį su įjungta &lt;strong&gt;bios_grub&lt;/strong&gt; vėliavėle.&lt;br/&gt;&lt;br/&gt;Neformatuotas 8 MB skaidinys yra būtinas, norint paleisti %1 BIOS sistemoje su GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="497"/>
      <source>Boot partition not encrypted</source>
      <translation>Paleidimo skaidinys nėra užšifruotas</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="498"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Kartu su užšifruotu šaknies skaidiniu, buvo nustatytas atskiras paleidimo skaidinys, tačiau paleidimo skaidinys nėra užšifruotas.&lt;br/&gt;&lt;br/&gt;Dėl tokios sąrankos iškyla tam tikrų saugumo klausimų, kadangi svarbūs sisteminiai failai yra laikomi neužšifruotame skaidinyje.&lt;br/&gt;Jeigu norite, galite tęsti, tačiau failų sistemos atrakinimas įvyks vėliau, sistemos paleidimo metu.&lt;br/&gt;Norėdami užšifruoti paleidimo skaidinį, grįžkite atgal ir sukurkite jį iš naujo bei skaidinių kūrimo lange pažymėkite parinktį &lt;strong&gt;Užšifruoti&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="627"/>
      <source>has at least one disk device available.</source>
      <translation>turi bent vieną prieinamą disko įrenginį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="628"/>
      <source>There are no partitions to install on.</source>
      <translation>Nėra skaidinių į kuriuos diegti.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Plasma išvaizdos ir turinio užduotis</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Nepavyko pasirinkti KDE Plasma išvaizdos ir turinio paketo</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="79"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Pasirinkite KDE Plasma darbalaukio išvaizdą ir turinį. Taip pat galite praleisti šį žingsnį ir konfigūruoti išvaizdą ir turinį, kai sistema bus nustatyta. Spustelėjus ant tam tikro išvaizdos ir turinio pasirinkimo, jums bus parodyta tiesioginė peržiūrą.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="84"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Pasirinkite KDE Plasma darbalaukio išvaizdą ir turinį. Taip pat galite praleisti šį žingsnį ir konfigūruoti išvaizdą ir turinį, kai sistema bus įdiegta. Spustelėjus ant tam tikro išvaizdos ir turinio pasirinkimo, jums bus parodyta tiesioginė peržiūrą.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <translation>Išvaizda ir turinys</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="79"/>
      <source>Saving files for later ...</source>
      <translation>Įrašomi failai vėlesniam naudojimui ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="118"/>
      <source>No files configured to save for later.</source>
      <translation>Nėra sukonfigūruota įrašyti jokius failus vėlesniam naudojimui.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="172"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Ne visus iš sukonfigūruotų failų pavyko išsaugoti.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="412"/>
      <source>
There was no output from the command.</source>
      <translation>
Nebuvo jokios išvesties iš komandos.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="413"/>
      <source>
Output:
</source>
      <translation>
Išvestis:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="417"/>
      <source>External command crashed.</source>
      <translation>Išorinė komanda užstrigo.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Komanda &lt;i&gt;%1&lt;/i&gt; užstrigo.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>External command failed to start.</source>
      <translation>Nepavyko paleisti išorinės komandos.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Nepavyko paleisti komandos &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>Internal error when starting command.</source>
      <translation>Paleidžiant komandą, įvyko vidinė klaida.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>Bad parameters for process job call.</source>
      <translation>Blogi parametrai proceso užduoties iškvietai.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="433"/>
      <source>External command failed to finish.</source>
      <translation>Nepavyko pabaigti išorinės komandos.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Nepavyko per %2 sek. pabaigti komandos &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="441"/>
      <source>External command finished with errors.</source>
      <translation>Išorinė komanda pabaigta su klaidomis.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="442"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Komanda &lt;i&gt;%1&lt;/i&gt; pabaigta su išėjimo kodu %2.</translation>
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
      <translation>nežinoma</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="30"/>
      <source>extended</source>
      <translation>išplėsta</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="32"/>
      <source>unformatted</source>
      <translation>nesutvarkyta</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="34"/>
      <source>swap</source>
      <translation>sukeitimų (swap)</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="130"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="167"/>
      <source>Default</source>
      <translation>Numatytasis</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="72"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="76"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>File not found</source>
      <translation>Failas nerastas</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="65"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Kelias &lt;pre&gt;%1&lt;/pre&gt; privalo būti absoliutus kelias.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="83"/>
      <source>Directory not found</source>
      <translation>Katalogas nerastas</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="84"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="94"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nepavyko sukurti naujo atsitiktinio failo &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="70"/>
      <source>No product</source>
      <translation>Nėra produkto</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="78"/>
      <source>No description provided.</source>
      <translation>Nepateikta jokio aprašo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="40"/>
      <source>(no mount point)</source>
      <translation>(nėra prijungimo taško)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="41"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Nesuskaidyta vieta arba nežinoma skaidinių lentelė</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Šis kompiuteris netenkina kai kurių %1 nustatymui keliamų rekomenduojamų reikalavimų.&lt;br/&gt;
        Sąranką galima tęsti, bet kai kurios ypatybės gali būti išjungtos.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="34"/>
      <source>Remove live user from target system</source>
      <translation>Šalinti demonstracinį naudotoją iš paskirties sistemos</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="36"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Šalinti tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="30"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Šalinti tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Diegimo programai nepavyko pašalinti tomų grupės, pavadinimu "%1".</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="127"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Pasirinkite, kur norėtumėte įdiegti %1.&lt;br/&gt;&lt;font color="red"&gt;Įspėjimas: &lt;/font&gt;tai ištrins visus, pasirinktame skaidinyje esančius, failus.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="149"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Pasirinktas elementas neatrodo kaip teisingas skaidinys.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="157"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 negali būti įdiegta laisvoje vietoje. Prašome pasirinkti esamą skaidinį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="167"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 negali būti įdiegta išplėstame skaidinyje. Prašome pasirinkti esamą pirminį ar loginį skaidinį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="177"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 negali būti įdiegta šiame skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="183"/>
      <source>Data partition (%1)</source>
      <translation>Duomenų skaidinys (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="203"/>
      <source>Unknown system partition (%1)</source>
      <translation>Nežinomas sistemos skaidinys (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="207"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 sistemos skaidinys (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="218"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Skaidinys %1 yra pernelyg mažas sistemai %2. Prašome pasirinkti skaidinį, kurio dydis siektų bent %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="240"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Šioje sistemoje niekur nepavyko rasti EFI skaidinio. Prašome grįžti ir naudoti rankinį skaidymą, kad nustatytumėte %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="251"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="292"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 sistema bus įdiegta skaidinyje %2.&lt;br/&gt;&lt;font color="red"&gt;Įspėjimas: &lt;/font&gt;visi duomenys skaidinyje %2 bus prarasti.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="259"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>%2 paleidimui bus naudojamas EFI sistemos skaidinys, esantis %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="275"/>
      <source>EFI system partition:</source>
      <translation>EFI sistemos skaidinys:</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="38"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Šis kompiuteris netenkina minimalių %1 diegimo reikalavimų.&lt;br/&gt;
        Diegimas negali būti tęsiamas.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Šis kompiuteris netenkina kai kurių %1 nustatymui keliamų rekomenduojamų reikalavimų.&lt;br/&gt;
        Sąranką galima tęsti, bet kai kurios ypatybės gali būti išjungtos.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="46"/>
      <source>Resize Filesystem Job</source>
      <translation>Failų sistemos dydžio keitimo užduotis</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>Invalid configuration</source>
      <translation>Neteisinga konfigūracija</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>Failų sistemos dydžio keitimo užduotyje yra neteisinga konfigūracija ir užduotis nebus paleista.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="175"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore neprieinama</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="176"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>Diegimo programai Calamares nepavyksta paleisti KPMCore, kuri skirta failų sistemos dydžio keitimo užduočiai.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="184"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="193"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="204"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="231"/>
      <source>Resize Failed</source>
      <translation>Dydžio pakeisti nepavyko</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>Šioje sistemoje nepavyko rasti %1 failų sistemos ir nepavyko pakeisti jos dydį.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>Šioje sistemoje nepavyko rasti %1 įrenginio ir nepavyko pakeisti jo dydį.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>%1 failų sistemos dydis negali būti pakeistas.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The device %1 cannot be resized.</source>
      <translation>%1 įrenginio dydis negali būti pakeistas.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>%1 failų sistemos dydis privalo būti pakeistas, tačiau tai negali būti atlikta.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="215"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>%1 įrenginio dydis privalo būti pakeistas, tačiau tai negali būti atlikta</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="40"/>
      <source>Resize partition %1.</source>
      <translation>Keisti skaidinio %1 dydį.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="47"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>Pakeisti &lt;strong&gt;%2MiB&lt;/strong&gt; skaidinio &lt;strong&gt;%1&lt;/strong&gt; dydį iki &lt;strong&gt;%3MiB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="58"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Keičiamas %2MiB skaidinio %1 dydis iki %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="77"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Diegimo programai nepavyko pakeisti skaidinio %1 dydį diske '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <translation>Keisti tomų grupės dydį</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="27"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>Keisti tomų grupės, pavadinimu %1, dydį iš %2 į %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Keisti tomų grupės, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;, dydį iš &lt;strong&gt;%2&lt;/strong&gt; į &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="60"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Diegimo programai nepavyko pakeisti tomų grupės, kurios pavadinimas „%1“, dydžio.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="133"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>Norėdami pasiekti geriausių rezultatų, įsitikinkite kad šis kompiuteris:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="134"/>
      <source>System requirements</source>
      <translation>Sistemos reikalavimai</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="256"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Šis kompiuteris netenkina minimalių %1 nustatymo reikalavimų.&lt;br/&gt;Sąranka negali būti tęsiama. &lt;a href="#details"&gt;Išsamiau...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="260"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Šis kompiuteris netenkina minimalių %1 diegimo reikalavimų.&lt;br/&gt;Diegimas negali būti tęsiamas. &lt;a href="#details"&gt;Išsamiau...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="267"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Šis kompiuteris netenkina kai kurių %1 nustatymui rekomenduojamų reikalavimų.&lt;br/&gt;Sąranką galima tęsti, tačiau kai kurios funkcijos gali būti išjungtos.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="271"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Šis kompiuteris netenkina kai kurių %1 diegimui rekomenduojamų reikalavimų.&lt;br/&gt;Diegimą galima tęsti, tačiau kai kurios funkcijos gali būti išjungtos.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="280"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Programa užduos kelis klausimus ir padės įsidiegti %2.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Scanning storage devices...</source>
      <translation>Peržiūrimi atminties įrenginiai...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Partitioning</source>
      <translation>Skaidymas</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
      <source>Set hostname %1</source>
      <translation>Nustatyti kompiuterio vardą %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nustatyti kompiuterio vardą &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
      <source>Setting hostname %1.</source>
      <translation>Nustatomas kompiuterio vardas %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="122"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="129"/>
      <source>Internal Error</source>
      <translation>Vidinė klaida</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="137"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <source>Cannot write hostname to target system</source>
      <translation>Nepavyko įrašyti kompiuterio vardo į paskirties sistemą</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="55"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Nustatyti klaviatūros modelį kaip %1, o išdėstymą kaip %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Nepavyko įrašyti klaviatūros sąrankos virtualiam pultui.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="397"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="414"/>
      <source>Failed to write to %1</source>
      <translation>Nepavyko įrašyti į %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="396"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Nepavyko įrašyti klaviatūros sąrankos X11 aplinkai.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="413"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Nepavyko įrašyti klaviatūros konfigūracijos į esamą /etc/default katalogą.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="43"/>
      <source>Set flags on partition %1.</source>
      <translation>Nustatyti vėliavėles skaidinyje %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>Nustatyti vėliavėles %1MiB skaidinyje %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="53"/>
      <source>Set flags on new partition.</source>
      <translation>Nustatyti vėliavėles naujame skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Išvalyti vėliavėles skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Išvalyti vėliavėles %1MiB skaidinyje &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition.</source>
      <translation>Išvalyti vėliavėles naujame skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Pažymėti vėliavėle skaidinį &lt;strong&gt;%1&lt;/strong&gt; kaip &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Pažymėti vėliavėle %1MiB skaidinį &lt;strong&gt;%2&lt;/strong&gt; kaip &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="96"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Pažymėti vėliavėle naują skaidinį kaip &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="108"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Išvalomos vėliavėlės skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="114"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Išvalomos vėliavėlės %1MiB skaidinyje&lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="119"/>
      <source>Clearing flags on new partition.</source>
      <translation>Išvalomos vėliavėlės naujame skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="124"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nustatomos &lt;strong&gt;%2&lt;/strong&gt; vėliavėlės skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Nustatomos vėliavėlės &lt;strong&gt;%3&lt;/strong&gt;, %1MiB skaidinyje &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Nustatomos vėliavėlės &lt;strong&gt;%1&lt;/strong&gt; naujame skaidinyje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="156"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Diegimo programai nepavyko nustatyti vėliavėlių skaidinyje %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="40"/>
      <source>Set password for user %1</source>
      <translation>Nustatyti naudotojo %1 slaptažodį</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="47"/>
      <source>Setting password for user %1.</source>
      <translation>Nustatomas slaptažodis naudotojui %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>Bad destination system path.</source>
      <translation>Neteisingas paskirties sistemos kelias.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="82"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMountPoint yra %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="88"/>
      <source>Cannot disable root account.</source>
      <translation>Nepavyksta išjungti pagrindinio naudotojo (root) paskyros.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>passwd terminated with error code %1.</source>
      <translation>komanda passwd nutraukė darbą dėl klaidos kodo %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot set password for user %1.</source>
      <translation>Nepavyko nustatyti slaptažodžio naudotojui %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>usermod terminated with error code %1.</source>
      <translation>komanda usermod nutraukė darbą dėl klaidos kodo %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="34"/>
      <source>Set timezone to %1/%2</source>
      <translation>Nustatyti laiko juostą kaip %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="62"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Nepavyko pasiekti pasirinktos laiko zonos</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="63"/>
      <source>Bad path: %1</source>
      <translation>Neteisingas kelias: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot set timezone.</source>
      <translation>Negalima nustatyti laiko juostas.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Nuorodos sukūrimas nepavyko, paskirtis: %1; nuorodos pavadinimas: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="77"/>
      <source>Cannot set timezone,</source>
      <translation>Nepavyksta nustatyti laiko juostos,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="78"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Nepavyksta įrašymui atidaryti failo /etc/timezone</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="166"/>
      <source>Preparing groups.</source>
      <translation>Ruošiamos grupės.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="178"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="183"/>
      <source>Could not create groups in target system</source>
      <translation>Nepavyko paskirties sistemoje sukurti grupių</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="184"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>Paskirties sistemoje nėra šių grupių: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="33"/>
      <source>Configure &lt;pre&gt;sudo&lt;/pre&gt; users.</source>
      <translation>Konfigūruoti &lt;pre&gt;sudo&lt;/pre&gt; naudotojus.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="55"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Nepavyko pritaikyti chmod failui sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="60"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Nepavyko įrašymui sukurti failo sudoers.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="41"/>
      <source>Shell Processes Job</source>
      <translation>Apvalkalo procesų užduotis</translation>
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
      <translation>Tai yra apžvalga to, kas įvyks, prasidėjus sąrankos procedūrai.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="50"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Tai yra apžvalga to, kas įvyks, prasidėjus diegimo procedūrai.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="36"/>
      <source>Summary</source>
      <translation>Suvestinė</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="37"/>
      <source>Installation feedback</source>
      <translation>Grįžtamasis ryšys apie diegimą</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
      <source>Sending installation feedback.</source>
      <translation>Siunčiamas grįžtamasis ryšys apie diegimą.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="60"/>
      <source>Internal error in install-tracking.</source>
      <translation>Vidinė klaida diegimo sekime.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="61"/>
      <source>HTTP request timed out.</source>
      <translation>Baigėsi HTTP užklausos laikas.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="122"/>
      <source>KDE user feedback</source>
      <translation>KDE naudotojo grįžtamasis ryšys</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="128"/>
      <source>Configuring KDE user feedback.</source>
      <translation>Konfigūruojamas KDE naudotojo grįžtamasis ryšys.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="150"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="156"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>Klaida KDE naudotojo grįžtamojo ryšio konfigūracijoje.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="151"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>Nepavyko teisingai sukonfigūruoti KDE naudotojo grįžtamojo ryšio, scenarijaus klaida %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="157"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>Nepavyko teisingai sukonfigūruoti KDE naudotojo grįžtamojo ryšio, Calamares klaida %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Machine feedback</source>
      <translation>Grįžtamasis ryšys apie kompiuterį</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="77"/>
      <source>Configuring machine feedback.</source>
      <translation>Konfigūruojamas grįžtamasis ryšys apie kompiuterį.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Klaida grįžtamojo ryšio apie kompiuterį konfigūravime.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="101"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Nepavyko teisingai sukonfigūruoti grįžtamojo ryšio apie kompiuterį, scenarijaus klaida %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="107"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Nepavyko teisingai sukonfigūruoti grįžtamojo ryšio apie kompiuterį, Calamares klaida %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Vietaženklis</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Spustelėkite čia norėdami &lt;span style=" font-weight:600;"&gt;nesiųsti visiškai jokios informacijos&lt;/span&gt; apie savo diegimą.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Išsamesnei informacijai apie naudotojų grįžtamąjį ryšį, spustelėkite čia&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="86"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>Sekimas padeda matyti kaip dažnai yra įdiegiama %1, kokioje aparatinėje įrangoje ji yra įdiegiama bei kokios yra naudojamos programos. Norėdami pamatyti kas bus išsiųsta, šalia kiekvienos srities spustelėkite pagalbos piktogramą.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="91"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Tai pažymėdami, išsiųsite informaciją apie savo diegimą ir aparatinę įrangą. Ši informacija bus išsiųsta tik &lt;b&gt;vieną kartą&lt;/b&gt;, užbaigus diegimą.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="94"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Tai pažymėdami, jūs periodiškai siųsite informaciją apie savo &lt;b&gt;kompiuterio&lt;/b&gt; diegimą, aparatinę įrangą ir programas į %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="98"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Tai pažymėję, reguliariai į %1 siųsite informaciją apie savo &lt;b&gt;naudotojo&lt;/b&gt; diegimą, aparatinę įrangą, programas bei naudojimosi programomis šablonus.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <translation>Grįžtamasis ryšys</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="156"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jei šiuo kompiuteriu naudosis keli žmonės, po sąrankos galite sukurti papildomas paskyras.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="162"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jei šiuo kompiuteriu naudosis keli žmonės, po diegimo galite sukurti papildomas paskyras.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="39"/>
      <source>Users</source>
      <translation>Naudotojai</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Naudotojai</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Raktas</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Reikšmė</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Sukurti tomų grupę</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Fizinių tomų sąrašas</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Tomų grupės pavadinimas:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Tomų grupės tipas:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Fizinio masto dydis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Bendras dydis:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Panaudota:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Iš viso sektorių:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Loginių tomų skaičius:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="18"/>
      <source>Form</source>
      <translation>Forma</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Pasirinkite programų ir sistemos kalbą</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>&amp;About</source>
      <translation>&amp;Apie</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="150"/>
      <source>Open donations website</source>
      <translation>Atverti paaukojimų internetinę svetainę</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>&amp;Donate</source>
      <translation>&amp;Paaukoti</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="163"/>
      <source>Open help and support website</source>
      <translation>Atverti pagalbos ir palaikymo internetinę svetainę</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>&amp;Support</source>
      <translation>&amp;Palaikymas</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Atverti strigčių ir klaidų sekimo internetinę svetainę</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>&amp;Known issues</source>
      <translation>Ž&amp;inomos problemos</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="189"/>
      <source>Open release notes website</source>
      <translation>Atverti laidos informacijos internetinę svetainę</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="192"/>
      <source>&amp;Release notes</source>
      <translation>Lai&amp;dos informacija</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="216"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina Calamares sąrankos programa, skirta %1 sistemai.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="217"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina %1 sąranka.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="222"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina Calamares diegimo programa, skirta %1 sistemai.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Jus sveikina %1 diegimo programa.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="228"/>
      <source>%1 support</source>
      <translation>%1 palaikymas</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 setup</source>
      <translation>Apie %1 sąranką</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 installer</source>
      <translation>Apie %1 diegimo programą</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="238"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;skirta %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Autorių teisės 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Autorių teisės 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Dėkojame &lt;a href="https://calamares.io/team/"&gt;Calamares komandai&lt;/a&gt; ir &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares vertėjų komandai&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; plėtojimą remia &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Išlaisvinanti programinė įranga.</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="41"/>
      <source>Welcome</source>
      <translation>Pasisveikinimas</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="48"/>
      <source>Welcome</source>
      <translation>Pasisveikinimas</translation>
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
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;
                        &lt;strong&gt;%2&lt;br/&gt;
                        skirta %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;
                        Autorių teisės 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;
                        Autorių teisės 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;
                        Dėkojame &lt;a href='https://calamares.io/team/'&gt;Calamares komandai&lt;/a&gt;
                        ir &lt;a href='https://www.transifex.com/calamares/calamares/'&gt;Calamares
                        vertėjų komandai&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;
                        &lt;a href='https://calamares.io/'&gt;Calamares&lt;/a&gt;
                        plėtojimą remia &lt;br/&gt;
                        &lt;a href='http://www.blue-systems.com/'&gt;Blue Systems&lt;/a&gt; -
                        Išlaisvinanti programinė įranga.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="96"/>
      <source>Back</source>
      <translation>Atgal</translation>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="46"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Kalbos&lt;/h1&gt; &lt;/br&gt;
                    Sistemos lokalės nustatymas įtakoja, kai kurių komandų eilutės naudotojo sąsajos elementų, kalbos ir simbolių rinkinį. Dabar yra nustatyta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="106"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Lokalės&lt;/h1&gt; &lt;/br&gt;
                    Sistemos lokalės nustatymas įtakoja skaičių ir datų formatą. Dabar yra nustatyta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="158"/>
      <source>Back</source>
      <translation>Atgal</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="45"/>
      <source>Keyboard Model</source>
      <translation>Klaviatūros modelis</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="377"/>
      <source>Layouts</source>
      <translation>Išdėstymai</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="148"/>
      <source>Keyboard Layout</source>
      <translation>Klaviatūros išdėstymas</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="60"/>
      <source>Click your preferred keyboard model to select layout and variant, or use the default one based on the detected hardware.</source>
      <translation>Pasirinkite pageidaujamą klaviatūros modelį, kad pasirinktumėte išdėstymą ir variantą arba naudokite numatytąjį, kuris remiasi aptikta aparatine įranga.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="253"/>
      <source>Models</source>
      <translation>Modeliai</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="260"/>
      <source>Variants</source>
      <translation>Variantai</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="276"/>
      <source>Keyboard Variant</source>
      <translation>Klaviatūros variantas</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="386"/>
      <source>Test your keyboard</source>
      <translation>Išbandykite savo klaviatūrą</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="81"/>
      <source>Change</source>
      <translation>Keisti</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Tai yra pavyzdinė laidos informacija.&lt;/p&gt;</translation>
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
            &lt;p&gt;Tai yra pavyzdinis QML failas, rodantis parinktis raiškiuoju tekstu su interaktyviu turiniu.&lt;/p&gt;

            &lt;p&gt;QML su raiškiuoju tekstu gali naudoti HTML žymes, interaktyvus turinys yra naudingas jutikliniuose ekranuose.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Tai yra pusjuodis tekstas&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;Tai yra kursyvinis tekstas&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;Tai yra pabrauktas tekstas&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Šis tekstas bus lygiuojamas centre.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;Tai yra perbraukimas&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Kodo pavyzdžiai:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Sąrašai:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU sistemos&lt;/li&gt;
                &lt;li&gt;AMD CPU sistemos&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Vertikalioji slankjuostė yra reguliuojama, dabartinis plotis nustatytas į 10.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>Atgal</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="36"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Pasirinkite naudotojo vardą ir prisijungimo duomenis, kad galėtumėte prisijungti ir atlikti administravimo užduotis</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="52"/>
      <source>What is your name?</source>
      <translation>Koks jūsų vardas?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="59"/>
      <source>Your Full Name</source>
      <translation>Jūsų visas vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Kokį vardą norite naudoti prisijungimui?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login Name</source>
      <translation>Prisijungimo vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="103"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Jei šiuo kompiuteriu naudosis keli žmonės, po diegimo galėsite sukurti papildomas paskyras.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="118"/>
      <source>What is the name of this computer?</source>
      <translation>Koks šio kompiuterio vardas?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="125"/>
      <source>Computer Name</source>
      <translation>Kompiuterio vardas</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="140"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Šis vardas bus naudojamas, jeigu padarysite savo kompiuterį matomą kitiems naudotojams tinkle.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="155"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Apsaugokite savo paskyrą slaptažodžiu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="166"/>
      <source>Password</source>
      <translation>Slaptažodis</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="185"/>
      <source>Repeat Password</source>
      <translation>Pakartokite slaptažodį</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="204"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus. Stiprus slaptažodis yra raidžių, skaičių ir punktuacijos ženklų mišinys, jis turi būti mažiausiai aštuonių simbolių, be to, turėtų būti reguliariai keičiamas.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="216"/>
      <source>Validate passwords quality</source>
      <translation>Tikrinti slaptažodžių kokybę</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="226"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Pažymėjus šį langelį, bus atliekamas slaptažodžio stiprumo tikrinimas ir negalėsite naudoti silpną slaptažodį.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="234"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Prisijungti automatiškai, neklausiant slaptažodžio</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="243"/>
      <source>Reuse user password as root password</source>
      <translation>Naudotojo slaptažodį naudoti pakartotinai kaip pagrindinio naudotojo (root) slaptažodį</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="253"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Naudoti tokį patį slaptažodį administratoriaus paskyrai.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="268"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Pasirinkite pagrindinio naudotojo (root) slaptažodį, kad apsaugotumėte savo paskyrą.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="279"/>
      <source>Root Password</source>
      <translation>Pagrindinio naudotojo (Root) slaptažodis</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="298"/>
      <source>Repeat Root Password</source>
      <translation>Pakartokite pagrindinio naudotojo (Root) slaptažodį</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="35"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Jus sveikina %1 &lt;quote&gt;%2&lt;/quote&gt; diegimo programa&lt;/h3&gt;
            &lt;p&gt;Ši programa užduos jums kelis klausimus ir padės kompiuteryje nusistatyti %1.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="66"/>
      <source>About</source>
      <translation>Apie</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Support</source>
      <translation>Palaikymas</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Known issues</source>
      <translation>Žinomos problemos</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="102"/>
      <source>Release notes</source>
      <translation>Laidos informacija</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="114"/>
      <source>Donate</source>
      <translation>Paaukoti</translation>
    </message>
  </context>
</TS>

<?xml version="1.0" ?><!DOCTYPE TS><TS language="lt" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>Šios sistemos &lt;strong&gt;paleidimo aplinka&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Senesnės x86 sistemos palaiko tik &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Šiuolaikinės sistemos, dažniausiai, naudoja &lt;strong&gt;EFI&lt;/strong&gt;, tačiau, jeigu jos yra paleistos suderinamumo veiksenoje, taip pat gali būti rodomos kaip BIOS.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>Ši sistema buvo paleista su &lt;strong&gt;EFI&lt;/strong&gt; paleidimo aplinka.&lt;br&gt;&lt;br&gt;Tam, kad sukonfigūruotų paleidimą iš EFI aplinkos, ši diegimo programa, &lt;strong&gt;EFI sistemos skaidinyje&lt;/strong&gt;, privalo išskleisti paleidyklės programą, kaip, pavyzdžiui, &lt;strong&gt;GRUB&lt;/strong&gt; ar &lt;strong&gt;systemd-boot&lt;/strong&gt;. Tai vyks automatiškai, nebent pasirinksite rankinį skaidymą ir tokiu atveju patys turėsite pasirinkti arba sukurti skaidinį.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>Ši sistema buvo paleista su &lt;strong&gt;BIOS&lt;/strong&gt; paleidimo aplinka.&lt;br&gt;&lt;br&gt;Tam, kad sukonfigūruotų paleidimą iš BIOS aplinkos, ši diegimo programa, arba skaidinio pradžioje, arba &lt;strong&gt;Paleidimo įraše (MBR)&lt;/strong&gt;, šalia skaidinių lentelės pradžios (pageidautina), privalo įdiegti paleidyklę, kaip, pavyzdžiui, &lt;strong&gt;GRUB&lt;/strong&gt;. Tai vyks automatiškai, nebent pasirinksite rankinį skaidymą ir tokiu atveju, viską turėsite nusistatyti patys.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation> %1 paleidimo įrašas (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>Paleidimo skaidinys</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>Sistemos skaidinys</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>Nediegti paleidyklės</translation>
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
        <translation>Tuščias puslapis</translation>
    </message>
</context>
<context>
    <name>Calamares::DebugWindow</name>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>VisuotinisKaupiklis</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>DarboEilė</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>Moduliai</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation>Tipas:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation>nėra</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation>Sąsaja:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation>Įrankiai</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation>Derinimo informacija</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="79"/>
        <source>Install</source>
        <translation>Diegimas</translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="101"/>
        <source>Done</source>
        <translation>Atlikta</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
        <source>Run command %1 %2</source>
        <translation>Vykdyti komandą %1 %2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="61"/>
        <source>Running command %1 %2</source>
        <translation>Vykdoma komanda %1 %2</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="273"/>
        <source>Running %1 operation.</source>
        <translation>Vykdoma %1 operacija.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="288"/>
        <source>Bad working directory path</source>
        <translation>Netinkama darbinio katalogo vieta</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="289"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>Darbinis %1 python katalogas  dėl %2 užduoties yra neskaitomas</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="299"/>
        <source>Bad main script file</source>
        <translation>Prastas pagrindinio skripto failas</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="300"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>Pagrindinis scenarijus %1  dėl python %2 užduoties yra neskaitomas</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="376"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>Boost.Python klaida užduotyje &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Back</source>
        <translation>&amp;Atgal</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="279"/>
        <source>&amp;Next</source>
        <translation>&amp;Toliau</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="288"/>
        <source>&amp;Cancel</source>
        <translation>A&amp;tsisakyti</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="77"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="289"/>
        <source>Cancel installation without changing the system.</source>
        <translation>Atsisakyti diegimo, nieko sistemoje nekeičiant.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="179"/>
        <source>Calamares Initialization Failed</source>
        <translation>Calamares inicijavimas nepavyko</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="180"/>
        <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
        <translation>Nepavyksta įdiegti %1. Calamares nepavyko įkelti visų sukonfigūruotų modulių. Tai yra problema, susijusi su tuo, kaip distribucija naudoja diegimo programą Calamares.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="185"/>
        <source>&lt;br/&gt;The following modules could not be loaded:</source>
        <translation>&lt;br/&gt;Nepavyko įkelti šių modulių:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="277"/>
        <source>&amp;Install</source>
        <translation>Į&amp;diegti</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="325"/>
        <source>Cancel installation?</source>
        <translation>Atsisakyti diegimo?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="326"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>Ar tikrai norite atsisakyti dabartinio diegimo proceso?
Diegimo programa užbaigs darbą ir visi pakeitimai bus prarasti.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="331"/>
        <source>&amp;Yes</source>
        <translation>&amp;Taip</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
        <source>&amp;No</source>
        <translation>&amp;Ne</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="163"/>
        <source>&amp;Close</source>
        <translation>&amp;Užverti</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="237"/>
        <source>Continue with setup?</source>
        <translation>Tęsti sąranką?</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="238"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>%1 diegimo programa, siekdama įdiegti %2, ketina atlikti pakeitimus diske.&lt;br/&gt;&lt;strong&gt;Šių pakeitimų nebegalėsite atšaukti.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="243"/>
        <source>&amp;Install now</source>
        <translation>Į&amp;diegti dabar</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="244"/>
        <source>Go &amp;back</source>
        <translation>&amp;Grįžti</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="283"/>
        <source>&amp;Done</source>
        <translation>A&amp;tlikta</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="284"/>
        <source>The installation is complete. Close the installer.</source>
        <translation>Diegimas užbaigtas. Užverkite diegimo programą.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="160"/>
        <source>Error</source>
        <translation>Klaida</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="161"/>
        <source>Installation Failed</source>
        <translation>Diegimas nepavyko</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="270"/>
        <source>Unknown exception type</source>
        <translation>Nežinomas išimties tipas</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="284"/>
        <source>unparseable Python error</source>
        <translation>Nepalyginama Python klaida</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="324"/>
        <source>unparseable Python traceback</source>
        <translation>Nepalyginamas Python atsekimas</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="329"/>
        <source>Unfetchable Python error.</source>
        <translation>Neatgaunama Python klaida.</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="44"/>
        <source>%1 Installer</source>
        <translation>%1 diegimo programa</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="111"/>
        <source>Show debug information</source>
        <translation>Rodyti derinimo informaciją</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>Šis kompiuteris netenkina minimalių %1 diegimo reikalavimų.&lt;br/&gt;Diegimas negali būti tęsiamas. &lt;a href=&quot;#details&quot;&gt;Išsamiau...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>Šis kompiuteris netenkina kai kurių %1 diegimui rekomenduojamų reikalavimų.&lt;br/&gt;Diegimą galima tęsti, tačiau kai kurios funkcijos gali būti išjungtos.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>Programa užduos kelis klausimus ir padės įsidiegti %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>Norėdami pasiekti geriausių rezultatų, įsitikinkite kad šis kompiuteris:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation>Sistemos reikalavimai</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="131"/>
        <source>After:</source>
        <translation>Po:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="238"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;Rankinis skaidymas&lt;/strong&gt;&lt;br/&gt;Galite patys kurti ar keisti skaidinių dydžius.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1001"/>
        <source>Boot loader location:</source>
        <translation>Paleidyklės vieta:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="945"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>%1 bus sumažintas iki %2MB ir naujas %3MB skaidinys bus sukurtas sistemai %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="129"/>
        <source>Select storage de&amp;vice:</source>
        <translation>Pasirinkite atminties įr&amp;enginį:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="130"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="927"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1052"/>
        <source>Current:</source>
        <translation>Dabartinis:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="798"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation>Pakartotinai naudoti %1 kaip namų skaidinį, skirtą %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="928"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Pasirinkite, kurį skaidinį sumažinti, o tuomet vilkite juostą, kad pakeistumėte skaidinio dydį&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1043"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;Pasirinkite kuriame skaidinyje įdiegti&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1099"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>Šioje sistemoje niekur nepavyko rasti EFI skaidinio. Prašome grįžti ir naudoti rankinį skaidymą, kad nustatytumėte %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1108"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%2 paleidimui bus naudojamas EFI sistemos skaidinys, esantis ties %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1116"/>
        <source>EFI system partition:</source>
        <translation>EFI sistemos skaidinys:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Atrodo, kad šiame įrenginyje nėra operacinės sistemos. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1237"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1274"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1320"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;Ištrinti diską&lt;/strong&gt;&lt;br/&gt;Tai &lt;font color=&quot;red&quot;&gt;ištrins&lt;/font&gt; visus, pasirinktame atminties įrenginyje, esančius duomenis.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Šiame atminties įrenginyje jau yra %1. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1241"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1292"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1316"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;Įdiegti šalia&lt;/strong&gt;&lt;br/&gt;Diegimo programa sumažins skaidinį, kad atlaisvintų vietą sistemai %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1245"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1324"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;Pakeisti skaidinį&lt;/strong&gt;&lt;br/&gt;Pakeičia skaidinį ir įrašo %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1287"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Šiame atminties įrenginyje jau yra operacinė sistema. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1311"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>Šiame atminties įrenginyje jau yra kelios operacinės sistemos. Ką norėtumėte daryti?&lt;br/&gt;Prieš atliekant bet kokius pakeitimus atminties įrenginyje, jūs galėsite apžvelgti ir patvirtinti savo pasirinkimus.</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="46"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation>Išvalyti prijungimus, siekiant atlikti skaidymo operacijas skaidiniuose %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="54"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation>Išvalomi prijungimai, siekiant atlikti skaidymo operacijas skaidiniuose %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="191"/>
        <source>Cleared all mounts for %1</source>
        <translation>Visi %1 prijungimai išvalyti</translation>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation>Išvalyti visus laikinuosius prijungimus.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation>Išvalomi visi laikinieji prijungimai.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation>Nepavyksta gauti laikinųjų prijungimų sąrašo.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation>Visi laikinieji prijungimai išvalyti.</translation>
    </message>
</context>
<context>
    <name>CommandList</name>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="127"/>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="138"/>
        <source>Could not run command.</source>
        <translation>Nepavyko paleisti komandos.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="128"/>
        <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
        <translation>Komanda yra vykdoma serverio aplinkoje ir turi žinoti šaknies kelią, tačiau nėra apibrėžtas joks rootMountPoint.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CommandList.cpp" line="139"/>
        <source>The command needs to know the user&apos;s name, but no username is defined.</source>
        <translation>Komanda turi žinoti naudotojo vardą, tačiau nebuvo apibrėžtas joks naudotojo vardas.</translation>
    </message>
</context>
<context>
    <name>ContextualProcessJob</name>
    <message>
        <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="117"/>
        <source>Contextual Processes Job</source>
        <translation>Konteksto procesų užduotis</translation>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>Sukurti skaidinį</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>Skaidinio tipas:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>&amp;Pirminė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>Iš&amp;plėstinė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation>Fai&amp;lų sistema:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>LVM LV name</source>
        <translation>LVM LV pavadinimas</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
        <source>Flags:</source>
        <translation>Vėliavėlės:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Prijungimo vieta:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>D&amp;ydis:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="72"/>
        <source>En&amp;crypt</source>
        <translation>Užši&amp;fruoti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="151"/>
        <source>Logical</source>
        <translation>Loginė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="156"/>
        <source>Primary</source>
        <translation>Pagrindinė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="173"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="262"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>Prijungimo taškas jau yra naudojamas. Prašome pasirinkti kitą.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>Sukurti naują %2MB skaidinį diske %4 (%3) su %1 failų sistema.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sukurti naują &lt;strong&gt;%2MB&lt;/strong&gt; skaidinį diske &lt;strong&gt;%4&lt;/strong&gt; (%3) su &lt;strong&gt;%1&lt;/strong&gt; failų sistema.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>Kuriamas naujas %1 skaidinys ties %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>Diegimo programai nepavyko sukurti skaidinio diske &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>Sukurti skaidinių lentelę</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>Naujos skaidinių lentelės kūrimas ištrins visus, diske esančius, duomenis.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>Kokio tipo skaidinių lentelę norite sukurti?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>Paleidimo Įrašas (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>GUID Skaidinių lentelė (GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>Sukurti naują %1 skaidinių lentelę ties %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="54"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Sukurti naują &lt;strong&gt;%1&lt;/strong&gt; skaidinių lentelę diske &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="64"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>Kuriama nauja %1 skaidinių lentelė ties %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="82"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>Diegimo programai nepavyko %1 sukurti skaidinių lentelės.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
        <source>Create user %1</source>
        <translation>Sukurti naudotoją %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sukurti naudotoją &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
        <source>Creating user %1.</source>
        <translation>Kuriamas naudotojas %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="81"/>
        <source>Sudoers dir is not writable.</source>
        <translation>Nepavyko įrašymui sukurti katalogo sudoers.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="85"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>Nepavyko įrašymui sukurti failo sudoers.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="93"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>Nepavyko pritaikyti chmod failui sudoers.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="99"/>
        <source>Cannot open groups file for reading.</source>
        <translation>Nepavyko skaitymui atverti grupių failo.</translation>
    </message>
</context>
<context>
    <name>CreateVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
        <source>Create new volume group named %1.</source>
        <translation>Sukurti naują tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="45"/>
        <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sukurti naują tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="52"/>
        <source>Creating new volume group named %1.</source>
        <translation>Kuriama nauja tomų grupė, pavadinimu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="65"/>
        <source>The installer failed to create a volume group named &apos;%1&apos;.</source>
        <translation>Diegimo programai nepavyko sukurti tomų grupės, pavadinimu &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="34"/>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
        <source>Deactivate volume group named %1.</source>
        <translation>Pasyvinti tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="41"/>
        <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Pasyvinti tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="61"/>
        <source>The installer failed to deactivate a volume group named %1.</source>
        <translation>Diegimo programai nepavyko pasyvinti tomų grupės, pavadinimu &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
        <source>Delete partition %1.</source>
        <translation>Ištrinti skaidinį %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Ištrinti skaidinį &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
        <source>Deleting partition %1.</source>
        <translation>Ištrinamas skaidinys %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>Diegimo programai nepavyko ištrinti skaidinio %1.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>Pasirinktame atminties įrenginyje esančios, &lt;strong&gt;skaidinių lentelės&lt;/strong&gt; tipas.&lt;br&gt;&lt;br&gt;Vienintelis būdas kaip galima pakeisti skaidinių lentelės tipą yra ištrinti ir iš naujo sukurti skaidinių lentelę, kas savo ruožtu ištrina visus atminties įrenginyje esančius duomenis.&lt;br&gt;Ši diegimo programa paliks esamą skaidinių lentelę, nebent aiškiai pasirinksite kitaip.&lt;br&gt;Jeigu nesate tikri, šiuolaikinėse sistemose pirmenybė yra teikiama GPT tipui.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>Šiame įrenginyje yra &lt;strong&gt;%1&lt;/strong&gt; skaidinių lentelė.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation>Tai yra &lt;strong&gt;ciklo&lt;/strong&gt; įrenginys.&lt;br&gt;&lt;br&gt;Tai pseudo-įrenginys be skaidinių lentelės, kuris failą padaro prieinamą kaip bloko įrenginį. Tokio tipo sąrankoje, dažniausiai, yra tik viena failų sistema.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>Šiai diegimo programai, pasirinktame atminties įrenginyje, &lt;strong&gt;nepavyko aptikti skaidinių lentelės&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Arba įrenginyje nėra skaidinių lentelės, arba ji yra pažeista, arba nežinomo tipo.&lt;br&gt;Ši diegimo programa gali jums sukurti skaidinių lentelę automatiškai arba per rankinio skaidymo puslapį.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;Tai yra rekomenduojamas skaidinių lentelės tipas, skirtas šiuolaikinėms sistemoms, kurios yra paleidžiamos iš &lt;strong&gt;EFI&lt;/strong&gt; paleidimo aplinkos.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation>&lt;br&gt;&lt;br&gt;Šį skaidinių lentelės tipą yra patartina naudoti tik senesnėse sistemose, kurios yra paleidžiamos iš &lt;strong&gt;BIOS&lt;/strong&gt; paleidimo aplinkos. Visais kitais atvejais yra rekomenduojamas GPT tipas.&lt;br&gt;&lt;strong&gt;Įspėjimas:&lt;/strong&gt; MBR skaidinių lentelė yra pasenusio MS-DOS eros standarto.&lt;br&gt;Gali būti kuriami tik 4 &lt;em&gt;pirminiai&lt;/em&gt; skaidiniai, o iš tų 4, vienas gali būti &lt;em&gt;išplėstas&lt;/em&gt; skaidinys, kuriame savo ruožtu gali būti daug &lt;em&gt;loginių&lt;/em&gt; skaidinių.</translation>
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
        <translation>%1 - (%2)</translation>
    </message>
</context>
<context>
    <name>DracutLuksCfgJob</name>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="131"/>
        <source>Write LUKS configuration for Dracut to %1</source>
        <translation>Dracut skirtąją LUKS konfigūraciją įrašyti į %1</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="133"/>
        <source>Skip writing LUKS configuration for Dracut: &quot;/&quot; partition is not encrypted</source>
        <translation>Praleisti LUKS konfigūracijos, kuri yra skirta Dracut, įrašymą: &quot;/&quot; skaidinys nėra užšifruotas</translation>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="149"/>
        <source>Failed to open %1</source>
        <translation>Nepavyko atverti %1</translation>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="47"/>
        <source>Dummy C++ Job</source>
        <translation>Fiktyvi C++ užduotis</translation>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>Keisti jau esamą skaidinį</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>Turinys:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation>Išsa&amp;ugoti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>Formatuoti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>Įspėjimas: Formatuojant skaidinį, sunaikinami visi jame esantys duomenys.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>&amp;Prijungimo vieta:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>Dy&amp;dis:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation>Fai&amp;lų sistema:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation>Vėliavėlės:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="269"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation>Prijungimo taškas jau yra naudojamas. Prašome pasirinkti kitą.</translation>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation>Užš&amp;ifruoti sistemą</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation>Slaptafrazė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation>Patvirtinkite slaptafrazę</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation>Prašome abiejuose langeliuose įrašyti tą pačią slaptafrazę.</translation>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="132"/>
        <source>Set partition information</source>
        <translation>Nustatyti skaidinio informaciją</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="156"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>Įdiegti %1 &lt;strong&gt;naujame&lt;/strong&gt; %2 sistemos skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="160"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Nustatyti &lt;strong&gt;naują&lt;/strong&gt; %2 skaidinį su prijungimo tašku &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="168"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Diegti %2 sistemą, %3 sistemos skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="173"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Nustatyti %3 skaidinį &lt;strong&gt;%1&lt;/strong&gt; su prijungimo tašku &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="185"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Diegti paleidyklę skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="195"/>
        <source>Setting up mount points.</source>
        <translation>Nustatomi prijungimo taškai.</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style=&quot; font-style:italic;&quot;&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Pažymėjus šį langelį, jūsų sistema nedelsiant pasileis iš naujo, kai spustelėsite &lt;span style=&quot; font-style:italic;&quot;&gt;Atlikta&lt;/span&gt; ar užversite diegimo programą.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
        <source>&amp;Restart now</source>
        <translation>&amp;Paleisti iš naujo dabar</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="51"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;Viskas atlikta.&lt;/h1&gt;&lt;br/&gt;%1 sistema jau įdiegta.&lt;br/&gt;Galite iš naujo paleisti kompiuterį dabar ir naudotis savo naująja sistema; arba galite tęsti naudojimąsi %2 sistema demonstracinėje aplinkoje.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="109"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation>&lt;h1&gt;Diegimas nepavyko&lt;/h1&gt;&lt;br/&gt;%1 nebuvo įdiegta jūsų kompiuteryje.&lt;br/&gt;Klaidos pranešimas buvo: %2.</translation>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation>Pabaiga</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation>Diegimas užbaigtas</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation>%1 diegimas yra užbaigtas.</translation>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>Formatuoti skaidinį %1 (failų sistema: %2, dydis: %3 MB) diske %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Formatuoti &lt;strong&gt;%3MB&lt;/strong&gt; skaidinį &lt;strong&gt;%1&lt;/strong&gt; su failų sistema &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>Formatuojamas skaidinys %1 su %2 failų sistema.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>Diegimo programai nepavyko formatuoti „%2“ disko skaidinio %1.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
        <source>Konsole not installed</source>
        <translation>Konsole neįdiegta</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
        <source>Please install KDE Konsole and try again!</source>
        <translation>Įdiekite KDE Konsole ir bandykite dar kartą!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>Vykdomas scenarijus: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>Scenarijus</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="219"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>Nustatyti klaviatūros modelį kaip %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="221"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>Nustatyti klaviatūros išdėstymą kaip %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>Klaviatūra</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>Sistemos lokalės nustatymas</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Sistemos lokalės nustatymas įtakoja, kai kurių komandų eilutės naudotojo sąsajos elementų, kalbos ir simbolių rinkinį.&lt;br/&gt;Dabar yra nustatyta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation>&amp;Atsisakyti</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="67"/>
        <source>&amp;OK</source>
        <translation>&amp;Gerai</translation>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="89"/>
        <source>I accept the terms and conditions above.</source>
        <translation>Sutinku su aukščiau išdėstytomis nuostatomis ir sąlygomis.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="116"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;Licencijos Sutartis&lt;/h1&gt;Ši sąrankos procedūra įdiegs nuosavybinę programinę įrangą, kuriai yra taikomos licencijavimo nuostatos.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="119"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>Prašome aukščiau peržiūrėti Galutinio Vartotojo Licencijos Sutartis (angl. EULA).&lt;br/&gt;Jeigu nesutiksite su nuostatomis, sąrankos procedūra negalės būti tęsiama.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="125"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;Licencijos Sutartis&lt;/h1&gt;Tam, kad pateiktų papildomas ypatybes ir pagerintų naudotojo patirtį, ši sąrankos procedūra gali įdiegti nuosavybinę programinę įrangą, kuriai yra taikomos licencijavimo nuostatos.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="130"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>Prašome aukščiau peržiūrėti Galutinio Vartotojo Licencijos Sutartis (angl. EULA).&lt;br/&gt;Jeigu nesutiksite su nuostatomis, tuomet nuosavybinė programinė įranga nebus įdiegta, o vietoj jos, bus naudojamos atviro kodo alternatyvos.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="160"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;%1 tvarkyklė&lt;/strong&gt;&lt;br/&gt;iš %2</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="167"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;%1 grafikos tvarkyklė&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="173"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 naršyklės papildinys&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="179"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 kodekas&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="185"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1 paketas&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="191"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;iš %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="203"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;žiūrėti licencijos sutartį&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>Licencija</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation>Sistemos kalba bus nustatyta į %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation>Skaičių ir datų lokalė bus nustatyta į %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation>Regionas:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation>Zona:</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>K&amp;eisti...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>Nustatyti laiko juostą kaip %1/%2.&lt;br/&gt;</translation>
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
        <translation>Įkeliami vietos duomenys...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="175"/>
        <source>Location</source>
        <translation>Vieta</translation>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="64"/>
        <source>Name</source>
        <translation>Pavadinimas</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="65"/>
        <source>Description</source>
        <translation>Aprašas</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="86"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation>Tinklo diegimas. (Išjungta: Nepavyksta gauti paketų sąrašus, patikrinkite savo tinklo ryšį)</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="96"/>
        <source>Network Installation. (Disabled: Received invalid groups data)</source>
        <translation>Tinklo diegimas. (Išjungtas: Gauti neteisingi grupių duomenys)</translation>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
        <source>Package selection</source>
        <translation>Paketų pasirinkimas</translation>
    </message>
</context>
<context>
    <name>PWQ</name>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="63"/>
        <source>Password is too short</source>
        <translation>Slaptažodis yra per trumpas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="85"/>
        <source>Password is too long</source>
        <translation>Slaptažodis yra per ilgas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="151"/>
        <source>Password is too weak</source>
        <translation>Slaptažodis yra per silpnas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="158"/>
        <source>Memory allocation error when setting &apos;%1&apos;</source>
        <translation>Atminties paskirstymo klaida, nustatant &quot;%1&quot;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
        <source>Memory allocation error</source>
        <translation>Atminties paskirstymo klaida</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
        <source>The password is the same as the old one</source>
        <translation>Slaptažodis yra toks pats kaip ir senas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
        <source>The password is a palindrome</source>
        <translation>Slaptažodis yra palindromas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
        <source>The password differs with case changes only</source>
        <translation>Slaptažodyje skiriasi tik raidžių dydis</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
        <source>The password is too similar to the old one</source>
        <translation>Slaptažodis pernelyg panašus į senąjį</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
        <source>The password contains the user name in some form</source>
        <translation>Slaptažodyje tam tikru pavidalu yra naudotojo vardas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
        <source>The password contains words from the real name of the user in some form</source>
        <translation>Slaptažodyje tam tikra forma yra žodžiai iš tikrojo naudotojo vardo</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="176"/>
        <source>The password contains forbidden words in some form</source>
        <translation>Slaptažodyje tam tikra forma yra uždrausti žodžiai</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="179"/>
        <source>The password contains less than %1 digits</source>
        <translation>Slaptažodyje yra mažiau nei %1 skaitmenys</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="180"/>
        <source>The password contains too few digits</source>
        <translation>Slaptažodyje yra per mažai skaitmenų</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="183"/>
        <source>The password contains less than %1 uppercase letters</source>
        <translation>Slaptažodyje yra mažiau nei %1 didžiosios raidės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
        <source>The password contains too few uppercase letters</source>
        <translation>Slaptažodyje yra per mažai didžiųjų raidžių</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="187"/>
        <source>The password contains less than %1 lowercase letters</source>
        <translation>Slaptažodyje yra mažiau nei %1 mažosios raidės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
        <source>The password contains too few lowercase letters</source>
        <translation>Slaptažodyje yra per mažai mažųjų raidžių</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
        <source>The password contains less than %1 non-alphanumeric characters</source>
        <translation>Slaptažodyje yra mažiau nei %1 neraidiniai ir neskaitiniai simboliai</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="192"/>
        <source>The password contains too few non-alphanumeric characters</source>
        <translation>Slaptažodyje yra per mažai neraidinių ir neskaitinių simbolių</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
        <source>The password is shorter than %1 characters</source>
        <translation>Slaptažodyje yra mažiau nei %1 simboliai</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
        <source>The password is too short</source>
        <translation>Slaptažodis yra per trumpas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
        <source>The password is just rotated old one</source>
        <translation>Slaptažodis yra toks pats kaip ir senas, tik apverstas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
        <source>The password contains less than %1 character classes</source>
        <translation>Slaptažodyje yra mažiau nei %1 simbolių klasės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
        <source>The password does not contain enough character classes</source>
        <translation>Slaptažodyje nėra pakankamai simbolių klasių</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
        <source>The password contains more than %1 same characters consecutively</source>
        <translation>Slaptažodyje yra daugiau nei %1 tokie patys simboliai iš eilės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
        <source>The password contains too many same characters consecutively</source>
        <translation>Slaptažodyje yra per daug tokių pačių simbolių iš eilės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
        <source>The password contains more than %1 characters of the same class consecutively</source>
        <translation>Slaptažodyje yra daugiau nei %1 tos pačios klasės simboliai iš eilės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
        <source>The password contains too many characters of the same class consecutively</source>
        <translation>Slaptažodyje yra per daug tos pačios klasės simbolių iš eilės</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
        <source>The password contains monotonic sequence longer than %1 characters</source>
        <translation>Slaptažodyje yra ilgesnė nei %1 simbolių monotoninė seka</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
        <source>The password contains too long of a monotonic character sequence</source>
        <translation>Slaptažodyje yra per ilga monotoninių simbolių seka</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="216"/>
        <source>No password supplied</source>
        <translation>Nepateiktas joks slaptažodis</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
        <source>Cannot obtain random numbers from the RNG device</source>
        <translation>Nepavyksta gauti atsitiktinių skaičių iš RNG įrenginio</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="220"/>
        <source>Password generation failed - required entropy too low for settings</source>
        <translation>Slaptažodžio generavimas nepavyko - reikalinga entropija nustatymams yra per maža</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
        <source>The password fails the dictionary check - %1</source>
        <translation>Slaptažodis nepraeina žodyno patikros - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="227"/>
        <source>The password fails the dictionary check</source>
        <translation>Slaptažodis nepraeina žodyno patikros</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="231"/>
        <source>Unknown setting - %1</source>
        <translation>Nežinomas nustatymas - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
        <source>Unknown setting</source>
        <translation>Nežinomas nustatymas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
        <source>Bad integer value of setting - %1</source>
        <translation>Bloga nustatymo sveikojo skaičiaus reikšmė - %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
        <source>Bad integer value</source>
        <translation>Bloga sveikojo skaičiaus reikšmė</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
        <source>Setting %1 is not of integer type</source>
        <translation>Nustatymas %1 nėra sveikojo skaičiaus tipo</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
        <source>Setting is not of integer type</source>
        <translation>Nustatymas nėra sveikojo skaičiaus tipo</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
        <source>Setting %1 is not of string type</source>
        <translation>Nustatymas %1 nėra eilutės tipo</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
        <source>Setting is not of string type</source>
        <translation>Nustatymas nėra eilutės tipo</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="261"/>
        <source>Opening the configuration file failed</source>
        <translation>Konfigūracijos failo atvėrimas nepavyko</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
        <source>The configuration file is malformed</source>
        <translation>Konfigūracijos failas yra netaisyklingas</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
        <source>Fatal failure</source>
        <translation>Lemtingoji klaida</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
        <source>Unknown error</source>
        <translation>Nežinoma klaida</translation>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>Klaviatūros modelis:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>Rašykite čia ir išbandykite savo klaviatūrą</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>Koks jūsų vardas?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>Kokį vardą norite naudoti prisijungimui?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>šrifto ryškumas: normalus</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Jei šiuo kompiuteriu naudosis keli žmonės, po diegimo galite sukurti papildomas paskyras.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>Apsaugokite savo paskyrą slaptažodžiu</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus. Stiprus slaptažodis yra raidžių, skaičių ir punktuacijos ženklų mišinys, jis turi būti mažiausiai aštuonių simbolių, be to, turėtų būti reguliariai keičiamas.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>Koks šio kompiuterio vardas?</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Šis vardas bus naudojamas, jeigu padarysite savo kompiuterį matomą kitiems naudotojams tinkle.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>Prisijungti automatiškai, neklausiant slaptažodžio.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>Naudoti tokį patį slaptažodį administratoriaus paskyrai.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>Pasirinkite slaptažodį administratoriaus paskyrai.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;Norint įsitikinti, kad rašydami slaptažodį nesuklydote, įrašykite tą patį slaptažodį du kartus.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation>Šaknies</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation>Namų</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation>Paleidimo</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation>EFI sistema</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation>Sukeitimų (swap)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation>Naujas skaidinys, skirtas %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation>Naujas skaidinys</translation>
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
        <translation>Laisva vieta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="142"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="174"/>
        <source>New partition</source>
        <translation>Naujas skaidinys</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="258"/>
        <source>Name</source>
        <translation>Pavadinimas</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="260"/>
        <source>File System</source>
        <translation>Failų sistema</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="262"/>
        <source>Mount Point</source>
        <translation>Prijungimo vieta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="264"/>
        <source>Size</source>
        <translation>Dydis</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>Atminties įre&amp;nginys:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>&amp;Sugrąžinti visus pakeitimus</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>Nauja skaidinių &amp;lentelė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>Cre&amp;ate</source>
        <translation>Su&amp;kurti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>&amp;Keisti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>Iš&amp;trinti</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
        <source>New Volume Group</source>
        <translation>Nauja tomų grupė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
        <source>Resize Volume Group</source>
        <translation>Keisti tomų grupės dydį</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
        <source>Deactivate Volume Group</source>
        <translation>Pasyvinti tomų grupę</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
        <source>Remove Volume Group</source>
        <translation>Šalinti tomų grupę</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
        <source>I&amp;nstall boot loader on:</source>
        <translation>Į&amp;diegti paleidyklę skaidinyje:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="217"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>Ar tikrai %1 norite sukurti naują skaidinių lentelę?</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
        <source>Can not create new partition</source>
        <translation>Nepavyksta sukurti naują skaidinį</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="242"/>
        <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
        <translation>Skaidinių lentelėje ties %1 jau yra %2 pirminiai skaidiniai ir daugiau nebegali būti pridėta. Pašalinkite vieną pirminį skaidinį ir vietoj jo, pridėkite išplėstą skaidinį.</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="71"/>
        <source>Gathering system information...</source>
        <translation>Renkama sistemos informacija...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="122"/>
        <source>Partitions</source>
        <translation>Skaidiniai</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="159"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>Diegti %1 &lt;strong&gt;šalia&lt;/strong&gt; kitos operacinės sistemos.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>&lt;strong&gt;Ištrinti&lt;/strong&gt; diską ir diegti %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>&lt;strong&gt;Pakeisti&lt;/strong&gt; skaidinį, įrašant %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="172"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>&lt;strong&gt;Rankinis&lt;/strong&gt; skaidymas.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="185"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>Įdiegti %1 &lt;strong&gt;šalia&lt;/strong&gt; kitos operacinės sistemos diske &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="191"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation>&lt;strong&gt;Ištrinti&lt;/strong&gt; diską &lt;strong&gt;%2&lt;/strong&gt; (%3) ir diegti %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="197"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>&lt;strong&gt;Pakeisti&lt;/strong&gt; skaidinį diske &lt;strong&gt;%2&lt;/strong&gt; (%3), įrašant %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="204"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation>&lt;strong&gt;Rankinis&lt;/strong&gt; skaidymas diske &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="212"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation>Diskas &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="240"/>
        <source>Current:</source>
        <translation>Dabartinis:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="257"/>
        <source>After:</source>
        <translation>Po:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>No EFI system partition configured</source>
        <translation>Nėra sukonfigūruoto EFI sistemos skaidinio</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="401"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation>EFI sistemos skaidinys yra būtinas, norint paleisti %1.&lt;br/&gt;&lt;br/&gt;Tam, kad sukonfigūruotumėte EFI sistemos skaidinį, grįžkite atgal ir pasirinkite arba sukurkite FAT32 failų sistemą su įjungta &lt;strong&gt;esp&lt;/strong&gt; vėliavėle ir &lt;strong&gt;%2&lt;/strong&gt; prijungimo tašku.&lt;br/&gt;&lt;br/&gt;Jūs galite tęsti ir nenustatę EFI sistemos skaidinio, tačiau tokiu atveju, gali nepavykti paleisti jūsų sistemos.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>EFI system partition flag not set</source>
        <translation>Nenustatyta EFI sistemos skaidinio vėliavėlė</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="415"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation>EFI sistemos skaidinys yra būtinas, norint paleisti %1.&lt;br/&gt;&lt;br/&gt;Skaidinys buvo sukonfigūruotas su prijungimo tašku &lt;strong&gt;%2&lt;/strong&gt;, tačiau jo &lt;strong&gt;esp&lt;/strong&gt; vėliavėlė yra nenustatyta.&lt;br/&gt;Tam, kad nustatytumėte vėliavėlę, grįžkite atgal ir redaguokite skaidinį.&lt;br/&gt;&lt;br/&gt;Jūs galite tęsti ir nenustatę vėliavėlės, tačiau tokiu atveju, gali nepavykti paleisti jūsų sistemos.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="450"/>
        <source>Boot partition not encrypted</source>
        <translation>Paleidimo skaidinys nėra užšifruotas</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="451"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation>Kartu su užšifruotu šaknies skaidiniu, buvo nustatytas atskiras paleidimo skaidinys, tačiau paleidimo skaidinys nėra užšifruotas.&lt;br/&gt;&lt;br/&gt;Dėl tokios sąrankos iškyla tam tikrų saugumo klausimų, kadangi svarbūs sisteminiai failai yra laikomi neužšifruotame skaidinyje.&lt;br/&gt;Jeigu norite, galite tęsti, tačiau failų sistemos atrakinimas įvyks vėliau, sistemos paleidimo metu.&lt;br/&gt;Norėdami užšifruoti paleidimo skaidinį, grįžkite atgal ir sukurkite jį iš naujo bei skaidinių kūrimo lange pažymėkite parinktį &lt;strong&gt;Užšifruoti&lt;/strong&gt;.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfJob</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
        <source>Plasma Look-and-Feel Job</source>
        <translation>Plasma išvaizdos ir turinio užduotis</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
        <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
        <source>Could not select KDE Plasma Look-and-Feel package</source>
        <translation>Nepavyko pasirinkti KDE Plasma išvaizdos ir turinio paketo</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfPage</name>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="20"/>
        <source>Placeholder</source>
        <translation>Vietaženklis</translation>
    </message>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="67"/>
        <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
        <translation>Pasirinkite KDE Plasma darbalaukio išvaizdą ir turinį. Taip pat galite praleisti šį žingsnį ir konfigūruoti išvaizdą ir turinį, kai sistema bus įdiegta. Spustelėjus ant tam tikro išvaizdos ir turinio pasirinkimo, jums bus parodyta tiesioginė peržiūrą.</translation>
    </message>
</context>
<context>
    <name>PlasmaLnfViewStep</name>
    <message>
        <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
        <source>Look-and-Feel</source>
        <translation>Išvaizda ir turinys</translation>
    </message>
</context>
<context>
    <name>PreserveFiles</name>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="85"/>
        <source>Saving files for later ...</source>
        <translation>Įrašomi failai vėlesniam naudojimui ...</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="123"/>
        <source>No files configured to save for later.</source>
        <translation>Nėra sukonfigūruota įrašyti jokius failus vėlesniam naudojimui.</translation>
    </message>
    <message>
        <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="177"/>
        <source>Not all of the configured files could be preserved.</source>
        <translation>Ne visus iš sukonfigūruotų failų pavyko išsaugoti.</translation>
    </message>
</context>
<context>
    <name>ProcessResult</name>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="271"/>
        <source>
There was no output from the command.</source>
        <translation>
Nebuvo jokios išvesties iš komandos.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="272"/>
        <source>
Output:
</source>
        <translation>
Išvestis:
</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="275"/>
        <source>External command crashed.</source>
        <translation>Išorinė komanda užstrigo.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="276"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
        <translation>Komanda &lt;i&gt;%1&lt;/i&gt; užstrigo.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="281"/>
        <source>External command failed to start.</source>
        <translation>Nepavyko paleisti išorinės komandos.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="282"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
        <translation>Nepavyko paleisti komandos &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="286"/>
        <source>Internal error when starting command.</source>
        <translation>Paleidžiant komandą, įvyko vidinė klaida.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="287"/>
        <source>Bad parameters for process job call.</source>
        <translation>Netinkamas proceso parametras</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="290"/>
        <source>External command failed to finish.</source>
        <translation>Nepavyko pabaigti išorinės komandos.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="291"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
        <translation>Nepavyko per %2 sek. pabaigti komandos &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="297"/>
        <source>External command finished with errors.</source>
        <translation>Išorinė komanda pabaigta su klaidomis.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="298"/>
        <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
        <translation>Komanda &lt;i&gt;%1&lt;/i&gt; pabaigta su išėjimo kodu %2.</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>Numatytasis klaviatūros modelis</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>Numatytasis</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="207"/>
        <source>unknown</source>
        <translation>nežinoma</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="209"/>
        <source>extended</source>
        <translation>išplėsta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="211"/>
        <source>unformatted</source>
        <translation>nesutvarkyta</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="213"/>
        <source>swap</source>
        <translation>sukeitimų (swap)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>Nesuskaidyta vieta arba nežinoma skaidinių lentelė</translation>
    </message>
</context>
<context>
    <name>RemoveVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="34"/>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
        <source>Remove Volume Group named %1.</source>
        <translation>Šalinti tomų grupę, pavadinimu %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="41"/>
        <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Šalinti tomų grupę, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="61"/>
        <source>The installer failed to remove a volume group named &apos;%1&apos;.</source>
        <translation>Diegimo programai nepavyko pašalinti tomų grupės, pavadinimu &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation>Pasirinkite, kur norėtumėte įdiegti %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Įspėjimas: &lt;/font&gt;tai ištrins visus, pasirinktame skaidinyje esančius, failus.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>Pasirinktas elementas neatrodo kaip teisingas skaidinys.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>%1 negali būti įdiegta laisvoje vietoje. Prašome pasirinkti esamą skaidinį.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>%1 negali būti įdiegta išplėstame skaidinyje. Prašome pasirinkti esamą pirminį ar loginį skaidinį.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>%1 negali būti įdiegta šiame skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation>Duomenų skaidinys (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation>Nežinomas sistemos skaidinys (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation>%1 sistemos skaidinys (%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Skaidinys %1 yra pernelyg mažas sistemai %2. Prašome pasirinkti skaidinį, kurio dydis siektų bent %3 GiB.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Šioje sistemoje niekur nepavyko rasti EFI skaidinio. Prašome grįžti ir naudoti rankinį skaidymą, kad nustatytumėte %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 sistema bus įdiegta skaidinyje %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Įspėjimas: &lt;/font&gt;visi duomenys skaidinyje %2 bus prarasti.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>%2 paleidimui bus naudojamas EFI sistemos skaidinys, esantis %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation>EFI sistemos skaidinys:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="68"/>
        <source>Gathering system information...</source>
        <translation>Renkama sistemos informacija...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="118"/>
        <source>has at least %1 GB available drive space</source>
        <translation>turi bent %1 GB laisvos vietos diske</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="120"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>Neužtenka vietos diske. Reikia bent %1 GB.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="128"/>
        <source>has at least %1 GB working memory</source>
        <translation>turi bent %1 GB darbinės atminties</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="130"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>Sistemai neužtenka darbinės atminties. Reikia bent %1 GB.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="138"/>
        <source>is plugged in to a power source</source>
        <translation>prijungta prie maitinimo šaltinio</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="139"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>Sistema nėra prijungta prie maitinimo šaltinio.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="146"/>
        <source>is connected to the Internet</source>
        <translation>prijungta prie Interneto</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="147"/>
        <source>The system is not connected to the Internet.</source>
        <translation>Sistema nėra prijungta prie Interneto.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="155"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>Diegimo programa yra vykdoma be administratoriaus teisių.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="163"/>
        <source>The screen is too small to display the installer.</source>
        <translation>Ekranas yra per mažas, kad būtų parodyta diegimo programa.</translation>
    </message>
</context>
<context>
    <name>ResizeFSJob</name>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="130"/>
        <source>Resize Filesystem Job</source>
        <translation>Failų sistemos dydžio keitimo užduotis</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="238"/>
        <source>Invalid configuration</source>
        <translation>Neteisinga konfigūracija</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="239"/>
        <source>The file-system resize job has an invalid configuration and will not run.</source>
        <translation>Failų sistemos dydžio keitimo užduotyje yra neteisinga konfigūracija ir užduotis nebus paleista.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="253"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="263"/>
        <source>KPMCore not Available</source>
        <translation>KPMCore neprieinama</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="254"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="264"/>
        <source>Calamares cannot start KPMCore for the file-system resize job.</source>
        <translation>Diegimo programai Calamares nepavyksta paleisti KPMCore, kuri skirta failų sistemos dydžio keitimo užduočiai.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="272"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="281"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="294"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="303"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="320"/>
        <source>Resize Failed</source>
        <translation>Dydžio keitimas patyrė nesėkmę</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="273"/>
        <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
        <translation>Šioje sistemoje nepavyko rasti %1 failų sistemos ir nepavyko pakeisti jos dydį.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="274"/>
        <source>The device %1 could not be found in this system, and cannot be resized.</source>
        <translation>Šioje sistemoje nepavyko rasti %1 įrenginio ir nepavyko pakeisti jo dydį.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="282"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="295"/>
        <source>The filesystem %1 cannot be resized.</source>
        <translation>%1 failų sistemos dydis negali būti pakeistas.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="283"/>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="296"/>
        <source>The device %1 cannot be resized.</source>
        <translation>%1 įrenginio dydis negali būti pakeistas.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="304"/>
        <source>The filesystem %1 must be resized, but cannot.</source>
        <translation>%1 failų sistemos dydis privalo būti pakeistas, tačiau tai negali būti atlikta.</translation>
    </message>
    <message>
        <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="305"/>
        <source>The device %1 must be resized, but cannot</source>
        <translation>%1 įrenginio dydis privalo būti pakeistas, tačiau tai negali būti atlikta</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
        <source>Resize partition %1.</source>
        <translation>Keisti skaidinio %1 dydį.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation>Pakeisti &lt;strong&gt;%2MB&lt;/strong&gt; skaidinio &lt;strong&gt;%1&lt;/strong&gt; dydį iki &lt;strong&gt;%3MB&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation>Keičiamas %2MB skaidinio %1 dydis iki %3MB.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>Diegimo programai nepavyko pakeisti skaidinio %1 dydį diske &apos;%2&apos;.</translation>
    </message>
</context>
<context>
    <name>ResizeVolumeGroupJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="55"/>
        <source>Resize volume group named %1 from %2 to %3.</source>
        <translation>Keisti tomų grupės, pavadinimu %1, dydį iš %2 į %3.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
        <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation>Keisti tomų grupės, pavadinimu &lt;strong&gt;%1&lt;/strong&gt;, dydį iš &lt;strong&gt;%2&lt;/strong&gt; į &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="70"/>
        <source>The installer failed to resize a volume group named &apos;%1&apos;.</source>
        <translation>Diegimo programai nepavyko pakeisti tomų grupės, pavadinimu &quot;%1&quot;, dydį.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation>Peržiūrimi atminties įrenginiai...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
        <source>Partitioning</source>
        <translation>Skaidymas</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="38"/>
        <source>Set hostname %1</source>
        <translation>Nustatyti kompiuterio vardą %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="45"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Nustatyti kompiuterio vardą &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="52"/>
        <source>Setting hostname %1.</source>
        <translation>Nustatomas kompiuterio vardas %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="62"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="69"/>
        <source>Internal Error</source>
        <translation>Vidinė klaida</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="76"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="87"/>
        <source>Cannot write hostname to target system</source>
        <translation>Nepavyko įrašyti kompiuterio vardo į paskirties sistemą</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>Nustatyti klaviatūros modelį kaip %1, o išdėstymą kaip %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>Nepavyko įrašyti klaviatūros sąrankos virtualiam pultui.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="326"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="332"/>
        <source>Failed to write to %1</source>
        <translation>Nepavyko įrašyti į %1</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>Nepavyko įrašyti klaviatūros sąrankos X11 aplinkai.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation>Nepavyko įrašyti klaviatūros konfigūracijos į esamą /etc/default katalogą.</translation>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
        <source>Set flags on partition %1.</source>
        <translation>Nustatyti vėliavėles skaidinyje %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation>Nustatyti vėliavėles %1MB skaidinyje %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
        <source>Set flags on new partition.</source>
        <translation>Nustatyti vėliavėles naujame skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Išvalyti vėliavėles skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Išvalyti vėliavėles %1MB skaidinyje &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
        <source>Clear flags on new partition.</source>
        <translation>Išvalyti vėliavėles naujame skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>Pažymėti vėliavėle skaidinį &lt;strong&gt;%1&lt;/strong&gt; kaip &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="85"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation>Pažymėti vėliavėle %1MB skaidinį &lt;strong&gt;%2&lt;/strong&gt; kaip &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Pažymėti vėliavėle naują skaidinį kaip &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Išvalomos vėliavėlės skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Išvalomos vėliavėlės %1MB skaidinyje &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
        <source>Clearing flags on new partition.</source>
        <translation>Išvalomos vėliavėlės naujame skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>Nustatomos &lt;strong&gt;%2&lt;/strong&gt; vėliavėlės skaidinyje &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation>Nustatomos vėliavėlės &lt;strong&gt;%3&lt;/strong&gt;, %1MB skaidinyje &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation>Nustatomos vėliavėlės &lt;strong&gt;%1&lt;/strong&gt; naujame skaidinyje.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="144"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>Diegimo programai nepavyko nustatyti vėliavėlių skaidinyje %1.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation>Nustatyti naudotojo %1 slaptažodį</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation>Nustatomas slaptažodis naudotojui %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation>Neteisingas paskirties sistemos kelias.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation>rootMountPoint yra %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="123"/>
        <source>Cannot disable root account.</source>
        <translation>Nepavyksta išjungti administratoriaus (root) paskyros.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="124"/>
        <source>passwd terminated with error code %1.</source>
        <translation>komanda passwd nutraukė darbą dėl klaidos kodo %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="139"/>
        <source>Cannot set password for user %1.</source>
        <translation>Nepavyko nustatyti slaptažodžio naudotojui %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation>komanda usermod nutraukė darbą dėl klaidos kodo %1.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>Nustatyti laiko juostą kaip %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>Nepavyko pasiekti pasirinktos laiko zonos</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>Neteisingas kelias: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>Negalima nustatyti laiko juostas.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>Nuorodos sukūrimas nepavyko, paskirtis: %1; nuorodos pavadinimas: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation>Nepavyksta nustatyti laiko juostos,</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>Nepavyksta įrašymui atidaryti failo /etc/timezone</translation>
    </message>
</context>
<context>
    <name>ShellProcessJob</name>
    <message>
        <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="51"/>
        <source>Shell Processes Job</source>
        <translation>Apvalkalo procesų užduotis</translation>
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
        <translation>Tai yra apžvalga to, kas įvyks, prasidėjus diegimo procedūrai.</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>Suvestinė</translation>
    </message>
</context>
<context>
    <name>TrackingInstallJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
        <source>Installation feedback</source>
        <translation>Grįžtamasis ryšys apie diegimą</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="53"/>
        <source>Sending installation feedback.</source>
        <translation>Siunčiamas grįžtamasis ryšys apie diegimą.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="88"/>
        <source>Internal error in install-tracking.</source>
        <translation>Vidinė klaida diegimo sekime.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="89"/>
        <source>HTTP request timed out.</source>
        <translation>Baigėsi HTTP užklausos laikas.</translation>
    </message>
</context>
<context>
    <name>TrackingMachineNeonJob</name>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="104"/>
        <source>Machine feedback</source>
        <translation>Grįžtamasis ryšys apie kompiuterį</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="114"/>
        <source>Configuring machine feedback.</source>
        <translation>Konfigūruojamas grįžtamasis ryšys apie kompiuterį.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="133"/>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="136"/>
        <source>Error in machine feedback configuration.</source>
        <translation>Klaida grįžtamojo ryšio apie kompiuterį konfigūravime.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="134"/>
        <source>Could not configure machine feedback correctly, script error %1.</source>
        <translation>Nepavyko teisingai sukonfigūruoti grįžtamojo ryšio apie kompiuterį, scenarijaus klaida %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingJobs.cpp" line="137"/>
        <source>Could not configure machine feedback correctly, Calamares error %1.</source>
        <translation>Nepavyko teisingai sukonfigūruoti grįžtamojo ryšio apie kompiuterį, Calamares klaida %1.</translation>
    </message>
</context>
<context>
    <name>TrackingPage</name>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
        <source>Placeholder</source>
        <translation>Vietaženklis</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=&quot; font-weight:600;&quot;&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Tai pažymėdami, nesiųsite &lt;span style=&quot; font-weight:600;&quot;&gt;visiškai jokios informacijos&lt;/span&gt; apie savo diegimą.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="123"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="185"/>
        <location filename="../src/modules/tracking/page_trackingstep.ui" line="247"/>
        <source>TextLabel</source>
        <translation>Teksto etiketė</translation>
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
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href=&quot;placeholder&quot;&gt;&lt;span style=&quot; text-decoration: underline; color:#2980b9;&quot;&gt;Išsamesnei informacijai apie naudotojų grįžtamąjį ryšį, spustelėkite čia&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
        <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
        <translation>Diegimo sekimas padeda %1 matyti kiek jie turi naudotojų, į kokią aparatinę įrangą naudotojai diegia %1 ir (su paskutiniais dviejais parametrais žemiau), gauti tęstinę informaciją apie pageidaujamas programas. Norėdami matyti kas bus siunčiama, šalia kiekvienos srities spustelėkite žinyno piktogramą.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="45"/>
        <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
        <translation>Tai pažymėdami, išsiųsite informaciją apie savo diegimą ir aparatinę įrangą. Ši informacija bus &lt;b&gt;išsiųsta tik vieną kartą&lt;/b&gt;, užbaigus diegimą.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="46"/>
        <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
        <translation>Tai pažymėdami, &lt;b&gt;periodiškai&lt;/b&gt; siųsite informaciją apie savo diegimą, aparatinę įrangą ir programas į %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/tracking/TrackingPage.cpp" line="47"/>
        <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
        <translation>Tai pažymėdami, &lt;b&gt;reguliariai&lt;/b&gt; siųsite informaciją apie savo diegimą, aparatinę įrangą, programas ir naudojimo būdus į %1.</translation>
    </message>
</context>
<context>
    <name>TrackingViewStep</name>
    <message>
        <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="59"/>
        <source>Feedback</source>
        <translation>Grįžtamasis ryšys</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="289"/>
        <source>Your username is too long.</source>
        <translation>Jūsų naudotojo vardas yra pernelyg ilgas.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="295"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>Jūsų naudotojo varde yra neleistinų simbolių. Leidžiamos tik mažosios raidės ir skaičiai.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="333"/>
        <source>Your hostname is too short.</source>
        <translation>Jūsų kompiuterio vardas yra pernelyg trumpas.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="339"/>
        <source>Your hostname is too long.</source>
        <translation>Jūsų kompiuterio vardas yra pernelyg ilgas.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="345"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>Jūsų kompiuterio varde yra neleistinų simbolių. Kompiuterio varde gali būti tik raidės, skaičiai ir brūkšniai.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="373"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="417"/>
        <source>Your passwords do not match!</source>
        <translation>Jūsų slaptažodžiai nesutampa!</translation>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="53"/>
        <source>Users</source>
        <translation>Naudotojai</translation>
    </message>
</context>
<context>
    <name>VolumeGroupBaseDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
        <source>VolumeGroupDialog</source>
        <translation>Tomų grupės dialogas</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
        <source>List of Physical Volumes</source>
        <translation>Fizinių tomų sąrašas</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
        <source>Volume Group Name:</source>
        <translation>Tomų grupės pavadinimas:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
        <source>Volume Group Type:</source>
        <translation>Tomų grupės tipas:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
        <source>Physical Extent Size:</source>
        <translation>Fizinio masto dydis:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
        <source> MiB</source>
        <translation> MiB</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
        <source>Total Size:</source>
        <translation>Bendras dydis:</translation>
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
        <translation>Panaudota:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
        <source>Total Sectors:</source>
        <translation>Iš viso sektorių:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
        <source>Quantity of LVs:</source>
        <translation>Loginių tomų skaičius:</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation>Forma</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>Ka&amp;lba:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>Lai&amp;dos informacija</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>Ž&amp;inomos problemos</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>&amp;Palaikymas</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>&amp;Apie</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Jus sveikina %1 diegimo programa.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;Jus sveikina Calamares diegimo programa, skirta %1 sistemai.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation>Apie %1 diegimo programą</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;sistemai %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Autorių teisės 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Autorių teisės 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Dėkojame: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg ir &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares vertėjų komandai&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;https://calamares.io/&quot;&gt;Calamares&lt;/a&gt; kūrimą remia &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Išlaisvinanti programinė įranga.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="290"/>
        <source>%1 support</source>
        <translation>%1 palaikymas</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="52"/>
        <source>Welcome</source>
        <translation>Pasisveikinimas</translation>
    </message>
</context>
</TS>
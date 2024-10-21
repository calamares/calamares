<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="sk" version="2.1">
  <context>
    <name>AboutData</name>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="17"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; pre %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="20"/>
      <source>Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://app.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="34"/>
      <source>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</source>
      <extracomment>Copyright year-year Name &lt;email-address&gt;</extracomment>
      <translation>Autorské práva %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>ActiveDirectoryJob</name>
    <message>
      <location filename="../src/modules/users/ActiveDirectoryJob.cpp" line="39"/>
      <source>Enroll system in Active Directory</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/ActiveDirectoryJob.cpp" line="45"/>
      <source>Enrolling system in Active Directory…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>AutoMountManagementJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/AutoMountManagementJob.cpp" line="22"/>
      <source>Managing auto-mount settings…</source>
      <comment>@status</comment>
      <translation>Spravujú sa nastavenia automatického pripojenia…</translation>
    </message>
  </context>
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="60"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>&lt;strong&gt;Zavádzacie prostredie&lt;/strong&gt; tohto systému.&lt;br&gt;&lt;br&gt;Staršie systémy architektúry x86 podporujú iba &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Moderné systémy obvykle používajú &lt;strong&gt;EFI&lt;/strong&gt;, ale tiež sa môžu zobraziť ako BIOS, ak sú spustené v režime kompatiblitiy.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="70"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Tento systém bol spustený so zavádzacím prostredím &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Na konfiguráciu spustenia z prostredia EFI, musí inštalátor umiestniť aplikáciu zavádzača, ako je &lt;strong&gt;GRUB&lt;/strong&gt; alebo &lt;strong&gt;systemd-boot&lt;/strong&gt; na &lt;strong&gt;oddiel systému EFI&lt;/strong&gt;. Toto je vykonané automaticky, pokiaľ nezvolíte ručné rozdelenie oddielov, v tom prípade ho musíte zvoliť alebo vytvoriť ručne.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="82"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Tento systém bol spustený so zavádzacím prostredím &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Na konfiguráciu spustenia z prostredia BIOS, musí inštalátor nainštalovať zavádzač, ako je &lt;strong&gt;GRUB&lt;/strong&gt;, buď na začiatok oddielu alebo na &lt;strong&gt;hlavný zavádzací záznam (MBR)&lt;/strong&gt; pri začiatku tabuľky oddielov (preferované). Toto je vykonané automaticky, pokiaľ nezvolíte ručné rozdelenie oddielov, v tom prípade ho musíte nainštalovať ručne.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="60"/>
      <source>Master Boot Record of %1</source>
      <comment>@info</comment>
      <translation>Hlavný zavádzací záznam (MBR) zariadenia %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="93"/>
      <source>Boot Partition</source>
      <comment>@info</comment>
      <translation>Zavádzací oddiel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="100"/>
      <source>System Partition</source>
      <comment>@info</comment>
      <translation>Systémový oddiel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="131"/>
      <source>Do not install a boot loader</source>
      <comment>@label</comment>
      <translation>Neinštalovať zavádzač</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="148"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="61"/>
      <source>Blank Page</source>
      <translation>Prázdna stránka</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>Globálne úložisko</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>Fronta úloh</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Moduly</translation>
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
      <translation>žiadny</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Rozhranie:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="102"/>
      <source>Crashes Calamares, so that Dr. Konqi can look at it.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="115"/>
      <source>Reloads the stylesheet from the branding directory.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="118"/>
      <source>Reload Stylesheet</source>
      <translation>Znovu načítať hárok so štýlmi</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="128"/>
      <source>Displays the tree of widget names in the log (for stylesheet debugging).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="131"/>
      <source>Widget Tree</source>
      <translation>Strom miniaplikácií</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="141"/>
      <source>Uploads the session log to the configured pastebin.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="144"/>
      <source>Send Session Log</source>
      <translation>Odoslať záznam relácie</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="166"/>
      <source>Debug Information</source>
      <comment>@title</comment>
      <translation>Ladiace informácie</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="77"/>
      <source>%p%</source>
      <comment>Progress percentage indicator: %p is where the number 0..100 is placed</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="117"/>
      <source>Set Up</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="117"/>
      <source>Install</source>
      <comment>@label</comment>
      <translation>Inštalácia</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Úloha zlyhala (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Zlyhanie naprogramovanej úlohy bolo výlučne vyžiadané.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="369"/>
      <source>Done</source>
      <translation>Hotovo</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Vzorová úloha (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="49"/>
      <source>Running command %1 in target system…</source>
      <comment>@status</comment>
      <translation>Spúšťa sa príkaz %1 v cieľovom systéme…</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="53"/>
      <source>Running command %1…</source>
      <comment>@status</comment>
      <translation>Spúšťa sa príkaz %1…</translation>
    </message>
  </context>
  <context>
    <name>Calamares::Python::Job</name>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="219"/>
      <source>Running %1 operation.</source>
      <translation>Spúšťa sa operácia %1.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="234"/>
      <source>Bad working directory path</source>
      <translation>Nesprávna cesta k pracovnému adresáru</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="235"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Pracovný adresár %1 pre úlohu jazyka python %2 nie je možné čítať.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="243"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="319"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="345"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="362"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="370"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="378"/>
      <source>Bad main script file</source>
      <translation>Nesprávny súbor hlavného skriptu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="244"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Súbor hlavného skriptu %1 pre úlohu jazyka python %2 nie je možné čítať.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="305"/>
      <source>Bad internal script</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="306"/>
      <source>Internal script for python job %1 raised an exception.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="320"/>
      <source>Main script file %1 for python job %2 could not be loaded because it raised an  exception.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="346"/>
      <source>Main script file %1 for python job %2 raised an exception.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="363"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="371"/>
      <source>Main script file %1 for python job %2 returned invalid results.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="379"/>
      <source>Main script file %1 for python job %2 does not contain a run() function.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="238"/>
      <source>Running %1 operation…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="266"/>
      <source>Bad working directory path</source>
      <comment>@error</comment>
      <translation>Nesprávna cesta k pracovnému adresáru</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="267"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>Pracovný adresár %1 pre úlohu jazyka python %2 nie je možné čítať.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="275"/>
      <source>Bad main script file</source>
      <comment>@error</comment>
      <translation>Nesprávny súbor hlavného skriptu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="276"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>Súbor hlavného skriptu %1 pre úlohu jazyka python %2 nie je možné čítať.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="348"/>
      <source>Boost.Python error in job "%1"</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="73"/>
      <source>Loading…</source>
      <comment>@status</comment>
      <translation>Načítava sa…</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="100"/>
      <source>QML step &lt;i&gt;%1&lt;/i&gt;.</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="286"/>
      <source>Loading failed.</source>
      <comment>@info</comment>
      <translation>Načítavanie zlyhalo.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="100"/>
      <source>Requirements checking for module '%1' is complete.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="124"/>
      <source>Waiting for %n module(s)…</source>
      <comment>@status</comment>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="125"/>
      <source>(%n second(s))</source>
      <comment>@status</comment>
      <translation>
        <numerusform>(%n sekunda)</numerusform>
        <numerusform>(%n sekundy)</numerusform>
        <numerusform>(%n sekúnd)</numerusform>
        <numerusform>(%n sekúnd)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="130"/>
      <source>System-requirements checking is complete.</source>
      <comment>@info</comment>
      <translation>Kontrola systémových požiadaviek je dokončená.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="165"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Odovzdanie nebolo úspešné. Nebolo dokončené žiadne webové vloženie.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="177"/>
      <source>Install log posted to

%1

Link copied to clipboard</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="183"/>
      <source>Install Log Paste URL</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
      <source>&amp;Yes</source>
      <translation>Án&amp;o</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
      <source>&amp;No</source>
      <translation>&amp;Nie</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="92"/>
      <source>&amp;Close</source>
      <translation>&amp;Zavrieť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="155"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Inštalácia zlyhala</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="156"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Inštalácia zlyhala</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="159"/>
      <source>Error</source>
      <comment>@title</comment>
      <translation>Chyba</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="188"/>
      <source>Calamares Initialization Failed</source>
      <comment>@title</comment>
      <translation>Zlyhala inicializácia inštalátora Calamares</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <comment>@info</comment>
      <translation>Nie je možné nainštalovať %1. Calamares nemohol načítať všetky konfigurované moduly. Je problém s tým, ako sa Calamares používa pri distribúcii.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <comment>@info</comment>
      <translation>&lt;br/&gt;Nebolo možné načítať nasledujúce moduly</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="336"/>
      <source>Continue with Setup?</source>
      <comment>@title</comment>
      <translation>Pokračovať v nastavovaní?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="337"/>
      <source>Continue with Installation?</source>
      <comment>@title</comment>
      <translation>Pokračovať v inštalácii?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="339"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>Inštalačný program distribúcie %1 sa chystá vykonať zmeny na vašom disku, aby nainštaloval distribúciu %2. &lt;br/&gt;&lt;strong&gt;Tieto zmeny nebudete môcť vrátiť späť.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>Inštalátor distribúcie %1 sa chystá vykonať zmeny na vašom disku, aby nainštaloval distribúciu %2. &lt;br/&gt;&lt;strong&gt;Tieto zmeny nebudete môcť vrátiť späť.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="348"/>
      <source>&amp;Set Up Now</source>
      <comment>@button</comment>
      <translation>&amp;Nastaviť teraz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="348"/>
      <source>&amp;Install Now</source>
      <comment>@button</comment>
      <translation>&amp;Inštalovať teraz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="355"/>
      <source>Go &amp;Back</source>
      <comment>@button</comment>
      <translation>Prejsť s&amp;päť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="402"/>
      <source>&amp;Set Up</source>
      <comment>@button</comment>
      <translation>&amp;Nastaviť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="402"/>
      <source>&amp;Install</source>
      <comment>@button</comment>
      <translation>&amp;Inštalovať</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="404"/>
      <source>Setup is complete. Close the setup program.</source>
      <comment>@tooltip</comment>
      <translation>Inštalácia je dokončená. Zavrite inštalačný program.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="405"/>
      <source>The installation is complete. Close the installer.</source>
      <comment>@tooltip</comment>
      <translation>Inštalácia je dokončená. Zatvorí inštalátor.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="407"/>
      <source>Cancel the setup process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>Cancel the installation process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="418"/>
      <source>&amp;Next</source>
      <comment>@button</comment>
      <translation>Ď&amp;alej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="423"/>
      <source>&amp;Back</source>
      <comment>@button</comment>
      <translation>&amp;Späť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="429"/>
      <source>&amp;Done</source>
      <comment>@button</comment>
      <translation>&amp;Dokončiť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="448"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>&amp;Zrušiť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="524"/>
      <source>Cancel Setup?</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="524"/>
      <source>Cancel Installation?</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="525"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Naozaj chcete zrušiť aktuálny priebeh inštalácie?
Inštalačný program bude ukončený a zmeny budú stratené.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="527"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Skutočne chcete zrušiť aktuálny priebeh inštalácie?
Inštalátor sa ukončí a všetky zmeny budú stratené.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="309"/>
      <source>Unknown exception type</source>
      <comment>@error</comment>
      <translation>Neznámy typ výnimky</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="327"/>
      <source>Unparseable Python error</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="371"/>
      <source>Unparseable Python traceback</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="378"/>
      <source>Unfetchable Python error</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="405"/>
      <source>%1 Setup Program</source>
      <translation>Inštalačný program distribúcie %1</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="406"/>
      <source>%1 Installer</source>
      <translation>Inštalátor distribúcie %1</translation>
    </message>
  </context>
  <context>
    <name>ChangeFilesystemLabelJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="34"/>
      <source>Set filesystem label on %1</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="41"/>
      <source>Set filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="50"/>
      <source>Setting filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="72"/>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="84"/>
      <source>The installer failed to update partition table on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Inštalátor zlyhal pri aktualizovaní tabuľky oddielov na disku „%1“.</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="38"/>
      <source>Gathering system information...</source>
      <translation>Zbierajú sa informácie o počítači...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="137"/>
      <source>Select storage de&amp;vice:</source>
      <comment>@label</comment>
      <translation>Vyberte úložné &amp;zariadenie:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="138"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1039"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1098"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1151"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Teraz:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="139"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Potom:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="897"/>
      <source>Reuse %1 as home partition for %2</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1040"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Vyberte oddiel na zmenšenie a potom potiahnutím spodného pruhu zmeňte veľkosť&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1064"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <comment>@info, %1 is partition name, %4 is product name</comment>
      <translation>Oddiel %1 bude zmenšený na %2MiB a nový %3MiB oddiel bude vytvorený pre distribúciu %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1142"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Vyberte oddiel, na ktorý sa má inštalovať&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1202"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <comment>@info, %1 is product name</comment>
      <translation>Oddiel systému EFI sa nedá v tomto počítači nájsť. Prosím, prejdite späť a použite ručné rozdelenie oddielov na inštaláciu distribúcie %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1211"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <comment>@info, %1 is partition path, %2 is product name</comment>
      <translation>Oddiel systému EFI na %1 bude použitý pre spustenie distribúcie %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1220"/>
      <source>EFI system partition:</source>
      <comment>@label</comment>
      <translation>Oddiel systému EFI:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1710"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Zdá sa, že toto úložné zariadenie neobsahuje operačný systém. Čo by ste chceli urobiť?&lt;br/&gt;Budete môcť skontrolovať a potvrdiť vaše voľby pred uplatnením akejkoľvek zmeny na úložnom zariadení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1715"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1742"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1762"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1784"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Vymazanie disku&lt;/strong&gt;&lt;br/&gt;Týmto sa &lt;font color="red"&gt;odstránia&lt;/font&gt; všetky údaje momentálne sa nachádzajúce na vybranom úložnom zariadení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1719"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1738"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1758"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1780"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Inštalácia popri súčasnom systéme&lt;/strong&gt;&lt;br/&gt;Inštalátor zmenší oddiel a uvoľní miesto pre distribúciu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1723"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1746"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1766"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1788"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Nahradenie oddielu&lt;/strong&gt;&lt;br/&gt;Nahradí oddiel distribúciou %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1732"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Toto úložné zariadenie obsahuje operačný systém %1. Čo by ste chceli urobiť?&lt;br/&gt;Budete môcť skontrolovať a potvrdiť vaše voľby pred uplatnením akejkoľvek zmeny na úložnom zariadení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1753"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Toto úložné zariadenie už obsahuje operačný systém. Čo by ste chceli urobiť?&lt;br/&gt;Budete môcť skontrolovať a potvrdiť vaše voľby pred uplatnením akejkoľvek zmeny na úložnom zariadení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1775"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Toto úložné zariadenie obsahuje viacero operačných systémov. Čo by ste chceli urobiť?&lt;br/&gt;Budete môcť skontrolovať a potvrdiť vaše voľby pred uplatnením akejkoľvek zmeny na úložnom zariadení.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1421"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>Toto úložné zariadenie už obsahuje operačný systém, ale tabuľka oddielov &lt;strong&gt;%1&lt;/strong&gt; sa líši od požadovanej &lt;strong&gt;%2&lt;/strong&gt;.
&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1445"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>Toto úložné zariadenie má jeden zo svojich oddielov &lt;strong&gt;pripojený&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1450"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <comment>@info</comment>
      <translation>Toto úložné zariadenie je súčasťou zariadenia s &lt;strong&gt;neaktívnym RAIDom&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1568"/>
      <source>No swap</source>
      <comment>@label</comment>
      <translation>Bez odkladacieho priestoru</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1577"/>
      <source>Reuse swap</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1580"/>
      <source>Swap (no Hibernate)</source>
      <comment>@label</comment>
      <translation>Odkladací priestor (bez hibernácie)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1583"/>
      <source>Swap (with Hibernate)</source>
      <comment>@label</comment>
      <translation>Odkladací priestor (s hibernáciou)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1586"/>
      <source>Swap to file</source>
      <comment>@label</comment>
      <translation>Odkladací priestor v súbore</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1599"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Ručné rozdelenie oddielov&lt;/strong&gt;&lt;br/&gt;Môžete vytvoriť alebo zmeniť veľkosť oddielov podľa seba.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1627"/>
      <source>Bootloader location:</source>
      <comment>@label</comment>
      <translation>Umiestnenie zavádzača:</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="267"/>
      <source>Successfully unmounted %1.</source>
      <translation>Úspešne odpojený oddiel %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="274"/>
      <source>Successfully disabled swap %1.</source>
      <translation>Úspešne zakázaný odkladací priestor na oddieli %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="300"/>
      <source>Successfully cleared swap %1.</source>
      <translation>Úspešne vymazaný odkladací priestor na oddieli %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="314"/>
      <source>Successfully closed mapper device %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="327"/>
      <source>Successfully disabled volume group %1.</source>
      <translation>Úspešne zakázaná skupina zväzkov %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="366"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <comment>@title</comment>
      <translation>Vymazať pripojenia pre operácie rozdelenia oddielov na zariadení %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="372"/>
      <source>Clearing mounts for partitioning operations on %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="391"/>
      <source>Cleared all mounts for %1</source>
      <translation>Vymazané všetky pripojenia pre zariadenie %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
      <source>Clearing all temporary mounts…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="70"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Vymazané všetky dočasné pripojenia.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="235"/>
      <source>Could not run command.</source>
      <translation>Nepodarilo sa spustiť príkaz.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="236"/>
      <source>The commands use variables that are not defined. Missing variables are: %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="142"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Inštalácia zlyhala</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="143"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Inštalácia zlyhala</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>The setup of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>Inštalácia distribúcie %1 nebola úspešne dokončená.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="146"/>
      <source>The installation of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>Inštalácia distribúcie %1 bola úspešne dokončená.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="150"/>
      <source>Setup Complete</source>
      <comment>@title</comment>
      <translation>Inštalácia dokončená</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="151"/>
      <source>Installation Complete</source>
      <comment>@title</comment>
      <translation>Inštalácia dokončená</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="153"/>
      <source>The setup of %1 is complete.</source>
      <comment>@info</comment>
      <translation>Inštalácia distribúcie %1 je dokončená.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="154"/>
      <source>The installation of %1 is complete.</source>
      <comment>@info</comment>
      <translation>Inštalácia distribúcie %1s je dokončená.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="504"/>
      <source>Keyboard model has been set to %1.</source>
      <comment>@label, %1 is keyboard model, as in Apple Magic Keyboard</comment>
      <translation>Model klávesnice bol nastavený na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="512"/>
      <source>Keyboard layout has been set to %1/%2.</source>
      <comment>@label, %1 is layout, %2 is layout variant</comment>
      <translation>Rozloženie klávesnice bolo nastavené na %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="381"/>
      <source>Set timezone to %1.</source>
      <comment>@action</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="418"/>
      <source>The system language will be set to %1.</source>
      <comment>@info</comment>
      <translation>Jazyk systému bude nastavený na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="425"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <comment>@info</comment>
      <translation>Miestne nastavenie čísel a dátumov bude nastavené na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Sieťová inštalácia. (Zakázaná: Nesprávna konfigurácia)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="55"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Sieťová inštalácia. (Zakázaná: Boli prijaté neplatné údaje o skupinách)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="57"/>
      <source>Network Installation. (Disabled: Internal error)</source>
      <translation>Sieťová inštalácia. (Zakázaná: vnútorná chyba)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="59"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Sieťová inštalácia. (Zakázaná: Nie je možné získať zoznamy balíkov. Skontrolujte vaše sieťové pripojenie.)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="61"/>
      <source>Network Installation. (Disabled: No package list)</source>
      <translation>Sieťová inštalácia. (Zakázaná: bez zoznamu balíkov)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="76"/>
      <source>Package selection</source>
      <translation>Výber balíkov</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="110"/>
      <source>Package Selection</source>
      <translation>Výber balíkov</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="112"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Prosím, vyberte produkt zo zoznamu. Vybraný produkt bude nainštalovaný.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="241"/>
      <source>Packages</source>
      <translation>Balíky</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>Install option: &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>Voľba inštalácie: &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>None</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="35"/>
      <source>Summary</source>
      <comment>@label</comment>
      <translation>Súhrn</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="39"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Toto je prehľad toho, čo sa stane, keď spustíte inštaláciu.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="44"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Toto je prehľad toho, čo sa stane, keď spustíte inštaláciu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="236"/>
      <source>Your username is too long.</source>
      <translation>Vaše používateľské meno je príliš dlhé.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="242"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Vaše používateľské meno musí začínať malým písmenom alebo podčiarkovníkom.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="246"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Sú povolené iba malé písmená, číslice, podtržníky a pomlčky.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="252"/>
      <source>'%1' is not allowed as username.</source>
      <translation>„%1“ nie je možné použiť ako používateľské meno.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="301"/>
      <source>Your hostname is too short.</source>
      <translation>Váš názov hostiteľa je príliš krátky.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="305"/>
      <source>Your hostname is too long.</source>
      <translation>Váš názov hostiteľa je príliš dlhý.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="311"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>„%1“ nie je možné použiť ako názov hostiteľa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="316"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Sú povolené iba písmená, číslice, podtržníky a pomlčky.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="597"/>
      <source>Your passwords do not match!</source>
      <translation>Vaše heslá sa nezhodujú!</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="611"/>
      <source>OK!</source>
      <translation>OK!</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="57"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="66"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Tento počítač nespĺňa niektoré z odporúčaných požiadaviek pre inštaláciu distribúcie %1.&lt;br/&gt;Inštalácia môže pokračovať, ale niektoré funkcie môžu byť zakázané.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="70"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Tento počítač nespĺňa niektoré z odporúčaných požiadaviek pre inštaláciu distribúcie %1.&lt;br/&gt;Inštalácia môže pokračovať, ale niektoré funkcie môžu byť zakázané.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="80"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Tento program vám položí niekoľko otázok a nainštaluje distribúciu %2 do vášho počítača.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="264"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vitajte v inštalačnom programe Calamares pre distribúciu %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="265"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vitajte pri inštalácii distribúcie %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="269"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vitajte v aplikácii Calamares, inštalátore distribúcie %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="270"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Vitajte v inštalátore distribúcie %1&lt;/h1&gt;</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="115"/>
      <source>Performing contextual processes' job…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Vytvorenie oddielu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>Veľ&amp;kosť:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>&amp;Typ oddielu:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>Primar&amp;y</source>
      <translation>H&amp;lavný</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>Ro&amp;zšírený</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;Systém súborov:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>Názov LVM LV</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>Bo&amp;d pripojenia:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="191"/>
      <source>Flags:</source>
      <translation>Príznaky:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="224"/>
      <source>Label for the filesystem</source>
      <translation>Menovka systému súborov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="234"/>
      <source>FS Label:</source>
      <translation>Menovka SS:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="67"/>
      <source>En&amp;crypt</source>
      <comment>@action</comment>
      <translation>Zaši&amp;frovať</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="195"/>
      <source>Logical</source>
      <comment>@label</comment>
      <translation>Logický</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="200"/>
      <source>Primary</source>
      <comment>@label</comment>
      <translation>Primárny</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="219"/>
      <source>GPT</source>
      <comment>@label</comment>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="91"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <comment>@info</comment>
      <translation>Bod pripojenia sa už používa. Prosím, vyberte iný.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="96"/>
      <source>Mountpoint must start with a &lt;tt&gt;/&lt;/tt&gt;.</source>
      <comment>@info</comment>
      <translation>Bod pripojenia musí začínať znakom &lt;tt&gt;/&lt;/tt&gt;.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="181"/>
      <source>Create new %1MiB partition on %3 (%2) with entries %4</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="189"/>
      <source>Create new %1MiB partition on %3 (%2)</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="196"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="212"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2) with entries &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="222"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="229"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="254"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="257"/>
      <source>Creating new %1 partition on %2…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="274"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Inštalátor zlyhal pri vytváraní oddielu na disku „%1“.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Vytvorenie tabuľky oddielov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Vytvorením novej tabuľky oddielov sa odstránia všetky existujúce údaje na disku.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Ktorý typ tabuľky oddielov chcete vytvoriť?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Hlavný zavádzací záznam (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>Tabuľka oddielov GUID (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="41"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="58"/>
      <source>Creating new %1 partition table on %2…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
      <source>Creating new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3)…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="86"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Inštalátor zlyhal pri vytváraní tabuľky oddielov na zariadení %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="33"/>
      <source>Create user %1</source>
      <translation>Vytvoriť používateľa %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="39"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="45"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="137"/>
      <source>Creating user %1…</source>
      <comment>@status</comment>
      <translation>Vytvára sa používateľ %1…</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="120"/>
      <source>Preserving home directory…</source>
      <comment>@status</comment>
      <translation>Uchováva sa domovský adresár…</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="145"/>
      <source>Configuring user %1</source>
      <comment>@status</comment>
      <translation>Nastavuje sa používateľ %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="153"/>
      <source>Setting file permissions…</source>
      <comment>@status</comment>
      <translation>Nastavujú sa oprávnenia súborov…</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <comment>@title</comment>
      <translation>Vytvoriť skupinu zväzkov</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="32"/>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="44"/>
      <source>Creating new volume group named %1…</source>
      <comment>@status</comment>
      <translation>Vytvorenie novej skupiny zväzkov s názvom %1…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Creating new volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="51"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Inštalátor zlyhal pri vytváraní skupiny zväzkov s názvom „%1“.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="38"/>
      <source>Deactivating volume group named %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="32"/>
      <source>Deactivating volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Inštalátor zlyhal pri deaktivovaní skupiny zväzkov s názvom %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="85"/>
      <source>Deleting partition %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="79"/>
      <source>Deleting partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="99"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Inštalátor zlyhal pri odstraňovaní oddielu %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="78"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Tento typ tabuľky oddielov je vhodný iba pre staršie systémy, ktoré sa spúšťajú zo zavádzacieho prostredia &lt;strong&gt;BIOS&lt;/strong&gt;. GPT je odporúčaná vo väčšine ďalších prípadov.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Upozornenie:&lt;/strong&gt; Tabuľka oddielov MBR je zastaralý štandard z éry operačného systému MS-DOS.&lt;br&gt;Môžu byť vytvorené iba 4 &lt;em&gt;primárne&lt;/em&gt; oddiely a z nich môže byť jeden &lt;em&gt;rozšíreným&lt;/em&gt; oddielom, ktorý môže následne obsahovať viacero &lt;em&gt;logických&lt;/em&gt; oddielov.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="89"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Toto je odporúčaná tabuľka oddielov pre moderné systémy, ktoré sa spúšťajú zo zavádzacieho prostredia &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="95"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Toto je &lt;strong&gt;slučkové&lt;/strong&gt; zariadenie.&lt;br&gt;&lt;br&gt;Je to pseudo-zariadenie bez tabuľky oddielov, čo umožňuje prístup k súborom ako na blokovom zariadení. Tento druh inštalácie obvykle obsahuje iba jeden systém súborov.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Inštalátor &lt;strong&gt;nemôže rozpoznať tabuľku oddielov&lt;/strong&gt; na vybranom úložnom zariadení.&lt;br&gt;&lt;br&gt;Zariadenie buď neobsahuje žiadnu tabuľku oddielov, alebo je tabuľka oddielov poškodená, alebo je neznámeho typu.&lt;br&gt;Inštalátor môže vytvoriť novú tabuľku oddielov buď automaticky alebo prostredníctvom stránky s ručným rozdelením oddielov.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="139"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Toto zariadenie obsahuje tabuľku oddielov &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="147"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Typ &lt;strong&gt;tabuľky oddielov&lt;/strong&gt; na vybranom úložnom zariadení.&lt;br&gt;&lt;br&gt;Jediným spôsobom ako zmeniť tabuľku oddielov je vymazanie a znovu vytvorenie tabuľky oddielov od začiatku, čím sa zničia všetky údaje úložnom zariadení.&lt;br&gt;Inštalátor ponechá aktuálnu tabuľku oddielov, pokiaľ sa výlučne nerozhodnete inak.&lt;br&gt;Ak nie ste si istý, na moderných systémoch sa preferuje typ tabuľky oddielov GPT.</translation>
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
      <source>Writing LUKS configuration for Dracut to %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skipping writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <comment>@error</comment>
      <translation>Zlyhalo otvorenie %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="35"/>
      <source>Performing dummy C++ job…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Úprava existujúceho oddielu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Con&amp;tent:</source>
      <translation>O&amp;bsah:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>&amp;Ponechať</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Formátovať</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Upozornenie: Naformátovaním oddielu sa vymažú všetky existujúce údaje.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>Bod pripoje&amp;nia:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source>Si&amp;ze:</source>
      <translation>V&amp;eľkosť:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="139"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="146"/>
      <source>Fi&amp;le System:</source>
      <translation>S&amp;ystém súborov:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="159"/>
      <source>Flags:</source>
      <translation>Príznaky:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="179"/>
      <source>Label for the filesystem</source>
      <translation>Menovka systému súborov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="189"/>
      <source>FS Label:</source>
      <translation>Menovka SS:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="280"/>
      <source>Passphrase for existing partition</source>
      <translation>Heslo pre existujúci oddiel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="281"/>
      <source>Partition %1 could not be decrypted with the given passphrase.&lt;br/&gt;&lt;br/&gt;Edit the partition again and give the correct passphrase or delete and create a new encrypted partition.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>&amp;Zašifrovať systém</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="43"/>
      <source>Your system does not seem to support encryption well enough to encrypt the entire system. You may enable encryption, but performance may suffer.</source>
      <translation>Zdá sa, že váš systém nepodporuje šifrovanie na takej úrovni, aby mohol byť zašifrovaný celý systém. Môžete povoliť šifrovanie, ale na úkor výkonu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="59"/>
      <source>Passphrase</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="69"/>
      <source>Confirm passphrase</source>
      <translation>Potvrdenie hesla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="165"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="181"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <comment>@tooltip</comment>
      <translation>Prosím, zadajte rovnaké heslo do oboch polí.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="171"/>
      <source>Password must be a minimum of %1 characters.</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ErrorDialog</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="40"/>
      <source>Details:</source>
      <translation>Podrobnosti:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="56"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Chceli by ste vložiť záznam z inštalácie na web?</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="179"/>
      <source>Set partition information</source>
      <comment>@title</comment>
      <translation>Nastaviť informácie o oddieli</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="208"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition with features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Nainštalovať distribúciu %1 na &lt;strong&gt;nový&lt;/strong&gt; systémový oddiel %2 s funkciami &lt;em&gt;%3&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="217"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="226"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt; and features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="235"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;%3</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="250"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt; with features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="260"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="270"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt; and features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="280"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;%4…</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="296"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="305"/>
      <source>Setting up mount points…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Reštartovať teraz</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="75"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Všetko je dokončené.&lt;/h1&gt;&lt;br/&gt;Distribúcia %1 bola nainštalovaná do vášho počítača.&lt;br/&gt;Teraz môžete začať používať váš nový systém.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="80"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Keď je zaškrtnuté toto políčko, váš systém sa okamžite reštartuje po stlačení tlačidla &lt;span style="font-style:italic;"&gt;Dokončiť&lt;/span&gt; alebo zatvorení inštalačného programu.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="89"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Všetko je dokončené.&lt;/h1&gt;&lt;br/&gt;Distribúcia %1 bola nainštalovaná do vášho počítača.&lt;br/&gt;Teraz môžete reštartovať počítač a spustiť váš nový systém, alebo pokračovať v používaní živého prostredia distribúcie %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="95"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Keď je zaškrtnuté toto políčko, váš systém sa okamžite reštartuje po stlačení tlačidla &lt;span style="font-style:italic;"&gt;Dokončiť&lt;/span&gt; alebo zatvorení inštalátora.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="109"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>&lt;h1&gt;Inštalácia zlyhala&lt;/h1&gt;&lt;br/&gt;Distribúcia %1 nebola nainštalovaná do vášho počítača.&lt;br/&gt;Chybová hláška: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="118"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>&lt;h1&gt;Inštalácia zlyhala&lt;/h1&gt;&lt;br/&gt;Distribúcia %1 nebola nainštalovaná do vášho počítača.&lt;br/&gt;Chybová hláška: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedQmlViewStep</name>
    <message>
      <location filename="../src/modules/finishedq/FinishedQmlViewStep.cpp" line="35"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Dokončenie</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="46"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Dokončenie</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="39"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="49"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="62"/>
      <source>%1 (%2)</source>
      <comment>partition label %1 (device path %2)</comment>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="64"/>
      <source>Formatting partition %1 with file system %2…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="73"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Inštalátor zlyhal pri formátovaní oddielu %1 na disku „%2“.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>Please ensure the system has at least %1 GiB available drive space.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>Available drive space is all of the hard disks and SSDs connected to the system.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="165"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Nie je dostatok miesta na disku. Vyžaduje sa aspoň %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="173"/>
      <source>has at least %1 GiB working memory</source>
      <translation>obsahuje aspoň %1 GiB voľnej operačnej pamäte</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="175"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Počítač neobsahuje dostatok operačnej pamäte. Vyžaduje sa aspoň %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="184"/>
      <source>is plugged in to a power source</source>
      <translation>je pripojený k zdroju napájania</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="185"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Počítač nie je pripojený k zdroju napájania.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="192"/>
      <source>is connected to the Internet</source>
      <translation>je pripojený k internetu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="193"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Počítač nie je pripojený k internetu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="200"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>má spustený inštalátor s právami správcu (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="204"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Inštalačný program nie je spustený s právami správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="205"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Inštalátor nie je spustený s právami správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="213"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>má obrazovku dostatočne veľkú na zobrazenie celého inštalátora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="217"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Obrazovka je príliš malá na to, aby bolo možné zobraziť inštalačný program.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="218"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Obrazovka je príliš malá na to, aby bolo možné zobraziť inštalátor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="227"/>
      <source>is always false</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="228"/>
      <source>The computer says no.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="236"/>
      <source>is always false (slowly)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="237"/>
      <source>The computer says no (slowly).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="244"/>
      <source>is always true</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="245"/>
      <source>The computer says yes.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="253"/>
      <source>is always true (slowly)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="254"/>
      <source>The computer says yes (slowly).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="262"/>
      <source>is checked three times.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="265"/>
      <source>The snark has not been checked three times.</source>
      <comment>The (some mythological beast) has not been checked three times.</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="39"/>
      <source>Collecting information about your machine…</source>
      <comment>@status</comment>
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
      <translation>Hromadný identifikátor výrobcu</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepodarilo sa vytvoriť adresáre &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepodarilo sa otvoriť súbor &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nepodarilo sa zapísať do súboru &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="27"/>
      <source>Creating initramfs…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="51"/>
      <source>Konsole not installed.</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="52"/>
      <source>Please install KDE Konsole and try again!</source>
      <comment>@info</comment>
      <translation>Prosím, nainštalujte Konzolu prostredia KDE a skúste to znovu!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="127"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <comment>@info</comment>
      <translation>Spúšťa sa skript: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="40"/>
      <source>Script</source>
      <comment>@label</comment>
      <translation>Skript</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klávesnica</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="41"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klávesnica</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System Locale Setting</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>Miestne nastavenie systému ovplyvní jazyk a znakovú sadu niektorých prvkov používateľského rozhrania v príkazovom riadku.&lt;br/&gt;Aktuálne nastavenie je &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>&amp;Zrušiť</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="56"/>
      <source>&amp;OK</source>
      <comment>@button</comment>
      <translation>&amp;OK</translation>
    </message>
  </context>
  <context>
    <name>LOSHJob</name>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="35"/>
      <source>Configuring encrypted swap.</source>
      <translation>Konfigurácia zašifrovaného odkladacieho priestoru.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="87"/>
      <source>No target system available.</source>
      <translation>Nie je dostupný žiadny cieľový systém.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="95"/>
      <source>No rootMountPoint is set.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="100"/>
      <source>No configFilePath is set.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Licenčné podmienky&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="142"/>
      <source>I accept the terms and conditions above.</source>
      <comment>@info</comment>
      <translation>Prijímam podmienky vyššie.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="144"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <comment>@info</comment>
      <translation>Prosím, prezrite si licenčné podmienky koncového používateľa (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <comment>@info</comment>
      <translation>Touto inštalačnou procedúrou sa nainštaluje uzavretý softvér, ktorý je predmetom licenčných podmienok.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="154"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <comment>@info</comment>
      <translation>Bez súhlasu podmienok nemôže inštalačná procedúra pokračovať.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <comment>@info</comment>
      <translation>Tento proces inštalácie môže nainštalovať uzavretý softvér, ktorý je predmetom licenčných podmienok v rámci poskytovania dodatočných funkcií a vylepšenia používateľských skúseností.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="165"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <comment>@info</comment>
      <translation>Ak nesúhlasíte s podmienkami, uzavretý softvér nebude nainštalovaný a namiesto neho budú použité alternatívy s otvoreným zdrojom.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="45"/>
      <source>License</source>
      <comment>@label</comment>
      <translation>Licencia</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="88"/>
      <source>URL: %1</source>
      <comment>@label</comment>
      <translation>URL: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="109"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;Ovládač %1&lt;/strong&gt;&lt;br/&gt;vytvoril %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="117"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;Ovládač grafickej karty %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;vytvoril %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;Zásuvný modul prehliadača %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;vytvoril %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="131"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;Kodek %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;vytvoril %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="138"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;Balík %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;vytvoril %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="145"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;vytvoril %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="169"/>
      <source>File: %1</source>
      <comment>@label</comment>
      <translation>Súbor: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="192"/>
      <source>Hide the license text</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="193"/>
      <source>Show the license text</source>
      <comment>@tooltip</comment>
      <translation>Zobraziť licenčný text</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="197"/>
      <source>Open the license agreement in browser</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <comment>@label</comment>
      <translation>Oblasť:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <comment>@label</comment>
      <translation>Zóna:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change…</source>
      <comment>@button</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Umiestnenie</translation>
    </message>
  </context>
  <context>
    <name>LocaleTests</name>
    <message>
      <location filename="../src/libcalamares/locale/Tests.cpp" line="272"/>
      <source>Quit</source>
      <translation>Ukončiť</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="71"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Umiestnenie</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="33"/>
      <source>Configuring LUKS key file.</source>
      <translation>Nastavuje sa kľúčový súbor LUKS.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="254"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="262"/>
      <source>No partitions are defined.</source>
      <translation>Nie sú určené žiadne oddiely.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="297"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="304"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Chyba pri inštalácii zašifrovaného koreňového súborového systému</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="298"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Koreňový oddiel %1 je typu LUKS, ale nebolo nastavené žiadne heslo.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="305"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Nepodarilo sa vytvoriť kľúčový súbor LUKS pre koreňový oddiel %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="55"/>
      <source>Generate machine-id.</source>
      <translation>Generovanie identifikátora počítača.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="71"/>
      <source>Configuration Error</source>
      <translation>Chyba konfigurácie</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="72"/>
      <source>No root mount point is set for MachineId.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="63"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="71"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="75"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="92"/>
      <source>File not found</source>
      <translation>Súbor sa nenašiel</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Cesta &lt;pre&gt;%1&lt;/pre&gt; musí byť úplnou cestou.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nepodarilo sa vytvoriť nový náhodný súbor &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="237"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Časová zóna: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@info</comment>
      <translation>Prosím, vyberte vaše preferované umiestnenie, aby mohol inštalátor pre vás navrhnúť
            miestne nastavenia a časovú zónu. Navrhnuté nastavenia môžete doladiť nižšie. Mapu môžete presúvať ťahaním a približovať alebo odďaľovať tlačidlami +/- alebo rolovaním myšou.</translation>
    </message>
  </context>
  <context>
    <name>Map-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="261"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Časová zóna: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="282"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@label</comment>
      <translation>Prosím, vyberte vaše preferované umiestnenie, aby mohol inštalátor pre vás navrhnúť
            miestne nastavenia a časovú zónu. Navrhnuté nastavenia môžete doladiť nižšie. Mapu môžete presúvať ťahaním a približovať alebo odďaľovať tlačidlami +/- alebo rolovaním myšou.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="50"/>
      <source>Package selection</source>
      <translation>Výber balíkov</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
      <source>Office software</source>
      <translation>Kancelársky softvér</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
      <source>Office package</source>
      <translation>Kancelársky balík</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="53"/>
      <source>Browser software</source>
      <translation>Prehliadač</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Browser package</source>
      <translation>Balík prehliadača</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Web browser</source>
      <translation>Webový prehliadač</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Kernel</source>
      <comment>label for netinstall module, Linux kernel</comment>
      <translation>Jadro</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Services</source>
      <comment>label for netinstall module, system services</comment>
      <translation>Služby</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Login</source>
      <comment>label for netinstall module, choose login manager</comment>
      <translation>Prihlásenie</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Desktop</source>
      <comment>label for netinstall module, choose desktop environment</comment>
      <translation>Pracovné prostredie</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Applications</source>
      <translation>Aplikácie</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Communication</source>
      <comment>label for netinstall module</comment>
      <translation>Komunikácia</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Development</source>
      <comment>label for netinstall module</comment>
      <translation>Vývoj</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Office</source>
      <comment>label for netinstall module</comment>
      <translation>Kancelária</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Multimedia</source>
      <comment>label for netinstall module</comment>
      <translation>Multimédiá</translation>
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
      <translation>Motívy</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Gaming</source>
      <comment>label for netinstall module</comment>
      <translation>Hry</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Utilities</source>
      <comment>label for netinstall module</comment>
      <translation>Nástroje</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Poznámky</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>H&amp;romadne:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Sem zadajte hromadný identifikátor. Bude uložený v cieľovom systéme.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;Konfigurácia od výrobcu&lt;/h1&gt;&lt;p&gt;Inštalátor Calamares použije nastavenia od výrobcu pri konfigurácii cieľového systému.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="118"/>
      <source>OEM Configuration</source>
      <translation>Konfigurácia od výrobcu</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="124"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nastavenie hromadného identifikátora výrobcu na &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Časová zóna: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Zóny</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Offline-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Časová zóna: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Zóny</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="52"/>
      <source>Password is too short</source>
      <translation>Heslo je príliš krátke</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="68"/>
      <source>Password is too long</source>
      <translation>Heslo je príliš dlhé</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="189"/>
      <source>Password is too weak</source>
      <translation>Heslo je príliš slabé</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="197"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Chyba počas vyhradzovania pamäte pri nastavovaní „%1“</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="200"/>
      <source>Memory allocation error</source>
      <translation>Chyba počas vyhradzovania pamäte</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password is the same as the old one</source>
      <translation>Heslo je rovnaké ako to staré</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="204"/>
      <source>The password is a palindrome</source>
      <translation>Heslo je palindróm</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password differs with case changes only</source>
      <translation>Heslo sa odlišuje iba vo veľkosti písmen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="208"/>
      <source>The password is too similar to the old one</source>
      <translation>Heslo je príliš podobné ako to staré</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password contains the user name in some form</source>
      <translation>Heslo obsahuje v nejakom tvare používateľské meno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="212"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Heslo obsahuje v nejakom tvare slová zo skutočného mena používateľa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Heslo obsahuje zakázané slová v určitom tvare</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Heslo obsahuje menej ako %n číslo</numerusform>
        <numerusform>Heslo obsahuje menej ako %n čísla</numerusform>
        <numerusform>Heslo obsahuje menej ako %n čísla</numerusform>
        <numerusform>Heslo obsahuje menej ako %n čísel</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password contains too few digits</source>
      <translation>Heslo tiež obsahuje pár číslic</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Heslo obsahuje menej ako %n veľké písmeno</numerusform>
        <numerusform>Heslo obsahuje menej ako %n veľké písmená</numerusform>
        <numerusform>Heslo obsahuje menej ako %n veľkého písmena</numerusform>
        <numerusform>Heslo obsahuje menej ako %n veľkých písmen</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="229"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Heslo obsahuje príliš málo veľkých písmen</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="233"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Heslo obsahuje menej ako %n malé písmeno</numerusform>
        <numerusform>Heslo obsahuje menej ako %n malé písmená</numerusform>
        <numerusform>Heslo obsahuje menej ako %n malého písmena</numerusform>
        <numerusform>Heslo obsahuje menej ako %n malých písmen</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="236"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Heslo obsahuje príliš málo malých písmen</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="240"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Heslo obsahuje príliš málo nealfanumerických znakov</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Heslo je kratšie ako %n znak</numerusform>
        <numerusform>Heslo je kratšie ako %n znaky</numerusform>
        <numerusform>Heslo je kratšie ako %n znaku</numerusform>
        <numerusform>Heslo je kratšie ako %n znakov</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>The password is too short</source>
      <translation>Heslo je príliš krátke</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Heslo je obrátená verzia predošlého hesla</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="256"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Heslo obsahuje menej ako %n triedu znakov</numerusform>
        <numerusform>Heslo obsahuje menej ako %n triedy znakov</numerusform>
        <numerusform>Heslo obsahuje menej ako %n triedy znakov</numerusform>
        <numerusform>Heslo obsahuje menej ako %n tried znakov</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
      <source>The password does not contain enough character classes</source>
      <translation>Heslo neobsahuje dostatok tried znakov</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Heslo obsahuje viac ako %n rovnaký znak opakujúci sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n rovnaké znaky opakujúce sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n rovnakého znaku opakujúceho sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n rovnakých znakov opakujúcich sa po sebe</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="266"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Heslo obsahuje príliš veľa rovnakých znakov</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="270"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Heslo obsahuje viac ako %n znak rovnakej triedy opakujúci sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n znaky rovnakej triedy opakujúce sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n znaku rovnakej triedy opakujúceho sa po sebe</numerusform>
        <numerusform>Heslo obsahuje viac ako %n znakov rovnakej triedy opakujúcich sa po sebe</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="276"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Heslo obsahuje postupne príliš veľa znakov toho istého typu</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="281"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="287"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Heslo obsahuje príliš dlhú sekvenciu monotónnych znakov</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="290"/>
      <source>No password supplied</source>
      <translation>Nebolo poskytnuté žiadne heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="292"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Nedajú sa získať náhodné čísla zo zariadenia RNG</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="294"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Generovanie hesla zlyhalo - potrebná entropia je príliš nízka na nastavenie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="299"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Heslo zlyhalo pri slovníkovej kontrole - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The password fails the dictionary check</source>
      <translation>Heslo zlyhalo pri slovníkovej kontrole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown setting - %1</source>
      <translation>Neznáme nastavenie - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="308"/>
      <source>Unknown setting</source>
      <translation>Neznáme nastavenie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="312"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Nesprávna celočíselná hodnota nastavenia - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="314"/>
      <source>Bad integer value</source>
      <translation>Nesprávna celočíselná hodnota</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="318"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Nastavenie %1 nie je celé číslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="320"/>
      <source>Setting is not of integer type</source>
      <translation>Nastavenie nie je celé číslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="324"/>
      <source>Setting %1 is not of string type</source>
      <translation>Nastavenie %1 nie je reťazec</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="326"/>
      <source>Setting is not of string type</source>
      <translation>Nastavenie nie je reťazec</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="328"/>
      <source>Opening the configuration file failed</source>
      <translation>Zlyhalo otváranie konfiguračného súboru</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="330"/>
      <source>The configuration file is malformed</source>
      <translation>Konfiguračný súbor je poškodený</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="332"/>
      <source>Fatal failure</source>
      <translation>Závažné zlyhanie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="334"/>
      <source>Unknown error</source>
      <translation>Neznáma chyba</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="50"/>
      <source>Product Name</source>
      <translation>Názov produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="63"/>
      <source>TextLabel</source>
      <translation>Textová menovka</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="79"/>
      <source>Long Product Description</source>
      <translation>Dlhý popis produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Výber balíkov</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Prosím, vyberte produkt zo zoznamu. Vybraný produkt bude nainštalovaný.</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Name</source>
      <translation>Názov</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Description</source>
      <translation>Popis</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard model:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="146"/>
      <source>Type here to test your keyboard</source>
      <translation>Tu môžete písať na odskúšanie vašej klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="153"/>
      <source>Switch Keyboard:</source>
      <extracomment>shortcut for switching between keyboard layouts</extracomment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Aké je vaše meno?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Vaše celé meno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Aké meno chcete použiť na prihlásenie?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>prihlásenie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Aký je názov tohto počítača?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Tento názov bude použitý, keď sprístupníte počítač v sieti.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Názov počítača</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Zvoľte heslo pre zachovanie vášho účtu v bezpečí.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom. Dobré heslo by malo obsahovať mix písmen, čísel a diakritiky, malo by mať dĺžku aspoň osem znakov a malo by byť pravidelne menené.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Zopakovanie hesla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Keď je zaškrtnuté toto políčko, kontrola kvality hesla bude ukončená a nebudete môcť použiť slabé heslo.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Požadovať silné heslá.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Prihlásiť automaticky bez pýtania hesla.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Použiť rovnaké heslo pre účet správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Zvoľte heslo pre účet správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="627"/>
      <source>Use Active Directory</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="638"/>
      <source>Domain:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="652"/>
      <source>Domain Administrator:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="662"/>
      <source>Password:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="680"/>
      <source>IP Address (optional):</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="178"/>
      <source>Root</source>
      <translation>Koreňový adresár</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="182"/>
      <source>Home</source>
      <comment>@label</comment>
      <translation>Domovský adresár</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="186"/>
      <source>Boot</source>
      <comment>@label</comment>
      <translation>Zavádzač</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="191"/>
      <source>EFI system</source>
      <comment>@label</comment>
      <translation>Systém EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="195"/>
      <source>Swap</source>
      <comment>@label</comment>
      <translation>Odkladací priestor</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="199"/>
      <source>New partition for %1</source>
      <comment>@label</comment>
      <translation>Nový oddiel pre %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
      <source>New partition</source>
      <comment>@label</comment>
      <translation>Nový oddiel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="228"/>
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
      <comment>@title</comment>
      <translation>Voľné miesto</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="161"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="205"/>
      <source>New Partition</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>Name</source>
      <comment>@title</comment>
      <translation>Názov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>File System</source>
      <comment>@title</comment>
      <translation>Systém súborov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>File System Label</source>
      <comment>@title</comment>
      <translation>Menovka systému súborov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="313"/>
      <source>Mount Point</source>
      <comment>@title</comment>
      <translation>Bod pripojenia</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="315"/>
      <source>Size</source>
      <comment>@title</comment>
      <translation>Veľkosť</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Úložné zar&amp;iadenie:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>V&amp;rátiť všetky zmeny</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Nová &amp;tabuľka oddielov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Vytvoriť</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Upraviť</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>O&amp;dstrániť</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Nová skupina zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Zmeniť veľkosť skupiny zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Deaktivovať skupinu zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Odstrániť skupinu zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Nai&amp;nštalovať zavádzač na:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="227"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Naozaj chcete vytvoriť novú tabuľku oddielov na zariadení %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="262"/>
      <source>Can not create new partition</source>
      <translation>Nedá sa vytvoriť nový oddiel</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="263"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>Tabuľka oddielov na %1 už obsahuje primárne oddiely %2 a nie je možné pridávať žiadne ďalšie. Odstráňte jeden primárny oddiel a namiesto toho pridajte rozšírenú oblasť.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="56"/>
      <source>Gathering system information…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="107"/>
      <source>Partitions</source>
      <comment>@label</comment>
      <translation>Oddiely</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="144"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="148"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="152"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="157"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning</source>
      <comment>@label</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="179"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3)</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="188"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="195"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="204"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="214"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="239"/>
      <source>Create a swap file.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="268"/>
      <source>Unsafe partition actions are enabled.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="271"/>
      <source>Partitioning is configured to &lt;b&gt;always&lt;/b&gt; fail.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="274"/>
      <source>No partitions will be changed.</source>
      <translation>Nebudú zmenené žiadne oddiely.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="314"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Teraz:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="332"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Potom:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="555"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a suitable filesystem.</source>
      <translation>Na spustenie distribúcie %1 je potrebný systémový oddiel EFI.&lt;br/&gt;&lt;br/&gt;Na konfiguráciu systémového oddielu EFI, prejdite späť a vyberte alebo vytvorte vhodný systém súborov.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="561"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;The EFI system partition does not meet recommendations. It is recommended to go back and select or create a suitable filesystem.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="569"/>
      <source>The filesystem must be mounted on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Systém súborov musí byť pripojený do &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="570"/>
      <source>The filesystem must have type FAT32.</source>
      <translation>Systém súborov musí byť typu FAT32.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="571"/>
      <source>The filesystem must have flag &lt;strong&gt;%1&lt;/strong&gt; set.</source>
      <translation>Systém súborov musí mať nastavený príznak &lt;strong&gt;%1 .</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="579"/>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="581"/>
      <source>The filesystem must be at least %1 MiB in size.</source>
      <translation>Systém súborov musí mať veľkosť aspoň %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="583"/>
      <source>The minimum recommended size for the filesystem is %1 MiB.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="585"/>
      <source>You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Môžete pokračovať bez nastavenia systémového oddielu EFI, ale váš systém môže zlyhať pri spúšťaní.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="587"/>
      <source>You can continue with this EFI system partition configuration but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="599"/>
      <source>No EFI system partition configured</source>
      <translation>Nie je nastavený žiadny oddiel systému EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="607"/>
      <source>EFI system partition configured incorrectly</source>
      <translation>Systémový oddiel EFI nie je správne nastavený</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="627"/>
      <source>EFI system partition recommendation</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="646"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Voľba na použitie tabuľky GPT s BIOSom</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="647"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;%2&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>Tabuľka oddielov GPT je najlepšou voľbou pre všetky systémy. Inštalátor podporuje taktiež inštaláciu pre systémy s BIOSom.&lt;br/&gt;&lt;br/&gt;Pre nastavenie tabuľky oddielov GPT s BIOSom, (ak ste tak už neučinili) prejdite späť a nastavte tabuľku oddielov na GPT, a potom vytvorte nenaformátovaný oddiel o veľkosti 8 MB s povoleným príznakom &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Nenaformátovaný oddiel o veľkosti 8 MB je potrebný na spustenie distribúcie %1 na systéme s BIOSom a tabuľkou GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="669"/>
      <source>Boot partition not encrypted</source>
      <translation>Zavádzací oddiel nie je zašifrovaný</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="670"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Spolu so zašifrovaným koreňovým oddielom bol nainštalovaný oddelený zavádzací oddiel, ktorý ale nie je zašifrovaný.&lt;br/&gt;&lt;br/&gt;S týmto typom inštalácie je ohrozená bezpečnosť, pretože dôležité systémové súbory sú uchovávané na nezašifrovanom oddieli.&lt;br/&gt;Ak si to želáte, môžete pokračovať, ale neskôr, počas spúšťania systému sa vykoná odomknutie systému súborov.&lt;br/&gt;Na zašifrovanie zavádzacieho oddielu prejdite späť a vytvorte ju znovu vybraním voľby &lt;strong&gt;Zašifrovať&lt;/strong&gt; v okne vytvárania oddielu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="762"/>
      <source>has at least one disk device available.</source>
      <translation>má dostupné aspoň jedno diskové zariadenie.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="763"/>
      <source>There are no partitions to install on.</source>
      <translation>Neexistujú žiadne oddiely, na ktoré je možné vykonať inštaláciu.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Applying Plasma Look-and-Feel…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Nepodarilo sa vybrať balík vzhľadu a dojmu prostredia KDE Plasma</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="80"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Prosím, zvoľte "look-and-feel" pre pracovné prostredie KDE Plasma. Tento krok môžete preskočiť po nastavení systému. Kliknutím na výber "look-and-feel" sa zobrazí živý náhľad daného vzhľadu a dojmu. </translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="87"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Prosím, zvoľte vzhľad a dojem pre pracovné prostredie KDE Plasma. Tento krok môžete preskočiť a nastaviť vzhľad a dojem po inštalácii systému. Kliknutím na výber Vzhľad a dojem sa zobrazí živý náhľad daného vzhľadu a dojmu.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <comment>@label</comment>
      <translation>Vzhľad a dojem</translation>
    </message>
  </context>
  <context>
    <name>PowerManagementInterface</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="138"/>
      <source>Calamares</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="138"/>
      <source>Installation in progress</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="56"/>
      <source>Saving files for later…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="64"/>
      <source>No files configured to save for later.</source>
      <translation>Žiadne konfigurované súbory pre uloženie na neskôr.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="88"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Nie všetky konfigurované súbory môžu byť uchované.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="301"/>
      <source>
There was no output from the command.</source>
      <translation>
Žiadny výstup z príkazu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="302"/>
      <source>
Output:
</source>
      <translation>
Výstup:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="307"/>
      <source>External command crashed.</source>
      <translation>Externý príkaz nečakane skončil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="308"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Príkaz &lt;i&gt;%1&lt;/i&gt; nečakane skončil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="315"/>
      <source>External command failed to start.</source>
      <translation>Zlyhalo spustenie externého príkazu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="316"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Zlyhalo spustenie príkazu &lt;i&gt;%1&lt;/i&gt; .</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="322"/>
      <source>Internal error when starting command.</source>
      <translation>Počas spúšťania príkazu sa vyskytla interná chyba.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="323"/>
      <source>Bad parameters for process job call.</source>
      <translation>Nesprávne parametre pre volanie úlohy procesu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="329"/>
      <source>External command failed to finish.</source>
      <translation>Zlyhalo dokončenie externého príkazu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="330"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Zlyhalo dokončenie príkazu &lt;i&gt;%1&lt;/i&gt; počas doby %2 sekúnd.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="338"/>
      <source>External command finished with errors.</source>
      <translation>Externý príkaz bol dokončený s chybami.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="339"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Príkaz &lt;i&gt;%1&lt;/i&gt; skončil s ukončovacím kódom %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Translation.cpp" line="170"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="33"/>
      <source>unknown</source>
      <comment>@partition info</comment>
      <translation>neznámy</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="35"/>
      <source>extended</source>
      <comment>@partition info</comment>
      <translation>rozšírený</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="37"/>
      <source>unformatted</source>
      <comment>@partition info</comment>
      <translation>nenaformátovaný</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="39"/>
      <source>swap</source>
      <comment>@partition info</comment>
      <translation>odkladací</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="145"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="192"/>
      <source>Default</source>
      <translation>Predvolený</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="101"/>
      <source>Directory not found</source>
      <translation>Adresár sa nenašiel</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="102"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nepodarilo sa vytvoriť nový náhodný súbor &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="74"/>
      <source>No product</source>
      <translation>Žiadny produkt</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="82"/>
      <source>No description provided.</source>
      <translation>Nie je poskytnutý żiadny popis.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="44"/>
      <source>(no mount point)</source>
      <translation>(žiadny bod pripojenia)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="39"/>
      <source>Unpartitioned space or unknown partition table</source>
      <comment>@info</comment>
      <translation>Nerozdelené miesto alebo neznáma tabuľka oddielov</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tento počítač nespĺňa niektoré z odporúčaných požiadaviek pre inštaláciu distribúcie %1.&lt;br/&gt;
  Inštalácia môže pokračovať, ale niektoré funkcie môžu byť zakázané.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="32"/>
      <source>Removing live user from the target system…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="38"/>
      <source>Removing Volume Group named %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="32"/>
      <source>Removing Volume Group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Inštalátor zlyhal pri odstraňovaní skupiny zväzkov s názvom „%1“.</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="37"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tento počítač nespĺňa minimálne požiadavky pre inštaláciu distribúcie %1.&lt;br/&gt;
  Inštalácia nemôže pokračovať.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="39"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tento počítač nespĺňa niektoré z odporúčaných požiadaviek pre inštaláciu distribúcie %1.&lt;br/&gt;
  Inštalácia môže pokračovať, ale niektoré funkcie môžu byť zakázané.</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="43"/>
      <source>Performing file system resize…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="162"/>
      <source>Invalid configuration</source>
      <comment>@error</comment>
      <translation>Neplatná konfigurácia</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="163"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <comment>@error</comment>
      <translation>Úloha zmeny veľkosti systému súborov má neplatnú konfiguráciu a nebude spustená.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>KPMCore not available</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="171"/>
      <source>Calamares cannot start KPMCore for the file system resize job.</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="180"/>
      <source>Resize failed.</source>
      <comment>@error</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="182"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>Systém súborov %1 sa nepodarilo nájsť v tomto systéme a nemôže sa zmeniť jeho veľkosť.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="184"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>Zariadenie %1 sa nepodarilo nájsť v tomto systéme a nemôže sa zmeniť jeho veľkosť.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="193"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="205"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="215"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="234"/>
      <source>Resize Failed</source>
      <comment>@error</comment>
      <translation>Zlyhala zmena veľkosti</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="194"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The filesystem %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>Nedá sa zmeniť veľkosť systému súborov %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The device %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>Nedá sa zmeniť veľkosť zariadenia %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="216"/>
      <source>The file system %1 must be resized, but cannot.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <source>The device %1 must be resized, but cannot</source>
      <comment>@info</comment>
      <translation>Musí sa zmeniť veľkosť zariadenia %1, ale nedá sa vykonať.</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="39"/>
      <source>Resize partition %1</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="45"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="54"/>
      <source>Resizing %2MiB partition %1 to %3MiB…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="70"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Inštalátor zlyhal pri zmene veľkosti oddielu %1 na disku „%2“.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <comment>@title</comment>
      <translation>Zmeniť veľkosť skupiny zväzkov</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="28"/>
      <source>Resize volume group named %1 from %2 to %3</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="47"/>
      <source>Resizing volume group named %1 from %2 to %3…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="58"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Inštalátor zlyhal pri zmene veľkosti skupiny zväzkov s názvom „%1“.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="47"/>
      <source>Checking requirements again in a few seconds ...</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="69"/>
      <source>Scanning storage devices…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="69"/>
      <source>Partitioning…</source>
      <comment>@status</comment>
      <translation>Rozdelenie oddielov…</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="36"/>
      <source>Set hostname %1</source>
      <translation>Nastavenie názvu hostiteľa %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="42"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Nastavenie názvu hostiteľa &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="48"/>
      <source>Setting hostname %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="121"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="128"/>
      <source>Internal Error</source>
      <translation>Vnútorná chyba</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="139"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="156"/>
      <source>Cannot write hostname to target system</source>
      <translation>Nedá sa zapísať názov hostiteľa do cieľového systému</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="66"/>
      <source>Setting keyboard model to %1, layout as %2-%3…</source>
      <comment>@status, %1 model, %2 layout, %3 variant</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="371"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <comment>@error</comment>
      <translation>Zlyhalo zapísanie nastavenia klávesnice pre virtuálnu konzolu.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="372"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is virtual console configuration path</comment>
      <translation>Zlyhalo zapísanie do %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="399"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <comment>@error</comment>
      <translation>Zlyhalo zapísanie nastavenia klávesnice pre server X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="400"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is keyboard configuration path</comment>
      <translation>Zlyhalo zapísanie do %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="416"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <comment>@error</comment>
      <translation>Zlyhalo zapísanie nastavenia klávesnice do existujúceho adresára /etc/default.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="417"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is default keyboard path</comment>
      <translation>Zlyhalo zapísanie do %1</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="44"/>
      <source>Set flags on partition %1</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="50"/>
      <source>Set flags on %1MiB %2 partition</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="54"/>
      <source>Set flags on new partition</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Set flags on partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="88"/>
      <source>Set flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="94"/>
      <source>Set flags on new partition to &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="112"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on new partition…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="122"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="130"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="136"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Inštalátor zlyhal pri nastavovaní príznakov na oddieli %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="38"/>
      <source>Set password for user %1</source>
      <translation>Nastavenie hesla pre používateľa %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="44"/>
      <source>Setting password for user %1…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="80"/>
      <source>Bad destination system path.</source>
      <translation>Nesprávny cieľ systémovej cesty.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMountPoint je %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>Cannot disable root account.</source>
      <translation>Nedá sa zakázať účet správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="108"/>
      <source>usermod terminated with error code %1.</source>
      <translation>Príkaz usermod ukončený s chybovým kódom %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>Cannot set password for user %1.</source>
      <translation>Nedá sa nastaviť heslo pre používateľa %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="32"/>
      <source>Setting timezone to %1/%2…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="60"/>
      <source>Cannot access selected timezone path.</source>
      <comment>@error</comment>
      <translation>Nedá sa získať prístup k vybranej ceste časovej zóny.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="61"/>
      <source>Bad path: %1</source>
      <comment>@error</comment>
      <translation>Nesprávna cesta: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="70"/>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <comment>@error</comment>
      <translation>Nedá sa nastaviť časová zóna.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <comment>@info</comment>
      <translation>Zlyhalo vytvorenie odakzu, cieľ: %1; názov odkazu: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Cannot open /etc/timezone for writing</source>
      <comment>@info</comment>
      <translation>Nedá sa otvoriť cesta /etc/timezone pre zapisovanie</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="181"/>
      <source>Preparing groups…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="193"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="198"/>
      <source>Could not create groups in target system</source>
      <translation>Nepodarilo sa vytvoriť skupiny v cieľovom systéme</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="199"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>Tieto skupiny chýbajú v cieľovom systéme: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="34"/>
      <source>Configuring &lt;pre&gt;sudo&lt;/pre&gt; users…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="70"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Nedá sa vykonať príkaz chmod na súbori sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="75"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Nedá sa vytvoriť súbor sudoers na zapisovanie.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="38"/>
      <source>Running shell processes…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>SlideCounter</name>
    <message>
      <location filename="../src/qml/calamares-qt5/slideshow/SlideCounter.qml" line="27"/>
      <location filename="../src/qml/calamares-qt6/slideshow/SlideCounter.qml" line="27"/>
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
      <translation>&amp;OK</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="24"/>
      <source>&amp;Yes</source>
      <translation>Án&amp;o</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="25"/>
      <source>&amp;No</source>
      <translation>&amp;Nie</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="26"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Zrušiť</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="27"/>
      <source>&amp;Close</source>
      <translation>&amp;Zavrieť</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <source>Installation feedback</source>
      <translation>Spätná väzba inštalácie</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Sending installation feedback…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Internal error in install-tracking.</source>
      <translation>Interná chyba príkazu install-tracking.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="125"/>
      <source>HTTP request timed out.</source>
      <translation>Požiadavka HTTP vypršala.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="192"/>
      <source>KDE user feedback</source>
      <translation>Používateľská spätná väzba prostredia KDE</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="198"/>
      <source>Configuring KDE user feedback…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="220"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="228"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>Chyba pri nastavovaní používateľskej spätnej väzby prostredia KDE.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="221"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>Nepodarilo sa správne nastaviť používateľskú spätnú väzbu prostredia KDE. Chyba %1 skriptu.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="229"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>Nepodarilo sa správne nastaviť používateľskú spätnú väzbu prostredia KDE. Chyba %1 inštalátora Calamares.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="135"/>
      <source>Machine feedback</source>
      <translation>Spätná väzba počítača</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="141"/>
      <source>Configuring machine feedback…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="164"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="173"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Chyba pri nastavovaní spätnej väzby počítača.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="166"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Nepodarilo sa správne nastaviť spätnú väzbu počítača. Chyba skriptu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="175"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Nepodarilo sa správne nastaviť spätnú väzbu počítača. Chyba inštalátora Calamares %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Zástupný text</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Kliknutím sem neodošlete &lt;span style=" font-weight:600;"&gt;absolútne žiadne informácie&lt;/span&gt; o vašej inštalácii.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Kliknutím sem získate viac informácií o spätnej väzbe od používateľa&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Vybraním tejto voľby odošlete informácie o vašej inštalácii a hardvéri. Tieto informácie budú odoslané &lt;b&gt;iba raz&lt;/b&gt; po dokončení inštalácie.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Vybraním tejto voľby budete pravidelne odosielať informácie o vašom &lt;b&gt;počítači&lt;/b&gt;, inštalácii, hardvéri a aplikáciách distribúcii %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Vybraním tejto voľby budete neustále odosielať informácie o vašej &lt;b&gt;používateľskej&lt;/b&gt; inštalácii, hardvéri, aplikáciách a charakteristike používania distribúcii %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <comment>@title</comment>
      <translation>Spätná väzba</translation>
    </message>
  </context>
  <context>
    <name>UmountJob</name>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="39"/>
      <source>Unmounting file systems…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="123"/>
      <source>No target system available.</source>
      <translation>Nie je dostupný žiadny cieľový systém.</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="131"/>
      <source>No rootMountPoint is set.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="199"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ak bude tento počítač používať viac ako jedna osoba, môžete nastaviť viacero účtov po inštalácii.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="205"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ak bude tento počítač používať viac ako jedna osoba, môžete nastaviť viacero účtov po inštalácii.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="35"/>
      <source>Users</source>
      <translation>Používatelia</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Používatelia</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="246"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Kľúč</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="250"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Hodnota</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Vytvoriť skupinu zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Zoznam fyzických zväzkov</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Názov skupiny zväzkov:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Typ skupiny zväzkov:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Fyzická veľkosť oblasti:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation> MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Celková veľkosť:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Využitá veľkosť:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Celkom sektorov:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Množstvo LZ:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Výber jazyka aplikácií a systému</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>Open donations website</source>
      <translation>Otvoriť webovú stránku s príspevkami</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="143"/>
      <source>&amp;Donate</source>
      <translation>&amp;Prispieť</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>Open help and support website</source>
      <translation>Otvoriť webovú stránku s pomocou a podporou</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
      <source>&amp;Support</source>
      <translation>Po&amp;dpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Otvoriť webovú stránku s problémami a chybami</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="169"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Známe problémy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>Open release notes website</source>
      <translation>Otvoriť webovú stránku s poznámkami k vydaniu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="182"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Poznámky k vydaniu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="237"/>
      <source>About %1 Setup</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="238"/>
      <source>About %1 Installer</source>
      <comment>@title</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="213"/>
      <source>%1 Support</source>
      <comment>@action</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="40"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Uvítanie</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="46"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Uvítanie</translation>
    </message>
  </context>
  <context>
    <name>ZfsJob</name>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="102"/>
      <source>Creating ZFS pools and datasets…</source>
      <comment>@status</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="162"/>
      <source>Failed to create zpool on </source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="180"/>
      <source>Configuration Error</source>
      <translation>Chyba konfigurácie</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="181"/>
      <source>No partitions are available for ZFS.</source>
      <translation>Nie sú dostupné žiadne oddiely pre ZFS.</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <source>Internal data missing</source>
      <translation>Chýbajú vnútorné údaje</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="264"/>
      <source>Failed to create zpool</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="336"/>
      <source>Failed to create dataset</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="337"/>
      <source>The output was: </source>
      <translation>Výstup bol:</translation>
    </message>
  </context>
  <context>
    <name>calamares-sidebar</name>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="89"/>
      <source>About</source>
      <translation>O inštalátore</translation>
    </message>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="115"/>
      <source>Debug</source>
      <translation>Ladiť</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="157"/>
      <source>About</source>
      <comment>@button</comment>
      <translation>O inštalátore</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="159"/>
      <source>Show information about Calamares</source>
      <comment>@tooltip</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="173"/>
      <source>Debug</source>
      <comment>@button</comment>
      <translation>Ladiť</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="175"/>
      <source>Show debug information</source>
      <comment>@tooltip</comment>
      <translation>Zobraziť ladiace informácie</translation>
    </message>
  </context>
  <context>
    <name>finishedq</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>Inštalácia dokončená</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <translation>Distribúcia %1 bola nainštalovaná do vášho počítača.&lt;br/&gt;
            Teraz môžete reštartovať váš počítač a spustiť nový systém, alebo pokračovať v používaní živého prostredia.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="65"/>
      <source>Close Installer</source>
      <translation>Zavrieť inštalátor</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="71"/>
      <source>Restart System</source>
      <translation>Reštartovať systém</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>finishedq-qt6</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="35"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Inštalácia dokončená</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="42"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>Distribúcia %1 bola nainštalovaná do vášho počítača.&lt;br/&gt;
            Teraz môžete reštartovať váš počítač a spustiť nový systém, alebo pokračovať v používaní živého prostredia.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="65"/>
      <source>Close Installer</source>
      <comment>@button</comment>
      <translation>Zavrieť inštalátor</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="71"/>
      <source>Restart System</source>
      <comment>@button</comment>
      <translation>Reštartovať systém</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>finishedq@mobile</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="36"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Inštalácia dokončená</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart your device.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>Distribúcia %1 bola nainštalovaná do vášho počítača.&lt;br/&gt;
            Teraz môžete reštartovať vaše zariadenie.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="66"/>
      <source>Close</source>
      <comment>@button</comment>
      <translation>Zavrieť</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="72"/>
      <source>Restart</source>
      <comment>@button</comment>
      <translation>Reštartovať</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Vybratím rozloženia aktivujete ukážku klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Model klávesnice:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Rozloženie</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Varianta</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Tu môžete písať na odskúšanie vašej klávesnice…</translation>
    </message>
  </context>
  <context>
    <name>keyboardq-qt6</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Vybratím rozloženia aktivujete ukážku klávesnice</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Model klávesnice:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Rozloženie</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Varianta</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Tu môžete písať na odskúšanie vašej klávesnice…</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Zmeniť</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>localeq-qt6</name>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Zmeniť</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Toto sú vzorové poznámky k vydaniu.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice je výkonným a bezplatným kancelárskym balíkom, ktorý používajú milióny ľudí po celom svete. Zahŕňa niekoľko aplikácií, ktoré ho robia najuniverzálnejším slobodným kancelárskym balíkom s otvoreným zdrojom na trhu.&lt;br/&gt;
                    Predvolená voľba.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Ak nechcete inštalovať kancelársky balík, stačí vybrať voľbu Žiadny kancelársky balík. Vždy môžete podľa potreby nejaký (alebo viacero) pridať neskôr vo vašom nainštalovanom systéme.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Žiadny kancelársky balík</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimálna inštalácia</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>packagechooserq-qt6</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice je výkonným a bezplatným kancelárskym balíkom, ktorý používajú milióny ľudí po celom svete. Zahŕňa niekoľko aplikácií, ktoré ho robia najuniverzálnejším slobodným kancelárskym balíkom s otvoreným zdrojom na trhu.&lt;br/&gt;
                    Predvolená voľba.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Ak nechcete inštalovať kancelársky balík, stačí vybrať voľbu Žiadny kancelársky balík. Vždy môžete podľa potreby nejaký (alebo viacero) pridať neskôr vo vašom nainštalovanom systéme.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Žiadny kancelársky balík</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimálna inštalácia</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>release_notes</name>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="45"/>
      <source>### %1
This an example QML file, showing options in Markdown with Flickable content.

QML with RichText can use HTML tags, with Markdown it uses the simple Markdown syntax, Flickable content is useful for touchscreens.

**This is bold text**

*This is italic text*

_This is underlined text_

&gt; blockquote

~~This is strikethrough~~

Code example:
```
ls -l /home
```

**Lists:**
 * Intel CPU systems
 * AMD CPU systems

The vertical scrollbar is adjustable, current width set to 10.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="80"/>
      <source>Back</source>
      <translation>Späť</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="43"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Vyberte vaše používateľské meno a poverenia na prihlásenie a vykonávanie administrátorských úloh</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="56"/>
      <source>What is your name?</source>
      <translation>Aké je vaše meno?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="63"/>
      <source>Your full name</source>
      <translation>Vaše celé meno</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Aké meno chcete použiť na prihlásenie?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login name</source>
      <translation>Prihlasovacie meno</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="116"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Ak bude tento počítač používať viac ako jedna osoba, môžete po inštalácii vytvoriť viacero účtov.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="129"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Sú povolené iba malé písmená, číslice, podtržníky a pomlčky.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="138"/>
      <source>root is not allowed as username.</source>
      <translation>root nie je možné použiť ako meno používateľa</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="147"/>
      <source>What is the name of this computer?</source>
      <translation>Aký je názov tohto počítača?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="153"/>
      <source>Computer name</source>
      <translation>Názov počítača</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="180"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Tento názov bude použitý, keď zviditeľníte počítač ostatným v sieti.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="193"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>Sú povolené iba písmená, číslice, podtržníky a pomlčky, v minimálnom počte dvoch znakov.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="202"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost nie možné použiť ako názov hostiteľa</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="211"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Zvoľte heslo pre zachovanie vášho účtu v bezpečí.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="221"/>
      <source>Password</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="238"/>
      <source>Repeat password</source>
      <translation>Zopakujte heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="265"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom. Dobré heslo by malo obsahovať mix písmen, čísel a diakritiky, malo by mať dĺžku aspoň osem znakov a malo by byť pravidelne menené.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="297"/>
      <source>Reuse user password as root password</source>
      <translation>Znovu použiť používateľské heslo ako heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="305"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Použiť rovnaké heslo pre účet správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Zvoľte heslo správcu pre zachovanie vášho účtu v bezpečí.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="328"/>
      <source>Root password</source>
      <translation>Heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="346"/>
      <source>Repeat root password</source>
      <translation>Zopakujte heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="372"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="402"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Prihlásiť automaticky bez pýtania hesla</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="410"/>
      <source>Validate passwords quality</source>
      <translation>Overiť kvalitu hesiel</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="420"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Keď je zaškrtnuté toto políčko, kontrola kvality hesla bude ukončená a nebudete môcť použiť slabé heslo.</translation>
    </message>
  </context>
  <context>
    <name>usersq-qt6</name>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="42"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Vyberte vaše používateľské meno a poverenia na prihlásenie a vykonávanie administrátorských úloh</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="55"/>
      <source>What is your name?</source>
      <translation>Aké je vaše meno?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="62"/>
      <source>Your full name</source>
      <translation>Vaše celé meno</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="79"/>
      <source>What name do you want to use to log in?</source>
      <translation>Aké meno chcete použiť na prihlásenie?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="86"/>
      <source>Login name</source>
      <translation>Prihlasovacie meno</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="115"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Ak bude tento počítač používať viac ako jedna osoba, môžete po inštalácii vytvoriť viacero účtov.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="128"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Sú povolené iba malé písmená, číslice, podtržníky a pomlčky.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="137"/>
      <source>root is not allowed as username.</source>
      <translation>root nie je možné použiť ako meno používateľa</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="146"/>
      <source>What is the name of this computer?</source>
      <translation>Aký je názov tohto počítača?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="152"/>
      <source>Computer name</source>
      <translation>Názov počítača</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="179"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Tento názov bude použitý, keď zviditeľníte počítač ostatným v sieti.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="192"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>Sú povolené iba písmená, číslice, podtržníky a pomlčky, v minimálnom počte dvoch znakov.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="201"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost nie možné použiť ako názov hostiteľa</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="210"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Zvoľte heslo pre zachovanie vášho účtu v bezpečí.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="220"/>
      <source>Password</source>
      <translation>Heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="237"/>
      <source>Repeat password</source>
      <translation>Zopakujte heslo</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="264"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom. Dobré heslo by malo obsahovať mix písmen, čísel a diakritiky, malo by mať dĺžku aspoň osem znakov a malo by byť pravidelne menené.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="296"/>
      <source>Reuse user password as root password</source>
      <translation>Znovu použiť používateľské heslo ako heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="304"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Použiť rovnaké heslo pre účet správcu.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="317"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Zvoľte heslo správcu pre zachovanie vášho účtu v bezpečí.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="327"/>
      <source>Root password</source>
      <translation>Heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="345"/>
      <source>Repeat root password</source>
      <translation>Zopakujte heslo správcu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="371"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Zadajte rovnaké heslo dvakrát, aby sa predišlo preklepom.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="401"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Prihlásiť automaticky bez pýtania hesla</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="409"/>
      <source>Validate passwords quality</source>
      <translation>Overiť kvalitu hesiel</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="419"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Keď je zaškrtnuté toto políčko, kontrola kvality hesla bude ukončená a nebudete môcť použiť slabé heslo.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Vitajte v inštalátore distribúcie %1 &lt;quote&gt;%2&lt;/quote&gt;&lt;/h3&gt;
            &lt;p&gt;Tento program vám položí niekoľko otázok a nainštaluje distribúciu %1 do vášho počítača.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="69"/>
      <source>Support</source>
      <translation>Podpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Známe problémy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Poznámky k vydaniu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="103"/>
      <source>Donate</source>
      <translation>Prispieť</translation>
    </message>
  </context>
  <context>
    <name>welcomeq-qt6</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Vitajte v inštalátore distribúcie %1 &lt;quote&gt;%2&lt;/quote&gt;&lt;/h3&gt;
            &lt;p&gt;Tento program vám položí niekoľko otázok a nainštaluje distribúciu %1 do vášho počítača.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="69"/>
      <source>Support</source>
      <translation>Podpora</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Známe problémy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Poznámky k vydaniu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="103"/>
      <source>Donate</source>
      <translation>Prispieť</translation>
    </message>
  </context>
</TS>

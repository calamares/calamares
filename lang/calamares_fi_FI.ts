<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="fi_FI" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="62"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>Järjestelmän &lt;strong&gt;käynnistysympäristö.&lt;/strong&gt; &lt;br&gt;&lt;br&gt;Vanhemmat x86-järjestelmät tukevat vain &lt;strong&gt;BIOS&lt;/strong&gt;-järjestelmää.&lt;br&gt;Nykyaikaiset järjestelmät käyttävät yleensä &lt;strong&gt;EFI&lt;/strong&gt;,mutta voivat myös näkyä BIOS tilassa, jos ne käynnistetään yhteensopivuustilassa.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="72"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Tämä järjestelmä käynnistettiin &lt;strong&gt;EFI&lt;/strong&gt; -käynnistysympäristössä.&lt;br&gt;&lt;br&gt;Jos haluat määrittää  EFI-ympäristön, tämän asennuksen on asennettava käynnistyksen latausohjelma, kuten &lt;strong&gt;GRUB&lt;/strong&gt; tai &lt;strong&gt;systemd-boot&lt;/strong&gt; ohjaus &lt;strong&gt;EFI -järjestelmän osioon&lt;/strong&gt;. Tämä on automaattinen oletus, ellet valitse manuaalista osiota, jolloin sinun on valittava asetukset itse.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="84"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Järjestelmä käynnistettiin &lt;strong&gt;BIOS&lt;/strong&gt; -käynnistysympäristössä.&lt;br&gt;&lt;br&gt;Jos haluat määrittää käynnistämisen BIOS-ympäristöstä, tämän asennusohjelman on asennettava käynnistyksen lataaja, kuten&lt;strong&gt;GRUB&lt;/strong&gt;, joko osion alkuun tai &lt;strong&gt;Master Boot Record&lt;/strong&gt; ,joka on osiotaulukon alussa (suositus). Tämä on automaattista, ellet valitset manuaalista osiota, jolloin sinun on valittava asetukset itse.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="58"/>
      <source>Master Boot Record of %1</source>
      <translation>%1:n MBR</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="91"/>
      <source>Boot Partition</source>
      <translation>Käynnistysosio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="98"/>
      <source>System Partition</source>
      <translation>Järjestelmäosio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="128"/>
      <source>Do not install a boot loader</source>
      <translation>Älä asenna käynnistyslatainta</translation>
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
      <translation>Tyhjä sivu</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>Globaali-tallennus</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>Työjono</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Moduulit</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Tyyppi:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>tyhjä</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Käyttöliittymä:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="97"/>
      <source>Tools</source>
      <translation>Työkalut</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="110"/>
      <source>Reload Stylesheet</source>
      <translation>Virkistä tyylisivu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="117"/>
      <source>Widget Tree</source>
      <translation>Widget puu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="217"/>
      <source>Debug information</source>
      <translation>Virheenkorjaustiedot</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Set up</source>
      <translation>Määritä</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="85"/>
      <source>Install</source>
      <translation>Asenna</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Työ epäonnistui (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Ohjelmoitua työn epäonnistumista pyydettiin erikseen.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="196"/>
      <source>Done</source>
      <translation>Valmis</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Esimerkki työ (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source>Run command '%1' in target system.</source>
      <translation>Suorita komento '%1' kohdejärjestelmässä.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="43"/>
      <source> Run command '%1'.</source>
      <translation> Suorita komento '%1'.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="50"/>
      <source>Running command %1 %2</source>
      <translation>Suoritetaan komentoa %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="192"/>
      <source>Running %1 operation.</source>
      <translation>Suoritetaan %1 toimenpidettä.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="221"/>
      <source>Bad working directory path</source>
      <translation>Epäkelpo työskentelyhakemiston polku</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="222"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Työkansio %1 pythonin työlle %2 ei ole luettavissa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="228"/>
      <source>Bad main script file</source>
      <translation>Huono pää-skripti tiedosto</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="229"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Pääskriptitiedosto %1 pythonin työlle %2 ei ole luettavissa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="297"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Boost.Python virhe työlle "%1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="67"/>
      <source>Loading ...</source>
      <translation>Ladataan ...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="88"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation>QML-vaihe &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="268"/>
      <source>Loading failed.</source>
      <translation>Lataus epäonnistui.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="94"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>Moduulin vaatimusten tarkistaminen &lt;i&gt;%1&lt;/i&gt; on valmis.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="115"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Odotetaan %n moduuli(t).</numerusform>
        <numerusform>Odotetaan %n moduuli(t).</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="116"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n sekunti(a))</numerusform>
        <numerusform>(%n sekunti(a))</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="121"/>
      <source>System-requirements checking is complete.</source>
      <translation>Järjestelmävaatimusten tarkistus on valmis.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Setup Failed</source>
      <translation>Asennus epäonnistui</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="150"/>
      <source>Installation Failed</source>
      <translation>Asennus Epäonnistui</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="151"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Haluatko liittää asennuslokin verkkoon?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="164"/>
      <source>Error</source>
      <translation>Virhe</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="171"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="518"/>
      <source>&amp;Yes</source>
      <translation>&amp;Kyllä</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="172"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>&amp;No</source>
      <translation>&amp;Ei</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="178"/>
      <source>&amp;Close</source>
      <translation>&amp;Sulje</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="189"/>
      <source>Install Log Paste URL</source>
      <translation>Asenna lokitiedon URL-osoite</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Lähettäminen epäonnistui. Web-liittämistä ei tehty.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="208"/>
      <source>Calamares Initialization Failed</source>
      <translation>Calamares-alustustaminen epäonnistui</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="209"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 ei voida asentaa. Calamares ei voinut ladata kaikkia määritettyjä moduuleja. Ongelma on siinä, miten jakelu käyttää Calamaresia.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="215"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Seuraavia moduuleja ei voitu ladata:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with setup?</source>
      <translation>Jatka asennusta?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>Continue with installation?</source>
      <translation>Jatka asennusta?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="329"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 asennusohjelma on aikeissa tehdä muutoksia levylle, jotta voit määrittää kohteen %2.&lt;br/&gt;&lt;strong&gt;Et voi kumota näitä muutoksia.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Asennus ohjelman %1 on tehtävä muutoksia levylle, jotta %2 voidaan asentaa.&lt;br/&gt;&lt;strong&gt;Et voi kumota näitä muutoksia.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Määritä nyt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>&amp;Install now</source>
      <translation>&amp;Asenna nyt</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>Go &amp;back</source>
      <translation>Mene &amp;takaisin</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Set up</source>
      <translation>&amp;Määritä</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Install</source>
      <translation>&amp;Asenna</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="394"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Asennus on valmis. Sulje asennusohjelma.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Asennus on valmis. Sulje asennusohjelma.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Peruuta asennus muuttamatta järjestelmää.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Peruuta asennus tekemättä muutoksia järjestelmään.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>&amp;Next</source>
      <translation>&amp;Seuraava</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="413"/>
      <source>&amp;Back</source>
      <translation>&amp;Takaisin</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Done</source>
      <translation>&amp;Valmis</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="438"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Peruuta</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel setup?</source>
      <translation>Peruuta asennus?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel installation?</source>
      <translation>Peruuta asennus?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="512"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Haluatko todella peruuttaa nykyisen asennuksen?
Asennusohjelma lopetetaan ja kaikki muutokset menetetään.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Oletko varma että haluat peruuttaa käynnissä olevan asennusprosessin? 
Asennusohjelma sulkeutuu ja kaikki muutoksesi katoavat.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="288"/>
      <source>Unknown exception type</source>
      <translation>Tuntematon poikkeustyyppi</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="306"/>
      <source>unparseable Python error</source>
      <translation>jäsentämätön Python virhe</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="350"/>
      <source>unparseable Python traceback</source>
      <translation>jäsentämätön Python jäljitys</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="357"/>
      <source>Unfetchable Python error.</source>
      <translation>Python virhettä ei voitu hakea.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="25"/>
      <source>Install log posted to:
%1</source>
      <translation>Asennuksen loki lähetetty:
%1</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="101"/>
      <source>Show debug information</source>
      <translation>Näytä virheenkorjaustiedot</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="155"/>
      <source>&amp;Back</source>
      <translation>&amp;Takaisin</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="167"/>
      <source>&amp;Next</source>
      <translation>&amp;Seuraava</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="180"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Peruuta</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="304"/>
      <source>%1 Setup Program</source>
      <translation>%1 Asennusohjelma</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="305"/>
      <source>%1 Installer</source>
      <translation>%1 Asennusohjelma</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="37"/>
      <source>Gathering system information...</source>
      <translation>Kerätään järjestelmän tietoja...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="120"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Valitse tallennus&amp;laite:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="121"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1092"/>
      <source>Current:</source>
      <translation>Nykyinen:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="122"/>
      <source>After:</source>
      <translation>Jälkeen:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="299"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Manuaalinen osiointi &lt;/strong&gt;&lt;br/&gt;Voit luoda tai muuttaa osioita itse.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="822"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Käytä %1 uudelleen kotiosiona kohteelle %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Valitse supistettava osio ja säädä alarivillä kokoa vetämällä&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="975"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 supistetaan %2Mib:iin ja uusi %3MiB-osio luodaan kohteelle %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1031"/>
      <source>Boot loader location:</source>
      <translation>Käynnistyksen lataajan sijainti:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1083"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Valitse asennettava osio&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1142"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>EFI-osiota ei löydy mistään tässä järjestelmässä. Siirry takaisin ja käytä manuaalista osiointia, kun haluat määrittää %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1150"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-järjestelmän osiota %1 käytetään käynnistettäessä %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1158"/>
      <source>EFI system partition:</source>
      <translation>EFI järjestelmäosio:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1291"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Tällä tallennuslaitteella ei näytä olevan käyttöjärjestelmää. Mitä haluat tehdä?&lt;br/&gt;Voit tarkistaa ja vahvistaa valintasi ennen kuin tallennuslaitteeseen tehdään muutoksia.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1296"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1333"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1355"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1380"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Tyhjennä levy&lt;/strong&gt;&lt;br/&gt;Tämä &lt;font color="red"&gt;poistaa&lt;/font&gt; kaikki tiedot valitussa tallennuslaitteessa.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1300"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1329"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1351"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1376"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Asenna nykyisen rinnalle&lt;/strong&gt;&lt;br/&gt;Asennus ohjelma supistaa osion tehdäkseen tilaa kohteelle %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1304"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1338"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1359"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1384"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Osion korvaaminen&lt;/strong&gt;&lt;br/&gt;korvaa osion %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1323"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Tässä tallennuslaitteessa on %1 dataa. Mitä haluat tehdä?&lt;br/&gt;Voit tarkistaa ja vahvistaa valintasi ennen kuin tallennuslaitteeseen tehdään muutoksia.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1346"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Tämä tallennuslaite sisältää jo käyttöjärjestelmän. Mitä haluaisit tehdä?&lt;br/&gt;Voit tarkistaa ja vahvistaa valintasi, ennen kuin tallennuslaitteeseen tehdään muutoksia.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1371"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Tämä tallennuslaite sisältää jo useita käyttöjärjestelmiä. Mitä haluaisit tehdä?&lt;br/&gt;Voit tarkistaa ja vahvistaa valintasi, ennen kuin tallennuslaitteeseen tehdään muutoksia.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1443"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>Tässä kiintolevyssä on jo käyttöjärjestelmä, mutta osiotaulukko &lt;strong&gt;%1&lt;/strong&gt; on erilainen kuin tarvittava &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1466"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <translation>Tähän kiintolevyyn on &lt;strong&gt;asennettu&lt;/strong&gt; yksi osioista.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1471"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <translation>Tämä kiintolevy on osa &lt;strong&gt;passiivista RAID&lt;/strong&gt; -laitetta.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1598"/>
      <source>No Swap</source>
      <translation>Ei välimuistia</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1606"/>
      <source>Reuse Swap</source>
      <translation>Kierrätä välimuistia</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1609"/>
      <source>Swap (no Hibernate)</source>
      <translation>Välimuisti (ei lepotilaa)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1612"/>
      <source>Swap (with Hibernate)</source>
      <translation>Välimuisti (lepotilan kanssa)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1615"/>
      <source>Swap to file</source>
      <translation>Välimuisti tiedostona</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="42"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Poista osiointitoimenpiteitä varten tehdyt liitokset kohteesta %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="49"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Tyhjennät kiinnitys osiointitoiminnoille %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="224"/>
      <source>Cleared all mounts for %1</source>
      <translation>Kaikki liitokset poistettu kohteesta %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="32"/>
      <source>Clear all temporary mounts.</source>
      <translation>Poista kaikki väliaikaiset liitokset.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="39"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Kaikki tilapäiset kiinnitykset tyhjennetään.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="51"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Väliaikaisten kiinnitysten luetteloa ei voi hakea.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="92"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Poistettu kaikki väliaikaiset liitokset.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="142"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="155"/>
      <source>Could not run command.</source>
      <translation>Komentoa ei voi suorittaa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="143"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>Komento toimii isäntäympäristössä ja sen täytyy tietää juuren polku, mutta root-liityntä kohtaa  ei ole määritetty.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="156"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Komennon on tiedettävä käyttäjän nimi, mutta käyttäjän tunnusta ei ole määritetty.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="326"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Aseta näppäimiston malli %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="333"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Aseta näppäimiston asetelmaksi %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="334"/>
      <source>Set timezone to %1/%2.</source>
      <translation>Aseta aikavyöhykkeeksi %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="372"/>
      <source>The system language will be set to %1.</source>
      <translation>Järjestelmän kielen asetuksena on %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="379"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>Numerot ja päivämäärät, paikallinen asetus on %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="38"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Verkko asennus. (Ei käytössä: virheellinen määritys)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="40"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Verkkoasennus. (Ei käytössä: Vastaanotettiin virheellisiä ryhmän tietoja)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="42"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation>Verkon asennus. (Ei käytössä: sisäinen virhe)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="44"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Verkkoasennus. (Ei käytössä: Pakettiluetteloita ei voi hakea, tarkista verkkoyhteys)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="50"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Tämä tietokone ei täytä vähimmäisvaatimuksia,  %1.&lt;br/&gt;Asennusta ei voi jatkaa. &lt;a href="#details"&gt;Yksityiskohdat...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="54"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Tämä tietokone ei täytä asennuksen vähimmäisvaatimuksia,  %1.&lt;br/&gt;Asennus ei voi jatkua. &lt;a href="#details"&gt;Yksityiskohdat...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="61"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.&lt;br/&gt;Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="65"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.
Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="75"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Tämä ohjelma kysyy joitakin kysymyksiä %2 ja asentaa tietokoneeseen.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="244"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa Calamares -asennusohjelmaan %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="245"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa %1 asennukseen&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="250"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa Calamares -asennusohjelmaan %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="251"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa %1 -asennusohjelmaan&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="212"/>
      <source>Your username is too long.</source>
      <translation>Käyttäjänimesi on liian pitkä.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="218"/>
      <source>'%1' is not allowed as username.</source>
      <translation>'%1' ei ole sallittu käyttäjänimenä.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="225"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Käyttäjätunnuksesi täytyy alkaa pienillä kirjaimilla tai alaviivoilla.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="229"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Vain pienet kirjaimet, numerot, alaviivat ja tavuviivat ovat sallittuja.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="274"/>
      <source>Your hostname is too short.</source>
      <translation>Isäntänimesi on liian lyhyt.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="278"/>
      <source>Your hostname is too long.</source>
      <translation>Isäntänimesi on liian pitkä.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="284"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>'%1' ei ole sallittu koneen nimenä.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="290"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Vain kirjaimet, numerot, alaviivat ja tavuviivat ovat sallittuja.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="527"/>
      <source>Your passwords do not match!</source>
      <translation>Salasanasi eivät täsmää!</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="119"/>
      <source>Contextual Processes Job</source>
      <translation>Prosessien yhteydessä tehtävät</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Luo levyosio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>K&amp;oko:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation> Mib</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Osion &amp;Tyyppi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>&amp;Primary</source>
      <translation>&amp;Ensisijainen</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>&amp;Laajennettu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>Tie&amp;dosto järjestelmä:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM LV nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Liitoskohta:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="192"/>
      <source>Flags:</source>
      <translation>Liput:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
      <source>En&amp;crypt</source>
      <translation>Sa&amp;laa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="161"/>
      <source>Logical</source>
      <translation>Looginen</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="166"/>
      <source>Primary</source>
      <translation>Ensisijainen</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="185"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="265"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Asennuskohde on jo käytössä. Valitse toinen.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="38"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Luo uusi %2Mib-osio %4 (%3) tiedostojärjestelmällä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="49"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Luo uusi &lt;strong&gt;%2Mib&lt;/strong&gt; osio &lt;strong&gt;%4&lt;/strong&gt; (%3) tiedostojärjestelmällä &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="61"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Luodaan uutta %1-osiota kohteessa %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="73"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Asennusohjelma epäonnistui osion luonnissa levylle '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Luo Osiotaulukko</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Uuden osiotaulukon luominen poistaa kaikki olemassa olevat tiedostot levyltä.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Minkälaisen osiotaulukon haluat luoda?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID Partition Table (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="39"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Luo uusi %1 osiotaulukko kohteessa %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Luo uusi &lt;strong&gt;%1&lt;/strong&gt; osiotaulukko kohteessa &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="57"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Luodaan uutta %1 osiotaulukkoa kohteelle %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="75"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Asennusohjelma epäonnistui osiotaulukon luonnissa kohteeseen %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="36"/>
      <source>Create user %1</source>
      <translation>Luo käyttäjä %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="43"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Luo käyttäjä &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="126"/>
      <source>Preserving home directory</source>
      <translation>Kotikansion säilyttäminen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="143"/>
      <source>Creating user %1</source>
      <translation>Luodaan käyttäjä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="151"/>
      <source>Configuring user %1</source>
      <translation>Määritetään käyttäjää %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
      <source>Setting file permissions</source>
      <translation>Tiedostojen oikeuksien määrittäminen</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <translation>Luo aseman ryhmä</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="31"/>
      <source>Create new volume group named %1.</source>
      <translation>Luo uusi aseman ryhmä nimellä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Luo uusi aseman ryhmä nimellä &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Creating new volume group named %1.</source>
      <translation>Luodaan uusi aseman ryhmä nimellä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="55"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Asennusohjelma ei voinut luoda aseman ryhmää nimellä '%1'.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="36"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Poista levyryhmän nimi %1 käytöstä.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="30"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Poista levyryhmän nimi käytöstä. &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Asennusohjelma ei pystynyt poistamaan levyryhmää nimellä %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="31"/>
      <source>Delete partition %1.</source>
      <translation>Poista levyosio %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="38"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Poista levyosio &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="45"/>
      <source>Deleting partition %1.</source>
      <translation>Poistetaan levyosiota %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Asennusohjelma epäonnistui osion %1 poistossa.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="97"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Tässälaitteessa on &lt;strong&gt;%1&lt;/strong&gt; osion taulukko.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Tämä &lt;strong&gt;loop&lt;/strong&gt; -laite.&lt;br&gt;&lt;br&gt;Se on pseudo-laite, jossa ei ole osio-taulukkoa ja joka tekee tiedostosta lohkotun aseman. Tällainen asennus sisältää yleensä vain yhden tiedostojärjestelmän.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="111"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Tämä asennusohjelma &lt;strong&gt;ei tunnista osion taulukkoa&lt;/strong&gt; valitussa tallennuslaitteessa.&lt;br&gt;&lt;br&gt;Laitteessa ei ole osio-taulukkoa, tai taulukko on vioittunut tai tuntematon.&lt;br&gt;Tämä asennusohjelma voi luoda uuden osiontaulukon sinulle, joko automaattisesti tai manuaalisesti.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Tämä on suositeltava osion taulun tyyppi nykyaikaisille järjestelmille, jotka käyttävät &lt;strong&gt;EFI&lt;/strong&gt; -käynnistysympäristöä.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="127"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Tämä osiotaulukon tyyppi on suositeltava vain vanhemmissa järjestelmissä, jotka käyttävät  &lt;strong&gt;BIOS&lt;/strong&gt; -käynnistysympäristöä. GPT:tä suositellaan useimmissa muissa tapauksissa.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Varoitus:&lt;/strong&gt;MBR-taulukko on vanhentunut MS-DOS-standardi.&lt;br&gt;Vain 4 &lt;em&gt;ensisijaisia&lt;/em&gt; Vain ensisijaisia osioita voidaan luoda, ja  4, niistä yksi voi olla &lt;em&gt;laajennettu&lt;/em&gt; osio, joka voi puolestaan sisältää monia  osioita &lt;em&gt;loogisia&lt;/em&gt; osioita.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="140"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Valitun tallennuslaitteen &lt;strong&gt;osion taulukon&lt;/strong&gt; tyyppi.&lt;br&gt;&lt;br&gt;Ainoa tapa muuttaa osion taulukon tyyppiä on poistaa ja luoda uudelleen osiot tyhjästä, mikä tuhoaa kaikki tallennuslaitteen tiedot. &lt;br&gt;Tämä asennusohjelma säilyttää nykyisen osion taulukon, ellet nimenomaisesti valitse muuta.&lt;br&gt;Jos olet epävarma, niin nykyaikaisissa järjestelmissä GPT on suositus.</translation>
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
      <translation>Kirjoita LUKS-kokoonpano Dracutille %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Ohita LUKS-määrityksen kirjoittaminen Dracutille: "/" -osio ei ole salattu</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <translation>Ei voi avata %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="37"/>
      <source>Dummy C++ Job</source>
      <translation>Dummy C++ -työ</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Muokkaa olemassa olevaa osiota</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Content:</source>
      <translation>Sisältö:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>&amp;Säilytä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Alusta</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Varoitus: Osion alustus tulee poistamaan kaikki olemassa olevat tiedostot.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Liitoskohta:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="123"/>
      <source>Si&amp;ze:</source>
      <translation>K&amp;oko:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="133"/>
      <source> MiB</source>
      <translation> Mib</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="140"/>
      <source>Fi&amp;le System:</source>
      <translation>Tie&amp;dosto järjestelmä:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="153"/>
      <source>Flags:</source>
      <translation>Liput:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="275"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Asennuskohde on jo käytössä. Valitse toinen.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Sa&amp;laa järjestelmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="46"/>
      <source>Passphrase</source>
      <translation>Salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="56"/>
      <source>Confirm passphrase</source>
      <translation>Vahvista salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="104"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="114"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Anna sama salasana molemmissa ruuduissa.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="138"/>
      <source>Set partition information</source>
      <translation>Aseta osion tiedot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="164"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Asenna %1 &lt;strong&gt;uusi&lt;/strong&gt; %2 järjestelmä osio.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="170"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Määritä &lt;strong&gt;uusi&lt;/strong&gt; %2 -osio liitepisteellä&lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="180"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Asenna %2 - %3 -järjestelmän osioon &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="187"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Määritä %3 osio &lt;strong&gt;%1&lt;/strong&gt; jossa on liitäntäpiste &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="200"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Asenna käynnistyslatain &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="209"/>
      <source>Setting up mount points.</source>
      <translation>Liitosten määrittäminen.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Käynnistä uudelleen</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="44"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;Valmista.&lt;/h1&gt;&lt;br/&gt;%1 on määritetty tietokoneellesi.&lt;br/&gt;Voit nyt alkaa käyttää uutta järjestelmääsi.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Kun tämä valintaruutu on valittu, järjestelmä käynnistyy heti, kun napsautat  &lt;span style="font-style:italic;"&gt;Valmis&lt;/span&gt; -painiketta tai suljet asennusohjelman.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Kaikki tehty.&lt;/h1&gt;&lt;br/&gt;%1 on asennettu tietokoneellesi.&lt;br/&gt;Voit joko uudelleenkäynnistää uuteen kokoonpanoosi, tai voit jatkaa %2 live-ympäristön käyttöä.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="59"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Kun tämä valintaruutu on valittuna, järjestelmä käynnistyy heti, kun napsautat &lt;span style="font-style:italic;"&gt;Valmis&lt;/span&gt; tai suljet asentimen.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="116"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Asennus epäonnistui&lt;/h1&gt;&lt;br/&gt;%1 ei ole määritetty tietokoneellesi.&lt;br/&gt; Virhesanoma oli: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="122"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Asennus epäonnistui &lt;/h1&gt;&lt;br/&gt;%1 ei ole asennettu tietokoneeseesi.&lt;br/&gt;Virhesanoma oli: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="67"/>
      <source>Finish</source>
      <translation>Valmis</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Setup Complete</source>
      <translation>Asennus valmis</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
      <source>Installation Complete</source>
      <translation>Asennus valmis</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="127"/>
      <source>The setup of %1 is complete.</source>
      <translation>Asennus %1 on valmis.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="128"/>
      <source>The installation of %1 is complete.</source>
      <translation>Asennus %1 on valmis.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="36"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Alustaa osiota %1 (tiedostojärjestelmä: %2, koko: %3 MiB) - %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="47"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Alustus &lt;strong&gt;%3MiB&lt;/strong&gt; osio &lt;strong&gt;%1&lt;/strong&gt; tiedostojärjestelmällä &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="58"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Alustaa osiota %1 tiedostojärjestelmällä %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="72"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Levyn '%2' osion %1 alustus epäonnistui.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>vähintään %1 GiB vapaata levytilaa</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="151"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Levytilaa ei ole riittävästi. Vähintään %1 GiB tarvitaan.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>has at least %1 GiB working memory</source>
      <translation>vähintään %1 GiB työmuistia</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Järjestelmässä ei ole tarpeeksi työmuistia. Vähintään %1 GiB vaaditaan.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="171"/>
      <source>is plugged in to a power source</source>
      <translation>on yhdistetty virtalähteeseen</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="172"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Järjestelmä ei ole kytketty virtalähteeseen.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>is connected to the Internet</source>
      <translation>on yhdistetty internetiin</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Järjestelmä ei ole yhteydessä internetiin.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="187"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>ajaa asennusohjelmaa järjestelmänvalvojana (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="190"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Asennus -ohjelma ei ole käynnissä järjestelmänvalvojan oikeuksin.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="191"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Asennus -ohjelma ei ole käynnissä järjestelmänvalvojan oikeuksin.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="199"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>näytöllä on riittävän suuri tarkkuus asentajalle</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="202"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Näyttö on liian pieni, jotta asennus -ohjelma voidaan näyttää.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="203"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Näyttö on liian pieni asentajan näyttämiseksi.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="42"/>
      <source>Collecting information about your machine.</source>
      <translation>Kerätään tietoja laitteesta.</translation>
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
      <translation>OEM-erän tunniste</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Hakemistoja ei voitu luoda &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Tiedostoa ei voitu avata &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Tiedostoon ei voitu kirjoittaa &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Initramfs luominen mkinitcpion avulla.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="28"/>
      <source>Creating initramfs.</source>
      <translation>Luodaan initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Konsole not installed</source>
      <translation>Pääte ei asennettuna</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="44"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Asenna KDE konsole ja yritä uudelleen!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="102"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Suoritetaan skripti: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="41"/>
      <source>Script</source>
      <translation>Skripti</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <translation>Näppäimistö</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>Näppäimistö</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System locale setting</source>
      <translation>Järjestelmän maa-asetus</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Järjestelmän kieli asetus vaikuttaa joidenkin komentorivin käyttöliittymän kieleen ja merkistön käyttöön.&lt;br/&gt;Nykyinen asetus on &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Peruuta</translation>
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
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Lisenssisopimus&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="136"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Hyväksyn yllä olevat ehdot ja edellytykset.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="138"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>Ole hyvä ja tarkista loppukäyttäjän lisenssisopimus (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="143"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>Tämä asennusohjelma asentaa patentoidun ohjelmiston, johon sovelletaan lisenssiehtoja.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="146"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>Jos et hyväksy ehtoja, asennusta ei voida jatkaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>Tämä asennus voi asentaa patentoidun ohjelmiston, johon sovelletaan lisenssiehtoja lisäominaisuuksien tarjoamiseksi ja käyttökokemuksen parantamiseksi.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>Jos et hyväksy ehtoja, omaa ohjelmistoa ei asenneta, vaan sen sijaan käytetään avoimen lähdekoodin vaihtoehtoja.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="43"/>
      <source>License</source>
      <translation>Lisenssi</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="88"/>
      <source>URL: %1</source>
      <translation>OSOITE: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="109"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;%1 ajuri&lt;/strong&gt;&lt;br/&gt;- %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 näytönohjaimet&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;- %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 selaimen laajennus&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;- %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 kodekki&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;- %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 paketti&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;- %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;- %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <translation>Tiedosto: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide license text</source>
      <translation>Piilota lisenssin teksti</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <translation>Näytä lisenssiteksti</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open license agreement in browser.</source>
      <translation>Avaa lisenssisopimus selaimessa.</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <translation>Alue:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <translation>Vyöhyke:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change...</source>
      <translation>&amp;Vaihda...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <translation>Sijainti</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="76"/>
      <source>Location</source>
      <translation>Sijainti</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="28"/>
      <source>Configuring LUKS key file.</source>
      <translation>LUKS-avaintiedoston määrittäminen.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="168"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="176"/>
      <source>No partitions are defined.</source>
      <translation>Osioita ei ole määritelty.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="211"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="218"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="226"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Salattu rootfs asennusvirhe</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="212"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Juuriosio %1 on LUKS, mutta salasanaa ei ole asetettu.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="219"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>LUKS-avaintiedostoa ei voitu luoda juuriosioon %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="227"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation>LUKS-avaintiedostoa ei voi määrittää osiossa %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="37"/>
      <source>Generate machine-id.</source>
      <translation>Luo koneen-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="53"/>
      <source>Configuration Error</source>
      <translation>Määritysvirhe</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="54"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Koneen tunnukselle ei ole asetettu root kiinnityskohtaa.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="243"/>
      <source>Timezone: %1</source>
      <translation>Aikavyöhyke: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="264"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <translation>Valitse sijainti kartalla, jotta asentaja voi ehdottaa paikalliset ja aikavyöhykeen asetukset.
             Voit hienosäätää alla olevia asetuksia. Etsi kartalta vetämällä ja suurenna/pienennä +/- -painikkeella tai käytä
hiiren vieritystä skaalaamiseen.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="47"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Package selection</source>
      <translation>Paketin valinta</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Office software</source>
      <translation>Office-ohjelmisto</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Office package</source>
      <translation>Office-paketti</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Browser software</source>
      <translation>Selainohjelmisto</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Browser package</source>
      <translation>Selainpaketti</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Web browser</source>
      <translation>Nettiselain</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Kernel</source>
      <translation>Kernel</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Services</source>
      <translation>Palvelut</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Login</source>
      <translation>Kirjaudu</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Desktop</source>
      <translation>Työpöytä</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Applications</source>
      <translation>Sovellukset</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Communication</source>
      <translation>Viestintä</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Development</source>
      <translation>Ohjelmistokehitys</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Office</source>
      <translation>Toimisto</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Multimedia</source>
      <translation>Multimedia</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Internet</source>
      <translation>Internetti</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Theming</source>
      <translation>Teema</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Gaming</source>
      <translation>Pelit</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Utilities</source>
      <translation>Apuohjelmat</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Huomautuksia</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Ba&amp;tch:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Syötä erän tunniste tähän. Tämä tallennetaan kohdejärjestelmään.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM asetukset&lt;/h1&gt;&lt;p&gt;Calamares käyttää OEM-asetuksia määritettäessä kohdejärjestelmää.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="122"/>
      <source>OEM Configuration</source>
      <translation>OEM-kokoonpano</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="128"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Aseta OEM valmistajan erän tunnus &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="37"/>
      <source>Select your preferred Region, or use the default one based on your current location.</source>
      <translation>Valitse alue tai käytä aluetta nykyisen sijaintisi perusteella.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="94"/>
      <location filename="../src/modules/localeq/Offline.qml" line="169"/>
      <location filename="../src/modules/localeq/Offline.qml" line="213"/>
      <source>Timezone: %1</source>
      <translation>Aikavyöhyke: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="111"/>
      <source>Select your preferred Zone within your Region.</source>
      <translation>Valitse haluamasi alue alueesi sisällä.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="182"/>
      <source>Zones</source>
      <translation>Vyöhykkeet</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="229"/>
      <source>You can fine-tune Language and Locale settings below.</source>
      <translation>Voit hienosäätää kieli- ja kieliasetuksia alla.</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="51"/>
      <source>Password is too short</source>
      <translation>Salasana on liian lyhyt</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="67"/>
      <source>Password is too long</source>
      <translation>Salasana on liian pitkä</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>Password is too weak</source>
      <translation>Salasana on liian heikko</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="196"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Muistin varausvirhe asetettaessa '%1'</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="199"/>
      <source>Memory allocation error</source>
      <translation>Muistin varausvirhe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="201"/>
      <source>The password is the same as the old one</source>
      <translation>Salasana on sama kuin vanha</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="203"/>
      <source>The password is a palindrome</source>
      <translation>Salasana on palindromi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="205"/>
      <source>The password differs with case changes only</source>
      <translation>Salasana eroaa vain vähäisin muutoksin</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="207"/>
      <source>The password is too similar to the old one</source>
      <translation>Salasana on liian samanlainen kuin vanha</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="209"/>
      <source>The password contains the user name in some form</source>
      <translation>Salasana sisältää jonkin käyttäjänimen</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="211"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Salasana sisältää sanoja käyttäjän todellisesta nimestä jossain muodossa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="214"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Salasana sisältää kiellettyjä sanoja</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="221"/>
      <source>The password contains too few digits</source>
      <translation>Salasana sisältää liian vähän numeroita</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="228"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Salasana sisältää liian vähän isoja kirjaimia</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="232"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Salasana sisältää vähemmän kuin %n pientä kirjainta</numerusform>
        <numerusform>Salasana sisältää vähemmän kuin %n pientä kirjainta</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="235"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Salasana sisältää liian vähän pieniä kirjaimia</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="242"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Salasana sisältää liian vähän erikoismerkkejä</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="249"/>
      <source>The password is too short</source>
      <translation>Salasana on liian lyhyt</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="258"/>
      <source>The password does not contain enough character classes</source>
      <translation>Salasana ei sisällä tarpeeksi merkkiluokkia</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="265"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Salasana sisältää liian monta samaa merkkiä peräkkäin</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Salasana sisältää liian monta saman luokan merkkiä peräkkäin</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="218"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Salasana sisältää vähemmän kuin %n numeroa</numerusform>
        <numerusform>Salasana sisältää vähemmän kuin %n numeroa</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="225"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Salasana sisältää vähemmän kuin %n isoa kirjainta</numerusform>
        <numerusform>Salasana sisältää vähemmän kuin %n isoa kirjainta</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="239"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>Salasana sisältää vähemmän kuin %n erikoismerkkiä</numerusform>
        <numerusform>Salasana sisältää vähemmän kuin %n erikoismerkkiä</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="246"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Salasana on lyhyempi kuin %1 merkkiä</numerusform>
        <numerusform>Salasana on lyhyempi kuin %n merkkiä</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="251"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Salasana on edellisen käänteinen versio</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="255"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Salasana sisältää vähemmän kuin %n tasoa</numerusform>
        <numerusform>Salasana sisältää vähemmän kuin %n tasoa</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="262"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Salasana sisältää enemmän kuin %n samaa merkkiä peräkkäin</numerusform>
        <numerusform>Salasana sisältää enemmän kuin %n samaa merkkiä peräkkäin</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="269"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Salasana sisältää enemmän kuin %n samaa merkkiä peräkkäin</numerusform>
        <numerusform>Salasana sisältää enemmän kuin %n samaa merkkiä peräkkäin</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>Salasana sisältää monotonisen jonon, joka on pidempi kuin %n merkkiä</numerusform>
        <numerusform>Salasana sisältää monotonisen jonon, joka on pidempi kuin %n merkkiä</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="286"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Salasanassa on liian pitkä monotoninen merkkijono</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>No password supplied</source>
      <translation>Salasanaa ei annettu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="291"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Satunnaislukuja ei voi saada RNG-laitteesta</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Salasanojen luonti epäonnistui - pakollinen vähimmäistaso liian alhainen asetuksia varten</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Salasana epäonnistui sanaston tarkistuksessa -%1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="301"/>
      <source>The password fails the dictionary check</source>
      <translation>Salasana epäonnistui sanaston tarkistuksessa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="305"/>
      <source>Unknown setting - %1</source>
      <translation>Tuntematon asetus - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="307"/>
      <source>Unknown setting</source>
      <translation>Tuntematon asetus</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="311"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Asetuksen virheellinen kokonaisluku - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="313"/>
      <source>Bad integer value</source>
      <translation>Virheellinen kokonaisluku</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="317"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Asetus %1 ei ole kokonaisluku</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="319"/>
      <source>Setting is not of integer type</source>
      <translation>Asetus ei ole kokonaisluku</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="323"/>
      <source>Setting %1 is not of string type</source>
      <translation>Asetus %1 ei ole merkkijono</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="325"/>
      <source>Setting is not of string type</source>
      <translation>Asetus ei ole merkkijono</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="327"/>
      <source>Opening the configuration file failed</source>
      <translation>Määritystiedoston avaaminen epäonnistui</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="329"/>
      <source>The configuration file is malformed</source>
      <translation>Määritystiedosto on väärin muotoiltu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="331"/>
      <source>Fatal failure</source>
      <translation>Vakava virhe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="333"/>
      <source>Unknown error</source>
      <translation>Tuntematon virhe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="775"/>
      <source>Password is empty</source>
      <translation>Salasana on tyhjä</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="24"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="44"/>
      <source>Product Name</source>
      <translation>Tuotteen nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="57"/>
      <source>TextLabel</source>
      <translation>Nimilappu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="73"/>
      <source>Long Product Description</source>
      <translation>Pitkä tuotekuvaus</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Paketin valinta</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Ole hyvä ja valitse tuote luettelosta. Valittu tuote asennetaan.</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="61"/>
      <source>Packages</source>
      <translation>Paketit</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Name</source>
      <translation>Nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="168"/>
      <source>Description</source>
      <translation>Kuvaus</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard Model:</source>
      <translation>Näppäimistön malli:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="135"/>
      <source>Type here to test your keyboard</source>
      <translation>Kirjoita tähän testaksesi näppäimistöäsi.</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Mikä on nimesi?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Koko nimesi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Mitä nimeä haluat käyttää sisäänkirjautumisessa?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>Kirjaudu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Mikä on tämän tietokoneen nimi?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Tätä nimeä tullaan käyttämään mikäli asetat tietokoneen näkyviin muille verkossa.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Tietokoneen nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Valitse salasana pitääksesi tilisi turvallisena.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Syötä salasana kahdesti välttääksesi kirjoitusvirheitä. Hyvän salasanan tulee sisältää sekoitetusti kirjaimia, numeroita ja erikoismerkkejä. Salasanan täytyy olla vähintään kahdeksan merkin mittainen ja tulee vaihtaa säännöllisin väliajoin.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Toista salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Kun tämä valintaruutu on valittu, salasanan vahvuus tarkistetaan, etkä voi käyttää heikkoa salasanaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Vaaditaan vahvat salasanat.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Kirjaudu automaattisesti ilman salasanaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Käytä pääkäyttäjän tilillä samaa salasanaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Valitse salasana pääkäyttäjän tilille.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Syötä salasana kahdesti välttääksesi kirjoitusvirheitä.&lt;/small&gt;</translation>
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
      <translation>EFI-järjestelmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition for %1</source>
      <translation>Uusi osio %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="215"/>
      <source>New partition</source>
      <translation>Uusi osiointi</translation>
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
      <translation>Vapaa tila</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="163"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="203"/>
      <source>New partition</source>
      <translation>Uusi osiointi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="296"/>
      <source>Name</source>
      <translation>Nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="298"/>
      <source>File System</source>
      <translation>Tiedostojärjestelmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="300"/>
      <source>Mount Point</source>
      <translation>Liitoskohta</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="302"/>
      <source>Size</source>
      <translation>Koko</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Tallennus&amp;laite:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>&amp;Peru kaikki muutokset</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Uusi osiointi&amp;taulukko</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Luo&amp;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Muokkaa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>&amp;Poista</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Uusi aseman ryhmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Muuta kokoa aseman-ryhmässä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Poista asemaryhmä käytöstä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Poista asemaryhmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>A&amp;senna käynnistyslatain:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="219"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Oletko varma, että haluat luoda uuden osion %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="254"/>
      <source>Can not create new partition</source>
      <translation>Ei voi luoda uutta osiota</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="255"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>%1 osio-taulukossa on jo %2 ensisijaista osiota, eikä sitä voi lisätä. Poista yksi ensisijainen osio ja lisää laajennettu osio.</translation>
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
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="125"/>
      <source>Partitions</source>
      <translation>Osiot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="163"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Asenna toisen käyttöjärjestelmän %1 &lt;strong&gt;rinnalle&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Tyhjennä&lt;/strong&gt; levy ja asenna %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="170"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Vaihda&lt;/strong&gt; osio jolla on %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="174"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;Manuaalinen&lt;/strong&gt; osointi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="187"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Asenna toisen käyttöjärjestelmän %1 &lt;strong&gt;rinnalle&lt;/strong&gt; levylle &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="194"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Tyhjennä&lt;/strong&gt; levy &lt;strong&gt;%2&lt;/strong&gt; (%3) ja asenna %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="200"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Korvaa&lt;/strong&gt; levyn osio &lt;strong&gt;%2&lt;/strong&gt; (%3) jolla on %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="207"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;Manuaalinen&lt;/strong&gt; osiointi levyllä &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="216"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Levy &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="242"/>
      <source>Current:</source>
      <translation>Nykyinen:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="260"/>
      <source>After:</source>
      <translation>Jälkeen:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="427"/>
      <source>No EFI system partition configured</source>
      <translation>EFI-järjestelmäosiota ei ole määritetty</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="428"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>EFI-järjestelmän osio on välttämätön käynnistyksessä %1.&lt;br/&gt;&lt;br/&gt;Jos haluat tehdä EFI-järjestelmän osion, mene takaisin ja luo FAT32-tiedostojärjestelmä, jossa&lt;strong&gt;%3&lt;/strong&gt; lippu on käytössä ja liityntäkohta. &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Voit jatkaa ilman EFI-järjestelmäosiota, mutta järjestelmä ei ehkä käynnisty.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="442"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation>EFI-järjestelmän osio on välttämätön käynnistyksessä %1.&lt;br/&gt;&lt;br/&gt;Osio on määritetty liityntäkohdan kanssa, &lt;strong&gt;%2&lt;/strong&gt; mutta sen &lt;strong&gt;%3&lt;/strong&gt; lippua ei ole asetettu.&lt;br/&gt;Jos haluat asettaa lipun, palaa takaisin ja muokkaa osiota.&lt;br/&gt;&lt;br/&gt;Voit jatkaa lippua asettamatta, mutta järjestelmä ei ehkä käynnisty.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="441"/>
      <source>EFI system partition flag not set</source>
      <translation>EFI-järjestelmäosion lippua ei ole asetettu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="468"/>
      <source>Option to use GPT on BIOS</source>
      <translation>BIOS:ssa mahdollisuus käyttää GPT:tä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="469"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>GPT-osiotaulukko on paras vaihtoehto kaikille järjestelmille. Tämä asennusohjelma tukee asennusta myös BIOS:n järjestelmään.&lt;br/&gt;&lt;br/&gt;Jos haluat määrittää GPT-osiotaulukon BIOS:ssa (jos sitä ei ole jo tehty) palaa takaisin ja aseta osiotaulukkoksi GPT. Luo seuraavaksi 8 Mb alustamaton osio &lt;strong&gt;bios_grub&lt;/strong&gt; lipulla käyttöön.&lt;br/&gt;&lt;br/&gt;Alustamaton 8 Mb osio on tarpeen %1:n käynnistämiseksi BIOS-järjestelmässä GPT:llä.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="497"/>
      <source>Boot partition not encrypted</source>
      <translation>Käynnistysosiota ei ole salattu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="498"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Erillinen käynnistysosio perustettiin yhdessä salatun juuriosion kanssa, mutta käynnistysosio ei ole salattu.&lt;br/&gt;&lt;br/&gt;Tällaisissa asetuksissa on tietoturvaongelmia, koska tärkeät järjestelmätiedostot pidetään salaamattomassa osiossa.&lt;br/&gt;Voit jatkaa, jos haluat, mutta tiedostojärjestelmän lukituksen avaaminen tapahtuu myöhemmin järjestelmän käynnistyksen aikana.&lt;br/&gt;Käynnistysosion salaamiseksi siirry takaisin ja luo se uudelleen valitsemalla &lt;strong&gt;Salaa&lt;/strong&gt; osion luominen -ikkunassa. </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="627"/>
      <source>has at least one disk device available.</source>
      <translation>on vähintään yksi levy käytettävissä.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="628"/>
      <source>There are no partitions to install on.</source>
      <translation>Asennettavia osioita ei ole.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Plasman ulkoasu</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>KDE-plasman ulkoasupakettia ei voi valita</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="79"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Valitse ulkoasu KDE-plasma -työpöydälle. Voit myös ohittaa tämän vaiheen ja määrittää ulkoasun, kun järjestelmä on asetettu. Klikkaamalla ulkoasun valintaa saat suoran esikatselun tästä ulkoasusta.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="84"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Valitse KDE-plasma -työpöydän ulkoasu. Voit myös ohittaa tämän vaiheen ja määrittää ulkoasun, kun järjestelmä on asennettu. Klikkaamalla ulkoasun valintaa saat suoran esikatselun tästä ulkoasusta.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <translation>Ulkoasu</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="79"/>
      <source>Saving files for later ...</source>
      <translation>Tiedostojen tallentaminen myöhemmin ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="118"/>
      <source>No files configured to save for later.</source>
      <translation>Ei tiedostoja, joita olisi määritetty tallentamaan myöhemmin.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="172"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Kaikkia määritettyjä tiedostoja ei voitu säilyttää.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="412"/>
      <source>
There was no output from the command.</source>
      <translation>
Komentoa ei voitu ajaa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="413"/>
      <source>
Output:
</source>
      <translation>
Ulostulo:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="417"/>
      <source>External command crashed.</source>
      <translation>Ulkoinen komento kaatui.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Komento &lt;i&gt;%1&lt;/i&gt; kaatui.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>External command failed to start.</source>
      <translation>Ulkoisen komennon käynnistäminen epäonnistui.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Komennon &lt;i&gt;%1&lt;/i&gt; käynnistäminen epäonnistui.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>Internal error when starting command.</source>
      <translation>Sisäinen virhe käynnistettäessä komentoa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>Bad parameters for process job call.</source>
      <translation>Huonot parametrit prosessin kutsuun.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="433"/>
      <source>External command failed to finish.</source>
      <translation>Ulkoinen komento ei onnistunut.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Komento &lt;i&gt;%1&lt;/i&gt; epäonnistui %2 sekunnissa.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="441"/>
      <source>External command finished with errors.</source>
      <translation>Ulkoinen komento päättyi virheisiin.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="442"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Komento &lt;i&gt;%1&lt;/i&gt; päättyi koodiin %2.</translation>
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
      <translation>tuntematon</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="30"/>
      <source>extended</source>
      <translation>laajennettu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="32"/>
      <source>unformatted</source>
      <translation>formatoimaton</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="34"/>
      <source>swap</source>
      <translation>swap</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="130"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="167"/>
      <source>Default</source>
      <translation>Oletus</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="72"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="76"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>File not found</source>
      <translation>Tiedostoa ei löytynyt</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="65"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Polku &lt;pre&gt;%1&lt;/pre&gt; täytyy olla ehdoton polku.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="83"/>
      <source>Directory not found</source>
      <translation>Kansiota ei löytynyt</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="84"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="94"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Uutta satunnaista tiedostoa ei voitu luoda &lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="70"/>
      <source>No product</source>
      <translation>Ei tuotetta</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="78"/>
      <source>No description provided.</source>
      <translation>Kuvausta ei ole.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="40"/>
      <source>(no mount point)</source>
      <translation>(ei liitoskohtaa)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="41"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Osioimaton tila tai tuntematon osion taulu</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.&lt;br/&gt;
Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="34"/>
      <source>Remove live user from target system</source>
      <translation>Poista Live-käyttäjä kohdejärjestelmästä</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="24"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="36"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Poista asemaryhmä nimeltä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="30"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Poista asemaryhmä nimeltä &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Asentaja ei onnistunut poistamaan nimettyä asemaryhmää '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="127"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Valitse minne %1 asennetaan.&lt;br/&gt;&lt;font color="red"&gt;Varoitus: &lt;/font&gt;tämä poistaa kaikki tiedostot valitulta osiolta.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="149"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Valitsemaasi kohta ei näytä olevan kelvollinen osio.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="157"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 ei voi asentaa tyhjään tilaan. Valitse olemassa oleva osio.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="167"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 ei voida asentaa jatketun osion. Valitse olemassa oleva ensisijainen tai looginen osio.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="177"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 ei voida asentaa tähän osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="183"/>
      <source>Data partition (%1)</source>
      <translation>Data osio (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="203"/>
      <source>Unknown system partition (%1)</source>
      <translation>Tuntematon järjestelmä osio (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="207"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 järjestelmäosio (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="218"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Osio %1 on liian pieni %2. Valitse osio, jonka kapasiteetti on vähintään %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="240"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;EFI-järjestelmäosiota ei löydy mistään tässä järjestelmässä. Palaa takaisin ja käytä manuaalista osiointia määrittämällä %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="251"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="267"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="292"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 asennetaan %2.&lt;br/&gt;&lt;font color="red"&gt;Varoitus: &lt;/font&gt;kaikki osion  %2 tiedot katoavat.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="259"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>EFI-järjestelmän osiota %1 käytetään käynnistettäessä %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="275"/>
      <source>EFI system partition:</source>
      <translation>EFI järjestelmäosio</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="38"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tämä tietokone ei täytä vähittäisvaatimuksia asennukseen %1.&lt;br/&gt;
        Asennusta ei voida jatkaa.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.&lt;br/&gt;
Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="46"/>
      <source>Resize Filesystem Job</source>
      <translation>Muuta tiedostojärjestelmän kokoa</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>Invalid configuration</source>
      <translation>Virheellinen konfiguraatio</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>Tiedostojärjestelmän koon muutto ei kelpaa eikä sitä suoriteta.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="175"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore ei saatavilla</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="176"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>Calamares ei voi käynnistää KPMCore-tiedostoa tiedostojärjestelmän koon muuttamiseksi.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="184"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="193"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="204"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="231"/>
      <source>Resize Failed</source>
      <translation>Kokomuutos epäonnistui</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>Tiedostojärjestelmää %1 ei löydy tästä järjestelmästä, eikä sen kokoa voi muuttaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>Laitetta %1 ei löydy tästä järjestelmästä, eikä sen kokoa voi muuttaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>Tiedostojärjestelmän %1 kokoa ei voi muuttaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The device %1 cannot be resized.</source>
      <translation>Laitteen %1 kokoa ei voi muuttaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>Tiedostojärjestelmän %1 kokoa on muutettava, mutta ei onnistu.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="215"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>Laitteen %1 kokoa on muutettava, mutta ei onnistu.</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="40"/>
      <source>Resize partition %1.</source>
      <translation>Muuta osion kokoa %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="47"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>Muuta &lt;strong&gt;%2MiB&lt;/strong&gt; osiota &lt;strong&gt;%1&lt;/strong&gt; - &lt;strong&gt;%3MiB&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="58"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Muuntaa %2MiB osion %1 to %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="77"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Asennusohjelma epäonnistui osion %1 koon muuttamisessa levyllä '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <translation>Muuta kokoa aseman-ryhmässä</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="27"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>Muuta %1 levyn kokoa  %2:sta %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Muuta levyä nimeltä &lt;strong&gt;%1&lt;/strong&gt; lähde &lt;strong&gt;%2&lt;/strong&gt; - &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="60"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Asentaja ei onnistunut muuttamaan nimettyä levyä '%1'.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="133"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>Saadaksesi parhaan lopputuloksen, tarkista että tämä tietokone:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="134"/>
      <source>System requirements</source>
      <translation>Järjestelmävaatimukset</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="256"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Tämä tietokone ei täytä vähimmäisvaatimuksia,  %1.&lt;br/&gt;Asennusta ei voi jatkaa. &lt;a href="#details"&gt;Yksityiskohdat...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="260"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Tämä tietokone ei täytä asennuksen vähimmäisvaatimuksia,  %1.&lt;br/&gt;Asennus ei voi jatkua. &lt;a href="#details"&gt;Yksityiskohdat...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="267"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.&lt;br/&gt;Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="271"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Tämä tietokone ei täytä joitakin suositeltuja vaatimuksia %1.
Asennus voi jatkua, mutta jotkin toiminnot saattavat olla pois käytöstä.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="280"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Tämä ohjelma kysyy joitakin kysymyksiä %2 ja asentaa tietokoneeseen.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Scanning storage devices...</source>
      <translation>Skannataan tallennuslaitteita...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="64"/>
      <source>Partitioning</source>
      <translation>Osiointi</translation>
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
      <translation>Aseta koneellenimi &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
      <source>Setting hostname %1.</source>
      <translation>Asetetaan koneellenimi %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="122"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="129"/>
      <source>Internal Error</source>
      <translation>Sisäinen Virhe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="137"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <source>Cannot write hostname to target system</source>
      <translation>Ei voida kirjoittaa isäntänimeä kohdejärjestelmään.</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="55"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Aseta näppäimistön malliksi %1, asetelmaksi %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Virtuaalikonsolin näppäimistöasetuksen tallentaminen epäonnistui.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="397"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="414"/>
      <source>Failed to write to %1</source>
      <translation>Kirjoittaminen epäonnistui kohteeseen %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="396"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>X11 näppäimistöasetuksen tallentaminen epäonnistui.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="413"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Näppäimistöasetusten kirjoittaminen epäonnistui olemassa olevaan /etc/default hakemistoon.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="43"/>
      <source>Set flags on partition %1.</source>
      <translation>Aseta liput osioon %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>Aseta liput %1MiB %2 osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="53"/>
      <source>Set flags on new partition.</source>
      <translation>Aseta liput uuteen osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Poista liput osiosta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Poista liput %1MiB &lt;strong&gt;%2&lt;/strong&gt; osiosta.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition.</source>
      <translation>Tyhjennä liput uuteen osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Merkitse osio &lt;strong&gt;%1&lt;/strong&gt; - &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Lippu %1MiB &lt;strong&gt;%2&lt;/strong&gt; osiosta &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="96"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Merkitse uusi osio &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="108"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Lipun poisto osiosta &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="114"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Tyhjennä liput %1MiB &lt;strong&gt;%2&lt;/strong&gt; osiossa.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="119"/>
      <source>Clearing flags on new partition.</source>
      <translation>Uusien osioiden lippujen poistaminen.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="124"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Lippujen &lt;strong&gt;%2&lt;/strong&gt; asettaminen osioon &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>Asetetaan liput &lt;strong&gt;%3&lt;/strong&gt;  %1MiB &lt;strong&gt;%2&lt;/strong&gt; osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Asetetaan liput &lt;strong&gt;%1&lt;/strong&gt; uuteen osioon.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="156"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Asennusohjelma ei voinut asettaa lippuja osioon %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="40"/>
      <source>Set password for user %1</source>
      <translation>Aseta salasana käyttäjälle %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="47"/>
      <source>Setting password for user %1.</source>
      <translation>Salasanan asettaminen käyttäjälle %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>Bad destination system path.</source>
      <translation>Huono kohteen järjestelmäpolku</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="82"/>
      <source>rootMountPoint is %1</source>
      <translation>rootMountPoint on %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="88"/>
      <source>Cannot disable root account.</source>
      <translation>Root-tiliä ei voi poistaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd päättyi virhekoodiin %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot set password for user %1.</source>
      <translation>Salasanaa ei voi asettaa käyttäjälle %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod päättyi virhekoodilla %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="34"/>
      <source>Set timezone to %1/%2</source>
      <translation>Aseta aikavyöhykkeeksi %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="62"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Ei pääsyä valittuun aikavyöhykkeen polkuun.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="63"/>
      <source>Bad path: %1</source>
      <translation>Huono polku: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot set timezone.</source>
      <translation>Aikavyöhykettä ei voi asettaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Linkin luominen kohteeseen %1 epäonnistui; linkin nimi: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="77"/>
      <source>Cannot set timezone,</source>
      <translation>Aikavyöhykettä ei voi määrittää,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="78"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Ei voi avata /etc/timezone</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="166"/>
      <source>Preparing groups.</source>
      <translation>Valmistellaan ryhmiä.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="178"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="183"/>
      <source>Could not create groups in target system</source>
      <translation>Ryhmiä ei voitu luoda kohdejärjestelmään</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="184"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>Kohderyhmästä puuttuu näitä ryhmiä: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="33"/>
      <source>Configure &lt;pre&gt;sudo&lt;/pre&gt; users.</source>
      <translation>Määritä &lt;pre&gt;sudo&lt;/pre&gt; käyttäjät.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="55"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Ei voida tehdä käyttöoikeuden muutosta sudoers -tiedostolle.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="60"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Ei voida luoda sudoers -tiedostoa kirjoitettavaksi.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="41"/>
      <source>Shell Processes Job</source>
      <translation>Shell-prosessien työ</translation>
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
      <translation>Tämä on yleiskuva siitä, mitä tapahtuu, kun asennusohjelma käynnistetään.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="50"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Tämä on yleiskuva siitä, mitä tapahtuu asennuksen aloittamisen jälkeen.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="36"/>
      <source>Summary</source>
      <translation>Yhteenveto</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="37"/>
      <source>Installation feedback</source>
      <translation>Asennuksen palaute</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="43"/>
      <source>Sending installation feedback.</source>
      <translation>Lähetetään asennuksen palautetta.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="60"/>
      <source>Internal error in install-tracking.</source>
      <translation>Sisäinen virhe asennuksen seurannassa.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="61"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP -pyyntö aikakatkaistiin.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="122"/>
      <source>KDE user feedback</source>
      <translation>KDE käyttäjän palaute</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="128"/>
      <source>Configuring KDE user feedback.</source>
      <translation>Määritä KDE käyttäjän palaute.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="150"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="156"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>Virhe KDE:n käyttäjän palautteen määrityksissä.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="151"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>KDE käyttäjän palautetta ei voitu määrittää oikein, komentosarjassa virhe %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="157"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>KDE käyttäjän palautetta ei voitu määrittää oikein, Calamares virhe %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Machine feedback</source>
      <translation>Koneen palaute</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="77"/>
      <source>Configuring machine feedback.</source>
      <translation>Konekohtaisen palautteen määrittäminen.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Virhe koneen palautteen määrityksessä.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="101"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Konekohtaista palautetta ei voitu määrittää oikein, komentosarjan virhe %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="107"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Koneen palautetta ei voitu määrittää oikein, Calamares-virhe %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Paikkamerkki</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Napsauta tätä &lt;span style=" font-weight:600;"&gt;jos et halua lähettää mitään&lt;/span&gt; tietoja asennuksesta.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Klikkaa tästä saadaksesi lisätietoja käyttäjäpalautteesta&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="86"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>Seuranta auttaa %1 näkemään, kuinka usein se asennetaan, mihin laitteistoon se on asennettu ja mihin sovelluksiin sitä käytetään. Jos haluat nähdä, mitä lähetetään, napsauta kunkin alueen vieressä olevaa ohjekuvaketta.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="91"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Valitsemalla tämän lähetät tietoja asennuksesta ja laitteistosta. Nämä tiedot lähetetään vain &lt;/b&gt;kerran&lt;/b&gt; asennuksen päätyttyä.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="94"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Valitsemalla tämän lähetät määräajoin tietoja &lt;b&gt;koneesi&lt;/b&gt; asennuksesta, laitteistosta ja sovelluksista, %1:lle.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="98"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Valitsemalla tämän lähetät säännöllisesti tietoja &lt;b&gt;käyttäjän&lt;/b&gt; asennuksesta, laitteistosta, sovelluksista ja sovellusten käyttötavoista %1:lle.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <translation>Palautetta</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="156"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jos useampi kuin yksi henkilö käyttää tätä tietokonetta, voit luoda useita tilejä asennuksen jälkeen.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="162"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jos useampi kuin yksi henkilö käyttää tätä tietokonetta, voit luoda useita tilejä asennuksen jälkeen.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="39"/>
      <source>Users</source>
      <translation>Käyttäjät</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Käyttäjät</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Avain</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Arvo</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Luo aseman ryhmä</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Fyysisten levyjen luoettelo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Aseman ryhmän nimi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Aseman ryhmän tyyppi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Fyysinen koko:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation> Mib</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Yhteensä koko:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Käytetty tila:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Sektorit yhteensä:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Määrä LVs:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="18"/>
      <source>Form</source>
      <translation>Lomake</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Valitse sovelluksen ja järjestelmän kieli</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>&amp;About</source>
      <translation>&amp;Tietoa</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="150"/>
      <source>Open donations website</source>
      <translation>Avaa lahjoitussivusto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>&amp;Donate</source>
      <translation>&amp;Lahjoita</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="163"/>
      <source>Open help and support website</source>
      <translation>Avaa ohje- ja tukisivusto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>&amp;Support</source>
      <translation>&amp;Tuki</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Avaa ongelmia käsittelevä verkkosivusto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Tunnetut ongelmat</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="189"/>
      <source>Open release notes website</source>
      <translation>Avaa julkaisutiedot verkkosivusto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="192"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Julkaisutiedot</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="216"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa Calamares -asennusohjelmaan %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="217"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa %1 asennukseen.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="222"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa Calamares -asennusohjelmaan %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="223"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Tervetuloa %1 -asennusohjelmaan.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="228"/>
      <source>%1 support</source>
      <translation>%1 tuki</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 setup</source>
      <translation>Tietoja %1 asetuksista</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>About %1 installer</source>
      <translation>Tietoa %1 asennusohjelmasta</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="238"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;- %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Kiitokset &lt;a href="https://calamares.io/team/"&gt;Calamares-tiimille&lt;/a&gt; ja &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares kääntäjille&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamaresin&lt;/a&gt; kehitystä sponsoroi &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="41"/>
      <source>Welcome</source>
      <translation>Tervetuloa</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="48"/>
      <source>Welcome</source>
      <translation>Tervetuloa</translation>
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
                        for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;
                        Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;
                        Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;
                        Kiitokset &lt;a href='https://calamares.io/team/'&gt;the Calamares tiimille&lt;/a&gt; 
                        ja &lt;a href='https://www.transifex.com/calamares/calamares/'&gt;Calamares 
                        kääntäjäille&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;
                        &lt;a href='https://calamares.io/'&gt;Calamares&lt;/a&gt; 
                        ohjelmistokehitystä sponsoroi &lt;br/&gt;
                        &lt;a href='http://www.blue-systems.com/'&gt;Blue Systems&lt;/a&gt; -
                        Liberating Software.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="96"/>
      <source>Back</source>
      <translation>Takaisin</translation>
    </message>
  </context>
  <context>
    <name>i18n</name>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="46"/>
      <source>&lt;h1&gt;Languages&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Kielet&lt;/h1&gt; &lt;/br&gt;
                    Järjestelmän sijaintiasetukset vaikuttaa joidenkin komentorivin käyttöliittymän elementtien kieliin ja merkistöihin. Nykyinen asetus on &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="106"/>
      <source>&lt;h1&gt;Locales&lt;/h1&gt; &lt;/br&gt;
                    The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;h1&gt;Sijainti&lt;/h1&gt; &lt;/br&gt;
                    Järjestelmän kieliasetus vaikuttaa numeroihin ja päivämääriin. Nykyinen asetus on &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/i18n.qml" line="158"/>
      <source>Back</source>
      <translation>Takaisin</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="45"/>
      <source>Keyboard Model</source>
      <translation>Näppäimistön malli</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="377"/>
      <source>Layouts</source>
      <translation>Asettelut</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="148"/>
      <source>Keyboard Layout</source>
      <translation>Näppäimistöasettelu</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="60"/>
      <source>Click your preferred keyboard model to select layout and variant, or use the default one based on the detected hardware.</source>
      <translation>Valitse haluamasi näppäimistömalli tai käytä oletusmallia havaitun laitteiston perusteella.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="253"/>
      <source>Models</source>
      <translation>Mallit</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="260"/>
      <source>Variants</source>
      <translation>Vaihtoehdot</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="276"/>
      <source>Keyboard Variant</source>
      <translation>Näppäimistön vaihtoehdot</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="386"/>
      <source>Test your keyboard</source>
      <translation>Näppäimistön testaaminen</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="81"/>
      <source>Change</source>
      <translation>Vaihda</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Nämä ovat esimerkkejä julkaisutiedoista.&lt;/p&gt;</translation>
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
            &lt;p&gt;Tämä esimerkki QML-tiedostosta, jossa näkyvät RichText-asetukset, joissa on liukuva sisältö.&lt;/p&gt;

            &lt;p&gt;QML Richtext voi käyttää HTML-tunnisteita, liukuva sisältö on hyödyllinen kosketusnäytöissä.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Tämä on lihavoitu teksti&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;Tämä on kursivoitu teksti&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;Tämä on alleviivattu teksti&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Tämä teksti on keskitetty&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;Tämä on yliviivattu&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Koodiesimerkki:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Listat:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU järjestelmät&lt;/li&gt;
                &lt;li&gt;AMD CPU järjestelmät&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Pystysuuntainen vieritys on säädettävissä, leveys nyt 10.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>Takaisin</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="36"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Valitse käyttäjänimi kirjautumiseen ja järjestelmänvalvojan tehtävien suorittamiseen</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="52"/>
      <source>What is your name?</source>
      <translation>Mikä on nimesi?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="59"/>
      <source>Your Full Name</source>
      <translation>Koko nimesi</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Mitä nimeä haluat käyttää sisäänkirjautumisessa?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login Name</source>
      <translation>Kirjautumisnimi</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="103"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Jos tätä tietokonetta käyttää useampi kuin yksi henkilö, voit luoda useita tilejä asennuksen jälkeen.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="118"/>
      <source>What is the name of this computer?</source>
      <translation>Mikä on tämän tietokoneen nimi?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="125"/>
      <source>Computer Name</source>
      <translation>Tietokoneen nimi</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="140"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Tätä nimeä käytetään, jos teet tietokoneen näkyväksi verkon muille käyttäjille.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="155"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Valitse salasana pitääksesi tilisi turvallisena.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="166"/>
      <source>Password</source>
      <translation>Salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="185"/>
      <source>Repeat Password</source>
      <translation>Toista salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="204"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Syötä sama salasana kahdesti, jotta se voidaan tarkistaa kirjoittamisvirheiden varalta. Hyvä salasana sisältää sekoituksen kirjaimia, numeroita ja välimerkkejä. Vähintään kahdeksan merkkiä pitkä ja se on vaihdettava säännöllisin väliajoin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="216"/>
      <source>Validate passwords quality</source>
      <translation>Tarkista salasanojen laatu</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="226"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Kun tämä valintaruutu on valittu, salasanan vahvuus tarkistetaan, etkä voi käyttää heikkoa salasanaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="234"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Kirjaudu automaattisesti ilman salasanaa</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="243"/>
      <source>Reuse user password as root password</source>
      <translation>Käytä käyttäjän salasanaa myös root-salasanana</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="253"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Käytä pääkäyttäjän tilillä samaa salasanaa.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="268"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Valitse root-salasana, jotta tilisi pysyy turvassa.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="279"/>
      <source>Root Password</source>
      <translation>Root salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="298"/>
      <source>Repeat Root Password</source>
      <translation>Toista Root salasana</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Syötä sama salasana kahdesti, jotta se voidaan tarkistaa kirjoitusvirheiden varalta.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="35"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Tervetuloa %1 &lt;quote&gt;%2&lt;/quote&gt; asentajaan&lt;/h3&gt;
            &lt;p&gt;Tämä ohjelma esittää sinulle joitain kysymyksiä ja asentaa %1 tietokoneellesi.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="66"/>
      <source>About</source>
      <translation>Tietoa</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Support</source>
      <translation>Tuki</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Known issues</source>
      <translation>Tunnetut ongelmat</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="102"/>
      <source>Release notes</source>
      <translation>Julkaisutiedot</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="114"/>
      <source>Donate</source>
      <translation>Lahjoita</translation>
    </message>
  </context>
</TS>

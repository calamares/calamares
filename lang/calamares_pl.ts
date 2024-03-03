<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="pl" version="2.1">
  <context>
    <name>AboutData</name>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="17"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; dla %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="20"/>
      <source>Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://app.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.</source>
      <translation>Podziękowania dla&lt;a href="https://calamares.io/team/"&gt; zespołu Calamares &lt;/a&gt;i &lt;a href="https://app.transifex.com/calamares/calamares/"&gt;zespołu tłumaczy Calamares&lt;/a&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="25"/>
      <source>&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>Rozwój &lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; jest sponsorowany przez &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="40"/>
      <source>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</source>
      <extracomment>Copyright year-year Name &lt;email-address&gt;</extracomment>
      <translation>Prawa autorskie %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>AutoMountManagementJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/AutoMountManagementJob.cpp" line="22"/>
      <source>Managing auto-mount settings…</source>
      <comment>@status</comment>
      <translation>Zarządzaj ustawieniami automatycznego montowania</translation>
    </message>
  </context>
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="60"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>&lt;strong&gt;Środowisko uruchomieniowe&lt;/strong&gt; systemu.&lt;br&gt;&lt;br&gt;Starsze systemy x86 obsługują tylko &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Nowoczesne systemy zwykle używają &lt;strong&gt;EFI&lt;/strong&gt;, lecz możliwe jest również ukazanie się BIOS, jeśli działa w trybie kompatybilnym.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="70"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Ten system został uruchomiony w środowisku rozruchowym &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Aby skonfigurować uruchomienie ze środowiska EFI, instalator musi wdrożyć aplikację programu rozruchowego, takiego jak &lt;strong&gt;GRUB&lt;/strong&gt; lub &lt;strong&gt;systemd-boot&lt;/strong&gt; na &lt;strong&gt;Partycji Systemu EFI&lt;/strong&gt;. Jest to automatyczne, chyba że wybierasz ręczne partycjonowanie, a w takim przypadku musisz wybrać ją lub utworzyć osobiście.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="82"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Ten system został uruchomiony w środowisku rozruchowym &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Aby skonfigurować uruchomienie ze środowiska BIOS, instalator musi zainstalować program rozruchowy, taki jak &lt;strong&gt;GRUB&lt;/strong&gt; na początku partycji lub w &lt;strong&gt;Głównym Sektorze Rozruchowym&lt;/strong&gt; blisko początku tablicy partycji (preferowane). Jest to automatyczne, chyba że wybierasz ręczne partycjonowanie, a w takim przypadku musisz ustawić ją osobiście.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="60"/>
      <source>Master Boot Record of %1</source>
      <comment>@info</comment>
      <translation>Master Boot Record %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="93"/>
      <source>Boot Partition</source>
      <comment>@info</comment>
      <translation>Partycja rozruchowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="100"/>
      <source>System Partition</source>
      <comment>@info</comment>
      <translation>Partycja systemowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="131"/>
      <source>Do not install a boot loader</source>
      <comment>@label</comment>
      <translation>Nie instaluj programu rozruchowego</translation>
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
      <translation>Pusta strona</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>Ogólne przechowywanie</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>Oczekujące zadania</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Moduły</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Rodzaj:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>brak</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Interfejs:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="102"/>
      <source>Crashes Calamares, so that Dr. Konqi can look at it.</source>
      <translation>Powoduje awarię Calamares, aby dr Konqui mógł się temu przyjrzeć.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="115"/>
      <source>Reloads the stylesheet from the branding directory.</source>
      <translation>Ponownie ładuje arkusz stylów z katalogu brandingu. </translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="118"/>
      <source>Reload Stylesheet</source>
      <translation>Przeładowuje Arkusz Stylów</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="128"/>
      <source>Displays the tree of widget names in the log (for stylesheet debugging).</source>
      <translation>Wyświetla drzewo nazw widżetów w dzienniku (do debugowania arkusza stylów).</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="131"/>
      <source>Widget Tree</source>
      <translation> Drzewo widżetów</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="141"/>
      <source>Uploads the session log to the configured pastebin.</source>
      <translation>Przesyła dziennik sesji do skonfigurowanego pliku na pastebin.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="144"/>
      <source>Send Session Log</source>
      <translation>Wyślij dziennik sesji</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="164"/>
      <source>Debug Information</source>
      <comment>@title</comment>
      <translation>Informacje dotyczące debugowania</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="77"/>
      <source>%p%</source>
      <comment>Progress percentage indicator: %p is where the number 0..100 is placed</comment>
      <translation>%p%</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Set Up</source>
      <comment>@label</comment>
      <translation>Skonfiguruj</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Install</source>
      <comment>@label</comment>
      <translation>Zainstaluj</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>Zadanie nie powiodło się (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Wyraźnie zażądano zaprogramowanej awarii zadania.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="203"/>
      <source>Done</source>
      <translation>Ukończono</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Przykładowe zadanie (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="49"/>
      <source>Running command %1 in target system…</source>
      <comment>@status</comment>
      <translation>Wykonywanie polecenia %1 w systemie docelowym...</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="53"/>
      <source>Running command %1…</source>
      <comment>@status</comment>
      <translation>Wykonywanie polecenia %1…</translation>
    </message>
  </context>
  <context>
    <name>Calamares::Python::Job</name>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="214"/>
      <source>Running %1 operation.</source>
      <translation>Wykonuję operację %1.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="229"/>
      <source>Bad working directory path</source>
      <translation>Niepoprawna ścieżka katalogu roboczego</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="230"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Katalog roboczy %1 dla zadań pythona %2 jest nieosiągalny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="238"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="314"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="340"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="357"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="365"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="373"/>
      <source>Bad main script file</source>
      <translation>Niepoprawny główny plik skryptu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="239"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Główny plik skryptu %1 dla zadań pythona %2 jest nieczytelny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="300"/>
      <source>Bad internal script</source>
      <translation>Błędny skrypt wewnętrzny</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="301"/>
      <source>Internal script for python job %1 raised an exception.</source>
      <translation>Wewnętrzny skrypt dla zadania python %1 zgłosił wyjątek.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="315"/>
      <source>Main script file %1 for python job %2 could not be loaded because it raised an  exception.</source>
      <translation>Główny plik skryptu %1 dla zadania python %2 nie mógł zostać załadowany, ponieważ zgłosił wyjątek.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="341"/>
      <source>Main script file %1 for python job %2 raised an exception.</source>
      <translation>Główny plik skryptu %1 dla zadania python %2 zgłosił wyjątek.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="358"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="366"/>
      <source>Main script file %1 for python job %2 returned invalid results.</source>
      <translation>Główny plik skryptu %1 dla zadania python %2 zwrócił nieprawidłowe wyniki.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="374"/>
      <source>Main script file %1 for python job %2 does not contain a run() function.</source>
      <translation>Główny plik skryptu %1 dla zadania python %2 nie zawiera funkcji run().</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Running %1 operation…</source>
      <comment>@status</comment>
      <translation>Wykonuję operację %1...</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="261"/>
      <source>Bad working directory path</source>
      <comment>@error</comment>
      <translation>Niepoprawna ścieżka katalogu roboczego</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="262"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>Katalog roboczy %1 dla zadań pythona %2 jest nieosiągalny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="270"/>
      <source>Bad main script file</source>
      <comment>@error</comment>
      <translation>Niepoprawny główny plik skryptu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="271"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>Główny plik skryptu %1 dla zadań pythona %2 jest nieczytelny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="343"/>
      <source>Boost.Python error in job "%1"</source>
      <comment>@error</comment>
      <translation>Błąd Boost.Python w zadaniu "%1"</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="73"/>
      <source>Loading…</source>
      <comment>@status</comment>
      <translation>Ładowanie...</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="100"/>
      <source>QML step &lt;i&gt;%1&lt;/i&gt;.</source>
      <comment>@label</comment>
      <translation>QML krok &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="286"/>
      <source>Loading failed.</source>
      <comment>@info</comment>
      <translation>Ładowanie nie powiodło się.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="99"/>
      <source>Requirements checking for module '%1' is complete.</source>
      <comment>@info</comment>
      <translation>Sprawdzanie wymagań dla modułu '%1' zostało zakończone.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="123"/>
      <source>Waiting for %n module(s)…</source>
      <comment>@status</comment>
      <translation>
        <numerusform>Oczekiwanie na %n moduł...</numerusform>
        <numerusform>Oczekiwanie na %n moduły...</numerusform>
        <numerusform>Oczekiwanie na %n modułów...</numerusform>
        <numerusform>Oczekiwanie na %n modułów...</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="124"/>
      <source>(%n second(s))</source>
      <comment>@status</comment>
      <translation>
        <numerusform>(%n sekunda)</numerusform>
        <numerusform>(%n sekundy)</numerusform>
        <numerusform>(%n sekund)</numerusform>
        <numerusform>(%n sekund)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="129"/>
      <source>System-requirements checking is complete.</source>
      <comment>@info</comment>
      <translation>Sprawdzanie wymagań systemowych zostało zakończone.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="165"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Przesyłanie nie powiodło się. Nie dokonano wklejania stron internetowych.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="177"/>
      <source>Install log posted to

%1

Link copied to clipboard</source>
      <translation>Dziennik instalacji opublikowany w

%1

Link skopiowany do schowka</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="183"/>
      <source>Install Log Paste URL</source>
      <translation>Wklejony adres URL dziennika instalacji</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
      <source>&amp;Yes</source>
      <translation>&amp;Tak</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
      <source>&amp;No</source>
      <translation>&amp;Nie</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="92"/>
      <source>&amp;Close</source>
      <translation>Zam&amp;knij</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="155"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Nieudane ustawianie</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="156"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Wystąpił błąd instalacji</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="159"/>
      <source>Error</source>
      <comment>@title</comment>
      <translation>Błąd</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="184"/>
      <source>Calamares Initialization Failed</source>
      <comment>@title</comment>
      <translation>Błąd inicjacji programu Calamares</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="185"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <comment>@info</comment>
      <translation>%1 nie może zostać zainstalowany. Calamares nie mógł wczytać wszystkich skonfigurowanych modułów. Jest to problem ze sposobem, w jaki Calamares jest używany przez dystrybucję.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <comment>@info</comment>
      <translation>&lt;br/&gt;Następujące moduły nie mogły zostać wczytane:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>Continue with Setup?</source>
      <comment>@title</comment>
      <translation>Kontynuować konfigurację?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="333"/>
      <source>Continue with Installation?</source>
      <comment>@title</comment>
      <translation>Kontynuować instalację?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>Program instalacyjny %1 dokona zmian na dysku, aby skonfigurować %2.&lt;br/&gt;&lt;strong&gt;Nie będzie można cofnąć tych zmian.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="339"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>Instalator %1 zamierza przeprowadzić zmiany na Twoim dysku, aby zainstalować %2.&lt;br/&gt;&lt;strong&gt;Nie będziesz mógł cofnąć tych zmian.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="344"/>
      <source>&amp;Set Up Now</source>
      <comment>@button</comment>
      <translation>U&amp;staw teraz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="344"/>
      <source>&amp;Install Now</source>
      <comment>@button</comment>
      <translation>Za&amp;instaluj teraz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="351"/>
      <source>Go &amp;Back</source>
      <comment>@button</comment>
      <translation>&amp;Wstecz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>&amp;Set Up</source>
      <comment>@button</comment>
      <translation>&amp;Skonfiguruj</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>&amp;Install</source>
      <comment>@button</comment>
      <translation>Za&amp;instaluj</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="400"/>
      <source>Setup is complete. Close the setup program.</source>
      <comment>@tooltip</comment>
      <translation>Konfiguracja jest zakończona. Zamknij program instalacyjny.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="401"/>
      <source>The installation is complete. Close the installer.</source>
      <comment>@tooltip</comment>
      <translation>Instalacja ukończona pomyślnie. Możesz zamknąć instalator.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="403"/>
      <source>Cancel the setup process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation>Anuluj konfigurację bez zmian w systemie.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="404"/>
      <source>Cancel the installation process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation>Anuluj konfigurację bez zmian w systemie.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="414"/>
      <source>&amp;Next</source>
      <comment>@button</comment>
      <translation>&amp;Dalej</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Back</source>
      <comment>@button</comment>
      <translation>&amp;Wstecz</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="425"/>
      <source>&amp;Done</source>
      <comment>@button</comment>
      <translation>&amp;Ukończono</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="444"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>&amp;Anuluj</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="516"/>
      <source>Cancel Setup?</source>
      <comment>@title</comment>
      <translation>Anulować konfigurację?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="516"/>
      <source>Cancel Installation?</source>
      <comment>@title</comment>
      <translation>Anulować instalację?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="517"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Czy naprawdę chcesz anulować bieżący proces konfiguracji?
Program instalacyjny zostanie zamknięty, a wszystkie zmiany zostaną utracone.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Czy na pewno chcesz anulować obecny proces instalacji?
Instalator zostanie zamknięty i wszystkie zmiany zostaną utracone.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="309"/>
      <source>Unknown exception type</source>
      <comment>@error</comment>
      <translation>Nieznany rodzaj wyjątku</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="327"/>
      <source>Unparseable Python error</source>
      <comment>@error</comment>
      <translation>Błąd Pythona niemożliwy do przeanalizowania</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="371"/>
      <source>Unparseable Python traceback</source>
      <comment>@error</comment>
      <translation>Błąd Pythone niemożliwy do prześledzenia</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="378"/>
      <source>Unfetchable Python error</source>
      <comment>@error</comment>
      <translation>Błąd Pythona niemożliwy do pobrania</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="405"/>
      <source>%1 Setup Program</source>
      <translation>%1 Program instalacyjny</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="406"/>
      <source>%1 Installer</source>
      <translation>Instalator %1</translation>
    </message>
  </context>
  <context>
    <name>ChangeFilesystemLabelJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="34"/>
      <source>Set filesystem label on %1</source>
      <comment>@title</comment>
      <translation>Ustaw etykietę systemu plików na %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="41"/>
      <source>Set filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Ustaw etykietę systemu plików &lt;strong&gt;%1&lt;/strong&gt; na partycji &lt;strong&gt;%2&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="50"/>
      <source>Setting filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Ustawianie etykiety systemu plików &lt;strong&gt;%1&lt;/strong&gt; na partycji &lt;strong&gt;%2&lt;/strong&gt;…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="72"/>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="84"/>
      <source>The installer failed to update partition table on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Instalator nie mógł zaktualizować tablicy partycji na dysku '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="38"/>
      <source>Gathering system information...</source>
      <translation>Zbieranie informacji o systemie...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="137"/>
      <source>Select storage de&amp;vice:</source>
      <comment>@label</comment>
      <translation>&amp;Wybierz urządzenie przechowywania:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="138"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1034"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1085"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1138"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Bieżący:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="139"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Po:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="896"/>
      <source>Reuse %1 as home partition for %2</source>
      <comment>@label</comment>
      <translation>Użyj ponownie %1 jako partycję główną dla %2</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1035"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Wybierz partycję do zmniejszenia, a następnie przeciągnij dolny pasek, aby zmienić jej rozmiar&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1059"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <comment>@info, %1 is partition name, %4 is product name</comment>
      <translation>%1 zostanie zmniejszony do %2MiB, a dla %4 zostanie utworzona nowa partycja %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1129"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Wybierz partycję, na której przeprowadzona będzie instalacja&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1189"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <comment>@info, %1 is product name</comment>
      <translation>Nigdzie w tym systemie nie można odnaleźć partycji systemowej EFI. Prosimy się cofnąć i użyć ręcznego partycjonowania dysku do ustawienia %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1197"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <comment>@info, %1 is partition path, %2 is product name</comment>
      <translation>Partycja systemowa EFI na %1 będzie użyta do uruchamiania %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1205"/>
      <source>EFI system partition:</source>
      <comment>@label</comment>
      <translation>Partycja systemowa EFI:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1334"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>To urządzenie pamięci masowej prawdopodobnie nie posiada żadnego systemu operacyjnego. Co chcesz zrobić?&lt;br/&gt;Będziesz miał możliwość przejrzenia oraz zatwierdzenia swoich ustawień przed wykonaniem jakichkolwiek zmian na tym urządzeniu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1339"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1376"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1397"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1422"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Wyczyść dysk&lt;/strong&gt;&lt;br/&gt;Ta operacja &lt;font color="red"&gt;usunie&lt;/font&gt; wszystkie dane obecnie znajdujące się na wybranym urządzeniu przechowywania.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1343"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1372"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1393"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1418"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Zainstaluj obok siebie&lt;/strong&gt;&lt;br/&gt;Instalator zmniejszy partycję, aby zrobić miejsce dla %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1347"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1380"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1401"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1426"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Zastąp partycję&lt;/strong&gt;&lt;br/&gt;Zastępowanie partycji poprzez %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1366"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>To urządzenie pamięci masowej posiada %1. Co chcesz zrobić?&lt;br/&gt;Będziesz miał możliwość przejrzenia oraz zatwierdzenia swoich ustawień przed wykonaniem jakichkolwiek zmian na tym urządzeniu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1388"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>To urządzenie pamięci masowej posiada już system operacyjny. Co chcesz zrobić?&lt;br/&gt;Będziesz miał możliwość przejrzenia oraz zatwierdzenia swoich ustawień przed wykonaniem jakichkolwiek zmian na tym urządzeniu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1413"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>To urządzenie pamięci masowej posiada kilka systemów operacyjnych. Co chcesz zrobić?&lt;br/&gt;Będziesz miał możliwość przejrzenia oraz zatwierdzenia swoich ustawień przed wykonaniem jakichkolwiek zmian na tym urządzeniu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1485"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>To urządzenie pamięci masowej ma już system operacyjny, ale tabela partycji &lt;strong&gt;%1 &lt;/strong&gt;różni się od wymaganego &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1508"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>To urządzenie pamięci masowej ma &lt;strong&gt;zamontowaną&lt;/strong&gt; jedną z partycji.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1513"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <comment>@info</comment>
      <translation>To urządzenie pamięci masowej jest częścią &lt;strong&gt;nieaktywnego urządzenia RAID&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1628"/>
      <source>No swap</source>
      <comment>@label</comment>
      <translation>Brak przestrzeni wymiany</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1637"/>
      <source>Reuse swap</source>
      <comment>@label</comment>
      <translation>Użyj ponownie przestrzeni wymiany</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1640"/>
      <source>Swap (no Hibernate)</source>
      <comment>@label</comment>
      <translation>Przestrzeń wymiany (bez hibernacji)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1643"/>
      <source>Swap (with Hibernate)</source>
      <comment>@label</comment>
      <translation>Przestrzeń wymiany (z hibernacją)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1646"/>
      <source>Swap to file</source>
      <comment>@label</comment>
      <translation>Przestrzeń wymiany do pliku</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1659"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Ręczne partycjonowanie&lt;/strong&gt;&lt;br/&gt;Możesz samodzielnie utworzyć lub zmienić rozmiar istniejących partycji.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1687"/>
      <source>Bootloader location:</source>
      <comment>@label</comment>
      <translation>Położenie programu rozruchowego:</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="267"/>
      <source>Successfully unmounted %1.</source>
      <translation>Pomyślnie odmontowano %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="274"/>
      <source>Successfully disabled swap %1.</source>
      <translation>Pomyślnie wyłączono pamięć wymiany %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="300"/>
      <source>Successfully cleared swap %1.</source>
      <translation>Pomyślnie wyczyszczono pamięć wymiany %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="314"/>
      <source>Successfully closed mapper device %1.</source>
      <translation>Pomyślnie zamknięto urządzenie mapujące %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="327"/>
      <source>Successfully disabled volume group %1.</source>
      <translation>Pomyślnie wyłączono grupę woluminów %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="366"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <comment>@title</comment>
      <translation>Wyczyść zamontowania dla operacji partycjonowania na %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="372"/>
      <source>Clearing mounts for partitioning operations on %1…</source>
      <comment>@status</comment>
      <translation>Czyszczenie punktów montowań dla operacji partycjonowania na %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="391"/>
      <source>Cleared all mounts for %1</source>
      <translation>Wyczyszczono wszystkie zamontowania dla %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
      <source>Clearing all temporary mounts…</source>
      <comment>@status</comment>
      <translation>Usuwanie wszystkich tymczasowych punktów montowania.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="70"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Wyczyszczono wszystkie tymczasowe montowania.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>Could not run command.</source>
      <translation>Nie można wykonać polecenia.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="165"/>
      <source>The commands use variables that are not defined. Missing variables are: %1.</source>
      <translation>Polecenia używają zmiennych, które nie są zdefiniowane. Brakujące zmienne to: %1.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="142"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Nieudane ustawianie</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="142"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Wystąpił błąd instalacji</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="144"/>
      <source>The setup of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>Instalacja %1 nie została ukończona pomyślnie.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>The installation of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>Instalacja %1 nie została ukończona pomyślnie.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="149"/>
      <source>Setup Complete</source>
      <comment>@title</comment>
      <translation>Ustawianie ukończone</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="150"/>
      <source>Installation Complete</source>
      <comment>@title</comment>
      <translation>Instalacja zakończona</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="151"/>
      <source>The setup of %1 is complete.</source>
      <comment>@info</comment>
      <translation>Ustawianie %1 jest ukończone.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="152"/>
      <source>The installation of %1 is complete.</source>
      <comment>@info</comment>
      <translation>Instalacja %1 ukończyła się pomyślnie.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="505"/>
      <source>Keyboard model has been set to %1&lt;br/&gt;.</source>
      <comment>@label, %1 is keyboard model, as in Apple Magic Keyboard</comment>
      <translation>Model klawiatury został ustawiony na %1&lt;br/&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="512"/>
      <source>Keyboard layout has been set to %1/%2.</source>
      <comment>@label, %1 is layout, %2 is layout variant</comment>
      <translation>Model klawiatury został ustawiony na %1/%2.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="373"/>
      <source>Set timezone to %1/%2</source>
      <comment>@action</comment>
      <translation>Ustaw strefę czasowa na %1/%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="410"/>
      <source>The system language will be set to %1.</source>
      <comment>@info</comment>
      <translation>Język systemu zostanie ustawiony na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="416"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <comment>@info</comment>
      <translation>Format liczb i daty zostanie ustawiony na %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Instalacja sieciowa. (Wyłączono: Nieprawidłowa konfiguracja)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="55"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Instalacja sieciowa. (Niedostępna: Otrzymano nieprawidłowe dane grupowe)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="57"/>
      <source>Network Installation. (Disabled: Internal error)</source>
      <translation>Instalacja sieciowa. (Wyłączono: Błąd wewnętrzny)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="59"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Instalacja sieciowa. (Wyłączona: Nie można pobrać listy pakietów, sprawdź swoje połączenie z siecią)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="61"/>
      <source>Network Installation. (Disabled: No package list)</source>
      <translation>Instalacja sieciowa. (Wyłączono: Brak listy pakietów)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="76"/>
      <source>Package selection</source>
      <translation>Wybór pakietów</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="110"/>
      <source>Package Selection</source>
      <translation>Wybór Pakietów</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="112"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Wybierz produkt z listy. Wybrany produkt zostanie zainstalowany.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="241"/>
      <source>Packages</source>
      <translation>Pakiety</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>Install option: &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>Opcja instalacji: &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>None</source>
      <translation>Brak</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="35"/>
      <source>Summary</source>
      <comment>@label</comment>
      <translation>Podsumowanie</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="39"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Jest to przegląd tego, co stanie się po rozpoczęciu procedury konfiguracji.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="44"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>To jest podsumowanie czynności, które zostaną wykonane po rozpoczęciu przez Ciebie instalacji.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="235"/>
      <source>Your username is too long.</source>
      <translation>Twoja nazwa użytkownika jest za długa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="241"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Nazwa użytkownika musi zaczynać się od małej litery lub podkreślenia.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="245"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Dozwolone są tylko małe litery, cyfry, podkreślenia i łączniki.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="251"/>
      <source>'%1' is not allowed as username.</source>
      <translation>'%1' nie może zostać użyte jako nazwa użytkownika.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="300"/>
      <source>Your hostname is too short.</source>
      <translation>Twoja nazwa komputera jest za krótka.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="304"/>
      <source>Your hostname is too long.</source>
      <translation>Twoja nazwa komputera jest za długa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="310"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>"%1" nie jest dozwolona jako nazwa hosta.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="315"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Dozwolone są tylko litery, cyfry, podkreślenia i łączniki.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="598"/>
      <source>Your passwords do not match!</source>
      <translation>Twoje hasła nie są zgodne!</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="612"/>
      <source>OK!</source>
      <translation>OK!</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="57"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue.</source>
      <translation>Ten komputer nie spełnia minimalnych wymagań, niezbędnych do instalacji %1.&lt;br/&gt;Konfiguracja nie może być kontynuowana.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue.</source>
      <translation>Ten komputer nie spełnia minimalnych wymagań, niezbędnych do instalacji %1.&lt;br/&gt;Instalacja nie może być kontynuowana.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="66"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Ten komputer nie spełnia niektórych zalecanych wymagań dotyczących konfigurowania %1. &lt;br/&gt;Konfiguracja może być kontynuowana, ale niektóre funkcje mogą być wyłączone.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="70"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Ten komputer nie spełnia wszystkich, zalecanych do instalacji %1 wymagań.&lt;br/&gt;Instalacja może być kontynuowana, ale niektóre opcje mogą być niedostępne.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="80"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Ten program zada Ci garść pytań i ustawi %2 na Twoim komputerze.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="264"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Witamy w programie instalacyjnym Calamares dla %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="265"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Witamy w konfiguracji %1 &lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="269"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Witamy w instalatorze Calamares dla %1&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="270"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Witamy w instalatorze %1</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="115"/>
      <source>Performing contextual processes' job…</source>
      <comment>@status</comment>
      <translation>Wykonywanie zadań związanych z procesami kontekstowymi...</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Utwórz partycję</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>Ro&amp;zmiar:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation>MB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Rodzaj par&amp;tycji:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>Primar&amp;y</source>
      <translation>Podstawow&amp;y</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>Ro&amp;zszerzona</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>System p&amp;lików:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>Nazwa LV LVM</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>Punkt &amp;montowania:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="191"/>
      <source>Flags:</source>
      <translation>Flagi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="224"/>
      <source>Label for the filesystem</source>
      <translation>Etykieta dla systemu plików</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="234"/>
      <source>FS Label:</source>
      <translation>Etykieta FS:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="67"/>
      <source>En&amp;crypt</source>
      <comment>@action</comment>
      <translation>Zaszy%fruj</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="195"/>
      <source>Logical</source>
      <comment>@label</comment>
      <translation>Logiczna</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="200"/>
      <source>Primary</source>
      <comment>@label</comment>
      <translation>Podstawowa</translation>
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
      <translation>Punkt montowania jest już używany. Proszę wybrać inny.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="96"/>
      <source>Mountpoint must start with a &lt;tt&gt;/&lt;/tt&gt;.</source>
      <comment>@info</comment>
      <translation>Punkt montowania musi się zaczynać od &lt;tt&gt;/&lt;/tt&gt;.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="181"/>
      <source>Create new %1MiB partition on %3 (%2) with entries %4</source>
      <comment>@title</comment>
      <translation>Utwórz nową partycję %1MiB na %3 (%2) z wpisami %4</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="189"/>
      <source>Create new %1MiB partition on %3 (%2)</source>
      <comment>@title</comment>
      <translation>Utwórz nową partycję %1MiB na %3 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="196"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1</source>
      <comment>@title</comment>
      <translation>Utwórz nową partycję %2MiB w %4 (%3) z systemem plików %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="212"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2) with entries &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Utwórz nową partycję &lt;strong&gt;%1MiB&lt;/strong&gt; na &lt;strong&gt;%3&lt;/strong&gt; (%2) z wpisami &lt;em&gt;%4&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="222"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>Utwórz nową partycję &lt;strong&gt;%1MiB&lt;/strong&gt; na &lt;strong&gt;%3&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="229"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Utwórz nową partycję &lt;strong&gt;%2MiB&lt;/strong&gt; w &lt;strong&gt;%4&lt;/strong&gt; (%3) z systemem plików &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="254"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="257"/>
      <source>Creating new %1 partition on %2…</source>
      <comment>@status</comment>
      <translation>Tworzenie nowej partycji %1 na %2...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="274"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Instalator nie mógł utworzyć partycji na dysku '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Utwórz tablicę partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Utworzenie nowej tablicy partycji usunie wszystkie istniejące na dysku dane.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Jaki rodzaj tablicy partycji chcesz utworzyć?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>Tablica partycji GUID (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="41"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="58"/>
      <source>Creating new %1 partition table on %2…</source>
      <comment>@status</comment>
      <translation>Tworzenie nowej tablicy partycji %1 na %2...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
      <source>Creating new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3)…</source>
      <comment>@status</comment>
      <translation>Tworzenie nowej tabeli partycji &lt;strong&gt;%1&lt;/strong&gt; na &lt;strong&gt;%2&lt;/strong&gt; (%3)...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="86"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Instalator nie mógł utworzyć tablicy partycji na %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="33"/>
      <source>Create user %1</source>
      <translation>Utwórz użytkownika %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="39"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>Utwórz użytkownika &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="45"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="137"/>
      <source>Creating user %1…</source>
      <comment>@status</comment>
      <translation>Tworzenie użytkownika %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="120"/>
      <source>Preserving home directory…</source>
      <comment>@status</comment>
      <translation>Zachowywanie katalogu domowego...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="145"/>
      <source>Configuring user %1</source>
      <comment>@status</comment>
      <translation>Konfigurowanie użytkownika %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="153"/>
      <source>Setting file permissions…</source>
      <comment>@status</comment>
      <translation>Przyznawanie uprawnień do plików...</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <comment>@title</comment>
      <translation>Utwórz grupę woluminów</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="32"/>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="44"/>
      <source>Creating new volume group named %1…</source>
      <comment>@status</comment>
      <translation>Tworzenie nowej grupy woluminów o nazwie %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Creating new volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Tworzenie nowej grupy woluminów o nazwie &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="51"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Instalator nie mógł utworzyć grupy woluminów o nazwie %1</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="38"/>
      <source>Deactivating volume group named %1…</source>
      <comment>@status</comment>
      <translation>Dezaktywowanie grupy woluminów o nazwie %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="32"/>
      <source>Deactivating volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Dezaktywowanie grupy woluminów o nazwie &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Instalator nie mógł dezaktywować grupy woluminów o nazwie %1</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="85"/>
      <source>Deleting partition %1…</source>
      <comment>@status</comment>
      <translation>Usuwanie partycji %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="79"/>
      <source>Deleting partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Usuwanie partycji &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="99"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Instalator nie mógł usunąć partycji %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="78"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Ten rodzaj tabeli partycji jest zalecany tylko dla systemów uruchamianych ze środowiska uruchomieniowego &lt;strong&gt;BIOS&lt;/strong&gt;. GPT jest zalecane w większości innych wypadków.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Ostrzeżenie:&lt;/strong&gt; tabele partycji MBR są przestarzałym standardem z ery MS-DOS.&lt;br&gt;Możesz posiadać tylko 4 partycje &lt;em&gt;podstawowe&lt;/em&gt;, z których jedna może być partycją &lt;em&gt;rozszerzoną&lt;/em&gt;, zawierającą wiele partycji &lt;em&gt;logicznych&lt;/em&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="89"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Zalecany rodzaj tabeli partycji dla nowoczesnych systemów uruchamianych przez &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="95"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>To jest urządzenie &lt;strong&gt;pętli zwrotnej&lt;/strong&gt;. To jest pseudo-urządzenie, które nie posiada tabeli partycji, która czyni plik dostępny jako urządzenie blokowe. Ten rodzaj instalacji zwykle zawiera tylko jeden system plików.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Instalator &lt;strong&gt;nie mógł znaleźć tabeli partycji&lt;/strong&gt; na zaznaczonym nośniku danych.&lt;br&gt;&lt;br&gt;Urządzenie nie posiada tabeli partycji bądź jest ona uszkodzona lub nieznanego rodzaju.&lt;br&gt;Instalator może utworzyć dla Ciebie nową tabelę partycji automatycznie, lub możesz uczynić to ręcznie.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="139"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>To urządzenie ma &lt;strong&gt;%1&lt;/strong&gt; tablicę partycji.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="147"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Typ &lt;strong&gt;tabeli partycji&lt;/strong&gt; na zaznaczonym nośniku danych.&lt;br&gt;&lt;br&gt;Jedyną metodą na zmianę tabeli partycji jest jej wyczyszczenie i utworzenie jej od nowa, co spowoduje utratę wszystkich danych.&lt;br&gt;Ten instalator zachowa obecną tabelę partycji, jeżeli nie wybierzesz innej opcji.&lt;br&gt;W wypadku niepewności, w nowszych systemach zalecany jest GPT.</translation>
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
      <translation>%1 - (%2) </translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="117"/>
      <source>Writing LUKS configuration for Dracut to %1…</source>
      <comment>@status</comment>
      <translation>Zapisywanie konfiguracji LUKS dla Dracut do %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skipping writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <comment>@info</comment>
      <translation>Pomijanie zapisywania konfiguracji LUKS dla Dracut: partycja "/" nie jest szyfrowana</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <comment>@error</comment>
      <translation>Nie udało się otworzyć %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="35"/>
      <source>Performing dummy C++ job…</source>
      <comment>@status</comment>
      <translation>Wykonywanie fikcyjnego zadania C++...</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Edycja istniejącej partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Con&amp;tent:</source>
      <translation>Zawar&amp;tość:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>&amp;Zachowaj</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Sformatuj</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Ostrzeżenie: Sformatowanie partycji wymaże wszystkie istniejące na niej dane.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>Punkt &amp;montowania:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source>Si&amp;ze:</source>
      <translation>Ro&amp;zmiar:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="139"/>
      <source> MiB</source>
      <translation> MB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="146"/>
      <source>Fi&amp;le System:</source>
      <translation>System p&amp;lików:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="159"/>
      <source>Flags:</source>
      <translation>Flagi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="179"/>
      <source>Label for the filesystem</source>
      <translation>Etykieta dla systemu plików</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="189"/>
      <source>FS Label:</source>
      <translation>Etykieta FS:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="259"/>
      <source>Passphrase for existing partition</source>
      <translation>Hasło dla istniejącej partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="260"/>
      <source>Partition %1 could not be decrypted with the given passphrase.&lt;br/&gt;&lt;br/&gt;Edit the partition again and give the correct passphrase or delete and create a new encrypted partition.</source>
      <translation>Nie można rozszyfrować partycji %1 za pomocą podanego hasła.&lt;br/&gt;&lt;br/&gt;Edytuj partycję ponownie i podaj poprawne hasło lub usuń i utwórz nową zaszyfrowaną partycję.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Zaszy&amp;fruj system</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="43"/>
      <source>Your system does not seem to support encryption well enough to encrypt the entire system. You may enable encryption, but performance may suffer.</source>
      <translation>Wydaje się, że system nie obsługuje szyfrowania wystarczająco dobrze, aby zaszyfrować cały system. Możesz włączyć szyfrowanie, ale wydajność może ucierpieć.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="59"/>
      <source>Passphrase</source>
      <translation>Hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="69"/>
      <source>Confirm passphrase</source>
      <translation>Potwierdź hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="153"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="168"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <comment>@tooltip</comment>
      <translation>Użyj tego samego hasła w obu polach.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="158"/>
      <source>Password must be a minimum of %1 characters.</source>
      <comment>@tooltip</comment>
      <translation>Hasło musi mieć co najmniej %1 znaków.</translation>
    </message>
  </context>
  <context>
    <name>ErrorDialog</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="40"/>
      <source>Details:</source>
      <translation>Szczegóły:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="56"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Czy chcesz wkleić dziennik instalacji do sieci Web?</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="179"/>
      <source>Set partition information</source>
      <comment>@title</comment>
      <translation>Ustaw informacje partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="208"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition with features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Zainstaluj %1 na &lt;strong&gt;nowej&lt;/strong&gt; partycji systemowej %2 z funkcjami &lt;em&gt;%3&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="217"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition</source>
      <comment>@info</comment>
      <translation>Zainstaluj %1 na &lt;strong&gt;nowej&lt;/strong&gt; partycji systemowej %2</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="226"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt; and features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Skonfiguruj &lt;strong&gt;nową&lt;/strong&gt; partycję %2 z punktem montowania &lt;strong&gt;%1&lt;/strong&gt; i funkcjami &lt;em&gt;%3&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="235"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;%3</source>
      <comment>@info</comment>
      <translation>Skonfiguruj &lt;strong&gt;nową&lt;/strong&gt; partycję %2 z punktem montowania &lt;strong&gt;%1&lt;/strong&gt;%3</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="250"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt; with features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Zainstaluj %2 na partycji systemowej %3 &lt;strong&gt;%1 &lt;/strong&gt;z funkcjami &lt;em&gt;%4&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="260"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Zainstaluj %2 na partycji systemowej %3 &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="270"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt; and features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>Skonfiguruj partycję %3 &lt;strong&gt;%1&lt;/strong&gt; z punktem montowania &lt;strong&gt;%2&lt;/strong&gt; i funkcjami &lt;em&gt;%4&lt;/em&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="280"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;%4…</source>
      <comment>@info</comment>
      <translation>Skonfiguruj partycję %3 &lt;strong&gt;%1 &lt;/strong&gt;z punktem montowania &lt;strong&gt;%2&lt;/strong&gt;%4...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="296"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@info</comment>
      <translation>Zainstaluj program rozruchowy na &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="305"/>
      <source>Setting up mount points…</source>
      <comment>@status</comment>
      <translation>Ustawianie punktów montowania...</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Uruchom ponownie teraz</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="75"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Wszystko gotowe.&lt;/h1&gt;&lt;br/&gt;%1 został skonfigurowany na twoim komputerze.&lt;br/&gt;Możesz teraz zacząć używać swojego nowego systemu.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="79"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Gdy to pole jest zaznaczone, system będzie uruchamiany ponownie natychmiast po kliknięciu na &lt;span style="font-style:italic;"&gt;Ukończone&lt;/span&gt; lub zamknięciu programu instalacyjnego.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="87"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Wszystko gotowe.&lt;/h1&gt;&lt;br/&gt;%1 został zainstalowany na Twoim komputerze.&lt;br/&gt;Możesz teraz ponownie uruchomić komputer, aby przejść do nowego systemu, albo kontynuować używanie środowiska live %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="92"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Gdy to pole jest zaznaczone, system będzie uruchamiany ponownie natychmiast po kliknięciu na &lt;span style="font-style:italic;"&gt;Ukończone&lt;/span&gt; lub zamknięciu programu instalacyjnego.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="105"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>&lt;h1&gt;Instalacja nie powiodła się&lt;/h1&gt;&lt;br/&gt;%1 nie został zainstalowany na twoim komputerze.&lt;br/&gt;Komunikat o błędzie: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="113"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>&lt;h1&gt;Instalacja nie powiodła się&lt;/h1&gt;&lt;br/&gt;Nie udało się zainstalować %1 na Twoim komputerze.&lt;br/&gt;Komunikat o błędzie: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedQmlViewStep</name>
    <message>
      <location filename="../src/modules/finishedq/FinishedQmlViewStep.cpp" line="35"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Koniec</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="46"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Koniec</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="39"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4</source>
      <comment>@title</comment>
      <translation>Sformatuj partycję %1 (system plików: %2, rozmiar: %3 MiB) na %4</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="49"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Sformatuj partycję &lt;strong&gt;%3MiB&lt;/strong&gt;&lt;strong&gt;%1&lt;/strong&gt; z systemem plików &lt;strong&gt;%2&lt;/strong&gt;</translation>
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
      <translation>Formatowanie partycji %1 z systemem plików %2...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="73"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Instalator nie mógł sformatować partycji %1 na dysku '%2'.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>Please ensure the system has at least %1 GiB available drive space.</source>
      <translation>Upewnij się, że system ma co najmniej %1 GiB wolnego miejsca na dysku.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>Available drive space is all of the hard disks and SSDs connected to the system.</source>
      <translation>Dostępne miejsce na dysku to wszystkie dyski twarde i dyski SSD podłączone do systemu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="165"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Nie ma wystarczającej ilości miejsca na dysku. Wymagane jest przynajmniej %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="173"/>
      <source>has at least %1 GiB working memory</source>
      <translation>ma przynajmniej %1 GiB pamięci roboczej</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="175"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>System nie ma wystarczającej ilości pamięci roboczej. Wymagane jest co najmniej %1 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="184"/>
      <source>is plugged in to a power source</source>
      <translation>jest podłączony do źródła zasilania</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="185"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>System nie jest podłączony do źródła zasilania.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="192"/>
      <source>is connected to the Internet</source>
      <translation>jest podłączony do Internetu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="193"/>
      <source>The system is not connected to the Internet.</source>
      <translation>System nie jest podłączony do Internetu.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="200"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>uruchamia instalator jako administrator (root)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="204"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Program instalacyjny nie jest uruchomiony z prawami administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="205"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Instalator jest uruchomiony bez praw administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="213"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>posiada ekran wystarczająco duży, aby pokazać cały instalator</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="217"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Ekran jest zbyt mały, aby wyświetlić program konfiguracyjny.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="218"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Zbyt niska rozdzielczość ekranu, aby wyświetlić instalator.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="227"/>
      <source>is always false</source>
      <translation>jest zawsze fałszywe</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="228"/>
      <source>The computer says no.</source>
      <translation>Komputer mówi nie.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="236"/>
      <source>is always false (slowly)</source>
      <translation>jest zawsze fałszywe (powoli)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="237"/>
      <source>The computer says no (slowly).</source>
      <translation>Komputer mówi nie (powoli)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="244"/>
      <source>is always true</source>
      <translation>jest zawsze prawdziwe</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="245"/>
      <source>The computer says yes.</source>
      <translation>Komputer mówi tak.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="253"/>
      <source>is always true (slowly)</source>
      <translation>jest zawsze prawdziwe (powoli)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="254"/>
      <source>The computer says yes (slowly).</source>
      <translation>Komputer mówi tak (powoli).</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="262"/>
      <source>is checked three times.</source>
      <translation>jest sprawdzany trzykrotnie.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="265"/>
      <source>The snark has not been checked three times.</source>
      <comment>The (some mythological beast) has not been checked three times.</comment>
      <translation>Snark nie był sprawdzany trzy razy.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="39"/>
      <source>Collecting information about your machine…</source>
      <comment>@status</comment>
      <translation>Zbieranie informacji o twoim urządzeniu...</translation>
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
      <translation>Identyfikator partii OEM</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nie można utworzyć katalogów &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nie można otworzyć pliku  &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Nie można zapisać do pliku  &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio…</source>
      <comment>@status</comment>
      <translation>Tworzenie initramfs przy użyciu mkinitcpio...</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="27"/>
      <source>Creating initramfs…</source>
      <comment>@status</comment>
      <translation>Tworzenie initramfs...</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="49"/>
      <source>Konsole not installed.</source>
      <comment>@error</comment>
      <translation>Konsola nie jest zainstalowana.</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="50"/>
      <source>Please install KDE Konsole and try again!</source>
      <comment>@info</comment>
      <translation>Zainstaluj KDE Konsole i spróbuj ponownie!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <comment>@info</comment>
      <translation>Wykonywanie skryptu: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="40"/>
      <source>Script</source>
      <comment>@label</comment>
      <translation>Skrypt</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klawiatura</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="41"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klawiatura</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System Locale Setting</source>
      <comment>@title</comment>
      <translation>Konfigurowanie ustawień regionalnych systemu</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>Systemowe ustawienia lokalne wpływają na ustawienia języka i znaków w niektórych elementach wiersza poleceń interfejsu użytkownika.&lt;br/&gt;Bieżące ustawienie to &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>&amp;Anuluj</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
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
      <translation>Konfigurowanie zaszyfrowanej przestrzeni wymiany.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="87"/>
      <source>No target system available.</source>
      <translation>Brak dostępnego systemu docelowego.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="95"/>
      <source>No rootMountPoint is set.</source>
      <translation>Brak ustawionego punktu montowania /.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="100"/>
      <source>No configFilePath is set.</source>
      <translation>Nie ustawiono ścieżki do pliku konfiguracyjnego.</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Umowa licencyjna&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="142"/>
      <source>I accept the terms and conditions above.</source>
      <comment>@info</comment>
      <translation>Akceptuję powyższe warunki korzystania.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="144"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <comment>@info</comment>
      <translation>Zapoznaj się z umowami licencyjnymi użytkownika końcowego (EULA).</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <comment>@info</comment>
      <translation>Ta procedura konfiguracji spowoduje zainstalowanie oprogramowania własnościowego, które podlega warunkom licencyjnym.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="152"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <comment>@info</comment>
      <translation>Jeśli nie zgadzasz się z warunkami, procedura konfiguracji nie będzie kontynuowana.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="157"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <comment>@info</comment>
      <translation>Ta procedura konfiguracji umożliwia zainstalowanie oprogramowania własnościowego, które podlega warunkom licencyjnym w celu zapewnienia dodatkowych funkcji i zwiększenia wygody użytkownika.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="162"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <comment>@info</comment>
      <translation>Jeśli nie zgadzasz się z warunkami, oprogramowanie własnościowe nie zostanie zainstalowane, a zamiast tego zostaną użyte alternatywy o otwartym kodzie źródłowym.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="45"/>
      <source>License</source>
      <comment>@label</comment>
      <translation>Licencja</translation>
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
      <translation>&lt;strong&gt;sterownik %1&lt;/strong&gt;&lt;br/&gt;autorstwa %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;sterownik graficzny %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;autorstwa %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;wtyczka do przeglądarki %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;autorstwa %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;kodek %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;autorstwa %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;pakiet %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;autorstwa %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;autorstwa %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <comment>@label</comment>
      <translation>Plik: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide the license text</source>
      <comment>@tooltip</comment>
      <translation>Ukryj tekst licencji</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <comment>@tooltip</comment>
      <translation>Pokaż tekst licencji</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open the license agreement in browser</source>
      <comment>@tooltip</comment>
      <translation>Otwórz umowę licencyjną w przeglądarce</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <comment>@label</comment>
      <translation>Region:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <comment>@label</comment>
      <translation>Strefa:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change…</source>
      <comment>@button</comment>
      <translation>&amp;Zmień...</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Położenie</translation>
    </message>
  </context>
  <context>
    <name>LocaleTests</name>
    <message>
      <location filename="../src/libcalamares/locale/Tests.cpp" line="266"/>
      <source>Quit</source>
      <translation>Wyjdź</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="71"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Położenie</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="33"/>
      <source>Configuring LUKS key file.</source>
      <translation>Konfigurowanie pliku klucza LUKS.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="254"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="262"/>
      <source>No partitions are defined.</source>
      <translation>Nie zdefiniowano żadnych partycji.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="297"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="304"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Błąd konfiguracji zaszyfrowanych rootfs</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="298"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>Partycja główna %1 to LUKS, ale nie ustawiono hasła.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="305"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>Nie można utworzyć pliku klucza LUKS dla partycji głównej %1.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="55"/>
      <source>Generate machine-id.</source>
      <translation>Generuj machine-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="71"/>
      <source>Configuration Error</source>
      <translation>Błąd konfiguracji</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="72"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>Dla MachineId nie ustawiono punktu montowania katalogu głównego (root).</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="63"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="71"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="75"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="92"/>
      <source>File not found</source>
      <translation>Plik nie został znaleziony</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>Ścieżka &lt;pre&gt;%1&lt;/pre&gt; musi być ścieżką bezwzględną.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nie można utworzyć nowego losowego pliku&lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="237"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Strefa czasowa: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@info</comment>
      <translation>Wybierz preferowaną lokalizację na mapie, aby instalator mógł zasugerować ustawienia regionalne 
            i ustawienia strefy czasowej. Możesz dostosować sugerowane ustawienia poniżej. Wyszukaj mapę, przeciągając
            aby przesuwać i używać przycisków +/-, aby powiększać/pomniejszać lub używać przewijania myszą do powiększania.</translation>
    </message>
  </context>
  <context>
    <name>Map-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="237"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Strefa czasowa: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@label</comment>
      <translation>Wybierz preferowaną lokalizację na mapie, aby instalator mógł zasugerować ustawienia regionalne 
            i ustawienia strefy czasowej. Możesz dostosować sugerowane ustawienia poniżej. Wyszukaj mapę, przeciągając
            aby przesuwać i używać przycisków +/-, aby powiększać/pomniejszać lub używać przewijania myszą do powiększania.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="50"/>
      <source>Package selection</source>
      <translation>Wybór pakietów</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
      <source>Office software</source>
      <translation>Oprogramowanie biurowe</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
      <source>Office package</source>
      <translation>Pakiet biurowy</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="53"/>
      <source>Browser software</source>
      <translation>Oprogramowanie przeglądarki</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Browser package</source>
      <translation>Pakiet przeglądarki</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Web browser</source>
      <translation>Przeglądarka internetowa</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Kernel</source>
      <comment>label for netinstall module, Linux kernel</comment>
      <translation>Jądro</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Services</source>
      <comment>label for netinstall module, system services</comment>
      <translation>Usługi</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Login</source>
      <comment>label for netinstall module, choose login manager</comment>
      <translation>Login</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Desktop</source>
      <comment>label for netinstall module, choose desktop environment</comment>
      <translation>Pulpit</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Applications</source>
      <translation>Aplikacje</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Communication</source>
      <comment>label for netinstall module</comment>
      <translation>Komunikacja</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Development</source>
      <comment>label for netinstall module</comment>
      <translation>Programowanie</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Office</source>
      <comment>label for netinstall module</comment>
      <translation>Biuro</translation>
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
      <translation>Wygląd</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Gaming</source>
      <comment>label for netinstall module</comment>
      <translation>Gra</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Utilities</source>
      <comment>label for netinstall module</comment>
      <translation>Narzędzia</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Notatki</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Par&amp;tia:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Wprowadź tutaj identyfikator partii. Zostanie on zapisany w systemie docelowym.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;Konfiguracja OEM &lt;/h1&gt;&lt;p&gt;Calamares użyje ustawień OEM podczas konfigurowania systemu docelowego.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="118"/>
      <source>OEM Configuration</source>
      <translation>Konfiguracja OEM</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="124"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Ustaw identyfikator partii OEM na &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation>Wybierz preferowany region lub użyj ustawień domyślnych</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Strefa czasowa: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation>Wybierz preferowaną strefę w swoim regionie</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Strefy</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation>Poniżej możesz dostosować ustawienia języka i ustawień regionalnych</translation>
    </message>
  </context>
  <context>
    <name>Offline-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation>Wybierz preferowany region lub użyj ustawień domyślnych</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Strefa czasowa: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation>Wybierz preferowaną strefę w swoim regionie</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Strefy</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation>Poniżej możesz dostosować ustawienia języka i ustawień regionalnych</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="52"/>
      <source>Password is too short</source>
      <translation>Hasło jest zbyt krótkie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="68"/>
      <source>Password is too long</source>
      <translation>Hasło jest zbyt długie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="189"/>
      <source>Password is too weak</source>
      <translation>Hasło jest zbyt słabe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="197"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Wystąpił błąd przydzielania pamięci przy ustawieniu '%1'</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="200"/>
      <source>Memory allocation error</source>
      <translation>Błąd przydzielania pamięci</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password is the same as the old one</source>
      <translation>Hasło jest takie samo jak poprzednie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="204"/>
      <source>The password is a palindrome</source>
      <translation>Hasło jest palindromem</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password differs with case changes only</source>
      <translation>Hasła różnią się tylko wielkością znaków</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="208"/>
      <source>The password is too similar to the old one</source>
      <translation>Hasło jest zbyt podobne do poprzedniego</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password contains the user name in some form</source>
      <translation>Hasło zawiera nazwę użytkownika</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="212"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Hasło zawiera fragment pełnej nazwy użytkownika</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Hasło zawiera jeden z niedozwolonych wyrazów</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Hasło zawiera mniej niż %n cyfrę</numerusform>
        <numerusform>Hasło zawiera mniej niż %n cyfry</numerusform>
        <numerusform>Hasło zawiera mniej niż %n cyfr</numerusform>
        <numerusform>Hasło zawiera mniej niż %n cyfr</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password contains too few digits</source>
      <translation>Hasło zawiera zbyt mało znaków</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Hasło zawiera mniej niż %n wielką literę</numerusform>
        <numerusform>Hasło zawiera mniej niż %n wielkie litery</numerusform>
        <numerusform>Hasło zawiera mniej niż %n wielkich liter</numerusform>
        <numerusform>Hasło zawiera mniej niż %n wielkich liter</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="229"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Hasło zawiera zbyt mało wielkich liter</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="233"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Hasło składa się z mniej niż %1 małej litery</numerusform>
        <numerusform>Hasło składa się z mniej niż %1 małych liter</numerusform>
        <numerusform>Hasło składa się z mniej niż %1 małych liter</numerusform>
        <numerusform>Hasło składa się z mniej niż %1 małych liter</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="236"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Hasło zawiera zbyt mało małych liter</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="240"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>Hasło zawiera mniej niż %n znak niealfanumeryczny</numerusform>
        <numerusform>Hasło zawiera mniej niż %n znaki niealfanumeryczne</numerusform>
        <numerusform>Hasło zawiera mniej niż %n znaków niealfanumerycznych</numerusform>
        <numerusform>Hasło zawiera mniej niż %n znaków niealfanumerycznych</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Hasło zawiera zbyt mało znaków niealfanumerycznych</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Hasło jest krótsze niż %n znak</numerusform>
        <numerusform>Hasło jest krótsze niż %n znaki</numerusform>
        <numerusform>Hasło jest krótsze niż %n znaków</numerusform>
        <numerusform>Hasło jest krótsze niż %n znaków</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>The password is too short</source>
      <translation>Hasło jest zbyt krótkie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Hasło jest obróconą wersją poprzedniego</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="256"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Hasło zawiera mniej niż %n klasę znaków</numerusform>
        <numerusform>Hasło zawiera mniej niż %n klasy znaków</numerusform>
        <numerusform>Hasło zawiera mniej niż %n klas znaków</numerusform>
        <numerusform>Hasło zawiera mniej niż %n klas znaków</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
      <source>The password does not contain enough character classes</source>
      <translation>Hasło zawiera zbyt mało rodzajów znaków</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Hasło zawiera więcej niż %n taki sam znak po sobie</numerusform>
        <numerusform>Hasło zawiera więcej niż %n takie same znaki po sobie</numerusform>
        <numerusform>Hasło zawiera więcej niż %n takich samych znaków po sobie</numerusform>
        <numerusform>Hasło zawiera więcej niż %n takich samych znaków po sobie</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="266"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Hasło zawiera zbyt wiele powtarzających się znaków</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="270"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Hasło zawiera więcej niż %n znak kolejno tej samej klasy</numerusform>
        <numerusform>Hasło zawiera więcej niż %n znaki kolejno tej samej klasy</numerusform>
        <numerusform>Hasło zawiera więcej niż %n znaków kolejno tej samej klasy</numerusform>
        <numerusform>Hasło zawiera więcej niż %n znaków kolejno tej samej klasy</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="276"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Hasło składa się ze zbyt wielu znaków tego samego rodzaju</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="281"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>Hasło zawiera sekwencję monotoniczną dłuższą niż %n znak</numerusform>
        <numerusform>Hasło zawiera sekwencję monotoniczną dłuższą niż %n znaki</numerusform>
        <numerusform>Hasło zawiera sekwencję monotoniczną dłuższą niż %n znaków</numerusform>
        <numerusform>Hasło zawiera sekwencję monotoniczną dłuższą niż %n znaków</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="287"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Hasło zawiera zbyt długi ciąg jednakowych znaków</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="290"/>
      <source>No password supplied</source>
      <translation>Nie podano hasła</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="292"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Nie można uzyskać losowych znaków z urządzenia RNG</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="294"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Błąd tworzenia hasła - wymagana entropia jest zbyt niska dla ustawień</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="299"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Hasło nie przeszło pomyślnie sprawdzenia słownikowego - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The password fails the dictionary check</source>
      <translation>Hasło nie przeszło pomyślnie sprawdzenia słownikowego</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown setting - %1</source>
      <translation>Nieznane ustawienie - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="308"/>
      <source>Unknown setting</source>
      <translation>Nieznane ustawienie</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="312"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Błędna wartość liczby całkowitej ustawienia - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="314"/>
      <source>Bad integer value</source>
      <translation>Błędna wartość liczby całkowitej</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="318"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Ustawienie %1 nie jest liczbą całkowitą</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="320"/>
      <source>Setting is not of integer type</source>
      <translation>Ustawienie nie jest liczbą całkowitą</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="324"/>
      <source>Setting %1 is not of string type</source>
      <translation>Ustawienie %1 nie jest ciągiem znaków</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="326"/>
      <source>Setting is not of string type</source>
      <translation>Ustawienie nie jest ciągiem znaków</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="328"/>
      <source>Opening the configuration file failed</source>
      <translation>Nie udało się otworzyć pliku konfiguracyjnego</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="330"/>
      <source>The configuration file is malformed</source>
      <translation>Plik konfiguracyjny jest uszkodzony</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="332"/>
      <source>Fatal failure</source>
      <translation>Błąd krytyczny</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="334"/>
      <source>Unknown error</source>
      <translation>Nieznany błąd</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="50"/>
      <source>Product Name</source>
      <translation>Nazwa produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="63"/>
      <source>TextLabel</source>
      <translation>EtykietaTekstowa</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="79"/>
      <source>Long Product Description</source>
      <translation>Długi opis produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Wybór Pakietów</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Wybierz produkt z listy. Wybrany produkt zostanie zainstalowany.</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Name</source>
      <translation>Nazwa</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Description</source>
      <translation>Opis</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard model:</source>
      <translation>Model klawiatury:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="146"/>
      <source>Type here to test your keyboard</source>
      <translation>Napisz coś tutaj, aby sprawdzić swoją klawiaturę</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="153"/>
      <source>Switch Keyboard:</source>
      <extracomment>shortcut for switching between keyboard layouts</extracomment>
      <translation>Przełącz klawiaturę:</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Jak się nazywasz?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Twoja Pełne Imię</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Jakiego imienia chcesz używać do logowania się?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>login</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Jaka jest nazwa tego komputera?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Ta nazwa będzie używana, jeśli udostępnisz swój komputer w sieci.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Nazwa Komputera</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Wybierz hasło, aby chronić swoje konto.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Wpisz swoje hasło dwa razy, aby mieć pewność, że uniknąłeś literówek. Dobre hasło powinno zawierać mieszaninę liter, cyfr, znaków specjalnych; mieć przynajmniej 8 znaków i być regularnie zmieniane.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Powtórz Hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Gdy to pole jest zaznaczone, siła hasła zostanie zweryfikowana i nie będzie można użyć słabego hasła.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Wymagaj silnych haseł.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Zaloguj automatycznie bez proszenia o hasło.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Użyj tego samego hasła dla konta administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Wybierz hasło do konta administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Wpisz to samo hasło dwa razy, aby mieć pewność, że uniknąłeś literówek.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="178"/>
      <source>Root</source>
      <translation>Systemowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="182"/>
      <source>Home</source>
      <comment>@label</comment>
      <translation>Domowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="186"/>
      <source>Boot</source>
      <comment>@label</comment>
      <translation>Rozruchowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="191"/>
      <source>EFI system</source>
      <comment>@label</comment>
      <translation>System EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="195"/>
      <source>Swap</source>
      <comment>@label</comment>
      <translation>Przestrzeń wymiany</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="199"/>
      <source>New partition for %1</source>
      <comment>@label</comment>
      <translation>Nowa partycja dla %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
      <source>New partition</source>
      <comment>@label</comment>
      <translation>Nowa partycja</translation>
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
      <translation>Wolna powierzchnia</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="161"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="205"/>
      <source>New Partition</source>
      <comment>@title</comment>
      <translation>Nowa partycja</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>Name</source>
      <comment>@title</comment>
      <translation>Nazwa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>File System</source>
      <comment>@title</comment>
      <translation>System plików</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>File System Label</source>
      <comment>@title</comment>
      <translation>Etykieta Systemu Plików</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="313"/>
      <source>Mount Point</source>
      <comment>@title</comment>
      <translation>Punkt montowania</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="315"/>
      <source>Size</source>
      <comment>@title</comment>
      <translation>Rozmiar</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Urządzenie przecho&amp;wywania:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>P&amp;rzywróć do pierwotnego stanu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Nowa &amp;tablica partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Ut_wórz</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Edycja</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>U&amp;suń</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Nowa Grupa Woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>Zmień Rozmiar Grupy Woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>Dezaktywuj Grupę Woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>Usuń Grupę Woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Zainstaluj program rozruchowy </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="224"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Czy na pewno chcesz utworzyć nową tablicę partycji na %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="259"/>
      <source>Can not create new partition</source>
      <translation>Nie można utworzyć nowej partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="260"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>Tablica partycji na %1 ma już %2 podstawowych partycji i więcej nie może już być dodanych. Prosimy o usunięcie jednej partycji systemowej i dodanie zamiast niej partycji rozszerzonej.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="56"/>
      <source>Gathering system information…</source>
      <comment>@status</comment>
      <translation>Zbieranie informacji o systemie...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="107"/>
      <source>Partitions</source>
      <comment>@label</comment>
      <translation>Partycje</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="143"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system</source>
      <comment>@label</comment>
      <translation>Zainstaluj %1 &lt;strong&gt;obok&lt;/strong&gt; innego systemu operacyjnego</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="147"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Wyczyść&lt;/strong&gt; dysk i zainstaluj %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="151"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Zastąp&lt;/strong&gt; partycję poprzez %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="156"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Ręczne&lt;/strong&gt; partycjonowanie</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="178"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3)</source>
      <comment>@info</comment>
      <translation>Zainstaluj %1 &lt;strong&gt;obok&lt;/strong&gt; innego systemu operacyjnego na dysku &lt;strong&gt;%2&lt;/strong&gt; (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="187"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;Wyczyść&lt;/strong&gt; dysk &lt;strong&gt;%2&lt;/strong&gt; (%3) i zainstaluj %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="194"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;Zastąp&lt;/strong&gt; partycję na dysku &lt;strong&gt;%2&lt;/strong&gt; (%3) poprzez %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="203"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;Ręczne&lt;/strong&gt; partycjonowanie na dysku &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="213"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>Dysk &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="257"/>
      <source>Unsafe partition actions are enabled.</source>
      <translation>Niebezpieczne akcje partycji są włączone.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="260"/>
      <source>Partitioning is configured to &lt;b&gt;always&lt;/b&gt; fail.</source>
      <translation>Partycjonowanie jest skonfigurowane tak, aby &lt;b&gt;zawsze&lt;/b&gt; kończyło się niepowodzeniem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="263"/>
      <source>No partitions will be changed.</source>
      <translation>Żadne partycje nie zostaną zmienione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="303"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Bieżący:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="321"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Po:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="543"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a suitable filesystem.</source>
      <translation>Partycja systemowa EFI jest niezbędna do uruchomienia %1.&lt;br/&gt;&lt;br/&gt;Do skonfigurowania partycji systemowej EFI, cofnij się i wybierz lub utwórz odpowiedni system plików.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="549"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;The EFI system partition does not meet recommendations. It is recommended to go back and select or create a suitable filesystem.</source>
      <translation>Partycja systemowa EFI jest niezbędna do uruchomienia %1.&lt;br/&gt;&lt;br/&gt;Partycja systemowa EFI nie spełnia wymagań. Zalecane jest cofnięcie się i wybranie lub utworzenie odpowiedniego systemu plików.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="557"/>
      <source>The filesystem must be mounted on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>System plików musi zostać zamontowany w &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="558"/>
      <source>The filesystem must have type FAT32.</source>
      <translation>System plików musi być typu FAT32.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="559"/>
      <source>The filesystem must have flag &lt;strong&gt;%1&lt;/strong&gt; set.</source>
      <translation>System plików musi mieć ustawioną flagę &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="567"/>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="569"/>
      <source>The filesystem must be at least %1 MiB in size.</source>
      <translation>Rozmiar systemu plików musi wynosić co najmniej %1 MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="571"/>
      <source>The minimum recommended size for the filesystem is %1 MiB.</source>
      <translation>Minimalny zalecany rozmiar systemu plików to %1 MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="573"/>
      <source>You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Możesz kontynuować bez konfigurowania partycji systemowej EFI, ale uruchomienie systemu może się nie powieść.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="575"/>
      <source>You can continue with this EFI system partition configuration but your system may fail to start.</source>
      <translation>Możesz kontynuować konfigurację tej partycji systemowej EFI, ale system może się nie uruchomić.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="587"/>
      <source>No EFI system partition configured</source>
      <translation>Nie skonfigurowano partycji systemowej EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="595"/>
      <source>EFI system partition configured incorrectly</source>
      <translation>Partycja systemowa EFI skonfigurowana niepoprawnie</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="615"/>
      <source>EFI system partition recommendation</source>
      <translation>Zalecenie dotyczące partycji systemowej EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="634"/>
      <source>Option to use GPT on BIOS</source>
      <translation>Opcja korzystania z GPT w BIOS-ie</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="635"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;%2&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>Tabela partycji GPT jest najlepszą opcją dla wszystkich systemów. Ten instalator obsługuje taką konfigurację również dla systemów BIOS. &lt;br/&gt;&lt;br/&gt;Aby skonfigurować tabelę partycji GPT w systemie BIOS, (jeśli jeszcze tego nie zrobiono) cofnij się i ustaw tabelę partycji na GPT, a następnie utwórz niesformatowaną partycję o rozmiarze 8 MB z włączoną flagą &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt; Niesformatowana partycja 8 MB jest niezbędna do uruchomienia %1 w systemie BIOS z GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="657"/>
      <source>Boot partition not encrypted</source>
      <translation>Niezaszyfrowana partycja rozruchowa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="658"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Oddzielna partycja rozruchowa została skonfigurowana razem z zaszyfrowaną partycją roota, ale partycja rozruchowa nie jest szyfrowana.&lt;br/&gt;&lt;br/&gt;Nie jest to najbezpieczniejsze rozwiązanie, ponieważ ważne pliki systemowe znajdują się na niezaszyfrowanej partycji.&lt;br/&gt;Możesz kontynuować, ale odblokowywanie systemu nastąpi później, w trakcie uruchamiania.&lt;br/&gt;Aby zaszyfrować partycję rozruchową, wróć i utwórz ją ponownie zaznaczając opcję &lt;strong&gt;Szyfruj&lt;/strong&gt; w oknie tworzenia partycji.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="750"/>
      <source>has at least one disk device available.</source>
      <translation>jest dostępne co najmniej jedno urządzenie dyskowe.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="751"/>
      <source>There are no partitions to install on.</source>
      <translation>Brak partycji na których można dokonać instalacji.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Applying Plasma Look-and-Feel…</source>
      <comment>@status</comment>
      <translation>Zastosowywanie funkcji Plasma Look-and-Feel...</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Nie można wybrać pakietu Wygląd-i-Zachowanie Plasmy KDE</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="80"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Proszę wybrać wygląd i styl dla pulpitu KDE Plazma. Możesz również pominąć ten krok i skonfigurować je po zainstalowaniu systemu. Kliknięcie na wybranym wyglądzie i stylu spowoduje wyświetlenie ich podglądu na żywo.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="87"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Wybierz wygląd i styl pulpitu Plazmy KDE. Możesz również pominąć ten krok i skonfigurować wygląd po zainstalowaniu systemu. Kliknięcie przycisku wyboru wyglądu i stylu daje podgląd na żywo tego wyglądu i stylu.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <comment>@label</comment>
      <translation>Wygląd-i-Zachowanie</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="56"/>
      <source>Saving files for later…</source>
      <comment>@status</comment>
      <translation>Zapisywanie plików na później...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="64"/>
      <source>No files configured to save for later.</source>
      <translation>Nie skonfigurowano żadnych plików do zapisania na później.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="88"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Nie wszystkie pliki konfiguracyjne mogą być zachowane.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="301"/>
      <source>
There was no output from the command.</source>
      <translation>
W wyniku polecenia nie ma żadnego rezultatu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="302"/>
      <source>
Output:
</source>
      <translation>
Wyjście:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="307"/>
      <source>External command crashed.</source>
      <translation>Zewnętrzne polecenie zakończone niepowodzeniem.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="308"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Wykonanie polecenia &lt;i&gt;%1&lt;/i&gt; nie powiodło się.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="315"/>
      <source>External command failed to start.</source>
      <translation>Nie udało się uruchomić zewnętrznego polecenia.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="316"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Polecenie &lt;i&gt;%1&lt;/i&gt; nie zostało uruchomione.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="322"/>
      <source>Internal error when starting command.</source>
      <translation>Wystąpił wewnętrzny błąd podczas uruchamiania polecenia.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="323"/>
      <source>Bad parameters for process job call.</source>
      <translation>Błędne parametry wywołania zadania.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="329"/>
      <source>External command failed to finish.</source>
      <translation>Nie udało się ukończyć zewnętrznego polecenia.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="330"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Nie udało się ukończyć polecenia &lt;i&gt;%1&lt;/i&gt; w ciągu %2 sekund.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="338"/>
      <source>External command finished with errors.</source>
      <translation>Ukończono zewnętrzne polecenie z błędami.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="339"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Polecenie &lt;i&gt;%1&lt;/i&gt; zostało ukończone z błędem o kodzie %2.</translation>
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
      <translation>nieznany</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="35"/>
      <source>extended</source>
      <comment>@partition info</comment>
      <translation>rozszerzona</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="37"/>
      <source>unformatted</source>
      <comment>@partition info</comment>
      <translation>niesformatowany</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="39"/>
      <source>swap</source>
      <comment>@partition info</comment>
      <translation>przestrzeń wymiany</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="145"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="192"/>
      <source>Default</source>
      <translation>Domyślnie</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="101"/>
      <source>Directory not found</source>
      <translation>Katalog nie został znaleziony</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="102"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Nie można utworzyć nowego losowego pliku&lt;pre&gt;%1&lt;/pre&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="74"/>
      <source>No product</source>
      <translation>Brak produktu</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="82"/>
      <source>No description provided.</source>
      <translation>Brak opisu.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="44"/>
      <source>(no mount point)</source>
      <translation>(brak punktu montowania)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="39"/>
      <source>Unpartitioned space or unknown partition table</source>
      <comment>@info</comment>
      <translation>Przestrzeń bez partycji lub nieznana tabela partycji</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Ten komputer nie spełnia niektórych zalecanych wymagań dotyczących konfigurowania %&lt;br/&gt;
       Konfiguracja może być kontynuowana, ale niektóre funkcje mogą być wyłączone.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="32"/>
      <source>Removing live user from the target system…</source>
      <comment>@status</comment>
      <translation>Usuwanie aktywnego użytkownika z systemu docelowego...</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="38"/>
      <source>Removing Volume Group named %1…</source>
      <comment>@status</comment>
      <translation>Usuwanie grupy woluminów o nazwie %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="32"/>
      <source>Removing Volume Group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Usuwanie grupy woluminów o nazwie &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Instalator nie mógł usunąć grupy woluminów o nazwie %1</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="37"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Ten komputer nie spełnia minimalnych wymagań dotyczących instalacji %1. &lt;br/&gt;
         Nie można kontynuować instalacji.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="39"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Ten komputer nie spełnia niektórych zalecanych wymagań dotyczących konfigurowania %&lt;br/&gt;
       Konfiguracja może być kontynuowana, ale niektóre funkcje mogą być wyłączone.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="43"/>
      <source>Performing file system resize…</source>
      <comment>@status</comment>
      <translation>Zmiana rozmiaru systemu plików...</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="162"/>
      <source>Invalid configuration</source>
      <comment>@error</comment>
      <translation>Nieprawidłowa konfiguracja</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="163"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <comment>@error</comment>
      <translation>Zadanie zmiany rozmiaru systemu plików ma nieprawidłową konfigurację 
i nie uruchomi się</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>KPMCore not available</source>
      <comment>@error</comment>
      <translation>KPMCore nie jest dostępne</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>Calamares cannot start KPMCore for the file system resize job.</source>
      <comment>@error</comment>
      <translation>Calamares nie może uruchomić KPMCore dla zadania zmiany rozmiaru systemu plików.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="179"/>
      <source>Resize failed.</source>
      <comment>@error</comment>
      <translation>Nieudana zmiana rozmiaru.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="181"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>System plików %1 nie mógł być znaleziony w tym systemie i nie może być zmieniony rozmiar</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="182"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>Urządzenie %1 nie mogło być znalezione w tym systemie i zmiana rozmiaru jest nie dostępna</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="189"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="201"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="212"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="231"/>
      <source>Resize Failed</source>
      <comment>@error</comment>
      <translation>Nieudana zmiana rozmiaru</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="191"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="203"/>
      <source>The filesystem %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>Zmiana rozmiaru w systemie plików %1 niedostępna</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="192"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="204"/>
      <source>The device %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>Zmiana rozmiaru w urządzeniu %1 niedostępna</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <source>The file system %1 must be resized, but cannot.</source>
      <comment>@info</comment>
      <translation>Wymagana zmiana rozmiaru w systemie plików %1 , ale nie jest ona możliwa.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The device %1 must be resized, but cannot</source>
      <comment>@info</comment>
      <translation>Wymagana zmiana rozmiaru w urządzeniu %1 , ale jest niedostępna</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="39"/>
      <source>Resize partition %1</source>
      <comment>@title</comment>
      <translation>Zmień rozmiar partycji %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="45"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Zmień rozmiar partycji &lt;strong&gt;%2MiB&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; na &lt;strong&gt;%3MiB&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="54"/>
      <source>Resizing %2MiB partition %1 to %3MiB…</source>
      <comment>@status</comment>
      <translation>Zmiana rozmiaru partycji %2MiB %1 na %3MiB...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="70"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Instalator nie mógł zmienić rozmiaru partycji %1 na dysku '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <comment>@title</comment>
      <translation>Zmień Rozmiar Grupy Woluminów</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="28"/>
      <source>Resize volume group named %1 from %2 to %3</source>
      <comment>@title</comment>
      <translation>Zmień rozmiar grupy woluminów o nazwie %1 z %2 na %3</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Zmień rozmiar grupy woluminów o nazwie &lt;strong&gt;%1&lt;/strong&gt; z &lt;strong&gt;%2&lt;/strong&gt; na &lt;strong&gt;%3&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="47"/>
      <source>Resizing volume group named %1 from %2 to %3…</source>
      <comment>@status</comment>
      <translation>Zmiana rozmiaru grupy woluminów o nazwie %1 z %2 na %3...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="58"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Instalator nie mógł zmienić rozmiaru grupy woluminów o nazwie %1</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="47"/>
      <source>Checking requirements again in a few seconds ...</source>
      <translation>Ponowne sprawdzanie wymagań za kilka sekund...</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Scanning storage devices…</source>
      <comment>@status</comment>
      <translation>Skanowanie urządzeń magazynujących...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Partitioning…</source>
      <comment>@status</comment>
      <translation>Partycjonowanie...</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="36"/>
      <source>Set hostname %1</source>
      <translation>Ustaw nazwę komputera %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="42"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Ustaw nazwę komputera &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="48"/>
      <source>Setting hostname %1…</source>
      <comment>@status</comment>
      <translation>Ustawianie nazwy hosta %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="121"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="128"/>
      <source>Internal Error</source>
      <translation>Błąd wewnętrzny</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="139"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="156"/>
      <source>Cannot write hostname to target system</source>
      <translation>Nie można zapisać nazwy komputera w docelowym systemie</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="66"/>
      <source>Setting keyboard model to %1, layout as %2-%3…</source>
      <comment>@status, %1 model, %2 layout, %3 variant</comment>
      <translation>Ustawienie modelu klawiatury na %1, z układem %2-%3...</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <comment>@error</comment>
      <translation>Błąd zapisu konfiguracji klawiatury dla konsoli wirtualnej.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is virtual console configuration path</comment>
      <translation>Nie można zapisać do %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="394"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <comment>@error</comment>
      <translation>Błąd zapisu konfiguracji klawiatury dla X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="395"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is keyboard configuration path</comment>
      <translation>Nie można zapisać do %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="411"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <comment>@error</comment>
      <translation>Błąd zapisu konfiguracji układu klawiatury dla istniejącego katalogu /etc/default.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="412"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is default keyboard path</comment>
      <translation>Nie można zapisać do %1</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="44"/>
      <source>Set flags on partition %1</source>
      <comment>@title</comment>
      <translation>Ustaw flagi na partycji %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="50"/>
      <source>Set flags on %1MiB %2 partition</source>
      <comment>@title</comment>
      <translation>Ustaw flagi na partycji %1MiB %2</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="54"/>
      <source>Set flags on new partition</source>
      <comment>@title</comment>
      <translation>Ustaw flagi na nowej partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Usuń flagi z partycji &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition</source>
      <comment>@info</comment>
      <translation>Usuń flagi z partycji %1MiB &lt;strong&gt;%2&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition</source>
      <comment>@info</comment>
      <translation>Usuń flagi z nowej partycji</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Set flags on partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Ustaw flagi na partycji &lt;strong&gt;%1&lt;/strong&gt; jako &lt;strong&gt;%2&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="88"/>
      <source>Set flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Ustaw flagi na partycji %1MiB &lt;strong&gt;%2&lt;/strong&gt; jako &lt;strong&gt;%3&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="94"/>
      <source>Set flags on new partition to &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Ustaw flagi na nowej partycji &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Usuwanie flag z partycji &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="112"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation>Usuwanie flag z partycji %1MiB &lt;strong&gt;%2&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on new partition…</source>
      <comment>@status</comment>
      <translation>Usuwanie flag z nowej partycji...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="122"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>Ustawianie flag &lt;strong&gt;%2&lt;/strong&gt; na partycji &lt;strong&gt;%1&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="130"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation>Ustawienie flag &lt;strong&gt;%3&lt;/strong&gt; na partycji %1MiB &lt;strong&gt;%2&lt;/strong&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="136"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition…</source>
      <comment>@status</comment>
      <translation>Ustawianie flag &lt;strong&gt;%1&lt;/strong&gt; na nowej partycji...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Instalator nie mógł ustawić flag na partycji %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="38"/>
      <source>Set password for user %1</source>
      <translation>Ustaw hasło dla użytkownika %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="44"/>
      <source>Setting password for user %1…</source>
      <comment>@status</comment>
      <translation>Ustawianie hasła użytkownika %1...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="80"/>
      <source>Bad destination system path.</source>
      <translation>Błędna ścieżka docelowa systemu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>rootMountPoint is %1</source>
      <translation>Punkt montowania / to %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>Cannot disable root account.</source>
      <translation>Nie można wyłączyć konta administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="108"/>
      <source>usermod terminated with error code %1.</source>
      <translation>Polecenie usermod przerwane z kodem błędu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>Cannot set password for user %1.</source>
      <translation>Nie można ustawić hasła dla użytkownika %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="32"/>
      <source>Setting timezone to %1/%2…</source>
      <comment>@status</comment>
      <translation>Ustawianie strefy czasowej na %1/%2…</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="60"/>
      <source>Cannot access selected timezone path.</source>
      <comment>@error</comment>
      <translation>Brak dostępu do wybranej ścieżki strefy czasowej.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="61"/>
      <source>Bad path: %1</source>
      <comment>@error</comment>
      <translation>Niepoprawna ścieżka: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="79"/>
      <source>Cannot set timezone.</source>
      <comment>@error</comment>
      <translation>Nie można ustawić strefy czasowej.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <comment>@info</comment>
      <translation>Błąd tworzenia dowiązania, cel: %1; nazwa dowiązania: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot open /etc/timezone for writing</source>
      <comment>@info</comment>
      <translation>Nie można otworzyć /etc/timezone celem zapisu</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="181"/>
      <source>Preparing groups…</source>
      <comment>@status</comment>
      <translation>Przygotowywanie grup...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="193"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="198"/>
      <source>Could not create groups in target system</source>
      <translation>Nie można utworzyć grup w systemie docelowym</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="199"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>W systemie docelowym brakuje tych grup: %1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="34"/>
      <source>Configuring &lt;pre&gt;sudo&lt;/pre&gt; users…</source>
      <comment>@status</comment>
      <translation>Konfigurowanie użytkowników &lt;pre&gt;sudo&lt;/pre&gt;...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="70"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Nie można wykonać chmod na pliku sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="75"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Nie można utworzyć pliku sudoers z możliwością zapisu.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="38"/>
      <source>Running shell processes…</source>
      <comment>@status</comment>
      <translation>Uruchamianie procesów powłoki...</translation>
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
      <translation>&amp;Tak</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="25"/>
      <source>&amp;No</source>
      <translation>&amp;Nie</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="26"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Anuluj</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="27"/>
      <source>&amp;Close</source>
      <translation>Zam&amp;knij</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <source>Installation feedback</source>
      <translation>Informacja zwrotna o instalacji</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Sending installation feedback…</source>
      <comment>@status</comment>
      <translation>Przesyłanie informacji zwrotnych dotyczących instalacji...</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Internal error in install-tracking.</source>
      <translation>Błąd wewnętrzny śledzenia instalacji.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="125"/>
      <source>HTTP request timed out.</source>
      <translation>Wyczerpano limit czasu żądania HTTP.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="192"/>
      <source>KDE user feedback</source>
      <translation>Opinie użytkowników KDE</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="198"/>
      <source>Configuring KDE user feedback…</source>
      <comment>@status</comment>
      <translation>Konfigurowanie informacji zwrotnej użytkowników KDE...</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="220"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="228"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>Błąd w konfiguracji opinii użytkowników KDE.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="221"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>Nie można poprawnie skonfigurować opinii użytkowników KDE, błąd skryptu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="229"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>Nie można poprawnie skonfigurować opinii użytkowników KDE, błąd Calamares %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="135"/>
      <source>Machine feedback</source>
      <translation>Maszynowa informacja zwrotna</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="141"/>
      <source>Configuring machine feedback…</source>
      <comment>@status</comment>
      <translation>Konfiguracja informacji zwrotnej...</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="164"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="173"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Błąd w konfiguracji maszynowej informacji zwrotnej.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="166"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Nie można poprawnie skonfigurować maszynowej informacji zwrotnej, błąd skryptu %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="175"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Nie można poprawnie skonfigurować maszynowej informacji zwrotnej, błąd Calamares %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Symbol zastępczy</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Kliknij tutaj, aby wysłać &lt;span style=" font-weight:600;"&gt;bez jakichkolwiek informacji&lt;/span&gt; o instalacji&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Naciśnij, aby dowiedzieć się więcej o uzyskiwaniu informacji zwrotnych.&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>Śledzenie pomaga %1 zobaczyć, jak często jest instalowany, na jakim sprzęcie jest zainstalowany i jakie aplikacje są używane. Aby zobaczyć, co zostanie wysłane, kliknij ikonę pomocy obok każdego obszaru.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Wybierając tę opcję, wyślesz informacje o instalacji i sprzęcie. Informacje te zostaną wysłane &lt;b&gt;tylko raz&lt;/b&gt; po zakończeniu instalacji.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Wybierając tę opcję, będziesz okresowo wysyłać informacje o instalacji &lt;b&gt;maszyny&lt;/b&gt;, sprzęcie i aplikacjach do %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Wybierając tę opcję, będziesz regularnie wysyłać informacje o instalacji &lt;b&gt;użytkownika&lt;/b&gt;, sprzęcie, aplikacjach i wzorcach użycia aplikacji do %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <comment>@title</comment>
      <translation>Informacje zwrotne</translation>
    </message>
  </context>
  <context>
    <name>UmountJob</name>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="39"/>
      <source>Unmounting file systems…</source>
      <comment>@status</comment>
      <translation>Odmontowywanie systemu plików...</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="123"/>
      <source>No target system available.</source>
      <translation>Brak dostępnego systemu docelowego.</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="131"/>
      <source>No rootMountPoint is set.</source>
      <translation>Brak ustawionego punktu montowania /.</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="189"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jeśli z tego komputera będzie korzystać więcej niż jedna osoba, po skonfigurowaniu można utworzyć wiele kont.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="195"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Jeśli z tego komputera będzie korzystać więcej niż jedna osoba, po instalacji można utworzyć wiele kont.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="35"/>
      <source>Users</source>
      <translation>Użytkownicy</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Użytkownicy</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Klucz</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Wartość</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Utwórz grupę woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Lista fizycznych woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Nazwa Grupy Woluminów :</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Typ Grupy Woluminów</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Rozmiar fizycznego rozszerzenia:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation> MB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Łączny Rozmiar :</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Użyty rozmiar:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Łącznie Sektorów :</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>Ilość Grup Woluminów :</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Wybierz język aplikacji i systemu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>Open donations website</source>
      <translation>Otwórz stronę darowizn</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="143"/>
      <source>&amp;Donate</source>
      <translation>Przekaż &amp;darowiznę</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>Open help and support website</source>
      <translation>Otwórz witrynę pomocy i obsługi technicznej</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
      <source>&amp;Support</source>
      <translation>&amp;Wsparcie</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Otwórz stronę do zgłaszania i śledzenia błędów</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="169"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Znane problemy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>Open release notes website</source>
      <translation>Otwórz witrynę informacji o wersji</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="182"/>
      <source>&amp;Release notes</source>
      <translation>Informacje o &amp;wydaniu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="235"/>
      <source>About %1 Setup</source>
      <comment>@title</comment>
      <translation>Informacje o konfiguratorze %1 </translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="236"/>
      <source>About %1 Installer</source>
      <comment>@title</comment>
      <translation> Informacje o instalatorze %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="212"/>
      <source>%1 Support</source>
      <comment>@action</comment>
      <translation>Wsparcie %1</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="40"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Witamy</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="46"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Witamy</translation>
    </message>
  </context>
  <context>
    <name>ZfsJob</name>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="102"/>
      <source>Creating ZFS pools and datasets…</source>
      <comment>@status</comment>
      <translation>Tworzenie pul i zestawów danych ZFS...</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="162"/>
      <source>Failed to create zpool on </source>
      <translation>Nie można utworzyć zpool na</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="180"/>
      <source>Configuration Error</source>
      <translation>Błąd konfiguracji</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="181"/>
      <source>No partitions are available for ZFS.</source>
      <translation>Żadne partycje nie są dostępne dla ZFS.</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <source>Internal data missing</source>
      <translation>Brak danych wewnętrznych</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="264"/>
      <source>Failed to create zpool</source>
      <translation>Nie udało się utworzyć zpool</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="336"/>
      <source>Failed to create dataset</source>
      <translation>Nie można utworzyć zestawu danych</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="337"/>
      <source>The output was: </source>
      <translation>Wynik był następujący:</translation>
    </message>
  </context>
  <context>
    <name>calamares-sidebar</name>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="89"/>
      <source>About</source>
      <translation>O nas</translation>
    </message>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="115"/>
      <source>Debug</source>
      <translation>Debug</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="157"/>
      <source>About</source>
      <comment>@button</comment>
      <translation>O nas</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="159"/>
      <source>Show information about Calamares</source>
      <comment>@tooltip</comment>
      <translation>Pokaż informacje o Calamares</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="173"/>
      <source>Debug</source>
      <comment>@button</comment>
      <translation>Debug</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="175"/>
      <source>Show debug information</source>
      <comment>@tooltip</comment>
      <translation>Pokaż informacje debugowania</translation>
    </message>
  </context>
  <context>
    <name>finishedq</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>Instalacja została zakończona</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <translation>%1 został zainstalowany na komputerze&lt;br/&gt;
            Możesz teraz ponownie uruchomić nowy system lub kontynuować korzystanie ze środowiska Live.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="65"/>
      <source>Close Installer</source>
      <translation>Zamknij instalator</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="71"/>
      <source>Restart System</source>
      <translation>Uruchom ponownie system</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Pełny dziennik instalacji jest dostępny jako installation.log w katalogu domowym użytkownika Live.&lt;br/&gt;
            Ten dziennik jest kopiowany do /var/log/installation.log systemu docelowego.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>finishedq-qt6</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="35"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Instalacja została zakończona</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="42"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>%1 został zainstalowany na komputerze&lt;br/&gt;
            Możesz teraz ponownie uruchomić nowy system lub kontynuować korzystanie ze środowiska Live.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="65"/>
      <source>Close Installer</source>
      <comment>@button</comment>
      <translation>Zamknij instalator</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="71"/>
      <source>Restart System</source>
      <comment>@button</comment>
      <translation>Uruchom ponownie system</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <comment>@info</comment>
      <translation>&lt;p&gt;Pełny dziennik instalacji jest dostępny jako installation.log w katalogu domowym użytkownika Live.&lt;br/&gt;
            Ten dziennik jest kopiowany do /var/log/installation.log systemu docelowego.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>finishedq@mobile</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="36"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Instalacja została zakończona</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart your device.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>%1 został zainstalowany na komputerze.&lt;br/&gt;
            Możesz teraz ponownie uruchomić urządzenie.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="66"/>
      <source>Close</source>
      <comment>@button</comment>
      <translation>Zamknij</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="72"/>
      <source>Restart</source>
      <comment>@button</comment>
      <translation>Uruchom ponownie</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Wybierz układ, aby aktywować podgląd klawiatury</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Model klawiatury:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Układ</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Wariant</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Napisz coś tutaj, aby sprawdzić swoją klawiaturę...</translation>
    </message>
  </context>
  <context>
    <name>keyboardq-qt6</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Wybierz układ, aby aktywować podgląd klawiatury</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Model klawiatury:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Układ</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Wariant</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Napisz coś tutaj, aby sprawdzić swoją klawiaturę...</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Zmień</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Języki&lt;/h3&gt; &lt;/br&gt;
                     Ustawienia regionalne systemu wpływają na język i zestaw znaków dla niektórych elementów interfejsu użytkownika wiersza polecenia. Bieżące ustawienie to &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Ustawienia regionalne&lt;/h3&gt; &lt;/br&gt;
                    Systemowe ustawienia regionalne wpływają na format liczb i dat. Bieżące ustawienie to&lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
  </context>
  <context>
    <name>localeq-qt6</name>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Zmień</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Języki&lt;/h3&gt; &lt;/br&gt;
                     Ustawienia regionalne systemu wpływają na język i zestaw znaków dla niektórych elementów interfejsu użytkownika wiersza polecenia. Bieżące ustawienie to &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Ustawienia regionalne&lt;/h3&gt; &lt;/br&gt;
                    Systemowe ustawienia regionalne wpływają na format liczb i dat. Bieżące ustawienie to&lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Są to przykładowe informacje o wersji.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice to potężny i darmowy pakiet biurowy, z którego korzystają miliony ludzi na całym świecie. Zawiera kilka aplikacji, które czynią go najbardziej wszechstronnym pakietem biurowym, wolnym oraz o otwartym kodzie źródłowym, na rynku.&lt;br/&gt;
                    Opcja domyślna.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Jeśli nie chcesz instalować pakietu biurowego, po prostu wybierz pozycję "bez pakietu biurowego". Zawsze możesz dodać jeden (lub więcej) później do zainstalowanego systemu, gdy nadejdzie potrzeba.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Bez pakietu biurowego</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>Utwórz minimalną instalację pulpitu, usuń wszystkie dodatkowe aplikacje i zdecyduj później, co chcesz dodać do swojego systemu. Przykłady tego, czego nie będzie w takiej instalacji, nie będzie pakietu biurowego, odtwarzaczy multimedialnych, przeglądarki obrazów ani obsługi druku. Będzie to tylko pulpit, przeglądarka plików, menedżer pakietów, edytor tekstu i prosta przeglądarka internetowa.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimalna instalacja</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>Wybierz opcję instalacji lub użyj domyślnej: LibreOffice w zestawie.</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq-qt6</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice to potężny i darmowy pakiet biurowy, z którego korzystają miliony ludzi na całym świecie. Zawiera kilka aplikacji, które czynią go najbardziej wszechstronnym pakietem biurowym, wolnym oraz o otwartym kodzie źródłowym, na rynku.&lt;br/&gt;
                    Opcja domyślna.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Jeśli nie chcesz instalować pakietu biurowego, po prostu wybierz pozycję "bez pakietu biurowego". Zawsze możesz dodać jeden (lub więcej) później do zainstalowanego systemu, gdy nadejdzie potrzeba.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Bez pakietu biurowego</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>Utwórz minimalną instalację pulpitu, usuń wszystkie dodatkowe aplikacje i zdecyduj później, co chcesz dodać do swojego systemu. Przykłady tego, czego nie będzie w takiej instalacji, nie będzie pakietu biurowego, odtwarzaczy multimedialnych, przeglądarki obrazów ani obsługi druku. Będzie to tylko pulpit, przeglądarka plików, menedżer pakietów, edytor tekstu i prosta przeglądarka internetowa.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimalna instalacja</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>Wybierz opcję instalacji lub użyj domyślnej: LibreOffice w zestawie.</translation>
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
            &lt;p&gt;Jest to przykładowy plik QML, pokazujący opcje w RichText z zawartością flickable.&lt;/p&gt;

            &lt;p&gt;QML z RichText może używać znaczników HTML, zawartość Flickable jest przydatna na ekranach dotykowych.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;To jest pogrubiony tekst&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;To jest kursywa&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;To jest tekst podkreślony&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Ten tekst będzie wyrównany do środka.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;To jest przekreślenie&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Przykład kodu:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Lists:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU systems&lt;/li&gt;
                &lt;li&gt;AMD CPU systems&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Pionowy pasek przewijania jest regulowany, aktualna szerokość ustawiona na 10.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>Wstecz</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="43"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Wybierz swoją nazwę użytkownika i poświadczenia, aby się zalogować i wykonywać zadania administracyjne</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="56"/>
      <source>What is your name?</source>
      <translation>Jak się nazywasz?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="63"/>
      <source>Your full name</source>
      <translation>Twoje Imię i Nazwisko</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Jakiego imienia chcesz używać do logowania się?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login name</source>
      <translation>Login</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="116"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Jeśli więcej niż jedna osoba będzie korzystać z tego komputera, po instalacji można utworzyć wiele kont.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="129"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Dozwolone są tylko małe litery, cyfry, podkreślenia i łączniki.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="138"/>
      <source>root is not allowed as username.</source>
      <translation>root nie jest dozwolony jako nazwa użytkownika.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="147"/>
      <source>What is the name of this computer?</source>
      <translation>Jaka jest nazwa tego komputera?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="153"/>
      <source>Computer name</source>
      <translation>Nazwa komputera</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="180"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Ta nazwa będzie używana, jeśli komputer będzie widoczny dla innych osób w sieci.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="193"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>Dozwolone są tylko litery, cyfry, podkreślenia i łączniki, co najmniej dwa znaki.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="202"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost nie jest dozwolony jako nazwa hosta.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="211"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Wybierz hasło, aby chronić swoje konto.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="221"/>
      <source>Password</source>
      <translation>Hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="238"/>
      <source>Repeat password</source>
      <translation>Powtórz hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="265"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Wprowadź to samo hasło dwa razy, aby można je było sprawdzić pod kątem błędów. Dobre hasło będzie zawierało litery, cyfry i znaki interpunkcyjne, powinno mieć co najmniej osiem znaków i być zmieniane w regularnych odstępach czasu.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="297"/>
      <source>Reuse user password as root password</source>
      <translation>Użyj ponownie hasła użytkownika jako hasła root'a</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="305"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Użyj tego samego hasła dla konta administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Wybierz hasło root'a, aby zapewnić bezpieczeństwo swojego konta.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="328"/>
      <source>Root password</source>
      <translation>Hasło roota</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="346"/>
      <source>Repeat root password</source>
      <translation>Powtórz hasło roota</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="372"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Wprowadź to samo hasło dwa razy, aby można je było sprawdzić jego ewentualne błędy.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="402"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Zaloguj się automatycznie bez pytania o hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="410"/>
      <source>Validate passwords quality</source>
      <translation>Sprawdzanie jakości haseł</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="420"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Gdy to pole jest zaznaczone, siła hasła zostanie zweryfikowana i nie będzie można użyć słabego hasła.</translation>
    </message>
  </context>
  <context>
    <name>usersq-qt6</name>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="42"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Wybierz swoją nazwę użytkownika i poświadczenia, aby się zalogować i wykonywać zadania administracyjne</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="55"/>
      <source>What is your name?</source>
      <translation>Jak się nazywasz?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="62"/>
      <source>Your full name</source>
      <translation>Twoje Imię i Nazwisko</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="79"/>
      <source>What name do you want to use to log in?</source>
      <translation>Jakiego imienia chcesz używać do logowania się?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="86"/>
      <source>Login name</source>
      <translation>Login</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="115"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Jeśli więcej niż jedna osoba będzie korzystać z tego komputera, po instalacji można utworzyć wiele kont.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="128"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Dozwolone są tylko małe litery, cyfry, podkreślenia i łączniki.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="137"/>
      <source>root is not allowed as username.</source>
      <translation>root nie jest dozwolony jako nazwa użytkownika.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="146"/>
      <source>What is the name of this computer?</source>
      <translation>Jaka jest nazwa tego komputera?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="152"/>
      <source>Computer name</source>
      <translation>Nazwa komputera</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="179"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Ta nazwa będzie używana, jeśli komputer będzie widoczny dla innych osób w sieci.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="192"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>Dozwolone są tylko litery, cyfry, podkreślenia i łączniki, co najmniej dwa znaki.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="201"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost nie jest dozwolony jako nazwa hosta.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="210"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Wybierz hasło, aby chronić swoje konto.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="220"/>
      <source>Password</source>
      <translation>Hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="237"/>
      <source>Repeat password</source>
      <translation>Powtórz hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="264"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Wprowadź to samo hasło dwa razy, aby można je było sprawdzić pod kątem błędów. Dobre hasło będzie zawierało litery, cyfry i znaki interpunkcyjne, powinno mieć co najmniej osiem znaków i być zmieniane w regularnych odstępach czasu.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="296"/>
      <source>Reuse user password as root password</source>
      <translation>Użyj ponownie hasła użytkownika jako hasła root'a</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="304"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Użyj tego samego hasła dla konta administratora.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="317"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Wybierz hasło root'a, aby zapewnić bezpieczeństwo swojego konta.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="327"/>
      <source>Root password</source>
      <translation>Hasło roota</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="345"/>
      <source>Repeat root password</source>
      <translation>Powtórz hasło roota</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="371"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Wprowadź to samo hasło dwa razy, aby można je było sprawdzić jego ewentualne błędy.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="401"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Zaloguj się automatycznie bez pytania o hasło</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="409"/>
      <source>Validate passwords quality</source>
      <translation>Sprawdzanie jakości haseł</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="419"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Gdy to pole jest zaznaczone, siła hasła zostanie zweryfikowana i nie będzie można użyć słabego hasła.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Witaj w instalatorze %1&lt;quote&gt;%2&lt;/quote&gt;&lt;/h3&gt;
             &lt;p&gt;Ten program zapyta cię o kilka rzeczy i ustawi %1 na twoim komputerze.&lt;/p&gt; </translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="69"/>
      <source>Support</source>
      <translation>Wsparcie</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Znane błędy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Informacje o wydaniu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="103"/>
      <source>Donate</source>
      <translation>Przekaż darowiznę</translation>
    </message>
  </context>
  <context>
    <name>welcomeq-qt6</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;Witaj w instalatorze %1&lt;quote&gt;%2&lt;/quote&gt;&lt;/h3&gt;
             &lt;p&gt;Ten program zapyta cię o kilka rzeczy i ustawi %1 na twoim komputerze.&lt;/p&gt; </translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="69"/>
      <source>Support</source>
      <translation>Wsparcie</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Znane błędy</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Informacje o wydaniu</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="103"/>
      <source>Donate</source>
      <translation>Przekaż darowiznę</translation>
    </message>
  </context>
</TS>

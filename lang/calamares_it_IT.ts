<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="it_IT" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="71"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>L'&lt;strong&gt;ambiente di avvio&lt;/strong&gt; di questo sistema. &lt;br&gt;&lt;br&gt;I vecchi sistemi x86 supportano solo &lt;strong&gt;BIOS&lt;/strong&gt;. &lt;bt&gt;I sistemi moderni normalmente usano &lt;strong&gt;EFI&lt;/strong&gt; ma possono anche apparire come sistemi BIOS se avviati in modalità compatibile.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="81"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Il sistema è stato avviato con un ambiente di boot &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Per configurare l'avvio da un ambiente EFI, il programma d'installazione deve inserire un boot loader come &lt;strong&gt;GRUB&lt;/strong&gt; o &lt;strong&gt;systemd-boot&lt;/strong&gt; su una &lt;strong&gt;EFI System Partition&lt;/strong&gt;. Ciò avviene automaticamente, a meno che non si scelga il partizionamento manuale che permette di scegliere un proprio boot loader personale.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="93"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>ll sistema è stato avviato con un ambiente di boot &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Per configurare l'avvio da un ambiente BIOS, il programma d'installazione deve installare un boot loader come &lt;strong&gt;GRUB&lt;/strong&gt; all'inizio di una partizione o nel &lt;strong&gt;Master Boot Record&lt;/strong&gt; vicino all'origine della tabella delle partizioni (preferito). Ciò avviene automaticamente, a meno che non si scelga il partizionamento manuale che permette di fare una configurazione personale.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="70"/>
      <source>Master Boot Record of %1</source>
      <translation>Master Boot Record di %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="104"/>
      <source>Boot Partition</source>
      <translation>Partizione di avvio</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="109"/>
      <source>System Partition</source>
      <translation>Partizione di sistema</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="139"/>
      <source>Do not install a boot loader</source>
      <translation>Non installare un boot loader</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="156"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="70"/>
      <source>Blank Page</source>
      <translation>Pagina Vuota</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="24"/>
      <source>GlobalStorage</source>
      <translation>GlobalStorage</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="34"/>
      <source>JobQueue</source>
      <translation>JobQueue</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="44"/>
      <source>Modules</source>
      <translation>Moduli</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="57"/>
      <source>Type:</source>
      <translation>Tipo:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="64"/>
      <location filename="../src/calamares/DebugWindow.ui" line="78"/>
      <source>none</source>
      <translation>nessuna</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="71"/>
      <source>Interface:</source>
      <translation>Interfaccia:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="93"/>
      <source>Tools</source>
      <translation>Strumenti</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="106"/>
      <source>Reload Stylesheet</source>
      <translation>Ricarica il foglio di stile</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="113"/>
      <source>Widget Tree</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="231"/>
      <source>Debug information</source>
      <translation>Informazioni di debug</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="120"/>
      <source>Set up</source>
      <translation>Installazione</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="120"/>
      <source>Install</source>
      <translation>Installa</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="39"/>
      <source>Job failed (%1)</source>
      <translation>Operazione fallita (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="40"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="118"/>
      <source>Done</source>
      <translation>Fatto</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="27"/>
      <source>Example job (%1)</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source>Run command '%1' in target system.</source>
      <translation>Esegui il comando '%1' sul sistema di destinazione</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source> Run command '%1'.</source>
      <translation>Esegui il comando '1%'</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="59"/>
      <source>Running command %1 %2</source>
      <translation>Comando in esecuzione %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="208"/>
      <source>Running %1 operation.</source>
      <translation>Operazione %1 in esecuzione.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="225"/>
      <source>Bad working directory path</source>
      <translation>Il percorso della cartella corrente non è corretto</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="226"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>La cartella corrente %1 per l'attività di Python %2 non è accessibile.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="232"/>
      <source>Bad main script file</source>
      <translation>File dello script principale non valido</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Il file principale dello script %1 per l'attività di python %2 non è accessibile.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="311"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Errore da Boost.Python nell'operazione "%1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message numerus="yes">
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="166"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>In attesa del(i) modulo(i) %n.</numerusform>
        <numerusform>In attesa del(i) modulo(i) %n.</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="167"/>
      <source>(%n second(s))</source>
      <translation type="unfinished">
        <numerusform/>
        <numerusform/>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="172"/>
      <source>System-requirements checking is complete.</source>
      <translation>Il controllo dei requisiti di sistema è completo.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="93"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="407"/>
      <source>&amp;Back</source>
      <translation>&amp;Indietro</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="95"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="402"/>
      <source>&amp;Next</source>
      <translation>&amp;Avanti</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="97"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="427"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Annulla</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="391"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Annulla l'installazione senza modificare il computer</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Annullare l'installazione senza modificare il sistema.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>Setup Failed</source>
      <translation>Installazione fallita</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="197"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Vuoi incollare il log di installazione nel web?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="235"/>
      <source>Install Log Paste URL</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="238"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="254"/>
      <source>Calamares Initialization Failed</source>
      <translation>Inizializzazione di Calamares Fallita</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="255"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 non può essere installato. Calamares non è stato in grado di caricare tutti i moduli configurati. Questo è un problema del modo in cui Calamares viene utilizzato dalla distribuzione.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="261"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Non è stato possibile caricare il seguente modulo:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="322"/>
      <source>Continue with installation?</source>
      <translation>Continuare l'installazione?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="324"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Il %1 programma di installazione sta per fare dei cambiamenti sul tuo disco per installare %2. Non sarà possibile annullare questi cambiamenti.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Installa adesso</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="386"/>
      <source>&amp;Set up</source>
      <translation>&amp;Installazione</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="386"/>
      <source>&amp;Install</source>
      <translation>&amp;Installa</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="388"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Installazione completata. Chiudere il programma di installazione.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="487"/>
      <source>Cancel setup?</source>
      <translation>Annullare l'installazione?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="487"/>
      <source>Cancel installation?</source>
      <translation>Annullare l'installazione?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="488"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Vuoi davvero annullare il processo di installazione? Il programma di installazione verrrà terminato e tutti i cambiamenti verranno persi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="490"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Si vuole davvero annullare l'installazione in corso?
Il programma d'installazione sarà terminato e tutte le modifiche andranno perse.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="217"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="494"/>
      <source>&amp;Yes</source>
      <translation>&amp;Si</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>&amp;No</source>
      <translation>&amp;No</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="224"/>
      <source>&amp;Close</source>
      <translation>&amp;Chiudi</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="322"/>
      <source>Continue with setup?</source>
      <translation>Procedere con la configurazione?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Il programma d'nstallazione %1 sta per eseguire delle modifiche al tuo disco per poter installare %2.&lt;br/&gt;&lt;strong&gt; Non sarà possibile annullare tali modifiche.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>&amp;Install now</source>
      <translation>&amp;Installa adesso</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="337"/>
      <source>Go &amp;back</source>
      <translation>&amp;Indietro</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="412"/>
      <source>&amp;Done</source>
      <translation>&amp;Fatto</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="389"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>L'installazione è terminata. Chiudere il programma d'installazione.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="210"/>
      <source>Error</source>
      <translation>Errore</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>Installation Failed</source>
      <translation>Installazione non riuscita</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="308"/>
      <source>Unknown exception type</source>
      <translation>Tipo di eccezione sconosciuto</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="326"/>
      <source>unparseable Python error</source>
      <translation>Errore Python non definibile</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="370"/>
      <source>unparseable Python traceback</source>
      <translation>Traceback Python non definibile</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="377"/>
      <source>Unfetchable Python error.</source>
      <translation>Errore di Python non definibile.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="34"/>
      <source>Install log posted to:
%1</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="72"/>
      <source>%1 Setup Program</source>
      <translation>%1 Programma di installazione</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="73"/>
      <source>%1 Installer</source>
      <translation>%1 Programma di installazione</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="142"/>
      <source>Show debug information</source>
      <translation>Mostra le informazioni di debug</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="45"/>
      <source>Gathering system information...</source>
      <translation>Raccolta delle informazioni di sistema...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="154"/>
      <source>After:</source>
      <translation>Dopo:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="330"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Partizionamento manuale&lt;/strong&gt;&lt;br/&gt;Si possono creare o ridimensionare le partizioni manualmente.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1024"/>
      <source>Boot loader location:</source>
      <translation>Posizionamento del boot loader:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="152"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Selezionare un dispositivo di me&amp;moria:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="153"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="951"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="996"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1082"/>
      <source>Current:</source>
      <translation>Corrente:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="827"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Riutilizzare %1 come partizione home per &amp;2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="952"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Selezionare una partizione da ridurre, trascina la barra inferiore per ridimensionare&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="967"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 sarà ridotta a %2MiB ed una nuova partizione di %3MiB sarà creata per %4</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1073"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Selezionare la partizione sulla quale si vuole installare&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1129"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>Impossibile trovare una partizione EFI di sistema. Si prega di tornare indietro ed effettuare un partizionamento manuale per configurare %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1138"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>La partizione EFI di sistema su %1 sarà usata per avviare %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1146"/>
      <source>EFI system partition:</source>
      <translation>Partizione EFI di sistema:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Questo dispositivo di memoria non sembra contenere alcun sistema operativo. Come si vuole procedere?&lt;br/&gt;Si potranno comunque rivedere e confermare le scelte prima di apportare i cambiamenti al dispositivo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1269"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1307"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1330"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1356"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Cancellare disco&lt;/strong&gt;&lt;br/&gt;Questo &lt;font color="red"&gt;cancellerà&lt;/font&gt; tutti i dati attualmente presenti sul dispositivo di memoria.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1297"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Questo dispositivo di memoria ha %1. Come si vuole procedere?&lt;br/&gt;Si potranno comunque rivedere e confermare le scelte prima di apportare i cambiamenti al dispositivo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1501"/>
      <source>No Swap</source>
      <translation>No Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1506"/>
      <source>Reuse Swap</source>
      <translation>Riutilizza Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1509"/>
      <source>Swap (no Hibernate)</source>
      <translation>Swap (senza ibernazione)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1512"/>
      <source>Swap (with Hibernate)</source>
      <translation>Swap (con ibernazione)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1515"/>
      <source>Swap to file</source>
      <translation>Swap su file</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1273"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1303"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1326"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1352"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Installare a fianco&lt;/strong&gt;&lt;br/&gt;Il programma di installazione ridurrà una partizione per dare spazio a %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1277"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1312"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1334"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1360"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Sostituire una partizione&lt;/strong&gt;&lt;br/&gt;Sostituisce una partizione con %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1321"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Questo dispositivo di memoria contenere già un sistema operativo. Come si vuole procedere?&lt;br/&gt;Si potranno comunque rivedere e confermare le scelte prima di apportare i cambiamenti al dispositivo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1347"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Questo dispositivo di memoria contenere diversi sistemi operativi. Come si vuole procedere?&lt;br/&gt;Comunque si potranno rivedere e confermare le scelte prima di apportare i cambiamenti al dispositivo.</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="47"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Rimuovere i punti di mount per operazioni di partizionamento su %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="55"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Rimozione dei punti di mount per le operazioni di partizionamento su %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="192"/>
      <source>Cleared all mounts for %1</source>
      <translation>Rimossi tutti i punti di mount per %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
      <source>Clear all temporary mounts.</source>
      <translation>Rimuovere tutti i punti di mount temporanei.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Rimozione di tutti i punti di mount temporanei.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Non è possibile ottenere la lista dei punti di mount temporanei.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Rimossi tutti i punti di mount temporanei.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="150"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="163"/>
      <source>Could not run command.</source>
      <translation>Impossibile eseguire il comando.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="151"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>Il comando viene eseguito nell'ambiente host e richiede il percorso di root ma nessun rootMountPoint (punto di montaggio di root) è definito.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>Il comando richiede il nome utente, nessun nome utente definito.</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="123"/>
      <source>Contextual Processes Job</source>
      <translation>Job dei processi contestuali</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
      <source>Create a Partition</source>
      <translation>Creare una partizione</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
      <source>Partition &amp;Type:</source>
      <translation>&amp;Tipo di partizione:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
      <source>&amp;Primary</source>
      <translation>&amp;Primaria</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
      <source>E&amp;xtended</source>
      <translation>E&amp;stesa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;le System:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
      <source>LVM LV name</source>
      <translation>Nome LV di LVM</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
      <source>Flags:</source>
      <translation>Flag:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
      <source>&amp;Mount Point:</source>
      <translation>Punto di &amp;mount:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
      <source>Si&amp;ze:</source>
      <translation>&amp;Dimensione:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="72"/>
      <source>En&amp;crypt</source>
      <translation>Cr&amp;iptare</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="151"/>
      <source>Logical</source>
      <translation>Logica</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="156"/>
      <source>Primary</source>
      <translation>Primaria</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="173"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="262"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Il punto di mount è già in uso. Sceglierne un altro.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>Crea una nuova partizione da %2MiB su %4 (%3) con file system %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Creazione della nuova partizione %1 su %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Il programma di installazione non è riuscito a creare la partizione sul disco '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
      <source>Create Partition Table</source>
      <translation>Creare la tabella delle partizioni</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>La creazione di una nuova tabella delle partizioni cancellerà tutti i dati esistenti sul disco.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Che tipo di tabella delle partizioni vuoi creare?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Master Boot Record (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>Tavola delle Partizioni GUID (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Creare una nuova tabella delle partizioni %1 su %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="54"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Creare una nuova tabella delle partizioni &lt;strong&gt;%1&lt;/strong&gt; su &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="64"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Creazione della nuova tabella delle partizioni %1 su %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="82"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Il programma di installazione non è riuscito a creare una tabella delle partizioni su %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
      <source>Create user %1</source>
      <translation>Creare l'utente %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Creare l'utente &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
      <source>Creating user %1.</source>
      <translation>Creazione utente %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
      <source>Sudoers dir is not writable.</source>
      <translation>La cartella sudoers non è scrivibile.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="89"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Impossibile creare il file sudoers in scrittura.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Impossibile eseguire chmod sul file sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="107"/>
      <source>Cannot open groups file for reading.</source>
      <translation>Impossibile aprire il file groups in lettura.</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="37"/>
      <source>Create Volume Group</source>
      <translation>Crea Gruppo di Volumi</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Create new volume group named %1.</source>
      <translation>Crea un nuovo gruppo di volumi denominato %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="45"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Crea un nuovo gruppo di volumi denominato &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="52"/>
      <source>Creating new volume group named %1.</source>
      <translation>Creazione del nuovo gruppo di volumi denominato %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="65"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Il programma di installazione non è riuscito a creare un gruppo di volumi denominato '%1'.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="34"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
      <source>Deactivate volume group named %1.</source>
      <translation>Disattiva gruppo di volumi denominato %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="41"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Disattiva gruppo di volumi denominato &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Il programma di installazione non è riuscito a disattivare il gruppo di volumi denominato %1.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
      <source>Delete partition %1.</source>
      <translation>Cancellare la partizione %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Cancellare la partizione &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
      <source>Deleting partition %1.</source>
      <translation>Cancellazione partizione %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Il programma di installazione non è riuscito a cancellare la partizione %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Il tipo di &lt;strong&gt;tabella delle partizioni&lt;/strong&gt; attualmente presente sul dispositivo di memoria selezionato.&lt;br&gt;&lt;br&gt;L'unico modo per cambiare il tipo di tabella delle partizioni è quello di cancellarla e ricrearla da capo, distruggendo tutti i dati sul dispositivo.&lt;br&gt;Il programma di installazione conserverà l'attuale tabella a meno che no si scelga diversamente.&lt;br&gt;Se non si è sicuri, sui sistemi moderni si preferisce GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Questo dispositivo ha una tabella delle partizioni &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="115"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Questo è un dispositivo &lt;strong&gt;loop&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;E' uno pseudo-dispositivo senza tabella delle partizioni che rende un file accessibile come block device. Questo tipo di configurazione contiene normalmente solo un singolo filesystem.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="122"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Il programma d'installazione &lt;strong&gt;non riesce a rilevare una tabella delle partizioni&lt;/strong&gt; sul dispositivo di memoria selezionato.&lt;br&gt;&lt;br&gt;Il dispositivo o non ha una tabella delle partizioni o questa è corrotta, oppure è di tipo sconosciuto.&lt;br&gt;Il programma può creare una nuova tabella delle partizioni, automaticamente o attraverso la sezione del partizionamento manuale.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="132"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Questo è il tipo raccomandato di tabella delle partizioni per i sistemi moderni che si avviano da un ambiente di boot &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="138"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Questo tipo di tabella delle partizioni è consigliabile solo su sistemi più vecchi che si avviano da un ambiente di boot &lt;strong&gt;BIOS&lt;/strong&gt;. GPT è raccomandato nella maggior parte degli altri casi.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Attenzione:&lt;/strong&gt; la tabella delle partizioni MBR è uno standar obsoleto dell'era MS-DOS.&lt;br&gt;Solo 4 partizioni &lt;em&gt;primarie&lt;/em&gt; possono essere create e di queste 4 una può essere una partizione &lt;em&gt;estesa&lt;/em&gt;, che può a sua volta contenere molte partizioni &lt;em&gt;logiche&lt;/em&gt;.</translation>
    </message>
  </context>
  <context>
    <name>DeviceModel</name>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="92"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="103"/>
      <source>%1 - (%2)</source>
      <extracomment>device[name] - (device-node[name])</extracomment>
      <translation>%1 - (%2)</translation>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="136"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Scrittura della configurazione LUKS per Dracut su %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="140"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Salto scrittura della configurazione LUKS per Dracut: la partizione "/" non è criptata</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="157"/>
      <source>Failed to open %1</source>
      <translation>Impossibile aprire %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
      <source>Dummy C++ Job</source>
      <translation>Processo Dummy C++</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
      <source>Edit Existing Partition</source>
      <translation>Modifica la partizione esistente</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
      <source>Content:</source>
      <translation>Contenuto:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
      <source>&amp;Keep</source>
      <translation>&amp;Mantenere</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
      <source>Format</source>
      <translation>Formattare</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Attenzione: la formattazione della partizione cancellerà tutti i dati!</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
      <source>&amp;Mount Point:</source>
      <translation>Punto di &amp;Mount:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
      <source>Si&amp;ze:</source>
      <translation>Di&amp;mensione:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
      <source>Fi&amp;le System:</source>
      <translation>Fi&amp;le System:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
      <source>Flags:</source>
      <translation>Flag:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="269"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Il punto di mount è già in uso. Sceglierne un altro.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
      <source>En&amp;crypt system</source>
      <translation>Cr&amp;iptare il sistema</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
      <source>Passphrase</source>
      <translation>Frase di accesso</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
      <source>Confirm passphrase</source>
      <translation>Confermare frase di accesso</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Si prega di immettere la stessa frase di accesso in entrambi i riquadri.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="130"/>
      <source>Set partition information</source>
      <translation>Impostare informazioni partizione</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="153"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Installare %1 sulla &lt;strong&gt;nuova&lt;/strong&gt; partizione di sistema %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="157"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Impostare la &lt;strong&gt;nuova&lt;/strong&gt; %2 partizione con punto di mount &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="165"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installare %2 sulla partizione di sistema %3 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="170"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Impostare la partizione %3 &lt;strong&gt;%1&lt;/strong&gt; con punto di montaggio &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="182"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Installare il boot loader su &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="192"/>
      <source>Setting up mount points.</source>
      <translation>Impostazione dei punti di mount.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
      <source>&lt;Restart checkbox tooltip&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Riavviare ora</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="58"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Quando questa casella è selezionata, il tuo computer verrà riavviato immediatamente quando clicchi su &lt;span style="font-style:italic;"&gt;Finito&lt;/span&gt; oppure chiudi il programma di setup.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="66"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Tutto fatto.&lt;/ h1&gt;&lt;br/&gt;%1 è stato installato sul computer.&lt;br/&gt;Ora è possibile riavviare il sistema, o continuare a utilizzare l'ambiente Live di %2 .</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="71"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="133"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installazione fallita&lt;/h1&gt;&lt;br/&gt;%1 non è stato installato sul tuo computer.&lt;br/&gt;Il messaggio di errore è: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="139"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Installazione Fallita&lt;/h1&gt;&lt;br/&gt;%1 non è stato installato sul tuo computer.&lt;br/&gt;Il messaggio di errore è: %2</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="78"/>
      <source>Finish</source>
      <translation>Termina</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="132"/>
      <source>Setup Complete</source>
      <translation>Installazione completata</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="133"/>
      <source>Installation Complete</source>
      <translation>Installazione completata</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="135"/>
      <source>The setup of %1 is complete.</source>
      <translation>L'installazione di %1 è completa</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="136"/>
      <source>The installation of %1 is complete.</source>
      <translation>L'installazione di %1 è completata.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>Formatta la partitione %1 (file system: %2, dimensione: %3 MiB) su %4.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Formatta la partizione &lt;strong&gt;%1&lt;/strong&gt; di dimensione &lt;strong&gt;%3MiB &lt;/strong&gt;  con il file system &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Formattazione della partizione %1 con file system %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Il programma di installazione non è riuscito a formattare la partizione %1 sul disco '%2'.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="126"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>ha almeno %1 GiB di spazio disponibile</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="128"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Non c'è abbastanza spazio sul disco. E' richiesto almeno %1 GiB</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="137"/>
      <source>has at least %1 GiB working memory</source>
      <translation>ha almeno %1 GiB di memoria</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="139"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Il sistema non ha abbastanza memoria. E' richiesto almeno %1 GiB</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="148"/>
      <source>is plugged in to a power source</source>
      <translation>è collegato a una presa di alimentazione</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Il sistema non è collegato a una presa di alimentazione.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>is connected to the Internet</source>
      <translation>è connesso a Internet</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="157"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Il sistema non è connesso a internet.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="164"/>
      <source>is running the installer as an administrator (root)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="167"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Il programma di installazione non è stato lanciato con i permessi di amministratore.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Il programma di installazione non è stato avviato con i diritti di amministrazione.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="176"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Lo schermo è troppo piccolo per mostrare il programma di installazione</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Schermo troppo piccolo per mostrare il programma d'installazione.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="51"/>
      <source>Collecting information about your machine.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>IDJob</name>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="38"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="47"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="59"/>
      <location filename="../src/modules/oemid/IDJob.cpp" line="67"/>
      <source>OEM Batch Identifier</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="48"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Impossibile creare le cartelle &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Impossibile aprire il file &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="68"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>Impossibile scrivere sul file &lt;code&gt;%1&lt;/code&gt;.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="40"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>Sto creando initramfs con mkinitcpio.</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="37"/>
      <source>Creating initramfs.</source>
      <translation>Sto creando initramfs.</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
      <source>Konsole not installed</source>
      <translation>Konsole non installata</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Si prega di installare KDE Konsole e riprovare!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Esecuzione script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="47"/>
      <source>Script</source>
      <translation>Script</translation>
    </message>
  </context>
  <context>
    <name>KeyboardPage</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="219"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Impostare il modello di tastiera a %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="223"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Impostare il layout della tastiera a %1%2.</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
      <source>Keyboard</source>
      <translation>Tastiera</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="32"/>
      <source>System locale setting</source>
      <translation>Impostazioni di localizzazione del sistema</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="39"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Le impostazioni di localizzazione del sistema influenzano la lingua e il set di caratteri per alcuni elementi di interfaccia da linea di comando. &lt;br/&gt;L'impostazione attuale è &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="63"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Annulla</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="64"/>
      <source>&amp;OK</source>
      <translation>&amp;OK</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="22"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Accetto i termini e le condizioni sopra indicati.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="164"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="169"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="52"/>
      <source>License</source>
      <translation>Licenza</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="96"/>
      <source>URL: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="117"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;da %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 driver video&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;da %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="130"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 plugin del browser&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;da %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="136"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;da %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="142"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1 pacchetto&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;da %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="148"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;da %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="171"/>
      <source>File: %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Show the license text</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="198"/>
      <source>Open license agreement in browser.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Hide license text</source>
      <translation>Nascondi il testo della licenza</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="259"/>
      <source>The system language will be set to %1.</source>
      <translation>La lingua di sistema sarà impostata a %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="260"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>I numeri e le date locali saranno impostati a %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="124"/>
      <source>Region:</source>
      <translation>Area:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="125"/>
      <source>Zone:</source>
      <translation>Zona:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="126"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="127"/>
      <source>&amp;Change...</source>
      <translation>&amp;Cambia...</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="267"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Imposta il fuso orario a %1%2.&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="99"/>
      <source>Location</source>
      <translation>Posizione</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="39"/>
      <source>Configuring LUKS key file.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="156"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="164"/>
      <source>No partitions are defined.</source>
      <translation>Non è stata specificata alcuna partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="192"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="199"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="207"/>
      <source>Encrypted rootfs setup error</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="193"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="200"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="208"/>
      <source>Could configure LUKS key file on partition %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="46"/>
      <source>Generate machine-id.</source>
      <translation>Genera machine-id.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="62"/>
      <source>Configuration Error</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="63"/>
      <source>No root mount point is set for MachineId.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NetInstallPage</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="61"/>
      <source>Name</source>
      <translation>Nome</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="62"/>
      <source>Description</source>
      <translation>Descrizione</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="109"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Installazione di rete. (Disabilitata: impossibile recuperare le liste dei pacchetti, controllare la connessione di rete)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="119"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Installazione di rete. (Disabilitata: Ricevuti dati non validi dei gruppi)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="158"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Package selection</source>
      <translation>Selezione del pacchetto</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="28"/>
      <source>Ba&amp;tch:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="38"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="121"/>
      <source>OEM Configuration</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="126"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="57"/>
      <source>Password is too short</source>
      <translation>Password troppo corta</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="73"/>
      <source>Password is too long</source>
      <translation>Password troppo lunga</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="149"/>
      <source>Password is too weak</source>
      <translation>Password troppo debole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="157"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>Errore di allocazione della memoria quando si imposta '%1'</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
      <source>Memory allocation error</source>
      <translation>Errore di allocazione di memoria</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
      <source>The password is the same as the old one</source>
      <translation>La password coincide con la precedente</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
      <source>The password is a palindrome</source>
      <translation>La password è un palindromo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
      <source>The password differs with case changes only</source>
      <translation>La password differisce solo per lettere minuscole e maiuscole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
      <source>The password is too similar to the old one</source>
      <translation>La password è troppo simile a quella precedente</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
      <source>The password contains the user name in some form</source>
      <translation>La password contiene il nome utente in qualche campo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>La password contiene parti del nome utente reale in qualche campo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="177"/>
      <source>The password contains forbidden words in some form</source>
      <translation>La password contiene parole vietate in alcuni campi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="181"/>
      <source>The password contains less than %1 digits</source>
      <translation>La password contiene meno di %1 cifre</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
      <source>The password contains too few digits</source>
      <translation>La password contiene poche cifre</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>The password contains less than %1 uppercase letters</source>
      <translation>La password contiene meno di %1 lettere maiuscole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
      <source>The password contains too few uppercase letters</source>
      <translation>La password contiene poche lettere maiuscole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
      <source>The password contains less than %1 lowercase letters</source>
      <translation>La password contiene meno di %1 lettere minuscole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
      <source>The password contains too few lowercase letters</source>
      <translation>La password contiene poche lettere minuscole</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password contains less than %1 non-alphanumeric characters</source>
      <translation>La password contiene meno di %1 caratteri non alfanumerici</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>La password contiene pochi caratteri non alfanumerici</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password is shorter than %1 characters</source>
      <translation>La password ha meno di %1 caratteri</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
      <source>The password is too short</source>
      <translation>La password è troppo corta</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password is just rotated old one</source>
      <translation>La password è solo una rotazione della precedente</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains less than %1 character classes</source>
      <translation>La password contiene meno di %1 classi di caratteri</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password does not contain enough character classes</source>
      <translation>La password non contiene classi di caratteri sufficienti</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains more than %1 same characters consecutively</source>
      <translation>La password contiene più di %1 caratteri uguali consecutivi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="230"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>La password contiene troppi caratteri uguali consecutivi</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="234"/>
      <source>The password contains more than %1 characters of the same class consecutively</source>
      <translation>La password contiene più di %1 caratteri consecutivi della stessa classe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="238"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>La password contiene molti caratteri consecutivi della stessa classe</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains monotonic sequence longer than %1 characters</source>
      <translation>La password contiene una sequenza monotona più lunga di %1 caratteri</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>La password contiene una sequenza di caratteri monotona troppo lunga</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>No password supplied</source>
      <translation>Nessuna password fornita</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>Impossibile ottenere numeri casuali dal dispositivo RNG</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="254"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Generazione della password fallita - entropia richiesta troppo bassa per le impostazioni</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="260"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>La password non supera il controllo del dizionario - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password fails the dictionary check</source>
      <translation>La password non supera il controllo del dizionario</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
      <source>Unknown setting - %1</source>
      <translation>Impostazioni sconosciute - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
      <source>Unknown setting</source>
      <translation>Impostazione sconosciuta</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Valore intero non valido per l'impostazione - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>Bad integer value</source>
      <translation>Valore intero non valido</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="284"/>
      <source>Setting %1 is not of integer type</source>
      <translation>Impostazione %1 non è di tipo intero</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>Setting is not of integer type</source>
      <translation>Impostazione non è di tipo intero</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Setting %1 is not of string type</source>
      <translation>Impostazione %1 non è di tipo stringa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>Setting is not of string type</source>
      <translation>Impostazione non è di tipo stringa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="300"/>
      <source>Opening the configuration file failed</source>
      <translation>Apertura del file di configurazione fallita</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The configuration file is malformed</source>
      <translation>Il file di configurazione non è corretto</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="304"/>
      <source>Fatal failure</source>
      <translation>Errore fatale</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown error</source>
      <translation>Errore sconosciuto</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="528"/>
      <source>Password is empty</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="20"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="40"/>
      <source>Product Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="53"/>
      <source>TextLabel</source>
      <translation>TextLabel</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="69"/>
      <source>Long Product Description</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="34"/>
      <source>Package Selection</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="35"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="70"/>
      <source>Packages</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
      <source>Keyboard Model:</source>
      <translation>Modello della tastiera:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
      <source>Type here to test your keyboard</source>
      <translation>Digitare qui per provare la tastiera</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
      <source>What is your name?</source>
      <translation>Qual è il tuo nome?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="120"/>
      <source>What name do you want to use to log in?</source>
      <translation>Quale nome usare per l'autenticazione?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="321"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Scegliere una password per rendere sicuro il tuo account.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="345"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="370"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Inserire la password due volte per controllare eventuali errori di battitura. Una buona password contiene lettere, numeri e segni di punteggiatura. Deve essere lunga almeno otto caratteri e dovrebbe essere cambiata a intervalli regolari.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="219"/>
      <source>What is the name of this computer?</source>
      <translation>Qual è il nome di questo computer?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="51"/>
      <source>Your Full Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="144"/>
      <source>login</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="243"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Questo nome sarà usato se rendi visibile il computer ad altre persone in una rete.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="246"/>
      <source>Computer Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="351"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="521"/>
      <source>Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="376"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="546"/>
      <source>Repeat Password</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="451"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="454"/>
      <source>Require strong passwords.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="461"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Accedere automaticamente senza chiedere la password.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="468"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Usare la stessa password per l'account amministratore.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="491"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Scegliere una password per l'account dell'amministratore.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="515"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="540"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Inserire la password due volte per controllare eventuali errori di battitura.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Root</source>
      <translation>Root</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="200"/>
      <source>Home</source>
      <translation>Home</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>Boot</source>
      <translation>Boot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
      <source>EFI system</source>
      <translation>Sistema EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="209"/>
      <source>New partition for %1</source>
      <translation>Nuova partizione per %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition</source>
      <translation>Nuova partizione</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="230"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1 %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="144"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="176"/>
      <source>Free Space</source>
      <translation>Spazio disponibile</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="148"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="180"/>
      <source>New partition</source>
      <translation>Nuova partizione</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="264"/>
      <source>Name</source>
      <translation>Nome</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="266"/>
      <source>File System</source>
      <translation>File System</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="268"/>
      <source>Mount Point</source>
      <translation>Punto di mount</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="270"/>
      <source>Size</source>
      <translation>Dimensione</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
      <source>Storage de&amp;vice:</source>
      <translation>Dispositivo di me&amp;moria:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
      <source>&amp;Revert All Changes</source>
      <translation>&amp;Annulla tutte le modifiche</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
      <source>New Partition &amp;Table</source>
      <translation>Nuova &amp;Tabella delle partizioni</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
      <source>Cre&amp;ate</source>
      <translation>Crea</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
      <source>&amp;Edit</source>
      <translation>&amp;Modificare</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
      <source>&amp;Delete</source>
      <translation>&amp;Cancellare</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
      <source>New Volume Group</source>
      <translation>Nuovo Gruppo di Volumi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
      <source>Resize Volume Group</source>
      <translation>RIdimensiona Gruppo di Volumi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
      <source>Deactivate Volume Group</source>
      <translation>Disattiva Gruppo di Volumi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
      <source>Remove Volume Group</source>
      <translation>Rimuovi Gruppo di Volumi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>I&amp;nstalla boot loader su:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="209"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Si è sicuri di voler creare una nuova tabella delle partizioni su %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="238"/>
      <source>Can not create new partition</source>
      <translation>Impossibile creare nuova partizione</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="239"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>La tabella delle partizioni su %1 contiene già %2 partizioni primarie, non se ne possono aggiungere altre. Rimuovere una partizione primaria e aggiungere una partizione estesa invece.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="78"/>
      <source>Gathering system information...</source>
      <translation>Raccolta delle informazioni di sistema...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="130"/>
      <source>Partitions</source>
      <translation>Partizioni</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Installare %1 &lt;strong&gt;a fianco&lt;/strong&gt; di un altro sistema operativo.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Cancellare&lt;/strong&gt; il disco e installare %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="175"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Sostituire&lt;/strong&gt; una partizione con %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="180"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>Partizionamento &lt;strong&gt;manuale&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="193"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Installare %1 &lt;strong&gt;a fianco&lt;/strong&gt; di un altro sistema operativo sul disco&lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="199"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Cancellare&lt;/strong&gt; il disco &lt;strong&gt;%2&lt;/strong&gt; (%3) e installa %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="205"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Sostituire&lt;/strong&gt; una partizione sul disco &lt;strong&gt;%2&lt;/strong&gt; (%3) con %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="212"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>Partizionamento &lt;strong&gt;manuale&lt;/strong&gt; sul disco &lt;strong&gt;%1&lt;/strong&gt; (%2).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="220"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Disco &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="248"/>
      <source>Current:</source>
      <translation>Corrente:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="265"/>
      <source>After:</source>
      <translation>Dopo:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="415"/>
      <source>No EFI system partition configured</source>
      <translation>Nessuna partizione EFI di sistema è configurata</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="416"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Una partizione EFI di sistema è necessaria per avviare %1.&lt;br/&gt;&lt;br/&gt;Per configurare una partizione EFI di sistema, tornare indietro e selezionare o creare un filesystem FAT32 con il flag &lt;strong&gt;esp&lt;/strong&gt; abilitato e un punto di mount &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Si può continuare senza configurare una partizione EFI ma il sistema rischia di non avviarsi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="429"/>
      <source>EFI system partition flag not set</source>
      <translation>Il flag della partizione EFI di sistema non è impostato.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="430"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation>Una partizione EFI di sistema è necessaria per avviare %1.&lt;br/&gt;&lt;br/&gt;Una partizione è stata configurata con punto di mount &lt;strong&gt;%2&lt;/strong&gt; ma il relativo flag &lt;strong&gt;esp&lt;/strong&gt; non è impostato.&lt;br/&gt;Per impostare il flag, tornare indietro e modificare la partizione.&lt;br/&gt;&lt;br/&gt;Si può continuare senza impostare il flag ma il sistema rischia di non avviarsi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="465"/>
      <source>Boot partition not encrypted</source>
      <translation>Partizione di avvio non criptata</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="466"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>E' stata configurata una partizione di avvio non criptata assieme ad una partizione root criptata. &lt;br/&gt;&lt;br/&gt;Ci sono problemi di sicurezza con questo tipo di configurazione perchè dei file di sistema importanti sono tenuti su una partizione non criptata.&lt;br/&gt;Si può continuare se lo si desidera ma dopo ci sarà lo sblocco del file system, durante l'avvio del sistema.&lt;br/&gt;Per criptare la partizione di avvio, tornare indietro e ricrearla, selezionando &lt;strong&gt;Criptare&lt;/strong&gt; nella finestra di creazione della partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="650"/>
      <source>has at least one disk device available.</source>
      <translation>ha almeno un'unità disco disponibile.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="651"/>
      <source>There are no partitons to install on.</source>
      <translation>Non ci sono partizioni su cui installare</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>Job di Plasma Look-and-Feel</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>Impossibile selezionare il pacchetto di KDE Plasma Look-and-Feel</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="70"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="76"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Scegliere il tema per il desktop KDE Plasma. Si può anche saltare questa scelta e configurare il tema dopo aver installato il sistema. Cliccando su selezione del tema, ne sarà mostrata un'anteprima dal vivo. </translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
      <source>Look-and-Feel</source>
      <translation>Look-and-Feel</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="84"/>
      <source>Saving files for later ...</source>
      <translation>Salvataggio dei file per dopo ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="122"/>
      <source>No files configured to save for later.</source>
      <translation>Nessun file configurato per dopo.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="176"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Non tutti i file configurati possono essere preservati.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="407"/>
      <source>
There was no output from the command.</source>
      <translation>Non c'era output dal comando.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="408"/>
      <source>
Output:
</source>
      <translation>
Output:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="412"/>
      <source>External command crashed.</source>
      <translation>Il comando esterno si è arrestato.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="413"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>Il comando &lt;i&gt;%1&lt;/i&gt; si è arrestato.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>External command failed to start.</source>
      <translation>Il comando esterno non si è avviato.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="419"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>Il comando %1 non si è avviato.
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>Internal error when starting command.</source>
      <translation>Errore interno all'avvio del comando.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Bad parameters for process job call.</source>
      <translation>Parametri errati per elaborare la chiamata al job.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>External command failed to finish.</source>
      <translation>Il comando esterno non è stato portato a termine.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>Il comando &lt;i&gt;%1&lt;/i&gt; non è stato portato a termine in %2 secondi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="436"/>
      <source>External command finished with errors.</source>
      <translation>Il comando esterno è terminato con errori.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="437"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>Il comando &lt;i&gt;%1&lt;/i&gt; è terminato con codice di uscita %2.</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="91"/>
      <source>Default Keyboard Model</source>
      <translation>Modello tastiera di default</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="133"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="168"/>
      <source>Default</source>
      <translation>Default</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="207"/>
      <source>unknown</source>
      <translation>sconosciuto</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="209"/>
      <source>extended</source>
      <translation>estesa</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="211"/>
      <source>unformatted</source>
      <translation>non formattata</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="213"/>
      <source>swap</source>
      <translation>swap</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="51"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Spazio non partizionato o tabella delle partizioni sconosciuta</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="47"/>
      <source>(no mount point)</source>
      <translation>(nessun mount point)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="65"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/locale/Label.cpp" line="46"/>
      <source>%1 (%2)</source>
      <extracomment>language[name] (country[name])</extracomment>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="79"/>
      <source>No product</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="87"/>
      <source>No description provided.</source>
      <translation>Non è stata fornita alcuna descrizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="55"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="63"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="67"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="117"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="132"/>
      <source>File not found</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="56"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="118"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="133"/>
      <source>Could not read random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="34"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="48"/>
      <source>Remove Volume Group named %1.</source>
      <translation>Rimuovi Gruppo di Volumi denominato %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="41"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rimuovi gruppo di volumi denominato &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="135"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Selezionare dove installare %1.&lt;br/&gt;&lt;font color="red"&gt;Attenzione: &lt;/font&gt;questo eliminerà tutti i file dalla partizione selezionata.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="161"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>L'elemento selezionato non sembra essere una partizione valida.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="169"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 non può essere installato su spazio non partizionato. Si prega di selezionare una partizione esistente.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="179"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 non può essere installato su una partizione estesa. Si prega di selezionare una partizione primaria o logica esistente.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="189"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 non può essere installato su questa partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="195"/>
      <source>Data partition (%1)</source>
      <translation>Partizione dati (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="212"/>
      <source>Unknown system partition (%1)</source>
      <translation>Partizione di sistema sconosciuta (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="217"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 partizione di sistema (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="228"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;La partizione %1 è troppo piccola per %2. Si prega di selezionare una partizione con capacità di almeno %3 GiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="251"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Nessuna partizione EFI di sistema rilevata. Si prega di tornare indietro e usare il partizionamento manuale per configurare %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="262"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="279"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="303"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 sarà installato su %2.&lt;br/&gt;&lt;font color="red"&gt;Attenzione: &lt;/font&gt;tutti i dati sulla partizione %2 saranno persi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="271"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>La partizione EFI di sistema a %1 sarà usata per avviare %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="287"/>
      <source>EFI system partition:</source>
      <translation>Partizione EFI di sistema:</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="59"/>
      <source>Resize Filesystem Job</source>
      <translation>Operazione di ridimensionamento del Filesystem</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="172"/>
      <source>Invalid configuration</source>
      <translation>Configurazione non valida</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="173"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>L'operazione di ridimensionamento del file-system ha una configurazione non valida e non verrà effettuata.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="197"/>
      <source>KPMCore not Available</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="188"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="198"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="206"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="215"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="228"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="237"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="254"/>
      <source>Resize Failed</source>
      <translation>Ridimensionamento fallito.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>Il filesystem %1 non è stato trovato su questo sistema, e non può essere ridimensionato.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="208"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>Il dispositivo %1 non è stato trovato su questo sistema, e non può essere ridimensionato.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="216"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="229"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>Il filesystem %1 non può essere ridimensionato.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="230"/>
      <source>The device %1 cannot be resized.</source>
      <translation>Il dispositivo %1 non può essere ridimensionato.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="238"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>Il filesystem %1 deve essere ridimensionato, ma non è possibile farlo.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="239"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>Il dispositivo %1 deve essere ridimensionato, non è possibile farlo</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
      <source>Resize partition %1.</source>
      <translation>Ridimensionare la partizione %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>Sto ridimensionando la partizione %1 di dimensione %2MiB a %3MiB.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Il programma di installazione non è riuscito a ridimensionare la partizione %1 sul disco '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="39"/>
      <source>Resize Volume Group</source>
      <translation>RIdimensiona Gruppo di Volumi</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="55"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>Ridimensiona il gruppo di volumi con nome %1 da %2 a %3.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>Ridimensiona il gruppo di volumi con nome &lt;strong&gt;%1&lt;/strong&gt; da &lt;strong&gt;%2&lt;/strong&gt; a &lt;strong&gt;%3&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="70"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Il programma di installazione non è riuscito a ridimensionare un volume di gruppo di nome '%1'</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="137"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>Per ottenere prestazioni ottimali, assicurarsi che questo computer:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="138"/>
      <source>System requirements</source>
      <translation>Requisiti di sistema</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="263"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Questo computer non soddisfa i requisiti minimi per l'installazione di %1.&lt;br/&gt;L'installazione non può continuare. &lt;a href="#details"&gt;Dettagli...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="267"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Questo computer non soddisfa i requisiti minimi per installare %1. &lt;br/&gt;L'installazione non può proseguire. &lt;a href="#details"&gt;Dettagli...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="274"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Questo computer non soddisfa alcuni requisiti raccomandati per l'installazione di %1.&lt;br/&gt;L'installazione può continuare, ma alcune funzionalità potrebbero essere disabilitate.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="278"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Questo computer non soddisfa alcuni requisiti consigliati per l'installazione di %1. &lt;br/&gt;L'installazione può proseguire ma alcune funzionalità potrebbero non essere disponibili.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="287"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Questo programma chiederà alcune informazioni e configurerà %2 sul computer.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
      <source>Scanning storage devices...</source>
      <translation>Rilevamento dei dispositivi di memoria...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
      <source>Partitioning</source>
      <translation>Partizionamento</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="39"/>
      <source>Set hostname %1</source>
      <translation>Impostare hostname %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="46"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Impostare hostname &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="53"/>
      <source>Setting hostname %1.</source>
      <translation>Impostare hostname %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="64"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="71"/>
      <source>Internal Error</source>
      <translation>Errore interno</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="78"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="89"/>
      <source>Cannot write hostname to target system</source>
      <translation>Impossibile scrivere l'hostname nel sistema di destinazione</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Imposta il modello di tastiera a %1, con layout %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Impossibile scrivere la configurazione della tastiera per la console virtuale.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="326"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="332"/>
      <source>Failed to write to %1</source>
      <translation>Impossibile scrivere su %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Impossibile scrivere la configurazione della tastiera per X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Impossibile scrivere la configurazione della tastiera nella cartella /etc/default.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
      <source>Set flags on partition %1.</source>
      <translation>Impostare i flag sulla partizione: %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
      <source>Set flags on new partition.</source>
      <translation>Impostare i flag sulla nuova partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rimuovere i flag sulla partizione &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="85"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="107"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="121"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition.</source>
      <translation>Rimuovere i flag dalla nuova partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Flag di partizione &lt;strong&gt;%1&lt;/strong&gt; come &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Flag della nuova partizione come &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Rimozione dei flag sulla partizione &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
      <source>Clearing flags on new partition.</source>
      <translation>Rimozione dei flag dalla nuova partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Impostazione dei flag &lt;strong&gt;%2&lt;/strong&gt; sulla partizione &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Impostazione dei flag &lt;strong&gt;%1&lt;/strong&gt; sulla nuova partizione.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="144"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Impossibile impostare i flag sulla partizione %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
      <source>Set password for user %1</source>
      <translation>Impostare la password per l'utente %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
      <source>Setting password for user %1.</source>
      <translation>Impostare la password per l'utente %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
      <source>Bad destination system path.</source>
      <translation>Percorso di destinazione del sistema errato.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
      <source>rootMountPoint is %1</source>
      <translation>punto di mount per root è %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="119"/>
      <source>Cannot disable root account.</source>
      <translation>Impossibile disabilitare l'account di root.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="120"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd è terminato con codice di errore %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="128"/>
      <source>Cannot set password for user %1.</source>
      <translation>Impossibile impostare la password per l'utente %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="129"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod si è chiuso con codice di errore %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
      <source>Set timezone to %1/%2</source>
      <translation>Impostare il fuso orario su %1%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Impossibile accedere al percorso della timezone selezionata.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Bad path: %1</source>
      <translation>Percorso errato: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <translation>Impossibile impostare il fuso orario.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Impossibile creare il link, destinazione: %1; nome del link: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
      <source>Cannot set timezone,</source>
      <translation>Impossibile impostare il fuso orario,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Impossibile aprire il file /etc/timezone in scrittura</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="46"/>
      <source>Shell Processes Job</source>
      <translation>Job dei processi della shell</translation>
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
      <location filename="../src/modules/summary/SummaryPage.cpp" line="57"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="60"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Una panoramica delle modifiche che saranno effettuate una volta avviata la procedura di installazione.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
      <source>Summary</source>
      <translation>Riepilogo</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="42"/>
      <source>Installation feedback</source>
      <translation>Valutazione dell'installazione</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="54"/>
      <source>Sending installation feedback.</source>
      <translation>Invio della valutazione dell'installazione.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Internal error in install-tracking.</source>
      <translation>Errore interno in install-tracking.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="72"/>
      <source>HTTP request timed out.</source>
      <translation>La richiesta HTTP è scaduta.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineNeonJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="80"/>
      <source>Machine feedback</source>
      <translation>Valutazione automatica</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="92"/>
      <source>Configuring machine feedback.</source>
      <translation>Configurazione in corso della valutazione automatica.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="117"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="123"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Errore nella configurazione della valutazione automatica.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="118"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Non è stato possibile configurare correttamente la valutazione automatica, errore dello script %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Non è stato possibile configurare correttamente la valutazione automatica, errore di Calamares %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
      <source>Placeholder</source>
      <translation>Segnaposto</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Selezionando questo, non verrà inviata &lt;span style=" font-weight:600;"&gt;alcuna informazione&lt;/span&gt; relativa alla propria installazione.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Cliccare qui per maggiori informazioni sulla valutazione degli utenti&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
      <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
      <translation>Il tracciamento dell'installazione aiuta %1 a capire quanti utenti vengono serviti, su quale hardware si installa %1 e (con le ultime due opzioni sotto), a ricevere continue informazioni sulle applicazioni preferite. Per vedere cosa verrà inviato, cliccare sull'icona di aiuto accanto ad ogni area.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="49"/>
      <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
      <translation>Selezionando questa opzione saranno inviate informazioni relative all'installazione e all'hardware. I dati saranno &lt;b&gt;inviati solo una volta&lt;/b&gt; al termine dell'installazione.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="51"/>
      <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
      <translation>Selezionando questa opzione saranno inviate &lt;b&gt;periodicamente&lt;/b&gt; informazioni sull'installazione, l'hardware e le applicazioni, a %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="54"/>
      <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
      <translation>Selezionando questa opzione verranno inviate &lt;b&gt;regolarmente&lt;/b&gt; informazioni sull'installazione, l'hardware, le applicazioni e i modi di utilizzo, a %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="64"/>
      <source>Feedback</source>
      <translation>Valutazione</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="139"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="145"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="342"/>
      <source>Your username is too long.</source>
      <translation>Il nome utente è troppo lungo.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="349"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="356"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="404"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="392"/>
      <source>Your hostname is too short.</source>
      <translation>Hostname è troppo corto.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="397"/>
      <source>Your hostname is too long.</source>
      <translation>Hostname è troppo lungo.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="421"/>
      <source>Your passwords do not match!</source>
      <translation>Le password non corrispondono!</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="55"/>
      <source>Users</source>
      <translation>Utenti</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="241"/>
      <source>Key</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="245"/>
      <source>Value</source>
      <translation>Valore</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
      <source>Create Volume Group</source>
      <translation>Crea Gruppo di Volumi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
      <source>List of Physical Volumes</source>
      <translation>Lista dei volumi fisici</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
      <source>Volume Group Name:</source>
      <translation>Nome Volume Group:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
      <source>Volume Group Type:</source>
      <translation>Tipo Volume Group:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
      <source>Physical Extent Size:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
      <source>Total Size:</source>
      <translation>Dimensione totale:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
      <source>Used Size:</source>
      <translation>Dimensione utilizzata:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
      <source>Total Sectors:</source>
      <translation>Totale Settori:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
      <source>Quantity of LVs:</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
      <source>Form</source>
      <translation>Modulo</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="69"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="82"/>
      <source>Select application and system language</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>Open donations website</source>
      <translation>Apri il sito web per le donazioni</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="143"/>
      <source>&amp;Donate</source>
      <translation>&amp;Donazioni</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>Open help and support website</source>
      <translation>Apri il sito web per l'aiuto ed il supporto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>Open issues and bug-tracking website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>Open release notes website</source>
      <translation>Apri il sito web delle note di rilascio</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="182"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Note di rilascio</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="169"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Problemi conosciuti</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
      <source>&amp;Support</source>
      <translation>&amp;Supporto</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="130"/>
      <source>&amp;About</source>
      <translation>&amp;Informazioni su</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="254"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Benvenuto nel programma d'installazione di %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="253"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Benvenuti nel programma di installazione Calamares per %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Benvenuto nel programma di installazione Calamares di %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="248"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Benvenuto nell'installazione di %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="266"/>
      <source>About %1 setup</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="266"/>
      <source>About %1 installer</source>
      <translation>Informazioni sul programma di installazione %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="269"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2019 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2019 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Grazie al &lt;a href="https://calamares.io/team/"&gt;team di Calamares&lt;/a&gt; ed al &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;team dei traduttori di Calamares&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="259"/>
      <source>%1 support</source>
      <translation>supporto %1</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="62"/>
      <source>Welcome</source>
      <translation>Benvenuti</translation>
    </message>
  </context>
</TS>

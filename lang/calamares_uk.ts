<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="uk" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="71"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>&lt;strong&gt;Завантажувальне середовище&lt;/strong&gt; цієї системи.&lt;br&gt;&lt;br&gt;Старі x86-системи підтримують тільки &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Нові системи зазвичай використовують&lt;strong&gt;EFI&lt;/strong&gt;, проте можуть також відображатися як BIOS, якщо запущені у режимі сумісності.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="81"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Цю систему було запущено із завантажувальним середовищем &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Щоб налаштувати завантаження з середовища EFI, установник повинен встановити на &lt;strong&gt;Системний Розділ EFI&lt;/strong&gt; програму-завантажувач таку, як &lt;strong&gt;GRUB&lt;/strong&gt; або &lt;strong&gt;systemd-boot&lt;/strong&gt;. Це буде зроблено автоматично, якщо ви не обрали розподілення диску вручну. В останньому випадку вам потрібно обрати завантажувач або встановити його власноруч.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="93"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Цю систему було запущено із завантажувальним середовищем &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Щоб налаштувати завантаження з середовища BIOS, установник повинен встановити завантажувач, такий, як &lt;strong&gt;GRUB&lt;/strong&gt; або на початку розділу або у &lt;strong&gt;Головний Завантажувальний Запис (Master Boot Record)&lt;/strong&gt; біля початку таблиці розділів (рекомендовано). Це буде зроблено автотматично, якщо ви не обрали розподілення диску вручну. В останньому випадку вам потрібно встановити завантажувач власноруч.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="70"/>
      <source>Master Boot Record of %1</source>
      <translation>Головний Завантажувальний Запис (Master Boot Record) %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="104"/>
      <source>Boot Partition</source>
      <translation>Розділ Boot</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="109"/>
      <source>System Partition</source>
      <translation>Системний розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="139"/>
      <source>Do not install a boot loader</source>
      <translation>Не встановлювати завантажувач</translation>
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
      <translation>Пуста сторінка</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="24"/>
      <source>GlobalStorage</source>
      <translation>Глобальне сховище</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="34"/>
      <source>JobQueue</source>
      <translation>Черга завдань</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="44"/>
      <source>Modules</source>
      <translation>Модулі</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="57"/>
      <source>Type:</source>
      <translation>Тип:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="64"/>
      <location filename="../src/calamares/DebugWindow.ui" line="78"/>
      <source>none</source>
      <translation>немає</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="71"/>
      <source>Interface:</source>
      <translation>Інтерфейс:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="93"/>
      <source>Tools</source>
      <translation>Інструменти</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="106"/>
      <source>Reload Stylesheet</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="113"/>
      <source>Widget Tree</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="231"/>
      <source>Debug information</source>
      <translation>Відлагоджувальна інформація</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="120"/>
      <source>Set up</source>
      <translation>Налаштувати</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="120"/>
      <source>Install</source>
      <translation>Встановити</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="39"/>
      <source>Job failed (%1)</source>
      <translation>Невдало виконане завдання (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="40"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Невдача в запрограмованому завданні була чітко задана.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="118"/>
      <source>Done</source>
      <translation>Зроблено</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="27"/>
      <source>Example job (%1)</source>
      <translation>Приклад завдання (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source>Run command '%1' in target system.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source> Run command '%1'.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="59"/>
      <source>Running command %1 %2</source>
      <translation>Запуск команди %1 %2</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="208"/>
      <source>Running %1 operation.</source>
      <translation>Запуск операції %1.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="225"/>
      <source>Bad working directory path</source>
      <translation>Неправильний шлях робочого каталогу</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="226"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>Неможливо прочитати робочу директорію %1 для завдання python %2.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="232"/>
      <source>Bad main script file</source>
      <translation>Неправильний файл головного сценарію</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>Неможливо прочитати файл головного сценарію %1 для завдання python %2.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="311"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>Помилка Boost.Python у завданні "%1".</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message numerus="yes">
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="166"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Очікування %n модулю.</numerusform>
        <numerusform>Очікування %n модулів.</numerusform>
        <numerusform>Очікування %n модулів.</numerusform>
        <numerusform>Очікування %n модулів.</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="167"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n секунда)</numerusform>
        <numerusform>(%n секунди)</numerusform>
        <numerusform>(%n секунд(и))</numerusform>
        <numerusform>(%n секунд(и))</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/modulesystem/RequirementsChecker.cpp" line="172"/>
      <source>System-requirements checking is complete.</source>
      <translation>Перевірка системних вимог завершена.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="93"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="407"/>
      <source>&amp;Back</source>
      <translation>&amp;Назад</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="95"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="402"/>
      <source>&amp;Next</source>
      <translation>&amp;Вперед</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="97"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="427"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Скасувати</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="391"/>
      <source>Cancel setup without changing the system.</source>
      <translation>Скасувати налаштування без зміни системи.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>Cancel installation without changing the system.</source>
      <translation>Скасувати встановлення без зміни системи.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>Setup Failed</source>
      <translation>Помилка встановлення</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="197"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation type="unfinished"/>
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
      <translation>Помилка ініціалізації Calamares</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="255"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 неможливо встановити. Calamares не зміг завантажити всі налаштовані модулі. Ця проблема зв'язана з тим, як Calamares використовується дистрибутивом.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="261"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;Не вдалося завантажити наступні модулі:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="322"/>
      <source>Continue with installation?</source>
      <translation>Продовжити встановлення?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="324"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Програма налаштування %1 збирається внести зміни до вашого диска, щоб налаштувати %2. &lt;br/&gt;&lt;strong&gt; Ви не зможете скасувати ці зміни.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>&amp;Set up now</source>
      <translation>&amp;Налаштувати зараз</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="386"/>
      <source>&amp;Set up</source>
      <translation>&amp;Налаштувати</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="386"/>
      <source>&amp;Install</source>
      <translation>&amp;Встановити</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="388"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>Встановлення виконано. Закрити програму встановлення.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="487"/>
      <source>Cancel setup?</source>
      <translation>Скасувати налаштування?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="487"/>
      <source>Cancel installation?</source>
      <translation>Скасувати встановлення?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="488"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="490"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Чи ви насправді бажаєте скасувати процес встановлення?
Установник закриється і всі зміни буде втрачено.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="217"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="494"/>
      <source>&amp;Yes</source>
      <translation>&amp;Так</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="495"/>
      <source>&amp;No</source>
      <translation>&amp;Ні</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="224"/>
      <source>&amp;Close</source>
      <translation>&amp;Закрити</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="322"/>
      <source>Continue with setup?</source>
      <translation>Продовжити встановлення?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="327"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>Установник %1 збирається зробити зміни на вашому диску, щоб встановити %2.&lt;br/&gt;&lt;strong&gt;Ці зміни неможливо буде повернути.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>&amp;Install now</source>
      <translation>&amp;Встановити зараз</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="337"/>
      <source>Go &amp;back</source>
      <translation>Перейти &amp;назад</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="412"/>
      <source>&amp;Done</source>
      <translation>&amp;Закінчити</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="389"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>Встановлення виконано. Закрити установник.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="210"/>
      <source>Error</source>
      <translation>Помилка</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="196"/>
      <source>Installation Failed</source>
      <translation>Втановлення завершилося невдачею</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="308"/>
      <source>Unknown exception type</source>
      <translation>Невідомий тип виключної ситуації</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="326"/>
      <source>unparseable Python error</source>
      <translation>нерозбірлива помилка Python</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="370"/>
      <source>unparseable Python traceback</source>
      <translation>нерозбірливе відстеження помилки Python</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="377"/>
      <source>Unfetchable Python error.</source>
      <translation>Помилка Python, інформацію про яку неможливо отримати.</translation>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="73"/>
      <source>%1 Installer</source>
      <translation>Установник %1</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="142"/>
      <source>Show debug information</source>
      <translation>Показати відлагоджувальну інформацію</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="45"/>
      <source>Gathering system information...</source>
      <translation>Збираємо інформацію про систему...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="154"/>
      <source>After:</source>
      <translation>Після:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="330"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Розподілення вручну&lt;/strong&gt;&lt;br/&gt;Ви можете створити або змінити розмір розділів власноруч.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1024"/>
      <source>Boot loader location:</source>
      <translation>Місцезнаходження завантажувача:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="152"/>
      <source>Select storage de&amp;vice:</source>
      <translation>Обрати &amp;пристрій зберігання:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="153"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="951"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="996"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1082"/>
      <source>Current:</source>
      <translation>Зараз:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="827"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>Використати %1 як домашній розділ (home) для %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="952"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Оберіть розділ для зменьшення, потім тягніть повзунок, щоб змінити розмір&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="967"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1073"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Оберіть розділ, на який встановити&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1129"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>В цій системі не знайдено жодного системного розділу EFI. Щоб встановити %1, будь ласка, поверніться та оберіть розподілення вручну.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1138"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>Системний розділ EFI %1 буде використано для встановлення %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1146"/>
      <source>EFI system partition:</source>
      <translation>Системний розділ EFI:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1264"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Цей пристрій зберігання, схоже, не має жодної операційної системи. Що ви бажаєте зробити?&lt;br/&gt;У вас буде можливість переглянути та підтвердити все, що ви обрали перед тим, як будуть зроблені будь-які зміни на пристрої зберігання.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1269"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1307"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1330"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1356"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Очистити диск&lt;/strong&gt;&lt;br/&gt;Це &lt;font color="red"&gt;знищить&lt;/font&gt; всі данні, присутні на обраному пристрої зберігання.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1297"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>На цьому пристрої зберігання є %1. Що ви бажаєте зробити?&lt;br/&gt;У вас буде можливість переглянути та підтвердити все, що ви обрали перед тим, як будуть зроблені будь-які зміни на пристрої зберігання.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1501"/>
      <source>No Swap</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1506"/>
      <source>Reuse Swap</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1509"/>
      <source>Swap (no Hibernate)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1512"/>
      <source>Swap (with Hibernate)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1515"/>
      <source>Swap to file</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1273"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1303"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1326"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1352"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Встановити поруч&lt;/strong&gt;&lt;br/&gt;Установник зменьшить розмір розділу, щоб вивільнити простір для %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1277"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1312"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1334"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1360"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Замінити розділ&lt;/strong&gt;&lt;br/&gt;Замінити розділу на %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1321"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>На цьому пристрої зберігання вже є операційна система. Що ви бажаєте зробити?&lt;br/&gt;У вас буде можливість переглянути та підтвердити все, що ви обрали перед тим, як будуть зроблені будь-які зміни на пристрої зберігання.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1347"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>На цьому пристрої зберігання вже є декілька операційних систем. Що ви бажаєте зробити?&lt;br/&gt;У вас буде можливість переглянути та підтвердити все, що ви обрали перед тим, як будуть зроблені будь-які зміни на пристрої зберігання.</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="47"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>Очистити точки підключення для операцій над розділами на %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="55"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>Очищення точок підключення для операцій над розділами на %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="192"/>
      <source>Cleared all mounts for %1</source>
      <translation>Очищено всі точки підключення для %1</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
      <source>Clear all temporary mounts.</source>
      <translation>Очистити всі тимчасові точки підключення.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
      <source>Clearing all temporary mounts.</source>
      <translation>Очищення всіх тимчасових точок підключення.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>Неможливо отримати список тимчасових точок підключення.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Очищено всі тимчасові точки підключення.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="150"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="163"/>
      <source>Could not run command.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="151"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="123"/>
      <source>Contextual Processes Job</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
      <source>Create a Partition</source>
      <translation>Створити розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
      <source> MiB</source>
      <translation> МіБ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
      <source>Partition &amp;Type:</source>
      <translation>&amp;Тип розділу:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
      <source>&amp;Primary</source>
      <translation>&amp;Основний</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
      <source>E&amp;xtended</source>
      <translation>&amp;Розширений</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;Файлова система:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
      <source>LVM LV name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
      <source>Flags:</source>
      <translation>Прапорці:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
      <source>&amp;Mount Point:</source>
      <translation>Точка &amp;підключення:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
      <source>Si&amp;ze:</source>
      <translation>Ро&amp;змір:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="72"/>
      <source>En&amp;crypt</source>
      <translation>За&amp;шифрувати</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="151"/>
      <source>Logical</source>
      <translation>Логічний</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="156"/>
      <source>Primary</source>
      <translation>Основний</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="173"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="262"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Точка підключення наразі використовується. Оберіть, будь ласка, іншу.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="44"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="55"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="67"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>Створення нового розділу %1 на %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="79"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>Установник зазнав невдачі під час створення розділу на диску '%1'.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
      <source>Create Partition Table</source>
      <translation>Створити таблицю розділів</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Створення нової таблиці розділів знищить всі данні, присутні на диску.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Таблицю розділів якого типу ви бажаєте створити?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Головний завантажувальний запис (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>Таблиця розділів GUID (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="47"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>Створити нову таблицю розділів %1 на %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="54"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Створити нову таблицю розділів &lt;strong&gt;%1&lt;/strong&gt; на &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="64"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>Створення нової таблиці розділів %1 на %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="82"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Установник зазнав невдачі під час створення таблиці розділів на %1.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
      <source>Create user %1</source>
      <translation>Створити користувача %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Створити користувача &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
      <source>Creating user %1.</source>
      <translation>Створення користувача %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
      <source>Sudoers dir is not writable.</source>
      <translation>Неможливо запиcати у директорію sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="89"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>Неможливо створити файл sudoers для запису.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Неможливо встановити права на файл sudoers.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="107"/>
      <source>Cannot open groups file for reading.</source>
      <translation>Неможливо відкрити файл груп для читання.</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="37"/>
      <source>Create Volume Group</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Create new volume group named %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="45"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="52"/>
      <source>Creating new volume group named %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="65"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="34"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="48"/>
      <source>Deactivate volume group named %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="41"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
      <source>Delete partition %1.</source>
      <translation>Видалити розділ %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="48"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Видалити розділ &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="56"/>
      <source>Deleting partition %1.</source>
      <translation>Видалення розділу %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Установник зазнав невдачі під час видалення розділу %1.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Тип &lt;strong&gt;таблиці розділів&lt;/strong&gt; на обраному пристрої зберігання.&lt;br&gt;&lt;br&gt;Єдиний спосіб змінити таблицю розділів - це очистити і створити таблицю розділів з нуля, що знищить всі дані на пристрої зберігання.&lt;br&gt;Установник залишить поточну таблицю розділів, якщо ви явно не оберете інше.&lt;br&gt;Якщо не впевнені, на більш сучасних системах надайте перевагу GPT.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>На цьому пристрої таблиця розділів &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="115"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Це &lt;strong&gt;loop-пристрій&lt;/strong&gt;.Це псевдо-пристрій, що не має таблиці розділів та дозволяє доступ до файлу як до блокового пристрою. Цей спосіб налаштування зазвичай містить одну єдину файлову систему.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="122"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Установник &lt;strong&gt;не може визначити таблицю розділів&lt;/strong&gt; на обраному пристрої зберігання.&lt;br&gt;&lt;br&gt;Пристрій або на має таблиці розділів, або таблицю розділів пошкоджено чи вона невідомого типу.&lt;br&gt;Установник може створити нову таблицю розділів для вас, автоматично або за допомогою сторінки розподілення вручну.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="132"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Це рекомендований тип таблиці розділів для сучасних систем, які запускаються за допомогою завантажувального середовища &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="138"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Цей тип таблиці розділів рекомендований лише для старих систем, які запускаються за допомогою завантажувального середовища &lt;strong&gt;BIOS&lt;/strong&gt;. GPT рекомендовано у більшості інших випадків.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Попередження:&lt;/strong&gt; таблиця розділів MBR - це застарілий стандарт часів MS-DOS. Можливо створити &lt;br&gt;Лише 4 &lt;em&gt;основних&lt;/em&gt; розділів, один зі яких може бути &lt;em&gt;розширеним&lt;/em&gt;, який в свою чергу може містити багато &lt;em&gt;логічних&lt;/em&gt; розділів.</translation>
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
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>DracutLuksCfgJob</name>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="136"/>
      <source>Write LUKS configuration for Dracut to %1</source>
      <translation>Записати налаштування LUKS для Dracut до %1</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="140"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Пропустити запис налаштування LUKS для Dracut: розділ "/" не зашифрований</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="157"/>
      <source>Failed to open %1</source>
      <translation>Не вдалося відкрити %1</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
      <source>Dummy C++ Job</source>
      <translation>Завдання-макет C++</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
      <source>Edit Existing Partition</source>
      <translation>Редагування розділу</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
      <source>Content:</source>
      <translation>Вміст:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
      <source>&amp;Keep</source>
      <translation>За&amp;лишити</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
      <source>Format</source>
      <translation>Форматувати</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Попередження: Форматування розділу знищить всі присутні на ньому дані.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
      <source>&amp;Mount Point:</source>
      <translation>Точка &amp;підключення:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
      <source>Si&amp;ze:</source>
      <translation>Ро&amp;змір:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source> MiB</source>
      <translation> МіБ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
      <source>Fi&amp;le System:</source>
      <translation>&amp;Файлова система:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
      <source>Flags:</source>
      <translation>Прапорці:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="269"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>Точка підключення наразі використовується. Оберіть, будь ласка, іншу.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
      <source>En&amp;crypt system</source>
      <translation>За&amp;шифрувати систему</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
      <source>Passphrase</source>
      <translation>Ключова фраза</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
      <source>Confirm passphrase</source>
      <translation>Підтвердження ключової фрази</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>Будь ласка, введіть однакову ключову фразу у обидва текстові вікна.</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="130"/>
      <source>Set partition information</source>
      <translation>Ввести інформацію про розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="153"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>Встановити %1 на &lt;strong&gt;новий&lt;/strong&gt; системний розділ %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="157"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Налаштувати &lt;strong&gt;новий&lt;/strong&gt; розділ %2 з точкою підключення &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="165"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Встановити %2 на системний розділ %3 &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="170"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Налаштувати розділ %3 &lt;strong&gt;%1&lt;/strong&gt; з точкою підключення &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="182"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Встановити завантажувач на &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="192"/>
      <source>Setting up mount points.</source>
      <translation>Налаштування точок підключення.</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="95"/>
      <source>&lt;Restart checkbox tooltip&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Перезавантажити зараз</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="58"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="66"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;Все зроблено.&lt;/h1&gt;&lt;br/&gt;%1 встановлено на ваш комп'ютер.&lt;br/&gt;Ви можете перезавантажитися до вашої нової системи або продовжити використання Live-середовища %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="71"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="133"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="139"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;Встановлення зазнало невдачі&lt;/h1&gt;&lt;br/&gt;%1 не було встановлено на Ваш комп'ютер.&lt;br/&gt;Повідомлення про помилку: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="78"/>
      <source>Finish</source>
      <translation>Завершити</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="132"/>
      <source>Setup Complete</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="133"/>
      <source>Installation Complete</source>
      <translation>Встановлення завершено</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="135"/>
      <source>The setup of %1 is complete.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="136"/>
      <source>The installation of %1 is complete.</source>
      <translation>Встановлення %1 завершено.</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="41"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="52"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="63"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>Форматування розділу %1 з файловою системою %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="77"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Установник зазнав невдачі під час форматування розділу %1 на диску '%2'.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="126"/>
      <source>has at least %1 GiB available drive space</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="128"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="137"/>
      <source>has at least %1 GiB working memory</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="139"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="148"/>
      <source>is plugged in to a power source</source>
      <translation>підключена до джерела живлення</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Система не підключена до джерела живлення.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>is connected to the Internet</source>
      <translation>з'єднано з мережею Інтернет</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="157"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Система не з'єднана з мережею Інтернет.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="164"/>
      <source>is running the installer as an administrator (root)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="167"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Установник запущено без прав адміністратора.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="176"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>The screen is too small to display the setup program.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Екран замалий для відображення установника.</translation>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="68"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="40"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="37"/>
      <source>Creating initramfs.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
      <source>Konsole not installed</source>
      <translation>Konsole не встановлено</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>Будь ласка встановіть KDE Konsole і спробуйте знову!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>Виконується скрипт: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="47"/>
      <source>Script</source>
      <translation>Скрипт</translation>
    </message>
  </context>
  <context>
    <name>KeyboardPage</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="219"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>Встановити модель клавіатури як %1.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="223"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>Встановити розкладку клавіатури як %1/%2.</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
      <source>Keyboard</source>
      <translation>Клавіатура</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="32"/>
      <source>System locale setting</source>
      <translation>Налаштування системної локалі</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="39"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Налаштування системної локалі впливає на мову та набір символів для деяких елементів інтерфейсу командного рядку.&lt;br/&gt;Наразі встановлено &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="63"/>
      <source>&amp;Cancel</source>
      <translation>&amp;Скасувати</translation>
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
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="22"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>I accept the terms and conditions above.</source>
      <translation>Я приймаю положення та умови, що наведені вище.</translation>
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
      <translation>Ліцензія</translation>
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
      <translation>&lt;strong&gt;Драйвер %1&lt;/strong&gt;&lt;br/&gt;від %2</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;Графічний драйвер %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;від %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="130"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;Плагін для переглядача тенет %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;від %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="136"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;Кодек %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;від %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="142"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;Пакет %1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;від %2&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="148"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;від %2&lt;/font&gt;</translation>
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
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="259"/>
      <source>The system language will be set to %1.</source>
      <translation>Мову %1 буде встановлено як системну.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="260"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>%1 буде встановлено як локаль чисел та дат.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="124"/>
      <source>Region:</source>
      <translation>Регіон:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="125"/>
      <source>Zone:</source>
      <translation>Зона:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="126"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="127"/>
      <source>&amp;Change...</source>
      <translation>&amp;Змінити...</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="267"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>Встановити зону %1/%2.&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="99"/>
      <source>Location</source>
      <translation>Місцезнаходження</translation>
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
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
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
      <translation>Ім'я</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="62"/>
      <source>Description</source>
      <translation>Опис</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="109"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Встановлення через мережу. (Вимкнено: Неможливо отримати список пакетів, перевірте ваше підключення до мережі)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="119"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Встановлення через мережу. (Вимкнено: Отримано неправильні дані про групи)</translation>
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
      <translation>Вибір пакетів</translation>
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
      <translation>Пароль занадто короткий</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="73"/>
      <source>Password is too long</source>
      <translation>Пароль задовгий</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="149"/>
      <source>Password is too weak</source>
      <translation>Пароль надто ненадійний</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="157"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
      <source>Memory allocation error</source>
      <translation>Помилка виділення пам'яті</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
      <source>The password is the same as the old one</source>
      <translation>Цей пароль такий же як і старий</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
      <source>The password is a palindrome</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
      <source>The password differs with case changes only</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
      <source>The password is too similar to the old one</source>
      <translation>Цей пароль надто схожий на попередній</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
      <source>The password contains the user name in some form</source>
      <translation>Цей пароль якимось чином містить ім'я користувача 
</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Цей пароль містить слова зі справжнього імені користувача в якійсь із форм</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="177"/>
      <source>The password contains forbidden words in some form</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="181"/>
      <source>The password contains less than %1 digits</source>
      <translation>Цей пароль містить менше ніж %1 символ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
      <source>The password contains too few digits</source>
      <translation>Цей пароль містить  замало символів</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>The password contains less than %1 uppercase letters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
      <source>The password contains too few uppercase letters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
      <source>The password contains less than %1 lowercase letters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
      <source>The password contains too few lowercase letters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password contains less than %1 non-alphanumeric characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password is shorter than %1 characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
      <source>The password is too short</source>
      <translation>Цей пароль занадто короткий</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password is just rotated old one</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains less than %1 character classes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password does not contain enough character classes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains more than %1 same characters consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="230"/>
      <source>The password contains too many same characters consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="234"/>
      <source>The password contains more than %1 characters of the same class consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="238"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains monotonic sequence longer than %1 characters</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>No password supplied</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="254"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="260"/>
      <source>The password fails the dictionary check - %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password fails the dictionary check</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
      <source>Unknown setting - %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
      <source>Unknown setting</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>Bad integer value of setting - %1</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>Bad integer value</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="284"/>
      <source>Setting %1 is not of integer type</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>Setting is not of integer type</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Setting %1 is not of string type</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>Setting is not of string type</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="300"/>
      <source>Opening the configuration file failed</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The configuration file is malformed</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="304"/>
      <source>Fatal failure</source>
      <translation>Фатальна помилка</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown error</source>
      <translation>Невідома помилка</translation>
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
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="40"/>
      <source>Product Name</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="53"/>
      <source>TextLabel</source>
      <translation type="unfinished"/>
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
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
      <source>Keyboard Model:</source>
      <translation>Модель клавіатури:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
      <source>Type here to test your keyboard</source>
      <translation>Напишіть тут, щоб перевірити клавіатуру</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
      <source>What is your name?</source>
      <translation>Ваше ім'я?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="120"/>
      <source>What name do you want to use to log in?</source>
      <translation>Яке ім'я ви бажаєте використовувати для входу?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="321"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Оберіть пароль, щоб тримати ваш обліковий рахунок у безпеці.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="345"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="370"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Введіть один й той самий пароль двічі, для перевірки щодо помилок введення. Надійному паролю слід містити суміш літер, чисел та розділових знаків, бути довжиною хоча б вісім символів та регулярно змінюватись.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="219"/>
      <source>What is the name of this computer?</source>
      <translation>Ім'я цього комп'ютера?</translation>
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
      <translation>&lt;small&gt;Це ім'я буде використовуватись, якщо ви зробите комп'ютер видимим іншим у мережі.&lt;/small&gt;</translation>
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
      <translation>Входити автоматично без паролю.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="468"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Використовувати той самий пароль і для облікового рахунку адміністратора.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="491"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Оберіть пароль для облікового рахунку адміністратора.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="515"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="540"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Введіть один й той самий пароль двічі, для перевірки щодо помилок введення.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Root</source>
      <translation>Корінь</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="200"/>
      <source>Home</source>
      <translation>Домівка</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>Boot</source>
      <translation>Завантажувальний розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
      <source>EFI system</source>
      <translation>EFI-система</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>Область підкачки</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="209"/>
      <source>New partition for %1</source>
      <translation>Новий розділ для %1</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition</source>
      <translation>Новий розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="230"/>
      <source>%1  %2</source>
      <extracomment>size[number] filesystem[name]</extracomment>
      <translation>%1  %2</translation>
    </message>
  </context>
  <context>
    <name>PartitionModel</name>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="144"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="176"/>
      <source>Free Space</source>
      <translation>Вільний простір</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="148"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="180"/>
      <source>New partition</source>
      <translation>Новий розділ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="264"/>
      <source>Name</source>
      <translation>Ім'я</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="266"/>
      <source>File System</source>
      <translation>Файлова система</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="268"/>
      <source>Mount Point</source>
      <translation>Точка підключення</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="270"/>
      <source>Size</source>
      <translation>Розмір</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
      <source>Storage de&amp;vice:</source>
      <translation>&amp;Пристрій зберігання:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
      <source>&amp;Revert All Changes</source>
      <translation>Скинути всі &amp;зміни</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
      <source>New Partition &amp;Table</source>
      <translation>Нова &amp;таблиця розділів</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
      <source>Cre&amp;ate</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
      <source>&amp;Edit</source>
      <translation>&amp;Редагувати</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
      <source>&amp;Delete</source>
      <translation>&amp;Видалити</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
      <source>New Volume Group</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
      <source>Resize Volume Group</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
      <source>Deactivate Volume Group</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
      <source>Remove Volume Group</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="209"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>Ви впевнені, що бажаєте створити нову таблицю розділів на %1?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="238"/>
      <source>Can not create new partition</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="239"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="78"/>
      <source>Gathering system information...</source>
      <translation>Збір інформації про систему...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="130"/>
      <source>Partitions</source>
      <translation>Розділи</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="167"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>Встановити %1 &lt;strong&gt;поруч&lt;/strong&gt; з іншою операційною системою.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>&lt;strong&gt;Очистити&lt;/strong&gt; диск та встановити %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="175"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>&lt;strong&gt;Замінити&lt;/strong&gt; розділ на %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="180"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>Розподілення диску &lt;strong&gt;власноруч&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="193"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>Встановити %1 &lt;strong&gt;поруч&lt;/strong&gt; з іншою операційною системою на диск &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="199"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;Очистити&lt;/strong&gt; диск &lt;strong&gt;%2&lt;/strong&gt; (%3) та встановити %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="205"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;Замінити&lt;/strong&gt; розділ на диску &lt;strong&gt;%2&lt;/strong&gt; (%3) на %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="212"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>Розподілення диску &lt;strong&gt;%1&lt;/strong&gt; (%2) &lt;strong&gt;власноруч&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="220"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>Диск &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="248"/>
      <source>Current:</source>
      <translation>Зараз:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="265"/>
      <source>After:</source>
      <translation>Після:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="415"/>
      <source>No EFI system partition configured</source>
      <translation>Не налаштовано жодного системного розділу EFI</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="416"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Щоб запустити %1, потрібен системний розділ EFI.&lt;br/&gt;&lt;br/&gt;Щоб налаштувати системний розділ EFI, поверніться та оберіть або створіть файлову систему FAT32 з увімкненною опцією &lt;strong&gt;esp&lt;/strong&gt; та точкою підключення &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;Ви можете продовжити не налаштовуючи системний розділ EFI, але ваша система може не запускатись.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="429"/>
      <source>EFI system partition flag not set</source>
      <translation>Опцію системного розділу EFI не встановлено</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="430"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation>Для запуску %1 потрібен системний розділ EFI.&lt;br/&gt;&lt;br/&gt;Розділ налаштовано з точкою підключення &lt;strong&gt;%2&lt;/strong&gt;, але опція &lt;strong&gt;esp&lt;/strong&gt; не встановлено.&lt;br/&gt;Щоб встановити опцію, поверніться та відредагуйте розділ.&lt;br/&gt;&lt;br/&gt;Ви можете продовжити не налаштовуючи цю опцію, але ваша система може не запускатись.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="465"/>
      <source>Boot partition not encrypted</source>
      <translation>Завантажувальний розділ незашифрований</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="466"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Було налаштовано окремий завантажувальний розділ поряд із зашифрованим кореневим розділом, але завантажувальний розділ незашифрований.&lt;br/&gt;&lt;br/&gt;Існують проблеми з безпекою такого типу, оскільки важливі системні файли зберігаються на незашифрованому розділі.&lt;br/&gt;Ви можете продовжувати, якщо бажаєте, але розблокування файлової системи відбудеться пізніше під час запуску системи.&lt;br/&gt;Щоб зашифрувати завантажувальний розділ, поверніться і створіть його знов, обравши &lt;strong&gt;Зашифрувати&lt;/strong&gt; у вікні створення розділів.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="650"/>
      <source>has at least one disk device available.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="651"/>
      <source>There are no partitons to install on.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="70"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="76"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="68"/>
      <source>Look-and-Feel</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="84"/>
      <source>Saving files for later ...</source>
      <translation>Збереження файлів на потім ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="122"/>
      <source>No files configured to save for later.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="176"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="407"/>
      <source>
There was no output from the command.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="408"/>
      <source>
Output:
</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="412"/>
      <source>External command crashed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="413"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>External command failed to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="419"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>Internal error when starting command.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Bad parameters for process job call.</source>
      <translation>Неправильні параметри визову завдання обробки.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="428"/>
      <source>External command failed to finish.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="436"/>
      <source>External command finished with errors.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="437"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="91"/>
      <source>Default Keyboard Model</source>
      <translation>Модель клавіатури за замовченням</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="133"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="168"/>
      <source>Default</source>
      <translation>За замовченням</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="207"/>
      <source>unknown</source>
      <translation>невідома</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="209"/>
      <source>extended</source>
      <translation>розширена</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="211"/>
      <source>unformatted</source>
      <translation>неформатовано</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="213"/>
      <source>swap</source>
      <translation>область підкачки</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="51"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>Нерозподілений простір або невідома таблиця розділів</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="47"/>
      <source>(no mount point)</source>
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="41"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
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
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="135"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>Оберіть, куди встановити %1.&lt;br/&gt;&lt;font color="red"&gt;Увага: &lt;/font&gt;це знищить всі файли на обраному розділі.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="161"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>Вибраний елемент не є дійсним розділом.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="169"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 не можна встановити на порожній простір. Будь ласка, оберіть дійсний розділ.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="179"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 не можна встановити на розширений розділ. Будь ласка, оберіть дійсний первинний фбо логічний розділ.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="189"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>%1 не можна встановити на цей розділ.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="195"/>
      <source>Data partition (%1)</source>
      <translation>Розділ з даними (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="212"/>
      <source>Unknown system partition (%1)</source>
      <translation>Невідомий системний розділ (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="217"/>
      <source>%1 system partition (%2)</source>
      <translation>Системний розділ %1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="228"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Розділ %1 замалий для %2. Будь ласка оберіть розділ розміром хоча б %3 Гб.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="251"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Системний розділ EFI у цій системі не знайдено. Для встановлення %1, будь ласка, поверніться назад і скористайтеся розподіленням вручну.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="262"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="279"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="303"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 буде встановлено на %2.&lt;br/&gt;&lt;font color="red"&gt;Увага: &lt;/font&gt;всі дані на розділі %2 буде загублено.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="271"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>Системний розділ EFI на %1 буде використано для запуску %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="287"/>
      <source>EFI system partition:</source>
      <translation>Системний розділ EFI:</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="59"/>
      <source>Resize Filesystem Job</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="172"/>
      <source>Invalid configuration</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="173"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation type="unfinished"/>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="207"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="208"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="216"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="229"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="230"/>
      <source>The device %1 cannot be resized.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="238"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="239"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="48"/>
      <source>Resize partition %1.</source>
      <translation>Змінити розмір розділу %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="55"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="66"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="85"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Установник зазнав невдачі під час зміни розміру розділу %1 на диску '%2'.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="39"/>
      <source>Resize Volume Group</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="55"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="46"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="70"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="137"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>Щоб отримати найкращий результат, будь-ласка переконайтеся, що цей комп'ютер:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="138"/>
      <source>System requirements</source>
      <translation>Системні вимоги</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="263"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="267"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>Цей комп'ютер не задовільняє мінімальним вимогам для встановлення %1.&lt;br/&gt;Встановлення неможливо продовжити. &lt;a href="#details"&gt;Докладніше...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="274"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="278"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Цей комп'ютер не задовільняє рекомендованим вимогам для встановлення %1.&lt;br/&gt;Встановлення можна продовжити, але деякі особливості можуть бути вимкненими.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="287"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Ця програма поставить кілька питань та встановить %2 на ваш комп'ютер.</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
      <source>Scanning storage devices...</source>
      <translation>Скануємо пристрої зберігання...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
      <source>Partitioning</source>
      <translation>Розподілюємо на розділи</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="39"/>
      <source>Set hostname %1</source>
      <translation>Встановити ім'я машини %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="46"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Встановити ім'я машини &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="53"/>
      <source>Setting hostname %1.</source>
      <translation>Встановлення імені машини %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="64"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="71"/>
      <source>Internal Error</source>
      <translation>Внутрішня помилка</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="78"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="89"/>
      <source>Cannot write hostname to target system</source>
      <translation>Не можу записати ім'я машини до системи</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>Встановити модель клавіатури %1, розкладку %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>Невдача під час запису кофігурації клавіатури для віртуальної консолі.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="322"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="326"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="332"/>
      <source>Failed to write to %1</source>
      <translation>Невдача під час запису до %1</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>Невдача під час запису конфігурації клавіатури для X11.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>Невдача під час запису кофігурації клавіатури до наявної директорії /etc/default.</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="49"/>
      <source>Set flags on partition %1.</source>
      <translation>Встановити прапорці на розділі %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="56"/>
      <source>Set flags on new partition.</source>
      <translation>Встановити прапорці на новому розділі.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="67"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Очистити прапорці на розділі &lt;strong&gt;%1&lt;/strong&gt;.</translation>
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
      <translation>Очистити прапорці на новому розділі.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="79"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>Встановити прапорці &lt;strong&gt;%2&lt;/strong&gt; для розділу &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="91"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Встановити прапорці &lt;strong&gt;%1&lt;/strong&gt; для нового розділу.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="103"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Очищуємо прапорці для розділу &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="111"/>
      <source>Clearing flags on new partition.</source>
      <translation>Очищуємо прапорці для нового розділу.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="115"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Встановлюємо прапорці &lt;strong&gt;%2&lt;/strong&gt; для розділу &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="127"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>Встановлюємо прапорці &lt;strong&gt;%1&lt;/strong&gt; для нового розділу.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="144"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Установник зазнав невдачі під час встановлення прапорців для розділу %1.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
      <source>Set password for user %1</source>
      <translation>Встановити пароль для користувача %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
      <source>Setting password for user %1.</source>
      <translation>Встановлення паролю для користувача %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
      <source>Bad destination system path.</source>
      <translation>Поганий шлях призначення системи.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
      <source>rootMountPoint is %1</source>
      <translation>Коренева точка підключення %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="119"/>
      <source>Cannot disable root account.</source>
      <translation>Не можу відключити обліковий запис root.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="120"/>
      <source>passwd terminated with error code %1.</source>
      <translation>passwd завершив роботу з кодом помилки %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="128"/>
      <source>Cannot set password for user %1.</source>
      <translation>Не можу встановити пароль для користувача %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="129"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod завершилася з кодом помилки %1.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
      <source>Set timezone to %1/%2</source>
      <translation>Встановити часову зону %1.%2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot access selected timezone path.</source>
      <translation>Не можу дістатися до шляху обраної часової зони.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Bad path: %1</source>
      <translation>Поганий шлях: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <translation>Не можу встановити часову зону.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>Невдача під час створення посилання, ціль: %1, назва посилання: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
      <source>Cannot set timezone,</source>
      <translation>Не можу встановити часову зону,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>Не можу відкрити /etc/timezone для запису</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="46"/>
      <source>Shell Processes Job</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>SlideCounter</name>
    <message>
      <location filename="../src/qml/calamares/slideshow/SlideCounter.qml" line="36"/>
      <source>%L1 / %L2</source>
      <extracomment>slide counter, %1 of %2 (numeric)</extracomment>
      <translation type="unfinished"/>
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
      <translation>Це огляд того, що трапиться коли ви почнете процедуру встановлення.</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
      <source>Summary</source>
      <translation>Огляд</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="42"/>
      <source>Installation feedback</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="54"/>
      <source>Sending installation feedback.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Internal error in install-tracking.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="72"/>
      <source>HTTP request timed out.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingMachineNeonJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="80"/>
      <source>Machine feedback</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="92"/>
      <source>Configuring machine feedback.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="117"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="123"/>
      <source>Error in machine feedback configuration.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="118"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
      <source>Form</source>
      <translation>Форма</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
      <source>Placeholder</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
      <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="49"/>
      <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="51"/>
      <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="54"/>
      <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="64"/>
      <source>Feedback</source>
      <translation type="unfinished"/>
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
      <translation>Ваше ім'я задовге.</translation>
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
      <translation>Ім'я машини занадто коротке.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="397"/>
      <source>Your hostname is too long.</source>
      <translation>Ім'я машини задовге.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="421"/>
      <source>Your passwords do not match!</source>
      <translation>Паролі не збігаються!</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="55"/>
      <source>Users</source>
      <translation>Користувачі</translation>
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
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
      <source>Create Volume Group</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
      <source>List of Physical Volumes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
      <source>Volume Group Name:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
      <source>Volume Group Type:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
      <source>Physical Extent Size:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
      <source> MiB</source>
      <translation> МіБ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
      <source>Total Size:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
      <source>Used Size:</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
      <source>Total Sectors:</source>
      <translation type="unfinished"/>
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
      <translation>Форма</translation>
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
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="143"/>
      <source>&amp;Donate</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>Open help and support website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>Open issues and bug-tracking website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>Open release notes website</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="182"/>
      <source>&amp;Release notes</source>
      <translation>При&amp;мітки до випуску</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="169"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Відомі проблеми</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
      <source>&amp;Support</source>
      <translation>Під&amp;тримка</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="130"/>
      <source>&amp;About</source>
      <translation>&amp;Про</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="254"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Ласкаво просимо до установника %1.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="253"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Ласкаво просимо до установника для %1 Calamares.&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="248"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="266"/>
      <source>About %1 setup</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="266"/>
      <source>About %1 installer</source>
      <translation>Про втановлювач %1</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="269"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2019 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="259"/>
      <source>%1 support</source>
      <translation>Підтримка %1</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="62"/>
      <source>Welcome</source>
      <translation>Вітаємо</translation>
    </message>
  </context>
</TS>

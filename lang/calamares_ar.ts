<?xml version="1.0" ?><!DOCTYPE TS><TS language="ar" version="2.1">
<context>
    <name>BootInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="69"/>
        <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
        <translation>&lt;strong&gt;بيئة الإقلاع&lt;/strong&gt; لهذا النّظام.&lt;br&gt;&lt;br&gt;أنظمة x86 القديمة تدعم &lt;strong&gt;BIOS&lt;/strong&gt; فقط.&lt;br&gt;غالبًا ما تستخدم الأنظمة الجديدة &lt;strong&gt;EFI&lt;/strong&gt;، ولكن ما زال بإمكانك إظهاره ك‍ BIOS إن بدأته بوضع التّوافقيّة.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="79"/>
        <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
        <translation>بدأ هذا النّظام ببيئة إقلاع &lt;strong&gt;EFI&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;لضبط البدء من بيئة EFI، يجب على المثبّت وضع تطبيق محمّل إقلاع، مثل &lt;strong&gt;GRUB&lt;/strong&gt; أو &lt;strong&gt;systemd-boot&lt;/strong&gt; على &lt;strong&gt;قسم نظام EFI&lt;/strong&gt;. هذا الأمر آليّ، إلّا إن اخترت التّقسيم يدويًّا، حيث عليك اخيتاره أو إنشاؤه بنفسك.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="91"/>
        <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
        <translation>بدأ هذا النّظام ببيئة إقلاع &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;لضبط البدء من بيئة BIOS، يجب على المثبّت وضع تطبيق محمّل إقلاع، مثل &lt;strong&gt;GRUB&lt;/strong&gt;، إمّا في بداية قسم أو في &lt;strong&gt;قطاع الإقلاع الرّئيس&lt;/strong&gt; قرب بداية جدول التّقسيم (محبّذ). هذا الأمر آليّ، إلّا إن اخترت التّقسيم يدويًّا، حيث عليك اخيتاره أو إنشاؤه بنفسك.</translation>
    </message>
</context>
<context>
    <name>BootLoaderModel</name>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="59"/>
        <source>Master Boot Record of %1</source>
        <translation>قطاع الإقلاع الرئيسي ل %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="76"/>
        <source>Boot Partition</source>
        <translation>قسم الإقلاع</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="81"/>
        <source>System Partition</source>
        <translation>قسم النظام</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="111"/>
        <source>Do not install a boot loader</source>
        <translation>لا تثبّت محمّل إقلاع</translation>
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
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="24"/>
        <source>GlobalStorage</source>
        <translation>التّخزين العموميّ</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="34"/>
        <source>JobQueue</source>
        <translation>صفّ المهامّ</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="44"/>
        <source>Modules</source>
        <translation>الوحدا</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="57"/>
        <source>Type:</source>
        <translation>النوع:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="64"/>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="78"/>
        <source>none</source>
        <translation>لاشيء</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="71"/>
        <source>Interface:</source>
        <translation>الواجهة:</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.ui" line="93"/>
        <source>Tools</source>
        <translation>الأدوات</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/utils/DebugWindow.cpp" line="182"/>
        <source>Debug information</source>
        <translation>معلومات التّنقيح</translation>
    </message>
</context>
<context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
        <location filename="../src/libcalamaresui/ExecutionViewStep.cpp" line="77"/>
        <source>Install</source>
        <translation>ثبت </translation>
    </message>
</context>
<context>
    <name>Calamares::JobThread</name>
    <message>
        <location filename="../src/libcalamares/JobQueue.cpp" line="89"/>
        <source>Done</source>
        <translation>انتهى</translation>
    </message>
</context>
<context>
    <name>Calamares::ProcessJob</name>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="51"/>
        <source>Run command %1 %2</source>
        <translation>شغّل الأمر 1% 2%</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="60"/>
        <source>Running command %1 %2</source>
        <translation>يشغّل الأمر 1% 2%</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="89"/>
        <source>External command crashed</source>
        <translation>انهار الأمر الخارجيّ</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="90"/>
        <source>Command %1 crashed.
Output:
%2</source>
        <translation>انهار الأمر %1.
الخرج:
%2</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="95"/>
        <source>External command failed to start</source>
        <translation>فشل الأمر الخارجي في البدء</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="96"/>
        <source>Command %1 failed to start.</source>
        <translation>فشل الأمر %1 في البدء</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="100"/>
        <source>Internal error when starting command</source>
        <translation>حدث خطأ داخلي أثناء بدء الأمر</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="101"/>
        <source>Bad parameters for process job call.</source>
        <translation>معاملات نداء المهمة سيّئة.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="104"/>
        <source>External command failed to finish</source>
        <translation>فشل الأمر الخارجي بالانتهاء</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="105"/>
        <source>Command %1 failed to finish in %2s.
Output:
%3</source>
        <translation>فشل الأمر %1 بالانتهاء خلال %2 ثانية.
الخرج:
%3</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="111"/>
        <source>External command finished with errors</source>
        <translation>انتهى الأمر الخارجي مع وجود أخطاء</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/ProcessJob.cpp" line="112"/>
        <source>Command %1 finished with exit code %2.
Output:
%3</source>
        <translation>انتهى الأمر %1 بشيفرة خروج %2.
الخرج:
%3</translation>
    </message>
</context>
<context>
    <name>Calamares::PythonJob</name>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="265"/>
        <source>Running %1 operation.</source>
        <translation>يشغّل عمليّة %1.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="280"/>
        <source>Bad working directory path</source>
        <translation>مسار سيء لمجلد العمل</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="281"/>
        <source>Working directory %1 for python job %2 is not readable.</source>
        <translation>لا يمكن القراءة من مجلد العمل %1 الخاص بعملية بايثون %2.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="291"/>
        <source>Bad main script file</source>
        <translation>ملفّ السّكربت الرّئيس سيّء.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="292"/>
        <source>Main script file %1 for python job %2 is not readable.</source>
        <translation>ملفّ السّكربت الرّئيس %1 لمهمّة بايثون %2 لا يمكن قراءته.</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonJob.cpp" line="368"/>
        <source>Boost.Python error in job &quot;%1&quot;.</source>
        <translation>خطأ Boost.Python في العمل &quot;%1&quot;.</translation>
    </message>
</context>
<context>
    <name>Calamares::ViewManager</name>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="73"/>
        <source>&amp;Back</source>
        <translation>&amp;رجوع</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="74"/>
        <source>&amp;Next</source>
        <translation>&amp;التالي</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="75"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="300"/>
        <source>&amp;Cancel</source>
        <translation>&amp;إلغاء</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="76"/>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="301"/>
        <source>Cancel installation without changing the system.</source>
        <translation>الغاء الـ تثبيت من دون احداث تغيير في النظام</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="99"/>
        <source>Cancel installation?</source>
        <translation>إلغاء التثبيت؟</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="100"/>
        <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
        <translation>أتريد إلغاء عمليّة التّثبيت الحاليّة؟
سيخرج المثبّت وتضيع كلّ التّغييرات.</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="105"/>
        <source>&amp;Yes</source>
        <translation>&amp;نعم</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="106"/>
        <source>&amp;No</source>
        <translation>&amp;لا</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="183"/>
        <source>&amp;Close</source>
        <translation>&amp;اغلاق</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="233"/>
        <source>Continue with setup?</source>
        <translation>الإستمرار في التثبيت؟</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="234"/>
        <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
        <translation>مثبّت %1 على وشك بإجراء تعديلات على قرصك لتثبيت %2.&lt;br/&gt;&lt;strong&gt;لن تستطيع التّراجع عن هذا.&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="239"/>
        <source>&amp;Install now</source>
        <translation>&amp;ثبت الأن</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="240"/>
        <source>Go &amp;back</source>
        <translation>&amp;إرجع</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="269"/>
        <source>&amp;Done</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="270"/>
        <source>The installation is complete. Close the installer.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="180"/>
        <source>Error</source>
        <translation>خطأ</translation>
    </message>
    <message>
        <location filename="../src/libcalamaresui/ViewManager.cpp" line="181"/>
        <source>Installation Failed</source>
        <translation>فشل التثبيت</translation>
    </message>
</context>
<context>
    <name>CalamaresPython::Helper</name>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="263"/>
        <source>Unknown exception type</source>
        <translation>نوع الاستثناء غير معروف</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="276"/>
        <source>unparseable Python error</source>
        <translation>خطأ بايثون لا يمكن تحليله</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="292"/>
        <source>unparseable Python traceback</source>
        <translation>تتبّع بايثون خلفيّ لا يمكن تحليله</translation>
    </message>
    <message>
        <location filename="../src/libcalamares/PythonHelper.cpp" line="296"/>
        <source>Unfetchable Python error.</source>
        <translation>خطأ لا يمكن الحصول علية في بايثون.</translation>
    </message>
</context>
<context>
    <name>CalamaresWindow</name>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="45"/>
        <source>%1 Installer</source>
        <translation>%1 المثبت</translation>
    </message>
    <message>
        <location filename="../src/calamares/CalamaresWindow.cpp" line="112"/>
        <source>Show debug information</source>
        <translation>أظهر معلومات التّنقيح</translation>
    </message>
</context>
<context>
    <name>CheckFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="39"/>
        <source>Checking file system on partition %1.</source>
        <translation>يفحص نظام الملفّات في القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CheckFileSystemJob.cpp" line="77"/>
        <source>The file system check on partition %1 failed.</source>
        <translation>فشل فحص نظام الملفّات في القسم %1.</translation>
    </message>
</context>
<context>
    <name>CheckerWidget</name>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="96"/>
        <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href=&quot;#details&quot;&gt;Details...&lt;/a&gt;</source>
        <translation>لا يستوفِ هذا الحاسوب أدنى متطلّبات تثبيت %1.&lt;br/&gt;لا يمكن متابعة التّثبيت. &lt;a href=&quot;#details&quot;&gt;التّفاصيل...&lt;/a&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="113"/>
        <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
        <translation>لا يستوفِ هذا الحاسوب بعض المتطلّبات المستحسنة لتثبيت %1.&lt;br/&gt;يمكن للمثبّت المتابعة، ولكن قد تكون بعض الميزات معطّلة.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="151"/>
        <source>This program will ask you some questions and set up %2 on your computer.</source>
        <translation>سيطرح البرنامج بعض الأسئلة عليك ويعدّ %2 على حاسوبك.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="174"/>
        <source>For best results, please ensure that this computer:</source>
        <translation>لأفضل النّتائج، تحقّق من أن الحاسوب:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/CheckerWidget.cpp" line="202"/>
        <source>System requirements</source>
        <translation>متطلّبات النّظام</translation>
    </message>
</context>
<context>
    <name>ChoicePage</name>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="128"/>
        <source>After:</source>
        <translation>بعد:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="235"/>
        <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
        <translation>&lt;strong&gt;تقسيم يدويّ&lt;/strong&gt;&lt;br/&gt;يمكنك إنشاء أو تغيير حجم الأقسام بنفسك.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="978"/>
        <source>Boot loader location:</source>
        <translation>مكان محمّل الإقلاع:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="922"/>
        <source>%1 will be shrunk to %2MB and a new %3MB partition will be created for %4.</source>
        <translation>سيتقلّص %1 إلى %2م.بايت وقسم %3م.بايت آخر جديد سيُنشأ ل‍%4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="126"/>
        <source>Select storage de&amp;vice:</source>
        <translation>اختر &amp;جهاز التّخزين:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="127"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="904"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="950"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1029"/>
        <source>Current:</source>
        <translation>الحاليّ:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="775"/>
        <source>Reuse %1 as home partition for %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="905"/>
        <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;اختر قسمًا لتقليصه، ثمّ اسحب الشّريط السّفليّ لتغيير حجمه &lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1020"/>
        <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
        <translation>&lt;strong&gt;اختر القسم حيث سيكون التّثبيت عليه&lt;/strong&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1076"/>
        <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>تعذّر إيجاد قسم النّظام EFI في أيّ مكان. فضلًا ارجع واستخدم التّقسيم اليدويّ لإعداد %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1085"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>قسم النّظام EFI على %1 سيُستخدم لبدء %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1093"/>
        <source>EFI system partition:</source>
        <translation>قسم نظام EFI:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1177"/>
        <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>لا يبدو أن في جهاز التّخزين أيّ نظام تشغيل. ما الذي تودّ فعله؟&lt;br/&gt;يمكنك مراجعة الاختيارات وتأكيدها قبل تطبيقها على جهاز التّخزين.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1182"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1219"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1241"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1265"/>
        <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color=&quot;red&quot;&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
        <translation>&lt;strong&gt;مسح القرص&lt;/strong&gt;&lt;br/&gt;هذا س&lt;font color=&quot;red&quot;&gt;يمسح&lt;/font&gt; كلّ البيانات الموجودة في جهاز التّخزين المحدّد.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1209"/>
        <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>على جهاز التّخزين %1. ما الذي تودّ فعله؟&lt;br/&gt;يمكنك مراجعة الاختيارات وتأكيدها قبل تطبيقها على جهاز التّخزين.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1186"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1215"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1237"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1261"/>
        <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
        <translation>&lt;strong&gt;ثبّت جنبًا إلى جنب&lt;/strong&gt;&lt;br/&gt;سيقلّص المثبّت قسمًا لتفريغ مساحة لِ‍ %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1190"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1224"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1245"/>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1269"/>
        <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
        <translation>&lt;strong&gt;استبدل قسمًا&lt;/strong&gt;&lt;br/&gt;يستبدل قسمًا مع %1 .</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1232"/>
        <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>على جهاز التّخزين هذا نظام تشغيل ذأصلًا. ما الذي تودّ فعله؟&lt;br/&gt;يمكنك مراجعة الاختيارات وتأكيدها قبل تطبيقها على جهاز التّخزين.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1256"/>
        <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
        <translation>على جهاز التّخزين هذا عدّة أنظمة تشغيل. ما الذي تودّ فعله؟&lt;br/&gt;يمكنك مراجعة الاختيارات وتأكيدها قبل تطبيقها على جهاز التّخزين.</translation>
    </message>
</context>
<context>
    <name>ClearMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="45"/>
        <source>Clear mounts for partitioning operations on %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="53"/>
        <source>Clearing mounts for partitioning operations on %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="190"/>
        <source>Cleared all mounts for %1</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ClearTempMountsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
        <source>Clear all temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
        <source>Clearing all temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="60"/>
        <source>Cannot get list of temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="99"/>
        <source>Cleared all temporary mounts.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>CreatePartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
        <source>Create a Partition</source>
        <translation>أنشئ قسمًا</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
        <source> MiB</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
        <source>Partition &amp;Type:</source>
        <translation>&amp;نوع القسم:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
        <source>&amp;Primary</source>
        <translation>أ&amp;ساسيّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
        <source>E&amp;xtended</source>
        <translation>ممت&amp;دّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
        <source>Fi&amp;le System:</source>
        <translation>نظام المل&amp;فّات:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="178"/>
        <source>Flags:</source>
        <translation>الشّارات:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
        <source>&amp;Mount Point:</source>
        <translation>نقطة ال&amp;ضّمّ:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
        <source>Si&amp;ze:</source>
        <translation>الح&amp;جم:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="66"/>
        <source>En&amp;crypt</source>
        <translation>تشفير</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="162"/>
        <source>Logical</source>
        <translation>منطقيّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="167"/>
        <source>Primary</source>
        <translation>أساسيّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="184"/>
        <source>GPT</source>
        <translation>GPT</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="269"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>CreatePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="50"/>
        <source>Create new %2MB partition on %4 (%3) with file system %1.</source>
        <translation>أنشئ قسم %2م.بايت جديد على %4 (%3) بنظام الملفّات %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="61"/>
        <source>Create new &lt;strong&gt;%2MB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>أنشئ قسم &lt;strong&gt;%2م.بايت&lt;/strong&gt; جديد على &lt;strong&gt;%4&lt;/strong&gt; (%3) بنظام الملفّات &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="73"/>
        <source>Creating new %1 partition on %2.</source>
        <translation>ينشئ قسم %1 جديد على %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="85"/>
        <source>The installer failed to create partition on disk &apos;%1&apos;.</source>
        <translation>فشل المثبّت في إنشاء قسم على القرص &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="94"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>تعذّر فتح الجهاز &apos;%1&apos;:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="104"/>
        <source>Could not open partition table.</source>
        <translation>تعذّر فتح جدول التّقسيم.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="128"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>فشل المثبّت في إنشاء نظام ملفّات على القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="136"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>فشل المثبّت في تحديث جدول التّقسيم على القرص &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
        <source>Create Partition Table</source>
        <translation>أنشئ جدول تقسيم</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
        <source>Creating a new partition table will delete all existing data on the disk.</source>
        <translation>إنشاء جدول تقسيم جددي سيحذف كلّ البيانات على القرص.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
        <source>What kind of partition table do you want to create?</source>
        <translation>ما نوع جدول التّقسيم الذي تريد إنشاءه؟</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
        <source>Master Boot Record (MBR)</source>
        <translation>قطاع إقلاع رئيس (MBR)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
        <source>GUID Partition Table (GPT)</source>
        <translation>جدول أقسام GUID ‏(GPT)</translation>
    </message>
</context>
<context>
    <name>CreatePartitionTableJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="50"/>
        <source>Create new %1 partition table on %2.</source>
        <translation>أنشئ جدول تقسيم %1 جديد على %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="57"/>
        <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation>أنشئ جدول تقسيم &lt;strong&gt;%1&lt;/strong&gt; جديد على &lt;strong&gt;%2&lt;/strong&gt; (%3).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="67"/>
        <source>Creating new %1 partition table on %2.</source>
        <translation>ينشئ جدول التّقسيم %1 الجديد على %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="77"/>
        <source>The installer failed to create a partition table on %1.</source>
        <translation>فشل المثبّت في إنشاء جدول تقسيم على %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="85"/>
        <source>Could not open device %1.</source>
        <translation>تعذّر فتح الجهاز %1.</translation>
    </message>
</context>
<context>
    <name>CreateUserJob</name>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="50"/>
        <source>Create user %1</source>
        <translation>أنشئ المستخدم %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="57"/>
        <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>أنشئ المستخدم &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="64"/>
        <source>Creating user %1.</source>
        <translation>ينشئ المستخدم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="80"/>
        <source>Sudoers dir is not writable.</source>
        <translation>دليل Sudoers لا يمكن الكتابة فيه.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="84"/>
        <source>Cannot create sudoers file for writing.</source>
        <translation>تعذّر إنشاء ملفّ sudoers للكتابة.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="92"/>
        <source>Cannot chmod sudoers file.</source>
        <translation>تعذّر تغيير صلاحيّات ملفّ sudores.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
        <source>Cannot open groups file for reading.</source>
        <translation>تعذّر فتح ملفّ groups للقراءة.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="159"/>
        <source>Cannot create user %1.</source>
        <translation>تعذّر إنشاء المستخدم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="161"/>
        <source>useradd terminated with error code %1.</source>
        <translation>أُنهي useradd برمز الخطأ %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="170"/>
        <source>Cannot add user %1 to groups: %2.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="173"/>
        <source>usermod terminated with error code %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="183"/>
        <source>Cannot set home directory ownership for user %1.</source>
        <translation>تعذّر تعيين مالك دليل المستخدم ليكون %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/CreateUserJob.cpp" line="185"/>
        <source>chown terminated with error code %1.</source>
        <translation>أُنهي chown برمز الخطأ %1.</translation>
    </message>
</context>
<context>
    <name>DeletePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="43"/>
        <source>Delete partition %1.</source>
        <translation>احذف القسم %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="51"/>
        <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>احذف القسم &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="59"/>
        <source>Deleting partition %1.</source>
        <translation>يحذف القسم %1 .</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="68"/>
        <source>The installer failed to delete partition %1.</source>
        <translation>فشل المثبّت في حذف القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="74"/>
        <source>Partition (%1) and device (%2) do not match.</source>
        <translation>لا يتوافق القسم (%1) مع الجهاز (%2).</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="86"/>
        <source>Could not open device %1.</source>
        <translation>تعذّر فتح الجهاز %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="95"/>
        <source>Could not open partition table.</source>
        <translation>تعذّر فتح جدول التّقسيم.</translation>
    </message>
</context>
<context>
    <name>DeviceInfoWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="150"/>
        <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
        <translation>نوع &lt;strong&gt;جدول التّقسيم&lt;/strong&gt; على جهاز التّخزين المحدّد.&lt;br&gt;&lt;br&gt;الطّريقة الوحيدة لتغيير النّوع هو بحذفه وإعادة إنشاء جدول التّقسيم من الصّفر، ممّا سيؤدّي إلى تدمير كلّ البيانات في جهاز التّخزين.&lt;br&gt;سيبقي هذا المثبّت جدول التّقسيم الحاليّ كما هو إلّا إن لم ترد ذلك.&lt;br&gt;إن لم تكن متأكّدًا، ف‍ GPT مستحسن للأنظمة الحديثة.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="107"/>
        <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
        <translation>للجهاز جدول تقسيم &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="114"/>
        <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="121"/>
        <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
        <translation>&lt;strong&gt;تعذّر اكتشاف جدول تقسيم&lt;/strong&gt; على جهاز التّخزين المحدّد.&lt;br&gt;&lt;br&gt;إمّا أن لا جدول تقسيم في الجهاز، أو أنه معطوب أو نوعه مجهول.&lt;br&gt;يمكن لهذا المثبّت إنشاء جدول تقسيم جديد، آليًّا أ, عبر صفحة التّقسيم اليدويّ.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="131"/>
        <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
        <translation>&lt;br&gt;&lt;br&gt;هذا هو نوع جدول التّقسيم المستحسن للأنظمة الحديثة والتي تبدأ ببيئة إقلاع &lt;strong&gt;EFI&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="137"/>
        <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
        <translation type="unfinished"/>
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
    <name>DracutLuksCfgJob</name>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="131"/>
        <source>Write LUKS configuration for Dracut to %1</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="133"/>
        <source>Skip writing LUKS configuration for Dracut: &quot;/&quot; partition is not encrypted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="149"/>
        <source>Failed to open %1</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>DummyCppJob</name>
    <message>
        <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
        <source>Dummy C++ Job</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>EditExistingPartitionDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
        <source>Edit Existing Partition</source>
        <translation>حرّر قسمًا موجودًا</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
        <source>Content:</source>
        <translation>المحتوى:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
        <source>&amp;Keep</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
        <source>Format</source>
        <translation>هيّئ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
        <source>Warning: Formatting the partition will erase all existing data.</source>
        <translation>تحذير: تهيئة القسم ستمسح بياناته كلّها.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
        <source>&amp;Mount Point:</source>
        <translation>نقطة ال&amp;ضّمّ:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
        <source>Si&amp;ze:</source>
        <translation>الح&amp;جم:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
        <source> MiB</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
        <source>Fi&amp;le System:</source>
        <translation>نظام المل&amp;فّات:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
        <source>Flags:</source>
        <translation>الشّارات:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="307"/>
        <source>Mountpoint already in use. Please select another one.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>EncryptWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
        <source>En&amp;crypt system</source>
        <translation>ع&amp;مِّ النّظام</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
        <source>Passphrase</source>
        <translation>عبارة المرور</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
        <source>Confirm passphrase</source>
        <translation>أكّد عبارة المرور</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="151"/>
        <source>Please enter the same passphrase in both boxes.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FillGlobalStorageJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="167"/>
        <source>Set partition information</source>
        <translation>اضبط معلومات القسم</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="191"/>
        <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
        <translation>ثبّت %1 على قسم نظام %2 &lt;strong&gt;جديد&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="195"/>
        <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>اضطب قسم %2 &lt;strong&gt;جديد&lt;/strong&gt; بنقطة الضّمّ &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="203"/>
        <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>ثبّت %2 على قسم النّظام %3 ‏&lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="208"/>
        <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>اضبط القسم %3 &lt;strong&gt;%1&lt;/strong&gt; بنقطة الضّمّ &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="220"/>
        <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>ثبّت محمّل الإقلاع على &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="230"/>
        <source>Setting up mount points.</source>
        <translation>يضبط نقاط الضّمّ.</translation>
    </message>
</context>
<context>
    <name>FinishedPage</name>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.ui" line="77"/>
        <source>&amp;Restart now</source>
        <translation>أ&amp;عد التّشغيل الآن</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="52"/>
        <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
        <translation>&lt;h1&gt;انتهينا.&lt;/h1&gt;&lt;br/&gt;لقد ثُبّت %1 على حاسوبك.&lt;br/&gt;يمكنك إعادة التّشغيل وفتح النّظام الجديد، أو متابعة استخدام بيئة %2 الحيّة.</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedPage.cpp" line="110"/>
        <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FinishedViewStep</name>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="59"/>
        <source>Finish</source>
        <translation>أنهِ</translation>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="124"/>
        <source>Installation Complete</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/finished/FinishedViewStep.cpp" line="125"/>
        <source>The installation of %1 is complete.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>FormatPartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="49"/>
        <source>Format partition %1 (file system: %2, size: %3 MB) on %4.</source>
        <translation>هيّء القسم %1 (نظام الملفّات: %2، الحجم: %3 م.بايت) على %4.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="60"/>
        <source>Format &lt;strong&gt;%3MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation>هيّء قسم &lt;strong&gt;%3م.بايت&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; بنظام الملفّات &lt;strong&gt;%2&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="71"/>
        <source>Formatting partition %1 with file system %2.</source>
        <translation>يهيّء القسم %1 بنظام الملفّات %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="83"/>
        <source>The installer failed to format partition %1 on disk &apos;%2&apos;.</source>
        <translation>فشل المثبّت في تهيئة القسم %1 على القرص &apos;%2&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="91"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>تعذّر فتح الجهاز &apos;%2&apos;:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="100"/>
        <source>Could not open partition table.</source>
        <translation>تعذّر فتح جدول التّقسيم.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="124"/>
        <source>The installer failed to create file system on partition %1.</source>
        <translation>فشل المثبّت في إنشاء نظام ملفّات في القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="133"/>
        <source>The installer failed to update partition table on disk &apos;%1&apos;.</source>
        <translation>فشل المثبّت في تحديث جدول التّقسيم على القرص &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalPage</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="69"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="84"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="96"/>
        <source>Konsole not installed</source>
        <translation>كونسول غير مثبّت</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="70"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="85"/>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="97"/>
        <source>Please install the kde konsole and try again!</source>
        <translation>فضلًا ثبّت كونسول كدي وجرّب مجدّدًا!</translation>
    </message>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
        <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
        <translation>ينفّذ السّكربت: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
</context>
<context>
    <name>InteractiveTerminalViewStep</name>
    <message>
        <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="45"/>
        <source>Script</source>
        <translation>سكربت</translation>
    </message>
</context>
<context>
    <name>KeyboardPage</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="220"/>
        <source>Set keyboard model to %1.&lt;br/&gt;</source>
        <translation>اضبط طراز لوحة المفتاتيح ليكون %1.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="222"/>
        <source>Set keyboard layout to %1/%2.</source>
        <translation>اضبط تخطيط لوحة المفاتيح إلى %1/%2.</translation>
    </message>
</context>
<context>
    <name>KeyboardViewStep</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="50"/>
        <source>Keyboard</source>
        <translation>لوحة المفاتيح</translation>
    </message>
</context>
<context>
    <name>LCLocaleDialog</name>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="34"/>
        <source>System locale setting</source>
        <translation>إعداد محليّة النّظام</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="41"/>
        <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>إعداد محليّة النّظام يؤثّر على لغة بعض عناصر واجهة مستخدم سطر الأوامر وأطقم محارفها.&lt;br/&gt;الإعداد الحاليّ هو &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="66"/>
        <source>&amp;Cancel</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="67"/>
        <source>&amp;OK</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LicensePage</name>
    <message>
        <location filename="../src/modules/license/LicensePage.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="88"/>
        <source>I accept the terms and conditions above.</source>
        <translation>أقبل الشّروط والأحكام أعلاه.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="115"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure will install proprietary software that is subject to licensing terms.</source>
        <translation>&lt;h1&gt;اتّفاقيّة التّرخيص&lt;/h1&gt;عمليّة الإعداد هذه ستثبّت برمجيّات مملوكة تخضع لشروط ترخيص.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="118"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, the setup procedure cannot continue.</source>
        <translation>فضلًا راجع اتّفاقيّات رخص المستخدم النّهائيّ (EULA) أعلاه.&lt;br/&gt;إن لم تقبل الشّروط، فلن تتابع عمليّة الإعداد.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="124"/>
        <source>&lt;h1&gt;License Agreement&lt;/h1&gt;This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
        <translation>&lt;h1&gt;اتّفاقيّة التّرخيص&lt;/h1&gt;يمكن لعمليّة الإعداد تثبيت برمجيّات مملوكة تخضع لشروط ترخيص وذلك لتوفير مزايا إضافيّة وتحسين تجربة المستخدم.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="129"/>
        <source>Please review the End User License Agreements (EULAs) above.&lt;br/&gt;If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
        <translation>فضلًا راجع اتّفاقيّات رخص المستخدم النّهائيّ (EULA) أعلاه.&lt;br/&gt;إن لم تقبل الشّروط، فلن تُثبّت البرمجيّات المملوكة وستُستخدم تلك مفتوحة المصدر بدلها.</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
        <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
        <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
        <translation>&lt;strong&gt;مشغّل %1&lt;/strong&gt;&lt;br/&gt;من%2</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="166"/>
        <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
        <translation>&lt;strong&gt;مشغّل %1 للرّسوميّات&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;من %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="172"/>
        <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;ملحقة %1 للمتصّفح&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;من %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="178"/>
        <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;مرماز %1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;من %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="184"/>
        <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;حزمة %1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;من %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="190"/>
        <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;by %2&lt;/font&gt;</source>
        <translation>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color=&quot;Grey&quot;&gt;من %2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/license/LicensePage.cpp" line="202"/>
        <source>&lt;a href=&quot;%1&quot;&gt;view license agreement&lt;/a&gt;</source>
        <translation>&lt;a href=&quot;%1&quot;&gt;اعرض اتّفاقيّة التّرخيص&lt;/a&gt;</translation>
    </message>
</context>
<context>
    <name>LicenseViewStep</name>
    <message>
        <location filename="../src/modules/license/LicenseViewStep.cpp" line="51"/>
        <source>License</source>
        <translation>الرّخصة</translation>
    </message>
</context>
<context>
    <name>LocalePage</name>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="387"/>
        <source>The system language will be set to %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="389"/>
        <source>The numbers and dates locale will be set to %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="215"/>
        <source>Region:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="216"/>
        <source>Zone:</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="220"/>
        <location filename="../src/modules/locale/LocalePage.cpp" line="221"/>
        <source>&amp;Change...</source>
        <translation>&amp;غيّر...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="398"/>
        <source>Set timezone to %1/%2.&lt;br/&gt;</source>
        <translation>اضبط المنطقة الزّمنيّة إلى %1/%2.&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocalePage.cpp" line="480"/>
        <source>%1 (%2)</source>
        <extracomment>Language (Country)</extracomment>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>LocaleViewStep</name>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="52"/>
        <source>Loading location data...</source>
        <translation>يحمّل بيانات المواقع...</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/LocaleViewStep.cpp" line="169"/>
        <source>Location</source>
        <translation>الموقع</translation>
    </message>
</context>
<context>
    <name>MoveFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="66"/>
        <source>Move file system of partition %1.</source>
        <translation>انقل نظام ملفّات القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="80"/>
        <source>Could not open file system on partition %1 for moving.</source>
        <translation>تعذّر فتح نظام الملفّات على القسم %1 للنّقل.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="86"/>
        <source>Could not create target for moving file system on partition %1.</source>
        <translation>تعذّر إنشاء هدف لنقل نظام الملفّات على القسم %1 إليه.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="95"/>
        <source>Moving of partition %1 failed, changes have been rolled back.</source>
        <translation>فشل نقل القسم %1، استُعيدت التّغييرات.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="101"/>
        <source>Moving of partition %1 failed. Roll back of the changes have failed.</source>
        <translation>فشل نقل القسم %1. فشلت استعادة التّغييرات.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="113"/>
        <source>Updating boot sector after the moving of partition %1 failed.</source>
        <translation>فشل تحديث قطاع الإقلاع بعد نقل القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="127"/>
        <source>The logical sector sizes in the source and target for copying are not the same. This is currently unsupported.</source>
        <translation>أحجام القطاعات المنطقيّة في المصدر والهدف ليسا متطابقين. هذا ليس مدعومًا حاليًّا.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="201"/>
        <source>Source and target for copying do not overlap: Rollback is not required.</source>
        <translation>لا يتداخل مصدر النّسخ وهدفه. الاستعادة غير ضروريّة.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="225"/>
        <location filename="../src/modules/partition/jobs/MoveFileSystemJob.cpp" line="233"/>
        <source>Could not open device %1 to rollback copying.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>NetInstallPage</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="79"/>
        <source>Name</source>
        <translation>الاسم</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="80"/>
        <source>Description</source>
        <translation>الوصف</translation>
    </message>
    <message>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="97"/>
        <location filename="../src/modules/netinstall/NetInstallPage.cpp" line="104"/>
        <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>NetInstallViewStep</name>
    <message>
        <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
        <source>Package selection</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>Page_Keyboard</name>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
        <source>Keyboard Model:</source>
        <translation>طراز لوحة المفاتيح:</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
        <source>Type here to test your keyboard</source>
        <translation>اكتب هنا لتجرّب لوحة المفاتيح</translation>
    </message>
</context>
<context>
    <name>Page_UserSetup</name>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
        <source>What is your name?</source>
        <translation>ما اسمك؟</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="117"/>
        <source>What name do you want to use to log in?</source>
        <translation>ما الاسم الذي تريده لتلج به؟</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="306"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="437"/>
        <location filename="../src/modules/users/page_usersetup.ui" line="582"/>
        <source>font-weight: normal</source>
        <translation>font-weight: normal</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="200"/>
        <source>&lt;small&gt;If more than one person will use this computer, you can set up multiple accounts after installation.&lt;/small&gt;</source>
        <translation>&lt;small&gt;إن كان عدد مستخدمي هذا الحاسوب أكثر من واحد، يمكنك إعداد عدّة حسابات بعد التّبثيت.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="335"/>
        <source>Choose a password to keep your account safe.</source>
        <translation>اختر كلمة مرور لإبقاء حسابك آمنًا.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="440"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
        <translation>&lt;small&gt;أدخل ذات كلمة المرور مرّتين، للتأكّد من عدم وجود أخطاء طباعيّة. تتكوّن كلمة المرور الجيّدة من خليط أحرف وأرقام وعلامات ترقيم، وطول لا يقلّ عن 8 محارف. كذلك يحبّذ تغييرها دوريًّا لزيادة الأمان.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="226"/>
        <source>What is the name of this computer?</source>
        <translation>ما اسم هذا الحاسوب؟</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="309"/>
        <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
        <translation>&lt;small&gt;سيُستخدم الاسم لإظهار الحاسوب للآخرين عبر الشّبكة.&lt;/small&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="450"/>
        <source>Log in automatically without asking for the password.</source>
        <translation>لِج آليًّا بدون طلب كلمة مرور.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="457"/>
        <source>Use the same password for the administrator account.</source>
        <translation>استخدم نفس كلمة المرور لحساب المدير.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="480"/>
        <source>Choose a password for the administrator account.</source>
        <translation>اختر كلمة مرور لحساب المدير.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/page_usersetup.ui" line="585"/>
        <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
        <translation>&lt;small&gt;أدخل ذات كلمة المرور مرّتين، للتّأكد من عدم وجود أخطاء طباعيّة.&lt;/small&gt;</translation>
    </message>
</context>
<context>
    <name>PartitionLabelsView</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="193"/>
        <source>Root</source>
        <translation>الجذر</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="196"/>
        <source>Home</source>
        <translation>المنزل</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="198"/>
        <source>Boot</source>
        <translation>الإقلاع</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="201"/>
        <source>EFI system</source>
        <translation>نظام EFI</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
        <source>Swap</source>
        <translation>التّبديل</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
        <source>New partition for %1</source>
        <translation>قسم جديد ل‍ %1</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
        <source>New partition</source>
        <translation>قسم جديد</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="224"/>
        <source>%1  %2</source>
        <translation>%1 %2</translation>
    </message>
</context>
<context>
    <name>PartitionModel</name>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="137"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="169"/>
        <source>Free Space</source>
        <translation>المساحة الحرّة</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="141"/>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="173"/>
        <source>New partition</source>
        <translation>قسم جديد</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="257"/>
        <source>Name</source>
        <translation>الاسم</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="259"/>
        <source>File System</source>
        <translation>نظام الملفّات</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="261"/>
        <source>Mount Point</source>
        <translation>نقطة الضّمّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/PartitionModel.cpp" line="263"/>
        <source>Size</source>
        <translation>الحجم</translation>
    </message>
</context>
<context>
    <name>PartitionPage</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
        <source>Storage de&amp;vice:</source>
        <translation>ج&amp;هاز التّخزين:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
        <source>&amp;Revert All Changes</source>
        <translation>ا&amp;عكس كلّ التّغييرات</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
        <source>New Partition &amp;Table</source>
        <translation>&amp;جدول تقسيم جديد</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
        <source>&amp;Create</source>
        <translation>أ&amp;نشئ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
        <source>&amp;Edit</source>
        <translation>ح&amp;رّر</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
        <source>&amp;Delete</source>
        <translation>ا&amp;حذف</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.ui" line="148"/>
        <source>Install boot &amp;loader on:</source>
        <translation>ثبّت م&amp;حمّل الإقلاع على:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="161"/>
        <source>Are you sure you want to create a new partition table on %1?</source>
        <translation>أمتأكّد من إنشاء جدول تقسيم جديد على %1؟</translation>
    </message>
</context>
<context>
    <name>PartitionViewStep</name>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="70"/>
        <source>Gathering system information...</source>
        <translation>جاري جمع معلومات عن النظام...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="121"/>
        <source>Partitions</source>
        <translation>الأقسام</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="158"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
        <translation>ثبّت %1 &lt;strong&gt;جنبًا إلى جنب&lt;/strong&gt; مع نظام تشغيل آخر.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="162"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
        <translation>&lt;strong&gt;امسح&lt;/strong&gt; القرص وثبّت %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="166"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
        <translation>&lt;strong&gt;استبدل&lt;/strong&gt; قسمًا ب‍ %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="171"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
        <translation>تقسيم &lt;strong&gt;يدويّ&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="184"/>
        <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="190"/>
        <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
        <translation>&lt;strong&gt;امسح&lt;/strong&gt; القرص &lt;strong&gt;%2&lt;/strong&gt; (%3) وثبّت %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="196"/>
        <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
        <translation>&lt;strong&gt;استبدل&lt;/strong&gt; قسمًا على القرص &lt;strong&gt;%2&lt;/strong&gt; (%3) ب‍ %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="203"/>
        <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="211"/>
        <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="239"/>
        <source>Current:</source>
        <translation>الحاليّ:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="256"/>
        <source>After:</source>
        <translation>بعد:</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="399"/>
        <source>No EFI system partition configured</source>
        <translation>لم يُضبط أيّ قسم نظام EFI</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="400"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;esp&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="413"/>
        <source>EFI system partition flag not set</source>
        <translation>راية قسم نظام EFI غير مضبوطة</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="414"/>
        <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;esp&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="448"/>
        <source>Boot partition not encrypted</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="449"/>
        <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="82"/>
        <source>Default Keyboard Model</source>
        <translation>نوع لوحة المفاتيح الافتراضي</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="127"/>
        <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="163"/>
        <source>Default</source>
        <translation>الافتراضي</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="210"/>
        <source>unknown</source>
        <translation>مجهول</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="212"/>
        <source>extended</source>
        <translation>ممتدّ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="214"/>
        <source>unformatted</source>
        <translation>غير مهيّأ</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/core/KPMHelpers.cpp" line="216"/>
        <source>swap</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="49"/>
        <source>Unpartitioned space or unknown partition table</source>
        <translation>مساحة غير مقسّمة أو جدول تقسيم مجهول</translation>
    </message>
</context>
<context>
    <name>ReplaceWidget</name>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
        <source>Form</source>
        <translation>نموذج</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="134"/>
        <source>Select where to install %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
        <translation>اختر مكان تثبيت %1.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;تحذير: &lt;/font&gt;سيحذف هذا كلّ الملفّات في القسم المحدّد.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="160"/>
        <source>The selected item does not appear to be a valid partition.</source>
        <translation>لا يبدو العنصر المحدّد قسمًا صالحًا.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="168"/>
        <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
        <translation>لا يمكن تثبيت %1 في مساحة فارغة. فضلًا اختر قسمًا موجودًا.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="178"/>
        <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
        <translation>لا يمكن تثبيت %1 على قسم ممتدّ. فضلًا اختر قسمًا أساسيًّا أو ثانويًّا.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="188"/>
        <source>%1 cannot be installed on this partition.</source>
        <translation>لا يمكن تثبيت %1 على هذا القسم.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="194"/>
        <source>Data partition (%1)</source>
        <translation>قسم البيانات (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="211"/>
        <source>Unknown system partition (%1)</source>
        <translation>قسم نظام مجهول (%1)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
        <source>%1 system partition (%2)</source>
        <translation>قسم نظام %1 ‏(%2)</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="227"/>
        <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
        <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;القسم %1 صغير جدًّا ل‍ %2. فضلًا اختر قسمًا بحجم %3 غ.بايت على الأقلّ.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="250"/>
        <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
        <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;تعذّر إيجاد قسم النّظام EFI في أيّ مكان. فضلًا ارجع واستخدم التّقسيم اليدويّ لإعداد %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="261"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="278"/>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="302"/>
        <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
        <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;سيُثبّت %1 على %2.&lt;br/&gt;&lt;font color=&quot;red&quot;&gt;تحذير: &lt;/font&gt;ستفقد كلّ البيانات على القسم %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="270"/>
        <source>The EFI system partition at %1 will be used for starting %2.</source>
        <translation>سيُستخدم قسم نظام EFI على %1 لبدء %2.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="286"/>
        <source>EFI system partition:</source>
        <translation>قسم نظام EFI:</translation>
    </message>
</context>
<context>
    <name>RequirementsChecker</name>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="67"/>
        <source>Gathering system information...</source>
        <translation>يجمع معلومات النّظام...</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="111"/>
        <source>has at least %1 GB available drive space</source>
        <translation>فيه على الأقل مساحة بحجم %1 غ.بايت حرّة</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="113"/>
        <source>There is not enough drive space. At least %1 GB is required.</source>
        <translation>ليست في القرص مساحة كافية. المطلوب هو %1 غ.بايت على الأقلّ.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="121"/>
        <source>has at least %1 GB working memory</source>
        <translation>فيه ذاكرة شاغرة بحجم %1 غ.بايت على الأقلّ</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="123"/>
        <source>The system does not have enough working memory. At least %1 GB is required.</source>
        <translation>ليس في النّظام ذاكرة شاغرة كافية. المطلوب هو %1 غ.بايت على الأقلّ.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="131"/>
        <source>is plugged in to a power source</source>
        <translation>موصول بمصدر للطّاقة</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="132"/>
        <source>The system is not plugged in to a power source.</source>
        <translation>النّظام ليس متّصلًا بمصدر للطّاقة.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="139"/>
        <source>is connected to the Internet</source>
        <translation>موصول بالإنترنت</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="140"/>
        <source>The system is not connected to the Internet.</source>
        <translation>النّظام ليس موصولًا بالإنترنت</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="148"/>
        <source>The installer is not running with administrator rights.</source>
        <translation>المثبّت لا يعمل بصلاحيّات المدير.</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/checker/RequirementsChecker.cpp" line="156"/>
        <source>The screen is too small to display the installer.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>ResizeFileSystemJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="76"/>
        <source>Resize file system on partition %1.</source>
        <translation>غيّر حجم نظام الملفّات على القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="91"/>
        <source>Parted failed to resize filesystem.</source>
        <translation>فشل Parted في تغيير حجم نظام الملفّات.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="101"/>
        <source>Failed to resize filesystem.</source>
        <translation>فشل تغيير حجم نظام الملفّات.</translation>
    </message>
</context>
<context>
    <name>ResizePartitionJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="187"/>
        <source>Resize partition %1.</source>
        <translation>غيّر حجم القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="194"/>
        <source>Resize &lt;strong&gt;%2MB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MB&lt;/strong&gt;.</source>
        <translation>غيّر حجم قسم &lt;strong&gt;%2م.بايت&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; إلى &lt;strong&gt;%3م.بايت&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="205"/>
        <source>Resizing %2MB partition %1 to %3MB.</source>
        <translation>يغيّر حجم قسم %2م.بايت %1 إلى %3م.بايت.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="232"/>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="298"/>
        <source>The installer failed to resize partition %1 on disk &apos;%2&apos;.</source>
        <translation>فشل المثبّت في تغيير حجم القسم %1 على القرص &apos;%2&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="237"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>تعذّر فتح الجهاز &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>ScanningDialog</name>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
        <source>Scanning storage devices...</source>
        <translation>يفحص أجهزة التّخزين...</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
        <source>Partitioning</source>
        <translation>يقسّم</translation>
    </message>
</context>
<context>
    <name>SetHostNameJob</name>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="37"/>
        <source>Set hostname %1</source>
        <translation>اضبط اسم المضيف %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="44"/>
        <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>اضبط اسم المضيف &lt;strong&gt;%1&lt;/strong&gt; .</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="51"/>
        <source>Setting hostname %1.</source>
        <translation>يضبط اسم المضيف 1%.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="61"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="68"/>
        <source>Internal Error</source>
        <translation>خطأ داخلي</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="75"/>
        <location filename="../src/modules/users/SetHostNameJob.cpp" line="86"/>
        <source>Cannot write hostname to target system</source>
        <translation>تعذّرت كتابة اسم المضيف إلى النّظام الهدف</translation>
    </message>
</context>
<context>
    <name>SetKeyboardLayoutJob</name>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
        <source>Set keyboard model to %1, layout to %2-%3</source>
        <translation>اضبك طراز لوحة المفتايح إلى %1، والتّخطيط إلى %2-%3</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="320"/>
        <source>Failed to write keyboard configuration for the virtual console.</source>
        <translation>فشلت كتابة ضبط لوحة المفاتيح للطرفيّة الوهميّة.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="321"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="325"/>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="331"/>
        <source>Failed to write to %1</source>
        <translation>فشلت الكتابة إلى %1</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="324"/>
        <source>Failed to write keyboard configuration for X11.</source>
        <translation>فشلت كتابة ضبط لوحة المفاتيح ل‍ X11.</translation>
    </message>
    <message>
        <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="330"/>
        <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>SetPartFlagsJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="48"/>
        <source>Set flags on partition %1.</source>
        <translation>اضبط رايات القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="51"/>
        <source>Set flags on %1MB %2 partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="55"/>
        <source>Set flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="66"/>
        <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>يمحي رايات القسم &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="70"/>
        <source>Clear flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
        <source>Clear flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="78"/>
        <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="84"/>
        <source>Flag %1MB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="90"/>
        <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="102"/>
        <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>يمحي رايات القسم &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="106"/>
        <source>Clearing flags on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="110"/>
        <source>Clearing flags on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="114"/>
        <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
        <translation>يضبط رايات &lt;strong&gt;%2&lt;/strong&gt; القسم&lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="120"/>
        <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="126"/>
        <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="140"/>
        <source>The installer failed to set flags on partition %1.</source>
        <translation>فشل المثبّت في ضبط رايات القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="148"/>
        <source>Could not open device &apos;%1&apos;.</source>
        <translation>تعذّر فتح الجهاز &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="157"/>
        <source>Could not open partition table on device &apos;%1&apos;.</source>
        <translation>تعذّر فتح جدول التّقسيم على الجهاز &apos;%1&apos;.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="169"/>
        <source>Could not find partition &apos;%1&apos;.</source>
        <translation>تعذّر إيجاد القسم &apos;%1&apos;.</translation>
    </message>
</context>
<context>
    <name>SetPartGeometryJob</name>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="144"/>
        <source>Update geometry of partition %1.</source>
        <translation>حدّث هندسة القسم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="156"/>
        <source>Failed to change the geometry of the partition.</source>
        <translation>فشل تغيير هندسة القسم.</translation>
    </message>
</context>
<context>
    <name>SetPasswordJob</name>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="48"/>
        <source>Set password for user %1</source>
        <translation>اضبط كلمة مرور للمستخدم %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="55"/>
        <source>Setting password for user %1.</source>
        <translation>يضبط كلمة مرور للمستخدم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="112"/>
        <source>Bad destination system path.</source>
        <translation>مسار النّظام المقصد سيّء.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="113"/>
        <source>rootMountPoint is %1</source>
        <translation>rootMountPoint هو %1</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="123"/>
        <source>Cannot disable root account.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="124"/>
        <source>passwd terminated with error code %1.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="139"/>
        <source>Cannot set password for user %1.</source>
        <translation>تعذّر ضبط كلمة مرور للمستخدم %1.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/SetPasswordJob.cpp" line="141"/>
        <source>usermod terminated with error code %1.</source>
        <translation>أُنهي usermod برمز الخطأ %1.</translation>
    </message>
</context>
<context>
    <name>SetTimezoneJob</name>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
        <source>Set timezone to %1/%2</source>
        <translation>اضبط المنطقة الزّمنيّة إلى %1/%2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
        <source>Cannot access selected timezone path.</source>
        <translation>لا يمكن الدخول إلى مسار المنطقة الزمنية المختارة.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
        <source>Bad path: %1</source>
        <translation>المسار سيّء: %1</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
        <source>Cannot set timezone.</source>
        <translation>لا يمكن تعيين المنطقة الزمنية.</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
        <source>Link creation failed, target: %1; link name: %2</source>
        <translation>فشل إنشاء الوصلة، الهدف: %1، اسم الوصلة: %2</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="96"/>
        <source>Cannot set timezone,</source>
        <translation>تعذّر ضبط المنطقة الزّمنيّة،</translation>
    </message>
    <message>
        <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="97"/>
        <source>Cannot open /etc/timezone for writing</source>
        <translation>تعذّر فتح ‎/etc/timezone للكتابة</translation>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/modules/summary/SummaryPage.cpp" line="49"/>
        <source>This is an overview of what will happen once you start the install procedure.</source>
        <translation>هذه نظرة عامّة عمّا سيحصل ما إن تبدأ عمليّة التّثبيت.</translation>
    </message>
</context>
<context>
    <name>SummaryViewStep</name>
    <message>
        <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
        <source>Summary</source>
        <translation>الخلاصة</translation>
    </message>
</context>
<context>
    <name>UsersPage</name>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="287"/>
        <source>Your username is too long.</source>
        <translation>اسم المستخدم طويل جدًّا.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="293"/>
        <source>Your username contains invalid characters. Only lowercase letters and numbers are allowed.</source>
        <translation>يحوي اسم المستخدم محارف غير صالح. المسموح هو الأحرف الصّغيرة والأرقام فقط.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="331"/>
        <source>Your hostname is too short.</source>
        <translation>اسم المضيف قصير جدًّا.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="337"/>
        <source>Your hostname is too long.</source>
        <translation>اسم المضيف طويل جدًّا.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="343"/>
        <source>Your hostname contains invalid characters. Only letters, numbers and dashes are allowed.</source>
        <translation>يحوي اسم المضيف محارف غير صالحة. المسموح فقط الأحرف والأرقام والشُّرط.</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="371"/>
        <location filename="../src/modules/users/UsersPage.cpp" line="415"/>
        <source>Your passwords do not match!</source>
        <translation>لا يوجد تطابق في كلمات السر!</translation>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="494"/>
        <source>Password is too short</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/users/UsersPage.cpp" line="513"/>
        <source>Password is too long</source>
        <translation type="unfinished"/>
    </message>
</context>
<context>
    <name>UsersViewStep</name>
    <message>
        <location filename="../src/modules/users/UsersViewStep.cpp" line="50"/>
        <source>Users</source>
        <translation>المستخدمين</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
        <source>Form</source>
        <translation>الصيغة</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
        <source>&amp;Language:</source>
        <translation>&amp;اللغة:</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="176"/>
        <source>&amp;Release notes</source>
        <translation>&amp;ملاحظات الإصدار</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
        <source>&amp;Known issues</source>
        <translation>&amp;مشاكل معروفة</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
        <source>&amp;Support</source>
        <translation>&amp;الدعم</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
        <source>&amp;About</source>
        <translation>&amp;حول</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
        <translation>&lt;h1&gt;مرحبًا بك في مثبّت %1.&lt;/h1&gt;</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="60"/>
        <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="73"/>
        <source>About %1 installer</source>
        <translation>حول 1% المثبت</translation>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="75"/>
        <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to: Anke Boersma, Aurélien Gâteau, Kevin Kofler, Lisa Vitolo, Philip Müller, Pier Luigi Fiorini, Rohan Garg and the &lt;a href=&quot;https://www.transifex.com/calamares/calamares/&quot;&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href=&quot;http://calamares.io/&quot;&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href=&quot;http://www.blue-systems.com/&quot;&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
        <translation type="unfinished"/>
    </message>
    <message>
        <location filename="../src/modules/welcome/WelcomePage.cpp" line="201"/>
        <source>%1 support</source>
        <translation>1%  الدعم</translation>
    </message>
</context>
<context>
    <name>WelcomeViewStep</name>
    <message>
        <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="51"/>
        <source>Welcome</source>
        <translation>مرحبا بك</translation>
    </message>
</context>
</TS>
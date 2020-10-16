<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="as" version="2.1">
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="71"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>এইটো চিছটেমৰ &lt;strong&gt;বুট পৰিবেশ&lt;/strong&gt;।&lt;br&gt;&lt;br&gt;পুৰণি x86 চিছটেমবোৰে কেৱল &lt;strong&gt;BIOSক&lt;/strong&gt;সমৰ্থন কৰে।&lt;br&gt;আধুনিক চিছটেমে সাধাৰণতে&lt;strong&gt;EFI&lt;/strong&gt; ব্যৱহাৰ কৰে, কিন্তু সামঞ্জস্যতা মোডত আৰম্ভ হ'লে BIOS দেখাব পাৰে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="81"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>চিছটেমটো &lt;strong&gt;EFI&lt;/strong&gt; বুট পৰিবেশত আৰম্ভ হৈছিল।&lt;br&gt;&lt;br&gt;EFI পৰিবেশৰ পৰা স্টাৰ্তআপ কন্ফিগাৰ কৰিবলৈ ইনস্তলাৰটোৱে &lt;strong&gt;GRUBৰ&lt;/strong&gt; দৰে বুট লোডাৰ বা এখন &lt;strong&gt;EFI চিছ্টেম বিভাজনত&lt;/strong&gt; &lt;strong&gt;systemd-boot&lt;/strong&gt; প্ৰয়োগ কৰিব লাগিব। এইটো প্ৰক্ৰিযা স্বত: স্ফুৰ্ত ভাবে হ'ব যদিহে আপুনি নিজে মেনুৱেল বিভজন চয়ন নকৰে, য'ত আপুনি নিজে এখন EFI বিভাজন বনাব লাগিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="93"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>চিছটেমটো &lt;strong&gt;BIOS&lt;/strong&gt; বুট পৰিবেশত আৰম্ভ হৈছিল।&lt;br&gt;&lt;br&gt;BIOS পৰিবেশ এটাৰ পৰা স্টাৰ্তআপ কন্ফিগাৰ কৰিবলৈ ইনস্তলাৰটোৱে &lt;strong&gt;GRUBৰ&lt;/strong&gt; দৰে বুট লোডাৰ ইনস্তল​ কৰিব লাগিব বিভাজনৰ আৰম্ভনিতে বা বিভাজন তালিকাৰ আৰম্ভনিৰ কাষৰ &lt;strong&gt;প্ৰধান বুত্ নথিত&lt;/strong&gt; (অগ্ৰাধিকাৰ ভিত্তিত)। এইটো প্ৰক্ৰিযা স্বত: স্ফুৰ্ত ভাবে হ'ব যদিহে আপুনি নিজে মেনুৱেল বিভজন চয়ন নকৰে, য'ত আপুনি নিজে বুত্ লোডাৰ চেত্ আপ কৰিব লাগিব।</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="68"/>
      <source>Master Boot Record of %1</source>
      <translation>%1ৰ প্ৰধান বুত্ নথি</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="102"/>
      <source>Boot Partition</source>
      <translation>বুত্ বিভাজন</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="109"/>
      <source>System Partition</source>
      <translation>চিছ্তেম বিভাজন</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="139"/>
      <source>Do not install a boot loader</source>
      <translation>বুত্ লোডাৰ ইনস্তল কৰিব নালাগে</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="157"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::BlankViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/BlankViewStep.cpp" line="70"/>
      <source>Blank Page</source>
      <translation>খালি পৃষ্ঠা</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="24"/>
      <source>GlobalStorage</source>
      <translation>গোলকীয় স্টোৰেজ</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="34"/>
      <source>JobQueue</source>
      <translation>কার্য্য লানি</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="44"/>
      <source>Modules</source>
      <translation>মডিউলবোৰ</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="57"/>
      <source>Type:</source>
      <translation>প্ৰকাৰ:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="64"/>
      <location filename="../src/calamares/DebugWindow.ui" line="78"/>
      <source>none</source>
      <translation>একো নাই</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="71"/>
      <source>Interface:</source>
      <translation>ইন্টাৰফেচ:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="93"/>
      <source>Tools</source>
      <translation>সঁজুলি</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="106"/>
      <source>Reload Stylesheet</source>
      <translation>স্টাইলছীট পুনৰ লোড্ কৰক</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="113"/>
      <source>Widget Tree</source>
      <translation>ৱিজেত্ ত্ৰি</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="231"/>
      <source>Debug information</source>
      <translation>ডিবাগ তথ্য</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="92"/>
      <source>Set up</source>
      <translation>চেত্ আপ</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="92"/>
      <source>Install</source>
      <translation>ইনস্তল</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="39"/>
      <source>Job failed (%1)</source>
      <translation>কার্য্য বিফল হল (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="40"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>প্ৰগ্ৰেম কৰা কাৰ্য্যৰ বিফলতা স্পষ্টভাবে অনুৰোধ কৰা হৈছিল।</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="114"/>
      <source>Done</source>
      <translation>হৈ গ'ল</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="27"/>
      <source>Example job (%1)</source>
      <translation>উদাহৰণ কার্য্য (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source>Run command '%1' in target system.</source>
      <translation>গন্তব্য চিছটেমত '%1' কমাণ্ড চলাওক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="52"/>
      <source> Run command '%1'.</source>
      <translation>'%1' কমাণ্ড চলাওক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="59"/>
      <source>Running command %1 %2</source>
      <translation> %1%2 কমাণ্ড চলি আছে</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="210"/>
      <source>Running %1 operation.</source>
      <translation>%1 কাৰ্য চলি আছে।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="239"/>
      <source>Bad working directory path</source>
      <translation>বেয়া কৰ্মৰত ডাইৰেক্টৰী পথ</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="240"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>%2 পাইথন কাৰ্য্যৰ %1 কৰ্মৰত ডাইৰেক্টৰী পঢ়িব নোৱাৰি।​</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="246"/>
      <source>Bad main script file</source>
      <translation>বেয়া মুখ্য লিপি ফাইল</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="247"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>%2 পাইথন কাৰ্য্যৰ %1 মূখ্য লিপি ফাইল পঢ়িব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="315"/>
      <source>Boost.Python error in job "%1".</source>
      <translation>"%1"  কাৰ্য্যত Boost.Python ত্ৰুটি।</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="76"/>
      <source>Loading ...</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="97"/>
      <source>QML Step &lt;i&gt;%1&lt;/i&gt;.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="261"/>
      <source>Loading failed.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="164"/>
      <source>Waiting for %n module(s).</source>
      <translation>
        <numerusform>Waiting for %n module(s).</numerusform>
        <numerusform>%n মডিউল(বোৰ)ৰ বাবে অপেক্ষাৰত।</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="165"/>
      <source>(%n second(s))</source>
      <translation>
        <numerusform>(%n second(s))</numerusform>
        <numerusform>(%n ছেকেণ্ড)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="170"/>
      <source>System-requirements checking is complete.</source>
      <translation>চিছ্তেমৰ বাবে প্রয়োজনীয় পৰীক্ষণ সম্পূর্ণ হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Setup Failed</source>
      <translation>চেত্ আপ বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="153"/>
      <source>Installation Failed</source>
      <translation>ইনস্তলেচন বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="154"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>আপুনি ৱেবত ইণ্স্টল ল'গ পেস্ট কৰিব বিচাৰে নেকি?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="167"/>
      <source>Error</source>
      <translation>ত্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="174"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="518"/>
      <source>&amp;Yes</source>
      <translation>হয় (&amp;Y)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="175"/>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>&amp;No</source>
      <translation>নহয় (&amp;N)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="181"/>
      <source>&amp;Close</source>
      <translation>বন্ধ (&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>Install Log Paste URL</source>
      <translation>ইনস্তল​ ল'গ পেস্ট URL</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="195"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>আপলোড বিফল হৈছিল। কোনো ৱেব-পেস্ট কৰা হোৱা নাছিল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="211"/>
      <source>Calamares Initialization Failed</source>
      <translation>কেলামাৰেচৰ আৰম্ভণি বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="212"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <translation>%1 ইনস্তল কৰিব পৰা নগ'ল। কেলামাৰেচে সকলোবোৰ সংৰূপ দিয়া মডিউল লোড্ কৰাত সফল নহ'ল। এইটো এটা আপোনাৰ ডিষ্ট্ৰিবিউচনে কি ধৰণে কেলামাৰেচ ব্যৱহাৰ কৰিছে, সেই সম্বন্ধীয় সমস্যা।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="218"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <translation>&lt;br/&gt;নিম্নোক্ত মডিউলবোৰ লোড্ কৰিৱ পৰা নগ'ল:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="328"/>
      <source>Continue with setup?</source>
      <translation>চেত্ আপ অব্যাহত ৰাখিব?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="328"/>
      <source>Continue with installation?</source>
      <translation>ইন্স্তলেচন অব্যাহত ৰাখিব?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="330"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 চেত্ আপ প্ৰগ্ৰেমটোৱে %2 চেত্ আপ কৰিবলৈ আপোনাৰ ডিস্কত সালসলনি কৰিব।&lt;br/&gt;&lt;strong&gt;আপুনি এইবোৰ পিছত পূৰ্বলৈ সলনি কৰিব নোৱাৰিব।&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="333"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <translation>%1 ইনস্তলাৰটোৱে %2 ইনস্তল কৰিবলৈ আপোনাৰ ডিস্কত সালসলনি কৰিব।&lt;br/&gt;&lt;strong&gt;আপুনি এইবোৰ পিছত পূৰ্বলৈ সলনি কৰিব নোৱাৰিব।&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="336"/>
      <source>&amp;Set up now</source>
      <translation>এতিয়া চেত্ আপ কৰক (&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="336"/>
      <source>&amp;Install now</source>
      <translation>এতিয়া ইনস্তল কৰক (&amp;I)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="343"/>
      <source>Go &amp;back</source>
      <translation>উভতি যাওক (&amp;b)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Set up</source>
      <translation>চেত্ আপ কৰক (&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="392"/>
      <source>&amp;Install</source>
      <translation>ইনস্তল (&amp;I)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="394"/>
      <source>Setup is complete. Close the setup program.</source>
      <translation>চেত্ আপ সম্পূৰ্ণ হ'ল। প্ৰোগ্ৰেম বন্ধ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="395"/>
      <source>The installation is complete. Close the installer.</source>
      <translation>ইনস্তলেচন সম্পূৰ্ণ হ'ল। ইন্স্তলাৰ বন্ধ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="397"/>
      <source>Cancel setup without changing the system.</source>
      <translation>চিছ্তেম সলনি নকৰাকৈ চেত্ আপ বাতিল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>Cancel installation without changing the system.</source>
      <translation>চিছ্তেম সলনি নকৰাকৈ ইনস্তলেচন বাতিল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="408"/>
      <source>&amp;Next</source>
      <translation>পৰবর্তী (&amp;N)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="413"/>
      <source>&amp;Back</source>
      <translation>পাছলৈ (&amp;B)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Done</source>
      <translation>হৈ গ'ল (&amp;D)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="438"/>
      <source>&amp;Cancel</source>
      <translation>বাতিল কৰক (&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel setup?</source>
      <translation>চেত্ আপ বাতিল কৰিব?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="511"/>
      <source>Cancel installation?</source>
      <translation>ইনস্তলেছন বাতিল কৰিব?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="512"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>সচাকৈয়ে চলিত চেত্ আপ প্ৰক্ৰিয়া বাতিল কৰিব বিচাৰে নেকি?
চেত্ আপ প্ৰোগ্ৰেম বন্ধ হ'ব আৰু গোটেই সলনিবোৰ নোহোৱা হৈ যাব।</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="514"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>সচাকৈয়ে চলিত ইনস্তল প্ৰক্ৰিয়া বাতিল কৰিব বিচাৰে নেকি?
ইনস্তলাৰ বন্ধ হ'ব আৰু গোটেই সলনিবোৰ নোহোৱা হৈ যাব।</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="297"/>
      <source>Unknown exception type</source>
      <translation>অপৰিচিত প্ৰকাৰৰ ব্যতিক্রম</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="315"/>
      <source>unparseable Python error</source>
      <translation>অপ্ৰাপ্য পাইথন ত্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="359"/>
      <source>unparseable Python traceback</source>
      <translation>অপ্ৰাপ্য পাইথন ত্ৰেচবেক</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="366"/>
      <source>Unfetchable Python error.</source>
      <translation>ঢুকি নোপোৱা পাইথন ক্ৰুটি।</translation>
    </message>
  </context>
  <context>
    <name>CalamaresUtils</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="34"/>
      <source>Install log posted to:
%1</source>
      <translation>ইনস্তল​​ ল'গ পোস্ট কৰা হৈছে:
%1</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="106"/>
      <source>Show debug information</source>
      <translation>দিবাগ তথ্য দেখাওক</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="172"/>
      <source>&amp;Back</source>
      <translation>পাছলৈ (&amp;B)</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="184"/>
      <source>&amp;Next</source>
      <translation>পৰবর্তী (&amp;N)</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="197"/>
      <source>&amp;Cancel</source>
      <translation>বাতিল কৰক (&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="281"/>
      <source>%1 Setup Program</source>
      <translation>%1 চেত্ আপ প্ৰোগ্ৰেম</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="282"/>
      <source>%1 Installer</source>
      <translation>%1 ইনস্তলাৰ</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="46"/>
      <source>Gathering system information...</source>
      <translation>চিছ্তেম তথ্য সংগ্ৰহ কৰা হৈ আছে...</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="156"/>
      <source>Select storage de&amp;vice:</source>
      <translation>স্তোৰেজ ডিভাইচ চয়ণ কৰক (&amp;v):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="157"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="957"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1002"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1088"/>
      <source>Current:</source>
      <translation>বর্তমান:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="158"/>
      <source>After:</source>
      <translation>পিছত:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="334"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself. Having a GPT partition table and &lt;strong&gt;fat32 512Mb /boot partition is a must for UEFI installs&lt;/strong&gt;, either use an existing without formatting or create one.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="833"/>
      <source>Reuse %1 as home partition for %2.</source>
      <translation>%1ক %2ৰ গৃহ বিভাজন হিচাপে পুনৰ ব্যৱহাৰ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="958"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;আয়তন সলনি কৰিবলৈ বিভাজন বাচনি কৰক, তাৰ পিছত তলৰ "বাৰ্" ডালৰ সহায়ত আয়তন চেত্ কৰক&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="973"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <translation>%1 বিভজনক সৰু কৰি %2MiB কৰা হ'ব আৰু %4ৰ বাবে %3MiBৰ নতুন বিভজন বনোৱা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1030"/>
      <source>Boot loader location:</source>
      <translation>বুত্ লোডাৰৰ অৱস্থান:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1079"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;ইনস্তল​ কৰিবলৈ এখন বিভাজন চয়ন কৰক&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1135"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>এই চিছটেমত এখনো EFI চিছটেম বিভাজন কতো পোৱা নগ'ল। অনুগ্ৰহ কৰি উভতি যাওক আৰু মেনুৱেল বিভাজন প্ৰক্ৰিয়া দ্বাৰা %1 চেত্ আপ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1144"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>%1ত থকা EFI চিছটেম বিভাজনটো %2ক আৰম্ভ কৰাৰ বাবে ব্যৱহাৰ কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1152"/>
      <source>EFI system partition:</source>
      <translation>EFI চিছটেম বিভাজন:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1270"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>এইটো ষ্টোৰেজ ডিভাইচত কোনো অপাৰেটিং চিছটেম নাই যেন লাগে। আপুনি কি কৰিব বিচাৰে?&lt;br/&gt;আপুনি ষ্টোৰেজ ডিভাইচটোত কিবা সলনি কৰাৰ আগতে পুনৰীক্ষণ আৰু চয়ন নিশ্চিত কৰিব পাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1275"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1313"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1336"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1362"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;ডিস্কত থকা গোটেই ডাটা আতৰাওক।&lt;/strong&gt;&lt;br/&gt; ইয়াৰ দ্ৱাৰা ষ্টোৰেজ ডিভাইছত বৰ্তমান থকা সকলো ডাটা &lt;font color="red"&gt;বিলোপ&lt;/font&gt; কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1279"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1309"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1332"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1358"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;সমান্তৰালভাৱে ইনস্তল কৰক&lt;/strong&gt;&lt;br/&gt; ইনস্তলাৰটোৱে %1ক ইনস্তল​ কৰাৰ বাবে এখন বিভাজন সৰু কৰি দিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1283"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1318"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1340"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1366"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;বিভাজন সলনি কৰক&lt;/strong&gt; &lt;br/&gt;এখন বিভাজনক % ৰ্ সৈতে সলনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1303"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>এইটো ষ্টোৰেজ ডিভাইচত %1 আছে। &lt;br/&gt; আপুনি কি কৰিব বিচাৰে? ষ্টোৰেজ ডিভাইচটোত যিকোনো সলনি কৰাৰ আগত আপুনি পুনৰীক্ষণ আৰু সলনি কৰিব পাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1327"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>এইটো ষ্টোৰেজ ডিভাইচত ইতিমধ্যে এটা অপাৰেটিং চিছটেম আছে। আপুনি কি কৰিব বিচাৰে? &lt;br/&gt;ষ্টোৰেজ ডিভাইচটোত যিকোনো সলনি কৰাৰ আগত আপুনি পুনৰীক্ষণ আৰু সলনি কৰিব পাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1353"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>এইটো ষ্টোৰেজ ডিভাইচত একাধিক এটা অপাৰেটিং চিছটেম আছে। আপুনি কি কৰিব বিচাৰে? 1ষ্টোৰেজ ডিভাইচটোত যিকোনো সলনি কৰাৰ আগত আপুনি পুনৰীক্ষণ আৰু সলনি কৰিব পাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1507"/>
      <source>No Swap</source>
      <translation>কোনো স্ৱেপ নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1512"/>
      <source>Reuse Swap</source>
      <translation>স্ৱেপ পুনৰ ব্যৱহাৰ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1515"/>
      <source>Swap (no Hibernate)</source>
      <translation>স্ৱেপ (হাইবাৰনেট নোহোৱাকৈ)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1518"/>
      <source>Swap (with Hibernate)</source>
      <translation>স্ৱোআপ (হাইবাৰনেটৰ সৈতে)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1521"/>
      <source>Swap to file</source>
      <translation>ফাইললৈ স্ৱোআপ কৰক।</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="50"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <translation>%1ত বিভাজন কৰ্য্যৰ বাবে মাউণ্ট্ আতৰাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="57"/>
      <source>Clearing mounts for partitioning operations on %1.</source>
      <translation>%1ত বিভাজন কৰ্য্যৰ বাবে মাউণ্ট্ আতৰ কৰি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="232"/>
      <source>Cleared all mounts for %1</source>
      <translation>%1ৰ গোটেই মাউন্ত আতৰোৱা হ'ল</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="42"/>
      <source>Clear all temporary mounts.</source>
      <translation>গোটেই অস্থায়ী মাউন্ত আঁতৰাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="49"/>
      <source>Clearing all temporary mounts.</source>
      <translation>গোটেই অস্থায়ী মাউন্ত আঁতৰোৱা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="61"/>
      <source>Cannot get list of temporary mounts.</source>
      <translation>অস্থায়ী মাউন্তৰ সূচী পোৱা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="102"/>
      <source>Cleared all temporary mounts.</source>
      <translation>গোটেই অস্থায়ী মাউন্ত আঁতৰোৱা হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="150"/>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="163"/>
      <source>Could not run command.</source>
      <translation>কমাণ্ড চলাব পৰা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="151"/>
      <source>The command runs in the host environment and needs to know the root path, but no rootMountPoint is defined.</source>
      <translation>কমাণ্ডটো হ'স্ট পৰিৱেশত চলে আৰু তাৰ বাবে ৰুট পথ জানাটো আৱশ্যক, কিন্তু rootMountPointৰ বিষয়ে একো উল্লেখ নাই।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>The command needs to know the user's name, but no username is defined.</source>
      <translation>কমাণ্ডটোৱে ব্যৱহাৰকাৰীৰ নাম জনাটো আৱশ্যক, কিন্তু কোনো ব্যৱহাৰকাৰীৰ নাম উল্লেখ নাই।</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="348"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>কিবোৰ্ডৰ মডেল %1ত চেট্ কৰক।&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="355"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>কিবোৰ্ডৰ লেআউট %1/%2 চেট্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="279"/>
      <source>The system language will be set to %1.</source>
      <translation>চিছটেমৰ ভাষা %1লৈ সলনি কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="280"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>সংখ্যা আৰু তাৰিখ স্থানীয় %1লৈ সলনি কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="313"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>সময় জ'ন  %1/%2লৈ সলনি কৰা হ'ল।&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="47"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>নেটৱৰ্ক ইনস্তলেচন। (নিস্ক্ৰিয়: ভুল কনফিগাৰেচন)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="49"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>নেটৱৰ্ক্ ইনস্তলেচন। (নিস্ক্ৰিয়: অকার্যকৰ গোটৰ তথ্য পোৱা গ'ল)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="51"/>
      <source>Network Installation. (Disabled: internal error)</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>নেটৱৰ্ক্ ইনস্তলেচন। (নিস্ক্ৰিয়: পেকেজ সুচী বিচাৰি পোৱা নগ'ল, আপোনাৰ নেটৱৰ্ক্ সংযোগ পৰীক্ষা কৰক)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="54"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>%1 চেত্ আপৰ বাবে নিম্নতম আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;স্থাপন প্ৰক্ৰিয়া অবিৰত ৰাখিব নোৱাৰিব। &lt;a href="#details"&gt;বিৱৰণ...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="58"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>%1 ইনস্তলচেন​ৰ বাবে নিম্নতম আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;ইনস্তলচেন​ প্ৰক্ৰিয়া অবিৰত ৰাখিব নোৱাৰিব। &lt;a href="#details"&gt;বিৱৰণ...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="65"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>%1 চেত্ আপৰ বাবে পৰামৰ্শ দিয়া আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;স্থাপন প্ৰক্ৰিয়া অবিৰত ৰাখিব পাৰিব, কিন্তু কিছুমান সুবিধা নিষ্ক্রিয় হৈ থাকিব। </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="69"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>%1 ইনস্তলচেন​ৰ বাবে পৰামৰ্শ দিয়া আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। ইনস্তলচেন​ অবিৰত ৰাখিব পাৰিব, কিন্তু কিছুমান সুবিধা নিষ্ক্রিয় হৈ থাকিব। </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="79"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>এইটো প্ৰগ্ৰেমে অপোনাক কিছুমান প্ৰশ্ন সুধিব আৰু অপোনাৰ কম্পিউটাৰত %2 স্থাপন কৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="230"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1ৰ কেলামাৰেচ চেত্ আপ প্ৰগ্ৰামলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="231"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt; %1 চেত্ আপলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="236"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1ৰ কেলামাৰেচ ইনস্তলাৰলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="237"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 ইনস্তলাৰলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="128"/>
      <source>Contextual Processes Job</source>
      <translation>প্রাসঙ্গিক প্ৰক্ৰিয়াবোৰৰ কাৰ্য্য</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="14"/>
      <source>Create a Partition</source>
      <translation>এখন বিভাজন বনাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="38"/>
      <source>Si&amp;ze:</source>
      <translation>আয়তন (&amp;z):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="48"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="55"/>
      <source>Partition &amp;Type:</source>
      <translation>বিভাজনৰ প্ৰকাৰ (&amp;T):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="67"/>
      <source>&amp;Primary</source>
      <translation>মুখ্য (&amp;P)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="77"/>
      <source>E&amp;xtended</source>
      <translation>সম্প্ৰসাৰিত (&amp;x)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="119"/>
      <source>Fi&amp;le System:</source>
      <translation>ফাইল চিছ্টেম (&amp;l):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="151"/>
      <source>LVM LV name</source>
      <translation>LVM LV নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="161"/>
      <source>&amp;Mount Point:</source>
      <translation>মাউন্ট পইন্ট (&amp;M):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="188"/>
      <source>Flags:</source>
      <translation>ফ্লেগ সমূহ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="74"/>
      <source>En&amp;crypt</source>
      <translation>এনক্ৰিপ্ত্ (&amp;c)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="159"/>
      <source>Logical</source>
      <translation>যুক্তিসম্মত</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="164"/>
      <source>Primary</source>
      <translation>মূখ্য</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="181"/>
      <source>GPT</source>
      <translation>GPT</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="271"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>এইটো মাওন্ট্ পইন্ট্ ইতিমধ্যে ব্যৱহাৰ হৈ আছে। অনুগ্ৰহ কৰি বেলেগ এটা বাচনি কৰক।</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="47"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1.</source>
      <translation>%1 ফাইল চিছটেমৰ সৈতে %4 (%3) ত %2MiBৰ নতুন বিভাজন বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="58"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;ত নতুন (%3) &lt;strong&gt;%1&lt;/strong&gt; ফাইল চিছটেমৰ &lt;strong&gt;%2MiB&lt;/strong&gt; বিভাজন কৰক। </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="70"/>
      <source>Creating new %1 partition on %2.</source>
      <translation>%2ত নতুন %1 বিভজন বনাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="82"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <translation>'%1' ডিস্কত নতুন বিভাজন বনোৱাত ইনস্তলাৰটো বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="20"/>
      <source>Create Partition Table</source>
      <translation>বিভাজন তালিকা বনাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="39"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>নতুন বিভাজন তালিকা বনালে ডিস্কত জমা থকা গোটেই ডাটা বিলোপ হৈ যাব। </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="65"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>আপুনি কেনেকুৱা ধৰণৰ বিভাজন তালিকা বনাব বিচাৰিছে?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="72"/>
      <source>Master Boot Record (MBR)</source>
      <translation>প্ৰধান বুট্ নথি (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="82"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID বিভাজন তালিকা (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="48"/>
      <source>Create new %1 partition table on %2.</source>
      <translation>%2ত নতুন %1 বিভাজন তালিকা বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="56"/>
      <source>Create new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3)ত নতুন &lt;strong&gt;%1&lt;/strong&gt; বিভাজন তালিকা বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="66"/>
      <source>Creating new %1 partition table on %2.</source>
      <translation>%2ত নতুন %1 বিভাজন তালিকা বনোৱা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="84"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>ইন্স্তলাৰটো %1ত বিভাজন তালিকা বনোৱাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="51"/>
      <source>Create user %1</source>
      <translation>%1 ব্যৱহাৰকৰ্তা বনাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="58"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; ব্যৱহাৰকৰ্তা বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="65"/>
      <source>Creating user %1.</source>
      <translation>%1 ব্যৱহাৰকৰ্তা বনোৱা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="83"/>
      <source>Sudoers dir is not writable.</source>
      <translation>Sudoers ডিৰেক্টৰি লিখনযোগ্য নহয়।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="89"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>লিখাৰ বাবে sudoers ফাইল বনাব পৰা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="98"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>sudoers ফাইলত chmod কৰিব পৰা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="107"/>
      <source>Cannot open groups file for reading.</source>
      <translation>পঢ়াৰ বাবে groups ফাইল খুলিব পৰা নগ'ল।</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="37"/>
      <source>Create Volume Group</source>
      <translation>ভলিউম্ গোট বনাওক</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="37"/>
      <source>Create new volume group named %1.</source>
      <translation>%1 নামৰ নতুন ভলিউম্ গোট বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="43"/>
      <source>Create new volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; নামৰ নতুন ভলিউম্ গোট বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="49"/>
      <source>Creating new volume group named %1.</source>
      <translation>%1 নামৰ নতুন ভলিউম্ গোট বনোৱা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="61"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>ইন্স্তলাৰটোৱে '%1' নামৰ নতুন ভলিউম্ গোট বনোৱাত বিফল হৈছে।</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="45"/>
      <source>Deactivate volume group named %1.</source>
      <translation>%1 নামৰ ভলিউম গোট নিস্ক্ৰিয় কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="39"/>
      <source>Deactivate volume group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; নামৰ ভলিউম গোট নিস্ক্ৰিয় কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>ইনস্তলাৰটো %1 নামৰ ভলিউম গোট নিস্ক্ৰিয় কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="40"/>
      <source>Delete partition %1.</source>
      <translation>%1 বিভাজন বিলোপ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="47"/>
      <source>Delete partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; বিভাজন ডিলিট কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="54"/>
      <source>Deleting partition %1.</source>
      <translation>%1 বিভাজন বিলোপ কৰা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="65"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>ইনস্তলাৰটো %1 বিভাজন বিলোপ কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="108"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>এইটো ডিভাইচত এখন &lt;strong&gt;%1&lt;/strong&gt; বিভাজন তালিকা আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="115"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>এইটো এটা &lt;strong&gt;লুপ&lt;/strong&gt; ডিভাইচ। &lt;br&gt;&lt;br&gt;এইটো স্য়ুড্' ডিভাইচত কোনো বিভাজন তালিকা নাই যিয়ে ফাইলক ব্লোক ডিভাইচ ৰূপে ব্যৱহাৰ কৰিব পাৰা কৰিব। এইধৰণৰ চেত্ আপত সাধাৰণতে একক ফাইল চিছটেম থাকে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="122"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>ইনস্তলাৰটোৱে বচনি কৰা ষ্টোৰেজ ডিভাইচত বিভাজন তালিকা বিচাৰি নাপলে। ডিভাইচটোত কোনো বিভাজন তালিকা নাই বা বিভাজন তালিকা বেয়া বা অগ্যাত প্ৰকাৰ। এই ইনস্তলাৰটোৱে আপোনাৰ বাবে নতুন বিভাজন তালিকা স্বত:ভাৱে বনাব পাৰে বা মেন্যুৱেল বিভাজন পেজৰ দ্বাৰা বনাব পাৰে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="132"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;&lt;strong&gt;EFI&lt;/strong&gt; বুট পৰিবেশত আৰম্ভ হোৱা আধুনিক চিছটেমবোৰৰ কাৰণে এইটো পৰমৰ্শ কৰা বিভাজন তালিকা।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="138"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;এইটো বিভাজন তালিকা কেৱল &lt;strong&gt;BIOS&lt;/strong&gt; বুট পৰিৱেশৰ পৰা আৰম্ভ হোৱা পুৰণি চিছটেমৰ বাবে গ্ৰহণ কৰা হয়। বাকী সকলোবোৰৰ বাবে GPT উপযুক্ত।&lt;br&gt;&lt;br&gt;&lt;strong&gt;সতৰ্কবাণী:&lt;/strong&gt; MBR বিভাজন তালিকা পুৰণি MS-DOS ৰ যুগৰ পদ্ধতি। &lt;br&gt;ইয়াত কেৱল 4 &lt;em&gt;মূখ্য&lt;/em&gt; বিভাজন বনাব পাৰি, ইয়াৰ পৰা এটা &lt;em&gt;প্ৰসাৰণ&lt;/em&gt; কৰিব পাৰি আৰু ইযাৰ ভিতৰত &lt;em&gt;logical&lt;/em&gt; বিভাজন ৰাখিব পাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="151"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>বাচনি কৰা ডিভাইচৰ বিভাজন তালিকাৰ প্ৰকাৰ। বিভাজন তালিকা বিলোপ কৰি আকৌ আৰম্ভনিৰ পৰা বনাইহে বিভাজন তালিকাৰ প্ৰকাৰ সলনি কৰিব পাৰি, যিয়ে ষ্টোৰেজ ডিভাইচত থকা গোটেই ডাটা বিলোপ কৰিব। যদি আপুনি বেলেগ একো বাচনি নকৰে, ইনস্তলাৰটোৱে বৰ্তমানৰ বিভাজন তালিকা প্ৰয়োগ কৰিব। যদি আপুনি নিশ্চিত নহয়, আধুনিক চিছটেমত GPT বাচনি কৰক।</translation>
    </message>
  </context>
  <context>
    <name>DeviceModel</name>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="93"/>
      <source>%1 - %2 (%3)</source>
      <extracomment>device[name] - size[number] (device-node[name])</extracomment>
      <translation>%1 - %2 (%3)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/DeviceModel.cpp" line="104"/>
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
      <translation>Dracutৰ বাবে LUKS কনফিগাৰেচন %1ত লিখক</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="140"/>
      <source>Skip writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <translation>Dracutৰ বাবে LUKS কনফিগাৰেচন লিখা বন্ধ কৰক: "/" বিভাজনত এনক্ৰিপছন নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="157"/>
      <source>Failed to open %1</source>
      <translation>%1 খোলাত বিফল হ'ল</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="46"/>
      <source>Dummy C++ Job</source>
      <translation>ডামী C++ কাৰ্য্য</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="20"/>
      <source>Edit Existing Partition</source>
      <translation>উপলব্ধ বিভাজন সম্পাদন কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="50"/>
      <source>Content:</source>
      <translation>সামগ্ৰী:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="60"/>
      <source>&amp;Keep</source>
      <translation>ৰাখক (&amp;K)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="70"/>
      <source>Format</source>
      <translation>ফৰ্মেট</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="89"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>সকিয়নি: বিভাজনটো ফৰমেট কৰিলে উপস্থিত থকা গোটেই ডাটা বিলোপ হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="99"/>
      <source>&amp;Mount Point:</source>
      <translation>মাউন্ট পইন্ট (&amp;M):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="119"/>
      <source>Si&amp;ze:</source>
      <translation>আয়তন (&amp;z):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="136"/>
      <source>Fi&amp;le System:</source>
      <translation>ফাইল চিছটেম:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="149"/>
      <source>Flags:</source>
      <translation>ফ্লেগ সমূহ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="278"/>
      <source>Mountpoint already in use. Please select another one.</source>
      <translation>এইটো মাওন্ট্ পইন্ট্ ইতিমধ্যে ব্যৱহাৰ হৈ আছে। অনুগ্ৰহ কৰি বেলেগ এটা বাচনি কৰক।</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="32"/>
      <source>En&amp;crypt system</source>
      <translation>চিছটেম এনক্ৰিপ্ত্ কৰক (&amp;c)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="42"/>
      <source>Passphrase</source>
      <translation>পাছফ্ৰেছ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="52"/>
      <source>Confirm passphrase</source>
      <translation>পাছফ্ৰেছ নিশ্ৱিত কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="153"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <translation>অনুগ্ৰহ কৰি দুয়োটা বাকচত একে পাছফ্ৰেছ প্রবিষ্ট কৰক।</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="139"/>
      <source>Set partition information</source>
      <translation>বিভাজন তথ্য চেত্ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="165"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition.</source>
      <translation>&lt;strong&gt;নতুন&lt;/strong&gt; %2 চিছটেম বিভাজনত %1  ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="171"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; মাউন্ট পইন্টৰ সৈতে &lt;strong&gt;নতুন&lt;/strong&gt; %2 বিভজন স্থাপন কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="181"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>%3 চিছটেম বিভাজনত &lt;strong&gt;%1&lt;/strong&gt;ত %2 ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="188"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>%3 বিভাজন &lt;strong&gt;%1&lt;/strong&gt; &lt;strong&gt;%2&lt;/strong&gt;ৰ সৈতে স্থাপন কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="201"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;1%ত&lt;/strong&gt; বুত্ লোডাৰ ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="210"/>
      <source>Setting up mount points.</source>
      <translation>মাউন্ট পইন্ট চেত্ আপ হৈ আছে।</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="98"/>
      <source>&amp;Restart now</source>
      <translation>পুনৰাৰম্ভ কৰক (&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="54"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <translation>&lt;h1&gt;সকলো কৰা হ'ল।&lt;/h1&gt; &lt;br/&gt;আপোনাৰ কম্পিউটাৰত %1  স্থাপন কৰা হ'ল। &lt;br/&gt;আপুনি এতিয়া নতুন চিছটেম ব্যৱহাৰ কৰা আৰম্ভ কৰিব পাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="58"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;এইটো বিকল্পত ক্লিক কৰাৰ লগে লগে আপোনাৰ চিছটেম পুনৰাৰম্ভ হ'ব যেতিয়া আপুনি &lt;span style="font-style:italic;"&gt;হৈ গ'ল&lt;/span&gt;ত ক্লিক কৰে বা চেত্ আপ প্ৰগ্ৰেম বন্ধ কৰে।&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="66"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <translation>&lt;h1&gt;সকলো কৰা হ'ল।&lt;/h1&gt; আপোনাৰ কম্পিউটাৰত %1  ইনস্তল কৰা হ'ল। &lt;br/&gt;আপুনি এতিয়া নতুন চিছটেম পুনৰাৰম্ভ কৰিব পাৰিব অথবা %2 লাইভ বাতাৱৰণ ব্যৱহাৰ কৰা অবিৰত ৰাখিব পাৰে।</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="71"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;এইটো বিকল্পত ক্লিক কৰাৰ লগে লগে আপোনাৰ চিছটেম পুনৰাৰম্ভ হ'ব যেতিয়া আপুনি &lt;span style="font-style:italic;"&gt;হৈ গ'ল&lt;/span&gt;ত ক্লিক কৰে বা ইনস্তলাৰ বন্ধ কৰে।&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="133"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;স্থাপন প্ৰক্ৰিয়া বিফল হ'ল।&lt;/h1&gt; &lt;br/&gt;আপোনাৰ কম্পিউটাৰত %1 স্থাপন নহ'ল্। &lt;br/&gt;ক্ৰুটি বাৰ্তা আছিল: %2।</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="139"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <translation>&lt;h1&gt;ইনস্তলচেন প্ৰক্ৰিয়া বিফল হ'ল।&lt;/h1&gt; &lt;br/&gt;আপোনাৰ কম্পিউটাৰত %1 ইনস্তল নহ'ল্। &lt;br/&gt;ক্ৰুটি বাৰ্তা আছিল: %2।</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="78"/>
      <source>Finish</source>
      <translation>সমাপ্ত</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="132"/>
      <source>Setup Complete</source>
      <translation>চেত্ আপ সম্পুৰ্ণ হৈছে</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="133"/>
      <source>Installation Complete</source>
      <translation>ইনস্তলচেন সম্পুৰ্ণ হ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="135"/>
      <source>The setup of %1 is complete.</source>
      <translation>%1ৰ চেত্ আপ সম্পুৰ্ণ হৈছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="136"/>
      <source>The installation of %1 is complete.</source>
      <translation>%1ৰ ইনস্তলচেন সম্পুৰ্ণ হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="45"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4.</source>
      <translation>%4ত ফৰ্মেট বিভাজন %1 ( ফাইল চিছটেম: %2, আয়তন: %3 MiB)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="56"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%3MiB&lt;/strong&gt; ৰ &lt;strong&gt;%1 %&lt;/strong&gt; বিভাজন &lt;strong&gt;%2&lt;/strong&gt; ফাইল চিছটেমৰ সৈতে ফৰ্মেট কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="67"/>
      <source>Formatting partition %1 with file system %2.</source>
      <translation>%1 ফৰ্মেট বিভাজনৰ সৈতে %2 ফাইল চিছটেম।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="81"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>ইনস্তলাৰটো '%2' ডিস্কত %1 বিভাজন​ ফৰ্মেট কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="126"/>
      <source>has at least %1 GiB available drive space</source>
      <translation>অতি কমেও %1 GiB খালী ঠাই ড্ৰাইভত উপলব্ধ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="128"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>ড্ৰাইভত পৰ্য্যাপ্ত খালী ঠাই নাই। অতি কমেও %1 GiB আৱশ্যক।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="137"/>
      <source>has at least %1 GiB working memory</source>
      <translation>অতি কমেও %1 GiB কাৰ্য্যকৰি মেম'ৰি আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="139"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>চিছটেমত পৰ্য্যাপ্ত কাৰ্য্যকৰি মেম'ৰী নাই। অতি কমেও %1 GiB আৱশ্যক।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="148"/>
      <source>is plugged in to a power source</source>
      <translation>পাৱাৰৰ  উৎসৰ লগত সংযোগ হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="149"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>চিছটেম পাৱাৰৰ উৎসৰ লগত সংযোগ হৈ থকা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="156"/>
      <source>is connected to the Internet</source>
      <translation>ইন্টাৰনেটৰ সৈতে সংযোগ হৈছে</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="157"/>
      <source>The system is not connected to the Internet.</source>
      <translation>চিছটেমটো ইন্টাৰনেটৰ সৈতে সংযোগ হৈ থকা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="164"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>ইনস্তলাৰটো প্ৰসাশনক (ৰুট) হিছাবে চলি আছে নেকি</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="167"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>চেত্ আপ প্ৰগ্ৰেমটো প্ৰসাশনীয় অধিকাৰৰ সৈতে চলি থকা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="168"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>ইনস্তলাৰটো প্ৰসাশনীয় অধিকাৰৰ সৈতে চলি থকা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="176"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>সম্পূৰ্ণ ইনস্তলাৰটো দেখাবলৈ প্ৰয়োজনীয় ডাঙৰ স্ক্ৰীণ আছে নেকি?</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="179"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>চেত্ আপ প্ৰগ্ৰেমটো প্ৰদৰ্শন কৰিবলৈ স্ক্ৰিনখনৰ আয়তন যথেস্ট সৰু।</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="180"/>
      <source>The screen is too small to display the installer.</source>
      <translation>ইনস্তলাৰটো প্ৰদৰ্শন কৰিবলৈ স্ক্ৰিনখনৰ আয়তন যথেস্ট সৰু।</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="51"/>
      <source>Collecting information about your machine.</source>
      <translation>আপোনাৰ মেছিনৰ বিষয়ে তথ্য সংগ্ৰহ কৰি আছে।</translation>
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
      <translation>মূল উপকৰণ নিৰ্মাতা গোট চিনক্তকাৰী</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="48"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; ডিৰেক্টৰীবোৰ বনাব পৰা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; ফাইল খুলিব পৰা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="68"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; ফাইলত লিখিব পৰা নাই।</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="40"/>
      <source>Creating initramfs with mkinitcpio.</source>
      <translation>mkinitcpioৰ দ্বাৰা initramfs বনাই থকা হৈছে।</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="37"/>
      <source>Creating initramfs.</source>
      <translation>initramfs বনাই থকা হৈছে।</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="53"/>
      <source>Konsole not installed</source>
      <translation>কনচোল্ ইন্সটল কৰা নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="54"/>
      <source>Please install KDE Konsole and try again!</source>
      <translation>অনুগ্ৰহ কৰি কেডিই কনচোল্ ইন্সটল কৰক আৰু পুনৰ চেষ্টা কৰক!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="116"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <translation>নিস্পাদিত লিপি: &amp;nbsp; &lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="47"/>
      <source>Script</source>
      <translation>লিপি</translation>
    </message>
  </context>
  <context>
    <name>KeyboardPage</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="213"/>
      <source>Set keyboard model to %1.&lt;br/&gt;</source>
      <translation>কিবোৰ্ডৰ মডেল %1ত চেট্ কৰক।&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.cpp" line="217"/>
      <source>Set keyboard layout to %1/%2.</source>
      <translation>কিবোৰ্ডৰ লেআউট %1/%2 চেট্ কৰক।</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="42"/>
      <source>Keyboard</source>
      <translation>কিবোৰ্ড</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="54"/>
      <source>Keyboard</source>
      <translation>কিবোৰ্ড</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="32"/>
      <source>System locale setting</source>
      <translation>চিছটেম থলি ছেটিং</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="39"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>চিছটেমৰ স্থানীয় ছেটিংস্ কমাণ্ডলাইনৰ কিছুমান উপভোক্তা ইন্টাৰফেছ উপাদানৰ ভাষা আৰু আখৰবোৰত প্ৰভাৱ পেলায়। বৰ্তমান ছেটিংস্ হ'ল: &lt;strong&gt;%1&lt;/strong&gt;।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="63"/>
      <source>&amp;Cancel</source>
      <translation>বাতিল কৰক (&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="64"/>
      <source>&amp;OK</source>
      <translation>ঠিক আছে (&amp;O)</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="22"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;অনুজ্ঞা-পত্ৰ চুক্তি&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>I accept the terms and conditions above.</source>
      <translation>মই ওপৰোক্ত চৰ্তাৱলী গ্ৰহণ কৰিছোঁ।</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="151"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <translation>অনুগ্ৰহ কৰি ব্যৱহাৰকৰ্তাৰ অনুজ্ঞা-পত্ৰ চুক্তি (EULA) সমূহ ভালদৰে নিৰীক্ষণ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="156"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <translation>এই চেচ্ আপ প্ৰক্ৰিয়াই মালিকানা চফটৱেৰ ইনস্তল কৰিব যিটো অনুজ্ঞা-পত্ৰৰ চৰ্তৰ অধীন বিষয় হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="159"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <translation>যদি আপুনি চৰ্তাৱলী গ্ৰহণ নকৰে, চেত্ আপ প্ৰক্ৰিয়া চলাই যাব নোৱাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="164"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <translation>এই চেত্ আপ প্ৰক্ৰিয়াই অতিৰিক্ত বৈশিষ্ট্য থকা সঁজুলি প্ৰদান কৰি ব্যৱহাৰকৰ্তাৰ অভিজ্ঞতা সংবৰ্দ্ধন কৰাৰ বাবে মালিকানা চফটৱেৰ ইনস্তল কৰিব যিটো অনুজ্ঞা-পত্ৰৰ চৰ্তৰ অধীন বিষয় হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="169"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <translation>যাদি আপুনি চৰ্তাৱলী নামানে, মালিকিস্ৱত্ত থকা চফ্টৱেৰ ইনস্তল নহব আৰু মুকলি উৎস বিকল্প ব্যৱহাৰ হ'ব।</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="52"/>
      <source>License</source>
      <translation>অনুজ্ঞা-পত্ৰ</translation>
    </message>
  </context>
  <context>
    <name>LicenseWidget</name>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="96"/>
      <source>URL: %1</source>
      <translation>URL: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="117"/>
      <source>&lt;strong&gt;%1 driver&lt;/strong&gt;&lt;br/&gt;by %2</source>
      <extracomment>%1 is an untranslatable product name, example: Creative Audigy driver</extracomment>
      <translation>&lt;br/&gt;%2ৰ দ্ৱাৰা &lt;strong&gt;%1 ড্ৰাইভাৰ&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="124"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;br/&gt;&lt;font color="Grey"&gt;%2ৰ দ্ৱাৰা&lt;/font&gt; &lt;strong&gt;%1 গ্ৰাফিক্চ্ ড্ৰাইভাৰ&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="130"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;br/&gt;&lt;font color="Grey"&gt;%2ৰ দ্ৱাৰা&lt;/font&gt; &lt;strong&gt;%1 ব্ৰাউজাৰ প্লাগ ইন&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="136"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;br/&gt;&lt;font color="Grey"&gt;%2ৰ দ্ৱাৰা&lt;/font&gt; &lt;strong&gt;%1 কোডেক&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="142"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;br/&gt;&lt;font color="Grey"&gt;%2ৰ দ্ৱাৰা&lt;/font&gt; &lt;strong&gt;%1 পেকেজ&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="148"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <translation>&lt;br/&gt;&lt;font color="Grey"&gt;%2ৰ দ্ৱাৰা&lt;/font&gt; &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="171"/>
      <source>File: %1</source>
      <translation>ফাইল: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Hide license text</source>
      <translation>অনুজ্ঞা-পত্ৰৰ লেখনি লুকাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="194"/>
      <source>Show the license text</source>
      <translation>অনুজ্ঞা-পত্ৰৰ লেখনি দেখাওক</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="198"/>
      <source>Open license agreement in browser.</source>
      <translation>অনুজ্ঞা-পত্ৰ চুক্তি ব্ৰাউজাৰত দেখাওক।</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="127"/>
      <source>Region:</source>
      <translation>ক্ষেত্ৰ:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="128"/>
      <source>Zone:</source>
      <translation>মন্ডল:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="129"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>&amp;Change...</source>
      <translation>সলনি... (&amp;C)</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="262"/>
      <source>The system language will be set to %1.</source>
      <translation>চিছটেমৰ ভাষা %1লৈ সলনি কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="263"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <translation>সংখ্যা আৰু তাৰিখ স্থানীয় %1লৈ সলনি কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="270"/>
      <source>Set timezone to %1/%2.&lt;br/&gt;</source>
      <translation>সময় জ'ন  %1/%2লৈ সলনি কৰা হ'ল।&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="95"/>
      <source>Location</source>
      <translation>অৱস্থান</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="100"/>
      <source>Location</source>
      <translation>অৱস্থান</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="39"/>
      <source>Configuring LUKS key file.</source>
      <translation>LUKS কি ফাইল কনফিগাৰ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="156"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="164"/>
      <source>No partitions are defined.</source>
      <translation>কোনো বিভাজনৰ বৰ্ণনা দিয়া নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="192"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="199"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="207"/>
      <source>Encrypted rootfs setup error</source>
      <translation>এনক্ৰিপছন থকা rootfs চেত্ আপত ত্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="193"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>ৰুট বিভাজন %1 LUKS, কিন্তু পাসফ্রেজ ছেট কৰা হোৱা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="200"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>%1 ৰুট বিভাজনৰ বাবে LUKS কি বনাৱ পৰা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="208"/>
      <source>Could not configure LUKS key file on partition %1.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="46"/>
      <source>Generate machine-id.</source>
      <translation>মেচিন-আইডি সৃষ্টি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="62"/>
      <source>Configuration Error</source>
      <translation>কনফিগাৰেচন ত্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="63"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>এইটো মেচিন-আইডিৰ বাবে কোনো মাউন্ট্ পইণ্ট্ট্ট্ ছেট কৰা নাই।</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Package selection</source>
      <translation>পেকেজ বাচনি</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Office software</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Office package</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Browser software</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Browser package</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Web browser</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="69"/>
      <source>Kernel</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="70"/>
      <source>Services</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="71"/>
      <source>Login</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="72"/>
      <source>Desktop</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="73"/>
      <source>Applications</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="74"/>
      <source>Communication</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="75"/>
      <source>Development</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="76"/>
      <source>Office</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="77"/>
      <source>Multimedia</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="78"/>
      <source>Internet</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="79"/>
      <source>Theming</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="80"/>
      <source>Gaming</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="81"/>
      <source>Utilities</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="34"/>
      <source>Notes</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="28"/>
      <source>Ba&amp;tch:</source>
      <translation>দল(&amp;t):</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="38"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;দলৰ পৰিচয় লিখক। এইটো গন্তব্য চিছটেমত জমা থাকিব।&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="48"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;মূল উপকৰণ নিৰ্মাতা কনফিগাৰেচন।&lt;/h1&gt; &lt;p&gt;গন্তব্য চিছটেম কনফিগাৰ কৰোতে কেলামাৰেচে মূল উপকৰণ নিৰ্মাতাৰ চেটিংস ব্যৱহাৰ কৰিব।&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="121"/>
      <source>OEM Configuration</source>
      <translation>মূল উপকৰণ নিৰ্মাতা কনফিগাৰেচন</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="126"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1ত&lt;/code&gt; মূল উপকৰণ নিৰ্মাতা গোট চিনক্তকাৰি চেত্ কৰক।</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="57"/>
      <source>Password is too short</source>
      <translation>পাছৱৰ্ড বহুত ছুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="73"/>
      <source>Password is too long</source>
      <translation>পাছৱৰ্ড বহুত দীঘল</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="149"/>
      <source>Password is too weak</source>
      <translation>পাছৱৰ্ড বহুত দুৰ্বল</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="157"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>'%1' চেটিংস কৰোতে মেম'ৰী আৱন্টন ক্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="162"/>
      <source>Memory allocation error</source>
      <translation>মেম'ৰী আৱন্টন ক্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="164"/>
      <source>The password is the same as the old one</source>
      <translation>পাছৱৰ্ডটো পুৰণি পাছৱৰ্ডৰ লগত একে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="166"/>
      <source>The password is a palindrome</source>
      <translation>পাছৱৰ্ডটো পেলিন্ড্ৰোম</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="168"/>
      <source>The password differs with case changes only</source>
      <translation>পাছৱৰ্ডকেইটাৰ মাজত কেৱল lower/upper caseৰ পাৰ্থক্য আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="170"/>
      <source>The password is too similar to the old one</source>
      <translation>পাছৱৰ্ডটো পুৰণি পাছৱৰ্ডৰ লগত যথেষ্ট একে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="172"/>
      <source>The password contains the user name in some form</source>
      <translation>পাছৱৰ্ডটোত কিবা প্ৰকাৰে ব্যৱহাৰকাৰীৰ নাম আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="174"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>পাছৱৰ্ডটোত কিবা প্ৰকাৰে ব্যৱহাৰকাৰীৰ আচল নামৰ কিবা শব্দ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="177"/>
      <source>The password contains forbidden words in some form</source>
      <translation>পাছৱৰ্ডটোত কিবা প্ৰকাৰে নিষিদ্ধ শব্দ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="181"/>
      <source>The password contains less than %1 digits</source>
      <translation>পাছৱৰ্ডটোত %1টাতকৈ কম সংখ্যা আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="184"/>
      <source>The password contains too few digits</source>
      <translation>পাছৱৰ্ডটোত বহুত কম সংখ্যাক সংখ্যা আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="188"/>
      <source>The password contains less than %1 uppercase letters</source>
      <translation>পাছৱৰ্ডটোত %1টাতকৈ কম uppercaseৰ বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="191"/>
      <source>The password contains too few uppercase letters</source>
      <translation>পাছৱৰ্ডটোত বহুত কম সংখ্যাক কম uppercaseৰ বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="195"/>
      <source>The password contains less than %1 lowercase letters</source>
      <translation>পাছৱৰ্ডটোত %1টাতকৈ কম lowercaseৰ বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="198"/>
      <source>The password contains too few lowercase letters</source>
      <translation>পাছৱৰ্ডটোত বহুত কম সংখ্যাক কম lowercaseৰ বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password contains less than %1 non-alphanumeric characters</source>
      <translation>পাছৱৰ্ডটোত %1টাতকৈ কম non-alphanumeric বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>পাছৱৰ্ডটোত বহুত কম সংখ্যাক কম non-alphanumeric বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password is shorter than %1 characters</source>
      <translation>পাছৱৰ্ডটোত %1টা বৰ্ণতকৈ ছুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="213"/>
      <source>The password is too short</source>
      <translation>পাছৱৰ্ডটো বহুত ছুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password is just rotated old one</source>
      <translation>পাছৱৰ্ডটো পুৰণি পাছৱৰ্ডৰ লগত সংশ্লিষ্ট</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains less than %1 character classes</source>
      <translation>পাছৱৰ্ডটোত %1টাতকৈ কম বৰ্ণ শ্ৰেণী আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password does not contain enough character classes</source>
      <translation>পাছৱৰ্ডটোত থকা বৰ্ণ শ্ৰেণী যথেষ্ট নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains more than %1 same characters consecutively</source>
      <translation>পাছৱৰ্ডটোত %1বাৰতকৈ বেছি একে বৰ্ণ উপর্যুপৰি আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="230"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>পাছৱৰ্ডটোত একে বৰ্ণ উপর্যুপৰি বহুতবাৰ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="234"/>
      <source>The password contains more than %1 characters of the same class consecutively</source>
      <translation>পাছৱৰ্ডটোত %1বাৰতকৈ একে বৰ্ণ শ্ৰেণীৰ বৰ্ণ উপর্যুপৰি বহুতবাৰ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="238"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>পাছৱৰ্ডটোত একে বৰ্ণ শ্ৰেণীৰ বৰ্ণ উপর্যুপৰি বহুতো আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains monotonic sequence longer than %1 characters</source>
      <translation>পাছৱৰ্ডটোত %1তকৈ বেছি ম'ন'টনিক চিকুৱেন্স্ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>পাছৱৰ্ডটোত বহুত দীঘল ম'ন'টনিক চিকুৱেন্স্ বৰ্ণ আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>No password supplied</source>
      <translation>কোনো পাছৱৰ্ড্ দিয়া নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>RNG ডেভাইচৰ পৰা কোনো ৰেণ্ডম সংখ্যা পোৱা নগ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="254"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>পাছৱৰ্ড্ বনোৱা কাৰ্য্য বিফল হ'ল - চেটিংসৰ বাবে আৱশ্যক এন্ট্ৰ'পী বহুত কম আছে</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="260"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>পাছৱৰ্ডটো অভিধানৰ পৰীক্ষণত বিফল হ'ল - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password fails the dictionary check</source>
      <translation>পাছৱৰ্ডটো অভিধানৰ পৰীক্ষণত বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="267"/>
      <source>Unknown setting - %1</source>
      <translation>অজ্ঞাত ছেটিংস - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="271"/>
      <source>Unknown setting</source>
      <translation>অজ্ঞাত ছেটিংস</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="275"/>
      <source>Bad integer value of setting - %1</source>
      <translation>ছেটিংসৰ বেয়া পুৰ্ণ সংখ্যা মান - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="280"/>
      <source>Bad integer value</source>
      <translation>বেয়া পুৰ্ণ সংখ্যা মান</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="284"/>
      <source>Setting %1 is not of integer type</source>
      <translation>চেটিংস্ %1 পূৰ্ণাংক নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="289"/>
      <source>Setting is not of integer type</source>
      <translation>চেটিংস্ পূৰ্ণাংক নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="293"/>
      <source>Setting %1 is not of string type</source>
      <translation>চেটিংস্ %1 স্ট্ৰিং নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="298"/>
      <source>Setting is not of string type</source>
      <translation>চেটিংস্ স্ট্ৰিং নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="300"/>
      <source>Opening the configuration file failed</source>
      <translation>কনফিগাৰেচন ফাইল খোলাত বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The configuration file is malformed</source>
      <translation>কনফিগাৰেচন ফাইলটো বেয়া</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="304"/>
      <source>Fatal failure</source>
      <translation>গভীৰ বিফলতা</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown error</source>
      <translation>অজ্ঞাত ক্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="581"/>
      <source>Password is empty</source>
      <translation>খালী পাছৱৰ্ড</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="20"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="40"/>
      <source>Product Name</source>
      <translation>পণ্যৰ নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="53"/>
      <source>TextLabel</source>
      <translation>TextLabel</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="69"/>
      <source>Long Product Description</source>
      <translation>পণ্যৰ দীঘল বিৱৰণ</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="34"/>
      <source>Package Selection</source>
      <translation>পেকেজ নিৰ্বাচন</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="35"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>সুচীৰ পৰা পণ্য এটা বাচনি কৰক। বাচনি কৰা পণ্যটো ইনস্তল হ'ব।</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserViewStep</name>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserViewStep.cpp" line="70"/>
      <source>Packages</source>
      <translation>পেকেজ</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Name</source>
      <translation>নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="176"/>
      <source>Description</source>
      <translation>বিৱৰণ</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="70"/>
      <source>Keyboard Model:</source>
      <translation>কিবোৰ্ড মডেল:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="131"/>
      <source>Type here to test your keyboard</source>
      <translation>আপোনাৰ কিবোৰ্ড পৰীক্ষা কৰিবলৈ ইয়াত টাইপ কৰক</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="36"/>
      <source>What is your name?</source>
      <translation>আপোনাৰ নাম কি?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="51"/>
      <source>Your Full Name</source>
      <translation>আপোনাৰ সম্পূৰ্ণ নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="120"/>
      <source>What name do you want to use to log in?</source>
      <translation>লগইনত আপোনি কি নাম ব্যৱহাৰ কৰিব বিচাৰে?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="144"/>
      <source>login</source>
      <translation>লগইন</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="219"/>
      <source>What is the name of this computer?</source>
      <translation>এইটো কম্পিউটাৰৰ নাম কি?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="243"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;যদি আপুনি আপোনাৰ কম্পিউটাৰটো বেলেগে নেটৱৰ্কত প্ৰদৰ্শন কৰে এই নামটো ব্যৱহাৰ হ'ব।&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="246"/>
      <source>Computer Name</source>
      <translation>কম্পিউটাৰৰ নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="321"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>আপোনাৰ একাউণ্ট সুৰক্ষিত ৰাখিবলৈ পাছৱৰ্ড এটা বাছনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="345"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="370"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;একে পাছৱৰ্ড দুবাৰ লিখক, যাতে লিখন ক্ৰুটিৰ পৰীক্ষণ কৰিব পৰা যায়। এটা ভাল পাছৱৰ্ডত বৰ্ণ, সংখ্যা আৰু punctuationৰ মিশ্ৰণ থাকে, অতি কমেও আঠটা বৰ্ণ থাকিব লাগে আৰু নিয়মিত সমযৰ ব্যৱধানত সলনি কৰি থাকিব লাগে।&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="351"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="521"/>
      <source>Password</source>
      <translation>পাছৱৰ্ড</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="376"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="546"/>
      <source>Repeat Password</source>
      <translation>পাছৱৰ্ড পুনৰ লিখক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="451"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>এই বাকচটো চিহ্নিত কৰিলে পাছ্ৱৰ্ডৰ প্ৰৱলতা কৰা হ'ব আৰু আপুনি দুৰ্বল পাছৱৰ্ড ব্যৱহাৰ কৰিব নোৱাৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="454"/>
      <source>Require strong passwords.</source>
      <translation>শক্তিশালী পাছৱৰ্ডৰ আৱশ্যক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="461"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>কোনো পাছৱৰ্ড নোসোধাকৈ স্ৱত:পূৰ্ণ  লগ্ইন কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="468"/>
      <source>Use the same password for the administrator account.</source>
      <translation>প্ৰশাসনীয় একাউন্টৰ বাবে একে পাছৱৰ্ড্ ব্যৱহাৰ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="491"/>
      <source>Choose a password for the administrator account.</source>
      <translation>প্ৰশাসনীয় একাউন্টৰ বাবে পাছৱৰ্ড এটা বাছনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="515"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="540"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;একে পাছৱৰ্ড দুবাৰ লিখক, যাতে লিখাত ক্ৰুটি আছে নেকি পৰীক্ষা কৰিব পাৰে।&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="197"/>
      <source>Root</source>
      <translation>মূল</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="200"/>
      <source>Home</source>
      <translation>ঘৰ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="202"/>
      <source>Boot</source>
      <translation>বুত্</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="205"/>
      <source>EFI system</source>
      <translation>ই এফ আই (EFI) চিছটেম</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="207"/>
      <source>Swap</source>
      <translation>স্ৱেপ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="209"/>
      <source>New partition for %1</source>
      <translation>%1 ৰ বাবে নতুন বিভাজন</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="211"/>
      <source>New partition</source>
      <translation>নতুন বিভাজন</translation>
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
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="168"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="208"/>
      <source>Free Space</source>
      <translation>খালী ঠাই</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="172"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="212"/>
      <source>New partition</source>
      <translation>নতুন বিভাজন</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="305"/>
      <source>Name</source>
      <translation>নাম</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>File System</source>
      <translation>ফাইল চিছটেম</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>Mount Point</source>
      <translation>মাউন্ট পইন্ট</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>Size</source>
      <translation>আয়তন</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="22"/>
      <source>Storage de&amp;vice:</source>
      <translation>ষ্টোৰেজ ডিভাইচ (&amp;v):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="51"/>
      <source>&amp;Revert All Changes</source>
      <translation>সকলো সলনি আগৰ দৰে কৰক (&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="87"/>
      <source>New Partition &amp;Table</source>
      <translation>নতুন বিভাজন তালিকা (&amp;T)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="107"/>
      <source>Cre&amp;ate</source>
      <translation>বনাওক (&amp;a)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="114"/>
      <source>&amp;Edit</source>
      <translation>সম্পাদনা কৰক (&amp;E)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="121"/>
      <source>&amp;Delete</source>
      <translation>বিলোপ কৰক (&amp;D)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="132"/>
      <source>New Volume Group</source>
      <translation>নতুন ভলিউম্ গোট</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="139"/>
      <source>Resize Volume Group</source>
      <translation>ভলিউম্ গোটৰ আয়তন সলনি কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="146"/>
      <source>Deactivate Volume Group</source>
      <translation>ভলিউম্ গোট নিস্ক্ৰিয় কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="153"/>
      <source>Remove Volume Group</source>
      <translation>ভলিউম্ গোট বিলোপ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="180"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>বুট লোডাৰ ইনস্তল কৰক (&amp;I):</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="211"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>আপুনি নিশ্চিতভাৱে %1ত নতুন তালিকা বনাব বিচাৰে নেকি?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="240"/>
      <source>Can not create new partition</source>
      <translation>নতুন বিভাজন বনাব নোৱৰি</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="241"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>%1ত থকা বিভাজন তালিকাত ইতিমধ্যে %2 মূখ্য বিভাজন আছে, আৰু একো যোগ কৰিব নোৱাৰিব। তাৰ সলনি এখন মূখ্য বিভাজন বিলোপ কৰক আৰু এখন প্ৰসাৰিত বিভাজন যোগ কৰক।</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="77"/>
      <source>Gathering system information...</source>
      <translation>চিছটেম তথ্য সংগ্ৰহ কৰা হৈ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="131"/>
      <source>Partitions</source>
      <translation>বিভাজনসমুহ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="168"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system.</source>
      <translation>%1ক বেলেগ এটা অপাৰেটিং চিছটেমৰ &lt;strong&gt;লগত &lt;/strong&gt;ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="173"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1.</source>
      <translation>ডিস্কত থকা সকলো ডাটা &lt;strong&gt;আতৰাওক&lt;/strong&gt; আৰু %1 ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="177"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1.</source>
      <translation>এখন বিভাজন %1ৰ লগত &lt;strong&gt;সলনি&lt;/strong&gt; কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="181"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning.</source>
      <translation>&lt;strong&gt;মেনুৱেল&lt;/strong&gt; বিভাজন।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="194"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3).</source>
      <translation>%1ক &lt;strong&gt;%2&lt;/strong&gt;(%3)ত ডিস্কত থকা বেলেগ অপাৰেটিং চিছটেমৰ &lt;strong&gt;লগত&lt;/strong&gt; ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="201"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3)ডিস্কত থকা সকলো ডাটা &lt;strong&gt;আতৰাওক&lt;/strong&gt; আৰু %1 ইনস্তল কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="207"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3) ডিস্কত এখন বিভাজন %1ৰ লগত &lt;strong&gt;সলনি&lt;/strong&gt; কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="214"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2).</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; (%2) ডিস্কত &lt;strong&gt;মেনুৱেল&lt;/strong&gt; বিভাজন।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="223"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <translation>ডিস্ক্ &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="249"/>
      <source>Current:</source>
      <translation>বর্তমান:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="266"/>
      <source>After:</source>
      <translation>পিছত:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="432"/>
      <source>No EFI system partition configured</source>
      <translation>কোনো EFI চিছটেম বিভাজন কনফিগাৰ কৰা হোৱা নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="433"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a FAT32 filesystem with the &lt;strong&gt;%3&lt;/strong&gt; flag enabled and mount point &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;&lt;br/&gt;You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="447"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;A partition was configured with mount point &lt;strong&gt;%2&lt;/strong&gt; but its &lt;strong&gt;%3&lt;/strong&gt; flag is not set.&lt;br/&gt;To set the flag, go back and edit the partition.&lt;br/&gt;&lt;br/&gt;You can continue without setting the flag but your system may fail to start.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="446"/>
      <source>EFI system partition flag not set</source>
      <translation>EFI চিছটেম বিভাজনত ফ্লেগ চেট কৰা নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="473"/>
      <source>Option to use GPT on BIOS</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="474"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;bios_grub&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="502"/>
      <source>Boot partition not encrypted</source>
      <translation>বুত্ বিভাজন এনক্ৰিপ্ত্ নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="503"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>এনক্ৰিপ্তেড ৰুট বিভাজনৰ সৈতে এটা বেলেগ বুট বিভাজন চেত্ আপ কৰা হৈছিল, কিন্তু বুট বিভাজন এনক্ৰিপ্তেড কৰা হোৱা নাই। &lt;br/&gt;&lt;br/&gt;এইধৰণৰ চেত্ আপ সুৰক্ষিত নহয় কাৰণ গুৰুত্ব্পুৰ্ণ চিছটেম ফাইল আন্এনক্ৰিপ্তেড বিভাজনত ৰখা হয়। &lt;br/&gt;আপুনি বিচাৰিলে চলাই থাকিব পাৰে কিন্তু পিছ্ত চিছটেম আৰম্ভৰ সময়ত ফাইল চিছটেম খোলা যাব। &lt;br/&gt;বুট বিভাজন এনক্ৰিপ্ত্ কৰিবলৈ উভতি যাওক আৰু বিভাজন বনোৱা windowত &lt;strong&gt;Encrypt&lt;/strong&gt; বাচনি কৰি আকৌ বনাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="720"/>
      <source>has at least one disk device available.</source>
      <translation>অতি কমেও এখন ডিস্ক্ উপলব্ধ আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionViewStep.cpp" line="721"/>
      <source>There are no partitions to install on.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="41"/>
      <source>Plasma Look-and-Feel Job</source>
      <translation>প্লজমা Look-and-Feel কাৰ্য্য</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="73"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="74"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>কেডিই প্লাজ্মা Look-and-Feel পেকেজ বাচনি কৰিব পৰা নগ'ল</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/page_plasmalnf.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="70"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>অনুগ্ৰহ কৰি কেডিই প্লজ্মা ডেক্সটপৰ বাবে এটা look-and-feel বাচনি কৰে। আপুনি এতিয়াৰ বাবে এইটো পদক্ষেপ এৰি থব পাৰে আৰু চিছটেম স্থাপন কৰাৰ পিছতো look-and-feel কন্ফিগাৰ কৰিব পাৰে। look-and-feel বাচনি এটাত ক্লিক্ কৰিলে ই আপোনাক live preview দেখুৱাব।</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="76"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>অনুগ্ৰহ কৰি কেডিই প্লজ্মা ডেক্সটপৰ বাবে এটা look-and-feel বাচনি কৰে। আপুনি এতিয়াৰ বাবে এইটো পদক্ষেপ এৰি থব পাৰে আৰু চিছটেম ইনস্তল কৰাৰ পিছতো look-and-feel কন্ফিগাৰ কৰিব পাৰে। look-and-feel বাচনি এটাত ক্লিক্ কৰিলে ই আপোনাক live preview দেখুৱাব।</translation>
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
      <translation>ফাইল পিছৰ বাবে জমা কৰি আছে ...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="122"/>
      <source>No files configured to save for later.</source>
      <translation>পিছলৈ জমা ৰাখিব কোনো ফাইল কন্ফিগাৰ কৰা হোৱা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="176"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>কন্ফিগাৰ কৰা গোটেই ফাইল জমা ৰাখিব নোৱৰি।</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="418"/>
      <source>
There was no output from the command.</source>
      <translation>
কমাণ্ডৰ পৰা কোনো আউটপুট পোৱা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="419"/>
      <source>
Output:
</source>
      <translation>
আউটপুট
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="423"/>
      <source>External command crashed.</source>
      <translation>বাহ্যিক কমাণ্ড ক্ৰেছ্ কৰিলে।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="424"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; কমাণ্ড ক্ৰেছ্ কৰিলে।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="429"/>
      <source>External command failed to start.</source>
      <translation>বাহ্যিক কমাণ্ড আৰম্ভ হোৱাত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="430"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; কমাণ্ড আৰম্ভ হোৱাত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="434"/>
      <source>Internal error when starting command.</source>
      <translation>কমাণ্ড আৰম্ভ কৰাৰ সময়ত আভ্যন্তৰীণ ক্ৰুটি।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="435"/>
      <source>Bad parameters for process job call.</source>
      <translation>প্ৰক্ৰিয়া কাৰ্য্যৰ বাবে বেয়া মান।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="439"/>
      <source>External command failed to finish.</source>
      <translation>বাহ্যিক কমাণ্ড সমাপ্ত কৰাত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="440"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; কমাণ্ড সমাপ্ত কৰাত %2 ছেকেণ্ডত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="447"/>
      <source>External command finished with errors.</source>
      <translation>বাহ্যিক কমাণ্ড ক্ৰটিৰ সৈতে সমাপ্ত হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CalamaresUtilsSystem.cpp" line="448"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; কমাণ্ড %2 এক্সিড্ কোডৰ সৈতে সমাপ্ত হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>QObject</name>
    <message>
      <location filename="../src/libcalamares/locale/Label.cpp" line="37"/>
      <source>%1 (%2)</source>
      <translation>%1 (%2)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="63"/>
      <source>Requirements checking for module &lt;i&gt;%1&lt;/i&gt; is complete.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; মডিউল পৰীক্ষণৰ বাবে আৱশ্যকতাবোৰ সম্পূৰ্ণ হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="36"/>
      <source>unknown</source>
      <translation>অজ্ঞাত</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="38"/>
      <source>extended</source>
      <translation>প্ৰসাৰিত</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="40"/>
      <source>unformatted</source>
      <translation>ফৰ্মেট কৰা হোৱা নাই</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="42"/>
      <source>swap</source>
      <translation>স্ৱেপ</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="91"/>
      <source>Default Keyboard Model</source>
      <translation>ডিফল্ট্ কিবোৰ্ড মডেল</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="133"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="168"/>
      <source>Default</source>
      <translation>ডিফল্ট্</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="73"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="81"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="85"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="102"/>
      <source>File not found</source>
      <translation>ফাইল বিচাৰি পোৱা নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="74"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation>&lt;pre&gt;%1&lt;/pre&gt; পথটো পূৰ্ণ পথ নহয়।</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="103"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>&lt;pre&gt;%1&lt;/pre&gt; ৰেন্ডম ফাইল বনাব পৰা নগ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="79"/>
      <source>No product</source>
      <translation>কোনো পণ্য নাই</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="87"/>
      <source>No description provided.</source>
      <translation>একো বিৱৰণি দিয়া হোৱা নাই।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="47"/>
      <source>(no mount point)</source>
      <translation>(কোনো মাউন্ট পইন্ট নাই)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="51"/>
      <source>Unpartitioned space or unknown partition table</source>
      <translation>বিভাজন নকৰা খালী ঠাই অথবা অজ্ঞাত বিভজন তালিকা</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="43"/>
      <source>Remove live user from target system</source>
      <translation>গন্তব্য চিছটেমৰ পৰা লাইভ ব্যৱহাৰকাৰি আতৰাওক</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="45"/>
      <source>Remove Volume Group named %1.</source>
      <translation>%1 নামৰ ভলিউম্ গোট বিলোপ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="39"/>
      <source>Remove Volume Group named &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; নামৰ ভলিউম্ গোট বিলোপ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="57"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>ইনস্তলটো %1 নামৰ নতুন ভলিউম্ গোট বিলোপ কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>ReplaceWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="139"/>
      <source>Select where to install %1.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;this will delete all files on the selected partition.</source>
      <translation>%1 ক'ত ইনস্তল লাগে বাচনি কৰক।&lt;br/&gt; &lt;font color="red"&gt;সকীয়নি: ইয়ে বাচনি কৰা বিভাজনৰ সকলো ফাইল বিলোপ কৰিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="165"/>
      <source>The selected item does not appear to be a valid partition.</source>
      <translation>বাচনি কৰা বস্তুটো এটা বৈধ বিভাজন নহয়।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="173"/>
      <source>%1 cannot be installed on empty space. Please select an existing partition.</source>
      <translation>%1 খালী ঠাইত ইনস্তল কৰিব নোৱাৰি। উপস্থিতি থকা বিভাজন বাচনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="183"/>
      <source>%1 cannot be installed on an extended partition. Please select an existing primary or logical partition.</source>
      <translation>%1 প্ৰসাৰিত ঠাইত ইনস্তল কৰিব নোৱাৰি। উপস্থিতি থকা মূখ্য বা লজিকেল বিভাজন বাচনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="193"/>
      <source>%1 cannot be installed on this partition.</source>
      <translation>এইখন বিভাজনত %1 ইনস্তল কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="200"/>
      <source>Data partition (%1)</source>
      <translation>ডাটা বিভাজন (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="216"/>
      <source>Unknown system partition (%1)</source>
      <translation>অজ্ঞাত চিছটেম বিভাজন (%1)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="221"/>
      <source>%1 system partition (%2)</source>
      <translation>%1 চিছটেম বিভাজন (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="232"/>
      <source>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;The partition %1 is too small for %2. Please select a partition with capacity at least %3 GiB.</source>
      <translation>&lt;strong&gt;%4&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt; %1 বিভাজনটো %2ৰ বাবে যথেষ্ট সৰু। অনুগ্ৰহ কৰি অতি কমেও %3 GiB সক্ষমতা থকা বিভাজন বাচনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="255"/>
      <source>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <translation>&lt;strong&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;এইটো চিছটেমৰ ক'তো এটা EFI চিছটেম বিভাজন বিচাৰি পোৱা নগ'ল। অনুগ্ৰহ কৰি উভতি যাওক আৰু %1 চেত্ আপ কৰিব মেনুৱেল বিভাজন ব্যৱহাৰ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="266"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="283"/>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="307"/>
      <source>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;%1 will be installed on %2.&lt;br/&gt;&lt;font color="red"&gt;Warning: &lt;/font&gt;all data on partition %2 will be lost.</source>
      <translation>&lt;strong&gt;%3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt; %1 %2ত ইনস্তল হ'ব। &lt;br/&gt;&lt;font color="red"&gt;সকীয়নি​: &lt;/font&gt;%2 বিভাজনত থকা গোটেই ডাটা বিলোপ হৈ যাব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="275"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <translation>%1 ত থকা EFI চিছটেম বিভাজনটো %2 আৰম্ভ কৰাৰ বাবে ব্যৱহাৰ কৰা হ'ব।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ReplaceWidget.cpp" line="291"/>
      <source>EFI system partition:</source>
      <translation>EFI চিছটেম বিভাজন:</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="57"/>
      <source>Resize Filesystem Job</source>
      <translation>ফাইল চিছটেম কাৰ্য্যৰ আয়তন পৰিৱৰ্তন কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>Invalid configuration</source>
      <translation>অকার্যকৰ কনফিগাৰেচন</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="171"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <translation>ফাইল চিছটেমটোৰ আয়তন পৰিৱৰ্তন কাৰ্য্যৰ এটা অকার্যকৰ কনফিগাৰেচন আছে আৰু সেইটো নচলিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="177"/>
      <source>KPMCore not Available</source>
      <translation>KPMCore ঊপলব্ধ নহয়</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="178"/>
      <source>Calamares cannot start KPMCore for the file-system resize job.</source>
      <translation>ফাইল চিছটেমৰ আয়তন সলনি কৰিবলৈ কেলামাৰেচে KPMCore আৰম্ভ নোৱাৰিলে।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="186"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="195"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="208"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="217"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="234"/>
      <source>Resize Failed</source>
      <translation>আয়তন পৰিৱৰ্তন কাৰ্য্য বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="187"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <translation>এইটো চিছটেমত %1 ফাইল চিছটেম বিছাৰি পোৱা নগ'ল আৰু সেইটোৰ আয়তন সলনি কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="188"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <translation>এইটো চিছটেমত %1 ডিভাইচ বিছাৰি পোৱা নগ'ল আৰু সেইটোৰ আয়তন সলনি কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="196"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="209"/>
      <source>The filesystem %1 cannot be resized.</source>
      <translation>%1 ফাইল চিছটেমটোৰ আয়তন সলনি কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="197"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="210"/>
      <source>The device %1 cannot be resized.</source>
      <translation>%1 ডিভাইচটোৰ আয়তন সলনি কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="218"/>
      <source>The filesystem %1 must be resized, but cannot.</source>
      <translation>%1 ফাইল চিছটেমটোৰ আয়তন সলনি কৰিব লাগে, কিন্তু কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="219"/>
      <source>The device %1 must be resized, but cannot</source>
      <translation>%1 ডিভাইচটোৰ আয়তন সলনি কৰিব লাগে, কিন্তু কৰিব নোৱাৰি।</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="49"/>
      <source>Resize partition %1.</source>
      <translation>%1 বিভাজনৰ আয়তন সলনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="56"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%2MiB&lt;/strong&gt; আয়তনৰ &lt;strong&gt;%1&lt;/strong&gt; বিভাজনৰ আয়তন সলনি কৰি &lt;strong&gt;%3MiB&lt;/strong&gt; কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="67"/>
      <source>Resizing %2MiB partition %1 to %3MiB.</source>
      <translation>%2MiB ৰ %1 বিভাজনৰ আয়তন সলনি কৰি %3 কৰি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="86"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>ইনস্তলাৰটো '%2' ডিস্কত %1 বিভাজনৰ​ আয়তন সলনি কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="39"/>
      <source>Resize Volume Group</source>
      <translation>ভলিউম্ গোটৰ আয়তন সলনি কৰক</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="36"/>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="54"/>
      <source>Resize volume group named %1 from %2 to %3.</source>
      <translation>%1 নামৰ ভলিউম্ গোটটোৰ আয়তন %2ৰ পৰা %3লৈ সলনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="45"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; নামৰ ভলিউম্ গোটটোৰ আয়তন &lt;strong&gt;%2&lt;/strong&gt;ৰ পৰা &lt;strong&gt;%3&lt;/strong&gt;লৈ সলনি কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="69"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>ইনস্তলাৰটো %1 নামৰ ভলিউম্ গোটটোৰ আয়তন সলনি কৰাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>ResultsListDialog</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="140"/>
      <source>For best results, please ensure that this computer:</source>
      <translation>উত্কৃষ্ট ফলাফলৰ বাবে অনুগ্ৰহ কৰি নিশ্চিত কৰক যে এইটো কম্পিউটাৰ হয়:</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="141"/>
      <source>System requirements</source>
      <translation>চিছটেমৰ আৱশ্যকতাবোৰ</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="261"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>%1 চেত্ আপৰ বাবে নিম্নতম আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;স্থাপন প্ৰক্ৰিয়া অবিৰত ৰাখিব নোৱাৰিব। &lt;a href="#details"&gt;বিৱৰণ...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="265"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue. &lt;a href="#details"&gt;Details...&lt;/a&gt;</source>
      <translation>%1 ইনস্তলচেন​ৰ বাবে নিম্নতম আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;ইনস্তলচেন​ প্ৰক্ৰিয়া অবিৰত ৰাখিব নোৱাৰিব। &lt;a href="#details"&gt;বিৱৰণ...&lt;/a&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="272"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>%1 চেত্ আপৰ বাবে পৰামৰ্শ দিয়া আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। &lt;br/&gt;স্থাপন প্ৰক্ৰিয়া অবিৰত ৰাখিব পাৰিব, কিন্তু কিছুমান সুবিধা নিষ্ক্রিয় হৈ থাকিব। </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="276"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>%1 ইনস্তলচেন​ৰ বাবে পৰামৰ্শ দিয়া আৱশ্যকতা এই কম্পিউটাৰটোৱে পূৰ্ণ নকৰে। ইনস্তলচেন​ অবিৰত ৰাখিব পাৰিব, কিন্তু কিছুমান সুবিধা নিষ্ক্রিয় হৈ থাকিব। </translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="285"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>এইটো প্ৰগ্ৰেমে অপোনাক কিছুমান প্ৰশ্ন সুধিব আৰু অপোনাৰ কম্পিউটাৰত %2 স্থাপন কৰিব।</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="84"/>
      <source>Scanning storage devices...</source>
      <translation>ষ্টোৰেজ ডিভাইচ স্কেন কৰি আছে...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="85"/>
      <source>Partitioning</source>
      <translation>বিভাজন কৰি আছে</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="46"/>
      <source>Set hostname %1</source>
      <translation>%1 হোস্ট্ নাম চেত্ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="53"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; হোস্ট্ নাম চেত্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="60"/>
      <source>Setting hostname %1.</source>
      <translation>%1 হোস্ট্ নাম চেত্ কৰি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="131"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="138"/>
      <source>Internal Error</source>
      <translation>আভ্যন্তৰিণ ক্ৰুটি</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="146"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="155"/>
      <source>Cannot write hostname to target system</source>
      <translation>গন্তব্য চিছটেমত হোষ্ট নাম লিখিব নোৱাৰিলে</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="59"/>
      <source>Set keyboard model to %1, layout to %2-%3</source>
      <translation>কিবোৰ্ডৰ মডেল %1 চেত্ কৰক, বিন্যাস %2-%3</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="351"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <translation>ভাৰচুৱেল কনচ'লৰ বাবে কিবোৰ্ড কনফিগাৰেচন লিখাত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="352"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="356"/>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="363"/>
      <source>Failed to write to %1</source>
      <translation>%1 ত লিখাত বিফল হ'ল</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="355"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <translation>X11ৰ বাবে কিবোৰ্ড কনফিগাৰেচন লিখাত বিফল হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="362"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <translation>উপস্থিত থকা /etc/default ডিৰেক্টৰিত কিবোৰ্ড কনফিগাৰেচন লিখাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="52"/>
      <source>Set flags on partition %1.</source>
      <translation>%1 বিভাজনত ফ্লেগ চেত্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="58"/>
      <source>Set flags on %1MiB %2 partition.</source>
      <translation>%1MiB ৰ %2 বিভাজনত ফ্লেগ চেত্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="62"/>
      <source>Set flags on new partition.</source>
      <translation>নতুন বিভাজনত ফ্লেগ চেত্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="74"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; বিভাজনত ফ্লেগ আতৰাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>%1MiB ৰ &lt;strong&gt;%2&lt;/strong&gt; বিভাজনৰ ফ্লেগবোৰ আতৰাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="84"/>
      <source>Clear flags on new partition.</source>
      <translation>নতুন বিভাজনৰ ফ্লেগ আতৰাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="89"/>
      <source>Flag partition &lt;strong&gt;%1&lt;/strong&gt; as &lt;strong&gt;%2&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; বিভাজনত &lt;strong&gt;%2&lt;/strong&gt;ৰ ফ্লেগ লগাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="98"/>
      <source>Flag %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition as &lt;strong&gt;%3&lt;/strong&gt;.</source>
      <translation>%1MiBৰ &lt;strong&gt;%2&lt;/strong&gt; বিভাজনত &lt;strong&gt;%3&lt;/strong&gt; ফ্লেগ লগাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Flag new partition as &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>নতুন বিভাজনত &lt;strong&gt;%1&lt;/strong&gt;ৰ ফ্লেগ লগাওক।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; বিভাজনৰ ফ্লেগ আতৰাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="123"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>%1MiB ৰ &lt;strong&gt;%2&lt;/strong&gt; বিভাজনৰ ফ্লেগবোৰ আতৰ কৰি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="128"/>
      <source>Clearing flags on new partition.</source>
      <translation>নতুন বিভাজনৰ ফ্লেগ আতৰাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="133"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; বিভাজনত &lt;strong&gt;%2&lt;/strong&gt; ফ্লেগ লগাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="142"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition.</source>
      <translation>%1MiBৰ &lt;strong&gt;%2&lt;/strong&gt; বিভাজনত &lt;strong&gt;%3&lt;/strong&gt; ফ্লেগ লগাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition.</source>
      <translation>নতুন বিভাজনত &lt;strong&gt;%1&lt;/strong&gt; ফ্লেগ লগাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="165"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>ইনস্তলাৰটো​ %1 বিভাজনত ফ্লেগ লগোৱাত বিফল হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="49"/>
      <source>Set password for user %1</source>
      <translation>%1 ব্যৱহাৰকাৰীৰ বাবে পাছ্ৱৰ্ড চেত্ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="56"/>
      <source>Setting password for user %1.</source>
      <translation>%1 ব্যৱহাৰকাৰীৰ বাবে পাছ্ৱৰ্ড চেত্ কৰি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <source>Bad destination system path.</source>
      <translation>গন্তব্যস্থানৰ চিছটেমৰ পথ বেয়া।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="91"/>
      <source>rootMountPoint is %1</source>
      <translation>ৰূট মাঊন্ট পইন্ট্ %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="97"/>
      <source>Cannot disable root account.</source>
      <translation>ৰূট একাঊন্ট নিস্ক্ৰিয় কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="98"/>
      <source>passwd terminated with error code %1.</source>
      <translation>%1 ক্ৰুটি কোডৰ সৈতে পাছৱৰ্ড সমাপ্তি হ'ল।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="106"/>
      <source>Cannot set password for user %1.</source>
      <translation>%1 ব্যৱহাৰকাৰীৰ পাছ্ৱৰ্ড চেত্ কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>usermod terminated with error code %1.</source>
      <translation>%1 ক্ৰুটি চিহ্নৰ সৈতে ইউজাৰম'ড সমাপ্ত হ'ল।</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="43"/>
      <source>Set timezone to %1/%2</source>
      <translation>%1/%2 টাইমজ'ন চেত্ কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <source>Cannot access selected timezone path.</source>
      <translation>বাচনি কৰা টাইমজ'ন পথত যাব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Bad path: %1</source>
      <translation>বেয়া পথ: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot set timezone.</source>
      <translation>টাইমজ'ন চেত্ কৰিব নোৱাৰি।</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="81"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <translation>লিংক বনোৱাত বিফল হ'ল, গন্তব্য স্থান: %1; লিংকৰ নাম: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="86"/>
      <source>Cannot set timezone,</source>
      <translation>টাইমজ'ন চেত্ কৰিব নোৱাৰি,</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="87"/>
      <source>Cannot open /etc/timezone for writing</source>
      <translation>/etc/timezone ত লিখিব খুলিব নোৱাৰি</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="46"/>
      <source>Shell Processes Job</source>
      <translation>ছেল প্ৰক্ৰিয়াবোৰৰ কাৰ্য্য</translation>
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
      <translation>চেত্ আপ প্ৰক্ৰিয়া হ'লে কি হ'ব এয়া এটা অৱলোকন।</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/SummaryPage.cpp" line="60"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>ইনস্তল প্ৰক্ৰিয়া হ'লে কি হ'ব এয়া এটা অৱলোকন।</translation>
    </message>
  </context>
  <context>
    <name>SummaryViewStep</name>
    <message>
      <location filename="../src/modules/summary/SummaryViewStep.cpp" line="43"/>
      <source>Summary</source>
      <translation>সাৰাংশ</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="42"/>
      <source>Installation feedback</source>
      <translation>ইনস্তল সম্বন্ধীয় প্ৰতিক্ৰিয়া</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="54"/>
      <source>Sending installation feedback.</source>
      <translation>ইন্স্তল সম্বন্ধীয় প্ৰতিক্ৰিয়া পঠাই আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="71"/>
      <source>Internal error in install-tracking.</source>
      <translation>ইন্স্তল-ক্ৰুটিৰ আভ্যন্তৰীণ ক্ৰুটি।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="72"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP ৰিকুৱেস্টৰ সময় উকলি গ'ল।</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineNeonJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="80"/>
      <source>Machine feedback</source>
      <translation>মেচিন সম্বন্ধীয় প্ৰতিক্ৰীয়া</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="92"/>
      <source>Configuring machine feedback.</source>
      <translation>মেচিন সম্বন্ধীয় প্ৰতিক্ৰীয়া কনফিগাৰ কৰি আছে‌।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="117"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="123"/>
      <source>Error in machine feedback configuration.</source>
      <translation>মেচিনত ফিডবেক কনফিগাৰেচনৰ ক্ৰুটি।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="118"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>মেচিনৰ প্ৰতিক্ৰিয়া ঠাকভাৱে কন্ফিগাৰ কৰিব পৰা নগ'ল, লিপি ক্ৰুটি %1।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>মেচিনৰ প্ৰতিক্ৰিয়া ঠাকভাৱে কন্ফিগাৰ কৰিব পৰা নগ'ল, কেলামাৰেচ ক্ৰুটি %1।</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="24"/>
      <source>Placeholder</source>
      <translation>প্লেচহোল্ডাৰ</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="72"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;By selecting this, you will send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;এইটো বাচনি কৰি, ইনস্তলচেন​ৰ বিষয়ে &lt;span style=" font-weight:600;"&gt;মুঠতে একো তথ্য&lt;/span&gt; আপুনি নপঠায়।&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="271"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;ব্যৱহাৰকাৰীৰ অধিক তথ্য পাবলৈ ইয়াত ক্লিক কৰক&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="44"/>
      <source>Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area.</source>
      <translation>ইনস্তলচেন​ ট্ৰেকিংয়ে %1 কিমান ব্যৱহাৰকাৰী আছে, তেওলোকে কি কি হাৰ্ডৱেৰত %1 ইনস্তল কৰিছে আৰু (তলৰ দুটা বিকল্পৰ লগত), পছন্দৰ এপ্লিকেচনৰ তথ্য নিৰন্তৰভাৱে পোৱাত সহায় কৰে। কি পঠাব জানিবলৈ অনুগ্ৰহ কৰি প্ৰত্যেক ক্ষেত্ৰৰ পিছৰ HELP আইকণত ক্লিক্ কৰক।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="49"/>
      <source>By selecting this you will send information about your installation and hardware. This information will &lt;b&gt;only be sent once&lt;/b&gt; after the installation finishes.</source>
      <translation>এইটো বাচনি কৰি আপুনি ইনস্তলচেন​ আৰু হাৰ্ডৱেৰৰ বিষয়ে তথ্য পঠাব। ইনস্তলচেন​ৰ পিছত &lt;b&gt;এই তথ্য এবাৰ পঠোৱা হ'ব&lt;/b&gt;।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="51"/>
      <source>By selecting this you will &lt;b&gt;periodically&lt;/b&gt; send information about your installation, hardware and applications, to %1.</source>
      <translation>এইটো বাচনি কৰি আপুনি ইনস্তলচেন​, হাৰ্ডৱেৰ আৰু এপ্লিকেচনৰ বিষয়ে &lt;b&gt;সময়ে সময়ে&lt;/b&gt; %1লৈ তথ্য পঠাব।</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="54"/>
      <source>By selecting this you will &lt;b&gt;regularly&lt;/b&gt; send information about your installation, hardware, applications and usage patterns, to %1.</source>
      <translation>এইটো বাচনি কৰি আপুনি ইনস্তলচেন​, হাৰ্ডৱেৰ, এপ্লিকেচন আৰু ব্যৱহাৰ পেটাৰ্ণৰ বিষয়ে &lt;b&gt;নিয়মিতভাৱে&lt;/b&gt; %1লৈ তথ্য পঠাব।</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="64"/>
      <source>Feedback</source>
      <translation>প্ৰতিক্ৰিয়া</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="149"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;যদি এটাতকৈ বেছি ব্যক্তিয়ে এইটো কম্পিউটাৰ ব্যৱহাৰ কৰে, আপুনি চেত্ আপৰ পিছত বহুতো একাউন্ট বনাব পাৰে।&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="155"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;যদি এটাতকৈ বেছি ব্যক্তিয়ে এইটো কম্পিউটাৰ ব্যৱহাৰ কৰে, আপুনি ইনস্তলচেন​ৰ পিছত বহুতো একাউন্ট বনাব পাৰে।&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="395"/>
      <source>Your username is too long.</source>
      <translation>আপোনাৰ ইউজাৰ নাম বহুত দীঘল।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="402"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>আপোনাৰ ব্যৱহাৰকাৰী নাম lowercase বৰ্ণ বা underscoreৰে আৰম্ভ হ'ব লাগিব।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="409"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>কেৱল lowercase বৰ্ণ, সংখ্যা, underscore আৰু hyphenৰ হে মাত্ৰ অনুমতি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="445"/>
      <source>Your hostname is too short.</source>
      <translation>আপোনাৰ হ'স্ট্ নাম বহুত ছুটি।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="450"/>
      <source>Your hostname is too long.</source>
      <translation>আপোনাৰ হ'স্ট্ নাম বহুত দীঘল।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="457"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>কেৱল বৰ্ণ, সংখ্যা, underscore আৰু hyphenৰ হে মাত্ৰ অনুমতি আছে।</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="474"/>
      <source>Your passwords do not match!</source>
      <translation>আপোনাৰ পাছৱৰ্ডকেইটাৰ মিল নাই!</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="76"/>
      <source>Users</source>
      <translation>ব্যৱহাৰকাৰীসকল</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="241"/>
      <source>Key</source>
      <translation>কি</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="245"/>
      <source>Value</source>
      <translation>মান</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="14"/>
      <source>Create Volume Group</source>
      <translation>ভলিউম্ গোট</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="20"/>
      <source>List of Physical Volumes</source>
      <translation>ফিজিকেল ভলিউমবোৰৰ সুচী</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="30"/>
      <source>Volume Group Name:</source>
      <translation>ভলিউম্ গোটৰ নাম:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="43"/>
      <source>Volume Group Type:</source>
      <translation>ভলিউম্ গোটৰ প্ৰকাৰ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="56"/>
      <source>Physical Extent Size:</source>
      <translation>ফিজিকেল ডিস্কৰ আয়তন সীমা:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="66"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="82"/>
      <source>Total Size:</source>
      <translation>মুঠ আয়তন:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="102"/>
      <source>Used Size:</source>
      <translation>ব্যৱহাৰ কৰা আয়তন:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="122"/>
      <source>Total Sectors:</source>
      <translation>মুঠ চেক্টৰবোৰ:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="142"/>
      <source>Quantity of LVs:</source>
      <translation>LVবোৰৰ সংখ্যা:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="14"/>
      <source>Form</source>
      <translation>ৰূপ</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="75"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="94"/>
      <source>Select application and system language</source>
      <translation>এপ্লিকেচন আৰু চিছটেম ভাষা বাচনি কৰক</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="136"/>
      <source>&amp;About</source>
      <translation>সম্পর্কে (&amp;A)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="146"/>
      <source>Open donations website</source>
      <translation>দান কৰা ৱেবচাইট খোলক</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="149"/>
      <source>&amp;Donate</source>
      <translation>দান কৰক (&amp;D)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="159"/>
      <source>Open help and support website</source>
      <translation>সহায়ক ৱেবচাইট খোলক</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="162"/>
      <source>&amp;Support</source>
      <translation>সহায় (&amp;S)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="172"/>
      <source>Open issues and bug-tracking website</source>
      <translation>সমস্যা আৰু ক্ৰুটি অনুসৰণৰ ৱেবচাইট খোলক</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="175"/>
      <source>&amp;Known issues</source>
      <translation>জ্ঞাত সমস্যা (&amp;K)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="185"/>
      <source>Open release notes website</source>
      <translation>মুক্তি টোকাৰ ৱেবচাইট খোলক</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="188"/>
      <source>&amp;Release notes</source>
      <translation>মুক্তি টোকা (&amp;R)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="228"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1ৰ কেলামাৰেচ চেত্ আপ প্ৰগ্ৰামলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="229"/>
      <source>&lt;h1&gt;Welcome to %1 setup.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt; %1 চেত্ আপলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="234"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1ৰ কেলামাৰেচ ইনস্তলাৰলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="235"/>
      <source>&lt;h1&gt;Welcome to the %1 installer.&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 ইনস্তলাৰলৈ আদৰণি জনাইছো।&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="240"/>
      <source>%1 support</source>
      <translation>%1 সহায়</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>About %1 setup</source>
      <translation>%1 চেত্ আপ প্ৰগ্ৰামৰ বিষয়ে</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="247"/>
      <source>About %1 installer</source>
      <translation>%1 ইনস্তলাৰৰ বিষয়ে</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="250"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt;for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;Copyright 2014-2017 Teo Mrnjavac &amp;lt;teo@kde.org&amp;gt;&lt;br/&gt;Copyright 2017-2020 Adriaan de Groot &amp;lt;groot@kde.org&amp;gt;&lt;br/&gt;Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://www.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.&lt;br/&gt;&lt;br/&gt;&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="60"/>
      <source>Welcome</source>
      <translation>আদৰণি</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="64"/>
      <source>Welcome</source>
      <translation>আদৰণি</translation>
    </message>
  </context>
  <context>
    <name>about</name>
    <message>
      <location filename="../src/modules/welcomeq/about.qml" line="56"/>
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
      <location filename="../src/modules/welcomeq/about.qml" line="105"/>
      <source>Back</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="25"/>
      <source>Keyboard Model</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="26"/>
      <source>Pick your preferred keyboard model or use the default one based on the detected hardware</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="41"/>
      <source>Refresh</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="51"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="163"/>
      <source>Layouts</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="79"/>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="139"/>
      <source>Keyboard Layout</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="101"/>
      <source>Models</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="109"/>
      <source>Variants</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="189"/>
      <source>Test your keyboard</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="61"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>release_notes</name>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="54"/>
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
      <location filename="../src/modules/welcomeq/release_notes.qml" line="85"/>
      <source>Back</source>
      <translation type="unfinished"/>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="44"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="71"/>
      <source>About</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="85"/>
      <source>Support</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="96"/>
      <source>Known issues</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="107"/>
      <source>Release notes</source>
      <translation type="unfinished"/>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="119"/>
      <source>Donate</source>
      <translation type="unfinished"/>
    </message>
  </context>
</TS>

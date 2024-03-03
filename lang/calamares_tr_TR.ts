<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS language="tr_TR" version="2.1">
  <context>
    <name>AboutData</name>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="17"/>
      <source>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%2&lt;br/&gt; for %3&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</source>
      <translation>&lt;h1&gt;%1&lt;/h1&gt;&lt;br/&gt;&lt;strong&gt;%3 için&lt;br/&gt;%2&lt;/strong&gt;&lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="20"/>
      <source>Thanks to &lt;a href="https://calamares.io/team/"&gt;the Calamares team&lt;/a&gt; and the &lt;a href="https://app.transifex.com/calamares/calamares/"&gt;Calamares translators team&lt;/a&gt;.</source>
      <translation>Teşekkürler &lt;a href="https://calamares.io/team/"&gt;Calamares takımı&lt;/a&gt; ve &lt;a href="https://app.transifex.com/calamares/calamares/"&gt;Calamares çevirmenleri&lt;/a&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="25"/>
      <source>&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; development is sponsored by &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Liberating Software.</source>
      <translation>&lt;a href="https://calamares.io/"&gt;Calamares&lt;/a&gt; geliştirmesi &lt;br/&gt;&lt;a href="http://www.blue-systems.com/"&gt;Blue Systems&lt;/a&gt; - Özgür Yazılım tarafından fonlanır.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/CalamaresAbout.cpp" line="40"/>
      <source>Copyright %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</source>
      <extracomment>Copyright year-year Name &lt;email-address&gt;</extracomment>
      <translation>Telif hakkı %1-%2 %3 &amp;lt;%4&amp;gt;&lt;br/&gt;</translation>
    </message>
  </context>
  <context>
    <name>AutoMountManagementJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/AutoMountManagementJob.cpp" line="22"/>
      <source>Managing auto-mount settings…</source>
      <comment>@status</comment>
      <translation>Otomatik bağlama ayarları yönetiliyor…</translation>
    </message>
  </context>
  <context>
    <name>BootInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="60"/>
      <source>The &lt;strong&gt;boot environment&lt;/strong&gt; of this system.&lt;br&gt;&lt;br&gt;Older x86 systems only support &lt;strong&gt;BIOS&lt;/strong&gt;.&lt;br&gt;Modern systems usually use &lt;strong&gt;EFI&lt;/strong&gt;, but may also show up as BIOS if started in compatibility mode.</source>
      <translation>Bu sistemin &lt;strong&gt;önyükleme ortamı&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Daha eski x86 sistemler yalnızca&lt;strong&gt;BIOS&lt;/strong&gt; destekler.&lt;br&gt;Çağdaş sistemler genellikle &lt;strong&gt;EFI&lt;/strong&gt; kullanır; ancak uyumluluk kipinde başlatılırlarsa BIOS olarak da görünebilirler.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="70"/>
      <source>This system was started with an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from an EFI environment, this installer must deploy a boot loader application, like &lt;strong&gt;GRUB&lt;/strong&gt; or &lt;strong&gt;systemd-boot&lt;/strong&gt; on an &lt;strong&gt;EFI System Partition&lt;/strong&gt;. This is automatic, unless you choose manual partitioning, in which case you must choose it or create it on your own.</source>
      <translation>Bu sistem, bir &lt;strong&gt;EFI&lt;/strong&gt; önyükleme ortamı ile başlatıldı.&lt;br&gt;&lt;br&gt;Bir EFI ortamından başlatmayı yapılandırmak için bu kurulum programı, bir &lt;strong&gt;EFI Sistem Bölüntüsü&lt;/strong&gt;'nde &lt;strong&gt;GRUB&lt;/strong&gt; veya &lt;strong&gt;systemd-boot&lt;/strong&gt; gibi bir önyükleyici yerleştirmelidir. Bu işlem, elle bölüntülemeyi seçmediğiniz sürece kendiliğinden yapılır. Elle bölüntülemeyi seçerseniz onu kendiniz oluşturmanız gerekecektir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/BootInfoWidget.cpp" line="82"/>
      <source>This system was started with a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment.&lt;br&gt;&lt;br&gt;To configure startup from a BIOS environment, this installer must install a boot loader, like &lt;strong&gt;GRUB&lt;/strong&gt;, either at the beginning of a partition or on the &lt;strong&gt;Master Boot Record&lt;/strong&gt; near the beginning of the partition table (preferred). This is automatic, unless you choose manual partitioning, in which case you must set it up on your own.</source>
      <translation>Bu sistem, bir &lt;strong&gt;BIOS&lt;/strong&gt; önyükleme ortamı ile başlatıldı.&lt;br&gt;&lt;br&gt;Bir BIOS ortamından başlatmayı yapılandırmak için bu kurulum programı, bir bölüntünün başına veya bölüntüleme tablosunun başlangıcındaki &lt;strong&gt;Ana Önyükleme Kaydı&lt;/strong&gt;'na (yeğlenen) &lt;strong&gt;GRUB&lt;/strong&gt; gibi bir önyükleyici kurmalıdır. Bu işlem, elle bölüntülemeyi seçmediğiniz sürece kendiliğinden yapılır. Elle bölüntülemeyi seçerseniz onu kendiniz oluşturmanız gerekecektir.</translation>
    </message>
  </context>
  <context>
    <name>BootLoaderModel</name>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="60"/>
      <source>Master Boot Record of %1</source>
      <comment>@info</comment>
      <translation>%1 Ana Önyükleme Kaydı</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="93"/>
      <source>Boot Partition</source>
      <comment>@info</comment>
      <translation>Önyükleme Bölüntüsü</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="100"/>
      <source>System Partition</source>
      <comment>@info</comment>
      <translation>Sistem Bölüntüsü</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/BootLoaderModel.cpp" line="131"/>
      <source>Do not install a boot loader</source>
      <comment>@label</comment>
      <translation>Bir önyükleyici kurma</translation>
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
      <translation>Boş Sayfa</translation>
    </message>
  </context>
  <context>
    <name>Calamares::DebugWindow</name>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="28"/>
      <source>GlobalStorage</source>
      <translation>Global Depolama</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="38"/>
      <source>JobQueue</source>
      <translation>İş Kuyruğu</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="48"/>
      <source>Modules</source>
      <translation>Modüller</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="61"/>
      <source>Type:</source>
      <translation>Tür:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="68"/>
      <location filename="../src/calamares/DebugWindow.ui" line="82"/>
      <source>none</source>
      <translation>yok</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="75"/>
      <source>Interface:</source>
      <translation>Arayüz:</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="102"/>
      <source>Crashes Calamares, so that Dr. Konqi can look at it.</source>
      <translation>Calamaresi çökerterek Dr. Konqi'nin bakabilmesini sağlar.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="115"/>
      <source>Reloads the stylesheet from the branding directory.</source>
      <translation>Biçem sayfasını marka dizininden yeniden yükler.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="118"/>
      <source>Reload Stylesheet</source>
      <translation>Biçem Sayfasını Yeniden Yükle</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="128"/>
      <source>Displays the tree of widget names in the log (for stylesheet debugging).</source>
      <translation>Günlükteki araç takımı adlarının ağacını görüntüler (biçem sayfası hata ayıklaması için).</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="131"/>
      <source>Widget Tree</source>
      <translation>Araç Takımı Ağacı</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="141"/>
      <source>Uploads the session log to the configured pastebin.</source>
      <translation>Oturum günlüğünü yapılandırılmış pastebin'e yükler.</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.ui" line="144"/>
      <source>Send Session Log</source>
      <translation>Oturum Günlüğünü Gönder</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="164"/>
      <source>Debug Information</source>
      <comment>@title</comment>
      <translation>Hata Ayıklama Bilgileri</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ExecutionViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="77"/>
      <source>%p%</source>
      <comment>Progress percentage indicator: %p is where the number 0..100 is placed</comment>
      <translation>%​%p</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Set Up</source>
      <comment>@label</comment>
      <translation>Ayarla</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/ExecutionViewStep.cpp" line="118"/>
      <source>Install</source>
      <comment>@label</comment>
      <translation>Sistem Kurulumu</translation>
    </message>
  </context>
  <context>
    <name>Calamares::FailJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="29"/>
      <source>Job failed (%1)</source>
      <translation>İş hatası (%1)</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="30"/>
      <source>Programmed job failure was explicitly requested.</source>
      <translation>Programlanan iş arızası açıkça istenmişti.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::JobThread</name>
    <message>
      <location filename="../src/libcalamares/JobQueue.cpp" line="203"/>
      <source>Done</source>
      <translation>Tamamlandı</translation>
    </message>
  </context>
  <context>
    <name>Calamares::NamedJob</name>
    <message>
      <location filename="../src/libcalamares/JobExample.cpp" line="17"/>
      <source>Example job (%1)</source>
      <translation>Örnek iş (%1)</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ProcessJob</name>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="49"/>
      <source>Running command %1 in target system…</source>
      <comment>@status</comment>
      <translation>Hedef sistemde %1 komutu çalıştırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/ProcessJob.cpp" line="53"/>
      <source>Running command %1…</source>
      <comment>@status</comment>
      <translation>%1 komutu çalıştırılıyor…</translation>
    </message>
  </context>
  <context>
    <name>Calamares::Python::Job</name>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="214"/>
      <source>Running %1 operation.</source>
      <translation>%1 işlemi yapılıyor.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="229"/>
      <source>Bad working directory path</source>
      <translation>Hatalı çalışma dizini yolu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="230"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <translation>%2 Python işi için %1 çalışma dizini okunabilir değil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="238"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="314"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="340"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="357"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="365"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="373"/>
      <source>Bad main script file</source>
      <translation>Hatalı ana betik dosyası</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="239"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <translation>%2 Python işi için %1 ana betik dosyası okunabilir değil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="300"/>
      <source>Bad internal script</source>
      <translation>Kötü dahili komut dosyası</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="301"/>
      <source>Internal script for python job %1 raised an exception.</source>
      <translation>%1 python işi için dahili komut dosyası bir istisna oluşturdu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="315"/>
      <source>Main script file %1 for python job %2 could not be loaded because it raised an  exception.</source>
      <translation>%2 python işi için ana komut dosyası %1, bir istisna oluşturduğundan yüklenemedi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="341"/>
      <source>Main script file %1 for python job %2 raised an exception.</source>
      <translation>%2 python işi için %1 ana komut dosyası bir istisna oluşturdu.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="358"/>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="366"/>
      <source>Main script file %1 for python job %2 returned invalid results.</source>
      <translation>%2 python işi için %1 ana komut dosyası geçersiz sonuçlar döndürdü.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/python/PythonJob.cpp" line="374"/>
      <source>Main script file %1 for python job %2 does not contain a run() function.</source>
      <translation>%2 python işi için %1 ana komut dosyası bir run() işlevi içermiyor.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::PythonJob</name>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="233"/>
      <source>Running %1 operation…</source>
      <comment>@status</comment>
      <translation>%1 işlemi çalıştırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="261"/>
      <source>Bad working directory path</source>
      <comment>@error</comment>
      <translation>Hatalı çalışma dizini yolu</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="262"/>
      <source>Working directory %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>%2 Python işi için %1 çalışma dizini okunabilir değil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="270"/>
      <source>Bad main script file</source>
      <comment>@error</comment>
      <translation>Hatalı ana betik dosyası</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="271"/>
      <source>Main script file %1 for python job %2 is not readable.</source>
      <comment>@error</comment>
      <translation>%2 Python işi için %1 ana betik dosyası okunabilir değil.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonJob.cpp" line="343"/>
      <source>Boost.Python error in job "%1"</source>
      <comment>@error</comment>
      <translation>"%1" işinde Boost.Python hatası</translation>
    </message>
  </context>
  <context>
    <name>Calamares::QmlViewStep</name>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="73"/>
      <source>Loading…</source>
      <comment>@status</comment>
      <translation>Yükleniyor…</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="100"/>
      <source>QML step &lt;i&gt;%1&lt;/i&gt;.</source>
      <comment>@label</comment>
      <translation>QML adımı &lt;i&gt;%1&lt;/i&gt;.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/viewpages/QmlViewStep.cpp" line="286"/>
      <source>Loading failed.</source>
      <comment>@info</comment>
      <translation>Yüklenemedi.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::RequirementsChecker</name>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="99"/>
      <source>Requirements checking for module '%1' is complete.</source>
      <comment>@info</comment>
      <translation>'%1' modülü için gereklilikler denetimi tamamlandı.</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="123"/>
      <source>Waiting for %n module(s)…</source>
      <comment>@status</comment>
      <translation>
        <numerusform>%n modül(leri) bekleniyor…</numerusform>
        <numerusform>%n modül bekleniyor…</numerusform>
      </translation>
    </message>
    <message numerus="yes">
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="124"/>
      <source>(%n second(s))</source>
      <comment>@status</comment>
      <translation>
        <numerusform>(%n saniye(ler))</numerusform>
        <numerusform>(%n saniye)</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/libcalamares/modulesystem/RequirementsChecker.cpp" line="129"/>
      <source>System-requirements checking is complete.</source>
      <comment>@info</comment>
      <translation>Sistem gereksinimleri denetimi tamamlandı.</translation>
    </message>
  </context>
  <context>
    <name>Calamares::ViewManager</name>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="165"/>
      <source>The upload was unsuccessful. No web-paste was done.</source>
      <translation>Karşıya yükleme başarısız oldu. Web yapıştırması yapılmadı.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="177"/>
      <source>Install log posted to

%1

Link copied to clipboard</source>
      <translation>Kurulum günlüğü şuraya gönderildi:

%1

Bağlantı panoya kopyalandı </translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/utils/Paste.cpp" line="183"/>
      <source>Install Log Paste URL</source>
      <translation>Günlük Yapıştırma URL'sini Kur</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="90"/>
      <source>&amp;Yes</source>
      <translation>&amp;Evet</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="91"/>
      <source>&amp;No</source>
      <translation>&amp;Hayır</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="92"/>
      <source>&amp;Close</source>
      <translation>&amp;Kapat</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="155"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Kurulum Başarısız Oldu</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="156"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Kurulum Başarısız Oldu</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="159"/>
      <source>Error</source>
      <comment>@title</comment>
      <translation>Hata</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="184"/>
      <source>Calamares Initialization Failed</source>
      <comment>@title</comment>
      <translation>Calamares İlklendirilemedi</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="185"/>
      <source>%1 can not be installed. Calamares was unable to load all of the configured modules. This is a problem with the way Calamares is being used by the distribution.</source>
      <comment>@info</comment>
      <translation>%1 kurulamıyor. Calamares yapılandırılan modüllerin tümünü yükleyemedi. Bu, Calamares'in kullandığınız dağıtıma uyarlanma yolundan kaynaklanan bir sorundur.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="192"/>
      <source>&lt;br/&gt;The following modules could not be loaded:</source>
      <comment>@info</comment>
      <translation>&lt;br/&gt;Aşağıdaki modüller yüklenemedi:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="332"/>
      <source>Continue with Setup?</source>
      <comment>@title</comment>
      <translation>Kurulum sürdürülsün mü?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="333"/>
      <source>Continue with Installation?</source>
      <comment>@title</comment>
      <translation>Kurulum sürdürülsün mü?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="335"/>
      <source>The %1 setup program is about to make changes to your disk in order to set up %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>%1 kurulum programı, %2 ayarlarını yapmak için diskinizde değişiklik yapmak üzere.&lt;br/&gt;&lt;strong&gt;Bu değişiklikleri geri alamayacaksınız.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="339"/>
      <source>The %1 installer is about to make changes to your disk in order to install %2.&lt;br/&gt;&lt;strong&gt;You will not be able to undo these changes.&lt;/strong&gt;</source>
      <comment>%1 is short product name, %2 is short product name with version</comment>
      <translation>%1 kurulum programı, %2 kurulumu için diskinizde değişiklikler yapmak üzere.&lt;br/&gt;&lt;strong&gt;Bu değişiklikleri geri alamayacaksınız.&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="344"/>
      <source>&amp;Set Up Now</source>
      <comment>@button</comment>
      <translation>Şimdi &amp;Kur</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="344"/>
      <source>&amp;Install Now</source>
      <comment>@button</comment>
      <translation>Şimdi &amp;Kur</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="351"/>
      <source>Go &amp;Back</source>
      <comment>@button</comment>
      <translation>Geri &amp;Git</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>&amp;Set Up</source>
      <comment>@button</comment>
      <translation>&amp;Kur</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="398"/>
      <source>&amp;Install</source>
      <comment>@button</comment>
      <translation>&amp;Kur</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="400"/>
      <source>Setup is complete. Close the setup program.</source>
      <comment>@tooltip</comment>
      <translation>Kurulum tamamlandı. Kurulum programını kapatın.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="401"/>
      <source>The installation is complete. Close the installer.</source>
      <comment>@tooltip</comment>
      <translation>Kurulum tamamlandı. Kurulum programını kapatın.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="403"/>
      <source>Cancel the setup process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation>Sistemi değiştirmeden kurulum işlemini iptal edin.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="404"/>
      <source>Cancel the installation process without changing the system.</source>
      <comment>@tooltip</comment>
      <translation>Sistemi değiştirmeden kurulum işlemini iptal edin.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="414"/>
      <source>&amp;Next</source>
      <comment>@button</comment>
      <translation>&amp;Sonraki</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="419"/>
      <source>&amp;Back</source>
      <comment>@button</comment>
      <translation>&amp;Geri</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="425"/>
      <source>&amp;Done</source>
      <comment>@button</comment>
      <translation>&amp;Tamam</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="444"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>İ&amp;ptal</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="516"/>
      <source>Cancel Setup?</source>
      <comment>@title</comment>
      <translation>Kurulum iptal edilsin mi?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="516"/>
      <source>Cancel Installation?</source>
      <comment>@title</comment>
      <translation>Kurulum iptal edilsin mi?</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="517"/>
      <source>Do you really want to cancel the current setup process?
The setup program will quit and all changes will be lost.</source>
      <translation>Geçerli kurulum sürecini iptal etmeyi gerçekten istiyor musunuz?
Kurulum programından çıkılacak ve tüm değişiklikler kaybedilecek.</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/ViewManager.cpp" line="519"/>
      <source>Do you really want to cancel the current install process?
The installer will quit and all changes will be lost.</source>
      <translation>Geçerli kurulum işlemini iptal etmeyi gerçekten istiyor musunuz?
Kurulum programından çıkılacak ve tüm değişiklikler kaybedilecek.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresPython::Helper</name>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="309"/>
      <source>Unknown exception type</source>
      <comment>@error</comment>
      <translation>Bilinmeyen istisna türü</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="327"/>
      <source>Unparseable Python error</source>
      <comment>@error</comment>
      <translation>Ayrıştırılamayan Python hatası</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="371"/>
      <source>Unparseable Python traceback</source>
      <comment>@error</comment>
      <translation>Ayrıştırılamayan Python geri izi</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/PythonHelper.cpp" line="378"/>
      <source>Unfetchable Python error</source>
      <comment>@error</comment>
      <translation>Getirilemeyen Python hatası.</translation>
    </message>
  </context>
  <context>
    <name>CalamaresWindow</name>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="405"/>
      <source>%1 Setup Program</source>
      <translation>%1 Kurulum Programı</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="406"/>
      <source>%1 Installer</source>
      <translation>%1 Kurulum Programı</translation>
    </message>
  </context>
  <context>
    <name>ChangeFilesystemLabelJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="34"/>
      <source>Set filesystem label on %1</source>
      <comment>@title</comment>
      <translation>%1 üzerindeki dosya sistemi etiketini ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="41"/>
      <source>Set filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; bölüntüsüne &lt;strong&gt;%1&lt;/strong&gt; dosya sistemi etiketini ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="50"/>
      <source>Setting filesystem label &lt;strong&gt;%1&lt;/strong&gt; to partition &lt;strong&gt;%2&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; bölüntüsüne &lt;strong&gt;%1&lt;/strong&gt; dosya sistemi etiketi ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="72"/>
      <location filename="../src/modules/partition/jobs/ChangeFilesystemLabelJob.cpp" line="84"/>
      <source>The installer failed to update partition table on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Kurulum programı, '%1' diskindeki bölüntüleme tablosunu güncelleyemedi.</translation>
    </message>
  </context>
  <context>
    <name>CheckerContainer</name>
    <message>
      <location filename="../src/modules/welcome/checker/CheckerContainer.cpp" line="38"/>
      <source>Gathering system information...</source>
      <translation>Sistem bilgisi toplanıyor…</translation>
    </message>
  </context>
  <context>
    <name>ChoicePage</name>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="137"/>
      <source>Select storage de&amp;vice:</source>
      <comment>@label</comment>
      <translation>Depolama ay&amp;gıtı seç:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="138"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1034"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1085"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1138"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Şu anki durum:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="139"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Sonrası:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="896"/>
      <source>Reuse %1 as home partition for %2</source>
      <comment>@label</comment>
      <translation>%1 bölüntüsünü %2 için ana kullanıcı bölüntüsü olarak yeniden kullan</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1035"/>
      <source>&lt;strong&gt;Select a partition to shrink, then drag the bottom bar to resize&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;Küçültmek için bir bölüntü seçip alttaki çubuğu sürükleyerek boyutlandırın&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1059"/>
      <source>%1 will be shrunk to %2MiB and a new %3MiB partition will be created for %4.</source>
      <comment>@info, %1 is partition name, %4 is product name</comment>
      <translation>%1, %2 MB olarak küçültülecek ve %4 için yeni bir %3 MB  bölüntü oluşturulacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1129"/>
      <source>&lt;strong&gt;Select a partition to install on&lt;/strong&gt;</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Üzerine kurulum yapılacak bölüntüyü seçin&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1189"/>
      <source>An EFI system partition cannot be found anywhere on this system. Please go back and use manual partitioning to set up %1.</source>
      <comment>@info, %1 is product name</comment>
      <translation>Bu sistemde bir EFI sistem bölüntüsü bulunamadı. Lütfen geri gidin ve %1 kurulumu için elle bölüntüleme gerçekleştirin.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1197"/>
      <source>The EFI system partition at %1 will be used for starting %2.</source>
      <comment>@info, %1 is partition path, %2 is product name</comment>
      <translation>%1 konumundaki EFI sistem bölüntüsü, %2 yazılımını başlatmak için kullanılacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1205"/>
      <source>EFI system partition:</source>
      <comment>@label</comment>
      <translation>EFI sistem bölüntüsü:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1334"/>
      <source>This storage device does not seem to have an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Bu depolama aygıtında bir işletim sistemi yok gibi görünüyor. Ne yapmak istersiniz?&lt;br/&gt;Depolama aygıtına yapacağınız herhangi bir değişiklik uygulanmadan önce değişikliklerinizi gözden geçirme ve onaylama şansına sahip olacaksınız.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1339"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1376"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1397"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1422"/>
      <source>&lt;strong&gt;Erase disk&lt;/strong&gt;&lt;br/&gt;This will &lt;font color="red"&gt;delete&lt;/font&gt; all data currently present on the selected storage device.</source>
      <translation>&lt;strong&gt;Diski sil&lt;/strong&gt;&lt;br/&gt;Seçili depolama aygıtında şu anda bulunan tüm veri &lt;font color="red"&gt;silinecektir&lt;/font&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1343"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1372"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1393"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1418"/>
      <source>&lt;strong&gt;Install alongside&lt;/strong&gt;&lt;br/&gt;The installer will shrink a partition to make room for %1.</source>
      <translation>&lt;strong&gt;Yanına kur&lt;/strong&gt;&lt;br/&gt;Kurulum programı, %1 için yer açmak üzere bir bölüntüyü küçültecektir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1347"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1380"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1401"/>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1426"/>
      <source>&lt;strong&gt;Replace a partition&lt;/strong&gt;&lt;br/&gt;Replaces a partition with %1.</source>
      <translation>&lt;strong&gt;Bölüntüyü başkasıyla değiştir&lt;/strong&gt;&lt;br/&gt;Bir bölüntüyü %1 ile değiştirir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1366"/>
      <source>This storage device has %1 on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Bu depolama aygıtında %1 var. Ne yapmak istersiniz?&lt;br/&gt;Depolama aygıtına yapacağınız herhangi bir değişiklik uygulanmadan önce değişikliklerinizi gözden geçirme ve onaylama şansına sahip olacaksınız.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1388"/>
      <source>This storage device already has an operating system on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Bu depolama aygıtında halihazırda bir işletim sistemi var. Ne yapmak istersiniz?&lt;br/&gt;Depolama aygıtına yapacağınız herhangi bir değişiklik uygulanmadan önce değişikliklerinizi gözden geçirme ve onaylama şansına sahip olacaksınız.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1413"/>
      <source>This storage device has multiple operating systems on it. What would you like to do?&lt;br/&gt;You will be able to review and confirm your choices before any change is made to the storage device.</source>
      <translation>Bu depolama aygıtı üzerinde birden çok işletim sistemi var. Ne yapmak istersiniz?&lt;br/&gt;Depolama aygıtına yapacağınız herhangi bir değişiklik uygulanmadan önce değişikliklerinizi gözden geçirme ve onaylama şansına sahip olacaksınız.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1485"/>
      <source>This storage device already has an operating system on it, but the partition table &lt;strong&gt;%1&lt;/strong&gt; is different from the needed &lt;strong&gt;%2&lt;/strong&gt;.&lt;br/&gt;</source>
      <translation>Bu depolama aygıtında halihazırda bir işletim sistemi var; ancak &lt;strong&gt;%1&lt;/strong&gt; bölüntüleme tablosu, gereken &lt;strong&gt;%2&lt;/strong&gt; tablosundan farklı.&lt;br/&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1508"/>
      <source>This storage device has one of its partitions &lt;strong&gt;mounted&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>Bu depolama aygıtının bölüntülerinden biri &lt;strong&gt;bağlı&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1513"/>
      <source>This storage device is a part of an &lt;strong&gt;inactive RAID&lt;/strong&gt; device.</source>
      <comment>@info</comment>
      <translation>Bu depolama aygıtı, &lt;strong&gt;etkin olmayan bir RAID&lt;/strong&gt; aygıtının parçasıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1628"/>
      <source>No swap</source>
      <comment>@label</comment>
      <translation>Takas alanı yok</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1637"/>
      <source>Reuse swap</source>
      <comment>@label</comment>
      <translation>Takas alanını yeniden kullan</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1640"/>
      <source>Swap (no Hibernate)</source>
      <comment>@label</comment>
      <translation>Takas Alanı (Hazırda Bekletme Kullanılamaz)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1643"/>
      <source>Swap (with Hibernate)</source>
      <comment>@label</comment>
      <translation>Takas Alanı (Hazırda Beklet ile)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1646"/>
      <source>Swap to file</source>
      <comment>@label</comment>
      <translation>Dosyaya Takas Yaz</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1659"/>
      <source>&lt;strong&gt;Manual partitioning&lt;/strong&gt;&lt;br/&gt;You can create or resize partitions yourself.</source>
      <translation>&lt;strong&gt;Elle bölüntüle&lt;/strong&gt;&lt;br/&gt;Kendiniz bölüntüler oluşturabilir ve boyutlandırabilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ChoicePage.cpp" line="1687"/>
      <source>Bootloader location:</source>
      <comment>@label</comment>
      <translation>Önyükleyici konumu:</translation>
    </message>
  </context>
  <context>
    <name>ClearMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="267"/>
      <source>Successfully unmounted %1.</source>
      <translation>%1 bağlantısı başarıyla kesildi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="274"/>
      <source>Successfully disabled swap %1.</source>
      <translation>%1 takas alanı başarıyla devre dışı bırakıldı.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="300"/>
      <source>Successfully cleared swap %1.</source>
      <translation>%1 takas alanı başarıyla temizlendi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="314"/>
      <source>Successfully closed mapper device %1.</source>
      <translation>%1 eşleyici aygıtı başarıyla kapatıldı.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="327"/>
      <source>Successfully disabled volume group %1.</source>
      <translation>%1 disk bölümü grubu başarıyla devre dışı bırakıldı.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="366"/>
      <source>Clear mounts for partitioning operations on %1</source>
      <comment>@title</comment>
      <translation>%1 üzerinde gerçekleştirilecek bölüntüleme işlemleri için bağlamaları çıkar</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="372"/>
      <source>Clearing mounts for partitioning operations on %1…</source>
      <comment>@status</comment>
      <translation>%1 üzerindeki bölüntüleme işlemleri için bağlamalar çıkarılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearMountsJob.cpp" line="391"/>
      <source>Cleared all mounts for %1</source>
      <translation>%1 için olan tüm bağlamalar çıkarıldı</translation>
    </message>
  </context>
  <context>
    <name>ClearTempMountsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="33"/>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="40"/>
      <source>Clearing all temporary mounts…</source>
      <comment>@status</comment>
      <translation>Tüm geçici bağlamalar çıkarılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ClearTempMountsJob.cpp" line="70"/>
      <source>Cleared all temporary mounts.</source>
      <translation>Tüm geçici bağlamalar çıkarıldı.</translation>
    </message>
  </context>
  <context>
    <name>CommandList</name>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="164"/>
      <source>Could not run command.</source>
      <translation>Komut çalıştırılamadı.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/CommandList.cpp" line="165"/>
      <source>The commands use variables that are not defined. Missing variables are: %1.</source>
      <translation>Komutlar tanımlanmamış değişkenleri kullanıyor. Eksik değişkenler: %1.</translation>
    </message>
  </context>
  <context>
    <name>Config</name>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="142"/>
      <source>Setup Failed</source>
      <comment>@title</comment>
      <translation>Kurulum Başarısız Oldu</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="142"/>
      <source>Installation Failed</source>
      <comment>@title</comment>
      <translation>Kurulum Başarısız Oldu</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="144"/>
      <source>The setup of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>%1 kurulumu başarıyla tamamlanamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="145"/>
      <source>The installation of %1 did not complete successfully.</source>
      <comment>@info</comment>
      <translation>%1 kurulumu başarıyla tamamlanamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="149"/>
      <source>Setup Complete</source>
      <comment>@title</comment>
      <translation>Kurulum Tamanlandı</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="150"/>
      <source>Installation Complete</source>
      <comment>@title</comment>
      <translation>Kurulum Tamamlandı</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="151"/>
      <source>The setup of %1 is complete.</source>
      <comment>@info</comment>
      <translation>%1 kurulumu tamamlandı.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/Config.cpp" line="152"/>
      <source>The installation of %1 is complete.</source>
      <comment>@info</comment>
      <translation>%1 kurulumu tamamlandı.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="505"/>
      <source>Keyboard model has been set to %1&lt;br/&gt;.</source>
      <comment>@label, %1 is keyboard model, as in Apple Magic Keyboard</comment>
      <translation>Klavye modeli %1 olarak ayarlandı&lt;br/&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/Config.cpp" line="512"/>
      <source>Keyboard layout has been set to %1/%2.</source>
      <comment>@label, %1 is layout, %2 is layout variant</comment>
      <translation>Klavye düzeni %1/%2 olarak ayarlandı.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="373"/>
      <source>Set timezone to %1/%2</source>
      <comment>@action</comment>
      <translation>Zaman dilimini %1/%2 olarak ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="410"/>
      <source>The system language will be set to %1.</source>
      <comment>@info</comment>
      <translation>Sistem dili %1 olarak ayarlanacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/Config.cpp" line="416"/>
      <source>The numbers and dates locale will be set to %1.</source>
      <comment>@info</comment>
      <translation>Sayılar ve günler için sistem yereli %1 olarak ayarlanacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="53"/>
      <source>Network Installation. (Disabled: Incorrect configuration)</source>
      <translation>Ağ Kurulumu. (Devre dışı: Yanlış yapılandırma)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="55"/>
      <source>Network Installation. (Disabled: Received invalid groups data)</source>
      <translation>Ağ Kurulumu. (Devre dışı: Geçersiz grup verisi alındı)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="57"/>
      <source>Network Installation. (Disabled: Internal error)</source>
      <translation>Ağ Kurulumu. (Devre dışı: İçsel hata)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="59"/>
      <source>Network Installation. (Disabled: Unable to fetch package lists, check your network connection)</source>
      <translation>Ağ Kurulumu. (Devre dışı: Paket listeleri alınamıyor, ağ bağlantısını denetleyin)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="61"/>
      <source>Network Installation. (Disabled: No package list)</source>
      <translation>Ağ Kurulumu. (Devre dışı: Paket listesi yok)</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/Config.cpp" line="76"/>
      <source>Package selection</source>
      <translation>Paket seçimi</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="110"/>
      <source>Package Selection</source>
      <translation>Paket Seçimi</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="112"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Lütfen listeden bir ürün seçin. Seçili ürün kurulacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="241"/>
      <source>Packages</source>
      <translation>Paketler</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>Install option: &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>Kurulum seçeneği: &lt;strong&gt;%1&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/Config.cpp" line="247"/>
      <source>None</source>
      <translation>Yok</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="35"/>
      <source>Summary</source>
      <comment>@label</comment>
      <translation>Kurulum Özeti</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="39"/>
      <source>This is an overview of what will happen once you start the setup procedure.</source>
      <translation>Bu, kurulum prosedürünü başlattıktan sonra neler olacağının genel bir görünümüdür.</translation>
    </message>
    <message>
      <location filename="../src/modules/summary/Config.cpp" line="44"/>
      <source>This is an overview of what will happen once you start the install procedure.</source>
      <translation>Kurulum süreci başladıktan sonra yapılacak işlere genel bir bakış.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="235"/>
      <source>Your username is too long.</source>
      <translation>Kullanıcı adınız pek uzun.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="241"/>
      <source>Your username must start with a lowercase letter or underscore.</source>
      <translation>Kullanıcı adınız küçük harf veya alt çizgi ile başlamalıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="245"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yalnızca küçük harflere, sayılara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="251"/>
      <source>'%1' is not allowed as username.</source>
      <translation>'%1', kullanıcı adı olarak uygun değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="300"/>
      <source>Your hostname is too short.</source>
      <translation>Makine adınız pek kısa.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="304"/>
      <source>Your hostname is too long.</source>
      <translation>Makine adınız pek uzun.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="310"/>
      <source>'%1' is not allowed as hostname.</source>
      <translation>'%1', makine adı olarak uygun değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="315"/>
      <source>Only letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yalnızca harflere, rakamlara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="598"/>
      <source>Your passwords do not match!</source>
      <translation>Parolalarınız eşleşmiyor!</translation>
    </message>
    <message>
      <location filename="../src/modules/users/Config.cpp" line="612"/>
      <source>OK!</source>
      <translation>TAMAM!</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="57"/>
      <source>This computer does not satisfy the minimum requirements for setting up %1.&lt;br/&gt;Setup cannot continue.</source>
      <translation>Bu bilgisayar, %1 kurulumu için en düşük gereksinimleri karşılamıyor. &lt;br/&gt;Kurulum sürdürülemiyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="60"/>
      <source>This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;Installation cannot continue.</source>
      <translation>Bu bilgisayar, %1 kurulumu için en düşük gereksinimleri karşılamıyor. &lt;br/&gt;Kurulum sürdürülemiyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="66"/>
      <source>This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;Setup can continue, but some features might be disabled.</source>
      <translation>Bu bilgisayar, %1 kurulumu için önerilen gereksinimlerin bazılarını karşılamıyor.&lt;br/&gt;Kurulum sürdürülebilir; ancak bazı özellikler devre dışı bırakılabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="70"/>
      <source>This computer does not satisfy some of the recommended requirements for installing %1.&lt;br/&gt;Installation can continue, but some features might be disabled.</source>
      <translation>Bu bilgisayar, %1 kurulumu için önerilen gereksinimlerin bazılarını karşılamıyor.&lt;br/&gt;
Kurulum sürdürülebilir; ancak bazı özellikler devre dışı bırakılabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="80"/>
      <source>This program will ask you some questions and set up %2 on your computer.</source>
      <translation>Bu program size bazı sorular sorup %2 yazılımını bilgisayarınıza kuracaktır.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="264"/>
      <source>&lt;h1&gt;Welcome to the Calamares setup program for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 için Calamares kurulum programına hoş geldiniz&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="265"/>
      <source>&lt;h1&gt;Welcome to %1 setup&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 kurulum programına hoş geldiniz&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="269"/>
      <source>&lt;h1&gt;Welcome to the Calamares installer for %1&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 için Calamares kurulum programına hoş geldiniz&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/Config.cpp" line="270"/>
      <source>&lt;h1&gt;Welcome to the %1 installer&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;%1 kurulum programına hoş geldiniz&lt;/h1&gt;</translation>
    </message>
  </context>
  <context>
    <name>ContextualProcessJob</name>
    <message>
      <location filename="../src/modules/contextualprocess/ContextualProcessJob.cpp" line="115"/>
      <source>Performing contextual processes' job…</source>
      <comment>@status</comment>
      <translation>Bağlamsal süreç işleri gerçekleştiriliyor…</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="18"/>
      <source>Create a Partition</source>
      <translation>Yeni Bölüntü Oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="42"/>
      <source>Si&amp;ze:</source>
      <translation>Bo&amp;yut:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="52"/>
      <source> MiB</source>
      <translation>MB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="59"/>
      <source>Partition &amp;Type:</source>
      <translation>Bölüntü &amp;türü:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="71"/>
      <source>Primar&amp;y</source>
      <translation>Birinci&amp;l</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="81"/>
      <source>E&amp;xtended</source>
      <translation>&amp;Genişletilmiş</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="123"/>
      <source>Fi&amp;le System:</source>
      <translation>D&amp;osya sistemi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="155"/>
      <source>LVM LV name</source>
      <translation>LVM LV adı</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="165"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Bağlama noktası:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="191"/>
      <source>Flags:</source>
      <translation>Bayraklar:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="224"/>
      <source>Label for the filesystem</source>
      <translation>Dosya sistemi etiketi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.ui" line="234"/>
      <source>FS Label:</source>
      <translation>DS etiketi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="67"/>
      <source>En&amp;crypt</source>
      <comment>@action</comment>
      <translation>Şif&amp;rele</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="195"/>
      <source>Logical</source>
      <comment>@label</comment>
      <translation>Mantıksal</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionDialog.cpp" line="200"/>
      <source>Primary</source>
      <comment>@label</comment>
      <translation>Birincil</translation>
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
      <translation>Bağlama noktası halihazırda kullanımda. Lütfen başka bir tane seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="96"/>
      <source>Mountpoint must start with a &lt;tt&gt;/&lt;/tt&gt;.</source>
      <comment>@info</comment>
      <translation>Bağlantı noktası bir &lt;tt&gt;/&lt;/tt&gt; ile başlamalıdır.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="181"/>
      <source>Create new %1MiB partition on %3 (%2) with entries %4</source>
      <comment>@title</comment>
      <translation>%3 (%2) üzerinde %4 girdileriyle ile yeni bir %1 MiB bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="189"/>
      <source>Create new %1MiB partition on %3 (%2)</source>
      <comment>@title</comment>
      <translation>%3 (%2) üzerinde yeni bir %1 MB bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="196"/>
      <source>Create new %2MiB partition on %4 (%3) with file system %1</source>
      <comment>@title</comment>
      <translation>%4 üzerinde (%3) ile %1 dosya sisteminde %2 MB bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="212"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2) with entries &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%3&lt;/strong&gt; (%2) üzerinde &lt;em&gt;%4&lt;/em&gt; girdisi ile yeni bir &lt;strong&gt;%1 MB&lt;/strong&gt; bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="222"/>
      <source>Create new &lt;strong&gt;%1MiB&lt;/strong&gt; partition on &lt;strong&gt;%3&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%3&lt;/strong&gt; (%2) üzerinde yeni bir &lt;strong&gt;%1 MB&lt;/strong&gt; bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="229"/>
      <source>Create new &lt;strong&gt;%2MiB&lt;/strong&gt; partition on &lt;strong&gt;%4&lt;/strong&gt; (%3) with file system &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%4&lt;/strong&gt; (%3) üzerinde ile &lt;strong&gt;%1&lt;/strong&gt; dosya sistemiyle &lt;strong&gt;%2 MB&lt;/strong&gt;bölüntü oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="254"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="257"/>
      <source>Creating new %1 partition on %2…</source>
      <comment>@status</comment>
      <translation>%2 üzerinde yeni %1 bölüntüsü oluşturuluyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionJob.cpp" line="274"/>
      <source>The installer failed to create partition on disk '%1'.</source>
      <comment>@info</comment>
      <translation>Kurulum programı, '%1' diskinde bölüntü oluşturamadı.</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="24"/>
      <source>Create Partition Table</source>
      <translation>Bölüntüleme Tablosu Oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="43"/>
      <source>Creating a new partition table will delete all existing data on the disk.</source>
      <translation>Yeni bir bölüntüleme tablosu oluşturmak, disk üzerinde var olan tüm veriyi siler.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="69"/>
      <source>What kind of partition table do you want to create?</source>
      <translation>Ne tür bir bölüntüleme tablosu oluşturmak istiyorsunuz?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="76"/>
      <source>Master Boot Record (MBR)</source>
      <translation>Ana Önyükleme Kaydı (MBR)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/CreatePartitionTableDialog.ui" line="86"/>
      <source>GUID Partition Table (GPT)</source>
      <translation>GUID Bölüntü Tablosu (GPT)</translation>
    </message>
  </context>
  <context>
    <name>CreatePartitionTableJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="41"/>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="58"/>
      <source>Creating new %1 partition table on %2…</source>
      <comment>@status</comment>
      <translation>%2 üzerinde yeni %1 bölüntü tablosu oluşturuluyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="49"/>
      <source>Creating new &lt;strong&gt;%1&lt;/strong&gt; partition table on &lt;strong&gt;%2&lt;/strong&gt; (%3)…</source>
      <comment>@status</comment>
      <translation>Yeni bir &lt;strong&gt;%1&lt;/strong&gt; bölüntü tablosu oluşturuluyor: &lt;strong&gt;%2&lt;/strong&gt; (%3)...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreatePartitionTableJob.cpp" line="86"/>
      <source>The installer failed to create a partition table on %1.</source>
      <translation>Kurulum programı, %1 üzerinde yeni bir bölüntü tablosu oluşturamadı.</translation>
    </message>
  </context>
  <context>
    <name>CreateUserJob</name>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="33"/>
      <source>Create user %1</source>
      <translation>%1 kullanıcısını oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="39"/>
      <source>Create user &lt;strong&gt;%1&lt;/strong&gt;</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; kullanıcı oluştur.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="45"/>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="137"/>
      <source>Creating user %1…</source>
      <comment>@status</comment>
      <translation>%1 kullanıcısı oluşturuluyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="120"/>
      <source>Preserving home directory…</source>
      <comment>@status</comment>
      <translation>Ana dizin korunuyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="145"/>
      <source>Configuring user %1</source>
      <comment>@status</comment>
      <translation>%1 kullanıcısı yapılandırılıyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CreateUserJob.cpp" line="153"/>
      <source>Setting file permissions…</source>
      <comment>@status</comment>
      <translation>Dosya izinleri ayarlanıyor...</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/CreateVolumeGroupDialog.cpp" line="28"/>
      <source>Create Volume Group</source>
      <comment>@title</comment>
      <translation>Disk Bölümü Grubu Oluştur</translation>
    </message>
  </context>
  <context>
    <name>CreateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="32"/>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="44"/>
      <source>Creating new volume group named %1…</source>
      <comment>@status</comment>
      <translation>%1 adlı yeni disk bölümü grubu oluşturuluyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="38"/>
      <source>Creating new volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; adlı yeni disk bölümü grubu oluşturuluyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/CreateVolumeGroupJob.cpp" line="51"/>
      <source>The installer failed to create a volume group named '%1'.</source>
      <translation>Kurulum programı, '%1' adında bir disk bölümü grubu oluşturamadı.</translation>
    </message>
  </context>
  <context>
    <name>DeactivateVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="38"/>
      <source>Deactivating volume group named %1…</source>
      <comment>@status</comment>
      <translation>%1 adlı disk bölümü grubu devre dışı bırakılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="32"/>
      <source>Deactivating volume group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; adlı disk bölümü grubu devre dışı bırakılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeactivateVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to deactivate a volume group named %1.</source>
      <translation>Kurulum programı, %1 adlı bir disk bölümü grubunu devre dışı bırakamadı.</translation>
    </message>
  </context>
  <context>
    <name>DeletePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="73"/>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="85"/>
      <source>Deleting partition %1…</source>
      <comment>@status</comment>
      <translation>%1 bölüntüsü siliniyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="79"/>
      <source>Deleting partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; bölüntüsü siliniyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/DeletePartitionJob.cpp" line="99"/>
      <source>The installer failed to delete partition %1.</source>
      <translation>Kurulum programı, %1 bölüntüsünü silemedi.</translation>
    </message>
  </context>
  <context>
    <name>DeviceInfoWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="78"/>
      <source>&lt;br&gt;&lt;br&gt;This partition table type is only advisable on older systems which start from a &lt;strong&gt;BIOS&lt;/strong&gt; boot environment. GPT is recommended in most other cases.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Warning:&lt;/strong&gt; the MBR partition table is an obsolete MS-DOS era standard.&lt;br&gt;Only 4 &lt;em&gt;primary&lt;/em&gt; partitions may be created, and of those 4, one can be an &lt;em&gt;extended&lt;/em&gt; partition, which may in turn contain many &lt;em&gt;logical&lt;/em&gt; partitions.</source>
      <translation>&lt;br&gt;&lt;br&gt;Bu bölüntüleme tablosu, bir &lt;strong&gt;BIOS&lt;/strong&gt; önyükleme ortamından başlayan eski sistemler için tavsiye edilir. Çoğu diğer durum için GPT önerilir.&lt;br&gt;&lt;br&gt;&lt;strong&gt;Uyarı:&lt;/strong&gt; MBR bölüntü tablosu, artık eskimiş bir MS-DOS dönemi standardıdır. &lt;br&gt;Yalnızca 4&lt;em&gt;birincil&lt;/em&gt; bölüntü oluşturulabilir ve dört birincil bölüntüden birinin altında, pek çok &lt;em&gt;mantıksal&lt;/em&gt; bölüntü içeren bir &lt;em&gt;genişletilmiş&lt;/em&gt; bölüntü olabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="89"/>
      <source>&lt;br&gt;&lt;br&gt;This is the recommended partition table type for modern systems which start from an &lt;strong&gt;EFI&lt;/strong&gt; boot environment.</source>
      <translation>&lt;br&gt;&lt;br&gt;Bu, bir &lt;strong&gt;EFI&lt;/strong&gt; önyükleme ortamından başlayan çağdaş sistemler için önerilen bölüntü tablosu türüdür.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="95"/>
      <source>This is a &lt;strong&gt;loop&lt;/strong&gt; device.&lt;br&gt;&lt;br&gt;It is a pseudo-device with no partition table that makes a file accessible as a block device. This kind of setup usually only contains a single filesystem.</source>
      <translation>Bu bir &lt;strong&gt;döngü&lt;/strong&gt; aygıtıdır.&lt;br&gt;&lt;br&gt;Bir dosyayı blok aygıtı olarak erişilebilir hale getiren, bölüntü tablosu olmayan yalancı bir aygıttır. Bu tür kurulumlar genellikle yalnızca tek bir dosya sistemi içerir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="104"/>
      <source>This installer &lt;strong&gt;cannot detect a partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The device either has no partition table, or the partition table is corrupted or of an unknown type.&lt;br&gt;This installer can create a new partition table for you, either automatically, or through the manual partitioning page.</source>
      <translation>Bu kurulum programı, seçili depolama aygıtındaki bir bölüntü tablosunu algılayamaz&lt;/strong&gt;.&lt;br&gt;&lt;br&gt;Aygıtın ya bölüntü tablosu yoktur ya da bölüm tablosu bozuktur veya bilinmeyen bir türdedir.&lt;br&gt;Bu kurulum programı, kendiliğinden veya elle bölüntüleme sayfası aracılığıyla sizin için yeni bir bölüntü tablosu oluşturabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="139"/>
      <source>This device has a &lt;strong&gt;%1&lt;/strong&gt; partition table.</source>
      <translation>Bu aygıtta bir &lt;strong&gt;%1&lt;/strong&gt; bölüntü tablosu var.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/DeviceInfoWidget.cpp" line="147"/>
      <source>The type of &lt;strong&gt;partition table&lt;/strong&gt; on the selected storage device.&lt;br&gt;&lt;br&gt;The only way to change the partition table type is to erase and recreate the partition table from scratch, which destroys all data on the storage device.&lt;br&gt;This installer will keep the current partition table unless you explicitly choose otherwise.&lt;br&gt;If unsure, on modern systems GPT is preferred.</source>
      <translation>Seçili depolama aygıtındaki &lt;strong&gt;bölüntü tablosu&lt;/strong&gt; türü.&lt;br&gt;&lt;br&gt;Bölüntü tablosu türünü değiştirmenin tek yolu, bölüntü tablosunu silip yeniden oluşturmaktır. Bu, depolama aygıtındaki tüm veriyi yok eder.&lt;br&gt;Kurulum programı, aksini seçmezseniz geçerli bölüntü tablosunu tutar.&lt;br&gt;Emin değilseniz çağdaş sistemlerde GPT'yi seçebilirsiniz.</translation>
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
      <translation>Dracut için LUKS yapılandırması %1'e yazılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="121"/>
      <source>Skipping writing LUKS configuration for Dracut: "/" partition is not encrypted</source>
      <comment>@info</comment>
      <translation>Dracut için LUKS yapılandırma yazımı atlanıyor: "/" bölüntüsü şifreli değil</translation>
    </message>
    <message>
      <location filename="../src/modules/dracutlukscfg/DracutLuksCfgJob.cpp" line="138"/>
      <source>Failed to open %1</source>
      <comment>@error</comment>
      <translation>%1 açılamadı</translation>
    </message>
  </context>
  <context>
    <name>DummyCppJob</name>
    <message>
      <location filename="../src/modules/dummycpp/DummyCppJob.cpp" line="35"/>
      <source>Performing dummy C++ job…</source>
      <comment>@status</comment>
      <translation>Yalandan C++ işi gerçekleştiriliyor…</translation>
    </message>
  </context>
  <context>
    <name>EditExistingPartitionDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="24"/>
      <source>Edit Existing Partition</source>
      <translation>Var Olan Bölüntüyü Düzenle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="54"/>
      <source>Con&amp;tent:</source>
      <translation>İçe&amp;rik:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="64"/>
      <source>&amp;Keep</source>
      <translation>&amp;Tut</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="74"/>
      <source>Format</source>
      <translation>Biçimlendir</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="93"/>
      <source>Warning: Formatting the partition will erase all existing data.</source>
      <translation>Uyarı: Bölüntüyü biçimlendirmek, var olan tüm veriyi siler.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="103"/>
      <source>&amp;Mount Point:</source>
      <translation>&amp;Bağlama noktası:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="129"/>
      <source>Si&amp;ze:</source>
      <translation>Bo&amp;yut:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="139"/>
      <source> MiB</source>
      <translation>MB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="146"/>
      <source>Fi&amp;le System:</source>
      <translation>D&amp;osya sistemi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="159"/>
      <source>Flags:</source>
      <translation>Bayraklar:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="179"/>
      <source>Label for the filesystem</source>
      <translation>Dosya sistemi etiketi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.ui" line="189"/>
      <source>FS Label:</source>
      <translation>DS etiketi:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="259"/>
      <source>Passphrase for existing partition</source>
      <translation>Var olan bölüntü için parola</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EditExistingPartitionDialog.cpp" line="260"/>
      <source>Partition %1 could not be decrypted with the given passphrase.&lt;br/&gt;&lt;br/&gt;Edit the partition again and give the correct passphrase or delete and create a new encrypted partition.</source>
      <translation>%1 bölüntüsünün şifresi verilen parola ile çözülemedi. &lt;br/&gt;&lt;br/&gt;Bölüntüyü yeniden düzenleyip ve doğru parolayı girin veya silip yeni bir şifreli bölüntü oluşturun.</translation>
    </message>
  </context>
  <context>
    <name>EncryptWidget</name>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="36"/>
      <source>En&amp;crypt system</source>
      <translation>Sistemi şif&amp;rele</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="43"/>
      <source>Your system does not seem to support encryption well enough to encrypt the entire system. You may enable encryption, but performance may suffer.</source>
      <translation>Sisteminiz, tüm sistemi şifrelemek için yeterince şifrelemeyi desteklemiyor gibi görünüyor. Şifrelemeyi etkinleştirebilirsiniz; ancak başarım düşebilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="59"/>
      <source>Passphrase</source>
      <translation>Parola</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.ui" line="69"/>
      <source>Confirm passphrase</source>
      <translation>Parolayı doğrula</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="153"/>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="168"/>
      <source>Please enter the same passphrase in both boxes.</source>
      <comment>@tooltip</comment>
      <translation>Her iki kutuya da aynı parolayı girin.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/EncryptWidget.cpp" line="158"/>
      <source>Password must be a minimum of %1 characters.</source>
      <comment>@tooltip</comment>
      <translation>Parola en az %1 karakter olmalıdır.</translation>
    </message>
  </context>
  <context>
    <name>ErrorDialog</name>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="40"/>
      <source>Details:</source>
      <translation>Ayrıntılar:</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/ErrorDialog.ui" line="56"/>
      <source>Would you like to paste the install log to the web?</source>
      <translation>Kurulum günlüğünü web'e yapıştırmak ister misiniz?</translation>
    </message>
  </context>
  <context>
    <name>FillGlobalStorageJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="179"/>
      <source>Set partition information</source>
      <comment>@title</comment>
      <translation>Bölüntü bilgisini ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="208"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition with features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>&lt;em&gt;%3&lt;/em&gt; özelliklerine sahip &lt;strong&gt;yeni&lt;/strong&gt; %2 sistem bölüntüsüne %1 yazılımını kur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="217"/>
      <source>Install %1 on &lt;strong&gt;new&lt;/strong&gt; %2 system partition</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;Yeni&lt;/strong&gt; %2 sistem bölüntüsüne %1 yazılımını kur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="226"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt; and features &lt;em&gt;%3&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>&lt;em&gt;%3&lt;/em&gt; özelliklerine sahip &lt;strong&gt;%1&lt;/strong&gt; bağlama noktasındaki &lt;strong&gt;yeni&lt;/strong&gt; %2 bölüntüsünü ayarla </translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="235"/>
      <source>Set up &lt;strong&gt;new&lt;/strong&gt; %2 partition with mount point &lt;strong&gt;%1&lt;/strong&gt;%3</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; %3 bağlama noktasındaki &lt;strong&gt;yeni&lt;/strong&gt; %2 bölüntüsünü ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="250"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt; with features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>&lt;em&gt;%4&lt;/em&gt; özellikleriyle &lt;strong&gt;%1&lt;/strong&gt; sistem bölümüne %3 üzerine %2 kur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="260"/>
      <source>Install %2 on %3 system partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; sistem bölüntüsüne %3 üzerine %2 kur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="270"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt; and features &lt;em&gt;%4&lt;/em&gt;</source>
      <comment>@info</comment>
      <translation>&lt;em&gt;%4%&lt;/em&gt; özellikleriyle &lt;strong&gt;%2&lt;/strong&gt; bağlama noktasındaki %3 bölüntüsü &lt;strong&gt;%1&lt;/strong&gt; ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="280"/>
      <source>Set up %3 partition &lt;strong&gt;%1&lt;/strong&gt; with mount point &lt;strong&gt;%2&lt;/strong&gt;%4…</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; %4 bağlama noktasıyla %3 bölüntüsü &lt;strong&gt;%1&lt;/strong&gt; ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="296"/>
      <source>Install boot loader on &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; üzerine sistem önyükleyicisini kur.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FillGlobalStorageJob.cpp" line="305"/>
      <source>Setting up mount points…</source>
      <comment>@status</comment>
      <translation>Bağlama noktaları ayarlanıyor...</translation>
    </message>
  </context>
  <context>
    <name>FinishedPage</name>
    <message>
      <location filename="../src/modules/finished/FinishedPage.ui" line="102"/>
      <source>&amp;Restart now</source>
      <translation>&amp;Şimdi yeniden başlat</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="75"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been set up on your computer.&lt;br/&gt;You may now start using your new system.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Kurulum tamamlandı.&lt;/h1&gt;&lt;br/&gt;%1 bilgisayarınıza kuruldu.&lt;br/&gt;Artık yeni sisteminizi kullanmaya başlayabilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="79"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the setup program.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Bu kutu işaretlendiğinde, &lt;span style="font-style:italic;"&gt;Tamam&lt;/span&gt;'a tıkladığınızda veya kurulum programını kapattığınızda sistem anında yeniden başlatılacaktır.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="87"/>
      <source>&lt;h1&gt;All done.&lt;/h1&gt;&lt;br/&gt;%1 has been installed on your computer.&lt;br/&gt;You may now restart into your new system, or continue using the %2 Live environment.</source>
      <comment>@info</comment>
      <translation>&lt;h1&gt;Her şey tamam.&lt;/h1&gt;&lt;br/&gt;%1 bilgisayarınıza kuruldu.&lt;br/&gt;Yeni kurduğunuz sistemi kullanmak için yeniden başlatabilir veya %2 çalışan sistemi ile sürdürebilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="92"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this box is checked, your system will restart immediately when you click on &lt;span style="font-style:italic;"&gt;Done&lt;/span&gt; or close the installer.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <comment>@tooltip</comment>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Bu kutu işaretlendiğinde, &lt;span style="font-style:italic;"&gt;Tamam&lt;/span&gt;'a tıkladığınızda veya kurulum programını kapattığınızda sistem anında yeniden başlatılacaktır.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="105"/>
      <source>&lt;h1&gt;Setup Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been set up on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>Kurulum Başarısız Oldu&lt;/h1&gt;&lt;br/&gt;%1 bilgisayarınıza kurulamadı.&lt;br/&gt;Hata iletisi: %2.</translation>
    </message>
    <message>
      <location filename="../src/modules/finished/FinishedPage.cpp" line="113"/>
      <source>&lt;h1&gt;Installation Failed&lt;/h1&gt;&lt;br/&gt;%1 has not been installed on your computer.&lt;br/&gt;The error message was: %2.</source>
      <comment>@info, %1 is product name with version</comment>
      <translation>&lt;h1&gt;Kurulum Başarısız Oldu&lt;/h1&gt;&lt;br/&gt;%1 bilgisayarınıza kurulamadı.&lt;br/&gt;Hata iletisi: %2.</translation>
    </message>
  </context>
  <context>
    <name>FinishedQmlViewStep</name>
    <message>
      <location filename="../src/modules/finishedq/FinishedQmlViewStep.cpp" line="35"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Kurulumu Tamamla</translation>
    </message>
  </context>
  <context>
    <name>FinishedViewStep</name>
    <message>
      <location filename="../src/modules/finished/FinishedViewStep.cpp" line="46"/>
      <source>Finish</source>
      <comment>@label</comment>
      <translation>Kurulumu Tamamla</translation>
    </message>
  </context>
  <context>
    <name>FormatPartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="39"/>
      <source>Format partition %1 (file system: %2, size: %3 MiB) on %4</source>
      <comment>@title</comment>
      <translation>%4 üzerindeki %1 bölüntüsünü biçimlendir (dosya sistemi: %2, boyut: %3 MB)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="49"/>
      <source>Format &lt;strong&gt;%3MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; with file system &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%3&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; bölüntüsünü &lt;strong&gt;%2&lt;/strong&gt; dosya sistemiyle biçimlendir</translation>
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
      <translation>%1 bölüntüsü, %2 dosya sistemi ile biçimlendiriliyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/FormatPartitionJob.cpp" line="73"/>
      <source>The installer failed to format partition %1 on disk '%2'.</source>
      <translation>Kurulum programı, '%2' diskindeki %1 bölüntüsünü biçimlendiremedi.</translation>
    </message>
  </context>
  <context>
    <name>GeneralRequirements</name>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="160"/>
      <source>Please ensure the system has at least %1 GiB available drive space.</source>
      <translation>Lütfen sistemde en az %1 GB kullanılabilir sürücü alanı bulunduğundan emin olun.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="162"/>
      <source>Available drive space is all of the hard disks and SSDs connected to the system.</source>
      <translation>Kullanılabilir sürücü alanı, sisteme bağlı tüm sabit diskler ve SSD'lerdir.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="165"/>
      <source>There is not enough drive space. At least %1 GiB is required.</source>
      <translation>Yeterli disk sürücüsü alanı yok. En az %1 GB disk alanı gereklidir.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="173"/>
      <source>has at least %1 GiB working memory</source>
      <translation>en az %1 GB bellek var</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="175"/>
      <source>The system does not have enough working memory. At least %1 GiB is required.</source>
      <translation>Sistemde yeterli çalışma belleği yok. En az %1 GiB gereklidir.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="184"/>
      <source>is plugged in to a power source</source>
      <translation>bir güç kaynağına takılı</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="185"/>
      <source>The system is not plugged in to a power source.</source>
      <translation>Sistem bir güç kaynağına bağlı değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="192"/>
      <source>is connected to the Internet</source>
      <translation>internete bağlı</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="193"/>
      <source>The system is not connected to the Internet.</source>
      <translation>Sistem internete bağlı değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="200"/>
      <source>is running the installer as an administrator (root)</source>
      <translation>kurulum programı yönetici (kök) olarak çalışıyor</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="204"/>
      <source>The setup program is not running with administrator rights.</source>
      <translation>Kurulum programı yönetici haklarıyla çalışmıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="205"/>
      <source>The installer is not running with administrator rights.</source>
      <translation>Kurulum programı, yönetici haklarıyla çalışmıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="213"/>
      <source>has a screen large enough to show the whole installer</source>
      <translation>tüm kurulum programını gösterecek kadar büyük bir ekran var</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="217"/>
      <source>The screen is too small to display the setup program.</source>
      <translation>Kurulum programını görüntülemek için ekran çok küçük.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="218"/>
      <source>The screen is too small to display the installer.</source>
      <translation>Ekran, kurulum programını görüntülemek için çok küçük.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="227"/>
      <source>is always false</source>
      <translation>her zaman yanlış</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="228"/>
      <source>The computer says no.</source>
      <translation>Bilgisayar hayır diyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="236"/>
      <source>is always false (slowly)</source>
      <translation>her zaman yanlış (yavaşça)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="237"/>
      <source>The computer says no (slowly).</source>
      <translation>Bilgisayar (yavaşça) hayır diyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="244"/>
      <source>is always true</source>
      <translation>her zaman doğru</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="245"/>
      <source>The computer says yes.</source>
      <translation>Bilgisayar evet diyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="253"/>
      <source>is always true (slowly)</source>
      <translation>her zaman doğru (yavaşça)</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="254"/>
      <source>The computer says yes (slowly).</source>
      <translation>Bilgisayar evet diyor (yavaşça).</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="262"/>
      <source>is checked three times.</source>
      <translation>üç kez denetlendi.</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/checker/GeneralRequirements.cpp" line="265"/>
      <source>The snark has not been checked three times.</source>
      <comment>The (some mythological beast) has not been checked three times.</comment>
      <translation>Snark üç kez denetlenmedi.</translation>
    </message>
  </context>
  <context>
    <name>HostInfoJob</name>
    <message>
      <location filename="../src/modules/hostinfo/HostInfoJob.cpp" line="39"/>
      <source>Collecting information about your machine…</source>
      <comment>@status</comment>
      <translation>Makineniz hakkında bilgi toplanıyor…</translation>
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
      <translation>OEM Toplu Tanımlayıcısı</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="40"/>
      <source>Could not create directories &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; dizinleri oluşturulamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="53"/>
      <source>Could not open file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; dosyası açılamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/IDJob.cpp" line="60"/>
      <source>Could not write to file &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>&lt;code&gt;%1&lt;/code&gt; dosyasına yazılamadı.</translation>
    </message>
  </context>
  <context>
    <name>InitcpioJob</name>
    <message>
      <location filename="../src/modules/initcpio/InitcpioJob.cpp" line="31"/>
      <source>Creating initramfs with mkinitcpio…</source>
      <comment>@status</comment>
      <translation>Mkinitcpio ile initramf's oluşturuluyor…</translation>
    </message>
  </context>
  <context>
    <name>InitramfsJob</name>
    <message>
      <location filename="../src/modules/initramfs/InitramfsJob.cpp" line="27"/>
      <source>Creating initramfs…</source>
      <comment>@status</comment>
      <translation>Initramfs oluşturuluyor...</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalPage</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="49"/>
      <source>Konsole not installed.</source>
      <comment>@error</comment>
      <translation>Konsole kurulu değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="50"/>
      <source>Please install KDE Konsole and try again!</source>
      <comment>@info</comment>
      <translation>KDE Konsole uygulamasını kurun ve yeniden deneyin!</translation>
    </message>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalPage.cpp" line="122"/>
      <source>Executing script: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</source>
      <comment>@info</comment>
      <translation>Betik yürütülüyor: &amp;nbsp;&lt;code&gt;%1&lt;/code&gt;</translation>
    </message>
  </context>
  <context>
    <name>InteractiveTerminalViewStep</name>
    <message>
      <location filename="../src/modules/interactiveterminal/InteractiveTerminalViewStep.cpp" line="40"/>
      <source>Script</source>
      <comment>@label</comment>
      <translation>Betik</translation>
    </message>
  </context>
  <context>
    <name>KeyboardQmlViewStep</name>
    <message>
      <location filename="../src/modules/keyboardq/KeyboardQmlViewStep.cpp" line="32"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klavye Düzeni</translation>
    </message>
  </context>
  <context>
    <name>KeyboardViewStep</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardViewStep.cpp" line="41"/>
      <source>Keyboard</source>
      <comment>@label</comment>
      <translation>Klavye Düzeni</translation>
    </message>
  </context>
  <context>
    <name>LCLocaleDialog</name>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="23"/>
      <source>System Locale Setting</source>
      <comment>@title</comment>
      <translation>Sistem Yerel Ayarı</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="30"/>
      <source>The system locale setting affects the language and character set for some command line user interface elements.&lt;br/&gt;The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>Sistem yerel ayarları, bazı komut satırı kullanıcı arayüzü ögeleri için olan dili ve karakter kümelerini etkiler.&lt;br/&gt;Geçerli ayar &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="54"/>
      <source>&amp;Cancel</source>
      <comment>@button</comment>
      <translation>İ&amp;ptal</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LCLocaleDialog.cpp" line="55"/>
      <source>&amp;OK</source>
      <comment>@button</comment>
      <translation>&amp;Tamam</translation>
    </message>
  </context>
  <context>
    <name>LOSHJob</name>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="35"/>
      <source>Configuring encrypted swap.</source>
      <translation>Şifreli takas alanı yapılandırılıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="87"/>
      <source>No target system available.</source>
      <translation>Kullanılabilir hedef sistem yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="95"/>
      <source>No rootMountPoint is set.</source>
      <translation>rootMountPoint ayarlanmadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksopenswaphookcfg/LOSHJob.cpp" line="100"/>
      <source>No configFilePath is set.</source>
      <translation>configFilePath ayarlanmadı.</translation>
    </message>
  </context>
  <context>
    <name>LicensePage</name>
    <message>
      <location filename="../src/modules/license/LicensePage.ui" line="26"/>
      <source>&lt;h1&gt;License Agreement&lt;/h1&gt;</source>
      <translation>&lt;h1&gt;Lisans Antlaşması&lt;/h1&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="142"/>
      <source>I accept the terms and conditions above.</source>
      <comment>@info</comment>
      <translation>Yukarıdaki şartları ve koşulları kabul ediyorum.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="144"/>
      <source>Please review the End User License Agreements (EULAs).</source>
      <comment>@info</comment>
      <translation>Lütfen Son Kullanıcı Lisans Sözleşmelerini (EULA) inceleyin.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="149"/>
      <source>This setup procedure will install proprietary software that is subject to licensing terms.</source>
      <comment>@info</comment>
      <translation>Bu kurulum prosedürü, lisanslama koşullarına tabi olan tescilli yazılımı kuracaktır.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="152"/>
      <source>If you do not agree with the terms, the setup procedure cannot continue.</source>
      <comment>@info</comment>
      <translation>Koşulları kabul etmiyorsanız kurulum prosedürü sürdürülemez.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="157"/>
      <source>This setup procedure can install proprietary software that is subject to licensing terms in order to provide additional features and enhance the user experience.</source>
      <comment>@info</comment>
      <translation>Bu kurulum prosedürü, ek özellikler sağlamak ve kullanıcı deneyimini geliştirmek için lisans koşullarına tabi olan özel yazılımlar kurabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicensePage.cpp" line="162"/>
      <source>If you do not agree with the terms, proprietary software will not be installed, and open source alternatives will be used instead.</source>
      <comment>@info</comment>
      <translation>Koşulları kabul etmezseniz lisans koşullarına tabi yazılım kurulmaz ve bunun yerine açık kaynak alternatifleri kullanılır.</translation>
    </message>
  </context>
  <context>
    <name>LicenseViewStep</name>
    <message>
      <location filename="../src/modules/license/LicenseViewStep.cpp" line="45"/>
      <source>License</source>
      <comment>@label</comment>
      <translation>Lisans</translation>
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
      <translation>&lt;strong&gt;%1 sürücüsü&lt;/strong&gt;&lt;br/&gt;, %2 tarafından</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="116"/>
      <source>&lt;strong&gt;%1 graphics driver&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <extracomment>%1 is usually a vendor name, example: Nvidia graphics driver</extracomment>
      <translation>&lt;strong&gt;%1 grafik sürücüsü&lt;/strong&gt;,&lt;br/&gt;&lt;font color="Grey"&gt;%2 tarafından&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="122"/>
      <source>&lt;strong&gt;%1 browser plugin&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1 tarayıcı eklentisi&lt;/strong&gt;,&lt;br/&gt;&lt;font color="Grey"&gt;%2&lt;/font&gt; tarafından</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="128"/>
      <source>&lt;strong&gt;%1 codec&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1 kodlayıcısı&lt;/strong&gt;,&lt;br/&gt;&lt;font color="Grey"&gt;%2 tarafından&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="134"/>
      <source>&lt;strong&gt;%1 package&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1 paketi&lt;/strong&gt;,&lt;br/&gt;&lt;font color="Grey"&gt;%2 tarafından&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="140"/>
      <source>&lt;strong&gt;%1&lt;/strong&gt;&lt;br/&gt;&lt;font color="Grey"&gt;by %2&lt;/font&gt;</source>
      <comment>@label, %1 is product name, %2 is product vendor</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt;,&lt;br/&gt;&lt;font color="Grey"&gt;%2 tarafından&lt;/font&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="163"/>
      <source>File: %1</source>
      <comment>@label</comment>
      <translation>Dosya: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Hide the license text</source>
      <comment>@tooltip</comment>
      <translation>Lisans metnini gizle</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="186"/>
      <source>Show the license text</source>
      <comment>@tooltip</comment>
      <translation>Lisans metnini göster</translation>
    </message>
    <message>
      <location filename="../src/modules/license/LicenseWidget.cpp" line="190"/>
      <source>Open the license agreement in browser</source>
      <comment>@tooltip</comment>
      <translation>Lisans sözleşmesini tarayıcıda açın</translation>
    </message>
  </context>
  <context>
    <name>LocalePage</name>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="130"/>
      <source>Region:</source>
      <comment>@label</comment>
      <translation>Kıta:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="131"/>
      <source>Zone:</source>
      <comment>@label</comment>
      <translation>Bölge:</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/LocalePage.cpp" line="132"/>
      <location filename="../src/modules/locale/LocalePage.cpp" line="133"/>
      <source>&amp;Change…</source>
      <comment>@button</comment>
      <translation>&amp;Değiştir…</translation>
    </message>
  </context>
  <context>
    <name>LocaleQmlViewStep</name>
    <message>
      <location filename="../src/modules/localeq/LocaleQmlViewStep.cpp" line="32"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Konum Bilgisi</translation>
    </message>
  </context>
  <context>
    <name>LocaleTests</name>
    <message>
      <location filename="../src/libcalamares/locale/Tests.cpp" line="266"/>
      <source>Quit</source>
      <translation>Çık</translation>
    </message>
  </context>
  <context>
    <name>LocaleViewStep</name>
    <message>
      <location filename="../src/modules/locale/LocaleViewStep.cpp" line="71"/>
      <source>Location</source>
      <comment>@label</comment>
      <translation>Konum Bilgisi</translation>
    </message>
  </context>
  <context>
    <name>LuksBootKeyFileJob</name>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="33"/>
      <source>Configuring LUKS key file.</source>
      <translation>LUKS anahtar dosyası yapılandırılıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="254"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="262"/>
      <source>No partitions are defined.</source>
      <translation>Tanımlı bölüntü yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="297"/>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="304"/>
      <source>Encrypted rootfs setup error</source>
      <translation>Şifrelenmiş rootfs ayarlama hatası</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="298"/>
      <source>Root partition %1 is LUKS but no passphrase has been set.</source>
      <translation>%1 kök bölüntüsü LUKS olacak; ancak bunun için parola ayarlanmadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/luksbootkeyfile/LuksBootKeyFileJob.cpp" line="305"/>
      <source>Could not create LUKS key file for root partition %1.</source>
      <translation>%1 kök bölüntüsü için LUKS anahtar dosyası oluşturulamadı.</translation>
    </message>
  </context>
  <context>
    <name>MachineIdJob</name>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="55"/>
      <source>Generate machine-id.</source>
      <translation>Makine kimliği oluştur.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="71"/>
      <source>Configuration Error</source>
      <translation>Yapılandırma Hatası</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="72"/>
      <source>No root mount point is set for MachineId.</source>
      <translation>MachineId için kök bağlama noktası ayarlanmadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="63"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="71"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="75"/>
      <location filename="../src/modules/machineid/Workers.cpp" line="92"/>
      <source>File not found</source>
      <translation>Dosya bulunamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="64"/>
      <source>Path &lt;pre&gt;%1&lt;/pre&gt; must be an absolute path.</source>
      <translation> &lt;pre&gt;%1&lt;/pre&gt; yolu mutlak bir yol olmalı.</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/Workers.cpp" line="93"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Yeni rastgele dosya&lt;pre&gt;%1&lt;/pre&gt; oluşturulamadı.</translation>
    </message>
  </context>
  <context>
    <name>Map</name>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="237"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Zaman dilimi: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@info</comment>
      <translation>Tercih ettiğiniz konumu haritada seçin ki kurulum programı ilgili yerel ayarları ve zaman dilimi
            ayarlarını size önerebilsin. Önerilen ayarları aşağıda ayrıntılı olarak değiştirebilirsiniz. Haritada arama yapmak
            için fareyle sürükleyin ve +/- düğmeleri veya fare tekerleği ile yakınlaştırıp uzaklaştırın.</translation>
    </message>
  </context>
  <context>
    <name>Map-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="237"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Zaman dilimi: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Map-qt6.qml" line="258"/>
      <source>Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.</source>
      <comment>@label</comment>
      <translation>Tercih ettiğiniz konumu haritada seçin ki kurulum programı ilgili yerel ayarları ve zaman dilimi
            ayarlarını size önerebilsin. Önerilen ayarları aşağıda ayrıntılı olarak değiştirebilirsiniz. Haritada arama yapmak
            için fareyle sürükleyin ve +/- düğmeleri veya fare tekerleği ile yakınlaştırıp uzaklaştırın.</translation>
    </message>
  </context>
  <context>
    <name>NetInstallViewStep</name>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="50"/>
      <source>Package selection</source>
      <translation>Paket seçimi</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="51"/>
      <source>Office software</source>
      <translation>Ofis yazılımı</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="52"/>
      <source>Office package</source>
      <translation>Ofis paketi</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="53"/>
      <source>Browser software</source>
      <translation>Tarayıcı yazılımı</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="54"/>
      <source>Browser package</source>
      <translation>Tarayıcı paketi</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="55"/>
      <source>Web browser</source>
      <translation>İnternet tarayıcısı</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="56"/>
      <source>Kernel</source>
      <comment>label for netinstall module, Linux kernel</comment>
      <translation>Çekirdek</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="57"/>
      <source>Services</source>
      <comment>label for netinstall module, system services</comment>
      <translation>Hizmetler</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="58"/>
      <source>Login</source>
      <comment>label for netinstall module, choose login manager</comment>
      <translation>Oturum aç</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="59"/>
      <source>Desktop</source>
      <comment>label for netinstall module, choose desktop environment</comment>
      <translation>Masaüstü</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="60"/>
      <source>Applications</source>
      <translation>Uygulamalar</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="61"/>
      <source>Communication</source>
      <comment>label for netinstall module</comment>
      <translation>İletişim</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="62"/>
      <source>Development</source>
      <comment>label for netinstall module</comment>
      <translation>Geliştirme</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="63"/>
      <source>Office</source>
      <comment>label for netinstall module</comment>
      <translation>Ofis</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="64"/>
      <source>Multimedia</source>
      <comment>label for netinstall module</comment>
      <translation>Çoklu Ortam</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="65"/>
      <source>Internet</source>
      <comment>label for netinstall module</comment>
      <translation>İnternet</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="66"/>
      <source>Theming</source>
      <comment>label for netinstall module</comment>
      <translation>Temalar</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="67"/>
      <source>Gaming</source>
      <comment>label for netinstall module</comment>
      <translation>Oyunlar</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/NetInstallViewStep.cpp" line="68"/>
      <source>Utilities</source>
      <comment>label for netinstall module</comment>
      <translation>İzlenceler</translation>
    </message>
  </context>
  <context>
    <name>NotesQmlViewStep</name>
    <message>
      <location filename="../src/modules/notesqml/NotesQmlViewStep.cpp" line="23"/>
      <source>Notes</source>
      <translation>Notlar</translation>
    </message>
  </context>
  <context>
    <name>OEMPage</name>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="32"/>
      <source>Ba&amp;tch:</source>
      <translation>Top&amp;lu:</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="42"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Enter a batch-identifier here. This will be stored in the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Buraya toplu tanımlayıcı girin. Bu, hedef sistemde depolanır.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMPage.ui" line="52"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Configuration&lt;/h1&gt;&lt;p&gt;Calamares will use OEM settings while configuring the target system.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;h1&gt;OEM Yapılandırması&lt;/h1&gt;&lt;p&gt;Calamares hedef sistemi yapılandırırken OEM ayarlarını kullanacaktır.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
  </context>
  <context>
    <name>OEMViewStep</name>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="118"/>
      <source>OEM Configuration</source>
      <translation>OEM Yapılandırması</translation>
    </message>
    <message>
      <location filename="../src/modules/oemid/OEMViewStep.cpp" line="124"/>
      <source>Set the OEM Batch Identifier to &lt;code&gt;%1&lt;/code&gt;.</source>
      <translation>OEM Toplu Tanımlayıcısını &lt;code&gt;%1&lt;/code&gt; olarak ayarla.</translation>
    </message>
  </context>
  <context>
    <name>Offline</name>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation>Tercih ettiğiniz bölgeyi seçin veya varsayılan ayarları kullanın</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Zaman dilimi: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation>Bölgenizde tercih ettiğiniz yeri seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Bölge</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation>Aşağıda dil ve yerel ayarlarında ince ayar yapabilirsiniz</translation>
    </message>
  </context>
  <context>
    <name>Offline-qt6</name>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="47"/>
      <source>Select your preferred region, or use the default settings</source>
      <comment>@label</comment>
      <translation>Tercih ettiğiniz bölgeyi seçin veya varsayılan ayarları kullanın</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="103"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="180"/>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="224"/>
      <source>Timezone: %1</source>
      <comment>@label</comment>
      <translation>Zaman dilimi: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="120"/>
      <source>Select your preferred zone within your region</source>
      <comment>@label</comment>
      <translation>Bölgenizde tercih ettiğiniz alanı seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="193"/>
      <source>Zones</source>
      <comment>@button</comment>
      <translation>Bölge</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/Offline-qt6.qml" line="240"/>
      <source>You can fine-tune language and locale settings below</source>
      <comment>@label</comment>
      <translation>Aşağıda dil ve yerel ayarlarında ince ayar yapabilirsiniz</translation>
    </message>
  </context>
  <context>
    <name>PWQ</name>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="52"/>
      <source>Password is too short</source>
      <translation>Parola pek kısa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="68"/>
      <source>Password is too long</source>
      <translation>Parola pek uzun</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="189"/>
      <source>Password is too weak</source>
      <translation>Parola pek zayıf</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="197"/>
      <source>Memory allocation error when setting '%1'</source>
      <translation>'%1' ayarlanırken bellek ayırma hatası</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="200"/>
      <source>Memory allocation error</source>
      <translation>Bellek ayırma hatası</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="202"/>
      <source>The password is the same as the old one</source>
      <translation>Parola, eskisiyle aynı</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="204"/>
      <source>The password is a palindrome</source>
      <translation>Parola, eskilerinden birinin ters okunuşu olabilir</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="206"/>
      <source>The password differs with case changes only</source>
      <translation>Parola yalnızca BÜYÜK/küçük harf türünden değişiklik gösteriyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="208"/>
      <source>The password is too similar to the old one</source>
      <translation>Parola, eski parolaya çok benziyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="210"/>
      <source>The password contains the user name in some form</source>
      <translation>Parola, kullanıcı adını bir biçimde içeriyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="212"/>
      <source>The password contains words from the real name of the user in some form</source>
      <translation>Parola, kullanıcının gerçek adını içeriyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="215"/>
      <source>The password contains forbidden words in some form</source>
      <translation>Parola, izin verilmeyen sözcükler içeriyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="219"/>
      <source>The password contains fewer than %n digits</source>
      <translation>
        <numerusform>Parola %n'den az basamak içeriyor</numerusform>
        <numerusform>Parola, %n basamaktan daha az basamak içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="222"/>
      <source>The password contains too few digits</source>
      <translation>Parolada pek az basamak var</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="226"/>
      <source>The password contains fewer than %n uppercase letters</source>
      <translation>
        <numerusform>Parola %n'den daha az büyük harf içeriyor</numerusform>
        <numerusform>Parola, %n BÜYÜK harften daha az harf içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="229"/>
      <source>The password contains too few uppercase letters</source>
      <translation>Parolada pek az BÜYÜK harf var</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="233"/>
      <source>The password contains fewer than %n lowercase letters</source>
      <translation>
        <numerusform>Parola %n'den daha az küçük harf içeriyor</numerusform>
        <numerusform>Parola, %n küçük harften daha az harf içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="236"/>
      <source>The password contains too few lowercase letters</source>
      <translation>Parola, pek az küçük harf içeriyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="240"/>
      <source>The password contains fewer than %n non-alphanumeric characters</source>
      <translation>
        <numerusform>Parola %n'den daha az alfasayısal olmayan karakter içeriyor</numerusform>
        <numerusform>Parola, %n abece-sayısal olmayan karakterden daha az karakter içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="243"/>
      <source>The password contains too few non-alphanumeric characters</source>
      <translation>Parola, pek az sayıda abece-sayısal olmayan karakter içeriyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="247"/>
      <source>The password is shorter than %n characters</source>
      <translation>
        <numerusform>Parola %n karakterden kısa</numerusform>
        <numerusform>Parola %n karakterden kısa</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="250"/>
      <source>The password is too short</source>
      <translation>Parola pek kısa</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="252"/>
      <source>The password is a rotated version of the previous one</source>
      <translation>Parola, öncekinin döndürülmüş bir sürümü</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="256"/>
      <source>The password contains fewer than %n character classes</source>
      <translation>
        <numerusform>Parola %n karakter sınıfından daha azını içeriyor</numerusform>
        <numerusform>Parola, %n karakter sınıfından daha azını içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="259"/>
      <source>The password does not contain enough character classes</source>
      <translation>Parola, yeterli sayıda karakter türü içermiyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="263"/>
      <source>The password contains more than %n same characters consecutively</source>
      <translation>
        <numerusform>Parola art arda %n'den fazla aynı karakter içeriyor</numerusform>
        <numerusform>Parola, %n karakterden daha çok karakter içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="266"/>
      <source>The password contains too many same characters consecutively</source>
      <translation>Parola, ardışık olarak aynı sayıda çok karakter içeriyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="270"/>
      <source>The password contains more than %n characters of the same class consecutively</source>
      <translation>
        <numerusform>Parola aynı sınıftan art arda %n'den fazla karakter içeriyor</numerusform>
        <numerusform>Parola, aynı sınıfın %n karakterinden daha çok karakter içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="276"/>
      <source>The password contains too many characters of the same class consecutively</source>
      <translation>Parola, aynı türden pek çok karakter içeriyor</translation>
    </message>
    <message numerus="yes">
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="281"/>
      <source>The password contains monotonic sequence longer than %n characters</source>
      <translation>
        <numerusform>Parola, %n karakterden uzun monoton bir sıra içeriyor</numerusform>
        <numerusform>Parola, %n karakterden uzun monoton bir sıra içeriyor</numerusform>
      </translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="287"/>
      <source>The password contains too long of a monotonic character sequence</source>
      <translation>Parola, çok uzun monoton karakter dizisi içeriyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="290"/>
      <source>No password supplied</source>
      <translation>Parola sağlanmadı</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="292"/>
      <source>Cannot obtain random numbers from the RNG device</source>
      <translation>RNG aygıtından rastgele sayılar elde edilemiyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="294"/>
      <source>Password generation failed - required entropy too low for settings</source>
      <translation>Parola üretimi başarısız oldu - ayarlar için entropi çok düşük gerekli</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="299"/>
      <source>The password fails the dictionary check - %1</source>
      <translation>Parola, sözlük denetimini geçemedi - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="302"/>
      <source>The password fails the dictionary check</source>
      <translation>Parola, sözlük denetimini geçemiyor</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="306"/>
      <source>Unknown setting - %1</source>
      <translation>Bilinmeyen ayar - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="308"/>
      <source>Unknown setting</source>
      <translation>Bilinmeyen ayar</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="312"/>
      <source>Bad integer value of setting - %1</source>
      <translation>Hatalı tamsayı değeri - %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="314"/>
      <source>Bad integer value</source>
      <translation>Hatalı tamsayı değeri</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="318"/>
      <source>Setting %1 is not of integer type</source>
      <translation>%1 ayarı tamsayı türünde değil</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="320"/>
      <source>Setting is not of integer type</source>
      <translation>Ayar tamsayı türünde değil</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="324"/>
      <source>Setting %1 is not of string type</source>
      <translation>%1 ayarı dizi türünde değil</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="326"/>
      <source>Setting is not of string type</source>
      <translation>Ayar dizi türünde değil</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="328"/>
      <source>Opening the configuration file failed</source>
      <translation>Yapılandırma dosyasını açma başarısız oldu</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="330"/>
      <source>The configuration file is malformed</source>
      <translation>Yapılandırma dosyası hatalı biçimde oluşturulmuş</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="332"/>
      <source>Fatal failure</source>
      <translation>Onulmaz hata</translation>
    </message>
    <message>
      <location filename="../src/modules/users/CheckPWQuality.cpp" line="334"/>
      <source>Unknown error</source>
      <translation>Bilinmeyen hata</translation>
    </message>
  </context>
  <context>
    <name>PackageChooserPage</name>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="50"/>
      <source>Product Name</source>
      <translation>Ürün Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="63"/>
      <source>TextLabel</source>
      <translation>MetinEtiketi</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/page_package.ui" line="79"/>
      <source>Long Product Description</source>
      <translation>Uzun Ürün Açıklaması</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="25"/>
      <source>Package Selection</source>
      <translation>Paket Seçimi</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageChooserPage.cpp" line="26"/>
      <source>Please pick a product from the list. The selected product will be installed.</source>
      <translation>Lütfen listeden bir ürün seçin. Seçili ürün kurulacak.</translation>
    </message>
  </context>
  <context>
    <name>PackageModel</name>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Name</source>
      <translation>Ad</translation>
    </message>
    <message>
      <location filename="../src/modules/netinstall/PackageModel.cpp" line="206"/>
      <source>Description</source>
      <translation>Açıklama</translation>
    </message>
  </context>
  <context>
    <name>Page_Keyboard</name>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="74"/>
      <source>Keyboard model:</source>
      <translation>Klavye modeli:</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="146"/>
      <source>Type here to test your keyboard</source>
      <translation>Sınamak için buraya yazın…</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/KeyboardPage.ui" line="153"/>
      <source>Switch Keyboard:</source>
      <extracomment>shortcut for switching between keyboard layouts</extracomment>
      <translation>Klavye değiştir:</translation>
    </message>
  </context>
  <context>
    <name>Page_UserSetup</name>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="40"/>
      <source>What is your name?</source>
      <translation>Adınız nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="55"/>
      <source>Your Full Name</source>
      <translation>Tam Adınız</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="124"/>
      <source>What name do you want to use to log in?</source>
      <translation>Oturum açmak için hangi adı kullanmak istiyorsunuz?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="148"/>
      <source>login</source>
      <translation>Oturum Açma</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="223"/>
      <source>What is the name of this computer?</source>
      <translation>Bu bilgisayarın adı nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="247"/>
      <source>&lt;small&gt;This name will be used if you make the computer visible to others on a network.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Bilgisayarınız herhangi bir ağ üzerinde görünür ise bu adı kullanacak.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="250"/>
      <source>Computer Name</source>
      <translation>Bilgisayar Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="325"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Hesabınızı güvende tutmak için bir parola seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="349"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="374"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Olası yazım hatalarının denetlenebilmesi için parolayı iki kez girin. İyi bir parola; harflerin karışımından, sayılardan ve noktalama işaretlerinden oluşur ve en az sekiz karakter uzunluğunda olup düzenli aralıklarla değiştirilmelidir.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="355"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="525"/>
      <source>Password</source>
      <translation>Parola</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="380"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="550"/>
      <source>Repeat Password</source>
      <translation>Parolayı Yinele</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="455"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Bu kutu işaretlendiğinde parola gücü denetlenir ve zayıf bir parola kullanamazsınız.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="458"/>
      <source>Require strong passwords.</source>
      <translation>Güçlü parola gerektir.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="465"/>
      <source>Log in automatically without asking for the password.</source>
      <translation>Parolayı sormadan kendiliğinden oturum aç.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="472"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Yönetici hesabı için aynı parolayı kullan.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="495"/>
      <source>Choose a password for the administrator account.</source>
      <translation>Yönetici hesabı için bir parola seç.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/page_usersetup.ui" line="519"/>
      <location filename="../src/modules/users/page_usersetup.ui" line="544"/>
      <source>&lt;small&gt;Enter the same password twice, so that it can be checked for typing errors.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Olası yazım hatalarının denetlenebilmesi için parolayı iki kez girin.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>PartitionLabelsView</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="178"/>
      <source>Root</source>
      <translation>Kök</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="182"/>
      <source>Home</source>
      <comment>@label</comment>
      <translation>Ana Klasör</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="186"/>
      <source>Boot</source>
      <comment>@label</comment>
      <translation>Önyükleme</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="191"/>
      <source>EFI system</source>
      <comment>@label</comment>
      <translation>EFI Sistem</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="195"/>
      <source>Swap</source>
      <comment>@label</comment>
      <translation>Takas</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="199"/>
      <source>New partition for %1</source>
      <comment>@label</comment>
      <translation>%1 için yeni bölüntü</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="203"/>
      <source>New partition</source>
      <comment>@label</comment>
      <translation>Yeni bölüntü</translation>
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
      <translation>Boş Alan</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="161"/>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="205"/>
      <source>New Partition</source>
      <comment>@title</comment>
      <translation>Yeni Bölüntü</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="307"/>
      <source>Name</source>
      <comment>@title</comment>
      <translation>Ad</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="309"/>
      <source>File System</source>
      <comment>@title</comment>
      <translation>Dosya Sistemi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="311"/>
      <source>File System Label</source>
      <comment>@title</comment>
      <translation>Dosya Sistemi Etiketi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="313"/>
      <source>Mount Point</source>
      <comment>@title</comment>
      <translation>Bağlama Noktası</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/core/PartitionModel.cpp" line="315"/>
      <source>Size</source>
      <comment>@title</comment>
      <translation>Boyut</translation>
    </message>
  </context>
  <context>
    <name>PartitionPage</name>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="26"/>
      <source>Storage de&amp;vice:</source>
      <translation>Depolama ay&amp;gıtı:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="55"/>
      <source>&amp;Revert All Changes</source>
      <translation>&amp;Tüm Değişiklikleri Geri Al</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="91"/>
      <source>New Partition &amp;Table</source>
      <translation>Yeni Bölüntü &amp;Tablosu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="111"/>
      <source>Cre&amp;ate</source>
      <translation>Oluş&amp;tur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="118"/>
      <source>&amp;Edit</source>
      <translation>&amp;Düzenle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="125"/>
      <source>&amp;Delete</source>
      <translation>&amp;Sil</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="136"/>
      <source>New Volume Group</source>
      <translation>Yeni Disk Bölümü Grubu</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="143"/>
      <source>Resize Volume Group</source>
      <translation>D. Bölümü Grubunu Yeniden Boyutlandır</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="150"/>
      <source>Deactivate Volume Group</source>
      <translation>D. Bölümü Grubunu Devre Dışı Bırak</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="157"/>
      <source>Remove Volume Group</source>
      <translation>D. Bölümü Grubunu Kaldır</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.ui" line="184"/>
      <source>I&amp;nstall boot loader on:</source>
      <translation>Önyükleyiciyi şuraya &amp;kur:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="224"/>
      <source>Are you sure you want to create a new partition table on %1?</source>
      <translation>%1 üzerinde yeni bir bölüntü tablosu oluşturmak istiyor musunuz?</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="259"/>
      <source>Can not create new partition</source>
      <translation>Yeni bölüntü oluşturulamıyor</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionPage.cpp" line="260"/>
      <source>The partition table on %1 already has %2 primary partitions, and no more can be added. Please remove one primary partition and add an extended partition, instead.</source>
      <translation>%1 üzerindeki bölüntü tablosu halihazırda %2 birincil bölüntüye sahip ve artık eklenemiyor. Lütfen bir birincil bölüntüyü kaldırın ve bunun yerine genişletilmiş bir bölüntü ekleyin.</translation>
    </message>
  </context>
  <context>
    <name>PartitionViewStep</name>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="56"/>
      <source>Gathering system information…</source>
      <comment>@status</comment>
      <translation>Sistem bilgileri toplanıyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="107"/>
      <source>Partitions</source>
      <comment>@label</comment>
      <translation>Disk Bölümleme</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="143"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system</source>
      <comment>@label</comment>
      <translation>Diğer işletim sisteminin &lt;strong&gt;yanına&lt;/strong&gt; %1 yükle.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="147"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk and install %1</source>
      <comment>@label</comment>
      <translation>Diski &lt;strong&gt;sil&lt;/strong&gt; ve %1 yükle.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="151"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition with %1</source>
      <comment>@label</comment>
      <translation>%1 ile disk bölümünün &lt;strong&gt;üzerine yaz&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="156"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning</source>
      <comment>@label</comment>
      <translation>&lt;strong&gt;Elle&lt;/strong&gt; bölümleme</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="178"/>
      <source>Install %1 &lt;strong&gt;alongside&lt;/strong&gt; another operating system on disk &lt;strong&gt;%2&lt;/strong&gt; (%3)</source>
      <comment>@info</comment>
      <translation>%1 &lt;strong&gt;%2&lt;/strong&gt; (%3) diskindeki diğer işletim sisteminin &lt;strong&gt;yanına&lt;/strong&gt; yükle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="187"/>
      <source>&lt;strong&gt;Erase&lt;/strong&gt; disk &lt;strong&gt;%2&lt;/strong&gt; (%3) and install %1</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3) diski &lt;strong&gt;sil&lt;/strong&gt; ve %1 yükle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="194"/>
      <source>&lt;strong&gt;Replace&lt;/strong&gt; a partition on disk &lt;strong&gt;%2&lt;/strong&gt; (%3) with %1</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%2&lt;/strong&gt; (%3) disk bölümünün %1 ile &lt;strong&gt;üzerine yaz&lt;/strong&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="203"/>
      <source>&lt;strong&gt;Manual&lt;/strong&gt; partitioning on disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; (%2) disk bölümünü &lt;strong&gt;elle&lt;/strong&gt; bölümle.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="213"/>
      <source>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</source>
      <comment>@info</comment>
      <translation>Disk &lt;strong&gt;%1&lt;/strong&gt; (%2)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="257"/>
      <source>Unsafe partition actions are enabled.</source>
      <translation>Güvenli olmayan bölüntü eylemleri etkinleştirildi.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="260"/>
      <source>Partitioning is configured to &lt;b&gt;always&lt;/b&gt; fail.</source>
      <translation>Bölüntüleme, &lt;b&gt;her zaman&lt;/b&gt; başarısız olacak şekilde yapılandırıldı.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="263"/>
      <source>No partitions will be changed.</source>
      <translation>Değiştirilecek bölüntü yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="303"/>
      <source>Current:</source>
      <comment>@label</comment>
      <translation>Şu anki durum:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="321"/>
      <source>After:</source>
      <comment>@label</comment>
      <translation>Sonrası:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="543"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;To configure an EFI system partition, go back and select or create a suitable filesystem.</source>
      <translation>%1 yazılımını başlatmak için bir EFI sistem bölüntüsü gereklidir. &lt;br/&gt;&lt;br/&gt; Bir EFI sistem bölüntüsünü yapılandırmak için geri dönün ve uygun bir dosya sistemi seçin veya oluşturun.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="549"/>
      <source>An EFI system partition is necessary to start %1.&lt;br/&gt;&lt;br/&gt;The EFI system partition does not meet recommendations. It is recommended to go back and select or create a suitable filesystem.</source>
      <translation>%1 yazılımını başlatmak için bir EFI sistem bölüntüsü gereklidir. &lt;br/&gt;&lt;br/&gt; EFI sistem bölüntüsü önerileri karşılamıyor. Geri dönüp uygun bir dosya sistemi seçmeniz veya oluşturmanız önerilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="557"/>
      <source>The filesystem must be mounted on &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>Dosya sistemi &lt;strong&gt;%1&lt;/strong&gt; üzerinde bağlanmalıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="558"/>
      <source>The filesystem must have type FAT32.</source>
      <translation>Dosya sistemi FAT32 türünde olmalıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="559"/>
      <source>The filesystem must have flag &lt;strong&gt;%1&lt;/strong&gt; set.</source>
      <translation>Dosya sisteminde &lt;strong&gt;%1&lt;/strong&gt; bayrağı ayarlanmış olmalıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="567"/>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="569"/>
      <source>The filesystem must be at least %1 MiB in size.</source>
      <translation>Dosya sisteminin boyutu en az %1 MB olmalıdır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="571"/>
      <source>The minimum recommended size for the filesystem is %1 MiB.</source>
      <translation>Dosya sistemi için önerilen minimum boyut %1 MB'dir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="573"/>
      <source>You can continue without setting up an EFI system partition but your system may fail to start.</source>
      <translation>Bir EFI sistem bölüntüsü ayarlamadan kurulumu sürdürebilirsiniz; ancak sisteminiz başlatılamayabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="575"/>
      <source>You can continue with this EFI system partition configuration but your system may fail to start.</source>
      <translation>Bu EFI sistem bölüntüsü yapılandırma işlemini sürdürebilirsiniz; ancak sisteminiz başlatılamayabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="587"/>
      <source>No EFI system partition configured</source>
      <translation>Yapılandırılan EFI sistem bölüntüsü yok</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="595"/>
      <source>EFI system partition configured incorrectly</source>
      <translation>EFI sistem bölüntüsü yanlış yapılandırılmış</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="615"/>
      <source>EFI system partition recommendation</source>
      <translation>EFI sistem bölüntüsü tavsiyesi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="634"/>
      <source>Option to use GPT on BIOS</source>
      <translation>BIOS'ta GPT kullanma seçeneği</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="635"/>
      <source>A GPT partition table is the best option for all systems. This installer supports such a setup for BIOS systems too.&lt;br/&gt;&lt;br/&gt;To configure a GPT partition table on BIOS, (if not done so already) go back and set the partition table to GPT, next create a 8 MB unformatted partition with the &lt;strong&gt;%2&lt;/strong&gt; flag enabled.&lt;br/&gt;&lt;br/&gt;An unformatted 8 MB partition is necessary to start %1 on a BIOS system with GPT.</source>
      <translation>GPT bölüntü tablosu, tüm sistemler için en iyi seçenektir. Bu kurulum programı, BIOS sistemleri için de böyle bir düzeni destekler.&lt;br/&gt;&lt;br/&gt;BIOS'ta bir GPT bölüntü tablosu yapılandırmak için (önceden yapılmadıysa) geri dönün ve bölüntü tablosunu GPT olarak ayarlayın; sonrasında &lt;strong&gt;%2&lt;/strong&gt; bayrağı etkinleştirilmiş bir biçimde 8 MB'lık biçimlendirilmemiş bir bölüntü oluşturun.&lt;br/&gt;&lt;br/&gt;%1 yazılımını bir BIOS sistemde GPT ile başlatmak için 8 MB'lık biçimlendirilmemiş bir bölüntü gereklidir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="657"/>
      <source>Boot partition not encrypted</source>
      <translation>Önyükleme bölüntüsü şifreli değil</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="658"/>
      <source>A separate boot partition was set up together with an encrypted root partition, but the boot partition is not encrypted.&lt;br/&gt;&lt;br/&gt;There are security concerns with this kind of setup, because important system files are kept on an unencrypted partition.&lt;br/&gt;You may continue if you wish, but filesystem unlocking will happen later during system startup.&lt;br/&gt;To encrypt the boot partition, go back and recreate it, selecting &lt;strong&gt;Encrypt&lt;/strong&gt; in the partition creation window.</source>
      <translation>Şifrelenmiş bir kök bölüntüsü ile birlikte ayrı bir önyükleme bölüntüsü ayarlandı; ancak önyükleme bölüntüsü şifrelenmiyor.&lt;br/&gt;&lt;br/&gt;Bu tür düzenler ile ilgili güvenlik endişeleri vardır; çünkü önemli sistem dosyaları şifrelenmemiş bir bölüntüde tutulur.&lt;br/&gt;İsterseniz sürdürebilirsiniz; ancak dosya sistemi kilidini açma, sistem başlatma işlem silsilesinde daha sonra gerçekleşecektir.&lt;br/&gt;Önyükleme bölüntüsünü şifrelemek için geri dönüp bölüntü oluşturma penceresinde &lt;strong&gt;Şifrele&lt;/strong&gt;'yi seçerek onu yeniden oluşturun.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="750"/>
      <source>has at least one disk device available.</source>
      <translation>en az bir disk aygıtı kullanılabilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/PartitionViewStep.cpp" line="751"/>
      <source>There are no partitions to install on.</source>
      <translation>Üzerine kurulacak bir bölüntü yok.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfJob</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="33"/>
      <source>Applying Plasma Look-and-Feel…</source>
      <comment>@status</comment>
      <translation>Plazma Görünüm ve Hissi Uygulanıyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="57"/>
      <location filename="../src/modules/plasmalnf/PlasmaLnfJob.cpp" line="58"/>
      <source>Could not select KDE Plasma Look-and-Feel package</source>
      <translation>KDE Plasma Görünüm ve His paketi seçilemedi</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfPage</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="80"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is set up. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Lütfen KDE Plasma Masaüstü için temalardan görünüm ve hissi seçin. Ayrıca bu adımı atlayabilir ve sistem ayarlandıktan sonra sistem görünüşünü yapılandırabilirsiniz. Bir görünüm ve his seçeneğine tıklarsanız size canlı bir önizleme gösterilecektir.</translation>
    </message>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfPage.cpp" line="87"/>
      <source>Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed. Clicking on a look-and-feel selection will give you a live preview of that look-and-feel.</source>
      <translation>Lütfen KDE Plasma Masaüstü için temalardan görünüm ve hissi seçin. Ayrıca bu adımı atlayabilir ve sistem ayarlandıktan sonra sistem görünüşünü yapılandırabilirsiniz. Bir görünüm ve his seçeneğine tıklarsanız size canlı bir önizleme gösterilecektir.</translation>
    </message>
  </context>
  <context>
    <name>PlasmaLnfViewStep</name>
    <message>
      <location filename="../src/modules/plasmalnf/PlasmaLnfViewStep.cpp" line="43"/>
      <source>Look-and-Feel</source>
      <comment>@label</comment>
      <translation>Görünüm ve His</translation>
    </message>
  </context>
  <context>
    <name>PreserveFiles</name>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="56"/>
      <source>Saving files for later…</source>
      <comment>@status</comment>
      <translation>Dosyalar daha sonrası için kaydediliyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="64"/>
      <source>No files configured to save for later.</source>
      <translation>Daha sonra kaydetmek için dosya yapılandırılmamış.</translation>
    </message>
    <message>
      <location filename="../src/modules/preservefiles/PreserveFiles.cpp" line="88"/>
      <source>Not all of the configured files could be preserved.</source>
      <translation>Yapılandırılmış dosyaların tümü korunamadı.</translation>
    </message>
  </context>
  <context>
    <name>ProcessResult</name>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="301"/>
      <source>
There was no output from the command.</source>
      <translation>
Komut çıktısı yok.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="302"/>
      <source>
Output:
</source>
      <translation>
Çıktı:
</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="307"/>
      <source>External command crashed.</source>
      <translation>Dış komut çöktü.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="308"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; crashed.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; komutu çöktü.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="315"/>
      <source>External command failed to start.</source>
      <translation>Dış komut başlatılamadı.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="316"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to start.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; komutu başlatılamadı.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="322"/>
      <source>Internal error when starting command.</source>
      <translation>Komut başlatılırken içsel hata.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="323"/>
      <source>Bad parameters for process job call.</source>
      <translation>Süreç iş çağrısı için hatalı parametreler.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="329"/>
      <source>External command failed to finish.</source>
      <translation>Dış komut işini bitiremedi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="330"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; failed to finish in %2 seconds.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; komutu, işini %2 saniyede bitiremedi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="338"/>
      <source>External command finished with errors.</source>
      <translation>Dış komut, işini hatalarla bitirdi.</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/utils/System.cpp" line="339"/>
      <source>Command &lt;i&gt;%1&lt;/i&gt; finished with exit code %2.</source>
      <translation>&lt;i&gt;%1&lt;/i&gt; komutu, %2 çıkış kodu ile işini bitirdi.</translation>
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
      <translation>bilinmeyen</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="35"/>
      <source>extended</source>
      <comment>@partition info</comment>
      <translation>genişletilmiş</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="37"/>
      <source>unformatted</source>
      <comment>@partition info</comment>
      <translation>biçimlendirilmemiş</translation>
    </message>
    <message>
      <location filename="../src/libcalamares/partition/FileSystem.cpp" line="39"/>
      <source>swap</source>
      <comment>@partition info</comment>
      <translation>takas</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="145"/>
      <location filename="../src/modules/keyboard/keyboardwidget/keyboardglobal.cpp" line="192"/>
      <source>Default</source>
      <translation>Öntanımlı</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="101"/>
      <source>Directory not found</source>
      <translation>Dizin bulunamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/machineid/MachineIdJob.cpp" line="102"/>
      <source>Could not create new random file &lt;pre&gt;%1&lt;/pre&gt;.</source>
      <translation>Yeni rastgele dosya&lt;pre&gt;%1&lt;/pre&gt; oluşturulamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="74"/>
      <source>No product</source>
      <translation>Ürün yok</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooser/PackageModel.cpp" line="82"/>
      <source>No description provided.</source>
      <translation>Sağlanan açıklama yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionDialogHelpers.cpp" line="44"/>
      <source>(no mount point)</source>
      <translation>(bağlama noktası yok)</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/PartitionLabelsView.cpp" line="39"/>
      <source>Unpartitioned space or unknown partition table</source>
      <comment>@info</comment>
      <translation>Bölüntülenmemiş alan veya bilinmeyen bölüntü tablosu</translation>
    </message>
  </context>
  <context>
    <name>Recommended</name>
    <message>
      <location filename="../src/modules/welcomeq/Recommended.qml" line="40"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Bu bilgisayar, %1 kurulumu için önerilen gereksinimlerin bazılarını karşılamıyor.&lt;br/&gt;
        Kurulum sürdürülebilir; ancak bazı özellikler devre dışı bırakılabilir.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>RemoveUserJob</name>
    <message>
      <location filename="../src/modules/removeuser/RemoveUserJob.cpp" line="32"/>
      <source>Removing live user from the target system…</source>
      <comment>@status</comment>
      <translation>Liveuser kullanıcı hedef sistemden kaldırılıyor..</translation>
    </message>
  </context>
  <context>
    <name>RemoveVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="26"/>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="38"/>
      <source>Removing Volume Group named %1…</source>
      <comment>@status</comment>
      <translation>%1 adlı disk bölümü grubu kaldırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="32"/>
      <source>Removing Volume Group named &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; adlı disk bölümü grubu kaldırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/RemoveVolumeGroupJob.cpp" line="46"/>
      <source>The installer failed to remove a volume group named '%1'.</source>
      <translation>Kurulum programı, '%1' adlı bir disk bölümü grubunu kaldıramadı.</translation>
    </message>
  </context>
  <context>
    <name>Requirements</name>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="37"/>
      <source>&lt;p&gt;This computer does not satisfy the minimum requirements for installing %1.&lt;br/&gt;
        Installation cannot continue.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Bu bilgisayar, %1 kurulumu için en düşük gereksinimleri karşılamıyor.&lt;br/&gt;
        Kurulum sürdürülemiyor.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/Requirements.qml" line="39"/>
      <source>&lt;p&gt;This computer does not satisfy some of the recommended requirements for setting up %1.&lt;br/&gt;
        Setup can continue, but some features might be disabled.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Bu bilgisayar, %1 kurulumu için önerilen gereksinimlerin bazılarını karşılamıyor.&lt;br/&gt;
        Kurulum sürdürülebilir; ancak bazı özellikler devre dışı bırakılabilir.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>ResizeFSJob</name>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="43"/>
      <source>Performing file system resize…</source>
      <comment>@status</comment>
      <translation>Dosya sistemi yeniden boyutlandırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="162"/>
      <source>Invalid configuration</source>
      <comment>@error</comment>
      <translation>Geçersiz yapılandırma</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="163"/>
      <source>The file-system resize job has an invalid configuration and will not run.</source>
      <comment>@error</comment>
      <translation>Dosya sistemini yeniden boyutlandıma işinin yapılandırması geçersiz ve çalışmayacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="169"/>
      <source>KPMCore not available</source>
      <comment>@error</comment>
      <translation>KPMCore kullanılamıyor</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="170"/>
      <source>Calamares cannot start KPMCore for the file system resize job.</source>
      <comment>@error</comment>
      <translation>Calamares, dosya sistemi yeniden boyutlandırma işi için KPMCore başlatamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="179"/>
      <source>Resize failed.</source>
      <comment>@error</comment>
      <translation>Boyutlandırma başarısız.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="181"/>
      <source>The filesystem %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>%1 dosya sistemi bu sistemde bulunamadı ve yeniden boyutlandırılamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="182"/>
      <source>The device %1 could not be found in this system, and cannot be resized.</source>
      <comment>@info</comment>
      <translation>%1 aygıtı bu sistemde bulunamadı ve yeniden boyutlandırılamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="189"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="201"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="212"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="231"/>
      <source>Resize Failed</source>
      <comment>@error</comment>
      <translation>Yeniden Boyutlandırma Başarısız Oldu</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="191"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="203"/>
      <source>The filesystem %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>%1 dosya sistemi yeniden boyutlandırılamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="192"/>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="204"/>
      <source>The device %1 cannot be resized.</source>
      <comment>@error</comment>
      <translation>%1 aygıtı yeniden boyutlandırılamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="213"/>
      <source>The file system %1 must be resized, but cannot.</source>
      <comment>@info</comment>
      <translation>%1 dosya sisteminin yeniden boyutlandırılması gerekiyor, ancak yapılamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/fsresizer/ResizeFSJob.cpp" line="214"/>
      <source>The device %1 must be resized, but cannot</source>
      <comment>@info</comment>
      <translation>%1 dosya sistemi yeniden boyutlandırılmalıdır; ancak yapılamıyor.</translation>
    </message>
  </context>
  <context>
    <name>ResizePartitionJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="39"/>
      <source>Resize partition %1</source>
      <comment>@title</comment>
      <translation>%1 bölüntüsünü yeniden boyutlandır</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="45"/>
      <source>Resize &lt;strong&gt;%2MiB&lt;/strong&gt; partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%3MiB&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%2 MiB&lt;/strong&gt; &lt;strong&gt;%1&lt;/strong&gt; bölüntüsünü &lt;strong&gt;%3 MiB&lt;/strong&gt; olarak yeniden boyutlandır</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="54"/>
      <source>Resizing %2MiB partition %1 to %3MiB…</source>
      <comment>@status</comment>
      <translation>%2 MB %1 bölüntüsü %3 MB olarak yeniden boyutlandırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizePartitionJob.cpp" line="70"/>
      <source>The installer failed to resize partition %1 on disk '%2'.</source>
      <translation>Kurulum programı, '%2' diski üzerindeki %1 bölüntüsünü yeniden boyutlandırılamadı.</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ResizeVolumeGroupDialog.cpp" line="30"/>
      <source>Resize Volume Group</source>
      <comment>@title</comment>
      <translation>Disk Bölümü Grubunu Yeniden Boyutlandır</translation>
    </message>
  </context>
  <context>
    <name>ResizeVolumeGroupJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="28"/>
      <source>Resize volume group named %1 from %2 to %3</source>
      <comment>@title</comment>
      <translation>%1 adlı disk bölümü grubunu %2 → %3 olarak yeniden boyutlandır</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="37"/>
      <source>Resize volume group named &lt;strong&gt;%1&lt;/strong&gt; from &lt;strong&gt;%2&lt;/strong&gt; to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;text_to_translate&gt;%1&lt;/text_to_translate&gt; adlı disk bölümü grubunu &lt;strong&gt;%2&lt;/strong&gt; → &lt;strong&gt;%3&lt;/strong&gt; olarak yeniden boyutlandır.</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="47"/>
      <source>Resizing volume group named %1 from %2 to %3…</source>
      <comment>@status</comment>
      <translation>%1 adlı disk bölümü grubu %2 → %3 olarak yeniden boyutlandırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/ResizeVolumeGroupJob.cpp" line="58"/>
      <source>The installer failed to resize a volume group named '%1'.</source>
      <translation>Kurulum programı, '%1' adlı bir disk bölümü grubunu yeniden boyutlandıramadı.</translation>
    </message>
  </context>
  <context>
    <name>ResultsListWidget</name>
    <message>
      <location filename="../src/modules/welcome/checker/ResultsListWidget.cpp" line="47"/>
      <source>Checking requirements again in a few seconds ...</source>
      <translation>Birkaç saniye içinde gereksinimler yeniden denetlenecek...</translation>
    </message>
  </context>
  <context>
    <name>ScanningDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Scanning storage devices…</source>
      <comment>@status</comment>
      <translation>Depolama aygıtları taranıyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/ScanningDialog.cpp" line="68"/>
      <source>Partitioning…</source>
      <comment>@status</comment>
      <translation>Bölüntüleniyor…</translation>
    </message>
  </context>
  <context>
    <name>SetHostNameJob</name>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="36"/>
      <source>Set hostname %1</source>
      <translation>%1 makine adını ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="42"/>
      <source>Set hostname &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; makine adını ayarla.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="48"/>
      <source>Setting hostname %1…</source>
      <comment>@status</comment>
      <translation>%1 makine adı ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="121"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="128"/>
      <source>Internal Error</source>
      <translation>İçsel Hata</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="139"/>
      <location filename="../src/modules/users/SetHostNameJob.cpp" line="156"/>
      <source>Cannot write hostname to target system</source>
      <translation>Hedef sisteme makine adı yazılamadı</translation>
    </message>
  </context>
  <context>
    <name>SetKeyboardLayoutJob</name>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="66"/>
      <source>Setting keyboard model to %1, layout as %2-%3…</source>
      <comment>@status, %1 model, %2 layout, %3 variant</comment>
      <translation>Klavye modeli %1 olarak, düzen ise %2-%3 olarak ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="368"/>
      <source>Failed to write keyboard configuration for the virtual console.</source>
      <comment>@error</comment>
      <translation>Sanal konsol için klavye yapılandırması yazılamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="369"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is virtual console configuration path</comment>
      <translation>%1 üzerine yazılamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="394"/>
      <source>Failed to write keyboard configuration for X11.</source>
      <comment>@error</comment>
      <translation>X11 için klavye yapılandırması yazılamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="395"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is keyboard configuration path</comment>
      <translation>%1 üzerine yazılamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="411"/>
      <source>Failed to write keyboard configuration to existing /etc/default directory.</source>
      <comment>@error</comment>
      <translation>Var olan /etc/default dizinine klavye yapılandırması yazılamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboard/SetKeyboardLayoutJob.cpp" line="412"/>
      <source>Failed to write to %1</source>
      <comment>@error, %1 is default keyboard path</comment>
      <translation>%1 üzerine yazılamadı</translation>
    </message>
  </context>
  <context>
    <name>SetPartFlagsJob</name>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="44"/>
      <source>Set flags on partition %1</source>
      <comment>@title</comment>
      <translation>%1 bölüntüsüne bayrakları ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="50"/>
      <source>Set flags on %1MiB %2 partition</source>
      <comment>@title</comment>
      <translation>%1 MB %2 bölüntüsüne bayrakları ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="54"/>
      <source>Set flags on new partition</source>
      <comment>@title</comment>
      <translation>Yeni bölüntüye bayrakları ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="65"/>
      <source>Clear flags on partition &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; bölüntüsündeki bayrakları temizle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="71"/>
      <source>Clear flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition</source>
      <comment>@info</comment>
      <translation>%1 MB &lt;strong&gt;%2&lt;/strong&gt; bölüntüsündeki bayrakları temizle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="75"/>
      <source>Clear flags on new partition</source>
      <comment>@info</comment>
      <translation>Yeni bölüntüdeki bayrakları temizle</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="80"/>
      <source>Set flags on partition &lt;strong&gt;%1&lt;/strong&gt; to &lt;strong&gt;%2&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; bölüntüsündeki bayrakları &lt;strong&gt;%2&lt;/strong&gt; olarak ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="88"/>
      <source>Set flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition to &lt;strong&gt;%3&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>%1 MB &lt;strong&gt;%2&lt;/strong&gt; bölüntüsünün bayraklarını &lt;strong&gt;%3&lt;/strong&gt; olarak ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="94"/>
      <source>Set flags on new partition to &lt;strong&gt;%1&lt;/strong&gt;</source>
      <comment>@info</comment>
      <translation>Yeni bölüntüdeki bayrakları &lt;strong&gt;%1&lt;/strong&gt; olarak ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="105"/>
      <source>Clearing flags on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; bölüntüsündeki bayraklar kaldırılıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="112"/>
      <source>Clearing flags on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation>%1 MB &lt;strong&gt;%2&lt;/strong&gt; bölüntüsündeki bayraklar temizleniyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="117"/>
      <source>Clearing flags on new partition…</source>
      <comment>@status</comment>
      <translation>Yeni bölüntüdeki bayraklar temizleniyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="122"/>
      <source>Setting flags &lt;strong&gt;%2&lt;/strong&gt; on partition &lt;strong&gt;%1&lt;/strong&gt;…</source>
      <comment>@status</comment>
      <translation>&lt;strong&gt;%1&lt;/strong&gt; bölüntüsüne &lt;strong&gt;%2&lt;/strong&gt; bayrakları ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="130"/>
      <source>Setting flags &lt;strong&gt;%3&lt;/strong&gt; on %1MiB &lt;strong&gt;%2&lt;/strong&gt; partition…</source>
      <comment>@status</comment>
      <translation>%1 MiB &lt;strong&gt;%2&lt;/strong&gt; bölüntüsüne &lt;strong&gt;%3&lt;/strong&gt; bayrakları ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="136"/>
      <source>Setting flags &lt;strong&gt;%1&lt;/strong&gt; on new partition…</source>
      <comment>@status</comment>
      <translation>Yeni bölüntüye &lt;strong&gt;%1&lt;/strong&gt; bayrakları ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/jobs/SetPartitionFlagsJob.cpp" line="149"/>
      <source>The installer failed to set flags on partition %1.</source>
      <translation>Kurulum programı, %1 bölüntüsüne bayrakları ayarlayamadı.</translation>
    </message>
  </context>
  <context>
    <name>SetPasswordJob</name>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="38"/>
      <source>Set password for user %1</source>
      <translation>%1 kullanıcısı için parolayı ayarla</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="44"/>
      <source>Setting password for user %1…</source>
      <comment>@status</comment>
      <translation>%1 kullanıcısı için parola ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="80"/>
      <source>Bad destination system path.</source>
      <translation>Bozuk hedef sistem yolu.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="81"/>
      <source>rootMountPoint is %1</source>
      <translation>rootBağlamaNoktası %1</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="89"/>
      <source>Cannot disable root account.</source>
      <translation>Kök hesabı devre dışı bırakılamaz.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="90"/>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="108"/>
      <source>usermod terminated with error code %1.</source>
      <translation>usermod %1 hata koduyla sonlandı.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/SetPasswordJob.cpp" line="107"/>
      <source>Cannot set password for user %1.</source>
      <translation>%1 kullanıcısı için parola ayarlanamıyor.</translation>
    </message>
  </context>
  <context>
    <name>SetTimezoneJob</name>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="32"/>
      <source>Setting timezone to %1/%2…</source>
      <comment>@status</comment>
      <translation>Saat dilimi %1/%2 olarak ayarlanıyor…</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="60"/>
      <source>Cannot access selected timezone path.</source>
      <comment>@error</comment>
      <translation>Seçili zaman dilimi yoluna erişilemedi.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="61"/>
      <source>Bad path: %1</source>
      <comment>@error</comment>
      <translation>Hatalı yol: %1</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="71"/>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="79"/>
      <source>Cannot set timezone.</source>
      <comment>@error</comment>
      <translation>Zaman dilimi ayarlanamıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="72"/>
      <source>Link creation failed, target: %1; link name: %2</source>
      <comment>@info</comment>
      <translation>Bağlantı oluşturulamadı, hedef: %1; bağlantı adı: %2</translation>
    </message>
    <message>
      <location filename="../src/modules/locale/SetTimezoneJob.cpp" line="80"/>
      <source>Cannot open /etc/timezone for writing</source>
      <comment>@info</comment>
      <translation>/etc/timezone yazmak için açılamıyor</translation>
    </message>
  </context>
  <context>
    <name>SetupGroupsJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="181"/>
      <source>Preparing groups…</source>
      <comment>@status</comment>
      <translation>Gruplar hazırlanıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="193"/>
      <location filename="../src/modules/users/MiscJobs.cpp" line="198"/>
      <source>Could not create groups in target system</source>
      <translation>Hedef sistemde gruplar oluşturulamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="199"/>
      <source>These groups are missing in the target system: %1</source>
      <translation>Bu gruplar hedef sistemde eksik, :%1</translation>
    </message>
  </context>
  <context>
    <name>SetupSudoJob</name>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="34"/>
      <source>Configuring &lt;pre&gt;sudo&lt;/pre&gt; users…</source>
      <comment>@status</comment>
      <translation>&lt;pre&gt;sudo&lt;/pre&gt; kullanıcıları yapılandırılıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="70"/>
      <source>Cannot chmod sudoers file.</source>
      <translation>Sudoers dosya izinleri ayarlanamadı.</translation>
    </message>
    <message>
      <location filename="../src/modules/users/MiscJobs.cpp" line="75"/>
      <source>Cannot create sudoers file for writing.</source>
      <translation>sudoers dosyası oluşturulamadı ve yazılamadı.</translation>
    </message>
  </context>
  <context>
    <name>ShellProcessJob</name>
    <message>
      <location filename="../src/modules/shellprocess/ShellProcessJob.cpp" line="38"/>
      <source>Running shell processes…</source>
      <comment>@status</comment>
      <translation>Shell işlemleri çalışıyor...</translation>
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
      <translation>&amp;Tamam</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="24"/>
      <source>&amp;Yes</source>
      <translation>&amp;Evet</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="25"/>
      <source>&amp;No</source>
      <translation>&amp;Hayır</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="26"/>
      <source>&amp;Cancel</source>
      <translation>İ&amp;ptal</translation>
    </message>
    <message>
      <location filename="../src/libcalamaresui/widgets/TranslationFix.cpp" line="27"/>
      <source>&amp;Close</source>
      <translation>&amp;Kapat</translation>
    </message>
  </context>
  <context>
    <name>TrackingInstallJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="100"/>
      <source>Installation feedback</source>
      <translation>Kurulum geri bildirimi</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="106"/>
      <source>Sending installation feedback…</source>
      <comment>@status</comment>
      <translation>Kurulum geri bildirimi gönderiliyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="124"/>
      <source>Internal error in install-tracking.</source>
      <translation>Kurulum izlemede içsel hata.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="125"/>
      <source>HTTP request timed out.</source>
      <translation>HTTP isteği zaman aşımına uğradı.</translation>
    </message>
  </context>
  <context>
    <name>TrackingKUserFeedbackJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="192"/>
      <source>KDE user feedback</source>
      <translation>KDE kullanıcı geri bildirimi</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="198"/>
      <source>Configuring KDE user feedback…</source>
      <comment>@status</comment>
      <translation>KDE kullanıcı geri bildirimleri yapılandırılıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="220"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="228"/>
      <source>Error in KDE user feedback configuration.</source>
      <translation>KDE kullanıcı geri bildirimi yapılandırmasında hata.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="221"/>
      <source>Could not configure KDE user feedback correctly, script error %1.</source>
      <translation>KDE kullanıcı geri bildirimi doğru yapılandırılamadı, betik hatası %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="229"/>
      <source>Could not configure KDE user feedback correctly, Calamares error %1.</source>
      <translation>KDE kullanıcı geri bildirimi doğru şekilde yapılandırılamadı; Calamares hatası %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingMachineUpdateManagerJob</name>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="135"/>
      <source>Machine feedback</source>
      <translation>Makine geri bildirimi</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="141"/>
      <source>Configuring machine feedback…</source>
      <comment>@status</comment>
      <translation>Makine geri bildirimini yapılandırılıyor.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="164"/>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="173"/>
      <source>Error in machine feedback configuration.</source>
      <translation>Makine geri bildirimi yapılandırmasında hata.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="166"/>
      <source>Could not configure machine feedback correctly, script error %1.</source>
      <translation>Makine geri bildirimi doğru yapılandırılamadı, betik hatası %1.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingJobs.cpp" line="175"/>
      <source>Could not configure machine feedback correctly, Calamares error %1.</source>
      <translation>Makine geri bildirimini doğru bir şekilde yapılandıramadı; Calamares hatası %1.</translation>
    </message>
  </context>
  <context>
    <name>TrackingPage</name>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="28"/>
      <source>Placeholder</source>
      <translation>Yer tutucu</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="76"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Click here to send &lt;span style=" font-weight:600;"&gt;no information at all&lt;/span&gt; about your installation.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Kurulumunuz hakkında &lt;span style=" font-weight:600;"&gt;hiçbir bilgi&lt;/span&gt; göndermemek için buraya tıklayın.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/page_trackingstep.ui" line="275"/>
      <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Click here for more information about user feedback&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
      <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;&lt;a href="placeholder"&gt;&lt;span style=" text-decoration: underline; color:#2980b9;"&gt;Kullanıcı geri bildirimi hakkında daha fazla bilgi için burayı tıklayın&lt;/span&gt;&lt;/a&gt;&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="95"/>
      <source>Tracking helps %1 to see how often it is installed, what hardware it is installed on and which applications are used. To see what will be sent, please click the help icon next to each area.</source>
      <translation>İzleme, %1 yazılımının ne sıklıkla kurulduğunu, hangi donanıma kurulduğunu ve hangi uygulamaların kullanıldığını görmesine yardımcı olur. Nelerin gönderileceğini görmek için lütfen her bir alanın yanındaki yardım simgesine tıklayın.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="100"/>
      <source>By selecting this you will send information about your installation and hardware. This information will only be sent &lt;b&gt;once&lt;/b&gt; after the installation finishes.</source>
      <translation>Bunu seçerek, kurulumunuz ve donanımınız hakkında bilgi göndereceksiniz. Bu bilgiler, kurulum bittikten sonra &lt;b&gt;yalnızca bir kez&lt;/b&gt; gönderilecektir.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="103"/>
      <source>By selecting this you will periodically send information about your &lt;b&gt;machine&lt;/b&gt; installation, hardware and applications, to %1.</source>
      <translation>Bunu seçerek, periyodik olarak %1 topluluğuna &lt;b&gt;makine&lt;/b&gt; kurulumu, donanım ve uygulamalarınız hakkında bilgi gönderirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/tracking/TrackingPage.cpp" line="107"/>
      <source>By selecting this you will regularly send information about your &lt;b&gt;user&lt;/b&gt; installation, hardware, applications and application usage patterns, to %1.</source>
      <translation>Bunu seçerek, &lt;b&gt;kullanıcı&lt;/b&gt; kurulumunuz, donanımınız, uygulamalarınız ve uygulama kullanım alışkanlıklarınız hakkında düzenli olarak %1 topluluğuna bilgi gönderirsiniz.</translation>
    </message>
  </context>
  <context>
    <name>TrackingViewStep</name>
    <message>
      <location filename="../src/modules/tracking/TrackingViewStep.cpp" line="49"/>
      <source>Feedback</source>
      <comment>@title</comment>
      <translation>Geri Bildirim</translation>
    </message>
  </context>
  <context>
    <name>UmountJob</name>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="39"/>
      <source>Unmounting file systems…</source>
      <comment>@status</comment>
      <translation>Dosya sistemleri ayırılıyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="123"/>
      <source>No target system available.</source>
      <translation>Kullanılabilir hedef sistem yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/umount/UmountJob.cpp" line="131"/>
      <source>No rootMountPoint is set.</source>
      <translation>Hiçbir rootMountPoint ayarlanmadı.</translation>
    </message>
  </context>
  <context>
    <name>UsersPage</name>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="189"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after setup.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Bu bilgisayarı birden çok kişi kullanacaksa kurulumdan sonra birden çok kullanıcı hesabı oluşturabilirsiniz.&lt;/small&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/users/UsersPage.cpp" line="195"/>
      <source>&lt;small&gt;If more than one person will use this computer, you can create multiple accounts after installation.&lt;/small&gt;</source>
      <translation>&lt;small&gt;Bu bilgisayarı birden çok kişi kullanacaksa kurulumdan sonra birden çok kullanıcı hesabı oluşturabilirsiniz.&lt;/small&gt;</translation>
    </message>
  </context>
  <context>
    <name>UsersQmlViewStep</name>
    <message>
      <location filename="../src/modules/usersq/UsersQmlViewStep.cpp" line="35"/>
      <source>Users</source>
      <translation>Kullanıcı Hesabı</translation>
    </message>
  </context>
  <context>
    <name>UsersViewStep</name>
    <message>
      <location filename="../src/modules/users/UsersViewStep.cpp" line="48"/>
      <source>Users</source>
      <translation>Kullanıcı Hesabı</translation>
    </message>
  </context>
  <context>
    <name>VariantModel</name>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="232"/>
      <source>Key</source>
      <comment>Column header for key/value</comment>
      <translation>Anahtar</translation>
    </message>
    <message>
      <location filename="../src/calamares/VariantModel.cpp" line="236"/>
      <source>Value</source>
      <comment>Column header for key/value</comment>
      <translation>Değer</translation>
    </message>
  </context>
  <context>
    <name>VolumeGroupBaseDialog</name>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="18"/>
      <source>Create Volume Group</source>
      <translation>Disk Bölümü Grubu Oluştur</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="24"/>
      <source>List of Physical Volumes</source>
      <translation>Fiziksel Disk Bölümlerinin Listesi</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="34"/>
      <source>Volume Group Name:</source>
      <translation>Disk bölümü grubu adı:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="47"/>
      <source>Volume Group Type:</source>
      <translation>Disk bölümü grubu türü:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="60"/>
      <source>Physical Extent Size:</source>
      <translation>Fiziksel genişleme boyutu:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="70"/>
      <source> MiB</source>
      <translation>MiB</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="86"/>
      <source>Total Size:</source>
      <translation>Toplam boyut:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="106"/>
      <source>Used Size:</source>
      <translation>Kullanılan boyut:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="126"/>
      <source>Total Sectors:</source>
      <translation>Toplam dilimler:</translation>
    </message>
    <message>
      <location filename="../src/modules/partition/gui/VolumeGroupBaseDialog.ui" line="146"/>
      <source>Quantity of LVs:</source>
      <translation>LVs miktarı:</translation>
    </message>
  </context>
  <context>
    <name>WelcomePage</name>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="79"/>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="98"/>
      <source>Select application and system language</source>
      <translation>Uygulama ve sistem dilini seç</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="140"/>
      <source>Open donations website</source>
      <translation>Bağış web sitesini aç</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="143"/>
      <source>&amp;Donate</source>
      <translation>&amp;Bağış Yap</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="153"/>
      <source>Open help and support website</source>
      <translation>Yardım ve destek web sitesini aç</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="156"/>
      <source>&amp;Support</source>
      <translation>&amp;Destek</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="166"/>
      <source>Open issues and bug-tracking website</source>
      <translation>Geri bildirim ve hata izleme web sitesi</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="169"/>
      <source>&amp;Known issues</source>
      <translation>&amp;Bilinen hatalar</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="179"/>
      <source>Open release notes website</source>
      <translation>Sürüm notları web sitesini aç</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.ui" line="182"/>
      <source>&amp;Release notes</source>
      <translation>&amp;Sürüm notları</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="235"/>
      <source>About %1 Setup</source>
      <comment>@title</comment>
      <translation>%1 Kurulum Programı Hakkında</translation>
    </message>
    <message>
      <location filename="../src/calamares/DebugWindow.cpp" line="236"/>
      <source>About %1 Installer</source>
      <comment>@title</comment>
      <translation>%1 Kurulum Programı Hakkında</translation>
    </message>
    <message>
      <location filename="../src/modules/welcome/WelcomePage.cpp" line="212"/>
      <source>%1 Support</source>
      <comment>@action</comment>
      <translation>%1 Destek</translation>
    </message>
  </context>
  <context>
    <name>WelcomeQmlViewStep</name>
    <message>
      <location filename="../src/modules/welcomeq/WelcomeQmlViewStep.cpp" line="40"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Hoş Geldiniz</translation>
    </message>
  </context>
  <context>
    <name>WelcomeViewStep</name>
    <message>
      <location filename="../src/modules/welcome/WelcomeViewStep.cpp" line="46"/>
      <source>Welcome</source>
      <comment>@title</comment>
      <translation>Hoş Geldiniz</translation>
    </message>
  </context>
  <context>
    <name>ZfsJob</name>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="102"/>
      <source>Creating ZFS pools and datasets…</source>
      <comment>@status</comment>
      <translation>ZFS havuzları ve veri kümeleri oluşturuluyor...</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="162"/>
      <source>Failed to create zpool on </source>
      <translation>Şurada zpool oluşturulamadı:</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="180"/>
      <source>Configuration Error</source>
      <translation>Yapılandırma Hatası</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="181"/>
      <source>No partitions are available for ZFS.</source>
      <translation>ZFS için kullanılabilir bölüntü yok.</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <source>Internal data missing</source>
      <translation>İçsel veri eksik</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="192"/>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="264"/>
      <source>Failed to create zpool</source>
      <translation>zpool oluşturulamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="336"/>
      <source>Failed to create dataset</source>
      <translation>Veri kümesi oluşturulamadı</translation>
    </message>
    <message>
      <location filename="../src/modules/zfs/ZfsJob.cpp" line="337"/>
      <source>The output was: </source>
      <translation>Çıktı şuydu:</translation>
    </message>
  </context>
  <context>
    <name>calamares-sidebar</name>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="89"/>
      <source>About</source>
      <translation>Hakkında</translation>
    </message>
    <message>
      <location filename="../src/calamares/calamares-sidebar.qml" line="115"/>
      <source>Debug</source>
      <translation>Hata Ayıklama</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="157"/>
      <source>About</source>
      <comment>@button</comment>
      <translation>Hakkında</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="159"/>
      <source>Show information about Calamares</source>
      <comment>@tooltip</comment>
      <translation>Calamares hakkında bilgi göster</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="173"/>
      <source>Debug</source>
      <comment>@button</comment>
      <translation>Hata Ayıklama</translation>
    </message>
    <message>
      <location filename="../src/calamares/CalamaresWindow.cpp" line="175"/>
      <source>Show debug information</source>
      <comment>@tooltip</comment>
      <translation>Hata ayıklama bilgisini göster</translation>
    </message>
  </context>
  <context>
    <name>finishedq</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="36"/>
      <source>Installation Completed</source>
      <translation>Kurulum Tamamlandı</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <translation>%1 bilgisayarınıza kuruldu.&lt;br/&gt;
            Kurduğunuz sistemi şimdi yeniden başlayabilir veya Canlı ortamı kullanmayı sürdürebilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="65"/>
      <source>Close Installer</source>
      <translation>Kurulum Programını Kapat</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="71"/>
      <source>Restart System</source>
      <translation>Sistemi Yeniden Başlat</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <translation>&lt;p&gt;Kurulumun tam günlüğü, Live kullanıcısının ana dizininde installation.log olarak mevcuttur.&lt;br/&gt;
            Bu günlük, hedef sistemin /var/log/installation.log dosyasına kopyalanır.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>finishedq-qt6</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="35"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Kurulum Tamamlandı</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="42"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart into your new system, or continue using the Live environment.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>%1 bilgisayarınıza kuruldu.&lt;br/&gt;
            Kurduğunuz sistemi şimdi yeniden başlayabilir veya Canlı ortamı kullanmayı sürdürebilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="65"/>
      <source>Close Installer</source>
      <comment>@button</comment>
      <translation>Kurulum Programını Kapat</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="71"/>
      <source>Restart System</source>
      <comment>@button</comment>
      <translation>Sistemi Yeniden Başlat</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq-qt6.qml" line="89"/>
      <source>&lt;p&gt;A full log of the install is available as installation.log in the home directory of the Live user.&lt;br/&gt;
            This log is copied to /var/log/installation.log of the target system.&lt;/p&gt;</source>
      <comment>@info</comment>
      <translation>&lt;p&gt;Kurulumun tam günlüğü, Live kullanıcısının ana dizininde installation.log olarak mevcuttur.&lt;br/&gt;
            Bu günlük, hedef sistemin /var/log/installation.log dosyasına kopyalanır.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>finishedq@mobile</name>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="36"/>
      <source>Installation Completed</source>
      <comment>@title</comment>
      <translation>Kurulum Tamamlandı</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="43"/>
      <source>%1 has been installed on your computer.&lt;br/&gt;
            You may now restart your device.</source>
      <comment>@info, %1 is the product name</comment>
      <translation>%1 bilgisayarınıza kuruldu.&lt;br/&gt;
           Artık aygıtınızı yeniden başlatabilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="66"/>
      <source>Close</source>
      <comment>@button</comment>
      <translation>Kapat</translation>
    </message>
    <message>
      <location filename="../src/modules/finishedq/finishedq@mobile.qml" line="72"/>
      <source>Restart</source>
      <comment>@button</comment>
      <translation>Yeniden Başlat</translation>
    </message>
  </context>
  <context>
    <name>keyboardq</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Klavye önizlemesini etkinleştirmek için bir düzen seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Klavye modeli:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Düzen</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Türev</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Sınamak için buraya yazın…</translation>
    </message>
  </context>
  <context>
    <name>keyboardq-qt6</name>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="61"/>
      <source>Select a layout to activate keyboard preview</source>
      <comment>@label</comment>
      <translation>Klavye önizlemesini etkinleştirmek için bir düzen seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="144"/>
      <source>&lt;b&gt;Keyboard model:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</source>
      <comment>@label</comment>
      <translation>&lt;b&gt;Klavye modeli:&amp;nbsp;&amp;nbsp;&lt;/b&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="185"/>
      <source>Layout</source>
      <comment>@label</comment>
      <translation>Düzen</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="258"/>
      <source>Variant</source>
      <comment>@label</comment>
      <translation>Türev</translation>
    </message>
    <message>
      <location filename="../src/modules/keyboardq/keyboardq-qt6.qml" line="311"/>
      <source>Type here to test your keyboard…</source>
      <comment>@label</comment>
      <translation>Sınamak için buraya yazın…</translation>
    </message>
  </context>
  <context>
    <name>localeq</name>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Değiştir</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Dil&lt;/h3&gt; &lt;/br&gt;
                            Sistem yerel ayarı, bazı komut satırı kullanıcı arabirimi öğeleri için dil ve karakter kümesini etkiler. Geçerli ayar: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Yerel&lt;/h3&gt; &lt;/br&gt;
                                Sistem yerel ayarı, sayı ve tarih biçimini etkiler. Geçerli ayar: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
  </context>
  <context>
    <name>localeq-qt6</name>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="76"/>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="106"/>
      <source>Change</source>
      <comment>@button</comment>
      <translation>Değiştir</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="142"/>
      <source>&lt;h3&gt;Languages&lt;/h3&gt; &lt;/br&gt;
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Dil&lt;/h3&gt; &lt;/br&gt;
                            Sistem yerel ayarı, bazı komut satırı kullanıcı arabirimi öğeleri için dil ve karakter kümesini etkiler. Geçerli ayar: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
    <message>
      <location filename="../src/modules/localeq/localeq-qt6.qml" line="213"/>
      <source>&lt;h3&gt;Locales&lt;/h3&gt; &lt;/br&gt;
                                The system locale setting affects the numbers and dates format. The current setting is &lt;strong&gt;%1&lt;/strong&gt;.</source>
      <comment>@info</comment>
      <translation>&lt;h3&gt;Yerel&lt;/h3&gt; &lt;/br&gt;
                                Sistem yerel ayarı, sayı ve tarih biçimini etkiler. Geçerli ayar: &lt;strong&gt;%1&lt;/strong&gt;.</translation>
    </message>
  </context>
  <context>
    <name>notesqml</name>
    <message>
      <location filename="../src/modules/notesqml/notesqml.qml" line="50"/>
      <source>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;These are example release notes.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1&lt;/h3&gt;
            &lt;p&gt;Bunlar örnek sürüm notlarıdır.&lt;/p&gt;</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice, dünya çapında milyonlarca insan tarafından kullanılan güçlü ve ücretsiz bir ofis paketidir. Onu piyasadaki en çok yönlü Ücretsiz ve Açık Kaynak ofis paketi yapan çeşitli uygulamalar içerir. &lt;br/&gt;
                    Varsayılan seçenek.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Bir ofis paketi yüklemek istemiyorsanız Ofis Paketi Yok'u seçmeniz yeterlidir. Gereksinim duyulduğunda, kurulu sisteminize her zaman bir (veya daha fazlasını) ekleyebilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Ofis Paketi Yok</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>Minimal bir masaüstü kurulumu oluşturun, tüm ekstra uygulamaları kaldırın ve daha sonra sisteminize ne eklemek istediğinize karar verin. Böyle bir kurulumda olmayacağına dair örnekler, Ofis Paketi, Ortam Oynatıcısı, Görsel Görüntüleyicisi veya Yazdırma Desteği olmayacaktır. Sadece bir masaüstü, dosya tarayıcısı, paket yöneticisi, metin düzenleyicisi ve basit web tarayıcısı olacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimal Kurulum</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>Lütfen kurulum için bir seçenek seçin veya öntanımlıyı kullanın: LibreOffice içerilir.</translation>
    </message>
  </context>
  <context>
    <name>packagechooserq-qt6</name>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="45"/>
      <source>LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.&lt;br/&gt;
                    Default option.</source>
      <translation>LibreOffice, dünya çapında milyonlarca insan tarafından kullanılan güçlü ve ücretsiz bir ofis paketidir. Onu piyasadaki en çok yönlü Ücretsiz ve Açık Kaynak ofis paketi yapan çeşitli uygulamalar içerir. &lt;br/&gt;
                    Varsayılan seçenek.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="59"/>
      <source>LibreOffice</source>
      <translation>LibreOffice</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="108"/>
      <source>If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.</source>
      <translation>Bir ofis paketi yüklemek istemiyorsanız Ofis Paketi Yok'u seçmeniz yeterlidir. Gereksinim duyulduğunda, kurulu sisteminize her zaman bir (veya daha fazlasını) ekleyebilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="121"/>
      <source>No Office Suite</source>
      <translation>Ofis Paketi Yok</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="172"/>
      <source>Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.</source>
      <translation>Minimal bir masaüstü kurulumu oluşturun, tüm ekstra uygulamaları kaldırın ve daha sonra sisteminize ne eklemek istediğinize karar verin. Böyle bir kurulumda olmayacağına dair örnekler, Ofis Paketi, Ortam Oynatıcısı, Görsel Görüntüleyicisi veya Yazdırma Desteği olmayacaktır. Sadece bir masaüstü, dosya tarayıcısı, paket yöneticisi, metin düzenleyicisi ve basit web tarayıcısı olacak.</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="185"/>
      <source>Minimal Install</source>
      <translation>Minimal Kurulum</translation>
    </message>
    <message>
      <location filename="../src/modules/packagechooserq/packagechooserq-qt6.qml" line="233"/>
      <source>Please select an option for your install, or use the default: LibreOffice included.</source>
      <translation>Lütfen kurulum için bir seçenek seçin veya öntanımlıyı kullanın: LibreOffice içerilir.</translation>
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
            &lt;p&gt;Bu, Flickable içeriğine sahip RichText'teki seçenekleri gösteren örnek bir QML dosyası.&lt;/p&gt;

            &lt;p&gt;RichText ile QML HTML etiketleri kullanabilir, Flickable içerik dokunmatik ekranlar için yararlıdır.&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Kalın yazı&lt;/b&gt;&lt;/p&gt;
            &lt;p&gt;&lt;i&gt;Yatık yazı&lt;/i&gt;&lt;/p&gt;
            &lt;p&gt;&lt;u&gt;Altı çizili yazı&lt;/u&gt;&lt;/p&gt;
            &lt;p&gt;&lt;center&gt;Ortaya hizalı yazı.&lt;/center&gt;&lt;/p&gt;
            &lt;p&gt;&lt;s&gt;Üzeri çizili yazı&lt;/s&gt;&lt;/p&gt;

            &lt;p&gt;Kod örneği:
            &lt;code&gt;ls -l /home&lt;/code&gt;&lt;/p&gt;

            &lt;p&gt;&lt;b&gt;Listeler:&lt;/b&gt;&lt;/p&gt;
            &lt;ul&gt;
                &lt;li&gt;Intel CPU sistemler&lt;/li&gt;
                &lt;li&gt;AMD CPU sistemler&lt;/li&gt;
            &lt;/ul&gt;

            &lt;p&gt;Dikey sarma çubuğu ayarlanabilir, geçerli genişlik 10 olarak ayarlanmıştır.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/release_notes.qml" line="76"/>
      <source>Back</source>
      <translation>Geri</translation>
    </message>
  </context>
  <context>
    <name>usersq</name>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="43"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Oturum açmak ve yönetici görevlerini gerçekleştirmek için kullanıcı adınızı ve kimlik bilgilerinizi seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="56"/>
      <source>What is your name?</source>
      <translation>Adınız nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="63"/>
      <source>Your full name</source>
      <translation>Tam Adınız</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="80"/>
      <source>What name do you want to use to log in?</source>
      <translation>Oturum açmak için hangi adı kullanmak istersiniz?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="87"/>
      <source>Login name</source>
      <translation>Oturum Açma Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="116"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Bu bilgisayarı birden çok kişi kullanacaksa kurulumdan sonra çoklu hesaplar oluşturabilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="129"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yalnızca küçük harflere, sayılara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="138"/>
      <source>root is not allowed as username.</source>
      <translation>root, uygun bir kullanıcı adı değildir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="147"/>
      <source>What is the name of this computer?</source>
      <translation>Bu bilgisayarın adı nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="153"/>
      <source>Computer name</source>
      <translation>Bilgisayar Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="180"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Bilgisayarı ağ üzerinde herkese görünür yaparsanız bu ad kullanılacaktır.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="193"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>En az iki karakter olmak üzere yalnızca harflere, sayılara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="202"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost, makine adı olarak uygun değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="211"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Hesabınızın güvenliğini sağlamak için bir parola seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="221"/>
      <source>Password</source>
      <translation>Parola</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="238"/>
      <source>Repeat password</source>
      <translation>Parolayı Yinele</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="265"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Yazım hatalarının denetlenebilmesi için aynı parolayı iki kez girin. İyi bir şifre, harflerin, sayıların ve noktalama işaretlerinin bir karışımını içerir; en az sekiz karakter uzunluğunda olmalı ve düzenli aralıklarla değiştirilmelidir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="297"/>
      <source>Reuse user password as root password</source>
      <translation>Kullanıcı parolasını yetkili kök parolası olarak yeniden kullan</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="305"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Yönetici hesabı için aynı parolayı kullanın.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="318"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Hesabınızı güvende tutmak için bir kök parolası seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="328"/>
      <source>Root password</source>
      <translation>Kök Parolası</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="346"/>
      <source>Repeat root password</source>
      <translation>Kök Parolasını Yinele</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="372"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Yazım hatalarının denetlenebilmesi için aynı parolayı iki kez girin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="402"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Parola sormadan kendiliğinden oturum aç</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="410"/>
      <source>Validate passwords quality</source>
      <translation>Parola kalitesini doğrulayın</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq.qml" line="420"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Bu kutu işaretlendiğinde, parola gücü denetlenir ve zayıf bir parola kullanamazsınız.</translation>
    </message>
  </context>
  <context>
    <name>usersq-qt6</name>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="42"/>
      <source>Pick your user name and credentials to login and perform admin tasks</source>
      <translation>Oturum açmak ve yönetici görevlerini gerçekleştirmek için kullanıcı adınızı ve kimlik bilgilerinizi seçin</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="55"/>
      <source>What is your name?</source>
      <translation>Adınız nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="62"/>
      <source>Your full name</source>
      <translation>Tam Adınız</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="79"/>
      <source>What name do you want to use to log in?</source>
      <translation>Oturum açmak için hangi adı kullanmak istiyorsunuz?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="86"/>
      <source>Login name</source>
      <translation>Oturum Açma Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="115"/>
      <source>If more than one person will use this computer, you can create multiple accounts after installation.</source>
      <translation>Bu bilgisayarı birden çok kişi kullanacaksa kurulumdan sonra çoklu hesaplar oluşturabilirsiniz.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="128"/>
      <source>Only lowercase letters, numbers, underscore and hyphen are allowed.</source>
      <translation>Yalnızca küçük harflere, sayılara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="137"/>
      <source>root is not allowed as username.</source>
      <translation>root, uygun bir kullanıcı adı değildir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="146"/>
      <source>What is the name of this computer?</source>
      <translation>Bu bilgisayarın adı nedir?</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="152"/>
      <source>Computer name</source>
      <translation>Bilgisayar Adı</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="179"/>
      <source>This name will be used if you make the computer visible to others on a network.</source>
      <translation>Bilgisayarı ağ üzerinde herkese görünür yaparsanız bu ad kullanılacaktır.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="192"/>
      <source>Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.</source>
      <translation>En az iki karakter olmak üzere yalnızca harflere, sayılara, alt çizgiye ve kısa çizgiye izin verilir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="201"/>
      <source>localhost is not allowed as hostname.</source>
      <translation>localhost, makine adı olarak uygun değil.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="210"/>
      <source>Choose a password to keep your account safe.</source>
      <translation>Hesabınızın güvenliğini sağlamak için bir parola seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="220"/>
      <source>Password</source>
      <translation>Parola</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="237"/>
      <source>Repeat password</source>
      <translation>Parolayı Yinele</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="264"/>
      <source>Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.</source>
      <translation>Yazım hatalarının denetlenebilmesi için aynı parolayı iki kez girin. İyi bir şifre, harflerin, sayıların ve noktalama işaretlerinin bir karışımını içerir; en az sekiz karakter uzunluğunda olmalı ve düzenli aralıklarla değiştirilmelidir.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="296"/>
      <source>Reuse user password as root password</source>
      <translation>Kullanıcı parolasını yetkili kök parolası olarak yeniden kullan</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="304"/>
      <source>Use the same password for the administrator account.</source>
      <translation>Yönetici hesabı için aynı parolayı kullan.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="317"/>
      <source>Choose a root password to keep your account safe.</source>
      <translation>Hesabınızı güvende tutmak için bir kök parolası seçin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="327"/>
      <source>Root password</source>
      <translation>Kök Parolası</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="345"/>
      <source>Repeat root password</source>
      <translation>Kök Parolasını Yinele</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="371"/>
      <source>Enter the same password twice, so that it can be checked for typing errors.</source>
      <translation>Yazım hatalarının denetlenebilmesi için aynı parolayı iki kez girin.</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="401"/>
      <source>Log in automatically without asking for the password</source>
      <translation>Parola sormadan kendiliğinden oturum aç</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="409"/>
      <source>Validate passwords quality</source>
      <translation>Parola kalitesini doğrulayın</translation>
    </message>
    <message>
      <location filename="../src/modules/usersq/usersq-qt6.qml" line="419"/>
      <source>When this box is checked, password-strength checking is done and you will not be able to use a weak password.</source>
      <translation>Bu kutu işaretlendiğinde, parola gücü denetlenir ve zayıf bir parola kullanamazsınız.</translation>
    </message>
  </context>
  <context>
    <name>welcomeq</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1 &lt;quote&gt;%2&lt;/quote&gt; kurucusuna hoş geldiniz&lt;/h3&gt;
           &lt;p&gt;Bu program size bazı sorular soracak ve bilgisayarınıza %1 kuracak.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="69"/>
      <source>Support</source>
      <translation>Destek</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Bilinen Sorunlar</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Sürüm Notları</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq.qml" line="103"/>
      <source>Donate</source>
      <translation>Bağış</translation>
    </message>
  </context>
  <context>
    <name>welcomeq-qt6</name>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="38"/>
      <source>&lt;h3&gt;Welcome to the %1 &lt;quote&gt;%2&lt;/quote&gt; installer&lt;/h3&gt;
            &lt;p&gt;This program will ask you some questions and set up %1 on your computer.&lt;/p&gt;</source>
      <translation>&lt;h3&gt;%1 &lt;quote&gt;%2&lt;/quote&gt; kurucusuna hoş geldiniz&lt;/h3&gt;
           &lt;p&gt;Bu program size bazı sorular soracak ve bilgisayarınıza %1 kuracak.&lt;/p&gt;</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="69"/>
      <source>Support</source>
      <translation>Destek</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="80"/>
      <source>Known Issues</source>
      <translation>Bilinen Sorunlar</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="91"/>
      <source>Release Notes</source>
      <translation>Sürüm Notları</translation>
    </message>
    <message>
      <location filename="../src/modules/welcomeq/welcomeq-qt6.qml" line="103"/>
      <source>Donate</source>
      <translation>Bağış</translation>
    </message>
  </context>
</TS>
